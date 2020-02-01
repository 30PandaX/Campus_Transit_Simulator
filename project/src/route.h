/**
 * @file route.h
 *
 * @Copyright 2019 3081 Staff, All rights reserved.
 */
 
#ifndef SRC_ROUTE_H_
#define SRC_ROUTE_H_

#include <list>
#include <iostream>
#include <string>

#include "./stop.h"

class Stop;

class Route {
 public:
  Route(std::string name, Stop ** stops, double * distances, int num_stops);
  void Update();
  void Report();
 private:
  std::list<Stop *> stops_;
  std::list<double> distances_between_;  // length = num_stops_ - 1
  std::string name_;
  int num_stops_;
  // double trip_time_; // derived data - total distance travelled on route
};
#endif  // SRC_ROUTE_H_

