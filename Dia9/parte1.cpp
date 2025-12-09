#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

typedef long long ll;

struct Punto2D
{
    int x, y;
};

ll calcularAreaMaxima(const vector<Punto2D> &puntos)
{
    ll max_area = 0;
    int n = puntos.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            ll base = abs((puntos[i].x - puntos[j].x) + 1);
            ll altura = abs((puntos[i].y - puntos[j].y) + 1);
            ll area = base * altura;
            max_area = max(max_area, area);
        }
    }
    return max_area;
}

int main(void)
{
    vector<Punto2D> puntos;
    string line;

    ifstream file("input.txt");
    if (!file.is_open())
    {
        cerr << "Error al abrir el archivo." << endl;
        return 1;
    }

    while (getline(file, line))
    {
        istringstream ss(line);
        char coma;
        Punto2D p;
        ss >> p.x >> coma >> p.y;
        puntos.push_back(p);
    }
    file.close();

    ll max_area = 0;
    int n = puntos.size();
    
    max_area = calcularAreaMaxima(puntos);

    cout << max_area << endl;
    return 0;
}