#include "surface.h"

float Sphere::getIntersection(Ray ray) {
    vec3 oc = ray.getOrigin() - center;
    float a = glm::dot(ray.getDirection(), ray.getDirection());
    float b = 2.0f * glm::dot(oc, ray.getDirection());
    float c = glm::dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return -1.0f;
    } else {
        return (-b - sqrt(discriminant)) / (2.0f * a);
    }
}

float Triangle::getIntersection(Ray ray) {
    vec3 e1 = vertices[1] - vertices[0];
    vec3 e2 = vertices[2] - vertices[0];
    vec3 h = glm::cross(ray.getDirection(), e2);
    float a = glm::dot(e1, h);
    if (a > -0.00001 && a < 0.00001) {
        return -1.0f;
    }
    float f = 1.0f / a;
    vec3 s = ray.getOrigin() - vertices[0];
    float u = f * glm::dot(s, h);
    if (u < 0.0f || u > 1.0f) {
        return -1.0f;
    }
    vec3 q = glm::cross(s, e1);
    float v = f * glm::dot(ray.getDirection(), q);
    if (v < 0.0f || u + v > 1.0f) {
        return -1.0f;
    }
    float t = f * glm::dot(e2, q);
    if (t > 0.00001) {
        return t;
    } else {
        return -1.0f;
    }
}

float Plane::getIntersection(Ray ray) {
    float denominator = glm::dot(normal, ray.getDirection());
    if (denominator > 0.00001 || denominator < -0.00001) {
        float t = (d - glm::dot(normal, ray.getOrigin())) / denominator;
        if (t > 0.00001) {
            return t;
        }
    }
    return -1.0f;
}

vec3 Sphere::getNormal(vec3 point) {
    return glm::normalize(point - center);
}

vec3 Triangle::getNormal(vec3 point) {
    return glm::cross(vertices[1] - vertices[0], vertices[2] - vertices[0]);
}

vec3 Plane::getNormal(vec3 point) {
    return normal;
}
