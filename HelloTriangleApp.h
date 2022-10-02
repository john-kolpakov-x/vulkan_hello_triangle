#ifndef VULKAN_HELLO_TRIANGLE_HELLO_TRIANGLE_APP_H
#define VULKAN_HELLO_TRIANGLE_HELLO_TRIANGLE_APP_H

#include <vector>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

class HelloTriangleApp {
public:
  int run();

private:
  GLFWwindow *window;
  VkInstance instance;
  VkDebugUtilsMessengerEXT debugMessenger;

  void initWindow();

  void initVulkan();

  /*initVulkan*/void createInstance();
  /*initVulkan*/bool checkValidationLayerSupport();
  /*initVulkan*/std::vector<const char*> getRequiredExtensions();

  void mainLoop();

  void cleanup();
};

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData);


#endif //VULKAN_HELLO_TRIANGLE_HELLO_TRIANGLE_APP_H
