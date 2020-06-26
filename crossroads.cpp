#include "crossroads.h"

Crossroad::Crossroad(int _roadWidth)
{
	roadWidth = _roadWidth;
}

void Crossroad::spawnCar(int way)
{
	Car* newCar = nullptr;
	int carType = rand() % 3;

	switch (way)
	{
	case 0: // up
	{
		if (carType == 0)
			newCar = new GasEngineCar(offset, roadWidth, CAR_WIDTH, CAR_HEIGHT, eDirection::UP, 100, 5);
		else if (carType == 1)
			newCar = new ElectroCar(offset, roadWidth, CAR_WIDTH, CAR_HEIGHT, eDirection::UP, 100, 5);
		else
			newCar = new HybridCar(offset, roadWidth, CAR_WIDTH, CAR_HEIGHT, eDirection::UP, 100, 5);

		up.push(newCar);
		break;
	}
	case 1:	// down
	{
		if (carType == 0)
			newCar = new GasEngineCar(-offset - CAR_WIDTH, -roadWidth - CAR_HEIGHT, CAR_WIDTH, CAR_HEIGHT, eDirection::DOWN, 100, 5);
		else if (carType == 1)
			newCar = new ElectroCar(-offset - CAR_WIDTH, -roadWidth - CAR_HEIGHT, CAR_WIDTH, CAR_HEIGHT, eDirection::DOWN, 100, 5);
		else
			newCar = new HybridCar(-offset - CAR_WIDTH, -roadWidth - CAR_HEIGHT, CAR_WIDTH, CAR_HEIGHT, eDirection::DOWN, 100, 5);

		down.push(newCar);
		break;
	}
	case 2:	// right
	{
		if (carType == 0)
			newCar = new GasEngineCar(-roadWidth - CAR_HEIGHT, offset, CAR_HEIGHT, CAR_WIDTH, eDirection::RIGHT, 100, 5);
		else if (carType == 1)
			newCar = new ElectroCar(-roadWidth - CAR_HEIGHT, offset, CAR_HEIGHT, CAR_WIDTH, eDirection::RIGHT, 100, 5);
		else
			newCar = new HybridCar(-roadWidth - CAR_HEIGHT, offset, CAR_HEIGHT, CAR_WIDTH, eDirection::RIGHT, 100, 5);

		right.push(newCar);
		break;
	}
	case 3:	// left
	{
		if (carType == 0)
			newCar = new GasEngineCar(roadWidth, -offset - CAR_WIDTH, CAR_HEIGHT, CAR_WIDTH, eDirection::LEFT, 100, 5);
		else if (carType == 1)
			newCar = new ElectroCar(roadWidth, -offset - CAR_WIDTH, CAR_HEIGHT, CAR_WIDTH, eDirection::LEFT, 100, 5);
		else
			newCar = new HybridCar(roadWidth, -offset - CAR_WIDTH, CAR_HEIGHT, CAR_WIDTH, eDirection::LEFT, 100, 5);

		left.push(newCar);
		break;
	}
	default:
		break;
	}

	newCar = nullptr;
}

void Crossroad::createCars()
{
	for (size_t i = 0; i < 10; i++)
	{
		spawnCar(rand() % 4);
	}
}

int Crossroad::load()
{
	return (int)!up.empty() + (int)!down.empty() + (int)!right.empty() + (int)!left.empty();
}

void Crossroad::deleteCar(queue<Car*>* way)
{
	delete way->front();
	way->front() = nullptr;
	way->pop();
}

void Crossroad::checkCrossroadLeave()
{
	if (!up.empty())
	{
		if (up.front()->model.coordinates.y + up.front()->model.sizes.height < -roadWidth)
			deleteCar(&up);
	}
	if (!down.empty())
	{
		if (down.front()->model.coordinates.y > roadWidth)
			deleteCar(&down);
	}
	if (!right.empty())
	{
		if (right.front()->model.coordinates.x > roadWidth)
			deleteCar(&right);
	}
	if (!left.empty())
	{
		if (left.front()->model.coordinates.x + left.front()->model.sizes.width < -roadWidth)
			deleteCar(&left);
	}
}

// упрощенная функция
/*void Crossroad::oneWayTraffic(queue<Car*>* leftWay, queue<Car*>* myWay, queue<Car*>* rightWay)
{
	// Если машина едущая слева не успела перегородить мне дорогу
	// и если справа нет помехи
	// я могу ехать
	if (!myWay->empty())
	{
		if (!leftWay->empty())
		{
			// Важное уточнение: первая проверка в это "if" будет работать корректно только в том случае, если
			// за единицу времени одна машина, преодолевает расстояние меньшее высоты или ширины соседнего автомобиля,
			// в зависимости от направления движения по вертикали или горизонтали соответсвенно.
			// Если за единицу времени авто успевает переместиться на большее расстояние чем высота или ширина авто,
			// то следует написать и спользовать функцию расчета преграды на пути  а не пересечения.

// иллюстрация
//
//	1)Исходное положение:			2) Пересеклись (скорость маленькая):			3) Перескочили (из-за большой скорости):
//
//	o-------+						o-------+													o----+										
//	|	B	|						| B o---|+													|	 |
//	+-------+						+---|---+|													|  A |
//										|  A |													|	 |
//		o----+							|	 |												    +----+
//		|	 |							+----+												o-------+
//		|  A |																				|	B	|
//		|	 |																				+-------+
//		+----+
//
			if (!myWay->front()->getFuturePosition().intersects(leftWay->front()->model) && rightWay->empty())
				myWay->front()->move();
		}
		else
		{
			if (rightWay->empty())
				myWay->front()->move();
		}
	}
}*/

// усложненная функция
void Crossroad::oneWayTraffic(queue<Car*>* leftWay, queue<Car*>* myWay, queue<Car*>* rightWay)
{
	// если очередь машин не пуста
	if (!myWay->empty())
	{
		// если слева есть машины
		if (!leftWay->empty())
		{
			// если машина слева мне не помешает
			if (!myWay->front()->getFuturePosition().intersects(leftWay->front()->model))
			{
				// если машины справа нету
				if (rightWay->empty())
					myWay->front()->move();
				else
				{	// если машина есть проверяем надо ли ее пропустить 
					if (myWay->front()->skipCarOnTheRight(rightWay->front()->model) == false)
					{
						myWay->front()->move();
					}
				}
			}
		}
		else
		{
			// если машины справа нету
			if (rightWay->empty())
				myWay->front()->move();
			else
			{	// если машина есть проверяем надо ли ее пропустить или мы ей пока не мешаем если проедем чуть вперед
				if (myWay->front()->skipCarOnTheRight(rightWay->front()->model) == false)
					myWay->front()->move();
			}
		}
	}
}

void Crossroad::specialOneWayTraffic(queue<Car*>* leftWay, queue<Car*>* myWay)
{
	if (!myWay->front()->getFuturePosition().intersects(leftWay->front()->model))
		myWay->front()->move();
}

queue<Car*>* Crossroad::getUpQueue()
{
	return &up;
}

queue<Car*>* Crossroad::getDownQueue()
{
	return &down;
}

queue<Car*>* Crossroad::getRightQueue()
{
	return &right;
}

queue<Car*>* Crossroad::getLeftQueue()
{
	return &left;
}

void Crossroad::traffic()
{
	checkCrossroadLeave();

	if (load() == 4) // deadlock
	{
		specialOneWayTraffic(&down, &right);
		oneWayTraffic(&left, &down, &right);
		oneWayTraffic(&up, &left, &down);
	}
	else
	{
		oneWayTraffic(&right, &up, &left);
		oneWayTraffic(&left, &down, &right);
		oneWayTraffic(&down, &right, &up);
		oneWayTraffic(&up, &left, &down);
	}
}

Crossroad::~Crossroad()
{
	while (!up.empty())
	{
		delete up.front();
		up.front() = nullptr;
		up.pop();
	}
	while (!down.empty())
	{
		delete down.front();
		down.front() = nullptr;
		down.pop();
	}
	while (!right.empty())
	{
		delete right.front();
		right.front() = nullptr;
		right.pop();
	}
	while (!left.empty())
	{
		delete left.front();
		left.front() = nullptr;
		left.pop();
	}
}
