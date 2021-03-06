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
#include <gf/AnimatedSprite.h>

#include <gf/Animation.h>

namespace gf {
inline namespace v1 {

  AnimatedSprite::AnimatedSprite()
  : m_animation(nullptr)
  {

  }

  void AnimatedSprite::setAnimation(Animation& animation) {
    m_animation = &animation;
    setTexture(*m_animation->getCurrentTexture());
    setTextureRect(m_animation->getCurrentBounds());
  }

  void AnimatedSprite::update(float dt) {
    if (m_animation == nullptr) {
      return;
    }

    if (m_animation->update(dt)) {
      setTexture(*m_animation->getCurrentTexture());
      setTextureRect(m_animation->getCurrentBounds());
    }
  }

}
}
