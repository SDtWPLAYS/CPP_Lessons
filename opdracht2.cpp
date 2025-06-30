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

    void show(st::string label, Vec3D const &self){ // Print the given string with some constant strings and the x, y, z value of the given vector
        st::cout << label << " is op de coordinaten: x = " << self.x << " y = " << self.y << " z = " << self.z << "\n";
    };

    void show(st::string label, float scalar){ // Print the given string with a constant string and the given float
        st::cout << label << " is de scalar: " << scalar << "\n";
    };

    void show(){ // Print an empty line
        st::cout << '\n';
    };

    Vec3D minus(Vec3D const &self){ // Calculate the vector going in the exact opposite direction of the given vector and return it
        auto x = -self.x;
        auto y = -self.y;
        auto z = -self.z;
        return Vec3D(x,y,z);
    };

    Vec3D add(Vec3D const &self, Vec3D const &other){ // Add given vector 2 to given vector 1 and return the resulting vector
        auto x = self.x + other.x;
        auto y = self.y + other.y;
        auto z = self.z + other.z;
        return Vec3D(x,y,z);
    };

    Vec3D sub(Vec3D const &self, Vec3D const &other){ // Subtract given vector 2 from given vector 1 and return the resulting vector
        auto x = self.x - other.x;
        auto y = self.y - other.y;
        auto z = self.z - other.z;
        return Vec3D(x,y,z);
    };

    Vec3D mul(Vec3D const &self, float scalar){ // Multiply the given vector with the given float scalar and return the resulting vector
        auto x = self.x * scalar;
        auto y = self.y * scalar;
        auto z = self.z * scalar;
        return Vec3D(x,y,z);
    };

    Vec3D div(Vec3D const &self, float scalar){ // Divide the given vector by the given float scalar and return the resulting vector
        auto x = self.x / scalar;
        auto y = self.y / scalar;
        auto z = self.z / scalar;
        return Vec3D(x,y,z);
    };

    float norm(Vec3D const &self){ // Calculate the lenght of the given vector and return it
        auto length = pow(pow(self.x,2) + pow(self.y,2) + pow(self.z,2), 0.5);
        return length;
    };

    Vec3D unit(Vec3D const &self){ // Calculate the vector with lenght 1 in the same direction as the given vector and return it
        auto scalar = norm(self);
        return div(self, scalar);
    };

    float dot(Vec3D const &self, Vec3D const &other){ // Calculate the dot product of the 2 given vectors and return it
        auto x = self.x * other.x;
        auto y = self.y * other.y;
        auto z = self.z * other.z;
        return x + y + z;
    };
    
    Vec3D cross(Vec3D const &self, Vec3D const &other){ // Calculate the crossproduct of the given vector with the other given vector and return the resulting vector
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
    vector1.show("Correct antwoord vector1 negatief", Vec3D(-0.4, -4.2, -1.8));
    vector2.show("Vector2 negatief", vector2.minus(vector2));
    vector2.show("Correct antwoord vector2 negatief", Vec3D(-3.7, -2.4, -5.0));
    vector1.show();

    vector1.show("Vector1 + vector2", vector1.add(vector1, vector2));
    vector1.show("Correct antwoord vector1 + vector2", Vec3D(4.1, 6.6, 6.8));
    vector1.show();

    vector1.show("Vector1 - vector2", vector1.sub(vector1, vector2));
    vector1.show("Correct antwoord vector1 - vector2", Vec3D(-3.3, 1.8, -3.2));
    vector2.show("Vector2 - vector1", vector2.sub(vector2, vector1));
    vector2.show("Correct antwoord vector2 - vector1", Vec3D(3.3, -1.8, 3.2));
    vector1.show();

    vector1.show("Vector1 x 5", vector1.mul(vector1, 5));
    vector1.show("Correct antwoord vector1 x 5", Vec3D(2., 21., 9.));
    vector2.show("Vector2 x 5", vector2.mul(vector2, 5));
    vector2.show("Correct antwoord vector2 x 5", Vec3D(18.5, 12., 25.));
    vector1.show();

    vector1.show("Vector1 / 2", vector1.div(vector1, 2));
    vector1.show("Correct antwoord vector1 / 2", Vec3D(0.2, 2.1, 0.9));
    vector2.show("Vector2 / 2", vector2.div(vector2, 2));
    vector2.show("Correct antwoord vector2 / 2", Vec3D(1.85, 1.2, 2.5));
    vector1.show();

    st::cout << "Lengte van vector1: " << vector1.norm(vector1) << '\n';
    st::cout << "Correcte lengte van vector1: " << 4.586937976 << '\n';
    st::cout << "Lengte van vector2: " << vector2.norm(vector2) << '\n';
    st::cout << "Correcte lengte van vector2: " << 6.66708332 << '\n';
    vector1.show();

    vector1.show("Zelfde richting met lengte 1 van vector1", vector1.unit(vector1));
    st::cout << "Lengte van deze vector: " << vector1.norm(vector1.unit(vector1)) << '\n';
    vector1.show("Correcte vector in dezelfde richting als vector1 met lengte 1", Vec3D(0.087204144, 0.915643512, 0.392418648));
    vector2.show("Zelfde richting met lengte 1 van vector2", vector2.unit(vector2));
    st::cout << "Lengte van deze vector: " << vector2.norm(vector2.unit(vector2)) << '\n';
    vector2.show("Correcte vector in dezelfde richting als vector2 met lengte 1", Vec3D(0.554965315, 0.359977502, 0.749953129));
    vector1.show();

    st::cout << "Inproduct vector1 met vector2: " << vector1.dot(vector1, vector2) << '\n';
    st::cout << "Correcte inproduct van vector 1 met vector 2: " << 20.56 << '\n';
    vector1.show();

    vector1.show("Uitproduct vector1 met vector2", vector1.cross(vector1, vector2));
    vector1.show("Correcte uitproduct vector1 met vector2", Vec3D(16.68, 4.66, -14.58));
    vector2.show("Uitproduct vector2 met vector1", vector2.cross(vector2, vector1));
    vector2.show("Correcte uitproduct vector2 met vector1", Vec3D(-16.68, -4.66, 14.58));
    vector1.show();
    return 0;
};