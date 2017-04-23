/*
	Dylan Bush & Adam Rucker
	4/23/2017
	Lab 13/ Heap Skew Lab
*/	
#if !defined HEAPSKEW_H
#define HEAPSKEW_H

#include "BinaryTree.h"
#include "wx/wx.h"
#include <iostream>
using namespace std;
template < class T >
class HeapSkew : public Drawable
{

   private:
      BinaryTree<T>* bt;
      int sze;
      BinaryTree<T>* merge(BinaryTree<T>* left, BinaryTree<T>* right);

      int (*compare_items) (T* item_1, T* item_2);

   public:
      HeapSkew(int (*comp_items) (T* item_1, T* item_2));
      ~HeapSkew();

      bool heapIsEmpty();
      void heapInsert(T* item);
      T* heapRemove();

      void draw(wxDC& dc, int width, int height);
      void mouseClicked(int x, int y);

};

// this is a MAXHEAP (largest items to top alphabetical order)
template < class T >
HeapSkew<T>::HeapSkew(int (*comp_items) (T* item_1, T* item_2)) : Drawable()
{ 
   bt = new BinaryTree<T>();
   sze = 0;

   compare_items = comp_items;
}

template < class T >
HeapSkew<T>::~HeapSkew() 
{ 
   delete bt;
}  

template < class T >
bool HeapSkew<T>::heapIsEmpty()
{
   return sze == 0;
}

template < class T >
BinaryTree<T>* HeapSkew<T>::merge(BinaryTree<T>* left, BinaryTree<T>* right)
{
  //DO THIS
	if (left->isEmpty())
	{
	   return right;
	}
	else if (right->isEmpty())
	{
	   return left;
	}
	BinaryTree<T>* result;
	int rootscomp=(*compare_items)(left->getRootItem(), right->getRootItem());
	if(rootscomp < 0)
	{
		//cout<<"right > left"<<endl;
			result = merge(right, left);
	}
	else
	{
		//cout<<"Running through the not recursive part"<<endl;
		result = left;
		BinaryTree<T>* LL = result->detachLeftSubtree();
		BinaryTree<T>* LR = result->detachRightSubtree();

		result->attachRightSubtree(LL);
		if(LR->isEmpty())
		{
			result->attachLeftSubtree(right);
		}
		else
		{
			result->attachLeftSubtree(merge(LR, right));
		}
		delete LL;
		delete LR;
	}
	return result;
}


template < class T >
void HeapSkew<T>::heapInsert(T* item)
{
   //DO THIS (calls merge, should be short)
   sze++;
   BinaryTree<T>* right = new BinaryTree<T>(item);
   bt = merge(bt, right);
}

template < class T >
T* HeapSkew<T>::heapRemove()
{
   //DO THIS (calls merge, should be short)
   T* item = bt->getRootItem();
   BinaryTree<T>* left = bt->detachLeftSubtree();
   BinaryTree<T>* right = bt->detachRightSubtree();
   delete bt;
   bt = merge(left, right);
   cout<<"Failed"<<endl;
   delete right;
   return item;
}

template < class T >
void HeapSkew<T>::draw(wxDC& dc, int width, int height)
{
   bt->draw(dc, width, height);
}

template < class T >
void HeapSkew<T>::mouseClicked(int x, int y) {bt->mouseClicked(x, y);}

#endif
