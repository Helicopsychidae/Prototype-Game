#define BOOST_TEST_MODULE QuadTree test
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <SDL.h>
#include <Quadtree.h>

BOOST_AUTO_TEST_CASE(testConstruction)
{
    SDL_Rect space = {0 , 0, 100, 200};
    Quadtree test_tree = Quadtree(0, space);

}
