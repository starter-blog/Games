#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

char choice;
int x, y;
int map[4][4];
int point;
int turn;
int randomX, randomY, random;
void show()
{
	srand((unsigned)time(NULL));
	while (true)
	{
		randomX = rand() % 4;
		randomY = rand() % 4;
		random = (rand() % 2 + 1) * 2;
		if (map[randomX][randomY] == 0) {
			map[randomX][randomY] = random;
			break;
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (map [i][j] != 0) printf("%4d", map[i][j]);
			else printf("    ");
		}
		printf("\n");
	}
}

void gotoxy(int x, int y)
{
	for (int o = 0; o < 4; o++) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (x != 0 && i + x >= 0 && i + x < 4) {
					if (map[i + x][j] == 0 || map[i + x][j] == map[i][j]) {
						if (map[i + x][j] == map[i][j]) point += map[i][j];
						map[i + x][j] += map[i][j];
						map[i][j] = 0;
					}
				}
				if (y != 0 && j + y >= 0 && j + y < 4) {
					if (map[i][j + y] == 0 || map[i][j + y] == map[i][j]) {
						if (map[i][j + y] == map[i][j]) point += map[i][j];
						map[i][j + y] += map[i][j];
						map[i][j] = 0;
					}
				}
			}
		}
		for (int i = 3; i >= 0; i--) {
			for (int j = 3; j >= 0; j--) {
				if (x != 0 && i + x >= 0 && i + x < 4) {
					if (map[i + x][j] == 0 || map[i + x][j] == map[i][j]) {
						if (map[i + x][j] == map[i][j]) point += map[i][j];
						map[i + x][j] += map[i][j];
						map[i][j] = 0;
					}
				}
	
				if (y != 0 && j + y >= 0 && j + y < 4) {
					if (map[i][j + y] == 0 || map[i][j + y] == map[i][j]) {
						if (map[i][j + y] == map[i][j]) point += map[i][j];
						map[i][j + y] += map[i][j];
						map[i][j] = 0;
					}
				}
			}
		}
	}
}

void begin() {
	system("mode con: cols=16 lines=5");
	system("color 0a");
}//크기 조정 및 색 변화

void move() {
	choice = getch();
	if (choice == 'w' || choice == 'W' || choice == 72) gotoxy(-1, 0);
	else if (choice == 'a' || choice == 'A' || choice == 75) gotoxy(0, -1);
	else if (choice == 's' || choice == 'S' || choice == 80) gotoxy(1, 0);
	else if (choice == 'd' || choice == 'D' || choice == 77) gotoxy(0, 1);
	else return;
	turn++;
}

int main() {

	begin();

	while (1)
	{
		printf("1. 게임시작\n2. 종료\n");
		choice = getch();
		if (choice == '1') break;
		else if (choice == '2') return 0;
		else
		{
			system("cls");
			printf("1 혹은 2중에 입력해주세요\n");
		}
	}

	while (1)
	{
		system("cls");
		show();
		move();
	}
}