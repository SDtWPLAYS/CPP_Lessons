#include <iostream>
#include <vector>
#include <cmath>
#include <C:\Users\Stijn\Documents\HR\Jaar2\programmeren_cpp\opdrachten\vec3D.cpp>

namespace st = std;

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

// // Define functions for Sphere
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

    // test part
    Sphere testSphere = Sphere(1.0, 10.0, 5.0, 2.0);
    Ray testRayForward = Ray(1.0, 10.0, -far, 0.0, 0.0, far);
    Ray testRayUp = Ray(1.0, -far, 5.0, 0.0, far, 0.0);
    Ray testRaySide = Ray(-far, 10.0, 5.0, far, 0.0, 0.0);
    if(testSphere.hit(testRayForward)){
        testRayForward.replaceHitpoint(testSphere.hitPoint(testRayForward));
        testRayForward.show();
    }
    else st::cout << "No hit!";
    // Expected hit at x = 1, y = 10, z = 3 with testSphere(1.0, 10.0, 5.0, 2.0) and testRayForward(1.0, 10.0, -far, 0.0, 0.0, far)
    if(testSphere.hit(testRayUp)){
        testRayUp.replaceHitpoint(testSphere.hitPoint(testRayUp));
        testRayUp.show();
    }
    else st::cout << "No hit!";
    // Expected hit at x = 1, y = 8, z = 5 with testSphere(1.0, 10.0, 5.0, 2.0) and testRayUp(1.0, -far, 5.0, 0.0, far, 0.0)
    if(testSphere.hit(testRaySide)){
        testRaySide.replaceHitpoint(testSphere.hitPoint(testRaySide));
        testRaySide.show();
    }
    else st::cout << "No hit!";
    // Expected hit at x = -1, y = 10, z = 5 with testSphere(1.0, 10.0, 5.0, 2.0) and testRaySide(-far, 10.0, 5.0, far, 0.0, 0.0)

    return 0;
};