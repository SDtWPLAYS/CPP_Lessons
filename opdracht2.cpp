#include <iostream>
#include <vector>
#include <cmath>

namespace st = std;

struct Vec3D{
    float x, y, z;
    Vec3D(float x, float y, float z){
        this->x = x;
        this->y = y;
        this->z = z;
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
};

int main(){
    auto vector1 = Vec3D(0.4, 4.2, 1.8);
    auto vector2 = Vec3D(3.7, 2.4, 5.0);
    vector1.show("Vector1", vector1);
    vector2.show("Vector2", vector2);
    vector1.show();

    vector1.show("Vector1 negatief", vector1.minus(vector1));
    vector2.show("Vector2 negatief", vector2.minus(vector2));
    vector1.show();

    vector1.show("Vector1 + vector2", vector1.add(vector1, vector2));
    vector1.show();

    vector1.show("Vector1 - vector2", vector1.sub(vector1, vector2));
    vector2.show("Vector2 - vector1", vector2.sub(vector2, vector1));
    vector1.show();

    vector1.show("Vector1 x 5", vector1.mul(vector1, 5));
    vector2.show("Vector2 x 5", vector2.mul(vector2, 5));
    vector1.show();

    vector1.show("Vector1 / 2", vector1.div(vector1, 2));
    vector2.show("Vector2 / 2", vector2.div(vector2, 2));
    vector1.show();

    st::cout << "Lengte van vector1: " << vector1.norm(vector1) << '\n';
    st::cout << "Lengte van vector2: " << vector2.norm(vector2) << '\n';
    vector1.show();

    vector1.show("Zelfde richting met lengte 1 van vector1", vector1.unit(vector1));
    st::cout << "Lengte van deze vector: " << vector1.norm(vector1.unit(vector1)) << '\n';
    vector2.show("Zelfde richting met lengte 1 van vector2", vector2.unit(vector2));
    st::cout << "Lengte van deze vector: " << vector2.norm(vector2.unit(vector2)) << '\n';
    vector1.show();

    st::cout << "Inproduct vector1 met vector2: " << vector1.dot(vector1, vector2) << '\n';
    vector1.show();

    vector1.show("Uitproduct vector1 met vector2", vector1.cross(vector1, vector2));
    vector2.show("Uitproduct vector2 met vector1", vector2.cross(vector2, vector1));
    vector1.show();

    return 0;
};