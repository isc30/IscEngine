#include "FrameBuffer.hpp"
#include "../../Utils/Log.hpp"
using namespace IscEngine;

FrameBuffer::FrameBuffer() {
	
	glGenFramebuffers(1, &this->id);

	/*FrameBuffer::bind(FrameBuffer(*this));

	// Bind Texture

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		Log::cout << "Error framebuffer: " << glCheckFramebufferStatus(GL_FRAMEBUFFER) << std::endl;
	}

	FrameBuffer::unbind();*/

}

FrameBuffer::~FrameBuffer() {

	glDeleteFramebuffers(1, &this->id);

}

void FrameBuffer::bind(const FrameBuffer& frameBuffer) {

	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer.id);

}

void FrameBuffer::unbind() {

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}