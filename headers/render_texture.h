#ifndef FRACTAL_EXPLORER_RENDER_TEXTURE_H_
#define FRACTAL_EXPLORER_RENDER_TEXTURE_H_

#include <glad/glad.h>

class RenderTexture
{
    public:
        RenderTexture(int width, int height);
        ~RenderTexture();

        void Bind() const;
        void Unbind() const;
        void BindTexture() const;
        void UnbindTexture() const;
    private:
        RenderTexture(const RenderTexture&) = delete;
        RenderTexture& operator=(const RenderTexture&) = delete;

        void CreateRenderTexture(int width, int height);

        GLuint m_framebuffer_id;
        GLuint m_render_texture_id;
};

#endif
