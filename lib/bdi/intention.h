/*
 * intention.h
 *
 *  Created on: May 25, 2020
 *      Author: Matuzalem Muller
 */

#ifndef BDI_INTENTION_H_
#define BDI_INTENTION_H_

#include "plan_base.h"
#include "belief_base.h"
#include "instantiated_plan.h"
#include <vector>
#include <cstdint>

class Intention
{
private:
  /// Vector of InstantiatedPlan that represents Intention stack
  std::vector <InstantiatedPlan> _plans;
  /// Max size of _plans stack
  uint8_t _size;
  /// Identified of Event that suspends intention from running
  EventID * _suspended_by;

  /**
   * Suspend intention. Intentions should be suspended when the instruction
   * ran on run_intention is added to the EventBase and no further instructions
   * can be run without processing the event first
   * @param event_id Pointer to EventID that blocks the intention from running
   */
  void suspend(EventID * event_id);

  /**
   * Unsuspend intention so instructions can be run
   */
  void unsuspend();

public:
  /**
   * Intention constructor
   * @param plan Pointer to plan to be instantiated as intention
   * @param size Size of _plans stack
   */
  Intention(Plan * plan, uint8_t size);

  virtual ~Intention();

  /**
   * Stack plan in _plan stack
   * @param plan Plan to be stacked
   * @return true if plan is added, false otherwise. False means that size of
   * _plans stack was exceeded and intention should likely be dropped
   */
  bool stack_plan(Plan * plan);

  /**
   * Run one instruction from plan from the top of _plans stack
   * @param beliefs Agent's BeliefBase
   * @param events Agent's EventBase
   * @return
   */
  bool run_intention(BeliefBase * beliefs, EventBase * events);

  /**
   * Check if intention is suspended by given event
   * @param event EventBase
   * @return true if Intention is suspended and _suspended_by still exists
   * in EventBase, false otherwise
   */
  bool is_suspended_by(Event * event);

  /**
   * Checks if intention execution finished based on size of _plans
   * @return true if intention is finished, false otherwise
   */
  bool is_finished() const;

  /**
   * Handles termination by adding goal deletion events to EventBase
   * @param beliefs Agent BeliefBase
   * @param events Agent EventBase where events will be added
   * @param plans Agent PlanBase where fail plans will be searched
   */
  void terminate(BeliefBase * beliefs, EventBase * events, PlanBase * plans);

  /**
   * Checks if event is suspended
   * @return true if suspended, false otherwise
   */
  bool is_suspended();

  EventID * get_event_id()
  {
    return _suspended_by;
  }
};

#endif /* BDI_INTENTION_H_ */
