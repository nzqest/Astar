#include"Astar.h"
#include<Windows.h>
#include<iostream>

using namespace std;
//�����ͼ���� 
int map[13][13] = {
//��ά�������ڴ�˳��洢�� 
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

	//������ʼ��
	Point* star = AllocPiont(12, 4);
	Point* end = AllocPiont(0, 0);

	//A*�㷨Ѱ��·��
	list<Point*>path = Getpath(star, end);

	cout << "Ѱ·���" << endl;

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