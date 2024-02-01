#include "scene.h"

Scene::Scene() {
    surfaces = vector<Surface*>();
    camera = NULL;
    lights = vector<Light*>();
}

Scene::~Scene() {
    for (int i = 0; i < surfaces.size(); i++) {
        delete surfaces[i];
    }
    if (camera != NULL) {
        delete camera;
    }
    for (int i = 0; i < lights.size(); i++) {
        delete lights[i];
    }
}

void Scene::addSurface(Surface* surface) {
    surfaces.push_back(surface);
}

void Scene::setCamera(Camera* camera) {
    this->camera = camera;
}

void Scene::addLight(Light* light) {
    lights.push_back(light);
}

void Scene::setAmbientLight(AmbientLight ambientLight) {
    this->ambientLight = ambientLight;
}

vec3 Scene::trace(Ray ray) {
    vec3 color = vec3(0.0f, 0.0f, 0.0f);
    for (int i = 0; i < surfaces.size(); i++) {
        vec3 surfaceColor = surfaces[i]->getMaterial().ambientColor;
        vec3 surfaceNormal = surfaces[i]->getNormal(ray.getOrigin());
        vec3 surfacePosition = surfaces[i]->getIntersection(ray) * ray.getDirection() + ray.getOrigin();

        vec3 surfaceToLight = vec3(0.0f, 0.0f, 0.0f);
        for (int j = 0; j < lights.size(); j++) {

            /*TODO right now this is all sorts of fucked up

            fix the surface color, right now thats not right

            add ambient light, maybe switch ambient light to be a seperate class from light

            */
            if (lights[j]->getIntensity(surfacePosition) > 0) {
                surfaceToLight = lights[j]->getPosition() - surfacePosition;
                Ray shadowRay = Ray(surfacePosition, surfaceToLight);
                bool inShadow = false;
                for (int k = 0; k < surfaces.size(); k++) {
                    if (surfaces[k]->getIntersection(shadowRay) != vec3(0.0f, 0.0f, 0.0f)) {
                        inShadow = true;
                        break;
                    }
                }
                if (!inShadow) {
                    vec3 lightColor = lights[j]->getColor();
                    float lightIntensity = lights[j]->getIntensity(surfacePosition);
                    float diffuse = dot(surfaceNormal, normalize(surfaceToLight));
                    color += surfaceColor * lightColor * lightIntensity * diffuse;
                }
            }
        }
    }
    return color;
}