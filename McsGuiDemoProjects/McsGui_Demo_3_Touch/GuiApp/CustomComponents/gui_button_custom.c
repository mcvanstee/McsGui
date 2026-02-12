#include "gui_button_custom.h"

#include <stddef.h>
#include <string.h>

#include "gui_app.h"
#include "Core/gui_memory.h"
#include "Graphics/gui_graphics.h"

#define GUI_CONFIG_BUTTON_CUSTOM_BUFFER_SIZE 5


#if !GUI_USE_DYNAMIC_MEMORY
static bool staticButtonCustomMemInUse[GUI_CONFIG_BUTTON_CUSTOM_BUFFER_SIZE] = {0};
static ButtonCustom_s staticButtonCustomMem[GUI_CONFIG_BUTTON_CUSTOM_BUFFER_SIZE] = {0};
#endif /* GUI_USE_DYNAMIC_MEMORY */

static void btnc_onDisplay(BaseComponent_s *p_base);
static void btnc_displayCustomText(ButtonCustom_s *p_customButton, Rectangle_s *p_background);
static void btnc_displayIconAndCustomText(ButtonCustom_s *p_customButton, Rectangle_s *p_background);
static void btnc_displayIcon(ButtonCustom_s *p_customButton);
static void btnc_displayBmpText(ButtonCustom_s *p_customButton, Rectangle_s *p_background);
static void btnc_displayIconAndBmpText(ButtonCustom_s *p_customButton, Rectangle_s *p_background);
static void btnc_displayBackground(ButtonCustom_s *p_customButton);

/**
 * @brief Creates a new malloced ButtonCustom component.
 * @return Pointer to the malloced memory.
 *
 * @warning The returned component is not initialized.
 */
ButtonCustom_s *button_custom_new(void)
{
#if GUI_USE_DYNAMIC_MEMORY
    return gui_mem_malloc(sizeof(ButtonCustom_s));
#else
    for (uint32_t i = 0; i < GUI_CONFIG_BUTTON_CUSTOM_BUFFER_SIZE; i++)
    {
        if (!staticButtonCustomMemInUse[i])
        {
            staticButtonCustomMemInUse[i] = true;

            return &staticButtonCustomMem[i];
        }
    }

    gui_log_write(GUI_LOG_LEVEL_ERROR, "No ButtonCustom_s static memory");

    return NULL;
#endif /* GUI_USE_DYNAMIC_MEMORY */
}


/**
 * @brief Creates a new ButtonCustom_s component and initializes it to default values.
 * @return Pointer to the ButtonCustom_s component.
 *
 */
ButtonCustom_s *button_custom_newInit(void)
{
    ButtonCustom_s *p_newButton = button_custom_new();
    button_custom_init(p_newButton);

    return p_newButton;
}


/**
 * @brief Delete the ButtonCustom component. This function calls the gui_mem_free function to free the allocated memory.
 * @param[in] p_buttonBase Pointer to the ButtonCustom component to be freed.
 *
 */
void button_custom_delete(BaseComponent_s *p_buttonBase)
{
    base_clear(p_buttonBase);
#if GUI_USE_DYNAMIC_MEMORY
    gui_mem_free(p_buttonBase, sizeof(ButtonCustom_s));
#else
    for (uint32_t i = 0; i < GUI_CONFIG_BUTTON_CUSTOM_BUFFER_SIZE; i++)
    {
        if (&staticButtonCustomMem[i].button.base == p_buttonBase)
        {
            staticButtonCustomMemInUse[i] = false;
            break;
        }
    }
#endif /* GUI_USE_DYNAMIC_MEMORY */
}


/**
 * @brief Initialize the ButtonCustom_s to the default values.
 * base is initialized to a image-component so it can hold a bmp,
 * base->onDelete calls button_custom_delete when deleted and
 * onHandleEvent calls button_custom_handleEvent when a event is posted to the GUI.
 * params[in] p_button Pointer to the button component.
 *
 */
void button_custom_init(ButtonCustom_s *p_customButton)
{
    button_init(&p_customButton->button);
    base_setOnDelete(p_customButton, button_custom_delete);
    base_setOnDisplay(p_customButton, btnc_onDisplay);
    base_setBmpKey(p_customButton, FILE_KEY_NONE);
    p_customButton->textBmp = FILE_KEY_NONE;
    touch_init(&p_customButton->touch);
    base_addTouch(p_customButton, &p_customButton->touch);
    anchor_init(&p_customButton->anchor);
    base_addAnchor(p_customButton, &p_customButton->anchor);

    fontdata_init(&p_customButton->fontData);
    p_customButton->text[0] = '\0';

    borderdata_init(&p_customButton->borderData);
    p_customButton->iconLeftMargin = 0;
    p_customButton->textLeftMargin = 0;
}

void button_custom_setIcon(ButtonCustom_s *p_button, const file_key_e icon)
{
    base_setBmpKey(p_button, icon);
}

void button_custom_setTextBmp(ButtonCustom_s *p_button, const file_key_e text)
{
    p_button->textBmp = text;
}

void button_custom_setText(ButtonCustom_s *p_button, const char *p_text)
{
    strncpy(p_button->text, p_text, GUI_CONFIG_TEXTBLOCK_MAX_STRING_LENGTH_INC_NULL);
}

void button_custom_setFont(ButtonCustom_s *p_button, const uint8_t font)
{
    p_button->fontData.font = font;
}

void button_custom_setColor(ButtonCustom_s *p_button, const Color_t color)
{
    base_setBackground(p_button, color);
}

void button_custom_showBorderOnly(ButtonCustom_s *p_button, const bool showBorderOnly)
{
    base_setTransparent(p_button, showBorderOnly);
}

void button_custom_setBorderColor(ButtonCustom_s *p_button, const Color_t color)
{
    p_button->borderData.borderColor = color;
}

void button_custom_setBorderThickness(ButtonCustom_s *p_button, const uint8_t thickness)
{
    p_button->borderData.borderThickness = thickness;
}

void button_custom_setRadius(ButtonCustom_s *p_button, const uint8_t radius)
{
    p_button->borderData.radius = radius;
}

static void btnc_onDisplay(BaseComponent_s *p_base)
{
    ButtonCustom_s *p_customButton = (ButtonCustom_s*)p_base;
    graphics_setPosistionFromAnchor(p_base);

    Rectangle_s background;
    rectangle_initFillPosSize(
        &background, p_base->background,
        p_base->x, p_base->y,
        p_base->width, p_base->height);
    rectangle_setRadius(&background, p_customButton->borderData.radius);
    rectangle_setBorderColor(&background, p_customButton->borderData.borderColor);
    rectangle_setBorderThickness(&background, p_customButton->borderData.borderThickness);

    if ((p_base->bmpKey == FILE_KEY_NONE) &&
        (p_customButton->textBmp == FILE_KEY_NONE))
    {
        btnc_displayCustomText(p_customButton, &background);
    }
    else if ((p_base->bmpKey != FILE_KEY_NONE) &&
             (p_customButton->textBmp == FILE_KEY_NONE) &&
             (p_customButton->text[0] != '\0'))
    {

        btnc_displayIconAndCustomText(p_customButton, &background);
    }
    else if ((p_base->bmpKey != FILE_KEY_NONE) &&
             (p_customButton->textBmp == FILE_KEY_NONE) &&
             (p_customButton->text[0] == '\0'))
    {
        btnc_displayIcon(p_customButton);
    }
    else if ((p_base->bmpKey == FILE_KEY_NONE) &&
             (p_customButton->textBmp != FILE_KEY_NONE))
    {
        btnc_displayBmpText(p_customButton, &background);
    }
    else if ((p_base->bmpKey != FILE_KEY_NONE) &&
             (p_customButton->textBmp != FILE_KEY_NONE))
    {
        btnc_displayIconAndBmpText(p_customButton, &background);
    }
    else
    {
    }
}

static void btnc_displayCustomText(ButtonCustom_s *p_customButton, Rectangle_s *p_background)
{
    TextBlock_s textBlock;
    textblock_initText(&textBlock, p_customButton->text);
    base_setDimensions(&textBlock.base, p_customButton->button.base.width, p_customButton->button.base.height);
    textblock_setFont(&textBlock, p_customButton->fontData.font);

    GuiAnchor_s anchor;
    anchor_init(&anchor);
    base_addAnchor(&textBlock, &anchor);
    anchor_setCenterInParent(&textBlock, p_background);

    base_display(p_background);
    base_display(&textBlock);
}

static void btnc_displayIconAndCustomText(ButtonCustom_s *p_customButton, Rectangle_s *p_background)
{
    Label_s icon;
    label_initBmp(&icon, p_customButton->button.base.bmpKey);
    base_setDimensions(&icon.base, p_customButton->iconWidth, p_customButton->iconWidth);

    GuiAnchor_s anchorIcon;
    anchor_init(&anchorIcon);
    base_addAnchor(&icon, &anchorIcon);
    anchor_setVerticalCenter(&icon, p_background);
    anchor_setLeftAnchor(&icon, p_background, Gui_Anchor_Left);
    anchor_setLeftMargin(&icon, p_customButton->iconLeftMargin);

    TextBlock_s textBlock;
    textblock_initText(&textBlock, p_customButton->text);
    base_setDimensions(
        &textBlock.base,
        (p_customButton->button.base.width - p_customButton->iconWidth - p_customButton->iconLeftMargin - p_customButton->textLeftMargin),
        p_customButton->button.base.height);
    textblock_setFont(&textBlock, p_customButton->fontData.font);
    base_setHorizontalAlignment(&textBlock, Gui_Align_Left);

    GuiAnchor_s textAnchor;
    anchor_init(&textAnchor);
    base_addAnchor(&textBlock, &textAnchor);
    anchor_setVerticalCenter(&textBlock, p_background);
    anchor_setLeftAnchor(&textBlock, &icon, Gui_Anchor_Right);
    anchor_setLeftMargin(&textBlock, p_customButton->textLeftMargin);

    base_display(p_background);
    base_display(&icon);
    base_display(&textBlock);
}

static void btnc_displayIcon(ButtonCustom_s *p_customButton)
{
    Label_s icon;
    label_initBmp(&icon, p_customButton->button.base.bmpKey);
    label_initBmpPosSize(
        &icon, p_customButton->button.base.bmpKey,
        p_customButton->button.base.x, p_customButton->button.base.y,
        p_customButton->button.base.width, p_customButton->button.base.height);
    btnc_displayBackground(p_customButton);
    base_display(&icon);
}

static void btnc_displayBmpText(ButtonCustom_s *p_customButton, Rectangle_s *p_background)
{
    Label_s textBmp;
    label_initBmp(&textBmp, p_customButton->textBmp);
    base_setDimensions(&textBmp.base, p_customButton->button.base.width, p_customButton->button.base.height);
    gui_app_translate(&textBmp);

    base_display(p_background);
    base_display(&textBmp);
}

static void btnc_displayIconAndBmpText(ButtonCustom_s *p_customButton, Rectangle_s *p_background)
{
    Label_s icon;
    label_initBmp(&icon, p_customButton->button.base.bmpKey);
    base_setDimensions(&icon.base, p_customButton->iconWidth, p_customButton->iconWidth);

    GuiAnchor_s anchorIcon;
    anchor_init(&anchorIcon);
    base_addAnchor(&icon, &anchorIcon);
    anchor_setVerticalCenter(&icon, p_background);
    anchor_setLeftAnchor(&icon, p_background, Gui_Anchor_Left);
    anchor_setLeftMargin(&icon, p_customButton->iconLeftMargin);

    Label_s textBmp;
    label_initBmp(&textBmp, p_customButton->textBmp);
    base_setDimensions(
        &textBmp.base,
        (p_customButton->button.base.width - p_customButton->iconWidth - p_customButton->iconLeftMargin - p_customButton->textLeftMargin),
        p_customButton->button.base.height);
    base_setHorizontalAlignment(&textBmp, Gui_Align_Left);
    gui_app_translate(&textBmp);

    GuiAnchor_s anchorTextBmp;
    anchor_init(&anchorTextBmp);
    base_addAnchor(&textBmp, &anchorTextBmp);
    anchor_setVerticalCenter(&textBmp, p_background);
    anchor_setLeftAnchor(&textBmp, &icon, Gui_Anchor_Right);
    anchor_setLeftMargin(&textBmp, p_customButton->textLeftMargin);

    base_display(p_background);
    base_display(&icon);
    base_display(&textBmp);
}

static void btnc_displayBackground(ButtonCustom_s *p_customButton)
{
    if ((!p_customButton->button.base.transparent) &&
        (p_customButton->borderData.borderThickness == 0))
    {
        Rectangle_s background;
        rectangle_initFillPosSize(
                &background, p_customButton->button.base.background,
                p_customButton->button.base.x, p_customButton->button.base.y,
                p_customButton->button.base.width, p_customButton->button.base.height);
        base_display(&background);
    }
    else if ((p_customButton->button.base.transparent) &&
             (p_customButton->borderData.borderThickness > 0))
    {
        Rectangle_s background;
        rectangle_initBorderPosSize(
                &background,
                p_customButton->button.base.x, p_customButton->button.base.y,
                p_customButton->button.base.width, p_customButton->button.base.height,
                p_customButton->borderData.borderThickness, p_customButton->borderData.borderColor);
        base_display(&background);
    }
    else if ((!p_customButton->button.base.transparent) &&
             (p_customButton->borderData.borderThickness >= 0))
    {
        Rectangle_s background;
        rectangle_initFillBorderPosSize(
                &background, p_customButton->button.base.background,
                p_customButton->button.base.x, p_customButton->button.base.y,
                p_customButton->button.base.width, p_customButton->button.base.height,
                p_customButton->borderData.borderThickness, p_customButton->borderData.borderColor);
        base_display(&background);
    }
    else
    {
    }
}
