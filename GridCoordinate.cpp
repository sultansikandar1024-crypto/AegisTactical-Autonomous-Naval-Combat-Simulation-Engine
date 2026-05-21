#include "GridCoordinate.h"
#include <cmath>

GridCoordinate::GridCoordinate(int x, int y, int z)
    : x(x), y(y), z(z) {
    if (!isWithinBounds()) {
        this->x = MIN_X;
        this->y = MIN_Y;
        this->z = SURFACE_Z;
    }
}

bool GridCoordinate::isWithinBounds() const {
    bool validDepth = (z == SURFACE_Z || z == DEEP_SEA_Z);
    bool validX = (x >= MIN_X && x <= MAX_X);
    bool validY = (y >= MIN_Y && y <= MAX_Y);
    return validDepth && validX && validY;
}

void GridCoordinate::setPosition(int newX, int newY, int newZ) {
    x = newX;
    y = newY;
    z = newZ;
    if (!isWithinBounds()) {
        x = MIN_X;
        y = MIN_Y;
        z = SURFACE_Z;
    }
}

double GridCoordinate::distanceTo(const GridCoordinate& other) const {
    int dx = x - other.x;
    int dy = y - other.y;
    int dz = z - other.z;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

std::string GridCoordinate::toString() const {
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
}

int GridCoordinate::getX() const { return x; }
int GridCoordinate::getY() const { return y; }
int GridCoordinate::getZ() const { return z; }

bool GridCoordinate::isSurface() const {
    return z == SURFACE_Z;
}

bool GridCoordinate::isDeepSea() const {
    return z == DEEP_SEA_Z;
}
