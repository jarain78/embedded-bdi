/*
 * intention.cpp
 *
 *  Created on: May 25, 2020
 *      Author: Matuzalem Muller
 */

#include "intention.h"

Intention::Intention() {} // @suppress("Class members should be properly initialized")

Intention::Intention(Plan plan, int size) {
  _size = size;
  _plans.init(size);
  _plans.push(plan.get_body());
}

Intention::~Intention() {}

void Intention::add_plan(Plan plan) {
  if (!_plans.is_full())
  {
    _plans.push(plan.get_body());
  }
}

bool Intention::run_intention(BeliefBase beliefs, EventBase events) { return true; }

bool Intention::is_finished() const{ return true; }
