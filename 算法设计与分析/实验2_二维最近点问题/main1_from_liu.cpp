
#include <bits/stdc++.h>
#define n 10

using namespace std;

struct point
{
    double x;
    double y;
};

double Distance(point p1, point p2)
{
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
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

void Merge(point *p,int left,int right,int mid)
{
    point temp[right - left + 1];
    int i = 0;
    int lindex = left;
    int rindex = mid + 1;
    while(lindex <= mid && rindex <= right)
    {
        temp[i++] = p[lindex].y < p[rindex].y ? p[lindex++] : p[rindex++];
    }
    while(lindex <= mid)
        temp[i++] = p[lindex++];
    while(rindex <= right)
        temp[i++] = p[rindex++];
    for(i=0;i < right - left + 1;i++)
        p[left + i] = temp[i];
}

static void Mergesort(point *p,int left,int right)
{
    if(left == right)
        return;
    int mid = (left + right) / 2;
    Mergesort(p,left,mid);
    Mergesort(p,mid + 1,right);
    Merge(p,left,right,mid);
}

double Shortdist(point *p,int low,int high,point *p1)
{
    double d,d1,d2,d3;
    int i,j,mid,index = 0;
    point tmp1[2],tmp2[2];
    point P[n];


    if(high - low == 1)   //只有两个点
        return Distance(p[low],p[high]);

    if(high - low == 2)  //只有3个点
    {
        double dist1 = Distance(p[low],p[low + 1]);
        double dist2 = Distance(p[low + 1],p[high]);
        double dist3 = Distance(p[low],p[high]);
        if(dist1 < dist2 && dist1 < dist3)
        {
            p1[0] = p[low];
            p1[1] = p[low + 1];
            return dist1;
        }

        if(dist2 < dist1 && dist2 < dist3)
        {
            p1[0] = p[low + 1];
            p1[1] = p[high];
            return dist2;
        }
        if(dist3 < dist2 && dist3 < dist1)
        {
            p1[0] = p[low];
            p1[1] = p[high];
            return dist3;
        }

    }

    mid = (low + high) / 2;
    d1 = Shortdist(p,low,mid,p1);
    tmp1[0] = p1[0];
    tmp1[1] = p1[1];
    d2 = Shortdist(p,mid+1,high,p1);
    tmp2[0] = p1[0];
    tmp2[1] = p1[1];
    d = Min(d1,d2);

    if(d == d1)
    {
        p1[0] = tmp1[0];
        p1[1] = tmp1[1];
    }
    else if(d == d2)
    {
        p1[0] = tmp2[0];
        p1[1] = tmp2[1];
    }

    for(i = mid;(i>=low) && ((p[mid].x - p[i].x)<d);i--)
        P[index++] = p[i];
    for(i = mid + 1;(i<=high) && ((p[i].x - p[mid].x)<d);i++)
        P[index++] = p[i];
    Mergesort(P,0,index-1);
    for(i = 0;i < index;i++)
    {
        for(j = i+1;j<=i+6;j++)
        {
            d3 = Distance(P[i],P[j]);
            if(d3 < d)
            {
                d = d3;
                p1[0] = P[i];
                p1[1] = P[j];
            }
        }
    }
    return d;
}

//double Shortestdist1(point *d)
//{
//    double min = 1e20;
//    for(int i=0;i<n;i++)
//    {
//        for(int j = i+1;j<n;j++)
//        {
//            double dist = Distance(d[i],d[j]);
//            if(dist < min)
//                min = dist;
//        }
//    }
//    return min;
//}



int main() {
    point p[n];

    srand((unsigned int)time(0));

    for(int i=0;i<n;i++)
    {
        p[i].x = rand();
        p[i].y = rand();
    }
    sort(p,p+n, cmpx);

    point p1[2];

    double shortestdist = Shortdist(p,0,n-1,p1);

    cout<<shortestdist<<endl;
    cout<<p1[0].x<<" "<<p1[0].y<<endl;
    cout<<p1[1].x<<" "<<p1[1].y<<endl;
    //cout<<Shortestdist1(p)<<endl;
}
