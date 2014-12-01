/*
 * TileCodeCorrect.h
 *
 *  Created on: Jun 15, 2014
 *      Author: jandres
 */

#ifndef TILECODECORRECT_H_
#define TILECODECORRECT_H_

#include <vector>
#include <map>
#include <random>
#include <cmath>

#include "TileCode.h"

using namespace std;

namespace AI {
namespace Algorithm {
namespace SL {

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
  TileCodeCorrect(vector<DimensionInfo<FLOAT> >& dimensionalInfos,
                  size_t numTilings);

  virtual FEATURE_VECTOR getFeatureVector(const STATE_CONT& parameters);

 protected:
  vector<vector<UINT> > _tileComponentMultiplier;
};

} // namespace SL
} // namespace Algorithm
} // namespace AI

#endif /* TILECODECORRECT_H_ */
