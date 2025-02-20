#include "gui_scrollbar.h"

#include "gui_memory.h"
#include "gui_log.h"
#include "Graphics/gui_graphics.h"

#define GUI_SCROLLBAR_BUFFER_SIZE 2

#if !GUI_USE_DYNAMIC_MEMORY
static bool staticScrollBarMemInUse[GUI_SCROLLBAR_BUFFER_SIZE] = {0};
static ScrollBar_s staticScrollBarMem[GUI_SCROLLBAR_BUFFER_SIZE] = {0};
#endif /* GUI_USE_DYNAMIC_MEMORY */

static void scrollbar_delete(BaseComponent_s *p_scrollbarBase);
static void scrollbar_onDisplay(BaseComponent_s *p_scrollbarBase);
static void scrollbar_displayThumbArea(ScrollBar_s *p_scrollBar);
static void scrollbar_displayThumb(ScrollBar_s *p_scrollBar);
static void scrollbar_moveUpButtonPressed(Button_s *p_button);
static void scrollbar_moveDownButtonPressed(Button_s *p_button);
static bool scrollbar_updateThumbPosition(ScrollBar_s *p_scrollBar);
static void scrollbar_deleteButton(BaseComponent_s *p_buttonBase);

ScrollBar_s* scrollbar_new(void)
{
#if GUI_USE_DYNAMIC_MEMORY
    return gui_mem_malloc(sizeof(ScrollBar_s));
#else
    for (uint32_t i = 0; i < GUI_SCROLLBAR_BUFFER_SIZE; i++)
    {
        if (!staticScrollBarMemInUse[i])
        {
            staticScrollBarMemInUse[i] = true;

            return &staticScrollBarMem[i];
        }
    }

    gui_log_write(GUI_LOG_LEVEL_ERROR, "No ScrollBar_s static memory");

    return NULL;
#endif /* GUI_USE_DYNAMIC_MEMORY */
}

ScrollBar_s* scrollbar_newInit(void)
{
    ScrollBar_s *p_scrollBar = scrollbar_new();
    scrollbar_init(p_scrollBar);

    return p_scrollBar;
}

static void scrollbar_delete(BaseComponent_s *p_scrollbarBase)
{
    base_clear(p_scrollbarBase);
#if GUI_USE_DYNAMIC_MEMORY
    gui_mem_free(p_scrollbarBase, sizeof(ScrollBar_s));
#else
    for (uint32_t i = 0; i < GUI_SCROLLBAR_BUFFER_SIZE; i++)
    {
        if (&staticScrollBarMem[i].base == p_scrollbarBase)
        {
                staticScrollBarMemInUse[i] = false;

                break;
        }
    }
#endif /* GUI_USE_DYNAMIC_MEMORY */
}

void scrollbar_init(ScrollBar_s *p_scrollBar)
{
    base_initParentComp(&p_scrollBar->base, scrollbar_delete);
    base_setOnDisplay(p_scrollBar, scrollbar_onDisplay);
    base_setSize(p_scrollBar, 10, 10);
    anchor_init(&p_scrollBar->anchor);
    base_addAnchor(&p_scrollBar->base, &p_scrollBar->anchor);

    button_init(&p_scrollBar->upButton);
    button_init(&p_scrollBar->downButton);
    touch_init(&p_scrollBar->upButtonTouch);
    touch_init(&p_scrollBar->downButtonTouch);
    base_addTouch(&p_scrollBar->upButton, &p_scrollBar->upButtonTouch);
    base_addTouch(&p_scrollBar->downButton, &p_scrollBar->downButtonTouch);

    base_setOnDelete(&p_scrollBar->upButton, scrollbar_deleteButton);
    base_setOnDelete(&p_scrollBar->downButton, scrollbar_deleteButton);
    base_addChild(&p_scrollBar->base, &p_scrollBar->upButton.base);
    base_addChild(&p_scrollBar->base, &p_scrollBar->downButton.base);

    p_scrollBar->thumbSize = SCROLLBAR_DEFAULT_THUMB_SIZE;
    p_scrollBar->thumbPosition = SCROLLBAR_DEFAULT_THUMB_POSITION;
    p_scrollBar->thumbMinSize = SCROLLBAR_MIN_THUMB_SIZE;
    p_scrollBar->thumbMaxSize = SCROLLBAR_MAX_THUMB_SIZE;
    p_scrollBar->orientation = Scrollbar_Vertical;
    p_scrollBar->thumbRadius = 0;
    p_scrollBar->thumbColor = 0xFFFFFFU;
    p_scrollBar->thumbAreaWidth = 10;
    p_scrollBar->thumbAreaRadius = 0;
    p_scrollBar->thumbAreaBorderThickness = 0;
    p_scrollBar->thumbAreaBorderColor = 0;
    p_scrollBar->p_listView = NULL;
}

void scrollbar_addListview(ScrollBar_s *p_scrollBar, ListView_s *p_listView)
{
    p_scrollBar->p_listView = p_listView;
    button_setOnPressed(&p_scrollBar->upButton, scrollbar_moveUpButtonPressed);
    button_setOnPressed(&p_scrollBar->downButton, scrollbar_moveDownButtonPressed);
}

void scrollbar_setWidth(ScrollBar_s *p_scrollBar, uint16_t width)
{
    base_setWidth(&p_scrollBar->base, width);
}

void scrollbar_setHeight(ScrollBar_s *p_scrollBar, uint16_t height)
{
    base_setHeight(&p_scrollBar->base, height);
}

void scrollbar_setThumbAreaWidth(ScrollBar_s *p_scrollBar, uint8_t width)
{
    p_scrollBar->thumbAreaWidth = width;
}

void scrollbar_setThumbAreaColor(ScrollBar_s *p_scrollBar, const Color_t color)
{
    base_setBackground(&p_scrollBar->base, color);
}

void scrollbar_setThumbRadius(ScrollBar_s *p_scrollBar, uint8_t radius)
{
    p_scrollBar->thumbRadius = radius;
}

void scrollbar_setThumbColor(ScrollBar_s *p_scrollBar, const Color_t color)
{
    p_scrollBar->thumbColor = color;
}

void scrollbar_setThumbAreaRadius(ScrollBar_s *p_scrollBar, uint8_t radius)
{
    p_scrollBar->thumbAreaRadius = radius;
}

void scrollbar_setThumbAreaBorderThickness(ScrollBar_s *p_scrollBar, uint8_t thickness)
{
    p_scrollBar->thumbAreaBorderThickness = thickness;
}

void scrollbar_setThumbAreaBorderColor(ScrollBar_s *p_scrollBar, const Color_t color)
{
    p_scrollBar->thumbAreaBorderColor = color;
}

void scrollbar_setUpIcon(ScrollBar_s *p_scrollBar, const file_key_e icon)
{
    base_setBmpKey(&p_scrollBar->upButton, icon);
}

void scrollbar_setDownIcon(ScrollBar_s *p_scrollBar, const file_key_e icon)
{
    base_setBmpKey(&p_scrollBar->downButton, icon);
}

void scrollbar_setButtonSize(ScrollBar_s *p_scrollBar, uint16_t width, uint16_t height)
{
    base_setSize(&p_scrollBar->upButton, width, height);
    base_setSize(&p_scrollBar->downButton, width, height);
}

void scrollbar_setThumbSize(ScrollBar_s *p_scrollBar, uint16_t thumbSize)
{
    p_scrollBar->thumbSize = thumbSize;
}

void scrollbar_setThumbPosition(ScrollBar_s *p_scrollBar, uint16_t thumbPosition)
{
    p_scrollBar->thumbPosition = thumbPosition;
}

void scrollbar_setThumbMinSize(ScrollBar_s *p_scrollBar, uint16_t thumbMinSize)
{
    p_scrollBar->thumbMinSize = thumbMinSize;
}

void scrollbar_setThumbMaxSize(ScrollBar_s *p_scrollBar, uint16_t thumbMaxSize)
{
    p_scrollBar->thumbMaxSize = thumbMaxSize;
}

void scrollbar_setOrientation(ScrollBar_s *p_scrollBar, ScrollBarOrientation_e orientation)
{
    p_scrollBar->orientation = orientation;
}

static void scrollbar_onDisplay(BaseComponent_s *p_scrollbarBase)
{
    ScrollBar_s *p_scrollBar = (ScrollBar_s*)p_scrollbarBase;
    graphics_setPosistionFromAnchor(p_scrollbarBase);

    if (p_scrollBar->orientation == Scrollbar_Vertical)
    {
        scrollbar_updateThumbPosition(p_scrollBar);
        base_setPosition(&p_scrollBar->upButton, p_scrollBar->base.x, p_scrollBar->base.y);
        base_setPosition(
            &p_scrollBar->downButton,
            p_scrollBar->base.x, p_scrollBar->base.y + p_scrollBar->base.height - p_scrollBar->downButton.base.height);
        base_display(&p_scrollBar->upButton);
        scrollbar_displayThumbArea(p_scrollBar);
        scrollbar_displayThumb(p_scrollBar);
        base_display(&p_scrollBar->downButton);
    }
    else
    {
        // Draw horizontal scrollbar
    }
}

static void scrollbar_displayThumbArea(ScrollBar_s *p_scrollBar)
{
    uint16_t thumbAreaWidth = p_scrollBar->thumbAreaWidth;
    const uint16_t thumbAreaHeight = p_scrollBar->base.height -
            (p_scrollBar->upButton.base.height + p_scrollBar->downButton.base.height);
    uint16_t thumbAreaX = p_scrollBar->base.x;
    const uint16_t thumbAreaY = p_scrollBar->base.y + p_scrollBar->upButton.base.height;

    if (p_scrollBar->base.width < p_scrollBar->thumbAreaWidth)
    {
        p_scrollBar->thumbAreaWidth = p_scrollBar->base.width;
        thumbAreaWidth = p_scrollBar->base.width;
    }
    else if (p_scrollBar->base.width > p_scrollBar->thumbAreaWidth)
    {
        thumbAreaX += ((p_scrollBar->base.width - p_scrollBar->thumbAreaWidth) / 2);
    }
    else
    {
    }

    Rectangle_s thumbArea;
    rectangle_initFillPosSize(
        &thumbArea, p_scrollBar->base.background,
        thumbAreaX, thumbAreaY,
        thumbAreaWidth, thumbAreaHeight);

    if (p_scrollBar->thumbAreaBorderThickness > 0)
    {
        rectangle_setBorderColor(&thumbArea, p_scrollBar->thumbAreaBorderColor);
        rectangle_setBorderThickness(&thumbArea, p_scrollBar->thumbAreaBorderThickness);
    }

    rectangle_setRadius(&thumbArea, p_scrollBar->thumbAreaRadius);
    base_display(&thumbArea);
}

static void scrollbar_displayThumb(ScrollBar_s *p_scrollBar)
{
    uint16_t thumbX = p_scrollBar->base.x + ((p_scrollBar->base.width - p_scrollBar->thumbAreaWidth) / 2);

    Rectangle_s thumb;
    rectangle_initFillPosSize(&thumb, p_scrollBar->thumbColor,
        thumbX, p_scrollBar->base.y + p_scrollBar->upButton.base.height + p_scrollBar->thumbPosition,
        p_scrollBar->thumbAreaWidth, p_scrollBar->thumbSize);
    rectangle_setRadius(&thumb, p_scrollBar->thumbRadius);
    base_display(&thumb);
}

static void scrollbar_moveUpButtonPressed(Button_s *p_button)
{
    ScrollBar_s *p_scrollBar = (ScrollBar_s*)p_button->base.p_parent;
    ListView_s *p_listView = (ListView_s*)p_scrollBar->p_listView;

    if (p_listView == NULL)
    {
        return;
    }

    listview_moveUp(p_listView);

    const bool updateThumbPosition = scrollbar_updateThumbPosition(p_scrollBar);

    if (updateThumbPosition)
    {
        scrollbar_displayThumbArea(p_scrollBar);
        scrollbar_displayThumb(p_scrollBar);
    }
}

static void scrollbar_moveDownButtonPressed(Button_s *p_button)
{
    ScrollBar_s *p_scrollBar = (ScrollBar_s*)p_button->base.p_parent;
    ListView_s *p_listView = (ListView_s*)p_scrollBar->p_listView;

    if (p_listView == NULL)
    {
        return;
    }

    listview_moveDown(p_listView);

    const bool updateThumbPosition = scrollbar_updateThumbPosition(p_scrollBar);

    if (updateThumbPosition)
    {
        scrollbar_displayThumbArea(p_scrollBar);
        scrollbar_displayThumb(p_scrollBar);
    }
}

static bool scrollbar_updateThumbPosition(ScrollBar_s *p_scrollBar)
{
    ListView_s *p_listView = p_scrollBar->p_listView;

    if (p_listView == NULL)
    {
        return false;
    }

    if (p_listView->numberOfItems == 0)
    {
        p_scrollBar->thumbPosition = 0;

        return false;
    }

    const uint16_t thumbAreaHeight = p_scrollBar->base.height -
            (p_scrollBar->upButton.base.height + p_scrollBar->downButton.base.height);
    uint16_t thumbSize = (thumbAreaHeight * p_listView->itemsVisible) / p_listView->numberOfItems;

    if (thumbSize < p_scrollBar->thumbMinSize)
    {
        thumbSize = p_scrollBar->thumbMinSize;
    }
    else if (thumbSize > p_scrollBar->thumbMaxSize)
    {
        thumbSize = p_scrollBar->thumbMaxSize;
    }
    else
    {

    }

    p_scrollBar->thumbSize = thumbSize;

    const uint16_t thumbAreaHeightWithoutThumbAndMinSize =
            thumbAreaHeight - p_scrollBar->thumbMaxSize;

    const uint16_t thumbPosition =
            (thumbAreaHeightWithoutThumbAndMinSize * p_listView->firstVisibleItemIndex) /
            (p_listView->numberOfItems - p_listView->itemsVisible);

    p_scrollBar->thumbPosition = thumbPosition;

    return true;
}

static void scrollbar_deleteButton(BaseComponent_s *p_buttonBase)
{
    // Dummy delete function for buttons
}
