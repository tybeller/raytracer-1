// Based on templates from learnopengl.com
#define GLEW_STATIC
#include <GL/glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <vector>

#include "surface.h"
#include "camera.h"
#include "light.h"
#include "scene.h"

#include <iostream>

using glm::vec3;
using std::vector;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;


const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "layout (location = 2) in vec2 aTexCoord;\n"
    "out vec3 ourColor;\n"
    "out vec2 TexCoord;\n"
    "void main()\n"
    "{\n"
	"gl_Position = vec4(aPos, 1.0);\n"
	"ourColor = aColor;\n"
	"TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 ourColor;\n"
    "in vec2 TexCoord;\n"
    "uniform sampler2D texture1;\n"
    "void main()\n"
    "{\n"
    "   FragColor = texture(texture1, TexCoord);\n"
    "}\n\0";
    

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "RAYTRACING BABY", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // // GLEW: load all OpenGL function pointers
    glewInit();

    // build and compile the shaders
    // ------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions          // colors           // texture coords
         1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    // load and create a texture 
    // -------------------------
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


    /* PLAN:
    This is where we will be making the most changes
    psuedo code from lecture:

    Camera(ortho, perspective)
        view-point, camera Basis
        resolution
        depth
        l,r,t,b (left right top bottom)
    RGB image[8][8]
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            Ray = Camera(i, j)
            for obj in list of objs in the scene
                int.ptr = obj.intersect(Ray)
                color = shading(int.ptr)
            image[i][j] = color

    1. Create a camera
    2. Create a list of objects in the scene
    3. Create a 2D array of RGB values
    4. For each pixel in the 2D array, create a ray from the camera
    5. For each object in the list of objects, check if the ray intersects with the object
    6. If the ray intersects with the object, calculate the color of the pixel using the shading function
    7. Set the color of the pixel in the 2D array to the calculated color
    8. Display the 2D array as an image

    Possible road map:
    Start with orthographic
    create a camera
    create a single object
    create a 2D array of RGB values
    create a ray from the camera for each pixel in the 2D array
    check if the ray intersects with the object
    if intersects, 1 color, if not black
    display the 2D array as an image*/


    /* TODO:
    - Create light source(s) and put in scene
    - Allow for more than 1 object in the scene
    - create shading functions
    */


    // Create the image (RGB Array) to be displayed
    const int width  = 800; // keep it in powers of 2!
    const int height = 800; // keep it in powers of 2!

    unsigned char image[width*height*3];


    //create cameras
    //OrthographicCamera orthoCam(width, height, vec3(0.0f, -100.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec3(-1.0f, 0.0f, 0.0f));
    PerspectiveCamera perspCam(width, height, vec3(2.0f, -10.0f, 5.0f), vec3(0.0f, 2.0f, -1.0f), vec3(-1.0f, 0.0f, 0.0f), 10.0f);

    Camera *cam = &perspCam;


    //create a scene
    Scene scene = Scene();

    //create a material
    Material material(vec3(255.0f, 19.0f, 1.0f), 0.1f, vec3(255.0f, 10.0f, 1.0f), 0.5f, vec3(255.0f, 10.0f, 1.0f), 5.5f, 100.0f, false, 0);
    Material material2(vec3(20.0f, 255.0f, 255.0f), 0.1f, vec3(20.0f, 255.0f, 255.0f), 0.3f, vec3(20.0f, 255.0f, 255.0f), 10.0f, 100.0f, true, 0.5f);
    Material triangleMaterial(vec3(55.0f, 55.0f, 55.0f), 0.1f, vec3(55.0f, 55.0f, 55.0f), 0.5f, vec3(55.0f, 55.0f, 55.0f), 10000.5f, 1000.0f, true, 1.0f);
    Material planeMaterial(vec3(130.0f, 130.0f, 130.0f), 0.1f, vec3(130.0f, 130.0f, 130.0f), 0.5f, vec3(130.0f, 130.0f, 130.0f), 10000.5f, 1000.0f, true, 0.1f);

    //create an object an an array of objects in the scene not using vector
    //dynamically allocate the sphere and an array to hold it
    Sphere* sphere = new Sphere(1.0, vec3(-3.0f, 0.0f, 0.0f), material);
    Sphere* sphere2 = new Sphere(1.5, vec3(3.0f, -3.0f, 0.5f), material2);
    Plane* plane = new Plane(vec3(0.0f, 0.0f, 1.0f), -1.0f, planeMaterial);

    Triangle* triangle = new Triangle(vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), triangleMaterial);
    Triangle* triangle2 = new Triangle(vec3(0.0f, 0.0f, 0.0f),  vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 2.0f), triangleMaterial);
    Triangle* triangle3 = new Triangle(vec3(0.0f, 0.0f, 0.0f),  vec3(0.0f, 10.0f, 0.0f), vec3(0.0f, 0.0f, 2.0f), triangleMaterial);
    Triangle* triangle4 = new Triangle(vec3(0.0f, 0.0f, 0.0f),  vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), triangleMaterial);

    scene.addSurface(sphere);
    scene.addSurface(sphere2);
    scene.addSurface(plane);
    scene.addSurface(triangle);
    scene.addSurface(triangle2);
    scene.addSurface(triangle3);
    scene.addSurface(triangle4);
    
    Light* directionalLight = new Light(vec3(255.0f, 255.0f, 255.0f), vec3(-50.0f, 50.0f,-50.0f), 0.02f);
    scene.addLight(directionalLight);

    AmbientLight ambientLight = AmbientLight(vec3(255.0f, 255.0f, 255.0f), 0.007f);
    scene.setAmbientLight(ambientLight);

    for(int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            Ray ray = cam->getRay(i, j);
            vec3 color = scene.trace(ray);


            int idx = (i * width + j) * 3;
            image[idx] = (unsigned char) color[0];
            image[idx+1] = (unsigned char) color[1];
            image[idx+2] = (unsigned char) color[2];
        }
    }

    unsigned char *data = &image[0];
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
   


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // bind Texture
        glBindTexture(GL_TEXTURE_2D, texture);

        // render container
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}