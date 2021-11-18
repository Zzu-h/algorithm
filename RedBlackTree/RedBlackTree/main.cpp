#include "RedBlackTreeVector.h"
#include<fstream>
char cmd;
int n;
RedBlackTreeVector tree;
ui id, space, price;
string name;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	//std::ofstream out("../../out.out");
	//std::streambuf* coutbuf = std::cout.rdbuf(); //save old buf
	//std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
	
	cin >> n;
	while (n--) {
		cin >> cmd;
		switch (cmd) {
		case 'I':	// insert app
			cin >> id >> name >> space >> price;
			cout << tree.insert(id, name, space, price) << '\n';
			break;
		case 'F':	// find app
			cin >> id;
			tree.find(id);
			break;
		case 'R':	// update app
			cin >> id >> name >> space >> price;
			tree.update(id, name, space, price);
			break;
		case 'D':	// discount
			ui x, y, P;
			cin >> x >> y >> P;
			tree.discount(x, y, P);
			break;
		default:
			break;
		}
	}
	return 0;
}