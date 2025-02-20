#include "gui_pane.h"


#include "Utils/gui_log.h"
#include "Utils/gui_memory.h"


#define GUI_PANE_BORDER_THICKNESS 8
#define GUI_PANE_X (STYLE_VIEW_X + GUI_PANE_BORDER_THICKNESS)
#define GUI_PANE_Y (STYLE_VIEW_Y + GUI_PANE_BORDER_THICKNESS)
#define GUI_PANE_WIDTH (STYLE_VIEW_WIDTH - (2 * GUI_PANE_BORDER_THICKNESS))
#define GUI_PANE_HEIGHT (STYLE_VIEW_HEIGHT - (2 * GUI_PANE_BORDER_THICKNESS))

#define GUI_PANE_BUFFER_SIZE 1

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
    if (p_pane != NULL)
    {
        pane_init(p_pane);
    }

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
    base_setPosition(&p_pane->base, GUI_PANE_X, GUI_PANE_Y);
    base_setSize(&p_pane->base, GUI_PANE_WIDTH, GUI_PANE_HEIGHT);
}

static void pane_onDisplay(BaseComponent_s *p_base)
{
    Rectangle_s background;
    rectangle_init(&background);
    rectangle_showBorderOnly(&background, true);
    rectangle_setBorderThickness(&background, GUI_PANE_BORDER_THICKNESS);
    rectangle_setBorderColor(&background, theme_getBackgroundColor());
    base_setSize(&background, STYLE_VIEW_WIDTH, STYLE_VIEW_HEIGHT);
    base_setPosition(&background, STYLE_VIEW_X, STYLE_VIEW_Y);
    base_display(&background);

    Rectangle_s paneBorder;
    rectangle_init(&paneBorder);
    rectangle_showBorderOnly(&paneBorder, true);
    rectangle_setBorderThickness(&paneBorder, 1);
    rectangle_setBorderColor(&paneBorder, theme_getPaneBorderColor());
    rectangle_setRadius(&paneBorder, 5);
    base_setSize(&paneBorder, p_base->width, p_base->height);
    base_setPosition(&paneBorder, p_base->x + 1, p_base->y + 1);
    base_display(&paneBorder);

    Rectangle_s paneBackground;
    rectangle_initFillPosSize(
            &paneBackground, theme_getPaneColor(),
            p_base->x, p_base->y,
            p_base->width, p_base->height);
    rectangle_setRadius(&paneBackground, 5);
    base_display(&paneBackground);
}
