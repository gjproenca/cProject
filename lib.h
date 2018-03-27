#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include <dirent.h>

//TODO_FIX: fix desesja inserir um novo registo com a posibilidade de se inserir outros carateres que nao sejan sim ou nao

typedef struct
{
    int IDPraia;
    char Nome[201];
    char Tipo[10];
    char Localidade[201];
    int IDLocalidade;
} Praia;

typedef struct
{
    int IDLocalidade;
    char Nome[201];
} Localidade;

void clrm()
{
    char c;
    do
    {
        c = getchar();
    }
    while (c != '\n' && c != EOF);
}

int strcmpCase(char *str1,char *str2)
{
    int i;
    char s1[strlen(str1)],s2[strlen(str2)];
    strcpy(s1,str1);
    strcpy(s2,str2);
    for(i=0; s1[i]; i++) s1[i]=toupper(s1[i]);
    for(i=0; s2[i]; i++) s2[i]=toupper(s2[i]);
    return strcmp(s1,s2);
}

int substrCase(char *str1,char *str2)
{
    int i;
    char s1[strlen(str1)],s2[strlen(str2)];

    strcpy(s1,str1);
    strcpy(s2,str2);

    for(i=0; s1[i]; i++) s1[i]=toupper(s1[i]);
    for(i=0; s2[i]; i++) s2[i]=toupper(s2[i]);

    if (strstr(s1,s2)==NULL)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void firstLetterUpper(char *ipt)
{
    for(int i=0; i<strlen(ipt); i++)
    {
        ipt[i]=tolower(ipt[i]);

        if(i==0 || (ipt[i-1]==' ' && ipt[i+1]!=' '))
        {
            ipt[i]=toupper(ipt[i]);
        }
    }
}

void LimparFicheiros()
{
    FILE *ficheiro;
    DIR* dir = opendir("./dados");

    if (dir)
    {
        /* Directory exists. */
        closedir(dir);
    }
    else
    {
        /* Directory does not exist. */
        puts("\nPasta Dados não existente, foi criada a pasta!");
        system("mkdir ./dados");
        closedir(dir);
    }

    dir = opendir("./export");

    if (dir)
    {
        /* Directory exists. */
        closedir(dir);
    }
    else
    {
        /* Directory does not exist. */
        puts("\nPasta Export não existente, foi criada a pasta!");
        system("mkdir ./export");
        closedir(dir);
    }

    ficheiro = fopen("./dados/Praias.dat","w");
    fclose(ficheiro);

    ficheiro = fopen("./dados/Localidades.dat","w");
    fclose(ficheiro);

    ficheiro = fopen("./dados/ContadorPraias.dat","w");
    fclose(ficheiro);

    ficheiro = fopen("./dados/ContadorLocalidades.dat","w");
    fclose(ficheiro);

    ficheiro = fopen("./export/Praias.csv","w");
    fclose(ficheiro);

    ficheiro = fopen("./export/Localidades.csv","w");
    fclose(ficheiro);

    ficheiro = fopen("./export/Praias.txt","w");
    fclose(ficheiro);

    ficheiro = fopen("./export/Localidades.txt","w");
    fclose(ficheiro);

    printf("\nFicheiro(s) inicializado(s) com sucesso!\n\nEnter para continuar...");
    getchar();

    return;
}

void InicializarFicheiros()
{
    FILE *ficheiro;
    DIR* dir = opendir("./dados");

    if (dir)
    {
        /* Directory exists. */
        closedir(dir);
    }
    else
    {
        /* Directory does not exist. */
        system("mkdir ./dados");
        closedir(dir);
    }

    dir = opendir("./export");

    if (dir)
    {
        /* Directory exists. */
        closedir(dir);
    }
    else
    {
        /* Directory does not exist. */
        system("mkdir ./export");
        closedir(dir);
    }

    ficheiro = fopen("./dados/Praias.dat","a");
    fclose(ficheiro);

    ficheiro = fopen("./dados/Localidades.dat","a");
    fclose(ficheiro);

    ficheiro = fopen("./dados/ContadorPraias.dat","a");
    fclose(ficheiro);

    ficheiro = fopen("./dados/ContadorLocalidades.dat","a");
    fclose(ficheiro);

    ficheiro = fopen("./export/Praias.csv","a");
    fclose(ficheiro);

    ficheiro = fopen("./export/Localidades.csv","a");
    fclose(ficheiro);

    ficheiro = fopen("./export/Praias.txt","a");
    fclose(ficheiro);

    ficheiro = fopen("./export/Localidades.txt","a");
    fclose(ficheiro);

    return;
}

int ContadorPraias(void)
{
    FILE *contador;
    int cont=0;
    contador = fopen("./dados/ContadorPraias.dat","r+");
    if(contador==NULL)
    {
        LimparFicheiros();
        contador = fopen("./dados/ContadorPraias.dat","r+");
    }
    if(contador!=NULL)
    {
        fread(&cont,sizeof(int),1,contador);
        cont++;
        rewind(contador);
        fwrite(&cont,sizeof(int),1,contador);
        fclose(contador);
    }
    return cont;
}

int ContadorLocalidades(void)
{
    FILE *contador;
    int cont=0;
    contador = fopen("./dados/ContadorLocalidades.dat","r+");
    if(contador==NULL)
    {
        LimparFicheiros();
        contador = fopen("./dados/ContadorLocalidades.dat","r+");
    }
    if(contador!=NULL)
    {
        fread(&cont,sizeof(int),1,contador);
        cont++;
        rewind(contador);
        fwrite(&cont,sizeof(int),1,contador);
        fclose(contador);
    }
    return cont;
}

int VerificarExistenciaPraia(char *nomePraia, char *nomeLocalidade)
{
    FILE *ficheiroPraia;
    Praia tempPraia;
    ficheiroPraia = fopen("./dados/Praias.dat","r");

    while (fread(&tempPraia,sizeof(Praia),1,ficheiroPraia)==1)
    {
        if(strcmpCase(tempPraia.Nome, nomePraia) == 0 && strcmpCase(tempPraia.Localidade, nomeLocalidade) == 0)
        {
            fclose(ficheiroPraia);
            return 1;
        }
    }
    fclose(ficheiroPraia);
    return 0;
}

int VerificarExistenciaLocalidade(char *nomeLocalidade)
{
    FILE *ficheiroLocalidade;
    Localidade tempLocalidade;
    ficheiroLocalidade = fopen("./dados/Localidades.dat","r");

    while (fread(&tempLocalidade,sizeof(Localidade),1,ficheiroLocalidade)==1)
    {
        if(strcmpCase(tempLocalidade.Nome, nomeLocalidade) == 0)
        {
            fclose(ficheiroLocalidade);
            return 1;
        }
    }
    fclose(ficheiroLocalidade);
    return 0;
}

void InserirLocalidade()
{
    FILE *ficheiro;
    Localidade temp;
    char option[2];
    fpos_t posicao;
    ficheiro = fopen("./dados/Localidades.dat","a");

    do
    {
        system("clear");

        do
        {
            memset(temp.Nome,'\0', sizeof(temp.Nome));
            printf("Nome: ");
            scanf("%200[^\n]",temp.Nome);
            clrm();
        }
        while(temp.Nome[0]=='\0');
        firstLetterUpper(temp.Nome);

        fgetpos(ficheiro,&posicao);
        rewind(ficheiro);

        if(VerificarExistenciaLocalidade(temp.Nome))
        {
            fsetpos(ficheiro,&posicao);
            puts("Localidade já existente");
        }
        else
        {
            fsetpos(ficheiro,&posicao);
            temp.IDLocalidade=ContadorLocalidades();
            printf("ID Localidade: %d\n",temp.IDLocalidade);

            fwrite(&temp,sizeof(Localidade),1,ficheiro);
        }

        do
        {
            memset(option,'\0', sizeof(option));
            printf("\nDeseja inserir um novo registo (S/N)? ");
            scanf("%s",option);
            clrm();
        }
        while(toupper((option[0])!='S'||toupper(option[0])!='N')&&strlen(option)!=1);
    }
    while(toupper(option[0])=='S');

    fclose(ficheiro);

    return;
}

void RegistarLocalidade(char *localidade)
{
    FILE *ficheiro;
    Localidade temp;
    ficheiro = fopen("./dados/Localidades.dat","a");

    temp.IDLocalidade=ContadorLocalidades();
    strcpy(temp.Nome, localidade);

    fwrite(&temp,sizeof(Localidade),1,ficheiro);

    fclose(ficheiro);

    return;
}

int EncontrarIDLocalidade(char *nomeLocalidade)
{
    FILE *ficheiroLocalidade;
    Localidade tempLocalidade;
    int contIDLocalidade=1;
    int IDLocalidade;
    ficheiroLocalidade = fopen("./dados/Localidades.dat","r");

    while (fread(&tempLocalidade,sizeof(Localidade),1,ficheiroLocalidade)==1)
    {
        if(strcmpCase(tempLocalidade.Nome, nomeLocalidade) == 0)
        {
            IDLocalidade=contIDLocalidade;
        }
        contIDLocalidade++;
    }

    fclose(ficheiroLocalidade);
    return IDLocalidade;
}

void InserirPraia()
{
    FILE *ficheiro;
    Praia temp;
    int tempIntTipo;
    char option[2];
    fpos_t posicao;
    ficheiro = fopen("./dados/Praias.dat","a");

    do
    {
        system("clear");

        do
        {
            memset(temp.Nome,'\0', sizeof(temp.Nome));
            printf("Nome: ");
            scanf("%200[^\n]",temp.Nome);
            clrm();
        }
        while(temp.Nome[0]=='\0');
        firstLetterUpper(temp.Nome);

        do
        {
            printf("Tipo (1 - Oceânica, 2 - Fluvial): ");
            scanf("%d",&tempIntTipo);
            clrm();
        }
        while(tempIntTipo != 1 && tempIntTipo != 2);

        strcpy(temp.Tipo,tempIntTipo==1?"Oceânica":"Fluvial");

        do
        {
            memset(temp.Localidade,'\0', sizeof(temp.Localidade));
            printf("Localidade: ");
            scanf("%200[^\n]",temp.Localidade);
            clrm();
        }
        while(temp.Localidade[0]=='\0');
        firstLetterUpper(temp.Localidade);

        fgetpos(ficheiro,&posicao);
        rewind(ficheiro);

        if(!VerificarExistenciaLocalidade(temp.Localidade))
        {
            RegistarLocalidade(temp.Localidade);

            puts("Localidade não existente, foi criado um novo registo em Localidades!");
        }

        if(VerificarExistenciaPraia(temp.Nome, temp.Localidade))
        {
            fsetpos(ficheiro,&posicao);
            puts("Praia já existente!");
        }
        else
        {
            fsetpos(ficheiro,&posicao);

            temp.IDLocalidade = EncontrarIDLocalidade(temp.Localidade);
            printf("ID Localidade: %d\n", temp.IDLocalidade);

            temp.IDPraia = ContadorPraias();
            printf("ID Praia: %d\n",temp.IDPraia);

            fwrite(&temp,sizeof(Praia),1,ficheiro);
        }

        do
        {
            memset(option,'\0', sizeof(option));
            printf("\nDeseja inserir um novo registo (S/N)? ");
            scanf("%s",option);
            clrm();
        }
        while(toupper((option[0])!='S'||toupper(option[0])!='N')&&strlen(option)!=1);
    }
    while(toupper(option[0])=='S');

    fclose(ficheiro);

    return;
}

int VerificarEsxistenciaDados(FILE *ficheiro)
{
    int c = fgetc(ficheiro);

    if (c == EOF)
    {
        return 0;
    }
    else
    {
        ungetc(c, ficheiro);
        return 1;
    }
}

void ListarPraiasOption()
{
    FILE *ficheiro;
    Praia temp;
    int cont=0;
    ficheiro = fopen("./dados/Praias.dat","r");

    if(ficheiro==NULL)
    {
        LimparFicheiros();
        return;
    }

    system("clear");

    while (fread(&temp,sizeof(Praia),1,ficheiro)==1)
    {
        cont==0?cont=1:putchar('\n');
        printf("Nome: %s\n",temp.Nome);
        printf("Tipo: %s\n",temp.Tipo);
        printf("Localidade: %s\n",temp.Localidade);
        printf("ID Localidade: %d\n",temp.IDLocalidade);
        printf("ID Praia: %d\n",temp.IDPraia);
    }

    fclose(ficheiro);

    return;
}

void ListarPraias()
{
    FILE *ficheiro;
    Praia temp;
    char option[2];
    int cont=0;
    ficheiro = fopen("./dados/Praias.dat","r");

    if(ficheiro==NULL)
    {
        LimparFicheiros();
        return;
    }

    system("clear");

    if(!VerificarEsxistenciaDados(ficheiro))
    {
        printf("Ficheiro sem registos!\n");

        do
        {
            memset(option,'\0', sizeof(option));
            printf("\nDeseja inserir um novo registo (S/N)? ");
            scanf("%s",option);
            clrm();
        }
        while(toupper((option[0])!='S'||toupper(option[0])!='N')&&strlen(option)!=1);

        if(toupper(option[0])=='S')
        {
            InserirPraia();

            do
            {
                memset(option,'\0', sizeof(option));
                printf("\nAinda quer listar a(s) Praia(s) (S/N)? ");
                scanf("%s",option);
                clrm();
            }
            while(toupper((option[0])!='S'||toupper(option[0])!='N')&&strlen(option)!=1);
        }

        if(toupper(option[0])=='S')ListarPraiasOption();
    }
    else
    {
        while (fread(&temp,sizeof(Praia),1,ficheiro)==1)
        {
            cont==0?cont=1:putchar('\n');
            printf("Nome: %s\n",temp.Nome);
            printf("Tipo: %s\n",temp.Tipo);
            printf("Localidade: %s\n",temp.Localidade);
            printf("ID Localidade: %d\n",temp.IDLocalidade);
            printf("ID Praia: %d\n",temp.IDPraia);
        }
    }

    fclose(ficheiro);

    printf("\nPressione Enter para continuar...");
    getchar();

    return;
}

void ListarLocalidadesOption()
{
    FILE *ficheiro;
    Localidade temp;
    int cont=0;
    ficheiro = fopen("./dados/Localidades.dat","r");

    if(ficheiro==NULL)
    {
        LimparFicheiros();
        return;
    }

    system("clear");

    while (fread(&temp,sizeof(Localidade),1,ficheiro)==1)
    {
        cont==0?cont=1:putchar('\n');
        printf("ID Localidade: %d\n",temp.IDLocalidade);
        printf("Nome: %s\n",temp.Nome);
    }

    fclose(ficheiro);

    return;
}

void ListarLocalidades()
{
    FILE *ficheiro;
    Localidade temp;
    char option[2];
    int cont=0;
    ficheiro = fopen("./dados/Localidades.dat","r");

    if(ficheiro==NULL)
    {
        LimparFicheiros();
        return;
    }

    system("clear");

    if(!VerificarEsxistenciaDados(ficheiro))
    {
        printf("Ficheiro sem registos!\n");

        do
        {
            memset(option,'\0', sizeof(option));
            printf("\nDeseja inserir um novo registo (S/N)? ");
            scanf("%s",option);
            clrm();
        }
        while(toupper((option[0])!='S'||toupper(option[0])!='N')&&strlen(option)!=1);

        if(toupper(option[0])=='S')
        {
            InserirLocalidade();

            do
            {
                memset(option,'\0', sizeof(option));
                printf("\nAinda quer listar a(s) Localidade(s) (S/N)? ");
                scanf("%s",option);
                clrm();
            }
            while(toupper((option[0])!='S'||toupper(option[0])!='N')&&strlen(option)!=1);
        }
        if(toupper(option[0])=='S')ListarLocalidadesOption();
    }
    else
    {
        while (fread(&temp,sizeof(Localidade),1,ficheiro)==1)
        {
            cont==0?cont=1:putchar('\n');
            printf("ID Localidade: %d\n",temp.IDLocalidade);
            printf("Nome: %s\n",temp.Nome);
        }
    }
    fclose(ficheiro);

    printf("\nPressione Enter para continuar...");
    getchar();

    return;
}

void ListarPraiasLocalidadeOption()
{
    FILE *ficheiro;
    Praia temp;
    int tempInputID;
    int booleanID=0;
    ficheiro = fopen("./dados/Praias.dat","r");

    if(ficheiro==NULL)
    {
        LimparFicheiros();
        return;
    }

    system("clear");

    printf("Insira o ID da Localidade: ");
    scanf("%d",&tempInputID);
    clrm();

    while (fread(&temp,sizeof(Praia),1,ficheiro)==1)
    {
        if(tempInputID==temp.IDLocalidade)
        {
            putchar('\n');
            printf("ID Praia: %d\n",temp.IDPraia);
            printf("Nome: %s\n",temp.Nome);
            printf("Tipo: %s\n",temp.Tipo);
            printf("Localidade: %s\n",temp.Localidade);
            printf("ID Localidade: %d\n",temp.IDLocalidade);

            booleanID=1;
        }
    }

    if(!booleanID) printf("\nNão existem Praias com este ID!\n");

    fclose(ficheiro);

    return;
}

void ListarPraiasLocalidade()
{
    FILE *ficheiro;
    Praia temp;
    int tempInputID;
    int booleanID=0;
    char option[2];
    ficheiro = fopen("./dados/Praias.dat","r");

    if(ficheiro==NULL)
    {
        LimparFicheiros();
        return;
    }

    system("clear");

    if(!VerificarEsxistenciaDados(ficheiro))
    {
        printf("Ficheiro sem registos!\n");

        do
        {
            memset(option,'\0', sizeof(option));
            printf("\nDeseja inserir um novo registo (S/N)? ");
            scanf("%s",option);
            clrm();
        }
        while(toupper((option[0])!='S'||toupper(option[0])!='N')&&strlen(option)!=1);

        if(toupper(option[0])=='S')
        {
            InserirPraia();

            do
            {
                memset(option,'\0', sizeof(option));
                printf("\nAinda quer listar a(s) Praias(s) por ID (S/N)? ");
                scanf("%s",option);
                clrm();
            }
            while(toupper((option[0])!='S'||toupper(option[0])!='N')&&strlen(option)!=1);
        }

        if(toupper(option[0])=='S')ListarPraiasLocalidadeOption();
    }
    else
    {
        printf("Insira o ID da Localidade: ");
        scanf("%d",&tempInputID);
        clrm();

        while (fread(&temp,sizeof(Praia),1,ficheiro)==1)
        {
            if(tempInputID==temp.IDLocalidade)
            {
                putchar('\n');
                printf("ID Praia: %d\n",temp.IDPraia);
                printf("Nome: %s\n",temp.Nome);
                printf("Tipo: %s\n",temp.Tipo);
                printf("Localidade: %s\n",temp.Localidade);
                printf("ID Localidade: %d\n",temp.IDLocalidade);

                booleanID=1;
            }
        }
        if(!booleanID) printf("\nNão existem Praias com este ID!\n");
    }

    fclose(ficheiro);

    printf("\nPressione Enter para continuar...");
    getchar();

    return;
}

void ProcurarPraiaOption()
{
    FILE *ficheiro;
    Praia temp;
    char tempInputNome[201];
    int booleanFound=0;
    ficheiro = fopen("./dados/Praias.dat","r");

    if(ficheiro==NULL)
    {
        LimparFicheiros();
        return;
    }

    system("clear");

    do
    {
        memset(tempInputNome,'\0', sizeof(tempInputNome));
        printf("Insira o nome da Praia a procurar: ");
        scanf("%200[^\n]",tempInputNome);
        clrm();
    }
    while(tempInputNome=='\0');

    while (fread(&temp,sizeof(Praia),1,ficheiro)==1)
    {
        if(strcmpCase(tempInputNome,temp.Nome) == 0)
        {
            putchar('\n');
            printf("ID Praia: %d\n",temp.IDPraia);
            printf("Nome: %s\n",temp.Nome);
            printf("Tipo: %s\n",temp.Tipo);
            printf("Localidade: %s\n",temp.Localidade);
            printf("ID Localidade: %d\n",temp.IDLocalidade);
            booleanFound=1;
        }
    }

    if(!booleanFound)puts("\nNão existem registos com este Nome!");

    fclose(ficheiro);

    return;
}

void ProcurarPraia()
{
    FILE *ficheiro;
    Praia temp;
    char option[2];
    char tempInputNome[201];
    int booleanFound=0;
    ficheiro = fopen("./dados/Praias.dat","r");

    if(ficheiro==NULL)
    {
        LimparFicheiros();
        return;
    }

    system("clear");


    if(!VerificarEsxistenciaDados(ficheiro))
    {
        printf("Ficheiro sem registos!\n");

        do
        {
            memset(option,'\0', sizeof(option));
            printf("\nDeseja inserir um novo registo (S/N)? ");
            scanf("%s",option);
            clrm();
        }
        while(toupper((option[0])!='S'||toupper(option[0])!='N')&&strlen(option)!=1);

        if(toupper(option[0])=='S')
        {
            InserirPraia();

            do
            {
                memset(option,'\0', sizeof(option));
                printf("\nAinda quer listar a(s) Praias(s) por Nome (S/N)? ");
                scanf("%s",option);
                clrm();
            }
            while(toupper((option[0])!='S'||toupper(option[0])!='N')&&strlen(option)!=1);
        }
        if(toupper(option[0])=='S')ProcurarPraiaOption();
    }
    else
    {
        do
        {
            memset(tempInputNome,'\0', sizeof(tempInputNome));
            printf("Insira o nome da Praia a procurar: ");
            scanf("%200[^\n]",tempInputNome);
            clrm();
        }
        while(tempInputNome[0]=='\0');

        while (fread(&temp,sizeof(Praia),1,ficheiro)==1)
        {
            if(strcmpCase(tempInputNome,temp.Nome) == 0)
            {
                putchar('\n');
                printf("ID Praia: %d\n",temp.IDPraia);
                printf("Nome: %s\n",temp.Nome);
                printf("Tipo: %s\n",temp.Tipo);
                printf("Localidade: %s\n",temp.Localidade);
                printf("ID Localidade: %d\n",temp.IDLocalidade);
                booleanFound=1;
            }
        }
    }

    if(!booleanFound) puts("\nNão existem registos com este Nome!");

    fclose(ficheiro);

    printf("\nPressione Enter para continuar...");
    getchar();

    return;
}

void AlterarPraiaOption()
{
    FILE *ficheiro;
    Praia temp;
    int IDPraia;
    int tempIntTipo;
    char option[2];
    fpos_t posicao;
    ficheiro = fopen("./dados/Praias.dat","r+");

    system("clear");

    printf("Insira o ID da praia a alterar: ");
    scanf("%d",&IDPraia);
    clrm();

    fgetpos(ficheiro,&posicao);

    while (fread(&temp,sizeof(Praia),1,ficheiro)==1)
    {
        if(IDPraia==temp.IDPraia)
        {
            putchar('\n');
            printf("ID Praia: %d\n",temp.IDPraia);
            printf("Nome: %s\n",temp.Nome);
            printf("Tipo: %s\n",temp.Tipo);
            printf("Localidade: %s\n",temp.Localidade);
            printf("ID Localidade: %d\n",temp.IDLocalidade);

            do
            {
                memset(option,'\0', sizeof(option));
                printf("\nTem a certeza que quer alterar este registo(S/N)? ");
                scanf("%s",option);
                clrm();
            }
            while(toupper((option[0])!='S'||toupper(option[0])!='N')&&strlen(option)!=1);

            if(toupper(option[0])=='S')
            {
                do
                {
                    memset(temp.Nome,'\0', sizeof(temp.Nome));
                    printf("Nome: ");
                    scanf("%200[^\n]",temp.Nome);
                    clrm();
                }
                while(temp.Nome[0]=='\0');
                firstLetterUpper(temp.Nome);

                do
                {
                    printf("Tipo (1 - Oceânica, 2 - Fluvial): ");
                    scanf("%d",&tempIntTipo);
                    clrm();
                }
                while(tempIntTipo != 1 && tempIntTipo != 2);

                strcpy(temp.Tipo,tempIntTipo==1?"Oceânica":"Fluvial");

                do
                {
                    memset(temp.Localidade,'\0', sizeof(temp.Localidade));
                    printf("Localidade: ");
                    scanf("%200[^\n]",temp.Localidade);
                    clrm();
                }
                while(temp.Localidade[0]=='\0');
                firstLetterUpper(temp.Localidade);

                if(!VerificarExistenciaLocalidade(temp.Localidade))
                {
                    RegistarLocalidade(temp.Localidade);

                    puts("Localidade não existente, foi criado um novo registo em Localidades!");

                    temp.IDLocalidade = EncontrarIDLocalidade(temp.Localidade);
                    printf("ID Localidade: %d\n", temp.IDLocalidade);
                }
                else
                {

                    temp.IDLocalidade = EncontrarIDLocalidade(temp.Localidade);
                    printf("ID Localidade: %d\n", temp.IDLocalidade);
                }

                printf("ID Praia: %d\n", temp.IDPraia);

                fsetpos(ficheiro,&posicao);
                fwrite(&temp,sizeof(Praia),1,ficheiro);
            }
        }
        fgetpos(ficheiro,&posicao);
    }

    fclose(ficheiro);

    return;
}

void AlterarPraia()
{
    FILE *ficheiro;
    Praia temp;
    int IDPraia;
    int tempIntTipo;
    char option[2];
    int booleanFound=0;
    fpos_t posicao;
    ficheiro = fopen("./dados/Praias.dat","r+");

    system("clear");

    fgetpos(ficheiro,&posicao);

    if(!VerificarEsxistenciaDados(ficheiro))
    {
        printf("Ficheiro sem registos!\n");

        do
        {
            memset(option,'\0', sizeof(option));
            printf("\nTem a certeza que quer alterar este registo(S/N)? ");
            scanf("%s",option);
            clrm();
        }
        while(toupper((option[0])!='S'||toupper(option[0])!='N')&&strlen(option)!=1);

        if(toupper(option[0])=='S')
        {
            InserirPraia();

            do
            {
                printf("\nAinda quer Alterar Praias(s) (S/N)? ");
                scanf("%s",option);
                clrm();
            }
            while(toupper((option[0])!='S'||toupper(option[0])!='N')&&strlen(option)!=1);
        }

        if(toupper(option[0])=='S')AlterarPraiaOption();
    }
    else
    {
        printf("Insira o ID da praia a alterar: ");
        scanf("%d",&IDPraia);
        clrm();

        while (fread(&temp,sizeof(Praia),1,ficheiro)==1)
        {
            if(IDPraia==temp.IDPraia)
            {
                putchar('\n');
                printf("Nome: %s\n",temp.Nome);
                printf("Tipo: %s\n",temp.Tipo);
                printf("Localidade: %s\n",temp.Localidade);
                printf("ID Praia: %d\n",temp.IDPraia);
                printf("ID Localidade: %d\n",temp.IDLocalidade);

                do
                {
                    memset(option,'\0', sizeof(option));
                    printf("\nTem a certeza que quer alterar este registo(S/N)? ");
                    scanf("%s",option);
                    clrm();
                }
                while(toupper((option[0])!='S'||toupper(option[0])!='N')&&strlen(option)!=1);

                if(toupper(option[0])=='S')
                {
                    do
                    {
                        memset(temp.Nome,'\0', sizeof(temp.Nome));
                        printf("Nome: ");
                        scanf("%200[^\n]",temp.Nome);
                        clrm();
                    }
                    while(temp.Nome[0]=='\0');
                    firstLetterUpper(temp.Nome);

                    do
                    {
                        printf("Tipo (1 - Oceânica, 2 - Fluvial): ");
                        scanf("%d",&tempIntTipo);
                        clrm();
                    }
                    while(tempIntTipo != 1 && tempIntTipo != 2);

                    strcpy(temp.Tipo,tempIntTipo==1?"Oceânica":"Fluvial");

                    do
                    {
                        memset(temp.Localidade,'\0', sizeof(temp.Localidade));
                        printf("Localidade: ");
                        scanf("%200[^\n]",temp.Localidade);
                        clrm();
                    }
                    while(temp.Localidade[0]=='\0');
                    firstLetterUpper(temp.Localidade);

                    if(!VerificarExistenciaLocalidade(temp.Localidade))
                    {
                        RegistarLocalidade(temp.Localidade);

                        puts("Localidade não existente, foi criado um novo registo em Localidades!");

                        temp.IDLocalidade = EncontrarIDLocalidade(temp.Localidade);
                        printf("ID Localidade: %d\n", temp.IDLocalidade);
                    }
                    else
                    {

                        temp.IDLocalidade = EncontrarIDLocalidade(temp.Localidade);
                        printf("ID Localidade: %d\n", temp.IDLocalidade);
                    }

                    printf("ID Praia: %d\n", temp.IDPraia);

                    fsetpos(ficheiro,&posicao);
                    fwrite(&temp,sizeof(Praia),1,ficheiro);

                    booleanFound=1;

                    break;
                }
            }

            fgetpos(ficheiro,&posicao);
        }

        if(!booleanFound && toupper(option[0])=='S')puts("\nNão existem registos com esta ID!");

    }

    fclose(ficheiro);

    printf("\nPressione Enter para continuar...");
    getchar();

    return;
}

void ExportarFicheirosCsv()
{
    DIR* dir = opendir("./export");
    if (dir)
    {
        /* Directory exists. */
        closedir(dir);
    }
    else
    {
        /* Directory does not exist. */
        puts("\nPasta Export não existente, foi criada a pasta!");
        system("mkdir ./export");
        closedir(dir);
    }

    FILE *ficheiroPraias=fopen("./dados/Praias.dat","r");
    FILE *ficheiroCsvPraias=fopen("./export/Praias.csv","w");
    FILE *ficheiroLocalidades=fopen("./dados/Localidades.dat","r");
    FILE *ficheiroCsvLocalidades=fopen("./export/Localidades.csv","w");
    Praia tempStructPraia;
    Localidade tempStructLocalidade;
    int tempIdLocalidadeLocalidade;
    char tempNomeLocalidade[200];
    int tempIdPraia;
    char tempNomePraia[200];
    char tempTipoPraia[10];
    char tempLocalidadePraia[200];
    int tempIdLocalidadePraia;

    fprintf(ficheiroCsvPraias,"ID Praia;Nome;Tipo;Localidade;ID Localidade\n");
    fprintf(ficheiroCsvLocalidades,"ID Localidade;Nome\n");

    while (fread(&tempStructPraia,sizeof(Praia),1,ficheiroPraias)==1)
    {
        tempIdPraia=tempStructPraia.IDPraia;
        strcpy(tempNomePraia,tempStructPraia.Nome);
        strcpy(tempTipoPraia,tempStructPraia.Tipo);
        strcpy(tempLocalidadePraia,tempStructPraia.Localidade);
        tempIdLocalidadePraia=tempStructPraia.IDLocalidade;

        fprintf(ficheiroCsvPraias,"%d;%s;%s;%s;%d\n",tempIdPraia,tempNomePraia,tempTipoPraia,tempLocalidadePraia,tempIdLocalidadePraia);
    }

    while (fread(&tempStructLocalidade,sizeof(Localidade),1,ficheiroLocalidades)==1)
    {
        tempIdLocalidadeLocalidade=tempStructLocalidade.IDLocalidade;
        strcpy(tempNomeLocalidade,tempStructLocalidade.Nome);

        fprintf(ficheiroCsvLocalidades,"%d;%s\n",tempIdLocalidadeLocalidade,tempNomeLocalidade);
    }

    //system("soffice --calc ./export/Praias.csv"); //fix this not opening corectly

    puts("\nFicheiros exportados com sucesso para a pasta Export!");
    puts("\nEnter para continuar...");
    getchar();

    fclose(ficheiroPraias);
    fclose(ficheiroCsvPraias);
    fclose(ficheiroLocalidades);
    fclose(ficheiroCsvLocalidades);

    return;
}

void ExportarFicheirosTxt()
{
    DIR* dir = opendir("./export");
    if (dir)
    {
        /* Directory exists. */
        closedir(dir);
    }
    else
    {
        /* Directory does not exist. */
        puts("\nPasta Export não existente, foi criada a pasta!");
        system("mkdir ./export");
        closedir(dir);
    }

    FILE *ficheiroPraias=fopen("./dados/Praias.dat","r");
    FILE *ficheiroCsvPraias=fopen("./export/Praias.txt","w");
    FILE *ficheiroLocalidades=fopen("./dados/Localidades.dat","r");
    FILE *ficheiroCsvLocalidades=fopen("./export/Localidades.txt","w");
    Praia tempStructPraia;
    Localidade tempStructLocalidade;
    int tempIdLocalidadeLocalidade;
    char tempNomeLocalidade[200];
    int tempIdPraia;
    char tempNomePraia[200];
    char tempTipoPraia[10];
    char tempLocalidadePraia[200];
    int tempIdLocalidadePraia;

    while (fread(&tempStructPraia,sizeof(Praia),1,ficheiroPraias)==1)
    {
        tempIdPraia=tempStructPraia.IDPraia;
        strcpy(tempNomePraia,tempStructPraia.Nome);
        strcpy(tempTipoPraia,tempStructPraia.Tipo);
        strcpy(tempLocalidadePraia,tempStructPraia.Localidade);
        tempIdLocalidadePraia=tempStructPraia.IDLocalidade;

        fprintf(ficheiroCsvPraias,"ID Praia: %d\nNome: %s\nTipo: %s\nLocalidade: %s\nID Localidade: %d\n\n",tempIdPraia,tempNomePraia,tempTipoPraia,tempLocalidadePraia,tempIdLocalidadePraia);
    }

    while (fread(&tempStructLocalidade,sizeof(Localidade),1,ficheiroLocalidades)==1)
    {
        tempIdLocalidadeLocalidade=tempStructLocalidade.IDLocalidade;
        strcpy(tempNomeLocalidade,tempStructLocalidade.Nome);

        fprintf(ficheiroCsvLocalidades,"ID Localidade: %d\nNome: %s\n\n",tempIdLocalidadeLocalidade,tempNomeLocalidade);
    }

    puts("\nFicheiros exportados com sucesso para a pasta Export!");
    puts("\nEnter para continuar...");
    getchar();

    fclose(ficheiroPraias);
    fclose(ficheiroCsvPraias);
    fclose(ficheiroLocalidades);
    fclose(ficheiroCsvLocalidades);

    return;
}
