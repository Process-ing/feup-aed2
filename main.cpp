/**
 * @file
 * @brief Main file of project.
 */

#include <iostream>
#include "Program.h"

using namespace std;

int main() {
    try {
        Program().launch();
    } catch (const exception& e) {
        cerr << "An error occurred: " << e.what();
        return 1;
    }
    return 0;
}
