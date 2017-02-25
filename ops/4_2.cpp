#include <bits/stdc++.h>
using namespace std;
#define forn(i, n) for (int i = 0; i < int(n); ++i)

typedef pair<int,int> pt;
#define x first
#define y second
#define pb push_back

const int N = 100;

int n, m;
int p[N], d[N];
bool used[N];
int c[N][N];
int C[N][N];

bool was[N][N];

int go(int v, int f) {
	used[v] = true;

	if (v == n - 1) {
		used[v] = false;
		return f;
	}

	vector <pt> g;
	forn(i, n) {
		if (v < i && c[v][i] && !used[i])
			g.pb(pt(-c[v][i], i));
	}

	sort(g.begin(), g.end());

	for (pt p: g) {
		int gg = go(p.y, min(f, -p.x));
		if (gg) {
			c[v][p.y] -= gg;
			c[p.y][v] += gg;
			used[v] = false;
			cerr << v + 1 << " ";
			return gg;
		}
	}

	used[v] = false;
	return 0;
}

int main() {
	assert(freopen("input.txt", "r", stdin));
	assert(cin >> n >> m);
	forn(_, m) {
		int u, v, w;
		assert(cin >> u >> v >> w);
		--u, --v;
		c[u][v] = w;
		C[u][v] = w;
		was[u][v] = was[v][u] = true;
	}

	int flow = 0;
	int gg = 0;
	do {
		gg = go(0, int(1e9));
		cerr << endl;
		cerr << gg << endl;
		flow += gg;
/*		forn(i, n) {
			forn(j, n) {
			cerr << c[i][j] << " ";
			}
		cerr << endl;
		}*/
	} while (gg);

	cout << flow << endl;
	forn(i, n)
		forn(j, n)
			if (i < j && was[i][j]) {
				int delta = C[i][j] - c[i][j];
				cout << i + 1 << " " << j + 1 << " " << delta << endl;
			}
		
	return 0;
}
