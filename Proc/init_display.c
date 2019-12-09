#include <stdio.h>
#include <Windows.h>
#include "init_display.h"

#define UP 0
#define DOWN 1
#define SUBMIT 2
#define sleeptime 3000

void gotoxy(int, int);
int keyControl();
int menuDraw();
void init_display();
void push_esc();
void logo();
void init();
void setcolor(unsigned short text, unsigned short back);//����

void init() {
	system("mode con cols=130 lines=35 | title ���!!");
}

void push_esc() {
	printf("����Ͻ÷��� ENTER��, ���� ȭ������ ���ư��÷��� ESC�� ��������\n\n");
	int temp = _getch();
	if (temp == 27) { //esc
		system("cls");
		init_display();
	}
}

void init_display() {
	while (1) {
		logo();
		int menuCode = menuDraw();
		
		switch (menuCode) {
		case 0:
			//�����
			system("cls");
			sql_insert_customer();
			Sleep(sleeptime);
			break;
		case 1:
			//����ȸ
			system("cls");
			sql_select_customer();
			Sleep(30000);
			break;
		case 2:
			system("cls");
			sql_insert_pet();	//�ݷ����� ���
			Sleep(sleeptime);
			break;
		case 3:
			system("cls");
			sql_update_customer();	//ȸ������ ����
			Sleep(sleeptime);
			break;
		case 4:
			system("cls");
			sql_insert_product();
			Sleep(sleeptime);
			break;
		case 5:
			exit(0);	 //����
		}
		system("cls");
	}
}

void logo() {
	setcolor(11, 0);
	printf("\n\n\n\n");
	printf("---------------------------------------------------\n\n");
	setcolor(14, 0);
	printf("    ######  #  #        ######  #  #         ######\n");
	printf("    #       #  #        #       #  #         #####\n");
	printf("    #       ####        #       ####         ####\n");
	printf("    #       #  #        #       #  #         ###\n");
	printf("    ######  #  #        ######  #  #         ##\n");
	printf("                                             #\n");
	printf("       #######             #######           \n");
	printf("      ##     ##           ##     ##          ##\n");
	printf("       #######             #######           #\n");
	setcolor(11, 0);
	printf("\n");
	printf("---------------------------------------------------\n");
	setcolor(15, 0);
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
	else if (temp == 13) //space:32  enter:13
		return SUBMIT;
}

int menuDraw() {
	int x = 20;
	int y = 18;
	gotoxy(x - 2, y);
	printf("> ȸ�����");
	gotoxy(x, y + 1);
	printf("ȸ����ȸ");
	gotoxy(x, y + 2);
	printf("�ݷ��������");
	gotoxy(x, y + 3);
	printf("ȸ����������");
	gotoxy(x, y + 4);
	printf("��ǰ ���");
	gotoxy(x, y + 5);
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
				if (y < 23) {
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

void setcolor(unsigned short text, unsigned short back)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}