#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <sqlite3.h>

using namespace std;
using namespace std::chrono;

class Player {
public:
    int playerID;
    string username;
    int age;
    string gender;

    Player(int id, const string& name, int playerAge, const string& playerGender)
        : playerID(id), username(name), age(playerAge), gender(playerGender) {}
};

vector<Player> getPlayersFromDatabase() {
    auto start = high_resolution_clock::now();

    vector<Player> players;

    sqlite3* db;
    int rc = sqlite3_open("E:/cursed/GameQueueSimulation/db/db.db", &db);

    if (rc != SQLITE_OK) {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return players;
    }

    const char* query = "SELECT playerID, username, age, gender FROM playerList";
    sqlite3_stmt* stmt;

    rc = sqlite3_prepare_v2(db, query, -1, &stmt, nullptr);

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        int playerID = sqlite3_column_int(stmt, 0);
        const char* username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        int age = sqlite3_column_int(stmt, 2);
        const char* gender = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));

        players.push_back(Player(playerID, username, age, gender));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start);
    cout << "getPlayersFromDatabase islemi " << duration.count() << " nanosaniye surdu." << endl;

    return players;
}

void printPlayerInfo(const vector<Player>& playerList, int playerAmount) {

    auto start = high_resolution_clock::now();

    srand(time(NULL));

    for (int i = 0; i < playerAmount; ++i) {
        const Player& currentPlayer = playerList[i];

        cout << currentPlayer.username << " with ID " << currentPlayer.playerID << " is now in the queue." << endl;

        int lb = 5, ub = 10;
        int connectionTime = (rand() % (ub - lb + 1)) + lb;
        this_thread::sleep_for(chrono::seconds(connectionTime));

        cout << currentPlayer.username << " with ID " << currentPlayer.playerID << " left the queue after " << connectionTime << " seconds." << endl;
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start);

    cout << "printPlayerInfo islemi " << duration.count() << " nanosaniye surdu." << endl;

}

int main() {
    auto start = high_resolution_clock::now();
    vector<Player> playerList = getPlayersFromDatabase();
    int playerAmount;

    do {
        cout << "Enter the amount of users to wait in the queue: " << endl;
        cin >> playerAmount;
        if (playerAmount > playerList.size())
            cout << "Can't do more than " << playerList.size() << endl;
    } while (playerAmount > playerList.size());

    printPlayerInfo(playerList, playerAmount);

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start);

    cout << "main islemi " << duration.count() << " nanosaniye surdu." << endl;

    return 0;
}
