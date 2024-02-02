#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "surface.h"

using glm::vec3;
using std::vector;

class Light {
public:
    Light(vec3 color, vec3 direction, float intensity) : color(color), intensity(intensity), direction(normalize(direction)) {};
    vec3 getColor();
    float getIntensity(vec3 pointPosition = vec3(0.0f));
    vec3 getDirection();
protected:
    vec3 color;
    float intensity;
    vec3 direction;
};

class SpotLight : public Light {
public:
    SpotLight(vec3 color, vec3 direction, float intensity, vec3 position, float angle) : Light(color, direction, intensity), position(position), angle(angle) {};
    
    float getIntensity(vec3 pointPosition);
    vec3 getPosition();
    float getAngle();
private:
    vec3 position;
    float angle;
};

class AmbientLight {
public:
    AmbientLight() : color(vec3(1.0f, 1.0f, 1.0f)), intensity(0.1f) {};
    AmbientLight(vec3 color, float intensity) : color(color), intensity(intensity) {};
    vec3 getColor();
    float getIntensity();
private:
    vec3 color;
    float intensity;
};