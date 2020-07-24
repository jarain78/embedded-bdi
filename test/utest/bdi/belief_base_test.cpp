/*
 * belief_base.h
 *
 *  Created on: Jul 24, 2020
 *      Author: Matuzalem Muller
 */

#include "gtest/gtest.h"
#include "bdi/belief_base.h"

bool update_belief_true(bool var)
{
  return true;
}

bool update_belief_false(bool var)
{
  return false;
}

class TBeliefBase : public ::testing::Test
{
protected:
  BeliefBase * belief_base;
  EventBase * event_base;
  int size = 3;

public:
  TBeliefBase()
  {
    belief_base = new BeliefBase(size);
    event_base = new EventBase(size);
  }

  ~TBeliefBase()
  {
    delete belief_base;
    delete event_base;
  }
};

TEST_F(TBeliefBase, add_belief)
{
  Statement stm_a('a');
  Statement stm_b('b');
  Statement stm_c('c');

  Belief belief_a(stm_a, update_belief_true, false);
  Belief belief_b(stm_b, update_belief_false, true);
  Belief belief_c(stm_c, NULL, false);

  EXPECT_TRUE(belief_base->add_belief(belief_a));
  EXPECT_TRUE(belief_base->add_belief(belief_b));
  EXPECT_TRUE(belief_base->add_belief(belief_c));
  EXPECT_FALSE(belief_base->add_belief(belief_a));
}

TEST_F(TBeliefBase, get_belief_state)
{
  Statement stm_a('a');
  Statement stm_b('b');
  Statement stm_c('c');

  Belief belief_a(stm_a, update_belief_true, false);
  Belief belief_b(stm_b, update_belief_false, true);
  Belief belief_c(stm_c, NULL, false);

  belief_base->add_belief(belief_a);
  belief_base->add_belief(belief_b);
  belief_base->add_belief(belief_c);

  EXPECT_FALSE(belief_base->get_belief_state(stm_a));
  EXPECT_TRUE(belief_base->get_belief_state(stm_b));
  EXPECT_FALSE(belief_base->get_belief_state(stm_c));
}

TEST_F(TBeliefBase, update)
{
  Statement stm_a('a');
  Statement stm_b('b');
  Statement stm_c('c');

  Belief belief_a(stm_a, update_belief_true, false);
  Belief belief_b(stm_b, update_belief_false, true);
  Belief belief_c(stm_c, NULL, false);

  belief_base->add_belief(belief_a);
  belief_base->add_belief(belief_b);
  belief_base->add_belief(belief_c);

  belief_base->update(event_base);

  EXPECT_TRUE(belief_base->get_belief_state(stm_a));
  EXPECT_FALSE(belief_base->get_belief_state(stm_b));
  EXPECT_FALSE(belief_base->get_belief_state(stm_c));

  EXPECT_FALSE(event_base->is_full());
}

TEST_F(TBeliefBase, change_belief_state)
{
  Statement stm_a('a');
  Statement stm_b('b');
  Statement stm_c('c');

  Belief belief_a(stm_a, update_belief_true, false);
  Belief belief_b(stm_b, NULL, true);

  belief_base->add_belief(belief_a);
  belief_base->add_belief(belief_b);

  EXPECT_TRUE(belief_base->change_belief_state(stm_a, true));
  EXPECT_TRUE(belief_base->get_belief_state(stm_a));

  EXPECT_TRUE(belief_base->change_belief_state(stm_b, false));
  EXPECT_FALSE(belief_base->get_belief_state(stm_b));

  EXPECT_FALSE(belief_base->change_belief_state(stm_c, false));
}

TEST_F(TBeliefBase, get_size)
{
  Statement stm_a('a');
  Statement stm_b('b');

  Belief belief_a(stm_a, update_belief_true, false);
  Belief belief_b(stm_b, NULL, true);

  belief_base->add_belief(belief_a);
  EXPECT_EQ(1, belief_base->get_size());

  belief_base->add_belief(belief_b);
  EXPECT_EQ(2, belief_base->get_size());
}
