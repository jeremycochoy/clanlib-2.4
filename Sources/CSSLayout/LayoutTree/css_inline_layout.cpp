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

#include "CSSLayout/precomp.h"
#include "css_inline_layout.h"
#include "css_layout_cursor.h"
#include "css_stacking_context.h"
#include "css_block_formatting_context.h"
#include "../BoxTree/css_box_text.h"
#include "../css_resource_cache.h"
#include "API/CSSLayout/css_box_properties.h"

CL_CSSInlineLayout::CL_CSSInlineLayout(CL_CSSBoxElement *element)
: CL_CSSLayoutTreeNode(element)
{
}

void CL_CSSInlineLayout::add_box(CL_CSSInlineGeneratedBox *box)
{
	boxes.add_box(box);
}

void CL_CSSInlineLayout::set_component_geometry()
{
	CL_CSSInlineGeneratedBox *cur = boxes.first_child;
	while (cur)
	{
		if (cur->layout_node)
		{
			cur->layout_node->set_component_geometry();
		}

		if (cur->first_child)
		{
			cur = cur->first_child;
		}
		else if (cur->next_sibling)
		{
			cur = cur->next_sibling;
		}
		else
		{
			while (cur && !cur->next_sibling)
			{
				cur = cur->parent;
			}
			if (cur)
			{
				cur = cur->next_sibling;
			}
		}
	}
}

int CL_CSSInlineLayout::get_first_line_baseline()
{
	for (size_t i = 0; i < lines.size(); i++)
	{
		CL_CSSInlineGeneratedBox *cur = lines[i];
		if (cur->layout_node)
		{
			int baseline = cur->layout_node->get_first_line_baseline();
			if (baseline != -1)
			{
				if (cur->layout_node->is_formatting_context_root())
					baseline += cur->layout_node->get_formatting_context()->get_local_y();
				return baseline;
			}
		}
		else
		{
			return cur->y + cur->ascent;
		}
	}
	return -1;
}

int CL_CSSInlineLayout::get_last_line_baseline()
{
	for (size_t i = lines.size(); i > 0; i++)
	{
		CL_CSSInlineGeneratedBox *cur = lines[i-1];
		if (cur->layout_node)
		{
			int baseline = cur->layout_node->get_last_line_baseline();
			if (baseline != -1)
			{
				if (cur->layout_node->is_formatting_context_root())
					baseline += cur->layout_node->get_formatting_context()->get_local_y();
				return baseline;
			}
		}
		else
		{
			return cur->y + cur->ascent;
		}
	}
	return -1;
}

void CL_CSSInlineLayout::prepare_children()
{
	CL_CSSInlineGeneratedBox *cur = boxes.first_child;
	while (cur)
	{
		if (cur->layout_node)
		{
			cur->layout_node->prepare(formatting_context, stacking_context);
		}

		if (cur->first_child)
		{
			cur = cur->first_child;
		}
		else if (cur->next_sibling)
		{
			cur = cur->next_sibling;
		}
		else
		{
			while (cur && !cur->next_sibling)
			{
				cur = cur->parent;
			}
			if (cur)
			{
				cur = cur->next_sibling;
			}
		}
	}
}

void CL_CSSInlineLayout::calculate_content_top_down_heights()
{
	CL_CSSInlineGeneratedBox *cur = boxes.first_child;
	while (cur)
	{
		if (cur->layout_node)
		{
			cur->layout_node->containing_height = height;
			cur->layout_node->calculate_top_down_heights();
		}

		if (cur->first_child)
		{
			cur = cur->first_child;
		}
		else if (cur->next_sibling)
		{
			cur = cur->next_sibling;
		}
		else
		{
			while (cur && !cur->next_sibling)
			{
				cur = cur->parent;
			}
			if (cur)
			{
				cur = cur->next_sibling;
			}
		}
	}
}

bool CL_CSSInlineLayout::add_content_margin_top(CL_CSSLayoutCursor &cursor)
{
	bool start_of_line = true;
	CL_CSSInlineGeneratedBox *cur = boxes.first_child;
	while (cur)
	{
		CL_CSSBoxNode *node = cur->box_node;
		CL_CSSBoxText *text = dynamic_cast<CL_CSSBoxText*>(node);
		if (text)
		{
			size_t text_start = 0;
			size_t text_end = text->processed_text.length();
			adjust_start_of_line_text_range(text, text_start, text_end, start_of_line);

			if (text->processed_text.substr(text_start, text_end - text_start).find_first_not_of(' ') != CL_String::npos)
				return true;
		}
		else if (cur->layout_node)
		{
			if (cur->layout_node->add_margin_top(cursor))
				return true;
		}

		if (cur->first_child)
		{
			cur = cur->first_child;
		}
		else if (cur->next_sibling)
		{
			cur = cur->next_sibling;
		}
		else
		{
			while (cur && !cur->next_sibling)
			{
				cur = cur->parent;
			}
			if (cur)
			{
				cur = cur->next_sibling;
			}
		}
	}

	if (height.use_content)
	{
		return false;
	}
	else
	{
		return height.value != 0.0f;
	}
}

bool CL_CSSInlineLayout::is_empty() const
{
	bool start_of_line = true;
	CL_CSSInlineGeneratedBox *cur = boxes.first_child;
	while (cur)
	{
		CL_CSSBoxNode *node = cur->box_node;
		CL_CSSBoxText *text = dynamic_cast<CL_CSSBoxText*>(node);
		if (text)
		{
			size_t text_start = 0;
			size_t text_end = text->processed_text.length();
			adjust_start_of_line_text_range(text, text_start, text_end, start_of_line);

			if (text->processed_text.substr(text_start, text_end - text_start).find_first_not_of(' ') != CL_String::npos)
				return false;
		}
		else if (cur->layout_node &&
			!cur->layout_node->get_element_node()->is_float() &&
			!cur->layout_node->get_element_node()->is_absolute() &&
			!cur->layout_node->get_element_node()->is_fixed())
		{
			if (!cur->layout_node->is_empty())
				return false;
		}

		if (cur->first_child)
		{
			cur = cur->first_child;
		}
		else if (cur->next_sibling)
		{
			cur = cur->next_sibling;
		}
		else
		{
			while (cur && !cur->next_sibling)
			{
				cur = cur->parent;
			}
			if (cur)
			{
				cur = cur->next_sibling;
			}
		}
	}

	if (height.use_content)
	{
		return true;
	}
	else
	{
		return height.value == 0.0f;
	}

/*
	if (height.use_content)
	{
		return is_empty_line(begin(), end());
	}
	else
	{
		return height.value == 0.0f;
	}*/
}

void CL_CSSInlineLayout::layout_content(CL_GraphicContext &gc, CL_CSSLayoutCursor &cursor, LayoutStrategy strategy)
{
	lines.clear();
	layout_inline_blocks_and_floats(gc, cursor.resources, strategy);
	create_linebreak_opportunities();

	CL_CSSInlinePosition line_start_pos = begin();
	size_t next_linebreak_opportunity = 0;
	while (line_start_pos != end())
	{
		if (line_start_pos.is_block_level() && !line_start_pos.is_float())
		{
			CL_CSSLayoutTreeNode *layout_node = line_start_pos.box->layout_node;

			if (layout_node->get_element_node()->computed_properties.position.type != CL_CSSBoxPosition::type_absolute &&
				layout_node->get_element_node()->computed_properties.position.type != CL_CSSBoxPosition::type_fixed)
			{
				generate_block_line(line_start_pos);
				layout_block_line(lines.back(), gc, cursor, strategy);
			}
			else
			{
				// We layout absolute or fixed elements later since they may rely on the calculated height of the normal flow.

				layout_node->static_position_parent = this;
				layout_node->static_position.left = cl_actual_to_used(cursor.x);
				layout_node->static_position.top = cl_actual_to_used(cursor.y + cursor.get_total_margin());
				layout_node->static_position.right = layout_node->static_position.left;
				layout_node->static_position.bottom = layout_node->static_position.top;
				layout_node->relative_x = relative_x + layout_node->get_local_relative_x();
				layout_node->relative_y = relative_y + layout_node->get_local_relative_y();
				layout_node->containing_width = width;
				layout_node->calc_preferred(gc, cursor.resources);
				layout_node->calculate_top_down_widths(normal_strategy);
				layout_node->calculate_top_down_heights();
				if (layout_node->width.expanding)
					layout_node->width.value = layout_node->preferred_width;
				layout_node->layout_formatting_root_helper(gc, cursor.resources, normal_strategy);
				layout_node->static_position.right = layout_node->static_position.left + layout_node->width.value;
				layout_node->static_position.bottom = layout_node->static_position.top + layout_node->height.value;
			}

			if (line_start_pos == linebreak_opportunities[next_linebreak_opportunity].pos)
				next_linebreak_opportunity++;

			line_start_pos.text_pos = 0;
			if (line_start_pos.box->first_child)
			{
				line_start_pos.box = line_start_pos.box->first_child;
			}
			else if (line_start_pos.box->next_sibling)
			{
				line_start_pos.box = line_start_pos.box->next_sibling;
			}
			else
			{
				while (line_start_pos.box && !line_start_pos.box->next_sibling)
				{
					line_start_pos.box = line_start_pos.box->parent;
				}
				if (line_start_pos.box)
				{
					line_start_pos.box = line_start_pos.box->next_sibling;
				}
			}
		}
		else
		{
			CL_CSSActualValue y = cl_used_to_actual(cursor.y + cursor.get_total_margin());
			CL_Rect line_box;

			CL_CSSInlinePosition line_end_pos = line_start_pos;
			CL_CSSActualValue available_width = cl_used_to_actual(width.value);
			CL_CSSActualValue used_width = 0;
			bool start_of_line = true;
			bool restart = false;
			while (next_linebreak_opportunity < linebreak_opportunities.size())
			{
				CL_CSSInlinePosition linebreak_pos = linebreak_opportunities[next_linebreak_opportunity].pos;
				bool is_newline = linebreak_opportunities[next_linebreak_opportunity].newline;

				bool next_start_of_line = start_of_line;
				CL_CSSActualValue segment_width = get_width(gc, cursor.resources, line_end_pos, linebreak_pos, next_start_of_line);

				if (start_of_line)
				{
					CL_CSSActualValue text_indent = 0;
					if (lines.empty())
					{
						if (element_node->computed_properties.text_indent.type == CL_CSSBoxTextIndent::type_length)
						{
							text_indent = cl_used_to_actual(element_node->computed_properties.text_indent.length.value);
						}
						else if (element_node->computed_properties.text_indent.type == CL_CSSBoxTextIndent::type_percentage)
						{
							text_indent = cl_used_to_actual(width.value * element_node->computed_properties.text_indent.percentage / 100.0f);
						}
					}

					CL_CSSActualValue w = cl_used_to_actual(width.value);
					if (width.expanding && strategy == preferred_strategy)
						w = 1000000;
					line_box = formatting_context->find_line_box(cursor.x + text_indent, cursor.x + w, y, 1, segment_width);
					available_width = line_box.get_width();
				}

				bool fits_on_line = used_width + segment_width <= available_width;
				if (!fits_on_line && start_of_line)
				{
					// To do: force line break at the character level
					fits_on_line = true;
				}

				if (width.expanding)
				{
					if (strategy == preferred_strategy)
						fits_on_line = true;
					else if (strategy == minimum_strategy)
						fits_on_line = start_of_line;
				}

				if (!fits_on_line)
					break;

				if (place_floats(line_start_pos, linebreak_pos, cursor.x, y, strategy))
				{
					restart = true;
					break;
				}
				used_width += segment_width;
				line_end_pos = linebreak_pos;
				next_linebreak_opportunity++;
				start_of_line = next_start_of_line;
				if (is_newline || (line_end_pos.is_block_level() && !line_end_pos.is_float()))
					break;
			}
			if (restart)
				continue;

			if (!is_empty_line(line_start_pos, line_end_pos))
			{
				generate_line(line_start_pos, line_end_pos);
				layout_line(lines.back(), line_box, gc, cursor.resources);
				cursor.apply_margin();
				cursor.y = cl_actual_to_used(line_box.bottom);

				if (strategy != normal_strategy && width.expanding)
					width.value = cl_max(width.value, cl_actual_to_used(line_box.left+used_width-cursor.x));
			}

			line_start_pos = line_end_pos;
		}
	}

	for (size_t i = 0; i < lines.size(); i++)
	{
		bool last_line = (i+1 == lines.size());
		if (!lines[i]->is_block_line())
			align_line(lines[i], gc, cursor.resources, last_line);
	}

	if (lines.empty() && height.value > 0.0f)
		cursor.apply_margin();
}

void CL_CSSInlineLayout::layout_absolute_and_fixed_content(CL_GraphicContext &gc, CL_CSSResourceCache *resources, CL_Rect containing_block, const CL_Size &viewport_size)
{
	if (get_element_node()->computed_properties.position.type != CL_CSSBoxPosition::type_static)
	{
		CL_Rect rect = get_padding_box();
		containing_block = rect;
	}

	CL_CSSInlineGeneratedBox *cur = boxes.first_child;
	while (cur)
	{
		if (cur->layout_node)
		{
			if (cur->layout_node->get_element_node()->computed_properties.position.type == CL_CSSBoxPosition::type_absolute ||
				cur->layout_node->get_element_node()->computed_properties.position.type == CL_CSSBoxPosition::type_fixed)
			{
				cur->layout_node->relative_x = relative_x + cur->layout_node->get_local_relative_x();
				cur->layout_node->relative_y = relative_y + cur->layout_node->get_local_relative_y();
				cur->layout_node->layout_absolute_or_fixed(gc, resources, containing_block, viewport_size);
			}

			cur->layout_node->layout_absolute_and_fixed_content(gc, resources, containing_block, viewport_size);
		}

		if (cur->first_child)
		{
			cur = cur->first_child;
		}
		else if (cur->next_sibling)
		{
			cur = cur->next_sibling;
		}
		else
		{
			while (cur && !cur->next_sibling)
			{
				cur = cur->parent;
			}
			if (cur)
			{
				cur = cur->next_sibling;
			}
		}
	}
}

void CL_CSSInlineLayout::render_layer_background(CL_GraphicContext &gc, CL_CSSResourceCache *resources, bool root)
{
	render_non_content(gc, resources, root);

	int pos_x = cl_used_to_actual(relative_x) + formatting_context->get_x();
	int pos_y = cl_used_to_actual(relative_y) + formatting_context->get_y();
	for (size_t i = 0; i < lines.size(); i++)
	{
		CL_CSSInlineGeneratedBox *cur = lines[i];
		while (cur)
		{
			CL_CSSBoxElement *element = cur->box_node ? dynamic_cast<CL_CSSBoxElement*>(cur->box_node) : 0;
			if (cur->layout_node)
			{
				//cur->layout_node->render_layer_background(gc, resources, false);
			}
			else if (element)
			{
				if (element->computed_properties.visibility.type == CL_CSSBoxVisibility::type_visible)
				{
					CL_Rect content(pos_x + cur->x, pos_y + cur->y, pos_x + cur->x + cur->width, pos_y + cur->y + cur->ascent + cur->descent);

					CL_Rect padding_box = content;
					padding_box.expand(
						cur->opening ? cl_used_to_actual(get_css_padding_width(element->computed_properties.padding_width_left, containing_width)) : 0,
						cl_used_to_actual(get_css_padding_height(element->computed_properties.padding_width_top, containing_height)),
						cur->closing ?  cl_used_to_actual(get_css_padding_width(element->computed_properties.padding_width_right, containing_width)) : 0,
						cl_used_to_actual(get_css_padding_height(element->computed_properties.padding_width_bottom, containing_height)));

					CL_Rect border_box = padding_box;
					border_box.expand(
						cur->opening ? cl_used_to_actual(element->computed_properties.border_width_left.length.value) : 0,
						cl_used_to_actual(element->computed_properties.border_width_top.length.value),
						cur->closing ? cl_used_to_actual(element->computed_properties.border_width_right.length.value) : 0,
						cl_used_to_actual(element->computed_properties.border_width_bottom.length.value));

					render_background(gc, resources, element, padding_box, padding_box);
					render_border(gc, element, border_box,
						cur->opening ? element->computed_properties.border_width_left.length.value : 0,
						element->computed_properties.border_width_top.length.value,
						cur->closing ? element->computed_properties.border_width_right.length.value : 0,
						element->computed_properties.border_width_bottom.length.value);
				}
			}

			if (cur->first_child)
			{
				cur = cur->first_child;
			}
			else if (cur->next_sibling)
			{
				cur = cur->next_sibling;
			}
			else
			{
				while (cur && !cur->next_sibling)
				{
					cur = cur->parent;
				}
				if (cur)
				{
					cur = cur->next_sibling;
				}
			}
		}
	}
}

void CL_CSSInlineLayout::render_layer_non_inline(CL_GraphicContext &gc, CL_CSSResourceCache *resources)
{
	for (size_t i = 0; i < lines.size(); i++)
	{
		CL_CSSInlineGeneratedBox *cur = lines[i];
		while (cur)
		{
			if (cur->layout_node)
			{
				CL_CSSLayoutTreeNode *object_node = cur->layout_node;
				bool is_same_stacking_context = (stacking_context == object_node->get_stacking_context());
				bool is_positioned = (object_node->get_element_node()->computed_properties.position.type != CL_CSSBoxPosition::type_static);
				bool is_float = object_node->get_element_node()->is_float();
				if (is_same_stacking_context && !is_positioned && !is_float)
				{
					object_node->render_layer_background(gc, resources, false);
					object_node->render_layer_non_inline(gc, resources);
				}
			}

			if (cur->first_child)
			{
				cur = cur->first_child;
			}
			else if (cur->next_sibling)
			{
				cur = cur->next_sibling;
			}
			else
			{
				while (cur && !cur->next_sibling)
				{
					cur = cur->parent;
				}
				if (cur)
				{
					cur = cur->next_sibling;
				}
			}
		}
	}
}

void CL_CSSInlineLayout::render_layer_floats(CL_GraphicContext &gc, CL_CSSResourceCache *resources)
{
	CL_CSSInlineGeneratedBox *cur = boxes.first_child;
	while (cur)
	{
		if (cur->layout_node)
		{
			CL_CSSLayoutTreeNode *object_node = cur->layout_node;
			bool is_same_stacking_context = (stacking_context == object_node->get_stacking_context());
			bool is_positioned = (object_node->get_element_node()->computed_properties.position.type != CL_CSSBoxPosition::type_static);
			bool is_float = object_node->get_element_node()->is_float();
			if (is_same_stacking_context && !is_positioned)
			{
				if (is_float)
				{
					object_node->render_layer_background(gc, resources, false);
					object_node->render_layer_non_inline(gc, resources);
					object_node->render_layer_floats(gc, resources);
					object_node->render_layer_inline(gc, resources);
				}
				else
				{
					object_node->render_layer_floats(gc, resources);
				}
			}
		}

		if (cur->first_child)
		{
			cur = cur->first_child;
		}
		else if (cur->next_sibling)
		{
			cur = cur->next_sibling;
		}
		else
		{
			while (cur && !cur->next_sibling)
			{
				cur = cur->parent;
			}
			if (cur)
			{
				cur = cur->next_sibling;
			}
		}
	}
}

void CL_CSSInlineLayout::render_layer_inline(CL_GraphicContext &gc, CL_CSSResourceCache *resources)
{
	int pos_x = cl_used_to_actual(relative_x) + formatting_context->get_x();
	int pos_y = cl_used_to_actual(relative_y) + formatting_context->get_y();

	for (size_t i = 0; i < lines.size(); i++)
	{
		CL_CSSInlineGeneratedBox *cur = lines[i];
		while (cur)
		{
			CL_CSSBoxNode *node = cur->box_node;
			CL_CSSBoxText *text = dynamic_cast<CL_CSSBoxText*>(node);
			if (text)
			{
				const CL_CSSBoxProperties &properties = text->get_properties();
				if (properties.visibility.type == CL_CSSBoxVisibility::type_visible)
				{
					CL_Font font = resources->get_font(gc, properties);
					CL_FontMetrics metrics = font.get_font_metrics(gc);
					font.draw_text(gc, pos_x + cur->x, pos_y + cur->y + cl_used_to_actual(metrics.get_ascent()), text->processed_text.substr(cur->text_start, cur->text_end - cur->text_start), properties.color.color);
				}
			}
			else if (cur->layout_node)
			{
				CL_CSSLayoutTreeNode *object_node = cur->layout_node;
				bool is_same_stacking_context = (stacking_context == object_node->get_stacking_context());
				bool is_positioned = (object_node->get_element_node()->computed_properties.position.type != CL_CSSBoxPosition::type_static);
				if (is_same_stacking_context && !is_positioned)
					object_node->render_layer_inline(gc, resources);
			}

			if (cur->first_child)
			{
				cur = cur->first_child;
			}
			else if (cur->next_sibling)
			{
				cur = cur->next_sibling;
			}
			else
			{
				while (cur && !cur->next_sibling)
				{
					cur = cur->parent;
				}
				if (cur)
				{
					cur = cur->next_sibling;
				}
			}
		}
	}
}

void CL_CSSInlineLayout::render_layer_positioned(CL_GraphicContext &gc, CL_CSSResourceCache *resources)
{
	CL_CSSInlineGeneratedBox *cur = boxes.first_child;
	while (cur)
	{
		if (cur->layout_node)
		{
			CL_CSSLayoutTreeNode *object_node = cur->layout_node;
			bool is_same_stacking_context = (stacking_context == object_node->get_stacking_context());
			bool is_positioned = (object_node->get_element_node()->computed_properties.position.type != CL_CSSBoxPosition::type_static);
			int level = object_node->get_stacking_context()->get_level();
			if (is_same_stacking_context)
			{
				if (is_positioned)
				{
					object_node->render_layer_background(gc, resources, false);
					object_node->render_layer_non_inline(gc, resources);
					object_node->render_layer_floats(gc, resources);
					object_node->render_layer_inline(gc, resources);
				}
				object_node->render_layer_positioned(gc, resources);
			}
			else if (!is_same_stacking_context && level == 0)
			{
				object_node->get_stacking_context()->render(gc, resources);
			}
		}

		if (cur->first_child)
		{
			cur = cur->first_child;
		}
		else if (cur->next_sibling)
		{
			cur = cur->next_sibling;
		}
		else
		{
			while (cur && !cur->next_sibling)
			{
				cur = cur->parent;
			}
			if (cur)
			{
				cur = cur->next_sibling;
			}
		}
	}
}

void CL_CSSInlineLayout::create_linebreak_opportunities()
{
	linebreak_opportunities.clear();
	bool prev_space = true;

	CL_CSSInlineGeneratedBox *cur = boxes.first_child;
	while (cur)
	{
		CL_CSSBoxNode *node = cur->box_node;
		CL_CSSBoxText *text = dynamic_cast<CL_CSSBoxText*>(node);
		if (text)
		{
			for (size_t j = 0; j < text->processed_text.size(); j++)
			{
				if (text->processed_text[j] == ' ')
				{
					prev_space = true;
				}
				else if (text->processed_text[j] == '\n')
				{
					linebreak_opportunities.push_back(CL_CSSInlineLineBreakOpportunity2(cur, j+1, true));
					prev_space = false;
				}
				else
				{
					if (prev_space && should_break_at_end_of_spaces(text->get_properties().white_space))
						linebreak_opportunities.push_back(CL_CSSInlineLineBreakOpportunity2(cur, j));
					prev_space = false;
				}
			}
		}
		else if (cur->layout_node && cur->layout_node->get_element_node()->is_block_level() && !cur->layout_node->get_element_node()->is_float())
		{
			linebreak_opportunities.push_back(CL_CSSInlineLineBreakOpportunity2(cur, 0));
		}

		if (cur->first_child)
		{
			cur = cur->first_child;
		}
		else if (cur->next_sibling)
		{
			cur = cur->next_sibling;
		}
		else
		{
			while (cur && !cur->next_sibling)
			{
				cur = cur->parent;
			}
			if (cur)
			{
				cur = cur->next_sibling;
			}
		}
	}
	linebreak_opportunities.push_back(CL_CSSInlineLineBreakOpportunity2(0, 0));
}

bool CL_CSSInlineLayout::should_break_at_end_of_spaces(const CL_CSSBoxWhiteSpace &whitespace)
{
	return whitespace.type != CL_CSSBoxWhiteSpace::type_pre || whitespace.type == CL_CSSBoxWhiteSpace::type_nowrap;
}

CL_CSSInlinePosition CL_CSSInlineLayout::begin() const
{
	return CL_CSSInlinePosition(boxes.first_child, 0);
}

CL_CSSInlinePosition CL_CSSInlineLayout::end() const
{
	return CL_CSSInlinePosition();
}

void CL_CSSInlineLayout::generate_block_line(CL_CSSInlinePosition pos)
{
	std::auto_ptr<CL_CSSInlineGeneratedBox> line(new CL_CSSInlineGeneratedBox());
	line->box_node = pos.box->box_node;
	line->layout_node = pos.box->layout_node;
	lines.push_back(line.get());
	line.release();
}

CL_CSSInlineGeneratedBox *CL_CSSInlineLayout::begin_tree(CL_CSSInlinePosition start, CL_CSSInlineGeneratedBox *line)
{
	CL_CSSInlineGeneratedBox *input = start.box;
	CL_CSSInlineGeneratedBox *output = 0;
	CL_CSSInlineGeneratedBox *cur = 0;
	try
	{
		while (input->parent->parent)
		{
			input = input->parent;
			CL_CSSInlineGeneratedBox *parent = new CL_CSSInlineGeneratedBox();
			parent->opening = false;
			parent->box_node = input->box_node;
			parent->layout_node = input->layout_node;
			if (cur)
				parent->add_box(cur);
			else
				output = parent;
			cur = parent;
		}
		if (cur)
			line->add_box(cur);
		if (output == 0)
			output = line;
		return output;
	}
	catch (...)
	{
		delete cur;
		throw;
	}
}

void CL_CSSInlineLayout::generate_line(CL_CSSInlinePosition start, CL_CSSInlinePosition end)
{
	std::auto_ptr<CL_CSSInlineGeneratedBox> line(new CL_CSSInlineGeneratedBox());
	CL_CSSInlineGeneratedBox *parent = begin_tree(start, line.get());

	bool start_of_line = true;
	CL_CSSInlinePosition cur = start;
	while (cur != end)
	{
		CL_CSSInlineGeneratedBox *output = 0;
		CL_CSSBoxText *text = dynamic_cast<CL_CSSBoxText*>(cur.box->box_node);
		if (text)
		{
			size_t text_start = cur.text_pos;
			size_t text_end;
			if (cur.box != end.box)
				text_end = text->processed_text.length();
			else
				text_end = end.text_pos;
			adjust_start_of_line_text_range(text, text_start, text_end, start_of_line);

			output = new CL_CSSInlineGeneratedBox();
			output->box_node = cur.box->box_node;
			output->layout_node = cur.box->layout_node;
			output->text_start = text_start;
			output->text_end = text_end;
			output->closing = false;
			parent->add_box(output);
		}
		else if (cur.box->layout_node == 0)
		{
			output = new CL_CSSInlineGeneratedBox();
			output->box_node = cur.box->box_node;
			output->closing = false;
			parent->add_box(output);
		}
		else if (!cur.box->layout_node->get_element_node()->is_float())
		{
			start_of_line = false;

			output = new CL_CSSInlineGeneratedBox();
			output->box_node = cur.box->box_node;
			output->layout_node = cur.box->layout_node;
			parent->add_box(output);
		}

		if (cur.box == end.box)
			break;

		cur.text_pos = 0;
		if (cur.box->first_child)
		{
			cur.box = cur.box->first_child;
			parent = output;
		}
		else if (cur.box->next_sibling)
		{
			if (output)
				output->closing = true;
			cur.box = cur.box->next_sibling;
		}
		else
		{
			while (cur.box && !cur.box->next_sibling)
			{
				if (output)
					output->closing = true;
				cur.box = cur.box->parent;
				output = parent;
				if (parent)
					parent = parent->parent;
			}
			if (cur.box)
			{
				if (output)
					output->closing = true;
				cur.box = cur.box->next_sibling;
			}
		}
	}

	lines.push_back(line.get());
	line.release();
}

bool CL_CSSInlineLayout::place_floats(CL_CSSInlinePosition start, CL_CSSInlinePosition end, CL_CSSActualValue x, CL_CSSActualValue y, LayoutStrategy strategy)
{
	CL_CSSInlineGeneratedBox *cur = start.box;
	while (cur != end.box)
	{
		if (cur->layout_node && !cur->floated && cur->layout_node->get_element_node()->is_float())
		{
			cur->floated = true;
			floats.push_back(cur->layout_node);
			CL_CSSActualValue float_width = cur->layout_node->get_block_width();
			CL_CSSActualValue float_height = cur->layout_node->get_block_height();

			if (cur->layout_node->get_element_node()->computed_properties.clear.type == CL_CSSBoxClear::type_left || cur->layout_node->get_element_node()->computed_properties.clear.type == CL_CSSBoxClear::type_both)
			{
				CL_CSSActualValue clear_left = formatting_context->find_left_clearance();
				y = cl_max(y, clear_left);
			}
			if (cur->layout_node->get_element_node()->computed_properties.clear.type == CL_CSSBoxClear::type_right || cur->layout_node->get_element_node()->computed_properties.clear.type == CL_CSSBoxClear::type_both)
			{
				CL_CSSActualValue clear_right = formatting_context->find_right_clearance();
				y = cl_max(y, clear_right);
			}

			CL_Rect float_box(0, 0, cur->layout_node->get_block_width(), cur->layout_node->get_block_height());
			float_box.translate(x, y);

			if (strategy == preferred_strategy && width.expanding)
			{
				CL_CSSActualValue w = 1000000;
				if (cur->layout_node->get_element_node()->computed_properties.float_box.type == CL_CSSBoxFloat::type_left)
				{
					float_box = formatting_context->float_left(float_box, x+w);
				}
				else if (cur->layout_node->get_element_node()->computed_properties.float_box.type == CL_CSSBoxFloat::type_right)
				{
					float_box = formatting_context->float_right_shrink_to_fit(float_box, x+w);
				}
				cur->layout_node->set_root_block_position(float_box.left, float_box.top);
			}
			else
			{
				if (cur->layout_node->get_element_node()->computed_properties.float_box.type == CL_CSSBoxFloat::type_left)
				{
					float_box = formatting_context->float_left(float_box, x+cl_used_to_actual(width.value));
				}
				else if (cur->layout_node->get_element_node()->computed_properties.float_box.type == CL_CSSBoxFloat::type_right)
				{
					float_box.translate(width.value-float_box.get_width(), 0);
					float_box = formatting_context->float_right(float_box, x+cl_used_to_actual(width.value));
				}
				cur->layout_node->set_root_block_position(float_box.left, float_box.top);
			}

			if (strategy != normal_strategy && width.expanding)
				width.value = cl_max(width.value, float_box.right - x);

			return true;
		}

		if (cur->first_child)
		{
			cur = cur->first_child;
		}
		else if (cur->next_sibling)
		{
			cur = cur->next_sibling;
		}
		else
		{
			while (cur && !cur->next_sibling)
			{
				cur = cur->parent;
			}
			if (cur)
			{
				cur = cur->next_sibling;
			}
		}
	}
	return false;
}

void CL_CSSInlineLayout::adjust_start_of_line_text_range(CL_CSSBoxText *text, size_t &text_start, size_t &text_end, bool &start_of_line) const
{
	if (start_of_line && text_start < text_end)
	{
		const CL_CSSBoxProperties &properties = text->get_properties();
		if (properties.white_space.type == CL_CSSBoxWhiteSpace::type_pre || properties.white_space.type == CL_CSSBoxWhiteSpace::type_pre_wrap)
		{
			start_of_line = false;
		}
		else
		{
			text_start = text->processed_text.find_first_not_of(' ', text_start);
			if (text_start == CL_String::npos || text_start >= text_end)
			{
				text_start = text_end;
			}
			else if (text->processed_text[text_start] != ' ')
			{
				start_of_line = false;
			}
		}
	}
}

bool CL_CSSInlineLayout::is_empty_line(CL_CSSInlinePosition start, CL_CSSInlinePosition end) const
{
	bool start_of_line = true;
	CL_CSSInlinePosition cur = start;
	while (cur != end)
	{
		CL_CSSBoxText *text = dynamic_cast<CL_CSSBoxText *>(cur.box->box_node);
		CL_CSSBoxElement *element = dynamic_cast<CL_CSSBoxElement *>(cur.box->box_node);
		if (text)
		{
			size_t text_start = cur.text_pos;
			size_t text_end;
			if (cur.box != end.box)
				text_end = text->processed_text.length();
			else
				text_end = end.text_pos;

			adjust_start_of_line_text_range(text, text_start, text_end, start_of_line);

			if (text->processed_text.substr(text_start, text_end - text_start).find_first_not_of(' ') != CL_String::npos)
				return false;
		}
		else if (cur.box->layout_node && !cur.box->layout_node->get_element_node()->is_float())
		{
			if (!cur.box->layout_node->is_empty())
				return false;
		}

		if (cur.box == end.box)
			break;

		cur.text_pos = 0;
		if (cur.box->first_child)
		{
			cur.box = cur.box->first_child;
		}
		else if (cur.box->next_sibling)
		{
			cur.box = cur.box->next_sibling;
		}
		else
		{
			while (cur.box && !cur.box->next_sibling)
			{
				cur.box = cur.box->parent;
				if (cur.box)
					element = dynamic_cast<CL_CSSBoxElement *>(cur.box->box_node);
			}
			if (cur.box)
			{
				cur.box = cur.box->next_sibling;
			}
		}
	}
	return true;
}

CL_CSSActualValue CL_CSSInlineLayout::get_width(CL_GraphicContext &gc, CL_CSSResourceCache *resources, CL_CSSInlinePosition start, CL_CSSInlinePosition end, bool &start_of_line)
{
	CL_CSSActualValue width = 0;
	CL_CSSInlinePosition cur = start;
	while (cur != end)
	{
		CL_CSSBoxText *text = dynamic_cast<CL_CSSBoxText *>(cur.box->box_node);
		CL_CSSBoxElement *element = dynamic_cast<CL_CSSBoxElement *>(cur.box->box_node);
		if (text)
		{
			size_t text_start = cur.text_pos;
			size_t text_end;
			if (cur.box != end.box)
				text_end = text->processed_text.length();
			else
				text_end = end.text_pos;

			adjust_start_of_line_text_range(text, text_start, text_end, start_of_line);
			CL_Font font = resources->get_font(gc, text->get_properties());
			width += font.get_text_size(gc, text->processed_text.substr(text_start, text_end - text_start)).width;
		}
		else if (element && !element->is_float())
		{
			if (cur.box->layout_node)
				start_of_line = false;

			if (cur.box->layout_node && (cur.box->layout_node->is_replaced() || cur.box->layout_node->get_element_node()->is_inline_block_level()))
			{
				width += cur.box->layout_node->get_block_width();
			}
			else
			{
				width += cl_used_to_actual(get_css_margin_width(element->computed_properties.margin_width_left, containing_width)) + cl_used_to_actual(element->computed_properties.border_width_left.length.value) + cl_used_to_actual(get_css_padding_width(element->computed_properties.padding_width_left, containing_width));
			}
		}

		if (cur.box == end.box)
			break;

		cur.text_pos = 0;
		if (cur.box->first_child)
		{
			cur.box = cur.box->first_child;
		}
		else if (cur.box->next_sibling)
		{
			if (element && !element->is_float())
				width += cl_used_to_actual(get_css_margin_width(element->computed_properties.margin_width_right, containing_width)) + cl_used_to_actual(element->computed_properties.border_width_right.length.value) + cl_used_to_actual(get_css_padding_width(element->computed_properties.padding_width_right, containing_width));
			cur.box = cur.box->next_sibling;
		}
		else
		{
			while (cur.box && !cur.box->next_sibling)
			{
				if (element && !element->is_float() && (cur.box->layout_node == 0 || !(cur.box->layout_node->is_replaced() || cur.box->layout_node->get_element_node()->is_inline_block_level())))
					width += cl_used_to_actual(get_css_margin_width(element->computed_properties.margin_width_right, containing_width)) + cl_used_to_actual(element->computed_properties.border_width_right.length.value) + cl_used_to_actual(get_css_padding_width(element->computed_properties.padding_width_right, containing_width));

				cur.box = cur.box->parent;
				if (cur.box)
					element = dynamic_cast<CL_CSSBoxElement *>(cur.box->box_node);
			}
			if (cur.box)
			{
				if (element && !element->is_float() && (cur.box->layout_node == 0 || !(cur.box->layout_node->is_replaced() || cur.box->layout_node->get_element_node()->is_inline_block_level())))
					width += cl_used_to_actual(get_css_margin_width(element->computed_properties.margin_width_right, containing_width)) + cl_used_to_actual(element->computed_properties.border_width_right.length.value) + cl_used_to_actual(get_css_padding_width(element->computed_properties.padding_width_right, containing_width));
				cur.box = cur.box->next_sibling;
			}
		}
	}
	return width;
}

void CL_CSSInlineLayout::layout_inline_blocks_and_floats(CL_GraphicContext &gc, CL_CSSResourceCache *resources, LayoutStrategy strategy)
{
	floats.clear();
	CL_CSSInlineGeneratedBox *cur = boxes.first_child;
	while (cur)
	{
		if (cur->layout_node && (cur->layout_node->get_element_node()->is_float() || cur->layout_node->get_element_node()->is_inline_block_level() || cur->layout_node->is_replaced()))
		{
			/*if (cur->layout_node->get_element_node()->name.find("abc") != CL_String::npos)
			{
				Sleep(1);
			}*/
			cur->floated = false;
			cur->layout_node->relative_x = relative_x + cur->layout_node->get_local_relative_x();
			cur->layout_node->relative_y = relative_y + cur->layout_node->get_local_relative_y();
			cur->layout_node->containing_width = width;
			cur->layout_node->layout_float(gc, resources, strategy);

			if (strategy == minimum_strategy && width.expanding)
				width.value = cl_max(width.value, cur->layout_node->get_block_width());
		}

		if (cur->first_child)
		{
			cur = cur->first_child;
		}
		else if (cur->next_sibling)
		{
			cur = cur->next_sibling;
		}
		else
		{
			while (cur && !cur->next_sibling)
			{
				cur = cur->parent;
			}
			if (cur)
			{
				cur = cur->next_sibling;
			}
		}
	}
}

void CL_CSSInlineLayout::layout_line(CL_CSSInlineGeneratedBox *line, CL_Rect &line_box, CL_GraphicContext &gc, CL_CSSResourceCache *resources)
{
	CL_CSSInlineGeneratedBox *cur = line->first_child;
	CL_CSSActualValue x = line_box.left;
	CL_CSSActualValue baseline_offset = 0;
	line->y = line_box.top;
	while (cur)
	{
		cur->y = line->y;

		CL_CSSBoxText *text = dynamic_cast<CL_CSSBoxText *>(cur->box_node);
		CL_CSSBoxElement *element = dynamic_cast<CL_CSSBoxElement *>(cur->box_node);
		if (text)
		{
			cur->x = x;
			const CL_CSSBoxProperties &properties = text->get_properties();
			CL_Font font = resources->get_font(gc, properties);
			CL_FontMetrics metrics = font.get_font_metrics(gc);
			cur->ascent = cl_used_to_actual(metrics.get_ascent());
			cur->descent = cl_used_to_actual(metrics.get_descent());
			switch (properties.line_height.type)
			{
			default:
			case CL_CSSBoxLineHeight::type_normal:
				cur->height = cur->ascent + cur->descent;
				break;
			case CL_CSSBoxLineHeight::type_length:
				cur->height = cl_used_to_actual(properties.line_height.length.value);
				break;
			case CL_CSSBoxLineHeight::type_number:
				cur->height = cl_used_to_actual(properties.line_height.number * properties.font_size.length.value);
				break;
			}
			cur->baseline_offset = baseline_offset;
			cur->parent->ascent = cl_max(cur->parent->ascent, cur->ascent);
			cur->parent->descent = cl_max(cur->parent->descent, cur->descent);
			cur->parent->height = cl_max(cur->parent->height, cur->height);
			CL_String t = text->processed_text.substr(cur->text_start, cur->text_end - cur->text_start);
			cur->width = font.get_text_size(gc, t).width;
			x += cur->width;
		}
		else if (element)
		{
			if (cur->layout_node && (cur->layout_node->is_replaced() || cur->layout_node->get_element_node()->is_inline_block_level()))
			{
				cur->height = cur->layout_node->get_block_height();
				cur->ascent = cur->height; // To do: fetch baseline from layout node
				cur->parent->ascent = cl_max(cur->parent->ascent, cur->ascent);
				cur->parent->height = cl_max(cur->parent->height, cur->height);
				cur->x = x;
				x += cur->layout_node->get_block_width();
			}
			else
			{
				if (cur->opening)
					x += cl_used_to_actual(get_css_margin_width(element->computed_properties.margin_width_left, containing_width)) + cl_used_to_actual(element->computed_properties.border_width_left.length.value) + cl_used_to_actual(get_css_padding_width(element->computed_properties.padding_width_left, containing_width));
				cur->x = x;
				cur->height = cl_used_to_actual(element->computed_properties.line_height.length.value);
				switch (element->computed_properties.line_height.type)
				{
				default:
				case CL_CSSBoxLineHeight::type_normal:
					break;
				case CL_CSSBoxLineHeight::type_length:
					cur->height = cl_used_to_actual(element->computed_properties.line_height.length.value);
					break;
				case CL_CSSBoxLineHeight::type_number:
					cur->height = cl_used_to_actual(element->computed_properties.line_height.number * element->computed_properties.font_size.length.value);
					break;
				}
			}
		}

		if (cur->first_child)
		{
			cur = cur->first_child;
		}
		else if (cur->next_sibling)
		{
			cur->width = x - cur->x;
			cur->parent->ascent = cl_max(cur->parent->ascent, cur->ascent);
			cur->parent->descent = cl_max(cur->parent->descent, cur->descent);
			cur->parent->height = cl_max(cur->parent->height, cur->height);
			if (element && cur->closing && (cur->layout_node == 0 || !(cur->layout_node->is_replaced() || cur->layout_node->get_element_node()->is_inline_block_level())))
			{
				x += cl_used_to_actual(get_css_margin_width(element->computed_properties.margin_width_right, containing_width)) + cl_used_to_actual(element->computed_properties.border_width_right.length.value) + cl_used_to_actual(get_css_padding_width(element->computed_properties.padding_width_right, containing_width));
			}

			cur = cur->next_sibling;
		}
		else
		{
			while (cur && !cur->next_sibling)
			{
				cur->width = x - cur->x;
				if (cur->parent)
				{
					cur->parent->ascent = cl_max(cur->parent->ascent, cur->ascent);
					cur->parent->descent = cl_max(cur->parent->descent, cur->descent);
					cur->parent->height = cl_max(cur->parent->height, cur->height);
				}
				if (element && cur->closing && (cur->layout_node == 0 || !(cur->layout_node->is_replaced() || cur->layout_node->get_element_node()->is_inline_block_level())))
				{
					x += cl_used_to_actual(get_css_margin_width(element->computed_properties.margin_width_right, containing_width)) + cl_used_to_actual(element->computed_properties.border_width_right.length.value) + cl_used_to_actual(get_css_padding_width(element->computed_properties.padding_width_right, containing_width));
				}

				cur = cur->parent;
				if (cur)
					element = dynamic_cast<CL_CSSBoxElement *>(cur->box_node);
			}
			if (cur)
			{
				cur->width = x - cur->x;
				cur->parent->ascent = cl_max(cur->parent->ascent, cur->ascent);
				cur->parent->descent = cl_max(cur->parent->descent, cur->descent);
				cur->parent->height = cl_max(cur->parent->height, cur->height);
				if (element && cur->closing && (cur->layout_node == 0 || !(cur->layout_node->is_replaced() || cur->layout_node->get_element_node()->is_inline_block_level())))
				{
					x += cl_used_to_actual(get_css_margin_width(element->computed_properties.margin_width_right, containing_width)) + cl_used_to_actual(element->computed_properties.border_width_right.length.value) + cl_used_to_actual(get_css_padding_width(element->computed_properties.padding_width_right, containing_width));
				}

				cur = cur->next_sibling;
			}
		}
	}

	switch (get_element_node()->computed_properties.line_height.type)
	{
	default:
	case CL_CSSBoxLineHeight::type_normal:
		break;
	case CL_CSSBoxLineHeight::type_length:
		line->height = cl_max(line->height, cl_used_to_actual(get_element_node()->computed_properties.line_height.length.value));
		break;
	case CL_CSSBoxLineHeight::type_number:
		line->height = cl_max(line->height, cl_used_to_actual(get_element_node()->computed_properties.line_height.number * get_element_node()->computed_properties.font_size.length.value));
		break;
	}

	//CL_CSSActualValue line_width = x - line_box.left;
	//CL_CSSActualValue extra_total = cl_max(0, line_box.get_width() - line_width);
	line->width = line_box.get_width();
	line_box.bottom = line->y + line->height;
}

void CL_CSSInlineLayout::align_line(CL_CSSInlineGeneratedBox *line, CL_GraphicContext &gc, CL_CSSResourceCache *resources, bool last_line)
{
	CL_CSSActualValue segments_width = line->last_child->x + line->last_child->width - line->first_child->x;
	CL_CSSActualValue extra_total = cl_max(0, line->width - segments_width);
	CL_CSSActualValue offset_x = 0;
	int word_count = 0;
	int word_index = 0;
	if (get_element_node()->computed_properties.text_align.type == CL_CSSBoxTextAlign::type_right)
	{
		offset_x = extra_total;
	}
	else if (get_element_node()->computed_properties.text_align.type == CL_CSSBoxTextAlign::type_center)
	{
		offset_x = extra_total / 2;
	}
	else if (get_element_node()->computed_properties.text_align.type == CL_CSSBoxTextAlign::type_justify && !last_line)
	{
		word_count = find_word_count(line);
	}

	bool start_of_line = true;
	bool prev_space = true;
	int baseline_y = line->y + (line->height - line->ascent - line->descent) / 2 + line->ascent;
	CL_CSSInlineGeneratedBox *cur = line->first_child;
	while (cur)
	{
		cur->x += offset_x;
		cur->y = baseline_y - cur->ascent;
		if (cur->layout_node && (cur->layout_node->is_replaced() || cur->layout_node->get_element_node()->is_inline_block_level()))
		{
			cur->layout_node->set_root_block_position(cur->x, cur->y);
		}

		if (word_count != 0)
		{
			CL_CSSBoxNode *node = cur->box_node;
			CL_CSSBoxText *text = dynamic_cast<CL_CSSBoxText*>(node);
			if (text)
			{
				for (size_t j = cur->text_start; j < cur->text_end; j++)
				{
					if (text->processed_text[j] == ' ')
					{
						prev_space = true;
					}
					else
					{
						if (prev_space && !start_of_line)
						{
							split_text(cur, j, gc, resources);
							cur = cur->next_sibling;

							CL_CSSActualValue v1 = extra_total * word_index / word_count;
							CL_CSSActualValue v2 = extra_total * (word_index + 1) / word_count;
							CL_CSSActualValue word_offset_x = v2-v1;
							word_index++;

							cur->x += word_offset_x;
							if (cur->parent)
								expand_box(cur->parent, word_offset_x);
							offset_x += word_offset_x;
						}
						prev_space = false;
						start_of_line = false;
					}
				}
			}
		}

		if (cur->first_child)
		{
			cur = cur->first_child;
		}
		else if (cur->next_sibling)
		{
			cur = cur->next_sibling;
		}
		else
		{
			while (cur && !cur->next_sibling)
			{
				cur = cur->parent;
			}
			if (cur)
			{
				cur = cur->next_sibling;
			}
		}
	}
}

void CL_CSSInlineLayout::split_text(CL_CSSInlineGeneratedBox *box, size_t text_pos, CL_GraphicContext &gc, CL_CSSResourceCache *resources)
{
	// Duplicate box:
	{
		std::auto_ptr<CL_CSSInlineGeneratedBox> box2(new CL_CSSInlineGeneratedBox());
		box2->box_node = box->box_node;
		box2->x = box->x;
		box2->y = box->y;
		box2->width = box->width;
		box2->height = box->height;
		box2->ascent = box->ascent;
		box2->descent = box->descent;
		box2->baseline_offset = box->baseline_offset;
		box2->text_start = text_pos;
		box2->text_end = box->text_end;
		box->text_end = text_pos;

		box2->parent = box->parent;
		box2->next_sibling = box->next_sibling;
		box->next_sibling = box2.get();
		if (box->parent && box->parent->last_child == box)
			box->parent->last_child = box2.get();
		box2.release();
	}

	CL_CSSInlineGeneratedBox *box2 = box->next_sibling;

	CL_CSSBoxText *text = dynamic_cast<CL_CSSBoxText *>(box->box_node);

	const CL_CSSBoxProperties &properties = text->get_properties();
	CL_Font font = resources->get_font(gc, properties);

	box->width = font.get_text_size(gc, text->processed_text.substr(box->text_start, box->text_end-box->text_start)).width;
	box2->width = font.get_text_size(gc, text->processed_text.substr(box2->text_start, box2->text_end-box2->text_start)).width;
	box2->x += box->width;
}

void CL_CSSInlineLayout::expand_box(CL_CSSInlineGeneratedBox *box, CL_CSSActualValue extra)
{
	while (box->parent)
	{
		box->width += extra;
		box = box->parent;
	}
}

int CL_CSSInlineLayout::find_word_count(CL_CSSInlineGeneratedBox *line)
{
	bool start_of_line = true;
	int word_count = 0;
	bool prev_space = true;
	CL_CSSInlineGeneratedBox *cur = line;
	while (cur)
	{
		CL_CSSBoxNode *node = cur->box_node;
		CL_CSSBoxText *text = dynamic_cast<CL_CSSBoxText*>(node);
		if (text)
		{
			for (size_t j = cur->text_start; j < cur->text_end; j++)
			{
				if (text->processed_text[j] == ' ')
				{
					prev_space = true;
				}
				else
				{
					if (prev_space && !start_of_line)
						word_count++;
					prev_space = false;
					start_of_line = false;
				}
			}
		}

		if (cur->first_child)
		{
			cur = cur->first_child;
		}
		else if (cur->next_sibling)
		{
			cur = cur->next_sibling;
		}
		else
		{
			while (cur && !cur->next_sibling)
			{
				cur = cur->parent;
			}
			if (cur)
			{
				cur = cur->next_sibling;
			}
		}
	}
	return word_count;
}

void CL_CSSInlineLayout::layout_block_line(CL_CSSInlineGeneratedBox *line, CL_GraphicContext &gc, CL_CSSLayoutCursor &cursor, LayoutStrategy strategy)
{
	if (line->layout_node->get_element_node()->is_overflow_visible() && !line->layout_node->get_element_node()->is_table() && !line->layout_node->is_replaced())
	{
		line->layout_node->containing_width = width;
		line->layout_node->layout_normal(gc, cursor, strategy);
		if (strategy != normal_strategy && width.expanding)
			width.value = cl_max(width.value, cl_actual_to_used(line->layout_node->get_block_width()));
	}
	else
	{
		int box_y = cl_used_to_actual(cursor.y+cursor.get_total_margin());
		if (line->layout_node->get_element_node()->computed_properties.clear.type == CL_CSSBoxClear::type_left || line->layout_node->get_element_node()->computed_properties.clear.type == CL_CSSBoxClear::type_both)
		{
			int clear_left = formatting_context->find_left_clearance();
			box_y = cl_max(box_y, clear_left);
		}
		if (line->layout_node->get_element_node()->computed_properties.clear.type == CL_CSSBoxClear::type_right || line->layout_node->get_element_node()->computed_properties.clear.type == CL_CSSBoxClear::type_both)
		{
			int clear_right = formatting_context->find_right_clearance();
			box_y = cl_max(box_y, clear_right);
		}

		line->layout_node->containing_width = width;
		if (strategy == normal_strategy)
		{
			CL_CSSActualValue available_width = formatting_context->find_line_box(cursor.x, cursor.x + cl_used_to_actual(width.value), box_y, 1, 0).get_width();
			line->layout_node->containing_width.value = available_width;
		}
		line->layout_node->calculate_top_down_widths(strategy);
		line->layout_node->calculate_top_down_heights();
		line->layout_node->layout_formatting_root_helper(gc, cursor.resources, strategy);

		CL_Rect float_box(0, 0, line->layout_node->get_block_width(), line->layout_node->get_block_height());
		float_box.translate(cursor.x, box_y);
		if (strategy == preferred_strategy && width.expanding)
		{
			float_box = formatting_context->place_left(float_box, cursor.x+1000000);
			cursor.apply_margin();
			cursor.y = float_box.bottom;
		}
		else
		{
			float_box = formatting_context->place_left(float_box, cursor.x+cl_used_to_actual(width.value));
			cursor.apply_margin();
			cursor.y = float_box.bottom;
		}

		if (strategy != normal_strategy && width.expanding)
			width.value = cl_max(width.value, cl_actual_to_used(float_box.right - cursor.x));

		line->layout_node->set_root_block_position(float_box.left, float_box.top);
	}
}

/////////////////////////////////////////////////////////////////////////////

CL_CSSInlineGeneratedBox::CL_CSSInlineGeneratedBox()
: opening(true), closing(true), text_start(0), text_end(0), box_node(0), layout_node(0),
  floated(false), x(0), width(0), y(0), height(0), ascent(0), descent(0), baseline_offset(0), parent(0), first_child(0), last_child(0), next_sibling(0)
{
}

CL_CSSInlineGeneratedBox::~CL_CSSInlineGeneratedBox()
{
	CL_CSSInlineGeneratedBox *cur = first_child;
	while (cur)
	{
		CL_CSSInlineGeneratedBox *next = cur->next_sibling;
		delete cur;
		cur = next;
	}
}

void CL_CSSInlineGeneratedBox::add_box(CL_CSSInlineGeneratedBox *child)
{
	child->parent = this;
	if (last_child)
	{
		last_child->next_sibling = child;
		last_child = child;
	}
	else
	{
		first_child = child;
		last_child = child;
	}
}
