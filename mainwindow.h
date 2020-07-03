#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <vector>
#include <QVector>



typedef std::vector<std::vector<int> > GameGrid;
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
    GameGrid rPentomino;
    GameView gameView;
    GameGrid mainGrid;
    QTimer *timer;



    virtual void paintEvent(QPaintEvent *event);
    virtual void resizeEvent(QResizeEvent *event);


private slots:
    void on_pushButton_clicked();
    void on_horizontalSlider_valueChanged(int value);
    void stepForward();

private:
    Ui::MainWindow *ui;
    GameGrid pentomino();
    GameView getGameView();
    void copyGrid(GameGrid&, GameGrid&);
    void drawRect(QPainter&);
    void updateGameBoard();
    void cellState(GameGrid&);
    void startStop();
};
#endif // MAINWINDOW_H
