#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int src, dest, weight;
}Edge;

void bellmanFord(Edge edges[], int V, int E, int src) {
    int dist[V];
    
    for (int i= 0;i <V; i++)
        dist[i] = INT_MAX;
    dist[src] = 0;

    for (int i =1; i <=V-1; i++) {
        for (int j= 0; j< E; j++) {
            int u= edges[j].src;
            int v= edges[j].dest;
            int w= edges[j].weight;
            if (dist[u] != INT_MAX && dist[u]+w<dist[v])
                dist[v]=dist[u] + w;
        }
    }

    for (int j=0; j<E; j++) {
        int u= edges[j].src;
        int v= edges[j].dest;
        int w= edges[j].weight;
        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            printf("Graph contains negative weight cycle\n");
            return;
        }
    }

    printf("\nShortest distances from pickup point (0):\n");
    for (int i= 0; i< V; i++) {
        printf("To address %d: ", i);
        if (dist[i]==INT_MAX) 
            printf("Unreachable\n");
        else
            printf("%d\n", dist[i]);
    }
}

int main() {
    int V;
    printf("Enter number of addresses (including pickup point): ");
    scanf("%d", &V);

    int E=V*(V-1); 
    Edge edges[E];
    int k=0;

    printf("Enter travel times between addresses (matrix format, 0 for same address):\n");
    int travelTime[V][V];
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &travelTime[i][j]);
        }
    }
    for (int i= 0; i< V; i++) {
        for (int j= 0; j< V; j++) {
            if (i!= j) {
                edges[k].src = i;
                edges[k].dest = j;
                edges[k].weight = travelTime[i][j];
                k++;
            }
        }
    }
    int pickupPoint;
    printf("Enter the pickup point index (0 to %d): ", V-1);
    scanf("%d", &pickupPoint);

    bellmanFord(edges, V, E, pickupPoint);

    return 0;
}
