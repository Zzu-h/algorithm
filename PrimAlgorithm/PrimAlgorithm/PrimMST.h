#pragma once
#include "Heap.h"

class Graph {
private:
	Node* find_list[maxNum];								// graph에 저장될 node의 list
public:
	void insert(int a, int b, int e);							// graph에 저장하는 method
	Node* getNode(int d) { return find_list[d]; }	// 해당하는 data의 node pointer를 return한다.
};

class PrimMST{
private:
	typedef pair<int, Node*> adjacency;
	Graph g;									// 해당 문제에 사용될 graph
	vector<int> print;					// 출력할 결과물들을 저장하는 vector
	void answerPrint(int count);	// 모든 결과물들을 출력하는 메소드
public:
	// graph g에 node 정보들을 insert하는 메소드
	void graphInsert(int a, int b, int e) { g.insert(a, b, e);	}
	void prims(int idx);	// 실제 prim 알고리즘을 수행하는 메소드
};