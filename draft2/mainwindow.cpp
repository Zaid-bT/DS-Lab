#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QMovie>
#include <QTimer>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->statusbar->showMessage("PAGE 1");

    this->setStyleSheet(
        //NO NEED TO ADD COLORS TO STACKWIDGETS...CHANGING MAINWINDOW COLOR DOES THE JOB
        //STACKWIDGET BACKGROUND COLOR OVERRIDES BUTTON BACKGROUND COLOR

        "QLabel {"  // applies to all label
        "    color: #00FF88;" //neon green
        "    font-size: 40px;"
        "    font-weight: bold;"
        "   font-family: Orbitron;"
        "   letter spacing: 5px"
        "}"

        "QPushButton {"  // applies to all buttons
        "    background-color: #1A1A1A;"
        "    color: #00FF88;"
        "    border: 2px solid #00FF88;"
        "    border-radius: 10px;"
        "    padding: 10px 18px;"
        "    font-size: 16px;"
        "    font-weight: bold;"
        "}"

        "QPushButton:hover {"
        "    background-color: #00994D;"
        "    color: #FFFFFF;"
        "}"

        "QPushButton:pressed {"
        "    background-color: #00FF88;"
        "    color: #FFFFFF;"
        "}"
        );


    connect(ui->mazeWidget, &MazeWidget::levelCompleted,this, &MainWindow::onLevelCompleted); /*connects levelCompleted(signal) from mazewidget to
                                                                                                    onLevelCompleted(slot) in mainwindow*/

    connect(ui->optimalPath, &MazeWidget::optimalAnimationFinished,
            this, &MainWindow::onOptimalAnimationFinished);


}



MainWindow::~MainWindow()
{
    delete ui;
}

// page index in ui: [start(pg1),difficulty(pg4),maze(pg2),sol(pg3)] = [0,1,2,3]

void MainWindow::on_startButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1); // goes to pg2 (from pg1)
    ui->statusbar->showMessage("PAGE 2");
}

void MainWindow::on_easyButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2); // goes to pg3 (maze page)
    ui->statusbar->showMessage("PAGE 3");

    ui->mazeWidget->lvlFinished = false; //restores movement

    //had to promote the new widget to MazeWidget so it can use the functions on MazeWidget.cpp
    MazeWidget *easyMaze = ui->page_2->findChild<MazeWidget*>("mazeWidget");
    if (!easyMaze) {
        qDebug() << "MazeWidget not found!";
        return;
    }
    easyMaze->generateMaze(20, 20);
    ui->mazeWidget->setFocus();
}


void MainWindow::on_hardButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2); // goes to pg3 (maze page)
    ui->statusbar->showMessage("PAGE 3");

    ui->mazeWidget->lvlFinished = false;

    MazeWidget *hardMaze = ui->page_2->findChild<MazeWidget*>("mazeWidget");
    if (!hardMaze){ //troubleshoot
        qDebug() << "MazeWidget not found!";
        return;
    }
    hardMaze->generateMaze(35, 35); //larger maze size
    ui->mazeWidget->hardMode = true;
    ui->mazeWidget->setFocus();

}


void MainWindow::on_medButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2); // goes to pg3 (maze page)
    ui->statusbar->showMessage("PAGE 3");

    ui->mazeWidget->lvlFinished = false;

    MazeWidget *medMaze = ui->page_2->findChild<MazeWidget*>("mazeWidget");
    if (!medMaze){
        qDebug() << "MazeWidget not found!";
        return;
    }
    medMaze->generateMaze(25, 25); //larger maze size
    ui->mazeWidget->medMode = true;
    ui->mazeWidget->setFocus();
}


void MainWindow::on_impButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2); // goes to pg3 (maze page)
    ui->statusbar->showMessage("PAGE 3");


    ;

    MazeWidget *impMaze = ui->page_2->findChild<MazeWidget*>("mazeWidget");
    if (!impMaze){
        qDebug() << "MazeWidget not found!";
        return;
    }
    impMaze->generateMaze(50, 50); //larger maze size
    ui->mazeWidget->medMode = true;
    ui->mazeWidget->setFocus();
}


void MainWindow::onLevelCompleted(){
    QMessageBox msg;
    msg.setWindowTitle("Maze Completed!");
    msg.setText("You have completed the maze!");
    msg.setIcon(QMessageBox::Information);
    QPushButton *showBtn = msg.addButton("Show Solution", QMessageBox::AcceptRole);

    msg.exec();  // wait for user action

    if (msg.clickedButton() == showBtn)
    {
        ui->stackedWidget->setCurrentIndex(3); // move to solution page (pg3)

        //Copy start and end positions from Pg2 to pg3
        ui->optimalPath->setStart(ui->mazeWidget->getStartCell().second,
                                  ui->mazeWidget->getStartCell().first);

        ui->optimalPath->setEnd(ui->mazeWidget->getEndCell().second,
                                ui->mazeWidget->getEndCell().first);

        //Copy same walls instead of generating new ones
        ui->optimalPath->setWalls(ui->mazeWidget->getVerticalWalls(),
                                ui->mazeWidget->getHorizontalWalls());


        ui->optimalPath->copyMazeFrom(ui->mazeWidget); //copy maze
        ui->optimalPath->setUserPath(ui->mazeWidget->getUserPath());


        //BFS on the SAME maze
        ui->optimalPath->bfsOptimalPath();

        //start BFS animation
        ui->optimalPath->startOptimalAnimation();

        ui->optimalPath->update();
    }


    ui->statusbar->showMessage("PAGE 4");


}



void MainWindow::onOptimalAnimationFinished()
{
    // delay
    QTimer::singleShot(3000,this,[this](){   // 3 sec buffer

        QMessageBox msg;
        msg.setWindowTitle("Level Completed!");

        msg.setText("Optimal solution has been revealed.\nWhat would you like to do?");
        msg.setIcon(QMessageBox::Question);

        QPushButton *goBack = msg.addButton("Choose Difficulty", QMessageBox::AcceptRole);
        QPushButton *exitBtn = msg.addButton("Exit Game", QMessageBox::RejectRole);

        msg.exec();

        if (msg.clickedButton() == goBack)
        {
            ui->stackedWidget->setCurrentIndex(1);  // Difficulty selection page
        }
        else if (msg.clickedButton() == exitBtn)
        {
            close(); // closes the application
        }
    });
}

