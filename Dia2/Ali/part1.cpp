#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define ull unsigned long long

using namespace std;

int main(int argc, char const *argv[])
{
    ifstream fich("input.txt");
    if (!fich.is_open()) {
        throw runtime_error("Error al abrir el archivo\n");
    }
    string l1;
    ull count = 0;

    while (getline(fich, l1))
    {
        istringstream ss(l1);
        string aux;
        while(getline(ss, aux,','))
        {
            int pos_guion = aux.find('-');
            ull desde = stoull(aux.substr(0,pos_guion));
            ull hasta = stoull(aux.substr(pos_guion + 1));
            for (ull i = desde; i <= hasta; i++)
            {
                string aell = to_string(i);
                // los numeros con digitos impares no pueden tener digitos repetidos dos veces
                if ((aell.size()) % 2 == 0) // si el nº de digitos es par
                {
                    int mid = (aell.size())/ 2;
                    if (aell.substr(0,mid) == aell.substr(mid))
                    {
                        count += i;
                    }
                }
            }
        }
    }
    cout << count << endl;
    fich.close();

    return 0;
}
