---
index: 4
title: Longest Manhadun
---
Header
---
const int maxn = 200005;
ll a[maxn][7];

ll n,m,k;
scanf("%lld%lld%lld",&n,&m,&k);
for (int i=0; i<n; i++)
    for (int j=0; j<k; j++) 
        scanf("%lld", &a[i][j]);
ll ans = 0;
for (int s=0; s<(1<<k); s++){
    ll  mi = inf, mx = -inf;
    for (int i=0; i<n+m; i++) {
        ll  t = 0;
        for (int j=0; j<k; j++)
            if ((1<<j) & s) t += a[i][j];
            else t -= a[i][j];
        mi = min(mi, t);
        mx = max(mx, t);
    }
    ans = max(ans, mx-mi);
}
printf("%lld\n",ans);


//n个5维坐标的点，求这n个点中曼哈顿距离的最大值。
//暴力枚举肯定超时。
//只考虑二维空间上两个坐标之间的曼哈顿距离(x1, y1) 和 (x2, y2)，|x1-x2| +|y1-y2|去掉绝对值符号后共有下列四种情况
//(x1-x2) + (y1-y2), (x1-x2) + (y2-y1), (x2-x1) + (y1-y2), (x2-x1) + (y2-y1)
//转化一下：
//(x1+y1) - (x2+y2), (x1-y1) - (x2-y2), (-x1+y1) - (-x2+y2), (-x1-y1) - (-x2-y2)
//显然，任意给两个点，我们分别计算上述四种情况，那么最大值就是曼哈顿距离。
//转化后，“-”号两侧的坐标形式是一样的。维数为5，因此我们可以用二进制枚举。
//最大曼哈顿距离 = max{每种情况下的最大值-最小值}
