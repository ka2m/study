#include <cstdio>
#include <queue>
#include <vector>
#define forn(i, n) for(i = 0; i<n; i++)
#define for2d(i, j, n, m) forn(i, n) forn(j, m)
using namespace std;
struct point {
    int x;
    int y;
}temp;

vector<point> graph;

vector<vector<char> > maze;

vector<int> paths;
vector<point> parents;

void print_maze() {
    int i, j;
    forn(i, maze.size()) { 
    forn(j, maze[i].size()) 
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
 
    getchar();
    maze.resize(n);

    int i;
    forn(i, n)
    maze[i].resize(m); 


    int j;
    forn(i, n) {
    forn(j, m)
        maze[i][j] = getchar();
    getchar();
    }

    struct point start_point;
    forn(i, n) 
    forn(j, m) 
        if (maze[i][j]=='s') {
            start_point.x = i;
            start_point.y = j;
            break;
        }

    for2d(i, j, n, m) {
        temp.x = i;
        temp.y = j;
        graph.push_back(temp);   
    }
    paths.resize(n*m);
    parents.resize(n*m);

   
   print_maze();
   printf("startpoint: %d %d", start_point.x, start_point.y);
   bfs(start_point);

   forn(i, n)
    printf("%d %d\n",parents[i].x, parents[i].y);

}
