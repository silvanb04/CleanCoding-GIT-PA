 /*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/

#include <stdlib.h>
#include <stdio.h>

    typedef struct Node
{
    int data;
    struct Node *next;
} Node;
/// pentru simplitate, folosim int uri pt a numi restaurantel/locatiile
/// ex: 1 - restaurantul 1 si tot asa

typedef struct 
{
    int nr_vertex;
    int *visited;
    struct Node **adj_list;
} Graph;

typedef struct 
{
    int top;
    int stack_cap;
    int *array;
} Stack;

Node *create_node(int v)
{
    Node *new_node = malloc(sizeof(Node));
    new_node->data = v;
    new_node->next = NULL;
    return new_node;
}

void add_edge(Graph *graph, int src, int dest)
{
    Node *new_node = create_node(dest);
    new_node->next = graph->adj_list[src];
    graph->adj_list[src] = new_node;
    new_node = create_node(src);
    new_node->next = graph->adj_list[dest];
    graph->adj_list[dest] = new_node;
}

Graph* create_graph(int v)
{
    int i;
    Graph *graph = malloc(sizeof(Graph));
    graph->nr_vertex = v;
    graph->adj_list = malloc(sizeof(Node *));
    graph->visited = malloc(sizeof(int) * v);

    for (int i = 0; i < v; i++)
    {
        graph->adj_list[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

Stack *create_stack(int stack_cap)
{
    Stack *stack = malloc(sizeof(Stack));
    stack->array = malloc(stack_cap * sizeof(int));
    stack->top = -1;
    stack->stack_cap = stack_cap;
    return stack;
}

void push(int data, Stack *stack)
{
    stack->top++;
    stack->array[stack->top] = data;
}

void DFS(Graph *graph, Stack *stack, int data)
{
    Node *adj_list = graph->adj_list[data];
    Node *aux = adj_list;
    graph->visited[data] = 1;
    push(data, stack);
    while (aux != NULL)
    {
        int connected_vertex = aux->data;
        if (graph->visited[connected_vertex] == 0)
            DFS(graph, stack, connected_vertex);
        aux = aux->next;
    }
}

void insert_edges(Graph *graph, int edge_nr, int nrv)
{
    int src, dest, i;
    printf("Adauga %d muchii (de la 1 la %d)\n", edge_nr, nrv);
    for (i = 0; i < edge_nr; i++)
    {
        scanf("%d%d", &src, &dest);
        add_edge(graph, src, dest);
    }
}

void wipe(Graph *graph, int nrv)
{
    for (int i = 0; i < nrv; i++)
    {
        graph->visited[i] = 0;
    }
}  
// void printGraph(struct Graph* graph) {
//     int i;
//     for (i = 0; i < N; i++) {
//         struct Node* ptr = graph->head[i];
//         while (ptr != NULL) {
//             printf("(%d -> %d)\t", i, ptr->dest);
//             ptr = ptr->next;
//         }
//         printf("\n");
//     }
// }
void canbe(Graph *graph, int nrv, Stack *stack1, Stack *stack2, int a[][100]) {
    int ans = 0; // Initialize ans
    for (int i = 0; i < nrv && !ans; i++) {
        wipe(graph, nrv);
        DFS(graph, stack1, i);
        for (int j = 0; j < nrv && !ans; j++) {
            wipe(graph, nrv);
            DFS(graph, stack2, j);
            if (graph->visited[i] && graph->visited[j]) {
                ans = 1; // Set ans to 1 if both i and j are reachable
                a[i][j] = 1;
            }
        }
    }
    //printf("Direct path exists: %d\n", ans);
}

int main()
{

    int nrv;
    int edg_nr;
    int src, dest;
    int i;
    int vertex_1;
    int vertex_2;
    int ans;
    int a[100][100];

    printf("Cate noduri are graful?");
    scanf("%d", &nrv);

    printf("Cate muchii are graful?");
    scanf("%d", &edg_nr);

    Graph *graph = create_graph(nrv);
    insert_edges(graph, edg_nr, nrv);

    Stack *stack1 = create_stack(2 * nrv);
    Stack *stack2 = create_stack(2 * nrv);

    printf("Introduceti 2 noduri:");
    scanf("%d%d", &vertex_1, &vertex_2);

    canbe(graph, nrv, stack1, stack2, a);

    if(a[vertex_1][vertex_2]==1)
          printf("exista drum intre cele doua noduri");
    else
    printf("nu");
    

}