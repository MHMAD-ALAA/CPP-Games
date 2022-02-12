#include "iostream"
#include "vector"
#include "fstream"
#include "string"
#include "time.h"
using namespace std;

void printMessage(string message, bool printTop = false, bool printBottom = false) {
    if (printTop) {
        cout << "+---------------------------------+" << endl;
        cout << "|";
    } else cout << "|";
    bool front = true;
    for (int i = message.length(); i < 33; ++i) {
        if (front) {
            message = " " + message;
        } else {
            message = message + " ";
        }
        front = !front;
    }
    cout << message.c_str();

    if (printBottom) {
        cout << "|" << endl;
        cout << "+---------------------------------+" << endl;
    } else cout << "|" << endl;
}
void DrawHangman(int guessCount = 0) {
    if (guessCount >= 1)
        printMessage("|");
    else
        printMessage("");

    if (guessCount >= 2)
        printMessage("|");
    else
        printMessage("");

    if (guessCount >= 3)
        printMessage("O");
    if (guessCount == 4)
        printMessage("/  ");
    if (guessCount == 5)
        printMessage("/| ");
    if (guessCount >= 6)
        printMessage("/|\\");
    else
        printMessage("");

    if (guessCount >= 7)
        printMessage("|");
    else
        printMessage("");

    if (guessCount == 8)
        printMessage("/   ");

    if (guessCount == 9)
        printMessage("/ \\");
    else
        printMessage("");
}
void printLetters (string input, char from, char to) {
    string shown;
    for (char ch = from; ch <= to; ++ch) {
        if (input.find(ch) == string::npos) {
            shown += ch;
            shown += " ";
        } else
            shown += "  ";
    }
    printMessage(shown);
}
void printAvailableLetters(string taken) {
    printMessage("Available Letters", true, true);
    printLetters(taken, 'A', 'M');
    printLetters(taken, 'N', 'Z');
}
bool checkWin(string word, string guessed) {
    bool won = true;
    string shown = "";
    for (int i = 0; i < word.length(); ++i) {
        if (guessed.find(word[i]) == string::npos) {
            won = false;
            shown += "_ ";
        } else {
            shown += word[i];
            shown += " ";
        }
    }
    printMessage(shown, false, true);
    return won;
}
string loadRandomWord(string path) {
    int lineCount = 0;
    string word;
    vector<string> allWords;
    ifstream fileReader(path);
    if (fileReader.is_open()) {
        while (getline(fileReader, word))
            allWords.push_back(word);

        int randomLine = rand() % allWords.size();
        word = allWords.at(randomLine);
        fileReader.close();
    }
    return word;
}
int triesLeft(string word, string guessed) {
    int error = 0;
    for (int i = 0; i < guessed.length(); ++i) {
        if (word.find(guessed[i]) == string::npos) {
            error++;
        }
    }
    return error;
}
int main() {
    srand(time(NULL));
    string guesses = "";
    string wordToGuess = "";
    bool win = false;
    int tries = 0;

    wordToGuess = loadRandomWord("words.txt");

    while (tries < 10) {
        system("cls");

        printMessage("hangman is cool!", true, true);
        DrawHangman(tries);
        printAvailableLetters(guesses);
        printMessage("Guess the word", true, true);
        win = checkWin(wordToGuess, guesses);

        if (win) break;

        char anotherGuess;
        cout << ">" ; cin >> anotherGuess;
        if (guesses.find(anotherGuess) == string::npos)
            guesses += anotherGuess;

        tries = triesLeft(wordToGuess, guesses);
    }

    if (win)
        printMessage("YOU WON!", true, true);
    else
        printMessage("GAME OVER!", true, true);

    getchar();
    return 0;
}
