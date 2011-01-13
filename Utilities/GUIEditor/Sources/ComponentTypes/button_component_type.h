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
**    Harry Storbacka
**    Kenneth Gangstoe
*/

#pragma once

#include "component_type.h"

class ButtonComponentType : public ComponentType
{
public:
	ButtonComponentType(const CL_String &xmlname, const CL_StringRef &name, int id, const CL_StringRef &icon)	
	: ComponentType(xmlname, name, id, icon) {}

	virtual CL_GUIComponent *create_component(CL_GUIComponent *parent) const
	{
		CL_PushButton *component = new CL_PushButton(parent);
		component->set_text("Button");
		component->set_geometry(CL_Rect(0, 0, 75, 23));
		return component;
	}
};
