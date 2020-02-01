/**
 * @file stop.cc
 *
 * @Copyright 2019 3081 Staff, All rights reserved.
 */

#include <iostream>
#include <vector>

#include "./stop.h"

Stop::Stop(int id, double longitude, double latitude) {
    // Defaults to Westbound Coffman Union stop
    // no initialization of list of passengers necessary
    id_ = id;
    longitude_ = longitude;
    latitude_ = latitude;
}

// are they all go onto the bus? or just one
int Stop::LoadPassengers(Bus * bus) {
    // loading some passengers onto a bus
    int loaded = 0;
    int pass_size = static_cast<int>(passengers_.size());
    for (int i=0; i < pass_size; i++) {
          Passenger *front = passengers_.front();
          if (bus->LoadPassenger(front)) {
            passengers_.pop_front();
            front->GetOnBus();
            loaded++;
          }
    }
    return loaded;
}

void Stop::Update() {
  for (std::list<Passenger *>::iterator it = passengers_.begin();
       it != passengers_.end(); it++) {  // loop through passes to update them
    (*it)->Update();
  }
}

int Stop::AddPassengers(Passenger * pass) {
    // add the passenger to the stop
    passengers_.push_back(pass);
    return 1;
}

Position Stop::GetPosition() {
  Position pos;
  pos.x = longitude_;
  pos.y = latitude_;
  return pos;
}

int Stop::GetNumPassengers() {
  int ret = passengers_.size();
  return ret;
}

int Stop::GetId() const {
  return id_;
}


void Stop::Report(std::ostream &out) const {
    out << "ID: " << id_ << std::endl;
    out << "Passengers waiting: " << passengers_.size() << std::endl;

    for (std::list<Passenger *>::const_iterator it = passengers_.begin();
        it != passengers_.end(); it++) {
      (*it)->Report(out);
    }
}
