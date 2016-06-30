#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <stack>
#include <queue>
#include <string>
#include <vector>
#include <set>
#include <map>

const int N = 1e5+5;
const double PI = acos(-1.0);

double degreeToR(int deg) {
    return deg * PI / 180.0;
}

struct SegmentTree{
#define lson (rt<<1)
#define rson ((rt<<1) | 1)
#define MID ((L+R)>>1)
#define lsonPAR lson, L, MID
#define rsonPAR rson, MID+1, R

    const static int TN = N << 2;

    double tx[TN], ty[TN];
    int ang[TN];

    void rotate(int rt, int dg){
        double a = degreeToR(dg);
        double x = tx[rt], y = ty[rt];
        double s = sin(a), c = cos(a);

        tx[rt] = c*x - s*y;
        ty[rt] = s*x + c*y;
    }

    void PushDown(int rt){
        if(ang[rt]){
            rotate(lson, ang[rt]);
            rotate(rson, ang[rt]);
            ang[lson] += ang[rt];
            ang[rson] += ang[rt];

            ang[rt] = 0;
        }
    }

    void PushUp(int rt){
        tx[rt] = tx[lson] + tx[rson];
        ty[rt] = ty[lson] + ty[rson];
    }

    void build(int rt, int L, int R) {
        ang[rt] = 0;
        if (L == R) {
            tx[rt] = 0;
            scanf("%lf", ty+rt);
        } else {
            build(lsonPAR);
            build(rsonPAR);
            PushUp(rt);
        }
    }

    void change(int rt, int L, int R, int l, int r, int v) {
        if (l > R || r < L) return;
        if (l <= L && r >= R) {
            ang[rt] += v;
            rotate(rt, v);
        } else {
            PushDown(rt);
            change(lsonPAR, l, r, v);
            change(rsonPAR, l, r, v);
            PushUp(rt);
        }
    }
};

SegmentTree st;

int deg[N];
int main() {
    int n, m, s, a, cas = 1;
    while (scanf("%d%d", &n, &m) == 2) {
        for (int i = 1; i <= n; i++) {
            deg[i] = 180;
        }
        st.build(1, 1, n);
        if (cas++ > 1) puts("");

        for (int i = 0; i < m; i++) {
            scanf("%d%d", &s, &a);
            st.change(1, 1, n, s+1, n, a - deg[s+1]);
            deg[s+1] = a;
            printf("%.2f %.2f\n", st.tx[1], st.ty[1]);
        }
    }
    return 0;
}