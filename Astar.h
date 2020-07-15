#pragma once
#include<list>




const int kConst1 = 10;//ֱ�ƶ�һ������
const int kConst2 = 14;//б�ƶ�һ������

typedef struct _Point {
	
	int x, y; //x����ᣬy��������
	int F, G, H;//F=G+H;
	struct _Point* parent;//parent������

}Point;


//����һ��ڵ�(����)
Point* AllocPiont(int x, int y);

/*��ʼ����ͼ*/
void InitAstar(int *_maze, int _lines,int _colums);

/*ͨ��A*�㷨Ѱ��·��*/
std::list<Point*>Getpath(Point* star, Point* end);

/*������Դ��������������*/
void ClearAstarMaze();

