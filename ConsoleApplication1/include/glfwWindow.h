#pragma once
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>
void destroyWindow(GLFWwindow* window) {
	std::cout << "Window Terminated" << std::endl;
	glfwTerminate();
}
struct glfw_deleter
{
	void operator()(GLFWwindow* p) const { destroyWindow(p); }

};
class glfwWindow {
	unsigned int major, minor;
	unsigned int width, height;
	std::unique_ptr<GLFWwindow, glfw_deleter> windowPointer;
public:
	glfwWindow(unsigned int major, unsigned int minor) {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	}
	std::unique_ptr<GLFWwindow, glfw_deleter>& creatWindow(unsigned int width, unsigned int height) {
		GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
		if (window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			throw 0;
		}
		glfwMakeContextCurrent(window);
		windowPointer = std::unique_ptr<GLFWwindow, glfw_deleter>(window,glfw_deleter());
		return windowPointer;
	}

	std::unique_ptr<GLFWwindow, glfw_deleter>& get() {
		return windowPointer;
	}

	void setFramebufferCallback(GLFWframebuffersizefun method) {
		glfwSetFramebufferSizeCallback(windowPointer.get(), method);
	}

	void setScrollCallback(GLFWscrollfun method) {
		glfwSetScrollCallback(windowPointer.get(), method);
	}

	bool shouldClose() {
		return glfwWindowShouldClose(windowPointer.get());
	}

	void swapBuffer() {
		glfwSwapBuffers(windowPointer.get());
	}


};

void pollEvent() {
	glfwPollEvents();
}

void terminate() {
	glfwTerminate();
}
