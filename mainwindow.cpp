#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    aline = ui->lineEdit_a->text().split(" ");
    bline = ui->lineEdit_b->text().split(" ");
    cline = ui->lineEdit_c->text().split(" ");
    updateSets();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    updateSets();
}

void MainWindow::updateSets()
{
    qDebug() << " ";
    A.clear();
    B.clear();
    C.clear();

    foreach (auto e, aline)
    {
        A.insert(e.toInt());
    }
    foreach (auto e, bline)
    {
        B.insert(e.toInt());
    }
    foreach (auto e, cline)
    {
        if (e != "")
            C.insert(e.toInt());
    }

    qDebug() << A;
    qDebug() << B;
    qDebug() << C;
}

void MainWindow::on_lineEdit_a_textChanged(const QString &arg1)
{
    aline = arg1.split(" ");
}

void MainWindow::on_lineEdit_b_textChanged(const QString &arg1)
{
    bline = arg1.split(" ");
}

void MainWindow::on_lineEdit_c_textChanged(const QString &arg1)
{
    cline = arg1.split(" ");
}
