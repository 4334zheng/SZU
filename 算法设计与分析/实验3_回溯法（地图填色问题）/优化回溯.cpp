#include <iostream>
#include <time.h>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;

#define CNum 5    //��ɫ��
#define Num 450    //����

class Node 
{
public:
    int color;  //��ǰ��ɫ 
    int ColorState[CNum + 1];  //��ɫ״̬��1Ϊ��ѡ����1Ϊ����ѡ
    int ColorNum;  //��ѡ��ɫ������ColorState��1������
    int NextNum;  //���� 
    Node()   //��ʼ�� 
	{
        color = 0;
        for (int i = 0; i < CNum + 1; ++i) 
		{
            ColorState[i] = 1;
        }
        ColorNum = CNum;
        NextNum = 0;
    }
};


int map[Num + 1][Num+1];  //�ڽӱ�
int MRV(Node *node)
{
	int min=9999;
	int ans=0;
	for(int i=1;i<=Num;i++)
	{
		if(node[i].color==0) //û���ʹ��ĵ� 
		{
			int min1=node[i].ColorNum; //�õ��ܹ�Ⱦɫ�������� 
			if(min>min1)
			{
				min=min1;
				ans=i;
			}
		}	
	}
	return ans;
}
int MRVAndDH(Node *node)
{
	int min=9999;
	int ans;
	for(int i=1;i<=Num;i++)
	{
		if(node[i].color==0) //ûȾɫ���ĵ� 
		{
			int min1=node[i].ColorNum; //�õ��ܹ�Ⱦɫ��������
			if(min>min1)
			{
				min=min1;
				ans=i;
			}
			else if(min==min1)//����ͬ����СȾɫ��ʱ 
			{
				if(node[i].NextNum>node[ans].NextNum)  //ѡ�������� 
				{
					ans=i;
				}
			} 
		}
	}
	return ans;
}
bool front(Node *node,int type,int j,int v)  //��ǰ̽�� 
{
	node[j].ColorState[type] = -v; //ɾ���õ���ɫ 
    node[j].ColorNum--;  //���ڽӵ��Ⱦɫ��Ŀ��һ 
    node[j].NextNum--;  //���ڽӵ����ض�����һ 
	if(node[j].ColorNum<=0)  //����ɾ���ڵ��û��������ɫ���� 
		return false;
	return true;
	
}
//���ݷ����� 
long long DFS(Node *node, int v, int count, int used) 
{
    if (count == Num) //�����һ���㣬�Żظõ�ķ����� 
    {
        return node[v].ColorNum;
    } 
	else 
	{
        long long ans = 0;
        for (int i = 1; i <= CNum; i++) 
		{
            if (node[v].ColorState[i] == 1) //�õ�v����Ⱦiɫ 
			{
                long long tempans = 0;
                node[v].color = i;   //�õ���ɫ��¼ 
                bool NewColor = i > used;  //�Ƿ�����ʹ�õ���ɫ�� �Ǿ�Ϊtrue ��֮Ϊfalse 
                
                for (int k = 1; k <= map[v][0]; ++k) 
				{
                    int j = map[v][k]; //jΪ�ڽӵĵ� 
                    if (node[j].color == 0 && node[j].ColorState[i] == 1) //δͿɫ�Ҹ���ɫ��ѡ 
					{
                        if(front(node,i,j,v)==false)
                        {
                        	goto Recall;  //��ǰ̽�鷢�ִ���ֱ�ӻ��� 
						}
                    }
                }
                if (NewColor==true)
                    tempans = DFS(node, MRVAndDH(node), count + 1, used + 1);
                else
                    tempans = DFS(node, MRVAndDH(node), count + 1, used);

                Recall:  //������� 
                for (int k = 1; k <= map[v][0]; ++k) 
				{
                    int j = map[v][k];
                    if (node[j].ColorState[i] == -v) //�����Ż� 
					{
                        node[j].ColorNum++;//��Ⱦ��Ŀ++ 
                        node[j].NextNum++;//����++ 
                        node[j].ColorState[i] = 1;//���� 
                    }
                }
                node[v].color = 0;  //���� 
                if (NewColor==true) //�����ɫΪ�� ,��Ѱ 
				{
                    ans += tempans * (CNum - used);
                    break;
                }
                ans += tempans;
            }
        }
        if (ans>100000000)  //15ɫ  ��25ɫ 
		{
			cout<<ans<<"\n";
		}
        return ans;
    }
}

int main() 
{
    Node node[Num + 1];
    fstream open("D://TempProject/le450_5a.col");
    //fstream open("D://TempProject/le450_25a.col");
    //fstream open("D://TempProject/le450_15b.col");
	string line;
	while(getline(open,line))
	{
		if(line[0]=='e') //Ϊmap�ڽӾ���ֵ 
		{
			int i=2;
			string temp1,temp2;
			while(1)
			{
				temp1+=line[i];
				i++;
				if(line[i]<'0'||line[i]>'9')
					break;
			}
			i++;
			while(1)
			{
				temp2+=line[i];
				i++;
				if(line[i]<'0'||line[i]>'9')
					break;
			}
			stringstream stream1(temp1);
			stringstream stream2(temp2);
			int v1,v2;
			stream1>>v1;stream2>>v2;
			//���� 1 330   map[1][0]=1   map[1][1]=330 
			//map[330][0]=1   map[330][1]=1
			map[v1][0]++;
		    map[v1][map[v1][0]] = v2;
		    map[v2][0]++;
		    map[v2][map[v2][0]] = v1;
		    node[v1].NextNum++; //�ȼ�һ 
		    node[v2].NextNum++;
		    //cout<<v1<<" "<<v2<<"\n";
		}	
	}
    cout << "�ڽӱ�ֵ���" << endl;
    clock_t startTime, endTime; 
	startTime = clock();
    long long a = DFS(node,1, 1, 0);
    endTime = clock();
    cout << "����ʱ��Ϊ" << (endTime - startTime)*1000 / CLOCKS_PER_SEC<<"ms\n";
    cout << "������:" << a << "\n";
    return 0;
}





































