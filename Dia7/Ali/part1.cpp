#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define ull unsigned long long

using namespace std;


int main(int argc, char const *argv[])
{
    ifstream fich("input.txt");
    string l1;
    ull count = 0;
    int flag = 1;

    while (getline(fich, l1))
    {
        istringstream ss (l1);
        string aux;

        while(ss >> aux){ // segons gpt aso ignora espais en blanc, prou util
        }
        flag += 1;
    }

    delete garbage;
    cout << count << endl;
    fich.close();

    return 0;
}
