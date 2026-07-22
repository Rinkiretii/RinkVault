#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <filesystem>
#include "src/json.hpp"

using json = nlohmann::json;
namespace fs = std::filesystem;

const std::string DATA_FILE = "data.json";

json loadData() {
    json data;
    if (fs::exists(DATA_FILE)) {
        std::ifstream in(DATA_FILE);
        if (in) {
            try {
                in >> data;
            } catch (const json::parse_error&) {
                std::cerr << "Warning: data.json was invalid, starting fresh.\n";
                data = json::object();
            }
        }
    }
    return data;
}

void saveData(const json& data) {
    std::ofstream out(DATA_FILE);
    out << data.dump(4);
}

double promptNumber(const std::string& prompt) {
    double value;
    std::cout << prompt;
    while (!(std::cin >> value)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Please enter a valid number: ";
    }
    return value;
}

int main() {
    json data = loadData();

    if (!data.contains("goal")) {
        double goal = promptNumber("Welcome! Enter your goal: ");
        data["goal"] = goal;
        data["accumulated"] = 0.0;
        saveData(data);
        std::cout << "Goal saved to " << DATA_FILE << ".\n";
    }

    std::cout << "\nCommands:\n"
              << "  goal  - set a new goal number\n"
              << "  add   - set the accumulated number\n"
              << "  show  - print current goal and est\n"
              << "  exit  - quit the program\n";

    std::string command;
    while (true) {
        std::cout << "\n> ";
        if (!(std::cin >> command)) break;

        if (command == "goal") {
            double goal = promptNumber("Enter new goal: ");
            data["goal"] = goal;
            saveData(data);
            std::cout << "Goal updated to " << goal << ".\n";
        } else if (command == "add") {
            double amount = promptNumber("Enter amount to add to accumulated: ");
            double accumulated = data.value("accumulated", 0.0) + amount;
            data["accumulated"] = accumulated;
            saveData(data);
            std::cout << "accumulated is now " << accumulated << ".\n";
        } else if (command == "show") {
            double goal = data.value("goal", 0.0);
            double accumulated = data.value("accumulated", 0.0);
            std::cout << "goal: " << goal << ", accumulated: " << accumulated;
            if (goal != 0.0) {
                double percent = (accumulated / goal) * 100.0;
                std::cout << " (" << percent << "%)";
            }
            std::cout << "\n";
        } else if (command == "exit") {
            break;
        } else {
            std::cout << "Unknown command. Use: goal | add | show | exit\n";
        }
    }

    return 0;
}