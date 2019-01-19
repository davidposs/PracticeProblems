#include "binarySearchTree.h"

/* Constructors */
template <typename T>
BinarySearchTree<T>::Node::Node() : _left(nullptr), _right(nullptr) {}

template <typename T>
BinarySearchTree<T>::Node::Node(const T val) : _left(nullptr), _right(nullptr), _data(val) {}

template <typename T>
BinarySearchTree<T>::BinarySearchTree() : _root(nullptr) {}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(const T data) : _root(std::unique_ptr<Node>(new Node(data))) {}

template <typename T>
bool BinarySearchTree<T>::find(const T val) const {
	return find(_root, val);
}

template <typename T>
bool BinarySearchTree<T>::find(const std::unique_ptr<Node>& root, const T val) const {
	if (root == nullptr) {
		return false;
	}
	else if (val == root->_data) {
		return true;
	}
	else if (val > root->_data) {
		return find(root->_right, val);
	}
	else {
		return find(root->_right, val);
	}
}

template <typename T>
void BinarySearchTree<T>::insert(const T val) {
	insert(_root, val);
}

template <typename T>
void BinarySearchTree<T>::insert(std::unique_ptr<Node>& root, const T val) {
	if (!root) {
		root = std::unique_ptr<Node>(new Node(val));
		return;
	}
	else if (root->_data == val) {
		std::cout << val << " already in tree!" << std::endl;
	}
	else if (root->_data > val) {
		insert(root->_left, val);
	}
	else {
		insert(root->_right, val);
	}
}

template <typename T>
void BinarySearchTree<T>::remove(const T val) {
	remove(_root, val);
}

template <typename T>
void BinarySearchTree<T>::remove(std::unique_ptr<Node>& root, const T val) {
	if (!root) {
		return;
	}
	if (val == root->_data) {
		removeRoot(root);
	}
	else if (root->_data > val) {
		remove(root->_left, val);
	}
	else if (root->_data < val) {
		remove(root->_right, val);
	}
}


template <typename T>
void BinarySearchTree<T>::removeRoot(std::unique_ptr<Node>& root) {
	std::unique_ptr<Node> delNode = std::move(root);
	T oldValue = delNode->_data;
	if (!delNode->_left && !delNode->_right) {
		delNode.release();
	}
	else if (delNode->_left && !delNode->_right) {
		root = std::move(delNode->_left);
		delNode.release();
		std::cout << "Deleted " << oldValue << " from tree. " << std::endl;
	}
	else if (delNode->_right && !delNode->_left) {
		root = std::move(delNode->_right);
		delNode.release();
		std::cout << "Deleted " << oldValue << " from tree. " << std::endl;
	}
	else if (delNode->_right && delNode->_left) {
		// Create new subtree based of smallest element in right subtree
		T minimum = min(delNode->_right);
		oldValue = delNode->_data;
		remove(delNode, minimum);
		delNode->_data = minimum;
		std::cout << "Replaced old key " << oldValue << " with " << minimum << std::endl;
	}
}

template <typename T>
T BinarySearchTree<T>::min(std::unique_ptr<Node>& root) {
	if (root->_left == nullptr) {
		return root->_data;
	}
	return min(root->_left);
}


// Traversals
template <typename T>
std::ostream& BinarySearchTree<T>::print(std::ostream& os) const {
	os << "Printing tree INORDER: [";
	print(os, _root);
	os << '\b' << "]";
	os << std::endl;
	return os;
}

template <typename T>
void BinarySearchTree<T>::print(std::ostream& os, const std::unique_ptr<Node>& root) const {
	if (!root) {
		os << '\b';
	}
	printInOrder(root->_left);
	os << root->_data << " ";
	printInOrder(root->_right);
}


template <typename T>
void BinarySearchTree<T>::printInOrder() const {
	std::cout << "Printing in order: [";
	printInOrder(_root);
	std::cout << "\b]" << std::endl;
}

template <typename T>
void BinarySearchTree<T>::printInOrder(const std::unique_ptr<Node>& root) const {
	if (!root) {
		return;
	}
	printInOrder(root->_left);
	std::cout << root->_data << " ";
	printInOrder(root->_right);
}

template <typename T>
void BinarySearchTree<T>::printPostOrder() const {
	std::cout << "Printing post order: [";
	printPostOrder(_root);
	std::cout << "\b]" << std::endl;
}

template <typename T>
void BinarySearchTree<T>::printPostOrder(const std::unique_ptr<Node>& root) const {
	if (!root) {
		return;
	}
	printPostOrder(root->_left);
	printPostOrder(root->_right);
	std::cout << root->_data << " ";
}

template <typename T>
void BinarySearchTree<T>::printPreOrder() const {
	std::cout << "Printing pre order: [";
	printPreOrder(_root);
	std::cout << "\b]" << std::endl;
}

template <typename T>
void BinarySearchTree<T>::printPreOrder(const std::unique_ptr<Node>& root) const {
	if (!root) {
		return;
	}
	std::cout << root->_data << " ";
	printPreOrder(root->_left);
	printPreOrder(root->_right);
}

// Test function
void test_binarySearchTree() {
	std::unique_ptr<BinarySearchTree<int>> tree = std::make_unique<BinarySearchTree<int>>(10);

	tree->insert(12);
	tree->insert(1);
	tree->insert(10);
	tree->insert(13);
	if (tree->find(13)) {
		std::cout << " found!" << std::endl;
	}
	for (int i = 0; i < 10; i++) {
		tree->insert(static_cast<int>(rand() % 15) + 0);
	}
	std::cout << "Before removing 13: " << std::endl;
	tree->printInOrder();
	tree->printPostOrder();
	tree->printPreOrder();
	std::cout << "After removing 13: " << std::endl;
	tree->remove(13);
	tree->printInOrder();
	tree->printPostOrder();
	tree->printPreOrder();
	std::cout << tree;
}


