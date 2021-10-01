#include <iostream>
#include <vector>
#include <cmath>

namespace st = std;

class Vec3D{
    float x, y, z;
    Vec3D(float x, float y, float z);
    void show(st::string label, Vec3D const &self);
    void show(st::string label, float scalar);
    void show(){
        st::cout << '\n';
    };
    Vec3D minus(Vec3D const &self);
    Vec3D add(Vec3D const &self, Vec3D const &other);
}

class Ray{

}