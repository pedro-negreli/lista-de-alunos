#include <stdio.h>
#include <string.h>
#define MAX 25

void linha()
{
    printf("============================================================\n");
}

void Menu()
{
    linha();

    printf("                     BEM VINDO AO MENU!!                 \n");
    printf("1-CADASTRAR\n");
    printf("2-LISTA\n");
    printf("3-SALVAR\n");
    printf("4-SAIR\n");

    linha();
}

void Cadastraraluno(char nome[][80], int idade[], char curso[][120], int *quantidade);
{
    if (quantidade >= MAX)
    {
        printf("Limite atingido\n");
        return;
    }


    printf("Qual o nome do aluno: ");
    fgets(nome[*quantidade],80, stdin);
    nome[quantidade][strcspn(nome[*quantidade], "\n")] = '\0';

    printf("Qual a idade do %s: ", nome[*quantidade]);
    scanf("%d", &idade[*quantidade]);
    getchar();


    printf("Qual o curso que o %s esta cursando", nome[*quantidade]);
    fgets(curso[*quantidade],120,stdin);
    curso[*quantidade][strcspn(curso[*quantidade], "\n")] = '\0';

    (*quantidade)++

    printf("Aluno cadastrado!!\n")
}


int main()
{
    

    Menu()
}