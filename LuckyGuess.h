#pragma once

#include "General.h"

#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

//Librarys For Random Number Generator
#include <cstdlib>
#include <ctime>

//Librarys For Print Delay
#include <thread>
#include <chrono>

//Colors
#define Red   "\033[31m"
#define Green "\033[32m"

using namespace std;

int NumberOptions[3] = {1, 2, 3};
int Streak = 0;
extern int Rebirths;
extern int RebirthCost;
int BasePay = 10;
int SlotsPay = 50;

const string Bold = "\033[1m";
const string ResetText = "\033[0m";
string ChosenNumber = "None";
string Title = R"(                                                                          
,--.                 ,--.                  ,----.                                 
|  |   ,--.,--. ,---.|  |,-. ,--. ,--.    '  .-./   ,--.,--. ,---.  ,---.  ,---.
|  |   |  ||  || .--'|     /  \  '  /     |  | .---.|  ||  || .-. :(  .-' (  .-'
|  '--.'  ''  '\ `--.|  \  \   \   '      '  '--'  |'  ''  '\   --..-'  `).-'  `)
`-----' `----'  `---'`--'`--'.-'  /        `------'  `----'  `----'`----' `----'
                             `---'                                                
)";
string RebirthTitle = R"(
                                                        ,------.
,------.        ,--.   ,--.         ,--.  ,--.         '  .--.  '
|  .--. ' ,---. |  |-. `--',--.--.,-'  '-.|  ,---.     '--' _|  |
|  '--'.'| .-. :| .-. ',--.|  .--''-.  .-'|  .-.  |     .--' __'
|  |\  \ \   --.| `-' ||  ||  |     |  |  |  | |  |     `---'
`--' '--' `----' `---' `--'`--'     `--'  `--' `--'     .---.
                                                        '---'
)";
string FAQTitle = R"(                                                                                                                      
,--.  ,--.       ,--.             ,-.,------.        ,-----.   ,-.
|  '--'  | ,---. |  | ,---.      / .'|  .---',--,--.'  .-.  '  '. \
|  .--.  || .-. :|  || .-. |    |  | |  `--,' ,-.  ||  | |  |   |  |
|  |  |  |\   --.|  || '-' '    |  | |  |`  \ '-'  |'  '-'  '-. |  |
`--'  `--' `----'`--'|  |-'      \ '.`--'    `--`--' `-----'--'.' /
                     `--'         `-'                          `-' 
)";
string Success = R"(
                                                 ,---.,---. 
 ,---.                                           |   ||   | 
'   .-' ,--.,--. ,---. ,---. ,---.  ,---.  ,---. |  .'|  .' 
`.  `-. |  ||  || .--'| .--'| .-. :(  .-' (  .-' |  | |  |  
.-'    |'  ''  '\ `--.\ `--.\   --..-'  `).-'  `)`--' `--'  
`-----'  `----'  `---' `---' `----'`----' `----' .--. .--.  
                                                 '--' '--'  
)";
string SlotsTitle = R"(                                                
                                                                          ,---.,---. 
,-----.                                    ,--------.,--.                 |   ||   |
|  |) /_  ,---. ,--,--, ,--.,--. ,---.     '--.  .--'`--',--,--,--. ,---. |  .'|  .' 
|  .-.  \| .-. ||      \|  ||  |(  .-'        |  |   ,--.|        || .-. :|  | |  |  
|  '--' /' '-' '|  ||  |'  ''  '.-'  `)       |  |   |  ||  |  |  |\   --.`--' `--'  
`------'  `---' `--''--' `----' `----'        `--'   `--'`--`--`--' `----'.--. .--.  
                                                                          '--' '--'                                                                                              
)";
string LineDividerMain = "----------------------------------------------------------------------------------------------------\n";
string LineDividerBonus = "------------------------------------------------------------------------------------";
string LineDividerRebirth = "---------------------------------------------------------------------------------\n";
string LineDividerFAQ =  "--------------------------------------------------------------------\n";
string LineDividerSuccess = "-----------------------------------------------------------\n";
string Jackpot = R"(
   $$$$$\                     $$\                            $$\     $$\ $$\ $$\
   \__$$ |                    $$ |                           $$ |    $$ |$$ |$$ |
      $$ | $$$$$$\   $$$$$$$\ $$ |  $$\  $$$$$$\   $$$$$$\ $$$$$$\   $$ |$$ |$$ |
      $$ | \____$$\ $$  _____|$$ | $$  |$$  __$$\ $$  __$$\\_$$  _|  $$ |$$ |$$ |
$$\   $$ | $$$$$$$ |$$ /      $$$$$$  / $$ /  $$ |$$ /  $$ | $$ |    \__|\__|\__|
$$ |  $$ |$$  __$$ |$$ |      $$  _$$<  $$ |  $$ |$$ |  $$ | $$ |$$\
\$$$$$$  |\$$$$$$$ |\$$$$$$$\ $$ | \$$\ $$$$$$$  |\$$$$$$  | \$$$$  |$$\ $$\ $$\
 \______/  \_______| \_______|\__|  \__|$$  ____/  \______/   \____/ \__|\__|\__|
                                        $$ |
                                        $$ |
                                        \__|
)";
string Pair = R"(
 __   __             ____       _        _      ____       _      _ 
 \ \ / /__  _   _   / ___| ___ | |_     / \    |  _ \ __ _(_)_ __| |
  \ V / _ \| | | | | |  _ / _ \| __|   / _ \   | |_) / _` | | '__| |
   | | (_) | |_| | | |_| | (_) | |_   / ___ \  |  __/ (_| | | |  |_|
   |_|\___/ \__,_|  \____|\___/ \__| /_/   \_\ |_|   \__,_|_|_|  (_)
                                                                
)";
string NoBonus = R"(
  _  _       ___                    _  __
 | \| |___  | _ ) ___ _ _ _  _ ___ (_)/ /
 | .` / _ \ | _ \/ _ \ ' \ || (_-<  _| | 
 |_|\_\___/ |___/\___/_||_\_,_/__/ (_) | 
                                      \_\
)";
string Correct = R"(
 ██████  ██████  ██████  ██████  ███████  ██████ ████████ 
██      ██    ██ ██   ██ ██   ██ ██      ██         ██    
██      ██    ██ ██████  ██████  █████   ██         ██    
██      ██    ██ ██   ██ ██   ██ ██      ██         ██    
 ██████  ██████  ██   ██ ██   ██ ███████  ██████    ██    
)";
string Wrong = R"(
██     ██ ██████   ██████  ███    ██  ██████  
██     ██ ██   ██ ██    ██ ████   ██ ██       
██  █  ██ ██████  ██    ██ ██ ██  ██ ██   ███ 
██ ███ ██ ██   ██ ██    ██ ██  ██ ██ ██    ██ 
 ███ ███  ██   ██  ██████  ██   ████  ██████  
)";
bool RebirthAction(){
    bool Choice = true;
    int Chosen;
    while (Choice == true){
        ClearScreen();
        cout << RebirthTitle << "\n"
             << LineDividerRebirth
             << "Do You Wish To Rebirth for " << RebirthCost << " Credits? (Enter A Number)\n" 
             << "--------------------------------------------------------------------------\n"
             << "1. Yes\n" << "2. No\n" << "3. Help (FaQ)\n" 
             << "--------------------------------------------------------------------------\n\n";
        cin >> Chosen;
        switch (Chosen){
            case 1:{
                ClearScreen();
                return true;
            }
            case 2:{
                ClearScreen();
                return false;
            }
            case 3:{
                string Answer = "";
                while (Answer != "done" || Answer != "Done"){
                    //Prints the FAQ Screen
                    ClearScreen();
                    cout << FAQTitle << LineDividerFAQ
                         << "What Is A Rebirth?: \n"
                         << "A Rebirth Is Something That Will Reset Your Credits And When Done, It Cannot Be Undone.\n"
                         << "In Return You Will Gain 1x More Credits, But Will Need 2x More To Rebirth Again.\n"
                         << "Now That You Know What A Rebirth Is, Type 'Done' To Go Back.\n"
                         << "Happy Gambling!!\n" << LineDividerFAQ;
                    cin >> Answer; //Taking User Input
                    //Evaluating User Input
                    if (Answer == "Done" || "done")
                        break;
                    else {
                        cout << "\nInvalid Answer";
                        PrintDots(3);
                        continue;
                    }
                }
            }
            default:
                //Connects to Choice 1,2,3 Invalid
                cout << "Invalid Answer";
                PrintDots(3);
                continue;     
        }
    }
    return false;
}

int SlotMachine (){
    int Sequence[3] = {1, 1, 1};
    ClearScreen();
    cout << SlotsTitle << LineDividerBonus << endl;
    for (int i = 1; i < 6; i++){
        for (int g = 0; g < 3; g++){
            Sequence[g] = rand()%9+1;
        }
        cout << "Number " << i << ": " << Sequence[0] << Sequence[1] << Sequence[2] << endl;
        Wait(1);
    }
    int a = Sequence[0]; int b = Sequence[1]; int c = Sequence[2];
    cout << LineDividerBonus << Bold << "\nYour Number Is: " << a << b << c << ResetText << endl;
    if (a == b && b == c){
        cout << LineDividerBonus << Jackpot << LineDividerBonus << endl;
        return 100*(Rebirths + 1);
    }
    else if (a == b || a == c || b == c){
        cout << LineDividerBonus << Pair << LineDividerBonus << endl;
        return 30*(Rebirths + 1);
    }
    else {
        cout << LineDividerBonus << NoBonus << LineDividerBonus << endl;
        return 10*(Rebirths + 1);
    }
}

void LuckyGuessGame(double& credits){
    while (ChosenNumber != ""){
        ClearScreen();
        cout << Title << "\n" << LineDividerMain;
        //Picks A Random Number In The Array
        int RandomNumber = NumberOptions[rand()%3+1];
        //Takes User Input
        if (credits >= RebirthCost)
            cout << "Enter A Number 1-3, 'Rebirth' For A Boost, Or 'Exit' To Leave\n" << LineDividerMain << "\n";
        else
            cout << "Enter A Number 1-3 Or Enter 'Exit'\n" << LineDividerMain;
        cin >> ChosenNumber;
        //Attempts To Convert To A Valid Integer Or Command
        try{
            int test = stoi(ChosenNumber);
        }
        catch (const invalid_argument& e) {
            if (ChosenNumber == "Exit" || ChosenNumber == "exit") 
                break; //Exists Game To Main Menu
            if (credits >= RebirthCost){
                if (ChosenNumber == "Rebirth" || ChosenNumber == "rebirth"){
                    if (RebirthAction() == true){
                        credits -= RebirthCost;
                        RebirthCost = RebirthCost*2;
                        Rebirths++;
                        ClearScreen();
                        cout << Success << LineDividerSuccess 
                             << "Credits: " << credits << "\nRebirths: " << Rebirths 
                             << "\nMultiplier: " << Rebirths + 1 << "\n" << LineDividerSuccess;
                        cout << "Closing";
                        PrintDots(5); continue;
                    }
                    else continue;
                }
                
            }
            cerr << "The Input '" << ChosenNumber << "' Is Invalid";
            PrintDots(3);
            continue;
        }
        catch (const out_of_range& e) {
            cerr << "The Number '" << ChosenNumber << "' Is Out Of Range";
            PrintDots(3);
            continue;
        }
        //MAIN GAME
        bool PrevCorrect = false;
        int TheNumber = stoi(ChosenNumber);
        if (TheNumber > 0 && TheNumber < 4){
            cout << LineDividerMain << "Loading"; PrintDots(3);
            if (TheNumber == RandomNumber){//Checks If Right Number Is Guessed
                int Gained = 0;
                auto StreakBoost = [](int streak){//A Lambda To Calculate Streak Multiplier
                    if (streak >= 1)
                        return static_cast<int>(pow(5, Streak));
                    else
                        return 1;
                };
                ClearScreen();
                cout << "\n" << LineDividerMain << Green << Correct << ResetText << LineDividerMain;
                cout << "YOU WON!!!";
                if (Streak >= 1){//On A Streak
                    cout << "\n------------------------------\n"
                         << "Loading Bonus"; PrintDots(4);
                    Gained = SlotMachine()*StreakBoost(Streak);
                    credits += Gained;//Adds Credits
                    Streak++;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Credits Earned: " << Gained
                         << "\nTotal Credits: " << credits
                         << "\nStreak: " << Streak
                         << "\n------------------------------"
                         << "\nHit [Enter] To Continue.";
                    if (cin.get())
                        continue;
                }
                else{//Default No Previous Streak
                  Gained = (10*(Rebirths + 1)*StreakBoost(Streak));
                  credits += Gained;//Adds Credits
                  Streak++;
                  cin.ignore(numeric_limits<streamsize>::max(), '\n');
                  cout << "\n------------------------------"
                       << "\nCredits Earned: " << Gained
                       << "\nTotal Credits: " << credits
                       << "\nStreak: " << Streak
                       << "\n------------------------------"
                       << "\nHit [Enter] To Continue.";
                    if (cin.get())
                        continue;
                  continue;
                }
            }
            else{//The Number Was Wrong
                ClearScreen();
                cout << "\n" << LineDividerMain << Red << Wrong << ResetText << LineDividerMain;
                Streak = 0;
                cout << "Try Again :(\n" << LineDividerMain << "Reloading";
                PrintDots(3);
                continue;
            }
        }
        else{
            cout << "\nThe Input '" << ChosenNumber << "' Is Invalid";
            PrintDots(3);
            continue;
        }
    }
    
    cout << "\nExiting Game";
    PrintDots(3);
    ClearScreen();
    return;
}
