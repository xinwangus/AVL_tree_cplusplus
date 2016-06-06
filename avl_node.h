#include <algorithm>
#include <assert.h>

typedef enum node_type_t 
{
	IS_LEFT_CHILD,
	IS_RIGHT_CHILD,
	IS_ROOT
} node_type;

template <typename T>
class AVL_node
{
public:
	AVL_node(T& t);
	~AVL_node();

	T v;
	AVL_node<T>* lp;
	AVL_node<T>* rp;
	AVL_node<T>* pp;

	int balance; // I define it as "Depth(right) - Depth(left)"

	void rotateLeft();
	void rotateRight();

	node_type getType();

	bool addNode(AVL_node<T>* np);
	AVL_node<T>* findNode(T& t);

	unsigned int depthFromMe();
};

// Node functions.

template <typename T> 
AVL_node<T>::AVL_node(T& t)
{
	v = t;
	lp = 0;
	rp = 0;
	pp = 0;
	balance = 0;
}

template <typename T> 
AVL_node<T>::~AVL_node()
{
}

template <typename T> 
node_type
AVL_node<T>::getType()
{
	if (this->pp == 0) {
		return IS_ROOT;
	} else if (this->pp->lp == this) {
		return IS_LEFT_CHILD;
	} else {
		assert(this->pp->rp == this);
		return IS_RIGHT_CHILD;
	}
}

template <typename T> 
void
AVL_node<T>::rotateLeft()
{
	//Only valid if this node has a valid rp.
	assert(rp != 0);
	if (rp == 0) { return;}

	node_type type = getType();
		
	AVL_node<T>* tmp_c = this->rp;
	AVL_node<T>* tmp_p = this->pp;
	AVL_node<T>* tmp_d = tmp_c->lp;

	tmp_c->pp = tmp_p;
	this->rp = tmp_d;
	this->pp = tmp_c;
	tmp_d->pp = this;
	tmp_c->lp = this;

	if (type == IS_LEFT_CHILD) {
		tmp_p->lp = tmp_c;
	} else if (type == IS_RIGHT_CHILD) {
		tmp_p->rp = tmp_c;
	}

	this->balance = this->balance - 1  - 
		((tmp_c->balance > 0)? (tmp_c->balance): 0);

	tmp_c->balance = tmp_c->balance - 1 +
		((this->balance < 0)? (this->balance): 0);

	// Need to upate tmp_p balance ??
}

template <typename T> 
void
AVL_node<T>::rotateRight()
{
	//Only valid if this node has a valid lp.
	assert(lp != 0);
	if (lp == 0) { return;}

	node_type type = getType();
		
	AVL_node<T>* tmp_b = this->lp;
	AVL_node<T>* tmp_p = this->pp;
	AVL_node<T>* tmp_e = tmp_b->rp;

	tmp_b->pp = tmp_p;
	this->lp = tmp_e;
	this->pp = tmp_b;
	tmp_e->pp = this;
	tmp_b->rp = this;

	if (type == IS_LEFT_CHILD) {
		tmp_p->lp = tmp_b;
	} else if (type == IS_RIGHT_CHILD) {
		tmp_p->rp = tmp_b;
	}

	this->balance = this->balance + 1 - 
		((tmp_b->balance < 0)? (tmp_b->balance): 0);

	tmp_b->balance = tmp_b->balance + 1 + 
		((this->balance > 0)? (this->balance): 0);

	// Need to upate tmp_p balance ??
}

template <typename T> 
bool
AVL_node<T>::addNode(AVL_node<T>* np)
{
	if (np == 0) { return false; }

	if (np->v == this->v) { return false; }

	if (np->v < this->v) {
		if (this->lp == 0) {
			this->lp = np;
			return true;
		} else {
			return this->lp->addNode(np);
		}
	}	

	if (np->v > this->v) {
		if (this->rp == 0) {
			this->rp = np;
			return true;
		} else {
			return this->rp->addNode(np);
		}
	}	
	return false;
}

template <typename T> 
AVL_node<T>* 
AVL_node<T>::findNode(T& t)
{
	if (this->v == t) {
		return this;
	} 

	if (t < this->v) {
		if (this->lp == 0) {
			return 0;
		} else {
			return findNode(this->lp);
		}
	}	
	if (t > this->v) {
		if (this->rp == 0) {
			return 0;
		} else {
			return findNode(this->rp);
		}
	}	
}

template <typename T> 
unsigned int
AVL_node<T>::depthFromMe()
{
	if ((lp == 0) && (rp == 0)) {
		return 1;
	}

	if ((lp == 0) && (rp != 0)) {
		return (1 + rp->depthFromMe());
	}

	if ((lp != 0) && (rp == 0)) {
		return (1 + lp->depthFromMe());
	}

	if ((lp != 0) && (rp != 0)) {
		return (1 + 
			(std::max(lp->depthFromMe(), 
			     rp->depthFromMe())));
	}
	// never reached.
	return 0;
}


