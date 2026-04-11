// #include <iostream>
// #include <vector>

// using namespace std;

// int main()
// {

//     int l, n;
//     cin >> l;
//     for (int i = 0; i < l; i++)
//     {
//         cin >> n;
//         vector<int> tablicaX(n / 2);
//         vector<int> tablicaY(n / 2);
//         for (int j = 0; j < n / 2; j++)
//         {
//             int w;
//             int w2;
//             cin >> w;
//             cin >> w2;
//             tablicaX[j] = w;
//             tablicaY[j] = w2;
//         }
//         long long pole = 0;
//         int liczbawiercholkow = n / 2;
//         for (int j = 0; j < liczbawiercholkow; j++)
//         {
//             int next = (j + 1) % liczbawiercholkow;
//             pole += ((long long)tablicaX[j] * tablicaY[next]) - ((long long)tablicaX[next] * tablicaY[j]);
//         }
//         cout << abs(pole) / 2 << endl;
//     }

//     return 0;
// }