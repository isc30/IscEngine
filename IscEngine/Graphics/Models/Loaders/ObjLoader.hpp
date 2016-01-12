#pragma once

#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
using namespace std;

#include <glm/glm.hpp>
using namespace glm;

bool loadObj(
	string path,
	std::vector<unsigned short> & indices,
	std::vector<glm::vec3> & vertices,
	std::vector<glm::vec2> & uvs,
	std::vector<glm::vec3> & normals
);