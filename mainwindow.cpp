#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new Scene();

    aline = ui->lineEdit_a->text().split(" ");
    bline = ui->lineEdit_b->text().split(" ");
    cline = ui->lineEdit_c->text().split(" ");
    updateSets();


    tm = new QTimer();
    connect(tm, &QTimer::timeout, this, &MainWindow::setUpScene);
    tm->start(100);
}

MainWindow::~MainWindow()
{
    delete scene;
    delete tm;
    delete ui;
}

void MainWindow::setUpScene()
{
    tm->stop();

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    int width = ui->graphicsView->width();
    int height = ui->graphicsView->height();

//    QRectF r(-width/2, -height/2, width, height);
    QRectF r(0, 0, width, height);
    scene->setSceneRect(r);
}

void MainWindow::on_pushButton_clicked()
{
    updateSets();
    scene->setCircles(A, B, C);
}

void MainWindow::updateSets()
{
    A.clear();
    B.clear();
    C.clear();

    foreach (auto e, aline)
    {
        if (e != "") A.insert(e.toInt());
    }
    foreach (auto e, bline)
    {
        if (e != "") B.insert(e.toInt());
    }
    foreach (auto e, cline)
    {
        if (e != "") C.insert(e.toInt());
    }

    qDebug() << A.values();
    qDebug() << B.values();
    qDebug() << "inter" << A.intersects(B);
    qDebug() << "eq" << (A == B);
    qDebug() << "B in A" << A.contains(B);
    qDebug() << "A in B" << B.contains(A);


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
