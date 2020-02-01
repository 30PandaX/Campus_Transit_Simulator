/**
 * @file passenger.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */

#ifndef SRC_PASSENGER_H_
#define SRC_PASSENGER_H_


/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <string>

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A class for the passengers, who are either waitng at
 * a stop or on a bus.
 *
 * This class describes the behavior of the campus transit passengers.
 * They are either waiting at a stop or on a bus. The \ref Update function
 * counts the time the passenger is at a stop and on a bus if the
 * passenger \ref GetOnBus .
 *
 */
class Passenger {  // : public Reporter {
 public:
   /**
   * @brief Constructs a passenger with a standard name and id.
   *
   *
   * @param[in] int holding an id number
   * @param[in] string holding a name of a created passenger.
   *
   */
  explicit Passenger(int = -1, std::string = "Nobody");
  /**
  * @brief Updates the passenger status.
  *
  * It updates the passenger status and it should be called in every timestep.
  * This method must make whatever changes to state that are required of the
  * simulation during a timestep. When the simulation is running, a passenger
  * is doing one of three things for that time step: waiting at a stop, riding
  * on a bus as it moved, or getting on/off the bus.
  *
  */
  void Update();
  /**
  * @brief Makes the passenger to get on bus.
  *
  * This function changes the status of the passenger from waiting at a stop
  * to getting on a bus. It should be called when a bus arrives at a stop and
  * is ready to pick up passengers.
  *
  */
  void GetOnBus();
  /**
  * @brief It returns the total wait of the passenger until the passenger
  * gets to their destination.
  *
  * @return The total time that a passenger has been waiting.
  */
  int GetTotalWait() const;
  /**
  * @brief Checks if the passenger is on a bus.
  *
  * @return True if the passenger is on a bus, false otherwise.
  */
  bool IsOnBus() const;
  /**
  * @brief It returns the destination id of the passenger.
  *
  * @return The destination id of the passenger.
  */
  int GetDestination() const;
  /**
  * @brief reports the status of the passenger to a given out stream
  * (default std::cout).
  *
  * @param[in] ostream the out stream of target the report.
  *
  */
  void Report(std::ostream &out = std::cout) const;

 private:
  std::string name_;
  int destination_stop_id_;
  int wait_at_stop_;
  int time_on_bus_;
  int id_;
  static int count_;  // global count, used to set ID for new instances
};
#endif  // SRC_PASSENGER_H_
