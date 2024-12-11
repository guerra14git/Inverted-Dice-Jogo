// Arquivo com funçoes

#ifndef _LABH_		//protectes from multiple including...
#define _LABH_		//... needs an #endif at bottom
#define _CRT_SECURE_NO_WARNINGS 1

//#include "constantes.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include <locale.h>

#define false	0
#define true	1


#define MY_COLOR_BLACK			0
#define MY_COLOR_DARK_BLUE		1
#define MY_COLOR_SOFT_GREEN		2
#define MY_COLOR_SOFT_BLUE		3
#define MY_COLOR_DARK_RED		4
#define MY_COLOR_PURPLE			5
#define MY_COLOR_DARK_YELLOW	6
#define MY_COLOR_GRAY			7
#define MY_COLOR_DARK_GRAY		8
#define MY_COLOR_CYAN			9
#define MY_COLOR_LIGTH_GREEN	10
#define MY_COLOR_LIGTH_BLUE		11
#define MY_COLOR_LIGTH_RED		12
#define MY_COLOR_PINK			13
#define MY_COLOR_LIGTH_YELLOW	14
#define MY_COLOR_WHITE			15

void trocaChars(char* a, char* b) {
	//esta função podia "voar" para o lab.h
	char tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}
void trocaInts(int* a, int* b) {
	//esta função podia "voar" para o lab.h
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

//changes both foreground and background colors
void setColors(int foreGround, int backGround) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backGround*16 + foreGround);
}
//by vec: {foreGround, backGround}
void setColors_(const int colors[2]) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colors[1] * 16 + colors[0]);
}
void setSwappedColors_(const int colors[2]) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colors[0] * 16 + colors[1]);
}
//changes foreground color while keeping background color
void setForeColor(int foreGround) {
	int backGround = MY_COLOR_BLACK;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
	backGround = csbiInfo.wAttributes / 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backGround * 16 + foreGround);
}
//changes background color while keeping foreground color
void setBackColor(int backGround) {
	int foreGround = MY_COLOR_BLACK;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
	foreGround = csbiInfo.wAttributes % 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backGround*16 + foreGround);
}
//Colors reset: foreground white, background black
void resetColor() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), MY_COLOR_BLACK * 16 + MY_COLOR_WHITE);
}
//----------------------------------------------------------

//recupera as cores em uso na consola
BOOL getColors(int* fore, int* back) {
	CONSOLE_SCREEN_BUFFER_INFO info;
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info))
		return false;
	short ret;
	ret = info.wAttributes;
	//background * 16 + main color
	(*back) = ret / 16;
	(*fore) = ret % 16;
	return true;
}
//by vec: {foreGround, backGround}
BOOL getColors_(int colors[]) {
	CONSOLE_SCREEN_BUFFER_INFO info;
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info))
		return false;
	short ret;
	ret = info.wAttributes;
	//background * 16 + main color
	(colors[1]) = ret / 16;
	(colors[0]) = ret % 16;
	return true;
}

//----------------------------------------------------------
// Set full screen - if true, or windowed - if false
void setFullScreen(BOOL on) {
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
	if (!on) {
		SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_WINDOWED_MODE, 0);
	}
}
// Get the horizontal and vertical screen sizes in:
// pixel - if(BOOL pixel ==  true), 
// lines and columns - if (BOOL pixel == false)
void GetDesktopResolution(BOOL pixel, int* horizontal, int* vertical)
{
	if (pixel) {
		RECT desktop;
		// Get a handle to the desktop window
		const HWND hDesktop = GetDesktopWindow();
		// Get the size of screen to the variable desktop
		GetWindowRect(hDesktop, &desktop);
		// The top left corner will have coordinates (0,0)
		// and the bottom right corner will have coordinates
		// (horizontal, vertical)
		(*horizontal) = desktop.right;
		(*vertical) = desktop.bottom;
	}else {

		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		(*horizontal) = (int)(csbi.srWindow.Right - csbi.srWindow.Left + 1);
		(*vertical) = (int)(csbi.srWindow.Bottom - csbi.srWindow.Top + 1);
	}
}
//----------------------------------------------------------

//allows to place the cursor at any given position
void gotoxy(int x, int y) {
	COORD c = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
//allows to draw a rectangle (filled, no lines) at any given position
void showRectFilledAt(int x, int y, int width, int height) {

	setlocale(LC_ALL, "C");
	int i, j;
	for (j = y; j < y + height; j++) {
		for (i = x; i < x + width; i++) {
			gotoxy(i, j);
			printf("%c", 219);
		}
	}
	setlocale(LC_ALL, "");
}
//allows to draw a rectangle (double lines) at any given position
void showRectAt(int x, int y, int width, int height){

	setlocale(LC_ALL, "C");
	int i;
	gotoxy(x, y);
	printf("%c", 201);
	for (i = 1; i < width; i++) {
		printf("%c", 205);
	}

	printf("%c", 187);
	gotoxy(x, height + y);
	printf("%c", 200);

	for (i = 1; i < width; i++) {
		printf("%c", 205);
	}

	printf("%c", 188);

	for (i = y + 1; i < height + y; i++){
		gotoxy(x, i);
		printf("%c", 186);

		gotoxy(x + width, i);
		printf("%c", 186);

	} 
	 setlocale(LC_ALL, "");
}
//allows to draw a rectangle (double lines) at any given position, rotated by 90º 
void show90RectAt(int x, int y, int width, int height){
	showRectAt(x,y,height*2,width/2);
}
//show a char at a designated position
void showCharAt(int x, int y, char c) {
	setlocale(LC_ALL, "C");
	gotoxy(x, y);
	printf("%c", c);
	setlocale(LC_ALL, "");
}
//write a 'string' verticaly at a designated position
void showVerticalWordAt(int x, int y, char c[], int charNumber) {
	setlocale(LC_ALL, "C");
	if (charNumber < 0 || charNumber >20) { return; }
	int i = 0;
	for(i = 0; i < charNumber; i++){
		gotoxy(x, y+i);
		printf("%c", c[i]);		
	}

	setlocale(LC_ALL, "");
}
//write an horizontal 'string' at a designated position
void printfAt(int x, int y, char c[]) {
	setlocale(LC_ALL, "C");
	gotoxy(x, y);
	printf("%s", c);		
	setlocale(LC_ALL, "");
}

//allows to draw a rectangle (single lines) with center at any given position
void showRectCenteredAt(int x, int y, int width, int height) {

	setlocale(LC_ALL, "C");
	int i;
	x = x - width / 2;
	y = y - height / 2;
	gotoxy(x, y);
	printf("%c", 218);
	for (i = 1; i < width; i++) {
		printf("%c", 196);
	}

	printf("%c", 191);
	gotoxy(x, height + y);
	printf("%c", 192);

	for (i = 1; i < width; i++) {
		printf("%c", 196);
	}

	printf("%c", 217);

	for (i = y + 1; i < height + y; i++) {
		gotoxy(x, i);
		printf("%c", 179);

		gotoxy(x + width, i);
		printf("%c", 179);

	}
	setlocale(LC_ALL, "");
}

void initRandom(){
	time_t t;
/* Intializes random number generator */
   srand((unsigned) time(&t));
}
//retorna o lançamento de um dado com n faces
int dado(int n_faces){
	if(n_faces != 0)
		return rand() % n_faces + 1;
	return -1;
}
//retorna um ínteiro aleatório entre dois limites fornecidos
int randomNumber(int min, int max){
	if(min == max)
		return min;
	int aux = min;
	if(min > max){
		min = max;
		max = aux;
	}

	return rand() % (max - min) + min;
}

// print the ascii table in two locale Modes 
// usage sample: printAscii(174, 223, 4);
void printAscii(int N0, int N, int col) {

	int i = 0, j = 0;
	int aux = 0, linhas = 0;

	if (N0 >= N || N <= 32 || col < 1)
		return;				// nothing to do here!
	if (N > 256) N = 256;	// upper limite of the set to print
	if (N0 < 32) N0 = 32;	// lower limite of the set to print...
							// ...first ascii numbers are indeed actions
	if (col > (N - N0)) col = N - N0; 	// number of columns to split the print

	printf("locale: ");
	setForeColor(MY_COLOR_DARK_RED);
	printf("\t setlocale(LC_ALL, \"C\");");
	setForeColor(MY_COLOR_SOFT_GREEN);
	printf("\t  setlocale(LC_ALL, \"Portuguese\");");
	resetColor();

	printf("\n\n");
	N++;
	linhas = (N - N0) / col;
	if ((N - N0) % col) linhas++;
	for (i = 0; i < linhas; i++) {
		for (j = 0; j < col; j++) {
			aux = i + j * linhas + N0;
			if (aux > N - 1) break;
			setlocale(LC_ALL, "C");
			printf("\t%3d - ", aux);
			setForeColor(MY_COLOR_DARK_RED);
			printf("%c", aux);
			resetColor();
			setlocale(LC_ALL, "");
			printf(" - ");
			setForeColor(MY_COLOR_SOFT_GREEN);
			printf("%c ", aux);
			resetColor();
		}
		printf("\n");
	}
	resetColor();
}


//lista dos códigos dos dados UTF-8 para os numeros de 1 a 6
wchar_t diceCodes[29] = { L'\u24FF',//L'\u24EA',//0
						  L'\u2460',L'\u2461',L'\u2462',L'\u2463',L'\u2464',
						  L'\u2465',L'\u2466',L'\u2467',L'\u2468',L'\u2469',
						  L'\u246A',L'\u246B',L'\u246C',L'\u246D',L'\u246E',
						  L'\u246F',L'\u2470',L'\u2471',L'\u2472',L'\u2473',
						  L'\u24F5',L'\u24B6'
						};
//Imprime na posição (x,y) da consola um codigo correspondente ao número passado para 
// um dado de 6 faces numerado de 1 a 6 
// NOTA: o tipo de letra na consola tem de suportar carateres UTF-8
void printDiceAt(int x, int y, int dice) {

	if (dice < 0 || dice > 22) return;
	// Configura o ambiente para suportar UTF-8
	// Define a localidade para UTF-8 (verifique se está disponível no sistema)
	// Pode ser necessário alterar o tipo de letra usado na consola
	//system("chcp 65001 > NUL");	
	SetConsoleOutputCP(CP_UTF8);	setlocale(LC_ALL, "en_US.UTF-8");

	gotoxy(x, y);
//	setColor(MY_COLOR_DARK_BLUE, MY_COLOR_WHITE); //esquema de cores fixo
	wprintf(L"%lc", diceCodes[dice]);
//	resetColor();

	//system("chcp 437 > NUL");	
	SetConsoleOutputCP(437); setlocale(LC_ALL, "");
	//// Define some Braille Unicode characters
	//wchar_t braille_1 = L'\u2801'; // ⠁ (1 dot)
	//wchar_t braille_2 = L'\u2803'; // ⠃ (2 dots diagonal)
	//wchar_t braille_3 = L'\u2807'; // ⠇ (3 dots)
	//wchar_t braille_4 = L'\u2827'; // ⠧ (4 dots)
	//wchar_t braille_6 = L'\u283F'; // ⠿ (6 dots)
	//
	//// Imprimir caracteres Braille
	//wprintf(L"Braille 1 dot: %lc\n", braille_1);
	//wprintf(L"Braille 2 dots: %lc\n", braille_2);
	//wprintf(L"Braille 6 dots: %lc\n", braille_6);
	//
	//wchar_t dice_1 = L'\u2680'; // ⚀ (1 dots)
	//wchar_t dice_2 = L'\u2681'; // ⚁ (2 dots)
	//wchar_t dice_3 = L'\u2682'; // ⚂ (3 dots)
	//wchar_t dice_4 = L'\u2683'; // ⚃ (4 dots)
	//wchar_t dice_5 = L'\u2684'; // ⚄ (5 dots)
	//wchar_t dice_6 = L'\u2685'; // ⚅ (6 dots)
	////wchar_t dice_0 = L'\u1F3B2'; // 🎲 (full dots)
	////
	//wprintf(L"\nDice 1 dots: %lc\n", dice_1);
	//wprintf(L"\nDice 2 dots: %lc\n", dice_2);
	//wprintf(L"\nDice 3 dots: %lc\n", dice_3);
	//wprintf(L"\nDice 4 dots: %lc\n", dice_4);
	//wprintf(L"\nDice 5 dots: %lc\n", dice_5);
	//wprintf(L"\nDice 6 dots: %lc\n", dice_6);
	////wprintf(L"\nDice 0 dots: %lc\n", dice_0);
	//
	//printf("\n\n");
}

int getConsoleWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;

    // Get the handle to the console's standard output
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    // Get console buffer information
    if (GetConsoleScreenBufferInfo(hStdout, &csbi)) {
        columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    } else {
        columns = -1; // Error case
    }

    return columns;
}

int getConsoleHeight() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int rows;

    // Get the handle to the console's standard output
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    // Get console buffer information
    if (GetConsoleScreenBufferInfo(hStdout, &csbi)) {
        rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    } else {
        rows = -1; // Error case
    }

    return rows;
}

#endif

/*
// Definição de cores ANSI
#define ANSI_RESET   "\x1B[0m"
#define ANSI_RED     "\x1B[31m"
#define ANSI_BLACK   "\x1B[30m"
#define ANSI_WHITE   "\x1B[37m"
#define ANSI_CLUBS   "\xE2\x99\xA3" // Símbolo do naipe de paus (♣)
#define ANSI_DIAMONDS "\xE2\x99\xA6" // Símbolo do naipe de ouros (♦)
#define ANSI_HEARTS  "\xE2\x99\xA5" // Símbolo do naipe de copas (♥)
#define ANSI_SPADES  "\xE2\x99\xA0" // Símbolo do naipe de espadas (♠)
*/