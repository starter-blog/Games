#define LeftArrow 75
#define RightArrow 77
#define UpArrow 72
#define DownArrow 80
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>
#include <math.h>
int Map[7][7], Player[2][7][7], Unit[2][7], MovePossible[7][7], AttackPossible[7][7], Hp[7][7], St[7][7], X, Y, SelectX, SelectY, Action, Time, Turn = 0, Mode = 1, check[2], Blank[2], cx, cy, cc;
void gotoxy(int x, int y);
void setting();
void DrawUnit(int x, int y);
void ShowMove(int x, int y);
void ShowAttack(int x, int y);
void ReMoving(int x, int y);
void ReselectionMode(int x, int y);
void SelectionMode(int x, int y);
void Moving(int x, int y);
void Attacking(int x, int y);
int main() {
	setting();
	SelectionMode(SelectX, SelectY);
	while (1) {
		Blank[0] = 0; Blank[1] = 0, check[0] = 0, check[1] = 0, cc = 0;
		for (int k = 0; k < 2; k++) {
			for (int i = 0; i < 7; i++) {
				for (int j = 0; j < 7; j++) {
					if (Player[k][i][j] > 0) {
						check[k]++;
						if (Player[k][i][j] == 6) cc = 1;
						else cc = 0;
						for (cx = -1 - cc; cx <= 1 + cc; cx++) {
							for (cy = -1 - cc; cy <= 1 + cc; cy++) {
								if (i + cx > 0 && i + cx < 7 && j + cy > 0 && j + cy < 7 && Map[i + cx][j + cy] == 0) Blank[k]++;
							}
						}
					}
				}
			}
			if (check[k] == 0) {
				system("cls");
				for (int L = 0; L < 22; L++) {
					gotoxy(0, L);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 + 16 * 7);
					if (L == 11) {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 + 16 * 0);
						printf("Player %d 의 All Kill 승리", 2 - k);
					}
					else if (L % 2 == 0) {
						if (k == 1) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 + 16 * 4);
						else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 + 16 * 1);
					}
					printf("                                            ");
				}
				Sleep(10000);
				return 0;
			}
			if (Blank[k] == 0) {
				system("cls");
				for (int L = 0; L < 22; L++) {
					gotoxy(0, L);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 + 16 * 7);
					if (L == 11) {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 + 16 * 0);
						printf("Player %d의 이동불가로 Player %d의 승리", k + 1, 2 - k);
					}
					else if (L % 2 == 0) {
						if (k == 1) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 + 16 * 4);
						else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 + 16 * 1);
					}
					printf("                                            ");
				}
				Sleep(10000);
				return 0;
			}
		}
		char choice = _getch();
		switch (Mode) {
		case 1:
			if (choice == LeftArrow && X > 0) SelectionMode(-1, 0);
			if (choice == RightArrow && X < 6) SelectionMode(1, 0);
			if (choice == UpArrow && Y > 0) SelectionMode(0, -1);
			if (choice == DownArrow && Y < 6) SelectionMode(0, 1);
			if (choice == ' ') {
				if (Player[Turn][X][Y] != 0) {
					if (St[X][Y] < -1) {
						St[X][Y] = 0;
						DrawUnit(X, Y);
						Action++;
						break;
					}
					Mode = 2;
					SelectX = X;
					SelectY = Y;
					ShowMove(SelectX, SelectY);
					Moving(0, 0);
				}
			}
			break;
		case 2:
			if (choice == LeftArrow && X > 0) Moving(-1, 0);
			if (choice == RightArrow && X < 6) Moving(1, 0);
			if (choice == UpArrow && Y > 0) Moving(0, -1);
			if (choice == DownArrow && Y < 6) Moving(0, 1);
			if (choice == 9) {
				Moving(0, 0);
				ReMoving(SelectX, SelectY);
				ShowAttack(SelectX, SelectY);
				Moving(0, 0);
				Mode = 3;
			}
			if (choice == 27) {
				Mode = 1;
				DrawUnit(X, Y);
				if (Map[X][Y] == 0) ReMoving(X, Y);
				ReMoving(SelectX, SelectY);
				ReselectionMode(SelectX, SelectY);
				SelectionMode(0, 0);
			}
			if (choice == ' ') {
				if (MovePossible[X][Y]) {
					int XX = X;
					int YY = Y;
					X = SelectX;
					Y = SelectY;
					ReMoving(SelectX, SelectY);
					SelectionMode(XX - SelectX, YY - SelectY);
					Map[X][Y] = Map[SelectX][SelectY];
					Player[Turn][X][Y] = Player[Turn][SelectX][SelectY];
					Hp[X][Y] = Hp[SelectX][SelectY];
					St[X][Y] = St[SelectX][SelectY];
					Map[SelectX][SelectY] = 0;
					Player[Turn][SelectX][SelectY] = 0;
					Hp[SelectX][SelectY] = 0;
					St[SelectX][SelectY] = 0;
					SelectX = X;
					SelectY = Y;
					DrawUnit(X, Y);
					ShowMove(SelectX, SelectY);
					Action++;
				}
			}
			break;
		case 3:
			if (choice == LeftArrow && X > 0) Moving(-1, 0);
			if (choice == RightArrow && X < 6) Moving(1, 0);
			if (choice == UpArrow && Y > 0) Moving(0, -1);
			if (choice == DownArrow && Y < 6) Moving(0, 1);
			if (choice == 9) {
				Moving(0, 0);
				ReMoving(SelectX, SelectY);
				ShowMove(SelectX, SelectY);
				Moving(0, 0);
				Mode = 2;
			}
			if (choice == 27) {
				Mode = 1;
				DrawUnit(X, Y);
				if (Map[X][Y] == 0) ReMoving(X, Y);
				ReMoving(SelectX, SelectY);
				ReselectionMode(SelectX, SelectY);
				SelectionMode(0, 0);
			}
			if (choice == ' ' && Map[X][Y] != 9) {
				if (AttackPossible[X][Y]) {
					Attacking(X, Y);
					DrawUnit(X, Y);
					ShowAttack(SelectX, SelectY);
					Moving(0, 0);
					Action++;
				}
			}
		}
		if (Action == 3) {
			DrawUnit(X, Y);
			if (Turn == 0) Turn++;
			else Turn--;
			ReMoving(SelectX, SelectY);
			ReselectionMode(SelectX, SelectY);
			SelectionMode(0, 0);
			Mode = 1;
			Action = 0;
		}
	}
}
void gotoxy(int x, int y) {
	COORD Cur = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}
void setting() {
	HANDLE COUT = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO Info;
	GetConsoleCursorInfo(COUT, &Info);
	Info.bVisible = FALSE;
	SetConsoleCursorInfo(COUT, &Info);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + 16 * 15);
	system("mode con cols=44 lines=22");
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 7; j++) {
			system("cls");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 + 16 * 0); printf("1. 흑마법사\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 + 16 * 2); printf("2. 자연술사\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 + 16 * 8); printf("3. 암석술사\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + 16 * 11); printf("4. 얼음법사\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 + 16 * 12); printf("5. 화염술사\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + 16 * 14); printf("6. 번개술사\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + 16 * 15); printf("7. 빛마법사\n");
			printf("Player%d의 %d번째 유닛을 선택해주세요.\n(7개까지 선택하며 중복 가능)\n", i + 1, j + 1); 
			Unit[i][j] = _getch();
			if (Unit[i][j] > '0' && Unit[i][j] < '8') {
				Unit[i][j] -= 48;
				if (i == 0) {
					Map[j][0] = Unit[i][j];
					Player[0][j][0] = Map[j][0];
					Hp[j][0] = 10;
				}
				else if (i == 1) {
					Map[j][6] = Unit[i][j];
					Player[1][j][6] = Map[j][6];
					Hp[j][6] = 10;
				}
			}
			else j--;
		}
	}
	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 22; j++) {
			if (i % 3 == 0 || j % 3 == 0) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8 + 16 * 0); printf("  ");
			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8 + 16 * 7); printf("  ");
			}
		}
	}
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			DrawUnit(i, j);
		}
	}
}
void DrawUnit(int x, int y) {
	if (Map[x][y] == 9) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + 16 * 13);
		gotoxy(6 * x + 2, 3 * y + 1); printf(" %2d ", Hp[x][y]);
		gotoxy(6 * x + 2, 3 * y + 2); printf("    ");
	}
	else if (Map[x][y] > 0) {
		if (Map[x][y] == Player[0][x][y]) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + 16 * 4);
		else if (Map[x][y] == Player[1][x][y]) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + 16 * 1);
		gotoxy(6 * x + 2, 3 * y + 1); printf("    ");
		gotoxy(6 * x + 2, 3 * y + 2); printf("    ");
		switch (Map[x][y]) {
		case 1 :	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 + 16 * 0); break;
		case 2 :	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 + 16 * 2); break;
		case 3 :	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 + 16 * 8); break;
		case 4 :	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + 16 * 11); break;
		case 5 :	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 + 16 * 12); break;
		case 6 :	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + 16 * 14); break;
		case 7 :	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + 16 * 15); break;
		}
		gotoxy(6 * x + 3, 3 * y + 1); printf("%2d", Hp[x][y]);
		gotoxy(6 * x + 3, 3 * y + 2); printf("  ");
	}
	else if (MovePossible[x][y] == 0 && AttackPossible[x][y] == 0) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + 16 * 7);
		gotoxy(6 * x + 2, 3 * y + 1); printf("    ");
		gotoxy(6 * x + 2, 3 * y + 2); printf("    ");
	}
	if (abs(St[x][y]) > 0) {
		if (St[x][y] > 0) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + 16 * 12);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + 16 * 11);
		gotoxy(6 * x + 3, 3 * y + 2); 
		for (int i = 0; i < abs(St[x][y]); i++) printf(" ");
	}
}
void ShowMove(int x, int y) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + 16 * 5);
	switch (Map[x][y]) {
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 7:
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				if (x + i >= 0 && x + i <= 6 && y + j >= 0 & y + j <= 6 && Map[x + i][y + j] == 0 && !(i == 0 && j == 0)) {
					gotoxy(6 * (x + i) + 2, 3 * (y + j) + 1);
					printf("    ");
					gotoxy(6 * (x + i) + 2, 3 * (y + j) + 2);
					printf("    ");
					MovePossible[x + i][y + j] = 1;
				}
			}
		}
		break;
	case 6:
		for (int i = -2; i <= 2; i++) {
			for (int j = -2; j <= 2; j++) {
				if (x + i >= 0 && x + i <= 6 && y + j >= 0 & y + j <= 6 && Map[x + i][y + j] == 0 && !(i == 0 && j == 0)) {
					gotoxy(6 * (x + i) + 2, 3 * (y + j) + 1);
					printf("    ");
					gotoxy(6 * (x + i) + 2, 3 * (y + j) + 2);
					printf("    ");
					MovePossible[x + i][y + j] = 1;
				}
			}
		}
	}
}
void ShowAttack(int x, int y) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + 16 * 6);
	switch (Map[x][y]) {
	case 1:
	case 2:
	case 4:
	case 5:
	case 6:
	case 7:
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				if (x + i >= 0 && x + i <= 6 && y + j >= 0 & y + j <= 6 && Map[x + i][y + j] == 0 && !(i == 0 && j == 0)) {
					gotoxy(6 * (x + i) + 2, 3 * (y + j) + 1);
					printf("    ");
					gotoxy(6 * (x + i) + 2, 3 * (y + j) + 2);
					printf("    ");
					AttackPossible[x + i][y + j] = 1;
				}
			}
		}
		break;
	case 3:
		for (int i = -3; i <= 3; i++) {
			for (int j = -3; j <= 3; j++) {
				if (x + i >= 0 && x + i <= 6 && y + j >= 0 & y + j <= 6 && Map[x + i][y + j] == 0 && !(i == 0 && j == 0)) {
					gotoxy(6 * (x + i) + 2, 3 * (y + j) + 1);
					printf("    ");
					gotoxy(6 * (x + i) + 2, 3 * (y + j) + 2);
					printf("    ");
					AttackPossible[x + i][y + j] = 1;
				}
			}
	}
	}
}
void ReMoving(int x, int y) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + 16 * 7);
	switch (Map[x][y]) {
	case 1: case 2: case 4:
	case 5: case 7:
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				if (x + i >= 0 && x + i <= 6 && y + j >= 0 & y + j <= 6 && Map[x + i][y + j] == 0) {
					gotoxy(6 * (x + i) + 2, 3 * (y + j) + 1);
					printf("    ");
					gotoxy(6 * (x + i) + 2, 3 * (y + j) + 2);
					printf("    ");
					MovePossible[x + i][y + j] = 0;
					AttackPossible[x + i][y + j] = 0;
				}
			}
		}
	case 6:
		for (int i = -2; i <= 2; i++) {
			for (int j = -2; j <= 2; j++) {
				if (x + i >= 0 && x + i <= 6 && y + j >= 0 & y + j <= 6 && Map[x + i][y + j] == 0) {
					gotoxy(6 * (x + i) + 2, 3 * (y + j) + 1);
					printf("    ");
					gotoxy(6 * (x + i) + 2, 3 * (y + j) + 2);
					printf("    ");
					MovePossible[x + i][y + j] = 0;
					AttackPossible[x + i][y + j] = 0;
				}
			}
		}
		break;
	case 3:
		for (int i = -3; i <= 3; i++) {
			for (int j = -3; j <= 3; j++) {
				if (x + i >= 0 && x + i <= 6 && y + j >= 0 & y + j <= 6 && Map[x + i][y + j] == 0) {
					gotoxy(6 * (x + i) + 2, 3 * (y + j) + 1);
					printf("    ");
					gotoxy(6 * (x + i) + 2, 3 * (y + j) + 2);
					printf("    ");
					MovePossible[x + i][y + j] = 0;
					AttackPossible[x + i][y + j] = 0;
				}
			}
		}
		break;
	case 0 : gotoxy(6 * x + 2, 3 * y + 1);
		printf("    ");
		gotoxy(6 * x + 2, 3 * y + 2);
		printf("    ");
	}
}
void ReselectionMode(int x, int y) {
	gotoxy(6 * x, 3 * y); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + 16 * 0); printf("        ");
	gotoxy(6 * x, 3 * y + 1); printf("  ");
	gotoxy(6 * x + 6, 3 * y + 1); printf("  ");
	gotoxy(6 * x, 3 * y + 2); printf("  ");
	gotoxy(6 * x + 6, 3 * y + 2); printf("  ");
	gotoxy(6 * x, 3 * y + 3); printf("        ");
}
void SelectionMode(int x, int y) {
	ReselectionMode(X, Y);
	X += x;
	Y += y; 
	gotoxy(8 * X, 4 * Y);
	if (Turn == 1) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + 16 * 9);
	else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + 16 * 12);
	gotoxy(6 * X, 3 * Y); printf("        ");
	gotoxy(6 * X, 3 * Y + 1); printf("  ");
	gotoxy(6 * X + 6, 3 * Y + 1); printf("  ");
	gotoxy(6 * X, 3 * Y + 2); printf("  ");
	gotoxy(6 * X + 6, 3 * Y + 2); printf("  ");
	gotoxy(6 * X, 3 * Y + 3); printf("        ");
}
void Moving(int x, int y) {
	gotoxy(6 * X + 2, 3 * Y + 1); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + 16 * 7);
	if (Mode == 2 && MovePossible[X][Y]) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + 16 * 5);
	else if (Mode == 3 && AttackPossible[X][Y]) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + 16 * 6);
	printf("    ");
	gotoxy(6 * X + 2, 3 * Y + 2); printf("    ");
	DrawUnit(X, Y);
	X += x;
	Y += y;
	gotoxy(6 * X + 2, 3 * Y + 1); 
	if (Turn == 1) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + 16 * 1); 
	else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + 16 * 4);
	printf("    ");
	gotoxy(6 * X + 2, 3 * Y + 2); printf("    ");
}
void Attacking(int x, int y) {
	int xx = x - SelectX, yy = y - SelectY;
	switch (Map[SelectX][SelectY]) {
	case 1: if (Hp[SelectX][SelectY] > 1) Hp[SelectX][SelectY] -= 1; DrawUnit(SelectX, SelectY);
	case 2: case 4: case 5:
	case 6: case 7:
	for (int i = 0; i < 10; i++) {
		gotoxy(6 * x + 2, 3 * y + 1); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + 16 * 7);
		printf("    ");
		gotoxy(6 * x + 2, 3 * y + 2); printf("    ");
		DrawUnit(x, y);
		if (x + xx < 0 || x + xx > 6 || y + yy == -1 || y + yy == 7) {
			if (Map[SelectX][SelectY] != 7) {
				DrawUnit(x, y);
				break;
			}
			if (x + xx < 0 || x + xx > 6) xx *= -1;
			if (y + yy < 1 || y + yy > 6) yy *= -1;
		}
		x += xx; y += yy;
		gotoxy(6 * x + 2, 3 * y + 1);
		if (Map[SelectX][SelectY] == 1) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + 16 * 0);
		else if (Map[SelectX][SelectY] == 2) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + 16 * 2);
		else if (Map[SelectX][SelectY] == 4) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + 16 * 11);
		else if (Map[SelectX][SelectY] == 5) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + 16 * 12);
		else if (Map[SelectX][SelectY] == 6) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + 16 * 14);
		else if (Map[SelectX][SelectY] == 7) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + 16 * 15);
		printf("    ");
		gotoxy(6 * x + 2, 3 * y + 2); printf("    ");
		Sleep(100);
		if (Map[x][y] > 0) {
			if(Map[SelectX][SelectY] != 2) Hp[x][y] -= 1;
			else if (Player[Turn][x][y] > 0) { Hp[x][y] += 1; St[x][y] = 0; }
			if (Map[SelectX][SelectY] == 1) { Hp[x][y]--; }
			else if (Map[SelectX][SelectY] == 4 && Map[x][y] != 4 && Map[x][y] != 5 && Map[x][y] != 9) { if (St[x][y] > -2) St[x][y]--; else if (St[x][y] == -2) Hp[x][y]--; }
			else if (Map[SelectX][SelectY] == 5 && Map[x][y] != 5 && Map[x][y] != 5) { St[x][y]++; if (St[x][y] == 3) { St[x][y] = 0; Hp[x][y] --; } }
			DrawUnit(x, y);
			if (Hp[SelectX][SelectY] < 1) {
				Mode = 1;
				ReMoving(SelectX, SelectY);
				ReselectionMode(SelectX, SelectY);
				SelectionMode(SelectX - X, SelectY - Y);
				Map[SelectX][SelectY] = 0;
				Player[Turn][SelectX][SelectY] = 0;
				gotoxy(6 * x + 2, 3 * y + 1); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + 16 * 7);
				printf("    ");
				gotoxy(6 * x + 2, 3 * y + 2); printf("    ");
				break;
			}
			else if (Hp[x][y] <= 0) {
				if(Map[x][y] == Player[!Turn][x][y]) Player[!Turn][x][y] = 0;
				else if (Map[x][y] == Player[Turn][x][y]) Player[Turn][x][y] = 0;
				Map[x][y] = 0;
				gotoxy(6 * x + 2, 3 * y + 1); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 + 16 * 7);
				printf("    ");
				gotoxy(6 * x + 2, 3 * y + 2); printf("    ");
			}
			if (Map[SelectX][SelectY] != 7) break;
		}
	}
	break;
	case 3: Map[x][y] = 9; Hp[x][y] = 1; break;
	}
}