/*
 * File:   StateInterface.h
 * Author: jandres
 *
 * Created on November 11, 2016, 4:55 AM
 */

#pragma once

namespace AI {
/*! \class StateInterface
 *  \brief An interface class for States.
 *  \tparam S State data type.
 */
template<class S>
class StateInterface {
 public:
  StateInterface(const S& value) : _value(value) {}

  virtual bool operator<(const StateInterface<S>& rhs) const {
    return this->_value < rhs._value;
  }

  virtual bool operator>(const StateInterface<S>& rhs) const {
    return this->_value > rhs._value;
  }

  virtual bool operator<=(const StateInterface<S>& rhs) const {
    return this->_value <= rhs._value;
  }

  virtual bool operator>=(const StateInterface<S>& rhs) const {
    return this->_value >= rhs._value;
  }

  virtual bool operator==(const StateInterface<S>& rhs) const {
    return this->_value == rhs._value;
  }

  virtual bool operator!=(const StateInterface<S>& rhs) const {
    return this->_value != rhs._value;
  }

  virtual StateInterface<S>& operator=(StateInterface<S>& rhs) {
    if (this == &rhs) {
      return *this;
    }

    this->_value = rhs._value;
    return *this;
  }

  virtual S& getValue() {
    return this->_value;
  }

  virtual const S& getValue() const {
    return this->_value;
  }

 protected:
  S _value;  // Value of this thing.
};
}