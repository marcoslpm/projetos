#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"
#include "aluno.h"

FILE *fpAluno;

Aluno A;

void abrirArquivoAluno() //ABRE ARQUIVO ALUNO
{
    fpAluno = fopen("aluno.txt","rb+"); //ABRE O ARQUIVO EM MODO LEITURA E ESCITA
    if(fpAluno == NULL)
    {
        fpAluno = fopen("aluno.txt","wb+"); //CRIA UM ARQUIVO EM MODO LEITURA E ESCRITA
        if(fpAluno == NULL)
        {
            printf("Nao abriu aluno.txt\n");
            exit(1);
        }
    }

}

void fecharArquivoAluno() //FECHA ARQUIVO ALUNO
{

    fclose(fpAluno);

}

void salvarNovoAluno(Aluno A) //SALVA UM NOVO ALUNO NO ARQUIVO
{
    fseek(fpAluno, 0, SEEK_END); //POSICIONA O PONTEIRO NO FINAL DO ARQUIVO
    fwrite(&A, sizeof(Aluno),1, fpAluno); //ESCREVE OS DADOS DE ENTRADA NO ARQUIVO
    fflush(fpAluno); //LIMPA O BUFFER DO TECLADO
}

void TelaAluno() //ABRE A TELA DE PREENCHIMENTO DOS DADOS DO ALUNO
{
    Borda(10, 3, 51, 26, 1, 1); //CRIA UMA BORDA PERSONALIZADA
    gotoxy(29, 4);              //POSICIONA O CURSOR OU PRINTF EM UM EIXO X E EIXO Y DO TERMINAL
    printf("FICHA DO ALUNO");
    gotoxy(14, 6);
    printf("CODIGO: ");
    gotoxy(14, 9);
    printf("NOME: ");
    gotoxy(14, 12);
    printf("ENDERECO: ");
    gotoxy(14, 15);
    printf("ALTURA: ");
    gotoxy(14, 18);
    printf("PESO: ");
    gotoxy(14, 21);
    printf("SEXO: ");
    gotoxy(14, 24);
    printf("CURSO: ");
    gotoxy(14, 27);
    printf("MENSALIDADE: ");
    Borda(26, 5, 30, 2, 0, 0);
    Borda(26, 8, 30, 2, 0, 0);
    Borda(26, 11, 30, 2, 0, 0);
    Borda(26, 14, 30, 2, 0, 0);
    Borda(26, 17, 30, 2, 0, 0);
    Borda(26, 20, 30, 2, 0, 0);
    Borda(26, 23, 30, 2, 0, 0);
    Borda(26, 26, 30, 2, 0, 0);
}

Aluno DigitarAluno() //FUNÇÃO PARA ENTRADA DE VALORES NAS VARIÁVEIS DO STRUCT
{
    Aluno A;

    tipocursor(TRUE); //ATIVA O CURSOR

    gotoxy(27,6);
    fflush(stdin);
    gets(A.Codigo);  //VARIÁVEL DO STRUCT RECEBE ENTRADA DE DADOS

    gotoxy(27, 9);
    fflush(stdin);
    gets(A.Nome);

    gotoxy(27, 12);
    fflush(stdin);
    gets(A.Endereco);

    gotoxy(27, 15);
    fflush(stdin);
    scanf("%f", &A.Altura);

    gotoxy(27, 18);
    fflush(stdin);
    scanf("%f", &A.Peso);

    ApagarCaixa(26, 20, 30, 2, 0, 0); //APAGA UMA CAIXA EM UMA DETERMINADA ÁREA DO TERMINAL
    Borda(26, 23, 30, 2, 0, 0);
    Borda(27, 20, 10, 2, 0, 0);
    Borda(43, 20, 10, 2, 0, 0);


    int OpcaoSexo = 0;

    char opcoesSexo[][51] = {"MASCULINO","FEMININO"};
    int xSexo[] = {28, 45};
    int ySexo[] = {21, 21};

    tipocursor(FALSE);

    OpcaoSexo = menu(opcoesSexo, xSexo, ySexo, OpcaoSexo, 2); //ABRE O MENU DE SELEÇÃO DO SEXO

    if(OpcaoSexo == 0)
    {
        ApagarCaixa(27, 20, 10, 2, 0, 0);
        ApagarCaixa(43, 20, 10, 2, 0, 0);
        Borda(26, 20, 30, 2, 0, 0);

        gotoxy(27, 21);
        printf("%s", opcoesSexo[OpcaoSexo]); //IMPRIME A OPÇÃO SELECIONADA NA TELA DO ALUNO

        strcpy(A.Sexo, opcoesSexo[OpcaoSexo]); //VARIÁVEL DO STRUCT RECEBE A OPÇÃO DE SEXO SELECIONADA
    }

    if(OpcaoSexo == 1)
    {
        ApagarCaixa(27, 20, 10, 2, 0, 0);
        ApagarCaixa(43, 20, 10, 2, 0, 0);
        Borda(26, 20, 30, 2, 0, 0);

        gotoxy(27, 21);
        printf("%s", opcoesSexo[OpcaoSexo]);

        strcpy(A.Sexo, opcoesSexo[OpcaoSexo]);
    }

    return A; //RETORNA ALUNO "A"
}

Aluno PesquisarAluno() //FAZ UMA PESQUISA NO BANCO DE DADOS DO ARQUIVO
{
    char codigo[5];
    Aluno A;
    ApagarCaixa(10, 3, 51, 26, 1, 1);
    Borda(10, 3, 51, 26, 1, 1);
    gotoxy(27, 6);
    printf("PESQUISA DE ALUNO");
    gotoxy(23, 15);
    printf("DIGITE O CODIGO DO ALUNO:");
    gotoxy(49, 15);
    scanf("%s", &codigo);
    fseek(fpAluno, 0, SEEK_SET);   //MOVE O PONTEIRO PARA O INÍCIO DO ARQUIVO
    while(fread(&A,sizeof(Aluno),1,fpAluno)){   //LÊ TODOS OS DADOS DO ARQUIVO
        if(strcmp(codigo, A.Codigo)== 0){     //COMPARA AS VARIÁVEIS
            return A;           //SE FOREM IGUAIS, RETORNA "A"
        }

        if(codigo != A.Codigo)    //SE FOREM DIFERENTES, CÓDIGO NÃO CADASTRADO
        {
            textcolor(RED);
            gotoxy(19, 13);
            printf("WARNING!!!!CODIGO NAO CADASTRADO!!!!");
        }

    }

    strcpy(A.Codigo, "");
    return A;

}

void ImprimirAluno(Aluno A) //IMRPIME OS DADOS DO ALUNO DIGITADO
{
    tipocursor(FALSE); //DESATIVA O CURSOR

    ApagarCaixa(10, 3, 55, 26, 1, 1);
    ApagarCaixa(0, 0, 86, 35, 1, 0);

    Borda(10, 3, 51, 26, 1, 1);

    gotoxy(28, 4);
    printf("FICHA DO ALUNO");

    gotoxy(14, 6);
    printf("CODIGO:");
    gotoxy(27,6);
    printf("%s", A.Codigo);

    gotoxy(14, 9);
    printf("NOME:");
    gotoxy(27, 9);
    printf("%s", A.Nome);

    gotoxy(14, 12);
    printf("ENDERECO:");
    gotoxy(27, 12);
    printf("%s", A.Endereco);

    gotoxy(14, 15);
    printf("ALTURA:");
    gotoxy(27, 15);
    printf("%.2fm", A.Altura);

    gotoxy(14, 18);
    printf("PESO:");
    gotoxy(27, 18);
    printf("%.2fkg", A.Peso);

    gotoxy(14, 21);
    printf("SEXO:");
    gotoxy(27, 21);
    printf("%s", A.Sexo);

    gotoxy(14, 24);
    printf("CURSO:");
    gotoxy(27, 24);
    printf("%s", A.Curso);

    gotoxy(14, 27);
    printf("MENSALIDADE:");
    gotoxy(27, 27);
    printf("R$%.2f", A.Mensalidade);
}

void ListarAlunos()  //FAZ UMA LISTAGEM SIMPLES DOS ALUNOS DA ACADEMIA
{
    FILE *fpAluno = fopen("aluno.txt", "rb");  //ABRE O ARQUIVO EM MODO LEITURA

    Aluno A;

    int y = 7;

    ApagarCaixa(0, 0, 86, 35, 1, 0);
    Borda(10, 3, 51, 26, 1, 1);
    gotoxy(27, 5);
    printf("LISTA DE ALUNOS");

    while(fread(&A, sizeof(Aluno), 1, fpAluno) == 1)
    {
        gotoxy(11,y);
        printf("CODIGO: %s - NOME: %s", A.Codigo, A.Nome);  //IMPRIME O CÓDIGO E O NOME DE CADA ALUNO
        y++;                   //A CADA INCREMENTAÇÃO, O EIXO Y RECEBE 1, ASSIM CADA PRINTF FICA DE BAIXO UM DO OUTRO
        Sleep(500);       //0.5 SEGUNDOS PARA CADA IMPRESSÃO
    }

    fclose(fpAluno);
    gotoxy(0, 32);
    system("pause");

}

Aluno CadastrarAluno()  //CADASTRA O ALUNO
{
    Aluno A;

    int OpcaoCurso = 0;

    char opcoesCursos[][51] = {"MUSCULACAO","PILATES","JUMP"};  //MENU DE OPÇÕES DE CURSOS
    int xCurso[] = {22, 37, 53};
    int yCurso[] = {24, 24, 24};

    TelaAluno();  //ABRE A TELA DO ALUNO

    A = DigitarAluno(); //FUNÇÃO PARA DIGITAR O ALUNO

    tipocursor(FALSE);

    ApagarCaixa(26, 23, 30, 2, 0, 0);
    Borda(26, 26, 30, 2, 0, 0);
    Borda(21, 23, 10, 2, 0, 0);
    Borda(35, 23, 10, 2, 0, 0);
    Borda(49, 23, 10, 2, 0, 0);

    OpcaoCurso = menu(opcoesCursos, xCurso, yCurso, OpcaoCurso, 3);


    if(OpcaoCurso == 0) //MUSCULAÇÃO R$ 89.90
    {
        ApagarCaixa(21, 23, 10, 2, 0, 0);
        ApagarCaixa(35, 23, 10, 2, 0, 0);
        ApagarCaixa(49, 23, 10, 2, 0, 0);
        Borda(26, 23, 30, 2, 0, 0);
        Borda(26, 26, 30, 2, 0, 0);

        gotoxy(27, 24);
        printf("%s", opcoesCursos[OpcaoCurso]);  //PRINTA A OPÇÃO SELECIONADA NA CAIXA DO CURSO

        strcpy(A.Curso, opcoesCursos[OpcaoCurso]); //A VARIÁVEL DO STRUCT RECEBE A OPCÃO DE CURSO SELECIONADA

        tipocursor(TRUE);
        gotoxy(27, 27);
        fflush(stdin);
        scanf("%f", &A.Mensalidade);  //APÓS SELECIONAR O CURSO, DIGITAR A MENSALIDADE
    }

    if(OpcaoCurso == 1) //PILATES R$ 109.90
    {
        ApagarCaixa(21, 23, 10, 2, 0, 0);
        ApagarCaixa(35, 23, 10, 2, 0, 0);
        ApagarCaixa(49, 23, 10, 2, 0, 0);
        Borda(26, 23, 30, 2, 0, 0);
        Borda(26, 26, 30, 2, 0, 0);

        gotoxy(27, 24);
        printf("%s", opcoesCursos[OpcaoCurso]);

        strcpy(A.Curso, opcoesCursos[OpcaoCurso]);

        tipocursor(TRUE);
        gotoxy(27, 27);
        fflush(stdin);
        scanf("%f", &A.Mensalidade);
    }

    if(OpcaoCurso == 2) //JUMP R$ 69.90
    {
        ApagarCaixa(21, 23, 10, 2, 0, 0);
        ApagarCaixa(35, 23, 10, 2, 0, 0);
        ApagarCaixa(49, 23, 10, 2, 0, 0);
        Borda(26, 23, 30, 2, 0, 0);
        Borda(26, 26, 30, 2, 0, 0);

        gotoxy(27, 24);
        printf("%s", opcoesCursos[OpcaoCurso]);

        strcpy(A.Curso, opcoesCursos[OpcaoCurso]);

        tipocursor(TRUE);
        gotoxy(27, 27);
        fflush(stdin);
        scanf("%f", &A.Mensalidade);
    }

    return A;
}

void AtivarAluno()  //JUNÇAO DE ALGUMAS FUNÇÕES
{
    Aluno A;

    int Escolha = 0;
    int EscolhaConfirmar = 0;

    char opcoes[][51] = {"NOVO","PESQUISAR","SAIR"}; //MENU DE OPÇÃO, NOVO ALUNO, PESQUISAR ALUNO OU SAIR
    int x[] = {20, 31, 48};
    int y[] = {16, 16, 16};

    char opcoesconfirma[][51] = {"SIM","CANCELAR"};  //MENU DE OPÇÃO, SALVAR OU NÃO O ALUNO
    int xCONFIRMA[] = {27, 37};
    int yCONFIRMA[] = {16, 16};

    abrirArquivoAluno();
    do
    {
        ApagarCaixa(0, 0, 86, 35, 1, 0);
        Borda(10, 3, 51, 26, 1, 1);
        Borda(16, 15, 10, 2, 0, 0);
        Borda(30, 15, 10, 2, 0, 0);
        Borda(44, 15, 10, 2, 0, 0);

        Escolha = menu(opcoes, x, y, Escolha, 3);

        if(Escolha == 0)
        {
            A = CadastrarAluno();

            tipocursor(FALSE);
            ApagarCaixa(10, 3, 51, 26, 1, 1);
            Borda(10, 3, 51, 26, 1, 1);
            gotoxy(22, 10);
            printf("DESEJA SALVAR ESSE ALUNO ?");

            Borda(22, 15, 10, 2, 0, 0);
            Borda(35, 15, 10, 2, 0, 0);
            EscolhaConfirmar = menu(opcoesconfirma, xCONFIRMA, yCONFIRMA, EscolhaConfirmar, 2);

            if(EscolhaConfirmar == 0)
            {
                salvarNovoAluno(A);
                tipocursor(FALSE);
                ApagarCaixa(10, 3, 51, 26, 1, 1);
                Borda(10, 3, 51, 26, 1, 1);
                gotoxy(23, 11);
                printf("!!!!SALVO COM SUCESSO!!!!");
                gotoxy(0, 32);
                system("pause");
            }

            if(EscolhaConfirmar == 1)
            {
                break;
            }

        }

            if(Escolha == 1)
            {
                tipocursor(FALSE);
                A = PesquisarAluno();
                if(strlen(A.Codigo) > 0)
                    ImprimirAluno(A);
                    gotoxy(0, 32);
                    system("pause");
                    ApagarCaixa(10, 3, 51, 26, 1, 1);
                    Borda(10, 3, 51, 26, 1, 1);
            }


    }
    while(Escolha != 2);
    fecharArquivoAluno();

}

void RelatorioCurso()  //FUNÇÃO PARA FAZER A SOMATÓRIA DAS MENSALIDADES POR CURSO E O TOTAL
{
    FILE *fpAluno = fopen("aluno.txt", "rb");  //ABRE O ARQUIVO EM MODO DE LEITURA

    Aluno A;

    float totalMusculacao = 0;
    float totalPilates = 0;
    float totalJump = 0;
    float valorTotal = 0;

    ApagarCaixa(0, 0, 86, 35, 1, 0);

    while (fread(&A, sizeof(Aluno), 1, fpAluno) == 1)
    {
        if (strcmp(A.Curso, "MUSCULACAO") == 0) {  //COMPARA SE A VARIÁVEL DO STRUCT TEM "MUSCULAÇÃO", QUANDO TIVER, AS MENSALIDADES VÃO SOMAR EM TOTAL
            totalMusculacao += A.Mensalidade;
        }
            else if (strcmp(A.Curso, "PILATES") == 0) {  //COMPARA SE A VARIÁVEL DO STRUCT TEM "PILATES", QUANDO TIVER, AS MENSALIDADES VÃO SOMAR EM TOTAL
                totalPilates += A.Mensalidade;
            }
                else if (strcmp(A.Curso, "JUMP") == 0) {  //COMPARA SE A VARIÁVEL DO STRUCT TEM "JUMP", QUANDO TIVER, AS MENSALIDADES VÃO SOMAR EM TOTAL
                    totalJump += A.Mensalidade;
                }
    }

    fclose(fpAluno);

    Borda(10, 3, 51, 26, 1, 1);
    gotoxy(27, 5);
    printf("RELATORIO DE CURSOS");
    gotoxy(11,8);
    printf("**SOMATORIA DAS MENSALIDADES DOS ALUNOS POR CURSO**");  //SAÍDAS DOS TOTAIS DAS MENSALIDADES
    gotoxy(13,11);
    printf("MUSCULACAO: R$ %.2f", totalMusculacao);
    gotoxy(13,13);
    printf("PILATES: R$ %.2f", totalPilates);
    gotoxy(13,15);
    printf("JUMP: R$ %.2f", totalJump);
    gotoxy(13,17);
    printf("TOTAL: R$ %.2f", valorTotal = (totalMusculacao + totalPilates + totalJump)); //VALOR TOTAL SOMANDO TODAS AS MENSALIDADES DE TODOS OS CURSOS
    gotoxy(0, 32);
    system("pause");
}

void ListarAlunosIMC()  //FAZ UMA LISTA DOS ALUNOS COM IMC MAIOR QUE 30
{
    FILE *fpAluno = fopen("aluno.txt", "rb");  //ABRE O ARQUIVO EM MODO DE LEITURA

    Aluno A;

    float imc = 0;
    int y1 = 7;

    ApagarCaixa(0, 0, 86, 35, 1, 0);
    Borda(10, 3, 81, 26, 1, 1);
    gotoxy(31, 5);
    printf("LISTA DE ALUNOS COM IMC MAIOR QUE 30");

    while(fread(&A, sizeof(Aluno), 1, fpAluno) == 1)
    {
        imc = A.Peso / (A.Altura * A.Altura);  //FAZ O CÁLCULO DO IMC

        if (imc > 30)
        {
            gotoxy(11,y1);
            printf("NOME: %s - PESO: %.2fkg - ALTURA: %.2fm - IMC: %.2f", A.Nome, A.Peso, A.Altura, imc);  //IMPRIME O NOME, PESO E O IMC
            y1++;
            Sleep(500);
        }
    }

    fclose(fpAluno);
    gotoxy(0, 32);
    system("pause");
    ApagarCaixa(10, 3, 86, 26, 1, 1);
}

void ListarAlunosPesoIdeal()  //FAZ UMA LISTA DOS ALUNOS COM O PESO IDEAL DE CADA UM
{
    FILE *fpAluno = fopen("aluno.txt", "rb");   //ABRE O ARQUIVO EM MODO DE LEITURA

    Aluno A;

    float pesoIdeal = 0;
    int y1 = 7;

    ApagarCaixa(0, 0, 86, 35, 1, 0);
    Borda(10, 3, 81, 26, 1, 1);
    gotoxy(34, 5);
    printf("LISTA DE ALUNOS COM PESO IDEAL");

    while (fread(&A, sizeof(Aluno), 1, fpAluno) == 1)
    {
        if(strcmp(A.Sexo, "MASCULINO") == 0)       //SE TIVER "MASCULINO" DENTRO NA VARIÁVEL DO STRUCT
        {
            pesoIdeal = 61.2328 + ((A.Altura - 1.6002) * 53.5433);  //VAI FAZER O CÁLCULO DO PESO IDEAL PARA PESSOAS DO SEXO MASCULINO
        }

        if(strcmp(A.Sexo, "FEMININO") == 0)     //SE TIVER "FEMININO" DENTRO NA VARIÁVEL DO STRUCT
        {
            pesoIdeal = 53.695 + ((A.Altura - 1.524) * 53.5433);   //VAI FAZER O CÁLCULO DO PESO IDEAL PARA PESSOAS DO SEXO FEMININO
        }

        gotoxy(11,y1);
        printf("NOME: %s - PESO: %.2fkg - PESO IDEAL: %.2fkg", A.Nome, A.Peso, pesoIdeal);  //IMPRIME O NOME, PESO E PESO IDEAL DA PESSOA
        y1++;
        Sleep(500);
    }

    fclose(fpAluno);
    gotoxy(0, 32);
    system("pause");
    ApagarCaixa(10, 3, 86, 26, 1, 1);
}

void AlterarAluno()   //FUNÇÃO PARA ALTERAR UM ALUNO
{
    FILE *fpAluno = fopen("aluno.txt", "r+b");  //ABRE O ARQUIVO PARA LEITURA E ESCRITA

    char codigo[5];

    ApagarCaixa(0, 0, 86, 35, 1, 0);
    Borda(10, 3, 51, 26, 1, 1);
    gotoxy(27, 5);
    printf("ALTERAR ALUNO");
    gotoxy(14, 10);
    printf("DIGITE O CODIGO DO ALUNO QUE DESEJA ALTERAR: ");
    fflush(stdin);
    gets(codigo);

    Aluno A;
    int alunoEncontrado = 0;

    while (fread(&A, sizeof(Aluno), 1, fpAluno) == 1) {
        if (strcmp(A.Codigo, codigo) == 0) {    //COMPARA OS CÓDIGOS, SE FOREM IGUAIS, VAI REPETIR O PROCESSO DE CADASTRAR ALUNO COMEÇANDO PELO NOME
            ImprimirAluno(A);      //IMPRIME A FICHA DO ALUNO DIGITADO
            gotoxy(0, 32);
            system("pause");

            ApagarCaixa(10, 3, 51, 26, 1, 1);
            Borda(10, 3, 51, 26, 1, 1);
            gotoxy(11, 7);
            TelaAluno();
            gotoxy(29, 4);
            printf("ALTERAR  ALUNO");

            tipocursor(TRUE);

            gotoxy(27, 9);
            fflush(stdin);
            gets(A.Nome);

            gotoxy(27, 12);
            fflush(stdin);
            gets(A.Endereco);

            gotoxy(27, 15);
            fflush(stdin);
            scanf("%f", &A.Altura);

            gotoxy(27, 18);
            fflush(stdin);
            scanf("%f", &A.Peso);

            ApagarCaixa(26, 20, 30, 2, 0, 0);
            Borda(26, 23, 30, 2, 0, 0);
            Borda(27, 20, 10, 2, 0, 0);
            Borda(43, 20, 10, 2, 0, 0);


            int OpcaoSexo = 0;

            char opcoesSexo[][51] = {"MASCULINO","FEMININO"};
            int xSexo[] = {28, 45};
            int ySexo[] = {21, 21};

            tipocursor(FALSE);

            OpcaoSexo = menu(opcoesSexo, xSexo, ySexo, OpcaoSexo, 2);

            if(OpcaoSexo == 0)
            {
                ApagarCaixa(27, 20, 10, 2, 0, 0);
                ApagarCaixa(43, 20, 10, 2, 0, 0);
                Borda(26, 20, 30, 2, 0, 0);

                gotoxy(27, 21);
                printf("%s", opcoesSexo[OpcaoSexo]);

                strcpy(A.Sexo, opcoesSexo[OpcaoSexo]);
            }

            if(OpcaoSexo == 1)
            {
                ApagarCaixa(27, 20, 10, 2, 0, 0);
                ApagarCaixa(43, 20, 10, 2, 0, 0);
                Borda(26, 20, 30, 2, 0, 0);

                gotoxy(27, 21);
                printf("%s", opcoesSexo[OpcaoSexo]);

                strcpy(A.Sexo, opcoesSexo[OpcaoSexo]);
            }

            int OpcaoCurso = 0;

            char opcoesCursos[][51] = {"MUSCULACAO","PILATES","JUMP"};
            int xCurso[] = {22, 37, 53};
            int yCurso[] = {24, 24, 24};

            tipocursor(FALSE);

            ApagarCaixa(26, 23, 30, 2, 0, 0);
            Borda(26, 26, 30, 2, 0, 0);
            Borda(21, 23, 10, 2, 0, 0);
            Borda(35, 23, 10, 2, 0, 0);
            Borda(49, 23, 10, 2, 0, 0);

            OpcaoCurso = menu(opcoesCursos, xCurso, yCurso, OpcaoCurso, 3);

            if(OpcaoCurso == 0)
            {
                ApagarCaixa(21, 23, 10, 2, 0, 0);
                ApagarCaixa(35, 23, 10, 2, 0, 0);
                ApagarCaixa(49, 23, 10, 2, 0, 0);
                Borda(26, 23, 30, 2, 0, 0);
                Borda(26, 26, 30, 2, 0, 0);

                gotoxy(27, 24);
                printf("%s", opcoesCursos[OpcaoCurso]);

                strcpy(A.Curso, opcoesCursos[OpcaoCurso]);

                tipocursor(TRUE);
                gotoxy(27, 27);
                fflush(stdin);
                scanf("%f", &A.Mensalidade);
            }

            if(OpcaoCurso == 1)
            {
                ApagarCaixa(21, 23, 10, 2, 0, 0);
                ApagarCaixa(35, 23, 10, 2, 0, 0);
                ApagarCaixa(49, 23, 10, 2, 0, 0);
                Borda(26, 23, 30, 2, 0, 0);
                Borda(26, 26, 30, 2, 0, 0);

                gotoxy(27, 24);
                printf("%s", opcoesCursos[OpcaoCurso]);

                strcpy(A.Curso, opcoesCursos[OpcaoCurso]);

                tipocursor(TRUE);
                gotoxy(27, 27);
                fflush(stdin);
                scanf("%f", &A.Mensalidade);
            }

            if(OpcaoCurso == 2)
            {
                ApagarCaixa(21, 23, 10, 2, 0, 0);
                ApagarCaixa(35, 23, 10, 2, 0, 0);
                ApagarCaixa(49, 23, 10, 2, 0, 0);
                Borda(26, 23, 30, 2, 0, 0);
                Borda(26, 26, 30, 2, 0, 0);

                gotoxy(27, 24);
                printf("%s", opcoesCursos[OpcaoCurso]);

                strcpy(A.Curso, opcoesCursos[OpcaoCurso]);

                tipocursor(TRUE);
                gotoxy(27, 27);
                fflush(stdin);
                scanf("%f", &A.Mensalidade);
            }

            fseek(fpAluno, -sizeof(Aluno), SEEK_CUR);   //VOLTA PARA A POSIÇÃO ATUAL DO ARQUIVO
            fwrite(&A, sizeof(Aluno), 1, fpAluno);      //SOBRESCREVE OS DADOS DO ALUNO NO ARQUIVO

            alunoEncontrado = 1;    //DEPOIS QUE ALTERADO, ESSA VARIÁVEL RECEBE 1
            break;
        }
    }

    fclose(fpAluno);

    if (!alunoEncontrado)   //SE A VARIÁVEL PERMANECER 0, RECEBE MENSAGEM DE ALUNO NÃO ENCONTRADO
    {
        textcolor(RED);
        gotoxy(19, 13);
        printf("WARNING!!!!ALUNO NAO ENCONTRADO!!!!");
        textcolor(BLUE);
        gotoxy(0, 32);
        system("pause");
    }

    else    //SENÃO CONTINUAR 0, OU SEJA, 1, RECEBE MENSAGEM DE DADOS ALTERADOS COM SUCESSO
    {
        ApagarCaixa(10, 3, 51, 26, 1, 1);
        Borda(10, 3, 51, 26, 1, 1);
        gotoxy(27, 5);
        printf("ALTERAR ALUNO");
        gotoxy(14, 13);
        printf("!!!!DADOS DO ALUNO ALTERADOS COM SUCESSO!!!!");
        gotoxy(0, 32);
        system("pause");
    }
}

void ExcluirAluno()   //FUNÇÃO PARA EXCLUIR ALUNO DO SISTEMA DE CADASTRAMENTO
{
    FILE *fpAluno = fopen("aluno.txt", "rb");   //ABRE O ARQUIVO EM MODO DE LEITURA

    if (fpAluno == NULL) {
        printf("Erro ao abrir o arquivo");
        return;
    }

    FILE* temporario = fopen("temp.txt", "wb"); //CRIA UM ARQUIVO TEMPORÁRIO EM MODO DE ESCRITA
    if (temporario == NULL) {
        printf("Erro ao abrir o arquivo temporario");
        fclose(fpAluno);
        return;
    }

    Aluno A;
    ApagarCaixa(0, 0, 86, 35, 1, 0);
    ApagarCaixa(0, 0, 86, 35, 1, 0);
    Borda(10, 3, 51, 26, 1, 1);
    gotoxy(27, 5);
    printf("EXCLUSAO DE ALUNO");

    int alunoExcluido = 0;
    char codigo[5];
    tipocursor(TRUE);
    gotoxy(14, 11);
    printf("DIGITE O CODIGO DO ALUNO QUE DESEJA EXCLUIR: ");
    gets(codigo);

    while (fread(&A, sizeof(Aluno), 1, fpAluno) == 1) {
        if (strcmp(A.Codigo, codigo) != 0) {       //COMPARA SE O CÓDIGO DO STRUCT E DA FUNÇÃO SÃO DIFERENTES
            fwrite(&A, sizeof(Aluno), 1, temporario); //SE SIM, VAI ESCREVER OS ALUNOS COM CÓDIGOS DIFERENTES NO ARQUIVO TEMPORÁRIO
        } else {
            alunoExcluido = 1;   //O CÓDIGO DIGITADO VAI PERMANECER NO ARQUIVO ORIGINAL E ESSA VARIÁVEL RECEBE 1
        }
    }

    fclose(fpAluno);
    fclose(temporario);

    remove("aluno.txt");    //O ARQUIVO ORIGINAL É EXCLUÍDO PERMANENTEMENTE
    rename("temp.txt", "aluno.txt");    //O ARQUIVO TEMPORÁRIO É RENOMEADO COM O MESMO NOME DO ARQUIVO ORIGINAL

    if (alunoExcluido == 1) {     //SE HOUVER UM ALUNO EXCLUÍDO, RECEBE A MENSAGEM DE ALUNO EXCLÍDO COM SUCESSO
        ApagarCaixa(10, 3, 51, 26, 1, 1);
        Borda(10, 3, 51, 26, 1, 1);
        gotoxy(27, 5);
        printf("EXCLUIR ALUNO");
        gotoxy(18,13);
        printf("!!!!ALUNO EXCLUIDO COM SUCESSO!!!!");
    }
    else {
        textcolor(RED);
        gotoxy(19, 13);
        printf("WARNING!!!!ALUNO NAO ENCONTRADO!!!!");  //SENÃO, RECEBE A MENSAGEM DE ALUNO NÃO ENCONTRADO
    }
    textcolor(BLUE);
    gotoxy(0,32);
    system("pause");
}










