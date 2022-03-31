#include <iostream>
#include "graph.h"
#include "bipartity_check.h"

void bipartite_test(graph* x) {

    int* color = (int*)calloc(x->n, sizeof(int));
    if (color) {
        //int* a = (int*)calloc(x->n, sizeof(int));
        //int* b = (int*)calloc(x->n, sizeof(int));
        //int k = 0, l = 0;

        if (is_bipartite(x, color)) {//bipartity_check_bfs(x, &a, &k, &b, &l)) {
            printf("Graph is not biparted");
        }
        else {
            printf("1st part: ");
            for (int i = 0; i < x->n; i++) {
                if (color[i] == 1) printf("%d ", i);
            }
            printf("\n2nd part: ");
            for (int i = 0; i < x->n; i++) {
                if (color[i] == 2) printf("%d ", i);
            }
        }
    }
}

int main() {
    int n = 4;
    /*
    printf("Enter number of vertexes of graph: ");
    scanf_s("%d", &n);
    getchar();
    */
    graph* x = graph_init(n);
    add_edge(x, 0, 1);
    add_edge(x, 1, 2);
    add_edge(x, 3, 0);
    graph_print(x);
    bipartite_test(x);
    /*int* a = (int*)calloc(n, sizeof(int));
    int* b = (int*)calloc(n, sizeof(int));
    int k = 0, l = 0;
    if (bipartity_check_bfs(x, &a, &k, &b, &l)) {
        printf("Graph is not biparted");
    }
    else {
        printf("1st part: ");
        for (int i = 0; i < k; i++) {
            printf("%d ", a[i]);
        }
        printf("\n2nd part: ");
        for (int i = 0; i < l; i++) {
            printf("%d ", b[i]);
        }
    }*/
    return 0;
}
