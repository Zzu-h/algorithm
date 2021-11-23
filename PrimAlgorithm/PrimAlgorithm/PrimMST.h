#pragma once
#include "Heap.h"

class Graph {
private:
	Node* find_list[maxNum];								// graph�� ����� node�� list
public:
	void insert(int a, int b, int e);							// graph�� �����ϴ� method
	Node* getNode(int d) { return find_list[d]; }	// �ش��ϴ� data�� node pointer�� return�Ѵ�.
};

class PrimMST{
private:
	typedef pair<int, Node*> adjacency;
	Graph g;									// �ش� ������ ���� graph
	vector<int> print;					// ����� ��������� �����ϴ� vector
	void answerPrint(int count);	// ��� ��������� ����ϴ� �޼ҵ�
public:
	// graph g�� node �������� insert�ϴ� �޼ҵ�
	void graphInsert(int a, int b, int e) { g.insert(a, b, e);	}
	void prims(int idx);	// ���� prim �˰����� �����ϴ� �޼ҵ�
};