#pragma once

/*void ClearScreen();
void Wait(float num);
void PrintDots(int amount);*/

#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>

//Librarys For Random Number Generator
#include <cstdlib>
#include <ctime>

//Librarys For Print Delay
#include <thread>
#include <chrono>

using namespace std;

void ClearScreen() {
#ifdef _WIN32
    system("cls");  // Windows
#else
    system("clear"); // Linux / macOS
#endif
}

void Wait(float num) {//Supports Decimal Second Values
    this_thread::sleep_for(chrono::milliseconds(static_cast<int>(num * 1000)));
}

void PrintDots(int amount){
    for (int i = 0; i < amount + 1; i++){
        Wait(0.7);
        cout << " ." << flush;
    }
}

void emptyFromVoucher(double& credits);
void sendToVoucher(double& credits);
