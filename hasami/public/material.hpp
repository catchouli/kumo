#pragma once

#include "renderer.hpp"

namespace hs {

class Material;

class ShaderVar
{
public:
  ShaderVar(const char* name)
    : m_name(name)
    , m_mat(nullptr)
    , m_dirty(true)
  {}

  void create(Material* mat);
  void update();

  const char* name() const { return m_name.c_str(); }

  virtual void* valPtr() const = 0;
  virtual hs::UniformType valTy() const = 0;

protected:
  std::string m_name;
  Material* m_mat;
  bool m_dirty;
};

template <typename T>
class ShaderVarT
  : public ShaderVar
{
public:
  ShaderVarT(const char* name, T val);
  void set(const T& val);

  const T& val() const { return m_val; }

  void* valPtr() const override { return (void*)&m_val; };
  hs::UniformType valTy() const override { static_assert(false, "ShaderVarT not implemented for this type"); };

private:
  T m_val;
};

class Sampler
{
public:
  Sampler(const char* name);

  void create(Material* mat, TextureUnit unit);

  void set(std::shared_ptr<hs::Texture> tex) { m_tex = tex; }

  hs::Texture* tex() { return m_tex.get(); }
  ShaderVarT<TextureUnit>& var() { return m_var; }

private:
  std::shared_ptr<hs::Texture> m_tex;
  ShaderVarT<TextureUnit> m_var;
};

class Material
{
public:
  Material(hs::Renderer* renderer, const char* shaderPath);

  void addUniform(ShaderVar* var);
  void addUniforms(std::vector<ShaderVar*> vars);
  void addSampler(Sampler* sampler);
  void addSamplers(std::vector<Sampler*> samplers);

  void flush();

  hs::Shader* shader() const { return m_shader.get(); }

private:
  std::shared_ptr<hs::Shader> m_shader;
  std::vector<ShaderVar*> m_vars;
  std::vector<Sampler*> m_samplers;
  TextureUnit m_units;
};

/* ShaderVarT */

template <typename T>
ShaderVarT<T>::ShaderVarT(const char* name, T val)
  : ShaderVar(name)
  , m_val(val)
{
}

template <typename T>
void ShaderVarT<T>::set(const T& val)
{
  assert(m_mat);
  if (!m_mat) {
    fprintf(stderr, "ShaderVar used without being initialised...");
  }

  m_val = val;
  m_dirty = true;
}

template <>
hs::UniformType ShaderVarT<float>::valTy() const {
  return hs::UniformType::Float;
}

template <>
hs::UniformType ShaderVarT<TextureUnit>::valTy() const {
  return hs::UniformType::Sampler2D;
}

template <>
hs::UniformType ShaderVarT<glm::mat4>::valTy() const {
  return hs::UniformType::Mat4;
}

}