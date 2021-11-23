#include "PrimMST.h"
int n, m, q;
int a, b, e;
char c;
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	cin >> n >> m >> q;
	PrimMST p;
	// graph(n) 积己 
	while (m--) {
		// edge insert 何盒
		cin >> a >> b >> e;
		p.graphInsert(a, b, e);
	}
	while (q--) {
		// 免仿何盒
		cin >> c >> a;
		p.prims(a);
	}
}