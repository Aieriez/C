#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct dataset{
    int dia, mes, ano;
    float valor;
}Dataset;

Dataset dados[1024];

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
    imprimir(row_count);
    fclose(fp);

    return 0;
}
