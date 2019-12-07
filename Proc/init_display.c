#include <stdio.h>
#include <Windows.h>
#include "init_display.h"

#define UP 0
#define DOWN 1
#define SUBMIT 2

void gotoxy(int, int);
int keyControl();
int menuDraw();
void init_display();
void push_esc();
void logo();
void init();

void init() {
	system("mode con cols=130 lines=35 | title ���!!");
}

void push_esc() {
	printf("����Ͻ÷��� ENTER��, ���� ȭ������ ���ư��÷��� ESC�� ��������\n");
	int temp = _getch();
	if (temp == 27) {
		system("cls");
		init_display();
	}
}

void init_display() {
	while (1) {
		
		int menuCode = menuDraw();
		
		switch (menuCode) {
		case 0:
			//�����
			system("cls");
			sql_insert_customer();
			break;
		case 1:
			//����ȸ
			system("cls");
			sql_select();
			break;
		case 2:
			system("cls");
			sql_update_customer();
			break;
		case 3:
			exit(0);	 //����
		}
		system("cls");
	}
}

void logo() {
	printf("\n\n\n\n");
	printf("---------------------------------------------------\n\n");
	printf("    ######  #  #        ######  #  #         ######\n");
	printf("    #       #  #        #       #  #         #####\n");
	printf("    #       ####        #       ####         ####\n");
	printf("    #       #  #        #       #  #         ###\n");
	printf("    ######  #  #        ######  #  #         ##\n");
	printf("                                             #\n");
	printf("       #######             #######           \n");
	printf("      ##     ##           ##     ##          ##\n");
	printf("       #######             #######           #\n");
	printf("\n");
	printf("---------------------------------------------------\n");
}

void gotoxy(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}

int keyControl() {
	int temp = _getch();

	if (temp == 72)
		return UP;
	else if (temp == 80)
		return DOWN;
	else if (temp == 32)
		return SUBMIT;
}

int menuDraw() {
	int x = 20;
	int y = 18;
	gotoxy(x + 19, y);
	logo();
	gotoxy(x - 2, y);
	printf("> ȸ�����");
	gotoxy(x, y + 1);
	printf("ȸ����ȸ");
	gotoxy(x, y + 2);
	printf("ȸ����������");
	gotoxy(x, y + 3);
	printf("  ����  ");
	while (1) {
		int n = keyControl();
		switch (n) {
			case UP: {
				if (y > 18) {
					gotoxy(x - 2, y);
					printf(" ");
					gotoxy(x - 2, --y);
					printf(">");
				}
				break;
			}

			case DOWN: {
				if (y < 21) {
					gotoxy(x - 2, y);
					printf(" ");
					gotoxy(x - 2, ++y);
					printf(">");
				}
				break;
			}

			case SUBMIT: {
				return y - 18;
			}
		}
	}
}