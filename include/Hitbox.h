#ifndef HITBOX_H
#define HITBOX_H


//Class to store and change hitbox bounds and relevant information.
class Hitbox{
    friend GameObject;
    public:
        Hitbox();
        virtual ~Hitbox();
        //Detects collisions between hitboxes.
        bool is_colliding(Hitbox other);

    private:
        GameObject owner;
        bool is_circle;
        union {
            SDL_Rect rect_hitbox;
            Circle circ_hitbox;
        };
        //Collision Detection Helper Functions.
        bool check_collision(SDL_Rect a, SDL_Rect b);
        bool check_collision(Circle a, SDL_Rect b);
        bool check_collision(Circle a, Circle b);
};

#endif // HITBOX_H
