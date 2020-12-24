#include "gui_rectangle.h"

#include <stddef.h>

#include "McsGui/Utils/gui_memory.h"


#if GUI_USE_DYNAMIC_MEMORY
/**
 * @brief Creates a new malloced Rectangle component.
 * @return Pointer to the malloced memory.
 *
 * @warning The returned component is not initialized.
 *
 */
Rectangle_s *rectangle_new(void)
{
    return gui_mem_malloc(sizeof(Rectangle_s));
}
#endif /* GUI_USE_DYNAMIC_MEMORY */


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
    p_rectangleBase = NULL;
#endif /* GUI_USE_DYNAMIC_MEMORY */
}


/**
 * @brief Initialize the Rectangle component to the default values.
 * @param[in] p_rectangle Pointer to the Rectangle component to be freed.
 *
 */
void rectangle_init(Rectangle_s *p_rectangle)
{
    filldata_init(&p_rectangle->fillData);
    base_initFillComp(&p_rectangle->base, &p_rectangle->fillData, rectangle_delete);
    p_rectangle->base.transparent = false;
}


/**
 * @brief Initialize the Rectangle component to the given values.
 * @param[in] p_rectangle Pointer to the Rectangle component.
 * @param[in] color
 * @param[in] xPos.
 * @param[in] yPos.
 * @param[in] width.
 * @param[in] height.
 *
 */
void rectangle_init_1(
        Rectangle_s *p_rectangle, const Color_t color,
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height)
{
    rectangle_init(p_rectangle);
    p_rectangle->base.background = color;
    p_rectangle->base.xPos = xPos;
    p_rectangle->base.yPos = yPos;
    p_rectangle->base.width = width;
    p_rectangle->base.height = height;
}


/**
 * @brief Initialize the Rectangle component with a border.
 * @param[in] p_rectangle Pointer to the Rectangle component.
 * @param[in] color
 * @param[in] xPos.
 * @param[in] yPos.
 * @param[in] width.
 * @param[in] height.
 * @param[in] borderThickness.
 * @param[in] borderColor.
 *
 */
void rectangle_init_2(
        Rectangle_s *p_rectangle, const Color_t color,
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height,
        const uint8_t borderThickness, const Color_t borderColor)
{
    rectangle_init_1(p_rectangle, color, xPos, yPos, width, height);
    FillData_s *p_fillData = (FillData_s *)p_rectangle->base.p_data;
    p_fillData->borderColor = borderColor;
    p_fillData->borderThickness = borderThickness;
}


/**
 * @brief Initialize the Rectangle component as a border.
 * @param[in] p_rectangle Pointer to the Rectangle component.
 * @param[in] xPos.
 * @param[in] yPos.
 * @param[in] width.
 * @param[in] height.
 * @param[in] borderThickness.
 * @param[in] borderColor.
 *
 */
void rectangle_initBorder(
        Rectangle_s *p_rectangle,
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height,
        const uint8_t borderThickness, const Color_t borderColor)
{
    rectangle_init_2(p_rectangle, 0, xPos, yPos, width, height, borderThickness, borderColor);
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

    FillData_s *p_fillData = (FillData_s *)p_rectangle->base.p_data;
    p_fillData->borderColor = color;
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

    FillData_s *p_fillData = (FillData_s *)p_rectangle->base.p_data;
    p_fillData->borderThickness = thickness;
}


/*** end of file ***/
