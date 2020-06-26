#include "carmodels.h"

RectangleCarModel::RectangleCarModel()
{
    coordinates.x = 0;
    coordinates.y = 0;
    sizes.width = 0;
    sizes.height = 0;
}

RectangleCarModel::RectangleCarModel(int x, int y, int width, int height)
{
    coordinates.x = x;
    coordinates.y = y;
    sizes.width = width;
    sizes.height = height;
}

bool RectangleCarModel::intersects(const RectangleCarModel& otherModel)
{
    if (coordinates.x > otherModel.coordinates.x + otherModel.sizes.width ||    // ������ ������ �������
        coordinates.x + sizes.width < otherModel.coordinates.x ||   // ������ ����� �������
        coordinates.y > otherModel.coordinates.y + otherModel.sizes.height ||   // ������ ���� �������
        coordinates.y + sizes.height < otherModel.coordinates.y)    // ������ ���� �������
    {
        return false;
    }
    else
    {
        return true;
    }

    /*return !(coordinates.y < otherModel.coordinates.y + otherModel.sizes.height ||
            coordinates.y + sizes.height > otherModel.coordinates.y ||
            coordinates.x + sizes.width < otherModel.coordinates.x ||
            coordinates.x > otherModel.coordinates.x + otherModel.sizes.width);*/
   // return ((coordinates.x >= otherModel.coordinates.x))
}