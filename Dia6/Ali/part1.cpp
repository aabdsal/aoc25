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
        
        switch (flag)
        {
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
            prev->next = new Node(data, flag, aux); 
        }
	}
    void sumData(string operador, ull &count, Node* &aux){
        if (aux == nullptr) {return;}

        ull sumaData;

        if (operador == "+") {sumaData = aux->data1 + aux->data2 + aux->data3 + aux->data4;}
        else if (operador == "*") {sumaData = aux->data1 * aux->data2 * aux->data3 * aux->data4;}

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
    ull count = 0;
    int flag = 1;

    Basura *garbage = new Basura();
    while (getline(fich, l1))
    {
        istringstream ss (l1);
        string aux;
        Node *first = garbage->getRaiz();
        Node *pa_operador = garbage->getRaiz();

        while(ss >> aux){ // segons gpt aso ignora espais en blanc, prou util
            if (flag == 1) {
                ull data = stoull(aux);
                garbage->insert(data, flag);
            }
            else if(flag < 5) {
                ull data = stoull(aux);
                garbage->rellenar(data, flag, first); // tinc q trobar la forma de diferenciar entre els seguents numeros
            }
            else {
                garbage->sumData(aux, count, pa_operador);
            }
        }
        flag += 1;
    }

    delete garbage;
    cout << count << endl;
    fich.close();

    return 0;
}
