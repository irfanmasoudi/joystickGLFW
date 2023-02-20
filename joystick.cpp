#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main(void)
{
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
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        

        int present = glfwJoystickPresent(GLFW_JOYSTICK_1);
//        std::cout << "Joystick 1 connected: "<< present << std::endl;
        
        if (present==1){
            int axesCount;
            int buttonCount;

            const float *axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
            const unsigned char *buttons = glfwGetJoystickButtons( GLFW_JOYSTICK_1, &buttonCount );

            /* Analog Left-Right */

           std::cout << "Number of axes: "<< axesCount << std::endl;
           std::cout << "Left Analog X: " << axes[0] << std::endl;
           std::cout << "Left Analog Y: " << axes[1] << std::endl;
           std::cout << "Right Analog X : " << axes[2] << std::endl;
           std::cout << "Right Analog Y : " << axes[3] << std::endl;
           std::cout << "R2: " << axes[4] << std::endl;
           std::cout << "L2: " << axes[5] << std::endl;

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
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
