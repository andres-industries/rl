/*
 * GradientDescent.h
 *
 *  Created on: Jun 11, 2014
 *      Author: jandres
 */
#ifndef _GRADIENT_DESCENT_H_
#define _GRADIENT_DESCENT_H_

#include "../../declares.h"

#include <set>
#include <map>
#include <vector>
#include <cstdlib>
#include <x86intrin.h>

#include "../../coding/TileCode.h"

using namespace std;

namespace rl {

using namespace coding;

namespace algorithm {

/*! \class GradientDescent
 *  \brief Early implementation of Gradient Descent specialized for Tile Coding.
 */
class GradientDescent {
 public:
  /**
   * @param tileCode Type of tile coding.
   * @param stepSize Step size for gradient descent.
   * @param discountRate discount rate for gradient descent.
   * @param lambda How influential is current state-action to ther state-action.
   */
  GradientDescent(TileCode& tileCode, rl::FLOAT stepSize,
                  rl::FLOAT discountRate, rl::FLOAT lambda);

  virtual ~GradientDescent();

  /**
   * @return Size of both weight vector and traces vector.
   */
  size_t getSize() const;

  /**
   * Get the value of the parameters in the real space.
   * @param parameters
   * @return corresponding value.
   */
  FLOAT getValueFromParameters(const vector<FLOAT>& parameters) const;

  /**
   * Get the value of the parameters in the real space.
   * @param featureVector
   * @return corresponding value.
   */
  FLOAT getValueFromFeatureVector(const FEATURE_VECTOR& fv) const;

  /**
   * @param parameters parameters.
   * @param fv feature vector output. Feature vector are samples taken around
   *           the parameters in the n-dimension tilecde.
   */
  FEATURE_VECTOR getFeatureVector(const vector<FLOAT>& parameters) const;

  /**
   * Increase the eligibility traces of a given feature vector.
   * Note: This is loads faster than replace elibility traces.
   * @param fv feature vector.
   */
  void incrementEligibilityTraces(const FEATURE_VECTOR& fv);

  /**
   * Replace the eligibility traces for each feature vector by 1.0F.
   * @param fv feature vector.
   */
  void replaceEligibilityTraces(const FEATURE_VECTOR& fv);

  /**
   * Decrease each eligibility traces by eligibility traces and discount rate $(\lambda)$
   */
  void decreaseEligibilityTraces();

  /**
   * Make all eligibility trace to 0.0F.
   */
  void resetEligibilityTraces();

  /**
   * @param currentStateVector array of current states.
   * @param actionVector action taken to get to nextStateVector.
   * @param nextStateVector array of next states.
   * @param reward reward for taking nextAction.
   */
  void updateWeights(const STATE_CONT& currentStateVector,
                     const ACTION_CONT& currentActionVector,
                     const STATE_CONT& nextStateVector,
                     const FLOAT nextActionValue, const FLOAT reward);

  /**
   * @param actionSet set of actions.
   * @param param array of current state.
   * @param actionVectorValueMap state-action to value mapping to be returned.
   * @param maxAction max action calculated while building action value map.
   */
  void buildActionValues(
      const set<ACTION_CONT>& actionSet, const vector<FLOAT>& param,
      map<ACTION_CONT, FLOAT>& actionVectorValueMap,
      ACTION_CONT& maxAction) const;

  /**
   * @param actionValueMap state-action to value mapping.
   * @return value.
   */
  FLOAT getMaxValue(
      const map<ACTION_CONT, FLOAT>& actionValueMap) const;

  /**
   * Update weights with tderror.
   * @param tdError
   */
  virtual void backUpWeights(FLOAT tdError);

 protected:
  TileCode& _tileCode;  //!< Tile Code.
  rl::FLOAT* _w;  //!< Vector of weights.
  rl::FLOAT* _e;  //!< Vector of eligibility traces.
  rl::FLOAT _stepSize;  //!< Step Size of the weight update.
  rl::FLOAT _discountRate;  //!< Discount rate, mix with _lambda on how past states
  //!< influence current.
  rl::FLOAT _lambda;  //!< lambda, mix with _lambda on how past states influence current.

  // Optimization.
  rl::FLOAT _discountRateTimesLambda;
  rl::FLOAT* _discountRateTimesLambdaArray;
};

} // namespace algorithm
} // namespace rl

#endif // _GRADIENT_DESCENT_H_