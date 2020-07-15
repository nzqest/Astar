#include"Astar.h"
#include<math.h>
#include<iostream>
#include<vector>




static int* maze; //对迷宫对应的二维数组用一级别指针表示
static int cols;//二维数组对应的列
static int lines;//二维数组对应的行

static std::list<Point*>openlist;//开放列表
static std::list<Point*>closelist;//关闭列表


static Point* findPath(Point* starPiont, Point* endPint);//搜索从起点到终点的最佳路径
static Point* getLeastfront();//从openlist获取最小min
std::vector<Point*>getSurroundPoint(const Point* point);//获取当前节点周围可达节点

static bool isCanreaserch(const Point* piont, const Point* target);//判断下一个点可否可达个点是否可以走

static Point* isInlist(const std::list<Point*>& list, const Point* point);//判断开放列表中是否包含某个点

static int calcG(Point* tmp_star, Point* point);//计算G值
static int calcH(Point* point, Point* end);//计算H值
static int calcF(Point* point);//计算F值
//分配一格节点(格子)
Point* AllocPiont(int x, int y) { 
	Point* tmp = new Point;

	memset(tmp, 0, sizeof(Point));//初始值清零
	
	tmp->x = x;
	tmp->y = y;
	return tmp;

}




/*初始化A*地图*/
void InitAstar(int* _maze, int _lines, int _colums) {
	maze = _maze;
	lines = _lines;
	cols = _colums;

}

/*通过A*算法寻找路径*/
std::list<Point*>Getpath(Point* star, Point* end) {
	
	Point* result = findPath(star, end);

	std::list<Point*>path;

	//返回路径，如果没有找到路径，返回空链表
	while (result) {
		path.push_front(result);
		result = result->parent;
	}
	return path;
}

/*搜索从起点到终点的最佳路径*/
static Point* findPath(Point* starPiont, Point* endPint) {
	openlist.push_back(AllocPiont(starPiont->x, starPiont->y));//置入起始点

	while (!openlist.empty()){
		//第一步到开放列表中取最小值
		Point* curPiont = getLeastfront();//
		
		//第二步，把当前节点放到关闭列表中去
		openlist.remove(curPiont);
		closelist.push_back(curPiont);

		//第三步找到当前可达节点，并计算F值
		std::vector<Point*>surroundiont = getSurroundPoint(curPiont);


		std::vector<Point*>::const_iterator iter;

		for (iter = surroundiont.begin(); iter != surroundiont.end(); iter++) {
			Point* target = *iter;
			//对某一个格子，如果他不在开放列表，加入到开放列表，设置当前格子为父节点
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

		//判断终点是否在open list里面
		Point* resPiont = isInlist(openlist, endPint);
		if (resPiont) {
			return resPiont;
		}
		
	}
	return NULL;

}




//从openlist获取最小min
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
//获取当前节点周围可达节点
std::vector<Point*>getSurroundPoint(const Point* point) {
	std::vector<Point*>surouundedpiont;

	//这两个嵌套循环判断了9个点

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
//判断下一个点可否可达个点是否可达

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

//判断开放列表中是否包含某个点
static Point* isInlist(const std::list<Point*>& list, const Point* point) {

	//判断某个节点是否在列表中，这里不能比较指针，因为每次入列是新开辟的节点
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
	
	int parentG = (point->parent == NULL ? NULL : point->parent->G);//如果是初始化节点否则置为空
	return parentG + extraG;
	}
//计算H值
static int calcH(Point* point, Point* end) {
	return (int)sqrt((double)(end->x - point->x) * (double)(end->x - point->x) + (double)(end->y - point->y) * (double)(end->y - point->y))*kConst1;

}
//计算F值
static int calcF(Point* point) {


	return point->G + point->H;
}


/*清理资源，结束后必须调用*/
void ClearAstarMaze() {
	maze = NULL;
	cols = 0;
	lines = 0;

	std::list<Point*>::iterator itor;

	for (itor = openlist.begin(); itor != openlist.end();) {
		delete *itor;//释放分配的内存
		itor = openlist.erase(itor);//擦除该元素并且指向下一个元素

	}

	for (itor = closelist.begin(); itor != closelist.end();) { 
		delete *itor;
		itor = closelist.erase(itor);

	}

}