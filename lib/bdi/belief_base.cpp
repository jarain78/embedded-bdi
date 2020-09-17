/*
 * belief_base.cpp
 *
 *  Created on: May 25, 2020
 *      Author: Matuzalem Muller
 */

#include "belief_base.h"

BeliefBase::BeliefBase(std::uint8_t size)
{
  _size = size;
  _belief_base.init(size);
}

BeliefBase::~BeliefBase() {}

bool BeliefBase::add_belief(Belief belief)
{
  if (_belief_base.size() == _size)
  {
    return false;
  }

  _belief_base.add_front(belief);
  return true;
}

void BeliefBase::update(EventBase * event_base)
{
  if (event_base)
  {
    for (std::uint8_t i = 0; i < _belief_base.size(); i++)
    {
      if (_belief_base.item_at(i)->update_belief())
      {
        if (!event_base->is_full())
        {
          if (_belief_base.item_at(i)->get_state())
          {
            // Add Event for BELIEF_ADDITION if belief is changed to true
            event_base->add_event(EventOperator::BELIEF_ADDITION,
                                  _belief_base.item_at(i)->get_statement()
            );
          } else {
            // Add Event for BELIEF_DELETION if belief is changed to false
            event_base->add_event(EventOperator::BELIEF_DELETION,
                                  _belief_base.item_at(i)->get_statement()
            );
          }
        }
      }
    }

  }
}

bool BeliefBase::change_belief_state(Statement stm, bool state)
{
  for (std::uint8_t i = 0; i < _belief_base.size(); i++)
  {
    if (_belief_base.item_at(i)->get_statement().is_equal(stm.get_name()))
    {
      _belief_base.item_at(i)->change_state(state);
      return true;
    }
  }

  return false;
}

bool BeliefBase::get_belief_state(Statement stm)
{
  for (std::uint8_t i = 0; i < _belief_base.size(); i++)
  {
    if (_belief_base.item_at(i)->get_statement().is_equal(stm))
    {
      return _belief_base.item_at(i)->get_state();
    }
  }

  return false;
}

const std::uint8_t BeliefBase::get_size()
{
  return _belief_base.size();
}

