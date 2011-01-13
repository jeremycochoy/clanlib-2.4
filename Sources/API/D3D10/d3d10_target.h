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
*/

/// \addtogroup clanD3D10_Display clanD3D10 Display
/// \{

#pragma once

#include "api_d3d10.h"
#include "../Display/display_target.h"
#include "../Core/System/sharedptr.h"
#include "../Core/Text/string_types.h"

/// \brief Display target for clanDisplay.
///
/// \xmlonly !group=D3D10/Display! !header=d3d10.h! \endxmlonly
class CL_API_D3D10 CL_D3D10Target : public CL_DisplayTarget
{
/// \name Construction
/// \{

public:
	/// \brief Constructs an D3D10 target.
	CL_D3D10Target();

	~CL_D3D10Target();

/// \}
/// \name Attributes
/// \{

public:

/// \}
/// \name Operations
/// \{

public:

/// \}
/// \name Implementation
/// \{

private:
/// \}
};

/// \}
