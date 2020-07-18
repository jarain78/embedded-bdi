/*
 * goal.cpp
 *
 *  Created on: Jun 3, 2020
 *      Author: Matuzalem Muller
 */

#include "goal.h"

Goal::Goal() {} // @suppress("Class members should be properly initialized")

Goal::Goal(Statement stm, EventOperator event_type)
{
  _operator = event_type;
  _statement = stm;
}

Goal::~Goal() {}

BodyReturn Goal::run_instruction(BeliefBase * belief_base, EventBase * event_base)
{
  if (event_base->add_event(_operator, _statement))
  {
    BodyReturn result(_type, true, event_base->last_event()->get_event_id());
    return result;
  } else {
    BodyReturn result(_type, false, NULL);
    return result;
  }
}


