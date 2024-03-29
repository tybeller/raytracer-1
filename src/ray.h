#pragma once
#include <glm/glm.hpp>

using glm::vec3;

class Ray {
public:
    Ray() {}
    Ray(const vec3& origin, const vec3& direction) : orig(origin), dir(normalize(direction)) {}
    vec3 getOrigin() const { return orig; }
    vec3 getDirection() const { return dir; }
    vec3 at(double t) const { return orig + float(t) * dir; }

private:
    vec3 orig;
    vec3 dir;
};