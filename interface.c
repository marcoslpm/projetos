#include "interface.h"

void gotoxy(int x, int y)       //DEFINE AS COORDENADAS EIXO X E Y NO TERMINAL
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void textcolor (int iColor)     //FUNÇÃO QUE COLORE TEXTO
{
    HANDLE hl= GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    BOOL b = GetConsoleScreenBufferInfo(hl, &bufferInfo);
    bufferInfo.wAttributes &= 0x00F0;
    SetConsoleTextAttribute (hl, bufferInfo.wAttributes |= iColor);
}

void textbackground (int iColor)    //FUNÇÃO QUE COLORE O FUNDO
{
    HANDLE hl= GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    SetConsoleTextAttribute (hl, bufferInfo.wAttributes |= (iColor << 4));
    BOOL b = GetConsoleScreenBufferInfo(hl, &bufferInfo);
    bufferInfo.wAttributes &= 0x000F;
}

void Borda(int x, int y, int largura, int altura, int tipo, int sombra)   //CRIA UMA BORDA EM UM DETERMINADO LOCAL NO TERMINAL
{
    char C[][6] = {"\xda\xbf\xc0\xd9\xc4\xb3",
                 "\xc9\xbb\xc8\xbc\xcd\xba"};

    textcolor(BLUE);
    int i,j;
    gotoxy(x, y);
    printf("%c", C[tipo][0]);
    for(i = 0; i < largura; i++) printf("%c", C[tipo][4]);
    printf("%c", C[tipo][1]);
    for(j=0; j< altura; j++)
    {
        gotoxy(x, y+j+1);
        printf("%c", C[tipo][5]);
        for(i = 0; i < largura; i++) printf(" ");
        printf("%c", C[tipo][5]);
        if(sombra) printf("\xb2");
    }
    gotoxy(x, y+altura);
    printf("%c", C[tipo][2]);
    for(i = 0; i < largura; i++) printf("%c", C[tipo][4]);
    printf("%c", C[tipo][3]);
    if(sombra)
    {
        gotoxy(x+1, y+altura+1);
        for(i = 0; i < largura+2; i++) printf("\xb2");
    }
}


int menu(char opcoes[][51], int x[], int y[], int opcao, int n){    //CRIA UM MENU DE SELEÇÃO
    int i, tecla; textbackground(BLUE); textcolor(WHITE);
    for(i = 0; i < n; i++){
        gotoxy(x[i], y[i]); printf("%s", opcoes[i]);
    }
    do{
        textbackground(WHITE);textcolor(BLUE);
        gotoxy(x[opcao], y[opcao]); printf("%s", opcoes[opcao]);
        tecla = getTecla();
        if(tecla == 13)return opcao;
        textbackground(BLUE);textcolor(WHITE);
        gotoxy(x[opcao], y[opcao]); printf("%s", opcoes[opcao]);
        if(tecla == TEC_BAIXO || tecla == TEC_DIR)opcao++;
        if(tecla == TEC_CIMA || tecla == TEC_ESQ)opcao--;
        if(opcao < 0)opcao = n - 1;
        if(opcao >= n)opcao = 0;
    }while(tecla != 27);
    return -1;
}


void ApagarCaixa(int x, int y, int Largura, int Altura, int tipo, int sombra)   //FUNÇÃO PARA APAGAR UMA BORDA DE UM DETERMINADO LOCAL
{
    int i, j;
    gotoxy(x, y);
    for(i = 0; i <= Largura + 1; i++) printf(" ");
    for(j = 0; j < Altura; j++){
        gotoxy(x, y + j + 1); printf(" ");
        for(i = 0; i < Largura; i++) printf(" ");
        gotoxy(x + Largura + 1, y + j + 1); printf(" ");
    }
    gotoxy(x, y + j + 1); printf(" ");
    for(i = 0; i <= Largura + 1; i++) printf(" ");
}

void tipocursor (int cursor)    //DEFINE SE O CURSOR FICA VISÍVEL NO TERMINAL OU NÃO
{
    HANDLE myconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CURSOR;
    BOOL result;
    CURSOR.dwSize = 1;
    if(cursor == 0)
        CURSOR.bVisible = FALSE;
    else
        CURSOR.bVisible = TRUE;
    result = SetConsoleCursorInfo(myconsole, &CURSOR);
}

int getTecla()
{
    int ch;
    ch = getch();
    if(ch == 224){
        ch = getch() + 1000;
    }
    return ch;
}

