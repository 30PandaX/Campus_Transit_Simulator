/**
 * @file bus.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#include "src/configuration_simulator.h"
#include <cstring>

#include "src/bus.h"
#include "src/route.h"

ConfigurationSimulator::ConfigurationSimulator(ConfigManager* configM,
                                      int argCount, const char** args) {
    configManager_ = configM;
    argCount_ = argCount;
    args_ = args;
}

ConfigurationSimulator::~ConfigurationSimulator() {
}

void ConfigurationSimulator::Start(const std::vector<int>& busStartTimings) {
    busStartTimings_ = busStartTimings;

    timeSinceLastBus_.resize(busStartTimings_.size());
    for (int i = 0; i < static_cast<int>(timeSinceLastBus_.size()); i++) {
        timeSinceLastBus_[i] = 0;
    }

    simulationTimeElapsed_ = 0;

    prototypeRoutes_ = configManager_->GetRoutes();
    for (int i = 0; i < static_cast<int>(prototypeRoutes_.size()); i++) {
        prototypeRoutes_[i]->Report(std::cout);

        prototypeRoutes_[i]->UpdateRouteData();
    }
}

void ConfigurationSimulator::Update() {
    simulationTimeElapsed_++;
    std::cout << "~~~~~~~~~~ The time is now " << simulationTimeElapsed_;
    std::cout << "~~~~~~~~~~" << std::endl;

    std::cout << "~~~~~~~~~~ Generating new busses if needed ";
    std::cout << "~~~~~~~~~~" << std::endl;

    // Check if we need to generate new busses
    for (int i = 0; i < static_cast<int>(timeSinceLastBus_.size()); i++) {
        // Check if we need to make a new bus
        if (0 >= timeSinceLastBus_[i]) {
            Route * outbound = prototypeRoutes_[2 * i];
            Route * inbound = prototypeRoutes_[2 * i + 1];

            busses_.push_back(new Bus(std::to_string(busId), outbound->Clone(),
                                      inbound->Clone(), 60, 1));
            busId++;

            timeSinceLastBus_[i] = busStartTimings_[i];
        } else {
            timeSinceLastBus_[i]--;
        }
    }

    std::cout << "~~~~~~~~~ Updating busses ";
    std::cout << "~~~~~~~~~" << std::endl;

    // Update busses
    for (int i = static_cast<int>(busses_.size()) - 1; i >= 0; i--) {
        busses_[i]->Update();

        if (busses_[i]->IsTripComplete()) {
            busses_.erase(busses_.begin() + i);
            continue;
        }

        busses_[i]->Report(std::cout);
    }

    std::cout << "~~~~~~~~~ Updating routes ";
    std::cout << "~~~~~~~~~" << std::endl;
    // Update routes
    for (int i = 0; i < static_cast<int>(prototypeRoutes_.size()); i++) {
        prototypeRoutes_[i]->Update();
        prototypeRoutes_[i]->Report(std::cout);
    }
}

int ConfigurationSimulator::ArgsChecker() {
  if (argCount_ > 4 || (argCount_== 2 && std::strcmp(args_[1], "help") == 0)) {
    return 1;  // execeed max args
  } else {
    if (argCount_ > 1) {
      int timing;
      int rounds;
      std::string filename = args_[1];

      if (argCount_ == 4) {
        timing = std::atoi(args_[3]);
        rounds = std::atoi(args_[2]);
        if (filename.find(".txt") == std::string::npos)
          return 4;
        if (rounds <= 0)
          return 3;  // rounds not right
        if (timing <= 0)
          return 2;  // timing not right
      }

      if (argCount_ == 3) {
        rounds = std::atoi(args_[2]);  // Number of rounds of generation
                                      // to simulate in test
        if (filename.find(".txt") == std::string::npos)
          return 4;
        if (rounds <= 0)
          return 3;
      }

      if (argCount_ == 2) {
        if (filename.find(".txt") == std::string::npos)
          return 4;
      }
    }
    return 0;  // success
  }
}
