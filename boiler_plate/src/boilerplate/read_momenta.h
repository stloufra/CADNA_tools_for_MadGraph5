#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

struct FourMomentum {
    double p[4];
};

struct Sim_params {
    std::vector<FourMomentum> momenta;
    double matrixElement;
    int matrixElementPrecision = -1;
    int event_num = 0;

    void printMomenta() const {
        std::cout << "Number of 4-momenta: " << momenta.size() << std::endl;
        for (size_t i = 0; i < momenta.size(); ++i) {
            const FourMomentum& momentum = momenta[i];
            std::cout << "4-Momentum " << i + 1 << ": ("
                      << std::setprecision(14)
                      << std::scientific
                      << momentum.p[0] << ", "
                      << momentum.p[1] << ", "
                      << momentum.p[2] << ", "
                      << momentum.p[3] << ")" << std::endl;
        }
    }
};

inline std::vector<Sim_params>
readSim_paramsFromFile(const std::string &filename, const int precision_tresh = 3)
{
    std::vector<Sim_params> allEvents;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return allEvents;
    }

    std::string line;
    Sim_params currentEvent;
    bool inMomentaSection = true;

    while (std::getline(file, line)) {
        if (line.find("Momenta: for event") != std::string::npos) {
            if (!inMomentaSection && (currentEvent.matrixElementPrecision != -1 || !currentEvent.momenta.empty())) {
                if (currentEvent.matrixElementPrecision < precision_tresh)
                    allEvents.push_back(currentEvent);
                currentEvent = Sim_params();
            }
            inMomentaSection = false;

            size_t pos = line.find("event");
            if (pos != std::string::npos) {
                currentEvent.event_num = std::stoi(line.substr(pos + 5));
            }
            continue;
        }

        if (line.find("Matrix element =") != std::string::npos) {
            size_t pos = line.find('=');
            if (pos != std::string::npos)
                currentEvent.matrixElement = std::stod(line.substr(pos + 1));
            continue;
        }

        if (line.find("Matrix element number of sig dig =") != std::string::npos) {
            size_t pos = line.find('=');
            if (pos != std::string::npos)
                currentEvent.matrixElementPrecision = std::stoi(line.substr(pos + 1));
            continue;
        }
    }

    // Push last event if valid
    if (currentEvent.matrixElementPrecision < precision_tresh)
        allEvents.push_back(currentEvent);

    file.clear();
    file.seekg(0, std::ios::beg);

    int event_num = 0;
    int particle = 0;
    bool rightMomenta = false;

    while (std::getline(file, line)) {
        if (line.find("Momenta: for event") != std::string::npos) {
            break;
        }

        if (line.find("Momenta casting for event") != std::string::npos) {
            rightMomenta = false;
            size_t pos = line.find("event");
            if (pos != std::string::npos) {
                pos += 5; // skip "event"
                while (pos < line.size() && !std::isdigit(line[pos])) pos++;
                if (pos < line.size()) {
                    currentEvent.event_num = std::stoi(line.substr(pos));
                }
                if (event_num < static_cast<int>(allEvents.size()) &&
                    currentEvent.event_num == allEvents[event_num].event_num) {
                    rightMomenta = true;
                }
            }
            particle = 0;
            if (rightMomenta) event_num++;
            continue;
        }

        if (rightMomenta) {

            if (!line.empty() && (std::isdigit(line[3]) || std::isdigit(line[4]))) {
                //std::cout << "Event number: " << currentEvent.event_num << std::endl;
                std::istringstream iss(line);
                int idx;
                FourMomentum m;
                if (iss >> idx >> m.p[0] >> m.p[1] >> m.p[2] >> m.p[3])
                    int idx = event_num - 1;
                if (idx >= 0 && idx < static_cast<int>(allEvents.size()))
                {
                    int idx = event_num - 1;
                    if (idx >= 0 && idx < static_cast<int>(allEvents.size())) {
                        allEvents[idx].momenta.push_back(m);
                    }
                    else
                    {
                        std::cout << "Error: idx out of bounds" << std::endl;
                    }
                }
            }
        }
    }

    return allEvents;
}

 //int main(int arg, char** argv) {
 //    const std::string filename = argv[1];
 //    std::vector<Sim_params> simParamsList = readSim_paramsFromFile(filename);

 //    // Display the extracted simulation parameters
 //    for (size_t i = 0; i < simParamsList.size(); ++i) {
 //        std::cout << "Event number: " << simParams.event_num << std::endl;
 //        Sim_params& simParams = simParamsList[i];
 //        std::cout << "Set " << i + 1 << ":" << std::endl;
 //        simParams.printMomenta();
 //        std::cout << "Matrix element: " << simParams.matrixElement << " GeV^-2" << std::endl;
 //        std::cout << "Matrix element precision: " << simParams.matrixElementPrecision << " sig dig" << std::endl;
 //        std::cout << std::endl;
 //    }

 //    return 0;
 //}
