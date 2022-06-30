#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;

int main()
{
    srand(time(0));

    cout << setfill('0') << setw(3) << rand() % 999
         << "."
         << setfill('0') << setw(3) << rand() % 999
         << "."
         << setfill('0') << setw(3) << rand() % 999
         << "."
         << setfill('0') << setw(2) << rand() % 99;

        
}
