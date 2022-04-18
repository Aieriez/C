#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define LINHAS 4
#define COLUNAS 6

float mes[LINHAS][COLUNAS];

void fillvendas (float venda){
    for (int i = 0; i < LINHAS; i++){
        printf("\n %dª Semana \n", i+1);
        for (int j = 0; j < COLUNAS; j++){
            printf ("Digite o valor das vendas do dia %d R$: ", j+1);
            scanf("%f", &venda);
            mes[i][j] = venda;
        }
    }
    printf("\n");
}
void showvendas (){
    for (int i = 0; i < LINHAS; i++){
        printf("\n%dª Semana", i+1);
        for (int j = 0; j < COLUNAS; j++){
            printf ("\nDia %d ", j+1);
            printf("R$: %.2f", mes[i][j]);
        }
    }
     printf("\n");
}
float mediavendas (){
    float soma, mediav;
    for (int i = 0; i < LINHAS; i++){
        for (int j = 0; j < COLUNAS; j++){
            soma = soma + mes[i][j];
        }
    }
    mediav = soma / 24;
    return mediav;
}
int main ()
{
    setlocale(LC_ALL,"");
    int opcao;
    float mes[LINHAS][COLUNAS], venda, media;
    do {
        printf("\n********************** Menu **********************\n");
        printf("1 - Preencher Vendas\n");
        printf("2 - Exibir as Vendas\n");
        printf("3 - Média de Vendas\n");
        printf("4 - Sair\n");
        printf("\n**************************************************\n");
        printf(" -> Digite o número da opçao desejada: ");
                    scanf("%d", &opcao);
        switch(opcao)
        {
                case 1:
                    fillvendas(venda);
                    break;
                case 2:
                    showvendas();
                    break;
                case 3:
                    printf("\nMedia de vendas do mês R$: %.2f \n", media = mediavendas());
                    break;
                case 4: break;
                default:
                    printf("\nOpção inexistente selecione novamente \n");
        }
    } while (opcao != 4);
    return 0;
}

