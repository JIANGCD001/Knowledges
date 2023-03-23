#include <bits/stdc++.h>
#define MAXN 400004
using namespace std;
long long in[MAXN],ans[MAXN<<1],tag[MAXN<<2];
inline long long left_child(long long father)
{
    return father<<1;
}
inline long long right_child(long long father)
{
    return father<<1|1;
}
inline void push_up(long long node)
{
    ans[node]=ans[left_child(node)]+ans[right_child(node)];
}
void build(long long node,long long left,long long right)
{
    tag[node]=0;
    if (left==right)
    {
        ans[node]=in[left];
        return;
    }
    long long mid=(left+right)>>1;
    build(left_child(node),left,mid);
    build(right_child(node),mid+1,right);
    push_up(node);
}
inline void f(long long node,long long left,long long right,long long k)
{
    tag[node]=tag[node]+k;
    ans[node]=ans[node]+k*(right-left+1);
}
inline void push_down(long long node,long long left,long long right)
{
    long long mid=(left+right)>>1;
    f(left_child(node),left,mid,tag[node]);
    f(right_child(node),mid+1,right,tag[node]);
    tag[node]=0;
}
inline void update(long long nleft,long long nright,long long left,long long right,long long node,long long k)
{
    if (nleft<=left&&right<=nright)
    {
        ans[node]+=k*(right-left+1);
        tag[node]+=k;
        return;
    }
    push_down(node,left,right);
    long long mid=(left+right)>>1;
    if (nleft<=mid)
    {
        update(nleft,nright,left,mid,left_child(node),k);
    }
    if (nright>mid)
    {
        update(nleft,nright,mid+1,right,right_child(node),k);
    }
    push_up(node);
}
long long query(long long qx,long long qy,long long left,long long right,long long node)
{
    long long result=0;
    if (qx<=left&&right<=qy)
    {
        return ans[node];
    }
    long long mid=(left+right)>>1;
    push_down(node,left,right);
    if (qx<=mid)
    {
        result+=query(qx,qy,left,mid,left_child(node));
    }
    if (qy>mid)
    {
        result+=query(qx,qy,mid+1,right,right_child(node));
    }
    return result;
}
int main()
{
    long long n,m;
    scanf("%lld %lld",&n,&m);
    for (int i=1;i<=n;i++)
    {
        scanf("%lld",&in[i]);
    }
    long long opt,x,y,k;
    build(1,1,n);
    while (m--)
    {
        scanf("%lld",&opt);
        switch (opt)
        {
            case 1:
            {
                scanf("%lld %lld %lld",&x,&y,&k);
                update(x,y,1,n,1,k);
                break;
            }
            case 2:
            {
                scanf("%lld %lld",&x,&y);
                printf("%lld\n",query(x,y,1,n,1));
                break;
            }
        }
    }
    return 0;
}
