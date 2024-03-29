/**
 * @file local_simulator.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef SRC_LOCAL_SIMULATOR_H_
#define SRC_LOCAL_SIMULATOR_H_

#include <vector>

#include "src/simulator.h"

class LocalSimulator : public Simulator {
 public:
  explicit LocalSimulator(std::ostream *outptr = &std::cout);
  bool Start() override;
  bool Update() override;
 private:
  std::vector<int> bus_counters_;
  std::vector<int> bus_start_timings_;
  std::vector<int> time_since_last_bus_generation_;
  int simulation_time_elapsed_;
  std::ostream *out_;
};

#endif  // SRC_LOCAL_SIMULATOR_H_
