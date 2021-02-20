#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->output_screen->setPlainText(this->expression);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_n0_clicked()
{
    this->expression.append("0");
    ui->output_screen->setPlainText(this->expression);
}

void MainWindow::on_n1_clicked()
{
    this->expression.append("1");
    ui->output_screen->setPlainText(this->expression);
}

void MainWindow::on_n2_clicked()
{
    this->expression.append("2");
    ui->output_screen->setPlainText(this->expression);
}

void MainWindow::on_n3_clicked()
{
    this->expression.append("3");
    ui->output_screen->setPlainText(this->expression);
}

void MainWindow::on_n4_clicked()
{
    this->expression.append("4");
    ui->output_screen->setPlainText(this->expression);
}

void MainWindow::on_n5_clicked()
{
    this->expression.append("5");
    ui->output_screen->setPlainText(this->expression);
}

void MainWindow::on_n6_clicked()
{
    this->expression.append("6");
    ui->output_screen->setPlainText(this->expression);
}

void MainWindow::on_n7_clicked()
{
    this->expression.append("7");
    ui->output_screen->setPlainText(this->expression);
}

void MainWindow::on_n8_clicked()
{
    this->expression.append("8");
    ui->output_screen->setPlainText(this->expression);
}

void MainWindow::on_n9_clicked()
{
    this->expression.append("9");
    ui->output_screen->setPlainText(this->expression);
}

void MainWindow::on_comma_clicked()
{
    if (this->expression.length())
    {
        if (this->expression[this->expression.length() - 1].isNumber())
        {
            bool flag{false};
            for (int i = this->expression.length() - 1; i > 0; i--)
            {
                if (this->expression[i] == ',')
                {
                    flag = true;
                }
                if (!this->expression[i].isNumber())
                {
                    break;
                }
            }
            if (!flag)
            {
                this->expression.append(",");
                ui->output_screen->setPlainText(this->expression);
            }
        }
    }
}

void MainWindow::on_sum_clicked()
{
    if (this->expression.length())
    {
        if (this->expression[this->expression.length() - 1].isNumber()
            || this->expression[this->expression.length() - 1] == ')')
        {
            this->expression.append("+");
            ui->output_screen->setPlainText(this->expression);
        }
    }
}

void MainWindow::on_sub_clicked()
{
    if (this->expression.length())
    {
        if (this->expression[this->expression.length() - 1].isNumber()
            || this->expression[this->expression.length() - 1] == '('
            || this->expression[this->expression.length() - 1] == ')')
        {
            this->expression.append("-");
            ui->output_screen->setPlainText(this->expression);
        }
    }
}

void MainWindow::on_multip_clicked()
{
    if (this->expression.length())
    {
        if (this->expression[this->expression.length() - 1].isNumber()
            || this->expression[this->expression.length() - 1] == ')')
        {
            this->expression.append("*");
            ui->output_screen->setPlainText(this->expression);
        }
    }
}

void MainWindow::on_div_clicked()
{
    if (this->expression.length())
    {
        if (this->expression[this->expression.length() - 1].isNumber()
            || this->expression[this->expression.length() - 1] == ')')
        {
            this->expression.append("/");
            ui->output_screen->setPlainText(this->expression);
        }
    }
}

void MainWindow::on_clear_clicked()
{
    this->expression.clear();
    ui->output_screen->setPlainText(this->expression);
}

void MainWindow::on_pl_per_min_clicked()
{
    if (this->expression.length())
    {
        if (this->expression[this->expression.length() - 1].isNumber())
        {
            for (int i = this->expression.length() - 1; i >= 0; i--)
            {
                if (!this->expression[i].isNumber() || (this->expression[i].isNumber() && i == 0))
                {
                    if (this->expression[i] == '+' || this->expression[i] == '-')
                    {
                        this->expression[i] = this->expression[i] == '+' ? '-' : '+';
                    }
                    else
                    {
                        this->expression.insert(i + (i == 0 ? 0 : 1), '-');
                    }
                    break;
                }
            }
        }
    }
    ui->output_screen->setPlainText(this->expression);
}

void MainWindow::on_br_left_clicked()
{
    if (this->expression.length())
    {
        QChar tmp {this->expression[this->expression.length() - 1]};
        if (!tmp.isNumber() && tmp != '(' && tmp != ')')
        {
            this->expression.append('(');
        }
    }
    else
    {
        this->expression.append('(');
    }
    ui->output_screen->setPlainText(this->expression);
}

void MainWindow::on_br_right_clicked()
{
    if (this->expression.length())
    {
        QChar tmp {this->expression[this->expression.length() - 1]};
        if (tmp.isNumber() && tmp != '(' && tmp != ')')
        {
            this->expression.append(')');
        }
    }
    ui->output_screen->setPlainText(this->expression);
}

void MainWindow::on_x_pow_y_clicked()
{
    if (this->expression.length())
    {
        QChar tmp {this->expression[this->expression.length() - 1]};
        if (tmp.isNumber() || tmp == ')')
        {
            this->expression.append('^');
            ui->output_screen->setPlainText(this->expression);
        }
    }
}

void MainWindow::on_x_pow_2_clicked()
{
    if (this->expression.length())
    {
        QChar tmp {this->expression[this->expression.length() - 1]};
        if (tmp.isNumber() || tmp == ')')
        {
            this->expression.append("^2");
            ui->output_screen->setPlainText(this->expression);
        }
    }
}

void MainWindow::on_sin_clicked()
{
    if (this->expression.length())
    {
        QChar tmp {this->expression[this->expression.length() - 1]};
        if (!tmp.isNumber() && tmp != ')')
        {
            this->expression.append("sin(");
        }
    }
    else
    {
        this->expression.append("sin(");
    }
    ui->output_screen->setPlainText(this->expression);
}

void MainWindow::on_cos_clicked()
{
    if (this->expression.length())
    {
        QChar tmp {this->expression[this->expression.length() - 1]};
        if (!tmp.isNumber() && tmp != ')')
        {
            this->expression.append("cos(");
        }
    }
    else
    {
        this->expression.append("cos(");
    }
    ui->output_screen->setPlainText(this->expression);
}

void MainWindow::on_clear_one_clicked()
{
    if (this->expression.length())
    {
        if (this->expression[this->expression.length() - 1] != '(')
        {
            this->expression.chop(1);
        }
        else
        {
            if (this->expression.length() >= 4 &&
                    (this->expression[this->expression.length() - 2] == 'n'
                  || this->expression[this->expression.length() - 2] == 's'))
            {
                this->expression.chop(4);
            }
            else
            {
                this->expression.chop(1);
            }
        }
    }
    ui->output_screen->setPlainText(this->expression);
}
