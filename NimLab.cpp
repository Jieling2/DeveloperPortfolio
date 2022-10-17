#include <iostream>
#include <time.h>
#include <string>

using namespace std;
void gameStart(bool);
void humanTurn(int &, string, bool &);
void computerTurn(int &, bool &);
bool getChoice();
void gameEnd(bool, string, bool &, int);
void printRules();
void sayGoodbye();
int numGetter(int &);
string switchTurns(string);
string coinFlip();
void playOptions();

int main(){
   cout << "Hello!" << endl << "Welcome to the game of NIM!" << endl << "Do you know the rules? (Y/N)" << endl;
   if (!getChoice())
      printRules();
   playOptions();
   }

void gameStart(bool playerVsPlayer){
   srand(time(0));
   int numStones = rand()%13 +12;
   cout << "Starting a new game. There are " << numStones << " stones in the pile." << endl;
   if (playerVsPlayer){
      cout << "Player 1 goes first. Do you want to flip a coin for who's player 1? (Y/N)" << endl;
      if (getChoice()){
         cout << coinFlip() << endl;
      }
      humanTurn(numStones, "Player 1", playerVsPlayer);
   }
   else{
   cout << "Would you like to go first? (Y/N)" << endl;
   getChoice() ? humanTurn(numStones, "Your", playerVsPlayer) : computerTurn(numStones, playerVsPlayer);
   }
}

void humanTurn(int &numStones, string whoseTurn, bool &playerVsPlayer){
   int turnStones;
   cout << whoseTurn << (playerVsPlayer ? "\'s " : " ") << "turn. There are " << numStones << " stones left. How many stones do you take?" << endl;
   numStones -= numGetter(numStones);
   if (numStones == 0){
      gameEnd(false, switchTurns(whoseTurn), playerVsPlayer, numStones);
   }
   else if (numStones == 1){
      gameEnd(false, switchTurns(whoseTurn), playerVsPlayer, numStones);
   }
   else if (playerVsPlayer){
      humanTurn(numStones, switchTurns(whoseTurn), playerVsPlayer);
   }
   else{
      computerTurn(numStones, playerVsPlayer);
   }
}

void computerTurn(int &numStones, bool &playerVsPlayer){
   cout << "You left " << numStones << " stones in the pile. ";
   if (numStones == 1){
      numStones -= 1;
      cout << "I take 1 stone." << endl;
   }
   else if (numStones%4 == 1){
      int randStones = rand()%3+1;
      numStones -= randStones;
      cout << "I take " << randStones << " stones." << endl;
   }
   else {
      for (int i = 1; i <= 3; i++){
         if ((numStones - i)%4 == 1){
            numStones -= i;
            cout << " I take " << i  << " stones." << endl;
            break;
         }
      }
   }
   (numStones == 0) ? gameEnd(true, "Congratulations! You", playerVsPlayer, numStones) : humanTurn(numStones, "Your", playerVsPlayer);
}

bool getChoice(){
   char usrChoice;
   string usrInput;
   cin >> usrInput;
   usrChoice = usrInput[0];
   return tolower(usrChoice) == 121 ? true : false;
}

void gameEnd(bool youWon, string whoseTurnGE, bool &playerVsPlayer, int numStones){
   if (numStones == 1){
      cout << " There is only 1 stone left in the pile. " << whoseTurnGE << " take(s) the last stone;" << endl;
   }
   if (youWon)
      cout << whoseTurnGE << " won." << endl;
   else
      cout << " I won this time." << endl;
   cout << "Would you like to play again? (Y/N)" << endl;
   getChoice() ? gameStart(playerVsPlayer) : sayGoodbye();
}

void printRules(){
   cout << "NIM is a two-person game that is played with a pile of stones. Players alternate taking turns, taking 1-3 stones from the pile each turn. The person who takes the last stone loses." << endl;
}

void sayGoodbye(){
   cout << "Goodbye!" << endl;
}

void playOptions(){
   int usrNumber;
   cout << "Select the option you'd like to play." << endl;
   cout << "1. Player vs. Player" << endl;
   cout << "2. Player vs. Computer" << endl;
   cout << "3. Quit" << endl;
   cin >> usrNumber;
   if (usrNumber == 1){
      const bool playerVsPlayer = true;
      gameStart(playerVsPlayer);
   }
   else if (usrNumber == 2){
      const bool playerVsPlayer = false;
      gameStart(playerVsPlayer);
   }
   else if (usrNumber == 3){
      sayGoodbye();
   }
   else {
      cout << "Invalid Number. Please choose again." << endl;
      playOptions();
   }
}
int numGetter(int &numStones){
   int turnStones;
   cin >> turnStones;
   while (turnStones > 3 || turnStones < 1){
      if (numStones >= 3){
         cout << "Invalid Number. Please enter a number between 1 and 3." << endl;
         cin >> turnStones;
      }
      else {
         cout << "Invalid number. There are only " << numStones << " stones left in the pile." << endl;
         cin >> turnStones;
      }
   }
   while (turnStones > numStones){
      cout << "Invalid number. There are only " << numStones << " stones left in the pile." << endl;
      cin >> turnStones;
   }
   return turnStones;
}

string switchTurns(string whoseTurn){
 return (whoseTurn == "Player 1") ? "Player 2" : "Player 1";

}

string coinFlip(){
   return (rand()%2) ? "Heads." : "Tails.";
}
