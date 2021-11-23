#include "PrimMST.h"
// graph에 insert함
void Graph::insert(int a, int b, int e) {
	Node* a_node, * b_node;
	a_node = find_list[a]; b_node = find_list[b];
	// 저장된 node가 없을 경우 새 node를 생성해 삽입한다.
	if (a_node == nullptr) {
		a_node = new Node(a);
		find_list[a] = a_node;
	}
	if (b_node == nullptr) {
		b_node = new Node(b);
		find_list[b] = b_node;
	}
	// 그 후 각자의 edge를 연결해 준다.
	a_node->insert(b_node, e);
	b_node->insert(a_node, e);
}

void PrimMST::prims(int d) {
	bool tree[maxNum] = { 0, };
	int id , counter = 0;
	Heap fringe(-1);		// minHeap으로 가치가 낮은게 우선순위가 높다.
	tree[d] = true;

	// 자기 자신부터 fringe set으로 포함시키고 tree만들기를 시작한다. 자기자신과의 관계는 0
	fringe.insert({ 0,  g.getNode(d) });
	while (!fringe.isEmpty()) {
		adjacency t = fringe.pop();										// fringe set에서 가장 가치가 낮은, 우선순위가 가장 높은 값을 꺼내온다.
		Node* curNode = t.node; counter += t.price;		// fringe set에서 꺼내온 가치는 총합에 저장, node는 curNode에 저장
		tree[curNode->data] = true;									// 꺼내온 data는 tree set에 포함된다.
		print.push_back(curNode->data);							// 출력 결과물에 출력할 data를 담는다.
		for (size_t i = 0; i < curNode->adj.size(); i++) {
			adjacency temp = curNode->adj[i];
			// 만일 인접 node가 tree에 존재한다면 fringe set을 돌지 않는다.
			if (!tree[temp.node->data]) {
				if ((id = fringe.find(temp.node)) != -1)			// tree에 존재하지 않고, fringe set에 존재한다면,
					fringe.update(id, temp.price);						// fringe set에 data의 가치를 변경한다.
				else
					fringe.insert(curNode->adj[i]);					// tree에도 존재하지 않고, fringe set에도 존재하지 않다면,  fringe set에 삽입
			}
		}
	}
	answerPrint(counter);
	print.clear();
}

// counter를 입력받아 총합과 함께 출력할 요소들을 모두 출력한다.
void PrimMST::answerPrint(int counter) {
	cout << counter;
	for (size_t i = 0; i < print.size(); i++) {
		cout << ' ' << print[i];
	}
	cout << '\n';
}