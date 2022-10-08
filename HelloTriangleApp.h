#ifndef VULKAN_HELLO_TRIANGLE_HELLO_TRIANGLE_APP_H
#define VULKAN_HELLO_TRIANGLE_HELLO_TRIANGLE_APP_H

#include <vector>
#include <optional>
#include <fstream>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

struct QueueFamilyIndices {
  std::optional<uint32_t> graphicsFamily;
  std::optional<uint32_t> presentFamily;

  [[nodiscard]] bool isComplete() const {
    return graphicsFamily.has_value() && presentFamily.has_value();
  }
};

struct SwapChainSupportDetails {
  VkSurfaceCapabilitiesKHR capabilities;
  std::vector<VkSurfaceFormatKHR> formats;
  std::vector<VkPresentModeKHR> presentModes;
};

class HelloTriangleApp {
public:
  int run();

private:

  /**
   * Дескриптор окна на экране
   */
  GLFWwindow *window;

  /**
   * Инстанция вулкана
   */
  VkInstance instance;

  /**
   * Дескриптор компонента, который отображает отладочные сообщения
   */
  VkDebugUtilsMessengerEXT debugMessenger;

  /**
   * Поверхность прорисовки. Куда будет рисоваться графика. Её окно отображает на экране.
   */
  VkSurfaceKHR surface;

  /**
   * Физическое устройство
   */
  VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

  /**
   * Логическое устройство
   */
  VkDevice device;

  /**
   * Очередь графических команд
   */
  VkQueue graphicsQueue;

  /**
   * Очередь отображения
   */
  VkQueue presentQueue;

  /**
   * Цепочка обновления. Она занимается поставкой прорисованных пикселей на экран окна.
   *
   * При изменении размера окна этот swap chain нужно пересоздать с другим расширением.
   */
  VkSwapchainKHR swapChain;

  /**
   * Хранение дескрипторов изображений, которые будут показываться на форме, как результат рендеринга
   */
  std::vector<VkImage> swapChainImages;

  /**
   * Формат картинок, работающих в цепочке обновления.
   */
  VkFormat swapChainImageFormat;

  /**
   * Разрешение картинок, работающих в цепочке обновления.
   */
  VkExtent2D swapChainExtent;

  /**
   * Размещение вьюшек картинок, которые позволят использовать картинки внутри Vulkan
   */
  std::vector<VkImageView> swapChainImageViews;

  void initWindow();

  void initVulkan();

  /*initVulkan*/void createInstance();

  /*initVulkan*/bool checkValidationLayerSupport();

  /*initVulkan*/std::vector<const char *> getRequiredExtensions();

  /*initVulkan*/void setupDebugMessenger();

  /*initVulkan*/void createSurface();

  /*initVulkan*/void pickPhysicalDevice();

  /*initVulkan*/bool isDeviceSuitable(VkPhysicalDevice aDevice);

  /*initVulkan*/bool checkDeviceExtensionSupport(VkPhysicalDevice aDevice);

  /*initVulkan*/QueueFamilyIndices findQueueFamilies(VkPhysicalDevice dev);

  /*initVulkan*/void createLogicalDevice();

  /*initVulkan*/SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice aDevice);

  /*initVulkan*/VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);

  /*initVulkan*/VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);

  /*initVulkan*/VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

  /*initVulkan*/void createSwapChain();

  /*initVulkan*/void createImageViews();

  /*initVulkan*/void createGraphicsPipeline();

  /*initVulkan*/VkShaderModule createShaderModule(const std::vector<char>& code);

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

void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);

static std::vector<char> readFile(const std::string& filename);

#endif //VULKAN_HELLO_TRIANGLE_HELLO_TRIANGLE_APP_H
