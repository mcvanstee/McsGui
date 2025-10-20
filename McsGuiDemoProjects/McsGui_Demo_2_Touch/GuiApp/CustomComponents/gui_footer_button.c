#include "gui_footer_button.h"

#include <stddef.h>

#include "Utils/gui_log.h"
#include "Utils/gui_memory.h"

#define GUI_FOOTER_BUTTON_BUFFER_SIZE 4


#if !GUI_USE_DYNAMIC_MEMORY
static bool staticFooterButtonMemInUse[GUI_FOOTER_BUTTON_BUFFER_SIZE];
static FooterButton_s staticFooterButtonMem[GUI_FOOTER_BUTTON_BUFFER_SIZE];
#endif /* GUI_USE_DYNAMIC_MEMORY */

static void footer_btn_onDisplay(BaseComponent_s *p_buttonBase);
static void footer_btn_displayBackground(BaseComponent_s *p_baseComponent);

FooterButton_s* footer_btn_new(void)
{
#if GUI_USE_DYNAMIC_MEMORY
	return gui_mem_malloc(sizeof(FooterButton_s));
#else
	for (uint32_t i = 0; i < GUI_FOOTER_BUTTON_BUFFER_SIZE; i++)
	{
		if (!staticFooterButtonMemInUse[i])
		{
			staticFooterButtonMemInUse[i] = true;

			return &staticFooterButtonMem[i];
		}
	}

	gui_log_write(GUI_LOG_LEVEL_ERROR, "No FooterButton_s static memory");

	return NULL;
#endif /* GUI_USE_DYNAMIC_MEMORY */
}

FooterButton_s* footer_btn_newInit(void)
{
	FooterButton_s *p_footerButton = footer_btn_new();
    if (p_footerButton != NULL)
    {
        footer_btn_init(p_footerButton);
    }

	return p_footerButton;
}

void footer_btn_delete(BaseComponent_s *p_footerButtonBase)
{
    base_clear(p_footerButtonBase);
#if GUI_USE_DYNAMIC_MEMORY
    gui_mem_free(p_footerButtonBase, sizeof(FooterButton_s));
#else
    for (uint32_t i = 0; i < GUI_FOOTER_BUTTON_BUFFER_SIZE; i++)
    {
        if (&staticFooterButtonMem[i].button.base == p_footerButtonBase)
        {
            staticFooterButtonMemInUse[i] = false;
            break;
        }
    }
#endif /* GUI_USE_DYNAMIC_MEMORY */
}

void footer_btn_init(FooterButton_s *p_footerButton)
{
    button_init(&p_footerButton->button);
    base_setOnDelete(p_footerButton, footer_btn_delete);
    base_setOnDisplay(p_footerButton, footer_btn_onDisplay);
    touch_init(&p_footerButton->touch);
    base_addTouch(&p_footerButton->button.base, &p_footerButton->touch);
    p_footerButton->content = FILE_KEY_NONE;
}

void footer_btn_initIcon(
        FooterButton_s *p_footerButton,
        file_key_e icon,
        void (*onPressed)(void))
{
    footer_btn_init(p_footerButton);

    base_setBmpKey(&p_footerButton->button.base, FILE_KEY_BUTTON_FOOTER_BUTTON);
    base_setSize(&p_footerButton->button.base, FOOTER_BTN_WIDTH, FOOTER_BTN_HEIGHT);
    button_setOnReleasedEvent(&p_footerButton->button, onPressed);

    p_footerButton->content = icon;
}

static void footer_btn_onDisplay(BaseComponent_s *p_buttonBase)
{
    // Do not call base_display() here, it calls this function again.
    //
    theme_setTheme(p_buttonBase);
    footer_btn_displayBackground(p_buttonBase);

    FooterButton_s *p_footerButton = (FooterButton_s*) p_buttonBase;

    Label_s content;
    label_initBmpPosSize(&content, p_footerButton->content,
            p_buttonBase->x, p_buttonBase->y,
            p_buttonBase->width, p_buttonBase->height);
    theme_setTheme(&content);
    theme_setAccentColor(&content);
    base_display(&content);
}

static void footer_btn_displayBackground(BaseComponent_s *p_baseComponent)
{
    Rectangle_s rect;
    rectangle_initFillPosSize(
            &rect, theme_getButtonBackgroundColor(),
            p_baseComponent->x, p_baseComponent->y,
            p_baseComponent->width, p_baseComponent->height);
    rectangle_setRadius(&rect, 4);
    base_display(&rect);
}
