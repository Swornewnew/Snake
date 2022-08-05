#include <graphics.h>      // 引用图形库头文件
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
struct SNAKE {   //蛇的速度，方向，大小
    int speed;
    int dirct;
    int size;
};
struct node {    //蛇头的坐标
    int x;
    int y;
};
struct DOT {    //食物的坐标
    int x;
    int y;
};
enum {       //方向
    RIGHT,
    LEFT,
    UP,
    DOWN,
};
#define snake_num 500    //蛇的最大长度
#define WINDOW_SIZE_LENGTH 200 //窗口长度
#define WINDOW_SIZE_WEITH 200  //窗口宽度
struct node point[snake_num];
struct SNAKE snake;
struct DOT dot;
void snakeattribute() {   //设置蛇的初始属性 ,点的初始位置
    snake.size = 4;
    snake.speed = 10;
    snake.dirct = RIGHT;
    srand(GetTickCount());
    dot.x = rand() % (WINDOW_SIZE_LENGTH / 10 - 2) * 10+10;
    dot.y = rand() % (WINDOW_SIZE_WEITH / 10 - 2) * 10+10;
    for (int i = 0; i <snake.size; i++) {
        point[i].x = 50 - i * 10;
        point[i].y = 10;
    }
}
void setingame() {     // 创建绘图窗口，背景颜色
    initgraph(WINDOW_SIZE_LENGTH, WINDOW_SIZE_WEITH);   //窗口大小
    setbkcolor(BLACK);
    cleardevice();
   
}
void dorw() {   //绘制蛇和点
    BeginBatchDraw();
    setbkcolor(RGB(0, 0, 0));
    cleardevice();
    setfillcolor(BLUE);   //设置蛇的颜色
    for (int i = 0; i < snake.size; i++) {
        solidcircle(point[i].x, point[i].y, 5);   // 画圆，半径 5        
    }
    setfillcolor(RED);   //设置点的颜色
    solidcircle(dot.x, dot.y, 5);
    for (int x = 5; x < WINDOW_SIZE_LENGTH; x += 10) {    //画网格
        line(x, 5, x, WINDOW_SIZE_WEITH-5);
    }
    for (int y = 5; y < WINDOW_SIZE_WEITH; y += 10) {
        line(5, y, WINDOW_SIZE_LENGTH-5, y);
    }
    EndBatchDraw();
}
void snakemove() {
    int i;
    for (i = snake.size-1; i>0; i--) {  //蛇的身体跟随蛇头移动
        point[i] = point[i - 1];
    }
    switch (snake.dirct) {
        case RIGHT:
            point[0].x += snake.speed;
            break;
        case LEFT:
            point[0].x -= snake.speed;
            break;
        case UP:
            point[0].y -= snake.speed;
            break;
        case DOWN:
            point[0].y += snake.speed;
            break;
    }
}
void snakedirction() {   //调整蛇的方向
    if(_kbhit()){
        switch (_gettch()) {
        case 'w':
        case 'W':
            if (snake.dirct != DOWN) {
                snake.dirct = UP;
            }
            break;
        case 's':
        case 'S':
            if (snake.dirct != UP) {
                snake.dirct = DOWN;
            }
            break;
        case 'a':
        case 'A':
            if (snake.dirct != RIGHT) {
                snake.dirct = LEFT;
            }
            break;
        case 'd':
        case 'D':
            if (snake.dirct != LEFT) {
                snake.dirct = RIGHT;
            }
            break;
        }
    }
}
bool isprime() {        //判断点是否在蛇内
    bool ret = 0;
    for (int i = 0; i < snake.size; i++) {
        if (point[i].x == dot.x && point[i].y == dot.y) {
            ret = 1;
        }
    }
    return ret;
}
void dotposition() {   //随机点位置       
    if (point[0].x == dot.x && point[0].y == dot.y) {
        snake.size++;
        do {
            dot.x = rand() % (WINDOW_SIZE_LENGTH/10-2) * 10+10;      //不超过窗口最大长度
            dot.y = rand() % (WINDOW_SIZE_WEITH/10-2) * 10+10;     //不超过窗口最大宽度
        } while (isprime());
    }
}

bool gameover() {    //判断游戏是否结束
    bool ret=0;
    if (point[0].x+10 > WINDOW_SIZE_LENGTH || point[0].y+10 > WINDOW_SIZE_WEITH || point[0].y-10< 0 || point[0].x-10 < 0) {
        ret = 1;
    }
    for (int i = 1; i < snake.size; i++) {
        if (point[i].x == point[0].x && point[i].y == point[0].y) {
            ret = 1;
        }
    }
    return ret;
}
int score() {
    int ret;
    ret = (snake.size - 4) * 10;
    return ret;
}
int main()
{
    snakeattribute();
    setingame();    
    while (1)
    {
        if (gameover()) {
            system("PAUSE");
            break;
        }
        dotposition();
        snakedirction();
        dorw();
        snakemove();
        Sleep(250);        
    }
    printf("GAME OVER\n");
    printf("你的得分为%d分\n", score());
}
