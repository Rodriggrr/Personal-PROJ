#include <iostream>
#include <sstream>
#include <windows.h>
#include <conio.h>
using namespace std;

struct calculator
{
    const float speedOfLight = 299792;
    long double speed;
    long double distance;
    long double result;
    long double time;
    int chosenValue = 0;
    int twoChosen = 0;
};


void move(int a, int b)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c;
    c.X = a;
    c.Y = b;
    SetConsoleCursorPosition(h, c);
}

void move_cursor(const int &opt)
{
     switch(opt)
    {
        case 3:
            move(20, 7);
            break;
        case 2:
            move(20, 10);
            break;
        case 1:
            move(20, 13);
            break;
    }
}    

void cursor_check(char choice, int &opt, calculator &cal)
{
    switch(choice)
    {
        case 'w':
            opt++;
            opt = (opt  > 3) ? 1 : opt;
            break;
        case 's':
            opt--;
            opt = (opt < 1) ? 3 : opt;
            break;
        case 'r':
            cal.twoChosen++;
            cal.chosenValue += 3;
            cal.speed = cal.speedOfLight;
            move(20, 7);
            cout << cal.speedOfLight;
            opt--;
            break;
    }

    move_cursor(opt);
   
}

void do_calc(int opt, stringstream &ss, calculator &cal)
{
    switch(opt)
    {
        case 3:
            ss >> cal.speed;
            break;
        case 2: 
            ss >> cal.distance;
            cal.distance *= 1000;
            break;
        case 1:
            ss >> cal.time;
            break;
    }
}   

void show_result(calculator &cal)
{
    cal.speed /= 0.27777778;
    cal.speed *= 1000;
    float oneHour = (cal.distance / cal.speed) / 1000;
    switch(cal.chosenValue)
    {
        case 5:
            move(20, 12);
            cout << "Tempo em horas, minutos, segundos e milisegundos:";
            move(20, 14);
            cout << oneHour << " hr";
            move(20, 15);
            cout << oneHour * 60 << " min";
            move(20, 16);
            cout << oneHour * 3600 << " s";
            move(20, 17);
            cout << oneHour * 3600000 << " ms";
            break;
        case 4:
            move(20, 10);
            cout << (cal.speed * (cal.time)) /1000;
            break;
        case 3:
            move(20, 7);
            cout << (cal.distance / (cal.time));
            break;
    }
}

void evaluate_choice(calculator &cal)
{
    int opt = 3;
    while(true){
        move_cursor(opt);
        if(cal.twoChosen == 2){
            show_result(cal);
            break;
        }
        char choice;
        choice = getch();
        string num;
        stringstream ss;
    
        if(isdigit(choice)){
            cal.twoChosen++;
            cal.chosenValue += opt;
            cout << choice;
            ss << choice;
            cin >> num;
            ss << num;
            do_calc(opt, ss, cal);
            opt--;
            move_cursor(opt);
        }
        else{
            cursor_check(choice, opt, cal);
        }
    }
}

void clear_screen(char fill = ' ') { 
    COORD tl = {0,0};
    CONSOLE_SCREEN_BUFFER_INFO s;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);   
    GetConsoleScreenBufferInfo(console, &s);
    DWORD written, cells = s.dwSize.X * s.dwSize.Y;
    FillConsoleOutputCharacter(console, fill, cells, tl, &written);
    FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
    SetConsoleCursorPosition(console, tl);
}

int main()
{
    SetConsoleTitleA("Calculadora de Tempo, Distância ou Velocidade.");
    calculator cal;
    move(0, 15);
    cout << "\nTerra - Lua:\n384 mil km;\n\nTerra - Sol:\n150 mi de km;\n\nTerra - Plutão:\n7.9 bi de km;"
         << "\n\nTerra - Marte:\n225 mi de km;\n\nFortal - Quix:\n168 km;\n\n";
    move(36, 0);
    cout << "Calculadora de Tempo, Distância ou Velocidade.";
    move(37, 1);
    cout << "Aperte 'r' para definir a velocidade da luz!";
    move(20, 6);
    cout << "Velocidade: (em km/h)";
    move(20, 9);
    cout << "Distância: (em km)";
    move(20, 12);
    cout << "Tempo: (em segundos)";

    evaluate_choice(cal);

    char choice;
    move(60, 6);
    cout << "Você deseja usar novamente?(s/n)";
    move(60, 7);
    choice = getch();

    if(choice == 'n')
        return 0;

    clear_screen();
    main();
}