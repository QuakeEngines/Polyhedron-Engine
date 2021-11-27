/*
Copyright (C) 1997-2001 Id Software, Inc.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef __SHARED__MATH_H__
#define __SHARED__MATH_H__

//-----------------
// Utilities
//-----------------
#include "Shared/math/utilities.h"

//-----------------
// Vectors
//-----------------
#include "Shared/math/vector2.h"
#include "Shared/math/vector3.h"
#include "Shared/math/vector4.h"
#include "Shared/math/vector5.h"

//-----------------
// Matrixes
//-----------------
#include "Shared/math/matrix3.h"
#include "Shared/math/matrix4.h"

//-----------------
// Plane
//-----------------
#include "Shared/math/plane.h"

//-----------------
// Colors
//-----------------
#include "Shared/math/color.h"

//-----------------
// Rectangles.
//-----------------
#include "Shared/math/rectangle.h"

//-----------------
// Quaternion.
//-----------------
#include "Shared/math/quaternion.h"

//-----------------
// TODO: These should ultimately be removed and/or replaced.
//-----------------
#define NUMVERTEXNORMALS    162
extern const vec3_t bytedirs[NUMVERTEXNORMALS];

#endif // __SHARED__MATH_H__
