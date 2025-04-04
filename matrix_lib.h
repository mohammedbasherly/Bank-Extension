#pragma once

#include <iostream>
#include <iomanip>
#include <cmath>
#include "global_funcs.h"
using namespace std;
using namespace global_funcs;

namespace matrix_lib {

    void fill3x3MatrixRandomly(int matrix[3][3], short rows, short cols)
    {
        for (short i = 0; i < 3; i++)
        {
            for (short j = 0; j < 3; j++)
            {
                matrix[i][j] = getRandomNumber(1, 100);
            }
        }
    }

    void fill3x3MatrixRandomly(int matrix[3][3], short rows, short cols, int minNumber, int maxNumber)
    {
        for (short i = 0; i < 3; i++)
        {
            for (short j = 0; j < 3; j++)
            {
                matrix[i][j] = getRandomNumber(minNumber, maxNumber);
            }
        }
    }

    void print3x3Matrix(int matrix[3][3], short rows, short cols)
    {
        for (short i = 0; i < 3; i++)
        {
            for (short j = 0; j < 3; j++)
            {
                cout << matrix[i][j] << "\t";
            }
            cout << endl;
        }
    }

    void print3x3Matrix(int matrix[3][3], short rows, short cols, short width)
    {
        for (short i = 0; i < 3; i++)
        {
            for (short j = 0; j < 3; j++)
            {
                printf("%0*d", width, matrix[i][j]);
                cout << '\t';
            }
            cout << endl;
        }
    }

    int sumOfCol(int matrix[3][3], short rows, short colIndex)
    {
        int sum = 0;

        for (short row = 0; row < rows; row++)
        {
            sum += matrix[row][colIndex];
        }

        return sum;
    }

    void printEachColSum(int matrix[3][3], short rows, short cols)
    {
        for (short i = 0; i < rows; i++)
        {
            cout << "Col " << i + 1 << ": " << sumOfCol(matrix, rows, i) << endl;
        }
    }

    void fillArrayWithMatrixEachColSum(int arrayOfColsSum[], int matrix[3][3], short rows, short cols)
    {
        for (short i = 0; i < rows; i++)
        {
            arrayOfColsSum[i] = sumOfCol(matrix, rows, i);
        }
    }

    int sumOfRow(int matrix[3][3], short rowIndex, short cols)
    {
        int sum = 0;
        for (short i = 0; i < cols; i++)
        {
            sum = sum + matrix[rowIndex][i];
        }
        return sum;
    }

    void printEachRowSum(int matrix[3][3], short rows, short cols)
    {
        for (short i = 0; i < rows; i++)
        {
            cout << "Row " << i + 1 << " sum = " << sumOfRow(matrix, i, cols) << endl;
        }
    }

    void fillArrayOfMatrixEachRowSum(int rowsSumArr[], int matrix[3][3], short rows, short cols)
    {
        for (short i = 0; i < rows; i++)
        {
            rowsSumArr[i] = sumOfRow(matrix, i, cols);
        }
    }

    void fill3x3MatrixWithOrderedNumbers(int matrix[3][3], short rows, short cols)
    {
        short cellNumber = 1;
        for (short i = 0; i < rows; i++)
        {
            for (short j = 0; j < cols; j++)
            {
                matrix[i][j] = cellNumber;
                cellNumber++; 
            }
        }
    }

    void read3x3Matrix(int matrix[3][3], short rows, short cols)
    {
        short cellNumber = 1;
        for (short i = 0; i < rows; i++)
        {
            for (short j = 0; j < cols; j++)
            {
                cout << "number " << cellNumber << ": ";
                matrix[i][j] = readIntNumber();
                cellNumber++; 
            }
        }
    }

    void transpose3x3Matrix(int matrix[3][3], short rows, short cols)
    {
        int tempMatrix[3][3];

        for (short col = 0; col < cols; col++)
        {
            for (short row = 0; row < rows; row++)
            {
                tempMatrix[row][col] = matrix[col][row];
            }
        }

        for (short row = 0; row < rows; row++)
        {
            for (short col = 0; col < cols; col++)
            {
                matrix[row][col] = tempMatrix[row][col];  
            }
        }
    }

    void transpose3x3Matrix(int transposeMatrix[3][3], int matrix[3][3], short rows, short cols)
    {
        for (short col = 0; col < cols; col++)
        {
            for (short row = 0; row < rows; row++)
            {
                transposeMatrix[row][col] = matrix[col][row];
            }
        }
    }

    void multiplicationOf3x3Matrices(int matrixResult[3][3], int matrix1[3][3], int matrix2[3][3], short rows, short cols)
    {
        for (short row = 0; row < rows; row++)
        {
            for (short col = 0; col < cols; col++)
            {
                matrixResult[row][col] = matrix1[row][col] * matrix2[row][col];
            }
        }
    }

    void getMiddleRowOfMatrix(int middleRow[3], int matrix[3][3], short rows, short cols)
    {
        short middleRowIndex = rows / 2;
        for (short col = 0; col < cols; col++)
            middleRow[col] = matrix[middleRowIndex][col];
    }

    void getMiddleColOfMatrix(int middleCol[3], int matrix[3][3], short rows, short cols)
    {
        short middleColIndex = cols / 2;
        for (short row = 0; row < rows; row++)
            middleCol[row] = matrix[row][middleColIndex];
    }

    int sumOfMatrix(int matrix[3][3], short rows, short cols)
    {
        int sum = 0;
        for (short row = 0; row < rows; row++)
        {
            sum += sumOfRow(matrix, row, cols);
        }
        return sum;
    }

    void copy3x3Matrix(int destinationMatrix[3][3], int sourceMatrix[3][3], short rows, short cols)
    {
        for (short row = 0; row < rows; row++)
        {
            for (short col = 0; col < cols; col++)
            {
                destinationMatrix[row][col] = sourceMatrix[row][col];
            }
        }
    }

    bool areMatricesEqual(int matrix1[3][3], int matrix2[3][3], short rows, short cols)
    {
        return sumOfMatrix(matrix1, rows, cols) == sumOfMatrix(matrix2, rows, cols);
    }

    bool areMatricesTypical(int matrix1[3][3], int matrix2[3][3], short rows, short cols)
    {
        for (short row = 0; row < rows; row++)
        {
            for (short col = 0; col < cols; col++)
            {
                if (matrix1[row][col] != matrix2[row][col])
                    return false;
            }
        }
        return true;
    }

    void fillMatrixIdentity(int matrix[3][3], short rows, short cols)
    {
        for (short row = 0; row < rows; row++)
        {
            for (short col = 0; col < cols; col++)
            {
                if (row == col)
                    matrix[row][col] = 1;
                else
                    matrix[row][col] = 0;
            }
        }
    }

    bool isMatrixIdentity(int matrix[3][3], short rows, short cols)
    {
        for (short row = 0; row < rows; row++)
        {
            for (short col = 0; col < cols; col++)
            {
                if (row == col && matrix[row][col] != 1)
                    return false;
                else if (row != col && matrix[row][col] != 0)
                    return false;
            }
        }
        return true;
    }

    bool isMatrixScalar(int matrix[3][3], short rows, short cols)
    {
        int firstDiagonalElement = matrix[0][0];
        for (short row = 0; row < rows; row++)
        {
            for (short col = 0; col < cols; col++)
            {
                if (row == col && matrix[row][col] != firstDiagonalElement)
                    return false;
                else if (row != col && matrix[row][col] != 0)
                    return false;
            }
        }
        return true;
    }

    short countNumberInMatrix(int numberToCount, int matrix[3][3], short rows, short cols)
    {
        short count = 0;
        for (short row = 0; row < rows; row++)
        {
            for (short col = 0; col < cols; col++)
            {
                if (matrix[row][col] == numberToCount)
                    count++;
            }
        }
        return count;
    }

    bool isMatrixSparce(int matrix[3][3], short rows, short cols)
    {
        short maxsize = rows * cols;
        return countNumberInMatrix(0, matrix, rows, cols) >= ceil(maxsize / 2.0);
    }

    bool isNumberExistInMatrix(int numberToLookFor, int matrix[3][3], short rows, short cols)
    {
        for (short row = 0; row < rows; row++)
        {
            for (short col = 0; col < cols; col++)
            {
                if (matrix[row][col] == numberToLookFor)
                    return true;
            }
        }
        return false;
    }

    void printIntersectedNumbersIn2Matrices(int matrix1[3][3], int matrix2[3][3], short rows, short cols)
    {
        int number = 0;
        for (short row = 0; row < rows; row++)
        {
            for (short col = 0; col < cols; col++)
            {
                number = matrix1[row][col];
                if (isNumberExistInMatrix(matrix1[row][col], matrix2, rows, cols))
                    cout << number << " ";
            }
        }
        cout << endl;
    }

    void fillArrayWithIntersectedNumbersIn2Matrices(int arr[9], int matrix1[3][3], int matrix2[3][3], short rows, short cols)
    {
        short index = 0;
        int number = 0;
        for (short row = 0; row < rows; row++)
        {
            for (short col = 0; col < cols; col++)
            {
                number = matrix1[row][col];
                if (isNumberExistInMatrix(number, matrix2, rows, cols))
                    arr[index] = number;
            }
        }
    }

    int minNumberInMatrix(int matrix[3][3], short rows, short cols)
    {
        int min = matrix[0][0];
        for (short row = 0; row < rows; row++)
        {
            for (short col = 0; col < cols; col++)
            {
                if (matrix[row][col] < min)
                    min = matrix[row][col];
            }
        }
        return min;
    }

    int maxNumberInMatrix(int matrix[3][3], short rows, short cols)
    {
        int max = matrix[0][0];
        for (short row = 0; row < rows; row++)
        {
            for (short col = 0; col < cols; col++)
            {
                if (matrix[row][col] > max)
                    max = matrix[row][col];
            }
        }
        return max;
    }

    bool isMatrixPalindrome(int matrix[3][3], short rows, short cols)
    {
        for (short row = 0; row < rows; row++)
        {
            if (!global_funcs::isArrayPalindrom(matrix[row], cols))
                return false;
        }
        return true;
    }

}