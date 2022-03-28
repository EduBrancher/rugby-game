// Standard headers
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Internal headers
#include "direction.h"
#include "position.h"
#include "spy.h"

// Main header
#include "defender.h"

// limit is a double between 0 and 1 that determines the maximum value of the random
// numbers generated. For instance, if it is 0.5, this generates a number between 0 
// and 0.5.

// OBS: Essa funcao nao deveria estar repetida aqui, deveria estar em um modulo util.h
// que agruparia funcoes genericamente uteis para varios propositos
// OU um modulo player.h que seria um objeto generico do qual attacker e defender herdam
double random_number(double limit){
    limit = fabs(limit);
    return (double) rand() / ((double) RAND_MAX * (double)(1 / limit));
}

//returns integer between 0 and limit - 1.
int random_integer(int limit){
    limit = abs(limit);
    return (int) (random_number(1) * limit);
    
}

bool equal_directions(direction_t a, direction_t b){
    return (a.i == b.i && a.j == b.j);
}

// Macros
#define UNUSED(x) (void)(x) // Auxiliary to avoid error of unused parameter

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

direction_t execute_defender_strategy(
    position_t defender_position, Spy attacker_spy) {
  // TODO: unused parameters, remove these lines later
  UNUSED(attacker_spy);

  static int rounds = 0;
  //static bool spy_used = false;
  //static bool spy = false;
  //static double spy_chance = 0.2;
  static position_t previous_position = INVALID_POSITION;
  static direction_t previous_direction = DIR_STAY;
  UNUSED(previous_direction);
  //static direction_t dirs[] = {DIR_UP, DIR_UP_RIGHT, DIR_RIGHT, DIR_DOWN_RIGHT,
  //                             DIR_DOWN, DIR_DOWN_LEFT, DIR_LEFT, DIR_UP_LEFT};
  //static int escape_index = 0;
  static int up_offset = 0;
  static int left_offset = 0;
  static int max_up = -1;
  static int max_down = 1;
  static bool going_up = false;
  static bool going_down = false;
  static time_t t;

  if (rounds == 0){
      srand(time(&t)%1127);
      rounds++;
      previous_direction = (direction_t) DIR_LEFT;
      left_offset++;
      going_up = true;
      previous_position = defender_position;
      return (direction_t) DIR_LEFT;
  }
  rounds++;


  if (going_up){
      if (max_up == -1){
          if (!equal_positions(defender_position, previous_position)){
              up_offset++;
              previous_direction = (direction_t) DIR_UP;
              previous_position = defender_position;
              return (direction_t) DIR_UP;
          }
          else{
              up_offset--;
              max_up = up_offset;
              up_offset--;
              previous_direction = (direction_t) DIR_DOWN;
              previous_position = defender_position;
              going_down = true;
              going_up = false;
              return (direction_t) DIR_DOWN;
          }
      }
      else{
          if (up_offset < max_up){
              up_offset++;
              previous_direction = (direction_t) DIR_UP;
              previous_position = defender_position;
              return(direction_t) DIR_UP;
          }
          else{
              going_up = false;
              going_down = true;
              up_offset--;
              previous_direction = (direction_t) DIR_DOWN;
              previous_position = defender_position;
              return (direction_t) DIR_DOWN;
          }
      }
  }
  else if (going_down){
      if (max_down == 1){
          if (!equal_positions(defender_position, previous_position)){
              up_offset--;
              previous_direction = (direction_t) DIR_DOWN;
              previous_position = defender_position;
              return (direction_t) DIR_DOWN;
          }
          else{
              up_offset++;
              going_up = true;
              going_down = false;
              max_down = up_offset;
              up_offset++;
              previous_direction = (direction_t) DIR_UP;
              previous_position = defender_position;
              return (direction_t) DIR_UP;
          }
      }
      else{
          if (up_offset > max_down){
              up_offset--;
              previous_direction = (direction_t) DIR_DOWN;
              previous_position = defender_position;
              return(direction_t) DIR_DOWN;
          }
          else{
              going_up = true;
              going_down = false;
              up_offset++;
              previous_direction = (direction_t) DIR_UP;
              previous_position = defender_position;
              return (direction_t) DIR_UP;
          }
      }
  }

  // TODO: Implement Defender logic here
  previous_direction = (direction_t) DIR_STAY;
  previous_position = defender_position;
  return (direction_t) DIR_STAY;
}

/*----------------------------------------------------------------------------*/
