#pragma once
#include <glm/glm.hpp>
#include "material.h"
#include "ray.h"

using glm::vec3;

/*We will have 2 type of surfaces, spheres and triangles
each surface will have a material property

*/
class Surface {
public:
    Surface(Material material) : material(material) {}
    virtual float getIntersection(Ray ray) = 0;
    Material getMaterial() { return material; }
    virtual vec3 getNormal(vec3 point) = 0;
protected:
    Material material;
};

class Sphere : public Surface {
public:
    Sphere(float radius, vec3 center, Material material) : radius(radius), center(center), Surface(material) {}
    using Surface::getIntersection;
    float getIntersection(Ray ray) override;
    vec3 getNormal(vec3 point) override;

private:
    float radius;
    vec3 center;
};

class Triangle : public Surface {
public:
    Triangle(vec3 v1, vec3 v2, vec3 v3, Material material) : vertices{v1, v2, v3}, Surface(material) {}
    using Surface::getIntersection;
    float getIntersection(Ray ray) override;
    vec3 getNormal(vec3 point) override;
private:
    vec3 vertices[3];
};

class Plane : public Surface {
public:
    Plane(vec3 normal, float d, Material material) : normal(normal), d(d), Surface(material) {}
    using Surface::getIntersection;
    float getIntersection(Ray ray) override;
    vec3 getNormal(vec3 point) override;
private:
    vec3 normal;
    float d;
};