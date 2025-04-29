#include <iostream>
#include <sstream>
#include <cmath>
#include <chrono>

using namespace std;
using namespace chrono;

class taylorSeries {
    long double x;
    unsigned numTerms;
    long double result;
    bool flag;

    long long int fact(unsigned number) const {
        long long int _result = 1;
        for(unsigned i = 2; i <= number; ++i)
            _result *= i;
        return _result;
    }

public:
    taylorSeries(long double _x = 0.0, unsigned _numTerms = 0, long double _result = 0.0, bool _flag = false) 
        : x(_x), numTerms(_numTerms), result(_result), flag(_flag) {}

    // Getter e setter para x
    long double& getX() {
        return x;
    }

    // Getter e setter para numTerms
    unsigned& getNumTerms() {
        return numTerms;
    }

    // Normaliza x para o intervalo [-pi/2, pi/2]
    void normalizeX() {
        if(x == 1.57079633){
            flag = true;
            return;
        }
        x = fmod(x, 2 * M_PI);
        if (x > M_PI) { 
            x -= 2 * M_PI;
        } else if (x < -M_PI) {
            x += 2 * M_PI;
        }
        if (x > M_PI / 2) {
            x = M_PI - x;
            flag = true; // Fora do intervalo de [-pi/2, pi/2]
            return;
        } else if (x < -M_PI / 2) {
            x = -M_PI - x;
            flag = true; // Fora do intervalo de [-pi/2, pi/2]
            return;
        }

        flag = false; // Está dentro do intervalo [-pi/2, pi/2]
    }

    // Calcula a serie de Taylor para o cosseno
    void calcSeries() {
        normalizeX();
        result = 1.0;
        int signal = -1;

        for(unsigned i = 1; i <= numTerms; ++i) {
            result += signal * (pow(x, (i * 2)) / fact(i * 2));
            signal *= -1;
        }

        if(flag)
            result *= -1; // Negativa o resultado pois esta fora do intervalo positivo do cosseno
    }

    // Obtem
    long double getResult() const {
        return result;
    }

    // Casting para string
    operator string() const {
        ostringstream oss;
        oss << "Pela série de Taylor -- Cos(" << x << "): " << result << endl;
        // Caso esteja fora do intervalo
        if(flag)
            oss << "O resultado mais próximo usando a função cos() da biblioteca cmath: " << -cos(x) << endl;
        else
            oss << "O resultado mais próximo usando a função cos() da biblioteca cmath: " << cos(x) << endl;
        return oss.str();
    }
};

// Procedimento que calcula o tempo de execucao do codigo
void executeCalculation(taylorSeries& calcCos, unsigned repetitions = 1000) {
    auto inicio = high_resolution_clock::now();
    for (unsigned i = 0; i < repetitions; ++i)
        calcCos.calcSeries();

    auto resultado = high_resolution_clock::now() - inicio;
    auto nanosecondsA = duration_cast<nanoseconds>(resultado).count();
    cout << "Tempo de execucao para " << repetitions << " repeticoes: " << nanosecondsA << " Nanosegundos" << endl;
    cout << "Tempo de execucao medio por repeticao: " << nanosecondsA / repetitions << " Nanosegundos" << endl;
}

int main(){
    taylorSeries calcCos;
    long double x;
    unsigned numTerms, choice = 1;

    while(choice != 0) {
        system("clear");
        cout << "-= Menu do Programa =-" << endl;
        cout << "1- Calcular com Graus" << endl;
        cout << "2- Calcular com Radianos" << endl;
        cout << "0- Sair" << endl;

        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Informe o valor em graus: ";
                cin >> x;
                if(static_cast<int>(x) % 90 == 0 && static_cast<int>(x / 90) % 2 != 0)
                    x = 1.57079633; // pi/2
                else
                    x *= (M_PI / 180.0); // Converter graus para radianos
                calcCos.getX() = x;
                cout << "Agora o número de termos: ";
                cin >> numTerms;
                calcCos.getNumTerms() = numTerms;
                calcCos.calcSeries();
                cout << string(calcCos);
                getchar();
                executeCalculation(calcCos);
                break;
            case 2:
                cout << "Informe o valor em radianos: ";
                cin >> x;
                calcCos.getX() = x; 
                cout << "Agora o número de termos: ";
                cin >> numTerms;
                calcCos.getNumTerms() = numTerms;
                calcCos.calcSeries();
                cout << string(calcCos);
                getchar();
                executeCalculation(calcCos);
                break;
            case 0:
                cout << "Saindo..." << endl;
                break;
            default:
                cout << "Opção inválida!" << endl;
                break;
        }
        getchar();
    }

    return 0;
}