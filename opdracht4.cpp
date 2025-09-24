#include <iostream>
#include <vector>
#include <cmath>

namespace st = std;

class Vec3D{
    protected:
        float x, y, z;

    public:
        Vec3D(float x = 0, float y = 0, float z = 0);
        float getX();
        float getY();
        float getZ();
        void show(st::string label);
        void show(st::string label, float scalar);
        void show();
        Vec3D minus() const;
        Vec3D add(Vec3D const &other) const;
        Vec3D sub(Vec3D const &other) const;
        Vec3D mul(float scalar) const;
        Vec3D div(float scalar) const;
        float norm() const;
        Vec3D unit() const;
        float dot(Vec3D const &other) const;
        Vec3D cross(Vec3D const &other) const;
    };

class Object{
    protected:
        float x, y, z;
        Vec3D center;
    public:
        Object(float x, float y, float z);
        virtual bool hit(Ray &ray) = 0;
};

class Ray{ // VPO most likely means virtual private object!
    protected:
        Vec3D firstHitpoint;
    public:
        Vec3D support, direction;
        Ray(float xSup, float ySup, float zSup, float xDir, float yDir, float zDir);
        void replaceHitpoint(Vec3D const &hitpoint);
        void show();
        bool scan();
};

class Sphere:Object{
    protected:
        float radius;

    public:
        Sphere(float x, float y, float z, float radius);
        float distFromRay(Ray const &ray) const;
        bool hit(Ray const &ray) const;
        Vec3D hitPoint(Ray const &ray) const;
};

class Floor:Object{
    protected:
    public:
        Floor();
        bool hit(Ray const &ray)const;
};

class RayScanner{
    protected:
        st::vector<Object> objects;
    public:
        RayScanner(Sphere sphere0, Sphere sphere1, Sphere sphere2, Floor floor);
        void scan(); // 80 breed 40 hoog. Oogpunt zit 3 meter achtere scherm
};

// Define functions for Vec3D
Vec3D::Vec3D(float x, float y, float z):x(x), y(y), z(z){};

float Vec3D::getX(){return this->x;};
float Vec3D::getY(){return this->y;};
float Vec3D::getZ(){return this->z;};

void Vec3D::show(st::string label){ // Print the given string with some constant strings and the x, y, z value of the given vector
    st::cout << label << " is op de coordinaten: x = " << this->x << " y = " << this->y << " z = " << this->z << "\n";
};

void Vec3D::show(st::string label, float scalar){ // Print the given string with a constant string and the given float
    st::cout << label << " is de scalar: " << scalar << "\n";
};

void Vec3D::show(){ // Print an empty line
    st::cout << '\n';
};

Vec3D Vec3D::minus() const{ // Calculate the vector going in the exact opposite direction of the given vector and return it
    auto x = -this->x;
    auto y = -this->y;
    auto z = -this->z;
    return Vec3D(x,y,z);
};

Vec3D Vec3D::add(Vec3D const &other) const{ // Add given vector 2 to given vector 1 and return the resulting vector
    auto x = this->x + other.x;
    auto y = this->y + other.y;
    auto z = this->z + other.z;
    return Vec3D(x,y,z);
};

Vec3D Vec3D::sub(Vec3D const &other) const{ // Subtract given vector 2 from given vector 1 and return the resulting vector
    auto x = this->x - other.x;
    auto y = this->y - other.y;
    auto z = this->z - other.z;
    return Vec3D(x,y,z);
};

Vec3D Vec3D::mul(float scalar) const{ // Multiply the given vector with the given float scalar and return the resulting vector
    auto x = this->x * scalar;
    auto y = this->y * scalar;
    auto z = this->z * scalar;
    return Vec3D(x,y,z);
};

Vec3D Vec3D::div(float scalar) const{ // Divide the given vector by the given float scalar and return the resulting vector
    auto x = this->x / scalar;
    auto y = this->y / scalar;
    auto z = this->z / scalar;
    return Vec3D(x,y,z);
};

float Vec3D::norm() const{ // Calculate the lenght of the given vector and return it
    float length = pow(pow(this->x,2) + pow(this->y,2) + pow(this->z,2), 0.5);
    return length;
};

Vec3D Vec3D::unit() const{ // Calculate the vector with lenght 1 in the same direction as the given vector and return it
    auto scalar = norm();
    return div(scalar);
};

float Vec3D::dot(Vec3D const &other) const{ // Calculate the dot product of the 2 given vectors and return it
    auto x = this->x * other.x;
    auto y = this->y * other.y;
    auto z = this->z * other.z;
    return x + y + z;
};

Vec3D Vec3D::cross(Vec3D const &other) const{ // Calculate the crossproduct of the given vector with the other given vector and return the resulting vector
    auto x = this->y * other.z - this->z * other.y;
    auto y = this->z * other.x - this->x * other.z;
    auto z = this->x * other.y - this->y * other.x;
    return Vec3D(x,y,z);
};

// Initialize Object
Object::Object(float x, float y, float z): center(x, y, z){}

// Initialize Ray
Ray::Ray(float xSup, float ySup, float zSup, float xDir, float yDir, float zDir){
    this->support = Vec3D(xSup, ySup, zSup);
    this->direction = Vec3D(xDir, yDir, zDir);
};

// Initialize Sphere
Sphere::Sphere(float x, float y, float z, float radius): Object(x, y, z){
    this->radius = radius;
};

// Initialize Floor
Floor::Floor(): Object(x, y, z){

};

// Initialize Rayscanner
RayScanner::RayScanner(Sphere sphere0, Sphere sphere1, Sphere sphere2, Floor floor){
    this->objects.push_back(sphere0);
    this->objects.push_back(sphere1);
    this->objects.push_back(sphere2);
    this->objects.push_back(floor);
};