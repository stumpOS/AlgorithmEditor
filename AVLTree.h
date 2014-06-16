#pragma once
#ifndef AVLTREE_H_
#define AVLTREE_H_
#include"BinaryTree.h"
#include"Node.h"
#include<cmath>

template<class T>
class AVLTree: public BinaryTree<T, Node<T> >
{
public:
	typedef Node<T> Node;
	typedef BinaryTree<T,Node> BinaryTree;
	AVLTree();
	~AVLTree();
	
	virtual Node *NewNode(const T &data){return new Node(data);}
	virtual void Insert(T key);
	virtual void Delete(T key);
	void SetBalanceFactors(Node *node);

	virtual void AddChildTo(Node *node,T key)
	{
		bool increasedHeight = false;
		if(node->IsChildless())
		{
			increasedHeight = true;
		}
		BinaryTree::AddChildTo(node,key);
		if(increasedHeight)
		{
			node->IncHeight();
			UpdateHeights(_root,key);
			Node **unbalanced_root = GetRootOfDeepestUnbalancedSubtree(_root,key);
			if(unbalanced_root != NULL)
			{
				Node *root = *unbalanced_root;
				Node **parent_ptr = SearchForParent(_root,root->GetNodeContents());
				Node *parent = *parent_ptr;
				RestoreBalanceByRotating(root, parent);
			}
		}	

	}
private:
	void AddressLeftHeavySubtree(Node *root,Node *parent)
	{
		Node *left_root = root->GetLeft();
		
		if(GetBalanceFactor(left_root)==-1)
		{
			root->SetLeftChild(left_root->GetRight());
			RotateLeft(left_root);	
		}
		if(parent != NULL)
		{
			SwapChildrenToPrepForRotation(parent, root, root->GetLeft());
		}
		else if(root == _root)
		{
			_root = root->GetLeft();
		}
		RotateRight(root);
	}
	void AddressRightHeavySubtree(Node *root, Node *parent)
	{
		Node *right_root = root->GetRight();
		if(GetBalanceFactor(right_root)==1)
		{
			root->SetRightChild(right_root->GetLeft());
			RotateRight(right_root);
		}
		if(parent != NULL)
		{
			SwapChildrenToPrepForRotation(parent, root, root->GetRight());
		}
		else if(root == _root)
		{
			_root = root->GetRight();
		}
		RotateLeft(root);
	}
	void SwapChildrenToPrepForRotation(Node *parent, Node *child, Node *grand_child)
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

	Node **GetRootOfDeepestUnbalancedSubtree(Node *root,T key)
	{
		Node **result = NULL, **descendent_result = NULL;
		if(root!=NULL)
		{
			if(abs(GetBalanceFactor(root))==2)
			{
				result = &root;
			}
			if(root->GetNodeContents()<key)
				descendent_result = GetRootOfDeepestUnbalancedSubtree(root->GetRight(),key);
			else if(root->GetNodeContents()>key)
				descendent_result = GetRootOfDeepestUnbalancedSubtree(root->GetLeft(),key);	
			result = (descendent_result != NULL)? descendent_result:result;
		}
		return result;
	}
	int GetBalanceFactor(Node *root)
	{
		int balanceFactor = 0, height_left=0,height_right=0;
		if(root->GetLeft()!=NULL)
		{
			height_left = root->GetLeft()->GetHeight();
		}
		if(root->GetRight()!=NULL)
		{
			height_right = root->GetRight()->GetHeight();
		}
		balanceFactor = height_left - height_right;
		return balanceFactor;
	}
	void RestoreBalanceByRotating(Node *child, Node *parent)
	{
		if(GetBalanceFactor(child)==2)
			AddressLeftHeavySubtree(child,parent);
		else if(GetBalanceFactor(child)==-2)
			AddressRightHeavySubtree(child,parent);
	}
};
template<class T>
AVLTree<T>::AVLTree()
{
}
template<class T>
AVLTree<T>::~AVLTree()
{
}
template<class T>
void AVLTree<T>::Insert(T key)
{
	if(_root==NULL)
		Initialize(key);
	else
	{
		Node* parent = Search<T>(key);
		if(parent != NULL)
		{
			AddChildTo(parent,key);	
		}
	}
}
template<class T>
void AVLTree<T>::Delete(T key)
{
}



#endif