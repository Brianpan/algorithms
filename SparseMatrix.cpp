// Sparse matrix for range minimum

#include <iostream>
#include <math.h>
#include <algorithm>

using namespace std;
#define MAX_N 1<<10
class SparseMatrix{
    private:
        int *series;
        int s_size;
        int t_num;
        int **matrix;

        void constructSparseMatrix(){
            for(int t = 0; t < t_num; t++){
                for(int i = 0; i < s_size ; i++){
                    if(t == 0 || t == 1){
                        matrix[t][i] = series[i];
                    }else{
                        int strid = pow(2, (t - 1));
                        if(i+strid < s_size){
                            matrix[t][i] = *std::min_element(matrix[t-1]+i, matrix[t-1]+i+strid);    
                        }
                    }
                }
            }
        }
    public:
        SparseMatrix(int *nums, int size) : series(nums), s_size(size){
            
            int idx = 1, num = 1;
            while(idx <= size){
                idx = idx<<1;
                num += 1;
            }

            t_num = num;
            // assign 2d array
            matrix = new int*[num];
            for(int i = 0; i < num; i++){
                matrix[i] = new int[s_size];
            }
            // construct sparse matrix
            constructSparseMatrix();
        }

        void showSeries(){
            for(int i = 0 ; i < s_size; i++){
                printf("%d,", *(series+i));
            }
            printf("\n");
        }
        void showSpecific(const int t, const int i){
            if(t >= t_num || i >= s_size) return;
            printf("--%d \n", matrix[t][i]);
        }

        int getRangeMin(const int l, const int r){
            if(l > r){
                return 100000;
            }else if(l == r){
                return matrix[0][l];
            }else{
                int range = r - l;
                int temp = 1;
                while(temp < range){
                    temp = temp << 1;
                }
                // ex: 1 3
                // min(matrix[2][1], matrix[1][2]);
                // ex: 1 4
                // min(matrix[])
                // l -> l+search_period
                // r-(search_period-1) -> r
                int search_period = temp/2;
                int y = r - (search_period-1);
                return min(matrix[search_period][l], matrix[search_period -1][y]);
            }
        }
};
int main()
{
   int nums[9] = {1, 37, 29, 6, 58, 12, 2, 9, 5};
   SparseMatrix a(nums, 9);
   printf("%d \n", a.getRangeMin(0, 3));
   printf("%d \n", a.getRangeMin(3, 7));

   return 0;
}

