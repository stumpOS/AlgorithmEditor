#pragma once
#ifndef BINARYTREE_H_
#define BINARYTREE_H_

#include<cstdlib>
#include<exception>
#include<typeinfo>
template<class T>
class BinaryTree
{
public:
	BinaryTree();
	virtual ~BinaryTree();
	void Destroy()
	{
		if(_root != NULL)
		{
			DestroySubtree(_root);
		}
	}

	class Node
	{
	public:
		friend class BinaryTree;
		Node(){_left=NULL;_right=NULL;}
		Node(const T &data)
		{
			_data = data;
			_left=NULL;
			_right=NULL;
		}
		~Node()
		{
			delete _data;
			_data = NULL;
		}
		T &GetNodeContents(){return _data;}
		Node *GetLeft(){return _left;}
		Node *GetRight(){return _right;}
		void SetLeftChild(Node *child){_left = child;}
		void SetRightChild(Node *child){_right = child;}

	private:
		Node *_left;
		Node *_right;
		T _data;
	};
	void AddChildTo(Node *node,T key)
	{
	
			if(node->GetNodeContents()>key && node->_left == NULL)
				node->_left = new Node(key);
			else if(node->GetNodeContents()<key && node->_right == NULL)
				node->_right = new Node(key);
			else if(node->GetNodeContents()==key)
				throw std::invalid_argument("already in tree");
			else
				throw std::invalid_argument("search failed");
		
	}

	template<class ComparableType>
	Node* Search(ComparableType key)
	{
		Node *result = NULL;

		if(_root != NULL)
		{
			result = Search<ComparableType>(_root, key);
		}
		return result;
	}
	void Initialize(T key)
	{
		_root = new Node(key);
	}
	virtual void Insert(T key) = 0;
	virtual void Delete(T key) = 0;

	int GetHeight(Node* root, int &height)
	{
		
		if(root != NULL)
		{
			int left_subtree_height = 0, right_subtree_height = 0;

			int left_height = GetHeight(root->_left, left_subtree_height);
			int right_height = GetHeight(root->_right, right_subtree_height);

			height += ((left_height > right_height)? left_height:right_height);

		}
		return height;
	}

protected:
	Node *_root;

private:
	template<class ComparableType>
	Node* Search(Node *root,ComparableType key)
	{

		T data = root->GetNodeContents();
		Node *next = ((ComparableType)data < key)? root->_left:root->_right;
		Node *result = NULL;
		
		if(next != NULL)
		{
			result = Search<ComparableType>(next,key);
		}
		else
		{
			result = root;
		}
		
		return result;
		
	}

	void DestroySubtree(Node *root)
	{
		if(root->_left!= NULL)
		{
			DestroySubtree(root->_left);
		}
		if(root->_right!=NULL)
		{
			DestroySubtree(root->_right);
		}
		delete root;
		root = NULL;
	}
};

template<class T>
BinaryTree<T>::BinaryTree()
{
	_root = NULL;
}
template<class T>
BinaryTree<T>::~BinaryTree()
{
	Destroy();
}


#endif