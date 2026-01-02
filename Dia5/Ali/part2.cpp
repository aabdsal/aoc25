#include <iostream>
#include <fstream>
#include <string>

#define ull unsigned long long

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

	void insert(ull desde,ull hasta) {
		Node* aux = new Node(desde, hasta, raiz); 
	    raiz = aux;
	}

    void sort() // de menor a mayor teniendo en cuenta ull desde
    {
        bool swapFet = true;
		while(swapFet){
            Node *aux = raiz;       
            swapFet = false;

            while (aux->next != nullptr)
            {
                if (aux->desde > aux->next->desde)
                {
                    ull temp1 = aux->next->desde;
                    aux->next->desde = aux->desde;
                    aux->desde = temp1;

                    ull temp2 = aux->next->hasta;
                    aux->next->hasta = aux->hasta;
                    aux->hasta = temp2;
                    swapFet = true;
                }
                aux = aux->next;
            }
		}
    }

    void mirarRangos(){
        Node *aux = raiz;

        while (aux != nullptr && aux ->next != nullptr)
        {
            if (aux->hasta >= aux->next->desde)
            {
                aux->hasta = max(aux->hasta, aux->next->hasta);
                Node *apuntar = aux->next->next;
                Node *temp = aux->next;
                delete temp;

                aux->next = apuntar;
            }
            else{
                aux = aux->next;
            }
        }
        
    }

    void sumar(ull &count){
        Node *aux = raiz;

        while (aux != nullptr)
        {
            count += (aux->hasta - aux->desde) + 1;
            aux = aux->next;
        }
        
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
        else if(l1.empty()) // estem en la linea de antes dels inputs de casos
        {
            break;
        }
    }
    cafe->sort();
    cafe->mirarRangos();
    cafe->sumar(count);

    delete cafe;
    cout << count << endl;
    fich.close();

    return 0;
}
