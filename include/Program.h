/**
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
};


#endif //FEUP_AED2_PROGRAM_H
