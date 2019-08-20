---
index: 5
title: Longest Up
---
Header
---
#include <bits/stdc++.h>
using namespace std;

vector<int> v1,v2,v3,v4,v5;


//二分法求最长不增子序列关键字下标（>=）
int binarySearch1(int key,int lowIndex,int highIndex)
{
    if(lowIndex==highIndex)
    {
        if(lowIndex == 0 && key>v2[0])
        {
            return lowIndex;
        }
        return lowIndex+1;

    }
    int midIndex = (lowIndex + highIndex + 1)/2;
    if(key<=v2[midIndex])
    {
        return binarySearch1(key,midIndex,highIndex);
    }
    else
    {
        return binarySearch1(key,lowIndex,midIndex-1);
    }
}
//二分法求最长单调递减子序列关键字下标(>)
int binarySearch2(int key,int lowIndex,int highIndex)
{
    if(lowIndex==highIndex)
    {
        if(key<v3[lowIndex])
        {
            return lowIndex+1;
        }
        return lowIndex;

    }
    int midIndex = (lowIndex + highIndex + 1)/2;
    if(key<v3[midIndex])
    {
        return binarySearch2(key,midIndex,highIndex);
    }
    else
    {
        return binarySearch2(key,lowIndex,midIndex-1);
    }
}
//二分法求最长不降子序列关键字下标(<=)
int binarySearch3(int key,int lowIndex,int highIndex)
{
    if(lowIndex==highIndex)
    {

        if(lowIndex == 0 && key<v4[0])
        {
            return lowIndex;
        }
        return lowIndex+1;

    }
    int midIndex = (lowIndex + highIndex + 1)/2;
    if(key<v4[midIndex])
    {
        return binarySearch3(key,lowIndex,midIndex-1);
    }
    else
    {
        return binarySearch3(key,midIndex,highIndex);
    }
}
//二分法求最长单调递增子序列关键字下标(<)
int binarySearch4(int key,int lowIndex,int highIndex)
{
    if(lowIndex==highIndex)
    {
        if(v5[lowIndex] == key)
        {
            return lowIndex;
        }
        else if(lowIndex == 0 && key<v5[0])
        {
            return lowIndex;
        }
        return lowIndex+1;

    }
    int midIndex = (lowIndex + highIndex + 1)/2;
    if(key<v5[midIndex])
    {
        return binarySearch4(key,lowIndex,midIndex-1);
    }
    else
    {
        return binarySearch4(key,midIndex,highIndex);
    }
}
int countTotal()
{
    int lowIndex = 0;
    v2.push_back(v1[0]);
    v3.push_back(v1[0]);
    v4.push_back(v1[0]);
    v5.push_back(v1[0]);

    for(int i=1;i<v1.size();i++)
    {
        //No.1
        lowIndex = binarySearch1(v1[i],0,v2.size()-1);
        if(lowIndex>v2.size()-1)
        {
            v2.push_back(v1[i]);
        }
        else
        {
            v2[lowIndex] = v1[i];
        }
        //No.2
        lowIndex = binarySearch2(v1[i],0,v3.size()-1);
        if(lowIndex>v3.size()-1)
        {
            v3.push_back(v1[i]);
        }
        else
        {
            v3[lowIndex] = v1[i];
        }
        //No.3
        lowIndex = binarySearch3(v1[i],0,v4.size()-1);
        if(lowIndex>v4.size()-1)
        {
            v4.push_back(v1[i]);
        }
        else
        {
            v4[lowIndex] = v1[i];
        }
        /.4
        lowIndex = binarySearch4(v1[i],0,v5.size()-1);
        if(lowIndex>v5.size()-1)
        {
            v5.push_back(v1[i]);
        }
        else
        {
            v5[lowIndex] = v1[i];
        }

    }

    cout<<"最长不增子序列长度："<<v2.size()<<endl;
    cout<<"最长单调递减子序列长度："<<v3.size()<<endl;
    cout<<"最长不降子序列长度："<<v4.size()<<endl;
    cout<<"最长单调递增子序列长度："<<v5.size()<<endl;

}


int main()
{
    int n;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        int a;
        cin>>a;
        v1.push_back(a);
    }
    if(n!=0)
    {
        countTotal();
    }
    return 0;
}
