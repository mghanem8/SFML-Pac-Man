/*
Author: Mohamed Ghanem
Class: ECE4122A
Last Date Modified: 10/21/2022
Description:
Ghost class header file.
 */
#include <SFML/Graphics.hpp>
enum class direction;
using namespace sf;
using namespace std;

class Ghost {
public:
    Sprite sprite; // initialize ghost sprite
    bool alive; // bool to check if ghost is alive
    direction dir; // ghost direction
    Ghost(const Texture& texture); // constructor
};