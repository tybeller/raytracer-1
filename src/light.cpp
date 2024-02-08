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

vec3 SpotLight::getSpotLightDirection(vec3 pointPosition) {
    return normalize(position - pointPosition);
    
}

float SpotLight::getIntensity(vec3 pointPosition) {
    vec3 lightDirection = pointPosition - position;
    float distance = length(lightDirection);
    lightDirection = normalize(lightDirection);
    float angle = acos(dot(lightDirection, direction));
    if (angle > maxAngle) {
        return 0.0f;
    }
    return intensity / (distance * distance) * (1.0f - angle / maxAngle);
}

vec3 SpotLight::getPosition() {
    return position;
}

float SpotLight::getMaxAngle() {
    return maxAngle;
}

vec3 AmbientLight::getColor() {
    return color;
}

float AmbientLight::getIntensity() {
    return intensity;
}
