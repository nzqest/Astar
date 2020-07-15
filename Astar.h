#pragma once
#include<list>




const int kConst1 = 10;//直移动一格消耗
const int kConst2 = 14;//斜移动一格消耗

typedef struct _Point {
	
	int x, y; //x代表横，y代表竖排
	int F, G, H;//F=G+H;
	struct _Point* parent;//parent的坐标

}Point;


//分配一格节点(格子)
Point* AllocPiont(int x, int y);

/*初始化地图*/
void InitAstar(int *_maze, int _lines,int _colums);

/*通过A*算法寻找路径*/
std::list<Point*>Getpath(Point* star, Point* end);

/*清理资源，结束后必须调用*/
void ClearAstarMaze();

