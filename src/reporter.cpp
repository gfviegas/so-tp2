#include "reporter.hpp"

// Constructor
Reporter::Reporter(void) {
}

void Reporter::print(ProcessManager pm) {
    printLine();
    cout << "The current system state is as follows";
    printLine();

}

void printLine(void){
    int i;
    for (i=0; i < 80; i++) {
        cout << "*";
    }
    cout <<"\n";
}
