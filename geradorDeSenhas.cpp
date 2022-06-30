#include <iostream>
#include <ctime>
using namespace std;

int main()
{
    srand (time(NULL));
    string component[4] = {
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 
        "abcdefghijklmnopqrstuvwxyz",
        "1234567890",
        "!@#$%&*+.;/"
        };

    string senha;

    for (int i = 0; i < (rand() % 12) + 8; i++)
    {
        int tam1 = rand() % 4;
        senha += component[tam1][rand() % (component[tam1].size())];
    }
    cout << senha << endl;
}