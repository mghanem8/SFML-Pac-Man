/*
Author: Mohamed Ghanem
Class: ECE4122A
Last Date Modified: 10/21/2022
Description:
Ghost class used to hold ghost sprite and parameters.
 */
#include "Ghost.h"
/*
 * Ghost constructor.
 */
Ghost::Ghost(const Texture& texture)
{
    Ghost::alive = false; // ghost is initially dead
    Ghost::sprite.setTexture(texture); // set ghost texture
    Ghost::sprite.setPosition(302, 245); // set start position
    Ghost::sprite.setScale(0.9, 0.9); // scale ghost sprite

}
