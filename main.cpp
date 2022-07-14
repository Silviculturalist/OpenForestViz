#include <GLFW/glfw3.h> //Windowing.
//#include <glad/glad.h> //OpenGL API function pointers.
#include <iostream>

//Check for escape input - to close window.
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

//triangle object
float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};  


int main(void)
{


    //Vertex Shader START
    //Compiled at run-time!

    /*
    For now this is stored at top of the code. 
    The vertex shader stored as a constant char string.
    ! A char string is ended by the \0. ! 
    */
    const char *vertexShaderSource = "#version 330 core\n"
    "layout(location=0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
    "}\0";

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL); //attach source to the object
    glCompileShader(vertexShader); //Compile shader at run-time.

    int success; //indicator of compilation success.
    char infoLog[512];  // Eventual error message storage container.
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success); //Get compilation status.

    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //Vertex Shader END

    //Fragment Shader START

    /*
    This sets the final color of the pixel.
    */

   
   const char *fragmentShaderSource  = "#version 330 core\n"
   "out vec4 FragColor\n"
   "void main()\n"
   "{\n"
   "FragColor = vec4(1.0f,  0.5f,   0.2f,   1.0f);\n"
   "}\0";

   unsigned int fragmentShader;
   fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
   glShaderSource(fragmentShader, 1, &fragmentShaderSource,NULL);
   glCompileShader(fragmentShader);

    //Fragment Shader END

    //Shader Program is the final linked version of the shaders.
    // Link shaders and use this when rendering.

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //Set shaderProgram to be used for every shader and rendering call.
    glUseProgram(shaderProgram);

    //Delete superfluous shader objects after linking them together in shaderProgram.
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    //VBO is a Vertex Buffer Object, used to create memory on the GPU.
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //We send the vertices data to the VBO.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices,GL_STATIC_DRAW);


    //VAO - Vertex Array Object here.


    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        //Check if escape has been pressed and close window.
        processInput(window);

        /* Render here */
        glClearColor(0.2f,  0.3f,   0.3f,   1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

