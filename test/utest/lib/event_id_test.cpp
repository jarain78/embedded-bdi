/*
 * event_id_test.cpp
 *
 *  Created on: Jul 12, 2020
 *      Author: Matuzalem Muller
 */

#include "gtest/gtest.h"
#include "lib/event_id.h"

class TEventID : public ::testing::Test
{
protected:
  EventID id_1;
  EventID * id_1_clone;
  EventID * id_2;

public:
  TEventID()
  {
    id_1_clone = &id_1;
    id_2 = new EventID();
  }

  virtual ~TEventID()
  {
    delete id_2;
  }
};

TEST_F(TEventID, get_id)
{
  EXPECT_EQ(id_2->get_id(), id_1.get_id()+1);
}

TEST_F(TEventID, is_equal)
{
  EXPECT_TRUE(id_1_clone->is_equal(id_1));
}
