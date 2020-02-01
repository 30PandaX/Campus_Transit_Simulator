/**
 * @file bus.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef SRC_RTEST_CONFIGURATION_SIMULATOR_H_
#define SRC_RTEST_CONFIGURATION_SIMULATOR_H_

#include <vector>
#include <list>

#include "src/rtest_config_manager.h"

class Route;
class Bus;
class Stop;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A class to simulate the transit by using a given configuration file.
 *
 * This class describes the behavior of the simulator using a given
 * configuration file. Before starting or updating the simulation, make sure
 * to check the arguments using \ref ArgsChecker
 *
 *
 */
class RtestConfigurationSimulator {
 public:
         /**
         * @brief Constructs a ConfigurationSimulator.
         *
         *
         * @param[in] a ConfigManager pointer
         * @param[in] an int that holds number of arguments
         * @param[in] a constant string array that holds the command line
         * arguments
         *
         *
         */
        RtestConfigurationSimulator(RtestConfigManager*, int argCount,
                                                        const char** args);
        ~RtestConfigurationSimulator();
        /**
        * @brief It starts or initializes the simulation
        *
        *
        */
        void Start(const std::vector<int>&);
        /**
        * @brief It updates the simulation for each timestep.
        *
        *
        */
        void Update();
        /**
        * @brief It checks the input arguments from command line.
        *
        * It check to make sure the input arguments from the config_sim
        * driver are valid and inform the caller the type of mistake from return
        * value.
        * 0 for valid arguments. 1 for invalid number of arguments.
        * 2 for invalid timing. 3 for invalid number of rounds.
        * 4 for invalid filename.
        *
        * @return an int that indicate valid input or the type of error.
        */
        int ArgsChecker();

 private:
        int argCount_;
        const char**args_;
        RtestConfigManager* configManager_;

        std::vector<int> busStartTimings_;
        std::vector<int> timeSinceLastBus_;
        int numTimeSteps_;
        int simulationTimeElapsed_;
        std::vector<Route *> prototypeRoutes_;
        std::vector<Bus *> busses_;

        int busId = 10000;
};

#endif  // SRC_RTEST_CONFIGURATION_SIMULATOR_H_
