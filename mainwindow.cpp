#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtMath>
#include <stack>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->output_screen->setPlainText(this->expression);
    qDebug() << qPow(-2,2.5);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool is_operation(const QString& str)
{
    return str[0] == '+'
        || str[0] == '-'
        || str[0] == '*'
        || str[0] == '/'
        || str[0] == '^';
}

bool is_oper_trig(const QString& str)
{
    return str[0] == '+'
        || str[0] == '-'
        || str[0] == '*'
        || str[0] == '/'
        || str[0] == '^'
        || str[0] == 's'
        || str[0] == 'c';
}

bool is_binary(const QString& str)
{
    if (str[0] == 's' || str[0] == 'c')
        return false;
    return true;
}

bool is_digit(const QString& str)
{
    bool flag{ false };
    for (auto& i : str)
    {
        if (i >= '0' && i <= '9')
            flag = true;
    }
    return flag;
}

int priority(const QString& str)
{
    switch (str[0].toLatin1())
    {
    case '(':
    case 's': /*sin*/
    case 'c': /*cos*/
        return 1;
    case '+':
    case '-':
        return 2;
    case '*':
    case '/':
        return 3;
    case '^':
        return 4;
    default:
        return 0;
    }
}


/*токенизация*/
bool get_tokens(std::vector<QString>& tokens, const QString& expression)
{
    QString tmp;
    bool incorrect{false};
    std::stack<QChar> check;
    for (unsigned long long i = 0; i < expression.length(); i++)
    {
        if (expression[i].isNumber() || expression[i] == '.')
        {
            tmp += expression[i];
        }
        else
        {
            if ((expression[i] == '+' || expression[i] == '-') && (i == 0 || !is_digit(QString{ expression[i - 1] })))
            {
                tmp += expression[i];
            }
            else
            {
                if (tmp.length())
                {
                    tokens.push_back(tmp);
                    tmp.clear();
                }
                if (expression[i] == 's' || expression[i] == 'c')
                {
                    tokens.push_back(expression.mid(i, 4));
                    i += 3;
                }
                else
                {
                    tokens.push_back(QString{ expression[i] });
                }


                if (expression[i] == '(')
                    check.push(expression[i]);
                if (expression[i] == ')')
                {
                    if (check.empty() || check.top() != '(')
                        incorrect = true;
                    else
                        check.pop();
                }
            }
        }
    }
    if (tmp.length())
    {
        tokens.push_back(tmp);
    }
    if (!check.empty())
    {
        incorrect = true;
    }
    return incorrect;
}

void get_post_tokens(const std::vector<QString>& tokens, std::vector<QString>& post_tokens)
{
    std::stack<QString> st;

    for (auto& i : tokens)
    {
        if (is_digit(i))
        {
            post_tokens.push_back(i);
        }
        else if (is_operation(i))
        {
            if (st.empty())
            {
                st.push(i);
            }
            else
            {
                while (!st.empty() && priority(st.top()) >= priority(i))
                {
                    post_tokens.push_back(st.top());
                    st.pop();
                }
                st.push(i);
            }
        }
        else if (priority(i) == 1)
        {
            st.push(i);
        }
        else if (i[0] == ')')
        {
            while (priority(st.top()) != 1)
            {
                post_tokens.push_back(st.top());
                st.pop();
            }
            if (st.top() == "sin(" || st.top() == "cos(")
            {
                post_tokens.push_back(st.top().mid(0, 3));
            }
            st.pop();
        }
    }
    while (!st.empty())
    {
        post_tokens.push_back(st.top());
        st.pop();
    }
}

double calc(const std::vector<QString>& post_tokens)
{
    std::map<QChar, std::function<double(const double&, const double&)>> operations;
    operations['+'] = [](const double& a, const double& b) { return a + b; };
    operations['-'] = [](const double& a, const double& b) { return a - b; };
    operations['*'] = [](const double& a, const double& b) { return a * b; };
    operations['/'] = [](const double& a, const double& b) { return a / b; };
    operations['^'] = [](const double& a, const double& b)
    {
        if (a < 0)
            return -std::pow(std::abs(a), b);
        return std::pow(a, b);
    };
    std::stack<double> result{};
    try
    {
        for (auto& i : post_tokens)
        {
            if (is_digit(i))
            {
                result.push(i.toDouble());
            }
            if (is_oper_trig(i))
            {
                if (!is_binary(i))
                {
                    double v{ result.top() };
                    result.pop();
                    if (i == "sin")
                        result.push(std::sin(v));
                    else
                        result.push(std::cos(v));
                }
                else
                {
                    double v2{ result.top() };
                    result.pop();
                    double v1{ result.top() };
                    result.pop();
                    double t{ operations[i[0]](v1, v2) };
                    result.push(t);
                }
            }
        }
        return result.top();
    }
    catch (...)
    {
        return 0;
    }
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
                if (this->expression[i] == '.')
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
                this->expression.append(".");
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

void MainWindow::on_calculate_clicked()
{
    bool incorrect{ false };
    std::vector<QString> tokens;
    incorrect = get_tokens(tokens, this->expression);
    if (!incorrect)
    {
        std::vector<QString> post_tokens;
        get_post_tokens(tokens, post_tokens);
        double result{calc(post_tokens)};
        this->expression = QString::number(result);
        ui->output_screen->setPlainText(this->expression);
    }
    else
    {
        this->expression = "";
        ui->output_screen->setPlainText(this->expression);
    }
}
