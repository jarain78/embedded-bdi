/*
 * body_instruction.h
 *
 *  Created on: May 31, 2020
 *      Author: Matuzalem Muller
 */

#ifndef SYNTAX_BODY_BODY_INSTRUCTION_H_
#define SYNTAX_BODY_BODY_INSTRUCTION_H_

#include "body_type.h"
#include "body_return.h"
#include "../bdi/belief_base.h"
#include "../bdi/event_base.h"

/**
 * Body instructions can be belief operations, goal operations (adopt/drop
 * intention) or action in the environment. This class is used as an interface
 * by the Action, BeliefOperation and Goal classes.
 */
class BodyInstruction
{
private:
  /// Function to act in the environment
  bool (*_take_action)(bool var);
  Statement _statement;
  EventOperator _operator;
  /// Identifies whether the instruction is an Action, Goal or Belief operation
  BodyType _type;

public:
  /**
   * Constructor for Actions
   * @param type Type of body instruction
   * @param stm Statement that represents the Plan name
   * @param take_action Function that acts in the environment
   */
  BodyInstruction(BodyType type, Statement stm, bool (*take_action)(bool var));

  /**
   * Constructor for Belief and Goal events
   * @param type Type of body instruction
   * @param stm Statement that represents the Plan name
   * @param event_operator Event that will be generated by instruction
   */
  BodyInstruction(BodyType type, Statement stm, EventOperator event_operator);

  virtual ~BodyInstruction() {};

  /**
   * Run instruction. For BodyTypes:
   *   * Action: acts in the environment
   *   * Belief: Updates Belief and creates Belief addition/deletion Event
   *   * Goal: Creates Goal addition/deletion Event
   * @param belief_base Agent's BeliefBase
   * @param event_base Agent's EventBase
   */
  BodyReturn run_instruction(BeliefBase * belief_base, EventBase * event_base);

  BodyType get_BodyType()
  {
    return _type;
  }
};

#endif /* SYNTAX_BODY_BODY_INSTRUCTION_H_ */
