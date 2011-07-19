/*
**  ClanLib SDK
**  Copyright (c) 1997-2011 The ClanLib Team
**
**  This software is provided 'as-is', without any express or implied
**  warranty.  In no event will the authors be held liable for any damages
**  arising from the use of this software.
**
**  Permission is granted to anyone to use this software for any purpose,
**  including commercial applications, and to alter it and redistribute it
**  freely, subject to the following restrictions:
**
**  1. The origin of this software must not be misrepresented; you must not
**     claim that you wrote the original software. If you use this software
**     in a product, an acknowledgment in the product documentation would be
**     appreciated but is not required.
**  2. Altered source versions must be plainly marked as such, and must not be
**     misrepresented as being the original software.
**  3. This notice may not be removed or altered from any source distribution.
**
**  Note: Some of the libraries ClanLib may link to may have additional
**  requirements or restrictions.
**
**  File Author(s):
**
**    Magnus Norddahl
**    Mark Page
*/

/// \addtogroup clanGL_Display clanGL Display
/// \{

#pragma once
#include "api_gl.h"

#include "../Core/System/cl_platform.h"

#ifdef __APPLE__
#include "AGL/opengl_window_provider_agl.h"
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#else
#include <GL/gl.h>
#endif

#ifndef CL_DISPLAYDEFINES_DEFINES
#define CL_DISPLAYDEFINES_DEFINES

#include <cstddef>

typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef signed char GLbyte;
typedef short GLshort;
typedef int GLint;
typedef int GLsizei;
typedef unsigned char GLubyte;
typedef unsigned short GLushort;
typedef unsigned int GLuint;
typedef cl_long CLint64;
typedef cl_ulong CLuint64;
typedef float GLfloat;
typedef float GLclampf;
typedef double GLdouble;
typedef double GLclampd;
typedef void GLvoid;
typedef char GLchar;
typedef ptrdiff_t GLintptr;
typedef ptrdiff_t GLsizeiptr;
typedef struct __CLsync *CLsync;

typedef void * CLDEBUGPROCARB;

/// \brief Display Defines
///
/// \xmlonly !group=GL/Display! !header=gl.h! \endxmlonly
enum CL_DisplayDefines
{
	// AttribMask
#ifndef GL_DEPTH_BUFFER_BIT
	GL_DEPTH_BUFFER_BIT               = 0x00000100,
	GL_STENCIL_BUFFER_BIT             = 0x00000400,
	GL_COLOR_BUFFER_BIT               = 0x00004000,
	// Boolean
#endif
#ifndef GL_FALSE
	GL_FALSE                          = 0,
	GL_TRUE                           = 1,
	// BeginMode
#endif
#ifndef GL_POINTS
	GL_POINTS                         = 0x0000,
	GL_LINES                          = 0x0001,
	GL_LINE_LOOP                      = 0x0002,
	GL_LINE_STRIP                     = 0x0003,
	GL_TRIANGLES                      = 0x0004,
	GL_TRIANGLE_STRIP                 = 0x0005,
	GL_TRIANGLE_FAN                   = 0x0006,
	// AlphaFunction
#endif
#ifndef GL_NEVER
	GL_NEVER                          = 0x0200,
	GL_LESS                           = 0x0201,
	GL_EQUAL                          = 0x0202,
	GL_LEQUAL                         = 0x0203,
	GL_GREATER                        = 0x0204,
	GL_NOTEQUAL                       = 0x0205,
	GL_GEQUAL                         = 0x0206,
	GL_ALWAYS                         = 0x0207,
	// BlendingFactorDest
#endif
#ifndef GL_ZERO
	GL_ZERO                           = 0,
	GL_ONE                            = 1,
	GL_SRC_COLOR                      = 0x0300,
	GL_ONE_MINUS_SRC_COLOR            = 0x0301,
	GL_SRC_ALPHA                      = 0x0302,
	GL_ONE_MINUS_SRC_ALPHA            = 0x0303,
	GL_DST_ALPHA                      = 0x0304,
	GL_ONE_MINUS_DST_ALPHA            = 0x0305,
	// BlendingFactorSrc
#endif
#ifndef GL_DST_COLOR
	GL_DST_COLOR                      = 0x0306,
	GL_ONE_MINUS_DST_COLOR            = 0x0307,
	GL_SRC_ALPHA_SATURATE             = 0x0308,
	// DrawBufferMode
#endif
#ifndef GL_NONE
	GL_NONE                           = 0,
	GL_FRONT_LEFT                     = 0x0400,
	GL_FRONT_RIGHT                    = 0x0401,
	GL_BACK_LEFT                      = 0x0402,
	GL_BACK_RIGHT                     = 0x0403,
	GL_FRONT                          = 0x0404,
	GL_BACK                           = 0x0405,
	GL_LEFT                           = 0x0406,
	GL_RIGHT                          = 0x0407,
	GL_FRONT_AND_BACK                 = 0x0408,
	// ErrorCode
#endif
#ifndef GL_NO_ERROR
	GL_NO_ERROR                       = 0,
	GL_INVALID_ENUM                   = 0x0500,
	GL_INVALID_VALUE                  = 0x0501,
	GL_INVALID_OPERATION              = 0x0502,
	GL_OUT_OF_MEMORY                  = 0x0505,
	// FrontFaceDirection
#endif
#ifndef GL_CW
	GL_CW                             = 0x0900,
	GL_CCW                            = 0x0901,
	// GetPName
#endif
#ifndef GL_POINT_SIZE
	GL_POINT_SIZE                     = 0x0B11,
	GL_POINT_SIZE_RANGE               = 0x0B12,
	GL_POINT_SIZE_GRANULARITY         = 0x0B13,
	GL_LINE_SMOOTH                    = 0x0B20,
	GL_LINE_WIDTH                     = 0x0B21,
	GL_LINE_WIDTH_RANGE               = 0x0B22,
	GL_LINE_WIDTH_GRANULARITY         = 0x0B23,
	GL_POLYGON_SMOOTH                 = 0x0B41,
	GL_CULL_FACE                      = 0x0B44,
	GL_CULL_FACE_MODE                 = 0x0B45,
	GL_FRONT_FACE                     = 0x0B46,
	GL_DEPTH_RANGE                    = 0x0B70,
	GL_DEPTH_TEST                     = 0x0B71,
	GL_DEPTH_WRITEMASK                = 0x0B72,
	GL_DEPTH_CLEAR_VALUE              = 0x0B73,
	GL_DEPTH_FUNC                     = 0x0B74,
	GL_STENCIL_TEST                   = 0x0B90,
	GL_STENCIL_CLEAR_VALUE            = 0x0B91,
	GL_STENCIL_FUNC                   = 0x0B92,
	GL_STENCIL_VALUE_MASK             = 0x0B93,
	GL_STENCIL_FAIL                   = 0x0B94,
	GL_STENCIL_PASS_DEPTH_FAIL        = 0x0B95,
	GL_STENCIL_PASS_DEPTH_PASS        = 0x0B96,
	GL_STENCIL_REF                    = 0x0B97,
	GL_STENCIL_WRITEMASK              = 0x0B98,
	GL_VIEWPORT                       = 0x0BA2,
	GL_DITHER                         = 0x0BD0,
	GL_BLEND_DST                      = 0x0BE0,
	GL_BLEND_SRC                      = 0x0BE1,
	GL_BLEND                          = 0x0BE2,
	GL_LOGIC_OP_MODE                  = 0x0BF0,
	GL_COLOR_LOGIC_OP                 = 0x0BF2,
	GL_DRAW_BUFFER                    = 0x0C01,
	GL_READ_BUFFER                    = 0x0C02,
	GL_SCISSOR_BOX                    = 0x0C10,
	GL_SCISSOR_TEST                   = 0x0C11,
	GL_COLOR_CLEAR_VALUE              = 0x0C22,
	GL_COLOR_WRITEMASK                = 0x0C23,
	GL_DOUBLEBUFFER                   = 0x0C32,
	GL_STEREO                         = 0x0C33,
	GL_LINE_SMOOTH_HINT               = 0x0C52,
	GL_POLYGON_SMOOTH_HINT            = 0x0C53,
	GL_UNPACK_SWAP_BYTES              = 0x0CF0,
	GL_UNPACK_LSB_FIRST               = 0x0CF1,
	GL_UNPACK_ROW_LENGTH              = 0x0CF2,
	GL_UNPACK_SKIP_ROWS               = 0x0CF3,
	GL_UNPACK_SKIP_PIXELS             = 0x0CF4,
	GL_UNPACK_ALIGNMENT               = 0x0CF5,
	GL_PACK_SWAP_BYTES                = 0x0D00,
	GL_PACK_LSB_FIRST                 = 0x0D01,
	GL_PACK_ROW_LENGTH                = 0x0D02,
	GL_PACK_SKIP_ROWS                 = 0x0D03,
	GL_PACK_SKIP_PIXELS               = 0x0D04,
	GL_PACK_ALIGNMENT                 = 0x0D05,
	GL_MAX_TEXTURE_SIZE               = 0x0D33,
	GL_MAX_VIEWPORT_DIMS              = 0x0D3A,
	GL_SUBPIXEL_BITS                  = 0x0D50,
	GL_TEXTURE_1D                     = 0x0DE0,
	GL_TEXTURE_2D                     = 0x0DE1,
	GL_POLYGON_OFFSET_UNITS           = 0x2A00,
	GL_POLYGON_OFFSET_POINT           = 0x2A01,
	GL_POLYGON_OFFSET_LINE            = 0x2A02,
	GL_POLYGON_OFFSET_FILL            = 0x8037,
	GL_POLYGON_OFFSET_FACTOR          = 0x8038,
	GL_TEXTURE_BINDING_1D             = 0x8068,
	GL_TEXTURE_BINDING_2D             = 0x8069,
	// GetTextureParameter
#endif
#ifndef GL_TEXTURE_WIDTH
	GL_TEXTURE_WIDTH                  = 0x1000,
	GL_TEXTURE_HEIGHT                 = 0x1001,
	GL_TEXTURE_INTERNAL_FORMAT        = 0x1003,
	GL_TEXTURE_BORDER_COLOR           = 0x1004,
	GL_TEXTURE_RED_SIZE               = 0x805C,
	GL_TEXTURE_GREEN_SIZE             = 0x805D,
	GL_TEXTURE_BLUE_SIZE              = 0x805E,
	GL_TEXTURE_ALPHA_SIZE             = 0x805F,
	// HintMode
#endif
#ifndef GL_DONT_CARE
	GL_DONT_CARE                      = 0x1100,
	GL_FASTEST                        = 0x1101,
	GL_NICEST                         = 0x1102,
	// DataType
#endif
#ifndef GL_BYTE
	GL_BYTE                           = 0x1400,
	GL_UNSIGNED_BYTE                  = 0x1401,
	GL_SHORT                          = 0x1402,
	GL_UNSIGNED_SHORT                 = 0x1403,
	GL_INT                            = 0x1404,
	GL_UNSIGNED_INT                   = 0x1405,
	GL_FLOAT                          = 0x1406,
	GL_DOUBLE                         = 0x140A,
	// LogicOp
#endif
#ifndef GL_CLEAR
	GL_CLEAR                          = 0x1500,
	GL_AND                            = 0x1501,
	GL_AND_REVERSE                    = 0x1502,
	GL_COPY                           = 0x1503,
	GL_AND_INVERTED                   = 0x1504,
	GL_NOOP                           = 0x1505,
	GL_XOR                            = 0x1506,
	GL_OR                             = 0x1507,
	GL_NOR                            = 0x1508,
	GL_EQUIV                          = 0x1509,
	GL_INVERT                         = 0x150A,
	GL_OR_REVERSE                     = 0x150B,
	GL_COPY_INVERTED                  = 0x150C,
	GL_OR_INVERTED                    = 0x150D,
	GL_NAND                           = 0x150E,
	GL_SET                            = 0x150F,
	// MatrixMode (for gl3.h, FBO attachment type)
#endif
#ifndef GL_TEXTURE
	GL_TEXTURE                        = 0x1702,
	// PixelCopyType
#endif
#ifndef GL_COLOR
	GL_COLOR                          = 0x1800,
	GL_DEPTH                          = 0x1801,
	GL_STENCIL                        = 0x1802,
	// PixelFormat
#endif
#ifndef GL_STENCIL_INDEX
	GL_STENCIL_INDEX                  = 0x1901,
	GL_DEPTH_COMPONENT                = 0x1902,
	GL_RED                            = 0x1903,
	GL_GREEN                          = 0x1904,
	GL_BLUE                           = 0x1905,
	GL_ALPHA                          = 0x1906,
	GL_RGB                            = 0x1907,
	GL_RGBA                           = 0x1908,
	// PolygonMode
#endif
#ifndef GL_POINT
	GL_POINT                          = 0x1B00,
	GL_LINE                           = 0x1B01,
	GL_FILL                           = 0x1B02,
	// StencilOp
#endif
#ifndef GL_KEEP
	GL_KEEP                           = 0x1E00,
	GL_REPLACE                        = 0x1E01,
	GL_INCR                           = 0x1E02,
	GL_DECR                           = 0x1E03,
	// StringName
#endif
#ifndef GL_VENDOR
	GL_VENDOR                         = 0x1F00,
	GL_RENDERER                       = 0x1F01,
	GL_VERSION                        = 0x1F02,
	GL_EXTENSIONS                     = 0x1F03,
	// TextureMagFilter
#endif
#ifndef GL_NEAREST
	GL_NEAREST                        = 0x2600,
	GL_LINEAR                         = 0x2601,
	// TextureMinFilter
#endif
#ifndef GL_NEAREST_MIPMAP_NEAREST
	GL_NEAREST_MIPMAP_NEAREST         = 0x2700,
	GL_LINEAR_MIPMAP_NEAREST          = 0x2701,
	GL_NEAREST_MIPMAP_LINEAR          = 0x2702,
	GL_LINEAR_MIPMAP_LINEAR           = 0x2703,
	// TextureParameterName
#endif
#ifndef GL_TEXTURE_MAG_FILTER
	GL_TEXTURE_MAG_FILTER             = 0x2800,
	GL_TEXTURE_MIN_FILTER             = 0x2801,
	GL_TEXTURE_WRAP_S                 = 0x2802,
	GL_TEXTURE_WRAP_T                 = 0x2803,
	// TextureTarget
#endif
#ifndef GL_PROXY_TEXTURE_1D
	GL_PROXY_TEXTURE_1D               = 0x8063,
	GL_PROXY_TEXTURE_2D               = 0x8064,
	// TextureWrapMode
#endif
#ifndef GL_REPEAT
	GL_REPEAT                         = 0x2901,
	// PixelInternalFormat
#endif
#ifndef GL_R3_G3_B2
	GL_R3_G3_B2                       = 0x2A10,
	GL_RGB4                           = 0x804F,
	GL_RGB5                           = 0x8050,
	GL_RGB8                           = 0x8051,
	GL_RGB10                          = 0x8052,
	GL_RGB12                          = 0x8053,
	GL_RGB16                          = 0x8054,
	GL_RGBA2                          = 0x8055,
	GL_RGBA4                          = 0x8056,
	GL_RGB5_A1                        = 0x8057,
	GL_RGBA8                          = 0x8058,
	GL_RGB10_A2                       = 0x8059,
	GL_RGBA12                         = 0x805A,
	GL_RGBA16                         = 0x805B,
#endif

#ifndef GL_UNSIGNED_BYTE_3_3_2
	GL_UNSIGNED_BYTE_3_3_2            = 0x8032,
	GL_UNSIGNED_SHORT_4_4_4_4         = 0x8033,
	GL_UNSIGNED_SHORT_5_5_5_1         = 0x8034,
	GL_UNSIGNED_INT_8_8_8_8           = 0x8035,
	GL_UNSIGNED_INT_10_10_10_2        = 0x8036,
	GL_TEXTURE_BINDING_3D             = 0x806A,
	GL_PACK_SKIP_IMAGES               = 0x806B,
	GL_PACK_IMAGE_HEIGHT              = 0x806C,
	GL_UNPACK_SKIP_IMAGES             = 0x806D,
	GL_UNPACK_IMAGE_HEIGHT            = 0x806E,
	GL_TEXTURE_3D                     = 0x806F,
	GL_PROXY_TEXTURE_3D               = 0x8070,
	GL_TEXTURE_DEPTH                  = 0x8071,
	GL_TEXTURE_WRAP_R                 = 0x8072,
	GL_MAX_3D_TEXTURE_SIZE            = 0x8073,
	GL_UNSIGNED_BYTE_2_3_3_REV        = 0x8362,
	GL_UNSIGNED_SHORT_5_6_5           = 0x8363,
	GL_UNSIGNED_SHORT_5_6_5_REV       = 0x8364,
	GL_UNSIGNED_SHORT_4_4_4_4_REV     = 0x8365,
	GL_UNSIGNED_SHORT_1_5_5_5_REV     = 0x8366,
	GL_UNSIGNED_INT_8_8_8_8_REV       = 0x8367,
	GL_UNSIGNED_INT_2_10_10_10_REV    = 0x8368,
	GL_BGR                            = 0x80E0,
	GL_BGRA                           = 0x80E1,
	GL_MAX_ELEMENTS_VERTICES          = 0x80E8,
	GL_MAX_ELEMENTS_INDICES           = 0x80E9,
	GL_CLAMP_TO_EDGE                  = 0x812F,
	GL_TEXTURE_MIN_LOD                = 0x813A,
	GL_TEXTURE_MAX_LOD                = 0x813B,
	GL_TEXTURE_BASE_LEVEL             = 0x813C,
	GL_TEXTURE_MAX_LEVEL              = 0x813D,
	GL_SMOOTH_POINT_SIZE_RANGE        = 0x0B12,
	GL_SMOOTH_POINT_SIZE_GRANULARITY  = 0x0B13,
	GL_SMOOTH_LINE_WIDTH_RANGE        = 0x0B22,
	GL_SMOOTH_LINE_WIDTH_GRANULARITY  = 0x0B23,
	GL_ALIASED_LINE_WIDTH_RANGE       = 0x846E,
#endif

#ifndef GL_CONSTANT_COLOR

	GL_CONSTANT_COLOR                 = 0x8001,
	GL_ONE_MINUS_CONSTANT_COLOR       = 0x8002,
	GL_CONSTANT_ALPHA                 = 0x8003,
	GL_ONE_MINUS_CONSTANT_ALPHA       = 0x8004,
	GL_BLEND_COLOR                    = 0x8005,
	GL_FUNC_ADD                       = 0x8006,
	GL_MIN                            = 0x8007,
	GL_MAX                            = 0x8008,
	GL_BLEND_EQUATION                 = 0x8009,
	GL_FUNC_SUBTRACT                  = 0x800A,
	GL_FUNC_REVERSE_SUBTRACT          = 0x800B,
#endif

#ifndef GL_TEXTURE0

	GL_TEXTURE0                       = 0x84C0,
	GL_TEXTURE1                       = 0x84C1,
	GL_TEXTURE2                       = 0x84C2,
	GL_TEXTURE3                       = 0x84C3,
	GL_TEXTURE4                       = 0x84C4,
	GL_TEXTURE5                       = 0x84C5,
	GL_TEXTURE6                       = 0x84C6,
	GL_TEXTURE7                       = 0x84C7,
	GL_TEXTURE8                       = 0x84C8,
	GL_TEXTURE9                       = 0x84C9,
	GL_TEXTURE10                      = 0x84CA,
	GL_TEXTURE11                      = 0x84CB,
	GL_TEXTURE12                      = 0x84CC,
	GL_TEXTURE13                      = 0x84CD,
	GL_TEXTURE14                      = 0x84CE,
	GL_TEXTURE15                      = 0x84CF,
	GL_TEXTURE16                      = 0x84D0,
	GL_TEXTURE17                      = 0x84D1,
	GL_TEXTURE18                      = 0x84D2,
	GL_TEXTURE19                      = 0x84D3,
	GL_TEXTURE20                      = 0x84D4,
	GL_TEXTURE21                      = 0x84D5,
	GL_TEXTURE22                      = 0x84D6,
	GL_TEXTURE23                      = 0x84D7,
	GL_TEXTURE24                      = 0x84D8,
	GL_TEXTURE25                      = 0x84D9,
	GL_TEXTURE26                      = 0x84DA,
	GL_TEXTURE27                      = 0x84DB,
	GL_TEXTURE28                      = 0x84DC,
	GL_TEXTURE29                      = 0x84DD,
	GL_TEXTURE30                      = 0x84DE,
	GL_TEXTURE31                      = 0x84DF,
	GL_ACTIVE_TEXTURE                 = 0x84E0,
	GL_MULTISAMPLE                    = 0x809D,
	GL_SAMPLE_ALPHA_TO_COVERAGE       = 0x809E,
	GL_SAMPLE_ALPHA_TO_ONE            = 0x809F,
	GL_SAMPLE_COVERAGE                = 0x80A0,
	GL_SAMPLE_BUFFERS                 = 0x80A8,
	GL_SAMPLES                        = 0x80A9,
	GL_SAMPLE_COVERAGE_VALUE          = 0x80AA,
	GL_SAMPLE_COVERAGE_INVERT         = 0x80AB,
	GL_TEXTURE_CUBE_MAP               = 0x8513,
	GL_TEXTURE_BINDING_CUBE_MAP       = 0x8514,
	GL_TEXTURE_CUBE_MAP_POSITIVE_X    = 0x8515,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_X    = 0x8516,
	GL_TEXTURE_CUBE_MAP_POSITIVE_Y    = 0x8517,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Y    = 0x8518,
	GL_TEXTURE_CUBE_MAP_POSITIVE_Z    = 0x8519,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Z    = 0x851A,
	GL_PROXY_TEXTURE_CUBE_MAP         = 0x851B,
	GL_MAX_CUBE_MAP_TEXTURE_SIZE      = 0x851C,
	GL_COMPRESSED_RGB                 = 0x84ED,
	GL_COMPRESSED_RGBA                = 0x84EE,
	GL_TEXTURE_COMPRESSION_HINT       = 0x84EF,
	GL_TEXTURE_COMPRESSED_IMAGE_SIZE  = 0x86A0,
	GL_TEXTURE_COMPRESSED             = 0x86A1,
	GL_NUM_COMPRESSED_TEXTURE_FORMATS = 0x86A2,
	GL_COMPRESSED_TEXTURE_FORMATS     = 0x86A3,
	GL_CLAMP_TO_BORDER                = 0x812D,
#endif

#ifndef GL_BLEND_DST_RGB

	GL_BLEND_DST_RGB                  = 0x80C8,
	GL_BLEND_SRC_RGB                  = 0x80C9,
	GL_BLEND_DST_ALPHA                = 0x80CA,
	GL_BLEND_SRC_ALPHA                = 0x80CB,
	GL_POINT_FADE_THRESHOLD_SIZE      = 0x8128,
	GL_DEPTH_COMPONENT16              = 0x81A5,
	GL_DEPTH_COMPONENT24              = 0x81A6,
	GL_DEPTH_COMPONENT32              = 0x81A7,
	GL_MIRRORED_REPEAT                = 0x8370,
	GL_MAX_TEXTURE_LOD_BIAS           = 0x84FD,
	GL_TEXTURE_LOD_BIAS               = 0x8501,
	GL_INCR_WRAP                      = 0x8507,
	GL_DECR_WRAP                      = 0x8508,
	GL_TEXTURE_DEPTH_SIZE             = 0x884A,
	GL_TEXTURE_COMPARE_MODE           = 0x884C,
	GL_TEXTURE_COMPARE_FUNC           = 0x884D,
#endif

#ifndef GL_BUFFER_SIZE

	GL_BUFFER_SIZE                    = 0x8764,
	GL_BUFFER_USAGE                   = 0x8765,
	GL_QUERY_COUNTER_BITS             = 0x8864,
	GL_CURRENT_QUERY                  = 0x8865,
	GL_QUERY_RESULT                   = 0x8866,
	GL_QUERY_RESULT_AVAILABLE         = 0x8867,
	GL_ARRAY_BUFFER                   = 0x8892,
	GL_ELEMENT_ARRAY_BUFFER           = 0x8893,
	GL_ARRAY_BUFFER_BINDING           = 0x8894,
	GL_ELEMENT_ARRAY_BUFFER_BINDING   = 0x8895,
	GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING = 0x889F,
	GL_READ_ONLY                      = 0x88B8,
	GL_WRITE_ONLY                     = 0x88B9,
	GL_READ_WRITE                     = 0x88BA,
	GL_BUFFER_ACCESS                  = 0x88BB,
	GL_BUFFER_MAPPED                  = 0x88BC,
	GL_BUFFER_MAP_POINTER             = 0x88BD,
	GL_STREAM_DRAW                    = 0x88E0,
	GL_STREAM_READ                    = 0x88E1,
	GL_STREAM_COPY                    = 0x88E2,
	GL_STATIC_DRAW                    = 0x88E4,
	GL_STATIC_READ                    = 0x88E5,
	GL_STATIC_COPY                    = 0x88E6,
	GL_DYNAMIC_DRAW                   = 0x88E8,
	GL_DYNAMIC_READ                   = 0x88E9,
	GL_DYNAMIC_COPY                   = 0x88EA,
	GL_SAMPLES_PASSED                 = 0x8914,
#endif

#ifndef GL_BLEND_EQUATION_RGB

	GL_BLEND_EQUATION_RGB             = 0x8009,
	GL_VERTEX_ATTRIB_ARRAY_ENABLED    = 0x8622,
	GL_VERTEX_ATTRIB_ARRAY_SIZE       = 0x8623,
	GL_VERTEX_ATTRIB_ARRAY_STRIDE     = 0x8624,
	GL_VERTEX_ATTRIB_ARRAY_TYPE       = 0x8625,
	GL_CURRENT_VERTEX_ATTRIB          = 0x8626,
	GL_VERTEX_PROGRAM_POINT_SIZE      = 0x8642,
	GL_VERTEX_ATTRIB_ARRAY_POINTER    = 0x8645,
	GL_STENCIL_BACK_FUNC              = 0x8800,
	GL_STENCIL_BACK_FAIL              = 0x8801,
	GL_STENCIL_BACK_PASS_DEPTH_FAIL   = 0x8802,
	GL_STENCIL_BACK_PASS_DEPTH_PASS   = 0x8803,
	GL_MAX_DRAW_BUFFERS               = 0x8824,
	GL_DRAW_BUFFER0                   = 0x8825,
	GL_DRAW_BUFFER1                   = 0x8826,
	GL_DRAW_BUFFER2                   = 0x8827,
	GL_DRAW_BUFFER3                   = 0x8828,
	GL_DRAW_BUFFER4                   = 0x8829,
	GL_DRAW_BUFFER5                   = 0x882A,
	GL_DRAW_BUFFER6                   = 0x882B,
	GL_DRAW_BUFFER7                   = 0x882C,
	GL_DRAW_BUFFER8                   = 0x882D,
	GL_DRAW_BUFFER9                   = 0x882E,
	GL_DRAW_BUFFER10                  = 0x882F,
	GL_DRAW_BUFFER11                  = 0x8830,
	GL_DRAW_BUFFER12                  = 0x8831,
	GL_DRAW_BUFFER13                  = 0x8832,
	GL_DRAW_BUFFER14                  = 0x8833,
	GL_DRAW_BUFFER15                  = 0x8834,
	GL_BLEND_EQUATION_ALPHA           = 0x883D,
	GL_MAX_VERTEX_ATTRIBS             = 0x8869,
	GL_VERTEX_ATTRIB_ARRAY_NORMALIZED = 0x886A,
	GL_MAX_TEXTURE_IMAGE_UNITS        = 0x8872,
	GL_FRAGMENT_SHADER                = 0x8B30,
	GL_VERTEX_SHADER                  = 0x8B31,
	GL_MAX_FRAGMENT_UNIFORM_COMPONENTS = 0x8B49,
	GL_MAX_VERTEX_UNIFORM_COMPONENTS  = 0x8B4A,
	GL_MAX_VARYING_FLOATS             = 0x8B4B,
	GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS = 0x8B4C,
	GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS = 0x8B4D,
	GL_SHADER_TYPE                    = 0x8B4F,
	GL_FLOAT_VEC2                     = 0x8B50,
	GL_FLOAT_VEC3                     = 0x8B51,
	GL_FLOAT_VEC4                     = 0x8B52,
	GL_INT_VEC2                       = 0x8B53,
	GL_INT_VEC3                       = 0x8B54,
	GL_INT_VEC4                       = 0x8B55,
	GL_BOOL                           = 0x8B56,
	GL_BOOL_VEC2                      = 0x8B57,
	GL_BOOL_VEC3                      = 0x8B58,
	GL_BOOL_VEC4                      = 0x8B59,
	GL_FLOAT_MAT2                     = 0x8B5A,
	GL_FLOAT_MAT3                     = 0x8B5B,
	GL_FLOAT_MAT4                     = 0x8B5C,
	GL_SAMPLER_1D                     = 0x8B5D,
	GL_SAMPLER_2D                     = 0x8B5E,
	GL_SAMPLER_3D                     = 0x8B5F,
	GL_SAMPLER_CUBE                   = 0x8B60,
	GL_SAMPLER_1D_SHADOW              = 0x8B61,
	GL_SAMPLER_2D_SHADOW              = 0x8B62,
	GL_DELETE_STATUS                  = 0x8B80,
	GL_COMPILE_STATUS                 = 0x8B81,
	GL_LINK_STATUS                    = 0x8B82,
	GL_VALIDATE_STATUS                = 0x8B83,
	GL_INFO_LOG_LENGTH                = 0x8B84,
	GL_ATTACHED_SHADERS               = 0x8B85,
	GL_ACTIVE_UNIFORMS                = 0x8B86,
	GL_ACTIVE_UNIFORM_MAX_LENGTH      = 0x8B87,
	GL_SHADER_SOURCE_LENGTH           = 0x8B88,
	GL_ACTIVE_ATTRIBUTES              = 0x8B89,
	GL_ACTIVE_ATTRIBUTE_MAX_LENGTH    = 0x8B8A,
	GL_FRAGMENT_SHADER_DERIVATIVE_HINT = 0x8B8B,
	GL_SHADING_LANGUAGE_VERSION       = 0x8B8C,
	GL_CURRENT_PROGRAM                = 0x8B8D,
	GL_POINT_SPRITE_COORD_ORIGIN      = 0x8CA0,
	GL_LOWER_LEFT                     = 0x8CA1,
	GL_UPPER_LEFT                     = 0x8CA2,
	GL_STENCIL_BACK_REF               = 0x8CA3,
	GL_STENCIL_BACK_VALUE_MASK        = 0x8CA4,
	GL_STENCIL_BACK_WRITEMASK         = 0x8CA5,
#endif

#ifndef GL_PIXEL_PACK_BUFFER

	GL_PIXEL_PACK_BUFFER              = 0x88EB,
	GL_PIXEL_UNPACK_BUFFER            = 0x88EC,
	GL_PIXEL_PACK_BUFFER_BINDING      = 0x88ED,
	GL_PIXEL_UNPACK_BUFFER_BINDING    = 0x88EF,
	GL_FLOAT_MAT2x3                   = 0x8B65,
	GL_FLOAT_MAT2x4                   = 0x8B66,
	GL_FLOAT_MAT3x2                   = 0x8B67,
	GL_FLOAT_MAT3x4                   = 0x8B68,
	GL_FLOAT_MAT4x2                   = 0x8B69,
	GL_FLOAT_MAT4x3                   = 0x8B6A,
	GL_SRGB                           = 0x8C40,
	GL_SRGB8                          = 0x8C41,
	GL_SRGB_ALPHA                     = 0x8C42,
	GL_SRGB8_ALPHA8                   = 0x8C43,
	GL_COMPRESSED_SRGB                = 0x8C48,
	GL_COMPRESSED_SRGB_ALPHA          = 0x8C49,
#endif

#ifndef GL_COMPARE_REF_TO_TEXTURE

	GL_COMPARE_REF_TO_TEXTURE         = 0x884E,
	GL_CLIP_DISTANCE0                 = 0x3000,
	GL_CLIP_DISTANCE1                 = 0x3001,
	GL_CLIP_DISTANCE2                 = 0x3002,
	GL_CLIP_DISTANCE3                 = 0x3003,
	GL_CLIP_DISTANCE4                 = 0x3004,
	GL_CLIP_DISTANCE5                 = 0x3005,
	GL_CLIP_DISTANCE6                 = 0x3006,
	GL_CLIP_DISTANCE7                 = 0x3007,
	GL_MAX_CLIP_DISTANCES             = 0x0D32,
	GL_MAJOR_VERSION                  = 0x821B,
	GL_MINOR_VERSION                  = 0x821C,
	GL_NUM_EXTENSIONS                 = 0x821D,
	GL_CONTEXT_FLAGS                  = 0x821E,
	GL_DEPTH_BUFFER                   = 0x8223,
	GL_STENCIL_BUFFER                 = 0x8224,
	GL_COMPRESSED_RED                 = 0x8225,
	GL_COMPRESSED_RG                  = 0x8226,
	GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT = 0x0001,
	GL_RGBA32F                        = 0x8814,
	GL_RGB32F                         = 0x8815,
	GL_RGBA16F                        = 0x881A,
	GL_RGB16F                         = 0x881B,
	GL_VERTEX_ATTRIB_ARRAY_INTEGER    = 0x88FD,
	GL_MAX_ARRAY_TEXTURE_LAYERS       = 0x88FF,
	GL_MIN_PROGRAM_TEXEL_OFFSET       = 0x8904,
	GL_MAX_PROGRAM_TEXEL_OFFSET       = 0x8905,
	GL_CLAMP_READ_COLOR               = 0x891C,
	GL_FIXED_ONLY                     = 0x891D,
	GL_MAX_VARYING_COMPONENTS         = 0x8B4B,
	GL_TEXTURE_1D_ARRAY               = 0x8C18,
	GL_PROXY_TEXTURE_1D_ARRAY         = 0x8C19,
	GL_TEXTURE_2D_ARRAY               = 0x8C1A,
	GL_PROXY_TEXTURE_2D_ARRAY         = 0x8C1B,
	GL_TEXTURE_BINDING_1D_ARRAY       = 0x8C1C,
	GL_TEXTURE_BINDING_2D_ARRAY       = 0x8C1D,
	GL_R11F_G11F_B10F                 = 0x8C3A,
	GL_UNSIGNED_INT_10F_11F_11F_REV   = 0x8C3B,
	GL_RGB9_E5                        = 0x8C3D,
	GL_UNSIGNED_INT_5_9_9_9_REV       = 0x8C3E,
	GL_TEXTURE_SHARED_SIZE            = 0x8C3F,
	GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH = 0x8C76,
	GL_TRANSFORM_FEEDBACK_BUFFER_MODE = 0x8C7F,
	GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS = 0x8C80,
	GL_TRANSFORM_FEEDBACK_VARYINGS    = 0x8C83,
	GL_TRANSFORM_FEEDBACK_BUFFER_START = 0x8C84,
	GL_TRANSFORM_FEEDBACK_BUFFER_SIZE = 0x8C85,
	GL_PRIMITIVES_GENERATED           = 0x8C87,
	GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN = 0x8C88,
	GL_RASTERIZER_DISCARD             = 0x8C89,
	GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS = 0x8C8A,
	GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS = 0x8C8B,
	GL_INTERLEAVED_ATTRIBS            = 0x8C8C,
	GL_SEPARATE_ATTRIBS               = 0x8C8D,
	GL_TRANSFORM_FEEDBACK_BUFFER      = 0x8C8E,
	GL_TRANSFORM_FEEDBACK_BUFFER_BINDING = 0x8C8F,
	GL_RGBA32UI                       = 0x8D70,
	GL_RGB32UI                        = 0x8D71,
	GL_RGBA16UI                       = 0x8D76,
	GL_RGB16UI                        = 0x8D77,
	GL_RGBA8UI                        = 0x8D7C,
	GL_RGB8UI                         = 0x8D7D,
	GL_RGBA32I                        = 0x8D82,
	GL_RGB32I                         = 0x8D83,
	GL_RGBA16I                        = 0x8D88,
	GL_RGB16I                         = 0x8D89,
	GL_RGBA8I                         = 0x8D8E,
	GL_RGB8I                          = 0x8D8F,
	GL_RED_INTEGER                    = 0x8D94,
	GL_GREEN_INTEGER                  = 0x8D95,
	GL_BLUE_INTEGER                   = 0x8D96,
	GL_RGB_INTEGER                    = 0x8D98,
	GL_RGBA_INTEGER                   = 0x8D99,
	GL_BGR_INTEGER                    = 0x8D9A,
	GL_BGRA_INTEGER                   = 0x8D9B,
	GL_SAMPLER_1D_ARRAY               = 0x8DC0,
	GL_SAMPLER_2D_ARRAY               = 0x8DC1,
	GL_SAMPLER_1D_ARRAY_SHADOW        = 0x8DC3,
	GL_SAMPLER_2D_ARRAY_SHADOW        = 0x8DC4,
	GL_SAMPLER_CUBE_SHADOW            = 0x8DC5,
	GL_UNSIGNED_INT_VEC2              = 0x8DC6,
	GL_UNSIGNED_INT_VEC3              = 0x8DC7,
	GL_UNSIGNED_INT_VEC4              = 0x8DC8,
	GL_INT_SAMPLER_1D                 = 0x8DC9,
	GL_INT_SAMPLER_2D                 = 0x8DCA,
	GL_INT_SAMPLER_3D                 = 0x8DCB,
	GL_INT_SAMPLER_CUBE               = 0x8DCC,
	GL_INT_SAMPLER_1D_ARRAY           = 0x8DCE,
	GL_INT_SAMPLER_2D_ARRAY           = 0x8DCF,
	GL_UNSIGNED_INT_SAMPLER_1D        = 0x8DD1,
	GL_UNSIGNED_INT_SAMPLER_2D        = 0x8DD2,
	GL_UNSIGNED_INT_SAMPLER_3D        = 0x8DD3,
	GL_UNSIGNED_INT_SAMPLER_CUBE      = 0x8DD4,
	GL_UNSIGNED_INT_SAMPLER_1D_ARRAY  = 0x8DD6,
	GL_UNSIGNED_INT_SAMPLER_2D_ARRAY  = 0x8DD7,
	GL_QUERY_WAIT                     = 0x8E13,
	GL_QUERY_NO_WAIT                  = 0x8E14,
	GL_QUERY_BY_REGION_WAIT           = 0x8E15,
	GL_QUERY_BY_REGION_NO_WAIT        = 0x8E16,
	GL_BUFFER_ACCESS_FLAGS            = 0x911F,
	GL_BUFFER_MAP_LENGTH              = 0x9120,
	GL_BUFFER_MAP_OFFSET              = 0x9121,
#endif

#ifndef GL_SAMPLER_2D_RECT

	GL_SAMPLER_2D_RECT                = 0x8B63,
	GL_SAMPLER_2D_RECT_SHADOW         = 0x8B64,
	GL_SAMPLER_BUFFER                 = 0x8DC2,
	GL_INT_SAMPLER_2D_RECT            = 0x8DCD,
	GL_INT_SAMPLER_BUFFER             = 0x8DD0,
	GL_UNSIGNED_INT_SAMPLER_2D_RECT   = 0x8DD5,
	GL_UNSIGNED_INT_SAMPLER_BUFFER    = 0x8DD8,
	GL_TEXTURE_BUFFER                 = 0x8C2A,
	GL_MAX_TEXTURE_BUFFER_SIZE        = 0x8C2B,
	GL_TEXTURE_BINDING_BUFFER         = 0x8C2C,
	GL_TEXTURE_BUFFER_DATA_STORE_BINDING = 0x8C2D,
	GL_TEXTURE_BUFFER_FORMAT          = 0x8C2E,
	GL_TEXTURE_RECTANGLE              = 0x84F5,
	GL_TEXTURE_BINDING_RECTANGLE      = 0x84F6,
	GL_PROXY_TEXTURE_RECTANGLE        = 0x84F7,
	GL_MAX_RECTANGLE_TEXTURE_SIZE     = 0x84F8,
	GL_RED_SNORM                      = 0x8F90,
	GL_RG_SNORM                       = 0x8F91,
	GL_RGB_SNORM                      = 0x8F92,
	GL_RGBA_SNORM                     = 0x8F93,
	GL_R8_SNORM                       = 0x8F94,
	GL_RG8_SNORM                      = 0x8F95,
	GL_RGB8_SNORM                     = 0x8F96,
	GL_RGBA8_SNORM                    = 0x8F97,
	GL_R16_SNORM                      = 0x8F98,
	GL_RG16_SNORM                     = 0x8F99,
	GL_RGB16_SNORM                    = 0x8F9A,
	GL_RGBA16_SNORM                   = 0x8F9B,
	GL_SIGNED_NORMALIZED              = 0x8F9C,
	GL_PRIMITIVE_RESTART              = 0x8F9D,
	GL_PRIMITIVE_RESTART_INDEX        = 0x8F9E,
#endif

#ifndef GL_CONTEXT_CORE_PROFILE_BIT

	GL_CONTEXT_CORE_PROFILE_BIT       = 0x00000001,
	GL_CONTEXT_COMPATIBILITY_PROFILE_BIT = 0x00000002,
	GL_LINES_ADJACENCY                = 0x000A,
	GL_LINE_STRIP_ADJACENCY           = 0x000B,
	GL_TRIANGLES_ADJACENCY            = 0x000C,
	GL_TRIANGLE_STRIP_ADJACENCY       = 0x000D,
	GL_PROGRAM_POINT_SIZE             = 0x8642,
	GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS = 0x8C29,
	GL_FRAMEBUFFER_ATTACHMENT_LAYERED = 0x8DA7,
	GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS = 0x8DA8,
	GL_GEOMETRY_SHADER                = 0x8DD9,
	GL_GEOMETRY_VERTICES_OUT          = 0x8916,
	GL_GEOMETRY_INPUT_TYPE            = 0x8917,
	GL_GEOMETRY_OUTPUT_TYPE           = 0x8918,
	GL_MAX_GEOMETRY_UNIFORM_COMPONENTS = 0x8DDF,
	GL_MAX_GEOMETRY_OUTPUT_VERTICES   = 0x8DE0,
	GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS = 0x8DE1,
	GL_MAX_VERTEX_OUTPUT_COMPONENTS   = 0x9122,
	GL_MAX_GEOMETRY_INPUT_COMPONENTS  = 0x9123,
	GL_MAX_GEOMETRY_OUTPUT_COMPONENTS = 0x9124,
	GL_MAX_FRAGMENT_INPUT_COMPONENTS  = 0x9125,
	GL_CONTEXT_PROFILE_MASK           = 0x9126,
#endif

#ifndef GL_VERTEX_ATTRIB_ARRAY_DIVISOR

	GL_VERTEX_ATTRIB_ARRAY_DIVISOR    = 0x88FE,
#endif

#ifndef GL_SAMPLE_SHADING

	GL_SAMPLE_SHADING                 = 0x8C36,
	GL_MIN_SAMPLE_SHADING_VALUE       = 0x8C37,
	GL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET = 0x8E5E,
	GL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET = 0x8E5F,
	GL_TEXTURE_CUBE_MAP_ARRAY         = 0x9009,
	GL_TEXTURE_BINDING_CUBE_MAP_ARRAY = 0x900A,
	GL_PROXY_TEXTURE_CUBE_MAP_ARRAY   = 0x900B,
	GL_SAMPLER_CUBE_MAP_ARRAY         = 0x900C,
	GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW  = 0x900D,
	GL_INT_SAMPLER_CUBE_MAP_ARRAY     = 0x900E,
	GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY = 0x900F,
#endif

#ifndef GL_DEPTH_COMPONENT32F

	GL_DEPTH_COMPONENT32F             = 0x8CAC,
	GL_DEPTH32F_STENCIL8              = 0x8CAD,
	GL_FLOAT_32_UNSIGNED_INT_24_8_REV = 0x8DAD,
#endif

#ifndef GL_INVALID_FRAMEBUFFER_OPERATION

	GL_INVALID_FRAMEBUFFER_OPERATION  = 0x0506,
	GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING = 0x8210,
	GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE = 0x8211,
	GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE = 0x8212,
	GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE = 0x8213,
	GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE = 0x8214,
	GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE = 0x8215,
	GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE = 0x8216,
	GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE = 0x8217,
	GL_FRAMEBUFFER_DEFAULT            = 0x8218,
	GL_FRAMEBUFFER_UNDEFINED          = 0x8219,
	GL_DEPTH_STENCIL_ATTACHMENT       = 0x821A,
	GL_MAX_RENDERBUFFER_SIZE          = 0x84E8,
	GL_DEPTH_STENCIL                  = 0x84F9,
	GL_UNSIGNED_INT_24_8              = 0x84FA,
	GL_DEPTH24_STENCIL8               = 0x88F0,
	GL_TEXTURE_STENCIL_SIZE           = 0x88F1,
	GL_TEXTURE_RED_TYPE               = 0x8C10,
	GL_TEXTURE_GREEN_TYPE             = 0x8C11,
	GL_TEXTURE_BLUE_TYPE              = 0x8C12,
	GL_TEXTURE_ALPHA_TYPE             = 0x8C13,
	GL_TEXTURE_DEPTH_TYPE             = 0x8C16,
	GL_UNSIGNED_NORMALIZED            = 0x8C17,
	GL_FRAMEBUFFER_BINDING            = 0x8CA6,
	GL_DRAW_FRAMEBUFFER_BINDING      = GL_FRAMEBUFFER_BINDING,
	GL_RENDERBUFFER_BINDING           = 0x8CA7,
	GL_READ_FRAMEBUFFER               = 0x8CA8,
	GL_DRAW_FRAMEBUFFER               = 0x8CA9,
	GL_READ_FRAMEBUFFER_BINDING       = 0x8CAA,
	GL_RENDERBUFFER_SAMPLES           = 0x8CAB,
	GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE = 0x8CD0,
	GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME = 0x8CD1,
	GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL = 0x8CD2,
	GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE = 0x8CD3,
	GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER = 0x8CD4,
	GL_FRAMEBUFFER_COMPLETE           = 0x8CD5,
	GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT = 0x8CD6,
	GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT = 0x8CD7,
	GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER = 0x8CDB,
	GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER = 0x8CDC,
	GL_FRAMEBUFFER_UNSUPPORTED        = 0x8CDD,
	GL_MAX_COLOR_ATTACHMENTS          = 0x8CDF,
	GL_COLOR_ATTACHMENT0              = 0x8CE0,
	GL_COLOR_ATTACHMENT1              = 0x8CE1,
	GL_COLOR_ATTACHMENT2              = 0x8CE2,
	GL_COLOR_ATTACHMENT3              = 0x8CE3,
	GL_COLOR_ATTACHMENT4              = 0x8CE4,
	GL_COLOR_ATTACHMENT5              = 0x8CE5,
	GL_COLOR_ATTACHMENT6              = 0x8CE6,
	GL_COLOR_ATTACHMENT7              = 0x8CE7,
	GL_COLOR_ATTACHMENT8              = 0x8CE8,
	GL_COLOR_ATTACHMENT9              = 0x8CE9,
	GL_COLOR_ATTACHMENT10             = 0x8CEA,
	GL_COLOR_ATTACHMENT11             = 0x8CEB,
	GL_COLOR_ATTACHMENT12             = 0x8CEC,
	GL_COLOR_ATTACHMENT13             = 0x8CED,
	GL_COLOR_ATTACHMENT14             = 0x8CEE,
	GL_COLOR_ATTACHMENT15             = 0x8CEF,
	GL_DEPTH_ATTACHMENT               = 0x8D00,
	GL_STENCIL_ATTACHMENT             = 0x8D20,
	GL_FRAMEBUFFER                    = 0x8D40,
	GL_RENDERBUFFER                   = 0x8D41,
	GL_RENDERBUFFER_WIDTH             = 0x8D42,
	GL_RENDERBUFFER_HEIGHT            = 0x8D43,
	GL_RENDERBUFFER_INTERNAL_FORMAT   = 0x8D44,
	GL_STENCIL_INDEX1                 = 0x8D46,
	GL_STENCIL_INDEX4                 = 0x8D47,
	GL_STENCIL_INDEX8                 = 0x8D48,
	GL_STENCIL_INDEX16                = 0x8D49,
	GL_RENDERBUFFER_RED_SIZE          = 0x8D50,
	GL_RENDERBUFFER_GREEN_SIZE        = 0x8D51,
	GL_RENDERBUFFER_BLUE_SIZE         = 0x8D52,
	GL_RENDERBUFFER_ALPHA_SIZE        = 0x8D53,
	GL_RENDERBUFFER_DEPTH_SIZE        = 0x8D54,
	GL_RENDERBUFFER_STENCIL_SIZE      = 0x8D55,
	GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE = 0x8D56,
	GL_MAX_SAMPLES                    = 0x8D57,
#endif

#ifndef GL_FRAMEBUFFER_SRGB

	GL_FRAMEBUFFER_SRGB               = 0x8DB9,
#endif

#ifndef GL_HALF_FLOAT

	GL_HALF_FLOAT                     = 0x140B,
#endif

#ifndef GL_MAP_READ_BIT

	GL_MAP_READ_BIT                   = 0x0001,
	GL_MAP_WRITE_BIT                  = 0x0002,
	GL_MAP_INVALIDATE_RANGE_BIT       = 0x0004,
	GL_MAP_INVALIDATE_BUFFER_BIT      = 0x0008,
	GL_MAP_FLUSH_EXPLICIT_BIT         = 0x0010,
	GL_MAP_UNSYNCHRONIZED_BIT         = 0x0020,
#endif

#ifndef GL_COMPRESSED_RED_RGTC1

	GL_COMPRESSED_RED_RGTC1           = 0x8DBB,
	GL_COMPRESSED_SIGNED_RED_RGTC1    = 0x8DBC,
	GL_COMPRESSED_RG_RGTC2            = 0x8DBD,
	GL_COMPRESSED_SIGNED_RG_RGTC2     = 0x8DBE,
#endif

#ifndef GL_RG

	GL_RG                             = 0x8227,
	GL_RG_INTEGER                     = 0x8228,
	GL_R8                             = 0x8229,
	GL_R16                            = 0x822A,
	GL_RG8                            = 0x822B,
	GL_RG16                           = 0x822C,
	GL_R16F                           = 0x822D,
	GL_R32F                           = 0x822E,
	GL_RG16F                          = 0x822F,
	GL_RG32F                          = 0x8230,
	GL_R8I                            = 0x8231,
	GL_R8UI                           = 0x8232,
	GL_R16I                           = 0x8233,
	GL_R16UI                          = 0x8234,
	GL_R32I                           = 0x8235,
	GL_R32UI                          = 0x8236,
	GL_RG8I                           = 0x8237,
	GL_RG8UI                          = 0x8238,
	GL_RG16I                          = 0x8239,
	GL_RG16UI                         = 0x823A,
	GL_RG32I                          = 0x823B,
	GL_RG32UI                         = 0x823C,
#endif

#ifndef GL_VERTEX_ARRAY_BINDING

	GL_VERTEX_ARRAY_BINDING           = 0x85B5,
#endif

#ifndef GL_UNIFORM_BUFFER

	GL_UNIFORM_BUFFER                 = 0x8A11,
	GL_UNIFORM_BUFFER_BINDING         = 0x8A28,
	GL_UNIFORM_BUFFER_START           = 0x8A29,
	GL_UNIFORM_BUFFER_SIZE            = 0x8A2A,
	GL_MAX_VERTEX_UNIFORM_BLOCKS      = 0x8A2B,
	GL_MAX_GEOMETRY_UNIFORM_BLOCKS    = 0x8A2C,
	GL_MAX_FRAGMENT_UNIFORM_BLOCKS    = 0x8A2D,
	GL_MAX_COMBINED_UNIFORM_BLOCKS    = 0x8A2E,
	GL_MAX_UNIFORM_BUFFER_BINDINGS    = 0x8A2F,
	GL_MAX_UNIFORM_BLOCK_SIZE         = 0x8A30,
	GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS = 0x8A31,
	GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS = 0x8A32,
	GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS = 0x8A33,
	GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT = 0x8A34,
	GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH = 0x8A35,
	GL_ACTIVE_UNIFORM_BLOCKS          = 0x8A36,
	GL_UNIFORM_TYPE                   = 0x8A37,
	GL_UNIFORM_SIZE                   = 0x8A38,
	GL_UNIFORM_NAME_LENGTH            = 0x8A39,
	GL_UNIFORM_BLOCK_INDEX            = 0x8A3A,
	GL_UNIFORM_OFFSET                 = 0x8A3B,
	GL_UNIFORM_ARRAY_STRIDE           = 0x8A3C,
	GL_UNIFORM_MATRIX_STRIDE          = 0x8A3D,
	GL_UNIFORM_IS_ROW_MAJOR           = 0x8A3E,
	GL_UNIFORM_BLOCK_BINDING          = 0x8A3F,
	GL_UNIFORM_BLOCK_DATA_SIZE        = 0x8A40,
	GL_UNIFORM_BLOCK_NAME_LENGTH      = 0x8A41,
	GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS  = 0x8A42,
	GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES = 0x8A43,
	GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER = 0x8A44,
	GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER = 0x8A45,
	GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER = 0x8A46,
	GL_INVALID_INDEX                  = 0xFFFFFFFFu,
#endif

#ifndef GL_COPY_READ_BUFFER

	GL_COPY_READ_BUFFER               = 0x8F36,
	GL_COPY_WRITE_BUFFER              = 0x8F37,
#endif

#ifndef GL_DEPTH_CLAMP

	GL_DEPTH_CLAMP                    = 0x864F,
#endif

#ifndef GL_QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION

	GL_QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION = 0x8E4C,
	GL_FIRST_VERTEX_CONVENTION        = 0x8E4D,
	GL_LAST_VERTEX_CONVENTION         = 0x8E4E,
	GL_PROVOKING_VERTEX               = 0x8E4F,
#endif

#ifndef GL_TEXTURE_CUBE_MAP_SEAMLESS

	GL_TEXTURE_CUBE_MAP_SEAMLESS      = 0x884F,
#endif

#ifndef GL_MAX_SERVER_WAIT_TIMEOUT

	GL_MAX_SERVER_WAIT_TIMEOUT        = 0x9111,
	GL_OBJECT_TYPE                    = 0x9112,
	GL_SYNC_CONDITION                 = 0x9113,
	GL_SYNC_STATUS                    = 0x9114,
	GL_SYNC_FLAGS                     = 0x9115,
	GL_SYNC_FENCE                     = 0x9116,
	GL_SYNC_GPU_COMMANDS_COMPLETE     = 0x9117,
	GL_UNSIGNALED                     = 0x9118,
	GL_SIGNALED                       = 0x9119,
	GL_ALREADY_SIGNALED               = 0x911A,
	GL_TIMEOUT_EXPIRED                = 0x911B,
	GL_CONDITION_SATISFIED            = 0x911C,
	GL_WAIT_FAILED                    = 0x911D,
	GL_SYNC_FLUSH_COMMANDS_BIT        = 0x00000001,

#define 	GL_TIMEOUT_IGNORED                (0xFFFFFFFFFFFFFFFFull)

	GL_SAMPLE_POSITION                = 0x8E50,
	GL_SAMPLE_MASK                    = 0x8E51,
	GL_SAMPLE_MASK_VALUE              = 0x8E52,
	GL_MAX_SAMPLE_MASK_WORDS          = 0x8E59,
	GL_TEXTURE_2D_MULTISAMPLE         = 0x9100,
	GL_PROXY_TEXTURE_2D_MULTISAMPLE   = 0x9101,
	GL_TEXTURE_2D_MULTISAMPLE_ARRAY   = 0x9102,
	GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY = 0x9103,
	GL_TEXTURE_BINDING_2D_MULTISAMPLE = 0x9104,
	GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY = 0x9105,
	GL_TEXTURE_SAMPLES                = 0x9106,
	GL_TEXTURE_FIXED_SAMPLE_LOCATIONS = 0x9107,
	GL_SAMPLER_2D_MULTISAMPLE         = 0x9108,
	GL_INT_SAMPLER_2D_MULTISAMPLE     = 0x9109,
	GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE = 0x910A,
	GL_SAMPLER_2D_MULTISAMPLE_ARRAY   = 0x910B,
	GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY = 0x910C,
	GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY = 0x910D,
	GL_MAX_COLOR_TEXTURE_SAMPLES      = 0x910E,
	GL_MAX_DEPTH_TEXTURE_SAMPLES      = 0x910F,
	GL_MAX_INTEGER_SAMPLES            = 0x9110,

#endif

#ifndef GL_SAMPLE_SHADING_ARB
	GL_SAMPLE_SHADING_ARB             = 0x8C36,
	GL_MIN_SAMPLE_SHADING_VALUE_ARB   = 0x8C37,

#endif

#ifndef GL_TEXTURE_CUBE_MAP_ARRAY_ARB
	GL_TEXTURE_CUBE_MAP_ARRAY_ARB     = 0x9009,
	GL_TEXTURE_BINDING_CUBE_MAP_ARRAY_ARB = 0x900A,
	GL_PROXY_TEXTURE_CUBE_MAP_ARRAY_ARB = 0x900B,
	GL_SAMPLER_CUBE_MAP_ARRAY_ARB     = 0x900C,
	GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW_ARB = 0x900D,
	GL_INT_SAMPLER_CUBE_MAP_ARRAY_ARB = 0x900E,
	GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY_ARB = 0x900F,

#endif

#ifndef GL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET_ARB
	GL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET_ARB = 0x8E5E,
	GL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET_ARB = 0x8E5F,

#endif

#ifndef GL_SHADER_INCLUDE_ARB
	GL_SHADER_INCLUDE_ARB             = 0x8DAE,
	GL_NAMED_STRING_LENGTH_ARB        = 0x8DE9,
	GL_NAMED_STRING_TYPE_ARB          = 0x8DEA,

#endif

#ifndef GL_COMPRESSED_RGBA_BPTC_UNORM_ARB
	GL_COMPRESSED_RGBA_BPTC_UNORM_ARB = 0x8E8C,
	GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM_ARB = 0x8E8D,
	GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_ARB = 0x8E8E,
	GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_ARB = 0x8E8F,

#endif

#ifndef GL_SRC1_COLOR
	GL_SRC1_COLOR                     = 0x88F9,

#endif

#ifndef GL_ONE_MINUS_SRC1_COLOR
	GL_ONE_MINUS_SRC1_COLOR           = 0x88FA,
	GL_ONE_MINUS_SRC1_ALPHA           = 0x88FB,
	GL_MAX_DUAL_SOURCE_DRAW_BUFFERS   = 0x88FC,

#endif

#ifndef GL_ANY_SAMPLES_PASSED
	GL_ANY_SAMPLES_PASSED             = 0x8C2F,

#endif

#ifndef GL_SAMPLER_BINDING
	GL_SAMPLER_BINDING                = 0x8919,

#endif

#ifndef GL_RGB10_A2UI
	GL_RGB10_A2UI                     = 0x906F,

#endif

#ifndef GL_TEXTURE_SWIZZLE_R
	GL_TEXTURE_SWIZZLE_R              = 0x8E42,
	GL_TEXTURE_SWIZZLE_G              = 0x8E43,
	GL_TEXTURE_SWIZZLE_B              = 0x8E44,
	GL_TEXTURE_SWIZZLE_A              = 0x8E45,
	GL_TEXTURE_SWIZZLE_RGBA           = 0x8E46,

#endif

#ifndef GL_TIME_ELAPSED
	GL_TIME_ELAPSED                   = 0x88BF,
	GL_TIMESTAMP                      = 0x8E28,

#endif

#ifndef GL_INT_2_10_10_10_REV
	GL_INT_2_10_10_10_REV             = 0x8D9F,

#endif

#ifndef GL_DRAW_INDIRECT_BUFFER
	GL_DRAW_INDIRECT_BUFFER           = 0x8F3F,
	GL_DRAW_INDIRECT_BUFFER_BINDING   = 0x8F43,

#endif

#ifndef GL_GEOMETRY_SHADER_INVOCATIONS
	GL_GEOMETRY_SHADER_INVOCATIONS    = 0x887F,
	GL_MAX_GEOMETRY_SHADER_INVOCATIONS = 0x8E5A,
	GL_MIN_FRAGMENT_INTERPOLATION_OFFSET = 0x8E5B,
	GL_MAX_FRAGMENT_INTERPOLATION_OFFSET = 0x8E5C,
	GL_FRAGMENT_INTERPOLATION_OFFSET_BITS = 0x8E5D,

#endif

#ifndef GL_DOUBLE_VEC2
	GL_DOUBLE_VEC2                    = 0x8FFC,
	GL_DOUBLE_VEC3                    = 0x8FFD,
	GL_DOUBLE_VEC4                    = 0x8FFE,
	GL_DOUBLE_MAT2                    = 0x8F46,
	GL_DOUBLE_MAT3                    = 0x8F47,
	GL_DOUBLE_MAT4                    = 0x8F48,
	GL_DOUBLE_MAT2x3                  = 0x8F49,
	GL_DOUBLE_MAT2x4                  = 0x8F4A,
	GL_DOUBLE_MAT3x2                  = 0x8F4B,
	GL_DOUBLE_MAT3x4                  = 0x8F4C,
	GL_DOUBLE_MAT4x2                  = 0x8F4D,
	GL_DOUBLE_MAT4x3                  = 0x8F4E,

#endif

#ifndef GL_ACTIVE_SUBROUTINES
	GL_ACTIVE_SUBROUTINES             = 0x8DE5,
	GL_ACTIVE_SUBROUTINE_UNIFORMS     = 0x8DE6,
	GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS = 0x8E47,
	GL_ACTIVE_SUBROUTINE_MAX_LENGTH   = 0x8E48,
	GL_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH = 0x8E49,
	GL_MAX_SUBROUTINES                = 0x8DE7,
	GL_MAX_SUBROUTINE_UNIFORM_LOCATIONS = 0x8DE8,
	GL_NUM_COMPATIBLE_SUBROUTINES     = 0x8E4A,
	GL_COMPATIBLE_SUBROUTINES         = 0x8E4B,

#endif

#ifndef GL_PATCHES
	GL_PATCHES                        = 0x000E,
	GL_PATCH_VERTICES                 = 0x8E72,
	GL_PATCH_DEFAULT_INNER_LEVEL      = 0x8E73,
	GL_PATCH_DEFAULT_OUTER_LEVEL      = 0x8E74,
	GL_TESS_CONTROL_OUTPUT_VERTICES   = 0x8E75,
	GL_TESS_GEN_MODE                  = 0x8E76,
	GL_TESS_GEN_SPACING               = 0x8E77,
	GL_TESS_GEN_VERTEX_ORDER          = 0x8E78,
	GL_TESS_GEN_POINT_MODE            = 0x8E79,

#endif

#ifndef GL_ISOLINES
	GL_ISOLINES                       = 0x8E7A,

#endif

#ifndef GL_FRACTIONAL_ODD
	GL_FRACTIONAL_ODD                 = 0x8E7B,
	GL_FRACTIONAL_EVEN                = 0x8E7C,

#endif

#ifndef GL_MAX_PATCH_VERTICES
	GL_MAX_PATCH_VERTICES             = 0x8E7D,
	GL_MAX_TESS_GEN_LEVEL             = 0x8E7E,
	GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS = 0x8E7F,
	GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS = 0x8E80,
	GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS = 0x8E81,
	GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS = 0x8E82,
	GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS = 0x8E83,
	GL_MAX_TESS_PATCH_COMPONENTS      = 0x8E84,
	GL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS = 0x8E85,
	GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS = 0x8E86,
	GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS = 0x8E89,
	GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS = 0x8E8A,
	GL_MAX_TESS_CONTROL_INPUT_COMPONENTS = 0x886C,
	GL_MAX_TESS_EVALUATION_INPUT_COMPONENTS = 0x886D,
	GL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS = 0x8E1E,
	GL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS = 0x8E1F,
	GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER = 0x84F0,
	GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER = 0x84F1,
	GL_TESS_EVALUATION_SHADER         = 0x8E87,
	GL_TESS_CONTROL_SHADER            = 0x8E88,

#endif

#ifndef GL_TRANSFORM_FEEDBACK
	GL_TRANSFORM_FEEDBACK             = 0x8E22,
	GL_TRANSFORM_FEEDBACK_BUFFER_PAUSED = 0x8E23,
	GL_TRANSFORM_FEEDBACK_BUFFER_ACTIVE = 0x8E24,
	GL_TRANSFORM_FEEDBACK_BINDING     = 0x8E25,

#endif

#ifndef GL_MAX_TRANSFORM_FEEDBACK_BUFFERS
	GL_MAX_TRANSFORM_FEEDBACK_BUFFERS = 0x8E70,
	GL_MAX_VERTEX_STREAMS             = 0x8E71,

#endif

#ifndef GL_FIXED
	GL_FIXED                          = 0x140C,
	GL_IMPLEMENTATION_COLOR_READ_TYPE = 0x8B9A,
	GL_IMPLEMENTATION_COLOR_READ_FORMAT = 0x8B9B,
	GL_LOW_FLOAT                      = 0x8DF0,
	GL_MEDIUM_FLOAT                   = 0x8DF1,
	GL_HIGH_FLOAT                     = 0x8DF2,
	GL_LOW_INT                        = 0x8DF3,
	GL_MEDIUM_INT                     = 0x8DF4,
	GL_HIGH_INT                       = 0x8DF5,
	GL_SHADER_COMPILER                = 0x8DFA,
	GL_NUM_SHADER_BINARY_FORMATS      = 0x8DF9,
	GL_MAX_VERTEX_UNIFORM_VECTORS     = 0x8DFB,
	GL_MAX_VARYING_VECTORS            = 0x8DFC,
	GL_MAX_FRAGMENT_UNIFORM_VECTORS   = 0x8DFD,

#endif

#ifndef GL_PROGRAM_BINARY_RETRIEVABLE_HINT
	GL_PROGRAM_BINARY_RETRIEVABLE_HINT = 0x8257,
	GL_PROGRAM_BINARY_LENGTH          = 0x8741,
	GL_NUM_PROGRAM_BINARY_FORMATS     = 0x87FE,
	GL_PROGRAM_BINARY_FORMATS         = 0x87FF,

#endif

#ifndef GL_VERTEX_SHADER_BIT
	GL_VERTEX_SHADER_BIT              = 0x00000001,
	GL_FRAGMENT_SHADER_BIT            = 0x00000002,
	GL_GEOMETRY_SHADER_BIT            = 0x00000004,
	GL_TESS_CONTROL_SHADER_BIT        = 0x00000008,
	GL_TESS_EVALUATION_SHADER_BIT     = 0x00000010,
	GL_ALL_SHADER_BITS                = 0xFFFFFFFF,
	GL_PROGRAM_SEPARABLE              = 0x8258,
	GL_ACTIVE_PROGRAM                 = 0x8259,
	GL_PROGRAM_PIPELINE_BINDING       = 0x825A,

#endif

#ifndef GL_MAX_VIEWPORTS
	GL_MAX_VIEWPORTS                  = 0x825B,
	GL_VIEWPORT_SUBPIXEL_BITS         = 0x825C,
	GL_VIEWPORT_BOUNDS_RANGE          = 0x825D,
	GL_LAYER_PROVOKING_VERTEX         = 0x825E,
	GL_VIEWPORT_INDEX_PROVOKING_VERTEX = 0x825F,
	GL_UNDEFINED_VERTEX               = 0x8260,

#endif

#ifndef GL_SYNC_CL_EVENT_ARB
	GL_SYNC_CL_EVENT_ARB              = 0x8240,
	GL_SYNC_CL_EVENT_COMPLETE_ARB     = 0x8241,

#endif

#ifndef GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB
	GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB   = 0x8242,
	GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH_ARB = 0x8243,
	GL_DEBUG_CALLBACK_FUNCTION_ARB    = 0x8244,
	GL_DEBUG_CALLBACK_USER_PARAM_ARB  = 0x8245,
	GL_DEBUG_SOURCE_API_ARB           = 0x8246,
	GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB = 0x8247,
	GL_DEBUG_SOURCE_SHADER_COMPILER_ARB = 0x8248,
	GL_DEBUG_SOURCE_THIRD_PARTY_ARB   = 0x8249,
	GL_DEBUG_SOURCE_APPLICATION_ARB   = 0x824A,
	GL_DEBUG_SOURCE_OTHER_ARB         = 0x824B,
	GL_DEBUG_TYPE_ERROR_ARB           = 0x824C,
	GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB = 0x824D,
	GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB = 0x824E,
	GL_DEBUG_TYPE_PORTABILITY_ARB     = 0x824F,
	GL_DEBUG_TYPE_PERFORMANCE_ARB     = 0x8250,
	GL_DEBUG_TYPE_OTHER_ARB           = 0x8251,
	GL_MAX_DEBUG_MESSAGE_LENGTH_ARB   = 0x9143,
	GL_MAX_DEBUG_LOGGED_MESSAGES_ARB  = 0x9144,
	GL_DEBUG_LOGGED_MESSAGES_ARB      = 0x9145,
	GL_DEBUG_SEVERITY_HIGH_ARB        = 0x9146,
	GL_DEBUG_SEVERITY_MEDIUM_ARB      = 0x9147,
	GL_DEBUG_SEVERITY_LOW_ARB         = 0x9148,

#endif

#ifndef GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT_ARB
	GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT_ARB = 0x00000004,
	GL_LOSE_CONTEXT_ON_RESET_ARB      = 0x8252,
	GL_GUILTY_CONTEXT_RESET_ARB       = 0x8253,
	GL_INNOCENT_CONTEXT_RESET_ARB     = 0x8254,
	GL_UNKNOWN_CONTEXT_RESET_ARB      = 0x8255,
	GL_RESET_NOTIFICATION_STRATEGY_ARB = 0x8256,
	GL_NO_RESET_NOTIFICATION_ARB      = 0x8261
#endif
};

#endif

/// \}


