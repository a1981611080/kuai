#ifndef WIDGET_H
#define WIDGET_H
#define post_x 175+j*FK_bc+b
#define post_y x+i*FK_bc-150
#define fx1 fk_yd[0][0]
#define fy1 fk_yd[0][1]
#define fx2 fk_yd[1][0]
#define fy2 fk_yd[1][1]
#define fx3 fk_yd[2][0]
#define fy3 fk_yd[2][1]
#define fx4 fk_yd[3][0]
#define fy4 fk_yd[3][1]



#include <QWidget>
#include<QPushButton>

const int FK_bc=25;//方块边长
const int youxi_w=375;//显示宽 16个格子
const int youxi_h=725;//显示高 29 个格子


//总共522个格





namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT









public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    int x;int y;

    void zuobiao(void);

    void shengmingjiesu(void);
    void daodi(void);
    void ban(void);
    void anniu1();
    void anniu2();
    void ban2(void);
    void xiaohang(void);
    void shibai(void);
    int shifouxuanzhuan();
    int xuanzhuanhanshu(int a);
    void qingpin(void);



protected:
void paintEvent(QPaintEvent *event);//绘图
void timerEvent(QTimerEvent *event); //场景刷新
void keyPressEvent(QKeyEvent *event);//键盘
//void keyReleaseEvent(QKeyEvent *event);







private slots:



private:
    Ui::Widget *ui;
    int refresh;
    QPushButton *b1;
    QPushButton *b2;



};


#endif // WIDGET_H
