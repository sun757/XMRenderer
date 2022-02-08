#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "texture.h"
#include <memory>
class Framebuffer {
public:
	int width, height;
	int id;
	Framebuffer(int width, int height){
		unsigned int framebuffer;
		glGenFramebuffers(1, &framebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		this->width = width;
		this->height = height;
		this->id = framebuffer;
	}
	std::unique_ptr<Texture2D> attachColorTexture() {
		std::unique_ptr<Texture2D> texture = make_unique<Texture2D>(this->width, this->height);
		unsigned int id = texture->getID();
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, id, 0);
		return texture;
	}
	unsigned int attachRenderBuffer() {
		unsigned int rbo;
		glGenRenderbuffers(1, &rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, this->width, this->height); // use a single renderbuffer object for both a depth AND stencil buffer.
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
		return rbo;
	}
	void bind() {
		glBindFramebuffer(GL_FRAMEBUFFER, id);
	}
	void unbind() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	void checkstatus() {
		// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
	}
};