#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
bool esAccesible(vector <string> &matriu, int i, int j){
    vector <vector<int> > adjacents = {{-1, 0},{-1,1},{0,1},{1,1},{1, 0},{1, -1},{0,-1},{-1,-1}};

    int count = 0;
    for (int k = 0; k < 8; k++)
    {
        int i_pos = i + adjacents[k][0];
        int j_pos = j + adjacents[k][1];
        if (i_pos >= 0 && i_pos < matriu.size() && j_pos >= 0 && j_pos < matriu[i].size()){
            if (matriu[i_pos][j_pos] == '@')
            {
                count++;
            }
        }
        if(count >= 4) {return false;}        
    }
    
    return true;
}
int main(int argc, char const *argv[])
{
    ifstream fich("input.txt");
    string l1;
    long count = 0;
    vector <string> matriu;

    while (getline(fich, l1))
    {
        matriu.push_back(l1);
    }

    for (int i = 0; i < matriu.size(); i++) // matriu.size() = nº de files
    {
        for (int j = 0; j < matriu[i].size(); j++) // matriu[i].size() = nº de columnes
        {
            if (matriu[i][j] == '@' and esAccesible(matriu, i ,j))// mirar si es accesible o no
            {
                count++;
            }
        }
        
    }
    
    cout << count << endl;
    fich.close();

    return 0;
}
