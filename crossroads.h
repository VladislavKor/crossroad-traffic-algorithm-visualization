#pragma once
#include "cars.h"
#include <queue>

using namespace std;

const int offset = 5; // ������ �� ������ �����������

/*
	Crossroad - ����� ��������� �������������� ����������� 4�� �����, � �������������� ���������, � ������� � ������ ��������� O(0,0),
	��� OX � OY ���������� ������ � ���� ������������. ������� A-D ���������� �������.
	����������� ��������:
		- UP: � -> D
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
	queue<Car*> up; // ������� ����� ����������� � -> D
	queue<Car*> down; // ������� ����� ����������� B -> C
	queue<Car*> right; // ������� ����� ����������� C -> A
	queue<Car*> left; // ������� ����� ����������� D -> B
	int roadWidth; // ������ ������ ��� ������� ������ �����������
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