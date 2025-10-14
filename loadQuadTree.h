#ifndef LOAD_QUADTREE_H
#define LOAD_QUADTREE_H

#include <string>
#include "QuadTree.h"
using namespace std;

// Loads all property coordinates and IDs from a file into a QuadTree
void loadQuadTreeFromFile(const string& filename, QuadTree& qt);

#endif
