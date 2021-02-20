#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

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
    void on_n0_clicked();
    void on_n1_clicked();
    void on_n2_clicked();
    void on_n3_clicked();
    void on_n4_clicked();
    void on_n5_clicked();
    void on_n6_clicked();
    void on_n7_clicked();
    void on_n8_clicked();
    void on_n9_clicked();

    void on_comma_clicked();

    void on_sum_clicked();

    void on_sub_clicked();

    void on_multip_clicked();

    void on_div_clicked();

    void on_clear_clicked();

    void on_pl_per_min_clicked();

    void on_br_left_clicked();

    void on_br_right_clicked();

    void on_x_pow_y_clicked();

    void on_x_pow_2_clicked();

    void on_sin_clicked();

    void on_cos_clicked();

    void on_clear_one_clicked();

    void on_calculate_clicked();

private:
    Ui::MainWindow *ui;
    QString expression;

};
#endif // MAINWINDOW_H
