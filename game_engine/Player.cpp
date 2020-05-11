#include "Player.h"

Player::Player()
{
    speed = 400;
    texture.loadFromFile("bob.png");
    sprite.setTexture(texture);
    position.x = 300;
    position.y = 200;
}
Sprite Player::getSprite()
{
    return sprite;
}
void Player::moveLeft()
{
    Left_pressed = true;
}
void Player::moveRight()
{
    Right_pressed = true;
}
void Player::moveTop()
{
    Top_pressed = true;
}
void Player::moveBottom()
{
    Bottom_pressed = true;
}
void Player::stopLeft()
{
    Left_pressed = false;
}
void Player::stopRight()
{
    Right_pressed = false;
}
void Player::stopTop()
{
    Top_pressed = false;
}
void Player::stopBottom()
{
    Bottom_pressed = false;
}
void Player::update(float elapsedTime)
{
    if(Right_pressed)
    {
        position.x += speed * elapsedTime;
    }
    else if(Left_pressed)
    {
        position.x -= speed * elapsedTime;
    }
    else if(Top_pressed)
    {
        position.y -= speed * elapsedTime;
    }
    else if(Bottom_pressed)
    {
        position.y += speed * elapsedTime;
    }
    sprite.setPosition(position);
}