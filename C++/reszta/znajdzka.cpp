#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int main()
{
    srand(time(0));
    int loso = rand() % 100 + 1;
    cout << loso << endl;
    int pick = 0;
    cout << "zgadnij liczbe" << endl;
    while (pick != loso)
    {
        cin >> pick;
        if (loso > pick)
        {
            cout << "wyzej" << endl;
        }
        else if (loso < pick)
        {
            cout << "nizej" << endl;
        }
    }
    cout << "nigger ballsack";
    return 0;
}