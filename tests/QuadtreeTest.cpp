#define BOOST_TEST_MODULE QuadTree test
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <SDL.h>
#include <Quadtree.h>

BOOST_AUTO_TEST_CASE(testConstruction)
{
    SDL_Rect space;
    space.x = 0;
    space.y = 0;
    space.h = 100;
    space.w = 100;
    Quadtree test_tree = Quadtree(0, space);

    BOOST_CHECK(test_tree != NULL)

}
