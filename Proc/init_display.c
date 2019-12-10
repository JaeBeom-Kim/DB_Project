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
void push_anykey();
void logo();
void init();
void setcolor(unsigned short text, unsigned short back);//색깔

void init() {
	system("mode con cols=58 lines=30 | title 댕댕!!");

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);

	COORD bufferSize = { 116,150 };
	SetConsoleScreenBufferSize(consoleHandle, bufferSize);
}

void init2() {
	system("mode con cols=130 lines=30 | title 댕댕!!");

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);

	COORD bufferSize = { 130,150 };
	SetConsoleScreenBufferSize(consoleHandle, bufferSize);
}

void push_esc() {
	printf("계속하시려면 아무 키를, 메인 화면으로 돌아가시려면 ESC 키를 입력하세요\n\n");
	int temp = _getch();
	if (temp == 27) { //esc
		system("cls");
		init_display();
	}
}

void push_anykey() {
	printf("\n\n메인 화면으로 돌아가시려면 아무키나 입력하세요\n\n");
	int temp = _getch();
	if (temp < 100000) {
		system("cls");
		init_display();
	}
}

void init_display() {
	while (1) {
		init();
		logo();
		int menuCode = menuDraw();
		
		switch (menuCode) {
		case 0:
			//고객등록
			system("cls");
			sql_insert_customer();
			Sleep(sleeptime);
			break;
		case 1:
			//고객조회
			system("cls");
			sql_select_customer();
			Sleep(30000);
			break;
		case 2:
			system("cls");
			sql_insert_pet();	//반려동물 등록
			Sleep(sleeptime);
			break;
		case 3:
			system("cls");
			sql_update_customer();	//회원정보 수정
			Sleep(sleeptime);
			break;
		case 4:						//상품 구매
			system("cls");
			purchase();
			break;
		case 5:					//구매내역 조회
			system("cls");
			sql_select_history();
			break;
		case 6:						//상품 목록
			system("cls");
			sql_select_product();
			break;
		case 7:						//상품 등록
			system("cls");
			sql_insert_product();
			Sleep(sleeptime);
			break;
		case 8:
			exit(0);	 //종료
		}
		system("cls");
	}
}

void logo() {
	setcolor(9, 15);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                    ■\n");
	setcolor(11, 15);
	printf("■----------------------------------------------------■\n");
	printf("■                                                    ■\n");
	setcolor(14, 15);
	printf("■    ######  #  #       ######  #  #       ######    ■\n");
	printf("■    #       #  #       #       #  #       #####     ■\n");
	printf("■    #       ####       #       ####       ####      ■\n");
	printf("■    #       #  #       #       #  #       ###       ■\n");
	printf("■    ######  #  #       ######  #  #       ##        ■\n");
	printf("■                                          #         ■\n");
	printf("■       #######            #######                   ■\n");
	printf("■      ##     ##          ##     ##        ##        ■\n");
	printf("■       #######            #######         #         ■\n");
	setcolor(11, 15);
	printf("■                                                    ■\n");
	printf("■----------------------------------------------------■\n");
	setcolor(9, 15);
	printf("■                                                    ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
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
	int x = 22;
	int y = 18;
	gotoxy(x - 2, y);
	printf("> 회원등록");
	gotoxy(x, y + 1);
	printf("회원조회");
	gotoxy(x, y + 2);
	printf("반려동물등록");
	gotoxy(x, y + 3);
	printf("회원정보수정");
	gotoxy(x, y + 4);
	printf("상품구매");
	gotoxy(x, y + 5);
	printf("구매내역 조회");
	gotoxy(x, y + 6);
	printf("상품목록");
	gotoxy(x, y + 7);
	printf("상품등록");
	gotoxy(x, y + 8);
	printf("  종료  ");
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
				if (y < 26) {
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