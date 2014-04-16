#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>
#define forn(i, n) for(i = 0; i<n; i++)

struct point {
    int x;
    int y;
};

struct point** graph;

char** maze;

void print_maze(int n, int m) {
    int i, j;
    forn(i, n) { 
    forn(j, m) 
        printf("%c", maze[i][j]);
    printf("\n");
        }   
}

int main(void) {
    int n, m; //size of the maze;

    freopen("input", "r", stdin);
    freopen("output", "w", stdout);

    scanf("%d %d", &n, &m);

    printf("%d*%d\n", n, m);
 
    //graph = (struct point**) malloc(n*sizeof(struct point*))
  
    maze = (char**) malloc(n*sizeof(char*));
    int i;
    forn(i, n)
    maze[i] = (char*) malloc(m*sizeof(char));

    forn(i, n)  
    scanf("%s", maze[i]);  

    print_maze(n, m);
}
