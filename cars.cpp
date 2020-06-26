#include "cars.h"

void Car::move()
{
	switch (direction) {
	case eDirection::UP:	// from down to up
		model.coordinates.y -= speed;
		break;
	case eDirection::DOWN:	// from up to down
		model.coordinates.y += speed;
		break;
	case eDirection::RIGHT:	// from left to right
		model.coordinates.x += speed;
		break;
	case eDirection::LEFT:	// from right to left
		model.coordinates.x -= speed;
		break;
	default:
		break;
	}
}

RectangleCarModel Car::getFuturePosition()
{
	if (direction == eDirection::UP)	// from down to up
		return RectangleCarModel(model.coordinates.x, model.coordinates.y - speed, model.sizes.width, model.sizes.height);
	else if (direction == eDirection::DOWN)	// from up to down
		return RectangleCarModel(model.coordinates.x, model.coordinates.y + speed, model.sizes.width, model.sizes.height);
	else if (direction == eDirection::RIGHT)	// from left to right
		return RectangleCarModel(model.coordinates.x + speed, model.coordinates.y, model.sizes.width, model.sizes.height);
	else	// from right to left
		return RectangleCarModel(model.coordinates.x - speed, model.coordinates.y, model.sizes.width, model.sizes.height);
}

bool Car::skipCarOnTheRight(const RectangleCarModel& rightCarModel)
{
	if (direction == eDirection::UP)
	{	
		// если помеха справа проехала часть перекрестка и больше не мешает нашему проезду
		if (model.coordinates.x > rightCarModel.coordinates.x + rightCarModel.sizes.width)
		{
			return false;
		}
		else // в противном случае
		{
			if (model.coordinates.y < rightCarModel.coordinates.y + rightCarModel.sizes.height)
			{
				return false;
			}
			else
			{
				if (getFuturePosition().coordinates.y > rightCarModel.coordinates.y + rightCarModel.sizes.height)
					return false;
				else
					return true;
			}
		}
	}
	else if (direction == eDirection::DOWN)
	{
		if (model.coordinates.x + model.sizes.width < rightCarModel.coordinates.x)
		{
			return false;
		}
		else
		{
			if (model.coordinates.y + getFuturePosition().sizes.height > rightCarModel.coordinates.y)
			{
				return false;
			}
			else
			{
				if (getFuturePosition().coordinates.y + getFuturePosition().sizes.height < rightCarModel.coordinates.y)
					return false;
				else
					return true;
			}
		}
	}
	else if (direction == eDirection::RIGHT)
	{
		if (model.coordinates.y > rightCarModel.coordinates.y + rightCarModel.sizes.height)
		{
			return false;
		}
		else
		{
			if (model.coordinates.x + getFuturePosition().sizes.width > rightCarModel.coordinates.x)
			{
				return false;
			}
			else
			{
				if (getFuturePosition().coordinates.x + getFuturePosition().sizes.width < rightCarModel.coordinates.x)
					return false;
				else
					return true;
			}
		}
	}
	else if (direction == eDirection::LEFT)
	{
		if (model.coordinates.y + model.sizes.height < rightCarModel.coordinates.y)
		{
			return false;
		}
		else
		{
			if (model.coordinates.x < rightCarModel.coordinates.x + rightCarModel.sizes.width)
			{
				return false;
			}
			else
			{
			if (getFuturePosition().coordinates.x > rightCarModel.coordinates.x +rightCarModel.sizes.width)
				return false;
			else
				return true;
			}
		}
	}
	else
	{
		return true;
	}
}



GasEngineCar::GasEngineCar(int x, int y, int width, int height, eDirection dir, int _fuel, int _speed)
{
	model.coordinates.x = x;
	model.coordinates.y = y;
	model.sizes.width = width;
	model.sizes.height = height;
	direction = dir;
	speed = _speed;
	fuel = _fuel;
}

int GasEngineCar::getFuel()
{
	return fuel;
}

void GasEngineCar::refill(int count)
{
	fuel += count;
}

void GasEngineCar::move()
{
	if (fuel > 0)
	{
		fuel--;
		Car::move();
	}
}

ElectroCar::ElectroCar(int x, int y, int width, int height, eDirection dir, int _charge, int _speed)
{
	model.coordinates.x = x;
	model.coordinates.y = y;
	model.sizes.width = width;
	model.sizes.height = height;
	direction = dir;
	speed = _speed;
	charge = _charge;
}

int ElectroCar::getFuel()
{
	return charge;
}

void ElectroCar::refill(int count)
{
	charge += count;
}

void ElectroCar::move()
{
	if (charge > 0)
	{
		charge--;
		Car::move();
	}
}

HybridCar::HybridCar(int x, int y, int width, int height, eDirection dir, int _fuel, int _speed)
{
	model.coordinates.x = x;
	model.coordinates.y = y;
	model.sizes.width = width;
	model.sizes.height = height;
	direction = dir;
	speed = _speed;
	charge = _fuel / 2;
	fuel = _fuel / 2;
}

void HybridCar::refill(int count)
{
	charge += count / 2; fuel += count / 2;
}

int HybridCar::getFuel()
{
	return fuel + charge;
}

void HybridCar::move()
{
	if (getFuel() > 0)
	{
		if (rand() % 2 == 0)
		{
			if (charge > 0)
				charge--;
			else
				fuel--;
		}
		else
		{
			if (fuel > 0)
				fuel--;
			else
				charge--;
		}
		Car::move();
	}
}
