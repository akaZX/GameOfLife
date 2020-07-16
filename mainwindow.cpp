#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <vector>
#include <QTableView>
#include <QVector>
#include <QPushButton>
#include <QThread>
#include <QString>




using namespace std;
// GameOfLife gameOfLife;

const int CELL_SIZE = 15;
const int topSpace = 50;
const QString play = " ▶️ ";
const QString pause = "❙❙";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    gameOfLife.setColumns(this->geometry().width() / CELL_SIZE);
    gameOfLife.setRows(((this->frameGeometry().height() - topSpace) / CELL_SIZE));
    flag = false;
    game = false;    

    getGameView(gameView);
    timer = new QTimer(this);

     ui->pushButton->setText(play);

    connect(timer, SIGNAL(timeout()),
            this, SLOT(stepForward()));

    gameOfLife.update();

    
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



void MainWindow::on_horizontalSlider_sliderReleased()
{
    startStop();
}



void MainWindow::paintEvent(QPaintEvent *event){

    std::cout << "   " << gameOfLife.getColumns() << "lentos plotis" << endl;
    getGameView(gameView);
    QPainter painter(this);
    QPen pen(Qt::black);
    QBrush brush(Qt::darkGray);
    painter.setPen(pen);
    painter.setBrush(brush);

    painter.drawRects(gameView);

}




//not used ATM
void MainWindow::resizeEvent(QResizeEvent *event)
{     
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
        if(!flag){ 	
            gameOfLife.stepForward();
        }
        update();
        // flag = true;
       

}




void MainWindow::getGameView(GameView& gameView)
{
    
    gameView.clear();
 
	
    for (unsigned int row = 1; row  < gameOfLife.gameBoard.size(); row++){
	cout << gameOfLife.gameBoard.size() << endl;
        for (unsigned int col = 1; col < gameOfLife.gameBoard[0].size(); col++){
             int cell = gameOfLife.gameBoard[row][col];
 
            if(cell == 1){
                QRect rec(CELL_SIZE *col,topSpace+ CELL_SIZE *row, CELL_SIZE, CELL_SIZE);
                gameView.append(rec);
                
               
            }
 
        }
 
    }
  

}

