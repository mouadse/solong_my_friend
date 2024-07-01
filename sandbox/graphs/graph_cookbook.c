#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_node {
  int val;
  struct s_node *next;
} node;

typedef struct s_graph {
  int size;
  node **list;
  int *visited;
} graph;

graph *createGraph(int size) {
  graph *g = (graph *)malloc(sizeof(graph));
  g->size = size;
  g->list = (node **)malloc(sizeof(node *) * size);
  g->visited = (int *)malloc(sizeof(int) * size);
  for (int i = 0; i < size; i++) {
    g->list[i] = NULL;
    g->visited[i] = 0;
  }
  return g;
}

node *createNode(int val) {
  node *newNode = (node *)malloc(sizeof(node));
  newNode->val = val;
  newNode->next = NULL;
  return newNode;
}

void addEdge(graph *g, int src, int dest) {
  node *newNode = createNode(dest);
  newNode->next = g->list[src];
  g->list[src] = newNode;

  newNode = createNode(src);
  newNode->next = g->list[dest];
  g->list[dest] = newNode;
}

void printGraph(graph *g) {
  for (int i = 0; i < g->size; i++) {
    node *temp = g->list[i];
    printf("Node %d: ", i);
    while (temp) {
      printf("%d -> ", temp->val);
      temp = temp->next;
    }
    printf("\n");
  }
}

void freeGraph(graph *g) {
  for (int i = 0; i < g->size; i++) {
    node *temp = g->list[i];
    while (temp) {
      node *temp2 = temp;
      temp = temp->next;
      free(temp2);
    }
  }
  free(g->list);
  free(g->visited);
  free(g);
}

void dfs(graph *g, int start) {
  g->visited[start] = 1;
  printf("Visited %d\n", start);

  node *adjList = g->list[start];
  while (adjList) {
    if (!g->visited[adjList->val]) {
      dfs(g, adjList->val);
    }
    adjList = adjList->next;
  }
}

void bfs(graph *g, int start) {
  int queue[g->size];
  int front = 0, rear = 0;
  queue[rear] = start;
  g->visited[start] = 1;
  printf("Visited %d\n", start);

  while (front <= rear) {
    int current = queue[front];
    node *adjList = g->list[current];
    while (adjList) {
      if (!g->visited[adjList->val]) {
        rear++;
        queue[rear] = adjList->val;
        g->visited[adjList->val] = 1;
        printf("Visited %d\n", adjList->val);
      }
      adjList = adjList->next;
    }
    front++;
  }
}

void floodFill(int **image, int sr, int sc, int newColor, int rows, int cols) {
  int color = image[sr][sc];
  if (color == newColor) {
    return;
  }
  image[sr][sc] = newColor;
  if (sr > 0 && image[sr - 1][sc] == color) {
    floodFill(image, sr - 1, sc, newColor, rows, cols);
  }
  if (sc > 0 && image[sr][sc - 1] == color) {
    floodFill(image, sr, sc - 1, newColor, rows, cols);
  }
  if (sr < rows - 1 && image[sr + 1][sc] == color) {
    floodFill(image, sr + 1, sc, newColor, rows, cols);
  }
  if (sc < cols - 1 && image[sr][sc + 1] == color) {
    floodFill(image, sr, sc + 1, newColor, rows, cols);
  }
}

// flood fill algorithm using graph

void floodFillGraph(graph *g, int start, int newColor) {
  int color = start;
  if (color == newColor) {
    return;
  }
  g->visited[start] = 1;
  node *adjList = g->list[start];
  while (adjList) {
    if (!g->visited[adjList->val]) {
      floodFillGraph(g, adjList->val, newColor);
    }
    adjList = adjList->next;
  }
  printf("Visited %d\n", start);
}

int main(void) {
  // This is a demo of implmenting graphs DSA and flood fill algorithm
  // create a map of 5x5 with 0s and 1s
  int rows = 5, cols = 5;
  int **image = (int **)malloc(sizeof(int *) * rows);
  for (int i = 0; i < rows; i++) {
    image[i] = (int *)malloc(sizeof(int) * cols);
    for (int j = 0; j < cols; j++) {
      image[i][j] = rand() % 2;
    }
  }

  // print the map
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      printf("%d ", image[i][j]);
    }
    printf("\n");
  }

  // flood fill the map
  floodFill(image, 2, 2, 3, rows, cols);
  printf("\n");
  // print the map
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      printf("%d ", image[i][j]);
    }
    printf("\n");
  }
  // Time to handle memory leaks
  for (int i = 0; i < rows; i++) {
    free(image[i]);
  }
  free(image);
  return (EXIT_SUCCESS);
}
