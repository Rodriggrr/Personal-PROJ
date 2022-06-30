#include <iostream>
#include <ctime>
#include <vector>
using namespace std;

void mostrar_matriz(vector<int> y)
{
    for(int i = 1, j = 0; i <= 16; i++, j++){
        if(y[j] == 0)
            cout << "* ";
        else
            cout << y[j] << " ";
        if(i % 4 == 0)
            cout << endl;
    }
}
//0 0 0 0 
//0 0 0 0
//0 0 0 0
//0 0 0 0

vector<int> colocar_aleatorio(vector<int> y)
{
    srand(rand());
    for(int i = rand() % 16; i < 16; i++)
        if(y[i] == 0){
            y[i] = (rand() % 10 == 0) ? 4 : 2;
            return y;
        }
    
}

vector<int> up(vector<int> y)
{
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 16; j++){
            if(y[j+4] == y[j] && y[j] != 0)//caso o número abaixo seja o mesmo
            {
                y[j] *= 2;
                y[j+4] = 0;
                i+=4;
            }
            if(y[j-4] == 0 && j-4 >= 0)
            {
                y[j-4] = y[j];
                y[j] = 0;
            }
        }
    return y;
}

vector<int> left(vector<int> y)
{
    for(int i = 15; i >= 0; i--){
        if(y[i-1] == y[i] && (i-1 != 3 && i-1 != 7 && i-1 != 11 && i-1 != 15) && i - 1 >= 0)  
        {
            y[i - 1] = y[i] * 2;
            y[i] = 0;
            i--;
        }
        if(y[i-1] == 0 && (i-1 != 3 && i-1 != 7 && i-1 != 11 && i-1 != 15) && y[i] != 0 && i - 1 >= 0)
        {
            y[i-1] = y[i];
            y[i] = 0;
        }
            
    }
    return y;
}

vector<int> right(vector<int> y)
{
    for(int i = 0; i < 15; i++){
        if(y[i+1] == y[i] && i + 1 % 4 != 0 && i + 1 <= 15)
        {
            y[i+1] = y[i] * 2;
            y[i] = 0;
        } 
        if(y[i+1] == 0 && (i+1) % 4 != 0 && y[i] != 0 && i+1 <= 15)
        {
            y[i+1] = y[i];
            y[i] = 0;
        }
    }
    return y;
}

vector<int> down(vector<int> y)
{
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 16; j++){
            if(y[j-4] == y[j] && y[j] != 0 && j-4 >= 0)//caso o número abaixo seja o mesmo
            {
                y[j] *= 2;
                y[j-4] = 0;
                i-=4;
            }
            if(y[j+4] == 0 && j+4 <= 15)
            {
                y[j+4] = y[j];
                y[j] = 0;
            }
        }
    return y;
}

vector<int> comprimir (vector<int> y, char lado)
{
    switch(lado){
        case 'w': 
            y = up(y);
            break;

        case 'a':
            y = left(y);
            break;

        case 'd':
            y = right(y);
            break;
        case 's':
            y = down(y);
            break;


    }
        return y;
}


int main()
{
    vector<int> matriz(16, 0);

    srand(time(NULL));

    matriz = colocar_aleatorio(matriz);
    matriz = colocar_aleatorio(matriz);
    mostrar_matriz(matriz);
    
    while(true)
    {
    char lado;
    cin >> lado;
    
    matriz = comprimir(matriz, lado);
    matriz = colocar_aleatorio(matriz);
    mostrar_matriz(matriz);
    }
    
}