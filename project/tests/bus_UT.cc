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

#include "../src/route.h"
#include "../src/passenger.h"
#include "../src/stop.h"
#include "../src/bus.h"
#include "../src/random_passenger_generator.h"

/******************************************************
* TEST FEATURE SetUp
*******************************************************/

class BusTests : public ::testing::Test {

	protected:

    Route* CC_EB;
    Route* CC_WB;
		double * CC_EB_distances;
    double * CC_WB_distances;

		Stop ** CC_EB_stops;
    Stop ** CC_WB_stops;

		std::list<Stop *> CC_EB_stops_list;
    std::list<Stop *> CC_WB_stops_list;

    std::list<double> CC_EB_probs;  //realistic .15, .3, .025, .05, .05, 0
    std::list<double> CC_WB_probs; //realistic .35, .05, .01, .01, .2, 0

    RandomPassengerGenerator* CC_EB_generator;
    RandomPassengerGenerator* CC_WB_generator;

    Stop *stop_CC_EB_1; //West bank station
    Stop *stop_CC_EB_2; //student union station
    Stop *stop_CC_EB_3; //Oak St & Washington Ave
    Stop *stop_CC_EB_4; //before transit
    Stop *stop_CC_EB_5; //st paul 1
    Stop *stop_CC_EB_6; //st paul 2
    Stop *stop_CC_EB_7; //st paul 2
    Stop *stop_CC_EB_8; //st paul 2


    //Westbound stops
    Stop *stop_CC_WB_1; //st paul 2
    Stop *stop_CC_WB_2; //st paul 1
    Stop *stop_CC_WB_3; //before transit
    Stop *stop_CC_WB_4; //Oak St & Washington Ave
    Stop *stop_CC_WB_5; //student union station
    Stop *stop_CC_WB_6; //West bank station
    Stop *stop_CC_WB_7; //West bank station
    Stop *stop_CC_WB_8; //West bank station
    Stop *stop_CC_WB_9; //West bank station


    Bus  *test_bus;

	virtual void SetUp() {
    //Stop ** all_stops = new Stop *[12];
    CC_EB_stops = new Stop *[8];
    //Eastbound stops
    stop_CC_EB_1 = new Stop(0, 44.972392, -93.243774);
    //   student union station
    stop_CC_EB_2 = new Stop(1, 44.973580, -93.235071);
    //   Oak St & Washington Ave
    stop_CC_EB_3 = new Stop(2, 44.975392, -93.226632);
    //   before transit
    stop_CC_EB_4 = new Stop(3, 44.975837, -93.222174);
    //   tway
    stop_CC_EB_5 = new Stop(4, 44.980753, -93.180669);
    //   Fairgrounds
    stop_CC_EB_6 = new Stop(5, 44.983375, -93.178810);
    //   Buford & Gartner
    stop_CC_EB_7 = new Stop(6, 44.984540, -93.181692);
    //   SPSC
    stop_CC_EB_8 = new Stop(7, 44.984630, -93.186352);

    CC_WB_stops = new Stop *[9];
    //Westbound stops
    stop_CC_WB_1 = new Stop(8, 44.984630, -93.186352);
    //   Buford & Gartner
    stop_CC_WB_2 = new Stop(9, 44.984482, -93.181657);
    //   Fairgrounds
    stop_CC_WB_3 = new Stop(10, 44.983703, -93.178846);
    //   Tway
    stop_CC_WB_4 = new Stop(11, 44.980663, -93.180808);
    //   before transit
    stop_CC_WB_5 = new Stop(12, 44.976397, -93.221801);
    //   Ridder
    stop_CC_WB_6 = new Stop(13, 44.978058, -93.229176);
    //   Jones-Eddy
    stop_CC_WB_7 = new Stop(14, 44.978366, -93.236038);
    //   Bruininks
    stop_CC_WB_8 = new Stop(15, 44.974549, -93.236927);
    //   Blegen
    stop_CC_WB_9 = new Stop(16, 44.972638, -93.243591);

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
    CC_EB_stops_list.push_back(stop_CC_EB_7);
    CC_EB_stops[6] = stop_CC_EB_7;
    CC_EB_stops_list.push_back(stop_CC_EB_8);
    CC_EB_stops[7] = stop_CC_EB_8;

    CC_WB_stops_list.push_back(stop_CC_WB_1);
    CC_WB_stops[0] = stop_CC_WB_1;
    CC_WB_stops_list.push_back(stop_CC_WB_2);
    CC_WB_stops[1] = stop_CC_WB_2;
    CC_WB_stops_list.push_back(stop_CC_WB_3);
    CC_WB_stops[2] = stop_CC_WB_3;
    CC_WB_stops_list.push_back(stop_CC_WB_4);
    CC_WB_stops[3] = stop_CC_WB_4;
    CC_WB_stops_list.push_back(stop_CC_WB_5);
    CC_WB_stops[4] = stop_CC_WB_5;
    CC_WB_stops_list.push_back(stop_CC_WB_6);
    CC_WB_stops[5] = stop_CC_WB_6;
    CC_WB_stops_list.push_back(stop_CC_WB_7);
    CC_WB_stops[6] = stop_CC_WB_7;
    CC_WB_stops_list.push_back(stop_CC_WB_8);
    CC_WB_stops[7] = stop_CC_WB_8;
    CC_WB_stops_list.push_back(stop_CC_WB_9);
    CC_WB_stops[8] = stop_CC_WB_9;

    CC_EB_distances = new double[7];
    CC_EB_distances[0] = 4;
    CC_EB_distances[1] = 4;
    CC_EB_distances[2] = 2;
    CC_EB_distances[3] = 19;
    CC_EB_distances[4] = 1;
    CC_EB_distances[5] = 1;
    CC_EB_distances[6] = 2;

    CC_WB_distances = new double[8];
    CC_WB_distances[0] = 2;
    CC_WB_distances[1] = 1;
    CC_WB_distances[2] = 2;
    CC_WB_distances[3] = 19;
    CC_WB_distances[4] = 3;
    CC_WB_distances[5] = 3;
    CC_WB_distances[6] = 2;
    CC_WB_distances[7] = 3;

    // std::list<double> CC_EB_probs;  //realistic .15, .3, .025, .05, .05, 0
    CC_EB_probs.push_back(.15);   // WB
    CC_EB_probs.push_back(.3);    // CMU
    CC_EB_probs.push_back(.025);  // O&W
    CC_EB_probs.push_back(.05);   // Pre-transit
    CC_EB_probs.push_back(.05);   // post-transit
    CC_EB_probs.push_back(.01);   // State fair
    CC_EB_probs.push_back(.01);   // Buford
    CC_EB_probs.push_back(0);     // SPSC - MUST BE 0

    // std::list<double> CC_WB_probs; //realistic .35, .05, .01, .01, .2, 0
    CC_WB_probs.push_back(.35);     // SPSC
    CC_WB_probs.push_back(.05);     // Buford
    CC_WB_probs.push_back(.01);     // State fair
    CC_WB_probs.push_back(.01);     // post-transit
    CC_WB_probs.push_back(.025);    // pre-transit
    CC_WB_probs.push_back(.05);     // Ridder
    CC_WB_probs.push_back(.1);      // Jones-Eddy
    CC_WB_probs.push_back(.3);      // Bruininks
    CC_WB_probs.push_back(0);       // Blegen

    CC_EB_generator = new RandomPassengerGenerator(CC_EB_probs, CC_EB_stops_list);
    CC_WB_generator = new RandomPassengerGenerator(CC_WB_probs, CC_WB_stops_list);

    CC_EB = new Route("Campus Connector - Eastbound", CC_EB_stops, CC_EB_distances, 8, CC_EB_generator);
    CC_WB = new Route("Campus Connector - Westbound", CC_WB_stops, CC_WB_distances, 9, CC_WB_generator);
    int cc1_counter = 10000;
    test_bus = new Bus(std::to_string(cc1_counter), CC_EB, CC_WB, 60, 1);
  }

    virtual void TearDown() {
    	delete CC_EB;
			for (int i=0; i<8; i++)
					delete CC_EB_stops[i];
			delete CC_EB_stops;
			delete CC_EB_distances;

      delete CC_WB;
      for (int i=0; i<9; i++)
          delete CC_WB_stops[i];
      delete CC_WB_stops;
      delete CC_WB_distances;
      delete test_bus;
  	}
};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(BusTests, Constructor) {
    int cc1_counter = 10000;
    test_bus = new Bus(std::to_string(cc1_counter), CC_EB, CC_WB, 60, 1);
    std::string output = test_bus->GetName();
    std::string expected = std::to_string(cc1_counter);
    EXPECT_EQ(output, expected);
};

TEST_F(BusTests, LoadPassenger) {
    int cc1_counter = 10000;
    test_bus = new Bus(std::to_string(cc1_counter), CC_EB, CC_WB, 60, 1);

    int max_pass = 10;
    Passenger* passengers[max_pass];

    for (int i=0; i<max_pass; i++){
        passengers[i] = new Passenger(int(i%10), std::to_string(i));
        test_bus->LoadPassenger(passengers[i]);
    }
    std::string output = std::to_string(test_bus->GetNumPassengers());
    std::string expected = std::to_string(max_pass);
    EXPECT_EQ(output, expected);
};

TEST_F(BusTests, LoadPassenger_Max) {
    int cc1_counter = 10000;
    test_bus = new Bus(std::to_string(cc1_counter), CC_EB, CC_WB, 60, 1);

    int max_pass = 100;
    Passenger* passengers[max_pass];

    for (int i=0; i<max_pass; i++){
        passengers[i] = new Passenger(int(i%10), std::to_string(i));
        test_bus->LoadPassenger(passengers[i]);
    }
    std::string output = std::to_string(test_bus->GetNumPassengers());
    std::string expected = std::to_string(test_bus->GetCapacity());
    EXPECT_EQ(output, expected);
};

TEST_F(BusTests, Update_1) {
    int cc1_counter = 10000;
    test_bus = new Bus(std::to_string(cc1_counter), CC_EB, CC_WB, 60, 1);

    int round = 2;
    for (int i=0; i<round; i++){
      test_bus->Update();
    }
    Stop * next_stop = test_bus->GetNextStop();
    std::string output = std::to_string(next_stop->GetId());
    Stop * expected_next_stop = CC_EB_stops_list.front();
    std::string expected = std::to_string(expected_next_stop->GetId());
    EXPECT_EQ(output, expected);
};

TEST_F(BusTests, Update_2) {
  int cc1_counter = 10000;
  test_bus = new Bus(std::to_string(cc1_counter), CC_EB, CC_WB, 60, 1);

  int round = 6;
  for (int i=0; i<round; i++){
    test_bus->Update();
  }
  Stop * next_stop = test_bus->GetNextStop();
  std::string output = std::to_string(next_stop->GetId());

  CC_EB_stops_list.pop_front();
  Stop * expected_next_stop = CC_EB_stops_list.front();
  std::string expected = std::to_string(expected_next_stop->GetId());
  EXPECT_EQ(output, expected);
};

TEST_F(BusTests, DataStruct_ID) {
  int cc1_counter = 10000;
  test_bus = new Bus(std::to_string(cc1_counter), CC_EB, CC_WB, 60, 1);
  test_bus->Update();

  std::string output = test_bus->GetBusData().id;
  std::string expected = std::to_string(cc1_counter);
  EXPECT_EQ(output, expected);
};

TEST_F(BusTests, UnloadPassenger) {
  int cc1_counter = 10000;
  test_bus = new Bus(std::to_string(cc1_counter), CC_EB, CC_WB, 60, 1);

  int max_pass = 16;
  Passenger* passengers[max_pass];

  for (int i=0; i<max_pass; i++) {
      int dest_stop = i+1;
      passengers[i] = new Passenger(dest_stop, std::to_string(i+1));
      test_bus->LoadPassenger(passengers[i]);
  }
  while (!test_bus->IsTripComplete()) {
    test_bus->Update();
  }
  std::string output = std::to_string(test_bus->GetNumPassengers());
  std::string expected = std::to_string(0);
  EXPECT_EQ(output, expected);
};
