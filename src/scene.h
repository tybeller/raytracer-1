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
    void setCamera(Camera* camera);
    void getCamera();
    void addLight(Light* light);
    void setAmbientLight(AmbientLight ambientLight);

    vec3 trace(Ray ray);
    
protected:
    vector<Surface*> surfaces;
    Camera* camera;
    vector<Light*> lights;
    AmbientLight ambientLight;
};