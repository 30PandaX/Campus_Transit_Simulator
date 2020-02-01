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
#include "../src/stop.h"

/******************************************************
* TEST FEATURE SetUp
*******************************************************/

class StopTests : public ::testing::Test {

	protected:

  	Stop* stop;

	virtual void SetUp() {
    	stop = new Stop(1);
  	}

  	virtual void TearDown() {
    	delete stop;
  	}

};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(StopTests, Constructor) {
  	EXPECT_EQ(stop->GetId(), 1);
};

TEST_F(StopTests, AddPass) {
    Passenger* a = new Passenger(2, "Amy");
    Passenger* b = new Passenger(3, "Belly");
    // Passenger c = new Passenger(4, "Cindy");
    // Passenger d = new Passenger(3, "Daniel");

    int expected_total = 0;
    expected_total += stop->AddPassengers(a);
    expected_total += stop->AddPassengers(b);
    // expected_total += AddPassengers(c);
    // expected_total += AddPassengers(d);

    testing::internal::CaptureStdout();
		stop->Report();
		std::string output = testing::internal::GetCapturedStdout();
		std::string expected = "ID: 1\nPassengers waiting: 2\n";
    std::string expected_a = "Name: Amy\nDestination: 2\nTotal Wait: 0\n\tWait at Stop: 0\n\tTime on bus: 0\n";
    std::string expected_b = "Name: Belly\nDestination: 3\nTotal Wait: 0\n\tWait at Stop: 0\n\tTime on bus: 0\n";
    expected = expected + expected_a + expected_b;
		EXPECT_EQ(output, expected);
};

TEST_F(StopTests, AddAlotPass) {
    int max_pass = 100;
    Passenger* passengers[max_pass];
		int expected_total = 0;
    for (int i=0; i<max_pass; i++){
	      passengers[i] = new Passenger(int(i%10), std::to_string(i));
				expected_total += stop->AddPassengers(passengers[i]);
    }

    testing::internal::CaptureStdout();
		stop->Report();
		std::string output = testing::internal::GetCapturedStdout();

		std::string expected = "ID: 1\nPassengers waiting: ";
		std::string pass_waits = std::to_string(max_pass) + "\n";
		std::string pass_report;
		for (int i=0; i<max_pass; i++){
    		pass_report = pass_report
												+ "Name: " + std::to_string(i) + "\nDestination: "
												+ std::to_string(int(i%10))
												+ "\nTotal Wait: 0\n\tWait at Stop: 0\n\tTime on bus: 0\n";
    }
		expected = expected + pass_waits + pass_report;
		EXPECT_EQ(output, expected);
};

TEST_F(StopTests, Update) {
    int max_pass = 100;
    Passenger* passengers[max_pass];
		int expected_total = 0;
    for (int i=0; i<max_pass; i++){
	      passengers[i] = new Passenger(int(i%10), std::to_string(i));
				expected_total += stop->AddPassengers(passengers[i]);
    }

		int frames = 10;
		for (int i=0; i<frames; i++)
			stop->Update();

    testing::internal::CaptureStdout();
		stop->Report();
		std::string output = testing::internal::GetCapturedStdout();

		std::string expected = "ID: 1\nPassengers waiting: ";
		std::string pass_waits = std::to_string(max_pass) + "\n";
		std::string pass_report;
		for (int i=0; i<max_pass; i++){
    		pass_report = pass_report
												+ "Name: " + std::to_string(i) + "\nDestination: "
												+ std::to_string(int(i%10))
												+ "\nTotal Wait: " + std::to_string(frames) + "\n\t"
												+ "Wait at Stop: " + std::to_string(frames) + "\n\t"
												+ "Time on bus: 0\n";
    }
		expected = expected + pass_waits + pass_report;
		EXPECT_EQ(output, expected);
};
