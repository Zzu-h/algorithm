#include "RedBlackTree.h"
#define key id

ui RedBlackTree::getDepth(Node * node) {
	Node* temp = Root;
	ui count = 0;
	while (temp != nullptr) {
		if (temp->key == node->key) return count;
		else if (temp->key > node->key) temp = temp->left;
		else temp = temp->right;
		count++;
	}
	return count;
}

ui RedBlackTree::insert(ui id, string name, ui space, ui price) {
	Node* newNode;
	if (size == 0) {
		newNode = new Node(id, name, space, price);
		newNode->color = black;
		Root = newNode;
		this->size++;
		return 0;
	}
	else {
		newNode = findNode(id);
		if (newNode != nullptr) return getDepth(newNode);

		newNode = new Node(id, name, space, price);
		if (key < Root->key) {
			if (Root->left == nullptr) {
				Root->left = newNode;
				newNode->par = Root;
			}
			else
				LeftInsert(Root->left, newNode);
		}
		else if (key > Root->key) {
			if (Root->right == nullptr) {
				Root->right = newNode;
				newNode->par = Root;
			}
			else
				RightInsert(Root->right, newNode);
		}
		DoubleRedCheck(newNode);
	}
	this->size++;
	return getDepth(newNode);
}
void RedBlackTree::LeftInsert(Node* L, Node* newNode) {
	if (newNode->key < L->key) {
		if (L->left == nullptr) {
			L->left = newNode;
			newNode->par = L;
		}
		else
			LeftInsert(L->left, newNode);
	}
	else if (newNode->key > L->key) {
		if (L->right == nullptr) {
			L->right = newNode;
			newNode->par = L;
		}
		else
			RightInsert(L->right, newNode);
	}
}
void RedBlackTree::RightInsert(Node* R, Node* newNode) {
	if (newNode->key < R->key) {
		if (R->left == nullptr) {
			R->left = newNode;
			newNode->par = R;
		}
		else
			LeftInsert(R->left, newNode);
	}
	else if (newNode->key > R->key) {
		if (R->right == nullptr) {
			R->right = newNode;
			newNode->par = R;
		}
		else
			RightInsert(R->right, newNode);
	}
};
bool RedBlackTree::DoubleRedCheck(Node* node) { 
	//redblack 발생 시 true return
	if (node == Root) return false;
	if (!node->par->isRed()) return false;

	Node* temp;
	if (uncleColor(node) == black) { reStructure(node); return false; }
	else temp = reColoring(node);

	return DoubleRedCheck(temp);
}
bool RedBlackTree::uncleColor(Node* node) {
	Node* temp = node->par->par;
	if (temp->right == node->par)
		return temp->left == nullptr ? black : temp->left->color;
	else
		return temp->right == nullptr ? black : temp->right->color;
}
Node* RedBlackTree::reColoring(Node* node) {
	Node* temp = node->par->par;
	temp->left->color = black;
	temp->right->color = black;
	temp->color = (temp == Root ? black : red);
	return temp;
}
Node* RedBlackTree::reStructure(Node* node) {
	// node가 1 2 3이 존재할 때 각 case 순서는 preorder로 읽는다.
	Node* parent = node->par, * gparent = parent->par, *ggparent = gparent->par;
	Node* L, *R, *MID;
	if (gparent->key > parent->key)
		if (parent->key > node->key) {// case 1 : 3 2 1
			gparent->left = parent->right;
			if (parent->right != nullptr) parent->right->par = gparent;
			parent->right = gparent;
			L = node; MID = parent; R = gparent;
		}
		else {// case 2: 3 1 2
			parent->right = node->left;
			if (node->left != nullptr)node->left->par = parent;
			gparent->left = node->right;
			if (node->right != nullptr) node->right->par = gparent;

			node->left = parent;
			node->right = gparent;
			L = parent; MID = node; R = gparent;
		}
	else
		if (parent->key > node->key) { // case 3: 1 3 2
			parent->left = node->right;
			if (node->right != nullptr) node->right->par = parent;
			gparent->right = node->left;
			if (node->left != nullptr) node->left->par = gparent;

			node->left = gparent;
			node->right = parent;
			L = gparent; MID = node; R = parent;
		}
		else { // case 4: 1 2 3
			gparent->right = parent->left;
			if (parent->left != nullptr) parent->left->par = gparent;

			parent->left = gparent;
			L = gparent; MID = parent; R = node;
		}

	L->par = MID; R->par = MID; MID->par = ggparent;
	L->color = red; R->color = red; MID->color = black;
	if (ggparent != nullptr)
		ggparent->left == gparent ? ggparent->left = MID : ggparent->right = MID;
	else Root = MID;

	return L;
}

Node* RedBlackTree::findNode(int id) {
	Node* temp = Root;
	while (temp != nullptr) {
		if (temp->key == key) return temp;
		else if (temp->key > key) temp = temp->left;
		else temp = temp->right;
	}
	return temp;
}
void RedBlackTree::find(ui id) {
	Node* finding = findNode(id);
	if (finding == nullptr) cout << "NULL\n";
	else cout << getDepth(finding) << ' ' << finding->name << ' ' << finding->space << ' ' << finding->price << '\n';
}
void RedBlackTree::update(ui id, string name, ui space, ui price) {
	Node* finding = findNode(id);
	if (finding == nullptr) cout << "NULL\n";
	else { 
		finding->name = name;
		finding->space = space;
		finding->price = price;
		cout << getDepth(finding) << '\n';
	}
}
void RedBlackTree::discount(ui x, ui y, ui P) {
	this->disX = x; this->disY = y; this->disP = 100 - P;
	postOrder(Root);
	this->disX = 0; this->disY = 0; this->disP = 0;
}
void RedBlackTree::postOrder(Node* node) {
	if (node->left != nullptr && node->left->key >= disX)
		postOrder(node->left);
	if (node->right != nullptr && node->right->key <= disY)
		postOrder(node->right);

	if (node->key >= disX && node->key <= disY)
		node->price = (node->price * disP / 100);
}
void RedBlackTree::preOrder(Node* node) {
	if (node->key >= disX && node->key <= disY) node->price = (node->price * disP / 100);

	if (node->left != nullptr)
		preOrder(node->left);
	if (node->right != nullptr)
		preOrder(node->right);
}

//Node* RedBlackTree::reStructure(Node* node){
//	Node** arr = new Node * [3];
//	arr[0] = node; arr[1] = node->par; arr[2] = arr[1]->par;
//	Node* temp = arr[2]->par;
//	bool flag = (temp == nullptr);
//
//	bool isLeft = false;
//	if(!flag) isLeft = (temp->left == arr[2]);
//	// 정렬
//	for (size_t i = 0; i < 3; i++) for (size_t k = 0; k < 2 - i; k++)
//		if (arr[k]->key > arr[k + 1]->key) swap(arr[k], arr[k + 1]);
//	// 자식 매칭 및 color 매칭
//
//	arr[0]->right = (arr[1]->left == arr[0] ? arr[0]->right : arr[1]->left);		arr[0]->color = red;
//	arr[2]->left = (arr[1]->right == arr[2] ? arr[2]->left : arr[1]->right);		arr[2]->color = red;
//	arr[1]->left = arr[0]; arr[1]->right = arr[2]; arr[1]->color = black;
//
//	arr[0]->par = arr[1]; arr[2]->par = arr[1]; arr[1]->par = temp;
//	if(!flag) isLeft ? temp->left = arr[1] : temp->right = arr[1];
//	else Root = arr[1];
//	return arr[0];
//}

//void RedBlackTree::discount(ui x, ui y, ui P) {
//	this->disX = x; this->disY = y; this->disP = 100 - P;
//	preOrder(Root);
//	this->disX = 0; this->disY = 0; this->disP = 0;
//}

//ui RedBlackTree::insert(ui id, string name, ui space, ui price) {
//	Node* newNode;
//	if (size == 0) {
//		newNode = new Node(id, name, space, price);
//		newNode->color = black;
//		Root = newNode;
//		this->size++;
//		list.push_back(newNode);
//		return 0;
//	}
//	else {
//		newNode = findNode(id);
//		if (newNode != nullptr) return getDepth(newNode);
//
//		newNode = new Node(id, name, space, price);
//		if (key < Root->key) {
//			if (Root->left == nullptr) {
//				Root->left = newNode;
//				newNode->par = Root;
//			}
//			else
//				LeftInsert(Root->left, newNode);
//		}
//		else if (key > Root->key) {
//			if (Root->right == nullptr) {
//				Root->right = newNode;
//				newNode->par = Root;
//			}
//			else
//				RightInsert(Root->right, newNode);
//		}
//		list.push_back(newNode);
//		DoubleRedCheck(newNode);
//	}
//	this->size++;
//	return getDepth(newNode);
//}