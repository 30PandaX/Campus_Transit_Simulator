/**
 * @file bus.cc
 *
 * @Copyright 2019 3081 Staff, All rights reserved.
 */

#include "src/bus.h"


Bus::Bus(std::string name, Route * out, Route * in, int capacity,
        double speed) {
  name_ = name;
  outgoing_route_ = out;
  incoming_route_ = in;
  passenger_max_capacity_ = capacity;
  speed_ = speed;
  distance_remaining_ = 0;
  out_distance_ = 0;
  in_distance_ = speed;
}


bool Bus::LoadPassenger(Passenger * new_passenger) {
  int size = passengers_.size();
  if (size < passenger_max_capacity_) {
    new_passenger->GetOnBus();
    passengers_.push_back(new_passenger);
    return true;
  } else {
    return false;
  }
}

int Bus::UnloadPassenger() {
  std::list<Passenger *>::iterator it = passengers_.begin();
  int unloaded = 0;
  for (it = passengers_.begin(); it != passengers_.end(); it++) {
    if ((*it)->GetDestination() == stop_arrived_at_->GetId()) {
      passengers_.remove(*it);
      unloaded++;
      it--;
    }
  }
  return unloaded;
}

bool Bus::Move() {
    if (out_distance_ > -1) {
      out_distance_ = out_distance_ - speed_;
    } else {
      in_distance_ = in_distance_ - speed_;
    }
    return true;
}

bool Bus::IsTripComplete() {
    if (incoming_route_->IsAtEnd() && distance_remaining_ < 0)
      return true;
    else
      return false;
}

// bool Refuel() {
//  // This may become more complex in the future
//  fuel_ = max_fuel_;
//}
double Bus::DockingProcess(Route * cur_route, float distance) {
  at_stop_ = 1;
  stop_arrived_at_ = cur_route->GetDestinationStop();
  int unloaded = UnloadPassenger();
  if (cur_route->IsAtEnd()) {
    distance = -1000;
    distance_remaining_ = 0;
  } else {
    int loaded = stop_arrived_at_->LoadPassengers(this);
    cur_route->NextStop();
    distance = cur_route->GetNextStopDistance();
    next_stop_ = cur_route->GetDestinationStop();

    if (!unloaded && !loaded) {  // skip this stop when no one waiting/off
      // SkipStop(distance);
    } else {
      distance_remaining_ = distance;  // normal case.
    }
  }
  distances_between_ = distance;
  return distance;
}

void Bus::SkipStop(float distance) {
    double offset = speed_ - distance_remaining_;  // bus should travel
    distance_remaining_ = distance - offset;  // more distance.
    if (distance_remaining_ < 0)  // bus shouldn't skip more than 1 stop
      distance_remaining_ = 0;
}

void Bus::Update() {  // using common Update format
  for (std::list<Passenger *>::iterator it = passengers_.begin();
      it != passengers_.end(); it++) {
        (*it)->Update();
  }
  // Move();
  if (out_distance_ <= 0 && out_distance_ >= -speed_) {
    // arrives at a outbound stop
    out_distance_ = DockingProcess(outgoing_route_, out_distance_);
  } else if (in_distance_ <= 0 && in_distance_ >= -speed_) {
    in_distance_ = DockingProcess(incoming_route_, in_distance_);
  } else if (out_distance_ > -1) {
      at_stop_ = 0;
      distance_remaining_ = out_distance_;
  } else {
      at_stop_ = 0;
      distance_remaining_ = in_distance_;
  }
  UpdateBusData();
  Move();
}

void Bus::UpdateBusData() {
  data_.id = name_;
  data_.position = GetPosition();
  data_.num_passengers = GetNumPassengers();
  data_.capacity = passenger_max_capacity_;
}

Position Bus::GetPosition() {
  Position new_pos;
  Position cur_pos = stop_arrived_at_->GetPosition();
  Position next_pos = next_stop_->GetPosition();
  if (at_stop_) {
    new_pos = cur_pos;
  } else {
    new_pos.x = (cur_pos.x + next_pos.x)/2;
    new_pos.y = (cur_pos.y + next_pos.y)/2;
  }
  return new_pos;
}

BusData Bus::GetBusData() {  // obtain the BusData struct.
  return data_;
}
std::string Bus::GetName() const {  // get the name of the bus
  return name_;
}
Stop * Bus::GetNextStop() {  // get the pointer to the bus's next stop
  return stop_arrived_at_;
}

size_t Bus::GetNumPassengers() {  // the current number of passengers on the bus
  return passengers_.size();
}
int Bus::GetCapacity() {  // get the maximum number of passengers
                         // that the bus can hold
  return passenger_max_capacity_;
}

void Bus::Report(std::ostream &out) {
  out << "Name: " << name_ << std::endl;
  out << "Speed: " << speed_ << std::endl;
  out << "Distance to next stop: " << distance_remaining_ << std::endl;
  out << "\tPassengers (" << passengers_.size() << "): " << std::endl;
  for (std::list<Passenger *>::iterator it = passengers_.begin();
      it != passengers_.end(); it++) {
    (*it)->Report(out);
  }
}
