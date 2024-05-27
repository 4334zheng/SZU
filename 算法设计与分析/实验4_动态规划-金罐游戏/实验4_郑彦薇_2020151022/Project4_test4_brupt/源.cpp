#include<iostream>
#include<vector>
using namespace std;

#define A 1
#define B -1
int* choice_A;
int Count;

//�����ݹ飬ͨ�����ʹ�ö���tmp����ʵ�ֶ�A��ѡ��ļ�¼
int getScore(vector<int>& nums, int size, int start, int end, int cnt, int count)
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

//getScore���Ż�������A����¼�������ظ��������ȡ����
int getScore_new(vector<int>& nums, int start, int end)
{
	int scoreStart, scoreEnd;
	int gap = end - start;
	if (gap == 0)
		return nums[start];
	else if (gap == 1)
	{
		scoreStart = nums[start];
		scoreEnd = nums[end];
	}
	else if (gap >= 2)
	{
		int num = getScore_new(nums, start + 1, end - 1);//��ԭ���ظ������ֵ��ȡ����
		scoreStart = nums[start] + min(getScore_new(nums, start + 2, end), num);
		scoreEnd = nums[end] + min(getScore_new(nums, start, end - 2), num);
	}
	return max(scoreStart, scoreEnd);
}

//ʹ�õݹ����ֵ
int delta(vector<int>& nums, int start, int end)
{
	if (start == end)
		return nums[start];
	int scoreStart = nums[start] - delta(nums, start + 1, end);
	int scoreEnd = nums[end] - delta(nums, start, end - 1);
	return max(scoreStart, scoreEnd);
}

//delta���Ż���ʹ�ü��������¼�м���
int delta_new(vector<int>& nums, int start, int end, int **M)
{
	if (end == start)
		return nums[start];
	if (M[start][end])
		return M[start][end];
	int scoreStart = nums[start] - delta_new(nums, start + 1, end, M);
	int scoreEnd = nums[end] - delta_new(nums, start, end - 1, M);
	M[start][end] = max(scoreStart, scoreEnd);
	return M[start][end];
}

int main()
{
	vector<int>nums;
	int N = 20;
	srand((unsigned int)time(0));
	//int N = rand() % 10 + 1;
	cout << "��޸�����" << N << endl <<"�����Ϊ��";
	int sum = 0;
	for (int i = 0; i < N; i++)
	{
		int num = rand() % 500 + 1;
		//int num;
		//cin >> num;
		cout << num << " ";
		nums.push_back(num);
		sum += num;
	}
	cout << endl;

	/*
	//�Ż�ǰ��⣬��Aѡ��������
	choice_A = new int[N];
	for (int i = 0; i < N; i++)
		choice_A[i] = 0;

	clock_t start, finish;
	start = clock();
	int t = 1;
	int total_A;
	while (t--)
		total_A = getScore(nums, N, 0, N - 1, A, 0);
	finish = clock();

	
	cout << "A���ܽ����Ϊ��" << total_A << endl;
	cout << "A��ѡ��Ϊ��";
	for (int i = 0; i < N; i++)
		if(choice_A[i] != 0)
			cout << choice_A[i] << " ";
	cout << endl;
	//cout << "B���ܽ����Ϊ��" << sum - total_A << endl;
	//cout << "A��B��" << 2 * total_A - sum << "�����" << endl;
	cout << "A��B��" << delta(nums, 0, N - 1) << "�����" << endl;

	cout << "the time cost is:" << double(finish - start) / CLOCKS_PER_SEC << "s" << endl;
	*/
	
	//�Ż������
	int** M = new int* [N];//��������
	for (int i = 0; i < N; i++)
		M[i] = new int[N];
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			M[i][j] = 0;
	clock_t start,finish;
	int t = 10;
	int total_A;
	start = clock();
	while(t--)
		total_A = getScore_new(nums, 0, N - 1);
	finish = clock();
	cout << "A���ܽ����Ϊ��" << total_A << endl;
	cout << "B���ܽ����Ϊ��" << sum - total_A << endl;
	//cout << "A��B��" << delta_new(nums, 0, N - 1, M) << "�����" << endl;
	cout << "the time cost is:" << double(finish - start) / CLOCKS_PER_SEC << "s" <<endl;
	
	return 0;
}