
//
// This source file is part of appleseed.
// Visit http://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2010-2013 Francois Beaune, Jupiter Jazz Limited
// Copyright (c) 2014-2017 Francois Beaune, The appleseedhq Organization
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#ifndef APPLESEED_FOUNDATION_MATH_SCALAR_H
#define APPLESEED_FOUNDATION_MATH_SCALAR_H

// appleseed.foundation headers.
#include "foundation/platform/arch.h"
#ifdef APPLESEED_USE_SSE
#include "foundation/platform/sse.h"
#endif
#include "foundation/platform/types.h"

// Standard headers.
#include <cassert>
#include <cmath>
#include <cstddef>
#ifdef _MSC_VER
#include <cstdlib>
#include <intrin.h>
#endif
#include <limits>

namespace foundation
{

//
// Constants.
//

template <typename T> inline T Pi()                 { return static_cast<T>(3.1415926535897932); }
template <typename T> inline T TwoPi()              { return static_cast<T>(6.2831853071795865); }  // 2 * Pi
template <typename T> inline T FourPi()             { return static_cast<T>(12.566370614359173); }  // 4 * Pi
template <typename T> inline T HalfPi()             { return static_cast<T>(1.5707963267948966); }  // Pi / 2
template <typename T> inline T PiOverFour()         { return static_cast<T>(0.7853981633974483); }  // Pi / 4
template <typename T> inline T RcpPi()              { return static_cast<T>(0.3183098861837907); }  // 1 / Pi
template <typename T> inline T TwoOverPi()          { return static_cast<T>(0.6366197723675813); }  // 2 / Pi
template <typename T> inline T FourOverPi()         { return static_cast<T>(1.2732395447351627); }  // 4 / Pi
template <typename T> inline T RcpHalfPi()          { return static_cast<T>(0.6366197723675813); }  // 1 / (Pi/2)
template <typename T> inline T RcpTwoPi()           { return static_cast<T>(0.1591549430918953); }  // 1 / (2 * Pi) = 0.5 / Pi
template <typename T> inline T RcpFourPi()          { return static_cast<T>(0.0795774715459477); }  // 1 / (4 * Pi)
template <typename T> inline T SqrtPi()             { return static_cast<T>(1.7724538509055160); }  // sqrt(Pi)
template <typename T> inline T PiSquare()           { return static_cast<T>(9.8696044010893586); }  // Pi^2
template <typename T> inline T FourPiSquare()       { return static_cast<T>(39.478417604357434); }  // 4 * Pi^2
template <typename T> inline T RcpPiSquare()        { return static_cast<T>(0.1013211836423378); }  // 1 / (Pi^2) = (1 / Pi)^2
template <typename T> inline T RcpFourPiSquare()    { return static_cast<T>(0.0253302959105844); }  // 1 / (4 * Pi^2)
template <typename T> inline T FourOverPiSquare()   { return static_cast<T>(0.4052847345693511); }  // 1 / (4 * Pi^2)
template <typename T> inline T SqrtTwo()            { return static_cast<T>(1.4142135623730950); }  // sqrt(2)
template <typename T> inline T RcpSqrtTwo()         { return static_cast<T>(0.7071067811865475); }  // 1 / sqrt(2) = sqrt(2) / 2
template <typename T> inline T SqrtThree()          { return static_cast<T>(1.7320508075688773); }  // sqrt(3)
template <typename T> inline T GoldenRatio()        { return static_cast<T>(1.6180339887498948); }  // (1 + sqrt(5)) / 2
template <typename T> inline T Ln10()               { return static_cast<T>(2.3025850929940457); }  // ln(10)


//
// Conversion operations.
//

// Convert an angle from degrees to radians.
template <typename T>
T deg_to_rad(const T angle);

// Convert an angle from radians to degrees.
template <typename T>
T rad_to_deg(const T angle);


//
// Arithmetic operations.
//

// Return the absolute value of the argument. This function complements
// the standard function std::abs() which is not necessary available for
// compiler-specific types (e.g. __int64).
template <typename T>
T abs(const T x);

// Return the square of the argument.
template <typename T>
T square(const T x);

// Return the cube of the argument.
template <typename T>
T cube(const T x);

// Return 1 / x.
template <typename T>
T rcp(const T x);

// Compile-time exponentiation of the form x^p where p >= 0.
// Note: swapped template arguments to allow writing pow_int<3>(3.14).
template <size_t P, typename T>
T pow_int(const T x);

// Runtime exponentiation of the form x^p where p >= 0.
template <typename T>
T pow_int(const T x, size_t p);

// Return the smallest power of 2 larger than a given integer x (x > 0).
template <typename T> T next_pow2(T x);
template <> int64 next_pow2<int64>(int64 x);
template <> uint64 next_pow2<uint64>(uint64 x);

// Return true if a given integer x is a power of 2.
template <typename T>
bool is_pow2(const T x);

// Return the base-2 logarithm of a given integer.
template <typename T>
T log2_int(T x);

// Return the log in a given base of a given scalar.
template <typename T>
T log(const T x, const T base);

// Return the next given power of a given scalar.
template <typename T>
T next_power(const T x, const T base);

// Round n (n >= 0) to the next multiple of m (m > 0).
template <typename T>
T next_multiple(const T n, const T m);

// Round n (n >= 0) to the previous multiple of m (m > 0).
template <typename T>
T prev_multiple(const T n, const T m);

// Return the factorial of a given integer.
template <typename T>
T factorial(T x);

// Return the binomial coefficient (n, k).
template <typename T>
T binomial(const T n, const T k);

// Clamp the argument to [low, high].
template <typename T>
T clamp(const T x, const T low, const T high);

// Clamp the argument to [0, 1].
template <typename T>
T saturate(const T x);

// Wrap the argument back to [0, 1).
template <typename T>
T wrap(const T x);

// Normalize an angle into [0, 2*Pi).
template <typename T>
T normalize_angle(const T angle);

// Semantically identical to static_cast<Int>(x).
template <typename Int, typename T>
Int truncate(const T x);

// Semantically identical to std::floor().
template <typename T>
T fast_floor(const T x);

// Semantically identical to std::ceil().
template <typename T>
T fast_ceil(const T x);

// Round x to the nearest integer with Round Half Away from Zero tie breaking rule.
// Reference: http://en.wikipedia.org/wiki/Rounding#Round_half_away_from_zero.
template <typename Int, typename T>
Int round(const T x);

// Compute a % n or fmod(a, n) and always return a non-negative value.
template <typename T>
T mod(const T a, const T n);

// Rotate an unsigned integer left or right by a given number of bits.
// Reference: https://stackoverflow.com/a/776523/393756
uint32 rotl32(const uint32 n, unsigned int shift);
uint64 rotl64(const uint64 n, unsigned int shift);
uint32 rotr32(const uint32 n, unsigned int shift);
uint64 rotr64(const uint64 n, unsigned int shift);

// linearstep() returns 0 for x < a, 1 for x > b, and generates
// a linear transition from 0 to 1 between x = a and x = b.
template <typename T>
T linearstep(const T a, const T b, const T x);

// smoothstep() returns 0 for x < a, 1 for x > b, and generates
// a smooth, C-infinite transition from 0 to 1 between x = a and
// x = b. The function has zero first derivatives at both x = a
// and x = b.
template <typename T>
T smoothstep(const T a, const T b, const T x);

// mix() returns a for x < 0, b for x > 1, and performs a linear
// blend between values a and b when x is between 0 and 1.
template <typename T, typename U>
T mix(const T a, const T b, const U x);

// lerp() returns the linear interpolation (1 - x) * a + x * b.
template <typename T, typename U>
T lerp(const T a, const T b, const U x);

// inverse_lerp() returns the relative position of x between a and b,
// i.e (x - a) / (b - a). It is the inverse operation of lerp().
template <typename T, typename U>
T inverse_lerp(const T a, const T b, const U x);

// fit() remaps a variable x from the range [min_x, max_x] to the
// range [min_y, max_y]. When x is outside the [min_x, max_x] range,
// a linear extrapolation outside the [min_y, max_y] range is used.
template <typename T>
T fit(
    const T x,
    const T min_x,
    const T max_x,
    const T min_y,
    const T max_y);
template <typename U, typename V>
V fit(
    const U x,
    const U min_x,
    const U max_x,
    const V min_y,
    const V max_y);


//
// Robust floating-point tests.
//
// todo: implement feq_ulp() and fz_ulp(), to compare scalars with precision
// expressed in ulp. Most probably an integer based comparison. Reference:
// http://www.cygnus-software.com/papers/comparingfloats/comparingfloats.htm.
//

// Default epsilon values for floating-point tests.
template <typename T> T default_eps();                      // intentionally left unimplemented
template <> inline float default_eps<float>()               { return 1.0e-6f; }
template <> inline double default_eps<double>()             { return 1.0e-14; }
template <> inline long double default_eps<long double>()   { return 1.0e-30L; }

// Allow using custom epsilon values in template code.
template <typename T> T make_eps(const float feps, const double deps);
template <> inline float make_eps(const float feps, const double /*deps*/)  { return feps; }
template <> inline double make_eps(const float /*feps*/, const double deps) { return deps; }

// Approximate equality tests.
template <typename T> bool feq(const T lhs, const T rhs);
template <typename T> bool feq(const T lhs, const T rhs, const T eps);
bool feq(const int lhs, const int rhs);

// Approximate zero tests.
template <typename T> bool fz(const T lhs);
template <typename T> bool fz(const T lhs, const T eps);
bool fz(const int lhs);


//
// Miscellaneous.
//

// Return the minimum signed finite value for a given type.
template <typename T> T signed_min()        { return std::numeric_limits<T>::min(); }
template <> inline float signed_min()       { return -std::numeric_limits<float>::max(); }
template <> inline double signed_min()      { return -std::numeric_limits<double>::max(); }
template <> inline long double signed_min() { return -std::numeric_limits<long double>::max(); }


//
// Conversion operations implementation.
//

template <>
inline float deg_to_rad(const float angle)
{
    return angle * (Pi<float>() / 180.0f);
}

template <>
inline double deg_to_rad(const double angle)
{
    return angle * (Pi<double>() / 180.0);
}

template <>
inline long double deg_to_rad(const long double angle)
{
    return angle * (Pi<long double>() / 180.0);
}

template <>
inline float rad_to_deg(const float angle)
{
    return angle * (180.0f / Pi<float>());
}

template <>
inline double rad_to_deg(const double angle)
{
    return angle * (180.0 / Pi<double>());
}

template <>
inline long double rad_to_deg(const long double angle)
{
    return angle * (180.0 / Pi<long double>());
}


//
// Arithmetic operations implementation.
//

template <typename T>
inline T abs(const T x)
{
    return x < T(0) ? -x : x;
}

template <typename T>
inline T square(const T x)
{
    return x * x;
}

template <typename T>
inline T cube(const T x)
{
    return x * x * x;
}

template <typename T>
inline T rcp(const T x)
{
    return T(1.0) / x;
}

template <typename T, size_t P>
struct PowIntHelper
{
    static T eval(const T x)
    {
        // Reference: http://en.wikipedia.org/wiki/Exponentiation_by_squaring
        if (P % 2 == 0)
            return PowIntHelper<T, P / 2>::eval(x * x);
        else
            return x * PowIntHelper<T, (P - 1) / 2>::eval(x * x);
    }
};

template <typename T>
struct PowIntHelper<T, 0>
{
    static T eval(const T x)
    {
        return T(1);
    }
};

template <size_t P, typename T>
inline T pow_int(const T x)
{
    return PowIntHelper<T, P>::eval(x);
}

template <typename T>
inline T pow_int(T x, size_t p)
{
    // Reference: http://en.wikipedia.org/wiki/Exponentiation_by_squaring

    T y = T(1);

    while (p)
    {
        if (p % 2 == 0)
        {
            x *= x;
            p /= 2;
        }
        else
        {
            y *= x;
            x *= x;
            p = (p - 1) / 2;
        }
    }

    return y;
}

template <typename T>
inline T next_pow2(T x)
{
    assert(x > 0);
    --x;
    x |= x >> 16;
    x |= x >> 8;
    x |= x >> 4;
    x |= x >> 2;
    x |= x >> 1;
    return x + 1;
}

template <>
inline int64 next_pow2<int64>(int64 x)
{
    assert(x > 0);
    --x;
    x |= x >> 32;
    x |= x >> 16;
    x |= x >> 8;
    x |= x >> 4;
    x |= x >> 2;
    x |= x >> 1;
    return x + 1;
}

template <>
inline uint64 next_pow2<uint64>(uint64 x)
{
    assert(x > 0);
    --x;
    x |= x >> 32;
    x |= x >> 16;
    x |= x >> 8;
    x |= x >> 4;
    x |= x >> 2;
    x |= x >> 1;
    return x + 1;
}

template <typename T>
inline bool is_pow2(const T x)
{
    return (x & (x - 1)) == 0;
}

template <typename T>
inline T log2_int(T x)
{
    assert(x > 0);

    T n = 0;

    while (x >>= 1)
        ++n;

    return n;
}

// Visual C++.
#if defined _MSC_VER

template <>
inline uint32 log2_int(const uint32 x)
{
    assert(x > 0);

    unsigned long index;
    _BitScanReverse(&index, x);

    return static_cast<uint32>(index);
}

#ifdef APPLESEED_ARCH64

template <>
inline uint64 log2_int(const uint64 x)
{
    assert(x > 0);

    unsigned long index;
    _BitScanReverse64(&index, x);

    return static_cast<uint64>(index);
}

#endif

// gcc.
#elif defined __GNUC__

template <>
inline unsigned int log2_int(const unsigned int x)
{
    assert(x > 0);
    return 8 * sizeof(unsigned int) - __builtin_clz(x) - 1;
}

template <>
inline unsigned long log2_int(const unsigned long x)
{
    assert(x > 0);
    return 8 * sizeof(unsigned long) - __builtin_clzl(x) - 1;
}

#endif

template <typename T>
inline T log(const T x, const T base)
{
    return std::log(x) / std::log(base);
}

template <typename T>
inline T next_power(const T x, const T base)
{
    return std::pow(base, fast_ceil(log(x, base)));
}

template <typename T>
inline T next_multiple(const T n, const T m)
{
    assert(n >= 0);
    assert(m > 0);
    return (n + m - 1) / m * m;
}

template <typename T>
inline T prev_multiple(const T n, const T m)
{
    assert(n >= 0);
    assert(m > 0);
    return n - n % m;
}

template <typename T>
inline T factorial(T x)
{
    assert(x >= 0);

    T fac = 1;

    while (x > 1)
    {
        fac *= x;
        --x;
    }

    return fac;
}

template <typename T>
inline T binomial(const T n, const T k)
{
    assert(k <= n);
    return factorial(n) / (factorial(k) * factorial(n - k));
}

template <typename T>
inline T clamp(const T x, const T low, const T high)
{
    assert(low <= high);
    return x < low ? low :
           x > high ? high :
           x;
}

template <typename T>
inline T saturate(const T x)
{
    return clamp(x, T(0.0), T(1.0));
}

template <typename T>
inline T wrap(const T x)
{
    const T y = std::fmod(x, T(1.0));
    return y < T(0.0) ? y + T(1.0) : y;
}

template <typename T>
inline T normalize_angle(const T angle)
{
    const T a = std::fmod(angle, TwoPi<T>());
    return a < T(0.0) ? a + TwoPi<T>() : a;
}

template <typename Int, typename T>
inline Int truncate(const T x)
{
    return static_cast<Int>(x);
}

#ifdef APPLESEED_USE_SSE

template <>
inline int8 truncate<int8>(const float x)
{
    return static_cast<int8>(_mm_cvttss_si32(_mm_load_ss(&x)));
}

template <>
inline int16 truncate<int16>(const float x)
{
    return static_cast<int16>(_mm_cvttss_si32(_mm_load_ss(&x)));
}

template <>
inline int32 truncate<int32>(const float x)
{
    return static_cast<int32>(_mm_cvttss_si32(_mm_load_ss(&x)));
}

template <>
inline int64 truncate<int64>(const float x)
{
    return static_cast<int64>(_mm_cvttss_si32(_mm_load_ss(&x)));
}

template <>
inline int8 truncate<int8>(const double x)
{
    return static_cast<int8>(_mm_cvttsd_si32(_mm_load_sd(&x)));
}

template <>
inline int16 truncate<int16>(const double x)
{
    return static_cast<int16>(_mm_cvttsd_si32(_mm_load_sd(&x)));
}

template <>
inline int32 truncate<int32>(const double x)
{
    return static_cast<int32>(_mm_cvttsd_si32(_mm_load_sd(&x)));
}

template <>
inline int64 truncate<int64>(const double x)
{
    return static_cast<int64>(_mm_cvttsd_si32(_mm_load_sd(&x)));
}

#endif

template <typename T>
inline T fast_floor(const T x)
{
    return std::floor(x);
}

template <typename T>
inline T fast_ceil(const T x)
{
    return std::ceil(x);
}

#ifdef APPLESEED_USE_SSE42

template <>
inline float fast_floor(const float x)
{
    M128Fields f;
    f.m128 = _mm_floor_ss(_mm_set1_ps(x), _mm_set1_ps(x));
    return f.f32[0];
}

template <>
inline double fast_floor(const double x)
{
    M128Fields f;
    f.m128d = _mm_floor_sd(_mm_set1_pd(x), _mm_set1_pd(x));
    return f.f64[0];
}

template <>
inline float fast_ceil(const float x)
{
    M128Fields f;
    f.m128 = _mm_ceil_ss(_mm_set1_ps(x), _mm_set1_ps(x));
    return f.f32[0];
}

template <>
inline double fast_ceil(const double x)
{
    M128Fields f;
    f.m128d = _mm_ceil_sd(_mm_set1_pd(x), _mm_set1_pd(x));
    return f.f64[0];
}

#endif

template <typename Int, typename T>
inline Int round(const T x)
{
    return truncate<Int>(x < T(0.0) ? x - T(0.5) : x + T(0.5));
}

template <typename T>
inline T mod(const T a, const T n)
{
    const T m = a % n;
    return m < 0 ? n + m : m;
}

template <>
inline float mod(const float a, const float n)
{
    const float m = std::fmod(a, n);
    return m < 0.0f ? n + m : m;
}

template <>
inline double mod(const double a, const double n)
{
    const double m = std::fmod(a, n);
    return m < 0.0 ? n + m : m;
}

#pragma warning (push)
#pragma warning (disable : 4146)    // unary minus operator applied to unsigned type, result still unsigned

inline uint32 rotl32(const uint32 n, unsigned int shift)
{
    const unsigned int Mask = 8 * sizeof(n) - 1;
    assert(shift <= Mask);

#ifdef _MSC_VER
    return _rotl(n, shift);
#else
    shift &= Mask;
    return (n << shift) | (n >> ((-shift) & Mask));
#endif
}

inline uint64 rotl64(const uint64 n, unsigned int shift)
{
    const unsigned int Mask = 8 * sizeof(n) - 1;
    assert(shift <= Mask);

#ifdef _MSC_VER
    return _rotl64(n, shift);
#else
    shift &= Mask;
    return (n << shift) | (n >> ((-shift) & Mask));
#endif
}

inline uint32 rotr32(const uint32 n, unsigned int shift)
{
    const unsigned int Mask = 8 * sizeof(n) - 1;
    assert(shift <= Mask);

#ifdef _MSC_VER
    return _rotr(n, shift);
#else
    shift &= Mask;
    return (n >> shift) | (n << ((-shift) & Mask));
#endif
}

inline uint64 rotr64(const uint64 n, unsigned int shift)
{
    const unsigned int Mask = 8 * sizeof(n) - 1;
    assert(shift <= Mask);

#ifdef _MSC_VER
    return _rotr64(n, shift);
#else
    shift &= Mask;
    return (n >> shift) | (n << ((-shift) & Mask));
#endif
}

#pragma warning (pop)

template <typename T>
inline T linearstep(const T a, const T b, const T x)
{
    assert(a < b);
    return x <= a ? T(0.0) :
           x >= b ? T(1.0) :
           (x - a) / (b - a);
}

template <typename T>
inline T smoothstep(const T a, const T b, const T x)
{
    assert(a < b);

    if (x <= a) return T(0.0);
    if (x >= b) return T(1.0);

    const T y = (x - a) / (b - a);
    return y * y * (T(3.0) - y - y);
}

template <typename T, typename U>
inline T mix(const T a, const T b, const U x)
{
    return x <= U(0.0) ? a :
           x >= U(1.0) ? b :
           lerp(a, b, x);
}

template <typename T, typename U>
inline T lerp(const T a, const T b, const U x)
{
    return (U(1.0) - x) * a + x * b;
}

template <typename T, typename U>
inline T inverse_lerp(const T a, const T b, const U x)
{
    assert(a != b);
    
    return (x - a) / (b - a);
}

template <typename T>
inline T fit(
    const T x,
    const T min_x,
    const T max_x,
    const T min_y,
    const T max_y)
{
    assert(min_x != max_x);

    const T k = (x - min_x) / (max_x - min_x);

    return min_y * (T(1.0) - k) + max_y * k;
}

template <typename U, typename V>
inline V fit(
    const U x,
    const U min_x,
    const U max_x,
    const V min_y,
    const V max_y)
{
    assert(min_x != max_x);

    const V k = static_cast<V>(x - min_x) / (max_x - min_x);

    return min_y * (V(1.0) - k) + max_y * k;
}


//
// Robust floating-point tests implementation.
//

template <typename T>
inline bool feq(const T lhs, const T rhs)
{
    return feq(lhs, rhs, default_eps<T>());
}

template <typename T>
inline bool feq(const T lhs, const T rhs, const T eps)
{
    // Handle case where lhs is exactly +0.0 or -0.0.
    if (lhs == T(0.0))
        return std::abs(rhs) < eps;

    // Handle case where rhs is exactly +0.0 or -0.0.
    if (rhs == T(0.0))
        return std::abs(lhs) < eps;

    const T abs_lhs = std::abs(lhs);
    const T abs_rhs = std::abs(rhs);

    // No equality if lhs/rhs overflows.
    if (abs_rhs < T(1.0) &&
        abs_lhs > abs_rhs * std::numeric_limits<T>::max())
        return false;

    // No equality if lhs/rhs underflows.
    if (abs_rhs > T(1.0) &&
        abs_lhs < abs_rhs * std::numeric_limits<T>::min())
        return false;

    // There is equality if the ratio lhs/rhs is close enough to 1.
    const T ratio = lhs / rhs;
    return ratio >= T(1.0) - eps && ratio <= T(1.0) + eps;
}

inline bool feq(const int lhs, const int rhs)
{
    return lhs == rhs;
}

template <typename T>
inline bool fz(const T lhs)
{
    return fz(lhs, default_eps<T>());
}

template <typename T>
inline bool fz(const T lhs, const T eps)
{
    return std::abs(lhs) < eps;
}

inline bool fz(const int lhs)
{
    return lhs == 0;
}

}       // namespace foundation

#endif  // !APPLESEED_FOUNDATION_MATH_SCALAR_H
