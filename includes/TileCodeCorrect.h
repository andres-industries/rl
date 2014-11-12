/*
 * TileCodeCorrect.h
 *
 *  Created on: Jun 15, 2014
 *      Author: jandres
 */

#ifndef TILECODECORRECT_H_
#define TILECODECORRECT_H_

#include <vector>
#include <random>
#include <cmath>

#include "TileCode.h"

using namespace std;

namespace AI {
namespace Algorithm {

/*! \class TileCodeCorrect
 *  \brief The recommend implementation of Tile Coding for medium size state-space.
 *
 *  This is called TileCodeCorrect, since feature vector are generated by careful
 *  offsetting ensuring the feature vectors are unique, in contrast to hashing alternatives
 *  in which there might be a collision thus feature vectors might not be unique. Although
 *  it is correct, it consumes more space than hashing alternative, making it impractical
 *  for high dimensional state-spaces.
 */
class TileCodeCorrect : public TileCode {
 public:
  /**
   * @param dimensionalInfos A vector dimensionalInfos.
   * @param numTilings The higher the value, the more accurate is the
   * 			generalization.
   */
  TileCodeCorrect(vector<DimensionInfo<FLOAT> > dimensionalInfos,
                  size_t numTilings);

  virtual void getFeatureVector(const STATE_CONT& parameters,
                                FEATURE_VECTOR& fv);

};

} /* namespace Algorithm */
} /* namespace AI */

inline AI::Algorithm::TileCodeCorrect::TileCodeCorrect(
    vector<DimensionInfo<FLOAT> > dimensionalInfos, size_t numTilings)
    : TileCode(dimensionalInfos, numTilings) {
}

inline void AI::Algorithm::TileCodeCorrect::getFeatureVector(
    const STATE_CONT& parameters, FEATURE_VECTOR& fv) {
  assert(this->getDimension() == parameters.size());

  for (AI::INT i = 0; i < this->_numTilings; i++) {
    vector<AI::INT> tileComponents(this->getDimension());
    for (size_t j = 0; j < this->getDimension(); j++) {
      tileComponents[j] = this->_paramToGridValue(parameters[j], i, j);
    }

    // x1 + x2*x1.gridSize + x3*x1.gridSize*x2.gridSize + ...
    size_t hashedIndex = 0;
    size_t tileComponentMultiplier = 1;
    for (size_t j = 0; j < this->getDimension(); j++) {
      hashedIndex += tileComponents[j] * tileComponentMultiplier;
      tileComponentMultiplier *= this->_dimensionalInfos[j].GetGridCountReal();
    }

    hashedIndex += tileComponentMultiplier * i;
    fv.push_back(hashedIndex);
  }
}

#endif /* TILECODECORRECT_H_ */
