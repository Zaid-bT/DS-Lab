#include "MazeWidget.h"
#include <QPainter>
#include <QRandomGenerator>
#include <QKeyEvent> //key inputs
#include <QQueue> //BFS works on Queue
#include <QTimer> //added back to animation of solution path (//blinking doesnt look gud so removed all functionality)

MazeWidget::MazeWidget(QWidget *parent) //contructor
    : QWidget(parent)
{
    setMinimumSize(400, 400);

    setFocusPolicy(Qt::StrongFocus); // without this keyPressEvent wont work


    // ADD BLINK TO SHOW CURRENT POSITION ON MAZE
    // blinkTimer = new QTimer(this);
    // connect(blinkTimer, &QTimer::timeout, this, [this]() {
    //     userBlinkVisible = !userBlinkVisible; // toggle visibility
    //     update(); //repaint maze
    // });
    // blinkTimer->start(300); // blink every 300 ms

}

//setter
void MazeWidget::setStart(int x, int y)
{
    startX = x;
    startY = y;
}

void MazeWidget::setEnd(int x, int y)
{
    endX = x;
    endY = y;
}
// bool MazeWidget::isWall(int row, int col) //check for wall at that position
// {
//     // safety check
//     if (row < 0 || row >= rows || col < 0 || col >= cols)
//         return false;

//     return maze[row][col] == 1;
// }


void MazeWidget::generateMaze(int r, int c) // rn maze has only one solution from start to end
// recursive backtracking always makes a perfect maze( one sol only)
{
    rows = r;
    cols = c;

    visited = std::vector<std::vector<bool>>(rows, std::vector<bool>(cols, false));  // check that if a cell has been visited
    verticalWalls = std::vector<std::vector<bool>>(rows, std::vector<bool>(cols + 1, true)); //for vertical walls in maze..col+1 to make border
    horizontalWalls = std::vector<std::vector<bool>>(rows + 1, std::vector<bool>(cols, true)); // horizontal maze in walls between rows

    carve(0,0);  // start maze from top left

    int loops = 0;
    // this part adds multiple solutions to maze...
    if(hardMode){
        loops = (rows * cols)/18; // more walls removed
        hardMode = false;
    }else if(medMode){
        medMode = false;
        loops = (rows*cols)/10;
    }else if(impMode){
        impMode = false;
        loops = (rows * cols) / 20;
    }else{

        loops = (rows * cols) / 2; //density of removing walls....greater value= less walls removed
    }

    addLoops(loops);

    startCell = {0, 0};
    endCell   = {rows - 1, cols - 1};

    userPos = startCell;
    userPath.clear();
    userPath.push_back(userPos);


    update();
}


void MazeWidget::addLoops(int loopCount) // adding random loops in maze add more than one solution to maze
{
    if (rows == 0 || cols == 0) return;

    QRandomGenerator *rng = QRandomGenerator::global();

    for (int i = 0; i < loopCount; i++)
    {
        int r = rng->bounded(rows);
        int c = rng->bounded(cols);

        bool removeHorizontal = rng->bounded(2); // random pick

        if (removeHorizontal)
        {
            if (r < rows && c < cols)
                horizontalWalls[r][c] = false;   // remove wall
        }
        else
        {
            if (r < rows && c < cols)
                verticalWalls[r][c] = false;     // remove wall
        }
    }
}


void MazeWidget::carve(int r, int c) //Recursive Backtracking here
{
    visited[r][c] = true;

    // order to visit neighbors (random)
    QVector<int> dirs = {0, 1, 2, 3};
    std::shuffle(dirs.begin(), dirs.end(), *QRandomGenerator::global());

    for (int d : dirs)
    {
        int nr = r;
        int nc = c;

        //add walls
        if (d == 0) nr = r - 1;     // up
        if (d == 1) nr = r + 1;     // down
        if (d == 2) nc = c - 1;     // left
        if (d == 3) nc = c + 1;     // right


        if (nr < 0 || nr >= rows || nc < 0 || nc >= cols)
            continue;

        if (visited[nr][nc])
            continue;

        // remove walls
        if (d == 0) horizontalWalls[r][c] = false;         // up
        if (d == 1) horizontalWalls[r + 1][c] = false;     // down
        if (d == 2) verticalWalls[r][c] = false;           // left
        if (d == 3) verticalWalls[r][c + 1] = false;       // right


        carve(nr, nc); // Recursion
    }
}

void MazeWidget::paintEvent(QPaintEvent *)// all drawings happen here
{
    if (rows == 0 || cols == 0)
        return;

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    cellSize = std::min(width() / cols, height() / rows);
    int w = width();
    int h = height();

    int cellW = w / cols;
    int cellH = h / rows;

    p.fillRect(0, 0, w, h, QColor("#0a0a0a"));  // dark background


    // horizontal walls
    p.setPen(QPen(QColor("#0c8900"), 3));  // neon green, thicker line
    for (int r = 0; r <= rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            if (horizontalWalls[r][c])
            {
                p.drawLine(c * cellW, r * cellH, (c + 1) * cellW, r * cellH);
            }
        }
    }

    // vertical walls
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c <= cols; c++)
        {
            if (verticalWalls[r][c])
            {
                p.drawLine(c * cellW, r * cellH,c * cellW, (r + 1) * cellH);
            }
        }
    }

    //  start marker
    p.setBrush(QColor("yellow")); /*light green  */
    p.setPen(Qt::NoPen);
    p.drawEllipse(startCell.second * cellW + cellW/4,startCell.first * cellH + cellH/4,cellW/2, cellH/2);

    //  end marker
    p.setBrush(Qt::red);
    p.setPen(Qt::NoPen);
    p.drawEllipse(endCell.second * cellW + cellW/4, endCell.first * cellH + cellH/4, cellW/2, cellH/2);



    // user path draw...this path makes a better trail but the dimensions hide the maze so had to change to different block look of trail
    // user path — solid cyan - solid fill is hiding the maze boundaries
    // p.setBrush(QColor("#00FFFF")); // cyan
    // p.setPen(Qt::NoPen);
    // for (auto &cell : userPath) {
    //     p.drawRect(cell.second*cellW,
    //                cell.first*cellH,
    //                cellW, cellH); // full cell fill
    // }



    // new user path – connected trail without hiding walls
    p.setBrush(QColor("#00FFFF")); // neon cyan
    p.setPen(Qt::NoPen);

    int marginW = cellW * 0.20;   // 20% left and right...rectangle dimensions fit inside maze
    int marginH = cellH * 0.20;   // 20% top and bottom
    for (auto &cell : userPath){
        int r = cell.first;
        int c = cell.second;

        p.drawRect(
            c * cellW + marginW,
            r * cellH + marginH,
            cellW - 2 * marginW,
            cellH - 2 * marginH
            );
    }


    // current player marker...updated it to look better
    int r = userPos.first;
    int c = userPos.second;

    int playerW = cellW * 0.6;
    int playerH = cellH * 0.6;

    QColor playerColor = QColor("#00FFFF"); // solid neon cyan
    QColor glowColor = QColor("yellow"); // glow...marks current pointer properly

    // glow behind...shows proper outlines of current position
    p.setBrush(glowColor);
    p.drawRect(
        c * cellW + (cellW - playerW) / 2 - 2,
        r * cellH + (cellH - playerH) / 2 - 2,
        playerW + 4,
        playerH + 4
        );


    // Player solid fill
    p.setBrush(playerColor);
    p.drawRect(
        c * cellW + (cellW - playerW) / 2,
        r * cellH + (cellH - playerH) / 2,
        playerW,
        playerH
        );


    // if (userBlinkVisible) //displays blinking
    // {
    //     p.setBrush(QColor(255, 0, 255, 200)); // magenta blinking user marker
    //     p.setPen(Qt::NoPen);

    //     int r = userPos.first;
    //     int c = userPos.second;

    //     p.drawRect(c * cellSize, r * cellSize, cellSize, cellSize);
    // }


    // display BFS solution
    p.setPen(Qt::NoPen);

    QColor optColor("#FFFF66");             // neon yellow (trail)
    QColor optGlow(255, 255, 140,180);      // glow behind

    // Draw glow BEHIND BFS trail (inside the cell, same size as trail, but soft)
    for (int i = 0; i < optimalStep && i < shortestPath.size(); ++i) {
        QPoint pt = shortestPath[i];
        int cx = pt.x();
        int ry = pt.y();

        p.setBrush(optGlow);
        p.drawRect(cx * cellW + marginW - 2,
                   ry * cellH + marginH - 2,
                   (cellW - 2 * marginW) + 4,
                   (cellH - 2 * marginH) + 4);
    }

    //Draw BFS trail itself (same style as user path rectangle)
    p.setBrush(optColor);
    for (int i = 0; i < optimalStep && i < shortestPath.size(); ++i) {
        QPoint pt = shortestPath[i];
        int cx = pt.x();
        int ry = pt.y();

        p.drawRect(cx * cellW + marginW,
                   ry * cellH + marginH,
                   cellW - 2 * marginW,
                   cellH - 2 * marginH);
    }

    //  After animation ends: show full BFS path + user path on top
    if (!optimalAnimating && optimalShownFully) {

        // Draw full BFS (final state)
        p.setBrush(optColor);
        for (auto &pt : shortestPath) {
            int cx = pt.x();
            int ry = pt.y();
            p.drawRect(cx * cellW + marginW,
                       ry * cellH + marginH,
                       cellW - 2 * marginW,
                       cellH - 2 * marginH);
        }

        // Draw full user path on top for comparison
        p.setBrush(QColor("#00FFFF")); // neon cyan user path
        for (auto &cell : copiedUserPath) {
            int rr = cell.first;
            int cc = cell.second;

            p.drawRect(cc * cellW + marginW,
                       rr * cellH + marginH,
                       cellW - 2 * marginW,
                       cellH - 2 * marginH);
        }
    }

}


void MazeWidget::keyPressEvent(QKeyEvent *event) //for taking inputs (arrow keys)
{
    if(lvlFinished){
        return; //user doesnt move after finishing
    }
    int r = userPos.first;
    int c = userPos.second;

    if (event->key() == Qt::Key_Up && r > 0 && !horizontalWalls[r][c])
        r--;
    else if (event->key() == Qt::Key_Down && r < rows-1 && !horizontalWalls[r+1][c])
        r++;
    else if (event->key() == Qt::Key_Left && c > 0 && !verticalWalls[r][c])
        c--;
    else if (event->key() == Qt::Key_Right && c < cols-1 && !verticalWalls[r][c+1])
        c++;

    if (userPos.first != r || userPos.second != c)
    {
        userPos = {r, c};
        userPath.push_back(userPos);
        update(); // repaint

        // Check if reached end
        if (userPos == endCell)
        {
            lvlFinished = true;
            emit levelCompleted(); // signal to MainWindow
        }
    }
}

void MazeWidget::copyMazeFrom(const MazeWidget *other) //copy the same maze on solution page rather than generating a new one
{
    this->rows = other->rows;
    this->cols = other->cols;

    this->verticalWalls = other->verticalWalls;
    this->horizontalWalls = other->horizontalWalls;

    this->startCell = other->startCell;
    this->endCell = other->endCell;

    this->setStart(startCell.second, startCell.first);
    this->setEnd(endCell.second, endCell.first);

    update();
}

void MazeWidget::setUserPath(const std::vector<QPair<int,int>>& path)
{
    copiedUserPath = path;
    update();
}

bool MazeWidget::canMove(int r, int c, int nr, int nc) //checks for whether path can move
{
    //check out of bounds
    if (nr < 0 || nr >= rows || nc < 0 || nc >= cols)
        return false;

    // Moving UP
    if (nr == r - 1 && nc == c)
        return !horizontalWalls[r][c];

    // Moving DOWN
    if (nr == r + 1 && nc == c)
        return !horizontalWalls[r + 1][c];

    // Moving LEFT
    if (nr == r && nc == c - 1)
        return !verticalWalls[r][c];

    // Moving RIGHT
    if (nr == r && nc == c + 1)
        return !verticalWalls[r][c + 1];

    return false;
}


bool MazeWidget::bfsOptimalPath()
{
    shortestPath.clear();

    // Directions (up, right, down, left)
    int dx[4] = { 0, 1, 0, -1 };
    int dy[4] = { -1, 0, 1, 0 };

    QVector<QVector<bool>> visited(rows, QVector<bool>(cols, false));
    QVector<QVector<QPoint>> parent(rows, QVector<QPoint>(cols, QPoint(-1,-1)));

    QQueue<QPoint> q;

    // BFS uses (row, col) coordinate system
    int sr = startY;
    int sc = startX;
    int er = endY;
    int ec = endX;

    q.enqueue(QPoint(sc, sr));  // BFS uses x = column,y=rows
    visited[sr][sc] = true;

    while (!q.isEmpty())
    {
        QPoint cur = q.dequeue();
        int r = cur.y();
        int c = cur.x();

        if (r == er && c == ec)// check for reaching end
        {
            QPoint p(c, r);
            while (p != QPoint(-1, -1))
            {
                shortestPath.push_back(p);
                QPoint parentCell = parent[p.y()][p.x()];
                p = parentCell;
            }
            std::reverse(shortestPath.begin(), shortestPath.end());
            return true;
        }

        //explore all 4 directions
        for (int i = 0; i < 4; i++)
        {
            int nr = r + dx[i];
            int nc = c + dy[i];

            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols)
                continue;

            if (!visited[nr][nc] && canMove(r, c, nr, nc))
            {
                visited[nr][nc] = true;
                parent[nr][nc] = QPoint(c, r);
                q.enqueue(QPoint(nc, nr));
            }
        }
    }

    return false;   // no path....doesnt matter as there is always a path
}


void MazeWidget::startOptimalAnimation(int intervalMs)
{
    if (shortestPath.empty()) {
        // ensure BFS already computed. If not, compute now:
        if(!bfsOptimalPath()) {
            // no path found; still signal finished so UI doesn't hang
            optimalShownFully = true;
            emit optimalAnimationFinished();
            update();
            return;
        }
    }

    // reset state
    optimalStep = 0;
    optimalAnimating = true;
    optimalShownFully = false;

    if (!optimalTimer) {
        optimalTimer = new QTimer(this);
        connect(optimalTimer, &QTimer::timeout, this, &MazeWidget::onOptimalTimerTick);
    }
    optimalTimer->start(intervalMs);
}

void MazeWidget::onOptimalTimerTick() //reveals step by step animation
{
    if (!optimalAnimating){
        if (optimalTimer) optimalTimer->stop();
        return;
    }

    // reveal next step
    if (optimalStep < static_cast<int>(shortestPath.size())) {
        ++optimalStep;
        update(); // repaint with extended path
    }

    if (optimalStep >= static_cast<int>(shortestPath.size())) {
        // animation finished
        optimalAnimating = false;
        optimalShownFully = true;
        if (optimalTimer) optimalTimer->stop();

        emit optimalAnimationFinished();
        update(); // final repaint to show full path + user path
    }
}

// all members used are children of QDesigner/QWidget so destructor is not needed...Qt handles automatically
