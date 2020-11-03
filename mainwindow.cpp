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

    //1
    QSet<int> a = {1};
    QSet<int> b = {2};
    QSet<int> c = {3};
    test.append({a, b, c});

    //2
    a = {1, 2};
    b = {2, 3};
    c = {4};
    test.append({a, b, c});

    //3
    a = {1, 2};
    b = {2, 3, 4};
    c = {4, 5};
    test.append({a, b, c});

    //4
    a = {1, 2, 3, 4};
    b = {2, 3, 5, 6};
    c = {3, 4, 5, 7};
    test.append({a, b, c});

    //5
    a = {1};
    b = {1, 2};
    c = {3};
    test.append({a, b, c});

    //6
    a = {1};
    b = {1, 2, 3};
    c = {3, 4};
    test.append({a, b, c});

    //7
    a = {1, 2};
    b = {1, 2, 3, 4};
    c = {2, 3, 5};
    test.append({a, b, c});

    //8
    a = {1};
    b = {1, 2};
    c = {1, 2, 3};
    test.append({a, b, c});

    //9
    a = {1};
    b = {2};
    c = {1, 2, 3};
    test.append({a, b, c});

    //10
    a = {1, 2};
    b = {2, 3};
    c = {1, 2, 3, 4};
    test.append({a, b, c});

    //11
    a = {1, 2, 3};
    b = {3, 4, 5};
    c = {2, 3, 4, 6};
    test.append({a, b, c});

    //12
    a = {1};
    b = {1};
    c = {2};
    test.append({a, b, c});

    //13
    a = {1, 2};
    b = {1, 2};
    c = {2, 3};
    test.append({a, b, c});

    //14
    a = {1};
    b = {1};
    c = {1, 2};
    test.append({a, b, c});

    //15
    a = {1};
    b = {1};
    c = {1};
    test.append({a, b, c});

    //16
    a = {1, 2};
    b = {1, 2};
    c = {1};
    test.append({a, b, c});

    //16
    a = {1, 2};
    b = {2, 3};
    c = {4};
    test.append({a, b, c});

    for (int i = 0; i < 16; ++i)
    {
        sort(test[i][0], test[i][1], test[i][2]);
        if ((i != 10 && (i+1) != 4) && (i+1) != categ)
        {
            qDebug() << 1 << i+1 << " - " << categ;
        }
        sort(test[i][0], test[i][2], test[i][1]);
        if ((i != 10 && (i+1) != 4) && (i+1) != categ)
        {
            qDebug() << 2 << i+1 << " - " << categ;
        }
        sort(test[i][1], test[i][2], test[i][0]);
        if ((i != 10 && (i+1) != 4) && (i+1) != categ)
        {
            qDebug() << 3 << i+1 << " - " << categ;
        }
        sort(test[i][1], test[i][0], test[i][2]);
        if ((i != 10 && (i+1) != 4) && (i+1) != categ)
        {
            qDebug() << 4 << i+1 << " - " << categ;
        }
        sort(test[i][2], test[i][1], test[i][0]);
        if ((i != 10 && (i+1) != 4) && (i+1) != categ)
        {
            qDebug() << 5 << i+1 << " - " << categ;
        }
        sort(test[i][2], test[i][0], test[i][1]);
        if ((i != 10 && (i+1) != 4) && (i+1) != categ)
        {
            qDebug()<< 6 << i+1 << " - " << categ;
        }
    }
}

MainWindow::~MainWindow()
{
    delete scene;
    delete tm;
    delete ui;
}

void MainWindow::sort(QSet<int> a, QSet<int> b, QSet<int> c)
{
    categ = -1;
    if ((a == b) && (b == c))
    {
        categ =  15;
    }
    else if (a == b || b == c || c == a)
    {
        if (b == c) swap(a,c);
        else if (c == a) swap(c,b);

        if (b.contains(c))
        {
            categ =  16;
        }
        else if (c.contains(a))
        {
            categ =  14;
        }
        else if (c.intersects(a))
        {
            categ =  13;
        }
        else
        {
            categ =  12;
        }
    }
    else if (a.intersects(b) && a.intersects(c) && b.intersects(c)
             && not a.contains(b) && not a.contains(c) && not b.contains(a) && not b.contains(c) && not c.contains(a) && not c.contains(b))
    {
        categ =  4;
    }
    else if (((a.intersects(b) && b.intersects(c)) || (a.intersects(c) && c.intersects(b)) || (b.intersects(a) && a.intersects(c)))
             && not a.contains(b) && not a.contains(c) && not b.contains(a) && not b.contains(c) && not c.contains(a) && not c.contains(b))
    {
        categ =  3;
    }
    else if ((not c.intersects(b) && b.contains(a)) || (not c.intersects(a) && a.contains(b)) ||
             (not b.intersects(a) && a.contains(c)) || (not b.intersects(c) && c.contains(a)) ||
             (not a.intersects(b) && b.contains(c)) || (not a.intersects(c) && c.contains(b)))
    {
        categ =  5;
    }
    else if ((a.contains(b) && b.contains(c)) || (a.contains(c) && c.contains(b)) ||
             (b.contains(a) && a.contains(c)) || (b.contains(c) && c.contains(a)) ||
             (c.contains(a) && a.contains(b)) || (c.contains(b) && b.contains(a)))
    {
        categ =  8;
    }
    else if ((a.contains(b) && a.contains(c)) || (b.contains(a) && b.contains(c)) || (c.contains(a) && c.contains(b)))
    {
        if ((a.contains(b) && a.contains(c) && c.intersects(b)) || (b.contains(a) && b.contains(c) && a.intersects(c)) ||
                (c.contains(a) && c.contains(b) && a.intersects(b)))
        {
            categ = 10;
        }
        else
        {
            categ =  9;
        }
    }
    else if (a.intersects(b) || a.intersects(c) || b.intersects(c))
    {
        if ((a.intersects(b) && not c.intersects(a+b)) || (a.intersects(c) && not b.intersects(a+c)) ||
                (b.intersects(c) && not a.intersects(b+c)))
        {
            categ =  2;
        }
        else
        {
            if (b.contains(c)) swap(a,b);
            else if (c.contains(a)) swap(c,a);
            else if (c.contains(b)) {swap(b,c); swap(a,b);}
            else if (a.contains(b)) swap(b,c);
            else if (b.contains(a)) {swap(a,b); swap(b,c);}


            if (c.intersects(b))
            {
                categ =  7;
            }
            else
            {
                categ =  6;
            }
        }
    }
    else if (not a.intersects(b) && not a.intersects(c) && not b.intersects(c))
    {
        categ =  1;
    }
    else
    {
        categ =  0;
    }
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
    scene->setCircles(A, B, C, categ);
}

void MainWindow::swap(QSet<int> &a, QSet<int> &b)
{
    QSet<int> temp;
    temp = a;
    a = b;
    b = temp;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{

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

    sort(A, B, C);
    qDebug() << categ;
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
