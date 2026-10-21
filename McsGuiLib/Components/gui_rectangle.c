#include "gui_rectangle.h"

#include <stddef.h>

#include "Core/gui_log.h"
#include "Core/gui_memory.h"

static void rectangle_delete(BaseComponent_s *p_rectangleBase);

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
static void rectangle_delete(BaseComponent_s *p_rectangleBase)
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
    p_rectangle->base.drawBackground = true;
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
    p_rectangle->base.backgroundColor = color;
    base_setSize(&p_rectangle->base, width, height);
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
    p_rectangle->base.backgroundColor = color;
    base_setPosition(&p_rectangle->base, x, y);
    base_setSize(&p_rectangle->base, width, height);
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
    p_rectangle->base.drawBackground = false;
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
    p_rectangle->base.drawBackground = false;
}


/**
 * @brief Display the Rectangle component.
 * @param[in] p_rectangle Pointer to the Rectangle component.
 *
 */
void rectangle_display(Rectangle_s *p_rectangle)
{
    base_display(&p_rectangle->base);
}


/**
 * @brief Set the id of the Rectangle component.
 * @param[in] p_rectangle Pointer to the Rectangle component.
 * @param[in] id Id of the Rectangle component.
 *
 */
void rectangle_setId(Rectangle_s *p_rectangle, const uint32_t id)
{
    if (id > 0)
    {
        p_rectangle->base.id = id;
    }
}


/**
 * @brief Set the background color of the Rectangle component.
 * @param[in] p_rectangle Pointer to the Rectangle component.
 * @param[in] color.
 *
 */
void rectangle_setColor(Rectangle_s *p_rectangle, const Color_t color)
{
    p_rectangle->base.backgroundColor = color;
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
 * @brief Set the showBorderOnly flag of the Rectangle component.
 * @param[in] p_rectangle Pointer to the Rectangle component.
 * @param[in] showBorderOnly If true, only the border is drawn when onDisplay is called.
 *
 */
void rectangle_setShowBorderOnly(Rectangle_s *p_rectangle, const bool showBorderOnly)
{
    p_rectangle->base.drawBackground = !showBorderOnly;
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
 * @brief Set the radius of the Rectangle component.
 * @param[in] p_rectangle Pointer to the Rectangle component.
 * @param[in] radius.
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


/**
 * @brief Set the x-position of the Rectangle component.
 * @param[in] p_rectangle Pointer to the Rectangle component.
 * @param[in] x x-position of the Rectangle component.
 *
 */
void rectangle_setX(Rectangle_s *p_rectangle, const uint16_t x)
{
    base_setX(&p_rectangle->base, x);
}


/**
 * @brief Set the y-position of the Rectangle component.
 * @param[in] p_rectangle Pointer to the Rectangle component.
 * @param[in] y y-position of the Rectangle component.
 *
 */
void rectangle_setY(Rectangle_s *p_rectangle, const uint16_t y)
{
    base_setY(&p_rectangle->base, y);
}


/**
 * @brief Set the width of the Rectangle component.
 * @param[in] p_rectangle Pointer to the Rectangle component.
 * @param[in] width Width of the Rectangle component.
 *
 */
void rectangle_setWidth(Rectangle_s *p_rectangle, const uint16_t width)
{
    base_setWidth(&p_rectangle->base, width);
}


/**
 * @brief Set the height of the Rectangle component.
 * @param[in] p_rectangle Pointer to the Rectangle component.
 * @param[in] height Height of the Rectangle component.
 *
 */
void rectangle_setHeight(Rectangle_s *p_rectangle, const uint16_t height)
{
    base_setHeight(&p_rectangle->base, height);
}


/**
 * @brief Set the position of the Rectangle component.
 * @param[in] p_rectangle Pointer to the Rectangle component.
 * @param[in] x x-position of the Rectangle component.
 * @param[in] y y-position of the Rectangle component.
 *
 */
void rectangle_setPosition(Rectangle_s *p_rectangle, const uint16_t x, const uint16_t y)
{
    base_setPosition(&p_rectangle->base, x, y);
}


/**
 * @brief Set the size of the Rectangle component.
 * @param[in] p_rectangle Pointer to the Rectangle component.
 * @param[in] width Width of the Rectangle component.
 * @param[in] height Height of the Rectangle component.
 *
 */
void rectangle_setSize(Rectangle_s *p_rectangle, const uint16_t width, const uint16_t height)
{
    base_setSize(&p_rectangle->base, width, height);
}


/**
 * @brief Set the visibility of the Rectangle component.
 * @param[in] p_rectangle Pointer to the Rectangle component.
 * @param[in] visible If true, the Rectangle component is visible.
 *
 */
void rectangle_setVisible(Rectangle_s *p_rectangle, const bool visible)
{
    p_rectangle->base.visible = visible;
}


/*** end of file ***/
