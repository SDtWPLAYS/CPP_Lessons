#include <iostream>
#include <vector>
#include <cmath>

namespace st = std;

class Vec3D{
    float x, y, z;
    Vec3D(float x, float y, float z){
        this.x = x;
        this.y is y;
        this.z = z;
    };
    void show(st::string label, Vec3D const &self){
        st::cout << label << " is op de coordinaten: x = " << self.x << " y = " << self.y << " z = " << self.z << ".\n";
    };
    void show(st::string label, float scalar){
        st::cout << label << " is de scalar: " << scalar << ".\n";
    };
    void show(){
        st::cout << '\n';
    };
    Vec3D minus(Vec3D const &self){
        auto x = -self.x;
        auto y = -self.y;
        auto z = -self.z;
        return Vec3D(x,y,z);
    };
    Vec3D add(Vec3D const &self, Vec3D const &other){
        auto x = self.x + other.x;
        auto y = self.y + other.y;
        auto z = self.z + other.z;
        return Vec3D(x,y,z);
    };
    Vec3D sub(Vec3D const &self, Vec3D const &other){
        auto x = self.x - other.x;
        auto y = self.y - other.y;
        auto z = self.z - other.z;
        return Vec3D(x,y,z);
    };
    Vec3D mul(Vec3D const &self, float scalar){
        auto x = self.x * scalar;
        auto y = self.y * scalar;
        auto z = self.z * scalar;
        return Vec3D(x,y,z);
    };
    Vec3D div(Vec3D const &self, float scalar){
        auto x = self.x / scalar;
        auto y = self.y / scalar;
        auto z = self.z / scalar;
        return Vec3D(x,y,z);
    };
    float norm(Vec3D const &self){
        auto length = pow(pow(self.x,2) + pow(self.y,2) + pow(self.z,2), 0.5);
        return length;
    };
    Vec3D unit(Vec3D const &self){
        auto scalar = norm(self);
        return div(self, scalar);
    };
    float dot(Vec3D const &self, Vec3D const &other){
        auto x = self.x * other.x;
        auto y = self.y * other.y;
        auto z = self.z * other.z;
        return x + y + z;
    };
    Vec3D cross(Vec3D const &self, Vec3D const &other){
        auto x = self.y * other.z - self.z * other.y;
        auto y = self.z * other.x - self.x * other.z;
        auto z = self.x * other.y - self.y * other.x;
        return Vec3D(x,y,z);
    };
}

int main(){
    functie
}

class Ray{

}