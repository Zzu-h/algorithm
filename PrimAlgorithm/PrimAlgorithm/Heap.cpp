#include "Heap.h"

// node�� �켱������ ���ϴ� �񱳿������̴�.
bool Heap::greaterComparator(adjacency &a, adjacency& b) {
	if (a.price == b.price)
		return a.node->data * direction > b.node->data * direction;
	return a.price * direction > b.price * direction;
}
// �� ��Ұ��� ��ġ�� �����Ѵ�.
void Heap::swap(int idx1, int idx2) {
	v[0] = v[idx1];
	v[idx1] = v[idx2];
	v[idx2] = v[0];
}
// upHeap ����
void Heap::upHeap(int idx) {
	if (idx == root_index)
		return;
	else {
		int parent = idx / 2;
		if (greaterComparator(v[parent], v[idx])) {
			swap(parent, idx);
			upHeap(parent);
		}
	}
}
// downHeap ����
void Heap::downHeap(int idx) {
	int left = idx * 2;
	int right = idx * 2 + 1;
	if (right <= heap_size) {
		if (!greaterComparator(v[left], v[right])) {
			if (!greaterComparator(v[left], v[idx])) {
				swap(left, idx);
				downHeap(left);
			}
			else return;
		}
		else {
			if (!greaterComparator(v[right], v[idx])) {
				swap(right, idx);
				downHeap(right);
			}
			else return;
		}
	}
	else if (left <= heap_size) {
		if (!greaterComparator(v[left], v[idx])) {
			swap(left, idx);
			downHeap(left);
		}
		else return;
	}
	else return;
}
// Heap insert ����, heap size ����
void Heap::insert(adjacency e) {
	v.push_back(e);
	heap_size++;
	upHeap(heap_size);
}
// heap�� �ֻ��� ��带 ������ ���ÿ� �ش� ���� return, heap size ����
pair<int, Node*> Heap::pop() {
	adjacency top = v[root_index];
	v[root_index] = v[heap_size];
	heap_size--;
	v.pop_back();
	downHeap(root_index);
	return top;
}

// primMST���� ������ ����
Node* Heap::top() {
	if (isEmpty())
		return nullptr;
	return v[root_index].node;
}
int Heap::size() {
	if (isEmpty())
		return -1;

	return heap_size;
}
bool Heap::isEmpty() {
	if (heap_size == 0)
		return true;
	else
		return false;
}

// �Էµ� node�� Heap �迭 index�� ã�� return, �� ã�� ��� -1�� return
int Heap::find(Node* e) {
	for(size_t i = 1;i < v.size(); i++)
		if(v[i].node->data == e->data) return i;
	return -1;
}
// �̹� ����� ���� ��ġ�� ���� ���� ��ġ p�� ��
void Heap::update(int idx, int p) {
	// p�� �� ������� ���� �����Ѵ�. �� �� upHeap�� ����(���� �ٲ� ���� ��� �켱������ �� ����.)
	if (v[idx].price * direction > p * direction) {
		v[idx].price = p;
		upHeap(idx);
	}
}