#include"snake.h"
void test() {
	Snake snake = { 0 };//初始化蛇状态InitGame(&snake);
	InitGame(&snake);//初始化游戏
	RunGame(&snake);// 运行游戏

}

int main(){
	setlocale(LC_ALL, "");
	srand((unsigned int)time(NULL));
	
	test();
	return 0;
}

//main函数 ：只负责基础设置（如设置区域、初始化随机数种子）
//test函数 ：专注于游戏相关的逻辑（创建贪吃蛇、初始化游戏、运行游戏）
//这种分离使得每个函数职责单一，更容易理解和维护。
