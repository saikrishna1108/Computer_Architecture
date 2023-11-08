#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

struct Event {
    int clockCycle;
    std::string instruction;
};

int main() {
    int value = 160;
    int clockCycle = 0;
    std::string l = " ld ";
    std::vector<Event> eventList;
    std::cout << std::left << std::setw(12) << "Clock Cycle"
              << std::setw(12) << "Fetch"
              << std::setw(12) << "Decode"
              << std::setw(12) << "Execute"
              << std::setw(12) << "Store"
              << std::setw(12) << "Value" << "\n";

    while (value > 0) {
        std::string instructions[] = {"ld", "add", "sd", "addi", "bne"};

        for (int i = 0; i < 4; i++) {
            for (int stage = 1; stage <= 4; stage++) {
                clockCycle++;
                std::string instruction = instructions[i];
                std::string n_instruction = instructions[i + 1];

                Event event;
                event.clockCycle = clockCycle;
                event.instruction = instruction;
                eventList.push_back(event);

                if (stage == 1) {
                    std::cout << std::left << std::setw(12) << clockCycle
                              << std::setw(12) << instruction
                              << std::setw(12) << "N/A"
                              << std::setw(12) << "N/A"
                              << std::setw(12) << "N/A"
                              << std::setw(12) << "Value: " << value << "\n";
                } else if (stage == 2) {
                    std::cout << std::left << std::setw(12) << clockCycle
                              << std::setw(12) << n_instruction
                              << std::setw(12) << instruction
                              << std::setw(12) << "N/A"
                              << std::setw(12) << "N/A"
                              << std::setw(12) << "Value: " << value << "\n";
                } else if (stage == 3) {
                    std::cout << std::left << std::setw(12) << clockCycle
                              << std::setw(12) << n_instruction
                              << std::setw(12) << "N/A"
                              << std::setw(12) << instruction
                              << std::setw(12) << "N/A"
                              << std::setw(12) << "Value: " << value << "\n";
                } else if (stage == 4) {
                    if (instruction == "addi") {
                        value = value - 8;
                    }
                    std::cout << std::left << std::setw(12) << clockCycle
                              << std::setw(12) << n_instruction
                              << std::setw(12) << "N/A"
                              << std::setw(12) << "N/A"
                              << std::setw(12) << instruction
                              << std::setw(12) << "Value: " << value << "\n";
                }
            }
        }
        clockCycle++;
        Event haltEvent;
        haltEvent.clockCycle = clockCycle;
        haltEvent.instruction = "stall";
        eventList.push_back(haltEvent);

        std::cout << std::left << std::setw(12) << "Clock Cycle"
                  << std::setw(12) << clockCycle
                  << std::setw(12) << "stall"
                  << "\n";
        if (value == 0) {
            l = " N/A  ";
        }
        for (int stage = 1; stage <= 4; stage++) {
            clockCycle++;
            Event bneEvent;
            bneEvent.clockCycle = clockCycle;
            bneEvent.instruction = "bne";
            eventList.push_back(bneEvent);

            if (stage == 1) {
                std::cout << std::left << std::setw(12) << clockCycle
                          << std::setw(12) << "bne"
                          << std::setw(12) << "N/A"
                          << std::setw(12) << "N/A"
                          << std::setw(12) << "N/A"
                          << std::setw(12) << "Value: " << value << "\n";
            } else if (stage == 2) {
                std::cout << std::left << std::setw(12) << clockCycle
                          << std::setw(12) << l
                          << std::setw(12) << "bne"
                          << std::setw(12) << "N/A"
                          << std::setw(12) << "N/A"
                          << std::setw(12) << "Value: " << value << "\n";
            } else if (stage == 3) {
                std::cout << std::left << std::setw(12) << clockCycle
                          << std::setw(12) << l
                          << std::setw(12) << "N/A"
                          << std::setw(12) << "bne"
                          << std::setw(12) << "N/A"
                          << std::setw(12) << "Value: " << value << "\n";
            } else if (stage == 4) {
                std::cout << std::left << std::setw(12) << clockCycle
                          << std::setw(12) << l
                          << std::setw(12) << "N/A"
                          << std::setw(12) << "N/A"
                          << std::setw(12) << "bne"
                          << std::setw(12) << "Value: " << value << "\n";
            }
        }
    }

    // Print the event list
    std::cout << "Event List:\n";
    for (const Event& event : eventList) {
        std::cout << "ClockCycle-" << event.clockCycle << " : " << event.instruction << "\n";
    }

    return 0;
}

