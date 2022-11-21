#pragma once

//----------------------------------------------------------------------------------------
//	Copyright © 2007 - 2022 Tangible Software Solutions, Inc.
//	This class can be used by anyone provided that the copyright notice remains intact.
//
//	This class includes methods to convert multidimensional arrays to C++ vectors.
//----------------------------------------------------------------------------------------
#include <vector>

class RectangularVectors
{
public:
    static std::vector<std::vector<std::vector<std::string>>> RectangularStdWstringVector(int size1, int size2, int size3)
    {
        std::vector<std::vector<std::vector<std::string>>> newVector(size1);
        for (int vector1 = 0; vector1 < size1; vector1++)
        {
            newVector[vector1] = std::vector<std::vector<std::string>>(size2);
            if (size3 > -1)
            {
                for (int vector2 = 0; vector2 < size2; vector2++)
                {
                    newVector[vector1][vector2] = std::vector<std::string>(size3);
                }
            }
        }

        return newVector;
    }

    static std::vector<std::vector<int>> RectangularIntVector(int size1, int size2)
    {
        std::vector<std::vector<int>> newVector(size1);
        for (int vector1 = 0; vector1 < size1; vector1++)
        {
            newVector[vector1] = std::vector<int>(size2);
        }

        return newVector;
    }

    static std::vector<std::vector<wchar_t>> RectangularWchar_tVector(int size1, int size2)
    {
        std::vector<std::vector<wchar_t>> newVector(size1);
        for (int vector1 = 0; vector1 < size1; vector1++)
        {
            newVector[vector1] = std::vector<wchar_t>(size2);
        }

        return newVector;
    }

    static std::vector<std::vector<double>> RectangularDoubleVector(int size1, int size2)
    {
        std::vector<std::vector<double>> newVector(size1);
        for (int vector1 = 0; vector1 < size1; vector1++)
        {
            newVector[vector1] = std::vector<double>(size2);
        }

        return newVector;
    }
};
