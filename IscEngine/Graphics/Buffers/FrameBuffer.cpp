#include "FrameBuffer.hpp"
#include "../../Utils/Log.hpp"
using namespace IscEngine;

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

//////////////////////////////////////////////////////////////////////////////////////////////
// Constructor
FrameBuffer::FrameBuffer(const unsigned int width, const unsigned int height, const bool color, const bool depth) {

	glGenFramebuffers(1, &this->id);

	FrameBuffer::bind(this);

	this->texture = new Texture();
	this->texture->create(width, height, color, depth);

	// Depth Buffer
	unsigned int depthrenderbuffer;
	glGenRenderbuffers(1, &depthrenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

	// Alternative : Depth texture. Slower.
	/*GLuint depthTexture;
	glGenTextures(1, &depthTexture);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT24, 1024, 768, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);*/

	if (color) {

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->texture->getId(), 0);
		unsigned int DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
		glDrawBuffers(1, DrawBuffers);

	} else if (depth) {

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, this->texture->getId(), 0);
		glDrawBuffer(GL_NONE);

	}

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		Log::cout << "Error framebuffer: " << glCheckFramebufferStatus(GL_FRAMEBUFFER) << std::endl;
	}

	FrameBuffer::unbind();

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Destructor
FrameBuffer::~FrameBuffer() {

	glDeleteFramebuffers(1, &this->id);

}