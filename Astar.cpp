#include"Astar.h"
#include<math.h>
#include<iostream>
#include<vector>




static int* maze; //���Թ���Ӧ�Ķ�ά������һ����ָ���ʾ
static int cols;//��ά�����Ӧ����
static int lines;//��ά�����Ӧ����

static std::list<Point*>openlist;//�����б�
static std::list<Point*>closelist;//�ر��б�


static Point* findPath(Point* starPiont, Point* endPint);//��������㵽�յ�����·��
static Point* getLeastfront();//��openlist��ȡ��Сmin
std::vector<Point*>getSurroundPoint(const Point* point);//��ȡ��ǰ�ڵ���Χ�ɴ�ڵ�

static bool isCanreaserch(const Point* piont, const Point* target);//�ж���һ����ɷ�ɴ�����Ƿ������

static Point* isInlist(const std::list<Point*>& list, const Point* point);//�жϿ����б����Ƿ����ĳ����

static int calcG(Point* tmp_star, Point* point);//����Gֵ
static int calcH(Point* point, Point* end);//����Hֵ
static int calcF(Point* point);//����Fֵ
//����һ��ڵ�(����)
Point* AllocPiont(int x, int y) { 
	Point* tmp = new Point;

	memset(tmp, 0, sizeof(Point));//��ʼֵ����
	
	tmp->x = x;
	tmp->y = y;
	return tmp;

}




/*��ʼ��A*��ͼ*/
void InitAstar(int* _maze, int _lines, int _colums) {
	maze = _maze;
	lines = _lines;
	cols = _colums;

}

/*ͨ��A*�㷨Ѱ��·��*/
std::list<Point*>Getpath(Point* star, Point* end) {
	
	Point* result = findPath(star, end);

	std::list<Point*>path;

	//����·�������û���ҵ�·�������ؿ�����
	while (result) {
		path.push_front(result);
		result = result->parent;
	}
	return path;
}

/*��������㵽�յ�����·��*/
static Point* findPath(Point* starPiont, Point* endPint) {
	openlist.push_back(AllocPiont(starPiont->x, starPiont->y));//������ʼ��

	while (!openlist.empty()){
		//��һ���������б���ȡ��Сֵ
		Point* curPiont = getLeastfront();//
		
		//�ڶ������ѵ�ǰ�ڵ�ŵ��ر��б���ȥ
		openlist.remove(curPiont);
		closelist.push_back(curPiont);

		//�������ҵ���ǰ�ɴ�ڵ㣬������Fֵ
		std::vector<Point*>surroundiont = getSurroundPoint(curPiont);


		std::vector<Point*>::const_iterator iter;

		for (iter = surroundiont.begin(); iter != surroundiont.end(); iter++) {
			Point* target = *iter;
			//��ĳһ�����ӣ���������ڿ����б����뵽�����б����õ�ǰ����Ϊ���ڵ�
			Point* exist = isInlist(openlist, target);

			
			if (!exist) {
				target->parent = curPiont;
				target->G = calcG(curPiont, target);
				target->H = calcH(target, endPint);
				target->F = calcF(target);
				openlist.push_back(target);
			}
			else {
				int tmpG = calcG(curPiont, target);
				if (tmpG < target->G) {
					exist->parent = curPiont;
					exist->G = tmpG;
					exist->F = calcF(target);
				}
				delete target;
			
				}
			}//end for
		surroundiont.clear();

		//�ж��յ��Ƿ���open list����
		Point* resPiont = isInlist(openlist, endPint);
		if (resPiont) {
			return resPiont;
		}
		
	}
	return NULL;

}




//��openlist��ȡ��Сmin
static Point* getLeastfront() {
	if (!openlist.empty()) {
		Point* resPoint = openlist.front();

		std::list<Point*>::const_iterator itor= openlist.begin();
		
		for (itor; itor != openlist.end(); itor++) {
			
			
			if ((*itor)->F < resPoint->F) {
				resPoint = *itor;
				}
		
			}

		return resPoint;
	
	}

	return NULL;
}
//��ȡ��ǰ�ڵ���Χ�ɴ�ڵ�
std::vector<Point*>getSurroundPoint(const Point* point) {
	std::vector<Point*>surouundedpiont;

	//������Ƕ��ѭ���ж���9����

	for (int x = point->x - 1; x <= point->x + 1; x++) {
		for (int y = point->y - 1; y <= point->y + 1; y++) {
			Point* tmp = AllocPiont(x, y);
			if (isCanreaserch(point, tmp)) {
				surouundedpiont.push_back(tmp);

			}
			else {
			
				delete tmp;
				}
			}
		}
	return surouundedpiont;

}
//�ж���һ����ɷ�ɴ�����Ƿ�ɴ�

static bool isCanreaserch(const Point* piont, const Point* target) {
	if(target->x<0||target->x>(lines-1)
		||target->y<0||target->y>(cols-1)
		||maze[target->x*cols + target->y]==1
		||maze[target->x * cols + target->y ] == 2
		||(target->x==piont->x&&target->y==piont->y)
		|| isInlist(closelist, target)){
		return false;
	}

	if (abs(piont->x - target->x) + abs(piont->y - target->y) == 1) {
		return true;
	}
	else {
		return false;
	}


}

//�жϿ����б����Ƿ����ĳ����
static Point* isInlist(const std::list<Point*>& list, const Point* point) {

	//�ж�ĳ���ڵ��Ƿ����б��У����ﲻ�ܱȽ�ָ�룬��Ϊÿ���������¿��ٵĽڵ�
	std::list<Point*>::const_iterator itor = list.begin();
	for (itor; itor != list.end(); itor++) {

		if ((*itor)->x == point->x && (*itor)->y == point->y) {

			return *itor;
		}

		
	}
	return NULL;
}

static int calcG(Point * tmp_star, Point * point) {
	int extraG = (abs(point->x - tmp_star->x) + abs(point->y - tmp_star->y)) == 1 ? kConst1 : kConst2;
	
	int parentG = (point->parent == NULL ? NULL : point->parent->G);//����ǳ�ʼ���ڵ������Ϊ��
	return parentG + extraG;
	}
//����Hֵ
static int calcH(Point* point, Point* end) {
	return (int)sqrt((double)(end->x - point->x) * (double)(end->x - point->x) + (double)(end->y - point->y) * (double)(end->y - point->y))*kConst1;

}
//����Fֵ
static int calcF(Point* point) {


	return point->G + point->H;
}


/*������Դ��������������*/
void ClearAstarMaze() {
	maze = NULL;
	cols = 0;
	lines = 0;

	std::list<Point*>::iterator itor;

	for (itor = openlist.begin(); itor != openlist.end();) {
		delete *itor;//�ͷŷ�����ڴ�
		itor = openlist.erase(itor);//������Ԫ�ز���ָ����һ��Ԫ��

	}

	for (itor = closelist.begin(); itor != closelist.end();) { 
		delete *itor;
		itor = closelist.erase(itor);

	}

}