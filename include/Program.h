/**
 * @file
 * Header file for class Program.
 */

#ifndef FEUP_AED2_PROGRAM_H
#define FEUP_AED2_PROGRAM_H


#include "Dataset.h"

class Program {
  public:
    Program();

    void launch();
  private:
    Dataset dataset_;

    void displayMainMenu();
    int receiveOption(int max);
    static void waitForEnter();
    static void clearScreen();
    void leave();
};


#endif //FEUP_AED2_PROGRAM_H
