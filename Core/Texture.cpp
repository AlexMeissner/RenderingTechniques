#include "Texture.h"
#include "print.h"

texture::texture(const fs::path& file_path)
{
    int width = 0, height = 0, channel_count = 0;
    const auto image_data = SOIL_load_image(file_path.u8string().c_str(), &width, &height, &channel_count, 0);

    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    GLuint data_format = 0;

    if (channel_count == 3)
    {
        data_format = GL_RGB;
    }
    else if (channel_count == 4)
    {
        data_format = GL_RGBA;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, data_format, width, height, 0, data_format, GL_UNSIGNED_BYTE, image_data);
    glBindTexture(GL_TEXTURE_2D, 0);

    SOIL_free_image_data(image_data);
}

texture::~texture()
{
    glDeleteTextures(1, &texture_id);
}

void texture::bind(const GLenum texture_unit) const
{
    glActiveTexture(texture_unit);
    glBindTexture(type, texture_id);
}

void texture::release(const GLenum texture_unit) const
{
    glActiveTexture(texture_unit);
    glBindTexture(GL_TEXTURE_2D, 0);
}