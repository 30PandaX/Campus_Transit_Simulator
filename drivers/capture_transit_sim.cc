/**
 * @file local_simulator.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#include <ctime>
#include <iostream>
#include <random>
#include <fstream>


#include "./local_simulator.h"

int main(int argc, char *argv[]) {
  int rounds = 100;  // Number of rounds of generation to simulate in test
  srand(static_cast<int64_t>(time(NULL)));
  // Seed the random number generator...
  std::ofstream outfile;
  if (argc != 2) {
    printf("Put in a path/filename as argument\n");
    printf("For example: run13.txt\n");

    exit(0);
  }
  outfile.open(argv[1]);

  LocalSimulator my_sim = LocalSimulator(&outfile);


  outfile << "/*************************" << std::endl << std::endl;
  outfile << "         STARTING" << std::endl;
  outfile << "        SIMULATION" << std::endl;
  outfile << "*************************/" << std::endl;

  my_sim.Start();

  outfile << "/*************************" << std::endl << std::endl;
  outfile << "           BEGIN" << std::endl;
  outfile << "          UPDATING" << std::endl;
  outfile << "*************************/" << std::endl;

  for (int i = 0; i < rounds; i++) {
      my_sim.Update();
  }

  outfile << "/*************************" << std::endl << std::endl;
  outfile << "        SIMULATION" << std::endl;
  outfile << "         COMPLETE" << std::endl;
  outfile << "*************************/" << std::endl;

  outfile.close();

  return 0;
}
