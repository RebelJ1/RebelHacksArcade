#pragma once

#include "General.h"

#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;

#define HEARTS   "♥"
#define DIAMONDS "◆"
#define CLUBS    "♣"
#define SPADES   "♠"

#define RED        "\033[31m"
#define BLACK      "\033[30m"
#define RESETCOLOR "\033[0m"

string POKER_LOGO = R"(                                                                              
,--.   ,--.,--.   ,--.                  ,------.        ,--.                  
 \  `.'  / `--' ,-|  | ,---.  ,---.     |  .--. ' ,---. |  |,-. ,---. ,--.--. 
  \     /  ,--.' .-. || .-. :| .-. |    |  '--' || .-. ||     /| .-. :|  .--' 
   \   /   |  |\ `-' |\   --.' '-' '    |  | --' ' '-' '|  \  \\   --.|  |    
    `-'    `--' `---'  `----' `---'     `--'      `---' `--'`--'`----'`--'    
                                                                              )";

string DIVIDER = "---------------------------------------------------------------------------------------------\n";

string POKER_RULES = R"(
After placing a bet, you are dealt a hand of 5 cards. You may select any 5 of 
those cards in your hand to return to the deck to redraw that many cards, or 
hold and keep your hand. Afterwards, your hand is judged based on the paytable
above. You receive a multiplier on your bet based on the highest tier your hand
reaches on the paytable. If your hand doesn't meet the standards of the paytable,
you lose your bet.

Royal Flush: 5 cards of the same suit, in sequential order of 10, J, Q, K, A
Straight: 5 cards in sequential order. Ace counts as rank 1 and 14, but not both
Flush: 5 cards that share the same suit
X of a kind: a number of cards that share rank (e.g. 4 Kings is 4 of a kind)
Pair: Any two cards that share rank
Full House: 3 of a kind with a pair
)";

struct Card
{
  int rank;
  string color, suit, ascii_model[7];
  bool isSelected = false;

  bool operator<(const Card& rhs) const { return rank < rhs.rank; }

  Card(int rank, string suit, string color) : rank(rank), suit(suit), color(color)
  {
    string card_letter;
    if(rank <= 9) card_letter = to_string(rank);
    else if(rank == 10) card_letter = "T";
    else if(rank == 11) card_letter = "J";
    else if(rank == 12) card_letter = "Q";
    else if(rank == 13) card_letter = "K";
    else card_letter += "A";

    ascii_model[0] = color + ".───────.";
    ascii_model[1] = color + "|"        + card_letter + "      │";
    ascii_model[2] = color + "│       │";
    ascii_model[3] = color + "|   "     + suit + "   |";
    ascii_model[4] = color + "│       │";
    ascii_model[5] = color + "│      "  + card_letter + "|";
    ascii_model[6] = color + "`───────'";
  };
};

void printPayTable();
void printHand(const vector<Card>& hand);

void runGame(double& credits);

bool is4ofKind      (const vector<Card>& hand);
bool isFullHouse    (const vector<Card>& hand);
bool isFlush        (const vector<Card>& hand);
bool isStraight     (const vector<Card>& hand);
bool is3ofKind      (const vector<Card>& hand);
bool isTwoPair      (const vector<Card>& hand);
bool isHighPair     (const vector<Card>& hand);
bool isStraightFlush(const vector<Card>& hand);
bool isRoyalFlush   (const vector<Card>& hand);


void printPayTable() {
  cout << ".──────────────────────────────────────────────────.\n"
       << "│Royal Flush-----------------------------------250x│\n"
       << "│Straight Flush---------------------------------50x│\n"
       << "│4 of a Kind------------------------------------25x│\n"
       << "│Full House-------------------------------------10x│\n"
       << "│Flush-------------------------------------------6x│\n"
       << "│Straight----------------------------------------4x│\n"
       << "│3 of a Kind-------------------------------------3x│\n"
       << "│2 Pairs-----------------------------------------2x│\n"
       << "│Pair (J or Higher)------------------------------1x│\n"
       << "'──────────────────────────────────────────────────'\n";     
}

void printHand(const vector<Card>& hand)
{
  for(int i(0); i < 7; i++)
  {
    for(int j(0); j < 5; j++)
      cout << hand[j].color << hand[j].ascii_model[i] << " ";
    cout << RESETCOLOR << "\n";
  }
}

void VideoPoker(double& credits)
{
  bool gameState = true;
  int optionSelect;

  while(gameState) {
    cout << POKER_LOGO << endl << DIVIDER
    << "Select Option:\n" << DIVIDER
    << "Credits: " << credits << endl
    << "1. Place a Bet\n"
    << "2. Insert Voucher\n";
      if(credits > 0)
        cout << "3. Cash Out\n"
             << "4. Game Info\n"
             << "5. Exit Game\n";
      else
        cout << "3. Game Info\n"
             << "4. Exit Game\n";

    cout << DIVIDER << "Your Choice: ";
    cin >> optionSelect;
    cout << DIVIDER;

    switch(optionSelect) {
      case 1:
        runGame(credits);
        break;
      case 2:
        emptyFromVoucher(credits);
        break;
      case 3: {
        if(credits > 0)
          sendToVoucher(credits);
        else {
          printPayTable();
          cout << POKER_RULES;
        }
      } break;
      case 4: {
        if(credits > 0) {
          cout << POKER_RULES;
          printPayTable();
        } else gameState = false;
      } break;
      case 5: {
        if(credits > 0)
          gameState = false;
        else {
          cout << "Error: Invalid Choice\n";
          cin.clear();
          cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        }
      }
      break;
      default: {
        cout << "Error: Invalid Choice\n";
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
      } break;
    }
  }
};

void runGame(double& credits) {
  mt19937 shuffleRNG;
  unsigned int randomSeed = static_cast<unsigned int>(time(0));
    shuffleRNG.seed(randomSeed);
  vector<Card> deck;
  vector<Card> hand;
  int pokerSelect, pokerTurn = 1;
  double bet = 0;
  string YorN;
  bool confirmPlayAgain = true, playAgain = true, validBet(false);

  do {

    while(!validBet)
    {
      cout << "You have " << credits << " credits.\n"
           << "How much would you like to bet? ";
      cin >> bet;
    
      if(bet > credits)
      {
        cout << "You don't have enough credits for that\n";
        validBet = false;
      } 
      else if(cin.fail() || bet < 0)
      {
        cout << "Invalid Bet\n";
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
      } else validBet = true;
    }

    for(int rank(2); rank < 14; rank++)
      deck.push_back(Card(rank, HEARTS,   RED));
    for(int rank(2); rank < 14; rank++)
      deck.push_back(Card(rank, DIAMONDS, RED));
    for(int rank(2); rank < 14; rank++)
      deck.push_back(Card(rank, CLUBS,    BLACK));
    for(int rank(2); rank < 14; rank++)
      deck.push_back(Card(rank, SPADES,   BLACK));

    shuffle(deck.begin(), deck.end(), shuffleRNG);

    for(int i(0); i < 5; i++)
    {
      hand.push_back(deck.back());
      deck.pop_back();
    }

    while(pokerTurn == 1) {
      printPayTable();
      printHand(hand);
      cout << DIVIDER
      << "Enter 1-5 to Select Cards to Redraw\n"
      << "Cards Selected: ";
     
      for (int i = 0; i < 5; i++) {
        if(hand[i].isSelected)
          cout << i << " ";
      }
        
      cout << "\n" << DIVIDER
      << "6. Redraw\n"
      << "7. Hold\n"
      << DIVIDER
      << "Your Choice: ";
      cin >> pokerSelect;

      switch(pokerSelect) {
        case 1:
          hand[0].isSelected = !hand[0].isSelected;
          break;
        case 2:
          hand[1].isSelected = !hand[1].isSelected;
          break;
        case 3:
          hand[2].isSelected = !hand[2].isSelected;
          break;
        case 4:
          hand[3].isSelected = !hand[3].isSelected;
          break;
        case 5:
          hand[4].isSelected = !hand[4].isSelected;
          break;
        case 6:
          pokerTurn = 2;
          break;
        case 7:
          pokerTurn = 3;
          break;
        default:
          cout << "Error: Invalid Choice\n";
          cin.clear();
          cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
          break;
      }
    }
    
    if(pokerTurn == 2)
      for(int i = 0; i < 5; i++)
        if(hand[i].isSelected) {
          deck.insert(deck.begin(), hand[i]); //deck.push_front(hand[i])
          hand[i] = deck.back();
          deck.pop_back();
        }

    printPayTable();
    printHand(hand);
    cout << DIVIDER;
    if(isRoyalFlush(hand)) {
      bet *= 250.0;
      cout << "Royal Flush! You won " << bet << " credits!\n";
    } else if(isStraightFlush(hand)) {
      bet *= 50.0;
      cout << "Straight Flush! You won " << bet << " credits!\n";
    } else if(is4ofKind(hand)) {
      bet *= 25.0;
      cout << "4 of a Kind! You won " << bet << " credits!\n";
    } else if(isFullHouse(hand)) {
      bet *= 10.0;
      cout << "Full House! You won " << bet << " credits!\n";
    } else if(isFlush(hand)) {
      bet *= 6.0;
      cout << "Flush! You won " << bet << " credits!\n";
    } else if(isStraight(hand)) {
      bet *= 4.0;
      cout << "Straight! You won " << bet << " credits!\n";
    } else if(is3ofKind(hand)) {
      bet *= 3.0;
      cout << "3 of a Kind! You won " << bet << " credits!\n";
    } else if(isTwoPair(hand)) {
      bet *= 2.0;
      cout << "Two Pair! You won " << bet << " credits!\n";
    }  else if(isHighPair(hand)) {
      bet *= 1.0;
      cout << "High Pair! You won your bet back!\n";
    } else {
      bet = 0.0;
      cout << "Game Over.\n";
    }
    
    credits += bet;
    cout << "New Credit Balance: " << fixed << setprecision(2) << credits 
    << defaultfloat << setprecision(6) << endl
    << DIVIDER << "\nPlay Again? Y/N";

    while(confirmPlayAgain == true) {
      cout << DIVIDER << "Your Choice: ";
      cin >> YorN;
      if(YorN  == "Y" || YorN  == "y") {
          confirmPlayAgain = false;
      } 
      else if (YorN == "N" || YorN  == "n") {
        confirmPlayAgain = false;
        playAgain = false; 
      }
      else {
        cout << "Error: Invalid choice\n";
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
      }
      }
    
    for(int i(0); i < 5; i++)
    {
      deck.push_back(hand.back());
      hand.pop_back();
    }
    
    hand.clear();
    pokerTurn = 1;
    
  } while(playAgain);
  return;
}


bool is4ofKind(const vector<Card>& hand) {
  vector<Card> handCopy = hand;
  sort(handCopy.begin(), handCopy.end());
  
  if(handCopy[0].rank == handCopy[1].rank &&
     handCopy[1].rank == handCopy[2].rank &&
     handCopy[2].rank == handCopy[3].rank)
    return true;

  return handCopy[1].rank == handCopy[2].rank &&
         handCopy[2].rank == handCopy[3].rank &&
         handCopy[3].rank == handCopy[4].rank;
}

bool isFullHouse(const vector<Card>& hand) {

  vector<Card> handCopy = hand;
  sort(handCopy.begin(), handCopy.end());

  if(handCopy[0].rank == handCopy[1].rank &&
     handCopy[1].rank == handCopy[2].rank &&
     handCopy[3].rank == handCopy[4].rank)
    return true;

  return handCopy[0].rank == handCopy[1].rank &&
         handCopy[2].rank == handCopy[3].rank &&
         handCopy[3].rank == handCopy[4].rank;
}

bool isFlush(const vector<Card>& hand) {
  for(int i = 0; i < 4; i++)
    if(hand[i].suit != hand[i+1].suit)
      return false;
  return true;
}

bool isStraight(const vector<Card>& hand) {
  vector<Card> handCopy = hand;
  sort(handCopy.begin(), handCopy.end());
  
  if(handCopy[0].rank == 2 && handCopy[1].rank == 3 
  && handCopy[2].rank == 4 && handCopy[3].rank == 5 
  && handCopy[4].rank == 14)
    return true;
  
  for(int i = 0; i < 4; i++)
    if(handCopy[i].rank + 1 == handCopy[i+1].rank)
      continue;
    else return false;
  return true;
}

bool isStraightFlush(const vector<Card>& hand) {
  if(!isStraight(hand))
   return false;
  return isFlush(hand);
}

bool isRoyalFlush(const vector<Card>& hand) {
  if(!isStraightFlush(hand))
   return false;

  bool aceFound(false), kingFound(false);
  for(int i = 0; i < 5; i++) {
    if(hand[i].rank == 14)
      aceFound = true;
    if(hand[i].rank == 13)
      kingFound = true;
    if(aceFound && kingFound)
      return true;
    }

  return false;
}

bool is3ofKind(const vector<Card>& hand) {  
  for(int h = 0; h < 3; h++)
    for(int i = h+1; i < 4; i++)
      for(int j = i+1; j < 5; j++)
        if(hand[h].rank == hand[i].rank && hand[i].rank == hand[j].rank)
          return true;

  return false;
}

bool isTwoPair(const vector<Card>& hand) {
if(isFullHouse(hand) || is4ofKind(hand)) {
  return false;
}
// AA BB C; A BB CC; AA B CC
  vector<Card> handCopy = hand;
  sort(handCopy.begin(), handCopy.end());

  if(handCopy[0].rank == handCopy[1].rank &&
     handCopy[2].rank == handCopy[3].rank)
    return true;
  if(handCopy[1].rank == handCopy[2].rank &&
     handCopy[3].rank == handCopy[4].rank)
     return true;
  if(handCopy[0].rank == handCopy[1].rank &&
     handCopy[3].rank == handCopy[4].rank)
    return true;
  return false;
}

bool isHighPair(const vector<Card>& hand) {
  for(int i = 0; i < 4; i++)
  for(int j = i+1; j < 5; j++)
    if(hand[i].rank == hand[j].rank)
      if(hand[i].rank > 10){
      return true;
      }
  
  return false;
}
