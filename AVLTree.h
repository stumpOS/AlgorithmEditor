#pragma once
#ifndef AVLTREE_H_
#define AVLTREE_H_
#include"BinaryTree.h"
#include<cmath>
template<class T>
class AVLTree: public BinaryTree<T>
{
public:
	AVLTree();
	~AVLTree();
	typedef BinaryTree<T>::Node Node;

	virtual void Insert(T key);
	virtual void Delete(T key);
	bool IsBalanced();
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
template<class T>
bool AVLTree<T>::IsBalanced()
{
	int rh =0,lh = 0;
	int right_height = GetHeight(_root->GetRight(),rh);
	int left_height = GetHeight(_root->GetLeft(),lh);
	if(abs(right_height - left_height)>1)
		return false;
	else
		return true;
}
#endif