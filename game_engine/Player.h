#include <SFML/Graphics.hpp>

using namespace sf;

class Player{
    private:
        Vector2f position;
        Sprite sprite;
        Texture texture;
        bool Left_pressed;
        bool Right_pressed;
        bool Top_pressed;
        bool Bottom_pressed;
        float speed;
    public:
        Player();
        Sprite getSprite();
        // player move
        void moveLeft();
        void moveRight();
        void moveTop();
        void moveBottom();
        void stopLeft();
        void stopRight();
        void stopTop();
        void stopBottom();
        // weapon func
        void weap_reload();
        void weap_shot();
        void switch_weapon();
        //equipment func
        void drop_item();
        void take_item();
        void use_item();
        //update display
        void update(float elapsedTime);

};