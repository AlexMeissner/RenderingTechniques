#include "Shader.h"
#include "print.h"

namespace
{
    std::string get_source_code(const fs::path& file_path)
    {
        std::string source_code;
        std::fstream file(file_path.c_str(), std::ios_base::in | std::ios_base::binary);

        if (file.is_open())
        {
            file.seekg(0, file.end);
            std::size_t stProgramLength = static_cast<std::size_t>(file.tellg());
            file.seekg(0, file.beg);

            char* sProgramStr = new char[stProgramLength + 1];
            file.read(sProgramStr, stProgramLength);
            file.close();
            sProgramStr[stProgramLength] = '\0';
            source_code = sProgramStr;
            delete[] sProgramStr;
        }
        else
        {
            print::error << "Could not open shader file: " << file_path << print::endl;
        }

        return source_code;
    }

    GLuint create_shader(const GLuint program, const GLenum type, const std::string& shader)
    {
        const GLuint shader_id = glCreateShader(type);

        const char* shader_source = shader.c_str();
        glShaderSource(shader_id, 1, &shader_source, NULL);
        glCompileShader(shader_id);

        GLint compile_status = GL_FALSE;
        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compile_status);

        if (compile_status == GL_TRUE)
        {
            glAttachShader(program, shader_id);
            print::success << "Created shader successfully. Program(" << program << "), Type(" << type << "), Id(" << shader_id << ")" << print::endl;
            return shader_id;
        }

        int error_log_size = 0;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &error_log_size);

        if (error_log_size > 0)
        {
            char* error_log = new char[error_log_size];
            glGetShaderInfoLog(shader_id, error_log_size, NULL, error_log);
            print::error << "Shader creation failed." << print::endl;
            print::error << error_log << print::endl;
            delete[] error_log;
        }

        return 0;
    }

    bool load_shader(const fs::path& file, const GLuint program, const GLenum type, GLuint& id)
    {
        const std::string source_code = get_source_code(file);

        if (source_code.empty())
        {
            return false;
        }

        if (const GLuint shader_id = create_shader(program, type, source_code))
        {
            id = shader_id;
            return true;
        }

        return false;
    }

    bool file_changed(const file_watch& watch)
    {
        if (fs::exists(watch.file))
        {
            return fs::last_write_time(watch.file) != watch.write_time;
        }

        return false;
    }
}

shader::shader()
    : program(glCreateProgram())
{
}

shader::~shader()
{
    wipe();
}

void shader::bind() const
{
    glUseProgram(program);
}

void shader::release() const
{
    glUseProgram(0);
}

void shader::hot_reload()
{
    if (file_changed(vertex_watch) |
        file_changed(tessellation_control_watch) |
        file_changed(tessellation_evaluation_watch) |
        file_changed(geometry_watch) |
        file_changed(fragment_watch) |
        file_changed(compute_watch))
    {
        print::info << "Hot reloading shader." << print::endl;

        const GLuint new_program = glCreateProgram();
        GLuint vertex_id = 0, tessellation_control_id = 0, tessellation_evaluation_id = 0, geometry_id = 0, fragment_id = 0, compute_id = 0;

        bool updated = true;

        if (!vertex_watch.file.empty())
        {
            vertex_watch.write_time = fs::last_write_time(vertex_watch.file);
            updated &= load_shader(vertex_watch.file, new_program, GL_VERTEX_SHADER, vertex_id);
        }
        if (!tessellation_control_watch.file.empty())
        {
            tessellation_control_watch.write_time = fs::last_write_time(tessellation_control_watch.file);
            updated &= load_shader(tessellation_control_watch.file, new_program, GL_TESS_CONTROL_SHADER, tessellation_control_id);
        }
        if (!tessellation_evaluation_watch.file.empty())
        {
            tessellation_evaluation_watch.write_time = fs::last_write_time(tessellation_evaluation_watch.file);
            updated &= load_shader(tessellation_evaluation_watch.file, new_program, GL_TESS_EVALUATION_SHADER, tessellation_evaluation_id);
        }
        if (!geometry_watch.file.empty())
        {
            geometry_watch.write_time = fs::last_write_time(geometry_watch.file);
            updated &= load_shader(geometry_watch.file, new_program, GL_GEOMETRY_SHADER, geometry_id);
        }
        if (!fragment_watch.file.empty())
        {
            fragment_watch.write_time = fs::last_write_time(fragment_watch.file);
            updated &= load_shader(fragment_watch.file, new_program, GL_FRAGMENT_SHADER, fragment_id);
        }
        if (!compute_watch.file.empty())
        {
            compute_watch.write_time = fs::last_write_time(compute_watch.file);
            updated &= load_shader(compute_watch.file, new_program, GL_COMPUTE_SHADER, compute_id);
        }

        if (updated && link(new_program))
        {
            wipe();
            program = new_program;
            vertex_watch.id = vertex_id;
            tessellation_control_watch.id = tessellation_control_id;
            tessellation_evaluation_watch.id = tessellation_evaluation_id;
            geometry_watch.id = geometry_id;
            fragment_watch.id = fragment_id;
            compute_watch.id = compute_id;
            print::success << "Hot reloading shader succeded." << print::endl;
        }
        else
        {
            glDeleteShader(vertex_id);
            glDeleteShader(tessellation_control_id);
            glDeleteShader(tessellation_evaluation_id);
            glDeleteShader(geometry_id);
            glDeleteShader(fragment_id);
            glDeleteShader(compute_id);
            glDeleteProgram(new_program);
            print::error << "Hot reloading shader failed." << print::endl;
        }
    }
}

void shader::set_uniform(const int location, const int uniform_1) const
{
    glUniform1i(location, uniform_1);
}

void shader::set_uniform(const int location, const float uniform_1) const
{
    glUniform1f(location, uniform_1);
}

void shader::set_uniform(const int location, const int number_of_matrices, const float* uniform) const
{
    glUniformMatrix4fv(location, number_of_matrices, GL_FALSE, uniform);
}

void shader::set_uniform(const int location, const float uniform_1, const float uniform_2) const
{
    glUniform2f(location, uniform_1, uniform_2);
}

void shader::set_uniform(const int location, const float uniform_1, const float uniform_2, const float uniform_3) const
{
    glUniform3f(location, uniform_1, uniform_2, uniform_3);
}

void shader::set_uniform(const int location, const float uniform_1, const float uniform_2, const float uniform_3, const float uniform_4) const
{
    glUniform4f(location, uniform_1, uniform_2, uniform_3, uniform_4);
}

bool shader::load_vertex_shader(const fs::path& file)
{
    return initialize(file, program, GL_VERTEX_SHADER, vertex_watch);
}

bool shader::load_tessellation_control_shader(const fs::path& file)
{
    return initialize(file, program, GL_TESS_CONTROL_SHADER, tessellation_control_watch);
}

bool shader::load_tessellation_evaluation_shader(const fs::path& file)
{
    return initialize(file, program, GL_TESS_EVALUATION_SHADER, tessellation_evaluation_watch);
}

bool shader::load_geometry_shader(const fs::path& file)
{
    return initialize(file, program, GL_GEOMETRY_SHADER, geometry_watch);
}

bool shader::load_fragment_shader(const fs::path& file)
{
    return initialize(file, program, GL_FRAGMENT_SHADER, fragment_watch);
}

bool shader::load_compute_shader(const fs::path& file)
{
    return initialize(file, program, GL_COMPUTE_SHADER, compute_watch);
}

int shader::get_uniform_location(const std::string& name) const
{
    const auto it = uniforms.find(name);

    if (it == uniforms.end())
    {
        print::error << "Shader has no uniform with name " << name;
        return -1;
    }
    else
    {
        return (*it).second;
    }
}

bool shader::initialize(const fs::path& file, const GLuint program, const GLenum type, file_watch& watch)
{
    watch.file = file;
    watch.write_time = fs::last_write_time(file);

    if (load_shader(file, program, type, watch.id))
    {
        return link(program);
    }

    return false;
}

void shader::wipe()
{
    print::info << "Wiping shader program (" << program << ")" << print::endl;
    glDeleteShader(vertex_watch.id);
    glDeleteShader(fragment_watch.id);
    glDeleteShader(tessellation_control_watch.id);
    glDeleteShader(tessellation_evaluation_watch.id);
    glDeleteShader(geometry_watch.id);
    glDeleteShader(compute_watch.id);
    glDeleteProgram(program);
}

bool shader::link(const GLuint program)
{
    glLinkProgram(program);

    GLint link_status = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &link_status);

    if (link_status == GL_TRUE)
    {
        uniforms.clear();
        int uniform_count = 0;
        int maximal_name_length = 0;

        glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &uniform_count);
        glGetProgramiv(program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maximal_name_length);

        if (uniform_count == 0 || maximal_name_length == 0)
        {
            return true;
        }

        GLchar* uniform = new GLchar[maximal_name_length];
        GLsizei uniform_length = 0;
        GLint   size = 0;
        GLenum  type;

        for (int i = 0; i < uniform_count; ++i)
        {
            glGetActiveUniform(program, static_cast<GLuint>(i), maximal_name_length, &uniform_length, &size, &type, uniform);
            const uint64_t    array_position = std::string(uniform).rfind('[');
            const std::string uniform_name = array_position == std::string::npos ? std::string(uniform) : std::string(uniform).substr(0, array_position);
            const GLint       location = glGetUniformLocation(program, uniform_name.c_str());
            uniforms[uniform_name] = location;
        }

        delete[] uniform;
        glGetError();

        return true;
    }

    GLint log_size = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_size);
    std::vector<GLchar> error_log(log_size);
    glGetProgramInfoLog(program, log_size, &log_size, &error_log[0]);
    const std::string message(error_log.begin(), error_log.end());
    print::error << message;

    return false;
}