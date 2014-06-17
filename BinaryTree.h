#pragma once
#ifndef BINARYTREE_H_
#define BINARYTREE_H_

#include<cstdlib>
#include<exception>
#include<typeinfo>
#define MAX(a,b) (a>b?a:b)

template<class T, class NodeType>
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
	template<class ComparableType>
	NodeType* Search(ComparableType key)
	{
		NodeType *result = NULL;

		if(_root != NULL)
		{
			result = Search<ComparableType>(_root, key);
		}
		return result;
	}
	void Initialize(T key)
	{
		_root = NewNode(key);
	}
	virtual void Insert(T key)
	{
		NodeType* parent = Search<T>(key);
		if(parent != NULL)
		{
			AddChildTo(parent,key);
		}
	}
	virtual void Delete(T key)
	{
		NodeType **parent = NULL;
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

	int GetHeight(NodeType* root, int &height)
	{	
		if(root != NULL)
		{
			int left_subtree_height = 0, right_subtree_height = 0;

			int left_height = GetHeight(root->GetLeft(), left_subtree_height)+1;
			int right_height = GetHeight(root->GetRight(), right_subtree_height)+1;

			height += ((left_height > right_height)? left_height:right_height);
		}
		return height;
	}
	NodeType** SearchForParent(NodeType *root,T key)
	{
		if(root==_root&&_root->GetNodeContents()==key)
			return NULL;
		T data = root->GetNodeContents();
		NodeType *next = (data < key)? root->GetRight():root->GetLeft();
		NodeType **result = NULL, **child = NULL;
		
		if(next != NULL)
		{
			if(next->GetNodeContents() == key)
			{
				result = &root;
			}
			else
			{
				result = SearchForParent(next,key);
			}
		}
		else if(next == NULL)
		{
			throw std::bad_typeid("NodeType not found");
		}
		
		return result;	
	}

	virtual void AddChildTo(NodeType *parent,T key)
	{
		if(parent->GetNodeContents()>key && parent->GetLeft() == NULL)
		{
			parent->SetLeftChild(NewNode(key));
		}
		else if(parent->GetNodeContents()<key && parent->GetRight() == NULL)
		{
			parent->SetRightChild(NewNode(key));
		}
		else if(parent->GetNodeContents()==key)
			throw std::invalid_argument("already in tree");
		else
			throw std::invalid_argument("search failed");	
	}	
protected:
	virtual NodeType *NewNode(const T &data){return new NodeType(data);}

	void RotateLeft(NodeType *root)
	{
		NodeType *newRoot = root->GetRight();
		if(newRoot != NULL)
		{
			NodeType *former_left = newRoot->GetLeft();

			newRoot->SetLeftChild(root);
			root->SetRightChild(former_left);
			UpdateHeights(_root,root->GetNodeContents());
		}
	}
	void RotateRight(NodeType *root)
	{
		NodeType *newRoot = root->GetLeft();
		if(newRoot != NULL)
		{
			NodeType *former_right = newRoot->GetRight();
			newRoot->SetRightChild(root);
			root->SetLeftChild(former_right);

			UpdateHeights(_root,root->GetNodeContents());
		}		
	}
	void UpdateHeights(NodeType *root,T key)
	{
		if(root!=NULL)
		{
			int height = 0;
			root->SetHeight(GetHeight(root,height));
			if(root->GetNodeContents()<key)
				UpdateHeights(root->GetRight(),key);
			else if(root->GetNodeContents()>key)
				UpdateHeights(root->GetLeft(),key);
		}
	}
	void SwapChildrenToPrepForRotation(NodeType *parent, NodeType *child, NodeType *grand_child)
	{
		if(parent->GetNodeContents() < child->GetNodeContents())
		{
			parent->SetRightChild(grand_child);
		}
		else if(parent->GetNodeContents() > child->GetNodeContents())
		{
			parent->SetLeftChild(grand_child);
		}
	}
	NodeType *_root;

private:
	template<class ComparableType>
	NodeType* Search(NodeType *root,ComparableType key)
	{

		T data = root->GetNodeContents();
		NodeType *result = NULL;
		if((ComparableType)data == key)
		{
			result = root;
		}
		else
		{
			NodeType *next = ((ComparableType)data < key)? root->GetRight():root->GetLeft();
			if(next != NULL)
				result = Search<ComparableType>(next,key);
			else
				result = root;	
		}
		return result;	
	}

	void DestroySubtree(NodeType *root)
	{
		if(root->GetLeft()!= NULL)
		{
			DestroySubtree(root->GetLeft());
		}
		if(root->GetRight()!=NULL)
		{
			DestroySubtree(root->GetRight());
		}
		delete root;
		root = NULL;
	}
};

template<class T, class NodeType>
BinaryTree<T, NodeType>::BinaryTree()
{
	_root = NULL;
}
template<class T, class NodeType>
BinaryTree<T, NodeType>::~BinaryTree()
{
	Destroy();
}


#endif