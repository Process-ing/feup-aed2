#include "Program.h"

using namespace std;

Program::Program() = default;

void Program::launch() {
    Dataset dataset;
    dataset.readFiles();
}
