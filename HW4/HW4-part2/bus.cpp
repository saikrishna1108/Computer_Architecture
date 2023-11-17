#include <iostream>
#include "decoder.h"
#include "execute.h"
#include "globalvar.h"
class BusArbitration {
public:
    BusArbitration() : currentDevice(1) {}

    // Function to determine the winner of bus arbitration (1 or 2)
    int getArbitrationWinner() {
        int winner = currentDevice;
        currentDevice = (currentDevice == 1) ? 2 : 1; // Toggle between devices 1 and 2
        return winner;
    }
    
    // Function to get the device that can access the bus
    int arbitrate() {
        return getArbitrationWinner();
    }
int getDataFromRAM(int address) {
    return ram[address];
}

// Function to write data to RAM at a specific address
void writeDataToRAM( int data, int address) {
    ram[address] = data;
}
private:
    int currentDevice;  // Currently granted device access

};


