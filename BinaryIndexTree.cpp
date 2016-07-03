// binary index implementation
// graph:       
//         4    8
//       2   6 
// root 1 3 5 7

#include <iostream>
#include "memory.h"

using namespace std;
class BinaryIndexTree{
	private:
		static const int MAX_N = 1<<16;
		int bit[MAX_N];
		int size;
	public:
		BinaryIndexTree(const int bSize);
		~BinaryIndexTree();
		int sum(int idx);
		void add(int idx, int x);
};

BinaryIndexTree::BinaryIndexTree(const int bSize){
	size = 2*bSize;
	memset(bit, 0, size);
}

BinaryIndexTree::~BinaryIndexTree()
{
	delete [] bit;
	return;
}

int BinaryIndexTree::sum(int idx)
{	
	if(idx > size)
		return 0;

	int total = 0;
	while(idx > 0){
		total += bit[idx];
		idx -= idx & (-idx);
	}
	return total;
}

void BinaryIndexTree::add(int idx, int x)
{
	while(idx <= size){
		bit[idx] += x;
		idx += idx & (-idx);
	}
	return;
}
int main(){
	BinaryIndexTree bTree(8);
	bTree.add(1, 10);
	bTree.add(3, 15);
	cout<<bTree.sum(3);
	return 0;
}