#include "Quadtree.h"
#include <SDL.h>
#include <iterator>
#include <boost/ptr_container/ptr_list.hpp>

//Credit: http://gamedevelopment.tutsplus.com/tutorials/quick-tip-use-quadtrees-to-detect-likely-collisions-in-2d-space--gamedev-374
/*TODO:
    Implement Hilbert Curve?


*/

//Maximum number of levels of the Quadtree.
const int Quadtree::MAX_DEPTH = 10;

//Maximum number of members of a Quadtree node after which a node must be split.
const int Quadtree::MAX_MEMBERS = 4;

Quadtree::Quadtree(int level, SDL_Rect rect_size)
{
    //Depth of current Quadtree node.
    depth = level;

    //Physical dimensions covered by current Quadtree.
    bounds = rect_size;

    //Array of Quadtree subnodes.
    nodes = new Quadtree[4];

    //List of members of the current node.
    //Change this to a list of pointers
    members = new ptr_list<GameObject>();

}

Quadtree::~Quadtree()
{
    //Clear tree.
    clear_tree();

    //Delete subtrees.
    delete[] nodes;
    nodes = NULL;

    /*Delete list of members. Does not delete the members, you passed them in,
     you clean them up yourself. Otherwise it will delete objects in use.*/
     delete members;
     members = NULL;
}

Quadtree::clear_tree()
{
    //Clear member elements.
    members.clear();

    //Clear subtrees.
    for(int i = 0; i < nodes.size(); i++)
    {
        if(nodes[i] != NULL)
        {
            nodes[i].clear_tree();
            delete nodes[i];
            nodes[i] = NULL;
        }
    }
}

Quadtree::split_tree()
{
    int half_width = (bounds.w / 2);
    int half_height = (bounds.h / 2);

    nodes[0] = new Quadtree(depth + 1, make_rect(half_width, half_height, x + half_width, y));
    nodes[1] = new Quadtree(depth + 1, make_rect(half_width, half_height, x, y));
    nodes[2] = new Quadtree(depth + 1, make_rect(half_width, half_height, x, y + half_height));
    nodes[3] = new Quadtree(depth + 1, make_rect(half_width, half_height, x + half_width, y + half_height));

}

Quadtree::make_rect(int width, int height, int x, int y)
{
    SDL_Rect rectangle;
    rectangle.w = width;
    rectangle.h = height;
    rectangle.x = x;
    rectangle.y = y;
    return rectangle;
}

//Get which node an object belongs to. Returns -1 for parent node.
Quadtree::get_quadrant_index(GameObject entity)
{
    int quad_index = -1;
    SDL_Rect hitbox = entity.getHitbox();

    double x_midpoint = bounds.x + (bounds.w / 2);
    double y_midpoint = bounds.y + (bounds.h / 2);


   // Object is completely in the top half of the Quadtree bounds.
   bool topQuadrant = (hitbox.y < y_midpoint && hitbox.y + hitbox.h < y_midpoint);
   // Object is completely in the bottom half of the Quadtree bounds.
   bool bottomQuadrant = (hitbox.y > y_midpoint);

    // Object is completely in the left half of the Quadtree bounds.
    if (hitbox.x < x_midpoint && hitbox.x + hitbox.w < x_midpoint) {
        if (topQuadrant) {
            quad_index = 1;
        }
        else if (bottomQuadrant) {
            quad_index = 2;
        }
    }
    // Object is completely in the right half of the Quadtree bounds.
    else if (hitbox.x > x_midpoint) {
        if (topQuadrant) {
            quad_index = 0;
        }
        else if (bottomQuadrant) {
            quad_index = 3;
        }
    }

   return quad_index;
}

/* Insert the object into the quadtree, splitting the node if MAX_MEMBERS
   is exceeded. When the node is split all its members are redistributed to
   appropriate subtrees.*/
 Quadtree::insert(GameObject entity) {

    /*Add GameObject to subtrees unless it doesn't fit, otherwise
      add it to the members of the current node.*/
    if (nodes[0] != null) {
        int quad_index = get_quadrant_index(entity);

        if (quad_index != -1) {
            nodes[quad_index].insert(entity);

            return;
        }
    }

    members.add(entity);

    if (members.size() > MAX_MEMBERs && depth < MAX_DEPTH) {
        if (nodes[0] == null) {
            split_tree();
        }

        for (iterator i = members.begin(); i != members.end();)
        {
            int quad_index = get_quadrant_index(i);
            if (quad_index != -1){
                nodes[quad_index].insert(i);
                i = members.erase(i);
            }
            else {
                i++;
            }
        }
    }
}


/*
 * Find potential collision targets.
 */
ptr_list retrieve(ptr_list collidable, GameObject entity) {
    int quad_index = get_quadrant_index(entity);
    if (quad_index != -1 && nodes[0] != null) {
        nodes[quad_index].retrieve(collidable, entity);
    }

    //Inserts members of node into list to be returned.
    collidable.insert(collidable.end(), members.begin(), members.end());

    return collidable;
 }
