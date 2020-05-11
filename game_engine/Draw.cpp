#include "Engine.h"

void Engine::draw()
{
    window.clear(Color::White);
    window.draw(back_sprite);
    window.draw(player.getSprite());
    window.display();
}