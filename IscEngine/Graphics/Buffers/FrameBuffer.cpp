#include "FrameBuffer.hpp"
#include "../../Utils/Log.hpp"
using namespace IscEngine;

//////////////////////////////////////////////////////////////////////////////////////////////
// Constructor
FrameBuffer::FrameBuffer() {
	
	glGenFramebuffers(1, &this->id);

	/*FrameBuffer::bind(FrameBuffer(*this));

	// Bind Texture

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		Log::cout << "Error framebuffer: " << glCheckFramebufferStatus(GL_FRAMEBUFFER) << std::endl;
	}

	FrameBuffer::unbind();*/

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Destructor
FrameBuffer::~FrameBuffer() {

	glDeleteFramebuffers(1, &this->id);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Binds the FrameBuffer
void FrameBuffer::bind(const FrameBuffer* const frameBuffer) {

	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer->id);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Unbinds the FrameBuffer
void FrameBuffer::unbind() {

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}