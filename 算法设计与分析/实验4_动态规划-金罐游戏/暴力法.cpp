#include <iostream>
#include <cmath>
#include <cstring>
#include <time.h>
#include <cstdlib>
using namespace std;
int array[100000];  //��� 
int nums; //����� 
int **M; //������� 
// �ݹ��൱�ڱ����� 
int recursion(int i,int j)
{
	if(i==j)   //�߽� 
	{
		return array[i];
	}
	int Left=array[i]-recursion(i+1,j); //ѡ��߷����� 
	int Right=array[j]- recursion(i,j-1); //ѡ�ұ߷����� 
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
		cout<<"AӮ\n";
	}
	else
	{
		cout<<"BӮ\n";
	}
}

// ���仯�ݹ�

int momeryrecursion(int i,int j)
{
	if(i==j)   //�߽� 
	{
		return array[i];
	}
	if(M[i][j]!=-1)  //�����������M���ǳ�ʼֵ��ֱ�� return 
	{
		return M[i][j];
	}
	int Left=array[i]-recursion(i+1,j); //ѡ��߷����� 
	int Right=array[j]- recursion(i,j-1); //ѡ�ұ߷����� 
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
    for(int i=1;i<=nums;i++)
	{
		array[i]=rand()%500+1; //�����ֵ������
		//cout<<array[i]<<' ';
	}
	cout<<"\n";	
	clock_t startTime, endTime; 
	/*startTime = clock();
	Recursion();
	endTime = clock();
	cout << "����ʱ��Ϊ" << (endTime - startTime)*1000 / CLOCKS_PER_SEC<<"ms\n";*/
	startTime = clock();	
	MomeryRecursion();
	endTime = clock();
	cout << "����ʱ��Ϊ" << (endTime - startTime)*1000 / CLOCKS_PER_SEC<<"ms\n";
	return 0;
}
