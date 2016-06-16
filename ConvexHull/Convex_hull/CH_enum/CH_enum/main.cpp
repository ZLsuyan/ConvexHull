#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <ctime>
#include <stdlib.h>

#define MAX_NUM  2000

using namespace std;

struct  point{
    int x;
    int y;
    int flag;
};
struct point my_point[MAX_NUM+1]; /*定义凸包点的信息*/
struct point my_ch[MAX_NUM+1];
struct point my_ch_top[MAX_NUM+1];
struct point my_ch_down[MAX_NUM+1];

int Min(int a,int b)
{
    if(a<=b)
        return a;
    else
        return b;
}
int Max(int a, int b)
{
    if(a>=b)
        return a;
    else
        return b;
}

void  my_convex_hull()
{
    int i,j,k,sign;
    double a=0,b=0,c=0;
    for(i=0; i<MAX_NUM; ++i)
        for(j=i+1; j<MAX_NUM; ++j)
        {
             a = my_point[j].y - my_point[i].y;
             b = my_point[i].x - my_point[j].x;
             c = ( my_point[i].x * my_point[j].y )-( my_point[i].y * my_point[j].x );
             sign=0;
             for(k=0; k<MAX_NUM; ++k)
             {
                 if( (k==j)||(k==i) )
                     continue;
                 if( ( (a*(my_point[k].x)+b*(my_point[k].y))>c ) )
                     ++sign;
                 if( ( (a*(my_point[k].x)+b*(my_point[k].y))<c ) )
                     --sign;
              }
              if( (sign==(MAX_NUM-2))||((sign==(2-MAX_NUM))) )
              {
                   my_point[i].flag=1;
                   my_point[j].flag=1;
              }
         }
}



/*交换函数，作用是交换数组中的两个元素的位置*/
void swap(struct point pts[],int i,int j)
{
    point tmp=pts[i];
    pts[i]=pts[j];
    pts[j]=tmp;
}

/*选择排序*/
void SelectionSort(struct point pts[],int n)
{
    for(int i=0;i<n-1;i++)
    {
        int smallest=i;
        for(int j=i+1;j<n;j++)
        {
            if(pts[smallest].x>pts[j].x)
                smallest=j;
        }
        swap(pts,i,smallest);
    }
}
/*****************************主函数******************************/
int main()
{
    int j=0, k=0, n=0;
    double a=0,b=0,c=0;
    point max_x, min_x;
    srand((unsigned)time(0));
    time_t   c_start,c_end;
    /*初始化随机数*/
    for(int i=0;i<MAX_NUM;i++)
    {
      my_point[i].x = (rand() % 101);
      my_point[i].y = (rand() % 101);
      my_point[i].flag=0;
    }

    for(int i=0;i<MAX_NUM;i++)
        cout<<"("<<my_point[i].x<<","<<my_point[i].y<<")"<<endl;
    cout<<endl;
    c_start=clock();
    my_convex_hull();/*调用凸包计算函数*/
    c_end=clock();
    /*for(int i=0;i<MAX_NUM;i++){
        if(my_point[i].flag==1)
            cout<<"("<<my_point[i].x<<","<<my_point[i].y<<")"<<endl;
    }
    cout<<endl;*/
    for(int i=0;i<MAX_NUM;i++){
        if(my_point[i].flag==1){
            my_ch[j].x=my_point[i].x;
            my_ch[j].y=my_point[i].y;
            my_ch[j].flag=my_point[i].flag;
            j++;
        }
    }
    SelectionSort(my_ch,j);
    max_x=my_ch[j-1];
    min_x=my_ch[0];
    a = max_x.y - min_x.y;
    b = min_x.x - max_x.x;
    c = ( min_x.x * max_x.y )-( min_x.y * max_x.x );
    my_ch_down[0]=my_ch[0];
    k++;
    for(int i=1;i<j-1;i++){
        if(a*my_ch[i].x+b*my_ch[i].y>c){
            my_ch_down[k]=my_ch[i];
            k++;
        }else if(a*my_ch[i].x+b*my_ch[i].y<c){
            my_ch_top[n]=my_ch[i];
            n++;
        }
    }
    my_ch_down[k]=my_ch[j-1];
    k++;
    for(int i=0;i<k;i++)
        cout<<"("<<my_ch_down[i].x<<","<<my_ch_down[i].y<<")"<<endl;
    for(int i=n-1;i>=0;i--)
        cout<<"("<<my_ch_top[i].x<<","<<my_ch_top[i].y<<")"<<endl;

    cout<<endl;
    cout<<"The running time is "<<difftime(c_end,c_start)<<"ms."<<endl;
    system("pause");
    return 0;
}


