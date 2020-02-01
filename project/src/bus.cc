#include "bus.h"

Bus::Bus(std::string name, Route * out, Route * in, int capacity, double speed) {
  name_ = name;
  outgoing_route_ = out;
  incoming_route_ = in;
  passenger_max_capacity_ = capacity;
  speed_ = speed;
  distance_remaining_ = 0;
}


bool Bus::LoadPassenger(Passenger * new_passenger) {
  return true;
}

bool Bus::Move() {
	return true;
}

//bool Refuel() {
//  //This may become more complex in the future
//  fuel_ = max_fuel_;
//}

void Bus::Update() { //using common Update format
  Move();
}

void Bus::Report() {
  std::cout << "Name: " << name_ << std::endl;
  std::cout << "Speed: " << speed_ << std::endl;
  std::cout << "Distance to next stop: " << distance_remaining_ << std::endl;
  std::cout << "\tPassengers (" << passengers_.size() << "): " << std::endl;
  for (std::list<Passenger *>::iterator it = passengers_.begin(); it != passengers_.end(); it++) {
    (*it)->Report();
  }
}