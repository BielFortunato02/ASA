#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <limits.h>

int _n, _m, _res;
std::vector<std::vector<int>> _matrix;
std::vector<int> _sequence;

void parser() {
    int num;
    std::string line;

    std::getline(std::cin, line);
    std::istringstream iss(line);

    // set the values for _n and _m
    iss >> _n >> _m;

    // read the matrix
    for (int i = 0; i < _n; i++) {
        std::vector<int> _matrixLine;
        std::getline(std::cin, line);
        std::istringstream issMatrix(line);
        while (issMatrix >> num) {
            _matrixLine.push_back(num);
        }
        _matrix.push_back(_matrixLine);
    }

    // read the sequence
    std::getline(std::cin, line);
    std::istringstream issSequence(line);
    while (issSequence >> num) {
        _sequence.push_back(num);
    }

    // read the result
    std::getline(std::cin, line);
    std::istringstream issResult(line);
    issResult >> _res;
}

void rebuildParentization(int i, int j, const std::vector<std::vector<int>>& parent) {
    if (i == j) {
        std::cout << _sequence[i];
        return;
    }

    int k = parent[i][j];
    std::cout << "(";
    rebuildParentization(i, k, parent);
    std::cout << " ";
    rebuildParentization(k + 1, j, parent);
    std::cout << ")";
}

int parentization() {
    std::vector<std::vector<int>> dp(_m, std::vector<int>(_m, -1)); // DP table to store results
    std::vector<std::vector<int>> parent(_m, std::vector<int>(_m, -1)); // Parent table for reconstruction

    // Precompute the base cases for subsequences of length 1
    for (int i = 0; i < _m; i++) {
        dp[i][i] = _sequence[i];
    }

    // Start filling the DP table for subsequences of length >= 2
    for (int len = 2; len <= _m; len++) {
        for (int i = 0; i <= _m - len; i++) {
            int j = i + len - 1;
            int minResult = INT_MAX;
            int bestK = -1;
            
            // Try every possible split (k)
            for (int k = i; k < j; k++) {
                int result = _matrix[dp[i][k] - 1][dp[k + 1][j] - 1];
                if (result < minResult) {
                    minResult = result;
                    bestK = k;
                }
            }

            dp[i][j] = minResult;
            parent[i][j] = bestK;
        }
    }

    // If the result in dp[0][m-1] matches the desired result, reconstruct the parenthesis
    if (dp[0][_m - 1] == _res) {
        std::cout << 1 << std::endl;
        rebuildParentization(0, _m - 1, parent);
        std::cout << std::endl;
        return 1;
    }

    std::cout << 0 << std::endl;
    return 0;
}

int main() {
    parser();
    return parentization();
}