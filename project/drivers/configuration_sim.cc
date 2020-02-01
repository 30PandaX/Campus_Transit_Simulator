/**
 * @file configuration_sim.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */

#include <cstring>
#include <iostream>
#include "src/config_manager.h"
#include "src/configuration_simulator.h"

void HelpPrint();

int main(int argc, const char**argv) {
  ConfigManager configM;
  ConfigurationSimulator config_sim = ConfigurationSimulator(&configM,
                                                              argc, argv);
  int checker = config_sim.ArgsChecker();
  printf("checker = %d\n", checker);
  if (checker != 0) {
    if (checker == 1) {
      std::cout << "Number of arguments should less than 5!" << std::endl;
      HelpPrint();
      exit(1);
    }
    if (checker == 2) {
      std::cout << "At least Timing  argument is not right" << std::endl;
      HelpPrint();
      exit(1);
    }
    if (checker == 3) {
      std::cout << "At least Rounds argument is not right" << std::endl;
      HelpPrint();
      exit(1);
    }
    if (checker == 4) {
      std::cout << "At least your filename is not right!" << std::endl;
      HelpPrint();
      exit(1);
    }
  } else {
    int rounds = 50;  // Number of rounds of generation to simulate in test
    int timing = 5;

    srand(static_cast<int64_t>(time(NULL)));
    // Seed the random number generator

    // NOTE: this usage will change depending on
    //       how you build your config_sim classes
    //   E.g., how will you handle getting the length of simulation value?


      if (argc == 4) {
        timing = std::atoi(argv[3]);
        rounds = std::atoi(argv[2]);  // Number of rounds of generation to
                                     // simulate in test
      }
      if (argc == 3) {
        rounds = std::atoi(argv[2]);  // Number of rounds of generation to
                                      // simulate in test
      }
      std::vector<int> busStartTimings_;
      busStartTimings_.push_back(timing);


      if (argc == 1) {
        std::cout << "Config file name was not specified, using default now!";
        std::cout << std::endl;
        std::cout << "Rounds: " << rounds << " Bus(es) start timing: ";
        std::cout << timing << std::endl;
        if (!configM.ReadConfig("config.txt")) {
          std::cout << "Fail to open file!" << std::endl;
          HelpPrint();
          exit(1);
        }
      } else {
        if (!configM.ReadConfig(argv[1])) {
          std::cout << "Fail to open file!\n";
          HelpPrint();
          exit(1);
        }
        std::cout << "Using file: " << argv[1] << " now!!" << std::endl;
      }


      std::cout << "/*************************" << std::endl;
      std::cout << "         STARTING" << std::endl;
      std::cout << "        SIMULATION" << std::endl;
      std::cout << "*************************/" << std::endl;
      config_sim.Start(busStartTimings_);

      std::cout << "/*************************"  << std::endl;
      std::cout << "           BEGIN" << std::endl;
      std::cout << "          UPDATING" << std::endl;
      std::cout << "*************************/" << std::endl;

      for (int i = 0; i < rounds; i++) {
        config_sim.Update();
      }
      std::cout << "/*************************" << std::endl;
      std::cout << "        SIMULATION" << std::endl;
      std::cout << "         COMPLETE" << std::endl;
      std::cout << "*************************/" << std::endl;
      std::cout << "Instruction: ./build/bin/configuration_sim help";
      std::cout << std::endl;
    }


    // Check command line params for config file name

    // if filename arg present
    //   Create ConfigManager
    //   Call ReadConfig
    //   Create ConfigurationSimulator
    //   Call Start on ConfigurationSimulator
    //   Start for loop, length of simulation (where from?)
    //     Call Update on ConfigurationSimulator
    // else
    //   echo info to the user about needing a config file name

    return 0;
}

void HelpPrint() {
  std::cout << "/************************************************" << std::endl;
  std::cout << "Usage: ./build/bin/configuration_sim <config_filename> ";
  std::cout << "<numTimeSteps> <busStartTimings>";
  std::cout << std::endl;
  std::cout << "If config file name was not specified, default config.txt";
  std::cout << std::endl;
  std::cout << "If number of time steps was not specified, default 50 rounds";
  std::cout << std::endl;
  std::cout << "If bus start timing was not specified, default is 5";
  std::cout << std::endl;
  std::cout << "Note that the input arguments should be all ints, and will be";
  std::cout << std::endl;
  std::cout << "round down to ints";
  std::cout << std::endl;
  std::cout << "************************************************/" << std::endl;
}
