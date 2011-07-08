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
**    Mark Page
*/

#pragma once

#include "scene_object.h"

class Scene;
class GraphicStore;

class ParticleObject : public SceneObject
{
public:
	ParticleObject(CL_GraphicContext &gc, Scene &scene_owner, SceneObject *parent_object);
	virtual ~ParticleObject();

	void Draw(CL_GraphicContext &gc, const CL_Mat4f &current_modelview);
private:
	void Draw(CL_GraphicContext &gc, GraphicStore *gs, const CL_Mat4f &modelview_matrix);

public:
	static const int num_points = 80000;

private:

	CL_VertexArrayBuffer object_positions_vbo;
	CL_VertexArrayBuffer object_colours_vbo;
};

