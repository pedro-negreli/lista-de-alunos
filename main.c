#include <stdio.h>
#include <string.h>
#define MAX 25


void Cadastraraluno()
{
    char nome[MAX][80];
    int idade[MAX];
    char curso[MAX][120];
    int quantidade = 0;

    if (quantidade >= MAX)
    {
        printf("Limite atingido\n");
        return;
    }


    printf("Qual o nome do aluno: ");
    fgets(nome[quantidade],80, stdin);
    nome[quantidade][strcspn(nome[quantidade], "\n")] = '\0';

    printf("Qual a idade do %s: ", nome);
    scanf("%d", &idade[quantidade]);
    getchar();


    printf("Qual o curso que o %s esta cursando", nome[quantidade]);
    fgets(curso[quantidade],120,stdin);
    curso[quantidade][strcspn(curso[quantidade], "\n")] = '\0';

    quantidade ++;

    printf("Aluno cadastrado!!");
}
