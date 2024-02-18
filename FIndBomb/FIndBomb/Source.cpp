#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>

int Bomb, FB, X, Y;
int Map[9][9], Hint[9][9], IFSHOW[9][9], Check[9][9];

void gotoxy(int x, int y) {
	COORD Cur = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

void Moving(int Mode) {
	if (Mode == 0) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + 16 * 11);
	else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + 16 * 0);
	gotoxy(8 * X, 4 * Y); 
	printf("          ");
	gotoxy(8 * X, 4 * Y + 1);
	printf("  ");
	gotoxy(8 * X + 8, 4 * Y + 1);
	printf("  ");
	gotoxy(8 * X, 4 * Y + 2);
	printf("  ");
	gotoxy(8 * X + 8, 4 * Y + 2);
	printf("  ");
	gotoxy(8 * X, 4 * Y + 3);
	printf("  ");
	gotoxy(8 * X + 8, 4 * Y + 3);
	printf("  ");
	gotoxy(8 * X, 4 * Y + 4);
	printf("          ");
}

void Setting() {
	srand((unsigned)time(NULL));
	HANDLE COUT = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO Info;
	GetConsoleCursorInfo(COUT, &Info);
	Info.bVisible = FALSE;
	SetConsoleCursorInfo(COUT, &Info);
	system("Mode con: COLS=74 LINES=37");
	if (Bomb < 40) {
		for (int i = 0; i < Bomb; i++) {
			int RandX = rand() % 9;
			int RandY = rand() % 9;
			if (Map[RandX][RandY] == 0) Map[RandX][RandY] = 1;
			else i--;
		}
	}
	else {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				Map[i][j] = 1;
			}
		}
		for (int i = 0; i <= 80 - Bomb; i++) {
			int RandX = rand() % 9;
			int RandY = rand() % 9;
			if (Map[RandX][RandY] == 1) Map[RandX][RandY] = 0;
			else i--;
		}
	}
	for (int i = 0; i < 37; i++) {
		for (int j = 0; j < 74; j += 2) {
			if (i % 4 == 0 || j % 8 == 0) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + 16 * 0);
			else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + 16 * 7);
			printf("  ");
		}
	}
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (Map[i][j] == 1) {
				for (int x = -1; x <= 1; x++) {
					for (int y = -1; y <= 1; y++) {
						if(i + x >= 0 && i + x < 9 && j + y >= 0 && j + y < 9)
						Hint[i + x][j + y]++;
					}
				}
			}
		}
	}
}

void ShowHint(int x, int y) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + 16 * 7);
	if (IFSHOW[x][y] == 0) {
		IFSHOW[x][y] = 1;
		gotoxy(8 * x + 4, 4 * y + 2);
		switch (Hint[x][y])
		{
		case 0 : SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + 16 * 7); break;
		case 1 : SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1 + 16 * 7); break;
		case 2 : SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2 + 16 * 7); break;
		case 3 : SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3 + 16 * 7); break;
		case 4 : SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4 + 16 * 7); break;
		case 5 : SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5 + 16 * 7); break;
		case 6 : SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6 + 16 * 7); break;
		case 7 : SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8 + 16 * 7); break;
		case 8 : SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9 + 16 * 7); break;
		}
		printf("%2d", Hint[x][y]);
		FB++;
		if (Hint[x][y] != 0) return;
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				if (i + x >= 0 && i + x < 9 && j + y >= 0 && j + y < 9 && !(i == 0 && j == 0))
					ShowHint(x + i, y + j);
			}
		}
	}
}

int main() {
	printf("지뢰의 개수를 고르시오 (최대 80개)\n");
	while (1) {
		scanf("%d", &Bomb);
		if (Bomb <= 80) break;
		else {
			system("cls");
			printf("최대 80개 까지 가능합니다.\n");
		}
	}
	Setting();
	Moving(0);
	while (1) {
		if (FB == 81 - Bomb) {
			system("cls");
			printf("승리!");
			Sleep(1000);
			return 0;
		}
		char choice = _getch();
		if (choice == 72) {
			Moving(1);
			if (Y > 0) Y--;
			else Y = 8;
			Moving(0);
		}
		if (choice == 75) {
			Moving(1);
			if (X > 0) X--;
			else X = 8;
			Moving(0);
		}
		if (choice == 77) {
			Moving(1);
			if (X < 8) X++;
			else X = 0;
			Moving(0);
		}
		if (choice == 80) {
			Moving(1);
			if (Y < 8) Y++;
			else Y = 0;
			Moving(0);
		}
		if (choice == ' ' && Check[X][Y] == 0) {
			if (Map[X][Y] == 1) return 0;
			ShowHint(X, Y);
		}
		if (choice == 9) {
			if (Check[X][Y] == 0 && !IFSHOW[X][Y]) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + 16 * 7);
				gotoxy(8 * X + 4, 4 * Y + 2);
				printf("▶");
				Check[X][Y] = 1;
			}
			else if (!IFSHOW[X][Y]) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + 16 * 7);
				gotoxy(8 * X + 4, 4 * Y + 2);
				printf("  ");
				Check[X][Y] = 0;
			}
		}
	}
}