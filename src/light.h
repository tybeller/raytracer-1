#pragma once
#include <glm/glm.hpp>

using glm::vec3;

class Light {
public:
    Light(vec3 color, float intensity) : color(color), intensity(intensity) {};
    vec3 getColor();
    float getIntensity();

protected:
    glm::vec3 color;
    float intensity;
};

class AmbientLight : public Light {
public:
    AmbientLight(vec3 color, float intensity) : Light(color, intensity) {};
};

class DirectionalLight : public Light {
public:
    DirectionalLight(vec3 color, float intensity, vec3 direction) : Light(color, intensity), direction(direction) {};
    vec3 getDirection();
private:
    vec3 direction;
};

class SpotLight : public Light {
public:
    SpotLight(vec3 color, float intensity, vec3 position, vec3 direction, float angle) : Light(color, intensity), position(position), direction(direction), angle(angle) {};
    vec3 getPosition();
    vec3 getDirection();
private:
    vec3 position;
    vec3 direction;
    float angle;
};