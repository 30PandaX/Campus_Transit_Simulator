#include <iostream>
#include <vector>

#include "stop.h"

Stop::Stop(int id, double longitude, double latitude) : id_(id), longitude_(longitude), latitude_(latitude) { //Defaults to Westbound Coffman Union stop
  // no initialization of list of passengers necessary
}

int Stop::AddPassengers(Passenger * pass) {
  return 0;
}

void Stop::Update() {
  for (std::list<Passenger *>::iterator it = passengers_.begin(); it != passengers_.end(); it++) {
    (*it)->Update();
  }
}

int Stop::GetId() const{
  return id_;
}

void Stop::Report() const {
  std::cout << "ID: " << id_ << std::endl;
  std::cout << "Passengers waiting: " << passengers_.size() << std::endl;
  for(std::list<Passenger *>::const_iterator it = passengers_.begin(); it != passengers_.end(); it++) {
    (*it)->Report();
  }
}