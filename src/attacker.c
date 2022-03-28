// Standard headers
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Internal headers
#include "direction.h"
#include "position.h"
#include "defender.h" //hack pra incluir as funcoes auxiliares
#include "spy.h"

// Main header
#include "attacker.h"

// Macros
#define UNUSED(x) (void)(x) // Auxiliary to avoid error of unused parameter


/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

direction_t execute_attacker_strategy(
    position_t attacker_position, Spy defender_spy) {

  static int rounds = 0;
  static bool spy_used = false;
  static bool spy = false;
  static double spy_chance = 0.2;
  static int wandering_steps = 0;
  static double wandering_chance = 0.9;
  static position_t previous_position = INVALID_POSITION;
  static direction_t previous_direction = DIR_STAY;
  static direction_t wandering_dir = DIR_UP;
  static direction_t dirs[] = {DIR_UP, DIR_UP_RIGHT, DIR_RIGHT, DIR_DOWN_RIGHT,
                               DIR_DOWN, DIR_DOWN_LEFT, DIR_LEFT, DIR_UP_LEFT};
  static int escape_index = 0;
  
  if (rounds > 3){
      wandering_chance = 0.2;
  }
  rounds++;
  //printf("random integer: %d \n", random_integer(8));
  //printf("random number: %lf \n", random_number(1));

  //check if we are stuck, and unstuck
  if (equal_positions(attacker_position, previous_position)){
      if (equal_directions(dirs[escape_index], previous_direction)){
          escape_index++;
          previous_direction = dirs[escape_index];
          previous_position = attacker_position;
          return dirs[escape_index];
      }
  }

  if (spy_used == false && random_number(1) < spy_chance && rounds > 3){
      spy = true;
      wandering_chance = 0;
  }
  
  if (spy){
      spy_used = true;
      spy = false;
      position_t defender_position = get_spy_position(defender_spy);
      int vertical_distance = attacker_position.i - defender_position.i;
      int horizontal_distance = attacker_position.j - defender_position.j;
      if (vertical_distance > 0){ //defender is above
          if (horizontal_distance >= -2 && vertical_distance <= 2 ) {
              wandering_dir = (direction_t) DIR_DOWN_LEFT; //defender is very close so we go down and away
          }
          else if (horizontal_distance > -3 && vertical_distance <= 3){
              wandering_dir = (direction_t) DIR_DOWN; //defender is close so we go down
          }
          else{
              wandering_dir = (direction_t) DIR_UP_RIGHT;
          }
      }
      else if (vertical_distance <= 0){ //below or on our line
          if (horizontal_distance >= -2 && vertical_distance >= -2) {
              wandering_dir = (direction_t) DIR_UP_LEFT; //defender is very close so we go up and away
          }
          else if (horizontal_distance >= -3 && vertical_distance >= -3) {
              wandering_dir = (direction_t) DIR_UP; //defender is close so we go up
          }
          else {
              wandering_dir = (direction_t) DIR_UP_RIGHT;
          }
      }
      wandering_steps = 3;
  }
  
  // check if we wander
  double wander = random_number(1);

  if (wander < wandering_chance && wandering_steps == 0){
      //printf("Attacker wandering\n");
      wandering_steps = 3;
      wandering_dir = dirs[random_integer(8)];
      //printf("wandering dir: { %d %d }\n", dirs->i, dirs->j);
  }

  //process wander
  if (wandering_steps > 0){
      wandering_steps--;
      previous_direction = wandering_dir;
      previous_position = attacker_position;
      return wandering_dir;
  }
  // TODO: Implement Attacker logic here
  previous_direction = (direction_t) DIR_RIGHT;
  previous_position = attacker_position;
  return (direction_t) DIR_RIGHT; 
}

/*----------------------------------------------------------------------------*/
