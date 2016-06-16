#include <iostream>
#include <cmath>
//#include <cstdlib>
#include <ctime>
#include <vector>
#include <stdlib.h>

#define MAX_NUM  3000

using namespace std;

struct  Point{
    int x;
    int y;
};

vector<Point> pts;//输入的点集
vector<Point> ch;//凸包中的点

int getArea(Point p1, Point p2, Point p3) {
    return p1.x * p2.y + p3.x * p1.y + p2.x * p3.y -
             p3.x * p2.y - p2.x * p1.y - p1.x * p3.y;
}

/*交换函数，作用是交换数组中的两个元素的位置*/
void swap(vector<Point> pts,int i,int j)
{
    Point tmp=pts[i];
    pts[i]=pts[j];
    pts[j]=tmp;
}

/*选择排序*/
void SelectionSort(vector<Point> pts,int n)
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

void d(Point p1, Point p2, vector<Point> s){
    if (s.empty()) {
       ch.push_back(p1);
       //ch.push_back(p2);
       return;
     }
    int area = 0;
    int maxArea = 0;
    Point pMax;
    for (int i = 0; i < s.size(); i++) {
        area = getArea(p1, p2, s[i]);//最大面积对应的点就是Pmax
        if (area > maxArea) {
            pMax = s[i];
            maxArea = area;
        }
    }
    //找出位于(p1, pMax)直线左边的点集s1
    //找出位于(pMax, p2)直线左边的点集s2
    vector<Point> s1;
    vector<Point> s2;
    Point p3;
    for (int i = 0; i < s.size(); i++) {
        p3 = s[i];
        if (getArea(p1, pMax, p3) > 0) {
            s1.push_back(p3);
        } else if (getArea(pMax, p2, p3) > 0) {
            s2.push_back(p3);
        }
    }
       //递归
    d(p1, pMax, s1);
    d(pMax, p2, s2);
}

vector<Point> eval(){
    ch.clear();
    if(pts.empty())
        return ch;
    vector<Point> ptsLeft;//左凸包中的点
    vector<Point> ptsRight;//右凸包中的点
    //排序
    SelectionSort(pts, pts.size());

    Point p1 = pts.front();//最左边的点
    Point p2 = pts.back();//最右边的点,用直线p1p2将原凸包分成两个小凸包
    Point p3;
    int area = 0;
    for (int i = 1; i < pts.size(); i++) {//穷举所有的点,
        p3 = pts[i];
        area = getArea(p1, p2, p3);
        if (area > 0) {
            ptsLeft.push_back(p3);//p3属于左
        } else if (area < 0) {
            ptsRight.push_back(p3);//p3属于右
        }
    }
    d(p1, p2, ptsLeft);//分别求解
    d(p2, p1, ptsRight);
    return ch;
}

int main()
{
    srand((unsigned)time(0));
    time_t c_start,c_end;
    for(int i=0;i<MAX_NUM;i++)
    {
        Point ptIn = { rand() % 101, rand() % 101 };
        pts.push_back(ptIn);
        cout << "("<<pts[i].x << ", " << pts[i].y <<")"<< endl;
    }
    cout<<endl;
    c_start=clock();
    eval();
    c_end=clock();
    for(int i=0;i<ch.size();i++)
    {
        cout<<"("<<ch[i].x<<","<<ch[i].y<<")"<<endl;
    }
    cout<<endl;
    cout<<"The running time is "<<difftime(c_end, c_start)/1000<<"s."<<endl;
    system("pause");
    return 0;
}

