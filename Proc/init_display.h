#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <Windows.h>
#include "init_display.h"

/* for oracle */
#include <sqlda.h>
#include <sqlca.h>
#include <sqlcpr.h>

#define UP 0
#define DOWN 1

void gotoxy(int, int);
int keyControl();
int menuDraw();
void init_display();
void push_esc();