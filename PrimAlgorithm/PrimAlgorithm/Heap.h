#pragma once
#include<iostream>
#include<vector>
using namespace std;

#define children  adj
#define price first
#define node second
#define maxNum 100001

// graph�� node
class Node {
private:
	typedef pair<int, Node*> adjacency;
public:
	// ���� ��尡 ����� vector
	vector<adjacency> adj;
	int data;		//�ڱ� �ڽ��� ������ ��ȣ
	Node(int d) {
		this->data = d;
	}
	// ���� ������ �Էµ� �� �� �޼ҵ带 ���� insert
	void insert(Node* b, int e) {
		adj.push_back({ e, b });
	}
};

// heap structure
class Heap {
private:
	typedef pair<int, Node*> adjacency;
	vector<adjacency> v;		// heap �迭
	int heap_size;					// heap�� ����� ����� size
	int root_index;					// �⺻������ ����� root Index = 1

	// minHeap / maxHeap�� �����ϴ� ��� -> 1�� ��� maxHeap / -1�� ��� minHeap
	int direction;					

	// �� ��Ҹ� �ٲٴ� �޼ҵ�
	void swap(int idx1, int idx2);
	void upHeap(int idx);
	void downHeap(int idx);
	// upHeap�� downHeap�� �����ϴ� �� �޼ҵ�
	bool greaterComparator(adjacency& a, adjacency& b);
public:
	Heap(int direction) {
		v.push_back({ -1, new Node(-1) });
		this->heap_size = 0;
		this->root_index = 1;
		this->direction = direction * -1;
	}
	void insert(adjacency e);		// insert �޼ҵ�
	pair<int, Node*> pop();		// pop �޼ҵ�, ������ ���ÿ� ���� top�� ������� return�Ѵ�.
	Node* top();						// ���� ���� �켱������ ���� Node�� return �Ѵ�.
	int size();								// ���� heap�� ����� ����� size
	bool isEmpty();					// heap�� ����ִ��� Ȯ���ϴ� �޼ҵ�
	int find(Node * e);				// ���ϴ� ��Ҹ� ã�� heap�� ����� index�� return
	void update(int idx, int p);	// index�� �޾� �ش� index�� ����� data�� �����ϴ� �޼ҵ�
};