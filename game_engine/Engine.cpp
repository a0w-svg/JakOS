#include "Engine.h"

Engine::Engine()
{
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    window.create(VideoMode(resolution.x, resolution.y),
    "ZSE", Style::Fullscreen);

    back_texture.loadFromFile("background.jpg");
    back_sprite.setTexture(back_texture);
}
void Engine::start()
{
    Clock clock;
    while(window.isOpen())
    {
        Time dt = clock.restart();
        float dtAsSeconds = dt.asSeconds();
        input();
        update(dtAsSeconds);
        draw();
    }
}