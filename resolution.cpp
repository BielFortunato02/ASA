#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <climits>

using namespace std;

const int MAXN = 15; // Limite do tamanho de n

int T[MAXN][MAXN]; // Tabela da operação ⊕
set<int> dp[MAXN][MAXN]; // DP para armazenar resultados possíveis
string trace[MAXN][MAXN]; // Rastreamento para parentetização

// Função para calcular todas as combinações possíveis
void solve(vector<int> &seq, int result) {
    int m = seq.size();
    
    // Inicializar DP para subcadeias de tamanho 1
    for (int i = 0; i < m; i++) {
        dp[i][i].insert(seq[i]);
        trace[i][i] = to_string(seq[i]);
    }

    // Preencher DP para subcadeias maiores
    for (int len = 2; len <= m; len++) { // Tamanho da subcadeia
        for (int i = 0; i <= m - len; i++) {
            int j = i + len - 1;
            for (int k = i; k < j; k++) {
                for (int x : dp[i][k]) {
                    for (int y : dp[k+1][j]) {
                        int res = T[x][y]; // Operação entre x e y
                        dp[i][j].insert(res);
                        // Atualizar trace se encontrou o resultado desejado
                        if (trace[i][j].empty() || res == result) {
                            trace[i][j] = "(" + trace[i][k] + " " + trace[k+1][j] + ")";
                        }
                    }
                }
            }
        }
    }

    // Verificar resultado final
    if (dp[0][m-1].count(result)) {
        cout << "1\n" << trace[0][m-1] << endl;
    } else {
        cout << "0\n";
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    // Ler tabela T
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> T[i][j];
        }
    }

    // Ler sequência e resultado desejado
    vector<int> seq(m);
    for (int i = 0; i < m; i++) cin >> seq[i];
    int result;
    cin >> result;

    // Resolver o problema
    solve(seq, result);

    return 0;
}
