#include "gui_rectangle.h"

#include <stddef.h>

#include "Core/gui_log.h"
#include "Core/gui_memory.h"


#if !GUI_USE_DYNAMIC_MEMORY
static bool staticRectMemInUse[GUI_CONFIG_RECTANGLE_BUFFER_SIZE] = {0};
static Rectangle_s staticRectMem[GUI_CONFIG_RECTANGLE_BUFFER_SIZE] = {0};
#endif /* GUI_USE_DYNAMIC_MEMORY */

/**
 * @brief Creates a new malloced Rectangle component.
 * @return Pointer to the malloced memory.
 *
 * @warning The returned component is not initialized.
 *
 */
Rectangle_s *rectangle_new(void)
{
#if GUI_USE_DYNAMIC_MEMORY
    return gui_mem_malloc(sizeof(Rectangle_s));
#else
    for (uint32_t i = 0; i < GUI_CONFIG_RECTANGLE_BUFFER_SIZE; i++)
    {
    	if (!staticRectMemInUse[i])
    	{
    		staticRectMemInUse[i] = true;

    		return &staticRectMem[i];
    	}
    }

    gui_log_write(GUI_LOG_LEVEL_ERROR, "No Rectangle_s static memory");

    return NULL;
#endif /* GUI_USE_DYNAMIC_MEMORY */
}


/**
 * @brief Creates a new Rectangle_s component and initializes it to default values.
 * @return Pointer to the Rectangle_s component.
 *
 */
Rectangle_s *rectangle_newInit(void)
{
	Rectangle_s *p_rectangle = rectangle_new();
	rectangle_init(p_rectangle);

	return p_rectangle;
}


/**
 * @brief Delete the Rectangle component. This functions calls the gui_mem_free function to free the allocated memory.
 * @param[in] p_rectangleBase Pointer to the Rectangle component to be freed.
 *
 */
void rectangle_delete(BaseComponent_s *p_rectangleBase)
{
    base_clear(p_rectangleBase);
#if GUI_USE_DYNAMIC_MEMORY
    gui_mem_free(p_rectangleBase, sizeof(Rectangle_s));
#else
    for (uint32_t i = 0; i < GUI_CONFIG_RECTANGLE_BUFFER_SIZE; i++)
    {
    	if (&staticRectMem[i].base == p_rectangleBase)
    	{
    		staticRectMemInUse[i] = false;
    		break;
    	}
    }
#endif /* GUI_USE_DYNAMIC_MEMORY */
}


/**
 * @brief Initialize the Rectangle component to the default values.
 * @param[in] p_rectangle Pointer to the Rectangle component to be freed.
 *
 */
void rectangle_init(Rectangle_s *p_rectangle)
{
    borderdata_init(&p_rectangle->borderData);
    base_initFillComp(&p_rectangle->base, &p_rectangle->borderData, rectangle_delete);
    p_rectangle->base.transparent = false;
}


/**
 * @brief Initialize the Rectangle component to the given values.
 * @param[in] p_rectangle Pointer to the Rectangle component.
 * @param[in] color
 * @param[in] width.
 * @param[in] height.
 *
 */
void rectangle_initFillSize(
        Rectangle_s *p_rectangle, const Color_t color,
        const uint16_t width, const uint16_t height)
{
    rectangle_init(p_rectangle);
    p_rectangle->base.background = color;
    p_rectangle->base.width = width;
    p_rectangle->base.height = height;
}


/**
 * @brief Initialize the Rectangle component to the given values.
 * @param[in] p_rectangle Pointer to the Rectangle component.
 * @param[in] color
 * @param[in] x x-position
 * @param[in] y y-position
 * @param[in] width.
 * @param[in] height.
 *
 */
void rectangle_initFillPosSize(
        Rectangle_s *p_rectangle, const Color_t color,
        const uint16_t x, const uint16_t y,
        const uint16_t width, const uint16_t height)
{
    rectangle_init(p_rectangle);
    p_rectangle->base.background = color;
    p_rectangle->base.x = x;
    p_rectangle->base.y = y;
    p_rectangle->base.width = width;
    p_rectangle->base.height = height;
}


/**
 * @brief Initialize the Rectangle component as a border.
 * @param[in] p_rectangle Pointer to the Rectangle component.
 * @param[in] color
 * @param[in] width.
 * @param[in] height.
 * @param[in] borderThickness.
 * @param[in] borderColor.
 *
 */
void rectangle_initFillBorderSize(
        Rectangle_s *p_rectangle, const Color_t color,
        const uint16_t width, const uint16_t height,
        const uint8_t borderThickness, const Color_t borderColor)
{
    rectangle_initFillSize(p_rectangle, color, width, height);
    BorderData_s *p_borderData = (BorderData_s*) p_rectangle->base.p_data;
    p_borderData->borderColor = borderColor;
    p_borderData->borderThickness = borderThickness;
}


/**
 * @brief Initialize the Rectangle component with a border.
 * @param[in] p_rectangle Pointer to the Rectangle component.
 * @param[in] color
 * @param[in] x x-position
 * @param[in] y y-position
 * @param[in] width.
 * @param[in] height.
 * @param[in] borderThickness.
 * @param[in] borderColor.
 *
 */
void rectangle_initFillBorderPosSize(
        Rectangle_s *p_rectangle, const Color_t color,
        const uint16_t x, const uint16_t y,
        const uint16_t width, const uint16_t height,
        const uint8_t borderThickness, const Color_t borderColor)
{
    rectangle_initFillPosSize(p_rectangle, color, x, y, width, height);
    BorderData_s *p_borderData = (BorderData_s *)p_rectangle->base.p_data;
    p_borderData->borderColor = borderColor;
    p_borderData->borderThickness = borderThickness;
}


/**
 * @brief Initialize the Rectangle component as a border.
 * @param[in] p_rectangle Pointer to the Rectangle component.
 * @param[in] width.
 * @param[in] height.
 * @param[in] borderThickness.
 * @param[in] borderColor.
 *
 */
void rectangle_initBorderSize(
        Rectangle_s *p_rectangle,
        const uint16_t width, const uint16_t height,
        const uint8_t borderThickness, const Color_t borderColor)
{
    rectangle_initFillBorderSize(p_rectangle, 0, width, height, borderThickness, borderColor);
    p_rectangle->base.transparent = true;
}


/**
 * @brief Initialize the Rectangle component as a border.
 * @param[in] p_rectangle Pointer to the Rectangle component.
 * @param[in] x x-position
 * @param[in] y y-position
 * @param[in] width.
 * @param[in] height.
 * @param[in] borderThickness.
 * @param[in] borderColor.
 *
 */
void rectangle_initBorderPosSize(
        Rectangle_s *p_rectangle,
        const uint16_t x, const uint16_t y,
        const uint16_t width, const uint16_t height,
        const uint8_t borderThickness, const Color_t borderColor)
{
    rectangle_initFillBorderPosSize(p_rectangle, 0, x, y, width, height, borderThickness, borderColor);
    p_rectangle->base.transparent = true;
}


/**
 * @brief Display rectangle by calling the onDisplay.
 * @param[in] p_rectangle Pointer to the Rectangle component.
 *
 */
void rectangle_displayDirect(Rectangle_s *p_rectangle)
{
    p_rectangle->base.onDisplay(&p_rectangle->base);
}


/**
 * @brief Set the background color of the Rectangle component.
 * @param[in] p_rectangle Pointer to the Rectangle component.
 * @param[in] color.
 *
 */
void rectangle_setColor(Rectangle_s *p_rectangle, const Color_t color)
{
    p_rectangle->base.background = color;
}


/*
 *
 */
void rectangle_showBorderOnly(Rectangle_s *p_rectangle, const bool showBorderOnly)
{
    p_rectangle->base.transparent = showBorderOnly;
}


/**
 * @brief Set the border color of the Rectangle component.
 * @param[in] p_rectangle Pointer to the Rectangle component.
 * @param[in] color.
 *
 */
void rectangle_setBorderColor(Rectangle_s *p_rectangle, const Color_t color)
{
    if (p_rectangle->base.p_data == NULL)
    {
        return;
    }

    BorderData_s *p_borderData = (BorderData_s *)p_rectangle->base.p_data;
    p_borderData->borderColor = color;
}


/**
 * @brief Set the border thickness of the Rectangle component.
 * @param[in] p_rectangle Pointer to the Rectangle component.
 * @param[in] thickness.
 *
 */
void rectangle_setBorderThickness(Rectangle_s *p_rectangle, const uint8_t thickness)
{
    if (p_rectangle->base.p_data == NULL)
    {
        return;
    }

    BorderData_s *p_borderData = (BorderData_s *)p_rectangle->base.p_data;
    p_borderData->borderThickness = thickness;
}


/**
 *
 */
void rectangle_setRadius(Rectangle_s *p_rectangle, const uint8_t radius)
{
    if (p_rectangle->base.p_data == NULL)
    {
        return;
    }

    BorderData_s *p_borderData = (BorderData_s*) p_rectangle->base.p_data;
    p_borderData->radius = radius;
}


/*** end of file ***/
