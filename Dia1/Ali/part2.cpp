#include <iostream>
#include <fstream>
#include <string>

#define INI 50

using namespace std;

int main(int argc, char const *argv[])
{
    ifstream fich("input.txt");
    if (!fich.is_open()) {
        throw runtime_error("Error al abrir el archivo\n");
    }
    string l1;
    int count = 0, desplazamiento = INI;
    //cout << "The dial starts by pointing at 50." << endl;

    while (getline(fich, l1))
    {
        char c = l1[0];
        int rotations = stoi(l1.substr(1));

        int distancia_al_cero = (c == 'L') ? ((!desplazamiento) ? 100 : desplazamiento) : ((!desplazamiento) ? 100 : 100 - desplazamiento);

        if (rotations >= distancia_al_cero) // copiada historica
        {
            count += 1 + ((rotations - distancia_al_cero) / 100); // 1 + mes les voltes que pasa per el 0
        }

        desplazamiento = (c == 'L') ? (desplazamiento - rotations) : (desplazamiento + rotations); 
        /// convertixc el numero a uno del 0 al 99
        desplazamiento = ((desplazamiento % 100) + 100) % 100;   

        //cout << "The dial is rotated " << l1 << " to point at " << desplazamiento << endl;
    }
    fich.close();

    cout << count << endl;
    return 0;
}
