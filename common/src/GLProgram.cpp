#include "GLProgram.hpp"

#include "GLShader.hpp"

GLProgram::GLProgram(const char* name) : GLNode(name)
{
    this->id = glCreateProgram();
}

GLProgram::GLProgram(std::shared_ptr<GLShader> vertex, std::shared_ptr<GLShader> fragment, const char* name) : GLNode(name)
{
    this->id = glCreateProgram();
    this->AddShader(vertex);
    this->AddShader(fragment);
}

GLProgram::~GLProgram()
{
    glDeleteProgram(this->id);
}

bool GLProgram::Status()
{
    glGetProgramiv(this->id, GL_LINK_STATUS, &status);
    if(!status)
    {
        GLint msize;
        glGetProgramiv(this->id, GL_INFO_LOG_LENGTH, &msize);
        msg.resize(msize);
        glGetProgramInfoLog(this->id, msize, NULL, &msg[0]);
        std::cerr << msg << std::endl;
        return false;
    }
    return true;
}

bool GLProgram::AddShader(std::shared_ptr<GLShader> shader)
{
    if(shader->Status())
    {
        glAttachShader(this->id, shader->getId());
    }
    return this->Status();
}

bool GLProgram::RemoveShader(std::shared_ptr<GLShader> shader)
{
    //TODO: Verify shader is flagged for delete after attach
    glGetShaderiv(shader->getId(), GL_DELETE_STATUS, &status);
    if(status)
    {
        glDetachShader(this->id, shader->getId());
        return true;
    }
    return false;
}

void GLProgram::SetAttributeIndex(const char* name, GLuint index)
{
    glBindAttribLocation(this->id, index, name);
}

