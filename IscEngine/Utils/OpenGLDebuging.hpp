#pragma once

#include <gl/glew.h>
#include <SFML/OpenGL.hpp>

#include "Log.hpp"
using namespace IscEngine;

void CheckOpenGLError(const char* stmt, const char* fname, int line) {

	GLenum err = glGetError();
	if (err != GL_NO_ERROR) {
		Log::cout << "OpenGL error " << err << ", at " << fname << ":" << line << " - for " << stmt << endl;
		abort();
	}

}

#ifdef _DEBUG
#define GL_CHECK(stmt) do { \
            stmt; \
            CheckOpenGLError(#stmt, __FILE__, __LINE__); \
        } while (0)
#else
#define GL_CHECK(stmt) stmt
#endif