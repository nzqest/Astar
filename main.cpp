#include"Astar.h"
#include<Windows.h>
#include<iostream>

using namespace std;
//定义地图数组 
int map[13][13] = {
//二维数组在内存顺序存储的 
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, }, 
{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, }, 
{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, }, 
{ 0, 1, 0, 1, 0, 1, 2, 1, 0, 1, 0, 1, 0, }, 
{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, },
{ 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, },
{ 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, }, 
{ 2, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 2, }, 
{ 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, }, 
{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, }, 
{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, }, 
{ 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, }, 
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, } };

void AstarTest() {
	InitAstar(&map[0][0], 13, 13);

	//设置起始点
	Point* star = AllocPiont(12, 4);
	Point* end = AllocPiont(0, 0);

	//A*算法寻找路径
	list<Point*>path = Getpath(star, end);

	cout << "寻路结果" << endl;

	list<Point*>::const_iterator iter;
	for (iter = path.begin(); iter != path.end(); iter++) {
		Point* cur = *iter;
		cout << '(' << cur->x << ',' << cur->y << ')' << endl;
		Sleep(800);
	
		}
	ClearAstarMaze();
}

int main(void) {
	AstarTest();

	system("pause");
	return 0;

}