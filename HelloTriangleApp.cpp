#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

#include <cstdlib>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <cstring>
#include "HelloTriangleApp.h"

using namespace std;

const vector<const char *> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

int HelloTriangleApp::run() {
  initWindow();
  initVulkan();
  mainLoop();
  cleanup();
  return EXIT_SUCCESS;
}

void HelloTriangleApp::initWindow() {
  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
}

void HelloTriangleApp::initVulkan() {
  createInstance();
}

void HelloTriangleApp::createInstance() {
  if (enableValidationLayers) {
    std::cout << "yc1vAg406n :: enableValidationLayers == TRUE" << std::endl;
    if (!checkValidationLayerSupport()) {
      throw std::runtime_error("io6oYbVw6k :: validation layers requested, but not available!");
    }
  } else {
#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnreachableCode"
    std::cout << "yc1vAg406n :: enableValidationLayers == FALSE" << std::endl;
#pragma clang diagnostic pop
  }

  VkApplicationInfo appInfo{};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pApplicationName = "Hello Triangle";
  appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.pEngineName = "No Engine";
  appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.apiVersion = VK_API_VERSION_1_0;

  VkInstanceCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  createInfo.pApplicationInfo = &appInfo;
  createInfo.enabledLayerCount = 0;

  uint32_t glfwExtensionCount = 0;
  const char **glfwExtensions;

  glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

  createInfo.enabledExtensionCount = glfwExtensionCount;
  createInfo.ppEnabledExtensionNames = glfwExtensions;

  {
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> extensions(extensionCount);

    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

    std::cout << "available extensions:\n";

    for (const auto &extension: extensions) {
      std::cout << "  " << extension.extensionName << '\n';
    }
  }

  if (enableValidationLayers) {
    createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
    createInfo.ppEnabledLayerNames = validationLayers.data();
  } else {
#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnreachableCode"
    createInfo.enabledLayerCount = 0;
#pragma clang diagnostic pop
  }

  vector<const char *> extensions = getRequiredExtensions();
  createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
  createInfo.ppEnabledExtensionNames = extensions.data();

  VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
  if (result != VK_SUCCESS) {
    throw std::runtime_error("LsL60VI8oa :: failed to create instance!");
  }
}

void HelloTriangleApp::mainLoop() {
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
  }
}

void HelloTriangleApp::cleanup() {
  vkDestroyInstance(instance, nullptr);

  glfwDestroyWindow(window);

  glfwTerminate();
}

bool HelloTriangleApp::checkValidationLayerSupport() { // NOLINT(readability-convert-member-functions-to-static)
  uint32_t layerCount;
  vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

  std::vector<VkLayerProperties> availableLayers(layerCount);
  vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

  for (const char *layerName: validationLayers) {
    bool layerFound = false;

    for (const auto &layerProperties: availableLayers) {
      if (strcmp(layerName, layerProperties.layerName) == 0) {
        layerFound = true;
        break;
      }
    }

    if (!layerFound) {
      return false;
    }
  }

  return true;
}

std::vector<const char *> HelloTriangleApp::getRequiredExtensions() {

  uint32_t glfwExtensionCount = 0;
  const char **glfwExtensions;
  glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

  std::vector<const char *> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

  if (enableValidationLayers) {
    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
  }

  cout << "M36ypHTGAn :: extensions.size() = " << extensions.size() << endl;
  for (int i = 0; i < extensions.size(); i++) {
    cout << "  lNUX8198V5 :: extensions[" << i << "] = " << extensions[i] << endl;
  }

  return extensions;
}

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    /**
     * VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT: диагностическое сообщение
     * VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT: информационное сообщение, например, о создании ресурса
     * VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT: сообщение о поведении, которое не обязательно является некорректным, но вероятнее всего указывает на ошибку
     * VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT: сообщение о некорректном поведении, которое может привести к сбою
     */
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    /**
     * VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT: произошедшее событие не связано со спецификацией или производительностью
     * VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT: произошедшее событие нарушает спецификацию или указывает на возможную ошибку
     * VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT: возможно неоптимальное использование Vulkan
     */
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    /**
     * Наиболее важные члены структуры VkDebugUtilsMessengerCallbackDataEXT
     * pMessage: отладочное сообщение в виде строки с завершающим нулем
     * pObjects: массив дескрипторов объектов, относящихся к сообщению
     * objectCount: количество объектов в массиве
     */
    const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
    void *pUserData) {

  /*

   Значения для перечисления выбраны таким образом, что вы можете использовать операцию сравнения, чтобы отсеять
   сообщения выше или ниже какого-то порога, например:

   if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
      // Message is important enough to show
   }

   */

  std::cerr << "xWDy1vJH8c :: validation layer: " << pCallbackData->pMessage << std::endl;

  /*
   Callback-функция возвращает VkBool32 тип. Результат указывает, нужно ли прервать вызов,
   создавший сообщение. Если callback-функция возвращает VK_TRUE, вызов прерывается и возвращается
   код ошибки VK_ERROR_VALIDATION_FAILED_EXT. Как правило, это происходит только при тестировании самих
   слоев валидации, в нашем же случае нужно вернуть VK_FALSE
   */
  return VK_FALSE;
}

#pragma clang diagnostic pop // for #pragma ide diagnostic ignored "OCUnusedMacroInspection"
