// *********************************************************************************************************************
// Description:		AVLTree is a balanced binary tree.
//					access time ~ log(n), building time ~ n*log(n), shorting time ~ n*log(n)
//					class T must implement
//						-initializing constructor
//						-int T::Compare(const T& ) method
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	Viktor Nagy, Sept. 2002
//
// SG compatible
// ********************************************************************************************************************* 

#ifndef __AVLTree_h__
#define __AVLTree_h__

#include "BaseAlgorithms.hpp"

#pragma once

#pragma warning (push)
#pragma warning (disable: 4127)


namespace GS
{

template <class T>
class AVLTree;

// ... class AVLNode ................................................................................................

template <class T>
class AVLNode
{
	friend class AVLTree<T>;

private:
	T* variable;
	int Depth;
	int numberOfElements;
	AVLNode* left;
	AVLNode* right;
	AVLNode* parent;

private:
	bool IsEmpty();
	AVLNode* NaiveDelete();
	bool IsAVLTree();
	void BalanceTree();
	bool LeftSideIsTooDeep();
	bool IsUnBalanced();
	void BalanceOnPath();
	void SetDepthOnPath();
	void SetDepth();
	void DoubleRotateLeft();
	void DoubleRotateRight();
	void RotateLeft();
	void RotateRight();
	void Extend(const T& insert);
	int  GetDepth();
	void SetNumberOfElements();
	int GetLeftNumber();
	int GetRightNumber();

	int GetPosition(const T& s);

	AVLNode* GetNext(const T& insert);
	AVLNode* GetNextWithIndex(const T& index);
	AVLNode* GetFirst();
	AVLNode* GetLast();
	AVLNode* GetNext();
	AVLNode* GetPrev();
	AVLNode* Position(int n);

	bool operator == (AVLNode& elem);

public:
	AVLNode(const T& s);
	~AVLNode();
};


template <class T>
AVLNode<T>::AVLNode(const T& s)
{
	variable = new T(s);
	left   = nullptr;
	right  = nullptr;
	parent = nullptr;
	numberOfElements = 1;
	Depth  = 1;
}

template <class T>
AVLNode<T>::~AVLNode()
{
	if( left != nullptr )
		delete left;
	if( right != nullptr )
		delete right;
	if( variable != nullptr )
		delete variable;
}

template <class T>
int AVLNode<T>::GetDepth()
{
	return Depth;
}

template <class T>
AVLNode<T>* AVLNode<T>::GetNext(const T& insert)
{
	int a = variable->Compare(insert);
	if( a > 0 )
		return left;
	if( a < 0 )
		return right;
	return this;
}

template <class T>
AVLNode<T>* AVLNode<T>::Position(int n)
{
	AVLNode<T>* elem = this;

	if( elem->numberOfElements < n )
		return nullptr;

	while( elem != nullptr)
	{
		if( elem->GetLeftNumber() >= n )
		{
			elem = elem->left;
			continue;
		}

		if( elem->GetLeftNumber()+1 == n )
		{
			return elem;
		}

		if( elem->GetLeftNumber()+1 < n )
		{
			n   -=  elem->GetLeftNumber()+1;
			elem = elem->right;
			continue;
		}
	}

	return nullptr;
}

template <class T>
int AVLNode<T>::GetPosition(const T& s)
{
	AVLNode<T>* aux  = this;
	AVLNode<T>* prev = nullptr;
	int pos = 1;

	while( true )
	{
		prev = aux;
		aux = aux->GetNext(s);

		if( aux == nullptr )
			return -1;

		if( aux != prev )
		{
			if( prev->right == aux )
				pos += prev->GetLeftNumber() + 1;
		}
		else
		{
			pos += aux->GetLeftNumber();
			break;
		}
	}

	if( aux == this )
		pos = GetLeftNumber() + 1;

	return pos;
}

template <class T>
int AVLNode<T>::GetLeftNumber()
{
	if( left == nullptr )
		return 0;
	else
		return left->numberOfElements;
}

template <class T>
int AVLNode<T>::GetRightNumber()
{
	if( right == nullptr )
		return 0;
	else
		return right->numberOfElements;
}



template <class T>
AVLNode<T>* AVLNode<T>::GetNextWithIndex(const T& index)
{
	int a = variable->Compare(index);
	if( a > 0 )
		return left;
	if( a < 0 )
		return right;
	return this;
}

template <class T>
void AVLNode<T>::Extend(const T& insert)
{
	int a = variable->Compare(insert);

	if( left == nullptr && a > 0 )
	{
		left = new AVLNode(insert);
		left->parent = this;
	}

	if( right == nullptr && a < 0 )
	{
		right = new AVLNode(insert);
		right->parent = this;
	}

	numberOfElements++;
	SetDepth();
}

template <class T>
void AVLNode<T>::RotateRight()
{
	if( left != nullptr )
	{

		T* p = variable; //Swap variables
		variable = left->variable;//parent ok!
		left->variable = p;

		AVLNode* thisRight =  right;
		AVLNode* thisLeft = left;
		AVLNode* thisLeftRight = left->right;

		left = left->left;
		right  = thisLeft;

		right->right = thisRight;
		right->left = thisLeftRight;

		if( left != nullptr )
			left ->parent = this;
		if( right->left != nullptr )
			right->left->parent = right;
		if( right->right != nullptr )
			right->right->parent = right;

		right->SetDepth();
		right->SetNumberOfElements();
		SetDepth();
	}
}

template <class T>
void AVLNode<T>::RotateLeft()
{
	if( right != nullptr )
	{
		T* p = variable; //Swap variables
		variable = right->variable;
		right->variable = p;

		AVLNode* thisLeft =  left;
		AVLNode* thisRight = right;
		AVLNode* thisRightLeft = right->left;

		right = right->right;
		left  = thisRight;

		left->left = thisLeft;
		left->right = thisRightLeft;

		if( right != nullptr )
			right->parent = this;
		if( left ->left != nullptr )
			left ->left->parent = left;
		if( left ->right != nullptr )
			left ->right->parent = left;

		left->SetDepth();
		left->SetNumberOfElements();
		SetDepth();

	}
}

template <class T>
void AVLNode<T>::DoubleRotateRight()
{
	if( left != nullptr )
	{
		left->RotateLeft();
		RotateRight();
	}
}


template <class T>
void AVLNode<T>::DoubleRotateLeft()
{
	if( right != nullptr )
	{
		right->RotateRight();
		RotateLeft();
	}
}

template <class T>
void AVLNode<T>::SetNumberOfElements()
{
	int leftNum = 0;
	int rightNum = 0;
	if( left != nullptr )
		leftNum = left->numberOfElements;
	if( right != nullptr )
		rightNum = right->numberOfElements;

	numberOfElements = leftNum + rightNum + 1;
}

template <class T>
void AVLNode<T>::SetDepth()
{
	if( left == nullptr && right == nullptr )
	{
		Depth = 1;
		return;
	}

	if( left == nullptr )
	{
		Depth = right->Depth + 1;
		return;
	}

	if ( right == nullptr )
	{
		Depth = left->Depth + 1;
		return;
	}


	Depth = ( left->Depth > right->Depth ? left->Depth : right->Depth) + 1;
}

template <class T>
void AVLNode<T>::SetDepthOnPath()
{
	AVLNode* elem = this;
	while( elem != nullptr )
	{
		int leftDepth = 0;
		int rightDepth = 0;

		if( elem->left != nullptr )
			leftDepth = elem->left->Depth;

		if( elem->right != nullptr )
			rightDepth = elem->right->Depth;

		elem->Depth = ((leftDepth>rightDepth)?leftDepth:rightDepth) + 1;

		elem->SetNumberOfElements();

		elem = elem->parent;
	}
}

template <class T>
void AVLNode<T>::BalanceOnPath()
{
	AVLNode* elem = this;
	while( elem != nullptr )
	{
		if( elem->IsUnBalanced() )
		{
			elem->BalanceTree();
		}
		else
			elem->SetDepth();

		elem = elem->parent;
	}
}

template <class T>
bool AVLNode<T>::IsUnBalanced()
{
	int leftDepth;
	int rightDepth;

	if( left == nullptr )
		leftDepth = 0;
	else
		leftDepth = left->GetDepth();

	if( right == nullptr )
		rightDepth = 0;
	else
		rightDepth = right->GetDepth();

	if( GS::Abs( leftDepth - rightDepth ) > 1 )
		return true;
	else
		return false;
}

template <class T>
bool AVLNode<T>::LeftSideIsTooDeep()
{
	int leftDepth;
	int rightDepth;

	if( left == nullptr )
		leftDepth = 0;
	else
		leftDepth = left->GetDepth();

	if( right == nullptr )
		rightDepth = 0;
	else
		rightDepth = right->GetDepth();

	return leftDepth > rightDepth;
}

template <class T>
void AVLNode<T>::BalanceTree()
{

	if( LeftSideIsTooDeep() )
	{
		if( left != nullptr )
		{
			if( left->LeftSideIsTooDeep() )
			{
				RotateRight();
			}
			else //right side too deep
			{
				DoubleRotateRight();
			}

		}
		else //right side too deep
		{
			DoubleRotateRight();
		}
	}
	else //right side too deep
	{
		if( right != nullptr )
		{
			if( right->LeftSideIsTooDeep() )
			{
				DoubleRotateLeft();
			}
			else //left side too deep
			{
				RotateLeft();
			}

		}
		else //left side too deep
		{
			DoubleRotateLeft();
		}
	}
}

template <class T>
bool AVLNode<T>::IsAVLTree()
{
	bool isAVL = true;

	if( !IsUnBalanced() )
	{
		if( left != nullptr )
			isAVL = left->IsAVLTree();
		if( right != nullptr && isAVL )
			isAVL = right->IsAVLTree();

		int leftDep = 0;
		int rightDep = 0;
		if( left != nullptr )
			leftDep = left->Depth;
		if( right != nullptr )
			rightDep = right->Depth;
		if( Depth != ((leftDep>rightDep)?leftDep:rightDep) + 1 )
			isAVL = false;
	}
	else
		isAVL = false;

	return isAVL;
}

template <class T>
AVLNode<T>* AVLNode<T>::NaiveDelete()
{
	AVLNode* ret = nullptr;
	if( left == nullptr )
	{
		if( parent != nullptr )
		{
			if( parent->left == this )
			{
				parent->left = right;
			}
			else//parent-> right == this
			{
				parent->right = right;
			}

			if( right != nullptr )
				right->parent = parent;

			ret = parent;

			left = nullptr;
			right = nullptr;
			delete this;


		}
		else// root && left == nullptr
		{
			if( right != nullptr )
			{
				delete variable;
				AVLNode* thisRight = right;

				variable = thisRight->variable;
				right = thisRight->right;
				left  = thisRight->left;

				thisRight->left = nullptr;
				thisRight->right = nullptr;
				thisRight->variable = nullptr;
				delete thisRight;

				ret = this;
			}
			else
			{
				delete variable;
				variable = nullptr;
			}
		}
	}
	else //left != nullptr
	{
		AVLNode* elem = left;
		while( elem->right != nullptr )
		{
			elem = elem->right;
		}

		//elem == replacing AVLNode
		delete variable;
		variable = elem->variable;

		if( elem->parent != nullptr )
		{

			if( elem->parent->left == elem )
			{
				elem->parent->left = elem->left;
			}
			else//parent-> right == this
			{
				elem->parent->right = elem->left;
			}

			if( elem->left != nullptr )
				elem->left->parent = elem->parent;

			ret = elem->parent;

			elem->left = nullptr;
			elem->right = nullptr;
			elem->variable = nullptr;
			delete elem;
		}
	}

	return ret;
}

template <class T>
bool AVLNode<T>::IsEmpty()
{
	return variable == nullptr;
}

template <class T>
AVLNode<T>* AVLNode<T>::GetFirst()
{
	AVLNode<T>* elem = this;
	while( elem->left != nullptr )
		elem = elem->left;
	return elem;
}

template <class T>
AVLNode<T>* AVLNode<T>::GetLast()
{
	AVLNode<T>* elem = this;
	while( elem->right != nullptr )
		elem = elem->right;
	return elem;
}

template <class T>
AVLNode<T>* AVLNode<T>::GetNext()
{
	if( right != nullptr )
	{
		AVLNode<T>* elem = right;
		while( elem->left != nullptr )
		{
			elem = elem->left;
		}
		return elem;
	}
	else
	{
		AVLNode<T>* elem = this;
		AVLNode<T>* prev = this;

		while( elem != nullptr )
		{
			if( elem->right != prev && elem != prev )
			{
				return elem;
			}

			prev = elem;
			elem = elem->parent;
		}

		return nullptr;
	}
}

template <class T>
AVLNode<T>* AVLNode<T>::GetPrev()
{
	if( left != nullptr )
	{
		AVLNode<T>* elem = left;
		while( elem->right != nullptr )
		{
			elem = elem->right;
		}
		return elem;
	}
	else
	{
		AVLNode<T>* elem = this;
		AVLNode<T>* prev = this;

		while( elem != nullptr )
		{
			if( elem->left != prev && elem != prev )
			{
				return elem;
			}

			prev = elem;
			elem = elem->parent;
		}

		return nullptr;
	}
}

template <class T>
bool AVLNode<T>::operator == (AVLNode<T>& elem)
{
	return variable == elem.variable;
}


// ... class AVLTree .....................................................................................................

template <class T>
class AVLTree
{
private:
	AVLNode<T>* root;
	mutable AVLNode<T>* current;
public:

	AVLTree();
	~AVLTree();
	void Clear();
	bool IsInside(const T& s);
	bool IsEmpty();
	T* Insert(const T& s);
	void Delete(const T& s);
	bool IsAVL();
	int GetDepth();
	int GetNum();
	T* GetFirst();
	const T* GetFirst() const;
	T* GetLast();
	const T* GetLast() const;
	T* GetNext();
	const T* GetNext() const;
	T* GetPrev();
	const T* GetPrev() const;

	bool SetActual(const T& s);
	int  GetPosition(const T& s);

	T* Position(int n);
	T* Index(const T& s);

	AVLTree(const AVLTree& avl);
	AVLTree& operator =  (const AVLTree& avl);
	bool	 operator == (const AVLTree& avl);
	bool	 operator != (const AVLTree& avl);
	T&		 operator [] (int n);
	T&		 operator [] (T& elem);

	AVLTree& operator + (const AVLTree& avl);
	AVLTree& operator - (const AVLTree& avl);

	AVLTree& operator + (const T& s);
	AVLTree& operator - (const T& s);

	AVLTree& operator += (const AVLTree& avl);
	AVLTree& operator -= (const AVLTree& avl);

	AVLTree& operator += (const T& s);
	AVLTree& operator -= (const T& s);
};



template <class T>
AVLTree<T>::AVLTree()
{
	root = nullptr;
	current = nullptr;
}

template <class T>
AVLTree<T>::~AVLTree()
{
	if( root != nullptr )
		delete root;
	root = nullptr;
}

template <class T>
void AVLTree<T>::Clear()
{
	if( root != nullptr )
		delete root;
	root = nullptr;
}

template <class T>
bool AVLTree<T>::IsInside(const T& s)
{
	if( root == nullptr )
		return false;

	AVLNode<T>* aux = root;
	AVLNode<T>* prev = nullptr;

	while( aux != nullptr && aux != prev )
	{
		prev = aux;
		aux = aux->GetNext(s);
	}

	if( aux == prev )
		return true;
	else
		return false;
}

template <class T>
bool AVLTree<T>::IsEmpty()
{
	return root == nullptr;
}


template <class T>
T* AVLTree<T>::Insert(const T& s)
{

	if( root == nullptr )
	{
		root = new AVLNode<T>(s);
		return root->variable;
	}

	AVLNode<T>* aux = root;
	AVLNode<T>* prev = nullptr;

	while( aux != nullptr && aux != prev )
	{
		prev = aux;
		aux = aux->GetNext(s);
	}

	if( aux == prev )
		return nullptr;


	prev->Extend(s);
	T* ret = prev->GetNext(s)->variable;
	prev->GetNext(s)->SetDepthOnPath();
	aux = root;
	prev = aux;
	AVLNode<T>* theLowestUnBalanced = nullptr;

	while(true)
	{
		
		if( aux->IsUnBalanced() )
		{
			theLowestUnBalanced = aux;
		}

		prev = aux;
		aux = aux->GetNext(s);
		if( aux == nullptr || aux == prev )
			break;
	}

	if( theLowestUnBalanced != nullptr )
	{
		theLowestUnBalanced->BalanceTree();
		theLowestUnBalanced->SetDepthOnPath();
	}

	return ret;

}

template <class T>
void AVLTree<T>::Delete(const T& s)
{
	AVLNode<T>* aux = root;
	AVLNode<T>* prev = nullptr;

	while( aux != nullptr && aux != prev )
	{
		prev = aux;
		aux = aux->GetNext(s);
	}


	if( aux == nullptr ) //there is no such AVLNode
		return;

	AVLNode<T>* startToRebuild = aux->NaiveDelete();

	if( root->IsEmpty() )
	{
		delete root;
		root = nullptr;
		return;
	}

	if( startToRebuild != nullptr )
	{
		startToRebuild->SetDepthOnPath();
		startToRebuild->BalanceOnPath();
	}
}

template <class T>
bool AVLTree<T>::IsAVL()
{
	if( root != nullptr )
		return root->IsAVLTree();
	else
		return true;
}

template <class T>
int AVLTree<T>::GetDepth()
{
	if( root != nullptr )
		return root->GetDepth();
	else
		return 0;
}

template <class T>
int AVLTree<T>::GetNum()
{
	if( root != nullptr )
		return root->numberOfElements;
	else
		return 0;
}

template <class T>
T* AVLTree<T>::Index(const T& s)
{
	AVLNode<T>* aux = root;
	AVLNode<T>* prev = nullptr;

	while( aux != nullptr && aux != prev )
	{
		prev = aux;
		aux = aux->GetNext(s);
	}

	if( aux != nullptr )
		return aux->variable;
	else
		return nullptr;
}

template <class T>
T* AVLTree<T>::GetFirst()
{
	if( root != nullptr )
		current = root->GetFirst();
	else
		return nullptr;

	if( current != nullptr )
		return current->variable;
	else
		return nullptr;
}

template <class T>
const T* AVLTree<T>::GetFirst() const
{
	if( root != nullptr )
		current = root->GetFirst();
	else
		return nullptr;

	if( current != nullptr )
		return current->variable;
	else
		return nullptr;
}

template <class T>
T* AVLTree<T>::GetLast()
{
	if( root != nullptr )
		current = root->GetLast();
	else
		return nullptr;

	if( current != nullptr )
		return current->variable;
	else
		return nullptr;
}

template <class T>
const T* AVLTree<T>::GetLast() const
{
	if( root != nullptr )
		current = root->GetLast();
	else
		return nullptr;

	if( current != nullptr )
		return current->variable;
	else
		return nullptr;
}

template <class T>
T* AVLTree<T>::GetNext()
{
	if( current != nullptr )
		current = current->GetNext();

	if( current != nullptr )
		return current->variable;
	else
		return nullptr;
}

template <class T>
const T* AVLTree<T>::GetNext() const
{
	if( current != nullptr )
		current = current->GetNext();

	if( current != nullptr )
		return current->variable;
	else
		return nullptr;
}


template <class T>
T* AVLTree<T>::GetPrev()
{
	if( current != nullptr )
		current = current->GetPrev();

	if( current != nullptr )
		return current->variable;
	else
		return nullptr;
}

template <class T>
const T* AVLTree<T>::GetPrev() const
{
	if( current != nullptr )
		current = current->GetPrev();

	if( current != nullptr )
		return current->variable;
	else
		return nullptr;
}

template <class T>
T* AVLTree<T>::Position(int n)
{
	if( root == nullptr )
		return nullptr;
	else
	{
		AVLNode<T>* selected =  root->Position(n);
		if( selected != nullptr )
			return selected->variable;
		else
			return nullptr;
	}
}

template <class T>
T&	AVLTree<T>::operator [](T& elem)
{
	T* selected = Index(elem);
	if( selected == nullptr )
	{
		Insert(elem);
		selected =  Index(elem);
	}

	return *selected;
}

template <class T>
bool AVLTree<T>::SetActual(const T& s)
{

	AVLNode<T>* aux = root;
	AVLNode<T>* prev = nullptr;

	while( aux != nullptr && aux != prev )
	{
		prev = aux;
		aux = aux->GetNext(s);
	}


	if( aux == nullptr ) //there is no such AVLNode
		return false;
	else
	{
		this->actual = aux;
		return true;
	}
}

template <class T>
AVLTree<T>& AVLTree<T>::operator = (const AVLTree<T>& avl)
{
	Clear();
	const T* elem = avl.GetFirst();
	while( elem != nullptr )
	{
		Insert(*elem);
		elem = avl.GetNext();
	}
	return *this;
}

template <class T>
AVLTree<T>::AVLTree(const AVLTree<T>& avl)
{
	root    = nullptr;
	current = nullptr;
	const T* elem = avl.GetFirst();
	while( elem != nullptr )
	{
		Insert(*elem);
		elem = avl.GetNext();
	}
}

template <class T>
bool AVLTree<T>::operator == (const AVLTree& avl)
{
	const T* elem = avl.GetFirst();
	while( elem != nullptr )
	{
		if( !IsInside(*elem) )
			return false;

		elem = avl.GetNext();

	}

	elem = GetFirst();
	while( elem != nullptr )
	{
		if( !avl.IsInside(*elem) )
			return false;

		elem = GetNext();

	}

	return true;
}

template <class T>
bool AVLTree<T>::operator != (const AVLTree& avl)
{
	return !(*this == avl);
}

template <class T>
T& AVLTree<T>::operator[](int n)
{
	if( root != nullptr )
	{
		AVLNode<T>* e = root->Position(n+1);
		if( e != nullptr )
			return *(e->variable);
		else
			throw "index error";
	}
	else
		throw "index error";
}

template <class T>
int  AVLTree<T>::GetPosition(const T& s)
{
	if( root != nullptr )
		return root->GetPosition(s);
	else
		return -1;
}


template <class T>
AVLTree<T>& AVLTree<T>::operator + (const AVLTree& avl)
{
	AVLNode<T>* elem = avl.GetFirst();

	while( elem != nullptr )
	{
		Insert(*elem);
		elem = avl.GetNext();
	}

	return *this;
}

template <class T>
AVLTree<T>& AVLTree<T>::operator - (const AVLTree& avl)
{
	AVLNode<T>* elem = avl.GetFirst();

	while( elem != nullptr )
	{
		Delete(*elem);
		elem = avl.GetNext();
	}

	return *this;
}

template <class T>
AVLTree<T>& AVLTree<T>::operator += (const AVLTree& avl)
{
	AVLNode<T>* elem = avl.GetFirst();

	while( elem != nullptr )
	{
		Insert(*elem);
		elem = avl.GetNext();
	}

	return *this;
}

template <class T>
AVLTree<T>& AVLTree<T>::operator -= (const AVLTree& avl)
{
	AVLNode<T>* elem = avl.GetFirst();

	while( elem != nullptr )
	{
		Delete(*elem);
		elem = avl.GetNext();
	}

	return *this;
}


template <class T>
AVLTree<T>& AVLTree<T>::operator + (const T& s)
{
	Insert(s);
	return *this;
}

template <class T>
AVLTree<T>& AVLTree<T>::operator - (const T& s)
{
	Delete(s);
	return *this;
}

template <class T>
AVLTree<T>& AVLTree<T>::operator += (const T& s)
{
	Insert(s);
	return *this;
}

template <class T>
AVLTree<T>& AVLTree<T>::operator -= (const T& s)
{
	Delete(s);
	return *this;
}

}

#pragma warning (pop)

#endif
