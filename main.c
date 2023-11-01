#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "aluno.h"

void TelaPrincipal()    //TELA INICIAL DO SISTEMA DE CADASTRAMENTO
{
    Borda(0, 0, 86, 32, 1, 0);
    textcolor(LIGHT_CYAN);
    gotoxy(4,1);
    printf("__    __      __    __      ______        ________        ______        ________ ");
    textcolor(LIGHT_CYAN);
    gotoxy(3,2);
    printf("/  |  /  |    /  \\  /  |    /      |      /        |      /      |      /        |");
    textcolor(LIGHT_CYAN);
    gotoxy(3,3);
    printf("$$ |  $$ |    $$  \\ $$ |    $$$$$$/       $$$$$$$$/       $$$$$$/       $$$$$$$$/ ");
    textcolor(LIGHT_BLUE);
    gotoxy(3,4);
    printf("$$ |  $$ |    $$$  \\$$ |      $$ |        $$ |__            $$ |           $$ |   ");
    textcolor(LIGHT_BLUE);
    gotoxy(3,5);
    printf("$$ |  $$ |    $$$$  $$ |      $$ |        $$    |           $$ |           $$ |   ");
    textcolor(LIGHT_BLUE);
    gotoxy(3, 6);
    printf("$$ |  $$ |    $$ |$$$$ |     _$$ |_       $$$$$/           _$$ |_          $$ |   ");
    textcolor(BLUE);
    gotoxy(3, 7);
    printf("$$ \\__$$/     $$ | $$$ |    / $$   |      $$ |            / $$   |         $$ |   ");
    textcolor(BLUE);
    gotoxy(3,8);
    printf(" $$$$$$/      $$/   $$/     $$$$$$/       $$/             $$$$$$/          $$/    ");
    textcolor(BLUE);
    gotoxy(9,10);
    printf("ACADEMIA PERSONALIZADA - UNIVERSIDADE ESTADUAL DE MONTES CLAROS");
    textcolor(BLUE);
    gotoxy(2, 31);
    printf("Feito por: Marcos L. P. Moura");

}
    char opcoes[][51] = {"CADASTRO DE ALUNO", "ALTERAR ALUNO", "EXCLUSAO DE ALUNO", "LISTA DE ALUNOS", "LISTA DE ALUNOS IMC > 30", "LISTA DE PESO IDEAL", "RELATORIO DE CURSOS", "FECHAR"};
    int x[] = {3, 3, 3, 3, 35, 35, 35, 35};
    int y[] = {20, 22, 24, 26, 20, 22, 24, 26};      //MENU DE SELE플O DA TELA INICIAL

int main()
{
    Aluno A;
    int escolha = 0;

    do
    {
        tipocursor(FALSE);

        TelaPrincipal();    //ABRE A FUN플O DA TELA INICIAL

        escolha = menu(opcoes, x, y, escolha, 8); //MENU DE SELE플O DA TELA INICIAL

        if(escolha == 0)AtivarAluno();
        if(escolha == 1)AlterarAluno();
        if(escolha == 2)ExcluirAluno();
        if(escolha == 3)ListarAlunos();
        if(escolha == 4)ListarAlunosIMC();
        if(escolha == 5)ListarAlunosPesoIdeal();
        if(escolha == 6)RelatorioCurso();
        if(escolha == 7)
        {
            fecharArquivoAluno();   //FECHA O ARQUIVO ALUNO
            Borda(24, 14, 21, 2, 0, 0);
            gotoxy(25, 15);
            printf("OBRIGADO PELO ACESSO!");
            break;  //ENCERRA O SISTEMA DE CADASTRAMENTO AO SELECIONAR A OP플O "FECHAR"
        }
    }
    while(escolha != -1);


    gotoxy(0, 33);
    return 0;
}
