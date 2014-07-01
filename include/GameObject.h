#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <vector>

//Class that represents in game objects.
class GameObject{
    public:
        GameObject();
        virtual ~GameObject();
        std::vector<Hitbox> get_hitboxes() { return hitboxes; }
        void set_hitboxes(std::vector<Hitbox> val) { hitboxes = val; }
        void add_hitbox(Hitbox new_hitbox);
        void remove_hitbox(Hitbox old_hitbox);
    protected:
    private:
        //If empty, the object doesn't have a hitbox and is intangible.
        std::vector<Hitbox> hitboxes;
};
#endif // GAMEOBJECT_H
