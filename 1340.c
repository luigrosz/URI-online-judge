#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct a {
    int elemento_fila[1000];
    int comeco_fila, final_fila;
    int elemento_pilha[1000];
    int indice_pilha;
    int elemento_lista_prioridade[1000];
    int indice_lista_prioridade;
} a;

void insere_fila(int valor, a *dado) {
    dado->elemento_fila[dado->final_fila++] = valor;
}
int remove_fila(a *dado) {
    if (dado->comeco_fila == dado->final_fila) {
        return -10000000;
    }
    return dado->elemento_fila[dado->comeco_fila++];
}

void insere_pilha(int valor, a *dado) {
    dado->elemento_pilha[++dado->indice_pilha] = valor;
}
int remove_pilha(a *dado) {
    if (dado->indice_pilha <= 0) {
        return -10000000;
    }
    return dado->elemento_pilha[dado->indice_pilha--];
}

void insere_lista_prioridade(int valor, a *dado) {
    int indexador_auxiliar;
    indexador_auxiliar = ++dado->indice_lista_prioridade;
    while (indexador_auxiliar > 1) {
        if (dado->elemento_lista_prioridade[indexador_auxiliar / 2] < valor) {
            dado->elemento_lista_prioridade[indexador_auxiliar] =
                dado->elemento_lista_prioridade[indexador_auxiliar / 2];
            indexador_auxiliar = indexador_auxiliar / 2;
        } else
            break;
    }
    dado->elemento_lista_prioridade[indexador_auxiliar] = valor;
}
int remove_lista_prioridade(a *dado) {
    int temporario, atual, proximo;
    if (dado->indice_lista_prioridade <= 0) {
        return -10000000;
    }
    temporario = dado->elemento_lista_prioridade[1];
    atual = 1;
    proximo = 2;
    dado->indice_lista_prioridade--;
    while (proximo <= dado->indice_lista_prioridade) {
        if (proximo < dado->indice_lista_prioridade &&
            dado->elemento_lista_prioridade[proximo + 1] >
                dado->elemento_lista_prioridade[proximo]) {
            proximo++;
        }
        if (dado->elemento_lista_prioridade[proximo] >
            dado->elemento_lista_prioridade[dado->indice_lista_prioridade +
                                            1]) {
            dado->elemento_lista_prioridade[atual] =
                dado->elemento_lista_prioridade[proximo];
            atual = proximo;
            proximo = atual * 2;
        } else
            break;
    }
    dado->elemento_lista_prioridade[atual] =
        dado->elemento_lista_prioridade[dado->indice_lista_prioridade + 1];
    return temporario;
}

int main(int argc, char *argv[]) {
    int comando, valor;
    int n, i;
    int flag[3];
    int recebido;
    a data;
    while (scanf("%d", &n) != EOF) {
        memset(flag, 0, sizeof(flag));
        data.comeco_fila = 0;
        data.final_fila = 0;
        data.indice_pilha = 0;
        data.indice_lista_prioridade = 0;
        for (i = 0; i < n; i++) {
            scanf("%d %d", &comando, &valor);

            if (comando == 1) {
                insere_fila(valor, &data);
                insere_pilha(valor, &data);
                insere_lista_prioridade(valor, &data);
            }

            else {
                recebido = remove_fila(&data);

                if (recebido != valor) {
                    flag[0] = 1;
                }
                recebido = remove_pilha(&data);
                if (recebido != valor) {
                    flag[1] = 1;
                }
                recebido = remove_lista_prioridade(&data);
                if (recebido != valor) {
                    flag[2] = 1;
                }
            }
        }

        if (flag[0] + flag[1] + flag[2] == 3)
            printf("impossible\n");

        else if (flag[0] + flag[1] + flag[2] < 2)
            printf("not sure\n");
        else {
            if (!flag[0]) printf("queue\n");
            if (!flag[1]) printf("stack\n");
            if (!flag[2]) printf("priority queue\n");
        }
    }
    return 0;
}