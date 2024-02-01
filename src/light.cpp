#include "light.h"

vec3 Light::getColor() {
    return color;
}

float Light::getIntensity() {
    return intensity;
}

vec3 DirectionalLight::getDirection() {
    return direction;
}

vec3 SpotLight::getPosition() {
    return position;
}

vec3 SpotLight::getDirection() {
    return direction;
}

