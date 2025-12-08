// Calcularemos la distancia entre dos puntos en un espacio 3D, y la introduciremos junto con los puntos en una priority queue (min-heap).
// La distancia se calcula com la distancia euclidiana (straight-line distance) entre dos puntos en el espacio 3D.
// Miremos las mas distancias mas cortas, y las uniermos usando un DSU (Disjoint Set Union).
// Lo haremos con todas las distancias, y antes de unir dos puntos, comprobaremos algunas cosas:
// 1. Si los puntos ya estan unidos en el DSU, no hacemos nada.
// 2. Si no estan unidos, los unimos.
// Luego miraremos los 3 conjuntos mas grandes resultantes y los multiplicaremos, por ejemplo, si al final los se termina con 6 conjuntos de tamanos 10, 8, 6, 4, 2, 1
// cogeremos 10*8*6 = 480, lo mismo para 10, 10, 8, 8, 5, 4, 2 -> 10*10*8 = 800.

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>
#include <tuple>
#include <random>

using namespace std;
typedef long long ll;

random_device rd;  // Objeto para generar semillas aleatorias
mt19937 gen(rd()); // Generador de números aleatorios Mersenne Twister

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

    void unir(int a, int b) // Unir dos conjuntos. Funcio tipica en els DSU, clarament no la he inventada jo,  algoritme tret de internet.
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
        }
    }

    int size(int a) // Per a estalviarnos un for despres al contar els tamanys dels conjunts
    {
        return tamano[find(a)];
    }
};

void asc_quick_sort(vector<int> &vec)
{
    if (vec.size() <= 1)
        return;

    uniform_int_distribution<> dis(0, (int)vec.size() - 1); // índice válido
    int pivot = vec[dis(gen)];

    vector<int> izq, medio, der;
    for (int num : vec)
    {
        if (num > pivot)
            izq.push_back(num); // mayores primero
        else if (num == pivot)
            medio.push_back(num);
        else
            der.push_back(num); // menores después
    }

    asc_quick_sort(izq);
    asc_quick_sort(der);

    vec.clear();
    vec.insert(vec.end(), izq.begin(), izq.end());
    vec.insert(vec.end(), medio.begin(), medio.end());
    vec.insert(vec.end(), der.begin(), der.end());
}

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
    // Enserio, que me torne a donar mal el problema perque havia ficat que les tres coordenades eren "int" i no que la primera era "long long"
    // He estat a punt de enviaro tot a prendre pel cul.
    // Me torna a paser y no torne a fer una variable de tipo "int" en la vida, les fare totes long long.

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

    const int UNIONES = puntos.size(); // Perque diu que fatja 1000 unions (que es igual a la contitat de punts del input), si demanara 10 unions (com en el exemple) ho posaria asi.

    for (int i = 0; i < UNIONES; ++i)
    {
        for (int j = i + 1; j < UNIONES; ++j)
        {
            ll distancia = calcularDistancia(puntos[i], puntos[j]); // Per a no ficar tota la formula faig la funcio, si es que apart de funcional, bonico, soc increible.
            colaPrioridad.push(make_tuple(distancia, i, j));        // Funcio make_tuple treta de lo que ve siguent internet, com casi tot lo nou que fique vamos.
        }
    }
    DSU dsu(UNIONES); // A bones hores me enrrecorde jo de crear aso. Fas un objecte tipo DSU per a les unions

    for (int i = 0; i < UNIONES; i++) // Com a maxim farem n-1 unions
    {
        if (colaPrioridad.empty())
        {
            break; // Per si de cas
        }
        auto [distancia, u, v] = colaPrioridad.top(); // Descompresio/Desempaquetat (ho gastava en Python y no sabia que asi tambe estava, pero lo de la variable tipo "auto" me te ballant)
        colaPrioridad.pop();                          // Per a no repetir

        if (dsu.find(u) != dsu.find(v)) // Si els dos punts no estan ja units a un altre, els unim
        {
            dsu.unir(u, v); // Unim els dos punts
        }
    }
    vector<int> tamanyos; // Vector per a guardar els tamanys dels conjunts.

    for (int i = 0; i < UNIONES; ++i) // Arriba a ser redundant pero bueno, no se com milloraro per a soles iterar als pares.
    {
        if (dsu.find(i) == i)
        {
            tamanyos.push_back(dsu.size(i)); // Afegim el tamany del conjunt
        }
    }
    asc_quick_sort(tamanyos); // Ordenem de major a menor els tamanys (sort(tamanos.begin(), tamanos.end(), greater<int>());)
    ll resultado = 1;         // Variable per a guardar el resultat de la multiplicacion. ll per si acar que ya no me fie de res y menys dels int.

    for (int i = 0; i < 3; ++i)
    {
        resultado *= tamanyos[i]; // Ya ordenat, multiplica els 3 mes grans
    }
    cout << resultado << endl;
    return 0;
}