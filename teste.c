#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 50

struct Node {
    int value;
    struct Node* next;
};

struct Graph {
    int num_nodes;
    struct Node** adjacency_list;
};

struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int num_nodes) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->num_nodes = num_nodes;
    graph->adjacency_list = (struct Node**)malloc(num_nodes * sizeof(struct Node*));

    for (int i = 0; i < num_nodes; i++) {
        graph->adjacency_list[i] = NULL;
    }

    return graph;
}

void addEdge(struct Graph* graph, int node1, int node2) {
    struct Node* newNode = createNode(node2);
    newNode->next = graph->adjacency_list[node1];
    graph->adjacency_list[node1] = newNode;

    newNode = createNode(node1);
    newNode->next = graph->adjacency_list[node2];
    graph->adjacency_list[node2] = newNode;
}

void dfs(struct Graph* graph, int node, int max_depth, int* edge_count, bool visited[MAX_NODES]) {
    visited[node] = true;

    if (max_depth > 0) {
        struct Node* neighbor = graph->adjacency_list[node];
        while (neighbor != NULL) {
            if (!visited[neighbor->value]) {
                (*edge_count)++;
                dfs(graph, neighbor->value, max_depth - 1, edge_count, visited);
            }
            neighbor = neighbor->next;
        }
    }
}

int main() {
    int test_cases;
    scanf("%d", &test_cases);

    while (test_cases--) {
        int num_nodes, starting_node, max_depth;
        scanf("%d %d %d", &starting_node, &num_nodes, &max_depth);

        struct Graph* graph = createGraph(num_nodes);

        for (int i = 0; i < max_depth; i++) {
            int node1, node2;
            scanf("%d %d", &node1, &node2);
            addEdge(graph, node1, node2);
        }

        bool visited[MAX_NODES] = {false};
        int edge_count = 0;

        dfs(graph, starting_node, max_depth, &edge_count, visited);

        printf("%d\n", edge_count * 2);

        // Liberar memória
        for (int i = 0; i < graph->num_nodes; i++) {
            struct Node* current = graph->adjacency_list[i];
            while (current != NULL) {
                struct Node* temp = current;
                current = current->next;
                free(temp);
            }
        }
        free(graph->adjacency_list);
        free(graph);
    }

    return 0;
}
