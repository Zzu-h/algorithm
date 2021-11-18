#pragma once
#include<iostream>

using namespace std;
typedef unsigned int ui;
#define red true
#define black false
#define midx 1000000
#define nil -1

class Node {
public:
	string name;
	ui space;
	ui price;
	bool color;
	int left;
	int right;
	int par;
	Node(string name, ui space, ui price) {
		this->name = name;
		this->space = space;
		this->price = price;
		this->color = red;
		this->left = nil;
		this->right = nil;
		this->par = nil;
	}
	bool isRed() {
		return this->color;
	}
};

class RedBlackTreeVector {
private:
	int size;
	int Root;
	bool flagOfreStructuring = false;
	Node** list;
	ui disX, disY, disP;

	// Insertion 관련 메소드
	bool DoubleRedCheck(int idx);
	bool uncleColor(Node* node);
	int reColoring(Node* node);
	void reStructure(int id);

	ui getDepth(int id);

	// 전체 탐색을 위한 메소드
	void postOrder(int id); 
public:
	RedBlackTreeVector() {
		this->size = 0;
		Root = nil;
		this->disX = 0;
		this->disY = 0;
		this->disP = 0;
		list = new Node * [midx]();
	}

	ui insert(ui id, string name, ui space, ui price);
	void find(ui id);
	void update(ui id, string name, ui space, ui price);
	void discount(ui x, ui y, ui P);
};