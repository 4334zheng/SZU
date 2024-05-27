
#include <bits/stdc++.h>
#define n 40000

using namespace std;

clock_t start,End;

struct point
{
    double x,y;
};
point p[1000001];
point tmp[1000001];

double Distance(point p1, point p2)
{
    if (p1.x == p2.x && p1.y == p2.y)
        return 1e20;

    double dist = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
    return dist;
}

double Min(double d1,double d2)
{
    return d1 < d2? d1 : d2;
}

bool cmpx(point a,point b)
{
    return a.x < b.x;
}

bool cmpy(point a,point b)
{
    return a.y < b.y;
}


double Shortdist2(point *p, int low, int high)
{

    double d,d1,d2,d3;
    int i,j,mid,index = 0;
    if(high == low)
        return 1e20;
    if(high - low == 1)   //只有两个点
        return Distance(p[low],p[high]);

    if(high - low == 2)  //只有3个点
    {
        double dist1 = Distance(p[low],p[low + 1]);
        double dist2 = Distance(p[low + 1],p[high]);
        double dist3 = Distance(p[low],p[high]);
        if(dist1 < dist2 && dist1 < dist3)
        {
            return dist1;
        }

        if(dist2 < dist1 && dist2 < dist3)
        {
            return dist2;
        }
        if(dist3 < dist2 && dist3 < dist1)
        {
            return dist3;
        }

    }

    mid = (low + high) / 2;
    d1 = Shortdist2(p, low, mid);
    d2 = Shortdist2(p, mid + 1, high);
    d = Min(d1,d2);


    for(i = mid;(i>=low) && ((p[mid].x - p[i].x)<d);i--)
        tmp[index++] = p[i];
    for(i = mid + 1;(i<=high) && ((p[i].x - p[mid].x)<d);i++)
        tmp[index++] = p[i];
    sort(tmp,tmp+index,cmpy);


    for(i = 0;i < index;i++)
    {
        for(j = i+1;j<=i+6;j++)
        {
            d3 = Distance(tmp[i],tmp[j]);
            if(d3 < d)
            {
                d = d3;
            }
        }
    }
    return d;
}

double Shortdist3(point *p, int low, int high)
{
    if(low >= high)
        return 1e20;
    if(low + 1 == high)
        return Distance(p[low],p[high]);
    int mid = (low + high) / 2;
    double cut = p[mid].x;  //需要提前记录，因为后面排序之后这个值可能会改变
    double d1 = Shortdist3(p, low, mid);
    double d2 = Shortdist3(p, mid + 1, high);
    double d = Min(d1,d2);
    //从这里开始归并排序
    //这里可以直接修改p，两侧已经对x已经进行过一次分治，cut值已经记录过，不必要继续维护x轴的顺序
    int l = low,h = mid + 1,index = 0;
    while(l <= mid && h <= high)
    {
        if(p[l].y <= p[h].y)
            tmp[index++] = p[l++];
        else
            tmp[index++] = p[h++];
    }
    while(l <= mid)
        tmp[index++] = p[l++];
    while(h <= high)
        tmp[index++] = p[h++];
    for(int i=0;i<index;i++)
        p[low + i] = tmp[i];
    //归并排序完成
    index = 0;
    for(int i=low;i <= high;i++)
    {
        if(fabs(p[i].x - cut) <= d)
            tmp[index++] = p[i];
    }
    for(int i=0;i<index;i++)
    {
        for(int j=i+1;j<=6;j++)
        {
            d = Min(d, Distance(tmp[i], tmp[j]));
        }
    }
    return d;
}


double Shortdist1(point *d) // 蛮力法
{
    double min = 1e20;
    for(int i=0;i<n;i++)
    {
        for(int j = i+1;j<n;j++)
        {
            double dist = Distance(d[i],d[j]);
            if(dist < min)
                min = dist;
        }
    }
    return min;
}





int main() {
    srand((unsigned int)time(0));

    for(int i=0;i<n;i++)
    {
        p[i].x = rand();
        p[i].y = rand();
    }
    sort(p,p+n, cmpx);

    start = clock();
    //double Shortestdist1 = Shortdist1(p);          //蛮力法
    double Shortestdist2 = Shortdist2(p, 0, n - 1);    // 分治法
    //double Shortestdist3 = Shortdist3(p, 0, n - 1);    //分治法归并排序
    cout<<endl;
    End = clock();

    //cout<<Shortestdist1<<endl;
    //cout<<Shortestdist2<<endl;
    //cout<<Shortestdist3<<endl;

    double sumtime = (double)(End - start)/CLOCKS_PER_SEC ;
    cout<<sumtime * 1000 <<"ms"<<endl;
//    cout<<Shortestdist1(p)<<endl;
}

