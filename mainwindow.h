#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#define _DEBUG

#include <QMainWindow>
#include <QSet>
#include <QDebug>
#include <QTimer>
#include <QKeyEvent>
#include <QResizeEvent>
#include <QtAlgorithms>

#include "scene.h"
#include "filledpath.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void sort(QSet<int> a, QSet<int> b, QSet<int> c);
    void swap(QSet<int> &a, QSet<int> &b);

private slots:
    void resizeEvent(QResizeEvent* event);
    void keyPressEvent(QKeyEvent *event);
    void setUpScene();
    void on_pushButton_clicked();

    void on_lineEdit_a_textChanged(const QString &arg1);

    void on_lineEdit_b_textChanged(const QString &arg1);

    void on_lineEdit_c_textChanged(const QString &arg1);

    void on_lineEdit_exp_textChanged(const QString &arg1);

    void on_pushButton_calc_clicked();

private:
    QPainterPath *path;
    QString expression;
    QString expression_fix;
    bool is_button_clicked = false;
#ifdef _DEBUG
    void updateTestSets();
    void getTests();
    QVector<QVector<QSet<int>>> test;
#endif

    Scene *scene;
    QTimer *tm;
    void updateSets();
    Ui::MainWindow *ui;
    QSet<int> A;
    QSet<int> B;
    QSet<int> C;
    QSet<int> D;
    QStringList aline;
    QStringList bline;
    QStringList cline;
    QVector<QSet<int>> eval;
    QVector<QPainterPath> vector_path;

    bool isStringCorrect(QString str);
    QSet<int> evaluate(QString str);
    QSet<int> roll(QString str);
    int categ = 0;
    int cnter = -1;
};
#endif // MAINWINDOW_H
