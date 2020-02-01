/**
 * @file bus.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef SRC_RTEST_CONFIG_MANAGER_H_
#define SRC_RTEST_CONFIG_MANAGER_H_

#include <vector>
#include <string>


class Route;

class RtestConfigManager {
 public:
        RtestConfigManager();
        ~RtestConfigManager();

        bool ReadConfig(const std::string filename);

        std::vector<Route *> GetRoutes() const { return routes; }

 private:
        std::vector<Route *> routes;
};

#endif  // SRC_RTEST_CONFIG_MANAGER_H_
