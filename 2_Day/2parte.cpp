#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <vector>

using namespace std;

void espacios(string &s)
{
    while (!s.empty() && isspace((unsigned char)s.front()))
        s.erase(s.begin()); // Elimina els espais al principi, perque sino me donava un error pero de locos
    while (!s.empty() && isspace((unsigned char)s.back()))
        s.pop_back(); // Igual pero al final
}

int repetitions(const std::string &s)
{
    int n = (int)s.size();
    if (n == 0)
        return 0;
    vector<int> pi(n, 0);
    for (int i = 1; i < n; ++i)
    {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            ++j;
        pi[i] = j;
    }

    int p = n - pi[n - 1];   // Posible repeticio
    if (p > 0 && n % p == 0) // Comprovacio
        return n / p;
    return 1; // Si no hi ha soles tornes que conte el substring inicial (tots tenen un al menys)
}

unsigned long long suma_invalido(const string &a, const string &b)
{
    // Try y Catch perque si no tampoc me anava, si aso es un proba y error molt dur
    try
    {
        unsigned long long start = stoll(a);
        unsigned long long end = stoll(b);
        if (start > end)
            return 0;
        unsigned long long Nvalid = 0;
        for (unsigned long long v = start; v <= end; ++v)
        {
            string s = to_string(v);
            int reps = repetitions(s);
            if (reps > 1)
                if ((int)s.size() % reps == 0)
                {
                    Nvalid += v;
                }
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