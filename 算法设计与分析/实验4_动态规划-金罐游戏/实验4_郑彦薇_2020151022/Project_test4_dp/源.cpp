#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;

#define INF 0x3f3f3f3f
#define A 1
#define B -1

int enter = 0;
int DP_total(int* nums, int start, int end, int** dp)
{
	if (dp[start][end] != INF)
		return dp[start][end];
	enter++;
	if (start == end) {
		dp[start][end] = nums[start];
		return nums[start];
	}
	int startScore = nums[start] - DP_total(nums, start + 1, end, dp);
	int endScore = nums[end] - DP_total(nums, start, end - 1, dp);
	dp[start][end] = max(startScore, endScore);
	return dp[start][end];
}

int main()
{
	int N = 5000;
	int* nums = new int[N];
	for (int i = 0; i < N; i++)
	{
		nums[i] = rand() % 100 + 1;
	}
	int sum = 0;
	for (int i = 0; i < N; i++)
	{
		sum += nums[i];
	}
	int** dp = new int* [N];
	for (int i = 0; i < N; i++)
		dp[i] = new int[N];
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			dp[i][j] = INF;
	int start = clock();
	cout << "A获得的金币总数为:" << (sum + DP_total(nums, 0, N - 1, dp)) / 2 << endl;
	int end = clock();
	cout << "耗时:" << end - start << "ms" << endl;
	// for(int i = 0 ; i < N; i ++)
	// {
	// 	for(int j = 0 ; j < N; j ++)
	// 	{
	// 		printf("%10d ",dp[i][j]);
	// 	}
	// 	cout << endl;
	// }
	system("pause");
	return 0;
}