#include "PrimMST.h"
int n, m, q;
int a, b, e;
char c;
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	cin >> n >> m >> q;
	PrimMST p;
	// graph(n) ���� 
	while (m--) {
		// edge insert �κ�
		cin >> a >> b >> e;
		p.graphInsert(a, b, e);
	}
	while (q--) {
		// ��ºκ�
		cin >> c >> a;
		p.prims(a);
	}
}