  /**
   * @file stop.h
   *
   * @copyright 2019 3081 Staff, All rights reserved.
   */

#ifndef SRC_STOP_H_
#define SRC_STOP_H_


/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <list>
#include <iostream>

#include "src/bus.h"
#include "src/passenger.h"
#include "src/data_structs.h"

class Bus;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A class for the stops, that have a set of passengers generated from
 * passenger generator.
 *
 * This class describes the behavior of the stops in campus transit.
 * It represents each place a bus stops to pick up and drop off passengers.
 *
 */
class Stop {
 public:
   /**
   * @brief Constructs a stop with a stop id, latitude coordinate, and
   * longitude coordinate.
   *
   *
   * @param[in] int holding an id number
   * @param[in] double holding a latitude coordinate.
   * @param[in] double holding a longitude coordinate.
   */
    explicit Stop(int, double = 44.973723, double = -93.235365);
    /**
    * @brief Removing passengers from stop and onto a bus
    *
    * @param[in] Bus * the bus that the passengers are getting on.
    *
    */
    int LoadPassengers(Bus *);
    /**
    * @brief It returns the stop id.
    *
    * @return The id of the stop.
    */
    int GetId() const;
    /**
    * @brief passengers to the stop (from the generator)
    *
    * @param[in] Passenger * the new passenger that is going to be added.
    *
    */
    int AddPassengers(Passenger *);
    /**
    * @brief Updates the passenger at the stop.
    *
    */
    void Update();
    /**
    * @brief reports the status of the stop to a given out stream
    * (default std::cout).
    *
    * @param[in] ostream the out stream of target the report.
    *
    */
    void Report(std::ostream &out = std::cout) const;
    /**
    * @brief It gets number of passenger waitng at the stop.
    *
    * @return an integer of number of passenger.
    */
    int GetNumPassengers();
    /**
    * @brief It gets the current stop positon in Latitude and longitude
    *coordinates. It collects position data for stop data structure.
    *
    * @return position struct of current position of the bus
    */
    Position GetPosition();


 private:
    int id_;
    std::list<Passenger *> passengers_;
    // considered array, vector, queue, list
    // int passengers_present_;  // derived information - not needed?
    float longitude_;
    float latitude_;  // are we using long/lat coords?
    StopData data_;
};
#endif  // SRC_STOP_H_
