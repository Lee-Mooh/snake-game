#include<stdio.h>
#include<Windows.h>//调用API函数
#include<locale.h>//本地化,打印汉字,宽字符
#include<stdlib.h>//要生成随机数函数
#include<time.h>
#define WALL  L'□'  //墙体
#define BODY  L'●' //蛇的身体
#define FOOD L'★' //蛇的食物
#define POS_X 24 //初始化页面的坐标
#define POS_Y 8 //初始化页面的坐标
#define KEY_PRESS(VK)((GetAsyncKeyState(VK)&1)?1:0)//用来确定是否按下
#pragma comment(lib,"Winmm.lib")//添加音乐

enum DIRECTION {
	UP = 1,
	DOWN,
	LEFT,
	RIGHT
};
enum STATUS {
	OK,
	KILL_BY_WALL,
	KILL_BY_SELF,
	EXIT
};

//设置蛇的一个结点
typedef struct SnakeNode {
	int x;
	int y;
	struct SnakeNode* prev;//前一个节点
	struct SnakeNode* next;//后一个结点
}SnakeNode;

typedef struct Snake {//这个结构体是储存整个蛇的状态的
	SnakeNode* phead;//创建一个头指针
	SnakeNode* ptail;//创建一个尾指针
	SnakeNode* pfood;//创建一个指向食物的指针
	enum STATUS status;
	enum DIRECTION way;
	int score; //总得分
	int foodscore;//每个食物的分数
	int sleeptime;//每走一步的间隔时间

}Snake;




  
