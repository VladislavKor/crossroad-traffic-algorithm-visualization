#pragma once
#include "cars.h"
#include <queue>

using namespace std;

const int offset = 5; // отступ от центра перекрестка

/*
	Crossroad - класс описывает крестообразный перекресток 4ех дорог, с правосторонним движением, с центром в начале координат O(0,0),
	оси OX и OY направлены вправа и вниз сответсвенно. Буквами A-D обозначены сектора.
	Направления движения:
		- UP: А -> D
		- DOWN: B -> C
		- RIGHT: C -> A
		- LEFT: D -> B

									|
									|
			x--; y-- (B)			|			x++; y-- (D)
									|
									|					  				 X (1,0)
 -----------------------------------o------------------------------------>
			  				  (0,0) |					  
									|
			x--; y++ (C)			|			x++; y++ (A)
									|
									|
							        V
							 Y (0,1)

						|			|			|
						|			|			|
						|			| roadWidth |
						|			|			|
						|			|			|
						|			|			|
------------------------						------------------------
												o---------+  o(roadWidth, -offset - height)
										<-----	|		  |
												+---------+
------------------------			o			------------------------
								(0,0)
										  /\	
										   |
------------------------				   |	------------------------
						|			|	o----+	|
						|			|	|	 |	| o(offset, roadWidth)
						|			|	|	 |	|
						|			|	|	 |	|
						|			|	+____+	|
						|			|			|
									offset
*/

class Crossroad
{
	queue<Car*> up; // очередь машин двигующихся А -> D
	queue<Car*> down; // очередь машин двигующихся B -> C
	queue<Car*> right; // очередь машин двигующихся C -> A
	queue<Car*> left; // очередь машин двигующихся D -> B
	int roadWidth; // ширина дороги для расчета границ перекрестка
public:
	Crossroad(int _roadWidth);
	void spawnCar(int way);
	void createCars();
	int load();
	void deleteCar(queue<Car*>* way);
	void checkCrossroadLeave();
	void oneWayTraffic(queue<Car*>* leftWay, queue<Car*>* myWay, queue<Car*>* rightWay);
	void specialOneWayTraffic(queue<Car*>* leftWay, queue<Car*>* myWay);
	queue<Car*>* getUpQueue();
	queue<Car*>* getDownQueue();
	queue<Car*>* getRightQueue();
	queue<Car*>* getLeftQueue();
	void traffic();
	~Crossroad();
};