#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 20
#define MAX_EDGES (MAX_VERTICES * (MAX_VERTICES - 1)) / 2

typedef struct {
    int from;
    int to;
    int weight;
} Edge;

typedef struct {
    int numVertices;
    int graphMatrix[MAX_VERTICES][MAX_VERTICES];
} GraphMatrix;

typedef struct Node {
    int vertex;
    int weight;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} AdjList[MAX_VERTICES];

typedef struct {
    int numEdges;
    Edge edges[MAX_EDGES];
} GraphEdges;

void initGraphMatrix(GraphMatrix* graphMatrix, int numVertices) {
    graphMatrix->numVertices = numVertices;
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            graphMatrix->graphMatrix[i][j] = INT_MAX;
        }
    }
}

void addEdgeMatrix(GraphMatrix* graphMatrix, int from, int to, int weight) {
    graphMatrix->graphMatrix[from][to] = weight;
    graphMatrix->graphMatrix[to][from] = weight;
}

void displayGraphMatrix(GraphMatrix* graphMatrix) {
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < graphMatrix->numVertices; i++) {
        for (int j = 0; j < graphMatrix->numVertices; j++) {
            if (graphMatrix->graphMatrix[i][j] != INT_MAX) {
                printf("%d ", graphMatrix->graphMatrix[i][j]);
            } else {
                printf("INF ");
            }
        }
        printf("\n");
    }
}

void initGraphEdges(GraphEdges* graphEdges) {
    graphEdges->numEdges = 0;
}

void addEdgeEdges(GraphEdges* graphEdges, int from, int to, int weight) {
    graphEdges->edges[graphEdges->numEdges].from = from;
    graphEdges->edges[graphEdges->numEdges].to = to;
    graphEdges->edges[graphEdges->numEdges].weight = weight;
    graphEdges->numEdges++;
}

void displayGraphEdges(GraphEdges* graphEdges) {
    printf("Edges and Weights:\n");
    for (int i = 0; i < graphEdges->numEdges; i++) {
        printf("(%d, %d) Weight: %d\n", graphEdges->edges[i].from, graphEdges->edges[i].to, graphEdges->edges[i].weight);
    }
}

void initAdjList(AdjList* adjList, int numVertices) {
    for (int i = 0; i < numVertices; i++) {
        (*adjList)[i].head = NULL;
    }
}

void addEdgeList(AdjList* adjList, int from, int to, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = to;
    newNode->weight = weight;
    newNode->next = (*adjList)[from].head;
    (*adjList)[from].head = newNode;

    newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = from;
    newNode->weight = weight;
    newNode->next = (*adjList)[to].head;
    (*adjList)[to].head = newNode;
}

void displayAdjList(AdjList* adjList, int numVertices) {
    printf("Adjacency List:\n");
    for (int i = 0; i < numVertices; i++) {
        Node* current = (*adjList)[i].head;
        printf("Vertex %d: ", i);
        while (current != NULL) {
            printf("(%d, %d) ", current->vertex, current->weight);
            current = current->next;
        }
        printf("\n");
    }
}

void primsMatrix(GraphMatrix* graphMatrix) {
    int parent[MAX_VERTICES];
    int key[MAX_VERTICES];
    int mstSet[MAX_VERTICES];

    for (int i = 0; i < graphMatrix->numVertices; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < graphMatrix->numVertices - 1; count++) {
        int minKey = INT_MAX, u;

        for (int v = 0; v < graphMatrix->numVertices; v++) {
            if (!mstSet[v] && key[v] < minKey) {
                minKey = key[v];
                u = v;
            }
        }

        mstSet[u] = 1;

        for (int v = 0; v < graphMatrix->numVertices; v++) {
            if (graphMatrix->graphMatrix[u][v] && !mstSet[v] && graphMatrix->graphMatrix[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graphMatrix->graphMatrix[u][v];
            }
        }
    }

    printf("\nMinimum Spanning Tree (Prim's Algorithm using Adjacency Matrix):\n");
    printf("Edge \t Weight\n");
    int totalWeight = 0;
    for (int i = 1; i < graphMatrix->numVertices; i++) {
        printf("%d - %d \t %d\n", parent[i], i, graphMatrix->graphMatrix[i][parent[i]]);
        totalWeight += graphMatrix->graphMatrix[i][parent[i]];
    }
    printf("Total Weight of Minimum Spanning Tree: %d\n", totalWeight);
}

void primsList(AdjList* adjList, int numVertices) {
    int parent[MAX_VERTICES];
    int key[MAX_VERTICES];
    int mstSet[MAX_VERTICES];

    for (int i = 0; i < numVertices; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < numVertices - 1; count++) {
        int minKey = INT_MAX, u;

        for (int v = 0; v < numVertices; v++) {
            if (!mstSet[v] && key[v] < minKey) {
                minKey = key[v];
                u = v;
            }
        }

        mstSet[u] = 1;

        Node* current = (*adjList)[u].head;
        while (current != NULL) {
            int v = current->vertex;
            int weight = current->weight;
            if (!mstSet[v] && weight < key[v]) {
                parent[v] = u;
                key[v] = weight;
            }
            current = current->next;
        }
    }

    printf("\nMinimum Spanning Tree (Prim's Algorithm using Adjacency List):\n");
    printf("Edge \t Weight\n");
    int totalWeight = 0;
    for (int i = 1; i < numVertices; i++) {
        printf("%d - %d \t %d\n", parent[i], i, key[i]);
        totalWeight += key[i];
    }
    printf("Total Weight of Minimum Spanning Tree: %d\n", totalWeight);
}

int compare(const void* a, const void* b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

int findSet(int parent[], int i) {
    if (parent[i] == -1)
        return i;
    return findSet(parent, parent[i]);
}

void unionSets(int parent[], int x, int y) {
    int xSet = findSet(parent, x);
    int ySet = findSet(parent, y);
    parent[xSet] = ySet;
}

void kruskalMatrix(GraphMatrix* graphMatrix, int numEdges, Edge edges[]) {
    GraphEdges graphEdges;
    initGraphEdges(&graphEdges);

    for (int i = 0; i < numEdges; i++) {
        addEdgeEdges(&graphEdges, edges[i].from, edges[i].to, edges[i].weight);
    }

    qsort(graphEdges.edges, graphEdges.numEdges, sizeof(Edge), compare);

    printf("\nMinimum Spanning Tree (Kruskal's Algorithm using Adjacency Matrix):\n");
    printf("Edge \t Weight\n");
    int totalWeight = 0;
    int parent[MAX_VERTICES];
    for (int i = 0; i < MAX_VERTICES; i++)
        parent[i] = -1;

    for (int i = 0; i < graphEdges.numEdges; i++) {
        int x = findSet(parent, graphEdges.edges[i].from);
        int y = findSet(parent, graphEdges.edges[i].to);

        if (x != y) {
            printf("%d - %d \t %d\n", graphEdges.edges[i].from, graphEdges.edges[i].to, graphEdges.edges[i].weight);
            totalWeight += graphEdges.edges[i].weight;
            unionSets(parent, x, y);
        }
    }
    printf("Total Weight of Minimum Spanning Tree: %d\n", totalWeight);
}

void kruskalList(AdjList* adjList, int numVertices, int numEdges, Edge edges[]) {
    GraphEdges graphEdges;
    initGraphEdges(&graphEdges);

    for (int i = 0; i < numEdges; i++) {
        addEdgeEdges(&graphEdges, edges[i].from, edges[i].to, edges[i].weight);
    }

    qsort(graphEdges.edges, graphEdges.numEdges, sizeof(Edge), compare);

    printf("\nMinimum Spanning Tree (Kruskal's Algorithm using Adjacency List):\n");
    printf("Edge \t Weight\n");
    int totalWeight = 0;
    int parent[MAX_VERTICES];
    for (int i = 0; i < MAX_VERTICES; i++)
        parent[i] = -1;

    for (int i = 0; i < graphEdges.numEdges; i++) {
        int x = findSet(parent, graphEdges.edges[i].from);
        int y = findSet(parent, graphEdges.edges[i].to);

        if (x != y) {
            printf("%d - %d \t %d\n", graphEdges.edges[i].from, graphEdges.edges[i].to, graphEdges.edges[i].weight);
            totalWeight += graphEdges.edges[i].weight;
            unionSets(parent, x, y);
        }
    }
    printf("Total Weight of Minimum Spanning Tree: %d\n", totalWeight);
}

int main() {
    int numVertices, numEdges;
    printf("Enter the number of vertices (max %d): ", MAX_VERTICES);
    scanf("%d", &numVertices);

    printf("Enter the number of edges (max %d): ", MAX_EDGES);
    scanf("%d", &numEdges);

    Edge edges[MAX_EDGES];
    printf("Enter edges in the format (from to weight):\n");
    for (int i = 0; i < numEdges; i++) {
        printf("Edge %d: ", i + 1);
        scanf("%d %d %d", &edges[i].from, &edges[i].to, &edges[i].weight);
    }

    GraphMatrix graphMatrix;
    initGraphMatrix(&graphMatrix, numVertices);

    AdjList adjList;
    initAdjList(&adjList, numVertices);

    for (int i = 0; i < numEdges; i++) {
        addEdgeMatrix(&graphMatrix, edges[i].from, edges[i].to, edges[i].weight);
        addEdgeList(&adjList, edges[i].from, edges[i].to, edges[i].weight);
    }

    int choice;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Display adjacency matrix\n");
        printf("2. Display adjacency list\n");
        printf("3. Find Minimum Spanning Tree using Prim's Algorithm (adjacency matrix)\n");
        printf("4. Find Minimum Spanning Tree using Prim's Algorithm (adjacency list)\n");
        printf("5. Find Minimum Spanning Tree using Kruskal's Algorithm (adjacency matrix)\n");
        printf("6. Find Minimum Spanning Tree using Kruskal's Algorithm (adjacency list)\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayGraphMatrix(&graphMatrix);
                break;

            case 2:
                displayAdjList(&adjList, numVertices);
                break;

            case 3:
                primsMatrix(&graphMatrix);
                break;

            case 4:
                primsList(&adjList, numVertices);
                break;

            case 5:
                kruskalMatrix(&graphMatrix, numEdges, edges);
                break;

            case 6:
                kruskalList(&adjList, numVertices, numEdges, edges);
                break;

            case 7:
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

