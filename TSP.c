#include <stdio.h>
#include <stdlib.h>
#define INF 1000000

int minCost;
int *bestPath;
void tsp(int **dist, int *path, int *visited, int N, int pos, int count, int cost) {
    if (count==N &&dist[pos][path[0]] >0) { // complete tour
        cost += dist[pos][path[0]];
        if (cost<minCost) {
            minCost = cost;
            for (int i= 0; i<= N; i++)
                bestPath[i] = path[i];
        }
        return;
    }

    for (int i= 0; i< N; i++) {
        if (!visited[i] && dist[pos][i]> 0) {
            visited[i] = 1;
            path[count] = i;
            tsp(dist, path, visited, N, i, count+ 1, cost+ dist[pos][i]);
            visited[i]= 0;
        }
    }
}

int main() {
    int N;
    printf("Enter number of cities: ");
    scanf("%d", &N);

    int **dist = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++)
        dist[i] = (int *)malloc(N * sizeof(int));

    printf("Enter distance matrix:\n");
    for (int i= 0; i< N;i++)
        for (int j= 0; j< N; j++)
            scanf("%d", &dist[i][j]);

    bestPath=(int *)malloc((N + 1) * sizeof(int));

    for (int start =0; start <N; start++) {
        minCost =INF;
        int *path =(int *)malloc((N + 1) * sizeof(int));
        int *visited =(int *)calloc(N, sizeof(int));

        path[0] =start;
        visited[start] =1;

        tsp(dist, path, visited, N, start, 1, 0);

        printf("Starting at city %d:\n", start + 1);
        printf("Path: ");
        for (int i =0; i <=N; i++)
            printf("%d%s", bestPath[i] + 1, (i< N) ? " -> " : "\n");
        printf("Cost of travelling is: %d\n\n", minCost);

        free(path);
        free(visited);
    }

    for (int i= 0; i< N; i++)
        free(dist[i]);
    free(dist);
    free(bestPath);

    return 0;
}
