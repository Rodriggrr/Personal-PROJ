#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

vector<int> receber_cartas(vector<int> cartas, int &cartaInt)
{
    int As = 0, outros = 0;
    cartas.push_back(rand() % 14);
    while(cartas.at(cartas.size() - 1) == 0)
        cartas.at(cartas.size() - 1) = rand() % 14;

    if(cartas.at(cartas.size() - 1) == 1)
    {
        As++;
        cartaInt += 10;
    }
    if(cartas.at(cartas.size() - 1) > 10)
        outros += cartas.at(cartas.size() - 1) - 10;

    cartaInt += cartas.at(cartas.size() - 1);

    if(outros > 0)
            cartaInt -= outros; 
    if(cartaInt > 21)
    {
        while(As > 0 && cartaInt > 21)
        {
            cartaInt -= 10;
            As--;
        }          
    }
    return cartas;
}

void mostrar_cartas(vector<int> cartas, int cartasCount, bool primRodada)
{
    bool esconderTotal = false;
    cout << "--------------------------------------\n";
    if(primRodada)
        cout << "Mesa:\n";
    cout << "[";
    for(int i = 0; i < cartas.size(); i++)
    {
        if(primRodada && cartasCount != 21)
        {
            cout << " ?,";
            primRodada = false;
            esconderTotal = true;
            continue;
        }
        cout << " ";
        if(cartas.at(i) == 1)
            cout << "A";
        else if(cartas.at(i) == 11)
            cout << "J";
        else if(cartas.at(i) == 12)
            cout << "Q";
        else if(cartas.at(i) == 13)
            cout << "K";
        else
            cout << cartas.at(i);
        if(i + 1 != cartas.size())
            cout << ",";
    }
    if(!esconderTotal && cartas.size() != 21)
        cout << " ]\nTotal: " << cartasCount << endl;
    else
        cout << " ]\nTotal: ?" << endl;

    cout << "--------------------------------------\n";
}

int main()
{
    srand(time(NULL));
    vector<int> cartas, cartasMesa;
    int cartasInt = 0, cartasMesaInt = 0;
    for(int i = 0; i < 2; i++)
    {
        cartas = receber_cartas(cartas, cartasInt);
        cartasMesa = receber_cartas(cartasMesa, cartasMesaInt);
    }
    mostrar_cartas(cartasMesa, cartasMesaInt, true);
    cout << endl;
    while(true)
    {
        mostrar_cartas(cartas, cartasInt, false);
        cout << endl;
        char choice;
        if(cartasInt > 21)
        {
            cout << "A mesa ganhou!\nDeseja jogar novamente? (s/n)\n";
            cin >> choice;
            if(choice == 's')
            {
                main();
                return 0;
            }
            else
                return 0;

        }
        cout << "Deseja puxar outra carta? (s/n)\n";
        cin >> choice;

        if(choice == 'n')
        {
            cout << "\nMesa:\n";
            while(cartasMesaInt < 21 && cartasMesaInt < cartasInt)
            {
                cartasMesa = receber_cartas(cartasMesa, cartasMesaInt);
                mostrar_cartas(cartasMesa, cartasMesaInt, false);
            }
            cout << endl;
            if((cartasMesaInt == cartasInt || cartasMesaInt > cartasInt) && cartasMesaInt <= 21)
            {
                cout << "A Mesa ganhou!\nDeseja jogar novamente? (s/n)\n";
                cin >> choice;
                if(choice == 's')
                {
                    main();
                    return 0;
                }
                else
                    return 0;

            } 
            else
                cout << "Você ganhou!\nDeseja jogar novamente? (s/n)\n";
                cin >> choice;
                if(choice == 's')
                {
                    main();
                    return 0;
                }
                else
                    return 0;
        }
        else
            cartas = receber_cartas(cartas, cartasInt);
    }
    
    
}