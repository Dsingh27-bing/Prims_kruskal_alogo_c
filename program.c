#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define infinity 99
int a[101][101];
int set[10];
int height[10]; // stores height of each node


void adjacency_mat(int n) {
  printf("\nAdjacency matrix A : \n\n");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i == j) {
        a[i][j] = 0;
      } else {
        a[i][j] = a[j][i] = 1 + (rand() % 10);
      }
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%d ",a[i][j]);        // printing adjacency matrix
    }
    printf("\n");
  }
}

void prim_mst(int n, int graph[n][n]) {
    for(int i=0; i<n; i++){
    for(int j=0; j<n;j++){  // coping a to graph matrix
      graph[i][j]=a[i][j];
    }
  }
  
    int key[n]; 
    int parent[n];
    int visited[n];  // visited vertices

    for (int i = 0; i < n; i++) {
        key[i] = infinity;    //initializing all key with all elements infinity
        visited[i] = 0; //initializing all elements in visited array as zero 
    }

    key[0] = 0;  //first key is set zero
    parent[0] = -1;   //first parent is chosen as -1

    for (int i = 0; i < n - 1; i++) {  
        int min_key = infinity;
        int u;

        for (int j = 0; j < n; j++) {  // we are selecting the min key value found among the vertices not included in visited array 
            if (visited[j] == 0 && key[j] < min_key) {
                min_key = key[j];
                u = j;
            }
        }

        visited[u] = 1;  //the vertex is added to visited array

        for (int v = 0; v < n; v++) {
            if (graph[u][v] && visited[v] == 0 && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }


  
    printf("\nEdges in the minimum spanning tree (Prim's algorithm):\n");
    int mst_matrix[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            mst_matrix[i][j] = 0;    //diagonal of matrix is 0
        }
    }
// mst is created with parent array
    for (int i = 1; i < n; i++) {
        printf("V%d - V%d: %d\n", i+1, parent[i]+1, graph[parent[i]][i]);   //printing smallest distance between vetices
        mst_matrix[parent[i]][i] = graph[parent[i]][i]; //creating the mst matrix which is the prim's matrix
        mst_matrix[i][parent[i]] = graph[i][parent[i]];
    }

    printf("\nPrim's graph:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", mst_matrix[i][j]);   // printing prim's matrix
        }
        printf("\n");
    }
}


// kruskal starts here 
// find3 function as mentioned in slides
int find3(int x) {
    int root = x;
    while (root != set[root]) {
        root = set[root];
    }

    // compress path from x to root
    int node = x;
    while (node != root) {
        int parent = set[node];
        set[node] = root; // node points to root, set aray stores parent of each node in the set
        node = parent; 
    }
    return root;
}

// union3 function as mentioned in slides 
void union3(int rootx, int rooty) {
    if (height[rootx] == height[rooty]) {
        height[rootx]++;
        set[rooty] = rootx; // y's tree points to x's tree
    } else if (height[rootx] > height[rooty]) {
        set[rooty] = rootx; // y's tree points to x's tree
    } else {
        set[rootx] = rooty; // x's tree points y's tree
    }  // whichever is the taller tree shorter tree points to it if they are same then it randomly selects one of them and the other points to it
}

// kruskal mst as mentioned in slides using union and find functions
void kruskal_mst(int n, int graph[n][n]) {
  for(int i=0; i<n; i++){
    for(int j=0; j<n;j++){  // coping a to graph matrix
      graph[i][j]=a[i][j];
    }
  }

  int mstk_matrix[10][10] = {0}; // initialing to 0, will be used to store mst

  // Initialize sets and heights
    for (int i = 0; i < n; i++) {
        set[i] = i;
        height[i] = 0;
    }

    // kruskal algo starts
    int edge = 0;
    int tree[10][2];
    while (edge < n - 1) {
        int min_weight = infinity;
        int u = -1, v = -1;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (graph[i][j] < min_weight) {
                    u = i;
                    v = j;
                    min_weight = graph[i][j];
                }
            }
        }
        int ucomp = find3(u);
        int vcomp = find3(v);
        if (ucomp != vcomp) {
            tree[edge][0] = u;
            tree[edge][1] = v;
            edge++;
            union3(ucomp, vcomp);
            mstk_matrix[u][v] = mstk_matrix[v][u] = graph[u][v];

        }
        graph[u][v] = graph[v][u] = infinity;

    }
  
     printf("\nKruskal's matrix: \n\n");
     for (int i = 0; i < n; i++) {
         for (int j = 0; j < n; j++) {   //printing kruskal matrix
             printf("%d ", mstk_matrix[i][j]);
         }
         printf("\n");
     }

    
    printf("\nKruskal's MST:\n\n");
    for (int i = 0; i < n - 1; i++) {
        printf("V%d-V%d: %d\n", tree[i][0]+1,tree[i][1]+1, mstk_matrix[tree[i][1]][tree[i][0]]);//printing the shortest distance between vertices 
    }


    return;
}

// main function
int main()
{
    
    srand(time(0)); // seed the random number generator

    // randomly select the number of vertices between 5 and 10
    int n = rand() % 6 + 5;
    printf("\nNumber of vertices: %d\n", n);
  
  adjacency_mat(n);
  
    char choice; //make choice for mst selection
    printf("\nSelect minimum spanning tree algorithm:\n");
    printf("1. Prim's Algorithm\n");
    printf("2. Kruskal's Algorithm\n");
    printf("Enter your choice as 'p' for Prim's and 'k' for Kruskal: ");
    scanf("%c", &choice);

    // perform the selected algorithm
    switch (choice)
    {
        case 'p':
            prim_mst(n, a);
            break;
        case 'k':
            kruskal_mst(n, a);
            break;
        default:
            printf("Invalid choice!\n");
            break;
    }

    return 0;
}
