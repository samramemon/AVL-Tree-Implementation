#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "dsexceptions.h"
#include <iostream>    // For NULL
#include <queue>  // For level order printout
#include <vector>
#include <algorithm> // For max() function
#include <cmath>
using namespace std;

// AvlTree class
//
// CONSTRUCTION: with ITEM_NOT_FOUND object used to signal failed finds
//
// ******************PUBLIC OPERATIONS*********************
// int size( )            --> Quantity of elements in tree
// int height( )          --> Height of the tree (null == -1)
// void insert( x )       --> Insert x
// void insert( vector<T> ) --> Insert whole vector of values
// void remove( x )       --> Remove x (unimplemented)
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted (in) order
// void printPreOrder( )  --> Print tree in pre order
// void printPostOrder( ) --> Print tree in post order
// void printInOrder( )   --> Print tree in *in* order
// ******************ERRORS********************************
// Throws UnderflowException as warranted
template <typename Comparable>
struct AvlNode
{
    Comparable element;
    AvlNode <Comparable>    *left;
    AvlNode  <Comparable>  *right;
    int       height;

    AvlNode( const Comparable & theElement, AvlNode <Comparable>*lt,
                                            AvlNode <Comparable>*rt, int h = 0 )
      : element( theElement ), left( lt ), right( rt ), height( h ) { }
};

template <typename Comparable>
class AvlTree
{
  public:
    AvlTree( ) : root( NULL )
      { }

    AvlTree( const AvlTree  & rhs ) : root( NULL )
    {
        *this = rhs;
    }

    ~AvlTree( )
    {
       cout << " [!] Destructor called." << endl;
       makeEmpty( );
    }

    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException( );
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException( );
        return findMax( root )->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x ) const
    {
        return contains( x, root );
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     *  TODO: Implement
     */
    bool isEmpty( ) const
    {
        return false;  // so not correct
    }

    /**
     * Return number of elements in tree.
     */
    int size( )
    {
      return size( root );
    }

    /**
     * Return height of tree.
     *  Null nodes are height -1
     */
    int height( )
    {
      return height( root );
    }
    
    AvlNode <Comparable> *& getRoot()
    {
        return root;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printInOrder( root );
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printInOrder( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printInOrder( root );
    }

    /**
     * Print the tree contents in pre order.
     */
    void printPreOrder( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printPreOrder( root );
    }

    /**
     * Print the tree contents in post order.
     */
    void printPostOrder( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printPostOrder( root );
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x )
    {
        insert( x, root );
    }

    /**
     * Insert vector of x's into the tree; duplicates are ignored.
     */
    void insert( vector<Comparable> vals)
    {
      for( auto x : vals ) {
        insert( x, root );
      }
    }
     

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     *  TODO: Implement
     */
    void remove( const Comparable & x , AvlNode <Comparable> *t)
    {
        //cout << "[!] Sorry, remove unimplemented; " << x << " still present" << endl;
        if (t==nullptr)
        {
            return;
        }
        if(x<t->element)
        {
            remove(x,t->left);
        }
        else if(t->element<x)
        {
            remove(x,t->right);
        }
        else if(t->left !=nullptr && t->right !=nullptr)
        {
            t->element= findMin(t->right)->element;
            remove(t->element, t->right);
        }
        else
        {
        AvlNode <Comparable> *pMem=t;
        t=(t->left !=nullptr)? t->left :t->right ;
        delete pMem;
        }

        if (height(t->left)-height(t->right) > 1)
        {    
           if (height(t->left->left) >= height(t->left->right))
           rotateWithLeftChild (t);
           else
           doubleWithLeftChild (t);
        }    
       else if (height(t->right)-height(t->left) > 1)
       {
           if (height(t->right->right)>=height(t->right->left))
           rotateWithRightChild (t);
           else
           doubleWithRightChild(t);
       }
       t->height=max(height(t->left),height(t->right))+1;
     
       
    }


    /**
     * Deep copy. - or copy assignment operator
     *  Will be in part II
     */
    const AvlTree & operator=( const AvlTree & rhs )
    {
      cout << " [!] Copy *assignment* operator called." << endl;
      
      return *this;
    }


/*****************************************************************************/
  private:
    

    AvlNode <Comparable>*root;

    /**
     * Internal method to count nodes in tree
     *  TODO: Implement
     */
    int size( AvlNode <Comparable>* & t )
    {
        if( t == nullptr)
        return(0);
        else
        if( t->left == nullptr && t->right == nullptr)
                return(1);
        else
                return(1 + (size(t->left) + size(t->right)));
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     *  TODO: Implement
     */
    
    void insert( const Comparable & x, AvlNode <Comparable>* & t )
    {
       // Definitely to do

       if (t == nullptr)
       {
           AvlNode <Comparable> *pMem= new AvlNode<Comparable>(x,nullptr,nullptr);
           t = pMem;
          
       }
       else if(x< t->element)
       insert (x, t->left);
       else if (x>t->element)
       insert (x, t->right);
       
        if (height(t->left)-height(t->right) > 1)
        {    
           if (height(t->left->left) >= height(t->left->right))
           rotateWithLeftChild (t);
           else
           doubleWithLeftChild (t);
        }    
       else if (height(t->right)-height(t->left) > 1)
       {
           if (height(t->right->right)>=height(t->right->left))
           rotateWithRightChild (t);
           else
           doubleWithRightChild(t);
       }
       t->height=max(height(t->left),height(t->right))+1;

             
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     *  You'll need this for deletes
     *  TODO: Implement
     */
    AvlNode <Comparable>* findMin( AvlNode <Comparable>*t ) const
    {
        if(t==nullptr)
        return nullptr;
        else 
        {
        while (t->left != NULL) {
        t = t->left;
        }
        }
      return t; // placeholder
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     *  TODO: Implement
     */
    AvlNode <Comparable> * findMax( AvlNode<Comparable> *t ) const
    {
        if(t==nullptr)
        return;
        else 
        {
        while (t->right != NULL) {
        t = t->right;
        }
        }
      
        return t;  // placeholder
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
     *  TODO: Implement
     */
    bool contains( const Comparable & x, AvlNode <Comparable>*t ) const
    { 
        if (t == nullptr)
        return false;
        if (t->element == x)
        return true;
        if (t->element < x)
        return contains(x, t->right);
        return contains(x, t->left);
        
     // Key is smaller than root's key
    }

/******************************************************/

    /**
     * Internal method to make subtree empty.
     *  TODO: implement for destructor
     * 
     */
    void makeEmpty( AvlNode <Comparable>* & t )
    {
        if( t != NULL ) {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;}
            
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     *  TODO: Implement
     */
    void printInOrder( AvlNode <Comparable>*t ) const
    {
      if (t == NULL)
      return;
      printInOrder (t->left);
      cout<<t->element<<"  ";
      printInOrder (t->right);
    }

    /**
     * Internal method to print a subtree rooted at t in pre order.
     *  TODO: Implement
     */
    void printPreOrder( AvlNode <Comparable>*t ) const
    {
      if (t == NULL)
      return;
      cout<<t->element<<"  ";
      printPreOrder (t->left);
      printPreOrder (t->right);
    }

    /**
     * Internal method to print a subtree rooted at t in post order.
     *  TODO: Implement
     */
    void printPostOrder( AvlNode <Comparable>*t ) const
    {
      if (t == NULL)
      return;
      printPostOrder ( t ->left );
      printPostOrder ( t ->right );
      cout<<t->element<<"  ";
    }

    /**
     * Internal method to clone subtree.
     */
    AvlNode <Comparable>* clone( AvlNode <Comparable>*t ) const
    {
        if( t == NULL )
            return NULL;
        else
            return new AvlNode<Comparable> ( t->element, clone( t->left ), clone( t->right ), t->height );
    }


    // Avl manipulations
    /**
     * Return the height of node t or -1 if NULL.
     *  TODO: Implement
     */
    int height( AvlNode <Comparable>*t ) const
    {
        if (t == nullptr)
        return -1;
    
        int leftTree= height(t->left);
        int rightTree = height(t->right);
        if (leftTree > rightTree) 
            return leftTree + 1;
        else 
            return rightTree + 1;
    }


    int max( int lhs, int rhs ) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     *  TODO: Implement
     */
    void rotateWithLeftChild( AvlNode <Comparable>* & k2 )
    {
        AvlNode <Comparable> *temp=k2->left;
        k2->left=temp->right;
        temp->right= k2;
        k2->height=max(height(k2->left), height(k2->right))+1;
        temp->height=max(height(temp->left), height(k2))+1;
        k2=temp;

    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     *  TODO: Implement
     */

    void rotateWithRightChild( AvlNode <Comparable>* & k1 )
    {
        AvlNode <Comparable> *temp=k1->right;
        k1->right=temp->left;
        temp->left=k1;
        k1->height=max(height(k1->right), height(k1->left))+1;
        temp->height=max(height(temp->right), height(k1))+1;
        k1=temp;
    }

    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     *  TODO: Implement
     * right left rotation
     */
    void doubleWithLeftChild( AvlNode <Comparable>* & k3 )
    {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     *  TODO: Implement
     */
    void doubleWithRightChild( AvlNode <Comparable>* & k1 )
    {
        rotateWithLeftChild(k1->left);
        rotateWithRightChild(k1);
    }
};

#endif
