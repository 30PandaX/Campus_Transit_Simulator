/**
 * @file local_simulator.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef SRC_LOCAL_SIMULATOR_H_
#define SRC_LOCAL_SIMULATOR_H_

#include <vector>

#include "simulator.h"

class LocalSimulator : public Simulator {
 public:
  bool Start() override;
  bool Update() override;
 private:
  int simulation_time_elapsed_;
  Passenger * pass_;
};

#endif // SRC_LOCAL_SIMULATOR_H_