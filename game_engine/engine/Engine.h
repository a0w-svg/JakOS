#include <SFML/Graphics.hpp>
#include "../player/Player.h"

using namespace sf;

class Engine {
    private:
        RenderWindow window;
        Sprite back_sprite;
        Texture back_texture;
        Player player;
        void input();
        void update(float dtAsSeconds);
        void draw();
    public:
        Engine();
        void start();

};