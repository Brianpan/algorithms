#include <cstdio>  
#include <cmath> 

const int ST_SIZE = (1<<15) - 1; 
const int MAX_N = 10000;
const int MAX_C = 10000;
const double EPS = 1e-8;

// input data init
int N,C;
int L[MAX_N];
int S, A;
// int L[3] = {5, 5, 5};

// segment tree int
double vx[ST_SIZE], vy[ST_SIZE];
double ang[ST_SIZE];

double prv_a[MAX_N];

void init(int k, int l, int r){
	ang[k] = vx[k] = 0;
	if(r-l == 1){
		vy[k] = L[l];
	}else{
		int lch = 2*k + 1;
		int rch = 2*k + 2;
		init(lch, l, (r+l)/2);
		init(rch, (r+l)/2, r);
		vy[k] = vy[lch] + vy[rch];
	}

	return;
}

void update_node(int s_pt, double a, int tree_pt, int l, int r){
	if(s_pt <= l || s_pt >= r) 
		return;
	else if(s_pt < r){
		int lch = 2*tree_pt + 1;
		int rch = 2*tree_pt + 2;
		int m = (l+r)/2;
		update_node(s_pt, a, lch, l, m);
		update_node(s_pt, a, rch, m, r);

		// update angle that is upper than the rotating node
		if(m >= s_pt){
			ang[tree_pt] += a;
		}	

		double sai = sin(ang[tree_pt]), 
			   cosine = cos(ang[tree_pt]);

		// separate position counting	   
		vx[tree_pt] = vx[lch] + vx[rch]*cosine - vy[rch]*sai;
		vy[tree_pt] = vy[lch] + vx[rch]*sai + vy[rch]*cosine;
	}
}

int main(){
	bool flag = false;
	while(scanf("%d%d", &N, &C) == 2){
		if(flag) 
			puts("");
		else 
			flag = true;
		for(int i = 0 ; i < N; i++){
			scanf("%d", &L[i]);
		}
		init(0, 0, N);
		
		for(int i = 0 ; i < N ; i++){
			prv_a[i] = 180*asin(1.0)/90.0;
		}

		while(C--){
			scanf("%d%d", &S, &A);
			double a = A*asin(1.0)/90.0;
			double rotated_a = a - prv_a[S];
			update_node(S, rotated_a, 0, 0, N);
			prv_a[S] = a;
			printf("%.2f %.2f\n", fabs(vx[0]) <EPS ? 0 : vx[0],
									fabs(vy[0]) <EPS ? 0 : vy[0]);
		}
	}
	// test part ok!
	// C = 2;
	// N = 3;
	// int L[3] = {5, 5, 5};
	// int S[2] = {1, 2};
	// int A[2] = {270, 90};

	// // init
	// init(0, 0, N);
	// for(int i = 1 ; i < N ; i++){
	// 	prv_a[i] = 180*asin(1.0)/90.0;
	// }
	// for(int i = 0; i< C; i ++){
	// 	int s = S[i];
	// 	double a = A[i]*asin(1.0)/90.0;
	// 	double rotated_a = a - prv_a[s];
	// 	printf("rot: %f \n", rotated_a);
	// 	update_node(s, rotated_a, 0, 0, N);
	// 	prv_a[s] = a;
	// 	printf("%.2f %.2f\n", vx[0], vy[0]);
	// }
	return 0;
}