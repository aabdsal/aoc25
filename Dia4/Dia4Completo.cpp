// Como para la parte 2 se necesita hacer la parte 1, aqui estan implementadas ambas partes con Grafos, aunque para la primera parte no es necesario ni siquiera usar grafos
// Y casi que ni eficiente, ya que seria como un "overkill" usar grafos para la priemra parte.

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <fstream>

using namespace std;

class Posicion // Como coordenada en la matriz
{
private:
    int fila;    // Aso seria com la "x"
    int columna; // Aso seria com la "y"

public:
    Posicion(int f = 0, int c = 0) : fila(f), columna(c) {}

    int getFila() const { return fila; }
    int getColumna() const { return columna; }

    bool operator==(const Posicion &otra) const
    {
        return fila == (otra.fila) && (columna == otra.columna);
    }

    bool operator<(const Posicion &otra) const // Para usar map en lugar de unordered_map
    {
        if (fila != otra.fila)
            return fila < otra.fila;
        return columna < otra.columna;
    }

    void mostrar() const // Ho vaig fer per a enterarme de algo quan feia el debug, per a vore on tenia els errors
    {
        cout << "(" << fila << "," << columna << ")";
    }
};

class Nodo // Asi comença lo bo, clase Nodo de la que estara compost el grafo
{
private:
    Posicion posicion;
    int grado; // Cantidad de vecinos activos (no eliminados)
    bool eliminado;
    vector<Posicion> vecinos; // Almacenamos posiciones en lugar de punteros

public:
    // Constructor
    Nodo(const Posicion &pos) : posicion(pos), grado(0), eliminado(false) {}

    // Getters
    Posicion getPosicion() const { return posicion; }
    int getGrado() const { return grado; }
    bool estaEliminado() const { return eliminado; }

    // Setters
    void setGrado(int g) { grado = g; }

    void agregarVecino(const Posicion &vecino) // Como unir los nodos (agregar un vecino) y se le aumenta el grado
    {
        vecinos.push_back(vecino);
        grado++;
    }

    void setEliminado(bool e) { eliminado = e; }

    void reducirGrado() // Asi es reduix el grau
    {
        if (!eliminado)
        {
            grado--;
        }
    }

    const vector<Posicion> &getVecinos() const
    {
        return vecinos;
    }

    bool esAccesible() const // Comprovar si es accesible (grau < 4 i no eliminat)
    {
        return !eliminado && grado < 4;
    }

    void mostrar() const // Mostrar info del nodo per a poder deuguear i vore on comença tot a anar malament
    {
        posicion.mostrar();
        cout << " [Grado: " << grado << ", Eliminado: " << (eliminado ? "Sí" : "No") << "]";
    }
};

class GrafoRollos // I asi ja comencen els Grafos complets
{
private:
    map<Posicion, Nodo> nodos;
    int filas;
    int columnas;

public:
    GrafoRollos(int f = 0, int c = 0) : filas(f), columnas(c) {}

    void setDimensiones(int f, int c)
    {
        filas = f;
        columnas = c;
    }

    void agregarNodo(const Posicion &pos)
    {
        if (nodos.find(pos) == nodos.end())
        {
            nodos.insert({pos, Nodo(pos)});
        }
    }

    Nodo *obtenerNodo(const Posicion &pos)
    {
        auto it = nodos.find(pos);
        return (it != nodos.end()) ? &(it->second) : nullptr;
    }

    const map<Posicion, Nodo> &getNodos() const
    {
        return nodos;
    }

    void construirDesdeMatriz(const vector<string> &matriz)
    {
        filas = matriz.size();
        columnas = matriz[0].size();

        // Primera pasada: crear todos los nodos
        for (int i = 0; i < filas; i++)
        {
            for (int j = 0; j < columnas; j++)
            {
                if (matriz[i][j] == '@')
                {
                    Posicion pos(i, j);
                    agregarNodo(pos);
                }
            }
        }

        for (int i = 0; i < filas; i++)
        {
            for (int j = 0; j < columnas; j++)
            {
                if (matriz[i][j] == '@')
                {
                    Posicion posActual(i, j);
                    Nodo *nodoActual = obtenerNodo(posActual);

                    for (int di = -1; di <= 1; di++) // Mirem a les 8 posicions veïnes
                    {
                        for (int dj = -1; dj <= 1; dj++)
                        {
                            if (di == 0 && dj == 0)
                                continue;
                            // Evitar duplicados: solo procesar cuando (di,dj) > (0,0) lexicográficamente
                            if (di < 0 || (di == 0 && dj < 0))
                                continue;

                            int ni = i + di;
                            int nj = j + dj;

                            if (ni >= 0 && ni < filas && nj >= 0 && nj < columnas)
                            {
                                if (matriz[ni][nj] == '@')
                                {
                                    Posicion posVecino(ni, nj);
                                    Nodo *nodoVecino = obtenerNodo(posVecino);

                                    // Conectar ambos nodos (grafo no dirigido)
                                    nodoActual->agregarVecino(posVecino);
                                    nodoVecino->agregarVecino(posActual);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    int contarAccesiblesIniciales() const
    {
        int contador = 0;
        for (const auto &par : nodos)
        {
            if (par.second.esAccesible())
            {
                contador++;
            }
        }
        return contador;
    }

    int eliminarEnCascada()
    {
        int totalEliminados = 0;
        queue<Posicion> cola;

        for (const auto &par : nodos)
        {
            if (par.second.esAccesible())
            {
                cola.push(par.first);
            }
        }

        while (!cola.empty())
        {
            Posicion posActual = cola.front();
            cola.pop();

            Nodo *nodoActual = obtenerNodo(posActual);

            if (nodoActual->estaEliminado() || !nodoActual->esAccesible())
            {
                continue;
            }

            nodoActual->setEliminado(true);
            totalEliminados++;

            // Reducir grado de vecinos
            for (const Posicion &posVecino : nodoActual->getVecinos())
            {
                Nodo *vecino = obtenerNodo(posVecino);
                if (!vecino->estaEliminado())
                {
                    vecino->reducirGrado();
                    if (vecino->esAccesible())
                    {
                        cola.push(posVecino);
                    }
                }
            }
        }

        return totalEliminados;
    }

    void mostrarEstado() const
    {
        cout << "=== ESTADO DEL GRAFO ===\n";
        cout << "Nodos totales: " << nodos.size() << "\n";

        int activos = 0, eliminados = 0, accesibles = 0;
        for (const auto &par : nodos)
        {
            if (par.second.estaEliminado())
            {
                eliminados++;
            }
            else
            {
                activos++;
                if (par.second.esAccesible())
                {
                    accesibles++;
                }
            }
        }

        cout << "Nodos activos: " << activos << "\n";
        cout << "Nodos eliminados: " << eliminados << "\n";
        cout << "Nodos accesibles: " << accesibles << "\n";

        cout << "\nDetalle de nodos:\n";
        for (const auto &par : nodos)
        {
            cout << "  ";
            par.second.mostrar();
            cout << "\n";
        }
        cout << "======================\n";
    }
};

int main(void)
{
    ifstream archivo("input.txt");
    if (!archivo.is_open())
    {
        cerr << "Error: No se pudo abrir el archivo input.txt\n";
        return 1;
    }

    vector<string> matriz;
    string linea;

    while (getline(archivo, linea))
    {
        matriz.push_back(linea);
    }
    archivo.close();

    GrafoRollos grafo;
    grafo.construirDesdeMatriz(matriz);

    int parte1 = grafo.contarAccesiblesIniciales();
    cout << "Parte 1: " << parte1 << endl;

    GrafoRollos grafoParaParte2;
    grafoParaParte2.construirDesdeMatriz(matriz);

    int parte2 = grafoParaParte2.eliminarEnCascada();
    cout << "Parte 2: " << parte2 << endl;

    return 0;
}
