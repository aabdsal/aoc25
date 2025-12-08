// Calcularemos la distancia entre dos puntos en un espacio 3D, y la introduciremos junto con los puntos en una priority queue (min-heap).
// La distancia se calcula com la distancia euclidiana (straight-line distance) entre dos puntos en el espacio 3D.
// Miremos las distancias mas cortas, y las uniremos usando un DSU (Disjoint Set Union).
// Iremos uniendo los puntos segun sus distancias hasta que solo queden 2 conjuntos separados.
// Cuando quedan solo 2 conjuntos, guardamos los indices de los dos ultimos puntos que no pudieron unirse.
// El resultado es la multiplicacion de la coordenada x de ambos puntos.
// ** Comentario generado por Copilot de acuerdo al codigo YA HECHO anteriormente **

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>
#include <tuple>

using namespace std;
typedef long long ll;

struct Puntos3D // Per a juntar les coordenades
{
    int x, y, z;
};

class DSU // Estructura base del DSU (Disjoint Set Union) treta de internet, ya sabia que existia y per a lo que servia, pero no sabia com implementar-la ni res.
{
private:
    vector<int> padre;
    vector<int> tamano;

public:
    DSU(int n) : padre(n), tamano(n, 1) // Constructor, al principi el propi numero es el seu propi pare
    {
        for (int i = 0; i < n; ++i)
        {
            padre[i] = i;
        }
    }

    int find(int a) // Trobar el representant del conjunt que conte a "a". Funcio tipica en els DSU, clarament no la he inventada jo, algoritme tret de internet.
    {
        if (padre[a] != a)
        {
            padre[a] = find(padre[a]);
        }
        return padre[a];
    }

    bool unir(int a, int b) // Unir dos conjuntos. Funcio tipica en els DSU, clarament no la he inventada jo,  algoritme tret de internet.
    {
        int raizA = find(a);
        int raizB = find(b);
        if (raizA != raizB)
        {
            // Unir por tamaño (el más pequeño al más grande)
            if (tamano[raizA] < tamano[raizB])
            {
                padre[raizA] = raizB;
                tamano[raizB] += tamano[raizA];
            }
            else
            {
                padre[raizB] = raizA;
                tamano[raizA] += tamano[raizB];
            }
            return true;
        }
        return false;
    }

    int size(int a) // Per a estalviarnos un for despres al contar els tamanys dels conjunts
    {
        return tamano[find(a)];
    }
};

ll calcularDistancia(const Puntos3D &a, const Puntos3D &b) // Calcular la distancia euclidiana que diu el problema
{
    ll dx = (ll)(a.x - b.x);
    ll dy = (ll)(a.y - b.y);
    ll dz = (ll)(a.z - b.z);
    return ((dx * dx) + (dy * dy) + (dz * dz));
}

int main(void)
{
    priority_queue<tuple<ll, int, int>, vector<tuple<ll, int, int>>, greater<tuple<ll, int, int>>> colaPrioridad; // Min-heap (al usar greater)

    string linea;
    ifstream archivo("input.txt");
    if (!archivo.is_open())
    {
        cerr << "No se pudo abrir el archivo." << endl;
        return 1;
    }
    vector<Puntos3D> puntos; // Vector de punts, per no guardar les cordenades per separat.

    while (getline(archivo, linea))
    {
        stringstream ss(linea); // Lo de sempre
        Puntos3D punto;
        char coma;
        if (ss >> punto.x >> coma >> punto.y >> coma >> punto.z) // Per a guardar els numeros y llevar les comes
        {
            puntos.push_back(punto);
        }
    }
    archivo.close();

    // En mayuscula perque aixina es posen les constants, encara que dona igual pero es una mania meua.
    const int UNIONES = puntos.size();

    for (int i = 0; i < UNIONES; ++i)
    {
        for (int j = i + 1; j < UNIONES; ++j)
        {
            ll distancia = calcularDistancia(puntos[i], puntos[j]); // Per a no ficar tota la formula faig la funcio, si es que apart de funcional, bonico, soc increible.
            colaPrioridad.push(make_tuple(distancia, i, j));        // Funcio make_tuple treta de lo que ve siguent internet, com casi tot lo nou que fique vamos.
        }
    }

    DSU dsu(UNIONES); // A bones hores me enrrecorde jo de crear aso. Fas un objecte tipo DSU per a les unions

    int conexiones = UNIONES; // Saber quan estan totes les uniones fetes
    int ultimo = 0;           // Asi se guardara la posicio del ultim
    int penultimo = 0;        // Y asi se guaradara la posicio del penultim

    while (conexiones > 1) // Mentres encara hi haja conexione per fer...
    {
        auto [distancia, u, v] = colaPrioridad.top(); // Lo mateix que antes, per a decomprimir una tupla en altres variables
        colaPrioridad.pop();                          // Per a no repetir

        if (conexiones == 2) // Quan soles queden dos per fer, les guardes
        {
            ultimo = u;    // Guardem
            penultimo = v; // Guardem
        }
        if (dsu.unir(u, v)) // Sols si conseguixes y pots unirles, se considera que l'es has unit.
        {
            --conexiones;
        }
    }

    ll resultado = ((ll)((((ll)puntos[ultimo].x) * ((ll)puntos[penultimo].x)))); // Una altra vegada no me donava be per el p*to ll y el (cast), ya esta, ni una variable mes tipo int

    cout << resultado << endl;
    return 0;
}