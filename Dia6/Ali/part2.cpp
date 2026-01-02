#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define ull unsigned long long

using namespace std;

class Node
{
public:
    Node *next;
    ull data1;
    ull data2;
    ull data3;
    ull data4;

    Node(ull data, int flag, Node *next = nullptr){
        this->data1 = 0;
        this->data2 = 0;
        this->data3 = 0;
        this->data4 = 0;
        
        switch (flag) {
        case 1:
            this->data1 = data;
            break;
        case 2:
            this->data2 = data;
            break;
        case 3:
            this->data3 = data;
            break;
        case 4:
            this->data4 = data;
            break;
        default:
            break;
        }
        this->next = nullptr;
    }
};

class Basura
{
private:
    Node *raiz;
public:
    Basura(Node *raiz = nullptr){
        this->raiz = raiz;
    }    
    ~Basura(){
		Node* aux = raiz;
		Node* nextNode;
		
		while(aux != nullptr){ 
			nextNode = aux->next;
			delete aux;
			aux = nextNode;
		}
    }
    void rellenar(ull &data, int flag, Node *&aux){
        if (aux == nullptr) {return;}
        
        if (flag == 2) {aux->data2 = data;}
        else if (flag == 3) {aux->data3 = data;}
        else if (flag == 4) {aux->data4 = data;}
        aux = aux->next;
    }
	void insert(ull data, int &flag) {
        if (raiz == nullptr) {
            Node* aux = new Node(data, flag, raiz); 
            raiz = aux; 
        }
        else {
            Node* aux = raiz; 
            Node* prev = nullptr;
            while (aux != nullptr)
            {
                prev = aux;
                aux = aux -> next;
            }
            prev->next = new Node(data, flag, nullptr); 
        }
	}
    void sumData(string operador, ull &count, Node* &aux){
        if (aux == nullptr) {return;}

        ull sumaData = 0;

        string unitats = to_string(aux->data1 % 10) + to_string(aux->data2 % 10) + to_string(aux->data3 % 10) + to_string(aux->data4 % 10);

        string decenes = "";
        decenes += (aux->data1 >= 10) ? to_string((aux->data1 / 10) % 10) : "";
        decenes += (aux->data2 >= 10) ? to_string((aux->data2 / 10) % 10) : "";
        decenes += (aux->data3 >= 10) ? to_string((aux->data3 / 10) % 10) : "";
        decenes += (aux->data4 >= 10) ? to_string((aux->data4 / 10) % 10) : "";

        string centenes = "";
        centenes += (aux->data1 >= 100) ? to_string((aux->data1 / 100) % 10) : "";
        centenes += (aux->data2 >= 100) ? to_string((aux->data2 / 100) % 10) : "";
        centenes += (aux->data3 >= 100) ? to_string((aux->data3 / 100) % 10) : "";
        centenes += (aux->data4 >= 100) ? to_string((aux->data4 / 100) % 10) : "";

        string milers = "";
        milers += (aux->data1 >= 1000) ? to_string((aux->data1 / 1000) % 10) : "";
        milers += (aux->data2 >= 1000) ? to_string((aux->data2 / 1000) % 10) : "";
        milers += (aux->data3 >= 1000) ? to_string((aux->data3 / 1000) % 10) : "";
        milers += (aux->data4 >= 1000) ? to_string((aux->data4 / 1000) % 10) : "";

        ull v1 = unitats.empty() ? 0 : stoull(unitats);
        ull v2 = decenes.empty() ? 0 : stoull(decenes);
        ull v3 = centenes.empty() ? 0 : stoull(centenes);
        ull v4 = milers.empty() ? 0 : stoull(milers);

        if (operador == "+") {
            sumaData = v1 + v2 + v3 + v4;
        }
        else if (operador == "*") {
            if (v2 == 0 && decenes.empty()) {v2 = 1;}
            if (v3 == 0 && centenes.empty()) {v3 = 1;}
            if (v4 == 0 && milers.empty()) {v4 = 1;}
            
            sumaData = v1 * v2 * v3 * v4;
        }

        count += sumaData;
        aux = aux->next;
    }

    Node* getRaiz(){
        return raiz;
    }
};

int main(int argc, char const *argv[])
{
    ifstream fich("input.txt"); 
    if (!fich.is_open()) {
        throw runtime_error("Error al abrir el archivo\n");
    }
    
    string l1;
    ull count = 0; int flag = 1;
    
    Basura *garbage = new Basura();

    while (getline(fich, l1))
    {
        istringstream ss (l1);
        string aux;
        Node *first = garbage->getRaiz();
        Node *paOperador = garbage->getRaiz();

        while(ss >> aux){ 
            if (flag == 1) { // data1
                ull data = stoull(aux);
                garbage->insert(data, flag);
            }
            else if(flag < 5) { // data2 3 i 4
                ull data = stoull(aux);
                garbage->rellenar(data, flag, first); 
            }
            else if(flag == 5){
                garbage->sumData(aux, count, paOperador);
            }
        }
        flag += 1;
    }

    delete garbage;
    cout << count << endl;
    fich.close();

    return 0;
}
