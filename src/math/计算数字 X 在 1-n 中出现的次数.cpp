---
index: 11
title: Count
---
计算数字 X 在 1-n 中出现的次数。
---
int count(int n, int x) {
    int cnt = 0, k;
    for (int i = 1;k = n / i;i *= 10) {
        // 高位的数字。
        int high = k / 10;
        if (x == 0) {
            if (high) {
                high--;
            } else {
                break;
            }
        }
        cnt += high * i;
        // 当前位的数字。
        int cur = k % 10;
        if (cur > x) {
            cnt += i;
        } else if (cur == x) {
            // n - k * i 为低位的数字。
            cnt += n - k * i + 1;
        }
    }
    return cnt;
}
