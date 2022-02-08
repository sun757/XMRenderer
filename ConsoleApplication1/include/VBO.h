#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
class VBO {
public:
	unsigned int id;
	VBO() {
		unsigned int vbo;
		glGenBuffers(1, &vbo);
		id = vbo;
	}
	void bufferData(unsigned int size,void * data, unsigned int usage ) {
		glBufferData(GL_ARRAY_BUFFER, size, data, usage);
	}
	void bind() {
		glBindBuffer(GL_ARRAY_BUFFER, this->id);
	}
	~VBO() {
		glDeleteBuffers(1, &(this->id));
	}
};