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

#include "hash/HashUNH.h"
#include "unh/UNH.h"

namespace rl {
namespace hash {

INT UNH::hash(const rl::BYTE * const byteArray, size_t len) {
  return hashUNH((rl::INT*) byteArray, len * sizeof(rl::INT), 4096);
}

INT UNH::hash(const vector<rl::BYTE>& msg) {
  return hashUNH((rl::INT*) msg.data(), msg.size() * sizeof(rl::INT), 4096);
}

}  // namespace hash
}  // namespace rl
