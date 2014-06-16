#pragma once
#ifndef NODE_H_
#define NODE_H_

template<class T>	
class Node
{
public:
	Node(){_left=NULL;_right=NULL;_height=0;}
	Node(const T &data)
	{
		_data = data;
		_left=NULL;
		_right=NULL;
		_height = 0;
	}
	virtual ~Node()
	{
	}
	T &GetNodeContents(){return _data;}
	Node *GetLeft(){return _left;}
	Node *GetRight(){return _right;}
	void SetLeftChild(Node *child){_left = child;}
	void SetRightChild(Node *child){_right = child;}
	void SetNodeContents(T data){_data = data;}
	bool IsChildless()
	{
		if(_left==NULL&&_right==NULL)
			return true;
		else
			return false;
	}
	bool IsFull()
	{
		if(_left!=NULL&&_right!=NULL)
			return true;
		else
			return false;
	}
	Node** IsChild(T candidate)
	{
		Node **child = NULL;
		bool matchLeft = IsChild(candidate,_left);
		bool matchRight;
		if(matchLeft==true)
			child = &_left;
		else 
		{
			matchRight = IsChild(candidate,_right);
			if(matchRight==true)
				child = &_right;
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
	int GetHeight(){return _height;}
	void SetHeight(int hf){_height = hf;}

	void IncHeight(){_height++;}
	void DecHeight(){_height--;}
protected:
	Node *_left;
	Node *_right;
	T _data;
	int _height;
};
#endif