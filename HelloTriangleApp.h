#ifndef VULKAN_HELLO_TRIANGLE_HELLO_TRIANGLE_APP_H
#define VULKAN_HELLO_TRIANGLE_HELLO_TRIANGLE_APP_H

#include <vector>
#include <optional>
#include <fstream>
#include <glm/glm.hpp>
#include <array>

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

static void framebufferResizeCallback(GLFWwindow *window, int width, int height);

struct Vertex {
  glm::vec2 pos;
  glm::vec3 color;

  static VkVertexInputBindingDescription getBindingDescription() {
    VkVertexInputBindingDescription bindingDescription{};

    bindingDescription.binding = 0;
    bindingDescription.stride = sizeof(Vertex);
    bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

    return bindingDescription;
  }

  static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
    std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};

    attributeDescriptions[0].binding = 0;
    attributeDescriptions[0].location = 0;
    attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
    attributeDescriptions[0].offset = offsetof(Vertex, pos);

    attributeDescriptions[1].binding = 0;
    attributeDescriptions[1].location = 1;
    attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
    attributeDescriptions[1].offset = offsetof(Vertex, color);

    return attributeDescriptions;
  }

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

  /**
   * Проход рендера
   */
  VkRenderPass renderPass;

  /**
   * Здесь задаются значения глобальных переменных, которые используются в шейдерах.
   */
  VkPipelineLayout pipelineLayout;

  /**
   * Графический конвейер
   */
  VkPipeline graphicsPipeline;

  /**
   * Фреймбуферы
   */
  std::vector<VkFramebuffer> swapChainFramebuffers;

  /**
   * Пул команд
   */
  VkCommandPool commandPool;

  /**
   * Список буферов команд
   */
  std::vector<VkCommandBuffer> commandBuffers;

  /**
   * Массив семафоров для каждого кадра.
   * Каждый семафор из этого массива сообщает, что картинка получена из цепочки вывода, и готова к рендеру.
   */
  std::vector<VkSemaphore> imageAvailableSemaphores;

  /**
   * Массив семафоров для каждого кадра.
   * Каждый семафор из этого массива сообщает, что картинку отрендерили и она готова для показу на экране, т.е. возврату обратно в цепочку вывода.
   */
  std::vector<VkSemaphore> renderFinishedSemaphores;

  /**
   * Барьеры для каждого кадра.
   *
   * Каждый барьер из этого массива предназначен для того, чтобы GPU сообщил CPU, что можно начать прорисовывать очередной кадр
   */
  std::vector<VkFence> inFlightFences;

  /**
   * Барьеры (вспомогательные).
   */
  std::vector<VkFence> imagesInFlight;

  /**
   * Индекс кадра
   */
  size_t currentFrame = 0;

  /**
   * Используется для пересоздания буферов картинок в случае изменения размеров главного окна
   */
  bool framebufferResized = false;

  /**
   * Дескриптор буфера для предоставления данных по вершинам
   */
  VkBuffer vertexBuffer;

  /**
   * Дескриптор памяти, выделенной для хранения данных по вершинам
   */
  VkDeviceMemory vertexBufferMemory;

  friend void framebufferResizeCallback(GLFWwindow *window, int width, int height);

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

  /*initVulkan*/VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);

  /*initVulkan*/VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);

  /*initVulkan*/void createSwapChain();

  /*initVulkan*/void createImageViews();

  /*initVulkan*/void createGraphicsPipeline();

  /*initVulkan*/VkShaderModule createShaderModule(const std::vector<char> &code);

  /*initVulkan*/void createRenderPass();

  /*initVulkan*/void createFramebuffers();

  /*initVulkan*/void createCommandPool();

  /*initVulkan*/void createCommandBuffers();

  /*initVulkan*/void createSyncObjects();

  /*initVulkan*/void createVertexBuffer();

  /*initVulkan*/void createBuffer(VkDeviceSize size,
                                  VkBufferUsageFlags usage,
                                  VkMemoryPropertyFlags properties,
                                  VkBuffer &buffer,
                                  VkDeviceMemory &bufferMemory);

  /*initVulkan*/uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

  /*initVulkan*/void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

  void recreateSwapChain();

  void cleanupSwapChain();

  void mainLoop();

  /*mainLoop*/void drawFrame();

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

static std::vector<char> readFile(const std::string &filename);

#endif //VULKAN_HELLO_TRIANGLE_HELLO_TRIANGLE_APP_H
