#include <iostream>
#include <ctime>
#include <iomanip>
using namespace std;

int main()
{
    srand(time(NULL));
    cout << "Choose your trial times:\n";
    int trialTimes;
    cin >> trialTimes;
    long double Heads = 0, Crown = 0;
    int progress = 0;
    for(int i = 0; i < trialTimes; i++){
        
        int random = rand() % 2;
        if(random == 0)
            Heads++;
        else
            Crown++;
        
        if(trialTimes >=  100)
            if (i % (trialTimes / 100) == 0){
                progress++;
                progress = (progress > 100) ? 100 : progress;
               
                cout << '\r' << "Progress: " << progress << "%";   
            }
    }
    cout << endl;
    long double headsPercent = Heads / (trialTimes / 100);
    long double crownPercent = Crown / (trialTimes / 100);
    cout << "Heads: " << (long int)Heads << " or "; 
    cout << fixed << setprecision(3) << headsPercent << "%.\n";
    cout << "Crown: " << (long int)Crown << " or "; 
    cout << fixed << setprecision(3) << crownPercent << "%.\n";
}