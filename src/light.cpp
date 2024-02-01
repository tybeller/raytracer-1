#include "light.h"

vec3 Light::getColor() {
    return color;
}

float Light::getIntensity(vec3 pointPosition) {
    return intensity;
}

vec3 DirectionalLight::getDirection() {
    return direction;
}

float SpotLight::getIntensity(vec3 pointPosition) {
    //TODO  
}

vec3 SpotLight::getPosition() {
    return position;
}

vec3 SpotLight::getDirection() {
    return direction;
}

