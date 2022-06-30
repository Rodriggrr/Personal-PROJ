#include <iostream>
#include <vector>
using namespace std;


int mesa = 0;
bool vaiIgnorar = false;

//Printar no terminal a quantidade que cada jogador tem.
void mostrar_dinheiro(vector<int> jogador, int quantiaJogs, int mesa, bool jogsFora, vector<int> jogsIgnorados)
{
    cout << "\n-----------------------------------\nQuantidade de milhos: " << endl;
    cout << "Mesa: " << mesa << endl;

    //Laço para imprimir os jogadores.
    for(int i = 1; i <= quantiaJogs; i++)
    {
        //Observar se o jogador atual está fora da rodada, ou se não tem milhos.
        bool ignorar = false;
        if(jogador.at(i - 1) == 0)
        {
            cout << "Jogador " << i << " não tem milhos.\n";
            ignorar = true;
        }
        if(jogsFora)
        {
            for(int  j = 0; j < jogsIgnorados.size(); j++)
            {
                if(i == (jogsIgnorados.at(j) + 1))
                    ignorar = true;
            }
        }
        //-------------------------------------------------------------------

        //Imprimir caso esteja jogando e com milhos.
        if(!ignorar)
        {
        cout << "Jogador " << i 
             << ": " << jogador.at(i - 1) 
             << endl;
        }
    }
    cout << "-----------------------------------\n";
}

//Observa se há algum jogador fora da rodada.
bool ver_jog_ignorados(vector<int> &jogsIgnorados, int jogAtual)
{
    //Retorna 'true' se houver algum jogador que não será contabilizado.
     for(int  j = 0; j < jogsIgnorados.size(); j++)
        {
            if(jogAtual == jogsIgnorados.at(j))
                return true;
        }
}

//Observa se há algum jogador sem dinheiro.
vector<int> jog_sem_dinheiro(vector<int> jogador, vector<int> jogsIgnorados, int quantidade, bool &semDinheiro, vector<int> &jogsSemDinheiro)
{
    //Retorna os jogadores que estarão fora da partida por falta de milhos.
    for(int i = 0; i < jogador.size(); i++)
    {
        if(jogador.at(i) - quantidade < 0)
        {
            jogsIgnorados.push_back(i);
            jogsSemDinheiro.push_back(i);
            vaiIgnorar = true;
            semDinheiro = true;
        }
    }
    return jogsIgnorados;
}

//Exclui os jogadores que decidiram não apostar.
vector<int> vaiIgnorar_jogador(vector <int> jogsIgnorados)
{
    //Remoção manual de jogadores na rodada atual; desistência.
    cout << "Diga quais jogadores vão sair da jogada, e digite \"0\" quando terminar.\n";
    while(true)
    {
        int jogvaiIgnorar;
        cin >> jogvaiIgnorar;

        if(jogvaiIgnorar == 0)
            return jogsIgnorados;

        jogsIgnorados.push_back(jogvaiIgnorar - 1);
    }
}

//Para quando um jogador aposta tudo.
vector<int> apostar_tudo(vector<int> jogador, vector<int> jogsIgnorados, bool jogsFora)
{
     for(int i = 0; i < jogador.size(); i++)
        {
            //Verifica se o jogador faz parte da rodada.
            bool ignorar = false;
            if(jogsFora)
            {
                ignorar = ver_jog_ignorados(jogsIgnorados, i);
            }
            //-----------------------------------------

            if(!ignorar)
            {
                mesa += jogador.at(i);
                jogador.at(i) = 0;
            }            
        }
        return jogador;
}

//Para quando um jogador faz uma aposta.
vector<int> apostar(vector<int> jogador, vector<int> &jogsIgnorados, int quantidade, bool jogsFora)
{
    vector<int> jogsSemDinheiro;
    bool semDinheiro = false;
    jogsIgnorados = jog_sem_dinheiro(jogador, jogsIgnorados, quantidade, semDinheiro, jogsSemDinheiro);

    if(semDinheiro)
    {
        cout << "\n---------------------\nOs seguintes jogadores saíram da rodada por falta de milhos:\n";
        for(int i =0; i < jogsSemDinheiro.size(); i++)
        {
            cout << "Jogador " << jogsSemDinheiro[i] + 1 << endl;
        }
        cout << "---------------------\n";
        jogsFora = true;
    }

     for(int i = 0; i < jogador.size(); i++)
        {
            //Verificar se jogador está na rodada.
            bool ignorar = false;
            if(jogsFora)
            {
               ignorar = ver_jog_ignorados(jogsIgnorados, i);
            }
            if(!ignorar)
            {
                mesa += quantidade;
                jogador.at(i) -= quantidade;
            }
        }
        return jogador;
}

//Verifica o tipo de aposta do jogador.
vector<int> tipo_aposta(vector<int> jogador, int quantidade, int quantiaJogs, bool jogsFora, vector<int> &jogsIgnorados)
{
    if(quantidade == 0)
    {
        
        jogador = apostar_tudo(jogador, jogsIgnorados, vaiIgnorar);
        return jogador;
    }
    else
    {
        jogador = apostar(jogador, jogsIgnorados, quantidade, vaiIgnorar);
        return jogador;
    }
}

//Verifica os comandos usados pelo jogador.
int comando_jog(vector<int> jogador, int quantiaJogs)
{
    vector<int> jogsIgnorados;
    while(true)
    {
        int jogEscolhido1, jogEscolhido2, quantia;
        cin >> jogEscolhido1;
        char comando, ch;
        cin >> comando;
        switch(comando){

            case '>':
                cin >> jogEscolhido2 >> quantia;
                if(jogEscolhido1 < 1 || jogador.at(jogEscolhido1 - 1) - quantia < 0 || jogEscolhido2 > jogador.size())
                    {
                        cout << "Não permitido!" << endl;
                        continue;
                    }
                jogador.at(jogEscolhido2 - 1) += quantia;
                jogador.at(jogEscolhido1 - 1) -= quantia;
                break;
            retorno:
            case 't': 
                cout << "\nJogador " << jogEscolhido1 << " apostou tudo!\nTodos os jogadores vão cobrir a aposta? (s/n)\n";
                cin >> ch;
                if(ch == 's')
                    {
                       jogador = tipo_aposta(jogador, 0, quantiaJogs, vaiIgnorar, jogsIgnorados);
                    }
                    else
                    {
                        jogsIgnorados = vaiIgnorar_jogador(jogsIgnorados);
                        vaiIgnorar = true;
                        jogador = tipo_aposta(jogador, 0, quantiaJogs, vaiIgnorar, jogsIgnorados);
                    }
                    break;

            case 'm': 
                cout << "\n\nJogador " << jogEscolhido1 << " recebe todos os milhos da mesa.\n";
                    jogador.at(jogEscolhido1 - 1) += mesa;
                    mesa = 0;
                    jogsIgnorados.clear();
                break;  

            case 'a':
                cin >> quantia;
                if(quantia == 0)
                {
                    cout << "Você precisa apostar algo!\n";
                    continue;
                }
                if(jogador.at(jogEscolhido1 - 1) == quantia)
                    goto retorno;
                if(jogador.at(jogEscolhido1 - 1) - quantia < 0)
                {
                    cout << "Você não tem milhos suficientes!" << endl;
                    continue;
                }
                cout << "\nJogador " << jogEscolhido1 << " aposta " << quantia << endl;
                cout << "\nTodos os jogadores com milho o suficiente vão cobrir a aposta? (s/n)\n";
                cin >> ch;
                if(ch == 's')
                {
                    jogador = tipo_aposta(jogador, quantia, quantiaJogs, vaiIgnorar, jogsIgnorados);
                }
                else
                {
                    jogsIgnorados = vaiIgnorar_jogador(jogsIgnorados);
                    vaiIgnorar = true;
                    jogador = tipo_aposta(jogador, quantia, quantiaJogs, vaiIgnorar, jogsIgnorados);
                }
        }
        mostrar_dinheiro(jogador, quantiaJogs, mesa, vaiIgnorar, jogsIgnorados);
    }
}

int main()
{
    cout << "Bem-vindo ao contador de Milhos de Poker!\n1 - Começar;\n2 - Comandos.\n";
    int decisao;
    cin >> decisao;
    if(decisao == 2)
    {
        cout << "\n---------------------"
                << "\n\"a\": Apostar\nEx: '1 a 10'  (1 = jogador que vai apostar, a = comando, 10 = valor apostado.)"
                << "\n\n\"t\": Apostar tudo\nEx: '1 t'     (1 == jogador que vai apostar, t = comando.)"
                << "\n\n\">\": Dar dinheiro\nEx: '1 > 2 5' (1 = jogador doador, > = comando, 2 = jogador recebente, 5 = valor doado.)"
                << "\n\n\"m\": Receber o montante da mesa.\nEx: '1 m'     (1 = jogador que vai receber o acumulo das apostas, m = comando.)"
                << "\n\nPressione ENTER para começar.\n---------------------\n";
    cin.get();
    cin.ignore(1);
    }

    cout << "Digite a quantidade de jogadores:" << endl;
    int jog;
    cin >> jog;

    cout << "Digite com quantos milhos cada jogador começa:\n";
    int comJog;
    cin >> comJog;

    vector<int> jogs(jog, comJog);
    mostrar_dinheiro(jogs, jog, 0, vaiIgnorar, jogs);
    comando_jog(jogs, jog);
}