#include <iostream>
#include <string>
#include <fstream>
#include <limits>
using namespace std;

string TITLE_LOGO = R"(  __  __      _ _   _      ___                 __   ___    _           ___     _           _ 
 |  \/  |_  _| | |_(_)___ / __|__ _ _ __  ___  \ \ / (_)__| |___ ___  | _ \___| |_____ _ _| |
 | |\/| | || | |  _| |___| (_ / _` | '  \/ -_)  \ V /| / _` / -_) _ \ |  _/ _ \ / / -_) '_|_|
 |_|  |_|\_,_|_|\__|_|    \___\__,_|_|_|_\___|   \_/ |_\__,_\___\___/ |_| \___/_\_\___|_| (_)
                                                                                             
)";

string GAME_SELECT_LOGO = R"(   ___                  ___      _        _   
  / __|__ _ _ __  ___  / __| ___| |___ __| |_ 
 | (_ / _` | '  \/ -_) \__ \/ -_) / -_) _|  _|
  \___\__,_|_|_|_\___| |___/\___|_\___\__|\__|
                                              )";

string LINE_DIVIDER = "---------------------------------------------------\n";

void selectVoucher(double& credits) {

}

void loadVoucher(double& credits) {

}

void cashOut(double& credits) {

}

void runLuckyGuess(double& credits) {

}

void runVideoPoker(double& credits) {

}


int main() {

bool programState = true, gameState = true, gameSelect = true, confirmation;
int choice, gameChoice;
double credits = 200;
string yesOrNo;

while (programState == true) {

cout << TITLE_LOGO << LINE_DIVIDER 
<< "Select Option:\n" << LINE_DIVIDER;

cout << "1. Insert Voucher\n" 
<< "2. Start Game\n";
if(credits > 0) {
cout << "3. Cash Out\n";
cout << "4. Exit\n";
} else {
cout << "3. Exit\n";
}
cout << LINE_DIVIDER << "Your Choice: ";

cin >> choice;

cout << LINE_DIVIDER;

switch (choice) {
  case 1: 
  {
    selectVoucher(credits);
    loadVoucher(credits);
  } break;

  case 2:
  {
    gameSelect = true;
    while(gameSelect) {
    
    cout << GAME_SELECT_LOGO << endl
    << "Play Lucky Guess to Earn Credits!\n"
    << "Use Credits to Play Other Games!\n"
    << "Credits: " << credits << endl
    << LINE_DIVIDER
    << "Select Your Game:\n"
    << LINE_DIVIDER
    << "1. Lucky Guess\n"
    << "2. Video Poker\n"
    << "3. Go Back\n"
    << LINE_DIVIDER << "Your Choice: ";
    cin >> gameChoice;
    cout << LINE_DIVIDER;

    switch(gameChoice) {
      case 1: 
        runLuckyGuess(credits);
        gameSelect = false;
        break;
      case 2:
        runVideoPoker(credits);
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
    cashOut(credits);
    credits = 0;
    } else { 
    programState = false;
    }
  
  } break;

  case 4: 
  {
    if(credits > 0) {
      confirmation = true;
      while(confirmation) {
        cout << "Are you sure you want to exit? You have unredeemed credits! (Y/N)\n"
        << LINE_DIVIDER
        << "Your Choice: "
        << LINE_DIVIDER;
        cin >> yesOrNo;
        if(yesOrNo == "Y" || yesOrNo == "y") {
          programState = false;
          confirmation = false;
        } else if (yesOrNo == "N" || yesOrNo == "n") {
          confirmation = false;
        } else {
          cout << "Error: Invalid choice\n";
          cin.clear();
          cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
      }
    }
    } else {
    cout << "Error: Invalid choice\n";
    }
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
