#pragma once
#include <glm/glm.hpp>
#include "ray.h"

using glm::vec2;
using glm::vec3;
using glm::cross;
using glm::normalize;

class Camera{
public:
    Camera(int width, int height, vec3 viewPoint, vec3 lookAt, vec3 up) : width(width), height(height), viewPoint(viewPoint), lookAt(normalize(lookAt)), up(normalize(up)){
        t = 10.0f;
        b = -10.0f;
        l = -10.0f;
        r = 10.0f;
    };
    ~Camera();
    vec2 pixelToPos(int i, int j);
    Ray** getRays();
    Ray getRay(int i, int j);

    vec3 getPosition() {
        return viewPoint;
    }
protected:
    int width;
    int height;
    vec3 lookAt; 
    vec3 up; // up vector
    vec3 viewPoint; // camera position
    float t, b, l, r; // top, bottom, left, right
    virtual void generateRays() = 0;
    Ray** rays;
};

class OrthographicCamera : public Camera {
public:
    OrthographicCamera(int width, int height, vec3 viewPoint, vec3 lookAt, vec3 up) : Camera(width, height, viewPoint, lookAt, up) {
        generateRays();
    }
    void generateRays() override;
};

class PerspectiveCamera : public Camera {
public:
    PerspectiveCamera(int width, int height, vec3 viewPoint, vec3 lookAt, vec3 up, float projectionDistance) : Camera(width, height, viewPoint, lookAt, up), projectionDistance(projectionDistance) {\
        generateRays();
    }
    void generateRays() override;
private:
    float projectionDistance;
};