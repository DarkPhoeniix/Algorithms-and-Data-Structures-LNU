#pragma once
#include <iostream>
#include <vector>

template <typename T>
class AVL_Tree
{
public:
	AVL_Tree();
	~AVL_Tree();

	void insert(const T& data);
	void erase(const T& data);
	bool find(const T& data) const;
	std::vector<T> treeToVector() const;

private:
	class Node {
	public:
		T data;
		int height;
		Node* left;
		Node* right;

		Node(const T& data);
		Node(const Node& copy);
		~Node();
	};
	Node* root;

	int _height(const Node* node) const;
	void simpleLeftRotation(Node*& subtree);
	void simpleRightRotation(Node*& subtree);
	void doubleLeftRotation(Node*& subtree);
	void doubleRightRotation(Node*& subtree);
	void rebalance(Node*& node);
	void _insert(Node*& node, const T& data);
	void _erase(Node*& node, const T& data);
	bool _find(Node* node, const T& data) const;
	void _treeToVector(Node* node, std::vector<T>& container) const;
};



template<typename T>
AVL_Tree<T>::Node::Node(const T& data)
	: data(data), height(1), left(nullptr), right(nullptr)
{	}

template<typename T>
AVL_Tree<T>::Node::Node(const Node& copy)
	: data(copy.data), height(copy.height), left(copy.left), right(copy.right)
{	}

template<typename T>
AVL_Tree<T>::Node::~Node()
{	}	



template<typename T>
AVL_Tree<T>::AVL_Tree()
	: root(nullptr)
{	}

template<typename T>
AVL_Tree<T>::~AVL_Tree()
{	
	while (this->root != nullptr) {
		_erase(this->root, this->root->data);
	}
}

template<typename T>
void AVL_Tree<T>::insert(const T& data)
{
	_insert(this->root, data);
}

template<typename T>
void AVL_Tree<T>::erase(const T& data)
{
	_erase(this->root, data);
}

template<typename T>
bool AVL_Tree<T>::find(const T& data) const
{
	return _find(root, data);
}

template<typename T>
std::vector<T> AVL_Tree<T>::treeToVector() const
{
	std::vector<T> container;
	_treeToVector(root, container);
	return container;
}

template<typename T>
inline int AVL_Tree<T>::_height(const Node* node) const
{
	if (node != nullptr) {
		return node->height;
	}
	return 0;
}

template<typename T>
void AVL_Tree<T>::simpleLeftRotation(Node*& subtree)
{
	Node* n = subtree, *nr = subtree->right;
	n->right = nr->left;
	nr->left = n;
	if (_height(subtree->left) > _height(subtree->right)) {
		subtree->height = 1 + _height(subtree->left);
	} else {
		subtree->height = 1 + _height(subtree->right);
	}
	subtree = nr;
}

template<typename T>
void AVL_Tree<T>::simpleRightRotation(Node*& subtree)
{
	Node* n = subtree, *nl = subtree->left;
	n->left = nl->right;
	nl->right = n;
	if (_height(subtree->left) > _height(subtree->right)) {
		subtree->height = 1 + _height(subtree->left);
	}
	else {
		subtree->height = 1 + _height(subtree->right);
	}
	subtree = nl;
}

template<typename T>
void AVL_Tree<T>::doubleLeftRotation(Node*& subtree)
{
	simpleRightRotation(subtree->right);
	simpleLeftRotation(subtree);
}

template<typename T>
void AVL_Tree<T>::doubleRightRotation(Node*& subtree)
{
	simpleLeftRotation(subtree->left);
	simpleRightRotation(subtree);
}

//    a				        b
//   / \				   / \
//  l   b      -->        a   r
//	   / \               / \
//	  c   r             l   c

//   a                       c
//  / \                    /  \
// l   b                  a     b
//    / \      -->       / \   / \
//   c   r              l   m n   r
//  / \
// m   n


template<typename T>
void AVL_Tree<T>::rebalance(Node*& node)
{
	if (node == nullptr) {
		return;
	}
	if (_height(node->left) - _height(node->right) == -2) {
		if (node->right != nullptr && _height(node->right->left) - _height(node->right->right) == 1) {
			doubleLeftRotation(node);
		} else {
			simpleLeftRotation(node);
		}
	}
	if (_height(node->left) - _height(node->right) == 2) {
		if (node->left != nullptr && _height(node->left->left) - _height(node->left->right) == -1) {
			doubleRightRotation(node);
		} else {
			simpleRightRotation(node);
		}
	}

	if (_height(node->left) > _height(node->right)) {
		node->height = 1 + _height(node->left);
	} else {
		node->height = 1 + _height(node->right);
	}
}

template<typename T>
void AVL_Tree<T>::_insert(Node*& node, const T& data)
{
	if (node == nullptr) {
		node = new Node(data);
	} else {
		if (data < node->data) {
			_insert(node->left, data);
		} else if (data > node->data) {
			_insert(node->right, data);
		}
	}
	rebalance(node);
}

template<typename T>
void AVL_Tree<T>::_erase(Node*& node, const T& data)
{
	if (node != nullptr) {
		if (node->data == data) {
			Node* child = nullptr;
			if (node->left != nullptr && node->right != nullptr) {
				child = node->right;
				while (child->left != nullptr) {
					child = child->left;
				}
				node->data = child->data;
				_erase(node->right, child->data);
			} else if (node->left != nullptr || node->right != nullptr) {
				if (node->left != nullptr && node->right == nullptr) {
					child = node->left;
				}
				else if (node->left == nullptr && node->right != nullptr) {
					child = node->right;
				}
				delete node;
				node = child;
			} else {
				delete node;
				node = nullptr;
			}
		} else {
			if (data < node->data) {
				_erase(node->left, data);
			} else {
				_erase(node->right, data);
			}
		}
	} else {
		throw std::exception("Error: uninitialized node");
	}
	rebalance(node);
}

template<typename T>
void AVL_Tree<T>::_treeToVector(Node* node, std::vector<T>& container) const
{
	if (node != nullptr) {
		_treeToVector(node->left, container);
		container.push_back(node->data);
		_treeToVector(node->right, container);
	}
}

template<typename T>
bool AVL_Tree<T>::_find(Node* node, const T& data) const
{
	if (node != nullptr) {
		if (node->data == data) {
			return true;
		} else if (data< node->data){
			_find(node->left, data);
		} else {
			_find(node->right, data);
		}
	}
	else {
		return false;
	}
}
