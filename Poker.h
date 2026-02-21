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
 //each card has a rank, color, suit, and ascii model. It also tracks if it is selected in hand

 /**
  * @brief operator overload so vector sort may be used with object
  * 
  * @param rhs constant reference to the card on the right side of less than
  * @return true if the rank is less than the rank of the card of the right
  */
  bool operator<(const Card& rhs) const { return rank < rhs.rank; }

 /**
  * @brief constructor for a card
  * 
  * @param Card takes the suit, rank and color of the card
  * @return creates a card object
  */
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

/**
 * @brief prints the pay table for Video Poker to terminal
 * 
 * @param 
 * @return void
 */
void printPayTable();

/**
 * @brief prints the cards in the player's hand
 * 
 * @param hand const reference to the player's hand
 * @return void
 */
void printHand(const vector<Card>& hand);

/**
 * @brief handles the actual Poker part of the game
 * 
 * @param credits reference to the player's current credit balance
 * @return void
 */
void runGame(double& credits);


/**
 * @brief checks if the player has a 4 of a kind in their hand
 * 
 * @param hand const reference to the player's hand
 * @return true if 4 of a kind, false if not
 */
bool is4ofKind      (const vector<Card>& hand);

/**
 * @brief checks if the player has a Full House in their hand
 * 
 * @param hand const reference to the player's hand
 * @return true if full house, false if not
 */
bool isFullHouse    (const vector<Card>& hand);

/**
 * @brief checks if the player has a Flush in their hand
 * 
 * @param hand const reference to the player's hand
 * @return true if the suits of the cards match, false if not
 */
bool isFlush        (const vector<Card>& hand);

/**
 * @brief checks if the player has a straight in their hand
 * 
 * @param hand const reference to the player's hand
 * @return true if the player has 5 consecutive ranked cards, false if not
 */
bool isStraight     (const vector<Card>& hand);

/**
 * @brief checks if the player has a 3 of a kind in their hand
 * 
 * @param hand const reference to the player's hand
 * @return true if 3 of a kind, false if not
 */
bool is3ofKind      (const vector<Card>& hand);

/**
 * @brief checks if the player has two pairs in their hand
 * 
 * @param hand const reference to the player's hand
 * @return true if there exists two pairs, false if not
 */
bool isTwoPair      (const vector<Card>& hand);

/**
 * @brief checks if the player has a High Pair in their hand
 * 
 * @param hand const reference to the player's hand
 * @return true if a pair of Jacks or better is in the hand, false if not
 */
bool isHighPair     (const vector<Card>& hand);

/**
 * @brief checks if the player has a Straight Flush in their hand
 * 
 * @param hand const reference to the player's hand
 * @return true if the user has both a straight and a flush (but not a royal flush), false if not
 */
bool isStraightFlush(const vector<Card>& hand);

/**
 * @brief checks if the player has a Royal Flush in their hand
 * 
 * @param hand const reference to the player's hand
 * @return true if the user has a straight of the same suit and cards 10, J Q, K, A, false if not
 */
bool isRoyalFlush   (const vector<Card>& hand);

/**
 * @brief handles the menu and voucher management before a poker game
 * 
 * @param credits reference to the player's current credit balance
 * @return void, credits returned by reference
 */

void VideoPoker(double& credits)
{
  bool gameState = true;
  int optionSelect;

  //while the poker application is running
  while(gameState) {
    cout << POKER_LOGO << "\n" << DIVIDER
    << "Select Option:\n" << DIVIDER
    << "Credits: " << credits << "\n"
    << "1. Place a Bet\n"
    << "2. Insert Voucher\n";
      if(credits > 0) //prints menu options based on if the user has credits
        cout << "3. Cash Out\n"
             << "4. Game Info\n"
             << "5. Exit Game\n";
      else
        cout << "3. Game Info\n"
             << "4. Exit Game\n";

    cout << DIVIDER << "Your Choice: ";
    cin >> optionSelect;
    cout << DIVIDER;

    switch(optionSelect) { //switch statement to control user input
      case 1: //runs the actual poker game
        if(credits < 0) {
          cout << "You don't have enough credits to make a bet!";
          break; //runGame will not work properly if the user has no credits
        }
        runGame(credits);
        break;
      case 2: //allows voucher redemption directly in the poker app
        emptyFromVoucher(credits);
        break;
      case 3: { //if the user has credits, gives the option to send credits to voucher
        if(credits > 0)
          sendToVoucher(credits);
        else { //otherwise prints the paytable
          printPayTable();
          cout << POKER_RULES;
        }
      } break;
      case 4: {
        if(credits > 0) { //prints the rules, or exits the game based on credit total
          cout << POKER_RULES;
          printPayTable();
        } else gameState = false;
      } break;
      case 5: { //exits game or gives an error depending on credit total
        if(credits > 0)
          gameState = false;
        else {
          cout << "Error: Invalid Choice\n";
          cin.clear();
          cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        }
      } break;
      default: {//if no input was matching, gives a generic error and clears cin
        cout << "Error: Invalid Choice\n";
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
      } break;
    }
  }
};

/**
 * @brief handles Poker game logic, manages deck and hand logic
 * 
 * @param credits reference to the player's current credit balance
 * @return void, credits returned by reference
 */
void runGame(double& credits) {
  //the extern variable was giving trouble, so RNG seed is redefined here
  mt19937 shuffleRNG;
  unsigned int randomSeed = static_cast<unsigned int>(time(0));
    shuffleRNG.seed(randomSeed);
  vector<Card> deck;
  vector<Card> hand;
  int pokerSelect, pokerTurn = 1;
  double bet = 0;
  string YorN;
  bool confirmPlayAgain(true), playAgain(true), validBet(false), disableWarning(false);

    for(int rank(2); rank < 14; rank++)
      deck.push_back(Card(rank, HEARTS,   RED));
    for(int rank(2); rank < 14; rank++)
      deck.push_back(Card(rank, DIAMONDS, RED));
    for(int rank(2); rank < 14; rank++)
      deck.push_back(Card(rank, CLUBS,    BLACK));
    for(int rank(2); rank < 14; rank++)
      deck.push_back(Card(rank, SPADES,   BLACK));
    //Creates the entire 52 card deck

  do {
    validBet = false;
    while(!validBet)
    { //Assumes bet is invalid to start while loop
      cout << "You have " << credits << " credits.\n"
           << "How much would you like to bet? ";
      cin >> bet;
    
      if(bet > credits)//bet validation
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
    credits -= bet;

    shuffle(deck.begin(), deck.end(), shuffleRNG); //shuffles the deck

    for(int i(0); i < 5; i++)
    {
      hand.push_back(deck.back());
      deck.pop_back();
    } //deals 5 cards from the deck into the hand

    while(pokerTurn == 1) { //turn 1 is when you have a redraw option still
      printPayTable();
      printHand(hand);
          
    if(isRoyalFlush(hand)) {
      cout << "Royal Flush\n";
    } else if(isStraightFlush(hand)) {
      cout << "Straight Flush\n";
    } else if(is4ofKind(hand)) {
      cout << "4 of a Kind\n";
    } else if(isFullHouse(hand)) {
      cout << "Full House\n";
    } else if(isFlush(hand)) {
      cout << "Flush\n";
    } else if(isStraight(hand)) {
      cout << "Straight\n";
    } else if(is3ofKind(hand)) {
      cout << "3 of a Kind\n";
    } else if(isTwoPair(hand)) {
      cout << "Two Pair\n";
    }  else if(isHighPair(hand)) {
      cout << "High Pair\n";
    }
      
      cout << DIVIDER
      << "Enter 1-5 to Select Cards to Redraw\n"
      << "Cards Selected: ";
     
      for (int i = 0; i < 5; i++) {
        if(hand[i].isSelected)
          cout << i+1 << " ";
      } //prints the number of selected cards by their order in hand
        
      cout << "\n" << DIVIDER
      << "6. Redraw\n"
      << "7. Hold\n"
      << DIVIDER
      << "Your Choice: ";
      cin >> pokerSelect;
      
      switch(pokerSelect) { //switch selection for user input
        case 1: //selects/unselects a card for 1-5
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
        case 6://if the user has no cards selected, prevents them from redrawing
          for (int i = 0; i < 5; i++)
            if(hand[i].isSelected) {
              disableWarning = true;
              pokerTurn = 2;
            }
          if(!disableWarning)
            cout << "You do not have any cards selected!";
          break;
        case 7://skips the redraw turn entirely
          pokerTurn = 3;
          break;
        default://checks for invalid input
          cout << "Error: Invalid Choice\n";
          cin.clear();
          cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
          break;
      }
    }
    
    if(pokerTurn == 2) //Redraws all selected cards
      for(int i = 0; i < 5; i++)
        if(hand[i].isSelected) {
          deck.insert(deck.begin(), hand[i]); //deck.push_front(hand[i])
          hand[i] = deck.back(); //Draws card
          deck.pop_back();
        }

    printPayTable();
    printHand(hand);
    cout << DIVIDER;
    if(isRoyalFlush(hand)) {//runs boolean functions to determine the highest tier
      bet *= 250.0;//the player won on the pay table
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
    
    credits += bet;//adds the credits won to their total, if there is any
    cout << "New Credit Balance: " << fixed << setprecision(2) << credits 
    << defaultfloat << setprecision(6) << endl
    << DIVIDER;
    
    if(credits < 0) //if the user has no credits, doesn't ask to play again
      confirmPlayAgain = false;
    else
      cout << "Play Again? Y/N\n";
    
    while(confirmPlayAgain == true) {//gets confirmation if they want to play again or not
      cout << DIVIDER << "Your Choice: ";
      cin >> YorN;
      if(YorN  == "Y" || YorN  == "y")
          confirmPlayAgain = false;
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
    } //puts the cards in the hand back in the deck and deletes the hand
    hand.clear();
    
    pokerTurn = 1;
    confirmPlayAgain = true;
    disableWarning = false;
  } while(playAgain);//if they want to play again, execute the while loop
}


void printHand(const vector<Card>& hand)
{
  for(int i(0); i < 7; i++)
  {
    for(int j(0); j < 5; j++)
      cout << hand[j].color << hand[j].ascii_model[i] << " ";
    cout << RESETCOLOR << "\n";
  }//prints the ASCII art of the cards line by line
}

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

bool is4ofKind(const vector<Card>& hand) {
  vector<Card> handCopy = hand;
  sort(handCopy.begin(), handCopy.end());
  //checks for XXXXY
  if(handCopy[0].rank == handCopy[1].rank &&
     handCopy[1].rank == handCopy[2].rank &&
     handCopy[2].rank == handCopy[3].rank)
    return true;
  //checks for XYYYY
  return handCopy[1].rank == handCopy[2].rank &&
         handCopy[2].rank == handCopy[3].rank &&
         handCopy[3].rank == handCopy[4].rank;
}

bool isFullHouse(const vector<Card>& hand) {

  vector<Card> handCopy = hand;
  sort(handCopy.begin(), handCopy.end());
  //checks for XXXYY
  if(handCopy[0].rank == handCopy[1].rank &&
     handCopy[1].rank == handCopy[2].rank &&
     handCopy[3].rank == handCopy[4].rank)
    return true;
  //checks for XXYYY
  return handCopy[0].rank == handCopy[1].rank &&
         handCopy[2].rank == handCopy[3].rank &&
         handCopy[3].rank == handCopy[4].rank;
}

bool isFlush(const vector<Card>& hand) {
  for(int i = 0; i < 4; i++)
    if(hand[i].suit != hand[i+1].suit)
      return false;
  return true;//if there is a suit that doesnt match, false
}

bool isStraight(const vector<Card>& hand) {
  vector<Card> handCopy = hand;
  sort(handCopy.begin(), handCopy.end());
  
  if(handCopy[0].rank == 2 && handCopy[1].rank == 3 
  && handCopy[2].rank == 4 && handCopy[3].rank == 5 
  && handCopy[4].rank == 14)//special case for A,2,3,4,5
    return true;
  
  for(int i = 0; i < 4; i++)
    if(handCopy[i].rank + 1 == handCopy[i+1].rank)
      continue;//checks if rank+1 matches the following rank, if not, false
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
    }//if its a straight flush with a king and ace, it must be a royal

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
}//the following patterns also flag full house and 4 of a kind
//Checks for patterns AA BB C; A BB CC; AA B CC
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
//checks for a pair, then checks if the rank of that pair is J or higher  
  return false;
}
