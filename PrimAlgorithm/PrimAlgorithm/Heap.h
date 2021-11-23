#pragma once
#include<iostream>
#include<vector>
using namespace std;

#define children  adj
#define price first
#define node second
#define maxNum 100001

// graph의 node
class Node {
private:
	typedef pair<int, Node*> adjacency;
public:
	// 인접 노드가 저장될 vector
	vector<adjacency> adj;
	int data;		//자기 자신의 조형물 번호
	Node(int d) {
		this->data = d;
	}
	// 간선 정보가 입력될 때 이 메소드를 통해 insert
	void insert(Node* b, int e) {
		adj.push_back({ e, b });
	}
};

// heap structure
class Heap {
private:
	typedef pair<int, Node*> adjacency;
	vector<adjacency> v;		// heap 배열
	int heap_size;					// heap에 저장된 요소의 size
	int root_index;					// 기본적으로 저장될 root Index = 1

	// minHeap / maxHeap을 선택하는 요소 -> 1일 경우 maxHeap / -1일 경우 minHeap
	int direction;					

	// 두 요소를 바꾸는 메소드
	void swap(int idx1, int idx2);
	void upHeap(int idx);
	void downHeap(int idx);
	// upHeap과 downHeap을 결정하는 비교 메소드
	bool greaterComparator(adjacency& a, adjacency& b);
public:
	Heap(int direction) {
		v.push_back({ -1, new Node(-1) });
		this->heap_size = 0;
		this->root_index = 1;
		this->direction = direction * -1;
	}
	void insert(adjacency e);		// insert 메소드
	pair<int, Node*> pop();		// pop 메소드, 삭제와 동시에 가장 top의 결과물을 return한다.
	Node* top();						// 현재 가장 우선순위가 높은 Node를 return 한다.
	int size();								// 현재 heap에 저장된 요소의 size
	bool isEmpty();					// heap이 비어있는지 확인하는 메소드
	int find(Node * e);				// 원하는 요소를 찾아 heap에 저장된 index를 return
	void update(int idx, int p);	// index를 받아 해당 index의 요소의 data를 수정하는 메소드
};