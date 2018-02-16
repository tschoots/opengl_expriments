#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>


// glfw: whenever the window size changed (by OS or user resize) this callbackfunction executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
   glViewport(0, 0, width, height);
}


// process all input: query wheterh relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window)
{
   if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, true);
}


int main()
{

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


  // glfw window creation
  GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
  if (window == NULL)
  {
    //std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  // make the context of our window the main context on the current thread
  glfwMakeContextCurrent(window);


  // glad: load all OpenGL funtion pointers
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
     std::cout << "Failed to initialize GLAD" << std::endl;
     return -1;
  }

  glViewport(0, 0, 800, 600);

  // register callback function when window is resized
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // the render loop
  while(!glfwWindowShouldClose(window))
  {
     // input
     processInput(window);

     // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
     glfwSwapBuffers(window);
     glfwPollEvents();
  }
  // glfw: terminate, clearing all previously allocated GLFW resources.
  glfwTerminate();

  std::cout << "This is the end my friend" << std::endl;


  return 0;
}
