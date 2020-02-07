#include "widget.h"
#include "ui_widget.h"

#include <QPainter>
#include <QPen>
#include <Time.h>
#include <QKeyEvent>
#include <QtGlobal>
#include <QMessageBox>
#include <QDebug>
#include <QFont>



/**********************
 bug修复历史:
1.左右边界判定

已有bug：
1.到底随机数 ok
2.碰撞中间插不进去
3.楼顶bug


 ******************/
//定义图案代码和边界 5为了防止未知数据进入
//田字
int item1[][5][5]=
{
{
    {0,0,0,0},
    {0,1,1,0},
    {0,1,1,0},
    {0,0,0,0},
},
/*{
    {0,0,0,0},
    {0,0,0,0},
    {0,1,1,0},
    {1,0,0,1},
},*/
};
//右L
int item2[][5][5]=
{


{
    {0,0,0,0},
    {0,1,0,0},
    {0,1,0,0},
    {0,1,1,0},
},

{
    {0,0,0,0},
    {0,0,0,0},
    {1,1,1,0},
    {1,0,0,0},
},
{
    {0,0,0,0},
    {1,1,0,0},
    {0,1,0,0},
    {0,1,0,0},
},
    {
        {0,0,0,0},
        {0,0,1,0},
        {1,1,1,0},
        {0,0,0,0},
    },
    };
//左L
int item3[][5][5]=
{
{
    {0,0,0,0},
    {0,0,1,0},
    {0,0,1,0},
    {0,1,1,0},
},
    {
        {0,0,0,0},
        {0,1,0,0},
        {0,1,1,1},
        {0,0,0,0},
    },
    {
        {0,0,0,0},
        {0,0,1,1},
        {0,0,1,0},
        {0,0,1,0},
    },
    {
        {0,0,0,0},
        {0,0,0,0},
        {0,1,1,1},
        {0,0,0,1},
    },



};
//右S
int item4[][5][5]=
{
{
    {0,0,0,0},
    {0,1,0,0},
    {0,1,1,0},
    {0,0,1,0},
},
    {
        {0,0,0,0},
        {0,0,0,0},
        {0,1,1,0},
        {1,1,0,0},
    },
    {
        {0,0,0,0},
        {1,0,0,0},
        {1,1,0,0},
        {0,1,0,0},
    },
    {
        {0,0,0,0},
        {0,1,1,0},
        {1,1,0,0},
        {0,0,0,0},
    },







};
//左S
int item5[][5][5]=
{
{
    {0,0,0,0},
    {0,0,1,0},
    {0,1,1,0},
    {0,1,0,0},
},
    {
        {0,0,0,0},
        {0,1,1,0},
        {0,0,1,1},
        {0,0,0,0},
    },
    {
        {0,0,0,0},
        {0,0,0,1},
        {0,0,1,1},
        {0,0,1,0},
    },
    {
        {0,0,0,0},
        {0,0,0,0},
        {0,1,1,0},
        {0,0,1,1},
    },






};
//山形
int item6[][5][5]=
{
{
    {0,0,0,0},
    {0,0,1,0},
    {0,1,1,1},
    {0,0,0,0},
},
    {
        {0,0,0,0},
        {0,0,1,0},
        {0,0,1,1},
        {0,0,1,0},
    },
    {
        {0,0,0,0},
        {0,0,0,0},
        {0,1,1,1},
        {0,0,1,0},
    },
    {
        {0,0,0,0},
        {0,0,1,0},
        {0,1,1,0},
        {0,0,1,0},
    },








};



//长条
int item7[][5][5]=
{
{
    {0,0,1,0},
    {0,0,1,0},
    {0,0,1,0},
    {0,0,1,0},
},
    {
        {0,0,0,0},
        {1,1,1,1},
        {0,0,0,0},
        {0,0,0,0},
    },

};

//画方块变量
int i,j;
//左右移动
int b=0;

//随机数
int sui;
int sui1;

//背景状态 定义0为空 1为有
int beijing[400][725];
int beix,beiy;

//当前运动方块坐标和确认当前方块的为第几个
int weizhi=0;
int fk_yd[4][2];//0-3  0-1

//全局变量
int start_j=0;
//暂停
int zhanting=0;
int kaishi=0;

//方块旋转
int xuanzhuan=0;
//边界判断
int boxr1=1,boxl1=1;
int boxr2=1,boxl2=1;

//游戏结束
int game_over=0;

//分数
int score=0;

//修bug




Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
     x = 0;y=0;
     //sui=rand()%7;
     anniu2();
     anniu1();




     for(i=0;i<=29;i++)
      {
         beijing[400][i*25]=1;
         beijing[0][i*25]=1;
     }
     for (i=0;i<=16;i++)
     {
         beijing[i*25][725]=1;
     }
//画边界



    //屏幕刷新
}

void Widget::paintEvent(QPaintEvent *event)



   {
        QPen painter;
    QBrush Brush;
    Brush.setColor(Qt::gray);
    Brush.setStyle(Qt::Dense6Pattern);
    QPainter p(this);
    p.setPen(painter);
    p.setBrush(Brush);
    p.drawRect(460,50,220,310);//右边 下一个
    p.drawRect(25,0,youxi_w,youxi_h);//左边游戏内
    Brush.setColor(Qt::white);Brush.setStyle(Qt::Dense1Pattern);
    p.setBrush(Brush);
    //画背景


   if (start_j==1)
   {
    for (i=0;i<=4;i++)
        for (j=0;j<=4;j++)
        {
            switch(sui)
            {
            case 0:
                if (item1[xuanzhuan][i][j]==1)
                {
                    zuobiao();
                 p.drawRect(post_x,post_y,FK_bc,FK_bc);


                }

                break;
            case 1: if (item2[xuanzhuan][i][j]==1)
                {
                    zuobiao();
                 p.drawRect(post_x,post_y,FK_bc,FK_bc);


                }

                break;
            case 2: if (item3[xuanzhuan][i][j]==1)
                {
                    zuobiao();
                 p.drawRect(post_x,post_y,FK_bc,FK_bc);


                }
                break;
            case 3:
                if (item4[xuanzhuan][i][j]==1)
                {
                    zuobiao();
                    p.drawRect(post_x,post_y,FK_bc,FK_bc);


                   }
                break;
            case 4:
                if (item5[xuanzhuan][i][j]==1)
                {
                    zuobiao();
                 p.drawRect(post_x,post_y,FK_bc,FK_bc);


                }
                break;
            case 5:

                if (item6[xuanzhuan][i][j]==1)
                {
                     zuobiao();
                 p.drawRect(post_x,post_y,FK_bc,FK_bc);


                }
                break;
            case 6:

                if (item7[xuanzhuan][i][j]==1)
                {
                    zuobiao();
                 p.drawRect(post_x,post_y,FK_bc,FK_bc);


                }
                break;


}





        }//画方块
    for (i=0;i<=3;i++)
        for (j=0;j<=3;j++)
        {
            switch(sui1)//sui1
            {
            case 0:
                if (item1[0][i][j]==1)
                {
                 p.drawRect(520+j*FK_bc,200+i*FK_bc,FK_bc,FK_bc);

                }

                break;
            case 1: if (item2[0][i][j]==1)
                {
                  p.drawRect(520+j*FK_bc,200+i*FK_bc,FK_bc,FK_bc);

                }

                break;
            case 2: if (item3[0][i][j]==1)
                {
                  p.drawRect(520+j*FK_bc,200+i*FK_bc,FK_bc,FK_bc);

                }
                break;
            case 3:
                if (item4[0][i][j]==1)
                {
                    p.drawRect(520+j*FK_bc,200+i*FK_bc,FK_bc,FK_bc);

                   }
                break;
            case 4:
                if (item5[0][i][j]==1)
                {
                  p.drawRect(520+j*FK_bc,200+i*FK_bc,FK_bc,FK_bc);

                }
                break;
            case 5:

                if (item6[0][i][j]==1)
                {
                  p.drawRect(520+j*FK_bc,200+i*FK_bc,FK_bc,FK_bc);

                }
                break;
            case 6:

                if (item7[0][i][j]==1)
                {
                  p.drawRect(520+j*FK_bc,200+i*FK_bc,FK_bc,FK_bc);

                }
                break;
                } }
//画下一个
//
//画已经下落的
    Brush.setColor(QColor(253,237,96));
    p.setBrush(Brush);
for (i=0;i<=28;i++)
    for (j=1;j<=15;j++)
    {
        if (beijing[j*25][i*25]==1)
           p.drawRect(j*25,i*25,25,25);

    }
//测试边界

//p.drawText(800,800,QString::number(shifouxuanzhuan()));



int yix;
for (yix=0;yix<=3;yix++)

    {
        p.drawText(900,800+25*yix,QString::number(fk_yd[yix][0]));
        p.drawText(900+50,800+25*yix,QString::number(fk_yd[yix][1]));
    }




QFont Font;
Font.setPixelSize(45);
p.setFont(Font);
p.drawText(540,490,QString::number(score));

for (i=0;i<=29;i++)
    for (j=0;j<=16;j++)
    {
        //p.drawText(j*25,i*25+25,QString::number(beijing[j*25][i*25]));


    }



//到底




//消行



daodi();

}
}




void Widget::timerEvent(QTimerEvent *event)//屏幕刷新+方块下移
 {
if(event->timerId()==refresh)
{
x=x+25;
if (boxr1)
{
    b+=25;
    boxr1=0;
}
if (boxl1)
{
    b-=25;
    boxl1=0;
}
if (boxr2)
{
    b+=25;
    x-=25;
    boxr2=0;
}
if (boxl2)
{
    b-=25;
    x-=25;
    boxl2=0;
}


xiaohang();

update();
shibai();



}
}


Widget::~Widget()
{
    delete ui;
}

/*void Widget::on_pushButton_clicked()
{
 refresh=startTimer(300);
 start_j=1;
 x=0,b=0;

}
*/





void Widget::keyPressEvent(QKeyEvent *event)
{

    if(event->key()==Qt::Key_Right)

    {
        if(beijing[fx1+25][fy1]!=1&&beijing[fx2+25][fy2]!=1&&beijing[fx3+25][fy3]!=1&&beijing[fx4+25][fy4]!=1    &&beijing[fx1+25][fy1+25]!=1&&beijing[fx2+25][fy2+25]!=1&&beijing[fx3+25][fy3+25]!=1&&beijing[fx4+25][fy4+25]!=1&&zhanting==0)
           boxr1=1;
        else
        {
            boxr1=0;
            if(beijing[fx1+25][fy1+25]==1||beijing[fx2+25][fy2+25]==1||beijing[fx3+25][fy3+25]==1||beijing[fx4+25][fy4+25]==1&&zhanting==0)
            {
                if (fx1<=350&&fx2<=350&&fx3<=350&&fx4<=350)
            boxl2=1;
            }
            else boxr2=0;

            }







         }



    if(event->key()==Qt::Key_Left)



    {

        if(beijing[fx1-25][fy1]!=1&&beijing[fx2-25][fy2]!=1&&beijing[fx3-25][fy3]!=1&&beijing[fx4-25][fy4]!=1     &&beijing[fx1-25][fy1+25]!=1&&beijing[fx2-25][fy2+25]!=1&&beijing[fx3-25][fy3+25]!=1&&beijing[fx4-25][fy4+25]!=1&&zhanting==0)
            boxl1=1;
    else
        {
    boxl1=0;

    if(beijing[fx1-25][fy1+25]!=1||beijing[fx2-25][fy2+25]!=1||beijing[fx3-25][fy3+25]!=1||beijing[fx4-25][fy4+25]==1)
    {
        if (fx1>=50&&fx2>=50&&fx3>=50&&fx4>=50)
    boxl2=1;
}
     else boxl2=0;
        }
    }



    if(event->key()==Qt::Key_Up)
        {
        if (shifouxuanzhuan()!=1)
        xuanzhuan=xuanzhuanhanshu(xuanzhuan);


        }











    if(event->key()==Qt::Key_Down)
        {


        int xialuo,jia,cunshu[4],xiao;
        if(fx1>=0&&fx2>=0&fx3>=0&&fx4>=0)
        {
        for (xialuo=0;xialuo<=3;xialuo++)
        {


            for(jia=0; ;jia++)
            {
                if (     beijing      [fk_yd[xialuo][0]]   [fk_yd[xialuo][1]+jia*25]    ==1    )
                {
                    cunshu[xialuo]=jia;
                    break;

                }

            }

            }// cunshu[0]  cunshu[1]  cunshu[2]  cunshu[3]
        xiao=cunshu[0];
        int shu;
        for(shu=0;shu<=3;shu++)
        {
            if (xiao>cunshu[shu])
                xiao=cunshu[shu];


        }
        xiao--;
        //xiao--;
        //x=x+xiao*25;

        for(shu=0;shu<=3;shu++)
        {
            beijing[fk_yd[shu][0]] [fk_yd[shu][1]+xiao*25]=1;


            //失败历史

        }
        x=0;
        b=0;
        sui=sui1;
        sui1=rand()%7;
        xuanzhuan=0;



    }


}
}





void Widget::zuobiao()
{
    fk_yd[weizhi][0]=post_x;
     fk_yd[weizhi][1]=post_y;
     if (weizhi==3) weizhi=-1;
     weizhi++;
}//weizhi 0,1,2,3






void Widget::shengmingjiesu()

{


        x=0;
        b=0;
        sui=sui1;
        sui1=rand()%7;
        xuanzhuan=0;




}





void Widget::daodi()
{


    if (beijing[fx1][fy1+25]==1||beijing[fx2][fy2+25]==1||beijing[fx3][fy3+25]==1||beijing[fx4][fy4+25]==1)
    {
        beijing[fx1][fy1]=1;
        beijing[fx2][fy2]=1;
        beijing[fx3][fy3]=1;
        beijing[fx4][fy4]=1;



        shengmingjiesu();




    }

    }





void Widget::ban()
{
    if (zhanting==0)
    {
    killTimer(refresh);
    b1->setText("继续");
   zhanting=1;}

    else if (zhanting==1)
    {
   refresh=startTimer(225);
    b1->setText("暂停");

    zhanting=0;}
}





void Widget::ban2()
{

    refresh=startTimer(225);
    start_j=1;
    x=0,b=0;
    qingpin();//清屏
    game_over=0;
    b1->setEnabled(true);



    if (kaishi==0)
    {

    b2->setText("重新开始");
    b1->setText("暂停");
    zhanting=0;
   //kaishi=1;
    }

    else if (kaishi==1)
    {

    b2->setText("开始游戏");
    kaishi=0;}
}



void Widget::anniu1()
{
    b1=new QPushButton(this);
    //b1->setParent(this);

    b1->setText("暂停");
    b1->move(610,630);
    b1->resize(71,51);
    b1->setFocusPolicy(Qt::NoFocus);
    connect(b1,&QPushButton::pressed,this,&Widget::ban);

    b1->setEnabled(false);
}



void Widget::anniu2()

{
    b2=new QPushButton(this);
    b2->setParent(this);

    b2->setText("开始游戏");
    b2->move(480,630);
    b2->resize(111,51);
    b2->setFocusPolicy(Qt::NoFocus);
    connect(b2,&QPushButton::pressed,this,&Widget::ban2);
}

//左右边界

void Widget::xiaohang()
{
    int hang,lie,t;
    for (hang=0;hang<=28;hang++)
    {  t=0;
        for(lie=1;lie<=15;lie++)
        {
            t=beijing[lie*25][hang*25]+t;
            if (t==15)
            {
                score+=10;
                for(lie=1;lie<=15;lie++)//目前已知第几行hang
                {
                    beijing[lie*25][hang*25]=0;
                }
                hang--;
                for( ;hang>=0;hang--)
                {
                    for (lie=1;lie<=15;lie++)
                    {
                        beijing[lie*25][hang*25+25]=beijing[lie*25][hang*25];
                    }
                }


            }

        }

}


}
void Widget::shibai()
{
   int toushu;

   for (toushu=1;toushu<=15;toushu++)
   {

       if (beijing[toushu*25][-25]==1)
       {
           if (game_over==0)
           {
           QMessageBox::information(NULL, "游戏结束", "你输了","不服气再来一次");
           game_over=1;
           qingpin();

           killTimer(refresh);
           start_j=0;
           b2->setText("开始游戏");
           b1->setEnabled(false);
           }

       }

   }


}

//需要变量sui，xuanzhuan,
int Widget::shifouxuanzhuan()
{
    int next;
    int tuichu;
    tuichu=0;
    next=xuanzhuan;

    next=xuanzhuanhanshu(xuanzhuan);//下一个随机旋转数；
    for (i=0;i<=4;i++)
        for (j=0;j<=4;j++)
        {
            if(tuichu==0)
            {
            switch(sui)
            {
            case 0:
                if (item1[next][i][j]==1)
                {

                 if (beijing[post_x][post_y]==1)
                 {return 1;
                 tuichu=1;
                 }





                }

                break;
            case 1: if (item2[next][i][j]==1)
                {
                    if (beijing[post_x][post_y]==1)
                    {return 1;
                    tuichu=1;
                    }



                }

                break;
            case 2: if (item3[next][i][j]==1)
                {

                    if (beijing[post_x][post_y]==1)
                    {return 1;
                    tuichu=1;
                    }



                }
                break;
            case 3:
                if (item4[next][i][j]==1)
                {

                    if (beijing[post_x][post_y]==1)
                    {return 1;
                    tuichu=1;
                    }


                   }
                break;
            case 4:
                if (item5[next][i][j]==1)
                {

                    if (beijing[post_x][post_y]==1)
                    {return 1;
                    tuichu=1;
                    }


                }
                break;
            case 5:

                if (item6[next][i][j]==1)
                {

                    if (beijing[post_x][post_y]==1)
                    {return 1;
                    tuichu=1;
                    }



                }
                break;
            case 6:

                if (item7[next][i][j]==1)
                {

                    if (beijing[post_x][post_y]==1)
                    {return 1;
                    tuichu=1;
                    }



                }
                break;
        }
        }


}
}

int Widget::xuanzhuanhanshu(int a)
{
    switch(sui)
    {
    case 0:a=0;break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:{
        a++;
        if (a>3)
            a=0;
    }break;

    case 6:
    {
        a++;
        if (a>1)
            a=0;
    }break;


}
    return a;
}

void Widget::qingpin()
{
    int qingx,qingy;
    for (qingx=1;qingx<=15;qingx++)
        for (qingy=-5;qingy<=28;qingy++)
        {
            beijing[qingx*25][qingy*25]=0;
        }
}



