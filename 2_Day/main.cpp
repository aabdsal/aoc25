#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cctype>

using namespace std;

void espacios(string &s)
{
    while (!s.empty() && isspace((unsigned char)s.front()))
        s.erase(s.begin()); // Elimina els espais al principi, perque sino me donava un error pero de locos
    while (!s.empty() && isspace((unsigned char)s.back()))
        s.pop_back(); // Igual pero al final
}

unsigned long long suma_invalido(const string &a, const string &b)
{
    // Try y Catch perque si no tampoc me anava, si aso es un proba y error molt dur
    try
    {
        unsigned long long start = stoull(a);
        unsigned long long end = stoull(b);
        if (start > end)
            return 0;
        unsigned long long Nvalid = 0;
        for (unsigned long long v = start; v <= end; ++v)
        {
            string s = to_string(v);
            if (s.size() % 2 != 0) // Mires que la longitud siga parell, perque si no son parells els tens que ignnorar o algo aixina posava
                continue;
            int m = s.size() / 2;
            // if (s.compare(0, m, s, m, m) == 0) Esta funciona, y se recomana gastar esta, pero no se perque si la que he posat ja fa lo que toca, no se que vol dir ixa "m" al final

            /* 
            Ya se lo que fa, compara la string s (s.compare()), desde la posicion 0 a la 0+m, en la string s (tercer parametre) desde la posicion m a la m+m (o sea desde la mitad fins al final) 
            */

            if (s.compare(0, m, s, m) == 0) // Funcio treta de internet que encara no se lo que fa pero bueno 
                    Nvalid += stoull(s);
        }
        return Nvalid;
    }

    catch (...) // Aso no sabia ni que se podia fer, que dur tot
    {
        return 0;
    }
}

int main(void)
{
    string line;
    unsigned long long Nvalid = 0;
    ifstream file("input.txt");
    while (getline(file, line))
    {
        stringstream ss(line);
        string token;
        while (getline(ss, token, ',')) // Aso me ho apute, perque ho he tret de un problema antic de CodeForces
        {
            espacios(token);
            int pos = token.find('-');

            string id1 = token.substr(0, pos);
            string id2 = token.substr(pos + 1);

            espacios(id1);
            espacios(id2);

            Nvalid += suma_invalido(id1, id2);
        }
    }

    cout << Nvalid << '\n';
    return 0;
}