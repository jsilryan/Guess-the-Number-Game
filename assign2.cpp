#include <iostream>
#include <fstream>
#include "time.h"
#include <cstdlib>
#include <windows.h>
#include <direct.h>
#define MAX 5
using namespace std;
int k = 1;
int l = 1;
class Session
{
 protected:
    int sess_number;
    string sess_name;
    int players;
 public:
    int leave, i, j;
    Session()
    {
        j = 0;
        sess_number = 0;
    }
    ~Session()
    {

    }
    void sess();
    void display();
};
class Player
{
protected:
    int player_id;
    string player_name;
public:
    int player_points;
    Player()
    {
        player_points = 0;
    }
    ~Player()
    {

    }
    int player_ans;
    void details();
    void awards();
    void answer();
};

class Round: public Session
{
public:
    int round_no;
    int guess_no;
    int correct, dev;
    Round()
    {
        round_no = 0;
        correct = 0;
    }
};

void Player::details()
{
    player_id = l;
    cout << "Enter player " << player_id << " name:\n";
    cin >> player_name;
    l++;
}

void Player::answer()
{
    cout << "Guess the number " << player_name << ":\n";
    cin >> player_ans;
}

void Player::awards()
{
    cout << player_id << ": " << player_name << ": " << player_points << endl;
    //To write into the file
    ofstream myfile;
    myfile.open("score{" + std::to_string(k) + "}.txt", ios::app);
    if (myfile.is_open())
    {
        myfile << player_id << ": " << player_name << ": " << player_points << endl;
    }

}

void Session::display()
{
    cout << "Session Name: " << sess_name << endl;
    cout << "Total Players: " << players << endl;
    //To print into file
    ofstream myfile;
    myfile.open("score{" + std::to_string(k) + "}.txt");
    if (myfile.is_open())
    {
        myfile << "Session Name: " << sess_name << endl;
        myfile << "Total Players: " << players << endl;
    }
}

void Session::sess()
{
    ofstream myfile;
    myfile.open("score{" + std::to_string(sess_number) + "}.txt");
    srand(time(NULL));
    sess_number = k;
    cout << "Enter session name:\n";
    cin >> sess_name;
    cout << "How many players are there?\n";
    cin >> players;
    Player pls[players];
    Round rs[MAX];
    for (i = 0; i < players; i++)
    {
        pls[i].details();
    }
    do
    {
        rs[j].guess_no = (rand()%100) + 1;
        cout << "Round " << j+1 << ": New random number generated!\n";
        for(i = 0; i < players; i++)
        {
            pls[i].answer();
            rs[j].dev = pls[i].player_ans - rs[j].guess_no;
            if (rs[j].dev < 0)
            {
                rs[j].dev = -rs[j].dev;
            }
            if (pls[i].player_ans == rs[j].guess_no)
            {
                pls[i].player_points = pls[i].player_points + 10;
                cout << "Correct Guess.\nNumber was " << rs[j].guess_no <<endl;
                rs[j].correct = 1;
                break;
            }
            else if (rs[j].dev <= 3)
            {
                pls[i].player_points = pls[i].player_points + 7;
                cout << "Wrong Guess.\n" <<endl;
            }
            else if (rs[j].dev > 3 && rs[j].dev <= 5)
            {
                pls[i].player_points = pls[i].player_points + 5;
                cout << "Wrong Guess.\n" <<endl;
            }
            else if (rs[j].dev > 5 && rs[j].dev <= 10)
            {
                pls[i].player_points = pls[i].player_points + 2;
            cout << "Wrong Guess.\n" <<endl;
            }
            else
            {
                pls[i].player_points = pls[i].player_points + 0;
                cout << "Wrong Guess.\n" <<endl;
            }
        }
        if (pls[i].player_ans != rs[j].guess_no)
        {
            cout << "Number was " << rs[j].guess_no <<endl;
        }
        rs[j].round_no++;
        j++;
        if (j < MAX)
        {
            cout << "Do you want to leave round? Enter 1 to leave:\n";
            cin >> leave;
        }
        else
        {
            cout << "No rounds left!\n";
        }
        if (leave == 1)
        {
            rs[j].round_no--;
            j--;
        }
    }while(leave != 1 && (rs[j].correct == 1 || i == players) && j < MAX);
    cout << "\nSession " << sess_number << ":\n";
    myfile << "\nSession " << sess_number << ":\n";
    display();
    for (i = 0; i < players; i++)
    {
        pls[i].awards();
    }
    myfile << "\n";
    l = 1;
    k++;
}

void intro()
{
    int j;
    cout << "Welcome to the Guessing game.\n";
    cout << "There are a maximum of 5 sessions with 5 rounds each:\n";
    for (j = 0; j < 3; j++)
    {
        cout << ".";
        Sleep(500);
    }
    cout << "\n";
}

int main()
{
    if (mkdir("C:/GameFolder") == -1)
    {
        cerr << " Error : " << strerror(errno) << endl;
    }
    else
    {
        cout << "Folder created!\n";
    }

    intro();
    int exit, j;
    int x = 0;
    Session Se[MAX];
    do
    {
        cout << "Session "<< x+1 << ":\n";
        Se[x].sess();
        x++;
        if (MAX - x > 0)
        {
            cout << "Enter 1 for a new session, " << MAX - x << " left:\n";
            cin >> exit;
            cout << "\n";
        }
        else
        {
            cout << "No session left";
        }

    }while (exit == 1);

}
