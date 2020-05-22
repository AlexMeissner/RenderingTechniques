#pragma once

#include <Windows.h>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <chrono>
#include <unordered_map>

#define GLEW_STATIC
#include <GL/glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtx/rotate_vector.hpp>

namespace fs = std::filesystem;