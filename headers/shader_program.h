#ifndef FRACTAL_EXPLORER_SHADER_PROGRAM_H_
#define FRACTAL_EXPLORER_SHADER_PROGRAM_H_

#include <glad/glad.h>

#include <vector>

class ShaderProgram
{
    public:
        ShaderProgram(const char* vertex_shader_source, const char* fragment_shader_source);
        ~ShaderProgram();

        void Bind() const;
        void Unbind() const;

        void SetUniform1i(const char* name, int value) const;
        void SetUniform1f(const char* name, float value) const;
        void SetUniform1d(const char* name, double value) const;
        void SetUniform2d(const char* name, double value_1, double value_2) const;
    private:
        ShaderProgram(const ShaderProgram&) = delete;
        ShaderProgram& operator=(const ShaderProgram&) = delete;

        GLuint CompileShader(const char* shader_source, const GLenum shader_type) const;
        GLuint LinkProgram(std::vector<GLuint> shader_ids) const ;
        GLuint CreateProgram(const char* vertex_shader_source, const char* fragment_shader_source) const;

        GLuint m_shader_program_id;
};

#endif
