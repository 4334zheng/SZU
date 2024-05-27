#include <iostream>
#include <cmath>
#include <cstring>
#include <time.h>
#include <cstdlib>
using namespace std;
int array[100000];  //金罐 
int nums; //金罐数 
int **M; //记忆矩阵 
// 递归相当于暴力法 
int recursion(int i,int j)
{
	if(i==j)   //边界 
	{
		return array[i];
	}
	int Left=array[i]-recursion(i+1,j); //选左边分数差 
	int Right=array[j]- recursion(i,j-1); //选右边分数差 
	if(Left>Right)
	{
		return Left;
	}
	else
	{
		return Right;
	}
}
void Recursion() 
{
    int ans=recursion(1,nums);
    if(ans>=0)
	{
		cout<<"A赢\n";
	}
	else
	{
		cout<<"B赢\n";
	}
}

// 记忆化递归

int momeryrecursion(int i,int j)
{
	if(i==j)   //边界 
	{
		return array[i];
	}
	if(M[i][j]!=-1)  //如果记忆数组M不是初始值，直接 return 
	{
		return M[i][j];
	}
	int Left=array[i]-recursion(i+1,j); //选左边分数差 
	int Right=array[j]- recursion(i,j-1); //选右边分数差 
	M[i][j]=max(Left,Right);
	return M[i][j];
}


void MomeryRecursion()
{
	M=new int*[nums];
	for(int i=1;i<=nums;i++)	
		M[i]=new int[nums];
	for(int i=1;i<=nums;i++)
		for(int j=1;j<=nums;j++)
			M[i][j]=-1;
    int ans=momeryrecursion(1,nums);
    if(ans>=0)
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
    for(int i=1;i<=nums;i++)
	{
		array[i]=rand()%500+1; //随机赋值给数组
		//cout<<array[i]<<' ';
	}
	cout<<"\n";	
	clock_t startTime, endTime; 
	/*startTime = clock();
	Recursion();
	endTime = clock();
	cout << "运行时间为" << (endTime - startTime)*1000 / CLOCKS_PER_SEC<<"ms\n";*/
	startTime = clock();	
	MomeryRecursion();
	endTime = clock();
	cout << "运行时间为" << (endTime - startTime)*1000 / CLOCKS_PER_SEC<<"ms\n";
	return 0;
}
