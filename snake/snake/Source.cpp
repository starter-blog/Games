#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

int SnakeX[100] = { 4, 5 }, SnakeY[100] = { 4,4,4,4 } ;
int FeedX, FeedY;
int Score, Die;
int length = 1;

void gotoxy(int x, int y)
{
	COORD CursorPosition = { 2 * x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}

void move(int x, int y) {
	if (SnakeX[length] == FeedX && SnakeY[length] == FeedY) {
		length++;
		for (int i = length; i > 0; i--) {
			SnakeX[i] = SnakeX[i - 1];
			SnakeY[i] = SnakeY[i - 1];
		}
		FeedX = 0;
		FeedY = 0;
	}
	for (int i = 0; i < length; i++) {
		SnakeX[i] = SnakeX[i + 1];
		SnakeY[i] = SnakeY[i + 1];
	}
	SnakeX[length] = SnakeX[length - 1] + x;
	SnakeY[length] = SnakeY[length - 1] + y;
	for (int i = 1; i < length; i++) {
		if (SnakeX[i] == SnakeX[length] && SnakeY[i] == SnakeY[length]) Die = 1;
	}
}

void item()
{
	int check = 1;
	int RandomX;
	int RandomY;
	for(int k = 0; k < 100; k++) {
		check = 1;
		srand((unsigned)time(NULL));
		RandomX = rand() % 8 + 1;
		RandomY = rand() % 8 + 1;
		for (int i = 0; i <= length; i++) {
			if (RandomX != SnakeX[i] && RandomY != SnakeY[i]) {
				check = 0;
			}
		}
		if (check) break;
	}
	if (check) {
		FeedX = RandomX;
		FeedY = RandomY;
		gotoxy(FeedX, FeedY);
		printf("*");
	}
}

void bg_and_snake()
{
	int timing = 0;
	int Mode = 0;

	char arrow;

	char bns[10][10];
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if(i == 0 || i == 9 || j == 0 || j== 9)
			bns[i][j] = -1;
		}
	}
	//----------- 맵 그리기 -------------
	int i, j;
	for (i = 0; i<10; i++)
	{
		for (j = 0; j<10; j++)
		{
			if (bns[i][j] == -1)
			{
				printf("□"); // 테두리
			}
			else
			{
				printf("  "); // 공백
			}
		}printf("\n");

	}
	//----------- 맵 그리기 -------------
	//----------- 뱀 그리기 -------------
	while (1)
	{
		if (Die) return;
		if (SnakeX[length] == 0 || SnakeX[length] == 9 || SnakeY[length] == 0 || SnakeY[length] == 9) return;
		if (timing > 20000) {
			Score += length * 5;

			gotoxy(0, 10);
			printf("Score : %d", Score);

			if (!FeedX && !FeedY) item();
			switch(Mode) {
			case 1: move(-1, 0); break;
			case 2: move(1, 0); break;
			case 3: move(0, -1); break;
			case 4: move(0, 1); break;
			}
				gotoxy(SnakeX[0], SnakeY[0]);
				printf(" ");
				gotoxy(SnakeX[length], SnakeY[length]);
				printf("■");
				timing = 0;
		}

		if (_kbhit()) {
			arrow = _getch();
			switch (arrow)
			{
			case LEFT:
				if (Mode != 2) {
					Mode = 1; timing = 20001;
				}
				break;
			case RIGHT:
				if (Mode != 1) {
					Mode = 2; timing = 20001;
				}
				break;
			case UP:
				if (Mode != 4) {
					Mode = 3; timing = 20001;
				}
				break;
			case DOWN:
				if (Mode != 3) {
					Mode = 4; timing = 20001;
				}
				break;
			}
		}
		else timing ++;
	}
}

int main()
{
	{// ------------------ 커서 지우는 함수 ---------------------
		HANDLE hConsole; // 콘솔 핸들
		CONSOLE_CURSOR_INFO ConsoleCursor; // 콘솔커서 정보 구조체

		hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // 핸들을 구하고

		ConsoleCursor.bVisible = false; // true 보임 , false 안보임
		ConsoleCursor.dwSize = 1; // 커서 사이즈

		SetConsoleCursorInfo(hConsole, &ConsoleCursor); // 설정
														// ------------------ 커서 지우는 함수 ---------------------
	}
	system("color 0a");
	system("mode con: COLS=20 LINES=11");
	bg_and_snake();
}