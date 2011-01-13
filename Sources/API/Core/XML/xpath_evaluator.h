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

/// \addtogroup clanCore_XML clanCore XML
/// \{

#pragma once

#include "../System/sharedptr.h"
#include "xpath_object.h"

class CL_DomNode;
class CL_XPathEvaluator_Impl;

/// \brief XPath evaluator.
///
/// \xmlonly !group=Core/XML! !header=core.h! \endxmlonly
class CL_XPathEvaluator
{
/// \name Construction
/// \{

public:
	CL_XPathEvaluator();

/// \}
/// \name Operations
/// \{

public:

	/// \brief Evaluate
	///
	/// \param expression = String Ref
	/// \param context_node = Dom Node
	///
	/// \return XPath Object
	CL_XPathObject evaluate(const CL_StringRef &expression, CL_DomNode context_node);

/// \}
/// \name Implementation
/// \{

private:
	CL_SharedPtr<CL_XPathEvaluator_Impl> impl;
/// \}
};

/// \}
