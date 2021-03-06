/*
 * Gamedev Framework (gf)
 * Copyright (C) 2016 Julien Bernard
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */
#include <cstdlib>
#include <iostream>

#include <gf/Event.h>
#include <gf/RenderWindow.h>
#include <gf/Texture.h>
#include <gf/TileLayer.h>
#include <gf/Views.h>
#include <gf/ViewContainer.h>
#include <gf/Window.h>

static constexpr unsigned MapWidth = 44;
static constexpr unsigned MapHeight = 25;

static int map[MapHeight][MapWidth] = {
  { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, },
  { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, },
  { -1, -1, 346, 315, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 284, 253, -1, -1, },
  { -1, -1, 252, 221, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 190, 159, -1, -1, },
  { -1, -1, 407, 345, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 407, 345, -1, -1, },
  { -1, -1, 407, 345, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 407, 345, -1, -1, },
  { -1, -1, 407, 345, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 31, 62, 62, 62, 62, 189, 62, 62, 62, 62, 439, -1, -1, -1, -1, -1, -1, -1, -1, 346, 315, 0, 0, 0, 0, 96, 345, -1, -1, },
  { -1, -1, 407, 345, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 93, -1, -1, -1, -1, -1, -1, -1, -1, -1, 93, -1, -1, -1, -1, -1, -1, -1, -1, 252, 221, 282, 282, 282, 282, 190, 345, -1, -1, },
  { -1, -1, 407, 345, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 93, -1, -1, -1, -1, -1, -1, -1, -1, -1, 93, -1, -1, -1, 346, 315, 284, 253, -1, 407, 345, -1, -1, -1, -1, 407, 345, -1, -1, },
  { -1, -1, 407, 345, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 313, 62, 62, 62, 62, 62, 62, 62, 62, 62, 251, -1, -1, -1, 252, 221, 190, 159, -1, 407, 345, -1, -1, -1, -1, 407, 345, -1, -1, },
  { -1, -1, 407, 345, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 407, 345, 407, 345, -1, 407, 345, -1, -1, -1, -1, 407, 345, -1, -1, },
  { -1, -1, 407, 345, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 407, 345, 158, 127, 0, 96, 65, -1, -1, -1, -1, 407, 345, -1, -1, },
  { -1, -1, 407, 345, 346, 315, 0, 0, 0, 284, 253, -1, 346, 315, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 96, 65, 64, 33, 282, 2, 435, -1, -1, -1, -1, 407, 345, -1, -1, },
  { -1, -1, 407, 345, 252, 221, 282, 282, 282, 190, 159, -1, 252, 221, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 2, 435, -1, -1, -1, -1, -1, -1, -1, -1, -1, 407, 345, -1, -1, },
  { -1, -1, 407, 345, 407, 345, -1, -1, -1, 407, 345, -1, 407, 345, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 407, 345, -1, -1, },
  { -1, -1, 407, 345, 407, 345, -1, -1, -1, 407, 345, -1, 407, 345, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 407, 345, -1, -1, },
  { -1, -1, 407, 345, 407, 345, -1, -1, -1, 158, 127, 0, 96, 65, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 31, 188, 345, -1, -1, },
  { -1, -1, 407, 345, 158, 127, 0, 284, 253, 64, 33, 282, 2, 435, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 93, 407, 345, -1, -1, },
  { -1, -1, 407, 345, 64, 33, 282, 190, 159, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 93, 407, 345, -1, -1, },
  { -1, -1, 407, 345, -1, -1, -1, 407, 345, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 93, 407, 345, -1, -1, },
  { -1, -1, 407, 345, -1, -1, -1, 407, 345, 31, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 251, 407, 345, -1, -1, },
  { -1, -1, 158, 127, 0, 0, 0, 96, 127, 157, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 217, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 96, 65, -1, -1, },
  { -1, -1, 64, 33, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 155, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 2, 435, -1, -1, },
  { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, },
  { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, },
};

static constexpr unsigned TileSize = 128;

int main() {
  gf::Vector2u screenSize(640, 480);

  gf::Window window("18_tilelayer", screenSize);
  gf::RenderWindow renderer(window);

  gf::ViewContainer views;

  gf::ExtendView view;
  view.setCenter({ 0.0f, 0.0f });
  view.setSize({ 480.0f, 480.0f });
  views.addView(view);

  views.onScreenResize(screenSize);

  gf::Texture texture;

  if (!texture.loadFromFile("18_tilelayer.png")) {
    return EXIT_FAILURE;
  }

  texture.setSmooth();

  gf::TileLayer tileLayer({ MapWidth, MapHeight });
  tileLayer.setTileSize({ TileSize, TileSize });
  tileLayer.setSpacing(2);
  tileLayer.setTexture(texture);
  tileLayer.setOrigin({ TileSize * MapWidth / 2, TileSize * MapHeight / 2 });

  for (unsigned y = 0; y < MapHeight; ++y) {
    for (unsigned x = 0; x < MapWidth; ++x) {
      tileLayer.setTile({ x, y }, map[y][x]);
    }
  }

  renderer.clear(gf::Color::darker(gf::Color::Spring));

  std::cout << "Gamedev Framework (gf) example #18: Tile Layer\n";
  std::cout << "This example shows a tile layer.\n";
  std::cout << "How to use:\n";
  std::cout << "\tUp/Down/Left/Right: move the view\n";
  std::cout << "\tPageUp/PageDown: Zoom in/out\n";
  std::cout << "\t1/2: Rotate\n";

  while (window.isOpen()) {
    gf::Event event;

    while (window.pollEvent(event)) {
      switch (event.type) {
        case gf::EventType::Closed:
          window.close();
          break;

        case gf::EventType::KeyPressed:
          switch (event.key.scancode) {
            case gf::Scancode::PageUp:
              view.zoom(0.8f);
              break;

            case gf::Scancode::PageDown:
              view.zoom(1.25f);
              break;

            case gf::Scancode::Left:
              view.move({ -0.5f * TileSize, 0 });
              break;

            case gf::Scancode::Right:
              view.move({ 0.5f * TileSize, 0 });
              break;

            case gf::Scancode::Up:
              view.move({ 0, -0.5f * TileSize });
              break;

            case gf::Scancode::Down:
              view.move({ 0, 0.5f * TileSize });
              break;

            case gf::Scancode::Num1:
              view.rotate(gf::Pi / 8);
              break;

            case gf::Scancode::Num2:
              view.rotate(-gf::Pi / 8);
              break;

            default:
              break;
          }
          break;

        default:
          break;
      }

      views.update(event);
    }

    renderer.setView(view);

    renderer.clear();
    renderer.draw(tileLayer);
    renderer.display();
  }

  return 0;
}
