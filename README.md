# RinkVault

Simple C++ application for tracking savings and progress toward a goal.

About

RinkVault works like a digital bank.

You set a goal, add your current amount, and the program calculates your progress percentage.

Example:

Goal: 1000
Current: 250
Progress: 25%

Data Storage

The program automatically creates and uses a "data.json" file to store information.

Requirements

- C++17 or newer
- JSON library (see /scr)

Build

Compile the source files:

g++ main.cpp -o RinkVault

License

This project is licensed under the MIT License.

See "LICENSE" for more information.

## Third-party libraries
This project uses the folllowing third-party library:
- **nlohmann/json**
  - Author: Niels Lohmann
  - License: MIT
  - Repository: https://github.com/nlohmann/json

See 'licenses/nlohmann_json_LICENSE.txt' for the full license test.