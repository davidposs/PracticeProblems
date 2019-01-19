#ifndef _BINARY_SEARCH_TREE_H
#define _BINARY_SEARCH_TREE_H

#include "beginnerProblems.h"

#include <memory>

void test_binarySearchTree();

template <typename T>
class BinarySearchTree {
public:
	BinarySearchTree();
	BinarySearchTree(const T);
	inline bool find(const T) const;
	inline void insert(const T);
	inline void remove(const T);
	inline void printInOrder() const;
	inline void printPostOrder() const;
	inline void printPreOrder() const;
	inline std::ostream& print(std::ostream&) const;
	friend std::ostream& operator<<(std::ostream& os, const std::unique_ptr<BinarySearchTree<T>>& root) {
		return root->print(os);
	}
private:
	struct Node {
		Node();
		Node(const T);
		std::unique_ptr<Node> _left;
		std::unique_ptr<Node> _right;
		T _data;
	};

	/* Private methods */
	bool find(const std::unique_ptr<Node>&, const T) const;
	void insert(std::unique_ptr<Node>&, const T);
	void remove(std::unique_ptr<Node>&, const T);
	void removeRoot(std::unique_ptr<Node>&);
	T min(std::unique_ptr<Node>&);
	
	void print(std::ostream&, const std::unique_ptr<Node>&)   const;
	void printPreOrder(const std::unique_ptr<Node>&)  const;
	void printPostOrder(const std::unique_ptr<Node>&) const;
	void printInOrder(const std::unique_ptr<Node>&)   const;

	/* Private Members */
	std::unique_ptr<Node> _root;
};

#endif /* _BINARY_SEARCH_TREE_H */