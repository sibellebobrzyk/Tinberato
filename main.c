#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dados
{
    char nome[100];
    char dataNascimento[15];
    int genero;
    char telefone[15];
    char cidade[50];
    char gosto1[5][30];
    char gosto2[7][30];
    char gosto3[5][30];
    char gosto4[5][30];
    int numMat1; //numMat indica o numero de opcoes escolhidas para cada gosto
    int numMat2;
    int numMat3;
    int numMat4;
};

void calcularCompatibilidadeComUsuario(char *nomePesquisa)
{
    int i, l, pnts;
    int totalmat_pesquisa, totalmat_usuario;
    int encontrada = 0;
    float compatibilidade;
    struct dados pessoas, usuarioAtual;
    FILE *arquivo;
    FILE *arquivo1;

    arquivo = fopen("dados.txt", "r");
    fread(&usuarioAtual, sizeof(usuarioAtual), 1, arquivo);

    while (!feof(arquivo))
    {
        compatibilidade = 0;
        pnts = 0;

        arquivo1 = fopen("dados.txt", "r");
        fread(&pessoas, sizeof(pessoas), 1, arquivo1);

        while (!feof(arquivo1))
        {
            if (strcasecmp(pessoas.nome, usuarioAtual.nome) != 0)
            {
                if (strcasecmp(nomePesquisa, usuarioAtual.nome) == 0)
                {
                    pnts = 0; // Reinicia os pontos para cada pessoa comparada
                    encontrada++;

                    for (i = 0; i < usuarioAtual.numMat1; i++)
                    {
                        for (l = 0; l < pessoas.numMat1; l++)
                        {
                            if (strcasecmp(usuarioAtual.gosto1[i], pessoas.gosto1[l]) == 0)
                            {
                                pnts++;
                            }
                        }
                    }

                    for (i = 0; i < usuarioAtual.numMat2; i++)
                    {
                        for (l = 0; l < pessoas.numMat2; l++)
                        {
                            if (strcasecmp(usuarioAtual.gosto2[i], pessoas.gosto2[l]) == 0)
                            {
                                pnts++;
                            }
                        }
                    }

                    for (i = 0; i < usuarioAtual.numMat3; i++)
                    {
                        for (l = 0; l < pessoas.numMat3; l++)
                        {
                            if (strcasecmp(usuarioAtual.gosto3[i], pessoas.gosto3[l]) == 0)
                            {
                                pnts++;
                            }
                        }
                    }

                    for (i = 0; i < usuarioAtual.numMat4; i++)
                    {
                        for (l = 0; l < pessoas.numMat4; l++)
                        {
                            if (strcasecmp(usuarioAtual.gosto4[i], pessoas.gosto4[l]) == 0)
                            {
                                pnts++;
                            }
                        }
                    }

                    totalmat_pesquisa = (usuarioAtual.numMat1 + usuarioAtual.numMat2 + usuarioAtual.numMat3 + usuarioAtual.numMat4);
                    totalmat_usuario = (pessoas.numMat1 + pessoas.numMat2 + pessoas.numMat3 + pessoas.numMat4);

                    compatibilidade = (pnts * 200.0) / (totalmat_pesquisa + totalmat_usuario);

                    printf("Compatibilidade de %s com %s eh %.2f\n", nomePesquisa, pessoas.nome, compatibilidade);
                }
            }
            fread(&pessoas, sizeof(pessoas), 1, arquivo1);
        }

        rewind(arquivo1);
        fread(&usuarioAtual, sizeof(usuarioAtual), 1, arquivo);

    }
    fclose(arquivo1);
    fclose(arquivo);

    if(encontrada==0)
    {
        printf("\nEsse usuario nao esta cadastrado\n");
    }
}

void pesquisaPorNome(char *nomePesquisa_nome)
{
    int encontrada = 0, compatibilidade;
    int g1, g2, g3, g4;
    char nomePesquisa[100];
    struct dados pessoas;
    FILE *arquivo;

    arquivo = fopen("dados.txt", "r");
    fread(&pessoas, sizeof(pessoas), 1, arquivo);

    while (!feof(arquivo))
    {
        if (strcasecmp(pessoas.nome, nomePesquisa_nome) == 0)
        {
            printf("\nInformacoes da pessoa encontrada:\n");
            printf("Nome: %s\n", pessoas.nome);
            printf("Data de nascimento: %s\n", pessoas.dataNascimento);
            printf("Genero: %d\n", pessoas.genero);
            printf("Telefone: %s\n", pessoas.telefone);
            printf("Cidade: %s\n", pessoas.cidade);

            for (g1 = 0; g1 < pessoas.numMat1; g1++)
            {
                printf("Gosto 1: %s\n", pessoas.gosto1[g1]);
            }

            for (g2 = 0; g2 < pessoas.numMat2; g2++)
            {
                printf("Gosto 2: %s\n", pessoas.gosto2[g2]);
            }

            for (g3 = 0; g3 < pessoas.numMat3; g3++)
            {
                printf("Gosto 3: %s\n", pessoas.gosto3[g3]);
            }
            for (g4 = 0; g4 < pessoas.numMat4; g4++)
            {
                printf("Gosto 4: %s\n", pessoas.gosto4[g4]);
            }
            encontrada = 1; // encontrada !=0
            printf("\n\n");
        }
        fread(&pessoas, sizeof(pessoas), 1, arquivo);
    }

    fclose(arquivo);

    if(encontrada==0)
    {
        printf("Nenhum usuario encontrado\n");
    }

    do   // teste de compatilidade opcional
    {
        printf("Voce deseja prosseguir com o teste de compatibilidade com o usuario escolhido?");
        printf("\n1 - Sim");
        printf("\n2 - Nao\n");
        scanf("%d", &compatibilidade);
    }
    while(compatibilidade < 1 || compatibilidade > 2);

    if (compatibilidade==1)
    {
        strcpy(nomePesquisa, nomePesquisa_nome); // nomePesquisa tem agora o valor de nomePesquisa_nome
        printf("\n");
        calcularCompatibilidadeComUsuario(nomePesquisa);
    }
}

void pesquisarPorCidade(char *cidadePesquisa)
{
    int encontrados = 0;
    FILE *arquivo;
    struct dados pessoas;

    arquivo = fopen("dados.txt", "r");
    fread(&pessoas, sizeof(pessoas), 1, arquivo);

    while (!feof(arquivo))
    {
        if (strcasecmp(pessoas.cidade, cidadePesquisa) == 0)
        {
            printf("Nome: %s\n", pessoas.nome);
            printf("Data de nascimento: %s\n", pessoas.dataNascimento);
            printf("Telefone: %s\n", pessoas.telefone);
            printf("Cidade: %s\n", pessoas.cidade);
            printf("\n");
            encontrados++;
        }
        fread(&pessoas, sizeof(pessoas), 1, arquivo);
    }

    if (encontrados == 0)
    {
        printf("Nenhuma pessoa encontrada na cidade %s.\n", cidadePesquisa);
    }

    fclose(arquivo);
}

void pesquisarPorGosto1(char *gostoPesquisa)
{
    int encontrados = 0;
    struct dados pessoas;
    FILE *arquivo;
    arquivo = fopen("dados.txt", "r");
    fread(&pessoas, sizeof(pessoas), 1, arquivo);

    while (!feof(arquivo))
    {
        if (strcasecmp(pessoas.gosto1, gostoPesquisa) == 0)
        {
            printf("\nNome: %s\n", pessoas.nome);
            printf("Data de nascimento: %s\n", pessoas.dataNascimento);
            printf("Telefone: %s\n", pessoas.telefone);
            printf("Cidade: %s\n", pessoas.cidade);
            printf("\n");
            encontrados++; // define se ha usuarios encontrados
        }
        fread(&pessoas, sizeof(pessoas), 1, arquivo);
    }
    if (encontrados == 0)
    {
        printf("\nNenhuma pessoa encontrada com o gosto desejado\n");
    }
    fclose(arquivo);
}

void pesquisarPorGosto2(char *gostoPesquisa2)
{
    int encontrados = 0;
    struct dados pessoas;
    FILE *arquivo;

    arquivo = fopen("dados.txt", "r");
    fread(&pessoas, sizeof(pessoas), 1, arquivo);

    while (!feof(arquivo))
    {
        if (strcasecmp(pessoas.gosto2, gostoPesquisa2) == 0)
        {
            printf("\nNome: %s\n", pessoas.nome);
            printf("Data de nascimento: %s\n", pessoas.dataNascimento);
            printf("Telefone: %s\n", pessoas.telefone);
            printf("Cidade: %s\n", pessoas.cidade);
            printf("\n");
            encontrados++; // define se ha usuarios encontrados
        }
        fread(&pessoas, sizeof(pessoas), 1, arquivo);
    }
    if (encontrados == 0)
    {
        printf("\nNenhuma pessoa encontrada com o gosto desejado.\n");
    }

    fclose(arquivo);
}

void pesquisarPorGosto3(char *gostoPesquisa3)
{
    int encontrados = 0;
    struct dados pessoas;
    FILE *arquivo;

    arquivo = fopen("dados.txt", "r");
    fread(&pessoas, sizeof(pessoas), 1, arquivo);

    while (!feof(arquivo))
    {
        if (strcasecmp(pessoas.gosto3, gostoPesquisa3) == 0)
        {
            printf("\nNome: %s\n", pessoas.nome);
            printf("Data de nascimento: %s\n", pessoas.dataNascimento);
            printf("Telefone: %s\n", pessoas.telefone);
            printf("Cidade: %s\n", pessoas.cidade);
            printf("\n");
            encontrados++; // define se ha usuarios encontrados
        }
        fread(&pessoas, sizeof(pessoas), 1, arquivo);
    }
    if (encontrados == 0)
    {
        printf("\nNenhuma pessoa encontrada com o gosto desejado.\n");
    }

    fclose(arquivo);
}

void pesquisarPorGosto4(char *gostoPesquisa4)
{
    int encontrados = 0;
    struct dados pessoas;
    FILE *arquivo;

    arquivo = fopen("dados.txt", "r");
    fread(&pessoas, sizeof(pessoas), 1, arquivo);

    while (!feof(arquivo))
    {
        if (strcasecmp(pessoas.gosto4, gostoPesquisa4) == 0)
        {
            printf("\nNome: %s\n", pessoas.nome);
            printf("Data de nascimento: %s\n", pessoas.dataNascimento);
            printf("Telefone: %s\n", pessoas.telefone);
            printf("Cidade: %s\n", pessoas.cidade);
            printf("\n");
            encontrados++; // define se ha usuarios encontrados
        }

        fread(&pessoas, sizeof(pessoas), 1, arquivo);
    }
    if (encontrados == 0)
    {
        printf("\nNenhuma pessoa encontrada com o gosto desejado.\n");
    }

    fclose(arquivo);
}
int main()
{
    struct dados pessoas, usuarioAtual;
    int escolha;
    int opcao_pesq;
    char cidadePesquisa[50];
    char gostoPesquisa[50];
    char gostoPesquisa2[50];
    char gostoPesquisa3[50];
    char gostoPesquisa4[50];
    int opcao1 = 0, opcao2 = 0, opcao3 = 0, opcao4 = 0;
    int x, y, z, s, i, l, pnts;
    char nomePesquisa[100]; // nome do usuario para pesquisa
    char nomePesquisa_nome[100]; // nome do usuario para pesquisa por nome
    FILE *arquivo;
    FILE *arquivo1;
    int totalmat_pesquisa, totalmat_usuario, encontrada = 0;
    float compatibilidade;

    do
    {
        printf("\n******************TINBERATO*******************\n\n");
        printf("\nO que voce deseja fazer?\n");
        printf("1. Realizar o cadastro\n");
        printf("2. Prosseguir com o teste de compatibilidade com usuario especifico\n");
        printf("3. Prosseguir com o teste de compatibilidade com todos os usuarios\n");
        printf("4. Realizar pesquisa\n");
        printf("5. Pesquisar usuario por nome\n");
        printf("6. Sair\n");
        printf("Digite a sua escolha: ");
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 1:

            fflush(stdin);
            printf("\nNome completo: ");
            gets(pessoas.nome);

            fflush(stdin);
            printf("\nData de nascimento (formato: DD/MM/AAAA): ");
            gets(pessoas.dataNascimento);

            do
            {
                printf("\nGenero:\n");
                printf("1 - Feminino\n");
                printf("2 - Masculino\n");
                printf("3 - Outro\n");
                printf("4 - Prefiro nao informar\n");
                scanf("%d", &pessoas.genero);
                getchar();
            }
            while(pessoas.genero < 1 || pessoas.genero > 4); //limita o usuario a respponder apenas as opcoes

            fflush(stdin);
            printf("\nTelefone: ");
            gets(pessoas.telefone);

            fflush(stdin);
            printf("\nCidade: ");
            gets(pessoas.cidade);

            printf("\nOnde/como voce prefere aproveitar o final de semana? \n");
            printf("Viajando\n");
            printf("Em casa\n");
            printf("Praia\n");
            printf("Museu\n");
            printf("Biblioteca\n");
            printf("Quantas opcoes voce deseja escolher? ");
            scanf("%d", &opcao1);

            if (opcao1 >= 1 && opcao1 <= 5)
            {
                pessoas.numMat1 = opcao1;

                for (z = 0; z < opcao1; z++)
                {
                    fflush(stdin);
                    printf("Digite a opcao %d:", z+1);
                    gets(pessoas.gosto1[z]);
                }
            }

            fflush(stdin);
            printf("\nDigite o(s) melhor/melhores genero(s) de filme: ");
            printf("\nAcao\n");
            printf("Terror\n");
            printf("Ficcao cientifica\n");
            printf("Drama\n");
            printf("Comedia\n");
            printf("Romance\n");
            printf("Trash\n");
            printf("Quantas opcoes voce deseja escolher? ");
            scanf("%d", &opcao2);

            if (opcao2 >= 1 && opcao2 <= 7)
            {
                pessoas.numMat2 = opcao2;

                for (x = 0; x < opcao2; x++)
                {
                    fflush(stdin);
                    printf("Digite a opcao %d:", x+1);
                    gets(pessoas.gosto2[x]);
                }
            }

            printf("\nSeu(s) hobby/hobbies: ");
            printf("\nLeitura\n");
            printf("Escutar musica\n");
            printf("Praticar esportes\n");
            printf("Cozinhar\n");
            printf("Quantas opcoes voce deseja escolher? ");
            scanf("%d", &opcao3);

            if (opcao3 >= 1 && opcao3 <= 5)
            {
                pessoas.numMat3 = opcao3;

                for (y = 0; y < opcao3; y++)
                {
                    fflush(stdin);
                    printf("Digite a opcao %d:", y+1);
                    gets(pessoas.gosto3[y]);
                }
            }

            printf("\nDate perfeito: ");
            printf("\nJantar\n");
            printf("Piquenique\n");
            printf("Cinema\n");
            printf("Barzinho\n");
            printf("Quantas opcoes voce deseja escolher? ");
            scanf("%d", &opcao4);

            if (opcao4 >= 1 && opcao4 <= 4)
            {
                pessoas.numMat4 = opcao4;

                for (s = 0; s < opcao4; s++)
                {
                    fflush(stdin);
                    printf("Digite a opcao %d:", s+1);
                    gets(pessoas.gosto4[s]);

                }
            }

            arquivo = fopen("dados.txt", "a+t");
            fwrite(&pessoas, sizeof(pessoas), 1, arquivo);
            fclose(arquivo);
            break;
        case 2:
            printf("\nDigite o seu nome para pesquisa de compatibilidade: ");
            fflush(stdin);
            gets(nomePesquisa);
            calcularCompatibilidadeComUsuario(nomePesquisa);
            break;
        case 3:
            arquivo = fopen("dados.txt", "r");
            fread(&usuarioAtual, sizeof(usuarioAtual), 1, arquivo);

            while (fread(&usuarioAtual, sizeof(usuarioAtual), 1, arquivo)==1)
            {
                compatibilidade = 0;
                pnts = 0;
                arquivo1 = fopen("dados.txt", "r");

                while (fread(&pessoas, sizeof(pessoas), 1, arquivo1)==1)
                {
                    if (strcasecmp(pessoas.nome, usuarioAtual.nome) != 0)
                    {
                        pnts = 0; // Reinicia os pontos para cada pessoa comparada
                        encontrada++;

                        for (i = 0; i < usuarioAtual.numMat1; i++)
                        {
                            for (l = 0; l < pessoas.numMat1; l++)
                            {
                                if (strcasecmp(usuarioAtual.gosto1[i], pessoas.gosto1[l]) == 0)
                                {
                                    pnts++;
                                }
                            }
                        }

                        for (i = 0; i < usuarioAtual.numMat2; i++)
                        {
                            for (l = 0; l < pessoas.numMat2; l++)
                            {
                                if (strcasecmp(usuarioAtual.gosto2[i], pessoas.gosto2[l]) == 0)
                                {
                                    pnts++;
                                }
                            }
                        }

                        for (i = 0; i < usuarioAtual.numMat3; i++)
                        {
                            for (l = 0; l < pessoas.numMat3; l++)
                            {
                                if (strcasecmp(usuarioAtual.gosto3[i], pessoas.gosto3[l]) == 0)
                                {
                                    pnts++;
                                }
                            }
                        }

                        for (i = 0; i < usuarioAtual.numMat4; i++)
                        {
                            for (l = 0; l < pessoas.numMat4; l++)
                            {
                                if (strcasecmp(usuarioAtual.gosto4[i], pessoas.gosto4[l]) == 0)
                                {
                                    pnts++;
                                }
                            }
                        }

                        totalmat_pesquisa = (usuarioAtual.numMat1 + usuarioAtual.numMat2 + usuarioAtual.numMat3 + usuarioAtual.numMat4);
                        totalmat_usuario = (pessoas.numMat1 + pessoas.numMat2 + pessoas.numMat3 + pessoas.numMat4);

                        compatibilidade = (pnts * 200.0) / (totalmat_pesquisa + totalmat_usuario);

                        printf("\nCompatibilidade de %s com %s eh %.2f\n", usuarioAtual, pessoas.nome, compatibilidade);
                    }
                }
                fseek(arquivo1, 0, SEEK_CUR);
            }
            fclose(arquivo1);
            fclose(arquivo);

            if(encontrada==0)
            {
                printf("\nEsse usuario nao esta cadastrado\n");
            }
            break;
        case 4:
            do
            {
                printf("\nEscolha o criterio de pesquisa: ");
                printf("\n1. Cidade\n");
                printf("2. Final de Semana\n");
                printf("3. Genero de filme\n");
                printf("4. Hobby\n");
                printf("5. Date\n");
                printf("6. Voltar ao menu principal\n");
                printf("Digite a opcao: ");
                scanf("%d", &opcao_pesq);
                printf("\n");

                switch (opcao_pesq)
                {
                case 1:
                    pesquisarPorCidade(cidadePesquisa);
                    break;
                case 2:
                    printf("Escolha entre as opcoes: ");
                    printf("\nViajando\n");
                    printf("Em casa\n");
                    printf("Praia\n");
                    printf("Museu\n");
                    printf("Biblioteca\n");
                    fflush(stdin);
                    printf("Digite a preferencia de final de semana para pesquisa: ");
                    gets(gostoPesquisa);
                    pesquisarPorGosto1(gostoPesquisa);
                    break;
                case 3:
                    printf("Escolha entre as opcoes: ");
                    printf("\nAcao\n");
                    printf("Terror\n");
                    printf("Ficcao cientifica\n");
                    printf("Drama\n");
                    printf("Comedia\n");
                    printf("Romance\n");
                    printf("Trash\n");
                    printf("Digite a preferencia de genero de filme para pesquisa: ");
                    fflush(stdin);
                    gets(gostoPesquisa2);
                    pesquisarPorGosto2(gostoPesquisa2);
                    break;
                case 4:
                    printf("Escolha entre as opcoes: ");
                    printf("\nLeitura\n");
                    printf("Escutar musica\n");
                    printf("Praticar esportes\n");
                    printf("Cozinhar\n");
                    fflush(stdin);
                    printf("Digite a preferencia de hobby para pesquisa: ");
                    gets(gostoPesquisa3);
                    pesquisarPorGosto3(gostoPesquisa3);
                    break;
                case 5:
                    printf("Escolha entre as opcoes: ");
                    printf("\nDate perfeito: \n");
                    printf("Jantar\n");
                    printf("Piquenique\n");
                    printf("Cinema\n");
                    printf("Barzinho\n");
                    fflush(stdin);
                    printf("Digite a preferencia de date para pesquisa: ");
                    gets(gostoPesquisa4);
                    pesquisarPorGosto4(gostoPesquisa4);
                    break;
                case 6:
                    break;
                default:
                    printf("Opcao invalida\n");
                }
            }
            while (opcao_pesq != 6);
            break;
        case 5:
            printf("\nDigite o nome do usuario: ");
            fflush(stdin);
            gets(nomePesquisa_nome);
            pesquisaPorNome(nomePesquisa_nome);
            break;
        case 6:
            printf("Saindo do programa...\n");
            break;
        default:
            printf("Opcao invalida\n");
        }
    }
    while (escolha != 5);

    return 0;
}
