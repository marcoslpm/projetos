#ifndef ALUNO_H_INCLUDED
#define ALUNO_H_INCLUDED

typedef struct{
    char Codigo[5];
    char Nome[51];
    char Sexo[15];
    char Endereco[100];
    float Peso;
    float Altura;
    char Curso[51];
    float Mensalidade;
}Aluno;

Aluno A;
Aluno DigitarAluno();
Aluno PesquisarAluno();
Aluno DigitarCurso();
Aluno CadastrarAluno();

void abrirArquivoAluno();
void fecharArquivoAluno();
void salvarNovoAluno(Aluno A);
void ImprimirAluno(Aluno A);
void AtivarAluno();
void TelaAluno();
void ListarAlunos();
void ExcluirAluno();
void AlterarAluno();
void ListarAlunosPesoIdeal();
void RelatorioCurso();
void ListarAlunosIMC();


#endif // ALUNO_H_INCLUDED
