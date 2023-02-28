/*
Author: Mohamed Ghanem
Class: ECE4122A
Last Date Modified: 10/21/2022
Description:
Main function used to initialize game parameters and run game.
 */
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Ghost.h"

using namespace sf;
using namespace std;

enum class direction { LEFT, RIGHT, UP, DOWN, NONE}; // enum class for direction of movement

vector<CircleShape> coins; // vector to store all coins
vector<RectangleShape> walls; // vector to store all walls
vector<Ghost> ghosts; // vector to store ghosts
vector<CircleShape> powerups; // vector to store all powerups
Clock powerClock; // initialize global power clock


/*
 * Method to check if all coins are transparent (have been consumed by pacman).
 */
bool checkCoins ()
{
    for (CircleShape &coin: coins)
    {
        if (coin.getFillColor() != Color::Transparent)
        {
            return false;
        }
    }
    return true;
}
/*
 * Method to check all ghosts are alive.
 */
bool checkGhosts ()
{
    for (Ghost &ghost: ghosts)
    {
        if (ghost.alive)
        {
            return false;
        }
    }
    return true;
}
/*
 * Method to create walls at specific position with specific width and height parameter.
 */
void makeWall (float x, float y, float width, float height)
{
    RectangleShape wall;
    wall.setPosition(x, y);
    wall.setSize(Vector2f(width,height));
    wall.setFillColor(Color::White);
    walls.push_back(wall);
}
/*
 * Method to generate random direction from direction enum class.
 */
direction randomDirection ()
{
    return direction(rand() % 4);
}
/*
 * Method to create powerup at specific position.
 */
void makePowerup (float x, float y)
{
    CircleShape powerup;
    powerup.setPosition(x, y);
    powerup.setRadius(7.0f);
    powerup.setFillColor(Color::White);
    powerups.push_back(powerup);
}
/*
 * Method to create row of coins starting at a specific position and with a specific number of coins.
 */
void makeRowCoins (float start, float y, int num)
{
    float spacing = start;
    for (int i = 0; i < num; i++)
    {
        CircleShape coin;
        coin.setRadius(2.5f);
        coin.setFillColor(Color::White);
        if (i % 2)
        {
            coin.setPosition(spacing, y);
            spacing += 21;
        } else {
            coin.setPosition(spacing, y);
            spacing += 20;
        }
        coins.push_back(coin);
    }
}
/*
 * Method to create cols of coins starting at a specific position and with a specific number of coins.
 */
void makeColCoins (float start, float x, int num)
{
    float spacing = start;
    for (int i = 0; i < num; i++)
    {
        CircleShape coin;
        coin.setRadius(2.5f);
        coin.setFillColor(Color::White);
        if (i % 2)
        {
            coin.setPosition(x, spacing);
            spacing += 21;
        } else {
            coin.setPosition(x, spacing);
            spacing += 20;
        }
        coins.push_back(coin);
    }
}
/*
 * Method to check if a sprite is close to intersecting a wall.
 */
bool intersectsWall (float x, float y, Sprite sprite)
{
    sprite.setPosition(x, y);
    for (RectangleShape &wall: walls)
    {
        if (wall.getGlobalBounds().intersects(sprite.getGlobalBounds()))
        {
            return true;
        }
    }
    return false;
}
/*
 * Method to move sprite according to specified direction.
 */
void moveSprite (Sprite &sprite, direction &d)
{
    float x = sprite.getPosition().x;
    float y = sprite.getPosition().y;
    switch (d)
    {
        case direction::RIGHT:
            if (!intersectsWall(x + 2, y, sprite))
            {
                sprite.setPosition(x + 1, y);
                break;
            }
            d = randomDirection();
        case direction::LEFT:
            if (!intersectsWall(x - 2, y, sprite))
            {
                sprite.setPosition(x - 1, y);
                break;
            }
            d = randomDirection();
        case direction::UP:
            if (!intersectsWall(x, y - 2, sprite))
            {
                sprite.setPosition(x, y - 1);
                break;
            }
            d = randomDirection();
        case direction::DOWN:
            if (!intersectsWall(x, y + 2, sprite))
            {
                sprite.setPosition(x, y + 1);
                break;
            }
            d = randomDirection();
        default:
            d = randomDirection();
    }
}
/*
 * Main method used to run game.
 */
int main() {


    VideoMode vm(641, 728); // create a video mode object

    RenderWindow window(vm, "Pacman"); // create and open a window for the game

    Texture textureBackground; // create a texture to hold a graphic on the GPU
    textureBackground.loadFromFile("/Users/ghanem/Desktop/ECE4122/Lab3v2/graphics/maze.bmp"); // load a graphic into the texture
    Sprite spriteBackground; // create a sprite
    spriteBackground.setTexture(textureBackground); // attach the texture to the sprite
    spriteBackground.setPosition(0, 0); // set the spriteBackground to cover the screen


    Texture texturePacman; // create pacman texture to hold a graphic on the GPU
    bool pacman = true; // bool to check if pacman is alive
    texturePacman.loadFromFile("/Users/ghanem/Desktop/ECE4122/Lab3v2/graphics/pacman.bmp"); // load pacman graphic into the texture
    Sprite spritePacman; // create pacman sprite
    spritePacman.setTexture(texturePacman);
    spritePacman.setPosition(302, 492); // set pacman initial position
    spritePacman.setScale(0.8, 0.8); // change pacman scale
    direction pacmanDirection = direction::NONE; // set pacman initial direction
    bool pacmanPowerUp = false; // bool to check if pacman is powered up

    Texture ghostTexture1; // create ghost texture to hold a graphic on the GPU
    ghostTexture1.loadFromFile("/Users/ghanem/Desktop/ECE4122/Lab3v2/graphics/red_ghost.bmp"); // load ghost graphic into the texture
    Ghost ghost1 = Ghost(ghostTexture1); // create ghost class with specific texture

    Texture ghostTexture2; // create ghost texture to hold a graphic on the GPU
    ghostTexture2.loadFromFile("/Users/ghanem/Desktop/ECE4122/Lab3v2/graphics/pink_ghost.bmp"); // load ghost graphic into the texture
    Ghost ghost2 = Ghost(ghostTexture2);

    Texture ghostTexture3; // create ghost texture to hold a graphic on the GPU
    ghostTexture3.loadFromFile("/Users/ghanem/Desktop/ECE4122/Lab3v2/graphics/blue_ghost.bmp"); // load ghost graphic into the texture
    Ghost ghost3 = Ghost(ghostTexture3); // create ghost class with specific texture

    Texture ghostTexture4; // create ghost texture to hold a graphic on the GPU
    ghostTexture4.loadFromFile("/Users/ghanem/Desktop/ECE4122/Lab3v2/graphics/orange_ghost.bmp"); // load ghost graphic into the texture
    Ghost ghost4 = Ghost(ghostTexture4); // create ghost class with specific texture

    // add ghosts to vector
    ghosts.push_back(ghost1);
    ghosts.push_back(ghost2);
    ghosts.push_back(ghost3);
    ghosts.push_back(ghost4);


    Text startMessage; // initialize start message text
    Font font; // initialize start message font
    font.loadFromFile("/Users/ghanem/Desktop/ECE4122/Lab3v2/KOMIKAP_.ttf"); // load start message font
    startMessage.setFont(font); // set start message font
    startMessage.setString("PRESS ENTER TO START"); // set start message text
    startMessage.setCharacterSize(50); // set start message text size
    startMessage.setFillColor(Color::White); // set start message text color
    bool start = false; // bool to check if game has started

    // center text on screen
    FloatRect textRect = startMessage.getLocalBounds();
    startMessage.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    startMessage.setPosition(320, 340);

    // create right tunnel rectangle
    RectangleShape rightTunnel;
    rightTunnel.setPosition(540, 305);
    rightTunnel.setSize(Vector2f(1, 36));

    // create left tunnel rectangle
    RectangleShape leftTunnel;
    leftTunnel.setPosition(60, 305);
    leftTunnel.setSize(Vector2f(1, 36));

    // create all coins
    makeRowCoins(60, 55, 12);
    makeRowCoins(347, 55, 12);
    makeRowCoins(60, 137, 26);
    makeRowCoins(60, 199, 6);
    makeRowCoins(470, 199, 6);
    makeRowCoins(60, 444, 12);
    makeRowCoins(347, 444, 12);
    makeRowCoins(60, 567, 6);
    makeRowCoins(470, 567, 6);
    makeRowCoins(60, 629, 26);
    makeRowCoins(164, 507, 7);
    makeRowCoins(347, 506, 7);
    makeRowCoins(224, 199, 4);
    makeRowCoins(347, 199, 4);
    makeRowCoins(80, 506, 1);
    makeRowCoins(551, 506, 1);
    makeRowCoins(224, 567, 4);
    makeRowCoins(347, 567, 4);
    makeColCoins(55, 162, 26);
    makeColCoins(55, 470, 26);
    makeColCoins(55, 60, 8);
    makeColCoins(55, 572, 8);
    makeColCoins(55, 285, 5);
    makeColCoins(55, 347, 5);
    makeColCoins(137, 224, 4);
    makeColCoins(136, 408, 4);
    makeColCoins(136, 408, 4);
    makeColCoins(444, 60, 4);
    makeColCoins(567, 60, 4);
    makeColCoins(444, 572, 4);
    makeColCoins(567, 572, 4);
    makeColCoins(567, 285, 3);
    makeColCoins(567, 347, 3);
    makeColCoins(526, 224, 3);
    makeColCoins(526, 408, 3);
    makeColCoins(506, 101, 3);
    makeColCoins(506, 531, 3);
    makeColCoins(444, 285, 3);
    makeColCoins(444, 347, 3);

    // create all walls
    makeWall(80, 75, 67, 45);
    makeWall(184, 75, 87, 45);
    makeWall(365, 75, 87, 45);
    makeWall(490, 75, 67, 45);
    makeWall(593, 22, 15, 643);
    makeWall(28, 22, 15, 643);
    makeWall(30, 23, 576, 20);
    makeWall(30, 649, 576, 20);
    makeWall(249, 286, 138, 77);
    makeWall(496, 347, 110, 77);
    makeWall(496, 224, 110, 77);
    makeWall(29, 218, 118, 87);
    makeWall(29, 342, 118, 87);
    makeWall(306, 157, 26, 87);
    makeWall(244, 157, 149, 25);
    makeWall(244, 403, 149, 25);
    makeWall(244, 527, 149, 25);
    makeWall(306, 403, 26, 87);
    makeWall(306, 527, 26, 87);
    makeWall(82, 158, 64, 25);
    makeWall(491, 158, 64, 25);
    makeWall(185, 465, 84, 25);
    makeWall(368, 465, 84, 25);
    makeWall(489, 466, 27, 85);
    makeWall(121, 466, 27, 85);
    makeWall(182, 343, 27, 85);
    makeWall(428, 343, 27, 85);
    makeWall(428, 528, 27, 85);
    makeWall(182, 528, 27, 85);
    makeWall(306, 38, 27, 85);
    makeWall(182, 158, 27, 148);
    makeWall(433, 162, 16, 139);
    makeWall(204, 223, 61, 17);
    makeWall(373, 223, 61, 17);
    makeWall(81, 465, 67, 26);
    makeWall(489, 465, 67, 26);
    makeWall(552, 526, 47, 26);
    makeWall(38, 526, 47, 26);
    makeWall(81, 588, 189, 26);
    makeWall(368, 588, 189, 26);

    // create powerups
    makePowerup(55, 91);
    makePowerup(569, 93);
    makePowerup(55, 501);
    makePowerup(569, 503);

    // start game loop
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        // if escape is pressed close window
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }
        // if all coins are consumed or pacman is dead or all ghosts are dead close window (end game)
        if (start && (checkCoins() || !pacman || checkGhosts()))
        {
            window.close();
        }
        // if enter is pressed start game
        if (Keyboard::isKeyPressed(Keyboard::Enter))
        {
            start = true; // set start to true
            // set all ghosts to alive
            for (Ghost &ghost: ghosts)
            {
                ghost.alive = true;
                ghost.dir = randomDirection();
            }
        }

        // keyboard arrows determine pacman direction
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            pacmanDirection = direction::RIGHT; // change pacman direction to right
        }
        else if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            pacmanDirection = direction::LEFT; // change pacman direction to left
        }
        else if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            pacmanDirection = direction::UP; // change pacman direction to up
        }
        else if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            pacmanDirection = direction::DOWN; // change pacman direction to down
        }
        direction copyDirection = pacmanDirection;
        moveSprite(spritePacman, copyDirection); // move pacman

        // check all coins
        for (CircleShape &coin: coins)
        {
            // if pacman intersects a coin set coin to disappear
            if (spritePacman.getGlobalBounds().intersects(coin.getGlobalBounds()))
            {
                coin.setFillColor(Color::Transparent);
            }
        }
        // check all powerups
        for (CircleShape &powerup: powerups)
        {
            // if pacman intersects a powerup
            if (spritePacman.getGlobalBounds().intersects(powerup.getGlobalBounds()))
            {
                powerup.setPosition(586, 701); // move powerup
                powerup.setFillColor(Color::Transparent); // make powerup transparent
                pacmanPowerUp = true; // set pacman to be powered up
                powerClock.restart(); // restart timer
            }
        }
        // check conditions for al ghosts
        for (Ghost &ghost: ghosts)
        {
            // if pacman comes in contact with a ghost
            if (spritePacman.getGlobalBounds().intersects(ghost.sprite.getGlobalBounds()))
            {
                // if pacman is powered up
                if (pacmanPowerUp)
                {
                    ghost.alive = false; // kill ghost that is in contact with pacman
                    ghost.sprite.setPosition(586, 701); // move ghost out of playable maze
                }
                else
                {
                    pacman = false; // if pacman is not powered up, kill pacman
                }
            }
            // if ghost goes through right tunnel spawn draw him at left tunnel in the next frame.
            else if (ghost.sprite.getGlobalBounds().intersects(rightTunnel.getGlobalBounds()))
            {
                ghost.sprite.setPosition(65, 306);
            }
            // if pacman goes through left tunnel spawn draw him at right tunnel in the next frame.
            else if (ghost.sprite.getGlobalBounds().intersects(leftTunnel.getGlobalBounds()))
            {
                ghost.sprite.setPosition(500, 306);
            }
        }

        // if pacman is powered up check if 5 seconds have elapsed
        if (pacmanPowerUp && powerClock.getElapsedTime() > seconds(5))
        {
            pacmanPowerUp = false; // set powerup to false if pacman has been powered up for 5 seconds
        }

        // if pacman goes through right tunnel spawn draw him at left tunnel in the next frame.
        if (spritePacman.getGlobalBounds().intersects(rightTunnel.getGlobalBounds()))
        {
            spritePacman.setPosition(65, 306);
        }
        // if pacman goes through left tunnel spawn draw him at right tunnel in the next frame.
        else if (spritePacman.getGlobalBounds().intersects(leftTunnel.getGlobalBounds()))
        {
            spritePacman.setPosition(500, 306);
        }

        window.clear(); // clear last frame
        window.draw(spriteBackground); // draw background
        if (start)
        {
            window.draw(spritePacman); // draw pacman if game has started
        }

        // draw ghosts if they are alive
        for (Ghost &ghost: ghosts)
        {
            if (ghost.alive)
            {
                moveSprite(ghost.sprite, ghost.dir);
                window.draw(ghost.sprite);
            }
        }

        // draw coins
        for (CircleShape &coin: coins)
        {
            window.draw(coin);
        }

        // draw powerups
        for (CircleShape &powerup: powerups)
        {
            window.draw(powerup);
        }

        // draw start message if game has not started
        if (!start)
        {
            window.draw(startMessage);
        }

        // display frame
        window.display();

        // adjust game speed
        if (pacmanPowerUp)
        {
            sleep(microseconds(2500)); // increase game speed when pacman is powered up
        }
        else
        {
            sleep(microseconds(5000)); // normal game speed to increase playability
        }
    }
    return 0;
}