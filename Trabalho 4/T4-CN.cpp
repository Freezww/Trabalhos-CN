#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Funcao para calcular o valor do polinomio em x
double calcPolynomial(const vector<double>& coef, double x) {
    double result = 0.0;
    int degree = coef.size() - 1;
    for (int i = 0; i <= degree; ++i) {
        result += coef[i] * pow(x, i); // coef[i] * x^i
    }
    return result;
}

// Funcao principal para encontrar os intervalos com raizes
void findRoots(const vector<double>& coef, int a, int b) {
    auto begin = high_resolution_clock::now(); // Marcar inicio do tempo

    cout << fixed << setprecision(7); // Definir a precisao de 7 casas decimais

    // Dividir o intervalo inicial em subintervalos menores (opcionalmente, para mais precisao)
    double step = 1; // Subintervalo pequeno para refinar a busca

    for (double i = a; i < b; i += step) {
        double f_a = calcPolynomial(coef, i);
        double f_b = calcPolynomial(coef, i + step);

        // Verifica se f(a) * f(b) < 0, indicando uma raiz no intervalo
        if (f_a * f_b < 0) {
            cout << "Raiz encontrada no intervalo: [" << i << ", " << i + step << "]\n";
            cout << "f(" << i << ") = " << f_a << ", f(" << i + step << ") = " << f_b << endl << endl;
        }
    }

    auto end = high_resolution_clock::now(); // Marcar fim do tempo
    auto duration = duration_cast<milliseconds>(begin - end).count();
    cout << "Tempo de execucao: " << duration << " ms" << endl;
}

int main() {
    int n, a, b,
        choice = 0;

    do{
        // Entrada do grau do polinomio e intervalo inicial
        cout << "Digite o grau do polinomio: ";
        cin >> n;

        vector<double> coef(n + 1); // Coeficientes do polinomio

        cout << "Digite os coeficientes (c0, c1, ..., cn): ";
        for (int i = 0; i <= n; ++i) {
            cin >> coef[i];
        }

        cout << "Digite o intervalo [a, b]: ";
        cin >> a >> b;

        // Chamar a funcao para encontrar os intervalos com raizes
        findRoots(coef, a, b);

        // Escolha do usuario
        cout << "Deseja informar outro polinomio?\n1- Sim\n0- Nao\n-->";
        cin >> choice;
    } while(choice != 0);

    return 0;
}