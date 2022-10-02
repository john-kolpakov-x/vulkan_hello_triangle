#ifndef VULKAN_HELLO_TRIANGLE_HELLO_TRIANGLE_APP_H
#define VULKAN_HELLO_TRIANGLE_HELLO_TRIANGLE_APP_H


class HelloTriangleApp {
public:
  int run();
private:
  void initVulkan();
  void mainLoop();
  void cleanup();
};


#endif //VULKAN_HELLO_TRIANGLE_HELLO_TRIANGLE_APP_H
