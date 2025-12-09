// Aso tarda la vida en compilar-se y ejecutarse, literalment tarda 2 min y 50 segons
//  Problema traduit de Python a C++

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <climits>

using namespace std;

struct Punto
{
    int x, y;

    Punto(int x = 0, int y = 0) : x(x), y(y) {}
    bool operator==(const Punto &otro) const
    {
        return x == otro.x && y == otro.y;
    }
};

struct PuntoHash // Tabla Hash pero de punts
{
    int operator()(const Punto &p) const
    {
        return hash<int>()(p.x) ^ (hash<int>()(p.y) << 1);
    }
};

int area(const Punto &a, const Punto &b) // Calcules el area entre dos punts
{
    return (abs(a.x - b.x) + 1) * (abs(a.y - b.y) + 1);
}

int main()
{
    vector<Punto> lines;
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
        int x, y;
        char coma;
        Punto p;
        ss >> p.x >> coma >> p.y;
        lines.push_back(p);
    }
    file.close();

    unordered_set<Punto, PuntoHash> bordes; // Asi fas els bordes per a saber com sera la figura i el perimetro
    Punto ultimo = lines[0];

    for (int i = 0; i <= lines.size(); i++)
    {
        Punto a;
        if (i < lines.size())
        {
            a = lines[i];
        }
        else
        {
            a = lines[0];
        }

        if (a.y == ultimo.y)
        {
            int iniX = min(a.x, ultimo.x);
            int finX = max(a.x, ultimo.x);
            for (int x = iniX; x <= finX; x++)
            {
                bordes.insert(Punto(x, a.y));
            }
        }
        else if (a.x == ultimo.x)
        {
            int iniY = min(a.y, ultimo.y);
            int finY = max(a.y, ultimo.y);
            for (int y = iniY; y <= finY; y++)
            {
                bordes.insert(Punto(a.x, y));
            }
        }
        ultimo = a;
    }

    unordered_map<int, vector<pair<Punto, Punto>>> vertices;
    vector<int> dist;

    for (int i = 0; i < lines.size(); i++)
    {
        for (int j = i + 1; j < lines.size(); j++)
        {
            int d = area(lines[i], lines[j]);
            dist.push_back(d);
            vertices[d].push_back({lines[i], lines[j]});
        }
    }

    // Ordenar áreas de mayor a menor
    sort(dist.begin(), dist.end(), greater<int>());

    // Encontrar el mínimo x global
    int gminX = INT_MAX;
    for (const auto &p : lines)
    {
        gminX = min(gminX, p.x);
    }

    // Buscar el rectángulo válido más grande
    for (int d : dist)
    {
        for (const auto &pair : vertices[d])
        {
            Punto a = pair.first;
            Punto b = pair.second;

            int maxX = max(a.x, b.x);
            int minX = min(a.x, b.x);
            int maxY = max(a.y, b.y);
            int minY = min(a.y, b.y);

            bool contiene = false;

            // Verificar filas interiores
            for (int y = minY + 1; y < maxY; y++)
            {
                if (bordes.find(Punto(maxX - 1, y)) != bordes.end() ||
                    bordes.find(Punto(minX + 1, y)) != bordes.end())
                {
                    contiene = true;
                    break;
                }
            }

            if (!contiene)
            {
                // Verificar columnas interiores
                for (int x = minX + 1; x < maxX; x++)
                {
                    if (bordes.find(Punto(x, maxY - 1)) != bordes.end() ||
                        bordes.find(Punto(x, minY + 1)) != bordes.end())
                    {
                        contiene = true;
                        break;
                    }
                }
            }

            if (!contiene)
            {
                // Ray casting desde fuera hasta el interior del rectángulo
                Punto p(gminX - 1, minY + 1);
                bool out = true;

                while (!(p.x == minX + 1 && p.y == minY + 1))
                {
                    p.x += 1;
                    if (bordes.find(p) != bordes.end())
                    {
                        out = !out;
                    }
                }

                if (!out)
                {
                    cout << d << endl;
                    return 0;
                }
            }
        }
    }

    return 0;
}