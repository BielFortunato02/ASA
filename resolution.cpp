#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int MAXN = 50; // Máximo tamanho da matriz
int T[MAXN][MAXN];
int seq[MAXN];
string dp[MAXN][MAXN][MAXN]; // DP para armazenar parentetizações

string solve(int n, int m, int target) {
    // Inicializar DP
    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= m; ++j) {
            for (int t = 0; t <= n; ++t) {
                dp[i][j][t] = ""; // Inicializa todas as strings como vazias
            }
        }
    }

    // Caso base: subcadeias de tamanho 1
    for (int i = 1; i <= m; ++i) {
        for (int t = 1; t <= n; ++t) {
            dp[i][i][t] = (seq[i] == t) ? to_string(seq[i]) : "";
        }
    }

    // Preencher DP para subcadeias maiores
    for (int len = 2; len <= m; ++len) { // Comprimento da subcadeia
        for (int i = 1; i + len - 1 <= m; ++i) { // Índice inicial da subcadeia
            int j = i + len - 1; // Índice final da subcadeia
            for (int t = 1; t <= n; ++t) { // Valor alvo
                for (int k = i; k < j; ++k) { // Divisão da subcadeia
                    for (int left = 1; left <= n; ++left) {
                        for (int right = 1; right <= n; ++right) {
                            if (T[left][right] == t && !dp[i][k][left].empty() && !dp[k + 1][j][right].empty()) {
                                string current = "(" + dp[i][k][left] + " " + dp[k + 1][j][right] + ")";
                                if (dp[i][j][t].empty() || current < dp[i][j][t]) {
                                    dp[i][j][t] = current;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return dp[1][m][target];
}

int main() {
    int n, m;
    cin >> n >> m;

    // Ler tabela T
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> T[i][j];
        }
    }

    // Ler sequência de entrada
    for (int i = 1; i <= m; ++i) {
        cin >> seq[i];
    }

    // Ler valor desejado
    int result;
    cin >> result;

    // Resolver o problema
    string solution = solve(n, m, result);

    // Output do resultado
    if (solution.empty()) {
        cout << "0\n";
    } else {
        cout << "1\n" << solution << endl;
    }

    return 0;
}