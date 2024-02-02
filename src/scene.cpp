#include "scene.h"

#include <glm/glm.hpp>
#include <typeinfo>

Scene::Scene() {
    surfaces = vector<Surface*>();
    lights = vector<Light*>();
    ambientLight = AmbientLight();
}

Scene::~Scene() {
    for (int i = 0; i < surfaces.size(); i++) {
        delete surfaces[i];
    }
    for (int i = 0; i < lights.size(); i++) {
        delete lights[i];
    }
}

void Scene::addSurface(Surface* surface) {
    surfaces.push_back(surface);
}

void Scene::addLight(Light* light) {
    lights.push_back(light);
}

void Scene::setAmbientLight(AmbientLight ambientLight) {
    this->ambientLight = ambientLight;
}

vec3 Scene::trace(Ray visionRay) {
    vec3 color = vec3(0.0f, 0.0f, 0.0f);
    float t = -1.0f;
    Surface* closestSurface = NULL;
    for (int i = 0; i < surfaces.size(); i++) {
        float surfaceT = surfaces[i]->getIntersection(visionRay);
        if (surfaceT > 0.0f && (t < 0.0f || surfaceT < t)) {
            t = surfaceT;
            closestSurface = surfaces[i];
        }
    }
    if (closestSurface != NULL) {
        //add ambient light
        Material surfaceMaterial = closestSurface->getMaterial();

        color += ambientLight.getColor() * ambientLight.getIntensity() * surfaceMaterial.getAmbient();

        /*
        vec3 impactPoint = visionRay.getOrigin() + t * visionRay.getDirection();
        vec3 normal = closestSurface->getNormal(impactPoint);
        // check that the normal is in the right direction
        if (glm::dot(normal, visionRay.getDirection()) > 0) {
            normal = -normal;
        }
        //add diffuse light
        for (int i = 0; i < lights.size(); i++) {
            vec3 lightDirection = lights[i]->getDirection() * -1.0f;
            float lightIntensity = lights[i]->getIntensity(impactPoint);


            //check if the light hits the object
            

    

        }*/


    }
    return color;
}