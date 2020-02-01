/**
 * @file random_passenger_generator.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */

#include "src/random_passenger_generator.h"

// Nothing to do here, just pass args along
RandomPassengerGenerator::RandomPassengerGenerator(std::list<double> probs,
    std::list<Stop *> stops) : PassengerGenerator(probs, stops) { }

/*
 *  GeneratePassengers uses the route's passenger generation probabilities per 
 *  stop to determine how many passengers to create. Each probability is a 
 *  double, i.e., .90 for a 90% probability of a passenger arriving at a stop 
 *  for this bus route. While the probability is > .0001 (.01%), we attempt to
 *  generate passengers. Each time, we multiply the probability by itself, 
 *  reducing the likelihood of additional passengers each time.
 *
 *  This controls for multiple passengers arriving at a given time.
 *  Once the probability drops below .0001, we end our generation cycle for the stop.
 */

int RandomPassengerGenerator::GeneratePassengers() {
  int passengers_added = 0;

  /* We don't actually know how to do this yet. We're working on it */
  
  return passengers_added;
}
