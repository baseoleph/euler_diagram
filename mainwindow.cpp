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

    tm = new QTimer();
    connect(tm, &QTimer::timeout, this, &MainWindow::setUpScene);
    tm->start(100);

#ifdef _DEBUG
    getTests();
#endif
}

MainWindow::~MainWindow()
{
    delete scene;
    delete tm;
    delete ui;
}

void MainWindow::classify_pattern(QSet<int> a, QSet<int> b, QSet<int> c)
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
    QRectF r(0, 0, width, height);
    scene->setSceneRect(r);

    scene->fp->updateBoundingRect(width, height);
    updateSets();
}

void MainWindow::on_pushButton_clicked()
{
    updateSets();
    scene->fp->unFillIntersects();
    scene->setCircles(A, B, C, categ);
    expression_fix = "";
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
#ifdef _DEBUG
    if (event->key() == Qt::Key_Return ||
            event->key() == Qt::Key_Enter)
    {
       ++cnter %= test.size()-1;
       A = test[cnter][0];
       B = test[cnter][1];
       C = test[cnter][2];
       updateTestSets();
       scene->setCircles(A, B, C, categ);
    }
    else if (event->key() == Qt::Key_0)
    {
       A = test[cnter][0];
       B = test[cnter][1];
       C = test[cnter][2];
       updateTestSets();
       scene->setCircles(A, B, C, categ);
    }
    else if (event->key() == Qt::Key_1)
    {
       A = test[cnter][0];
       B = test[cnter][2];
       C = test[cnter][1];
       updateTestSets();
       scene->setCircles(A, B, C, categ);
    }
    else if (event->key() == Qt::Key_2)
    {
       A = test[cnter][1];
       B = test[cnter][0];
       C = test[cnter][2];
       updateTestSets();
       scene->setCircles(A, B, C, categ);
    }
    else if (event->key() == Qt::Key_3)
    {
       A = test[cnter][1];
       B = test[cnter][2];
       C = test[cnter][0];
       updateTestSets();
       scene->setCircles(A, B, C, categ);
    }
    else if (event->key() == Qt::Key_4)
    {
       A = test[cnter][2];
       B = test[cnter][0];
       C = test[cnter][1];
       updateTestSets();
       scene->setCircles(A, B, C, categ);
    }
    else if (event->key() == Qt::Key_5)
    {
       A = test[cnter][2];
       B = test[cnter][1];
       C = test[cnter][0];
       updateTestSets();
       scene->setCircles(A, B, C, categ);
    }
#else
    Q_UNUSED(event)
#endif
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

    classify_pattern(A, B, C);
    if (ui->lineEdit_a->text() == "" || ui->lineEdit_b->text() == "" || ui->lineEdit_c->text() == "")
    {
       ui->pushButton->setEnabled(false);
    }
    else
    {
        scene->setCircles(A, B, C, categ);
    }
}

void MainWindow::on_lineEdit_a_textChanged(const QString &arg1)
{
    aline = arg1.split(" ");
    if (ui->lineEdit_a->text() == "" || ui->lineEdit_b->text() == "" || ui->lineEdit_c->text() == "")
    {
       ui->pushButton->setEnabled(false);
    }
    else
    {
       ui->pushButton->setEnabled(true);
    }
}

void MainWindow::on_lineEdit_b_textChanged(const QString &arg1)
{
    bline = arg1.split(" ");
    if (ui->lineEdit_a->text() == "" || ui->lineEdit_b->text() == "" || ui->lineEdit_c->text() == "")
    {
       ui->pushButton->setEnabled(false);
    }
    else
    {
       ui->pushButton->setEnabled(true);
    }
}

void MainWindow::on_lineEdit_c_textChanged(const QString &arg1)
{
    cline = arg1.split(" ");
    if (ui->lineEdit_a->text() == "" || ui->lineEdit_b->text() == "" || ui->lineEdit_c->text() == "")
    {
       ui->pushButton->setEnabled(false);
    }
    else
    {
       ui->pushButton->setEnabled(true);
    }
}


#ifdef _DEBUG
void MainWindow::updateTestSets()
{
   QList<int> list = {};
   QString string;
   classify_pattern(A, B, C);
   list = A.values();
   string = "";
    foreach(auto e, list)
    {
        string += QString::number(e) + " ";
    }
   ui->lineEdit_a->setText(string);

   list = B.values();
   string = "";
    foreach(auto e, list)
    {
        string += QString::number(e) + " ";
    }
   ui->lineEdit_b->setText(string);

   list = C.values();
   string = "";
    foreach(auto e, list)
    {
        string += QString::number(e) + " ";
    }
   ui->lineEdit_c->setText(string);

   ui->statusbar->showMessage(QString::number(cnter + 1));
}
#endif

#ifdef _DEBUG
void MainWindow::getTests()
{
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
        classify_pattern(test[i][0], test[i][1], test[i][2]);
        if ((i != 10 && (i+1) != 4) && (i+1) != categ)
        {
            qDebug() << 1 << i+1 << " - " << categ;
        }
        classify_pattern(test[i][0], test[i][2], test[i][1]);
        if ((i != 10 && (i+1) != 4) && (i+1) != categ)
        {
            qDebug() << 2 << i+1 << " - " << categ;
        }
        classify_pattern(test[i][1], test[i][2], test[i][0]);
        if ((i != 10 && (i+1) != 4) && (i+1) != categ)
        {
            qDebug() << 3 << i+1 << " - " << categ;
        }
        classify_pattern(test[i][1], test[i][0], test[i][2]);
        if ((i != 10 && (i+1) != 4) && (i+1) != categ)
        {
            qDebug() << 4 << i+1 << " - " << categ;
        }
        classify_pattern(test[i][2], test[i][1], test[i][0]);
        if ((i != 10 && (i+1) != 4) && (i+1) != categ)
        {
            qDebug() << 5 << i+1 << " - " << categ;
        }
        classify_pattern(test[i][2], test[i][0], test[i][1]);
        if ((i != 10 && (i+1) != 4) && (i+1) != categ)
        {
            qDebug()<< 6 << i+1 << " - " << categ;
        }
    }
}
#endif

void MainWindow::resizeEvent(QResizeEvent* event)
{
    Q_UNUSED(event)
    int width = ui->graphicsView->width();
    int height = ui->graphicsView->height();
    QRectF r(0, 0, width, height);
    scene->setSceneRect(r);
    scene->setCircles(A, B, C, categ);

    scene->fp->path.clear();
    eval.clear();
    vector_path.clear();

    if (expression_fix != "")
    {
        roll(expression_fix);
        scene->fp->path = vector_path.last();
        scene->colorize();
    }

}

void MainWindow::on_lineEdit_exp_textChanged(const QString &arg1)
{
    expression = "(" + arg1.trimmed().simplified().toLower() + ")";
    while (expression.indexOf(" ") != -1) expression.remove(" ");
    if (isStringCorrect(expression)) ui->pushButton_calc->setEnabled(true);
    else ui->pushButton_calc->setEnabled(false);
}

bool MainWindow::isStringCorrect(QString str)
{
    if (str.isEmpty()) return true;
    if (str.contains("()")) return false;
    if (str.count("(") != str.count(")")) return false;
    QVector<QString> stack = {};
    for (int i = 0; i < str.size(); ++i)
    {
        if (str[i] == "(") stack.push_back("(");
        if (str[i] == ")" && stack.endsWith("(")) stack.pop_back();
        else if (str[i] == ")") return false;
    }
    if (not stack.isEmpty()) return false;

    QString without_letters = str;
    while (without_letters.indexOf("a") != -1) without_letters.remove("a");
    while (without_letters.indexOf("b") != -1) without_letters.remove("b");
    while (without_letters.indexOf("c") != -1) without_letters.remove("c");
    stack.clear();
    if (without_letters != "()")
    {
        for (int i = 0; i < without_letters.size(); ++i)
        {
            if (without_letters[i] == "(") stack.push_back("(");
            if (without_letters[i] == "&" || without_letters[i] == "|" || without_letters[i] == "\\") stack.push_back(QString(without_letters[i]));
            if (without_letters[i] == ")" && stack.endsWith("(")) stack.pop_back();
            else if (without_letters[i] == ")" && (stack[stack.size()-2] == "(") && (stack.endsWith("&") || stack.endsWith("|") || stack.endsWith("\\")))
            {
                stack.pop_back();
                stack.pop_back();
            }
        }
        if (not stack.isEmpty()) return false;
    }


    int permiss_cnt = str.count("a") + str.count("b") + str.count("c") +
                      str.count("&") + str.count("|") + str.count("\\") +
                      str.count("(") + str.count(")");
    if(permiss_cnt != str.size()) return false;

//    int pos = 0;
    for (int i = 0; i < str.size(); ++i)
    {
        if (i != 0            && str[i] == "(" && (str[i-1] == "a" || str[i-1] == "b" || str[i-1] == "c")) return false;
        if (i != str.size()-1 && str[i] == "(" && (str[i+1] == "&" || str[i+1] == "|" || str[i+1] == "\\")) return false;
        if (i != 0            && str[i] == ")" && (str[i-1] == "&" || str[i-1] == "|" || str[i-1] == "\\")) return false;
        if (i != str.size()-1 && str[i] == ")" && (str[i+1] == "a" || str[i+1] == "b" || str[i+1] == "c")) return false;

        if (i != 0            && (str[i] == "&" || str[i] == "|" || str[i] == "\\") &&
                                 (str[i-1] == "(" || str[i-1] == "&" || str[i-1] == "|" || str [i-1] == "\\")) return false;

        if (i != str.size()-1 && (str[i] == "&" || str[i] == "|" || str[i] == "\\") &&
                                 (str[i+1] == ")" || str[i+1] == "&" || str[i+1] == "|" || str [i+1] == "\\")) return false;

        if (i != 0            && (str[i] == "a" || str[i] == "b" || str[i] == "c") &&
                                 (str[i-1] == ")" || str[i-1] == "a" || str[i-1] == "b" || str [i-1] == "c")) return false;

        if (i != str.size()-1 && (str[i] == "a" || str[i] == "b" || str[i] == "c") &&
                                 (str[i+1] == "(" || str[i+1] == "a" || str[i+1] == "b" || str [i+1] == "c")) return false;

//        if (str[i] == "&" || str[i] == "|" || str[i] == "\\")
//        {
//            if (pos != 0 && i - pos <= 2) return false;
//            pos = i;
//        }
    }

    return true;
}

QSet<int> MainWindow::evaluate(QString str)
{
    QSet<int> a;
    QSet<int> b;
    QSet<int> ans;
    QPainterPath apath;
    QPainterPath bpath;
    QPainterPath anspath;

    int p = 0;

    if (str[0] == "%")
    {
        p = str.indexOf("%", 1);
        QString s = str.mid(1, p-1);
        a = eval[str.mid(1, p-1).toInt()];
        apath = vector_path[str.mid(1, p-1).toInt()];
    }
    else
    {
        if (str[0] == "a")
        {
            a = A;
            apath.addEllipse(QRectF(scene->Ael->pos().x(), scene->Ael->pos().y(), scene->Ael->rect().width(), scene->Ael->rect().height()));
        }
        if (str[0] == "b")
        {
            a = B;
            apath.addEllipse(QRectF(scene->Bel->pos().x(), scene->Bel->pos().y(), scene->Bel->rect().width(), scene->Bel->rect().height()));
        }
        if (str[0] == "c")
        {
            a = C;
            apath.addEllipse(QRectF(scene->Cel->pos().x(), scene->Cel->pos().y(), scene->Cel->rect().width(), scene->Cel->rect().height()));
        }

    }
    if (not (str.indexOf("&") != -1 || str.indexOf("|") != -1 || str.indexOf("\\") != -1))
    {
        ans = a;
        anspath = apath;
    }
    else
    {
        if (str[p+2] == "%")
        {
            int t = p+3;
            p = str.indexOf("%", p+3) - p+2;
            // Костыль
            QString s = str.mid(t, 1);
            b = eval[str.mid(t, 1).toInt()];
            bpath = vector_path[str.mid(t, 1).toInt()];
//            qDebug() << str.mid(1, p+1);
        }
        else
        {
            if (str[p+2] == "a")
            {
                b = A;
                bpath.addEllipse(QRectF(scene->Ael->pos().x(), scene->Ael->pos().y(), scene->Ael->rect().width(), scene->Ael->rect().height()));
            }
            if (str[p+2] == "b")
            {
                b = B;
                bpath.addEllipse(QRectF(scene->Bel->pos().x(), scene->Bel->pos().y(), scene->Bel->rect().width(), scene->Bel->rect().height()));
            }
            if (str[p+2] == "c")
            {
                b = C;
                bpath.addEllipse(QRectF(scene->Cel->pos().x(), scene->Cel->pos().y(), scene->Cel->rect().width(), scene->Cel->rect().height()));
            }
        }

//        qDebug() << str << a << b;
        if (str.indexOf("&") != -1)
        {
             ans = a&b;
             anspath = apath.intersected(bpath);
        }
        else if (str.indexOf("|") != -1)
        {
             ans = a|b;
             anspath = apath.united(bpath);
        }
        else if (str.indexOf("\\") != -1)
        {
             ans = a-b;
             anspath = apath.subtracted(bpath);
        }
    }



    vector_path.append(anspath);
    return ans;
}

QSet<int> MainWindow::roll(QString expression)
{
    while (expression.indexOf(")") != -1)
    {
        int right_par = expression.indexOf(")");
        int left_par = expression.left(right_par).lastIndexOf("(");
        int lp = left_par + 1;
        int rp = right_par - left_par - 1;
        QString tempstr = expression.mid(lp, rp);
        eval.append(evaluate(tempstr));
        expression = expression.replace(lp-1, rp+2, "%" + QString::number(eval.size()-1) + "%");
    }


    return eval.last();
}

void MainWindow::on_pushButton_calc_clicked()
{
    expression_fix = expression;
    scene->fp->path.clear();
    eval.clear();
    vector_path.clear();

    D = roll(expression);
    scene->fp->path = vector_path.last();
    scene->colorize();
    QList<int> temp = D.values();
    std::sort(temp.begin(), temp.end());
    QString str = "";
    foreach (auto e, temp) str += QString::number(e) + " ";
    str = str.trimmed();
    str = "D = {" + str + "}";
    ui->label_d->setText(str);
}
