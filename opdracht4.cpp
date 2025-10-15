#include <iostream>
#include <vector>
#include <cmath>
#include <C:\Users\Stijn\Documents\HR\Jaar2\programmeren_cpp\opdrachten\vec3D.cpp>

namespace st = std;

class Object{
    protected:
        float x, y, z;
        Vec3D center;
    public:
        Object(float x, float y, float z);
        virtual bool hit(Ray &ray) = 0;
};

class Ray{ 
    // VPO most likely means virtual private object!
    protected:
        Vec3D firstHitpoint;
    public:
        Vec3D support, direction;
        Ray(float xSup, float ySup, float zSup, float xDir, float yDir, float zDir);
        void replaceHitpoint(Vec3D const &hitpoint);
        void show();
        bool scan();
};

class Sphere:public Object{
    protected:
        float radius;

    public:
        Sphere(float x, float y, float z, float radius);
        float distFromRay(Ray const &ray) const;
        bool hit(Ray &ray);
        Vec3D hitPoint(Ray &ray) const;
};

class Floor:public Object{
    protected:
    public:
        Floor();
        bool hit(Ray &ray);
};

class RayScanner{
    protected:
        st::vector<Object> objects;
    public:
        RayScanner(Sphere sphere0, Sphere sphere1, Sphere sphere2, Floor floor);
        void scan(int screenWidth); 
};

// Initialize Object
Object::Object(float x, float y, float z): center(x, y, z){};

// Initialize Ray
Ray::Ray(float xSup, float ySup, float zSup, float xDir, float yDir, float zDir){
    this->support = Vec3D(xSup, ySup, zSup);
    this->direction = Vec3D(xDir, yDir, zDir);
};

// Initialize Sphere
Sphere::Sphere(float x, float y, float z, float radius): Object(x, y, z){
    this->radius = radius;
};

float Sphere::distFromRay(Ray const &ray) const{ // Calculate the distance from the centre of the sphere to the ray
    return ray.support.sub(center).cross(ray.direction).norm(); 
};

bool Sphere::hit(Ray &ray){
    // if(distFromRay(ray) <= this->radius){ // If the distance of the ray to the sphere is smaller or equal than its radius then it hits the sphere
    //     return true;
    // }      
    return false;
};

// Initialize Floor
Floor::Floor(): Object(0.0, -25.0, 0.0){ // Initialize floor 25 meters below center of the screen

};

bool Floor::hit(Ray &ray){
    auto directionY = ray.direction.getY();
    if(directionY >= 0) return false; // If y in direction >= 0 then the vector does not go down and because of that will never hit the floor
    auto lengthHitVector = this->y / directionY;
    auto hitX = ray.direction.getX() * lengthHitVector;
    auto hitZ = ray.direction.getZ() * lengthHitVector;
    if(st::fmod(hitX, 16) < 8){
        if(st::fmod(hitZ, 8) > 4) return true;
    }
    else{
        if(st::fmod(hitZ, 8) < 4) return true;
    };
    return false;
}

// Initialize Rayscanner
RayScanner::RayScanner(Sphere sphere0, Sphere sphere1, Sphere sphere2, Floor floor){
    this->objects.push_back(sphere0);
    this->objects.push_back(sphere1);
    this->objects.push_back(sphere2);
    this->objects.push_back(floor);
};

void RayScanner::scan(int screenWidth){ 
    st::vector<st::vector<bool>> screen;
    for(int x = -(screenWidth/2); x < screenWidth/2; x++){ // width of the screen
        for(int y = -(screenWidth/4); y < screenWidth/4; y++){ // height of the screen
            auto ray = Ray(0.0, 0.0, -3.0, x, y, 0.0); // start ray 3 meters in front of the screen and goes to the correct pixel in the screen
            bool hit = false;
            for(auto &object:objects){
                if(object.hit(ray)) hit = true;
            };
            screen.emplace_back();
            if(hit){
                screen[y+(screenWidth/4)].push_back(0.25);
            }
            else screen[y+(screenWidth/4)].push_back(0.0);
        }
    }

    for(auto y:screen){ // Print screen
        for(auto x:y){
            if(x == 0.0){ // No brightness
                st::cout << "  ";
            }
            // else if(x == 0.25){ // Low brightness
            //     st::cout << "LL";
            // }
            // else if(x == 0.5){ // Medium brightness
            //     st::cout << "PP";
            // }
            else{
                st::cout << "NN"; // High brightness
            }
        }
    }
};

int main(){
    auto floor = Floor();
    auto sphere1 = Sphere(-5, 15, 2, 3);
    auto sphere2 = Sphere(30, 8, 8, 4.5);
    auto sphere3 = Sphere(-20.8, 3.6, 9.2, 1.75);
    auto rayscanner = RayScanner(sphere1, sphere2, sphere3, floor);
    rayscanner.scan(80); // 80 breed (80 / 2) 40 hoog. Oogpunt zit 3 meter achter het scherm 1.7 meter van de grond
    return 0;
};