/* 
 * https://en.wikipedia.org/wiki/AVL_tree
 */
#include "avl_node.h"


template <typename T>
class AVL_tree
{
public:	
	AVL_tree();
	~AVL_tree();

	// TODO, need to balance the tree.
	bool add_node(T& t);
	// bool delete_node(T& t);
	AVL_node<T>* find(T& t);

	unsigned int depth();
	// int distance(T& t1, T& t2);
	
	unsigned int count;
private:
	AVL_node<T>* rootp;
};


// Tree functions.

template <typename T>
AVL_tree<T>::AVL_tree()
:rootp(0),count(0)
{
}

template <typename T>
AVL_tree<T>::~AVL_tree()
{
}

template <typename T>
bool
AVL_tree<T>::add_node(T& t)
{
	AVL_node<T>* tmp = new AVL_node<T>(t);

	if (rootp == 0) {
		rootp = tmp;
		count++;
		return true;
	}
	bool added = rootp->addNode(tmp);
	if (!added) {
		delete tmp;
	} else {
		count++;
	}
	return added;
}

template <typename T>
AVL_node<T>* 
AVL_tree<T>::find(T& t)
{
	if (rootp == 0) {
		return 0;
	}
	return rootp->findNode(t);
}



template <typename T>
unsigned int
AVL_tree<T>::depth()
{
	if (rootp == 0) {
		return 0;
	} else {
		return (rootp->depthFromMe());
	}
}

