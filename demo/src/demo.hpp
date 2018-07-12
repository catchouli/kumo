#pragma once

#include "renderer.hpp"
#include "mesh.hpp"
#include "scenegraph.hpp"
#include "camera.hpp"
#include "standardmaterial.hpp"

#include <memory>

class Demo : public hs::App
{
public:
  Demo(hs::Window* window);

  void render(hs::Window* window) override;
  bool running() override { return m_running; }
  void input(const SDL_Event* evt);

private:
  bool m_running;

  std::shared_ptr<hs::FPSCamera> m_camera;

  std::shared_ptr<hs::SceneNode> m_scenegraph;

  // Miku
  std::shared_ptr<hs::AssemblyNode> m_miku;
  std::shared_ptr<hs::ModelNode> m_mikuModel;

  // Globe
  std::shared_ptr<hs::AssemblyNode> m_globe;
};