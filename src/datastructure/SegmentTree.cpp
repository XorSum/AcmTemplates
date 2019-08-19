---
title: SegmentTree
chapter: DataStructure
---

struct STree{

    int data[maxn<<2];
    int lazy[maxn<<2];
    
    void modify(int rt,int l,int r,int val) {
        data[rt] += val*(r-l+1);
        lazy[rt] += val;
    }
    
    void pushdown(int rt,int l,int r){
        if (lazy[rt]){
            int mid = (l+r)/2;
            modify(rt*2,l,mid,lazy[rt]);
            modify(rt*2+1,mid+1,r,lazy[rt]);
            lazy[rt] = 0;
        }
    }

    void update(int rt,int l,int r,int L,int R,int val){
        if (L<=l&r<=R){
            modify(rt,l,r,val);
        }else{
            int mid = (l+r)/2;
            pushdown(rt,l,r);
            if (L<=mid) update(rt*2,l,mid,L,R,val);
            if (mid<R) update(rt*2+1,mid+1,r,L,R,val);
            data[rt] = data[rt*2] + data[rt*2+1];            
        }
    }

    int query(int rt,int l,int r,int L,int R){
        if (L<=l&&r<=R){
            return data[rt];
        }
        pushdown(rt,l,r);
        int mid = (l+r)/2;
        int ret =  0;
        if (L<=mid) ret += query(rt*2,l,mid,L,R);
        if (mid<R) ret += query(rt*2+1,mid+1,r,L,R);
        return ret;
    }
        
};
