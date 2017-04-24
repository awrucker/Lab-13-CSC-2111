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
      
      // pre Takes two trees and 
      // post returns a new binary tree that is a heap
      BinaryTree<T>* merge(BinaryTree<T>* left, BinaryTree<T>* right);

      int (*compare_items) (T* item_1, T* item_2);

   public:
      /*
		Pre: Receives (*comp_items)
		Post: Creates a new HeapSkew
	  */	
      HeapSkew(int (*comp_items) (T* item_1, T* item_2));
      /*
		Pre:
		Post:Deletes the HeapSkew
	  */	
	  ~HeapSkew();
	  /*
		Pre:
		Post:Returns whether the heap is empty
	  */	
      bool heapIsEmpty();
	  /*
		Pre:Receives a T* item
		Post: Adds the T* item to the heap
	  */	
      void heapInsert(T* item);
      /*
		Pre:
		Post: Returns the largest item in the heap
	  */	
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
	   return right;        //if left is empty return the right subtree
	}
	else if (right->isEmpty())
	{
	   return left;      // if right is empty return the left subtree
	}
	BinaryTree<T>* result;
	int rootscomp=(*compare_items)(left->getRootItem(), right->getRootItem());   //gets a compare
	if(rootscomp < 0)
	{
		//cout<<"right > left"<<endl;
			result = merge(right, left);      //recursivly calls the function
	}
	else
	{
		//cout<<"Running through the not recursive part"<<endl;
		result = left;
		BinaryTree<T>* LL = result->detachLeftSubtree();      //puts the result of detatch left into LL
	
		BinaryTree<T>* LR = result->detachRightSubtree();     // puts the result of detatch right into LR

		result->attachRightSubtree(LL);
		if(LR->isEmpty())
		{
			result->attachLeftSubtree(right);     //combining the trees into heap
		}
		else
		{
			result->attachLeftSubtree(merge(LR, right));//combining the trees into heap
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
   bt = merge(bt, right);  //calls merge
}

template < class T >
T* HeapSkew<T>::heapRemove()
{
   //DO THIS (calls merge, should be short)
   sze--;//change the sze
   T* item = bt->getRootItem();//get the root item of the binary tree
   BinaryTree<T>* left = bt->detachLeftSubtree();//get the left subtree
   BinaryTree<T>* right = bt->detachRightSubtree();//get the right subtree
   delete bt;//delete the old tree
   bt = merge(left, right);//merge the two trees together
   return item;//returns the item;
}

template < class T >
void HeapSkew<T>::draw(wxDC& dc, int width, int height)
{
   bt->draw(dc, width, height);
}

template < class T >
void HeapSkew<T>::mouseClicked(int x, int y) {bt->mouseClicked(x, y);}

#endif
