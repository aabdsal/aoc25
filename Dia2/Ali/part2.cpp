#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

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
                string num = to_string(i); // convertir a string
                int digitos = num.size(); // tamaño del numero
                
                for (int j = 1; j <= digitos/2; j++) // pa fer substrigs en divisores
                {
                    if (num.size() % j == 0) // si es divisor
                    {
                        string patron = num.substr(0, j);
                        string reconstruido = "";
                        for (int k = 0; k < digitos/j; k++) { reconstruido += patron; }
                        if (reconstruido == num) 
                        { 
                            count += i; 
                            break; // per a que no faja el for j = 1
                        }
                        
                    }
                }    
            }
        }
    }
    cout << count << endl;
    fich.close();

    return 0;
}
