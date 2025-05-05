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

// Tests if a close guess with one character difference decrements attempts
TEST(GuesserTest, same_length_close_guess) {
  Guesser object("Secret");
  ASSERT_EQ(false, object.match("Secref"));
  ASSERT_EQ(object.remaining(), 2);
}

// Verifies a guess with exactly two character differences still allows continued guessing
TEST(GuesserTest, same_length_two_char_difference) {
  Guesser object("Secret");
  ASSERT_EQ(false, object.match("Secryt"));
  ASSERT_EQ(object.remaining(), 2);
}

// Checks if a longer guess that differs significantly locks the secret
TEST(GuesserTest, longer_guess) {
  Guesser object("Secret");
  ASSERT_EQ(false, object.match("SecretExtra"));
  ASSERT_EQ(object.remaining(), 0);
}

// Examines if a shorter guess depletes all attempts when distance exceeds threshold
TEST(GuesserTest, shorter_guess) {
  Guesser object("Secret");
  ASSERT_EQ(false, object.match("Sec"));
  ASSERT_EQ(false, object.match("Secret"));
  ASSERT_EQ(object.remaining(), 0);
}

// Ensures completely different strings trigger the anti brute force mechanism
TEST(GuesserTest, completely_different_guess) {
  Guesser object("Secret");
  ASSERT_EQ(false, object.match("CompletelyDifferent"));
  ASSERT_EQ(false, object.match("Secret"));
  ASSERT_EQ(object.remaining(), 3);
}

// Validates that secrets longer than 32 characters get properly truncated
TEST(GuesserTest, secret_truncation) {
  Guesser object("ThisIsAVeryLongSecretThatShouldBeTruncatedAtThirtyTwoCharacters");
  ASSERT_EQ(true, object.match("ThisIsAVeryLongSecretThatShouldBeTr"));
}

// Confirms that guesses reset to 3 after a successful match
TEST(GuesserTest, correct_match_resets_guesses) {
  Guesser object("Secret");
  object.match("wrong");
  object.match("Secret");
  ASSERT_EQ(object.remaining(), 3);
}

// Makes sure the system locks permanently after a major distance violation
TEST(GuesserTest, lock_after_distance_violation) {
  Guesser object("Secret");
  object.match("totally");
  ASSERT_EQ(false, object.match("Secret"));
  ASSERT_EQ(object.remaining(), 3);
}

// Verifies the system properly locks after running out of allowed attempts
TEST(GuesserTest, lock_after_no_attempts) {
  Guesser object("Secret");
  object.match("Secre1");
  object.match("Secre2");
  object.match("Secre3");
  ASSERT_EQ(false, object.match("Secret"));
}

// Checks if special characters in secrets are handled appropriately
TEST(GuesserTest, special_characters) {
  Guesser object("S@cr#t!");
  ASSERT_EQ(true, object.match("S@cr#t!"));
}

// Demonstrates that the system is case sensitive when matching
TEST(GuesserTest, case_sensitivity) {
  Guesser object("Secret");
  ASSERT_EQ(false, object.match("secret"));
  ASSERT_EQ(false, object.match("Secret"));
  ASSERT_EQ(object.remaining(), 0);
}

// Tests a sequence of closely-related guesses followed by a correct match
TEST(GuesserTest, sequential_guesses) {
  Guesser object("Secret");
  object.match("Secre1");
  ASSERT_EQ(object.remaining(), 2);
  object.match("Secre2");
  ASSERT_EQ(object.remaining(), 1);
  ASSERT_EQ(true, object.match("Secret"));
  ASSERT_EQ(object.remaining(), 3);
}

// Examines how whitespace is treated in secrets and guesses
TEST(GuesserTest, whitespace_handling) {
  Guesser object("Secret ");
  ASSERT_EQ(false, object.match("Secret"));
  ASSERT_EQ(true, object.match("Secret "));
}

// Validates behavior when attempting to guess with an empty string
TEST(GuesserTest, empty_guess) {
  Guesser object("Secret");
  ASSERT_EQ(false, object.match(""));
  ASSERT_EQ(object.remaining(), 2);
}

// Tests a guess with exactly distance 2 (boundary condition)
TEST(GuesserTest, exactly_distance_two) {
  Guesser object("Secret");
  ASSERT_EQ(false, object.match("Secrat"));
  ASSERT_EQ(object.remaining(), 2);
}

// Explores what happens when a guess just exceeds the distance threshold
TEST(GuesserTest, distance_just_over_threshold) {
  Guesser object("Secret");
  ASSERT_EQ(false, object.match("Secrab"));
  ASSERT_EQ(false, object.match("Secret"));
}

// Simple test for perfect match on first try
TEST(GuesserTest, exact_match) {
  Guesser object("Secret");
  ASSERT_EQ(true, object.match("Secret"));
}

// Tests if system can be reset after a match but then locked with a bad guess
TEST(GuesserTest, reset_after_match_then_lock) {
  Guesser object("Secret");
  object.match("wrong");
  ASSERT_EQ(true, object.match("Secret"));
  ASSERT_EQ(object.remaining(), 3);
  object.match("completely different");
  ASSERT_EQ(false, object.match("Secret"));
}

// Checks if guesses reset multiple times after repeated successful matches
TEST(GuesserTest, multiple_resets) {
  Guesser object("Secret");
  object.match("Secre1");
  ASSERT_EQ(true, object.match("Secret"));
  object.match("Secre2");
  ASSERT_EQ(true, object.match("Secret"));
  ASSERT_EQ(object.remaining(), 3);
}
