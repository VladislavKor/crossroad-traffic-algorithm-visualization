#pragma once
#include "carmodels.h"
#include "constants.h"
#include <cstdlib>

/*
	Car - ����������� ������� �����, ����������� ����������
 
	model - ������������� ���������� �� ��������� ����� ��������������
	
	speed - �������� ���������� (�������������� ��������� �� ����������� � ��������� �� 1 ���)
 
	direction - ����������� ��������

	move() - ������� ��������� ��������� ���������� �� ���������

	getFuturePosition() - ������� ������� ���������� ��������� ���������� �� ���������
 
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
	GasEngineCar - ����� ��������� �� Car, ��������� ������ ���������������� ���� � ��������� ����������
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
	ElectroCar - ����� ��������� �� Car, ��������� ������ ���������������� ���� � ������������� ����������
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
	HybridCar - ����� ��������� �� Car, ��������� ������ ���������������� ���� � ��������� ����������
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