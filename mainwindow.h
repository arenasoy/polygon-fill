#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "painter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_clearButton_clicked();
    void on_red_clicked();
    void on_orange_clicked();
    void on_yellow_clicked();
    void on_green_clicked();
    void on_blue_clicked();
    void on_purple_clicked();
    void on_gray_clicked();
    void on_white_clicked();

private:
    Ui::MainWindow *ui;
    Painter *painter;
};

#endif // MAINWINDOW_H
