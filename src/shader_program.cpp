#include "shader_program.h"

#include <iostream>
#include <stdexcept>

ShaderProgram::ShaderProgram(const char* vertex_shader_source, const char* fragment_shader_source)
{
    m_shader_program_id = CreateProgram(vertex_shader_source, fragment_shader_source);

    if (m_shader_program_id == 0)
    {
        throw std::runtime_error("Failed to load shader program");
    }
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(m_shader_program_id);

    m_shader_program_id = 0;
}

void ShaderProgram::Bind() const
{
    glUseProgram(m_shader_program_id);
}

void ShaderProgram::Unbind() const
{
    glUseProgram(0);
}

void ShaderProgram::SetUniform1i(const char* name, int value) const
{
    glUniform1i(glGetUniformLocation(m_shader_program_id, name), value);
}

void ShaderProgram::SetUniform1f(const char* name, float value) const
{
    glUniform1f(glGetUniformLocation(m_shader_program_id, name), value);
}

void ShaderProgram::SetUniform1d(const char* name, double value) const
{
    glUniform1d(glGetUniformLocation(m_shader_program_id, name), value);
}

void ShaderProgram::SetUniform2d(const char* name, double value_1, double value_2) const
{
    glUniform2d(glGetUniformLocation(m_shader_program_id, name), value_1, value_2);
}

/*
 * Compiles a GLSL shader, returning the shader object id on success or 0 on failure
 */
GLuint ShaderProgram::CompileShader(const GLchar* shader_source, const GLenum shader_type) const
{
	GLuint shader_id = glCreateShader(shader_type);

	glShaderSource(shader_id, 1, &shader_source, nullptr);
	glCompileShader(shader_id);

	GLint compilation_success;
	GLchar errorLog[512];

	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compilation_success);

	if (!compilation_success)
	{
		glGetShaderInfoLog(shader_id, 512, nullptr, errorLog);
		std::cerr << "Shader compilation error: " << errorLog << '\n';

		return 0;
	}

	return shader_id;
}

/*
* Links a GLSL program, returning the shader program object id on success or 0 on failure
*/
GLuint ShaderProgram::LinkProgram(std::vector<GLuint> shader_ids) const
{
	GLuint shader_program_id = glCreateProgram();

	for (GLuint shader_id : shader_ids)
	{
		glAttachShader(shader_program_id, shader_id);
	}

	glLinkProgram(shader_program_id);

	GLint link_success;
	GLchar errorLog[512];

	glGetProgramiv(shader_program_id, GL_LINK_STATUS, &link_success);

	if (!link_success)
	{
		glGetProgramInfoLog(shader_program_id, 512, nullptr, errorLog);
		std::cerr << "Shader program link error: " << errorLog << '\n';

		return 0;
	}

	return shader_program_id;
}

GLuint ShaderProgram::CreateProgram(const GLchar* vertex_shader_source, const GLchar* fragment_shader_source) const
{
	GLuint vertex_shader_id = CompileShader(vertex_shader_source, GL_VERTEX_SHADER);
	GLuint fragment_shader_id = CompileShader(fragment_shader_source, GL_FRAGMENT_SHADER);
	GLuint shader_program_id = LinkProgram({ vertex_shader_id, fragment_shader_id });

	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);

	return shader_program_id;
}
