#include "LuckyGuess.h"
#include "Poker.h"
#include "General.h"

#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <cstdlib>
#include <cmath>

using namespace std;

int Rebirths = 0;
int RebirthCost = 250;

string TITLE_LOGO = R"(
  __  __      _ _   _      ___                 __   ___    _           ___     _           _ 
 |  \/  |_  _| | |_(_)___ / __|__ _ _ __  ___  \ \ / (_)__| |___ ___  | _ \___| |_____ _ _| |
 | |\/| | || | |  _| |___| (_ / _` | '  \/ -_)  \ V /| / _` / -_) _ \ |  _/ _ \ / / -_) '_|_|
 |_|  |_|\_,_|_|\__|_|    \___\__,_|_|_|_\___|   \_/ |_\__,_\___\___/ |_| \___/_\_\___|_| (_)
                                                                                             
)";

string GAME_SELECT_LOGO = R"(
   ___                  ___      _        _   
  / __|__ _ _ __  ___  / __| ___| |___ __| |_ 
 | (_ / _` | '  \/ -_) \__ \/ -_) / -_) _|  _|
  \___\__,_|_|_|_\___| |___/\___|_\___\__|\__|
                                              )";

string LINE_DIVIDER = "---------------------------------------------------------------------------------------------\n";


int main() {
  
  unsigned int randomSeed = static_cast<unsigned int>(time(0));
  mt19937 shuffleRNG;
  srand(randomSeed);
  shuffleRNG.seed(randomSeed);

  bool programState = true, gameSelect = true, confirmation;
  int choice, gameChoice;
  double credits = 200;
  string yesOrNo;

  while (programState) {
    ClearScreen();
    cout << TITLE_LOGO << LINE_DIVIDER 
    << "Select Option:\n" << LINE_DIVIDER;

    cout << "1. Insert Voucher\n" 
         << "2. Start Game\n";
    if(credits > 0)
      cout << "3. Cash Out\n"
           << "4. Exit\n";
    else cout << "3. Exit\n";

    cout << LINE_DIVIDER << "Your Choice: ";
    cin >> choice;
    cout << LINE_DIVIDER;

    switch (choice) {
      case 1: 
        emptyFromVoucher(credits);
        break;
      case 2:
      {
        gameSelect = true;
        while(gameSelect) {
          ClearScreen();
          cout << GAME_SELECT_LOGO << "\n"
            << "Play Lucky Guess to Earn Credits!\n"
            << "Use Credits to Play Other Games!\n"
            << "Credits: " << credits << "\n"
            << LINE_DIVIDER
            << "Select Your Game:\n"
            << LINE_DIVIDER
            << "1. Lucky Guess\n"
            << "2. Video Poker\n"
            << "3. Go Back\n"
            << LINE_DIVIDER << "Your Choice (A Number): ";
          cin >> gameChoice;
          cout << LINE_DIVIDER;

          switch(gameChoice) {
            case 1:
              LuckyGuessGame(credits);
              gameSelect = false;
              break;
            case 2:
              VideoPoker(credits);
              gameSelect = false;
              break;
            case 3:
              gameSelect = false;
              break;
          default:
              cout << "Error: Invalid Choice\n";
              cin.clear();
              cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
              break;
          }
        }
      } break;

      case 3:
      {
        if(credits > 0) {
          sendToVoucher(credits);
          credits = 0;
        } else programState = false;
      } break;

      case 4: 
      {
        if(credits > 0) {
          confirmation = true;
          while(confirmation) {
            cout << "Are you sure you want to exit? You have unredeemed credits! (Y/N)\n"
            << LINE_DIVIDER << "Your Choice: ";
            cin >> yesOrNo;
            if(yesOrNo == "Y" || yesOrNo == "y") {
              programState = false;
              confirmation = false;
            } 
            else if (yesOrNo == "N" || yesOrNo == "n")
              confirmation = false; 
            else {
              cout << "Error: Invalid choice\n";
              cin.clear();
              cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            }
          }
        } else cout << "Error: Invalid choice\n";
      } break;

      default:
        cout << "Error: Invalid choice\n";
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        break;
    }
  }

  return 0;
}

void emptyFromVoucher(double& credits) {

  ifstream voucherFile("voucher.txt");
  string creditString;
  double newCredits;

  if(!voucherFile.is_open()) {
    cout << "voucher.txt was not found. Returning to menu.\n"
    << LINE_DIVIDER;
    return;
  }

  if(voucherFile >> newCredits) {
    credits += newCredits;
    cout << "Added " << newCredits << " credits to your balance!\n";
  } else {
    cout << "Invalid voucher data found. Resetting voucher balance to 0.00.\n"
    << LINE_DIVIDER;
  }

  voucherFile.close();

  ofstream voucherFileOutput("voucher.txt");
  voucherFileOutput << "0.00";
  voucherFileOutput.close(); 

}

void sendToVoucher(double& credits) {

ifstream voucherFile("voucher.txt");
double newCredits;
if(voucherFile.is_open()) {

if(voucherFile >> newCredits) {
 credits += newCredits;
}

voucherFile.close();
}

ofstream voucherFileOutput("voucher.txt");

credits = floor(credits * 100.00) / 100.00;
voucherFileOutput << fixed << setprecision(2) << credits;
credits = 0.00;
voucherFileOutput.close();
cout << "Game balance cashed out and written to voucher!\n"
<< LINE_DIVIDER;

}
