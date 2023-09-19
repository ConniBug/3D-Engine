//
// Created by Conni Bilham on 10/07/2023.
//

#include <thread>
#include "Storage.h"
#include "../include/Window.h"

Window::Window(int width, int height, std::string title, int fullscreen, Camera* camera) : width(width), height(height), title(title) {
    this->loaded_scene = storage->scene_list.at(storage->loaded_scene_number);
    this->camera = camera;

    GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);
    if (window == nullptr) {
        logging::error("Failed to create GLFW window");
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        logging::error("Failed to initialize GLAD");
        return;
    }

    logging::debug("OpenGL Version: " + std::string((char*)glGetString(GL_VERSION)));
    logging::debug("OpenGL Vendor: " + std::string((char*)glGetString(GL_VENDOR)));
    logging::debug("OpenGL Renderer: " + std::string((char*)glGetString(GL_RENDERER)));
    logging::debug("OpenGL Shading Language Version: " + std::string((char*)glGetString(GL_SHADING_LANGUAGE_VERSION)));

    glfwSetKeyCallback(window, key_callback);
    glfwSetCharCallback(window, character_callback);

    glfwGetFramebufferSize(window, &width, &height);
    glfwSetFramebufferSizeCallback(window, window_size_callback);
    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, window_size_callback);

    glfwSetWindowUserPointer(window, this);
    auto mouse_callback = [](GLFWwindow* window, double xposIn, double yposIn) {
        static_cast<class Window*>(glfwGetWindowUserPointer(window))->mouse_callback(window, xposIn, yposIn);
    };
    glfwSetCursorPosCallback(window, mouse_callback);
    auto scroll_callback = [](GLFWwindow* window, double xoffset, double yoffset) {
        static_cast<class Window*>(glfwGetWindowUserPointer(window))->scroll_callback(window, xoffset, yoffset);
    };
    glfwSetScrollCallback(window, scroll_callback);


    logging::info("Window created");

    loaded_scene->init(this->camera);

    while(!glfwWindowShouldClose(window)) {
        // ((void (*)(GLFWwindow*)) window_loop_callback)(window);
        window_loop_callback(window);
    }

}

Window::~Window() {
    logging::info("Destroying window");
    for (auto* scene : storage->scene_list) {
        delete scene;
    }

    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void Window::set_camera(Camera* camera_n) {
    this->camera = camera_n;
}

void Window::window_size_callback(GLFWwindow* window, int width, int height) {
    logging::info("Window size changed: " + std::to_string(width) + "x" + std::to_string(height));

    glViewport(0, 0, width, height);
}

static bool vsync = true;

float fps_history[100];
static bool full = false;
static int fps_history_index = 0;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;
float averageFPS = 0.0f;
float averageFrameTime = 0.0f;
void Window::window_loop_callback(GLFWwindow *window) {
    auto currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    averageFrameTime = averageFrameTime == 0.0f ? deltaTime : (averageFrameTime + deltaTime) / 2.0f;
//    std::cout << "FPS: " << averageFPS << std::endl;
//    std::cout << "Frame time: " << averageFrameTime << std::endl;

    glClearColor(0.2f, 0.0f, 0.2f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    if (glfwRawMouseMotionSupported()) {
        logging::info("Raw mouse motion supported");
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    }
    handle_input(window);



//    static auto triangle = new Entity_t();
//    shaders[0]->apply();
//
//    // create transformations
//    glm::mat4 view          = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
//    glm::mat4 projection    = glm::mat4(1.0f);
//    projection = glm::perspective(glm::radians(camera->fov), (float)800 / (float)600, 0.1f, 100.0f);
//    view = camera->view_matrix();
//
//    const float radius = 10.0f;
//    float camX = sin(glfwGetTime()) * radius;
//    float camZ = cos(glfwGetTime()) * radius;
//    view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
//
//    if(main_rotation.x != 0 || main_rotation.y != 0 || main_rotation.z != 0) {
//        auto normalized = glm::normalize(main_rotation);
//        view = glm::rotate(view, glm::radians(glm::length(main_rotation)), normalized);
//    }

//    // pass transformation matrices to the shader
//    glUniformMatrix4fv(glGetUniformLocation(shaders[0]->id, "view"), 1, GL_FALSE, &view[0][0]);
//    glUniformMatrix4fv(glGetUniformLocation(shaders[0]->id, "projection"), 1, GL_FALSE, &projection[0][0]);

    static int frameCount = 0;
    frameCount++;


    loaded_scene->update(deltaTime);

    /* Draws a square */
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(-0.5f, 0.5f);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glEnd();

    glfwSwapBuffers(window);

    if (!full && fps_history_index + 1 == 100) {
        full = true;
        logging::info("FPS history full");
    }
    fps_history[fps_history_index] = 1.0f / deltaTime;
    fps_history_index = (fps_history_index + 1) % 100;

    const float fps = 30.0f;
    auto currentFrameDuation = glfwGetTime() - currentFrame;
    if (vsync) {
        glfwSwapInterval(1);
        if (currentFrameDuation < 1.0 / fps) {
            std::this_thread::sleep_for(std::chrono::milliseconds((int)((1.0 / fps - currentFrameDuation) * 1000)));
        }
        auto newFrameDuration = glfwGetTime() - currentFrame;

        // If lagging
        if (newFrameDuration > 1.0) {
            logging::error("Lagging behind: " + std::to_string(1/newFrameDuration));
        }
    } else
        glfwSwapInterval(0);

    glfwPollEvents();

    glUseProgram(0);
}

#include "../Scenes/main_scene.h"
void Window::handle_input(GLFWwindow *window) {
    static bool wireframe = false;
    static double last_click = 0;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    static bool sprinting = false;

    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        sprinting = true;
    else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
        sprinting = false;

    static bool ready = false;
    static bool toggle = false;
    if(glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS && ready) {
        logging::info("Toggle cursor");

        if(!toggle)
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        else
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        toggle = !toggle;
        ready = false;
    }
    else if(glfwGetKey(window, GLFW_KEY_C) == GLFW_RELEASE) {
        ready = true;
    }

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->HandleKeyboard(Camera::CameraMovement::FORWARD, deltaTime, sprinting);
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->HandleKeyboard(Camera::CameraMovement::BACKWARD, deltaTime);

    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->HandleKeyboard(Camera::CameraMovement::LEFT, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->HandleKeyboard(Camera::CameraMovement::RIGHT, deltaTime);


    // Everything below will only execute every x amount of time when the key is held
    double current_time = glfwGetTime();
    if(current_time - last_click < 0.2)
        return;

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        logging::info("Reloading scene");

        storage->loaded_scene_number = storage->loaded_scene_number == 0 ? 1 : 0;
        this->loaded_scene = storage->scene_list.at(storage->loaded_scene_number);
        storage->loaded_scene = this->loaded_scene;

        this->loaded_scene->init(this->camera);
        last_click = current_time;
    }

    // VSync toggle
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
        logging::info("VSync: " + std::to_string(vsync));

        vsync = !vsync;
        last_click = current_time;
    }

    if(glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
        logging::info("Wireframe: " + std::to_string(wireframe));

        if (wireframe)
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        wireframe = !wireframe;
        last_click = current_time;
    }

    // -/+ for FOV
//    std::cout << "FOV: " << camera->fov << std::endl;
    if(glfwGetKey(window,  GLFW_KEY_EQUAL) == GLFW_PRESS) {
        camera->HandleMouseScroll(10);
        last_click = current_time;
    }
    if(glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS) {
        camera->HandleMouseScroll(-10);
        last_click = current_time;
    }
}

void Window::mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    static float lastX = 800.0f / 2.0;
    static float lastY = 600.0 / 2.0;

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    static bool firstMouse = true;
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera->HandleMouseMovement(xoffset, yoffset);
}

void Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera->HandleMouseScroll(yoffset);
}
