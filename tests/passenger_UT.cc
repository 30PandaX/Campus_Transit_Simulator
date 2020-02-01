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
#include "../src/passenger.h"

/******************************************************
* TEST FEATURE SetUp
*******************************************************/

class PassengerTests : public ::testing::Test {

	protected:

  	Passenger* passenger;

	virtual void SetUp() {
    	passenger = new Passenger();
  	}

  	virtual void TearDown() {
    	delete passenger;
  	}

};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(PassengerTests, Constructor) {
  	EXPECT_EQ(passenger->IsOnBus(), false);
  	passenger->GetOnBus();
  	EXPECT_EQ(passenger->IsOnBus(), true);
};

TEST_F(PassengerTests, UpdateWait) {
		EXPECT_EQ(passenger->IsOnBus(), false);
		for (int i=0; i<10; i++)
			passenger->Update();
  	EXPECT_EQ(passenger->GetTotalWait(), 10);
};

TEST_F(PassengerTests, ReportAtStop) {
		EXPECT_EQ(passenger->IsOnBus(), false);
		for (int i=0; i<18; i++)
			passenger->Update();
		testing::internal::CaptureStdout();
		passenger->Report();
		std::string output = testing::internal::GetCapturedStdout();
		std::string expected = "Name: Nobody\nDestination: -1\nTotal Wait: 18\n\tWait at Stop: 18\n\tTime on bus: 0\n";
		EXPECT_EQ(output, expected);

};

TEST_F(PassengerTests, ReportOnBus) {
		EXPECT_EQ(passenger->IsOnBus(), false);
		for (int i=0; i<10; i++)
			passenger->Update();
		passenger->GetOnBus();
		for (int i=0; i<10; i++)
			passenger->Update();
		testing::internal::CaptureStdout();
		passenger->Report();
		std::string output = testing::internal::GetCapturedStdout();
		std::string expected = "Name: Nobody\nDestination: -1\nTotal Wait: 21\n\tWait at Stop: 10\n\tTime on bus: 11\n";
		EXPECT_EQ(output, expected);

};

TEST_F(PassengerTests, ReportRename) {
		EXPECT_EQ(passenger->IsOnBus(), false);
		passenger= new Passenger(5, "Panda");

		for (int i=0; i<10; i++)
			passenger->Update();
		passenger->GetOnBus();
		for (int i=0; i<10; i++)
			passenger->Update();
		testing::internal::CaptureStdout();
		passenger->Report();
		std::string output = testing::internal::GetCapturedStdout();
		std::string expected = "Name: Panda\nDestination: 5\nTotal Wait: 21\n\tWait at Stop: 10\n\tTime on bus: 11\n";
		EXPECT_EQ(output, expected);

};

TEST_F(PassengerTests, ReportRename_b) {
		EXPECT_EQ(passenger->IsOnBus(), false);
		passenger= new Passenger(5, "Panda");
		for (int i=0; i<10; i++)
			passenger->Update();
		passenger->GetOnBus();
		for (int i=0; i<10; i++)
			passenger->Update();

		std::ofstream outfile;
		outfile.open("PassengerReport.txt");
		passenger->Report(outfile);
		outfile.close();

		std::ifstream infile;
		infile.open("PassengerReport.txt");
		std::string output;
		getline (infile, output, '\0');
		infile.close();

		std::string expected = "Name: Panda\nDestination: 5\nTotal Wait: 21\n\tWait at Stop: 10\n\tTime on bus: 11\n";
		EXPECT_EQ(output, expected);
};
