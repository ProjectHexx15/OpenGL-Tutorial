#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>


// Callback function to adjust the viewport when the window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// Function to process input from the user
void processInput(GLFWwindow* window);

// Function to load shader source code from a file
std::string loadShaderSrc(const char* filename);

int main() 
{
	int success;
	char infolog[512];

	// Initialize GLFW
	glfwInit();

	// Tells GLFW what version of OpenGL we are using (3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Tells GLFW we are using the core profile, only modern functions are available
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// This is needed to ensure that the code works on MacOS
# ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
# endif

	// Create a window
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Tutorial", NULL, NULL);

	// Check if the window was created successfully, if not, print an error message and terminate GLFW
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// set the current context to the window we just created
	glfwMakeContextCurrent(window);

	// Load GLAD so it configures OpenGL, if it fails, print an error message and terminate GLFW
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Specify the viewport of OpenGL in the window
	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// shaders

	// compile vertex shader

	unsigned int vertexShader;
	// create a vertex shader object
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// load the vertex shader source code from a file
	std::string vertShaderSrc = loadShaderSrc("Assets/vertexShader.glsl");
	// convert the vertex shader source code to a C-style string
	const GLchar* vertShader = vertShaderSrc.c_str();
	// attach the vertex shader source code to the vertex shader object
	glShaderSource(vertexShader, 1, &vertShader, NULL);
	glCompileShader(vertexShader);

	// check for vertex shader compile errors
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
		std::cout << "Error compiling vertex shader: " << infolog << std::endl;
	}

	// compile fragment shader

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); 
	// create a fragment shader object
	std::string fragShaderSrc = loadShaderSrc("Assets / fragmentShader.glsl"); 
	// load the fragment shader source code from a file
	const GLchar* fragShader = fragShaderSrc.c_str(); 
	// convert the fragment shader source code to a C-style string
	glShaderSource(fragmentShader, 1, &fragShader, NULL);
	// attach the fragment shader source code to the fragment shader object
	glCompileShader(fragmentShader);

	// check for fragment shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infolog);
		std::cout << "Error compiling fragment shader: " << infolog << std::endl;
	}

	// link shaders to create a shader program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	// attach the vertex and fragment shaders to the shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
		std::cout << "Error linking shader program: " << infolog << std::endl;
	}

	// delete the shader objects once we've linked them into the program, as we no longer need them
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Main render loop
	while (!glfwWindowShouldClose(window))
	{
		// Input
		processInput(window);

		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// send new frame to the screen
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	// Check if the escape key is pressed, if so, set the window to close
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

std::string loadShaderSrc(const char* filename)
{
	std::ifstream file; //this is the file stream that will be used to read the shader source code from a file
	std::stringstream buf; //this is the string stream that will be used to store the shader source code in a string

	std::string ret = ""; // return string that will be used to store the shader source code

	file.open(filename); //open the file

	if (file.is_open())
	{
		buf << file.rdbuf(); //read the file into the string stream
		ret = buf.str(); //convert the string stream into a string
	}
	else
	{
		std::cout << "Could not open file: " << filename << std::endl;
	}

	file.close(); // close the file so it doesnt leak memory

	return ret; // return the shader source code

}

