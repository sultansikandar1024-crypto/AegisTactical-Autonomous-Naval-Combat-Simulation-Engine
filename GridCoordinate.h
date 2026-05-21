#ifndef GRIDCOORDINATE_H
#define GRIDCOORDINATE_H

#include <string>

class GridCoordinate {
private:
    int x;
    int y;
    int z;
    static const int MIN_X = 0;
    static const int MIN_Y = 0;
    static const int MAX_X = 9;
    static const int MAX_Y = 9;
    static const int SURFACE_Z = 0;
    static const int DEEP_SEA_Z = -1;

public:
    GridCoordinate(int x = 0, int y = 0, int z = SURFACE_Z);
    bool isWithinBounds() const;
    void setPosition(int newX, int newY, int newZ);
    double distanceTo(const GridCoordinate& other) const;
    std::string toString() const;
    int getX() const;
    int getY() const;
    int getZ() const;
    bool isSurface() const;
    bool isDeepSea() const;
};

#endif // GRIDCOORDINATE_H
