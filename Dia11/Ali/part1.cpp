#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

// He de crear una tabla hash que a la posicio aaa me duga a bbb i you
// Al final lo dificil del grafo es el algoritme de busqueda, pero la estrucutra es una hash table

class TableEntry
{
private:
    string key;
    vector<string> vecindario;
    bool visitado;
public:
	TableEntry(string key, string vecinos){
		this->key = key;
		this->vecindario.push_back(vecinos);
        this->visitado = false;
	}
    string getKey(){
        return this->key;
    }
    vector<string> getVecinos(){
        return this->vecindario;
    }
    bool getVisitado(){
        return this->visitado;
    }
    void setVisitado(bool visitado){
        this->visitado = visitado;
    }
    void addVecino(string vecino) { 
        vecindario.push_back(vecino); 
    }
};


class HashTable
{
private:
    int n, max;
    vector<vector<TableEntry>> tabla;
	int hash(string key){
		int res = 0;
		for(int i = 0; i < key.length(); i++){	
			res += key[i] - '0';
		}
		return res % max;
	}
public:
    HashTable(int size){
        tabla.resize(size);
        max = size;
        n = 0;
    }

	void insert(string key, string vecinos){
        int pos = hash(key);
        int i = search(key, pos);
		if(i != -1){
			tabla[pos][i].addVecino(vecinos);
		}else{
		    TableEntry aux = TableEntry(key, vecinos);
		    tabla[pos].push_back(aux);
		    n++;
        }
	}
	int search(string key, int pos){
        for (int i = 0; i < tabla[pos].size(); i++)
        {
            if (tabla[pos][i].getKey() == key) {return i;}
        }
        return -1;
	}
    vector<string> getVecinos(string key){
        int pos = hash(key);
        int i = search(key, pos);
        if(i != -1){
            return tabla[pos][i].getVecinos();
        }
        return {};
    }
    void marcarVisitado(string key, bool estado){
        int pos = hash(key);
        int i = search(key, pos);
        if(i != -1){
            tabla[pos][i].setVisitado(estado);
        }
    }
    bool esVisitado(string key){
        int pos = hash(key);
        int i = search(key, pos);
        if(i != -1){
            return tabla[pos][i].getVisitado();
        }
        return false;
    }	
};

int contarCaminos(HashTable &h1, string desde, string hasta){ // recursivitat es una pila
    if(desde == hasta) return 1;
    vector <string> vecinos = h1.getVecinos(desde);

    int total = 0;
    h1.marcarVisitado(desde, true);

    for (int i = 0; i < vecinos.size(); i++){
        if (!h1.esVisitado(vecinos[i])){
            total += contarCaminos(h1, vecinos[i], hasta);
        }
    }

    h1.marcarVisitado(desde, false);
    return total;
}

int main(int argc, char const *argv[])
{
    ifstream fich("input.txt");
    string l1;
    int count = 0;

    HashTable h1(559); // numero de linies del input
    while (getline(fich, l1))
    {
        int pos = l1.find(':');
        string key = l1.substr(0, pos);

        string vecino = l1.substr(pos + 1);
        stringstream ss (vecino);

        while(ss >> vecino){
            h1.insert(key, vecino);
        }
    }

    count = contarCaminos(h1, "you", "out");

    cout << count << endl;
    fich.close();

    return 0;
}


