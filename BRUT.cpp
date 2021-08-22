#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>
#include <conio.h>

using namespace std;

string orgString = "qixhllaT";
int vecSize = 120;
vector<char> orgVString(orgString.size());
vector<vector<char>> suggSymb(orgString.size(), vector<char>(vecSize, NULL)); // For any symbols in orgString has a vector with suggested symbols. Every vector with suggested symbols has a number of them.
vector<vector<char>> suggSymb_zero(orgString.size(), vector<char>(vecSize, NULL));

// Вывод содержимого вектора в консоль (int)
void show_vector(vector<char>& a)
{
    for (vector<char>::iterator it = a.begin(); it != a.end(); ++it)
        cout << *it << " ";
}
void show_vector(vector<int>& a)
{
    for (vector<int>::iterator it = a.begin(); it != a.end(); ++it)
        cout << *it << " ";
}

/// <summary>
/// 
/// </summary>
/// <param name="a"> Here is your 2D vector </param>
/// <param name="oneString"> bool param. Set to true, if you want to write one string of 2D vector </param>
/// <param name="b"> int param. You need to put number of string in 2D vector </param>
void show_double_vector(vector<vector<char>>& a, bool oneString = false, int b=0)
{
    for (int y = 0; y < a.size(); y++) {
        if (oneString == true) {
            if (y != b) {
                continue;
            }
        }
        for (int x = 0; x < a[y].size(); x++) {
            if (x == 0 && oneString == false) {
                cout << orgVString[y] << " | ";
            }
            if (a[y][x] == NULL) {
                break;
            }
            else {
                cout << a[y][x] << '+';
            }
        }
        cout << endl;
    }
}

void calculation()
{
    vector<int> temp(suggSymb.size(), 0);

    int cache = 0;
    int allComb = 1;

    for (size_t y = 0; y < suggSymb.size(); y++) {
        for (size_t x = 0; x < vecSize; x++) {
            if (suggSymb[y][x] == NULL) {
                break;
            }
            else {
                cache++;
            }
        }
        if (cache != 0) {
            temp[y] = (cache + 1); // Plus one because we want a start symbol to be counted too
            cache = 0;
        }
    }
    for (size_t i = 0; i < temp.size(); i++) {
        if (temp[i] != 0)
            allComb *= temp[i];
    }
    show_vector(temp);
    cout << "All combination number is " << allComb << endl;
}

void menu()
{
    string rawInpt = " ";
    int cckdIntInpt = 0;
    char cckdChrInpt = ' ';

    // Adding string to vector
    for (int i = 0; i < orgString.size(); i++) {
        orgVString[i] = orgString[i];
    }

    while (true) {
        // Writing number of symbol
        for (int i = 0; i < orgString.size(); i++) {
            cout << i << " ";
        }
        cout << endl;
        // Writing symbols
        show_vector(orgVString);

        cout << "\n\nEnter number of symbol: ";
        cin >> rawInpt;

        try {
            cckdIntInpt = stoi(rawInpt);
            if (cckdIntInpt < 0 || cckdIntInpt > orgString.size()-1) {
                cout << "GET LOST FUCKER\n\n";
                continue;
            }
        }
        catch (exception Except) {
            cout << "You've got\n" << Except.what() << "\nCongrats!\n\n";
            continue;
        }

        while (true) {
            cout << "Your symbol is \"" << orgVString[cckdIntInpt] << "\", his number is \"" << cckdIntInpt <<
                "\"\nSuggested symbols: ";
            show_double_vector(suggSymb, true, cckdIntInpt);
            cout << "\n\n(\'ex\' - for exit, \'st\' - for start, \'rs\' - for reset ALL SYMBOLS. Repeat symbol to delete it)\nEnter suggested symbol: ";
            cin >> rawInpt;
            
            if (rawInpt.size() > 1) {
                if (rawInpt == "ex") {
                    break;
                }
                else if (rawInpt == "st") {
                    calculation();
                    break;
                }
                else if (rawInpt == "rs") {
                    suggSymb = suggSymb_zero;
                    continue;
                }
                cckdChrInpt = rawInpt[rawInpt.size() - 1];
            }
            else {
                cckdChrInpt = rawInpt[0];
            }

            for (size_t i = 0; i < suggSymb[cckdIntInpt].size(); i++) {
                // Checking, if entered symbol already was in orgVstring (original string vector)
                if (cckdChrInpt == orgVString[cckdIntInpt]) {
                    break;
                }
                else if (suggSymb[cckdIntInpt][i] == cckdChrInpt) {
                    suggSymb[cckdIntInpt][i] = NULL;
                    // DELETING OPERATION (Just moving all things to the left: "1 <- 2 <- 3")
                    for (size_t j = i; j < suggSymb[cckdIntInpt].size(); j++) {
                        if (suggSymb[cckdIntInpt][j + 1] != NULL) {
                            suggSymb[cckdIntInpt][j] = suggSymb[cckdIntInpt][j + 1];
                            if (suggSymb[cckdIntInpt][j + 2] == NULL)
                                suggSymb[cckdIntInpt][j + 1] = NULL;
                        }
                        else {
                            break;
                        }
                    }
                    break;
                }
                // Adding symbol to the vector<vector<char>>
                else if (suggSymb[cckdIntInpt][i] == NULL) {
                    suggSymb[cckdIntInpt][i] = cckdChrInpt;
                    break;
                }
            }
            // Writing spreadsheet of suggested symbols (Two dimensional vector)
            show_double_vector(suggSymb);
        }
    }
}

int main()
{
    menu();

    system("pause");
}