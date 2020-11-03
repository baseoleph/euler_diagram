#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSet>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_lineEdit_a_textChanged(const QString &arg1);

    void on_lineEdit_b_textChanged(const QString &arg1);

    void on_lineEdit_c_textChanged(const QString &arg1);

private:
    void updateSets();
    Ui::MainWindow *ui;
    QSet<int> A;
    QSet<int> B;
    QSet<int> C;
    QStringList aline;
    QStringList bline;
    QStringList cline;

};
#endif // MAINWINDOW_H
