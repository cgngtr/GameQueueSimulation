#include <iostream>
#include <cstdlib> // ?
#include <queue>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;
using namespace this_thread;
using namespace chrono;

int main()
{
    queue<int> q;
    vector<int> playerID = { 1, 2, 3, 4, 5 }; 
    time_t start, end;
    int userAmount; // Enter an amount of users to wait in the q system.

    q.push(playerID[0]);
    // random time needs to be spent before dequeuing (5-10s)
    thread printLater{ [&] {
        srand(time(NULL)); // random seed gen
        cout << to_string(playerID[0]) + " is now in the queue." << endl;
        int lb = 5, ub = 10;
        int connectionTime = (rand() % (ub - lb + 1)) + lb;
        sleep_for(seconds(connectionTime));
        cout << to_string(playerID[0]) + " left the queue after " + to_string(connectionTime) + " seconds." << endl;
        } 
            };
    printLater.join();
    q.pop();

    return 0;
}



/*Way to print out elements.
int frontElement = q.front();
cout << frontElement << endl;
 ------------------------------
 Ideas
 Kullanicinin ID'sine gore belirli ozellikleri olsun. Isim, yas, cinsiyet gibi.
 Sisteme giris yapildiginda bu bilgiler terminal uzerinden gosterilsin.
 Cikis yaparken kullanici ID'si ve ismi verilip cikis yapilma bilgisi gosterilsin.
 Bu dongu, user sayisi bitene kadar devam etsin.
 */
