#pragma once
#include <vector>
#include "surface.h"
#include "camera.h"
#include "light.h"

using std::vector;

class Scene {
public:
    Scene();
    ~Scene();
    void addSurface(Surface* surface);
    void addLight(Light* light);
    void setAmbientLight(AmbientLight ambientLight);
    void renderImage(Camera* cam);
    vec3 trace(Ray ray);
    unsigned char* getImage();
    
protected:
    vector<Surface*> surfaces;
    vector<Light*> lights;
    AmbientLight ambientLight;
    unsigned char* image;
};