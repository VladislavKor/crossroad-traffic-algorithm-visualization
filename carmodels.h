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

/* ����� RectangleCarModel ��������� ������ ������ ����� �������������

			 width
 		 o---+			width
 		 |   |		   o--------+
   height|   |  height |        |    o: (x,y)
 		 |   |         +--------+
 		 +---+

   coordinates - ���������� �������� ������ ���� ������ �� ���������

   sizes - ������� ������ �� ������ � ������

   intersects() - ���������� ����������� ������� �� ���������, � ������ ����������� ���������� true
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