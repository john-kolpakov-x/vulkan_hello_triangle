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
  setupDebugMessenger();
  pickPhysicalDevice();
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

  VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
  if (enableValidationLayers) {
    createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
    createInfo.ppEnabledLayerNames = validationLayers.data();

    populateDebugMessengerCreateInfo(debugCreateInfo);
    createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT *) &debugCreateInfo;
  } else {
#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnreachableCode"
    createInfo.enabledLayerCount = 0;
    createInfo.pNext = nullptr;
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
  if (enableValidationLayers) {
    DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
  }

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

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance,
                                      const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
                                      const VkAllocationCallbacks *pAllocator,
                                      VkDebugUtilsMessengerEXT *pDebugMessenger) {
  auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
  if (func != nullptr) {
    return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
  } else {
    return VK_ERROR_EXTENSION_NOT_PRESENT;
  }
}

void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
                                   const VkAllocationCallbacks *pAllocator) {
  auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
  if (func != nullptr) {
    func(instance, debugMessenger, pAllocator);
  }
}


void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo) {
  createInfo = {};
  createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
  createInfo.messageSeverity = 0
                               | VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
                               | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
                               | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
  createInfo.messageType = 0
                           | VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
                           | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
                           | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
  createInfo.pfnUserCallback = debugCallback;
}

void HelloTriangleApp::setupDebugMessenger() {
#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnreachableCode"
  if (!enableValidationLayers) return;
#pragma clang diagnostic pop

  VkDebugUtilsMessengerCreateInfoEXT createInfo;
  populateDebugMessengerCreateInfo(createInfo);
  createInfo.pUserData = this; // Optional

  VkResult result = CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger);
  if (result != VK_SUCCESS) {
    throw runtime_error("eID5O7K0ig :: failed to set up debug messenger!");
  }
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
    /**
     * В нашем случае это HelloTriangleApp*
     */
    void *pUserData) {

  /*

   Значения для перечисления выбраны таким образом, что вы можете использовать операцию сравнения, чтобы отсеять
   сообщения выше или ниже какого-то порога, например:

   if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
      // Message is important enough to show
   }

   */

  // TODO validation message
  //std::cerr << "xWDy1vJH8c :: validation layer: " << pCallbackData->pMessage << std::endl;

  /*
   Callback-функция возвращает VkBool32 тип. Результат указывает, нужно ли прервать вызов,
   создавший сообщение. Если callback-функция возвращает VK_TRUE, вызов прерывается и возвращается
   код ошибки VK_ERROR_VALIDATION_FAILED_EXT. Как правило, это происходит только при тестировании самих
   слоев валидации, в нашем же случае нужно вернуть VK_FALSE
   */
  return VK_FALSE;
}

void HelloTriangleApp::pickPhysicalDevice() {
  uint32_t deviceCount = 0;
  vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
  if (deviceCount == 0) {
    throw runtime_error("failed to find GPUs with Vulkan support!");
  }

  std::vector<VkPhysicalDevice> devices(deviceCount);
  vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

  cout << "0ab57f33NP :: Physical devices:" << endl;
  for (const auto &device: devices) {
    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);
    cout << "    qCnwQb5NcF :: device id = " << deviceProperties.deviceID;
    cout << ", device name = " << deviceProperties.deviceName << endl;
  }

  for (const auto &device: devices) {
    if (isDeviceSuitable(device)) {
      physicalDevice = device;
      break;
    }
  }

  if (physicalDevice == VK_NULL_HANDLE) {
    throw runtime_error("failed to find a suitable GPU!");
  }

  {
    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);
    cout << "8VRpTvWXY6 :: Selected physical device: " << deviceProperties.deviceName << endl;
  }

}

bool HelloTriangleApp::isDeviceSuitable(VkPhysicalDevice device) {

  VkPhysicalDeviceProperties deviceProperties;
  vkGetPhysicalDeviceProperties(device, &deviceProperties);

  VkPhysicalDeviceFeatures deviceFeatures;
  vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

  return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
         deviceFeatures.geometryShader;
}

#pragma clang diagnostic pop // for #pragma ide diagnostic ignored "OCUnusedMacroInspection"
