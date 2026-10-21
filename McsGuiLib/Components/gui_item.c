#include "gui_item.h"

#include <stddef.h>
#include <string.h>

#include "Core/gui_log.h"
#include "Core/gui_memory.h"
#include "Graphics/gui_graphics.h"

#if !GUI_USE_DYNAMIC_MEMORY
static bool staticItemMemInUse[GUI_CONFIG_ITEM_BUFFER_SIZE] = {0};
static Item_s staticItemMem[GUI_CONFIG_ITEM_BUFFER_SIZE] = {0};
#endif /* GUI_USE_DYNAMIC_MEMORY */

static void item_delete(BaseComponent_s *p_itemBase);
static void item_display(BaseComponent_s *p_itemBase);

/**
 * @brief Creates a new malloced Item component.
 * @return Pointer to the malloced memory.
 *
 * @warning The returned component is not initialized.
 *
 */
Item_s *item_new(void)
{
#if GUI_USE_DYNAMIC_MEMORY
return gui_mem_malloc(sizeof(Item_s));
#else
    for (uint32_t i = 0; i < GUI_CONFIG_ITEM_BUFFER_SIZE; i++)
    {
        if (!staticItemMemInUse[i])
        {
            staticItemMemInUse[i] = true;

            return &staticItemMem[i];
        }
    }

    gui_log_write(GUI_LOG_LEVEL_ERROR, "No Item_s static memory");

    return NULL;
#endif /* GUI_USE_DYNAMIC_MEMORY */
}


/**
 * @brief Creates a new Item_s component and initializes it to default values.
 * @return Pointer to the Item_s component.
 *
 */
Item_s *item_newInit(void)
{
    Item_s *p_item = item_new();
    item_init(p_item);

    return p_item;
}



/**
 * @brief Initializes the Item_s component and sets the position.
 * @param p_item Pointer to the Item_s structure.
 * @param x X position of the component.
 * @param y Y position of the component.
 *
 */
void item_initPos(Item_s *p_item, const uint16_t x, const uint16_t y)
{
    item_init(p_item);
    p_item->base.x = x;
    p_item->base.y = y;
}


/**
 * @brief Initializes the Item_s component and sets the size.
 * @param p_item Pointer to the Item_s structure.
 * @param width Width of the component.
 * @param height Height of the component.
 *
 */
void item_initSize(Item_s *p_item, const uint16_t width, const uint16_t height)
{
    item_init(p_item);
    p_item->base.width = width;
    p_item->base.height = height;
}


/**
 * @brief Initializes the Item_s component and sets the position and size.
 * @param p_item Pointer to the Item_s structure.
 * @param x X position of the component.
 * @param y Y position of the component.
 * @param width Width of the component.
 * @param height Height of the component.
 *
 */
void item_initPosSize(Item_s *p_item, const uint16_t x, const uint16_t y, const uint16_t width, const uint16_t height)
{
    item_init(p_item);
    p_item->base.x = x;
    p_item->base.y = y;
    p_item->base.width = width;
    p_item->base.height = height;
}

/**
 * @brief Deletes the Item_s component.
 * @param p_itemBase Pointer to the BaseComponent_s structure.
 *
 */
static void item_delete(BaseComponent_s *p_itemBase)
{
    base_clear(p_itemBase);
#if GUI_USE_DYNAMIC_MEMORY
    gui_mem_free(p_itemBase, sizeof(Item_s));
#else
    for (uint32_t i = 0; i < GUI_CONFIG_ITEM_BUFFER_SIZE; i++)
    {
        if (&staticItemMem[i].base == p_itemBase)
        {
            memset(&staticItemMem[i], 0, sizeof(Item_s));
            staticItemMemInUse[i] = false;
            break;
        }
    }
#endif /* GUI_USE_DYNAMIC_MEMORY */
}


/**
 * @brief Initializes the Item_s component.
 * @param p_item Pointer to the Item_s structure.
 *
 */
void item_init(Item_s *p_item)
{
    base_initParentComp(&p_item->base, item_delete);
    p_item->base.onDisplay = item_display;
}


/**
 * @brief Adds a component to the Item_s component.
 * @param p_item Pointer to the Item_s component.
 * @param p_component Pointer to the component to be added.
 *
 */
void item_addComponent(Item_s *p_item, void *p_component)
{
    base_addChild(&p_item->base, p_component);
}


/**
 * @brief Sets the ID of the Item_s component.
 * @param p_item Pointer to the Item_s structure.
 * @param id ID of the component.
 *
 */
void item_setId(Item_s *p_item, const uint8_t id)
{
    base_setId(&p_item->base, id);
}


/**
 * @brief Sets the X position of the Item_s component.
 * @param p_item Pointer to the Item_s structure.
 * @param x X position of the component.
 *
 */
void item_setX(Item_s *p_item, const uint16_t x)
{
    base_setX(&p_item->base, x);
}


/**
 * @brief Sets the Y position of the Item_s component.
 * @param p_item Pointer to the Item_s structure.
 * @param y Y position of the component.
 *
 */
void item_setY(Item_s *p_item, const uint16_t y)
{
    base_setY(&p_item->base, y);
}


/**
 * @brief Sets the width of the Item_s component.
 * @param p_item Pointer to the Item_s structure.
 * @param width Width of the component.
 *
 */
void item_setWidth(Item_s *p_item, const uint16_t width)
{
    base_setWidth(&p_item->base, width);
}


/**
 * @brief Sets the height of the Item_s component.
 * @param p_item Pointer to the Item_s structure.
 * @param height Height of the component.
 *
 */
void item_setHeight(Item_s *p_item, const uint16_t height)
{
    base_setHeight(&p_item->base, height);
}


/**
 * @brief Sets the position of the Item_s component.
 * @param p_item Pointer to the Item_s structure.
 * @param x X position of the component.
 * @param y Y position of the component.
 *
 */
void item_setPosition(Item_s *p_item, const uint16_t x, const uint16_t y)
{
    base_setPosition(&p_item->base, x, y);
}


/**
 * @brief Sets the size of the Item_s component.
 * @param p_item Pointer to the Item_s structure.
 * @param width Width of the component.
 * @param height Height of the component.
 *
 */
void item_setSize(Item_s *p_item, const uint16_t width, const uint16_t height)
{
    base_setSize(&p_item->base, width, height);
}


/**
 * @brief Sets the visibility of the Item_s component.
 * @param p_item Pointer to the Item_s structure.
 * @param visible Visibility state (true for visible, false for hidden).
 *
 */
void item_setVisible(Item_s *p_item, const bool visible)
{
    p_item->base.visible = visible;
}


static void item_display(BaseComponent_s *p_itemBase)
{
#if GUI_CONFIG_USE_ANCHOR
    if (p_itemBase->p_anchor != NULL)
    {
        graphics_setPosistionFromAnchor(p_itemBase);
    }
#endif /* GUI_CONFIG_USE_ANCHOR */

    graphics_displayComponent(p_itemBase);
}
