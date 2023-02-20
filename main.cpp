#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";


int main(void)
{

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
    }; 

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // glBindVertexArray(0); // no need to unbind it every time 
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();

        std::cout << "Here" << std::endl;

        int present = glfwJoystickPresent(GLFW_JOYSTICK_1);
//        std::cout << "Joystick 1 connected: "<< present << std::endl;
        
        if (present==1){
            int axesCount;
            int buttonCount;

            const float *axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
            const unsigned char *buttons = glfwGetJoystickButtons( GLFW_JOYSTICK_1, &buttonCount );

            /* Analog Left-Right */

        //    std::cout << "Number of axes: "<< axesCount << std::endl;
        //    std::cout << "Left Analog X: " << axes[0] << std::endl;
        //    std::cout << "Left Analog Y: " << axes[1] << std::endl;
        //    std::cout << "Right Analog X : " << axes[2] << std::endl;
        //    std::cout << "Right Analog Y : " << axes[3] << std::endl;
        //    std::cout << "R2: " << axes[4] << std::endl;
        //    std::cout << "L2: " << axes[5] << std::endl;

            /* Button */

//            if ( GLFW_PRESS == buttons[0] )
//            {
//                std::cout << "A Pressed" << std::endl;
//            }
//            else if ( GLFW_RELEASE == buttons[0] )
//            {
//                std::cout << "A Released" << std::endl;
//            }
//            if ( GLFW_PRESS == buttons[1] )
//            {
//                std::cout << "B Pressed" << std::endl;
//            }
//            else if ( GLFW_RELEASE == buttons[1] )
//            {
//                std::cout << "B Released" << std::endl;
//            }
//            if ( GLFW_PRESS == buttons[3] )
//            {
//                std::cout << "X Pressed" << std::endl;
//            }
//            else if ( GLFW_RELEASE == buttons[3] )
//            {
//                std::cout << "X Released" << std::endl;
//            }
//            if ( GLFW_PRESS == buttons[4] )
//            {
//                std::cout << "Y Pressed" << std::endl;
//            }
//            else if ( GLFW_RELEASE == buttons[4] )
//            {
//                std::cout << "Y Released" << std::endl;
//            }
            
//            if ( GLFW_PRESS == buttons[6] )
//            {
//                std::cout << "L1 Pressed" << std::endl;
//            }
//            else if ( GLFW_RELEASE == buttons[6] )
//            {
//                std::cout << "L1 Released" << std::endl;
//            }
//            if ( GLFW_PRESS == buttons[7] )
//            {
//                std::cout << "R1 Pressed" << std::endl;
//            }
//            else if ( GLFW_RELEASE == buttons[7] )
//            {
//                std::cout << "R1 Released" << std::endl;
//            }
//
//            if ( GLFW_PRESS == buttons[10] )
//            {
//                std::cout << "Select Pressed" << std::endl;
//            }
//            else if ( GLFW_RELEASE == buttons[10] )
//            {
//                std::cout << "Select Released" << std::endl;
//            }
//            if ( GLFW_PRESS == buttons[11] )
//            {
//                std::cout << "Start Pressed" << std::endl;
//            }
//            else if ( GLFW_RELEASE == buttons[11] )
//            {
//                std::cout << "Start Released" << std::endl;
//            }
//
//            if ( GLFW_PRESS == buttons[15] )
//            {
//                std::cout << "Between Start and Select Pressed" << std::endl;
//            }
//            else if ( GLFW_RELEASE == buttons[15] )
//            {
//                std::cout << "Between Start and Select Released" << std::endl;
//            }


            /*Arrows*/
            
            if ( GLFW_PRESS == buttons[16] )
            {
                std::cout << "Arrow Up Pressed" << std::endl;
            }
            else if ( GLFW_RELEASE == buttons[16] )
            {
                std::cout << "Arrow Up Released" << std::endl;
            }
            
            if ( GLFW_PRESS == buttons[17] )
            {
                std::cout << "Arrow Right Pressed" << std::endl;
            }
            else if ( GLFW_RELEASE == buttons[17] )
            {
                std::cout << "Arrow Right Released" << std::endl;
            }
            
            if ( GLFW_PRESS == buttons[18] )
            {
                std::cout << "Arrow Down Pressed" << std::endl;
            }
            else if ( GLFW_RELEASE == buttons[18] )
            {
                std::cout << "Arrow Down Released" << std::endl;
            }
            
            if ( GLFW_PRESS == buttons[19] )
            {
                std::cout << "Arrow Left Pressed" << std::endl;
            }
            else if ( GLFW_RELEASE == buttons[19] )
            {
                std::cout << "Arrow Left Released" << std::endl;
            }
            
        }
        
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;

}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
