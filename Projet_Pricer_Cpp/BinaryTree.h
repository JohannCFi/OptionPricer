#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <iostream>
#include <vector>



template <typename T>

class BinaryTree
{

private:

	std::vector<std::vector<T>> _tree;
	int _depth;

public:
	BinaryTree()
		: _depth(0) {
	}

	void setDepth(int depth) {
		_depth = depth;
		_tree.resize(depth + 1);
		for (int n = 0; n <= depth; ++n) {
			_tree[n].resize(n + 1);
		}
	}

	void setNode(int n, int i, T value) {
		_tree.at(n).at(i) = value;
	}

	T getNode(int n, int i) const {
		return _tree.at(n).at(i);
	}

	void display() const {
		for (int n = 0; n <= depth; ++n) {
			for (int i = 0; i <= n; ++i) {
				std::cout << getNode(n, i) << "";
			}
			std::cout << std::endl;
		}
	}



};
#endif 