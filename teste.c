#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Graph {
    char* name[100];
};

int main () {
    struct Graph* graph = malloc(sizeof(struct Graph)); // Alocação de memória para a estrutura

    for (int i = 1; i <= 3; i++) {
        graph->name[i] = (char *)malloc(21 * sizeof(char)); // Alocar memória para o nome

        char name[21];
        scanf("%s", name);

        strcpy(graph->name[i], name); // Copiar o nome para a alocação de memória
        printf("%s: %s\n", graph->name[i], name);
    }

    return 0;
}