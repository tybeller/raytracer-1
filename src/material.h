#pragma once
#include <glm/glm.hpp>

using glm::vec3;


class Material {
public:
    /* Material has ambient, diffuse, and specular components
    Each component has a color and a strength
    The specular component also has a phong exponent
    The material can also be glazed (reflective) */

    Material(vec3 ambientColor, float ambientStr, 
            vec3 diffuseColor, float diffuseStr, 
            vec3 specularColor, float specularStr, 
            float phongExp, 
            bool glazed = false) : 
        ambientColor(ambientColor), ambientStrength(ambientStr),
        diffuseColor(diffuseColor), diffuseStrength(diffuseStr),
        specularColor(specularColor), specularStrength(specularStr), phongExp(phongExp), 
        glazed(glazed) {}

    vec3 ambientColor;
    float ambientStrength;

    vec3 diffuseColor;
    float diffuseStrength;

    vec3 specularColor;
    float specularStrength;

    float phongExp;

    bool glazed;
};