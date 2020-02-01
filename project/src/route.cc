/**
 * @file route.cc
 *
 * @Copyright 2019 3081 Staff, All rights reserved.
 */

#include "src/route.h"
 // Constructor
Route::Route(std::string name, Stop ** stops, double * distances,
              int num_stops, PassengerGenerator * pass_gen) {
  for (int i = 0; i < num_stops; i++) {  // loop through all stops on the route
    stops_.push_back(stops[i]);
  }  // push them to stops list
  for (int i = 0; i < num_stops - 1; i++) {
    distances_between_.push_back(distances[i]);
  }
  // Get distances_between_ data from args and store them to private variable
  name_ = name;
  num_stops_ = num_stops;
  generator_ = pass_gen;
  destination_stop_index_ = 0;
  destination_stop_ = stops_.front();
}

Route * Route::Clone() {
  std::string new_name = name_;  // make a copy of name
  Stop ** new_stops = new Stop *[num_stops_];  // create a new list to store
  int i = 0;                                  // stops
  for (std::list<Stop *>::const_iterator it = stops_.begin();
      it != stops_.end(); it++) {  // loop through stops list ot create copy
    new_stops[i]=*it;
    i++;
  }
  double * new_dist_betn = new double[num_stops_-1];  // create a new list to
  i = 0;                                              // store distance data
  for (std::list<double>::const_iterator it = distances_between_.begin();
      it != distances_between_.end(); it++) {
    new_dist_betn[i]=*it;   // loop through distance list ot create copy
    i++;
  }
  int new_num_stops = num_stops_;  // create new route using Constructor
  Route * new_route = new Route (new_name, new_stops, new_dist_betn,
                                  new_num_stops, generator_);
  return new_route;
}

void Route::Update() {
  GenerateNewPassengers();  // generates passengers at stops randomly
  for ( std::list<Stop *>::iterator it = stops_.begin();
      it != stops_.end(); it++) {
    (*it)->Update();  // loop through stops to update
  }
  if (IsAtEnd())  // if bus reaches the end of rout,  set the index to be 0
    destination_stop_index_ = 0;  // for switching bounds
  UpdateRouteData();
}

int Route::GenerateNewPassengers() {  // generates passengers on its route
  return generator_ -> GeneratePassengers();
}

bool Route::IsAtEnd() const {
  if (destination_stop_index_ >= num_stops_-1) {
    return true;  // destination_stop_index_ increases when bus stops at a stop
  } else {
    return false;
  }
}

void Route::NextStop() {  // advance a stop to next stop
  destination_stop_index_++;  // increase by one to indicate arrived
  auto it = std::next(stops_.begin(), destination_stop_index_);
  // find the next stop using index
  destination_stop_ = *it;
}

Stop * Route::GetDestinationStop() const {
  return destination_stop_;
}

double Route::GetTotalRouteDistance() const {
  double sum = std::accumulate(std::begin(distances_between_),
                std::end(distances_between_), 0.0);
  return sum;
}

double Route::GetNextStopDistance() const {
  auto it =
              std::next(distances_between_.begin(), destination_stop_index_-1);
  return static_cast<double>(*it);
}

std::string Route::GetName() {
  return name_;
}

std::list<Stop *> Route::GetStops() {
  return stops_;
}

void Route::UpdateRouteData() {
  data_.id = name_;
  std::vector<StopData> stop_data;
  for (std::list<Stop *>::const_iterator it = stops_.begin();
      it != stops_.end(); it++) {
    StopData new_stop;
    new_stop.id = std::to_string((*it)->GetId());
    new_stop.position = (*it)->GetPosition();
    new_stop.num_people = (*it)->GetNumPassengers();
    stop_data.push_back(new_stop);
  }
  data_.stops = stop_data;
}

RouteData Route::GetRouteData() {
  return data_;
}

void Route::Report(std::ostream &out) {
  out << "Name: " << name_ << std::endl;
  out << "Num stops: " << num_stops_ << std::endl;
  for (std::list<Stop *>::const_iterator it = stops_.begin();
      it != stops_.end(); it++) {
    (*it)->Report(out);
  }
}
