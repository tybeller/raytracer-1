#include "light.h"

vec3 Light::getColor() {
    return color;
}

float Light::getIntensity(vec3 pointPosition) {
    return intensity;
}

vec3 Light::getDirection() {
    return direction;
}

float SpotLight::getIntensity(vec3 pointPosition) {
    //TODO  
    return 0.0f;
}

vec3 SpotLight::getPosition() {
    return position;
}

float SpotLight::getAngle() {
    return angle;
}

vec3 AmbientLight::getColor() {
    return color;
}

float AmbientLight::getIntensity() {
    return intensity;
}
