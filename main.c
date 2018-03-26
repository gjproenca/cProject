#include "lib.h"

int main()
{
    int option;

    do
    {
        InicializarFicheiros();

        option=-1;

        system("clear");

        puts("1 - Inserir Praia");
        puts("2 - Inserir Localidade");
        puts("3 - Listar Praias");
        puts("4 - Listar Localidades");
        puts("5 - Listar Praias por Localidade");
        puts("6 - Procurar Praia");
        puts("7 - Alterar Praia");
        puts("8 - Exportar ficheiros para Csv");
        puts("9 - Exportar ficheiros para Txt");
        puts("10 - Inicializar todos os ficheiros");
        puts("0 - Sair");

        printf("\nOpção: ");
        scanf("%d",&option);
        clrm();

        switch(option)
        {
        case 1:
            InserirPraia();
            break;
        case 2:
            InserirLocalidade();
            break;
        case 3:
            ListarPraias();
            break;
        case 4:
            ListarLocalidades();
            break;
        case 5:
            ListarPraiasLocalidade();
            break;
        case 6:
            ProcurarPraia();
            break;
        case 7:
            AlterarPraia();
            break;
        case 8:
            ExportarFicheirosCsv();
            break;
        case 9:
            ExportarFicheirosTxt();
            break;
        case 10:
            LimparFicheiros();
            break;
        }
    }
    while(option!=0);

    return 0;
}
