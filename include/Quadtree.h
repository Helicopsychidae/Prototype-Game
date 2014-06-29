#ifndef QUADTREE_H
#define QUADTREE_H


class Quadtree
{
    public:
        Quadtree(int level, SDL_Rect rect_size);
        ~Quadtree();

        void clear_tree();
        void insert(GameObject entity);

    protected:
    private:
        const int MAX_MEMBERS, MAX_DEPTH;
        int depth;
        ptr_list<GameObject> members;
        SDL_Rect bounds;
        Quadtree[] nodes;

        void split_tree();
        SDL_Rect make_rect(int width, int height, int x, int y);
        int get_quadrant_index(GameObject entity);
        ptr_list<GameObject> retrieve(ptr_list collidable, GameObject entity);
};

#endif // QUADTREE_H
