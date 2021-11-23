#include "Heap.h"

// node의 우선순위를 정하는 비교연산자이다.
bool Heap::greaterComparator(adjacency &a, adjacency& b) {
	if (a.price == b.price)
		return a.node->data * direction > b.node->data * direction;
	return a.price * direction > b.price * direction;
}
// 두 요소간에 위치를 변경한다.
void Heap::swap(int idx1, int idx2) {
	v[0] = v[idx1];
	v[idx1] = v[idx2];
	v[idx2] = v[0];
}
// upHeap 수행
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
// downHeap 수행
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
// Heap insert 수행, heap size 증가
void Heap::insert(adjacency e) {
	v.push_back(e);
	heap_size++;
	upHeap(heap_size);
}
// heap의 최상위 노드를 삭제와 동시에 해당 값을 return, heap size 감소
pair<int, Node*> Heap::pop() {
	adjacency top = v[root_index];
	v[root_index] = v[heap_size];
	heap_size--;
	v.pop_back();
	downHeap(root_index);
	return top;
}

// primMST에선 쓰이진 않음
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

// 입력된 node의 Heap 배열 index를 찾아 return, 못 찾을 경우 -1을 return
int Heap::find(Node* e) {
	for(size_t i = 1;i < v.size(); i++)
		if(v[i].node->data == e->data) return i;
	return -1;
}
// 이미 저장된 값의 가치와 새로 들어온 가치 p를 비교
void Heap::update(int idx, int p) {
	// p가 더 작을경우 값을 변경한다. 그 후 upHeap을 수행(새로 바뀐 값이 적어도 우선순위가 더 높다.)
	if (v[idx].price * direction > p * direction) {
		v[idx].price = p;
		upHeap(idx);
	}
}