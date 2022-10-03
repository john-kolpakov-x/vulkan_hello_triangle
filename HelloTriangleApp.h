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
  VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

  void initWindow();

  void initVulkan();

  /*initVulkan*/void createInstance();

  /*initVulkan*/bool checkValidationLayerSupport();

  /*initVulkan*/std::vector<const char *> getRequiredExtensions();

  /*initVulkan*/void setupDebugMessenger();

  /*initVulkan*/void pickPhysicalDevice();

  /*initVulkan*/bool isDeviceSuitable(VkPhysicalDevice device);

  void mainLoop();

  void cleanup();
};

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
    void *pUserData);

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance,
                                      const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
                                      const VkAllocationCallbacks *pAllocator,
                                      VkDebugUtilsMessengerEXT *pDebugMessenger);

void DestroyDebugUtilsMessengerEXT(VkInstance instance,
                                   VkDebugUtilsMessengerEXT debugMessenger,
                                   const VkAllocationCallbacks *pAllocator);

void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

#endif //VULKAN_HELLO_TRIANGLE_HELLO_TRIANGLE_APP_H
