#include "RedBlackTreeVector.h"

ui RedBlackTreeVector::getDepth(int id) {
	ui count = 0;
	ui idx = id % midx;
	int temp = Root;
	while (temp != nil) {
		if (temp  == idx) return count;
		else if (temp > idx) temp = list[temp]->left;
		else temp = list[temp]->right;
		count++;
	}

	return count;
}

ui RedBlackTreeVector::insert(ui id, string name, ui space, ui price) {
	int count = 0;
	if (size == 0) {
		Root = id % midx;
		list[Root] = new Node(name, space, price);
		list[Root]->color = black;
		list[Root]->par = nil;
		this->size++;
		return 0;
	}
	else {
		if (list[id % midx] != nullptr) return getDepth(id % midx);

		list[id % midx] = new Node(name, space, price);
		int temp = Root;		
		while (size >= count) {
			count++;
			if (temp > id%midx) {
				if (list[temp % midx]->left == nil) {
					list[temp % midx]->left = id % midx;
					list[id % midx]->par = temp % midx;
					break;
				}
				temp = list[temp % midx]->left;
			}
			else {
				if (list[temp % midx]->right == nil) {
					list[temp % midx]->right = id % midx;
					list[id % midx]->par = temp % midx;
					break;
				}
				temp = list[temp % midx]->right;
			}
		}

		DoubleRedCheck(id % midx);
		if (flagOfreStructuring) {
			count = getDepth(id % midx);
			flagOfreStructuring = false;
		}
	}
	this->size++;
	return count;
}
bool RedBlackTreeVector::DoubleRedCheck(int idx) {
	//redblack 발생 시 true return
	if (idx == Root) return false;
	if (!list[(list[idx]->par)]->color) return false;

	int temp;
	if (uncleColor(list[idx]) == black) { reStructure(idx); return false; }
	else temp = reColoring(list[idx]);

	return DoubleRedCheck(temp);
}
bool RedBlackTreeVector::uncleColor(Node* node) {
	Node* temp = list[list[node->par]->par];
	if (temp->right == node->par)
		return temp->left == nil ? black : list[temp->left]->color;
	else
		return temp->right == nil ? black : list[temp->right]->color;
}
int RedBlackTreeVector::reColoring(Node* node) {
	int ggparent = list[node->par]->par;
	Node* temp = list[ggparent];
	list[temp->left]->color = black;
	list[temp->right]->color = black;
	temp->color = (ggparent == Root ? black : red);
	return ggparent;
}
void RedBlackTreeVector::reStructure(int id) {
	// node가 1 2 3이 존재할 때 각 case 순서는 preorder로 읽는다.
	flagOfreStructuring = true;
	Node* node = list[id];
	int parent = node->par, gparent = list[parent]->par, ggparent = list[gparent]->par;
	int L, R, MID;
	if (gparent > parent) {
		if (parent > id)
		{// case 1 : 3 2 1
			list[gparent]->left = list[parent]->right;
			if (list[parent]->right != nil) list[list[parent]->right]->par = gparent;
			list[parent]->right = gparent;
			L = id; MID = parent; R = gparent;
		}
		else //if (parent < id)
		{// case 2: 3 1 2
			list[parent]->right = node->left;
			if (node->left != nil) list[node->left]->par = parent;
			list[gparent]->left = node->right;
			if (node->right != nil) list[node->right]->par = gparent;

			node->left = parent;
			node->right = gparent;
			L = parent; MID = id; R = gparent;
		}
	}
	else //if (gparent < parent)
	{
		if (parent > id)
		{ // case 3: 1 3 2
			list[parent]->left = node->right;
			if (node->right != nil) list[node->right]->par = parent;
			list[gparent]->right = node->left;
			if (node->left != nil) list[node->left]->par = gparent;

			node->left = gparent;
			node->right = parent;
			L = gparent; MID = id; R = parent;
		}
		else //if(parent < id)
		{ // case 4: 1 2 3
			list[gparent]->right = list[parent]->left;
			if (list[parent]->left != nil) list[list[parent]->left]->par = gparent;

			list[parent]->left = gparent;
			L = gparent; MID = parent; R = id;
		}
	}

	list[L]->par = MID; list[R]->par = MID; list[MID]->par = ggparent;
	list[L]->color = red; list[R]->color = red; list[MID]->color = black;
	if (ggparent != nil) 
		list[ggparent]->left == gparent ? list[ggparent]->left = MID : list[ggparent]->right = MID;
	else Root = MID;
}
void RedBlackTreeVector::find(ui id) {
	ui idx = id % midx;
	if (list[idx] == nullptr) cout << "NULL\n";
	else cout << getDepth(idx) << ' ' << list[idx]->name << ' ' << list[idx]->space << ' ' << list[idx]->price << '\n';
}
void RedBlackTreeVector::update(ui id, string name, ui space, ui price) {
	int finding = id % midx;
	if (list[finding] == nullptr) cout << "NULL\n";
	else {
		list[finding]->name = name;
		list[finding]->space = space;
		list[finding]->price = price;
		cout << getDepth(finding) << '\n';
	}
}
void RedBlackTreeVector::discount(ui x, ui y, ui P) {
	this->disX = x % midx; this->disY = y % midx; this->disP = 100 - P;
	postOrder(Root);
	this->disX = 0; this->disY = 0; this->disP = 0;
}
void RedBlackTreeVector::postOrder(int id) {
	if (list[id]->left != nil)
		postOrder(list[id]->left);
	if (list[id]->right != nil)
		postOrder(list[id]->right);

	if (id >= disX && id <= disY)
		list[id]->price = (list[id]->price * disP / 100);
}