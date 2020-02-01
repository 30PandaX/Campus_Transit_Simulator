/**
 * @file bus.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef SRC_BUS_H_
#define SRC_BUS_H_


/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <list>
#include <string>

#include "src/passenger.h"
#include "src/route.h"
#include "src/stop.h"
#include "src/data_structs.h"


class PassengerUnloader;
class PassengerLoader;
class Route;
class Stop;


/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A class for buses that are responsible for moving, picking up and
 * droping off passengers.
 *
 * This class describes the behavior of the buses operating on the transit.
 * Buses have a speed (a distance to move per time unit) and a max capacity
 * for passengers. Every Bus keeps track of the passengers on that Bus.
 *
 *
 */
class Bus {
 public:
   /**
   * @brief Constructs a bus with a outbound \ref Route, inbound \ref Route,
   * capacity, name, and speed.
   *
   *
   * @param[in] string holding a name of a created bus.
   * @param[in] Route* holding an outbound route.
   * @param[in] Route* holding an inbound route.
   * @param[in] int holding a capacity that a bus can load.
   * @param[in] double holding a speed of a created bus.
   *
   */
  Bus(std::string name, Route * out, Route * in, int capacity = 60,
                                                 double speed = 1);
   /**
   * @brief Loads a \ref Passenger on to the bus.
   *
   * @param[in] Passenger * holding a pointer of a Passenger that is going to
   * be loaded.
   *
   * @return True if the given passenger is loaded successfully,
   * false ohterwise.
   */
  bool LoadPassenger(Passenger *);  // returning revenue delta
  /**
  *
  * @brief Unloads passengers when the bus arriving at their destination.
  *
  * @return the number of passengers that are unloaded successfully,
  */
  int UnloadPassenger();
  /**
  *
  * @brief Moves the bus toward its next stop.
  *
  * @return True if bus is moved successfully,
  */
  bool Move();
  /**
  *
  * @brief Checks if the bus completes both inbound and outbound trip.
  *
  * @return True if the bus completes the trip, false ohterwise.
  */
  bool IsTripComplete();
  /**
  * @brief Updates the status of the bus.
  *
  * It updates the bus status and it should be called in every timestep.
  * This method must make whatever changes to state that are required of the
  * simulation during a timestep. When the simulation is running, a bus
  * shold update the onboard passengers and moving forward.
  * If the bus arrives at a stop, the unloading and loading process happen
  * when calling update.
  *
  */
  void Update();
  /**
  * @brief reports the status of the bus to a given out stream
  * (default std::cout).
  *
  * @param[in] ostream the out stream of target the report.
  *
  */
  void Report(std::ostream &out = std::cout);
  /**
  * @brief It updates and initializes the data_struct of the bus. It is called
  * inside the Update()
  */
  void UpdateBusData();
  /**
  * @brief It gets the current bus positon in Latitude and longitude coordinates.
  * It collects position data for bus data structure.
  *
  * @return position struct of current position of the bus
  */
  Position GetPosition();
  /**
  * @brief It gets bus data for vis_sim.
  *
  * @return bus struct of current bus
  */
  BusData GetBusData();
  /**
  * @brief It collects position data for bus data structure.
  * It is called by the visualizer to obtain the BusData struct.
  *
  * @return a string of bus name
  */
  std::string GetName() const;
  /**
  * @brief It gets the incoming stop.
  *
  * It is called by the visualizer to get the name of the bus
  * @return a stop pointer of the incoming stop
  */
  Stop * GetNextStop();
  /**
  * @brief It gets the number of passengers on the bus.
  *
  * It is called by the visualizer to get the pointer to the bus's next stop
  */
  size_t GetNumPassengers();
  /**
  * @brief It gets the bus max capacity.
  *
  * It is called by the visualizer to get the maximum number of passengers that
  * the bus can hold.
  */
  int GetCapacity();





 private:
  std::list<Passenger *> passengers_;
  int passenger_max_capacity_;
  std::string name_;
  double speed_;  ///< could also be called
                  ///< "distance travelled in one time step"
  double out_distance_;  ///< starting at the first stop in the route
  double in_distance_;  ///< will start at the last stop in the prior route)
  Route * outgoing_route_;
  Route * incoming_route_;
  Stop * stop_arrived_at_;  ///< stop bus currently arrived at
  BusData data_;
  double distance_remaining_;  ///< when negative?, unload/load procedure occurs
                              ///< AND next stop set
  // double revenue_; // revenue collected from passengers, doesn't include
                      // passengers who pay on deboard
  // double fuel_;   // may not be necessary for our simulation
  // double max_fuel_;
  int at_stop_;  // an indicator to determine if bus is at stop.
  Stop * next_stop_;
  double distances_between_;  // static when bus moving between stops
  double DockingProcess(Route * cur_route, float dist);  /// internal called by
                                                         /// bus update
  void SkipStop(float distance);  /// internal called by DockingProcess
};
#endif  // SRC_BUS_H_
