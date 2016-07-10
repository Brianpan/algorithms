// BinaryIndexTree practice
// using BinaryIndexTree to count how many changes in a bubbleSort

#include <iostream>
#include <algorithm>
#include <memory.h>

using namespace std;

//Binary index tree
class BinaryIndexTree{
	private:
		static const int MAX_SIZE = 1<<16;
		int bit[MAX_SIZE];
		int b_size;
	public:
		BinaryIndexTree(const int size);
		int sum(const int idx);
		void add(const int idx, const int val);	
};

BinaryIndexTree::BinaryIndexTree(const int size){
	b_size = 2*size;
	memset(bit, 0, b_size);
}

int BinaryIndexTree::sum(const int idx){
	if(idx > b_size){
		return 0;
	}
	int t_idx = idx, total = 0;
	while(t_idx > 0){
		total += bit[t_idx];
		t_idx -= t_idx & -(t_idx);
	}

	return total;
}

void BinaryIndexTree::add(const int idx, const int val){
	int t_idx = idx;
	if(t_idx == 0 || t_idx > b_size){
		return;
	}
	while(t_idx < b_size){
		bit[t_idx] += val;
		t_idx += t_idx & (-t_idx);
	}

	return;
}

int solveBubble(int *aptr, const int size){
	BinaryIndexTree t1(1<<10);
	long long total = 0;
	int min_element = *std::min_element(aptr, aptr+size);
	int base_of_element = 0;
	if(min_element < 0){
		base_of_element = -min_element + 1;
	}
	for(int j = 0; j < size; j ++){
		int act_val = aptr[j] + base_of_element;
		total += j - t1.sum(act_val);
		t1.add(act_val, 1);
	}
	return total;	
}
int main(){
	int n = 5;
	int arr[n] = {3, -1, 5, 9, 6};
	cout<<solveBubble(arr, n)<<endl;
}	