#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
using namespace std;

struct cell {
	int x, y;
	bool equals(cell a);
};

bool cell::equals(cell a) {
	return (x == a.x) && (y == a.y);
}

bool operator <(const cell &x, const cell &y) {
    if(x.x != y.x)
        return x.x < y.x;
    return x.y < y.y;
}

const int MAX = 50;
vector<vector<int> > field(MAX, vector<int>(MAX));
vector<string> solution;
queue<cell> q;
map<cell, int> d;
map<cell, string> p;
int dx[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dy[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
string dname[8] = { "N", "NE", "E", "SE", "S", "SW", "W", "NW" };
cell start, finish, immutableFinish;
int n, m;


void updatePosition(string dir, cell& curCell) {
	if (dir == "N" || dir == "NE" || dir == "NW")
		curCell.x --;
	if (dir == "S" || dir == "SE" || dir == "SW")
		curCell.x ++;
	if (dir == "W" || dir == "SW" || dir == "NW")
		curCell.y --;
	if (dir == "E" || dir == "SE" || dir == "SW")
		curCell.y ++;
}

void evaluateSolution() {
	reverse(solution.begin(), solution.end());
	cell curCell; 
	curCell.x = start.x;
	curCell.y = start.y;
	for (auto s: solution) {
		cout << s << " ";
		updatePosition(s, curCell);
		field[curCell.x][curCell.y] = 2;
	}
	cout<<endl;
}

void printField() {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (start.x == i && start.y == j)
				cout<<"S";
			else if (immutableFinish.x == i && immutableFinish.y == j)
				cout<<"F";
			else if (field[i][j] == 2)
				cout<<"x";
			else if (field[i][j] == 1)
				cout << "#";
			else cout << ".";
		}
		cout << endl;
	}	
}

int find(string s) {
	for (int i = 0; i < 8; ++i) {
		if (dname[i] == s) {
			return i;
		}
	}

	return -1;
}

bool check(int x, int y) {
	return (x >= 0) && (x < n) && (y >= 0) && (y < m) && (field[x][y] == 0);
}

int main() {
	freopen("input", "r", stdin);
	freopen("output", "w", stdout);
	cin >> n >> m;

	string line;
	char c;
	for (int i = 0; i < n; ++i) {
		cin >> line;

		for (int j = 0; j < m; ++j) {
			c = line[j];

			if (c == '.') {
				field[i][j] = 0;
			} else if (c == '#') {
				field[i][j] = 1;
			} else if (c == 'S') {
				start.x = i;
				start.y = j;
			} else if (c == 'F') {
				immutableFinish.x = i;
				finish.x = i;
				immutableFinish.y = j;
				finish.y = j;
			}
		}
	}

	q.push(start);
	d[start] = 0;
	int x, y, vx, vy;

	bool breaked = false;
	while (!q.empty()) {
		cell v = q.front();
		q.pop();

		x = v.x;
		y = v.y;
		for (int i = 0; i < 8; ++i) {
			vx = x;
			vy = y;

			vx += dx[i];
			vy += dy[i];
			
			cell to = { vx, vy };
			if (d.count(to) == 0 && check(vx, vy)) {
				d[to] = d[v] + 1;
				p[to] = dname[i];
				q.push(to);

				if (to.equals(finish)) {
					breaked = true;
					break;
				}
			}
		}

		if (breaked) {
			break;
		}
	}

	if (d.count(finish) == 0) {
		cout << -1;
		return 0;
	}
	
	printField();

	cout << endl << "Cells to go: " << d[finish] << endl;
	while (!start.equals(finish)) {
		string path = p[finish];
		int index = find(path);

		solution.push_back(path);

		finish.x -= dx[index];
		finish.y -= dy[index];
	}

	evaluateSolution();

	printField();

	return 0;
}