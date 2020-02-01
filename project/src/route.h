/**
 * @file route.h
 *
 * @Copyright 2019 3081 Staff, All rights reserved.
 */

#ifndef SRC_ROUTE_H_
#define SRC_ROUTE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <list>
#include <iostream>
#include <string>
#include <numeric>

#include "src/passenger_generator.h"
#include "src/stop.h"
#include "src/data_structs.h"


class PassengerGenerator;
class Stop;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A class for the routes that are responsible for keeping and updating
 * a set of stops.
 *
 * This class describes the behavior of the routes of the campus transit.
 * Routes are a series of stops. Each of them has an instance hold references
 * to each of its stops as well as the distances between each stop.
 *
 *
 */
class Route {
 public:
   /**
   * @brief Constructs a route with a standard name, a set of stop pointers,
   * distances between stops, number of stops on the route, and a passenger
   * generator pointer.
   *
   * @param[in] string holding a name of a created route.
   * @param[in] Stop ** holding a set of stops pointers.
   * @param[in] double * holding an array of distences between stops.
   * @param[in] int holding the total number of stops on the route
   * @param[in] PassengerGenerator * holding a passenger generator
   * pointer to generate passengers.
   */
  Route(std::string name, Stop ** stops, double * distances, int num_stops,
        PassengerGenerator *);
  /**
  * @brief Makes a fresh clone of route with the same stops.
  *
  * @return A new copy of route with the same stop references.
  */
  Route * Clone();
  /**
  * @brief Updates the route status as well as the stops on this route.
  *
  * It updates the route status as well as the stops on this route. It calls
  * \ref GenerateNewPassengers to generate new passengers.
  * It should be called in every timestep.
  *
  */
  void Update();
  /**
  * @brief Reports the status of the route to a given out stream
  * (default std::cout).
  *
  * @param[in] ostream the out stream of target the report.
  *
  */
  void Report(std::ostream &out = std::cout);
  /**
  * @brief Checks if the route is at its final stop.
  *
  * @return True if the route is at its final stop., false otherwise.
  */
  bool IsAtEnd() const;
  /**
  * @brief Changes destination_stop_ to next stop
  *
  */
  void NextStop();
  /**
  * @brief Get pointer to next stop
  *
  */
  Stop * GetDestinationStop() const;
  /**
  * @brief Get total route distance the
  *
  */
  double GetTotalRouteDistance() const;
  /**
  * @brief Get the distance bwteen two stops.
  *
  */
  double GetNextStopDistance() const;
  /**
  * @brief Get name of stop.
  *
  */
  std::string GetName();
  /**
  * @brief Get a list of stops on this route.
  *
  */
  std::list<Stop *> GetStops();
  /**
  * @brief It updates and initializes the data_struct of the route. It is called
  * inside the Update()
  */
  void UpdateRouteData();
  /**
  * @brief It gets bus data for vis_sim.
  *
  * @return route struct of current route.
  */
  RouteData GetRouteData();


 private:
  int GenerateNewPassengers();       ///< generates passengers on its route
  PassengerGenerator * generator_;
  std::list<Stop *> stops_;
  std::list<double> distances_between_;  ///< length = num_stops_ - 1
  std::string name_;
  int num_stops_;
  int destination_stop_index_;  ///< always starts at zero, no init needed
  Stop * destination_stop_;
  RouteData data_;
  ///< double trip_time_;  // derived data - total distance travelled on route
};
#endif  // SRC_ROUTE_H_
