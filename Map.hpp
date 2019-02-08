#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED

#include <string>

class Map {

public:
    Map();
    ~Map();

    static void LoadMap(std::string path, int sizeX, int sizeY, int scale);


private:

};
#endif // MAP_HPP_INCLUDED
