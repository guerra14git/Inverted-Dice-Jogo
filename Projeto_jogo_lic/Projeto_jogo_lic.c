#include "func.h"
#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <locale.h>

typedef struct JOGADOR {
    char nome[20 + 1]; //max 20char
    char tipo;
    int score;
}Jogador, jog;

typedef struct DADO {
    int num[5];
}Dado;

const char I[5][8] = { // 7 porque cada linha tem até 6 caracteres + o terminador nulo '\0'
    "######",
    "  ##  ",
    "  ##  ",
    "  ##  ",
    "######"
};

const char N[5][8] = {
    "##   ##",
    "###  ##",
    "## # ##",
    "##  ###",
    "##   ##"
};

const char V[5][8] = {
    "#     #",
    "##   ##",
    " ## ## ",
    "  ###  ",
    "   #   "
};

const char E[5][8] = {
    "#######",
    "##     ",
    "###### ",
    "##     ",
    "#######"
};

const char R[5][8] = {
    "###### ",
    "##   ##",
    "###### ",
    "##  ## ",
    "##   ##"
};

const char T[5][8] = {
    "#######",
    "   ##  ",
    "   ##  ",
    "   ##  ",
    "   ##  "
};

const char D[5][8] = {
    "#####  ",
    "##  ## ",
    "##   ##",
    "##  ## ",
    "#####  "
};

const char C[5][8] = {
    " ######",
    "##     ",
    "##     ",
    "##     ",
    " ######"
};

const char SPACE[5][8] = {
    "       ",
    "       ",
    "       ",
    "       ",
    "       "
};

// Lista de ponteiros para as letras (corrigido para o tipo correto)
const char (*LETTERS[])[8] = { I, N, V, E, R, T, E, D, SPACE, D, I, C, E };

static void changeAspectDefault() {
    setForeColor(MY_COLOR_PURPLE);
}

static void printLine(int line) {
    printf("\n");
    for (int i = 0; i < 13; i++) {
        printf("%s  ", LETTERS[i][line]);  // O "  " serve para separar os caracteres
    }
    //printf("\n"); // Nova linha após imprimir uma linha de todos os caracteres
}

static void printInvertedDice() {
    for (int i = 0; i < 5; i++) {  // Para cada linha da arte de "INVERTED DICE"
        printLine(i);
    }
}

static int menuInicial() { //menu inicial
    int screen_width, screen_height, opc=0;
    GetDesktopResolution(FALSE, &screen_width, &screen_height);
    int x = (screen_width - 35) / 2, y = (screen_height - 10) / 2;
    //se a screen_resolution nao estiver bem definir valores como x=constante
    int lastX = screen_width - 22; // Última posição horizontal
    int lastY = screen_height - 1;
    do {
        int x = (screen_width - 35) / 2, y = (screen_height - 10) / 2;
        gotoxy((screen_width - 70) / 2, 1); printInvertedDice();
        gotoxy(lastX, lastY);printf("AUTOR - RICARDO GUERRA");
        gotoxy(0, lastY);printf("INVERTED DICE - GAME");

        gotoxy(x, y);
        printf("X- - - - - - -M-E-N-U- - - - - - -X"); y++;y++;
        y++; gotoxy(x + 10, y); printf("1 -- Novo Jogo");
        y++; y++;gotoxy(x + 10, y); printf("2 -- Carregar Jogo");
        y++; y++;gotoxy(x + 10, y); printf("3 -- Regras");
        y++; y++;gotoxy(x + 10, y); printf("4 -- Sair"); y++;
        y++; y++; gotoxy(x, y); printf("X- - - - - - -~- -~- -~- - - - - -X");
        y++; y++; gotoxy(x + 9, y); printf("Escolha uma opcao: ");y++;
        gotoxy(x+15,y);printf("=> ");(void)scanf("%d", &opc);
        if (opc != 1 && opc != 2 && opc != 3 && opc != 4) {
            setForeColor(MY_COLOR_LIGTH_RED);
            gotoxy((screen_width - 16)/2, 0);printf("Opcao invalida!");
            Sleep(1500);
            changeAspectDefault();
        }
        system("cls");
    } while (opc != 1 && opc != 2 && opc != 3 && opc != 4);
    return opc;
}

static int regrasJogo()
{
    int i = 0, num = (rand() % 5) + 1, temp_1 = 0, num_1[5] = { 1,1,2,3,1 }, num_2[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    char op;
    system("cls");
    int screen_width, screen_height;
    GetDesktopResolution(FALSE, &screen_width, &screen_height);
    int x[] = {(screen_width - 34) / 2,(screen_width - 83) / 2,(screen_width - 13) / 2, (screen_width - 45) / 2, (screen_width - 57) / 2, (screen_width - 100) / 2 };
    int y = (screen_height - screen_height / 2) - 13;

    gotoxy(x[0], y);printf("X===============================X");y++;
    gotoxy(x[0], y);printf("Bem vindos ao jogo INVERTED DICE!");y++;
    gotoxy(x[0], y);printf("X===============================X");y++;y++; Sleep(1000);
    gotoxy(x[1], y);printf("X================================================================================X");y++;
    gotoxy(x[1], y);printf("O resultado de um lancamento e a soma das faces dos dados que nao estao presentes.");y += 2;Sleep(1000);
    gotoxy(x[2], y);printf("Por exemplo:");y++;y++;Sleep(1000);
    for (i = 0;i < 5;i++) {
        setColors(MY_COLOR_DARK_BLUE + i, MY_COLOR_BLACK);
        showRectAt(x[3] + 2*i * 5, y, 4, 2);Sleep(100);
        gotoxy(x[3] + 2 + 2*i * 5, y+1); // valores+(x) para centrar no quadrado
        printf("%d", num_1[i]);
    } changeAspectDefault();y += 4;Sleep(1000);
    gotoxy(x[4], y);printf("O resultado foi 15 pois e a soma dos numeros que faltam.");y += 2;Sleep(1000);
    for (i = 0;i < 20;i++) {
        setColors(MY_COLOR_SOFT_BLUE, MY_COLOR_BLACK);
        showRectAt(x[5] + i * 5, y, 4, 2);
        gotoxy(x[5] + 2 + i * 5, y + 1); // valores+(x) para centrar no quadrado
        setColors(MY_COLOR_SOFT_BLUE, MY_COLOR_BLACK);printf("%d", num_2[i]);Sleep(50);
        if (i < 5) {
            setColors(MY_COLOR_LIGTH_BLUE, MY_COLOR_BLACK);
            showRectAt(x[5] + i * 5, y + 3, 4, 2);
        }
        else if (i >= 5 && i <= 15) {
            setColors(MY_COLOR_SOFT_BLUE, MY_COLOR_BLACK);
            showRectAt(x[5] + i * 5, y + 3, 4, 2);
        }
        if (i >= 15) {
            setColors(MY_COLOR_LIGTH_BLUE, MY_COLOR_BLACK);
            showRectAt(x[5] + i * 5, y + 3, 4, 2);
        }
        if (i == 14) {
            setColors(MY_COLOR_LIGTH_GREEN, MY_COLOR_BLACK);
            showRectFilledAt(x[5] + i * 5, y + 3, 4, 2);
            showRectAt(x[5] + i * 5, y + 3, 4, 2);
        }
    }y += 6;setColors(MY_COLOR_SOFT_BLUE, MY_COLOR_BLACK);
    gotoxy(x[5], y);printf(" x--------50-pts-------x ");printf(" x---------------------50-pts-------------------x ");
    printf(" x--------50-pts-------x "); y++;y++; Sleep(1000);setColors(MY_COLOR_PURPLE, MY_COLOR_BLACK);
    gotoxy(x[4], y);printf("A casa 15 fica marcada e não podemos volar a marca-la.");y++;y++;Sleep(1000);
    gotoxy(x[4], y);printf("Sair do tutorial e voltar ao menu?(s/n): ");(void)scanf("%c", &op);
    //if (op == 's') { menuInicial();}
    if (op == 's') { system("cls"); return 1; }
    changeAspectDefault();
    return 0;
}

static void sairJogo() {
    int screen_width, screen_height;
    GetDesktopResolution(FALSE, &screen_width, &screen_height);
    int x = (screen_width - 34) / 2, y = (screen_height - screen_height / 2) - 3;
    system("cls");
    gotoxy(x, y);printf("Obrigado por jogar INVERTED DICE!"); y++;y++; Sleep(500);
    gotoxy(x, y);printf("A sair em: ");Sleep(800);setColors(MY_COLOR_SOFT_BLUE, MY_COLOR_BLACK);printf("..3");Sleep(800);printf("..2");Sleep(800);printf("..1");Sleep(800);y++;y++;gotoxy(x, y);
    system("exit"); //ou exit(0)
}

static void rodarDados(int x, int y, int num_repeticoes) {
    int i; char opc = 0;
    Dado dado;
    for (i = 0;i < 5;i++) {
        dado.num[i] = (rand() % 5) + 1;
    }
    for (i = 0; i < num_repeticoes; i++) {
        setColors(MY_COLOR_CYAN + i, MY_COLOR_BLACK);
        showRectAt(x + 2 * i * 5, y, 4, 2); Sleep(100);
        gotoxy(x + 2 + 2 * i * 5, y + 1); // valores+(x) para centrar no quadrado
        printf("%d", dado.num[i]);
    }
    
    /*for (i = 0;i < 2;i++) {
        printf("Deseja rodar os dados?(s/n): ");(void)scanf("%c", &opc);
        if (opc == 's') {
            for (i = 0;i < 5;i++) {
                dado.num[i] = (rand() % 5) + 1;
            }
            for (i = 0; i < num_repeticoes; i++) {
                setColors(MY_COLOR_CYAN + i, MY_COLOR_BLACK);
                showRectAt(x + 2 * i * 5, y, 4, 2); Sleep(100);
                gotoxy(x + 2 + 2 * i * 5, y + 1); // valores+(x) para centrar no quadrado
                printf("%d", dado.num[i]);
            }
        }
        else if (opc == 'n') {
            changeAspectDefault();
            return 0;
        }
        else {
            printf("");
        }
    } */
}

/*static void somaNumeros() {

}*/

static void iniciarJogo() {
    int screen_width, screen_height;
    Jogador jogador;
    int i = 0; char opc;
    GetDesktopResolution(FALSE, &screen_width, &screen_height);
    int x[] = {(screen_width - 23) / 2, (screen_width - 70) / 2, (screen_width - 43) / 2 };
    int y = (screen_height) / 7;
    system("cls");
    gotoxy(0, 0);printf("INVERTED DICE - GAME");
    gotoxy(x[1], y);printf("Introduza o nome do Jogador 1: ");(void)scanf("%s", &jogador.nome);y++;
    gotoxy(x[1], y);printf("Bem vindo, %s", jogador.nome); Sleep(2000);
    system("cls");
    gotoxy(0, 0);printf("INVERTED DICE - GAME");
    gotoxy(x[1], 5);printf("O jogo vai comecar em ");Sleep(1000);printf("..3");Sleep(1000);printf("..2");Sleep(1000);printf("..1");system("cls");y++;y++;
    showRectAt(x[1], 3, 70, 8);
    rodarDados(x[2], y - 1, 5);
    printf("Deseja rodar os dados?(s/n): ");(void)scanf("%c", &opc);
    if (opc == 's') { rodarDados(x[2], y - 1, 5); }
    else if (opc == 's') { rodarDados(x[2], y - 1, 5); } y++; y++;
    printf("Deseja rodar os dados novamente?(s/n): ");(void)scanf("%c", &opc);
    if (opc == 's') { rodarDados(x[2], y - 1, 5); }
    else if (opc == 's') { rodarDados(x[2], y - 1, 5); }
    system("pause");
}

int main()
{ 
    int opc = 0, opt;
    srand(time(NULL));
    changeAspectDefault();
    while (opc != 3) {
        opc = menuInicial();
        switch (opc)
        {
        case 1:
            Sleep(100);
            iniciarJogo();
            break;
        case 2:
            //smthing
            break;
        case 3:
            Sleep(100);
            opt = regrasJogo();
            if (opt == 1) {Sleep(500);menuInicial(); }
            break;
        case 4:
            Sleep(100);
            sairJogo();
            break;
        default:
            break;
        }
    }
    system("pause");
    return 0;
}