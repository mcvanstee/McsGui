#include "gui_pane.h"

#include "colors.h"
#include "style.h"
#include "Graphics/gui_graphics.h"
#include "Core/gui_log.h"
#include "Core/gui_memory.h"

#define GUI_PANE_BUFFER_SIZE 5

#if !GUI_USE_DYNAMIC_MEMORY
static bool staticPaneMemInUse[GUI_PANE_BUFFER_SIZE];
static Pane_s staticPaneMem[GUI_PANE_BUFFER_SIZE];
#endif /* GUI_USE_DYNAMIC_MEMORY */

static void pane_onDisplay(BaseComponent_s *p_base);

Pane_s* pane_new(void)
{
#if GUI_USE_DYNAMIC_MEMORY
    return gui_mem_malloc(sizeof(Pane_s));
#else
    for (uint32_t i = 0; i < GUI_PANE_BUFFER_SIZE; i++)
    {
        if (!staticPaneMemInUse[i])
        {
            staticPaneMemInUse[i] = true;

            return &staticPaneMem[i];
        }
    }

    gui_log_write(GUI_LOG_LEVEL_ERROR, "No Pane_s static memory");

    return NULL;
#endif /* GUI_USE_DYNAMIC_MEMORY */
}

Pane_s* pane_newInit(void)
{
    Pane_s *p_pane = pane_new();
    pane_init(p_pane);

    return p_pane;
}

void pane_delete(BaseComponent_s *p_paneBase)
{
    base_clear(p_paneBase);

#if GUI_USE_DYNAMIC_MEMORY
    gui_mem_free(p_paneBase, sizeof(Pane_s));
#else
    for (uint32_t i = 0; i < GUI_PANE_BUFFER_SIZE; i++)
    {
        if (&staticPaneMem[i].base == p_paneBase)
        {
            staticPaneMemInUse[i] = false;

            break;
        }
    }
#endif /* GUI_USE_DYNAMIC_MEMORY */
}

void pane_init(Pane_s *p_pane)
{
    base_initParentComp(&p_pane->base, pane_delete);
    base_setOnDisplay(&p_pane->base, pane_onDisplay);
    p_pane->radius = 0;
    p_pane->borderPane = false;
}

void pane_setRadius(Pane_s *p_pane, uint8_t radius)
{
    p_pane->radius = radius;
}

void pane_setBorderPane(Pane_s *p_pane, bool borderPane)
{
    p_pane->borderPane = borderPane;
}

void pane_addComponent(Pane_s *p_pane, void *p_component)
{
	base_addChild(&p_pane->base, (BaseComponent_s *)p_component);
}

static void pane_onDisplay(BaseComponent_s *p_base)
{
	Pane_s *p_pane = (Pane_s*)p_base;

    if (p_base->p_anchor != NULL)
    {
        graphics_setPosistionFromAnchor(p_base);
    }

	if (p_pane->borderPane)
	{
		Rectangle_s paneBorder;
		rectangle_initBorderPosSize(
				&paneBorder,
				p_base->x, p_base->y,
				p_base->width, p_base->height,
				1, COLOR_SEPARATOR);
		rectangle_setRadius(&paneBorder, p_pane->radius);
		base_display(&paneBorder);
	}
	else
	{
		Rectangle_s paneBackground;
		rectangle_initFillPosSize(
				&paneBackground, COLOR_PANE,
				p_base->x, p_base->y,
				p_base->width, p_base->height);
		rectangle_setRadius(&paneBackground, p_pane->radius);
		base_display(&paneBackground);
	}

	graphics_displayComponent(p_base);
}
