#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;
#define ull unsigned long long
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
    int getPos(string key){
        return hash(key);
    }
    // Gemini
    vector<vector<ull>> initMemo(){
        vector<vector<ull>> memo(max);
        for(int i = 0; i < max; i++){
            memo[i].resize(tabla[i].size(), -1);
        }
        return memo;
    }
};

ull contarCaminos(HashTable &h1, string desde, string hasta, vector<vector<ull>> &memo){
    if (desde == hasta) return 1;

    int pos = h1.getPos(desde);
    int i = h1.search(desde, pos);

    if (i == -1) return 0;

    if (memo[pos][i] != -1) return memo[pos][i];

    vector <string> vecinos = h1.getVecinos(desde);
    ull total = 0;
    
    for (int i = 0; i < vecinos.size(); i++){
        total += contarCaminos(h1, vecinos[i], hasta, memo);
    }
    
    memo[pos][i] = total;
    return total;
}

int main(int argc, char const *argv[])
{
    ifstream fich("input.txt");
    string l1;
    
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

    // Gemini
    vector<vector<ull>> memo1 = h1.initMemo();
    ull tramo1 = contarCaminos(h1, "svr", "dac", memo1);
    
    vector<vector<ull>> memo2 = h1.initMemo();
    ull tramo2 = contarCaminos(h1, "dac", "fft", memo2);
    
    vector<vector<ull>> memo3 = h1.initMemo();
    ull tramo3 = contarCaminos(h1, "fft", "out", memo3);
    
    ull ruta1 = tramo1 * tramo2 * tramo3;

    vector<vector<ull>> memo4 = h1.initMemo();
    ull tramo4 = contarCaminos(h1, "svr", "fft", memo4);
    
    vector<vector<ull>> memo5 = h1.initMemo();
    ull tramo5 = contarCaminos(h1, "fft", "dac", memo5);
    
    vector<vector<ull>> memo6 = h1.initMemo();
    ull tramo6 = contarCaminos(h1, "dac", "out", memo6);
    
    ull ruta2 = tramo4 * tramo5 * tramo6;

    cout << ruta1 + ruta2 << endl;
    fich.close();

    return 0;
}


