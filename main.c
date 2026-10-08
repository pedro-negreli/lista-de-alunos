#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 25

void linha()
{
    printf("============================================================\n");
}

int Menu()
{
    int escolha = 0;
    linha();

    printf("                     BEM VINDO AO MENU!!                 \n");
    printf("1-CADASTRAR\n");
    printf("2-LISTA\n");
    printf("3-SALVAR\n");
    printf("4-SAIR\n");

    linha();

    scanf("%d",&escolha);
    return escolha;
}

void CadastrarAluno(char nome[][80], int idade[], char curso[][120], int *quantidade)
{
    if (*quantidade >= MAX)
    {
        printf("Limite atingido\n");
        return;
    }
    getchar();

    printf("Qual o nome do aluno: ");
    fgets(nome[*quantidade],80, stdin);
    nome[*quantidade][strcspn(nome[*quantidade], "\n")] = '\0';

    printf("Qual a idade do %s: ", nome[*quantidade]);
    scanf("%d", &idade[*quantidade]);
    getchar();


    printf("Qual o curso que o %s esta cursando: ", nome[*quantidade]);
    fgets(curso[*quantidade],120,stdin);
    curso[*quantidade][strcspn(curso[*quantidade], "\n")] = '\0';

    (*quantidade)++;

    printf("Aluno cadastrado!!\n");
}

void ListarLista(char nome[][80], int idade[], char curso[][120],int quantidade)
{
    for(int i = 0;i < quantidade;i++)
    {   

        printf("%d |        %s      |    %d    |     %s        |\n", i , nome[i], idade[i], curso[i]);
        
    }
}

void SalvarLista(char nome[][80], int idade[], char curso[][120],int quantidade)
{
    FILE* arquivo;

    arquivo = fopen("alunos.csv", "w");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    for(int i = 0; i < quantidade;i++)
    {
        fprintf(arquivo, "%s;%d;%s\n",nome[i],idade[i],curso[i]);

    }

    fclose(arquivo);
}

int EnviarBanco()
{
    int retorno;

    retorno = system(
        "bcp escola.dbo.alunos_import in envia.csv"
        "-S localhost,1433 "
        "-U sa "
        "-P \"$SQL_SA_PASSWORD\" "
        "-c "
        "-t';' "
        "-r '\\n' "
        "-u"
    );
    
    if(retorno != 0)
    {
        printf("Erro ao tentar enviar para o Banco\n");
    }
    
    printf("Enviado para o banco com sucesso!!\n");
    return 1;


}

void CriarArquivoEnvio(char nome[][80], int idade[], char curso[][120],int quantidade,int enviados)
{
    FILE* arquivo;

    arquivo = fopen("envia.csv", "w");

    if(arquivo == NULL)
    {
        printf("Erro ao criar arquvio enviar.csv\n");

    }

    for(int i = enviados;i < quantidade;i++)
    {
        fprintf(arquivo, "%s;%d;%s\n",nome[i][80],idade[i],curso[i][120]);
    }

fclose(arquivo);
}

void BuscarBanco()
{
    int retorno;

    retorno = system(
        "bcp \"SELECT nome, idade, curso FROM escola.dbo.alunos_import\""
        "queryout alunos.csv"
        "-S localhost, 1433"
        "-U sa"
        "-p \"$SQL_SA_PASSWORD\""
        "-c "
        "-t ';'"
        "-r '\n"
        "-u"
    );
    return retorno == 1;
}

void CarrergarArquivo(char nome[][80], int idade[],char curso[][120], int *quantidade)
{
    FILE *arquivo;

    arquivo = fopen("alunos.csv", "r");
    
    if(arquivo == NULL)
    {
        printf("Erro ao abrir arquivo!!\n");
    }

    while(*quantidade < MAX && fscanf(arquivo," %79[%^;];%d;%119[^\n]",nome[*quantidade],idade[*quantidade],curso[*quantidade]) == 3)
    {
        (*quantidade)++;
    }

fcolse(arquivo);

}



int main()
{
    ///////////////// vetores paralelos///////////
    char nome[MAX][80];
    int idade[MAX];
    char curso[MAX][120];
////////////////////////////////////////////
    int quantidade = 0;
    int escolha;
    int enviados = 0;
////////////////////////////////////////

do{
    escolha = Menu();
    switch (escolha)
    {
    case 1:
        CadastrarAluno(nome, idade, curso, &quantidade);
        break;
    
    case 2:
        printf("Lista\n");
        printf("id |    nome     | idade |    curso   |\n");
        ListarLista(nome, idade, curso, quantidade);
        break;


    case 3:
        printf("Salvar\n");
        SalvarLista(nome,idade,curso, quantidade);
        if(quantidade > enviados)
        {
            CriarArquivoEnvio(nome,idade,curso,quantidade,enviados);
        

            if (EnviarBanco())
            {
                enviados = quantidade;
            }
        }
        else
        {
            printf("Nenhum aluno novo para enviar\n");
        }

        break;

    case 4:
        printf("Sair\n");
        break;

    default:
        printf("Não existe essa opção!!");
        break;
    }
}while(escolha != 4);

}