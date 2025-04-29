/*
Resolução de sistemas lineares pelo método de Gauss-Seidel
Entrada:
- ordem da matriz (máximo 10) dos coeficientes das incógnitas
- Sistema linear
- Precisão
- Solução inicial
Saída
- Resultados de cada passo (sistema e erro) com 7 casas decimais
- Solução
- Tempo de execução 
*/

#include <iostream>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <sstream>

using namespace std;
using namespace std::chrono;

class Gauss_Seidel{
    double **matriz;
    double *solution;
    unsigned order;
    double precision;

    // Obtem o maior elemento da solucao em modulo
    double absBiggerSolution(){
        double value = 0;
        for(unsigned i = 0; i < order; ++i)
            if(fabs(solution[i]) > value)
                value = fabs(solution[i]);
        return value;
    }
public:
    // Construtor da classe
    Gauss_Seidel(unsigned _order = 0) : order(_order), precision(0.0)
    {
        matriz = new double*[order];
        for(unsigned i = 0; i < order; ++i)
            matriz[i] = new double[order + 1];

        solution = new double[order];

        for(unsigned i = 0; i < order; ++i)
            solution[i] = 0;
    }

    // Destrutor da classe
    ~Gauss_Seidel(){
        for(unsigned i = 0; i < order; ++i)
            delete[] matriz[i];
        delete[] matriz;

        delete[] solution;
    }

    unsigned& getOrder(){
        return order;
    }

    // Retorna o vetor solucao da matriz
    double* getSolution(){
        return solution;
    }

    // Coloca a solucao
    void setSolution(double value, unsigned index){
        solution[index] = value; 
    }

    // Organiza a matriz da forma correta para o metodo
    bool swapLines(){
        bool flag = false;
        for(unsigned i = 0; i < order; ++i){
            for(unsigned j = 0; j < order; ++j)
                if(j != i){
                    if(matriz[j][i] > matriz[i][i]){
                        swap(matriz[i], matriz[j]);
                        flag = true;
                    }
                }
        }
        return flag;
    }

    // Verifica a convergencia
    bool convergence(){
        bool flag = true;
        double a = 0, b = 0;

        for(unsigned i = 0; i < order; ++i){
            b = fabs(matriz[i][i]);
            for(unsigned j = 0; j < order; ++j){
                if(j != i)
                    a += fabs(matriz[i][j]);
            }

            cout << a << "/" << b;

            if(a / b >= 1){
                cout << ">= 1";
                flag = false;
                break;
            } else
                cout << " < 1";
            cout << endl;

            a = 0;
        }

        return flag;
    }

    // Calcula o erro da solucao atual
    double calcSeidel(){
        double *prevSolution = new double[order];
        double distance = 0, distanceAux = 0;

        copy(solution, solution + order, prevSolution);

        for(unsigned i = 0; i < order; ++i){
            solution[i] = 0;
            for(unsigned j = 0; j < order + 1; ++j){
                if(j != i)
                    if(j < order)
                        solution[i] += (1/matriz[i][i]) * (-matriz[i][j] * solution[j]); 
                    else
                        solution[i] += (1/matriz[i][i]) * matriz[i][j];
            }

            if(fabs(solution[i] - prevSolution[i]) > distance)
                distance = fabs(solution[i]) - fabs(prevSolution[i]);
        }    

        // Retorna o produto da maior distancia pelo maior valor em modulo da solucao
        return distance / absBiggerSolution();
    }

    // Operador de acesso ao indice
    double* operator[](int index){
        return matriz[index];
    }

    operator string(){
        ostringstream oss;

        for(unsigned i = 0; i < order; ++i){
            for(unsigned j = 0; j < order + 1; ++j){
                oss << matriz[i][j];
                oss << "  ";
            }
            oss << endl;
        }
        return oss.str();
    }
};

int main(){
    unsigned choice, order;
    double precision, error, value;
    double *solution;

    do{
        system("clear");
        // Leitura da ordem da matriz
        cout << "Informe a ordem do sistema: ";
        cin >> order;

        // Criacao do objeto
        Gauss_Seidel matriz(order);

        // Leitura do sistema linear
        cout << endl << "Informe os elementos do sistema linear:" << endl;

        for(unsigned i = 0; i < order; ++i){
            for(unsigned j = 0; j < order + 1; ++j){
                cout << "Elemento " << i + 1 << ", " << j + 1 << ": ";
                cin >> matriz[i][j];
            }
        }

        // Leitura da precisao
        cout << "Informe a precisao que deseja: ";
        cin >> precision;

        // Leitura da solucao inicial
        for(unsigned i = 0; i < order; ++i){
            cout << "Solucao X" << i + 1 << ": ";
            cin >> value;
            matriz.setSolution(value, i);
        }

        auto start = high_resolution_clock::now();

        // Faz as trocas de linhas caso necessario
        bool flag = matriz.swapLines();

        // Confirma se houve troca de linhas
        if(flag)
            cout << "Matriz apos as trocas de linha: " << endl << string(matriz) << endl;
        
        // Verifica a convergencia
        flag = matriz.convergence();

        // Confirme se ha convergencia ou nao
        if(flag)
            cout << "Convergencia garantida!" << endl;
        else
            cout << "Convergencia nao garantida!" << endl;
        cout << endl;

        do{
            error = matriz.calcSeidel();
            solution = matriz.getSolution();

            // Apresenta o erro obtido
            cout << "Erro: " << error;
            if(error >= precision)
                cout << " >= " << precision << endl;
            else
                cout << " < " << precision << endl;
            cout << endl;
            
            // Apresenta a solucao atual
            cout << "Solucao atual" << endl;
            for(unsigned i = 0; i < order; ++i)
                cout << "X" << i+1 << ": " << solution[i] << endl;
            cout << endl;
        }while(error >= precision);

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);

        cout << "Tempo de execução: " << duration.count() << " nanosegundos" << endl;

        getchar();
        getchar();

        cout << "Deseja continuar?" << endl <<"1- Sim" << endl << "0- Nao" << endl << "-->";
        cin >> choice;

    }while(choice != 0);

    return 0;
}

//3 10 2 1 7 1 5 1 -8 2 3 10 6 0.05 0.7 -1.6 0.6