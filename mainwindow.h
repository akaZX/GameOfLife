#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gameoflife.h"
#include <QMainWindow>
#include <QPainter>
#include <QTimer>

#include <QVector>




typedef  QVector<QRect> GameView;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    bool flag;
    bool game;
	
    QPainter painter;   
    GameView gameView;
    QTimer *timer;
	


    virtual void paintEvent(QPaintEvent *event);
    virtual void resizeEvent(QResizeEvent *event);

   // void getRectangles(int, int, GameView&);
private slots:
    void on_pushButton_clicked();
    void stepForward();
    void on_horizontalSlider_sliderReleased();

private:
    
    Ui::MainWindow *ui;
    GameOfLife gameOfLife;
    void getGameView(GameView&);
    
    void drawRect(QPainter&);
    
    void startStop();
   
};
#endif // MAINWINDOW_H
