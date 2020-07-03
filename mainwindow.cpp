#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <vector>
#include <unistd.h>
#include <QTableView>
#include <QVector>
#include <QPushButton>
#include <QThread>
#include <QString>
#include <unistd.h>


typedef std::vector<std::vector<int> > GameGrid;
typedef  QVector<QRect> GameView;

using namespace std;



int gameColumns;
int gameRows;
const int cellSize = 10;
const QString play = " ▶️ ";
const QString pause = "❙❙";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    flag = false;
    game = false;
    rPentomino = pentomino();
    GameView gameView = getGameView();
    mainGrid = GameGrid(gameRows, vector<int>(gameColumns, 0));
    timer = new QTimer(this);

     ui->pushButton->setText(play);

    connect(timer, SIGNAL(timeout()),
            this, SLOT(stepForward()));


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    game = !game;
    startStop();
 }



void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    game = false;
    startStop();
}


void MainWindow::paintEvent(QPaintEvent *event){

    gameView = getGameView();
    QPainter painter( this);
    QPen pen(Qt::black);
    QBrush brush(Qt::black);
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawRects(gameView);

}



//updates size variables
void MainWindow::resizeEvent(QResizeEvent *event){
    gameColumns = this->geometry().width() / cellSize;
    gameRows = this-> frameGeometry().height() / cellSize;
     mainGrid = GameGrid(gameRows, vector<int>(gameColumns, 0));
     flag = false;
     game = false;
     startStop();
}



void MainWindow::copyGrid(GameGrid& mainGrid, GameGrid& grid2){

    for (unsigned int i = 0; i < mainGrid.size(); i++) {
        for (unsigned int j = 0; j < mainGrid.size(); j++) { grid2[i][j] = mainGrid[i][j]; }
    }

}

void MainWindow::updateGameBoard()
{

       for(int i = 0; i < rPentomino.size(); ++i){
         for(int j = 0; j < rPentomino[i].size(); j++){
             mainGrid[gameRows/3 + i][gameColumns/8+j] = rPentomino[i][j];

         }
       }


}

void MainWindow::cellState(GameGrid& mainGrid)
{

    GameGrid grid2(gameRows, vector<int>(gameColumns, 0));
     copyGrid(mainGrid, grid2);

     for (unsigned int i = 1; i < mainGrid.size()-1; i++) {
         for (unsigned int b = 1; b < mainGrid[i].size()-1; b++) {
             int life = 0;
             for (int c = -1; c < 2; c++) {
                 for (int d = -1; d < 2; d++) {
                     if (!(c == 0 && d == 0)) {
                         if (grid2[i + c][b + d] == 1) {
                            ++life;
                            }
                     }
                 }
             }

           if (life < 2) {
               mainGrid[i][b] = 0; }
           else if (life == 3) {
               mainGrid[i][b] = 1; }
           else if (life > 3) {
               mainGrid[i][b] = 0;
           }
         }
     }


}

void MainWindow::startStop()
{
    if(game){
        ui->pushButton->setText(pause);

        timer->start(750 - ui->horizontalSlider->value());
    }else{
         ui->pushButton->setText(play);
       timer->stop();
    }

}

void MainWindow::stepForward()
{

        if(!flag)    updateGameBoard();
        update();
        flag = true;
        cellState(mainGrid);

}




GameGrid MainWindow::pentomino(){

            GameGrid rPentomino =
    {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
    {1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };

//            {{0,0,0},{1,1,1},{0,0,0}};

    return rPentomino;

}



GameView MainWindow::getGameView()
{
    GameView gameView;
    int cell= 0;

    for (unsigned int row = 1; row  < mainGrid.size(); row++){

        for (unsigned int col = 1; col < mainGrid[0].size(); col++){
            cell = mainGrid[row][col];

            if(cell == 1){
                QRect rec(cellSize*col,50+cellSize*row,cellSize,cellSize);
                gameView.append(rec);

            }

        }

    }
    return gameView;

}
