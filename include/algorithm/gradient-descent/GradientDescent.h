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

#pragma once

#include <algorithm>
#include <vector>
#include <array>

#include "../../declares.h"
#include "../../coding/TileCode.h"
#include "GradientDescentAbstract.h"

using std::vector;
using std::array;

using rl::coding::spTileCode;

namespace rl {
namespace algorithm {

/*! \class GradientDescent
 *  \brief Gradient Descent implementation.
 *  \tparam D Number of dimension.
 *  \tparam NUM_TILINGS Number of tilings.
 *  \tparam STATE_DIM Number of dimension in State.
 *                    This also implies ACTION_DIM = D - STATE_DIM.
 */
template <size_t D, size_t NUM_TILINGS, size_t STATE_DIM>
class GradientDescent :
  public GradientDescentAbstract<D, NUM_TILINGS, STATE_DIM> {
 public:
  using GradientDescentAbstract<
    D, NUM_TILINGS, STATE_DIM>::GradientDescentAbstract;

  void updateWeights(
    const typename GradientDescentAbstract<
      D,
      NUM_TILINGS,
      STATE_DIM>::spStateParam& currentStateVector,
    const typename GradientDescentAbstract<
      D,
      NUM_TILINGS,
      STATE_DIM>::spActionParam& currentActionVector,
    const typename GradientDescentAbstract<
      D,
      NUM_TILINGS,
      STATE_DIM>::spStateParam& nextStateVector,
    const FLOAT nextActionValue,
    const FLOAT reward) override;
};

template <size_t D, size_t NUM_TILINGS, size_t STATE_DIM>
void GradientDescent<D, NUM_TILINGS, STATE_DIM>::updateWeights(
  const typename GradientDescentAbstract<
    D,
    NUM_TILINGS,
    STATE_DIM>::spStateParam& currentStateVector,
  const typename GradientDescentAbstract<
    D,
    NUM_TILINGS,
    STATE_DIM>::spActionParam& currentActionVector,
  const typename GradientDescentAbstract<
    D,
    NUM_TILINGS,
    STATE_DIM>::spStateParam& nextStateVector,
  const FLOAT nextActionValue,
  const FLOAT reward) {
  floatArray<D> currentParams;
  std::copy(currentStateVector->begin(),
            currentStateVector->end(),
            currentParams.begin());
  std::copy(currentActionVector->begin(),
            currentActionVector->end(),
            currentParams.begin() + currentStateVector->size());

  FEATURE_VECTOR currentStateFv =
    std::move(this->getFeatureVector(currentParams));

  FLOAT tdError = reward + this->_discountRate * nextActionValue
    - this->getValueFromFeatureVector(currentStateFv);

  for (auto f : currentStateFv) {
    this->_w[f] += tdError * this->_stepSize;
  }
}

}  // namespace algorithm
}  // namespace rl
