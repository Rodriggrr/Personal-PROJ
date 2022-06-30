#include <iostream>
using namespace std;


bool velha = true;
void mostrar_matriz(char mt[3][3])
{
    velha = true;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(mt[i][j] != 'X' && mt[i][j] != 'O'){
                cout << " •";
                velha = false;
            }
            else
                cout << " " << mt[i][j];
        }
        cout << endl;
    }
}

void choice(char matriz[3][3], int letter)
{
    char playerLetter = (letter == 0) ? 'O' : 'X';
    char choice;
    cin >> choice;
    switch(choice){
        case 'a': matriz[1][0] = playerLetter;
            break;
        case 'q': matriz[0][0] = playerLetter;
            break;
        case 'z': matriz[2][0] = playerLetter;
            break;
        case 'x': matriz[2][1] = playerLetter;
            break;
        case 's': matriz[1][1] = playerLetter;
            break;
        case 'w': matriz[0][1] = playerLetter;
            break;
        case 'e': matriz[0][2] = playerLetter;
            break;
        case 'd': matriz[1][2] = playerLetter;
            break;
        case 'c': matriz[2][2] = playerLetter;            
    }   
}

char verify_win(char mat[3][3])
{
    bool win = true;
    char winner = 'a';
    for(int i = 0; i < 3; i++){    
        if(mat[i][1] == mat[i][0] && mat[i][2] == mat[i][0])
                winner = mat[i][i];
        if(mat[1][i] == mat[0][i] && mat[2][i] == mat[0][i])
                winner = mat[i][i];

        

    }
        if(mat[0][0] == mat[1][1] && mat[2][2] == mat[0][0])
                winner = mat[0][0];
        
        if(mat[0][2] == mat[1][1] && mat[1][1] == mat[2][0])
                winner = mat[0][2];
        
    
    return winner;
}

int main(char winner)
{
    char matriz[3][3];
    matriz[0][1] = 'a';
    mostrar_matriz(matriz);
    int xoro = 0;
    winner = 'a';
    while(true){
        xoro++;
        xoro %= 2;
        choice(matriz, xoro);
        mostrar_matriz(matriz);
        winner = verify_win(matriz);
    
        if(winner != 'a'){
            cout << "\n\"" << winner << "\" ganhou!" << endl;
            winner = 'a';
            break;
        }
        else if(velha){
            cout << "Deu velha! Ninguém ganhou.\n";
            break;
        }
    }
    cout << "Deseja jogar novamente? (s/n)\n";
    char choice;
    cin >> choice;
    if(choice == 's'){
        main('a');
        return 0;
    } else {
        return 0;
    }
}