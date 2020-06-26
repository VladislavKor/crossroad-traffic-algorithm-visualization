#pragma once

struct Coordinates
{
	int x;
	int y;
};

struct Sizes
{
	int width;
	int height;
};

/* Класс RectangleCarModel описывает модель машины ввиде прямоуголника

			 width
 		 o---+			width
 		 |   |		   o--------+
   height|   |  height |        |    o: (x,y)
 		 |   |         +--------+
 		 +---+

   coordinates - координаты верхнего левого угла модели на плоскости

   sizes - размеры модели по ширине и высоте

   intersects() - провереяет пересечение моделей на плоскости, в случае пересечения возвращает true
*/
class RectangleCarModel
{
public:
	Coordinates coordinates;
	Sizes sizes;

	RectangleCarModel();
	RectangleCarModel(int x, int y, int width, int height);
	bool intersects(const RectangleCarModel& otherModel);
};