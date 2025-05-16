#include "gui_color_checkbox.h"

#include <stddef.h>
#include <string.h>

#include "gui_app.h"
#include "Graphics/gui_graphics.h"
#include "Utils/gui_log.h"
#include "Utils/gui_memory.h"

#define GUI_COLOR_CHECKBOX_BUFFER_SIZE 6

#define COLOR_CHECKBOX_WIDTH 50
#define COLOR_CHECKBOX_HEIGHT 50
#define CHECKBOX_WIDTH 20
#define CHECKBOX_HEIGHT 20

#if !GUI_USE_DYNAMIC_MEMORY
static bool staticColorCheckboxMemInUse[GUI_COLOR_CHECKBOX_BUFFER_SIZE];
static ColorCheckbox_s staticColorCheckboxMem[GUI_COLOR_CHECKBOX_BUFFER_SIZE];
#endif /* GUI_USE_DYNAMIC_MEMORY */


static void color_checkbox_onDisplay(BaseComponent_s *p_baseComponent);
static void color_checkbox_focusChanged(BaseComponent_s *p_baseComponent);
static void color_checkbox_selectionChanged(Checkbox_s *p_checkbox);


ColorCheckbox_s *color_checkbox_new(void)
{
#if GUI_USE_DYNAMIC_MEMORY
    return gui_mem_malloc(sizeof(ColorCheckbox_s));
#else
    for (uint32_t i = 0; i < GUI_COLOR_CHECKBOX_BUFFER_SIZE; i++)
    {
        if (!staticColorCheckboxMemInUse[i])
        {
            staticColorCheckboxMemInUse[i] = true;

            return &staticColorCheckboxMem[i];
        }
    }

    gui_log_write(GUI_LOG_LEVEL_ERROR, "No ColorCheckbox_s static memory");

    return NULL;
#endif /* GUI_USE_DYNAMIC_MEMORY */
}

ColorCheckbox_s* color_checkbox_newInit(void)
{
    ColorCheckbox_s *p_colorCheckbox = color_checkbox_new();
    if (p_colorCheckbox != NULL)
    {
        color_checkbox_init(p_colorCheckbox);
    }

    return p_colorCheckbox;
}

void color_checkbox_delete(BaseComponent_s *p_colorCheckboxBase)
{
    base_clear(p_colorCheckboxBase);
#if GUI_USE_DYNAMIC_MEMORY
    gui_mem_free(p_colorCheckboxBase, sizeof(ColorCheckbox_s));
#else
    for (uint32_t i = 0; i < GUI_COLOR_CHECKBOX_BUFFER_SIZE; i++)
    {
        if (&staticColorCheckboxMem[i].checkbox.base == p_colorCheckboxBase)
        {
            staticColorCheckboxMemInUse[i] = false;
            break;
        }
    }
#endif /* GUI_USE_DYNAMIC_MEMORY */
}

void color_checkbox_init(ColorCheckbox_s *p_colorCheckbox)
{
    checkbox_init(&p_colorCheckbox->checkbox);
    p_colorCheckbox->color = 0;
    base_setBmpKey(p_colorCheckbox, FILE_KEY_ICON_PANE_CHECKMARK);
    base_setSize(p_colorCheckbox, COLOR_CHECKBOX_WIDTH, COLOR_CHECKBOX_HEIGHT);
    base_setOnDisplay(p_colorCheckbox, color_checkbox_onDisplay);
    base_setOnDelete(p_colorCheckbox, color_checkbox_delete);
    base_setOnFocusChanged(p_colorCheckbox, color_checkbox_focusChanged);
    base_setHorizontalAlignment(p_colorCheckbox, Gui_Align_Right);
    base_setVerticalAlignment(p_colorCheckbox, Gui_Align_Top);
    checkbox_setOnSelectionChanged(&p_colorCheckbox->checkbox, color_checkbox_selectionChanged);
    keynav_init(&p_colorCheckbox->keyNavigation);
    base_addKeyNavigation(p_colorCheckbox, &p_colorCheckbox->keyNavigation);
}

static void color_checkbox_onDisplay(BaseComponent_s *p_baseComponent)
{
    Color_t borderColor;
    ColorCheckbox_s *p_colorCheckbox = (ColorCheckbox_s *)p_baseComponent;

    if (p_baseComponent->focused)
    {
        borderColor = (g_guiApp.theme.theme ==  PROPERTY_THEME_VALUE_DARK) ? COLOR_ACCENT_WHITE : COLOR_ACCENT_BLACK;
    }
    else
    {
        borderColor = p_colorCheckbox->color;
    }

    Rectangle_s rect;
    rectangle_initFillPosSize(
            &rect, p_colorCheckbox->color,
            p_baseComponent->x, p_baseComponent->y,
            p_baseComponent->width, p_baseComponent->height);
    rectangle_setRadius(&rect, 3);
    base_display(&rect);

    color_checkbox_selectionChanged(&p_colorCheckbox->checkbox);

    Rectangle_s border;
    rectangle_initBorderPosSize(
            &border,
            p_baseComponent->x, p_baseComponent->y,
            p_baseComponent->width, p_baseComponent->height
            , 2, borderColor);
    rectangle_setRadius(&border, 3);
    base_display(&border);
}

static void color_checkbox_focusChanged(BaseComponent_s *p_baseComponent)
{
    Color_t borderColor = (g_guiApp.theme.theme ==  PROPERTY_THEME_VALUE_DARK) ? COLOR_ACCENT_WHITE : COLOR_ACCENT_BLACK;
    ColorCheckbox_s *p_colorCheckbox = (ColorCheckbox_s *)p_baseComponent;
    Checkbox_s *p_checkbox = &p_colorCheckbox->checkbox;

    if (!p_baseComponent->focused)
    {
        borderColor = p_colorCheckbox->color;
    }

    if (p_checkbox->checked)
    {
        Rectangle_s border;
        rectangle_initBorderPosSize(
                &border,
                p_baseComponent->x, p_baseComponent->y,
                CHECKBOX_WIDTH, CHECKBOX_HEIGHT,
                3, theme_getPaneColor());

        GuiAnchor_s anchorBorder;
        anchor_init(&anchorBorder);
        base_addAnchor(&border, &anchorBorder);
        anchor_setRightAnchor(&border, p_baseComponent, Gui_Anchor_Right);
        anchor_setTopAnchor(&border, p_baseComponent, Gui_Anchor_Top);

        base_display(&border);
    }

    Rectangle_s border;
    rectangle_initBorderPosSize(
            &border,
            p_baseComponent->x, p_baseComponent->y,
            p_baseComponent->width, p_baseComponent->height,
            2, borderColor);
    rectangle_setRadius(&border, 3);
    base_display(&border);
}

static void color_checkbox_selectionChanged(Checkbox_s *p_checkbox)
{
    BaseComponent_s *p_base = &p_checkbox->base;
    ColorCheckbox_s *p_colorCheckbox = (ColorCheckbox_s *)p_base;

    if (p_checkbox->checked)
    {
        Rectangle_s border;
        rectangle_initFillPosSize(
                &border, theme_getPaneColor(),
                p_base->x, p_base->y,
                CHECKBOX_WIDTH, CHECKBOX_HEIGHT);

        GuiAnchor_s anchorBorder;
        anchor_init(&anchorBorder);
        base_addAnchor(&border, &anchorBorder);
        anchor_setRightAnchor(&border, p_base, Gui_Anchor_Right);
        anchor_setTopAnchor(&border, p_base, Gui_Anchor_Top);

        base_display(&border);

        Label_s label;
        label_initBmpPosSize(
                &label, FILE_KEY_ICON_PANE_CHECKMARK,
                p_base->x, p_base->y,
                CHECKBOX_WIDTH, CHECKBOX_HEIGHT);
        theme_setTheme(&label);

        GuiAnchor_s anchorLabel;
        anchor_init(&anchorLabel);
        base_addAnchor(&label, &anchorLabel);
        anchor_setRightAnchor(&label, p_base, Gui_Anchor_Right);
        anchor_setTopAnchor(&label, p_base, Gui_Anchor_Top);

        base_display(&label);

        if (p_checkbox->base.focused)
        {
            const Color_t color = (g_guiApp.theme.theme ==  PROPERTY_THEME_VALUE_DARK) ? COLOR_ACCENT_WHITE : COLOR_ACCENT_BLACK;

            Rectangle_s border;
            rectangle_initBorderPosSize(&border, p_base->x, p_base->y, p_base->width, p_base->height, 2, color);
            rectangle_setRadius(&border, 3);
            base_display(&border);
        }
    }
    else
    {
        Rectangle_s rect;
        rectangle_initFillPosSize(
                &rect, p_colorCheckbox->color,
                p_base->x, p_base->y,
                CHECKBOX_WIDTH, CHECKBOX_HEIGHT);

        GuiAnchor_s anchorRect;
        anchor_init(&anchorRect);
        base_addAnchor(&rect, &anchorRect);
        anchor_setRightAnchor(&rect, p_base, Gui_Anchor_Right);
        anchor_setTopAnchor(&rect, p_base, Gui_Anchor_Top);

        base_display(&rect);
    }
}

void color_checkbox_setColor(ColorCheckbox_s *p_colorCheckbox, const Color_t color)
{
    p_colorCheckbox->color = color;
}
