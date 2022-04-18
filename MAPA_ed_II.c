#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct dataset{
    int dia, mes, ano;
    float valor;
}Dataset;

Dataset dados[1024];

void merge(Dataset vet1[], int comeco, int meio, int fim) {
    int com1 = comeco, com2 = meio+1, comAux = 0, tam = fim-comeco+1;
    Dataset vetAux[fim];

    while(com1 <= meio && com2 <= fim){
        if(vet1[com1].ano > vet1[com2].ano) {
            vetAux[comAux] = vet1[com1];
            com1++;
        }else if ((vet1[com1].ano == vet1[com2].ano) && (vet1[com1].mes > vet1[com2].mes)){
            vetAux[comAux] = vet1[com1];
            com1++;
         }else {
            vetAux[comAux] = vet1[com2];
            com2++;
        }
        comAux++;
    }

    while(com1 <= meio){
        vetAux[comAux] = vet1[com1];
        comAux++;
        com1++;
    }

    while(com2 <= fim) {
        vetAux[comAux] = vet1[com2];
        comAux++;
        com2++;
    }

    for(comAux = comeco; comAux <= fim; comAux++){
        vet1[comAux] = vetAux[comAux-comeco];
    }
    free(vetAux);
}

void mergeSort(Dataset vetor[], int comeco, int fim){
    if (comeco < fim) {
        int meio = (fim+comeco)/2;

        mergeSort(vetor, comeco, meio);
        mergeSort(vetor, meio+1, fim);
        merge(vetor, comeco, meio, fim);
    }
}
void process_field(int field_count, char *value, int i) {
    if (field_count == 0) {
        dados[i].dia = atoi(value);
    }
     if (field_count == 1) {
        dados[i].mes = atoi(value);
    }
     if (field_count == 2) {
        dados[i].ano = atoi(value);
    }
    if (field_count == 3) {
        dados[i].valor = atof(value);
    }
}

void imprimir(int row_count){
  for (int i = 2 ; i <= row_count; i++ ){
        printf("Data:\t 0%d/", dados[i].dia);
        if(dados[i].mes < 10){
            printf("0%d/%d\t", dados[i].mes, dados[i].ano);
        }else{
            printf("%d/%d\t", dados[i].mes, dados[i].ano);
        }
        printf("Valor:\t %.2f\n", dados[i].valor);
    }
}

int main(void) {
    setlocale(LC_ALL, "Portuguese");
    char filename[] = "bcdata.sgs.4468.csv";
    char buf[1024];
    char token[1024];
    int in_date = 0;
    int row_count = 0;
    int field_count = 0;
    int token_pos = 0;
    int i = 0;

    FILE *fp = fopen(filename, "r");

    if (!fp) {
        printf("Arquivo não pode ser aberto!\n");
        return 0;
    }
   while (fgets(buf, 1024, fp)) {
        row_count++;

        if (row_count == 1) {
            continue;
        }
        field_count = 0;
        i = 0;
        do {
            token[token_pos++] = buf[i];

            if (buf[i] == '/' || buf[i] == ';' || buf[i] == '\n') {
                token[token_pos - 1] = 0;
                token_pos = 0;
                process_field(field_count++, token, row_count);
            }
        } while (buf[++i]);
    }

    mergeSort(dados, 2, row_count);
    printf("Arquivo após MergeSort:\n");
    imprimir(row_count);

    fclose(fp);

    return 0;
}
