#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

// Window dimensions
const GLuint WIDTH = 800 , HEIGHT = 600;

const GLchar *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const GLchar* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

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
  GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
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

  glViewport(0, 0, WIDTH, HEIGHT);

  // register callback function when window is resized
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // build and compile our shader program
  // vertex shader
  GLint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  // check if compilation was succesfull
  GLint succes;
  GLchar infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &succes);
  if (!succes)
  {
     glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
     std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  // fragment shader
  GLint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader,1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  // check compile time errors
  if (!succes)
  {
     glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
     std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
  // link shaders
  GLint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  // check for linking errors
  if (!succes)
  {
     glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
     std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);




  // Set up vertex data (and buffer(s) and configure vertex attributes
  float vertices[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
       -0.5f, -0.5f, 0.0f,  // bollom left
       -0.5f,  0.5f, 0.0f   // top left
  };
  GLuint indices[] = {
        0, 1, 3,    // first triangle
        1, 2, 3     // second triangle
  };

  // get VBO buffer (vertex buffer objects on GPU)
  GLuint VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
  glBindVertexArray(VAO);

  // give the VBO buffer a type , can have several buffers on the GPU as long as they have different types
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // Note that this is allowed, the cal lto glVertexAttribPointer registrered VBO as the current bound vertex buffer object so afterwards we can safely unbind.
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  // Unbind the VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound t this VAO
  // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary
  glBindVertexArray(0);

  // Uncommenting this call will result in wireframe polygons.
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  // the render loop
  while(!glfwWindowShouldClose(window))
  {
     // check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
     glfwPollEvents();

     // input
     processInput(window);

     glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
     glClear(GL_COLOR_BUFFER_BIT);

     // Draw our first triangle
     glUseProgram(shaderProgram);
     glBindVertexArray(VAO);
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
     glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
     glBindVertexArray(0);

     // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
     glfwSwapBuffers(window);

  }

  // optional: de-allocate all resources one they've outlived their purpose
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);

  // glfw: terminate, clearing all previously allocated GLFW resources.
  glfwTerminate();

  std::cout << "This is the end my friend" << std::endl;


  return 0;
}
