#include<iostream>
using namespace std;
#include<cmath>
#include<time.h>

#define n 1000

struct point {
    int x;
    int y;
};

point* temp1 = (point*)malloc(sizeof(point) * n);

double dis(point dot1, point dot2)
{
    double d = sqrt((dot1.x - dot2.x) * (dot1.x - dot2.x) + (dot1.y - dot2.y) * (dot1.y - dot2.y));
    return d;
}

void merge_X(point* dot, int low, int mid, int high)
{
    //struct point* dot1 = new point[n];
    for (int k = low; k < high + 1; k++)
        temp1[k] = dot[k];
    int i = low, j = mid + 1, k = low;
    while (i < mid + 1 && j < high + 1)
    {
        if (temp1[i].x < temp1[j].x)
            dot[k++] = temp1[i++];
        else
            dot[k++] = temp1[j++];
    }
    while (i < mid + 1)
        dot[k++] = temp1[i++];
    while (j < high + 1)
        dot[k++] = temp1[j++];
    //delete[]dot1;
}

void MergeSort_X(point* dot, int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        MergeSort_X(dot, low, mid);
        MergeSort_X(dot, mid + 1, high);
        merge_X(dot, low, mid, high);
    }
}

void merge_Y(point* temp, int low, int mid, int high)
{
    //struct point* temp1 = new point[n];
    for (int k = low; k < high + 1; k++)
        temp1[k] = temp[k];
    int i = low, j = mid + 1, k = low;
    while (i < mid + 1 && j < high + 1)
    {
        if (temp1[i].y < temp1[j].y)
            temp[k++] = temp1[i++];
        else
            temp[k++] = temp1[j++];
    }
    while (i < mid + 1)
        temp[k++] = temp1[i++];
    while (j < high + 1)
        temp[k++] = temp1[j++];
    //delete[]temp1;
}

void MergeSort_Y(point* temp, int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        MergeSort_Y(temp, low, mid);
        MergeSort_Y(temp, mid + 1, high);
        merge_Y(temp, low, mid, high);
    }
}

double func(point dot[], int left, int right, point dot1[])
{
    double min_d, min_dl, min_dr;
    int mid = (left + right) / 2;
    if (left == right)//一个点，返回无穷
        return 99999999;
    if (left + 1 == right)//两个点，直接返回两点间距离
    {
        dot1[0] = dot[left];
        dot1[1] = dot[right];
        min_d = dis(dot[left], dot[right]);
        return min_d;
    }

    //多于2个点根据点的个数划分为两个点集，递归求解左右两个点集
    point* dotL = new point[2];
    min_dl = func(dot, left, mid, dot1);
    dotL[0] = dot1[0];
    dotL[1] = dot1[1];
    point* dotR = new point[2];
    min_dr = func(dot, mid + 1, right, dot1);
    dotR[0] = dot1[0];
    dotR[1] = dot1[1];
    if (min_dl > min_dr) {
        min_d = min_dr;
        dot1[0] = dotR[0];
        dot1[1] = dotR[1];
    }
    else {
        min_d = min_dl;
        dot1[0] = dotL[0];
        dot1[1] = dotL[1];
    }
    //将位于中线两侧的点存储到temp中
    struct point* temp = new point[right - left + 1];
    int m = 0;
    for (int i = left; i <= right; i++)
    {
        if (dot[i].x > (dot[mid].x - min_d) && dot[i].x < (dot[mid].x + min_d)) {
            temp[m++] = dot[i];
        }
    }
    //对temp按y的值进行排序
    MergeSort_Y(temp, 0, m-1);
    
    //求中线两侧点对距离
    for (int i = 0; i <= m-1; i++)
    {
        for (int j = i + 1; j <= m-1 && j <= i + 6; j++)
        {
            if ((temp[j].y - temp[i].y) > min_d)
                break;
            if (dis(temp[i], temp[j]) <= min_d)
            {
                min_d = dis(temp[i], temp[j]);
                dot1[0] = temp[i];
                dot1[1] = temp[j];
            }
        }
    }
    delete[]temp;
    delete[]dotL;
    delete[]dotR;
    return min_d;
}

void Divide(point dot[])
{
    struct point* dot_temp = new point[n];
    for (int i = 0; i < n; i++)
        dot_temp[i] = dot[i];
    double min_d;
    struct point* dot1 = new point[2];

    clock_t start, finish;
    int t = 1;//repeating the process
    start = clock();
    while (t--)
    {
        for (int i = 0; i < n; i++)
            dot[i] = dot_temp[i];
        //根据x的大小对dot进行排序
        MergeSort_X(dot, 0, n-1);
        
        //分治递归
        min_d = func(dot, 0, n-1, dot1);

    }
    finish = clock();

    cout << "The minimun distance is: " << min_d << endl;
    cout << "The time cost is: " << double(finish - start) / CLOCKS_PER_SEC << endl;
    cout << "These two point are:(" << dot1[0].x << "," << dot1[0].y << ")and(" << dot1[1].x << "," << dot1[1].y << ")" << endl;
    delete[]dot_temp;
    delete[]dot1;
}

void Brute(point dot[])
{
    double min_d = 99999999;
    double d;
    int t = 1;//repeating the process
    clock_t start, finish;
    int k1, k2;
    start = clock();
    while (t--) {
        for (int i = 0; i < n - 1; i++)
            for (int j = i + 1; j < n; j++) {
                d = sqrt((dot[i].x - dot[j].x) * (dot[i].x - dot[j].x) + (dot[i].y - dot[j].y) * (dot[i].y - dot[j].y));
                if (min_d > d) {
                    min_d = d;
                    k1 = i;
                    k2 = j;
                }
            }
    }
    finish = clock();
    cout << "The minimun distance is: " << min_d << endl;
    cout << "The time cost is: " << double(finish - start) / CLOCKS_PER_SEC << endl;
    cout << "These two point are:(" << dot[k1].x << "," << dot[k1].y << ")and(" << dot[k2].x << "," << dot[k2].y << ")" << endl;
}

int main()
{
    struct point* dot = new point[n];
    srand((unsigned int)time(0));

    for (int i = 0; i < n; i++)
    {
        dot[i].x = rand() % (10 * n);
        dot[i].y = rand() % (10 * n);
    }

    Brute(dot);
    Divide(dot);
    delete[]dot;

    return 0;
}