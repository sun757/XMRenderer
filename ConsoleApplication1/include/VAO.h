#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
class VAO {
public:
	unsigned int id;
	VAO() {
		unsigned int vao;
		glGenVertexArrays(1, &vao);
		id = vao;
	}
	void enableVertexArrayPointer(unsigned int index, unsigned int size, GLenum type, GLboolean normalized,GLsizei stride, GLvoid * pointer) {
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, size, type, normalized, stride, pointer);
	}
	void bind() {
		glBindVertexArray(this->id);
	}
	~VAO() {
		glDeleteVertexArrays(1, &(this->id));
	}

};