#include <iostream>
#include <vector>
#include <time.h>
#include <chrono>
#include <ctime>
#include <fstream>
#include "BigInt.hpp"
using std::fstream;
using std::vector;
using std::cout;

//makes a square matrix of sequential int values of side length n
//warning: previous matrix will be deleted!
void generateMatrix(vector<vector<int>>& matrix, int n) {
    matrix.clear();

    //generates n row matrices and pushes them to matrix
    vector<int> temp;
    for(int i = 0; i < n; i++) {
        temp.clear();
        for(int j = 0; j < n; j++) {
            temp.push_back(i * n + j + 1);
        }
        matrix.push_back(temp);
    }
}

double rotate1ClockTime(vector<vector<int>>& matrix) {

    auto start = std::chrono::system_clock::now();

    int temp = 0;
    
    //left and right
    int L = 0;
    int R = matrix.size() - 1;
    //matrix is square so top == left
    //and right == bottom
    int T = L;
    int B = R;
    
    /* schematic:
    *          dist
    *       <----->
    *       L             R
    *       * * * x ... * *  T  ^
    *                     *     |
    *                     *     | dist
    *    ^   x            x     v
    *    |   *          ....
    *dist|   *
    *    v   *...   x * * *  B
    *               <----->
    *                   dist
    *
    */
    
    //plan - rotate the four elements as depicted for each
    //square layer, going until one entire side worth of elements
    //is rotated, then moving inward
    
    while(R - L > 0) {
        
        for(int d = 0; d < R - L; d++) {
            temp = matrix[T][L + d];
            matrix[T][L + d] = matrix[B - d][L];
            matrix[B - d][L] = matrix[B][R - d];
            matrix[B][R - d] = matrix[T + d][R];
            matrix[T + d][R] = temp;
        }
        
        L += 1;
        R -= 1;
        T = L;
        B = R;
        
    }
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    return elapsed.count();
}

int rotate1NumOpers(vector<vector<int>>& matrix) {
    int temp = 0;
    
    //left and right
    int L = 0;
    int R = matrix.size() - 1;
    //matrix is square so top == left
    //and right == bottom
    int T = L;
    int B = R;
    
    int numAssigns = 5;

    /* schematic:
    *          dist
    *       <----->
    *       L             R
    *       * * * x ... * *  T  ^
    *                     *     |
    *                     *     | dist
    *    ^   x            x     v
    *    |   *          ....
    *dist|   *
    *    v   *...   x * * *  B
    *               <----->
    *                   dist
    *
    */
    
    //plan - rotate the four elements as depicted for each
    //square layer, going until one entire side worth of elements
    //is rotated, then moving inward
    
    while(R - L > 0) {
        
        for(int d = 0; d < R - L; d++) {
            temp = matrix[T][L + d];
            matrix[T][L + d] = matrix[B - d][L];
            matrix[B - d][L] = matrix[B][R - d];
            matrix[B][R - d] = matrix[T + d][R];
            matrix[T + d][R] = temp;
            numAssigns += 5;
        }
        
        L += 1;
        R -= 1;
        T = L;
        B = R;
        numAssigns += 4;
        
    }
    return numAssigns;
}

double rotate2ClockTime(vector<vector<int>>& matrix) {
    auto start = std::chrono::system_clock::now();
    
    int temp = 0;
    //indices top, left, bottom, right; assume square matrix
    int T = 0;
    int L = T;
    int B = matrix.size() - 1;
    int R = B;

    
    
    while(R - L > 0) {
        for(int i = 0; i < R - L; i++) {
            temp = matrix[T][L];   


            for(int i = 0; i < R - L; i++) {
                matrix[T + i][L] = matrix[T + i + 1][L];
            }
            for(int i = 0; i < R - L; i++) {
                matrix[B][L + i] = matrix[B][L + i + 1];
            }
            for(int i = 0; i < R - L; i++) {
                matrix[B - i][R] = matrix[B - i - 1][R];
            }
            for(int i = 0; i < R - L; i++) {
                matrix[T][R - i] = matrix[T][R - i - 1];
            }
            matrix[T][L + 1] = temp;
        }
        L += 1;
        T = L;
        R -= 1;
        B = R;
    }
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    return elapsed.count();
}

int rotate2NumOpers(vector<vector<int>>& matrix) {
    int temp = 0;
    //indices top, left, bottom, right; assume square matrix
    int T = 0;
    int L = T;
    int B = matrix.size() - 1;
    int R = B;

    int numAssigns = 5;

    while(R - L > 0) {
        for(int i = 0; i < R - L; i++) {
            temp = matrix[T][L];   
            numAssigns++;

            for(int i = 0; i < R - L; i++) {
                matrix[T + i][L] = matrix[T + i + 1][L];
                numAssigns++;
            }
            for(int i = 0; i < R - L; i++) {
                matrix[B][L + i] = matrix[B][L + i + 1];
                numAssigns++;
            }
            for(int i = 0; i < R - L; i++) {
                matrix[B - i][R] = matrix[B - i - 1][R];
                numAssigns++;
            }
            for(int i = 0; i < R - L; i++) {
                matrix[T][R - i] = matrix[T][R - i - 1];
                numAssigns++;
            }
            matrix[T][L + 1] = temp;
            numAssigns++;
        }
        L += 1;
        T = L;
        R -= 1;
        B = R;
        numAssigns += 4;
    }
    return numAssigns;
}

void printMatrix(vector<vector<int>> matrix) {
    int k = matrix.size();
    for(int i = 0; i < k; i++) {
        for(int j = 0; j < k; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << std::endl;
    }
}

int main() {

    fstream output;
    output.open("output.txt", std::ios::out);
    vector<vector<int>> matrix;

    int sizeMin = 20;
    int sizeMax = 600;
    int sizeStep = 20;

    

    for(int i = sizeMin; i <= sizeMax; i += sizeStep) {
        cout << i << std::endl;
        generateMatrix(matrix, i);
        output << i << "," << rotate1ClockTime(matrix) << "," << rotate1NumOpers(matrix)
            << "," << rotate2ClockTime(matrix) << "," << rotate2NumOpers(matrix) << std::endl;
    }


    output.close();
    return 0;
}