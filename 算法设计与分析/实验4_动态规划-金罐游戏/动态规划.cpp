#include <iostream>
#include <cmath>
#include <cstring>
#include <time.h>
#include <cstdlib>
using namespace std;
int *array;  //金罐 
int nums; //金罐数 
int **dp; //动态规划矩阵 
// 递归相当于暴力法 

//动态规划
void DynamicProgramme()
{
	dp=new int*[nums+2];
	for(int i=0;i<=nums+2;i++)	
		dp[i]=new int[nums+2];
	for(int i=1;i<=nums;i++)
	{
        dp[i][i] = array[i];
    }	
    for(int i=nums-1;i>=1;i--)
    	for(int j=i+1;j<=nums;j++)
    	{
    		int Left=array[i]-dp[i+1][j];
    		int Right=array[j]-dp[i][j-1];
    		dp[i][j]=max(Left,Right);
		}
	if(dp[1][nums]>=0)
	{
		cout<<"A赢\n";
	}
	else
	{
		cout<<"B赢\n";
	}
}
int main()
{
	cout<<"请输入想要的金币数\n";
	cin>>nums;
	/*for(int i=1;i<=nums;i++)
		cin>>array[i];*/
	array=new int[nums+2];
    for(int i=1;i<=nums;i++)
	{
		array[i]=rand()%500+1; //随机赋值给数组
		//cout<<array[i]<<' ';
	}
	cout<<"\n";
	clock_t startTime, endTime; 
	startTime = clock();
	DynamicProgramme();
	endTime = clock();
	cout << "运行时间为" << (endTime - startTime)*1000 / CLOCKS_PER_SEC<<"ms\n";
	return 0;
}
