/*
 * Sarsa_test.cpp
 */

#include <vector>
#include <iostream>

#include "rl"

#include "RandomWalkEnvironment.h"
#include "SensorRandomWalk.h"

#include "../../lib/catch.hpp"

using std::vector;

using namespace std;

SCENARIO("QLearningETWatkins converge to a solution",
         "[rl::QLearningETWatkins]") {
  GIVEN("A random walk environment") {
    rl::agent::Actuator <rl::INT> arw(rl::spActionSet<rl::INT>({ L, R }));  // Setup actuator with actions.
    rl::SensorRandomWalk srw;  // Setup sensor.
    srw.addTerminalState(T);  // Setup terminal state.
    rl::RandomWalkEnvironment rwEnv(arw, srw);  // Setup environment.

    rl::policy::EpsilonGreedy <rl::INT, rl::INT> policy(1.0F);
    rl::algorithm::QLearningET <rl::INT, rl::INT> qLearningETWatkins(0.1F, 0.9F, policy, 0.5);

    rl::agent::Agent <rl::INT, rl::INT> agent(rwEnv, qLearningETWatkins);

    WHEN("We do multiple episodes") {
      rl::INT iterationCount = 0;
      for (rl::INT i = 0; i < 100; i++) {
        agent.reset();  // Overloaded to go back to set b.

        iterationCount = agent.executeEpisode();

        THEN("At the end, we solve the random walk environment in 2 iteration") {
          REQUIRE(iterationCount <= 2);
        }
      }
    }
  }
}
