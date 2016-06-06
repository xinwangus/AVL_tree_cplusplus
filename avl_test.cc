#include <iostream>
#include <random>
#include "avl_tree.h"

using namespace std;

int main()
{
	AVL_tree<int> my_avl;
	int val;

	default_random_engine dre;
	uniform_int_distribution<int> di(1,1000); // what?

	unsigned int failed_count = 0;

	for (int i = 0; i < 100; i++) {
		val = di(dre);
		if (!my_avl.add_node(val)) {
			failed_count++;
		} else {
			cout << "Added: " << val << endl;
		}
	}

	cout << "Depth of tree is: " 
	     << my_avl.depth()
	     << endl;
	cout << "Count of tree is: " 
	     << my_avl.count
	     << endl;
	cout << "Count of failed add is: " 
	     << failed_count
	     << endl;
	return 0;
}
