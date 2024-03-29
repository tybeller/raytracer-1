#include "camera.h"

Camera::~Camera(){
    for(int i = 0; i < width; i++){
        delete[] rays[i];
    }
    delete[] rays;
}

Ray** Camera::getRays(){
    return rays;
}

Ray Camera::getRay(int i, int j){
    return rays[i][j];
}

void Camera::changeView(vec3 viewPoint, vec3 lookAt, vec3 up){
    this->viewPoint = viewPoint;
    this->lookAt = normalize(lookAt);
    this->up = normalize(up);
    generateRays();
}

void OrthographicCamera::generateRays(){
    vec3 e = viewPoint;
    vec3 w = normalize(-lookAt);
    vec3 u = normalize(cross(up, w));
    vec3 v = normalize(cross(w, u));
    
    float aspectRatio = (float)width / (float)height;
    float halfWidth = aspectRatio * 10;
    float halfHeight = 1.0 * 10;
    float pixelWidth = halfWidth * 2.0 / (float)width;
    float pixelHeight = halfHeight * 2.0 / (float)height;
    rays = new Ray*[width];
    for(int i = 0; i < width; i++){
        rays[i] = new Ray[height];
        for(int j = 0; j < height; j++){
            float x = -halfWidth + pixelWidth * (i + 0.5);
            float y = halfHeight - pixelHeight * (j + 0.5);
            vec3 origin = viewPoint + y * u + x * v;
            rays[i][j] = Ray(origin, -w);
        }
    }
}

void PerspectiveCamera::generateRays(){
    vec3 e = viewPoint;
    vec3 w = normalize(-lookAt);
    vec3 u = normalize(cross(up, w));
    vec3 v = normalize(cross(w, u));
    
    float aspectRatio = (float)width / (float)height;
    float halfWidth = aspectRatio* 10;
    float halfHeight = 1.0 * 10;
    float pixelWidth = halfWidth * 2.0 / (float)width;
    float pixelHeight = halfHeight * 2.0 / (float)height;
    rays = new Ray*[width];
    for(int i = 0; i < width; i++){
        rays[i] = new Ray[height];
        for(int j = 0; j < height; j++){
            float x = -halfWidth + pixelWidth * (i + 0.5);
            float y = halfHeight - pixelHeight * (j + 0.5);
            vec3 origin = viewPoint;
            vec3 direction = normalize(-projectionDistance*w + y*u + x*v);
            rays[i][j] = Ray(origin, direction);
        }
    }
}