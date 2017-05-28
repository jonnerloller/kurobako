#ifndef SIZEDTYPES_H
#define SIZEDTYPES_H
#include <cstdint>
#include <atomic>
#ifdef _WINDOWS
    using int8 = std::int8_t;
    using int16 = std::int16_t;
    using int32 = std::int32_t;
    using int64 = std::int64_t;
    using uint8 = std::uint8_t;
    using uint16 = std::uint16_t;
    using uint32 = std::uint32_t;
    using uint64 = std::uint64_t;
    using uintptr = std::uintptr_t;
    using atomic_int8 =	    std::atomic<std::int8_t>;
    using atomic_uint8 =	std::atomic<std::uint8_t>;
    using atomic_int16 =	std::atomic<std::int16_t>;
    using atomic_uint16 =	std::atomic<std::uint16_t>;
    using atomic_int32 =	std::atomic<std::int32_t>;
    using atomic_uint32 =	std::atomic<std::uint32_t>;
    using atomic_int64 =	std::atomic<std::int64_t>;
    using atomic_uint64 =   std::atomic<std::uint64_t>;
    using atomic_uintptr =  std::atomic<std::uintptr_t>;
	using f32 = float;
	using f64 = double;
	using cstr = const char*;
	using byte = uint8_t;
#endif // ifdef _WINDOWS

#endif