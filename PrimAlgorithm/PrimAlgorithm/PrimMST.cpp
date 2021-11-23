#include "PrimMST.h"
// graph�� insert��
void Graph::insert(int a, int b, int e) {
	Node* a_node, * b_node;
	a_node = find_list[a]; b_node = find_list[b];
	// ����� node�� ���� ��� �� node�� ������ �����Ѵ�.
	if (a_node == nullptr) {
		a_node = new Node(a);
		find_list[a] = a_node;
	}
	if (b_node == nullptr) {
		b_node = new Node(b);
		find_list[b] = b_node;
	}
	// �� �� ������ edge�� ������ �ش�.
	a_node->insert(b_node, e);
	b_node->insert(a_node, e);
}

void PrimMST::prims(int d) {
	bool tree[maxNum] = { 0, };
	int id , counter = 0;
	Heap fringe(-1);		// minHeap���� ��ġ�� ������ �켱������ ����.
	tree[d] = true;

	// �ڱ� �ڽź��� fringe set���� ���Խ�Ű�� tree����⸦ �����Ѵ�. �ڱ��ڽŰ��� ����� 0
	fringe.insert({ 0,  g.getNode(d) });
	while (!fringe.isEmpty()) {
		adjacency t = fringe.pop();										// fringe set���� ���� ��ġ�� ����, �켱������ ���� ���� ���� �����´�.
		Node* curNode = t.node; counter += t.price;		// fringe set���� ������ ��ġ�� ���տ� ����, node�� curNode�� ����
		tree[curNode->data] = true;									// ������ data�� tree set�� ���Եȴ�.
		print.push_back(curNode->data);							// ��� ������� ����� data�� ��´�.
		for (size_t i = 0; i < curNode->adj.size(); i++) {
			adjacency temp = curNode->adj[i];
			// ���� ���� node�� tree�� �����Ѵٸ� fringe set�� ���� �ʴ´�.
			if (!tree[temp.node->data]) {
				if ((id = fringe.find(temp.node)) != -1)			// tree�� �������� �ʰ�, fringe set�� �����Ѵٸ�,
					fringe.update(id, temp.price);						// fringe set�� data�� ��ġ�� �����Ѵ�.
				else
					fringe.insert(curNode->adj[i]);					// tree���� �������� �ʰ�, fringe set���� �������� �ʴٸ�,  fringe set�� ����
			}
		}
	}
	answerPrint(counter);
	print.clear();
}

// counter�� �Է¹޾� ���հ� �Բ� ����� ��ҵ��� ��� ����Ѵ�.
void PrimMST::answerPrint(int counter) {
	cout << counter;
	for (size_t i = 0; i < print.size(); i++) {
		cout << ' ' << print[i];
	}
	cout << '\n';
}