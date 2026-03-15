/*
MIT License

Copyright (c) 2026 Himanshu Kumar

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#if !defined(SIKO_MATH_H)
#define SIKO_MATH_H

#ifndef MSTD_H
typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef float  f32;
typedef double f64;

#if _MSC_VER
#define force_inline __forceinline
#elif __clang__ || __GNUC__
#define force_inline __attribute__((always_inline))
#else
#error force_inline not defined for this compiler.
#endif
#endif

typedef union i8vec2 i8vec2;
union i8vec2 {
	i8 data[2];
	struct {
		i8 x;
		i8 y;
	};
};

typedef union i8vec3 i8vec3;
union i8vec3 {
	i8 data[3];
	struct {
		i8 x;
		i8 y;
		i8 z;
	};
};

typedef union i8vec4 i8vec4;
union i8vec4 {
	i8 data[4];
	struct {
		i8 x;
		i8 y;
		i8 z;
		i8 w;
	};
};

typedef union i16vec2 i16vec2;
union i16vec2 {
	i16 data[2];
	struct {
		i16 x;
		i16 y;
	};
};

typedef union i16vec3 i16vec3;
union i16vec3 {
	i16 data[3];
	struct {
		i16 x;
		i16 y;
		i16 z;
	};
};

typedef union i16vec4 i16vec4;
union i16vec4 {
	i16 data[4];
	struct {
		i16 x;
		i16 y;
		i16 z;
		i16 w;
	};
};

typedef union i32vec2 i32vec2;
union i32vec2 {
	i32 data[2];
	struct {
		i32 x;
		i32 y;
	};
};

typedef union i32vec3 i32vec3;
union i32vec3 {
	i32 data[3];
	struct {
		i32 x;
		i32 y;
		i32 z;
	};
};

typedef union i32vec4 i32vec4;
union i32vec4 {
	i32 data[4];
	struct {
		i32 x;
		i32 y;
		i32 z;
		i32 w;
	};
};

typedef union i64vec2 i64vec2;
union i64vec2 {
	i64 data[2];
	struct {
		i64 x;
		i64 y;
	};
};

typedef union i64vec3 i64vec3;
union i64vec3 {
	i64 data[3];
	struct {
		i64 x;
		i64 y;
		i64 z;
	};
};

typedef union i64vec4 i64vec4;
union i64vec4 {
	i64 data[4];
	struct {
		i64 x;
		i64 y;
		i64 z;
		i64 w;
	};
};

typedef union u8vec2 u8vec2;
union u8vec2 {
	u8 data[2];
	struct {
		u8 x;
		u8 y;
	};
};

typedef union u8vec3 u8vec3;
union u8vec3 {
	u8 data[3];
	struct {
		u8 x;
		u8 y;
		u8 z;
	};
};

typedef union u8vec4 u8vec4;
union u8vec4 {
	u8 data[4];
	struct {
		u8 x;
		u8 y;
		u8 z;
		u8 w;
	};
};

typedef union u16vec2 u16vec2;
union u16vec2 {
	u16 data[2];
	struct {
		u16 x;
		u16 y;
	};
};

typedef union u16vec3 u16vec3;
union u16vec3 {
	u16 data[3];
	struct {
		u16 x;
		u16 y;
		u16 z;
	};
};

typedef union u16vec4 u16vec4;
union u16vec4 {
	u16 data[4];
	struct {
		u16 x;
		u16 y;
		u16 z;
		u16 w;
	};
};

typedef union u32vec2 u32vec2;
union u32vec2 {
	u32 data[2];
	struct {
		u32 x;
		u32 y;
	};
};

typedef union u32vec3 u32vec3;
union u32vec3 {
	u32 data[3];
	struct {
		u32 x;
		u32 y;
		u32 z;
	};
};

typedef union u32vec4 u32vec4;
union u32vec4 {
	u32 data[4];
	struct {
		u32 x;
		u32 y;
		u32 z;
		u32 w;
	};
};

typedef union u64vec2 u64vec2;
union u64vec2 {
	u64 data[2];
	struct {
		u64 x;
		u64 y;
	};
};

typedef union u64vec3 u64vec3;
union u64vec3 {
	u64 data[3];
	struct {
		u64 x;
		u64 y;
		u64 z;
	};
};

typedef union u64vec4 u64vec4;
union u64vec4 {
	u64 data[4];
	struct {
		u64 x;
		u64 y;
		u64 z;
		u64 w;
	};
};

typedef union f32vec2 f32vec2;
union f32vec2 {
	f32 data[2];
	struct {
		f32 x;
		f32 y;
	};
};

typedef union f32vec3 f32vec3;
union f32vec3 {
	f32 data[3];
	struct {
		f32 x;
		f32 y;
		f32 z;
	};
};

typedef union f32vec4 f32vec4;
union f32vec4 {
	f32 data[4];
	struct {
		f32 x;
		f32 y;
		f32 z;
		f32 w;
	};
};

typedef union f64vec2 f64vec2;
union f64vec2 {
	f64 data[2];
	struct {
		f64 x;
		f64 y;
	};
};

typedef union f64vec3 f64vec3;
union f64vec3 {
	f64 data[3];
	struct {
		f64 x;
		f64 y;
		f64 z;
	};
};

typedef union f64vec4 f64vec4;
union f64vec4 {
	f64 data[4];
	struct {
		f64 x;
		f64 y;
		f64 z;
		f64 w;
	};
};

static force_inline i8vec2 i8vec2_add(i8vec2 a, i8vec2 b) {
	i8vec2 result;

	for (u8 i = 0; i < 2; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i8vec2 i8vec2_sub(i8vec2 a, i8vec2 b) {
	i8vec2 result;

	for (u8 i = 0; i < 2; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i8vec2 i8vec2_hadamard(i8vec2 a, i8vec2 b) {
	i8vec2 result;

	for (u8 i = 0; i < 2; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i8 i8vec2_dot(i8vec2 a, i8vec2 b) {
	i8 result = a.x * b.x + a.y * b.y;
	return result;
}

static force_inline i8vec2 i8vec2_scale(i8vec2 a, i8 b) {
	i8vec2 result;

	for (u8 i = 0; i < 2; i++) {
		result.data[i] = a.data[i] * b;
	}

	return result;
}

static force_inline i8vec3 i8vec3_add(i8vec3 a, i8vec3 b) {
	i8vec3 result;

	for (u8 i = 0; i < 3; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i8vec3 i8vec3_sub(i8vec3 a, i8vec3 b) {
	i8vec3 result;

	for (u8 i = 0; i < 3; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i8vec3 i8vec3_hadamard(i8vec3 a, i8vec3 b) {
	i8vec3 result;

	for (u8 i = 0; i < 3; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i8 i8vec3_dot(i8vec3 a, i8vec3 b) {
	i8 result = a.x * b.x + a.y * b.y + a.z * b.z;
	return result;
}

static force_inline i8vec3 i8vec3_scale(i8vec3 a, i8 b) {
	i8vec3 result;

	for (u8 i = 0; i < 3; i++) {
		result.data[i] = a.data[i] * b;
	}

	return result;
}

static force_inline i8vec4 i8vec4_add(i8vec4 a, i8vec4 b) {
	i8vec4 result;

	for (u8 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i8vec4 i8vec4_sub(i8vec4 a, i8vec4 b) {
	i8vec4 result;

	for (u8 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i8vec4 i8vec4_hadamard(i8vec4 a, i8vec4 b) {
	i8vec4 result;

	for (u8 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i8 i8vec4_dot(i8vec4 a, i8vec4 b) {
	i8 result = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	return result;
}

static force_inline i8vec4 i8vec4_scale(i8vec4 a, i8 b) {
	i8vec4 result;

	for (u8 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] * b;
	}

	return result;
}

static force_inline i16vec2 i16vec2_add(i16vec2 a, i16vec2 b) {
	i16vec2 result;

	for (u8 i = 0; i < 2; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i16vec2 i16vec2_sub(i16vec2 a, i16vec2 b) {
	i16vec2 result;

	for (u8 i = 0; i < 2; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i16vec2 i16vec2_hadamard(i16vec2 a, i16vec2 b) {
	i16vec2 result;

	for (u8 i = 0; i < 2; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i16 i16vec2_dot(i16vec2 a, i16vec2 b) {
	i16 result = a.x * b.x + a.y * b.y;
	return result;
}

static force_inline i16vec2 i16vec2_scale(i16vec2 a, i16 b) {
	i16vec2 result;

	for (u8 i = 0; i < 2; i++) {
		result.data[i] = a.data[i] * b;
	}

	return result;
}

static force_inline i16vec3 i16vec3_add(i16vec3 a, i16vec3 b) {
	i16vec3 result;

	for (u8 i = 0; i < 3; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i16vec3 i16vec3_sub(i16vec3 a, i16vec3 b) {
	i16vec3 result;

	for (u8 i = 0; i < 3; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i16vec3 i16vec3_hadamard(i16vec3 a, i16vec3 b) {
	i16vec3 result;

	for (u8 i = 0; i < 3; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i16 i16vec3_dot(i16vec3 a, i16vec3 b) {
	i16 result = a.x * b.x + a.y * b.y + a.z * b.z;
	return result;
}

static force_inline i16vec3 i16vec3_scale(i16vec3 a, i16 b) {
	i16vec3 result;

	for (u8 i = 0; i < 3; i++) {
		result.data[i] = a.data[i] * b;
	}

	return result;
}

static force_inline i16vec4 i16vec4_add(i16vec4 a, i16vec4 b) {
	i16vec4 result;

	for (u8 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i16vec4 i16vec4_sub(i16vec4 a, i16vec4 b) {
	i16vec4 result;

	for (u8 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i16vec4 i16vec4_hadamard(i16vec4 a, i16vec4 b) {
	i16vec4 result;

	for (u8 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i16 i16vec4_dot(i16vec4 a, i16vec4 b) {
	i16 result = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	return result;
}

static force_inline i16vec4 i16vec4_scale(i16vec4 a, i16 b) {
	i16vec4 result;

	for (u8 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] * b;
	}

	return result;
}

static force_inline i32vec2 i32vec2_add(i32vec2 a, i32vec2 b) {
	i32vec2 result;

	for (u8 i = 0; i < 2; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i32vec2 i32vec2_sub(i32vec2 a, i32vec2 b) {
	i32vec2 result;

	for (u8 i = 0; i < 2; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i32vec2 i32vec2_hadamard(i32vec2 a, i32vec2 b) {
	i32vec2 result;

	for (u8 i = 0; i < 2; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i32 i32vec2_dot(i32vec2 a, i32vec2 b) {
	i32 result = a.x * b.x + a.y * b.y;
	return result;
}

static force_inline i32vec2 i32vec2_scale(i32vec2 a, i32 b) {
	i32vec2 result;

	for (u8 i = 0; i < 2; i++) {
		result.data[i] = a.data[i] * b;
	}

	return result;
}

static force_inline i32vec3 i32vec3_add(i32vec3 a, i32vec3 b) {
	i32vec3 result;

	for (u8 i = 0; i < 3; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i32vec3 i32vec3_sub(i32vec3 a, i32vec3 b) {
	i32vec3 result;

	for (u8 i = 0; i < 3; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i32vec3 i32vec3_hadamard(i32vec3 a, i32vec3 b) {
	i32vec3 result;

	for (u8 i = 0; i < 3; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i32 i32vec3_dot(i32vec3 a, i32vec3 b) {
	i32 result = a.x * b.x + a.y * b.y + a.z * b.z;
	return result;
}

static force_inline i32vec3 i32vec3_scale(i32vec3 a, i32 b) {
	i32vec3 result;

	for (u8 i = 0; i < 3; i++) {
		result.data[i] = a.data[i] * b;
	}

	return result;
}

static force_inline i32vec4 i32vec4_add(i32vec4 a, i32vec4 b) {
	i32vec4 result;

	for (u8 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i32vec4 i32vec4_sub(i32vec4 a, i32vec4 b) {
	i32vec4 result;

	for (u8 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i32vec4 i32vec4_hadamard(i32vec4 a, i32vec4 b) {
	i32vec4 result;

	for (u8 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i32 i32vec4_dot(i32vec4 a, i32vec4 b) {
	i32 result = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	return result;
}

static force_inline i32vec4 i32vec4_scale(i32vec4 a, i32 b) {
	i32vec4 result;

	for (u8 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] * b;
	}

	return result;
}

static force_inline i64vec2 i64vec2_add(i64vec2 a, i64vec2 b) {
	i64vec2 result;

	for (u8 i = 0; i < 2; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i64vec2 i64vec2_sub(i64vec2 a, i64vec2 b) {
	i64vec2 result;

	for (u8 i = 0; i < 2; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i64vec2 i64vec2_hadamard(i64vec2 a, i64vec2 b) {
	i64vec2 result;

	for (u8 i = 0; i < 2; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i64 i64vec2_dot(i64vec2 a, i64vec2 b) {
	i64 result = a.x * b.x + a.y * b.y;
	return result;
}

static force_inline i64vec2 i64vec2_scale(i64vec2 a, i64 b) {
	i64vec2 result;

	for (u8 i = 0; i < 2; i++) {
		result.data[i] = a.data[i] * b;
	}

	return result;
}

static force_inline i64vec3 i64vec3_add(i64vec3 a, i64vec3 b) {
	i64vec3 result;

	for (u8 i = 0; i < 3; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i64vec3 i64vec3_sub(i64vec3 a, i64vec3 b) {
	i64vec3 result;

	for (u8 i = 0; i < 3; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i64vec3 i64vec3_hadamard(i64vec3 a, i64vec3 b) {
	i64vec3 result;

	for (u8 i = 0; i < 3; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i64 i64vec3_dot(i64vec3 a, i64vec3 b) {
	i64 result = a.x * b.x + a.y * b.y + a.z * b.z;
	return result;
}

static force_inline i64vec3 i64vec3_scale(i64vec3 a, i64 b) {
	i64vec3 result;

	for (u8 i = 0; i < 3; i++) {
		result.data[i] = a.data[i] * b;
	}

	return result;
}

static force_inline i64vec4 i64vec4_add(i64vec4 a, i64vec4 b) {
	i64vec4 result;

	for (u8 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i64vec4 i64vec4_sub(i64vec4 a, i64vec4 b) {
	i64vec4 result;

	for (u8 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i64vec4 i64vec4_hadamard(i64vec4 a, i64vec4 b) {
	i64vec4 result;

	for (u8 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i64 i64vec4_dot(i64vec4 a, i64vec4 b) {
	i64 result = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	return result;
}

static force_inline i64vec4 i64vec4_scale(i64vec4 a, i64 b) {
	i64vec4 result;

	for (u8 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] * b;
	}

	return result;
}

static force_inline u8vec2 u8vec2_add(u8vec2 a, u8vec2 b) {
	u8vec2 result;

	for (u8 i = 0; i < 2; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u8vec2 u8vec2_sub(u8vec2 a, u8vec2 b) {
	u8vec2 result;

	for (u8 i = 0; i < 2; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u8vec2 u8vec2_hadamard(u8vec2 a, u8vec2 b) {
	u8vec2 result;

	for (u8 i = 0; i < 2; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u8 u8vec2_dot(u8vec2 a, u8vec2 b) {
	u8 result = a.x * b.x + a.y * b.y;
	return result;
}

static force_inline u8vec2 u8vec2_scale(u8vec2 a, u8 b) {
	u8vec2 result;

	for (u8 i = 0; i < 2; i++) {
		result.data[i] = a.data[i] * b;
	}

	return result;
}

static force_inline u8vec3 u8vec3_add(u8vec3 a, u8vec3 b) {
	u8vec3 result;

	for (u8 i = 0; i < 3; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u8vec3 u8vec3_sub(u8vec3 a, u8vec3 b) {
	u8vec3 result;

	for (u8 i = 0; i < 3; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u8vec3 u8vec3_hadamard(u8vec3 a, u8vec3 b) {
	u8vec3 result;

	for (u8 i = 0; i < 3; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u8 u8vec3_dot(u8vec3 a, u8vec3 b) {
	u8 result = a.x * b.x + a.y * b.y + a.z * b.z;
	return result;
}

static force_inline u8vec3 u8vec3_scale(u8vec3 a, u8 b) {
	u8vec3 result;

	for (u8 i = 0; i < 3; i++) {
		result.data[i] = a.data[i] * b;
	}

	return result;
}

static force_inline u8vec4 u8vec4_add(u8vec4 a, u8vec4 b) {
	u8vec4 result;

	for (u8 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u8vec4 u8vec4_sub(u8vec4 a, u8vec4 b) {
	u8vec4 result;

	for (u8 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u8vec4 u8vec4_hadamard(u8vec4 a, u8vec4 b) {
	u8vec4 result;

	for (u8 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u8 u8vec4_dot(u8vec4 a, u8vec4 b) {
	u8 result = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	return result;
}

static force_inline u8vec4 u8vec4_scale(u8vec4 a, u8 b) {
	u8vec4 result;

	for (u8 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] * b;
	}

	return result;
}

static force_inline u16vec2 u16vec2_add(u16vec2 a, u16vec2 b) {
	u16vec2 result;

	for (u8 i = 0; i < 2; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u16vec2 u16vec2_sub(u16vec2 a, u16vec2 b) {
	u16vec2 result;

	for (u8 i = 0; i < 2; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u16vec2 u16vec2_hadamard(u16vec2 a, u16vec2 b) {
	u16vec2 result;

	for (u8 i = 0; i < 2; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u16 u16vec2_dot(u16vec2 a, u16vec2 b) {
	u16 result = a.x * b.x + a.y * b.y;
	return result;
}

static force_inline u16vec2 u16vec2_scale(u16vec2 a, u16 b) {
	u16vec2 result;

	for (u8 i = 0; i < 2; i++) {
		result.data[i] = a.data[i] * b;
	}

	return result;
}

static force_inline u16vec3 u16vec3_add(u16vec3 a, u16vec3 b) {
	u16vec3 result;

	for (u8 i = 0; i < 3; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u16vec3 u16vec3_sub(u16vec3 a, u16vec3 b) {
	u16vec3 result;

	for (u8 i = 0; i < 3; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u16vec3 u16vec3_hadamard(u16vec3 a, u16vec3 b) {
	u16vec3 result;

	for (u8 i = 0; i < 3; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u16 u16vec3_dot(u16vec3 a, u16vec3 b) {
	u16 result = a.x * b.x + a.y * b.y + a.z * b.z;
	return result;
}

static force_inline u16vec3 u16vec3_scale(u16vec3 a, u16 b) {
	u16vec3 result;

	for (u8 i = 0; i < 3; i++) {
		result.data[i] = a.data[i] * b;
	}

	return result;
}

static force_inline u16vec4 u16vec4_add(u16vec4 a, u16vec4 b) {
	u16vec4 result;

	for (u8 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u16vec4 u16vec4_sub(u16vec4 a, u16vec4 b) {
	u16vec4 result;

	for (u8 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u16vec4 u16vec4_hadamard(u16vec4 a, u16vec4 b) {
	u16vec4 result;

	for (u8 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u16 u16vec4_dot(u16vec4 a, u16vec4 b) {
	u16 result = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	return result;
}

static force_inline u16vec4 u16vec4_scale(u16vec4 a, u16 b) {
	u16vec4 result;

	for (u8 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] * b;
	}

	return result;
}

static force_inline u32vec2 u32vec2_add(u32vec2 a, u32vec2 b) {
	u32vec2 result;

	for (u8 i = 0; i < 2; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u32vec2 u32vec2_sub(u32vec2 a, u32vec2 b) {
	u32vec2 result;

	for (u8 i = 0; i < 2; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u32vec2 u32vec2_hadamard(u32vec2 a, u32vec2 b) {
	u32vec2 result;

	for (u8 i = 0; i < 2; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u32 u32vec2_dot(u32vec2 a, u32vec2 b) {
	u32 result = a.x * b.x + a.y * b.y;
	return result;
}

static force_inline u32vec2 u32vec2_scale(u32vec2 a, u32 b) {
	u32vec2 result;

	for (u8 i = 0; i < 2; i++) {
		result.data[i] = a.data[i] * b;
	}

	return result;
}

static force_inline u32vec3 u32vec3_add(u32vec3 a, u32vec3 b) {
	u32vec3 result;

	for (u8 i = 0; i < 3; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u32vec3 u32vec3_sub(u32vec3 a, u32vec3 b) {
	u32vec3 result;

	for (u8 i = 0; i < 3; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u32vec3 u32vec3_hadamard(u32vec3 a, u32vec3 b) {
	u32vec3 result;

	for (u8 i = 0; i < 3; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u32 u32vec3_dot(u32vec3 a, u32vec3 b) {
	u32 result = a.x * b.x + a.y * b.y + a.z * b.z;
	return result;
}

static force_inline u32vec3 u32vec3_scale(u32vec3 a, u32 b) {
	u32vec3 result;

	for (u8 i = 0; i < 3; i++) {
		result.data[i] = a.data[i] * b;
	}

	return result;
}

static force_inline u32vec4 u32vec4_add(u32vec4 a, u32vec4 b) {
	u32vec4 result;

	for (u8 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u32vec4 u32vec4_sub(u32vec4 a, u32vec4 b) {
	u32vec4 result;

	for (u8 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u32vec4 u32vec4_hadamard(u32vec4 a, u32vec4 b) {
	u32vec4 result;

	for (u8 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u32 u32vec4_dot(u32vec4 a, u32vec4 b) {
	u32 result = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	return result;
}

static force_inline u32vec4 u32vec4_scale(u32vec4 a, u32 b) {
	u32vec4 result;

	for (u8 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] * b;
	}

	return result;
}

static force_inline u64vec2 u64vec2_add(u64vec2 a, u64vec2 b) {
	u64vec2 result;

	for (u8 i = 0; i < 2; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u64vec2 u64vec2_sub(u64vec2 a, u64vec2 b) {
	u64vec2 result;

	for (u8 i = 0; i < 2; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u64vec2 u64vec2_hadamard(u64vec2 a, u64vec2 b) {
	u64vec2 result;

	for (u8 i = 0; i < 2; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u64 u64vec2_dot(u64vec2 a, u64vec2 b) {
	u64 result = a.x * b.x + a.y * b.y;
	return result;
}

static force_inline u64vec2 u64vec2_scale(u64vec2 a, u64 b) {
	u64vec2 result;

	for (u8 i = 0; i < 2; i++) {
		result.data[i] = a.data[i] * b;
	}

	return result;
}

static force_inline u64vec3 u64vec3_add(u64vec3 a, u64vec3 b) {
	u64vec3 result;

	for (u8 i = 0; i < 3; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u64vec3 u64vec3_sub(u64vec3 a, u64vec3 b) {
	u64vec3 result;

	for (u8 i = 0; i < 3; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u64vec3 u64vec3_hadamard(u64vec3 a, u64vec3 b) {
	u64vec3 result;

	for (u8 i = 0; i < 3; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u64 u64vec3_dot(u64vec3 a, u64vec3 b) {
	u64 result = a.x * b.x + a.y * b.y + a.z * b.z;
	return result;
}

static force_inline u64vec3 u64vec3_scale(u64vec3 a, u64 b) {
	u64vec3 result;

	for (u8 i = 0; i < 3; i++) {
		result.data[i] = a.data[i] * b;
	}

	return result;
}

static force_inline u64vec4 u64vec4_add(u64vec4 a, u64vec4 b) {
	u64vec4 result;

	for (u8 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u64vec4 u64vec4_sub(u64vec4 a, u64vec4 b) {
	u64vec4 result;

	for (u8 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u64vec4 u64vec4_hadamard(u64vec4 a, u64vec4 b) {
	u64vec4 result;

	for (u8 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u64 u64vec4_dot(u64vec4 a, u64vec4 b) {
	u64 result = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	return result;
}

static force_inline u64vec4 u64vec4_scale(u64vec4 a, u64 b) {
	u64vec4 result;

	for (u8 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] * b;
	}

	return result;
}

static force_inline f32vec2 f32vec2_add(f32vec2 a, f32vec2 b) {
	f32vec2 result;

	for (u8 i = 0; i < 2; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline f32vec2 f32vec2_sub(f32vec2 a, f32vec2 b) {
	f32vec2 result;

	for (u8 i = 0; i < 2; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline f32vec2 f32vec2_hadamard(f32vec2 a, f32vec2 b) {
	f32vec2 result;

	for (u8 i = 0; i < 2; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline f32 f32vec2_dot(f32vec2 a, f32vec2 b) {
	f32 result = a.x * b.x + a.y * b.y;
	return result;
}

static force_inline f32vec2 f32vec2_scale(f32vec2 a, f32 b) {
	f32vec2 result;

	for (u8 i = 0; i < 2; i++) {
		result.data[i] = a.data[i] * b;
	}

	return result;
}

static force_inline f32vec3 f32vec3_add(f32vec3 a, f32vec3 b) {
	f32vec3 result;

	for (u8 i = 0; i < 3; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline f32vec3 f32vec3_sub(f32vec3 a, f32vec3 b) {
	f32vec3 result;

	for (u8 i = 0; i < 3; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline f32vec3 f32vec3_hadamard(f32vec3 a, f32vec3 b) {
	f32vec3 result;

	for (u8 i = 0; i < 3; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline f32 f32vec3_dot(f32vec3 a, f32vec3 b) {
	f32 result = a.x * b.x + a.y * b.y + a.z * b.z;
	return result;
}

static force_inline f32vec3 f32vec3_scale(f32vec3 a, f32 b) {
	f32vec3 result;

	for (u8 i = 0; i < 3; i++) {
		result.data[i] = a.data[i] * b;
	}

	return result;
}

static force_inline f32vec4 f32vec4_add(f32vec4 a, f32vec4 b) {
	f32vec4 result;

	for (u8 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline f32vec4 f32vec4_sub(f32vec4 a, f32vec4 b) {
	f32vec4 result;

	for (u8 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline f32vec4 f32vec4_hadamard(f32vec4 a, f32vec4 b) {
	f32vec4 result;

	for (u8 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline f32 f32vec4_dot(f32vec4 a, f32vec4 b) {
	f32 result = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	return result;
}

static force_inline f32vec4 f32vec4_scale(f32vec4 a, f32 b) {
	f32vec4 result;

	for (u8 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] * b;
	}

	return result;
}

static force_inline f64vec2 f64vec2_add(f64vec2 a, f64vec2 b) {
	f64vec2 result;

	for (u8 i = 0; i < 2; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline f64vec2 f64vec2_sub(f64vec2 a, f64vec2 b) {
	f64vec2 result;

	for (u8 i = 0; i < 2; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline f64vec2 f64vec2_hadamard(f64vec2 a, f64vec2 b) {
	f64vec2 result;

	for (u8 i = 0; i < 2; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline f64 f64vec2_dot(f64vec2 a, f64vec2 b) {
	f64 result = a.x * b.x + a.y * b.y;
	return result;
}

static force_inline f64vec2 f64vec2_scale(f64vec2 a, f64 b) {
	f64vec2 result;

	for (u8 i = 0; i < 2; i++) {
		result.data[i] = a.data[i] * b;
	}

	return result;
}

static force_inline f64vec3 f64vec3_add(f64vec3 a, f64vec3 b) {
	f64vec3 result;

	for (u8 i = 0; i < 3; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline f64vec3 f64vec3_sub(f64vec3 a, f64vec3 b) {
	f64vec3 result;

	for (u8 i = 0; i < 3; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline f64vec3 f64vec3_hadamard(f64vec3 a, f64vec3 b) {
	f64vec3 result;

	for (u8 i = 0; i < 3; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline f64 f64vec3_dot(f64vec3 a, f64vec3 b) {
	f64 result = a.x * b.x + a.y * b.y + a.z * b.z;
	return result;
}

static force_inline f64vec3 f64vec3_scale(f64vec3 a, f64 b) {
	f64vec3 result;

	for (u8 i = 0; i < 3; i++) {
		result.data[i] = a.data[i] * b;
	}

	return result;
}

static force_inline f64vec4 f64vec4_add(f64vec4 a, f64vec4 b) {
	f64vec4 result;

	for (u8 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline f64vec4 f64vec4_sub(f64vec4 a, f64vec4 b) {
	f64vec4 result;

	for (u8 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline f64vec4 f64vec4_hadamard(f64vec4 a, f64vec4 b) {
	f64vec4 result;

	for (u8 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline f64 f64vec4_dot(f64vec4 a, f64vec4 b) {
	f64 result = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	return result;
}

static force_inline f64vec4 f64vec4_scale(f64vec4 a, f64 b) {
	f64vec4 result;

	for (u8 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] * b;
	}

	return result;
}

typedef union i8mat2x2 i8mat2x2;
union i8mat2x2 {
	i8 data[4];

	i8 mat[2][2];

	struct {
		i8 _11, _12;
		i8 _21, _22;
	};
};

typedef union i8mat2x3 i8mat2x3;
union i8mat2x3 {
	i8 data[6];

	i8 mat[2][3];

	struct {
		i8 _11, _12, _13;
		i8 _21, _22, _23;
	};
};

typedef union i8mat2x4 i8mat2x4;
union i8mat2x4 {
	i8 data[8];

	i8 mat[2][4];

	struct {
		i8 _11, _12, _13, _14;
		i8 _21, _22, _23, _24;
	};
};

typedef union i8mat3x2 i8mat3x2;
union i8mat3x2 {
	i8 data[6];

	i8 mat[3][2];

	struct {
		i8 _11, _12;
		i8 _21, _22;
		i8 _31, _32;
	};
};

typedef union i8mat3x3 i8mat3x3;
union i8mat3x3 {
	i8 data[9];

	i8 mat[3][3];

	struct {
		i8 _11, _12, _13;
		i8 _21, _22, _23;
		i8 _31, _32, _33;
	};
};

typedef union i8mat3x4 i8mat3x4;
union i8mat3x4 {
	i8 data[12];

	i8 mat[3][4];

	struct {
		i8 _11, _12, _13, _14;
		i8 _21, _22, _23, _24;
		i8 _31, _32, _33, _34;
	};
};

typedef union i8mat4x2 i8mat4x2;
union i8mat4x2 {
	i8 data[8];

	i8 mat[4][2];

	struct {
		i8 _11, _12;
		i8 _21, _22;
		i8 _31, _32;
		i8 _41, _42;
	};
};

typedef union i8mat4x3 i8mat4x3;
union i8mat4x3 {
	i8 data[12];

	i8 mat[4][3];

	struct {
		i8 _11, _12, _13;
		i8 _21, _22, _23;
		i8 _31, _32, _33;
		i8 _41, _42, _43;
	};
};

typedef union i8mat4x4 i8mat4x4;
union i8mat4x4 {
	i8 data[16];

	i8 mat[4][4];

	struct {
		i8 _11, _12, _13, _14;
		i8 _21, _22, _23, _24;
		i8 _31, _32, _33, _34;
		i8 _41, _42, _43, _44;
	};
};

typedef union i16mat2x2 i16mat2x2;
union i16mat2x2 {
	i16 data[4];

	i16 mat[2][2];

	struct {
		i16 _11, _12;
		i16 _21, _22;
	};
};

typedef union i16mat2x3 i16mat2x3;
union i16mat2x3 {
	i16 data[6];

	i16 mat[2][3];

	struct {
		i16 _11, _12, _13;
		i16 _21, _22, _23;
	};
};

typedef union i16mat2x4 i16mat2x4;
union i16mat2x4 {
	i16 data[8];

	i16 mat[2][4];

	struct {
		i16 _11, _12, _13, _14;
		i16 _21, _22, _23, _24;
	};
};

typedef union i16mat3x2 i16mat3x2;
union i16mat3x2 {
	i16 data[6];

	i16 mat[3][2];

	struct {
		i16 _11, _12;
		i16 _21, _22;
		i16 _31, _32;
	};
};

typedef union i16mat3x3 i16mat3x3;
union i16mat3x3 {
	i16 data[9];

	i16 mat[3][3];

	struct {
		i16 _11, _12, _13;
		i16 _21, _22, _23;
		i16 _31, _32, _33;
	};
};

typedef union i16mat3x4 i16mat3x4;
union i16mat3x4 {
	i16 data[12];

	i16 mat[3][4];

	struct {
		i16 _11, _12, _13, _14;
		i16 _21, _22, _23, _24;
		i16 _31, _32, _33, _34;
	};
};

typedef union i16mat4x2 i16mat4x2;
union i16mat4x2 {
	i16 data[8];

	i16 mat[4][2];

	struct {
		i16 _11, _12;
		i16 _21, _22;
		i16 _31, _32;
		i16 _41, _42;
	};
};

typedef union i16mat4x3 i16mat4x3;
union i16mat4x3 {
	i16 data[12];

	i16 mat[4][3];

	struct {
		i16 _11, _12, _13;
		i16 _21, _22, _23;
		i16 _31, _32, _33;
		i16 _41, _42, _43;
	};
};

typedef union i16mat4x4 i16mat4x4;
union i16mat4x4 {
	i16 data[16];

	i16 mat[4][4];

	struct {
		i16 _11, _12, _13, _14;
		i16 _21, _22, _23, _24;
		i16 _31, _32, _33, _34;
		i16 _41, _42, _43, _44;
	};
};

typedef union i32mat2x2 i32mat2x2;
union i32mat2x2 {
	i32 data[4];

	i32 mat[2][2];

	struct {
		i32 _11, _12;
		i32 _21, _22;
	};
};

typedef union i32mat2x3 i32mat2x3;
union i32mat2x3 {
	i32 data[6];

	i32 mat[2][3];

	struct {
		i32 _11, _12, _13;
		i32 _21, _22, _23;
	};
};

typedef union i32mat2x4 i32mat2x4;
union i32mat2x4 {
	i32 data[8];

	i32 mat[2][4];

	struct {
		i32 _11, _12, _13, _14;
		i32 _21, _22, _23, _24;
	};
};

typedef union i32mat3x2 i32mat3x2;
union i32mat3x2 {
	i32 data[6];

	i32 mat[3][2];

	struct {
		i32 _11, _12;
		i32 _21, _22;
		i32 _31, _32;
	};
};

typedef union i32mat3x3 i32mat3x3;
union i32mat3x3 {
	i32 data[9];

	i32 mat[3][3];

	struct {
		i32 _11, _12, _13;
		i32 _21, _22, _23;
		i32 _31, _32, _33;
	};
};

typedef union i32mat3x4 i32mat3x4;
union i32mat3x4 {
	i32 data[12];

	i32 mat[3][4];

	struct {
		i32 _11, _12, _13, _14;
		i32 _21, _22, _23, _24;
		i32 _31, _32, _33, _34;
	};
};

typedef union i32mat4x2 i32mat4x2;
union i32mat4x2 {
	i32 data[8];

	i32 mat[4][2];

	struct {
		i32 _11, _12;
		i32 _21, _22;
		i32 _31, _32;
		i32 _41, _42;
	};
};

typedef union i32mat4x3 i32mat4x3;
union i32mat4x3 {
	i32 data[12];

	i32 mat[4][3];

	struct {
		i32 _11, _12, _13;
		i32 _21, _22, _23;
		i32 _31, _32, _33;
		i32 _41, _42, _43;
	};
};

typedef union i32mat4x4 i32mat4x4;
union i32mat4x4 {
	i32 data[16];

	i32 mat[4][4];

	struct {
		i32 _11, _12, _13, _14;
		i32 _21, _22, _23, _24;
		i32 _31, _32, _33, _34;
		i32 _41, _42, _43, _44;
	};
};

typedef union i64mat2x2 i64mat2x2;
union i64mat2x2 {
	i64 data[4];

	i64 mat[2][2];

	struct {
		i64 _11, _12;
		i64 _21, _22;
	};
};

typedef union i64mat2x3 i64mat2x3;
union i64mat2x3 {
	i64 data[6];

	i64 mat[2][3];

	struct {
		i64 _11, _12, _13;
		i64 _21, _22, _23;
	};
};

typedef union i64mat2x4 i64mat2x4;
union i64mat2x4 {
	i64 data[8];

	i64 mat[2][4];

	struct {
		i64 _11, _12, _13, _14;
		i64 _21, _22, _23, _24;
	};
};

typedef union i64mat3x2 i64mat3x2;
union i64mat3x2 {
	i64 data[6];

	i64 mat[3][2];

	struct {
		i64 _11, _12;
		i64 _21, _22;
		i64 _31, _32;
	};
};

typedef union i64mat3x3 i64mat3x3;
union i64mat3x3 {
	i64 data[9];

	i64 mat[3][3];

	struct {
		i64 _11, _12, _13;
		i64 _21, _22, _23;
		i64 _31, _32, _33;
	};
};

typedef union i64mat3x4 i64mat3x4;
union i64mat3x4 {
	i64 data[12];

	i64 mat[3][4];

	struct {
		i64 _11, _12, _13, _14;
		i64 _21, _22, _23, _24;
		i64 _31, _32, _33, _34;
	};
};

typedef union i64mat4x2 i64mat4x2;
union i64mat4x2 {
	i64 data[8];

	i64 mat[4][2];

	struct {
		i64 _11, _12;
		i64 _21, _22;
		i64 _31, _32;
		i64 _41, _42;
	};
};

typedef union i64mat4x3 i64mat4x3;
union i64mat4x3 {
	i64 data[12];

	i64 mat[4][3];

	struct {
		i64 _11, _12, _13;
		i64 _21, _22, _23;
		i64 _31, _32, _33;
		i64 _41, _42, _43;
	};
};

typedef union i64mat4x4 i64mat4x4;
union i64mat4x4 {
	i64 data[16];

	i64 mat[4][4];

	struct {
		i64 _11, _12, _13, _14;
		i64 _21, _22, _23, _24;
		i64 _31, _32, _33, _34;
		i64 _41, _42, _43, _44;
	};
};

typedef union u8mat2x2 u8mat2x2;
union u8mat2x2 {
	u8 data[4];

	u8 mat[2][2];

	struct {
		u8 _11, _12;
		u8 _21, _22;
	};
};

typedef union u8mat2x3 u8mat2x3;
union u8mat2x3 {
	u8 data[6];

	u8 mat[2][3];

	struct {
		u8 _11, _12, _13;
		u8 _21, _22, _23;
	};
};

typedef union u8mat2x4 u8mat2x4;
union u8mat2x4 {
	u8 data[8];

	u8 mat[2][4];

	struct {
		u8 _11, _12, _13, _14;
		u8 _21, _22, _23, _24;
	};
};

typedef union u8mat3x2 u8mat3x2;
union u8mat3x2 {
	u8 data[6];

	u8 mat[3][2];

	struct {
		u8 _11, _12;
		u8 _21, _22;
		u8 _31, _32;
	};
};

typedef union u8mat3x3 u8mat3x3;
union u8mat3x3 {
	u8 data[9];

	u8 mat[3][3];

	struct {
		u8 _11, _12, _13;
		u8 _21, _22, _23;
		u8 _31, _32, _33;
	};
};

typedef union u8mat3x4 u8mat3x4;
union u8mat3x4 {
	u8 data[12];

	u8 mat[3][4];

	struct {
		u8 _11, _12, _13, _14;
		u8 _21, _22, _23, _24;
		u8 _31, _32, _33, _34;
	};
};

typedef union u8mat4x2 u8mat4x2;
union u8mat4x2 {
	u8 data[8];

	u8 mat[4][2];

	struct {
		u8 _11, _12;
		u8 _21, _22;
		u8 _31, _32;
		u8 _41, _42;
	};
};

typedef union u8mat4x3 u8mat4x3;
union u8mat4x3 {
	u8 data[12];

	u8 mat[4][3];

	struct {
		u8 _11, _12, _13;
		u8 _21, _22, _23;
		u8 _31, _32, _33;
		u8 _41, _42, _43;
	};
};

typedef union u8mat4x4 u8mat4x4;
union u8mat4x4 {
	u8 data[16];

	u8 mat[4][4];

	struct {
		u8 _11, _12, _13, _14;
		u8 _21, _22, _23, _24;
		u8 _31, _32, _33, _34;
		u8 _41, _42, _43, _44;
	};
};

typedef union u16mat2x2 u16mat2x2;
union u16mat2x2 {
	u16 data[4];

	u16 mat[2][2];

	struct {
		u16 _11, _12;
		u16 _21, _22;
	};
};

typedef union u16mat2x3 u16mat2x3;
union u16mat2x3 {
	u16 data[6];

	u16 mat[2][3];

	struct {
		u16 _11, _12, _13;
		u16 _21, _22, _23;
	};
};

typedef union u16mat2x4 u16mat2x4;
union u16mat2x4 {
	u16 data[8];

	u16 mat[2][4];

	struct {
		u16 _11, _12, _13, _14;
		u16 _21, _22, _23, _24;
	};
};

typedef union u16mat3x2 u16mat3x2;
union u16mat3x2 {
	u16 data[6];

	u16 mat[3][2];

	struct {
		u16 _11, _12;
		u16 _21, _22;
		u16 _31, _32;
	};
};

typedef union u16mat3x3 u16mat3x3;
union u16mat3x3 {
	u16 data[9];

	u16 mat[3][3];

	struct {
		u16 _11, _12, _13;
		u16 _21, _22, _23;
		u16 _31, _32, _33;
	};
};

typedef union u16mat3x4 u16mat3x4;
union u16mat3x4 {
	u16 data[12];

	u16 mat[3][4];

	struct {
		u16 _11, _12, _13, _14;
		u16 _21, _22, _23, _24;
		u16 _31, _32, _33, _34;
	};
};

typedef union u16mat4x2 u16mat4x2;
union u16mat4x2 {
	u16 data[8];

	u16 mat[4][2];

	struct {
		u16 _11, _12;
		u16 _21, _22;
		u16 _31, _32;
		u16 _41, _42;
	};
};

typedef union u16mat4x3 u16mat4x3;
union u16mat4x3 {
	u16 data[12];

	u16 mat[4][3];

	struct {
		u16 _11, _12, _13;
		u16 _21, _22, _23;
		u16 _31, _32, _33;
		u16 _41, _42, _43;
	};
};

typedef union u16mat4x4 u16mat4x4;
union u16mat4x4 {
	u16 data[16];

	u16 mat[4][4];

	struct {
		u16 _11, _12, _13, _14;
		u16 _21, _22, _23, _24;
		u16 _31, _32, _33, _34;
		u16 _41, _42, _43, _44;
	};
};

typedef union u32mat2x2 u32mat2x2;
union u32mat2x2 {
	u32 data[4];

	u32 mat[2][2];

	struct {
		u32 _11, _12;
		u32 _21, _22;
	};
};

typedef union u32mat2x3 u32mat2x3;
union u32mat2x3 {
	u32 data[6];

	u32 mat[2][3];

	struct {
		u32 _11, _12, _13;
		u32 _21, _22, _23;
	};
};

typedef union u32mat2x4 u32mat2x4;
union u32mat2x4 {
	u32 data[8];

	u32 mat[2][4];

	struct {
		u32 _11, _12, _13, _14;
		u32 _21, _22, _23, _24;
	};
};

typedef union u32mat3x2 u32mat3x2;
union u32mat3x2 {
	u32 data[6];

	u32 mat[3][2];

	struct {
		u32 _11, _12;
		u32 _21, _22;
		u32 _31, _32;
	};
};

typedef union u32mat3x3 u32mat3x3;
union u32mat3x3 {
	u32 data[9];

	u32 mat[3][3];

	struct {
		u32 _11, _12, _13;
		u32 _21, _22, _23;
		u32 _31, _32, _33;
	};
};

typedef union u32mat3x4 u32mat3x4;
union u32mat3x4 {
	u32 data[12];

	u32 mat[3][4];

	struct {
		u32 _11, _12, _13, _14;
		u32 _21, _22, _23, _24;
		u32 _31, _32, _33, _34;
	};
};

typedef union u32mat4x2 u32mat4x2;
union u32mat4x2 {
	u32 data[8];

	u32 mat[4][2];

	struct {
		u32 _11, _12;
		u32 _21, _22;
		u32 _31, _32;
		u32 _41, _42;
	};
};

typedef union u32mat4x3 u32mat4x3;
union u32mat4x3 {
	u32 data[12];

	u32 mat[4][3];

	struct {
		u32 _11, _12, _13;
		u32 _21, _22, _23;
		u32 _31, _32, _33;
		u32 _41, _42, _43;
	};
};

typedef union u32mat4x4 u32mat4x4;
union u32mat4x4 {
	u32 data[16];

	u32 mat[4][4];

	struct {
		u32 _11, _12, _13, _14;
		u32 _21, _22, _23, _24;
		u32 _31, _32, _33, _34;
		u32 _41, _42, _43, _44;
	};
};

typedef union u64mat2x2 u64mat2x2;
union u64mat2x2 {
	u64 data[4];

	u64 mat[2][2];

	struct {
		u64 _11, _12;
		u64 _21, _22;
	};
};

typedef union u64mat2x3 u64mat2x3;
union u64mat2x3 {
	u64 data[6];

	u64 mat[2][3];

	struct {
		u64 _11, _12, _13;
		u64 _21, _22, _23;
	};
};

typedef union u64mat2x4 u64mat2x4;
union u64mat2x4 {
	u64 data[8];

	u64 mat[2][4];

	struct {
		u64 _11, _12, _13, _14;
		u64 _21, _22, _23, _24;
	};
};

typedef union u64mat3x2 u64mat3x2;
union u64mat3x2 {
	u64 data[6];

	u64 mat[3][2];

	struct {
		u64 _11, _12;
		u64 _21, _22;
		u64 _31, _32;
	};
};

typedef union u64mat3x3 u64mat3x3;
union u64mat3x3 {
	u64 data[9];

	u64 mat[3][3];

	struct {
		u64 _11, _12, _13;
		u64 _21, _22, _23;
		u64 _31, _32, _33;
	};
};

typedef union u64mat3x4 u64mat3x4;
union u64mat3x4 {
	u64 data[12];

	u64 mat[3][4];

	struct {
		u64 _11, _12, _13, _14;
		u64 _21, _22, _23, _24;
		u64 _31, _32, _33, _34;
	};
};

typedef union u64mat4x2 u64mat4x2;
union u64mat4x2 {
	u64 data[8];

	u64 mat[4][2];

	struct {
		u64 _11, _12;
		u64 _21, _22;
		u64 _31, _32;
		u64 _41, _42;
	};
};

typedef union u64mat4x3 u64mat4x3;
union u64mat4x3 {
	u64 data[12];

	u64 mat[4][3];

	struct {
		u64 _11, _12, _13;
		u64 _21, _22, _23;
		u64 _31, _32, _33;
		u64 _41, _42, _43;
	};
};

typedef union u64mat4x4 u64mat4x4;
union u64mat4x4 {
	u64 data[16];

	u64 mat[4][4];

	struct {
		u64 _11, _12, _13, _14;
		u64 _21, _22, _23, _24;
		u64 _31, _32, _33, _34;
		u64 _41, _42, _43, _44;
	};
};

typedef union f32mat2x2 f32mat2x2;
union f32mat2x2 {
	f32 data[4];

	f32 mat[2][2];

	struct {
		f32 _11, _12;
		f32 _21, _22;
	};
};

typedef union f32mat2x3 f32mat2x3;
union f32mat2x3 {
	f32 data[6];

	f32 mat[2][3];

	struct {
		f32 _11, _12, _13;
		f32 _21, _22, _23;
	};
};

typedef union f32mat2x4 f32mat2x4;
union f32mat2x4 {
	f32 data[8];

	f32 mat[2][4];

	struct {
		f32 _11, _12, _13, _14;
		f32 _21, _22, _23, _24;
	};
};

typedef union f32mat3x2 f32mat3x2;
union f32mat3x2 {
	f32 data[6];

	f32 mat[3][2];

	struct {
		f32 _11, _12;
		f32 _21, _22;
		f32 _31, _32;
	};
};

typedef union f32mat3x3 f32mat3x3;
union f32mat3x3 {
	f32 data[9];

	f32 mat[3][3];

	struct {
		f32 _11, _12, _13;
		f32 _21, _22, _23;
		f32 _31, _32, _33;
	};
};

typedef union f32mat3x4 f32mat3x4;
union f32mat3x4 {
	f32 data[12];

	f32 mat[3][4];

	struct {
		f32 _11, _12, _13, _14;
		f32 _21, _22, _23, _24;
		f32 _31, _32, _33, _34;
	};
};

typedef union f32mat4x2 f32mat4x2;
union f32mat4x2 {
	f32 data[8];

	f32 mat[4][2];

	struct {
		f32 _11, _12;
		f32 _21, _22;
		f32 _31, _32;
		f32 _41, _42;
	};
};

typedef union f32mat4x3 f32mat4x3;
union f32mat4x3 {
	f32 data[12];

	f32 mat[4][3];

	struct {
		f32 _11, _12, _13;
		f32 _21, _22, _23;
		f32 _31, _32, _33;
		f32 _41, _42, _43;
	};
};

typedef union f32mat4x4 f32mat4x4;
union f32mat4x4 {
	f32 data[16];

	f32 mat[4][4];

	struct {
		f32 _11, _12, _13, _14;
		f32 _21, _22, _23, _24;
		f32 _31, _32, _33, _34;
		f32 _41, _42, _43, _44;
	};
};

typedef union f64mat2x2 f64mat2x2;
union f64mat2x2 {
	f64 data[4];

	f64 mat[2][2];

	struct {
		f64 _11, _12;
		f64 _21, _22;
	};
};

typedef union f64mat2x3 f64mat2x3;
union f64mat2x3 {
	f64 data[6];

	f64 mat[2][3];

	struct {
		f64 _11, _12, _13;
		f64 _21, _22, _23;
	};
};

typedef union f64mat2x4 f64mat2x4;
union f64mat2x4 {
	f64 data[8];

	f64 mat[2][4];

	struct {
		f64 _11, _12, _13, _14;
		f64 _21, _22, _23, _24;
	};
};

typedef union f64mat3x2 f64mat3x2;
union f64mat3x2 {
	f64 data[6];

	f64 mat[3][2];

	struct {
		f64 _11, _12;
		f64 _21, _22;
		f64 _31, _32;
	};
};

typedef union f64mat3x3 f64mat3x3;
union f64mat3x3 {
	f64 data[9];

	f64 mat[3][3];

	struct {
		f64 _11, _12, _13;
		f64 _21, _22, _23;
		f64 _31, _32, _33;
	};
};

typedef union f64mat3x4 f64mat3x4;
union f64mat3x4 {
	f64 data[12];

	f64 mat[3][4];

	struct {
		f64 _11, _12, _13, _14;
		f64 _21, _22, _23, _24;
		f64 _31, _32, _33, _34;
	};
};

typedef union f64mat4x2 f64mat4x2;
union f64mat4x2 {
	f64 data[8];

	f64 mat[4][2];

	struct {
		f64 _11, _12;
		f64 _21, _22;
		f64 _31, _32;
		f64 _41, _42;
	};
};

typedef union f64mat4x3 f64mat4x3;
union f64mat4x3 {
	f64 data[12];

	f64 mat[4][3];

	struct {
		f64 _11, _12, _13;
		f64 _21, _22, _23;
		f64 _31, _32, _33;
		f64 _41, _42, _43;
	};
};

typedef union f64mat4x4 f64mat4x4;
union f64mat4x4 {
	f64 data[16];

	f64 mat[4][4];

	struct {
		f64 _11, _12, _13, _14;
		f64 _21, _22, _23, _24;
		f64 _31, _32, _33, _34;
		f64 _41, _42, _43, _44;
	};
};

static force_inline i8mat2x2 i8mat2x2_add(i8mat2x2 a, i8mat2x2 b) {
	i8mat2x2 result = {0};

	for(i32 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i8mat2x2 i8mat2x2_sub(i8mat2x2 a, i8mat2x2 b) {
	i8mat2x2 result = {0};

	for(i32 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i8mat2x2 i8mat2x2_hadamard(i8mat2x2 a, i8mat2x2 b) {
	i8mat2x2 result = {0};

	for(i32 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i8mat2x3 i8mat2x3_add(i8mat2x3 a, i8mat2x3 b) {
	i8mat2x3 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i8mat2x3 i8mat2x3_sub(i8mat2x3 a, i8mat2x3 b) {
	i8mat2x3 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i8mat2x3 i8mat2x3_hadamard(i8mat2x3 a, i8mat2x3 b) {
	i8mat2x3 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i8mat2x4 i8mat2x4_add(i8mat2x4 a, i8mat2x4 b) {
	i8mat2x4 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i8mat2x4 i8mat2x4_sub(i8mat2x4 a, i8mat2x4 b) {
	i8mat2x4 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i8mat2x4 i8mat2x4_hadamard(i8mat2x4 a, i8mat2x4 b) {
	i8mat2x4 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i8mat3x2 i8mat3x2_add(i8mat3x2 a, i8mat3x2 b) {
	i8mat3x2 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i8mat3x2 i8mat3x2_sub(i8mat3x2 a, i8mat3x2 b) {
	i8mat3x2 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i8mat3x2 i8mat3x2_hadamard(i8mat3x2 a, i8mat3x2 b) {
	i8mat3x2 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i8mat3x3 i8mat3x3_add(i8mat3x3 a, i8mat3x3 b) {
	i8mat3x3 result = {0};

	for(i32 i = 0; i < 9; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i8mat3x3 i8mat3x3_sub(i8mat3x3 a, i8mat3x3 b) {
	i8mat3x3 result = {0};

	for(i32 i = 0; i < 9; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i8mat3x3 i8mat3x3_hadamard(i8mat3x3 a, i8mat3x3 b) {
	i8mat3x3 result = {0};

	for(i32 i = 0; i < 9; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i8mat3x4 i8mat3x4_add(i8mat3x4 a, i8mat3x4 b) {
	i8mat3x4 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i8mat3x4 i8mat3x4_sub(i8mat3x4 a, i8mat3x4 b) {
	i8mat3x4 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i8mat3x4 i8mat3x4_hadamard(i8mat3x4 a, i8mat3x4 b) {
	i8mat3x4 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i8mat4x2 i8mat4x2_add(i8mat4x2 a, i8mat4x2 b) {
	i8mat4x2 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i8mat4x2 i8mat4x2_sub(i8mat4x2 a, i8mat4x2 b) {
	i8mat4x2 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i8mat4x2 i8mat4x2_hadamard(i8mat4x2 a, i8mat4x2 b) {
	i8mat4x2 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i8mat4x3 i8mat4x3_add(i8mat4x3 a, i8mat4x3 b) {
	i8mat4x3 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i8mat4x3 i8mat4x3_sub(i8mat4x3 a, i8mat4x3 b) {
	i8mat4x3 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i8mat4x3 i8mat4x3_hadamard(i8mat4x3 a, i8mat4x3 b) {
	i8mat4x3 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i8mat4x4 i8mat4x4_add(i8mat4x4 a, i8mat4x4 b) {
	i8mat4x4 result = {0};

	for(i32 i = 0; i < 16; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i8mat4x4 i8mat4x4_sub(i8mat4x4 a, i8mat4x4 b) {
	i8mat4x4 result = {0};

	for(i32 i = 0; i < 16; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i8mat4x4 i8mat4x4_hadamard(i8mat4x4 a, i8mat4x4 b) {
	i8mat4x4 result = {0};

	for(i32 i = 0; i < 16; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i16mat2x2 i16mat2x2_add(i16mat2x2 a, i16mat2x2 b) {
	i16mat2x2 result = {0};

	for(i32 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i16mat2x2 i16mat2x2_sub(i16mat2x2 a, i16mat2x2 b) {
	i16mat2x2 result = {0};

	for(i32 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i16mat2x2 i16mat2x2_hadamard(i16mat2x2 a, i16mat2x2 b) {
	i16mat2x2 result = {0};

	for(i32 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i16mat2x3 i16mat2x3_add(i16mat2x3 a, i16mat2x3 b) {
	i16mat2x3 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i16mat2x3 i16mat2x3_sub(i16mat2x3 a, i16mat2x3 b) {
	i16mat2x3 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i16mat2x3 i16mat2x3_hadamard(i16mat2x3 a, i16mat2x3 b) {
	i16mat2x3 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i16mat2x4 i16mat2x4_add(i16mat2x4 a, i16mat2x4 b) {
	i16mat2x4 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i16mat2x4 i16mat2x4_sub(i16mat2x4 a, i16mat2x4 b) {
	i16mat2x4 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i16mat2x4 i16mat2x4_hadamard(i16mat2x4 a, i16mat2x4 b) {
	i16mat2x4 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i16mat3x2 i16mat3x2_add(i16mat3x2 a, i16mat3x2 b) {
	i16mat3x2 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i16mat3x2 i16mat3x2_sub(i16mat3x2 a, i16mat3x2 b) {
	i16mat3x2 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i16mat3x2 i16mat3x2_hadamard(i16mat3x2 a, i16mat3x2 b) {
	i16mat3x2 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i16mat3x3 i16mat3x3_add(i16mat3x3 a, i16mat3x3 b) {
	i16mat3x3 result = {0};

	for(i32 i = 0; i < 9; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i16mat3x3 i16mat3x3_sub(i16mat3x3 a, i16mat3x3 b) {
	i16mat3x3 result = {0};

	for(i32 i = 0; i < 9; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i16mat3x3 i16mat3x3_hadamard(i16mat3x3 a, i16mat3x3 b) {
	i16mat3x3 result = {0};

	for(i32 i = 0; i < 9; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i16mat3x4 i16mat3x4_add(i16mat3x4 a, i16mat3x4 b) {
	i16mat3x4 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i16mat3x4 i16mat3x4_sub(i16mat3x4 a, i16mat3x4 b) {
	i16mat3x4 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i16mat3x4 i16mat3x4_hadamard(i16mat3x4 a, i16mat3x4 b) {
	i16mat3x4 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i16mat4x2 i16mat4x2_add(i16mat4x2 a, i16mat4x2 b) {
	i16mat4x2 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i16mat4x2 i16mat4x2_sub(i16mat4x2 a, i16mat4x2 b) {
	i16mat4x2 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i16mat4x2 i16mat4x2_hadamard(i16mat4x2 a, i16mat4x2 b) {
	i16mat4x2 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i16mat4x3 i16mat4x3_add(i16mat4x3 a, i16mat4x3 b) {
	i16mat4x3 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i16mat4x3 i16mat4x3_sub(i16mat4x3 a, i16mat4x3 b) {
	i16mat4x3 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i16mat4x3 i16mat4x3_hadamard(i16mat4x3 a, i16mat4x3 b) {
	i16mat4x3 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i16mat4x4 i16mat4x4_add(i16mat4x4 a, i16mat4x4 b) {
	i16mat4x4 result = {0};

	for(i32 i = 0; i < 16; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i16mat4x4 i16mat4x4_sub(i16mat4x4 a, i16mat4x4 b) {
	i16mat4x4 result = {0};

	for(i32 i = 0; i < 16; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i16mat4x4 i16mat4x4_hadamard(i16mat4x4 a, i16mat4x4 b) {
	i16mat4x4 result = {0};

	for(i32 i = 0; i < 16; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i32mat2x2 i32mat2x2_add(i32mat2x2 a, i32mat2x2 b) {
	i32mat2x2 result = {0};

	for(i32 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i32mat2x2 i32mat2x2_sub(i32mat2x2 a, i32mat2x2 b) {
	i32mat2x2 result = {0};

	for(i32 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i32mat2x2 i32mat2x2_hadamard(i32mat2x2 a, i32mat2x2 b) {
	i32mat2x2 result = {0};

	for(i32 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i32mat2x3 i32mat2x3_add(i32mat2x3 a, i32mat2x3 b) {
	i32mat2x3 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i32mat2x3 i32mat2x3_sub(i32mat2x3 a, i32mat2x3 b) {
	i32mat2x3 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i32mat2x3 i32mat2x3_hadamard(i32mat2x3 a, i32mat2x3 b) {
	i32mat2x3 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i32mat2x4 i32mat2x4_add(i32mat2x4 a, i32mat2x4 b) {
	i32mat2x4 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i32mat2x4 i32mat2x4_sub(i32mat2x4 a, i32mat2x4 b) {
	i32mat2x4 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i32mat2x4 i32mat2x4_hadamard(i32mat2x4 a, i32mat2x4 b) {
	i32mat2x4 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i32mat3x2 i32mat3x2_add(i32mat3x2 a, i32mat3x2 b) {
	i32mat3x2 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i32mat3x2 i32mat3x2_sub(i32mat3x2 a, i32mat3x2 b) {
	i32mat3x2 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i32mat3x2 i32mat3x2_hadamard(i32mat3x2 a, i32mat3x2 b) {
	i32mat3x2 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i32mat3x3 i32mat3x3_add(i32mat3x3 a, i32mat3x3 b) {
	i32mat3x3 result = {0};

	for(i32 i = 0; i < 9; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i32mat3x3 i32mat3x3_sub(i32mat3x3 a, i32mat3x3 b) {
	i32mat3x3 result = {0};

	for(i32 i = 0; i < 9; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i32mat3x3 i32mat3x3_hadamard(i32mat3x3 a, i32mat3x3 b) {
	i32mat3x3 result = {0};

	for(i32 i = 0; i < 9; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i32mat3x4 i32mat3x4_add(i32mat3x4 a, i32mat3x4 b) {
	i32mat3x4 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i32mat3x4 i32mat3x4_sub(i32mat3x4 a, i32mat3x4 b) {
	i32mat3x4 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i32mat3x4 i32mat3x4_hadamard(i32mat3x4 a, i32mat3x4 b) {
	i32mat3x4 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i32mat4x2 i32mat4x2_add(i32mat4x2 a, i32mat4x2 b) {
	i32mat4x2 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i32mat4x2 i32mat4x2_sub(i32mat4x2 a, i32mat4x2 b) {
	i32mat4x2 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i32mat4x2 i32mat4x2_hadamard(i32mat4x2 a, i32mat4x2 b) {
	i32mat4x2 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i32mat4x3 i32mat4x3_add(i32mat4x3 a, i32mat4x3 b) {
	i32mat4x3 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i32mat4x3 i32mat4x3_sub(i32mat4x3 a, i32mat4x3 b) {
	i32mat4x3 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i32mat4x3 i32mat4x3_hadamard(i32mat4x3 a, i32mat4x3 b) {
	i32mat4x3 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i32mat4x4 i32mat4x4_add(i32mat4x4 a, i32mat4x4 b) {
	i32mat4x4 result = {0};

	for(i32 i = 0; i < 16; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i32mat4x4 i32mat4x4_sub(i32mat4x4 a, i32mat4x4 b) {
	i32mat4x4 result = {0};

	for(i32 i = 0; i < 16; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i32mat4x4 i32mat4x4_hadamard(i32mat4x4 a, i32mat4x4 b) {
	i32mat4x4 result = {0};

	for(i32 i = 0; i < 16; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i64mat2x2 i64mat2x2_add(i64mat2x2 a, i64mat2x2 b) {
	i64mat2x2 result = {0};

	for(i32 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i64mat2x2 i64mat2x2_sub(i64mat2x2 a, i64mat2x2 b) {
	i64mat2x2 result = {0};

	for(i32 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i64mat2x2 i64mat2x2_hadamard(i64mat2x2 a, i64mat2x2 b) {
	i64mat2x2 result = {0};

	for(i32 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i64mat2x3 i64mat2x3_add(i64mat2x3 a, i64mat2x3 b) {
	i64mat2x3 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i64mat2x3 i64mat2x3_sub(i64mat2x3 a, i64mat2x3 b) {
	i64mat2x3 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i64mat2x3 i64mat2x3_hadamard(i64mat2x3 a, i64mat2x3 b) {
	i64mat2x3 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i64mat2x4 i64mat2x4_add(i64mat2x4 a, i64mat2x4 b) {
	i64mat2x4 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i64mat2x4 i64mat2x4_sub(i64mat2x4 a, i64mat2x4 b) {
	i64mat2x4 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i64mat2x4 i64mat2x4_hadamard(i64mat2x4 a, i64mat2x4 b) {
	i64mat2x4 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i64mat3x2 i64mat3x2_add(i64mat3x2 a, i64mat3x2 b) {
	i64mat3x2 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i64mat3x2 i64mat3x2_sub(i64mat3x2 a, i64mat3x2 b) {
	i64mat3x2 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i64mat3x2 i64mat3x2_hadamard(i64mat3x2 a, i64mat3x2 b) {
	i64mat3x2 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i64mat3x3 i64mat3x3_add(i64mat3x3 a, i64mat3x3 b) {
	i64mat3x3 result = {0};

	for(i32 i = 0; i < 9; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i64mat3x3 i64mat3x3_sub(i64mat3x3 a, i64mat3x3 b) {
	i64mat3x3 result = {0};

	for(i32 i = 0; i < 9; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i64mat3x3 i64mat3x3_hadamard(i64mat3x3 a, i64mat3x3 b) {
	i64mat3x3 result = {0};

	for(i32 i = 0; i < 9; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i64mat3x4 i64mat3x4_add(i64mat3x4 a, i64mat3x4 b) {
	i64mat3x4 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i64mat3x4 i64mat3x4_sub(i64mat3x4 a, i64mat3x4 b) {
	i64mat3x4 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i64mat3x4 i64mat3x4_hadamard(i64mat3x4 a, i64mat3x4 b) {
	i64mat3x4 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i64mat4x2 i64mat4x2_add(i64mat4x2 a, i64mat4x2 b) {
	i64mat4x2 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i64mat4x2 i64mat4x2_sub(i64mat4x2 a, i64mat4x2 b) {
	i64mat4x2 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i64mat4x2 i64mat4x2_hadamard(i64mat4x2 a, i64mat4x2 b) {
	i64mat4x2 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i64mat4x3 i64mat4x3_add(i64mat4x3 a, i64mat4x3 b) {
	i64mat4x3 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i64mat4x3 i64mat4x3_sub(i64mat4x3 a, i64mat4x3 b) {
	i64mat4x3 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i64mat4x3 i64mat4x3_hadamard(i64mat4x3 a, i64mat4x3 b) {
	i64mat4x3 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline i64mat4x4 i64mat4x4_add(i64mat4x4 a, i64mat4x4 b) {
	i64mat4x4 result = {0};

	for(i32 i = 0; i < 16; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline i64mat4x4 i64mat4x4_sub(i64mat4x4 a, i64mat4x4 b) {
	i64mat4x4 result = {0};

	for(i32 i = 0; i < 16; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline i64mat4x4 i64mat4x4_hadamard(i64mat4x4 a, i64mat4x4 b) {
	i64mat4x4 result = {0};

	for(i32 i = 0; i < 16; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u8mat2x2 u8mat2x2_add(u8mat2x2 a, u8mat2x2 b) {
	u8mat2x2 result = {0};

	for(i32 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u8mat2x2 u8mat2x2_sub(u8mat2x2 a, u8mat2x2 b) {
	u8mat2x2 result = {0};

	for(i32 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u8mat2x2 u8mat2x2_hadamard(u8mat2x2 a, u8mat2x2 b) {
	u8mat2x2 result = {0};

	for(i32 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u8mat2x3 u8mat2x3_add(u8mat2x3 a, u8mat2x3 b) {
	u8mat2x3 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u8mat2x3 u8mat2x3_sub(u8mat2x3 a, u8mat2x3 b) {
	u8mat2x3 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u8mat2x3 u8mat2x3_hadamard(u8mat2x3 a, u8mat2x3 b) {
	u8mat2x3 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u8mat2x4 u8mat2x4_add(u8mat2x4 a, u8mat2x4 b) {
	u8mat2x4 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u8mat2x4 u8mat2x4_sub(u8mat2x4 a, u8mat2x4 b) {
	u8mat2x4 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u8mat2x4 u8mat2x4_hadamard(u8mat2x4 a, u8mat2x4 b) {
	u8mat2x4 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u8mat3x2 u8mat3x2_add(u8mat3x2 a, u8mat3x2 b) {
	u8mat3x2 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u8mat3x2 u8mat3x2_sub(u8mat3x2 a, u8mat3x2 b) {
	u8mat3x2 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u8mat3x2 u8mat3x2_hadamard(u8mat3x2 a, u8mat3x2 b) {
	u8mat3x2 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u8mat3x3 u8mat3x3_add(u8mat3x3 a, u8mat3x3 b) {
	u8mat3x3 result = {0};

	for(i32 i = 0; i < 9; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u8mat3x3 u8mat3x3_sub(u8mat3x3 a, u8mat3x3 b) {
	u8mat3x3 result = {0};

	for(i32 i = 0; i < 9; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u8mat3x3 u8mat3x3_hadamard(u8mat3x3 a, u8mat3x3 b) {
	u8mat3x3 result = {0};

	for(i32 i = 0; i < 9; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u8mat3x4 u8mat3x4_add(u8mat3x4 a, u8mat3x4 b) {
	u8mat3x4 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u8mat3x4 u8mat3x4_sub(u8mat3x4 a, u8mat3x4 b) {
	u8mat3x4 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u8mat3x4 u8mat3x4_hadamard(u8mat3x4 a, u8mat3x4 b) {
	u8mat3x4 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u8mat4x2 u8mat4x2_add(u8mat4x2 a, u8mat4x2 b) {
	u8mat4x2 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u8mat4x2 u8mat4x2_sub(u8mat4x2 a, u8mat4x2 b) {
	u8mat4x2 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u8mat4x2 u8mat4x2_hadamard(u8mat4x2 a, u8mat4x2 b) {
	u8mat4x2 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u8mat4x3 u8mat4x3_add(u8mat4x3 a, u8mat4x3 b) {
	u8mat4x3 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u8mat4x3 u8mat4x3_sub(u8mat4x3 a, u8mat4x3 b) {
	u8mat4x3 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u8mat4x3 u8mat4x3_hadamard(u8mat4x3 a, u8mat4x3 b) {
	u8mat4x3 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u8mat4x4 u8mat4x4_add(u8mat4x4 a, u8mat4x4 b) {
	u8mat4x4 result = {0};

	for(i32 i = 0; i < 16; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u8mat4x4 u8mat4x4_sub(u8mat4x4 a, u8mat4x4 b) {
	u8mat4x4 result = {0};

	for(i32 i = 0; i < 16; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u8mat4x4 u8mat4x4_hadamard(u8mat4x4 a, u8mat4x4 b) {
	u8mat4x4 result = {0};

	for(i32 i = 0; i < 16; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u16mat2x2 u16mat2x2_add(u16mat2x2 a, u16mat2x2 b) {
	u16mat2x2 result = {0};

	for(i32 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u16mat2x2 u16mat2x2_sub(u16mat2x2 a, u16mat2x2 b) {
	u16mat2x2 result = {0};

	for(i32 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u16mat2x2 u16mat2x2_hadamard(u16mat2x2 a, u16mat2x2 b) {
	u16mat2x2 result = {0};

	for(i32 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u16mat2x3 u16mat2x3_add(u16mat2x3 a, u16mat2x3 b) {
	u16mat2x3 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u16mat2x3 u16mat2x3_sub(u16mat2x3 a, u16mat2x3 b) {
	u16mat2x3 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u16mat2x3 u16mat2x3_hadamard(u16mat2x3 a, u16mat2x3 b) {
	u16mat2x3 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u16mat2x4 u16mat2x4_add(u16mat2x4 a, u16mat2x4 b) {
	u16mat2x4 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u16mat2x4 u16mat2x4_sub(u16mat2x4 a, u16mat2x4 b) {
	u16mat2x4 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u16mat2x4 u16mat2x4_hadamard(u16mat2x4 a, u16mat2x4 b) {
	u16mat2x4 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u16mat3x2 u16mat3x2_add(u16mat3x2 a, u16mat3x2 b) {
	u16mat3x2 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u16mat3x2 u16mat3x2_sub(u16mat3x2 a, u16mat3x2 b) {
	u16mat3x2 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u16mat3x2 u16mat3x2_hadamard(u16mat3x2 a, u16mat3x2 b) {
	u16mat3x2 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u16mat3x3 u16mat3x3_add(u16mat3x3 a, u16mat3x3 b) {
	u16mat3x3 result = {0};

	for(i32 i = 0; i < 9; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u16mat3x3 u16mat3x3_sub(u16mat3x3 a, u16mat3x3 b) {
	u16mat3x3 result = {0};

	for(i32 i = 0; i < 9; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u16mat3x3 u16mat3x3_hadamard(u16mat3x3 a, u16mat3x3 b) {
	u16mat3x3 result = {0};

	for(i32 i = 0; i < 9; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u16mat3x4 u16mat3x4_add(u16mat3x4 a, u16mat3x4 b) {
	u16mat3x4 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u16mat3x4 u16mat3x4_sub(u16mat3x4 a, u16mat3x4 b) {
	u16mat3x4 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u16mat3x4 u16mat3x4_hadamard(u16mat3x4 a, u16mat3x4 b) {
	u16mat3x4 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u16mat4x2 u16mat4x2_add(u16mat4x2 a, u16mat4x2 b) {
	u16mat4x2 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u16mat4x2 u16mat4x2_sub(u16mat4x2 a, u16mat4x2 b) {
	u16mat4x2 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u16mat4x2 u16mat4x2_hadamard(u16mat4x2 a, u16mat4x2 b) {
	u16mat4x2 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u16mat4x3 u16mat4x3_add(u16mat4x3 a, u16mat4x3 b) {
	u16mat4x3 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u16mat4x3 u16mat4x3_sub(u16mat4x3 a, u16mat4x3 b) {
	u16mat4x3 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u16mat4x3 u16mat4x3_hadamard(u16mat4x3 a, u16mat4x3 b) {
	u16mat4x3 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u16mat4x4 u16mat4x4_add(u16mat4x4 a, u16mat4x4 b) {
	u16mat4x4 result = {0};

	for(i32 i = 0; i < 16; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u16mat4x4 u16mat4x4_sub(u16mat4x4 a, u16mat4x4 b) {
	u16mat4x4 result = {0};

	for(i32 i = 0; i < 16; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u16mat4x4 u16mat4x4_hadamard(u16mat4x4 a, u16mat4x4 b) {
	u16mat4x4 result = {0};

	for(i32 i = 0; i < 16; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u32mat2x2 u32mat2x2_add(u32mat2x2 a, u32mat2x2 b) {
	u32mat2x2 result = {0};

	for(i32 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u32mat2x2 u32mat2x2_sub(u32mat2x2 a, u32mat2x2 b) {
	u32mat2x2 result = {0};

	for(i32 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u32mat2x2 u32mat2x2_hadamard(u32mat2x2 a, u32mat2x2 b) {
	u32mat2x2 result = {0};

	for(i32 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u32mat2x3 u32mat2x3_add(u32mat2x3 a, u32mat2x3 b) {
	u32mat2x3 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u32mat2x3 u32mat2x3_sub(u32mat2x3 a, u32mat2x3 b) {
	u32mat2x3 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u32mat2x3 u32mat2x3_hadamard(u32mat2x3 a, u32mat2x3 b) {
	u32mat2x3 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u32mat2x4 u32mat2x4_add(u32mat2x4 a, u32mat2x4 b) {
	u32mat2x4 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u32mat2x4 u32mat2x4_sub(u32mat2x4 a, u32mat2x4 b) {
	u32mat2x4 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u32mat2x4 u32mat2x4_hadamard(u32mat2x4 a, u32mat2x4 b) {
	u32mat2x4 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u32mat3x2 u32mat3x2_add(u32mat3x2 a, u32mat3x2 b) {
	u32mat3x2 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u32mat3x2 u32mat3x2_sub(u32mat3x2 a, u32mat3x2 b) {
	u32mat3x2 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u32mat3x2 u32mat3x2_hadamard(u32mat3x2 a, u32mat3x2 b) {
	u32mat3x2 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u32mat3x3 u32mat3x3_add(u32mat3x3 a, u32mat3x3 b) {
	u32mat3x3 result = {0};

	for(i32 i = 0; i < 9; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u32mat3x3 u32mat3x3_sub(u32mat3x3 a, u32mat3x3 b) {
	u32mat3x3 result = {0};

	for(i32 i = 0; i < 9; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u32mat3x3 u32mat3x3_hadamard(u32mat3x3 a, u32mat3x3 b) {
	u32mat3x3 result = {0};

	for(i32 i = 0; i < 9; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u32mat3x4 u32mat3x4_add(u32mat3x4 a, u32mat3x4 b) {
	u32mat3x4 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u32mat3x4 u32mat3x4_sub(u32mat3x4 a, u32mat3x4 b) {
	u32mat3x4 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u32mat3x4 u32mat3x4_hadamard(u32mat3x4 a, u32mat3x4 b) {
	u32mat3x4 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u32mat4x2 u32mat4x2_add(u32mat4x2 a, u32mat4x2 b) {
	u32mat4x2 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u32mat4x2 u32mat4x2_sub(u32mat4x2 a, u32mat4x2 b) {
	u32mat4x2 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u32mat4x2 u32mat4x2_hadamard(u32mat4x2 a, u32mat4x2 b) {
	u32mat4x2 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u32mat4x3 u32mat4x3_add(u32mat4x3 a, u32mat4x3 b) {
	u32mat4x3 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u32mat4x3 u32mat4x3_sub(u32mat4x3 a, u32mat4x3 b) {
	u32mat4x3 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u32mat4x3 u32mat4x3_hadamard(u32mat4x3 a, u32mat4x3 b) {
	u32mat4x3 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u32mat4x4 u32mat4x4_add(u32mat4x4 a, u32mat4x4 b) {
	u32mat4x4 result = {0};

	for(i32 i = 0; i < 16; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u32mat4x4 u32mat4x4_sub(u32mat4x4 a, u32mat4x4 b) {
	u32mat4x4 result = {0};

	for(i32 i = 0; i < 16; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u32mat4x4 u32mat4x4_hadamard(u32mat4x4 a, u32mat4x4 b) {
	u32mat4x4 result = {0};

	for(i32 i = 0; i < 16; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u64mat2x2 u64mat2x2_add(u64mat2x2 a, u64mat2x2 b) {
	u64mat2x2 result = {0};

	for(i32 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u64mat2x2 u64mat2x2_sub(u64mat2x2 a, u64mat2x2 b) {
	u64mat2x2 result = {0};

	for(i32 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u64mat2x2 u64mat2x2_hadamard(u64mat2x2 a, u64mat2x2 b) {
	u64mat2x2 result = {0};

	for(i32 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u64mat2x3 u64mat2x3_add(u64mat2x3 a, u64mat2x3 b) {
	u64mat2x3 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u64mat2x3 u64mat2x3_sub(u64mat2x3 a, u64mat2x3 b) {
	u64mat2x3 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u64mat2x3 u64mat2x3_hadamard(u64mat2x3 a, u64mat2x3 b) {
	u64mat2x3 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u64mat2x4 u64mat2x4_add(u64mat2x4 a, u64mat2x4 b) {
	u64mat2x4 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u64mat2x4 u64mat2x4_sub(u64mat2x4 a, u64mat2x4 b) {
	u64mat2x4 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u64mat2x4 u64mat2x4_hadamard(u64mat2x4 a, u64mat2x4 b) {
	u64mat2x4 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u64mat3x2 u64mat3x2_add(u64mat3x2 a, u64mat3x2 b) {
	u64mat3x2 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u64mat3x2 u64mat3x2_sub(u64mat3x2 a, u64mat3x2 b) {
	u64mat3x2 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u64mat3x2 u64mat3x2_hadamard(u64mat3x2 a, u64mat3x2 b) {
	u64mat3x2 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u64mat3x3 u64mat3x3_add(u64mat3x3 a, u64mat3x3 b) {
	u64mat3x3 result = {0};

	for(i32 i = 0; i < 9; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u64mat3x3 u64mat3x3_sub(u64mat3x3 a, u64mat3x3 b) {
	u64mat3x3 result = {0};

	for(i32 i = 0; i < 9; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u64mat3x3 u64mat3x3_hadamard(u64mat3x3 a, u64mat3x3 b) {
	u64mat3x3 result = {0};

	for(i32 i = 0; i < 9; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u64mat3x4 u64mat3x4_add(u64mat3x4 a, u64mat3x4 b) {
	u64mat3x4 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u64mat3x4 u64mat3x4_sub(u64mat3x4 a, u64mat3x4 b) {
	u64mat3x4 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u64mat3x4 u64mat3x4_hadamard(u64mat3x4 a, u64mat3x4 b) {
	u64mat3x4 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u64mat4x2 u64mat4x2_add(u64mat4x2 a, u64mat4x2 b) {
	u64mat4x2 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u64mat4x2 u64mat4x2_sub(u64mat4x2 a, u64mat4x2 b) {
	u64mat4x2 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u64mat4x2 u64mat4x2_hadamard(u64mat4x2 a, u64mat4x2 b) {
	u64mat4x2 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u64mat4x3 u64mat4x3_add(u64mat4x3 a, u64mat4x3 b) {
	u64mat4x3 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u64mat4x3 u64mat4x3_sub(u64mat4x3 a, u64mat4x3 b) {
	u64mat4x3 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u64mat4x3 u64mat4x3_hadamard(u64mat4x3 a, u64mat4x3 b) {
	u64mat4x3 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline u64mat4x4 u64mat4x4_add(u64mat4x4 a, u64mat4x4 b) {
	u64mat4x4 result = {0};

	for(i32 i = 0; i < 16; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline u64mat4x4 u64mat4x4_sub(u64mat4x4 a, u64mat4x4 b) {
	u64mat4x4 result = {0};

	for(i32 i = 0; i < 16; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline u64mat4x4 u64mat4x4_hadamard(u64mat4x4 a, u64mat4x4 b) {
	u64mat4x4 result = {0};

	for(i32 i = 0; i < 16; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline f32mat2x2 f32mat2x2_add(f32mat2x2 a, f32mat2x2 b) {
	f32mat2x2 result = {0};

	for(i32 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline f32mat2x2 f32mat2x2_sub(f32mat2x2 a, f32mat2x2 b) {
	f32mat2x2 result = {0};

	for(i32 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline f32mat2x2 f32mat2x2_hadamard(f32mat2x2 a, f32mat2x2 b) {
	f32mat2x2 result = {0};

	for(i32 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline f32mat2x3 f32mat2x3_add(f32mat2x3 a, f32mat2x3 b) {
	f32mat2x3 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline f32mat2x3 f32mat2x3_sub(f32mat2x3 a, f32mat2x3 b) {
	f32mat2x3 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline f32mat2x3 f32mat2x3_hadamard(f32mat2x3 a, f32mat2x3 b) {
	f32mat2x3 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline f32mat2x4 f32mat2x4_add(f32mat2x4 a, f32mat2x4 b) {
	f32mat2x4 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline f32mat2x4 f32mat2x4_sub(f32mat2x4 a, f32mat2x4 b) {
	f32mat2x4 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline f32mat2x4 f32mat2x4_hadamard(f32mat2x4 a, f32mat2x4 b) {
	f32mat2x4 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline f32mat3x2 f32mat3x2_add(f32mat3x2 a, f32mat3x2 b) {
	f32mat3x2 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline f32mat3x2 f32mat3x2_sub(f32mat3x2 a, f32mat3x2 b) {
	f32mat3x2 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline f32mat3x2 f32mat3x2_hadamard(f32mat3x2 a, f32mat3x2 b) {
	f32mat3x2 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline f32mat3x3 f32mat3x3_add(f32mat3x3 a, f32mat3x3 b) {
	f32mat3x3 result = {0};

	for(i32 i = 0; i < 9; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline f32mat3x3 f32mat3x3_sub(f32mat3x3 a, f32mat3x3 b) {
	f32mat3x3 result = {0};

	for(i32 i = 0; i < 9; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline f32mat3x3 f32mat3x3_hadamard(f32mat3x3 a, f32mat3x3 b) {
	f32mat3x3 result = {0};

	for(i32 i = 0; i < 9; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline f32mat3x4 f32mat3x4_add(f32mat3x4 a, f32mat3x4 b) {
	f32mat3x4 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline f32mat3x4 f32mat3x4_sub(f32mat3x4 a, f32mat3x4 b) {
	f32mat3x4 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline f32mat3x4 f32mat3x4_hadamard(f32mat3x4 a, f32mat3x4 b) {
	f32mat3x4 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline f32mat4x2 f32mat4x2_add(f32mat4x2 a, f32mat4x2 b) {
	f32mat4x2 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline f32mat4x2 f32mat4x2_sub(f32mat4x2 a, f32mat4x2 b) {
	f32mat4x2 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline f32mat4x2 f32mat4x2_hadamard(f32mat4x2 a, f32mat4x2 b) {
	f32mat4x2 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline f32mat4x3 f32mat4x3_add(f32mat4x3 a, f32mat4x3 b) {
	f32mat4x3 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline f32mat4x3 f32mat4x3_sub(f32mat4x3 a, f32mat4x3 b) {
	f32mat4x3 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline f32mat4x3 f32mat4x3_hadamard(f32mat4x3 a, f32mat4x3 b) {
	f32mat4x3 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline f32mat4x4 f32mat4x4_add(f32mat4x4 a, f32mat4x4 b) {
	f32mat4x4 result = {0};

	for(i32 i = 0; i < 16; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline f32mat4x4 f32mat4x4_sub(f32mat4x4 a, f32mat4x4 b) {
	f32mat4x4 result = {0};

	for(i32 i = 0; i < 16; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline f32mat4x4 f32mat4x4_hadamard(f32mat4x4 a, f32mat4x4 b) {
	f32mat4x4 result = {0};

	for(i32 i = 0; i < 16; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline f64mat2x2 f64mat2x2_add(f64mat2x2 a, f64mat2x2 b) {
	f64mat2x2 result = {0};

	for(i32 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline f64mat2x2 f64mat2x2_sub(f64mat2x2 a, f64mat2x2 b) {
	f64mat2x2 result = {0};

	for(i32 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline f64mat2x2 f64mat2x2_hadamard(f64mat2x2 a, f64mat2x2 b) {
	f64mat2x2 result = {0};

	for(i32 i = 0; i < 4; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline f64mat2x3 f64mat2x3_add(f64mat2x3 a, f64mat2x3 b) {
	f64mat2x3 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline f64mat2x3 f64mat2x3_sub(f64mat2x3 a, f64mat2x3 b) {
	f64mat2x3 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline f64mat2x3 f64mat2x3_hadamard(f64mat2x3 a, f64mat2x3 b) {
	f64mat2x3 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline f64mat2x4 f64mat2x4_add(f64mat2x4 a, f64mat2x4 b) {
	f64mat2x4 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline f64mat2x4 f64mat2x4_sub(f64mat2x4 a, f64mat2x4 b) {
	f64mat2x4 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline f64mat2x4 f64mat2x4_hadamard(f64mat2x4 a, f64mat2x4 b) {
	f64mat2x4 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline f64mat3x2 f64mat3x2_add(f64mat3x2 a, f64mat3x2 b) {
	f64mat3x2 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline f64mat3x2 f64mat3x2_sub(f64mat3x2 a, f64mat3x2 b) {
	f64mat3x2 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline f64mat3x2 f64mat3x2_hadamard(f64mat3x2 a, f64mat3x2 b) {
	f64mat3x2 result = {0};

	for(i32 i = 0; i < 6; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline f64mat3x3 f64mat3x3_add(f64mat3x3 a, f64mat3x3 b) {
	f64mat3x3 result = {0};

	for(i32 i = 0; i < 9; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline f64mat3x3 f64mat3x3_sub(f64mat3x3 a, f64mat3x3 b) {
	f64mat3x3 result = {0};

	for(i32 i = 0; i < 9; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline f64mat3x3 f64mat3x3_hadamard(f64mat3x3 a, f64mat3x3 b) {
	f64mat3x3 result = {0};

	for(i32 i = 0; i < 9; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline f64mat3x4 f64mat3x4_add(f64mat3x4 a, f64mat3x4 b) {
	f64mat3x4 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline f64mat3x4 f64mat3x4_sub(f64mat3x4 a, f64mat3x4 b) {
	f64mat3x4 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline f64mat3x4 f64mat3x4_hadamard(f64mat3x4 a, f64mat3x4 b) {
	f64mat3x4 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline f64mat4x2 f64mat4x2_add(f64mat4x2 a, f64mat4x2 b) {
	f64mat4x2 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline f64mat4x2 f64mat4x2_sub(f64mat4x2 a, f64mat4x2 b) {
	f64mat4x2 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline f64mat4x2 f64mat4x2_hadamard(f64mat4x2 a, f64mat4x2 b) {
	f64mat4x2 result = {0};

	for(i32 i = 0; i < 8; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline f64mat4x3 f64mat4x3_add(f64mat4x3 a, f64mat4x3 b) {
	f64mat4x3 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline f64mat4x3 f64mat4x3_sub(f64mat4x3 a, f64mat4x3 b) {
	f64mat4x3 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline f64mat4x3 f64mat4x3_hadamard(f64mat4x3 a, f64mat4x3 b) {
	f64mat4x3 result = {0};

	for(i32 i = 0; i < 12; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

static force_inline f64mat4x4 f64mat4x4_add(f64mat4x4 a, f64mat4x4 b) {
	f64mat4x4 result = {0};

	for(i32 i = 0; i < 16; i++) {
		result.data[i] = a.data[i] + b.data[i];
	}

	return result;
}

static force_inline f64mat4x4 f64mat4x4_sub(f64mat4x4 a, f64mat4x4 b) {
	f64mat4x4 result = {0};

	for(i32 i = 0; i < 16; i++) {
		result.data[i] = a.data[i] - b.data[i];
	}

	return result;
}

static force_inline f64mat4x4 f64mat4x4_hadamard(f64mat4x4 a, f64mat4x4 b) {
	f64mat4x4 result = {0};

	for(i32 i = 0; i < 16; i++) {
		result.data[i] = a.data[i] * b.data[i];
	}

	return result;
}

#endif // SIKO_MATH_H