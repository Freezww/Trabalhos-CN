/*
    Cálculo de determinante pelo método de Gauss com pivotação parcial
    - Entrada:
      Ordem da matriz (Máximo 10)
      Matriz
    - Saída
      Resultados de cada passo com 1 casa decimal
      Determinante
      Tempo de execução 
*/

#include <iostream>
#include <cmath>
#include <sstream>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

class GaussWPivo{
    double **matriz;
    short unsigned order;
    int signal;

    // Primeiro parametro: Pivo
    // Segundo parametro: O alvo da linha
    double getM(double A, double B, unsigned i, unsigned j){
        // Calculo de M21: M21 = - A21 / A11 - Exemplo
        cout << "M" << i + 1 << "," << j + 1 << " = " << -B << "/" << A << endl;
        double M = -B / A;
        return M;
    }

    // Primeiro parametro: Pivo
    // Segundo parametro: O alvo da linha
    double getMWCout(double A, double B){
        // Calculo de M21: M21 = - A21 / A11 - Exemplo
        double M = -B / A;
        return M;
    }
public:
    // Construtor da classe
    GaussWPivo(unsigned _order = 0) : signal(1){
        order = _order;                     // Atribui a ordem da matriz
        matriz = new double*[order];         // Aloca as linhas da matriz
        for(short unsigned i = 0; i < order; ++i)
            matriz[i] = new double[order];   // Aloca as colunas da matriz
    }

    // Destrutor da classe
    // Falta implementar
    ~GaussWPivo(){
        for(short unsigned i = 0; i < order; ++i)
            delete[] matriz[i];
        delete [] matriz;
    }

    string matrizToString(){
        ostringstream oss;
        oss << fixed << setprecision(1);  // Define o número de casas decimais e a formatação fixa

        for(unsigned i = 0; i < order; ++i){
            for(unsigned j = 0; j < order; ++j){
                // Corrige valores como -0.0
                double value = matriz[i][j];
                if (abs(value) < 0.00005) {
                    value = 0.0;
                }
                oss << setw(7) << value;
            }
            oss << "\n";
        }

        return oss.str();
    }

    // Calcula o determinante de uma matriz utilizando o metodo de Gauss com pivotacao parcial
    double calcDetWithGauss(){
        system("clear");
        cout << "Matriz Inicial:" << endl << matrizToString() << endl;
        // Verifica se a matriz tem ordem maior que 1 para a execucao do metodo
        if(order > 1){
            // Metodo de Gauss linha a linha
            for(short unsigned i = 0; i < order - 1; ++i){
                // Verificacao do pivo
                int position;                   // Guarda a posicao do maior elemento da coluna
                double value = matriz[i][i];    // Utilizada para verificacoes
                bool flag = false;              // Sinaliza se deve haver troca ou nao de linhas
                for(short unsigned verify = i + 1; verify < order; ++verify){
                    if(fabs(matriz[verify][i]) > fabs(value)){
                        position = verify;
                        value = matriz[verify][i];
                        flag = true;
                    }
                }
                // Verifica se a flag sinaliza uma troca de linha
                if(flag){
                    swap(matriz[i], matriz[position]); // Faz a troca das linhas caso necessario
                    cout << endl << "Troca de linha: L" << i+1 << " com L" << position + 1 << ": " << endl;
                    cout << matrizToString() << endl;
                    signal *= -1;           // Serve para ver se havera troca de sinal ou nao no resultado do determinante
                }
                
                for(short unsigned j = i + 1; j < order; ++j){
                    double M = getM(matriz[i][i], matriz[j][i], j, i);
                    for(short unsigned k = 0; k < order; ++k)
                        matriz[j][k] = M * matriz[i][k] + matriz[j][k];
                }

                cout << endl << "Matriz apos modificacoes:" << endl << string(matrizToString()) << endl;
            }
        }
        double det = 1;
        cout << "Calculo da determinante:" << endl;
        for(short unsigned k = 0; k < order; ++k){
            cout << det << " * " << matriz[k][k] << endl;   
            det *= matriz[k][k];
        }
        
        cout << "Determinante:" << det << endl;
        det *= signal;
        if(signal == -1)
            cout << "Como houveram trocas de linhas" << endl << "Determinante: " << det << endl << endl;
        return det;
    }

    // Calcula o determinante de uma matriz utilizando o metodo de Gauss com pivotacao parcial
    // Obs: Nao contem saidas na tela. Utilizado para o calculo do tempo de execucao
    void calcDetWithGaussWCout(){
        // Verifica se a matriz tem ordem maior que 1 para a execucao do metodo
        if(order > 1){
            // Metodo de Gauss linha a linha
            for(short unsigned i = 0; i < order - 1; ++i){
                // Verificacao do pivo
                int position;                   // Guarda a posicao do maior elemento da coluna
                double value = matriz[i][i];    // Utilizada para verificacoes
                bool flag = false;              // Sinaliza se deve haver troca ou nao de linhas
                for(short unsigned verify = i + 1; verify < order; ++verify)
                    if(fabs(matriz[verify][i]) > fabs(value)){
                        position = verify;
                        value = matriz[verify][i];
                        flag = true;
                        signal *= -1;           // Serve para ver se havera troca de sinal ou nao no resultado do determinante
                    }
                // Verifica se a flag sinaliza uma troca de linha
                if(flag)
                    swap(matriz[i], matriz[position]); // Faz a troca das linhas caso necessario
                
                for(short unsigned j = i + 1; j < order; ++j){
                    double M = getMWCout(matriz[i][i], matriz[j][i]);
                    for(short unsigned k = 0; k < order; ++k)
                        matriz[j][k] = M * matriz[i][k] + matriz[j][k];
                }
            }
        }
        double det = 1;
        for(short unsigned k = 0; k < order; ++k)
            det *= matriz[k][k];
        
        det *= signal;
    }

    // Operador de acesso ao indice
    double* operator[](int index){
        return matriz[index];
    }
};

// Procedimento que calcula o tempo de execucao do codigo
void executeCalculation(GaussWPivo& calcDet, unsigned repetitions = 1000) {
    auto inicio = high_resolution_clock::now();
    for (unsigned i = 0; i < repetitions; ++i)
        calcDet.calcDetWithGaussWCout();

    auto resultado = high_resolution_clock::now() - inicio;
    auto nanosecondsA = duration_cast<nanoseconds>(resultado).count();
    cout << "Tempo de execucao para " << repetitions << " repeticoes: " << nanosecondsA << " Nanosegundos" << endl;
    cout << "Tempo de execucao medio por repeticao: " << nanosecondsA / repetitions << " Nanosegundos" << endl;
}

int main(){
    unsigned choice;
    unsigned order;

    do{
        cout << "Informe a ordem da matriz" << endl << "--> ";
        cin >> order;
        GaussWPivo calcDet(order);

        for(unsigned i = 0; i < order; ++i){
            for(unsigned j = 0; j < order; ++j){
                double value;
                cout << "Informe o elemento " << i + 1 << ", " << j + 1 << ":";
                cin >> value;
                calcDet[i][j] = value; 
            }
        }

        double det = calcDet.calcDetWithGauss();

        executeCalculation(calcDet);

        cout << "Deseja continuar?" << endl << "1- Sim" << endl << "0- Nao" << endl << "-->";
        cin >> choice;

    }while(choice != 0);

    return 0;
}