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

class Ray{
    protected:
        Vec3D firstHitpoint;
    public:
        Vec3D support, direction;
        Ray(float xSup, float ySup, float zSup, float xDir, float yDir, float zDir);
        void replaceHitpoint(Vec3D const &hitpoint);
        void show();
};

class Sphere{
    protected:
        Vec3D center;
        float radius;

    public:
        Sphere(float x, float y, float z, float radius);
        float distFromRay(Ray const &ray) const;
        bool hit(Ray const &ray) const;
        Vec3D hitPoint(Ray const &ray) const;
};

// Define functions for Vec3D
Vec3D::Vec3D(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
};

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

// Define functions for Sphere
Sphere::Sphere(float x, float y, float z, float radius){
    this->center = Vec3D(x, y, z);
    this->radius = radius;
};

float Sphere::distFromRay(Ray const &ray) const{ // Calculate the distance from the centre of the sphere to the ray
    return ray.support.sub(center).cross(ray.direction).norm(); 
};

bool Sphere::hit(Ray const &ray) const{
    if(distFromRay(ray) <= this->radius){ // If the distance of the ray to the sphere is smaller or equal than its radius then it hits the sphere
        return true;
    }      
    return false;
};

Vec3D Sphere::hitPoint(Ray const &ray) const{ // Calculate where the ray hits the sphere
    auto beta = this->center.add(ray.support.sub(this->center).cross(ray.direction));
    auto a = sqrt(pow(this-> radius, 2) - pow(distFromRay(ray), 2)); // Calculate distance between beta and hitpoint
    auto gamma = beta.sub(ray.direction.mul(a)); // Calculate where gamma would be by subtracting the lenght between beta and hitpoint in the direction of the ray
    return gamma;
};

// Define functions for Ray
Ray::Ray(float xSup, float ySup, float zSup, float xDir, float yDir, float zDir){
    this->support = Vec3D(xSup, ySup, zSup);
    this->direction = Vec3D(xDir, yDir, zDir).unit(); 
    this->firstHitpoint = Vec3D(xDir, yDir, zDir);
};

void Ray::replaceHitpoint(Vec3D const &hitpoint){ // Calculate where the ray hits the sphere and return the resulting vector
    auto n = hitpoint.sub(this->support);
    auto o = firstHitpoint.sub(this->support);
    if(sqrt(pow(n.getX(), 2) + pow(n.getY(), 2) + pow(n.getY(), 2)) < sqrt(pow(o.getX(), 2) + pow(o.getY(), 2) + pow(o.getY(), 2))){
        //If the lenght of the vector from ray origin to hitpoint is smaller then the lenght of the ray origin to the older hitpoint overwrite first hitpoint
        this->firstHitpoint = hitpoint;
    }
    return;
}

void Ray::show(){
    this->firstHitpoint.show("Raakpunt");
};

int main(){
    auto far = 2e31;

    auto spheres = st::vector<Sphere>({
        Sphere(-0.4, 0.23, -1, 0.4), 
        Sphere(0.4, 0.4, -1.2, 0.3), 
        Sphere(0.7, -0.15, -1.5, 0.2)
    });

    auto rays = st::vector<Ray>({
        Ray(-far, 0.23, -1.0, far, 0.0, 0.0), 
        Ray(0.4, -far, -1.2, 0.0, far, 0.0), 
        Ray(0.7, -0.15, -far, 0.0, 0.0, far)
    });
    
    for(auto &ray:rays){
        for(auto &sphere:spheres){
            if(sphere.hit(ray)){
                ray.replaceHitpoint(sphere.hitPoint(ray));
            }
        }
        ray.show();
    }

    return 0;
};