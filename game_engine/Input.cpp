#include "Engine.h"

void Engine::input()
{
    if(Keyboard::isKeyPressed(Keyboard::Escape))
    {
        window.close();
    }
    else if(Keyboard::isKeyPressed(Keyboard::A))
    {
        player.moveLeft();
    }
    else
    {
        player.stopLeft();
    }
    if(Keyboard::isKeyPressed(Keyboard::D))
    {
        player.moveRight();
    }
    else
    {
        player.stopRight();
    }
    if(Keyboard::isKeyPressed(Keyboard::W))
    {
        player.moveTop();
    }
    else
    {
        player.stopTop();
    }
    if(Keyboard::isKeyPressed(Keyboard::S))
    {
        player.moveBottom();
    }
    else
    {
        player.stopBottom();
    }
    if(Keyboard::isKeyPressed(Keyboard::R))
    {
        player.weap_reload();
    }
}