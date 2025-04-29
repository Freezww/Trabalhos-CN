#include <iostream>
#include <cmath>
#include <chrono>  // Para calcular o tempo de execucao

using namespace std;

class calcRaiz{
private:
    double currentSolution, p, m, error;
    int iterations;
public:
    // Construtor padrao da classe
    calcRaiz() : currentSolution(1.0), p(0.0), m(0.0), error(0.0), iterations(0) {}

    // Set p
    void setP(double _p){
        p = _p;
    }

    // Set m
    void setM(double _m){
        m = _m;
    }

    // Set error
    void setError(double _error){
        error = _error;
    }

    // Set iterations
    void setIterations(int _iterations){
        iterations = _iterations;
    }

    // Funcao que faz as iteracoes desejadas
    void NewtonRaphson(int choice){
        int count = 0;

        switch(choice){
            // Iteracoes
            case 1:
                currentSolution = 1;

                while(count < iterations){
                    // Formula de Newton Raphson para calculo de raiz
                    currentSolution = (1/m) * ((m - 1) * currentSolution + p / pow(currentSolution, m - 1));

                    // Impressao dos resultados
                    printf("X%d: %lf\n\n", count, currentSolution);

                    count++;
                }

                break;

            // Erro
            case 2:
                double lastSolution, currentError;

                currentSolution = 1;

                // Criterio de parada: atual menos a anterior tem que ser menor ou igual ao erro
                do{
                    lastSolution = currentSolution;

                    // Formula de Newton Raphson para calculo de raiz
                    currentSolution = ((1/m) * (((m - 1) * currentSolution) + (p / pow(currentSolution, m - 1))));

                    // Calculo do erro
                    currentError = currentSolution - lastSolution;
                    currentError = fabs(currentError);

                    // Impressao dos resultados
                    printf("X%d: %lf\nErro atual: %lf\n\n", count, currentSolution, currentError);

                    count++;
                }while(currentError > error);

                break;

            default:
                break;
        }
    }
};

int main(){ 
    calcRaiz TCalc;
    int menuChoice = 0, choiceCalc = 0;

    do{
        double aux;
        int auxInt;

        // Leitura de P
        cout << "Informe P:";
        cin >> aux;
        TCalc.setP(aux);

        // Leitura de M
        cout << "Informe M:";
        cin >> aux;
        TCalc.setM(aux);

        do{
            // Leitura de qual sera o criterio de parada
            cout << "Deseja colocar o criterio de parada por erro ou iteracoes?" << endl;
            cout << "1 - Iteracoes" << endl << "2 - Erro" << endl << "-->";
            cin >> choiceCalc;

            // Validacao da escolha
            if(choiceCalc != 1 && choiceCalc != 2)
                cout << "Opcao invalida!" << endl;

        }while(choiceCalc != 1 && choiceCalc != 2);

        switch(choiceCalc){
            case 1:
                cout << "Informe a quantidade de iteracoes que deseja:" << endl;
                cin >> auxInt;
                TCalc.setIterations(auxInt);
                break;

            case 2:
                cout << "Informe o erro que deseja:" << endl;
                cin >> aux;
                TCalc.setError(aux);
                break;

            default:
                break;
        }
        
        // Inicio da medicao de tempo
        auto start = chrono::high_resolution_clock::now();

        TCalc.NewtonRaphson(choiceCalc);  // Calculo da raiz

        // Fim da medicao de tempo
        auto end = chrono::high_resolution_clock::now();

        // Calculo da duracao
        chrono::duration<double> duration = end - start;
        cout << "Tempo de execucao: " << duration.count() << " segundos" << endl;

        cout << "Deseja fazer uma nova raiz?" << endl << "0 - Sair" << endl << "1 - Nova raiz" << endl;
        cin >> menuChoice;

    }while(menuChoice != 0);

    return 0;
}