#include <iostream>
#include <fstream>
#include <string>

#define ull unsigned long long
#define fresh true
#define spoiled false

using namespace std;

class Node
{
public:
    Node *next;
    ull desde;
    ull hasta;
    Node(ull desde, ull hasta, Node *next = nullptr){
        this->desde = desde;
        this->hasta = hasta;
        this->next = next;
    }
    bool isFresh(ull num){
        return (hasta >= num  && num >= desde) ? fresh : spoiled;
    }
};

class Cafeteria
{
private:
    Node *raiz;
public:
    Cafeteria(Node *raiz = nullptr){
        this->raiz = raiz;
    }    
    ~Cafeteria(){
		Node* aux = raiz;
		Node* nextNode;
		
		while(aux != nullptr){ 
			nextNode = aux->next;
			delete aux;
			aux = nextNode;
		}
    }

    bool search(string data){
        Node *aux = raiz;
		ull num = stoull(data);

		while(aux != nullptr && aux->isFresh(num) == spoiled){
			aux = aux->next;
		}
		if(aux != nullptr) return fresh;
		else return spoiled;
    }

	void insert(ull desde,ull hasta) {
		Node* aux = new Node(desde, hasta, raiz); 
	    raiz = aux;
	}
};



int main(int argc, char const *argv[])
{
    ifstream fich("input.txt");
    if (!fich.is_open()) {
        throw runtime_error("Error al abrir el archivo\n");
    }
    string l1;
    int count = 0;
    
    bool inflexion = false;
    Cafeteria *cafe = new Cafeteria();

    while (getline(fich, l1))
    {
        int pos_guion = l1.find('-');
        if (pos_guion > 0) // part del input on estan els rangos
        {
            ull desde = stoull(l1.substr(0, pos_guion));
            ull hasta = stoull(l1.substr(pos_guion + 1));
            cafe->insert(desde, hasta);
        }
        else if (inflexion) // part del input on estan els casos
        {
            count += (cafe->search(l1) == true) ? 1 : 0;
        }
        else if(l1.empty()) // estem en la linea de antes dels inputs de casos
        {
            inflexion = true;
        }
    }
    delete cafe;
    cout << count << endl;
    fich.close();

    return 0;
}
