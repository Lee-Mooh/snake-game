#include"snake.h"  //头文件

//定位光标
void SetPos(int x, int y) {
	HANDLE houtput = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Pos = { x,y };
	SetConsoleCursorPosition(houtput, Pos);

}
//隐藏光标
void  HideCursor(){
	HANDLE houtput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor_info = { 0 }; //创建光标信息
	GetConsoleCursorInfo(houtput,&cursor_info);
	cursor_info.bVisible = 0;
	SetConsoleCursorInfo(houtput, &cursor_info);
}
void pause(){
	while(1){
		Sleep(300);
		if (KEY_PRESS(VK_SPACE)) {
			SetPos(0, 28);
			printf("                                                                     ");
			break;
		
		}
	}
}

void CreateWelcome() {
	SetPos(35,15);
	printf("欢乐时光就要开始了");
	SetPos(0, 28);
}
void NOTICE(){
	SetPos(30,10);
	printf("请使用W,A,S,D来控制蛇的移动");
	SetPos(35,12);
	printf("J为加速,K为减速");
	SetPos(30,14);
	printf("ESC退出游戏,space暂停游戏");
	SetPos(0,28);
	
}
void CreateMap() {
	setlocale(LC_ALL,"");
	SetPos(0, 0);
	for (int i = 0; i < 44; i+=2){
		wprintf(L"%lc", WALL);
	}
	SetPos(0, 25);
	for (int i = 0; i < 44; i+=2) {
		wprintf(L"%lc", WALL);
	}
	for (int i = 0; i < 26; i++) {
		SetPos(0, i);
		wprintf(L"%lc", WALL);
	}
	for (int i = 0; i < 26; i++) {
		SetPos(44, i);
		wprintf(L"%lc",WALL);
	}
	SetPos(0,28);

}
void CreateHelp(){
	SetPos(55, 5);
	printf("不允许碰墙,不允许碰蛇身");
	SetPos(55, 8);
	printf("请使用W,A,S,D来控制蛇的移动");
	SetPos(55, 10);
	printf("J为加速,K为减速");
	SetPos(55,12);
	printf("加速食物分值变大,减速食物分值变小");
	SetPos(55, 14);
	printf("ESC退出游戏,space暂停游戏");
	SetPos(0, 28);
}
void InitSnake(Snake*p){
	setlocale(LC_ALL, "");
	SetPos(32, 5);
	SnakeNode* cur = NULL;
	for (int i = 0; i < 5; i++) {
	    cur = (SnakeNode*)malloc(sizeof(SnakeNode));
		cur->next = NULL;
		cur->prev = NULL;
		cur->x = POS_X +i*2;
		cur->y = POS_Y;
    if (p->phead ==NULL) {
			p->phead = cur;
			p->ptail = cur;
	}
		else {
			cur->next = p->phead;
			p->phead->prev = cur;
			p->phead = cur;
		}
	}
	cur = p->phead;//初始化cur
	while (cur!= NULL) {
		SetPos(cur->x, cur->y);//定位光标到每一个节点
		wprintf(L"%lc",BODY);
		cur = cur->next;
    } 
	p->status = OK;
	p->score = 0;
	p->way = RIGHT;
	p->foodscore = 10;
	p->sleeptime = 250;
	SetPos(0, 28);
 }

void CreateFood(Snake*p){
	int x, y;
again:
	x = (rand() % 20+ 1)*2;
	y = rand() % 24+ 1;
	SnakeNode* cur = p->phead;
	while (cur!=NULL) {
		if (cur->x == x && cur->y == y) {
			goto again;
		}
		cur = cur->next;
		
	}
	SnakeNode* pFood = (SnakeNode*)malloc(sizeof(SnakeNode));
	//这里千万不能写反,如果是pFood=p->pfood,因为pfood未初始化,所以刚分配空间的pFood变成了NULL,造成了内存泄漏
	p->pfood=pFood;
	pFood->x = x;
	pFood->y = y;
    SetPos(x, y);
	wprintf(L"%lc",FOOD);
	SetPos(0, 28);
}

void InitGame(Snake*p) {
	system("mode con cols=100 lines=35");
	system("title 贪吃蛇");
	PlaySound(TEXT("snakemusic .wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	HideCursor();
	CreateWelcome();
	system("pause");
	system("cls");
    
	NOTICE();
	system("pause");
	system("cls");
	CreateMap();
	CreateHelp();
	InitSnake(p);
	CreateFood(p);
	SetPos(0,28);
	system("echo ------------------- 请按任意键开始游戏 -------------------&pause>nul");
	

}
void HeadAppear(Snake*p){
	SnakeNode* NewHead = (SnakeNode*)malloc(sizeof(SnakeNode));
	if (p->way == UP) {
		NewHead->x = p->phead->x;
		NewHead->y = p->phead->y-1;
	}
	else if (p->way == DOWN) {
		NewHead->x = p->phead->x;
		NewHead->y = p->phead->y+1;
	}
	else if (p->way == LEFT) {
		NewHead->x = p->phead->x-2;
		NewHead->y = p->phead->y;
	}
	else if (p->way == RIGHT) {
		NewHead->x = p->phead->x+2;
		NewHead->y = p->phead->y;
	}
	NewHead->next = p -> phead;
    p->phead->prev=NewHead  ;
	p->phead = NewHead;
	SetPos(NewHead->x, NewHead->y);
	wprintf(L"%lc",BODY);
}
void TailDisappear(Snake*p){
	SnakeNode* cur = p->ptail;
	SetPos(cur->x, cur->y);
	printf(" ");
	p->ptail = cur->prev;
	cur->prev->next = NULL;
	free(cur);
}
int NextisFood(Snake*p){
	if (p->way == UP && p->pfood->x == p->phead->x && p->pfood->y == p->phead->y - 1) {
		return 1;
	}
	else if (p->way == DOWN&& p->pfood->x == p->phead->x && p->pfood->y == p->phead->y+1) {
		return 1;
	}
	else if (p->way == RIGHT&& p->pfood->x == p->phead->x+2 && p->pfood->y == p->phead->y) {
		return 1;
	}
	else if (p->way == LEFT&& p->pfood->x == p->phead->x-2 && p->pfood->y == p->phead->y) {
		return 1;
	}
	return 0;
}
void KillByWall(Snake*p){
	if (p->phead->x == 0 || p->phead->x == 44 || p->phead->y == 0 || p->phead->y==25) {
        PlaySound(NULL, NULL, SND_FILENAME);
		p->status = KILL_BY_WALL;
		SetPos(30,26);
		printf("GAME OVER");
		SetPos(30,27);
		printf("你的的总得分是%d",p->score);
		SetPos(p->phead->x, p->phead->y);
		wprintf(L"%lc", L'×');
	}
}
void KillBySelf(Snake*p){
	SnakeNode* cur = p->phead;
	while (cur->next!= NULL) {//这里不能写cur!=NULL,因为最后一个结点的cur->next->x/y是NULL
		if (cur->next->x == p->phead->x && cur->next->y == p->phead->y) {
           PlaySound(NULL, NULL, SND_FILENAME);
			p->status = KILL_BY_SELF;
			SetPos(30, 26);
			printf("GAME OVER");
			SetPos(30, 27);
			printf("你的的总得分是%d", p->score);
			SetPos(p->phead->x, p->phead->y);
			wprintf(L"%lc", L'×');
			break;
		}
		cur = cur->next;
	}

}
void RunGame(Snake* p) {
	SetPos(0, 28);
	printf("                                                         ");
	do {
		//打印得分
		SetPos(4, 26);
		printf("当前的得分是:%d",p->score);
		SetPos(4, 27);
		printf("当前食物的分数是:%d",p->foodscore);
		//改变状态
		if (KEY_PRESS(87)&&p->way!=DOWN) {
			p->way = UP;
		}
		else if (KEY_PRESS(83)&&p->way!=UP) {
			p->way = DOWN;
		}
		else if (KEY_PRESS(65)&&p->way!=RIGHT) {
			p->way = LEFT;
		}
		else if (KEY_PRESS(68)&&p->way!=LEFT) {
			p->way = RIGHT;
		}
		
		else if (KEY_PRESS(VK_SPACE)) {
			SetPos(0, 28);
			printf("--------------------按下空格以继续游戏--------------------");
			pause();
		}
		else if (KEY_PRESS(VK_ESCAPE)) {
			p->status = EXIT;
			break;
		}
		else if (KEY_PRESS(74)) {
			if (p->sleeptime > 50) {
				p->sleeptime -= 50;
				p->foodscore += 10;
			}
		}
		else if (KEY_PRESS(75)) {
			if (p->sleeptime < 500) {
				p->sleeptime += 50;
				p->foodscore -= 10;
			}
		}
		if (NextisFood(p) ){
			free(p->pfood);
			HeadAppear(p);
			CreateFood(p);
			p->score += p->foodscore;
		}
		else {
			TailDisappear(p);
			HeadAppear(p);
		}
		KillByWall(p);
		KillBySelf(p);
		Sleep(p->sleeptime);
	
	} while (p->status == OK);
	SetPos(0, 28);
}