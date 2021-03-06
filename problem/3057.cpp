#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long ll;

int r, c, m[300][300];
bool dp[300][300][300];

ll row[300][300], rrow[300][300];
ll col[300][300], rcol[300][300];
    
bool chk(int x,int y,int size){
    int si = x-size+1, ei = x;
    int sj = y-size+1, ej = y;
    if(si<0 || sj<0) return false;
    
    int bit;
    for(int k=0;k<size;k+=bit){
        bit = min(60,size-k);
        ll a = (row[si][sj+k] & ((1LL<<bit)-1));
        ll b =(rrow[ei][ej-k] & ((1LL<<bit)-1));
        if(a != b) return false;
        ll c = (col[si+k][sj] & ((1LL<<bit)-1));
        ll d =(rcol[ei-k][ej] & ((1LL<<bit)-1));
        if(c != d) return false;
    }
    return true;
}

int solve(){
    for(int i=r-1;i>=0;--i)
        for(int j=c-1;j>=0;--j){
            if(j==c-1) row[i][j] = m[i][j];
            else row[i][j] = 2LL*row[i][j+1] + m[i][j];
            if(i==r-1) col[i][j] = m[i][j];
            else col[i][j] = 2LL*col[i+1][j] + m[i][j];
        }
    for(int i=0;i<r;++i)
        for(int j=0;j<c;++j){
            if(j==0) rrow[i][j] = m[i][j];
            else rrow[i][j] = 2LL*rrow[i][j-1] + m[i][j];
            if(i==0) rcol[i][j] = m[i][j];
            else rcol[i][j] = 2LL*rcol[i-1][j] + m[i][j];
        }

    int ans = 1;
    int upp = min(r,c);
    for(int i=0;i<r;++i)
        for(int j=0;j<c;++j)
            dp[i][j][0] = dp[i][j][1] = true;
    for(int i=1;i<r;++i)
        for(int j=1;j<c;++j)
            for(int k=2;k<=upp;++k)
                if(dp[i-1][j-1][k-2] && chk(i,j,k)){
                        dp[i][j][k] = true;
                        ans = max(ans, k);
                }
    return ans>1 ? ans : -1;
}

int main(){
    scanf("%d%d",&r,&c);
    for(int i=0;i<r;++i)
        for(int j=0;j<c;++j)
            scanf("%1d",&m[i][j]);
    printf("%d",solve());
}
