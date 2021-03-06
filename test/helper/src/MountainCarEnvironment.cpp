/**
 * rl - Reinforcement Learning
 * Copyright (C) 2016  Joey Andres<yeojserdna@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <cassert>
#include <cmath>
#include <iostream>

#include "rl"
#include "../include/MountainCarEnvironment.h"

MountainCarEnvironment::MountainCarEnvironment(
  const spActuator<floatArray<1>>& actuator,
  const spSensor<floatArray<2>>& sensor) :
  rl::agent::Environment<floatArray<2>, floatArray<1>>(actuator, sensor) {
}

rl::spStateAndReward<floatArray<2>>
MountainCarEnvironment::getNextStateAndReward(
  const MountainCarEnvironment::SA& stateAction) {
  auto act = rl::spFloatArray<1>(
    new rl::floatArray<1>(*stateAction.getAction()));

  /*if (act[0] < 0 || act[0] > 2) {
    cout << "Illegal" << endl;
    assert(false && "Action Set recognized.");
    }*/
  auto nextState = rl::spFloatArray<2>(
    new rl::floatArray<2>(*stateAction.getState()));

  rl::INT copyAct = act->at(0) - 1;
  rl::FLOAT nextReward = -1;
  if (copyAct == 0) {
    nextReward = -1;
  } else {
    nextReward = -2;
  }

  nextState->at(VEL) +=
      (0.001F * copyAct - 0.0025F * std::cos(3.0F * nextState->at(POS)));

  if (nextState->at(VEL) < -0.07F) {
    nextState->at(VEL) = -0.07F;
  } else if (nextState->at(VEL) >= 0.07F) {
    nextState->at(VEL) = 0.06999999F;
  }

  nextState->at(POS) += nextState->at(VEL);

  if (nextState->at(POS) >= 0.5F) {
    nextState->at(POS) = 0.5;
    nextReward = 0;
  } else if (nextState->at(POS) < -1.2F) {
    nextState->at(POS) = -1.2F;
    nextState->at(VEL) = 0.0F;
  }

  return { nextState, nextReward };
}

MountainCarEnvironmentFactory::MountainCarEnvironmentFactory(
  const spActuator<floatArray<1>>& actuator,
  const spSensor<floatArray<2>>& sensor) {
  this->_instance = spEnvironment<floatArray<2>, floatArray<1>>(
    new MountainCarEnvironment(actuator, sensor));
}
