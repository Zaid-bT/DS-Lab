#pragma once

#include <QWidget>
#include <vector>

class MazeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MazeWidget(QWidget *parent = nullptr);

    void generateMaze(int rows, int cols);   // call this from mainwindow
    void addLoops(int c);

    bool hardMode = false;
    bool medMode = false;
    bool impMode = false;

    void setStart(int x,int y);
    void setEnd(int x,int y);
    bool canMove(int r, int c, int nr, int nc);
    //bool isWall(int row, int col);

    bool lvlFinished = false;

    bool bfsOptimalPath();     // finds shortest path
    QVector<QPoint> shortestPath;   // store final optimal path
    bool showOptimal = false;

    int getRows() const { return rows; }
    int getCols() const { return cols; }

    //getters for walls
    const std::vector<std::vector<bool>>& getVerticalWalls() const { return verticalWalls; }
    const std::vector<std::vector<bool>>& getHorizontalWalls() const { return horizontalWalls; }
    //getter for start and end cells
    QPair<int,int> getStartCell() const { return startCell; }
    QPair<int,int> getEndCell() const { return endCell; }

    //setter for walls
    void setWalls(const std::vector<std::vector<bool>>& vWalls,
                  const std::vector<std::vector<bool>>& hWalls)
    {
        verticalWalls = vWalls;
        horizontalWalls = hWalls;
    }

    void copyMazeFrom(const MazeWidget *other);

    void startOptimalAnimation(int intervalMs = 80); // start reveal animation

    // setters for copying maze/start/end/user path from main page
    void setUserPath(const std::vector<QPair<int,int>>& path); // copy user path
    const std::vector<QPair<int,int>>& getUserPath() const { //getter for user path
        return userPath;
    }



protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override; // to take user input

signals:
    void levelCompleted(); //tells Qt that MAzeWidge can emit this signal..
    void optimalAnimationFinished();  // emits signal when animation ends


private:
    QVector<QVector<int>> maze;

    int rows = 0;
    int cols = 0;
    int cellSize = 20 ;


    // bool userBlinkVisible= true;
    // QTimer *blinkTimer ;

    QPair<int,int> startCell = {0, 0};// top left cell
    QPair<int,int> endCell = {0, 0};   // bottom right cell

    QPair<int,int> userPos = {0, 0};  // current position in grid
    std::vector<QPair<int,int>> userPath; // stores the path


    std::vector<std::vector<bool>> visited;
    std::vector<std::vector<bool>> verticalWalls;
    std::vector<std::vector<bool>> horizontalWalls;

    void carve(int r, int c);

    int startX,startY;
    int endX,endY;
    QVector<QPoint>bfs();

    //std::vector<QPoint> shortestPath;    // result of bfs (x=col,y=row)
    int optimalStep = 0;                 // count how many steps revealed so far
    bool optimalAnimating = false;       //
    bool optimalShownFully = false;      // finished animation
    QTimer *optimalTimer = nullptr;

    // copy of user path to display on solution page
    std::vector<QPair<int,int>> copiedUserPath;

private slots:
    void onOptimalTimerTick();

};
