#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_clearButton_clicked()
{
    this->ui->painter->clear();
}

void MainWindow::on_red_clicked()
{
    this->ui->painter->changeColor(Qt::red);
}

void MainWindow::on_orange_clicked()
{
    this->ui->painter->changeColor(QColor(252, 175, 62, 255));
}

void MainWindow::on_yellow_clicked()
{
    this->ui->painter->changeColor(Qt::yellow);
}

void MainWindow::on_green_clicked()
{
    this->ui->painter->changeColor(Qt::green);
}

void MainWindow::on_blue_clicked()
{
    this->ui->painter->changeColor(Qt::blue);
}

void MainWindow::on_purple_clicked()
{
    this->ui->painter->changeColor(QColor(173, 127, 168, 255));
}

void MainWindow::on_gray_clicked()
{
    this->ui->painter->changeColor(QColor(186, 189, 182, 255));
}

void MainWindow::on_white_clicked()
{
    this->ui->painter->changeColor(Qt::white);
}

