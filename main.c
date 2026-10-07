#include <stdio.h>
#include <string.h>



void Cadastraraluno()
{
    char nome[80];
    int idade;
    char curso[120];

    printf("Qual o nome do aluno: ");
    fgets(nome,80, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    printf("Qual a idade do %s: ", nome);
    scanf("%d", idade);

    printf("Qual o curso que o %s esta cursando", nome);
    fgets(curso,120,stdin);
    curso[strcspn(curso, "\n")] = '\0';

    FILE* alunos;

    fopen("alunos.csv", "w");

    if(alunos == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    fprintf(alunos, "%s;%d;%s\n", nome, idade, curso);

    fclose(alunos);

    printf("Cadastro com sucesso!!");
}