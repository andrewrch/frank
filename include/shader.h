#pragma once

#include <gl/glew.h>
#include <vector>
#include "handle.h"

namespace frank
{
  namespace detail
  {
    struct CreateShader
    {
      GLuint operator()(GLenum type)
      {
        return glCreateShader(type);
      }
    };

    struct DeleteShader
    {
      void operator()(GLuint handle)
      {
        glDeleteShader(handle);
      }
    };
  }

  using ShaderHandle = Handle<detail::CreateShader, detail::DeleteShader>;
  class Shader : public ShaderHandle
  {
  public:
    Shader(GLenum type)
      : ShaderHandle(type)
    {
    }
    template <typename... Strings>
    void addSource(const std::string& src, Strings... more)
    {
      source.push_back(src);
      addSource(more...);
    }
    void compile()
    {
      glCompileShader(getHandle());
    }
  private:
    void addSource() {}
    std::vector<std::string> source;
  };
}