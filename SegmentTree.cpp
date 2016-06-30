// Segment Tree for range min

#include <iostream>
#include <string>
using namespace std;

const int MAX_N = 1 << 17;

class SegmentTree{
    private:
        int n_pt;
        int data[2*MAX_N-1];     
    public:
        SegmentTree(int n_);
        int show_n();
        void update(int k, int val);
        int query(int lb, int rb, int k, int l, int r);
};

SegmentTree::SegmentTree(int n_){
    int n = 1;
    while(n < n_){
        n *= 2;
    }
    for(int idx = 0; idx < 2*n-1; idx++){
        data[idx] = MAX_N;
    }
    
    //assign n
    n_pt = n;
}

int SegmentTree::show_n(){
    return n_pt;
}

void SegmentTree::update(int k, int val){
    int idx = k + n_pt -1;
    data[idx] = val;
    
    while(idx > 0){
        idx = (idx-1)/2;
        data[idx] = min(data[2*idx+1], data[2*idx+2]);
    }
    return;
}

// query [lb, rb)
// usage: query(5, 10, 0, 0, n)
// where n is the element number
int SegmentTree::query(int lb, int rb, int k, int l, int r){
    //out of bound
    if(lb >= r || rb <= l){
        return MAX_N;
    }
    //in the bound
    if(lb <= l && rb >= r){
        return data[k];
    }
    else{
        int lval = query(lb, rb, 2*k+1, l, (l+r)/2);
        int rval = query(lb, rb, 2*k+2, (l+r)/2, r);
        return min(lval, rval);
    }
    
}

int main()
{
  SegmentTree s(10);
  s.update(9, 3);
  s.update(8, 2);
  cout<<s.query(5, 10, 0, 0, 10)<<endl;
}
