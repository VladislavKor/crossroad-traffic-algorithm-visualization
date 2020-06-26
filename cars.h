#pragma once
#include "carmodels.h"
#include "constants.h"
#include <cstdlib>

/*
	Car - виртуальный базовый класс, описывающий автомобиль
 
	model - представление автомобиля на плоскости ввиде прямоугольника
	
	speed - скорость автомобиля (преодалеваемое растояние по горизонтали и вертикали за 1 раз)
 
	direction - направление движения

	move() - функция изменения координат автомобиля на плоскости

	getFuturePosition() - функция расчета следующего положения автомобиля на плоскости
 
 */
class Car
{
public:
	RectangleCarModel model;
	int speed;
	eDirection direction;

	void move();
	RectangleCarModel getFuturePosition();
	bool skipCarOnTheRight(const RectangleCarModel& rightCarModel);
	virtual int getFuel() = 0;
	virtual void refill(int num) = 0;
	virtual ~Car() {};
};

/*
	GasEngineCar - класс наследник от Car, описывает логику функционирования авто с топлевным двигателем
*/
class GasEngineCar : public Car
{
	int fuel;
public:
	GasEngineCar(int x, int y, int width, int height, eDirection dir, int _fuel, int _speed);
	int getFuel();
	void refill(int count);
	void move();
	virtual ~GasEngineCar() {}
};

/*
	ElectroCar - класс наследник от Car, описывает логику функционирования авто с электрическим двигателем
*/
class ElectroCar : public Car
{
	int charge;
public:
	ElectroCar(int x, int y, int width, int height, eDirection dir, int _charge, int _speed);
	int getFuel();
	void refill(int count);
	void move();
	virtual ~ElectroCar() {}
};

/*
	HybridCar - класс наследник от Car, описывает логику функционирования авто с гибридным двигателем
*/
class HybridCar : public Car
{
	int fuel;
	int charge;
public:
	HybridCar(int x, int y, int width, int height, eDirection dir, int _fuel, int _speed);
	void refill(int count);
	int getFuel();
	void move();
	virtual ~HybridCar() {}
};