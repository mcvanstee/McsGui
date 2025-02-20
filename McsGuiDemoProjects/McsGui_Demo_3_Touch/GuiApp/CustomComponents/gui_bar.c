#include "gui_bar.h"

#include "gui_app.h"
#include "colors.h"
#include "Graphics/gui_graphics.h"
#include "Utils/gui_log.h"
#include "Utils/gui_memory.h"
#include "fs_file_search.h"

#define GUI_BAR_BUFFER_SIZE 8


#if !GUI_USE_DYNAMIC_MEMORY
static bool staticBarMemInUse[GUI_BAR_BUFFER_SIZE];
static Bar_s staticBarMem[GUI_BAR_BUFFER_SIZE];
#endif /* GUI_USE_DYNAMIC_MEMORY */

static void bar_onDisplay(BaseComponent_s *p_base);
static void bar_delete(BaseComponent_s *p_baseComponent);


Bar_s* bar_new(void)
{
#if GUI_USE_DYNAMIC_MEMORY
	return gui_mem_malloc(sizeof(Bar_s));
#else
	for (uint32_t i = 0; i < GUI_BAR_BUFFER_SIZE; i++)
	{
		if (!staticBarMemInUse[i])
		{
			staticBarMemInUse[i] = true;

			return &staticBarMem[i];
		}
	}

	gui_log_write(GUI_LOG_LEVEL_ERROR, "No Bar_s static memory");

	return NULL;
#endif /* GUI_USE_DYNAMIC_MEMORY */
}

Bar_s* bar_newInit(void)
{
	Bar_s *p_bar = bar_new();
	bar_init(p_bar);

	return p_bar;
}

static void bar_delete(BaseComponent_s *p_baseComponent)
{
	base_clear(p_baseComponent);
#if GUI_USE_DYNAMIC_MEMORY
	gui_mem_free(p_baseComponent, sizeof(Bar_s));
#else
	for (uint32_t i = 0; i < GUI_BAR_BUFFER_SIZE; i++)
	{
		if (&staticBarMem[i].base == p_baseComponent)
		{
			staticBarMemInUse[i] = false;

			break;
		}
	}
#endif /* GUI_USE_DYNAMIC_MEMORY */
}

void bar_init(Bar_s *p_bar)
{
	base_initParentComp(&p_bar->base, bar_delete);
	base_setOnDisplay(p_bar, bar_onDisplay);
	base_setSize(p_bar, BAR_WIDTH, BAR_HEIGHT);

	p_bar->fillColor = COLOR_ACCENT_BLUE;
	p_bar->emptyColor = COLOR_BAR_BACKGROUND;
	p_bar->borderColor = COLOR_SEPARATOR;
	p_bar->level = 0;
}

void bar_setLevel(Bar_s *p_bar, uint8_t level)
{
	p_bar->level = level;
}

void bar_updateLevel(Bar_s *p_bar, uint8_t level)
{
	p_bar->level = level;
	base_display(p_bar);
}

void bar_setColors(Bar_s *p_bar, Color_t fillColor, Color_t emptyColor, Color_t borderColor)
{
	p_bar->fillColor = fillColor;
	p_bar->emptyColor = emptyColor;
	p_bar->borderColor = borderColor;
}

static void bar_onDisplay(BaseComponent_s *p_base)
{
	Bar_s *p_bar = (Bar_s*) p_base;

    if (p_base->p_anchor != NULL)
    {
        graphics_setPosistionFromAnchor(p_base);
    }

    Rectangle_s background;
    rectangle_initFillBorderPosSize(
    		&background, p_bar->emptyColor,
			p_base->x, p_base->y,
			p_base->width, p_base->height,
			1, p_bar->borderColor);
    rectangle_setRadius(&background, 3);
	base_display(&background);

	uint16_t fillHeight = p_base->height * p_bar->level / 100;

	Rectangle_s fill;
    rectangle_initFillSize(&fill, p_bar->fillColor, p_base->width, fillHeight);
    rectangle_setRadius(&fill, 3);

    GuiAnchor_s anchor;
    anchor_init(&anchor);
    base_addAnchor(&fill, &anchor);
    anchor_setBottomAnchor(&fill, p_base, Gui_Anchor_Bottom);
    anchor_setLeftAnchor(&fill, p_base, Gui_Anchor_Left);
    base_display(&fill);
}
