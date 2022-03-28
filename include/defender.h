#ifndef DEFENDER_H
#define DEFENDER_H

// Internal headers
#include "position.h"
#include "spy.h"

// Functions

/**
 * Main algorithm to move Defender player in a Game.
 * Given the player position, it should decide the next direction
 * they will take in the field.
 */
direction_t execute_defender_strategy(position_t defender_position,
                                      Spy attacker_spy);
                                      

double random_number(double limit);
int random_integer(int limit);
bool equal_directions(direction_t a, direction_t b);

#endif // DEFENDER_H
