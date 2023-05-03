#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "Fila.h"
#include "pilha.h"
#include <stdbool.h>

Fila f;
Pilha p;

int main(){
    int n, a, b, **adj, *vis, *pais; 
    printf("quantos nodos existem na grafo?\n");
    scanf("%d", &n);

    //iniciando os vetor "dinamicamente"
    pais = malloc((n+1)*sizeof(int));
    vis = malloc((n+1)*sizeof(int));
    adj = malloc((n+1)*sizeof(int*));
    for(int i = 1; i <= n; i++){
        adj[i] = malloc((n+1)*sizeof(int));
    }

    printf("insira a matriz de adjacencia\n");
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            scanf("%d", &adj[i][j]);
        }
    }

    printf("qual o nodo inicial?\n");
    scanf("%d", &a);
    printf("qual o nodo final?\n");
    scanf("%d", &b);
     
    inicializa_fila(&f, n+5);

    //inicia bfs
    bool flag = false;
    printf("a: %d, b: %d\n", a, b);
    vis[a] = 1; 
    inserir(&f, a);
    while(!fila_vazia(f) && !flag){
        int atual;
        remover(&f, &atual);
        for(int i = 1; i <= n; i++){
            if(adj[atual][i] && !vis[i]){
                vis[i] = 1;
                pais[i] = atual;
                inserir(&f, i);
                if(i == b){
                    flag = true;
                    break;
                }
            }
        }
    }
    

    if(!flag){
        printf("Nao ha caminho entre %d e %d\n", a, b);
    } else {
        printf("Caminho de %d ate %d: ", a, b);
        int aux = b;
        inicializa_pilha(&p, n+5);
        while(aux != a){
            empilha(&p, aux);
            /* printf("%d ", aux); */
            /* assert(aux != 0); */
            if(aux == 0) break;
            aux = pais[aux];
        }
        empilha(&p, a);
        /* printf("%d", a); */
    }
    for(int i = 0; i < n; i++){
        int k;
        if(desempilha(&p, &k) != ERRO_PILHA_VAZIA){
            printf("\n", k);
        };
    }
    printf("\n");
    //libera memoria
    for(int i = 1; i <= n; i++){
        free(adj[i]);
    }
    free(adj);
    free(vis);
    free(pais);


    return EXIT_SUCCESS;
}

/* debug

   for(int i = 0; i < n; i++){
   for(int j = 0; j < n; j++){
   printf("%d ", adj[i][j]);
   }
   printf("\n");
   }

   for(int i = 0; i < n; i++){
   printf("%d  ", vis[i]);
   }
   */
