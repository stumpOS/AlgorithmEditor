#pragma once
#ifndef FUNCTIONTREE_H_
#define FUNCTIONTREE_H_
#include<stack>
#include "BinaryTree.h"
#include "Node.h"
template<class T>
class FunctionTree: public BinaryTree<T, Node<T> >
{
public:
	typedef Node<T> node;
	FunctionTree(void){}
	~FunctionTree(void){}
	virtual void Insert(T key)
	{

	}
	virtual void Delete(T key){}
	void InitializeFunctionTree(T key)
	{
		if(_root == NULL)
		{
			_root = new node(key);
			_nonTerminatedBranches.push(_root);
		}
	}
	void AddChildOperation(T key)
	{
		if(_root==NULL)
			InitializeFunctionTree(key);
		else
		{
			node *child = new node(key);
			AddChildToCurrentBranch(child);
			_nonTerminatedBranches.push(child);
		}
	}
	void AddChildOperand(T key)
	{
		node *child = new node(key);
		AddChildToCurrentBranch(child);
		node* current_branch = _nonTerminatedBranches.top();

		if(current_branch->IsFull())
			_nonTerminatedBranches.pop();

	}
	void AddChildToCurrentBranch(node *child)
	{
		if(!_nonTerminatedBranches.empty())
		{
			node *parent = _nonTerminatedBranches.top();
			
			if(parent->GetLeft()==NULL)
			{	
				parent->SetLeftChild(child);
			}
			else if(parent->GetRight()==NULL)
			{
				parent->SetRightChild(child);
			}
			else
			{
				throw std::logic_error("attempted to add child to full parent");
			}
		}
		else if(_root==NULL)
		{
			throw std::logic_error("attempted to add operation to uninitialized tree");
		}
		else
		{
			throw std::logic_error("attempted to add operation to complete tree");
		}
	}

private:
	std::stack<node *> _nonTerminatedBranches;

};

#endif

