#include "Solution.h"

namespace Plater
{
    Solution::Solution(float plateWidth_, float plateHeight_, float plateDiameter_, int plateMode_, float precision_, Bitmap *baseBmp_)
        : plateWidth(plateWidth_), plateHeight(plateHeight_), plateDiameter(plateDiameter_), plateMode(plateMode_), precision(precision_), baseBmp(baseBmp_)
    {
    }

    Solution::~Solution()
    {
        for (auto plate : plates) {
            delete plate;
        }
    }

    Plate *Solution::getPlate(int index)
    {
        if (((unsigned int)index) < plates.size()) {
            return plates[index];
        } else {
            return NULL;
        }
    }

    Plate *Solution::lastPlate()
    {
        return plates[plates.size()-1];
    }

    void Solution::addPlate()
    {
        plates.push_back(new Plate(plateWidth, plateHeight, plateDiameter, plateMode, precision, baseBmp));
    }

    int Solution::countPlates()
    {
        return plates.size();
    }

    float Solution::score()
    {
        return countPlates() + (1-1/(float)(1+lastPlate()->countParts()));
    }
}
