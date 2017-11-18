#include "render_texture.h"

#include <iostream>
#include <stdexcept>

RenderTexture::RenderTexture(int width, int height)
{
    CreateRenderTexture(width, height);
}

RenderTexture::~RenderTexture()
{
    glDeleteTextures(1, &m_render_texture_id);
    glDeleteFramebuffers(1, &m_framebuffer_id);

    m_render_texture_id = 0;
    m_framebuffer_id = 0;
}

void RenderTexture::Bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer_id);
}

void RenderTexture::Unbind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderTexture::BindTexture() const
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_render_texture_id);
}

void RenderTexture::UnbindTexture() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void RenderTexture::CreateRenderTexture(int width, int height)
{
    glGenFramebuffers(1, &m_framebuffer_id);
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer_id);

    glGenTextures(1, &m_render_texture_id);

    glBindTexture(GL_TEXTURE_2D, m_render_texture_id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, (void*) 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_render_texture_id, 0);
    
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cerr << "Failed to initialize framebuffer\n";
        std::runtime_error("FRAMEBUFFER INITIALIZATION ERROR");
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
