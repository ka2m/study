#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <queue>

using namespace std;

const int dx[8] = {1, 1, 0, -1, -1, -1, 0, 1};
const int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};
// const int dx[4]={1, 0, -1, 0};
// const int dy[4]={0, 1, 0, -1};

struct point {
    int x;
    int y;
};

int n, m;
vector<vector<char> > maze;
map<point, bool> endpoints;

bool operator <(const point &x, const point &y) {
    if(x.x != y.x)
        return x.x < y.x;
    return x.y < y.y;
}

bool check(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m && maze[x][y] != '*';
}

void print_maps(map<point, int> p) {
    for (map<point, int>::iterator it = p.begin(); it != p.end(); ++it)
    {
        printf("%d %d: %d\n", it->first.x, it->first.y, it->second);
    }

}

void print_maze() {
    for (vector<vector<char> >::iterator it = maze.begin(); it != maze.end(); ++it) {
        for (vector<char>::iterator ti = it->begin(); ti != it->end(); ++ti) {
            printf("%c", *ti);
        }
        printf("\n");   
    }
}


map<point, int> bfs(point start) {
    queue<point> q;
    map<point, int> result;
    vector<vector<bool> > used(n, vector<bool>(m, false));
    
    q.push(start);

    while(!q.empty()) {
        point cur = q.front();
        q.pop();
        
        for(int i=0; i<8; i++) {
            int x = cur.x + dx[i];
            int y = cur.y + dy[i];
            point to = {x, y};

            if(check(x, y) && !used[x][y]) {                

                q.push(to);
                used[x][y] = true;
                result[to] = result[cur]+1;
    
            }
        }
    }

    return result;
}

int main(void) {
    freopen("input", "r", stdin);
    freopen("output", "w", stdout);

    scanf("%d %d\n", &n, &m);
    maze.resize(n);

    point start, end;
    printf("%d %d\n", n, m);

    for (int i=0; i<n; i++) {
        maze[i].resize(m);
        for (int j=0; j<m; j++) {
            cin>>maze[i][j];            
            if (maze[i][j] == 's') {
                start.x = i;
                start.y = j;
            }
            else if (maze[i][j] == 'f') {
                end.x = i;
                end.y = j;              
                endpoints[end] = true;
            }           
         }         
     }
    
    printf("start: (%d, %d)\n", start.x, start.y);
    printf("end: (%d, %d)\n", end.x, end.y);

    map<point, int> start_to_finish = bfs(start);
    printf("s->f ways:\n");
    print_maps(start_to_finish);

    endpoints.clear();
    endpoints[end] = true;
    
    map<point, int> finish_to_start = bfs(end);
    printf("f->s ways:\n");
    print_maps(finish_to_start);

   

   for (map<point, int>::iterator it=start_to_finish.begin(); it != start_to_finish.end(); ++it) {        
            if (it->second + finish_to_start.find(it->first)->second == start_to_finish[end])
                maze[it->first.x][it->first.y] = 'x';
        
   }
   print_maze();   

  

}
