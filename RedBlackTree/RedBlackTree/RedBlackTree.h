#pragma once
#include<iostream>

using namespace std;
typedef unsigned int ui;
#define red true
#define black false

class Node {
public:
	ui id;
	string name;
	ui space;
	ui price;
	bool color;
	Node* left;
	Node* right;
	Node* par;
	Node(ui id, string name, ui space, ui price) {
		this->id = id;
		this->name = name;
		this->space = space;
		this->price = price;
		this->color = red;
		this->left = nullptr;
		this->right = nullptr;
		this->par = nullptr;
	}
	bool isRed() {
		return this->color;
	}
};

class RedBlackTree {
private:
	int size;
	Node* Root;
	//vector<Node*> list;
	ui disX, disY, disP;

	// Insertion 관련 메소드
	void LeftInsert(Node* L, Node* newNode);
	void RightInsert(Node* R, Node* newNode);
	bool DoubleRedCheck(Node* newNode);
	bool uncleColor(Node* node);
	Node* reColoring(Node* node);
	Node* reStructure(Node* node);

	ui getDepth(Node* node);

	// Node찾기 관련 메소드
	Node* findNode(int data);

	// 전체 탐색을 위한 메소드
	void postOrder(Node* node);
	void preOrder(Node* node);
public:
	RedBlackTree() {
		this->size = 0;
		Root = nullptr;
		this->disX = 0;
		this->disY = 0;
		this->disP = 0;
	}

	ui insert(ui id, string name, ui space, ui price);
	void find(ui id);
	void update(ui id, string name, ui space, ui price);
	void discount(ui x, ui y, ui P);
};