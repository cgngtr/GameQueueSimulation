#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>

using namespace std;
using namespace this_thread;
using namespace chrono;

class Player {
public:
    int playerID;
    string username;
    int age;
    string gender;

    Player(int id, const string& name, int playerAge, const string& playerGender)
        : playerID(id), username(name), age(playerAge), gender(playerGender) {}
};

int main()
{
    vector<Player> playerList;
    int userAmount; // Enter an amount of users to wait in the q system. (Less than 4)

    // Pushing players to the list.
    playerList.push_back(Player(2558960, "reveck", 25, "Male"));
    playerList.push_back(Player(2558961, "baechu", 30, "Female"));
    playerList.push_back(Player(2558962, "beemo", 22, "Male"));

    do
    {
        cout << "Enter the amount of users to wait in the queue: " << endl;
        cin >> userAmount;
        if(userAmount > playerList.size())
            cout << "Can't do more than 3 " << endl;
    } while (userAmount > playerList.size());

    srand(time(NULL));
    int exclusiveElementThreshold = 1; // Not sure if it's a fine way to name this.

    for (int i = 0; i < userAmount; ++i) {
        Player& currentPlayer = playerList[i]; // If & werent used, currentPlayer would 
                                               // have been a copy and modifications wouldn't affect the original element.

        cout << currentPlayer.username << " with ID " << currentPlayer.playerID << " is now in the queue." << endl;

        int lb = 5, ub = 10; // Setting lower and upper bounds for connectionTime.
        int connectionTime = (rand() % (ub - lb + exclusiveElementThreshold)) + lb; // Randomly setting connection time.
        sleep_for(seconds(connectionTime));

        cout << currentPlayer.username << " with ID " << currentPlayer.playerID << " left the queue after " + to_string(connectionTime) +" seconds." << endl;
    }
    return 0;
    
}

/*Way to print out elements.
int frontElement = q.front();
cout << frontElement << endl;
 ------------------------------
 Ideas

 DONE
 Kullanicinin ID'sine gore belirli ozellikleri olsun. Isim, yas, cinsiyet gibi.
 Sisteme giris yapildiginda bu bilgiler terminal uzerinden gosterilsin.
 Cikis yaparken kullanici ID'si ve ismi verilip cikis yapilma bilgisi gosterilsin.
 Bu dongu, user sayisi bitene kadar devam etsin.

 TODO
 - Additional queue system : Dequeueing users considering connectionTime. First one that is able to dequeue, dequeues.
 - Priority queueing
 - Connecting to a db?
 */