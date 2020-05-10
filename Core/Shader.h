#pragma once

#include "CommonHeaders.h"

struct file_watch
{
    GLuint id = 0;
    fs::path file;
    fs::file_time_type write_time;
};

class shader
{
public:
    shader();
    ~shader();

    void bind() const;
    void release() const;
    void hot_reload();
    void set_uniform(const int location, const int uniform_1) const;
    void set_uniform(const int location, const float uniform_1) const;
    void set_uniform(const int location, const int number_of_matrices, const float* uniform) const;
    void set_uniform(const int location, const float uniform_1, const float uniform_2) const;
    void set_uniform(const int location, const float uniform_1, const float uniform_2, const float uniform_3) const;
    void set_uniform(const int location, const float uniform_1, const float uniform_2, const float uniform_3, const float uniform_4) const;

    bool load_vertex_shader(const fs::path& file);
    bool load_tessellation_control_shader(const fs::path& file);
    bool load_tessellation_evaluation_shader(const fs::path& file);
    bool load_geometry_shader(const fs::path& file);
    bool load_fragment_shader(const fs::path& file);
    bool load_compute_shader(const fs::path& file);

    int get_uniform_location(const std::string& name) const;

private:
    bool initialize(const fs::path& file, const GLuint program, const GLenum type, file_watch& watch);
    bool link(const GLuint program);
    void wipe();

private:
    GLuint program = 0;

    file_watch vertex_watch;
    file_watch tessellation_control_watch;
    file_watch tessellation_evaluation_watch;
    file_watch geometry_watch;
    file_watch fragment_watch;
    file_watch compute_watch;

    std::unordered_map<std::string, int> uniforms;
};