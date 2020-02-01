/* STUDENTS: YOU MUST ADD YOUR PASSENGER UNIT TESTS TO THIS FILE. FORMAT YOUR
 * TESTS TO FIT THE SPECIFICATIONS GIVEN BY THE TESTS PROVIDED IN THIS FILE.
 *
 * Please note, the assessment tests for grading, will use the same include
 * files, class names, and function names for accessing students' code that you
 * find in this file.  So students, if you write your code so that it passes
 * these feedback tests, you can be assured that the auto-grader will at least
 * be able to properly link with your code.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <list>

#include "../src/route.h"
#include "../src/passenger.h"
#include "../src/stop.h"
#include "../src/random_passenger_generator.h"

/******************************************************
* TEST FEATURE SetUp
*******************************************************/

class RouteTests : public ::testing::Test {

	protected:

		Route* CC_EB;
		double * CC_EB_distances;
		Stop ** CC_EB_stops;
		std::list<Stop *> CC_EB_stops_list;
    std::list<double> CC_EB_probs;  //realistic .15, .3, .025, .05, .05, 0
    RandomPassengerGenerator* CC_EB_generator;
    Stop *stop_CC_EB_1; //West bank station
    Stop *stop_CC_EB_2; //student union station
    Stop *stop_CC_EB_3; //Oak St & Washington Ave
    Stop *stop_CC_EB_4; //before transit
    Stop *stop_CC_EB_5; //st paul 1
    Stop *stop_CC_EB_6; //st paul 2

	virtual void SetUp() {
			//Stop ** all_stops = new Stop *[12];
			CC_EB_stops = new Stop *[6];
		  //Eastbound stops
		  stop_CC_EB_1 = new Stop(0, 43, -92.5); //West bank station
		  stop_CC_EB_2 = new Stop(1); //student union station
		  stop_CC_EB_3 = new Stop (2, 44.973820, -93.227117); //Oak St & Washington Ave
		  stop_CC_EB_4 = new Stop (3, 45, -94); //before transit
		  stop_CC_EB_5 = new Stop (4, 46, -95); //st paul 1
		  stop_CC_EB_6 = new Stop (5, 47, -96); //st paul 2

		  CC_EB_stops_list.push_back(stop_CC_EB_1);
		  CC_EB_stops[0] = stop_CC_EB_1;
		  CC_EB_stops_list.push_back(stop_CC_EB_2);
		  CC_EB_stops[1] = stop_CC_EB_2;
		  CC_EB_stops_list.push_back(stop_CC_EB_3);
		  CC_EB_stops[2] = stop_CC_EB_3;
		  CC_EB_stops_list.push_back(stop_CC_EB_4);
		  CC_EB_stops[3] = stop_CC_EB_4;
		  CC_EB_stops_list.push_back(stop_CC_EB_5);
		  CC_EB_stops[4] = stop_CC_EB_5;
		  CC_EB_stops_list.push_back(stop_CC_EB_6);
		  CC_EB_stops[5] = stop_CC_EB_6;

			CC_EB_distances = new double[5];
		  CC_EB_distances[0] = 5;
		  CC_EB_distances[1] = 4;
		  CC_EB_distances[2] = 3;
		  CC_EB_distances[3] = 10;
		  CC_EB_distances[4] = 6;

		  // std::list<double> CC_EB_probs;  //realistic .15, .3, .025, .05, .05, 0
		  CC_EB_probs.push_back(.15); //WB
		  CC_EB_probs.push_back(.3); //CMU
		  CC_EB_probs.push_back(.025); //O&W
		  CC_EB_probs.push_back(.05); //Pre-transit
		  CC_EB_probs.push_back(.05); //STP 1
		  CC_EB_probs.push_back(0); //STP 1
		  //TODO: is this always true? If so, we may want to reduce the length of probs to_char_type
		  //        remove possibility of generating passengers with nowhere to go

		  CC_EB_generator = new RandomPassengerGenerator(CC_EB_probs, CC_EB_stops_list);
		  CC_EB = new Route("Campus Connector - Eastbound", CC_EB_stops, CC_EB_distances, 6, CC_EB_generator);

	}

  	virtual void TearDown() {
    	delete CC_EB;
			for (int i=0; i<6; i++)
					delete CC_EB_stops[i];
			delete CC_EB_stops;
			delete CC_EB_distances;
  	}
};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/
TEST_F(RouteTests, Constructor) {
	testing::internal::CaptureStdout();
	CC_EB->Report();
	std::string output = testing::internal::GetCapturedStdout();

	std::string expected = "Name: Campus Connector - Eastbound\nNum stops: 6\n";
	for (int i=0; i<6; i++){
			expected = expected + "ID: "
                          + std::to_string(CC_EB_stops[i]->GetId())
													+"\nPassengers waiting: 0\n";
	}
	EXPECT_EQ(output, expected);
};

TEST_F(RouteTests, Clone) {
  Route* clone_route = CC_EB->Clone();

	testing::internal::CaptureStdout();
	clone_route->Report();
	std::string output = testing::internal::GetCapturedStdout();

	std::string expected = "Name: Campus Connector - Eastbound\nNum stops: 6\n";
	for (int i=0; i<6; i++){
			expected = expected + "ID: "
                          + std::to_string(CC_EB_stops[i]->GetId())
													+"\nPassengers waiting: 0\n";
	}
	EXPECT_EQ(output, expected);
};

TEST_F(RouteTests, GetName) {
  // RouteData data = CC_EB->GetRouteData();
  // std::string output = data.id;
  std::string output = CC_EB->GetName();
  std::string expected = "Campus Connector - Eastbound";
  EXPECT_EQ(output, expected);
};

TEST_F(RouteTests, DataStruct_ID) {
  CC_EB->UpdateRouteData();
  RouteData data = CC_EB->GetRouteData();
  std::string output = data.id;
  std::string expected = "Campus Connector - Eastbound";
  EXPECT_EQ(output, expected);
};

TEST_F(RouteTests, DataStruct_stops) {
  CC_EB->UpdateRouteData();
  RouteData data = CC_EB->GetRouteData();
  std::vector<StopData> stops = data.stops;

  for (unsigned i=0; i<stops.size(); i++) {
    std::string output = stops.at(i).id;
    Stop* expected_stop = CC_EB_stops_list.front();
    CC_EB_stops_list.pop_front();
    std::string expected = std::to_string(expected_stop->GetId());
    EXPECT_EQ(output, expected);
  }
};

TEST_F(RouteTests, Update) {

  int max_pass = 10;
  Passenger* passengers[max_pass];
  int expected_total = 0;

  for (std::list<Stop *>::const_iterator it = CC_EB_stops_list.begin();
      it != CC_EB_stops_list.end(); it++) {
      for (int i=0; i<max_pass; i++){
          passengers[i] = new Passenger(int(i%10), std::to_string(i));
          expected_total += (*it)->AddPassengers(passengers[i]);
      }
  }
  for (unsigned i=0; i<CC_EB_stops_list.size();i++) {
    CC_EB_probs.pop_front();
    CC_EB_probs.push_back(0);
  }

  CC_EB_generator = new RandomPassengerGenerator(CC_EB_probs, CC_EB_stops_list);
  CC_EB = new Route("Campus Connector - Eastbound", CC_EB_stops, CC_EB_distances, 6, CC_EB_generator);

  int rounds = 20;
  for (int i=0; i<rounds; i++)
    CC_EB->Update();

  std::string output;
  std::string expected;
  std::string report_head;
  std::string pass_waits;
  std::string pass_report;
  for (std::list<Stop *>::const_iterator it = CC_EB_stops_list.begin();
      it != CC_EB_stops_list.end(); it++) {
    testing::internal::CaptureStdout();
    (*it)->Report();
     output += testing::internal::GetCapturedStdout();

    report_head = "ID: "+std::to_string((*it)->GetId())+"\nPassengers waiting: ";
    pass_waits = std::to_string(max_pass) + "\n";
    pass_report = "";
    for (int i=0; i<max_pass; i++){
        pass_report = pass_report
                        + "Name: " + std::to_string(i) + "\nDestination: "
                        + std::to_string(int(i%10))
                        + "\nTotal Wait: " + std::to_string(rounds) + "\n\t"
                        + "Wait at Stop: " + std::to_string(rounds) + "\n\t"
                        + "Time on bus: 0\n";
    }
    expected += report_head + pass_waits + pass_report;
  }
  EXPECT_EQ(output, expected);
};

TEST_F(RouteTests, Report) {

  int max_pass = 10;
  Passenger* passengers[max_pass];
  int expected_total = 0;

  for (std::list<Stop *>::const_iterator it = CC_EB_stops_list.begin();
      it != CC_EB_stops_list.end(); it++) {
      for (int i=0; i<max_pass; i++){
          passengers[i] = new Passenger(int(i%10), std::to_string(i));
          expected_total += (*it)->AddPassengers(passengers[i]);
      }
  }
  for (unsigned i=0; i<CC_EB_stops_list.size();i++) {
    CC_EB_probs.pop_front();
    CC_EB_probs.push_back(0);
  }

  CC_EB_generator = new RandomPassengerGenerator(CC_EB_probs, CC_EB_stops_list);
  CC_EB = new Route("Campus Connector - Eastbound", CC_EB_stops, CC_EB_distances, 6, CC_EB_generator);

  int rounds = 20;
  for (int i=0; i<rounds; i++)
    CC_EB->Update();

  testing::internal::CaptureStdout();
  CC_EB->Report();
  std::string output= testing::internal::GetCapturedStdout();
  std::string expected = "Name: " + CC_EB->GetRouteData().id + "\nNum stops: "
                          + std::to_string(CC_EB_stops_list.size()) + "\n";
  std::string report_head;
  std::string pass_waits;
  std::string pass_report;
  for (std::list<Stop *>::const_iterator it = CC_EB_stops_list.begin();
      it != CC_EB_stops_list.end(); it++) {


    report_head = "ID: "+std::to_string((*it)->GetId())+"\nPassengers waiting: ";
    pass_waits = std::to_string(max_pass) + "\n";
    pass_report = "";
    for (int i=0; i<max_pass; i++){
        pass_report = pass_report
                        + "Name: " + std::to_string(i) + "\nDestination: "
                        + std::to_string(int(i%10))
                        + "\nTotal Wait: " + std::to_string(rounds) + "\n\t"
                        + "Wait at Stop: " + std::to_string(rounds) + "\n\t"
                        + "Time on bus: 0\n";
    }
    expected += report_head + pass_waits + pass_report;
  }
  EXPECT_EQ(output, expected);
};

TEST_F(RouteTests, IsAtEnd_NextStop_1) {

  int max_pass = 10;
  Passenger* passengers[max_pass];
  int expected_total = 0;

  for (std::list<Stop *>::const_iterator it = CC_EB_stops_list.begin();
      it != CC_EB_stops_list.end(); it++) {
      for (int i=0; i<max_pass; i++){
          passengers[i] = new Passenger(int(i%10), std::to_string(i));
          expected_total += (*it)->AddPassengers(passengers[i]);
      }
  }
  for (unsigned i=0; i<CC_EB_stops_list.size();i++) {
    CC_EB_probs.pop_front();
    CC_EB_probs.push_back(0);
  }

  CC_EB_generator = new RandomPassengerGenerator(CC_EB_probs, CC_EB_stops_list);
  CC_EB = new Route("Campus Connector - Eastbound", CC_EB_stops, CC_EB_distances, 6, CC_EB_generator);

  int rounds = 20;
  for (int i=0; i<rounds; i++)
    CC_EB->Update();

  for (int i=0; i<3; i++)
    CC_EB->NextStop();

  std::string output;
  if (CC_EB->IsAtEnd()) {
    output = "true";
  }
  else {
    output = "false";
  }

  std::string expected = "false";
  EXPECT_EQ(output, expected);
};

TEST_F(RouteTests, IsAtEnd_NextStop_2) {

  int max_pass = 10;
  Passenger* passengers[max_pass];
  int expected_total = 0;

  for (std::list<Stop *>::const_iterator it = CC_EB_stops_list.begin();
      it != CC_EB_stops_list.end(); it++) {
      for (int i=0; i<max_pass; i++){
          passengers[i] = new Passenger(int(i%10), std::to_string(i));
          expected_total += (*it)->AddPassengers(passengers[i]);
      }
  }
  for (unsigned i=0; i<CC_EB_stops_list.size();i++) {
    CC_EB_probs.pop_front();
    CC_EB_probs.push_back(0);
  }

  CC_EB_generator = new RandomPassengerGenerator(CC_EB_probs, CC_EB_stops_list);
  CC_EB = new Route("Campus Connector - Eastbound", CC_EB_stops, CC_EB_distances, 6, CC_EB_generator);

  int rounds = 6;
  for (int i=0; i<rounds; i++)
    CC_EB->Update();

  int size = CC_EB_stops_list.size() -1;
  for (int i=0; i<size; i++)
    CC_EB->NextStop();

  std::string output;
  if (CC_EB->IsAtEnd()) {
    output = "true";
  }
  else {
    output = "false";
  }

  std::string expected = "true";
  EXPECT_EQ(output, expected);
};

TEST_F(RouteTests, IsAtEnd_NextStop_3) {

  int max_pass = 10;
  Passenger* passengers[max_pass];
  int expected_total = 0;

  for (std::list<Stop *>::const_iterator it = CC_EB_stops_list.begin();
      it != CC_EB_stops_list.end(); it++) {
      for (int i=0; i<max_pass; i++){
          passengers[i] = new Passenger(int(i%10), std::to_string(i));
          expected_total += (*it)->AddPassengers(passengers[i]);
      }
  }
  for (unsigned i=0; i<CC_EB_stops_list.size();i++) {
    CC_EB_probs.pop_front();
    CC_EB_probs.push_back(0);
  }

  CC_EB_generator = new RandomPassengerGenerator(CC_EB_probs, CC_EB_stops_list);
  CC_EB = new Route("Campus Connector - Eastbound", CC_EB_stops, CC_EB_distances, 6, CC_EB_generator);

  int rounds = 20;
  for (int i=0; i<rounds; i++)
    CC_EB->Update();

  for (int i=0; i<30; i++)
    CC_EB->NextStop();
  std::string output;

  if (CC_EB->IsAtEnd()) {
    output = "true";
  }
  else {
    output = "false";
  }

  std::string expected = "true";
  EXPECT_EQ(output, expected);
};

TEST_F(RouteTests, GetDestinationStop_1) {

  int max_pass = 10;
  Passenger* passengers[max_pass];
  int expected_total = 0;

  for (std::list<Stop *>::const_iterator it = CC_EB_stops_list.begin();
      it != CC_EB_stops_list.end(); it++) {
      for (int i=0; i<max_pass; i++){
          passengers[i] = new Passenger(int(i%10), std::to_string(i));
          expected_total += (*it)->AddPassengers(passengers[i]);
      }
  }
  for (unsigned i=0; i<CC_EB_stops_list.size();i++) {
    CC_EB_probs.pop_front();
    CC_EB_probs.push_back(0);
  }

  CC_EB_generator = new RandomPassengerGenerator(CC_EB_probs, CC_EB_stops_list);
  CC_EB = new Route("Campus Connector - Eastbound", CC_EB_stops, CC_EB_distances, 6, CC_EB_generator);

  int rounds = 20;
  for (int i=0; i<rounds; i++)
    CC_EB->Update();

  Stop * next_stop = CC_EB->GetDestinationStop();
  std::string output = std::to_string(next_stop->GetId());
  std::string expected = "0";
  EXPECT_EQ(output, expected);
};

TEST_F(RouteTests, GetDestinationStop_2) {

  int max_pass = 10;
  Passenger* passengers[max_pass];
  int expected_total = 0;

  for (std::list<Stop *>::const_iterator it = CC_EB_stops_list.begin();
      it != CC_EB_stops_list.end(); it++) {
      for (int i=0; i<max_pass; i++){
          passengers[i] = new Passenger(int(i%10), std::to_string(i));
          expected_total += (*it)->AddPassengers(passengers[i]);
      }
  }
  for (unsigned i=0; i<CC_EB_stops_list.size();i++) {
    CC_EB_probs.pop_front();
    CC_EB_probs.push_back(0);
  }

  CC_EB_generator = new RandomPassengerGenerator(CC_EB_probs, CC_EB_stops_list);
  CC_EB = new Route("Campus Connector - Eastbound", CC_EB_stops, CC_EB_distances, 6, CC_EB_generator);

  int rounds = 20;
  for (int i=0; i<rounds; i++)
    CC_EB->Update();

  for (int i=0; i<3; i++)
    CC_EB->NextStop();

  Stop * next_stop = CC_EB->GetDestinationStop();
  std::string output = std::to_string(next_stop->GetId());
  std::string expected = "3";
  EXPECT_EQ(output, expected);
};
