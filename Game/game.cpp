#include <iostream>
#include <time.h>
#include <cstdlib>
#include <windows.h>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

vector<int> highlighting_pos;
void line(char ch)
{
    for (int i = 0; i < 60; i++)
    {
        cout << ch;
    }
    cout << endl;
}
void header()
{
    system("cls");
    line('=');
    cout << "\t\tNUMBER DETECTION GAME\n";
    line('=');
}
void printInstructions()
{
    ifstream file("instructions.txt");
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            cout << line << endl;
        }
        file.close();
    }
    else
    {
        cout << "Unable to open file" << endl;
    }
}
const int MAX_LIVES = 3;
class LivesStack
{
private:
    int top;
    int tries[MAX_LIVES];

public:
    LivesStack()
    {
        top = -1;
    }
    bool isEmpty()
    {
        return top == -1;
    }
    bool isFull()
    {
        return top == MAX_LIVES - 1;
    }

    void push(int value)
    {
        if (!isFull())
        {
            tries[++top] = value;
        }
    }

    int pop()
    {
        if (top >= 0)
        {
            return tries[top--];
        }
        return -1;
    }
    int getTop()
    {
        return top;
    }

    int *getTries()
    {
        return tries;
    }
};

struct Node
{
    int data;
    Node *next;
};

int points = 0;
int livesLeft = 3;
char rows[7] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
char columns[7] = {'1', '2', '3', '4', '5', '6', '7'};

class NumbersQueue
{
private:
    Node *front, *rear;

public:
    NumbersQueue()
    {
        front = rear = NULL;
    }

    void enqueue(int elem)
    {
        Node *newnode;
        newnode = new Node;
        newnode->data = elem;
        newnode->next = NULL;

        if (front == NULL)
            front = rear = newnode;
        else
        {
            rear->next = newnode;
            rear = newnode;
        }
    }
    int numberToFind()
    {
        srand(time(NULL));
        return rand() % 60 + 10;
    }

    void settingNumbers(int n, int num)
    {
        srand(time(NULL));
        int *random_array = new int[n];
        int index1 = rand() % n + 1;
        Sleep(100);
        int index2 = rand() % n + 1;
        if (index1 == 1 || index2 == 1)
        {
            highlighting_pos.push_back(index1);
            highlighting_pos.push_back(index1 + 1);
            highlighting_pos.push_back(index1 + 2);
        }
        if (index2 == 1)
        {
            highlighting_pos.push_back(index2);
            highlighting_pos.push_back(index2 + 1);
            highlighting_pos.push_back(index2 + 2);
        }
        if (index1 == n)
        {
            highlighting_pos.push_back(index1);
            highlighting_pos.push_back(index1 - 1);
            highlighting_pos.push_back(index1 - 2);
        }
        if (index2 == n)
        {
            highlighting_pos.push_back(index2);
            highlighting_pos.push_back(index2 - 1);
            highlighting_pos.push_back(index2 - 2);
        }
        if (index1 != 1 && index1 != n)
        {
            highlighting_pos.push_back(index1);
            highlighting_pos.push_back(index1 - 1);
            highlighting_pos.push_back(index1 + 1);
        }
        if (index2 != 1 && index2 != n)
        {
            highlighting_pos.push_back(index2);
            highlighting_pos.push_back(index2 - 1);
            highlighting_pos.push_back(index2 + 1);
        }

        for (int i = 0; i < n; i++)
        {
            if (i == index1 - 1 || i == index2 - 1)
            {
                random_array[i] = num;
            }
            else
            {
                random_array[i] = rand() % 60 + 10;
            }
            Sleep(100);
        }
        for (int i = 0; i < n; i++)
        {
            enqueue(random_array[i]);
        }
    }

    void displayGrid(int position, int n, int s, LivesStack lives)
    {
        Node *temp;
        temp = front;
        int count = 0;
        int i = 1;
        int r = 0;
        string line;
        if (s == 3)
        {
            line = "----------------------------";
        }
        else if (s == 5)
        {
            line = "--------------------------------------------";
        }
        else if (s == 7)
        {
            line = "------------------------------------------------------------";
        }
        cout << " " << line << endl;
        cout << " \t";

        for (int i = 0; i < s; i++)
        {
            cout << " " << columns[i] << "\t";
        }
        cout << "\n " << line;
        cout << endl
             << " | " << rows[r];
        cout << " |\t";

        while (temp != NULL)
        {
            if (i == position)
            {
                cout << "\033[1;32m" << setw(2) << setfill('0') << temp->data << "\033[0m\t"; // Highlighted in green
            }
            else
            {
                bool found = false;
                int *tries = lives.getTries();
                for (int j = 0; j <= lives.getTop(); j++)
                {
                    if (i == tries[j])
                    {
                        cout << setw(2) << setfill('0') << temp->data << "\t";
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    auto it = find(highlighting_pos.begin(), highlighting_pos.end(), i);
                    if (it != highlighting_pos.end())
                    {
                        cout << "\033[1;31m##\033[0m\t"; // Double '#' highlighted in red
                    }
                    else
                    {
                        cout << "##\t"; // Double '#'
                    }
                }
            }
            count++;
            temp = temp->next;
            if (count == s && r < s - 1)
            {
                cout << endl
                     << " | " << rows[r + 1] << " |\t";
                count = 0;
                r++;
            }
            i++;
        }
        cout << endl;
    }

    bool checkNumber(int position, int target)
    {
        int number;
        Node *temp;
        temp = front;
        int i = 1;
        while (i < position)
        {
            temp = temp->next;
            i++;
        }
        number = temp->data;
        if (number == target)
        {
            return true;
        }
        else
            return false;
    }

    int setPosition(char rowPos, char colPos, int n)
    {
        int position;
        int row = rowPos - 65;
        if (rowPos >= 97 && rowPos <= 122)
            row = rowPos - 97;
        int col = colPos - 49;
        position = (row * n) + col + 1;
        return position;
    }

    bool playLevel(int lev, int n, int s, int max_tries)
    {
        header();
        data(lev, livesLeft);
        int target = numberToFind();
        settingNumbers(n, target);
        cout << "\nTarget: " << target << endl
             << endl;
        displayGrid(-1, n, s, LivesStack());
        LivesStack lives;

        char rowChoice, colChoice;
        int choice;
        int tries = 0;
        livesLeft = 3;
        while (tries < max_tries)
        {
            cout << "\nEnter position (eg. B3): ";
            cin >> rowChoice >> colChoice;
            choice = setPosition(rowChoice, colChoice, s);
            int valueToBeDeleted = choice;
            auto it = find(highlighting_pos.begin(), highlighting_pos.end(),
                           valueToBeDeleted);

            if (it != highlighting_pos.end())
            {
                highlighting_pos.erase(it);
            }
            cout << endl;
            displayGrid(choice, n, s, lives);
            if (checkNumber(choice, target))
            {
                if (livesLeft == 3)
                {
                    points += 5;
                }
                else if (livesLeft == 2)
                {
                    points += 3;
                }
                else if (livesLeft == 1)
                {
                    points += 2;
                }
                return true;
            }
            else
            {
                cout << "Try again!" << endl;
                lives.push(choice);
                tries++;
                livesLeft = max_tries - tries;
                cout << endl;
                data(lev, livesLeft);
            }
        }
        return false;
    }

    void data(int level, int livesLeft)
    {
        line('-');
        cout << "Total Lives: " << 3 << "\t\t\t\tRemaining Lives: " << livesLeft << endl;
        cout << "Current Level: " << level << "\t\t\tPoints: " << points << endl;
        line('-');
    }

    bool level1Passed = false;
    bool level2Passed = false;

    void playLevelWise(NumbersQueue game, int n)
    {
        int lev = n;
        int grid;
        if (n == 1)
        {
            cout << "\t\tLEVEL 1 - EASY\n";
            grid = 3;
        }
        else if (n == 2)
        {
            cout << "\t\tLEVEL 2 - MEDIUM\n";
            grid = 5;
        }
        else if (n == 3)
        {
            cout << "\t\tLEVEL 3 - HARD\n";
            grid = 7;
        }
        data(lev, livesLeft);
        if (game.playLevel(lev, (grid * grid), grid, MAX_LIVES))
        {
            cout << "Congratulations you have passed level " << lev << "!" << endl;
            data(lev, livesLeft);
        }
        else
        {
            cout << "You couldn't complete level " << lev << ". Game Over! :(" << endl;
        }
        getchar();
        getchar();
    }

    void levels(char ch)
    {
        system("cls");
        header();

        NumbersQueue game;
        switch (ch)
        {
        case 1:
            points = 0;
            livesLeft = 3;

            playLevelWise(game, 1);
            cout << "Press any key to go back to the main menu." << endl;
            getchar();
            getchar();
            mainPage();

            break;
        case 2:
            points = 0;
            livesLeft = 3;
            playLevelWise(game, 2);
            cout << "Press any key to go back to the main menu." << endl;
            getchar();
            getchar();
            mainPage();

            break;
        case 3:
            points = 0;
            livesLeft = 3;
            playLevelWise(game, 3);
            cout << "Press any key to go back to the main menu." << endl;
            getchar();
            getchar();
            mainPage();

            break;
        case 4:
            points = 0;
            livesLeft = 3;
            livesLeft = 3;
            playLevelWise(game, 1);
            playLevelWise(game, 2);
            playLevelWise(game, 3);
            break;

        default:
            break;
        }
    }

    void mainPage()
    {
        int ch;
        bool menu;
        system("cls");
        do
        {
            menu = false;
            header();
            cout << "Choose an option: \n";
            cout << endl
                 << "[1] Play Game\n"
                 << "[2] Instructions\n"
                 << "[3] Exit\n"
                 << endl;
            line('-');
            cout << "Enter your choice: ";
            cin >> ch;

            switch (ch)
            {
            case 1:
                system("cls");
                header();
                int levelChoice;
                cout << "Choose a level to play: " << endl;
                cout << "[1] Level 1 - Easy" << endl
                     << "[2] Level 2 - Medium" << endl
                     << "[3] Level 3 - Hard" << endl
                     << "[4] Conventional - Easy to Hard" << endl;
                line('-');
                cout << "Enter your choice: ";
                cin >> levelChoice;

                levels(levelChoice);

                break;
            case 2:
                system("cls");
                header();
                cout << "\t\t    Instructions" << endl;
                line('-');
                printInstructions();
                line('-');
                cout << endl
                     << "Press any key to go back to the main menu." << endl;
                getchar();
                getchar();
                mainPage();
                break;
            case 3:
                system("cls");
                header();
                cout << "\nThank you! See you next time! : >\n"
                     << endl;
                line('-');
                Sleep(1000);
                menu = true;
                exit(0);
                break;
            default:
                header();
                cout << "Invalid choice. Please try again." << endl;
                cout << "Press any key to go back to the main menu." << endl;
                getchar();
                getchar();
                mainPage();
                break;
            }
        } while (menu);
    }
};

int main()
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, 600, 600, TRUE);
    system("cls");
    NumbersQueue game;
    game.mainPage();
}