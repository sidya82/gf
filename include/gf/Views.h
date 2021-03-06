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
#ifndef GF_VIEWS_H
#define GF_VIEWS_H

#include "Portability.h"
#include "View.h"

namespace gf {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
inline namespace v1 {
#endif

  /**
   * @ingroup graphics
   * @brief Stretch view
   *
   * This view assumes that the screen is always the same size as the world.
   * The world will then be stretched to fit the screen. There are no black
   * bars, but the aspect ratio may not be the same after the scaling took
   * place.
   *
   * ![Stretch view](@ref stretchview.png)
   *
   * @sa gf::AdaptativeView
   */
  class GF_API StretchView : public AdaptativeView {
  public:
    virtual void onScreenResize(Vector2u screenSize) override;
  };

  /**
   * @ingroup graphics
   * @brief Fit view
   *
   * This view will always maintain the aspect ratio of the world, while
   * scaling it as much as possible to fit the screen. One disadvantage
   * with this strategy is that there may appear black bars.
   *
   * ![Fit view](@ref fitview.png)
   *
   * @sa gf::AdaptativeView
   */
  class GF_API FitView : public AdaptativeView {
  public:
    virtual void onScreenResize(Vector2u screenSize) override;
  };

  /**
   * @ingroup graphics
   * @brief Fill view
   *
   * This view keeps the aspect ratio of the world, but it will always fill
   * the whole screen which might result in parts of the world being cut off.
   *
   * ![Fill view](@ref fillview.png)
   *
   * @sa gf::AdaptativeView
   */
  class GF_API FillView : public AdaptativeView {
  public:
    virtual void onScreenResize(Vector2u screenSize) override;

  protected:
    virtual void onWorldResize(Vector2f worldSize) override;

  private:
    Vector2f m_worldSize;
  };

  /**
   * @ingroup graphics
   * @brief Extend view
   *
   * This view keeps the world aspect ratio without black bars by extending
   * the world in one direction. The world is first scaled to fit within the
   * viewport, then the shorter dimension is lengthened to fill the viewport.
   *
   * ![Extend view](@ref extendview.png)
   *
   * @sa gf::AdaptativeView
   */
  class GF_API ExtendView : public AdaptativeView {
  public:
    virtual void onScreenResize(Vector2u screenSize) override;

  protected:
    virtual void onWorldResize(Vector2f worldSize) override;

  private:
    Vector2f m_worldSize;
  };

  /**
   * @ingroup graphics
   * @brief Screen view
   *
   * This view will always match the window size which means that no scaling
   * happens and no black bars appear. As a disadvantage this means that the
   * gameplay might change, because a player with a bigger screen might see
   * more of the game, than a player with a smaller screen size.
   *
   * This view can be used to display [HUD](https://en.wikipedia.org/wiki/HUD_%28video_gaming%29).
   *
   * ![Screen view](@ref screenview.png)
   *
   * @sa gf::AdaptativeView
   */
  class GF_API ScreenView : public AdaptativeView {
  public:
    virtual void onScreenResize(Vector2u screenSize) override;
  };

#ifndef DOXYGEN_SHOULD_SKIP_THIS
}
#endif
}

#endif // GF_VIEWS_H
