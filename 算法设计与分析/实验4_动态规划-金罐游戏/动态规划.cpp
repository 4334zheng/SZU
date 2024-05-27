#include <iostream>
#include <cmath>
#include <cstring>
#include <time.h>
#include <cstdlib>
using namespace std;
int *array;  //��� 
int nums; //����� 
int **dp; //��̬�滮���� 
// �ݹ��൱�ڱ����� 

//��̬�滮
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
		cout<<"AӮ\n";
	}
	else
	{
		cout<<"BӮ\n";
	}
}
int main()
{
	cout<<"��������Ҫ�Ľ����\n";
	cin>>nums;
	/*for(int i=1;i<=nums;i++)
		cin>>array[i];*/
	array=new int[nums+2];
    for(int i=1;i<=nums;i++)
	{
		array[i]=rand()%500+1; //�����ֵ������
		//cout<<array[i]<<' ';
	}
	cout<<"\n";
	clock_t startTime, endTime; 
	startTime = clock();
	DynamicProgramme();
	endTime = clock();
	cout << "����ʱ��Ϊ" << (endTime - startTime)*1000 / CLOCKS_PER_SEC<<"ms\n";
	return 0;
}
