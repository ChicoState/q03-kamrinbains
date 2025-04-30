/**
 * Unit Tests for the class
**/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

// Example "smoke test" (can be deleted)
// Create a guessing object, no guesses means remaining should still equal 3
TEST(GuesserTest, object_creation_remaining)
{
  Guesser object("Secret");
  ASSERT_EQ( object.remaining(), 3 );
}


// False guess, should return false
TEST(GuesserTest, false_guess)
{
  Guesser object("Secret");
  ASSERT_EQ( false, object.match("yoooo") );
}

// Test if blank string works and if guessing blank string is correct
TEST(GuesserTest, blank_secret)
{
  Guesser object("");
  ASSERT_EQ( true , object.match("") );
}


// Fail a guess, yet distance is < 2 so remaining should be 2
// false guess, check remaining
TEST(GuesserTest, false_remaining)
{
  Guesser object("");
  object.match("y");
  ASSERT_EQ( object.remaining(), 2 );
}
