/*
 * stacked_intention.cpp
 *
 *  Created on: Sep 15, 2020
 *      Author: Matuzalem Muller
 */

#include "common_lib.h"
#include "gtest/gtest.h"
#include "agent/agent.h"
#include "configuration.h"

class TStackedIntention : public ::testing::Test
{
protected:
  Agent * agent;
  BeliefBase * beliefs;
  EventBase * events;
  PlanBase * plans;
  IntentionBase * intentions;
  StackedIntention * stacked_intention;

public:
  TStackedIntention()
  {
    stacked_intention = new StackedIntention();

    beliefs = stacked_intention->get_belief_base();
    events = stacked_intention->get_event_base();
    plans = stacked_intention->get_plan_base();
    intentions = stacked_intention->get_intention_base();

    agent = new Agent(beliefs, events, plans, intentions);
  }

  ~TStackedIntention()
  {
    delete this->stacked_intention;
    delete this->agent;
  }
};

TEST_F(TStackedIntention, run_stacked_intention)
{
  EXPECT_TRUE(intentions->is_empty());
  EXPECT_TRUE(events->is_full());

  agent->run();
  EXPECT_EQ(10, shared_var);
  EXPECT_TRUE(intentions->is_full());
  EXPECT_TRUE(events->is_empty());

  agent->run();
  EXPECT_TRUE(intentions->is_full());
  EXPECT_TRUE(events->is_full());

  agent->run();
  EXPECT_EQ(20, shared_var);
  EXPECT_TRUE(intentions->is_full());
  EXPECT_TRUE(events->is_empty());

  agent->run();
  EXPECT_TRUE(intentions->is_full());
  EXPECT_TRUE(events->is_full());

  agent->run();
  EXPECT_EQ(30, shared_var);
  EXPECT_TRUE(intentions->is_empty());
  EXPECT_TRUE(events->is_empty());

  agent->run();
  EXPECT_EQ(30, shared_var);
  EXPECT_TRUE(intentions->is_empty());
  EXPECT_TRUE(events->is_empty());

  agent->run();
  EXPECT_EQ(30, shared_var);
  EXPECT_TRUE(intentions->is_empty());
  EXPECT_TRUE(events->is_empty());
}
