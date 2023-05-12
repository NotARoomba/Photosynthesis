#pragma once
#include <iostream>
#include <type_traits>
#include <map>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "../shaders/shader.h"
#include "../photosynthesis.h"

#include <ft2build.h>
#include FT_FREETYPE_H  

class TextRenderer {
    struct Character {
        unsigned int textureID;  // ID handle of the glyph texture
        glm::ivec2   size;       // Size of glyph
        glm::ivec2   bearing;    // Offset from baseline to left/top of glyph
        unsigned int advance;    // Offset to advance to next glyph
    };
    std::map<char, Character> Characters;
    FT_Library ft;
    FT_Face face;
    unsigned int texture;
    unsigned int VAO, VBO;
    int loadFont(char const* path);
    glm::mat4 model;
   public:
        Shader* shader;
        TextRenderer(const char* fontPath, const char* vertPath = "src/shaders/text.vert", const char* fragPath = "src/shaders/text.frag");
        void renderText(std::string text, float x, float y, float scale, glm::vec3 color, Photosynthesis* app);
};
