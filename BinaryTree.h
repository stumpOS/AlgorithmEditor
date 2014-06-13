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
		}
		T &GetNodeContents(){return _data;}
		Node *GetLeft(){return _left;}
		Node *GetRight(){return _right;}
		void SetLeftChild(Node *child){_left = child;}
		void SetRightChild(Node *child){_right = child;}
		void SetNodeContents(T data){_data = data;}
		bool IsFull()
		{
			if(_left!=NULL&&_right!=NULL)
				return true;
			else
				return false;
		}
		Node* IsChild(T candidate)
		{
			Node *child = NULL;
			bool matchLeft = IsChild(candidate,_left);
			bool matchRight;
			if(matchLeft==true)
				child = _left;
			else 
			{
				matchRight = IsChild(candidate,_right);
				if(matchRight==true)
					child = _right;
			}
			return child; 
		}
		static bool IsChild(T candidate, Node *child)
		{
			bool match = false;
			if(child!=NULL)
			{
				if(candidate==child->GetNodeContents())
					match = true;
			}
			return match;
		}

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
	virtual void Insert(T key)
	{
		Node* parent = Search<T>(key);
		if(parent != NULL)
		{
			AddChildTo(parent,key);
		}
	}
	virtual void Delete(T key)
	{
		Node *parent = NULL;
		try
		{
			parent = SearchForParent(_root,key);
		}
		catch(std::logic_error const& keyIsRootException)
		{
			delete _root;
			_root = NULL;
		}
	}

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
	Node* SearchForParent(Node *root,T key)
	{
		T data = root->GetNodeContents();
		Node *next = (data < key)? root->_left:root->_right;
		Node *result = NULL, *child = NULL;
		
		if(next != NULL)
		{
			if(next->GetNodeContents() == key)
			{
				throw std::logic_error("no parent");
			}
			child = next->IsChild(key);
			if(child!=NULL)
			{
				result = next;
			}
			else
			{
				result = SearchForParent(next,key);
			}
		}
		else if(next == NULL)
		{
			throw std::bad_typeid("node not found");
		}
		
		return result;	
	}
	Node* GetDeepestLeft(Node *root)
	{
		if(root->_left!=NULL)
			return GetDeepestLeft(root->left);
		else
			return root;
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