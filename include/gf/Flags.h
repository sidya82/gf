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
 *
 * Part of this file comes from SFML, with the same license:
 * Copyright (C) 2007-2015 Laurent Gomila (laurent@sfml-dev.org)
 */
#ifndef GF_FLAGS_H
#define GF_FLAGS_H

#include <type_traits>

namespace gf {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
inline namespace v1 {
#endif

  /**
   * @brief Bitfield relying on an enumeration
   *
   * ~~~
   * enum class AnimalProperties {
   *   HasClaws     = 0x01,
   *   CanFly       = 0x02,
   *   EatsFish     = 0x04,
   *   IsEndangered = 0x08,
   * };
   *
   * namespace gf {
   *   template<>
   *   struct EnableBitmaskOperators<AnimalProperties> {
   *     static constexpr bool value = true;
   *   };
   * }
   *
   * gf::Flags<AnimalProperties> seahawk = AnimalProperties::CanFly | AnimalProperties::EatsFish;
   * seahawk |= AnimalProperties::IsEndangered;
   *
   * bool b = seahawk.test(AnimalProperties::HasClaws); // false
   * ~~~
   *
   */
  template<typename E>
  class Flags {
  public:
    /**
     * @brief Default constructor
     */
    constexpr Flags()
    : m_data{0}
    {

    }

    /**
     * @brief Constructor with an enum value
     *
     * @param e An enum value
     */
    constexpr Flags(E e)
    : m_data(static_cast<Type>(e))
    {

    }

    /**
     * @brief Binary NOT operator
     *
     * @returns A bitfield where all flags have been inverted
     */
    constexpr Flags<E> operator~() const {
      return Flags(~m_data);
    }

    /**
     * @brief Binary OR and assignment
     *
     * @param flags Another bitfield
     * @return The bitfield with a binary OR of the flags and the other's flags
     */
    Flags<E>& operator|=(Flags<E> flags) {
      m_data |= flags.m_data;
      return *this;
    }

    /**
     * @brief Binary AND and assignment
     *
     * @param flags Another bitfield
     * @return The bitfield with a binary AND of the flags and the other's flags
     */
    Flags<E>& operator&=(Flags<E> flags) {
      m_data &= flags.m_data;
      return *this;
    }

    /**
     * @brief Test if any flag is set
     *
     * @returns True if any flag is set
     */
    operator bool() const {
      return m_data != 0;
    }

    /**
     * @brief Test if a specified flag is set
     *
     * @param flag The flag to test
     * @return True if the flag is set
     */
    bool test(E flag) const {
      return (m_data & static_cast<Type>(flag)) != 0;
    }

    /**
     * @brief Set a flag
     *
     * @param flag The flag to set
     */
    void set(E flag) {
      m_data |= static_cast<Type>(flag);
    }

    /**
     * @brief Reset a flag
     *
     * @param flag The flag to reset
     */
    void reset(E flag) {
      m_data &= ~static_cast<Type>(flag);
    }

  private:
    using Type = typename std::underlying_type<E>::type;

    Flags(Type data)
    : m_data(data)
    {

    }

    Type m_data;
  };

  /**
   * @relates Flags
   * @brief Binary OR between two bitfields
   *
   * @param lhs The first bitfield
   * @param rhs The second bitfield
   * @return The bitfield with a binary OR of the two bitfields
   */
  template<typename E>
  inline
  Flags<E> operator|(Flags<E> lhs, Flags<E> rhs) {
    Flags<E> flags(lhs);
    flags |= rhs;
    return flags;
  }

  /**
   * @relates Flags
   * @brief Binary OR between a bitfield and a flag
   *
   * @param lhs The bitfield
   * @param rhs The flag
   * @return The bitfield with a binary OR of the bitfield and the flag
   */
  template<typename E>
  inline
  Flags<E> operator|(Flags<E> lhs, E rhs) {
    Flags<E> flags(lhs);
    flags |= rhs;
    return flags;
  }

  /**
   * @relates Flags
   * @brief Binary OR between a flag and a bitfield
   *
   * @param lhs The flag
   * @param rhs The bitfield
   * @return The bitfield with a binary OR of the flag and the bitfield
   */
  template<typename E>
  inline
  Flags<E> operator|(E lhs, Flags<E> rhs) {
    Flags<E> flags(lhs);
    flags |= rhs;
    return flags;
  }

  /**
   * @relates Flags
   * @brief Binary AND between two bitfields
   *
   * @param lhs The first bitfield
   * @param rhs The second bitfield
   * @return The bitfield with a binary AND of the two bitfields
   */
  template<typename E>
  inline
  Flags<E> operator&(Flags<E> lhs, Flags<E> rhs) {
    Flags<E> flags(lhs);
    flags &= rhs;
    return flags;
  }

  /**
   * @relates Flags
   * @brief Binary AND between a bitfield and a flag
   *
   * @param lhs The bitfield
   * @param rhs The flag
   * @return The bitfield with a binary AND of the bitfield and the flag
   */
  template<typename E>
  inline
  Flags<E> operator&(Flags<E> lhs, E rhs) {
    Flags<E> flags(lhs);
    flags &= rhs;
    return flags;
  }

  /**
   * @relates Flags
   * @brief Binary AND between a flag and a bitfield
   *
   * @param lhs The flag
   * @param rhs The bitfield
   * @return The bitfield with a binary AND of the flag and the bitfield
   */
  template<typename E>
  inline
  Flags<E> operator&(E lhs, Flags<E> rhs) {
    Flags<E> flags(lhs);
    flags &= rhs;
    return flags;
  }

#ifndef DOXYGEN_SHOULD_SKIP_THIS
}
#endif

#ifndef DOXYGEN_SHOULD_SKIP_THIS
// this traits is not versioned to ease external usage
template<typename E>
struct EnableBitmaskOperators {
  static constexpr bool value = false;
};
#endif

}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
template<typename E>
typename std::enable_if<gf::EnableBitmaskOperators<E>::value, gf::Flags<E>>::type
operator|(E lhs, E rhs) {
  gf::Flags<E> flags(lhs);
  flags |= rhs;
  return flags;
}

template<typename E>
typename std::enable_if<gf::EnableBitmaskOperators<E>::value, gf::Flags<E>>::type
operator&(E lhs, E rhs) {
  gf::Flags<E> flags(lhs);
  flags &= rhs;
  return flags;
}

template<typename E>
typename std::enable_if<gf::EnableBitmaskOperators<E>::value, gf::Flags<E>>::type
operator~(E val) {
  gf::Flags<E> flags(val);
  return ~flags;
}
#endif

#endif // GF_FLAGS_H
