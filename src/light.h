#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "surface.h"

using glm::vec3;
using std::vector;

class Light {
public:
    Light(vec3 color, vec3 direction, float intensity) : color(color), intensity(intensity), direction(normalize(direction)) {};
    virtual ~Light() {};
    vec3 getColor();
    float getIntensity(vec3 pointPosition = vec3(0.0f));
    vec3 getDirection();
protected:
    vec3 color;
    float intensity;
    vec3 direction;
};

class DirectionalLight : public Light {
public:
    DirectionalLight(vec3 color, vec3 direction, float intensity) : Light(color, direction, intensity) {};
};


class SpotLight : public Light {
public:
    SpotLight(vec3 color, vec3 direction, float intensity, vec3 position, float maxAngle) : Light(color, direction, intensity), position(position), maxAngle(maxAngle) {};
    
    float getIntensity(vec3 pointPosition);
    vec3 getSpotLightDirection(vec3 pointPosition);
    vec3 getPosition();
    float getMaxAngle();
private:
    vec3 position;
    float maxAngle;
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