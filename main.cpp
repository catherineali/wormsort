#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int n, m, p[100000], a[100000], b[100000], w[100000], mark[100000];
int lo = 1e9, hi;
vector <int> adj[100000];

void dfs(int cow, int fill) {
	mark[cow] = fill;
	for (int i : adj[cow]) {
		if (!mark[i]) {
			dfs(i, fill);
		}
	}
}

bool wormsort(int x) {
	int cur = 1;
	for (int i = 0; i < n; i++) {
		mark[i] = 0;
		adj[i].clear();
	}
	for (int i = 0; i < m; i++) {
		if (w[i] >= x) {
			adj[a[i]].push_back(b[i]);
			adj[b[i]].push_back(a[i]);
		}
	}
	for (int i = 0; i < n; i++) {
		if (!mark[i]) {
			dfs(i, cur);
			cur++;
		}
	}
	for (int i = 0; i < n; i++) {
		if (mark[p[i]] != mark[i]) {
			return 0;
		}
	}
	return 1;
}

bool sorted() {
	for (int i = 0; i < n; i++) {
		if (p[i] != i) {
			return 0;
		}
	}
	return 1;
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> p[i];
		p[i]--;
	}
	for (int i = 0; i < m; i++) {
		cin >> a[i] >> b[i] >> w[i];
		a[i]--, b[i]--;
		lo = min(lo, w[i]);
		hi = max(hi, w[i]);
	}
	if (sorted()) {
		cout << -1 << endl;
		return 0;
	}
	while (lo < hi) {
		int mid = (lo + hi + 1) / 2;
		if (wormsort(mid)) {
			lo = mid;
		}
		else {
			hi = mid - 1;
		}
	}
	cout << lo << endl;
}