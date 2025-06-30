#include <iostream>
#include <vector>
#include <cmath>

class Vec3D {
public:
    float x, y, z;
    Vec3D(float x = 0, float y = 0, float z = 0);
    Vec3D operator+(const Vec3D& other) const;
    float dot(const Vec3D& other) const;
    Vec3D cross(const Vec3D& other) const;
    Vec3D normalize() const;
    Vec3D sub(Vec3D const &other) const;
};

class Object {
public:
    Vec3D center;
    Object(float x, float y, float z);
    virtual bool hit(Ray& ray) = 0; // Pure virtual function
    virtual ~Object() {}
};

using VPO = std::vector<Object*>;

class Ray {
public:
    Vec3D origin, direction;
    VPO& objects;
    Ray(float xStart, float yStart, VPO& objects);
    bool scan();
};

class Sphere: public Object {
public:
    float radius;
    Sphere(float x, float y, float z, float r);
    bool hit(Ray& ray);
};

class Floor: public Object {
public:
    Floor(float x, float y, float z);
    bool hit(Ray& ray);
};

class RayScanner {
public:
    std::vector<Object*> objects;
    RayScanner();
    void scan();
};

// Define Vec3D functions
Vec3D::Vec3D(float x, float y, float z): x(x), y(y), z(z) {}
// Vector addition
Vec3D Vec3D::operator+(const Vec3D& other) const {
    return Vec3D(x + other.x, y + other.y, z + other.z);
}

// Dot product
float Vec3D::dot(const Vec3D& other) const {
    return x * other.x + y * other.y + z * other.z;
}

// Cross product
Vec3D Vec3D::cross(const Vec3D& other) const {
    return Vec3D(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
}

// Normalize
Vec3D Vec3D::normalize() const {
    float length = std::sqrt(x*x + y*y + z*z);
    return Vec3D(x / length, y / length, z / length);
}

Vec3D Vec3D::sub(Vec3D const &other) const{ // Subtract given vector 2 from given vector 1 and return the resulting vector
auto x = this->x - other.x;
auto y = this->y - other.y;
auto z = this->z - other.z;
return Vec3D(x,y,z);
};

// Define Object functions
Object::Object(float x, float y, float z) : center(x, y, z) {}

// Define Ray functions
Ray::Ray(float xStart, float yStart, VPO& objects) : origin(xStart, 0, yStart), objects(objects) {}
bool Ray::scan() {
    for (auto& obj : objects) {
        if (obj->hit(*this)) {
            return true; // Stop als de straal een object raakt
        }
    }
    return false; // Geen object geraakt
}

// Define Sphere functions
Sphere::Sphere(float x, float y, float z, float r) : Object(x, y, z), radius(r) {}
bool Sphere::hit(Ray& ray){
    // Bereken of de straal de bol raakt (gebruik de straal- en bolformule)
    Vec3D oc = ray.origin.sub(center);
    float a = ray.direction.dot(ray.direction);
    float b = 2.0f * oc.dot(ray.direction);
    float c = oc.dot(oc) - radius * radius;

    float discriminant = b * b - 4 * a * c;
    return discriminant > 0; // Als er een intersectie is
}

// Define Floor functions
Floor::Floor(float x, float y, float z) : Object(x, y, z) {}

bool Floor::hit(Ray& ray){
    // Stel: het vlak is horizontaal, dus y = constant
    float t = (0 - ray.origin.y) / ray.direction.y;
    if (t > 0) {
        // Bepaal het raakpunt op het vlak
        float x = ray.origin.x + t * ray.direction.x;
        float z = ray.origin.z + t * ray.direction.z;
        // Check of de ray op een licht- of donker veld valt
        return ((int(x) + int(z)) % 2 == 0); // Voorbeeld logica voor schaken
    }
    return false;
}

// Define RayScanner functions
RayScanner::RayScanner() {
    // Voeg objecten toe (3 Sphere's en 1 Floor)
    objects.push_back(new Floor(0, -1, 0));
    objects.push_back(new Sphere(1, 0, 5, 1));
    objects.push_back(new Sphere(-1, 0, 5, 1));
    objects.push_back(new Sphere(0, 0, 5, 1));
}

void RayScanner::scan() {
    for (int y = 0; y < 40; ++y) {
        for (int x = 0; x < 80; ++x) {
            Ray ray(x, y, objects);  // Beginpunt 3 meter achter het scherm
            if (ray.scan()) {
                std::cout << "#"; // Object geraakt
            } else {
                std::cout << "."; // Geen object geraakt
            }
        }
        std::cout << std::endl;
    }
}