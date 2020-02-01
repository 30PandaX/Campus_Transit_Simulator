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
 #include "../src/configuration_simulator.h"


/******************************************************
* TEST FEATURE SetUp
*******************************************************/

class ConfigTests : public ::testing::Test {

	protected:

    int argc;
    const char ** argv;
    ConfigManager* configM;
    ConfigurationSimulator* config_sim;


	virtual void SetUp() {
    argc = 0;
    argv = new const char*[argc];
    argv[0] = "./build/bin/config_sim";
    configM = new ConfigManager();
    config_sim = new ConfigurationSimulator(configM, argc, argv);
  }

  virtual void TearDown() {
    	delete configM;
      delete config_sim;

  	}

};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(ConfigTests, Constructor) {
  std::string output = std::to_string(config_sim->ArgsChecker());
  std::string expected = std::to_string(0);
  EXPECT_EQ(output, expected); //default success
};

TEST_F(ConfigTests, SuccessFileName) {
  argc = 2;
  argv = new const char*[argc];
  argv[1] = "config.txt";
  config_sim = new ConfigurationSimulator(configM, argc, argv);

  std::string output = std::to_string(config_sim->ArgsChecker());
  std::string expected = std::to_string(0);
  EXPECT_EQ(output, expected); //default success
};

TEST_F(ConfigTests, WrongFileName) {
  argc = 2;
  argv = new const char*[argc];
  argv[1] = "dlufsafjld";
  config_sim = new ConfigurationSimulator(configM, argc, argv);

  std::string output = std::to_string(config_sim->ArgsChecker());
  std::string expected = std::to_string(4);
  EXPECT_EQ(output, expected); // wrong filename
};

TEST_F(ConfigTests, SuccessRounds) {
  argc = 3;
  argv = new const char*[argc];
  argv[1] = "config.txt";
  argv[2] = "10";

  config_sim = new ConfigurationSimulator(configM, argc, argv);

  std::string output = std::to_string(config_sim->ArgsChecker());
  std::string expected = std::to_string(0);
  EXPECT_EQ(output, expected);
};

TEST_F(ConfigTests, WrongRounds) {
  argc = 3;
  argv = new const char*[argc];
  argv[1] = "config.txt";
  argv[2] = "-1";

  config_sim = new ConfigurationSimulator(configM, argc, argv);

  std::string output = std::to_string(config_sim->ArgsChecker());
  std::string expected = std::to_string(3);
  EXPECT_EQ(output, expected);
};

TEST_F(ConfigTests, SuccessTiming) {
  argc = 4;
  argv = new const char*[argc];
  argv[1] = "config.txt";
  argv[2] = "10";
  argv[3] = "100";

  config_sim = new ConfigurationSimulator(configM, argc, argv);

  std::string output = std::to_string(config_sim->ArgsChecker());
  std::string expected = std::to_string(0);
  EXPECT_EQ(output, expected);
};

TEST_F(ConfigTests, WrongTiming) {
  argc = 4;
  argv = new const char*[argc];
  argv[1] = "config.txt";
  argv[2] = "10";
  argv[3] = "fbhahwrio aewru234 890uy34298 fdhsoiuhw34r hweif wehfioew ";

  config_sim = new ConfigurationSimulator(configM, argc, argv);

  std::string output = std::to_string(config_sim->ArgsChecker());
  std::string expected = std::to_string(2);
  EXPECT_EQ(output, expected);
};

TEST_F(ConfigTests, WrongArgsLenth_1) {
  argc = 5;
  argv = new const char*[argc];
  argv[1] = "config.txt";
  argv[2] = "10";
  argv[3] = "10";
  argv[4] = "fbhahwrio aewru234 890uy34298 fdhsoiuhw34r hweif wehfioew ";

  config_sim = new ConfigurationSimulator(configM, argc, argv);

  std::string output = std::to_string(config_sim->ArgsChecker());
  std::string expected = std::to_string(1);
  EXPECT_EQ(output, expected);
};

TEST_F(ConfigTests, WrongArgsLenth_2) {
  argc = 100;
  argv = new const char*[argc];
  argv[1] = "config.txt";
  argv[2] = "10";
  argv[3] = "10";
  for (int i=4; i<100; i++)
    argv[i] = "fbhahwrio aewru234 890uy34298 fdhsoiuhw34r hweif wehfioew ";

  config_sim = new ConfigurationSimulator(configM, argc, argv);

  std::string output = std::to_string(config_sim->ArgsChecker());
  std::string expected = std::to_string(1);
  EXPECT_EQ(output, expected);
};
