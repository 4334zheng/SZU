//С��ģ�¶��㷨��֤
#include<iostream>
#include<vector>
using namespace std;

#define A 1
#define B -1
int* choice_A;
int Count;
int* SUM;

//�����ݹ飬ͨ�����ʹ�ö���tmp����ʵ�ֶ�A��ѡ��ļ�¼
int getScore(int* nums, int size, int start, int end, int cnt, int count)
{
	if (cnt == A) {
		if (start == end) {
			choice_A[count] = nums[start];
			return nums[start];
		}
		int temp1 = nums[start] + getScore(nums, size, start + 1, end, B, count + 1);
		int* tmp = new int[size];
		for (int i = 0; i < size; i++)
			tmp[i] = choice_A[i];
		int temp2 = nums[end] + getScore(nums, size, start, end - 1, B, count + 1);
		if (temp1 > temp2)
		{
			for (int i = 0; i < size; i++)
				choice_A[i] = tmp[i];
			choice_A[count] = nums[start];
			delete[]tmp;
			return temp1;
		}
		choice_A[count] = nums[end];
		delete[]tmp;
		return temp2;
	}
	if (start == end)
		return 0;
	int p1 = getScore(nums, size, start + 1, end, A, count);
	int* tmp = new int[size];
	for (int i = 0; i < size; i++)
		tmp[i] = choice_A[i];
	int p2 = getScore(nums, size, start, end - 1, A, count);
	if (p1 < p2)
	{
		for (int i = 0; i < size; i++)
			choice_A[i] = tmp[i];
		delete[]tmp;
		return p1;
	}
	delete[]tmp;
	return p2;
}

void Brupt_print(int N)
{
	cout << "A��ѡ���";
	for (int i = 0; i < N; i++)
		if (choice_A[i] != 0)
			cout << choice_A[i] << " ";
	cout << endl;
}

//��̬�滮�����������Զ�����
int DP_total(int* nums, int start, int end, int cnt, int** dp)
{
	if (cnt == A)
	{
		if (dp[start][end] >= 0)
			return dp[start][end];
		if (start == end)
			return nums[start];
		int p1 = nums[start] + DP_total(nums, start + 1, end, B, dp);
		int p2 = nums[end] + DP_total(nums, start, end - 1, B, dp);
		if (p1 > p2)
		{
			dp[start][end] = p1;//���
			return p1;
		}
		dp[start][end] = p2;//���
		return p2;
	}
	if (start == end)
		return 0;
	int sum = SUM[end] - SUM[start] + nums[start];
	int q1 = DP_total(nums, start + 1, end, A, dp);
	int q2 = DP_total(nums, start, end - 1, A, dp);
	if (q1 < q2)
	{
		dp[start][end] = sum - q1;//���
		return q1;
	}
	dp[start][end] = sum - q2;//���
	return q2;
}
void DP_print(int* nums, int start, int end, int** dp)
{
	cout << "A��ѡ���";
	//��̬�滮��¼��ҵ�ѡ��
	int i = start, j = end - 1;
	int a = 0, b = 0;
	int** choice_AB = new int* [2];
	choice_AB[0] = new int[end];
	choice_AB[1] = new int[end];
	for (int i = 0; i < end; i++) {
		choice_AB[0][i] = 0;
		choice_AB[1][i] = 0;
	}
	int cnt = A;
	for (int k = 0; k < end - 1; k++)
	{
		if (dp[i + 1][j] < dp[i][j - 1])
		{
			if (cnt == A)
			{
				choice_AB[0][a++] = nums[i];
				cnt = B;
			}
			else
			{
				choice_AB[1][b++] = nums[i];
				cnt = A;
			}
			i++;
		}
		else
		{
			if (cnt == A)
			{
				choice_AB[0][a++] = nums[j];
				cnt = B;
			}
			else
			{
				choice_AB[1][b++] = nums[j];
				cnt = A;
			}
			j--;
		}
	}
	for (int i = 0; i < a; i++)
		cout << choice_AB[0][i] << " ";
	cout << endl;
}

int main()
{
	int N = 20;
	srand((unsigned int)time(0));
	//int N = rand() % 20 + 1;
	cout << "�������Ϊ��" << N;
	//vector<int>nums;
	int* nums = new int[N];
	for (int i = 0; i < N; i++)
	{
		//int num = rand() % 10000 + 1;
		//nums.push_back(num);
		nums[i] = rand() % 10000 + 1;
	}

	cout << endl << "�����ݹ�Ľ����" << endl;
	choice_A = new int[N];
	for (int i = 0; i < N; i++)
		choice_A[i] = 0;
	cout << "A��õĽ��������" << getScore(nums, N, 0, N - 1, A, 0) << endl;
	Brupt_print(N);

	cout << endl << "��̬�滮�Ľ����" << endl;
	int** dp = new int* [N];
	for (int i = 0; i < N; i++) {
		dp[i] = new int[N];
		for (int j = 0; j < N; j++)
			dp[i][j] = -1;
		dp[i][i] = nums[i];
	}
	SUM = new int[N];
	SUM[0] = nums[0];
	for (int i = 1; i < N; i++)
		SUM[i] = SUM[i - 1] + nums[i];
	cout << "A��õĽ��������" << DP_total(nums, 0, N - 1, A, dp) << endl;
	DP_print(nums, 0, N, dp);

	return 0;
}