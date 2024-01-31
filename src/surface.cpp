#include "surface.h"

float Sphere::intersects(Ray ray) {
    vec3 oc = ray.origin() - center;
    float a = glm::dot(ray.direction(), ray.direction());
    float b = 2.0f * glm::dot(oc, ray.direction());
    float c = glm::dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return -1.0f;
    } else {
        return (-b - sqrt(discriminant)) / (2.0f * a);
    }
}

float Triangle::intersects(Ray ray) {
    vec3 e1 = vertices[1] - vertices[0];
    vec3 e2 = vertices[2] - vertices[0];
    vec3 h = glm::cross(ray.direction(), e2);
    float a = glm::dot(e1, h);
    if (a > -0.00001 && a < 0.00001) {
        return -1.0f;
    }
    float f = 1.0f / a;
    vec3 s = ray.origin() - vertices[0];
    float u = f * glm::dot(s, h);
    if (u < 0.0f || u > 1.0f) {
        return -1.0f;
    }
    vec3 q = glm::cross(s, e1);
    float v = f * glm::dot(ray.direction(), q);
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

float Plane::intersects(Ray ray) {
    float denominator = glm::dot(normal, ray.direction());
    if (denominator > 0.00001 || denominator < -0.00001) {
        float t = (d - glm::dot(normal, ray.origin())) / denominator;
        if (t > 0.00001) {
            return t;
        }
    }
    return -1.0f;
}