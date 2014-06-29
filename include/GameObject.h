#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


//A circle structure.
struct Circle
{
    int x, y;
    int r;
};

//A point structure, usable for creating polygonal hitboxes.
struct Point
{
    int x, y;
};

//A class that stores a set of points (in order) which form a polygon.
class Polygon
{

    private:
        vector<Point> points;
};

//Class that represents in game objects.
class GameObject
{
    public:
        GameObject();
        virtual ~GameObject();
        vector<Hitbox> get_hitboxes() { return hitboxes; }
        void set_hitboxes(vector<Hitbox> val) { hitboxes = val; }
        void add_hitbox(Hitbox new_hitbox);
        void remove_hitbox(Hitbox old_hitbox);
    protected:
    private:
        //If empty, the object doesn't have a hitbox and is intangible.
        vector<Hitbox> hitboxes;
};


//Class to store and change hitbox bounds and relevant information.
class Hitbox
{
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
#endif // GAMEOBJECT_H
