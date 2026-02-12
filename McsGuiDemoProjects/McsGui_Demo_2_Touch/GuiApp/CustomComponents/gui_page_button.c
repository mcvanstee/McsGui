#include "gui_page_button.h"

#include <stddef.h>
#include <string.h>

#include "gui_app.h"
#include "Core/gui_memory.h"

#define GUI_PAGE_BUTTON_BUFFER_SIZE 8

#define PAGE_BTN_WIDTH 146
#define PAGE_BTN_HEIGHT 90


#if !GUI_USE_DYNAMIC_MEMORY
static bool staticPageButtonMemInUse[GUI_PAGE_BUTTON_BUFFER_SIZE];
static PageButton_s staticPageButtonMem[GUI_PAGE_BUTTON_BUFFER_SIZE];
#endif /* GUI_USE_DYNAMIC_MEMORY */

static void page_btn_onDisplay(BaseComponent_s *p_buttonBase);
static void page_btn_displayBackground(BaseComponent_s *p_baseComponent);

PageButton_s *page_btn_new(void)
{
#if GUI_USE_DYNAMIC_MEMORY
	return gui_mem_malloc(sizeof(PageButton_s));
#else
    for (uint32_t i = 0; i < GUI_PAGE_BUTTON_BUFFER_SIZE; i++)
    {
    	if (!staticPageButtonMemInUse[i])
    	{
    		staticPageButtonMemInUse[i] = true;

    		return &staticPageButtonMem[i];
    	}
    }

    gui_log_write(GUI_LOG_LEVEL_ERROR, "No PageButton_s static memory");

    return NULL;
#endif /* GUI_USE_DYNAMIC_MEMORY */
}

PageButton_s *page_btn_newInit(void)
{
	PageButton_s *p_pageButton = page_btn_new();
    if (p_pageButton != NULL)
    {
        page_btn_init(p_pageButton);
    }

	return p_pageButton;
}

void page_btn_delete(BaseComponent_s *p_pageButtonBase)
{
	base_clear(p_pageButtonBase);
#if GUI_USE_DYNAMIC_MEMORY
    gui_mem_free(p_pageButtonBase, sizeof(PageButton_s));
#else
    for (uint32_t i = 0; i < GUI_PAGE_BUTTON_BUFFER_SIZE; i++)
    {
    	if (&staticPageButtonMem[i].button.base == p_pageButtonBase)
    	{
    		memset(&staticPageButtonMem[i], 0, sizeof(PageButton_s));
    		staticPageButtonMemInUse[i] = false;
    		break;
    	}
    }
#endif /* GUI_USE_DYNAMIC_MEMORY */
}

void page_btn_init(PageButton_s *p_pageButton)
{
	button_init(&p_pageButton->button);
    base_setOnDelete(p_pageButton, page_btn_delete);
    base_setOnDisplay(p_pageButton, page_btn_onDisplay);
    base_setBmpKey(p_pageButton, FILE_KEY_BUTTON_PAGE_BACKGROUND);
    base_setDimensions(p_pageButton, PAGE_BTN_WIDTH, PAGE_BTN_HEIGHT);
	touch_init(&p_pageButton->touch);
	base_addTouch(&p_pageButton->button, &p_pageButton->touch);

	p_pageButton->icon = FILE_KEY_NONE;
	p_pageButton->text = FILE_KEY_NONE;
}

void page_btn_initIconText(
		PageButton_s *p_pageButton,
		const file_key_e icon, const file_key_e text,
		void (*onPressed)(void))
{
	page_btn_init(p_pageButton);

	p_pageButton->icon = icon;
	p_pageButton->text = text;
	button_setOnReleasedEvent(&p_pageButton->button, onPressed);
}

static void page_btn_onDisplay(BaseComponent_s *p_buttonBase)
{
    // Do not call base_display() here, it calls this function again.
    //
    theme_applyThemeProperty(p_buttonBase);
    page_btn_displayBackground(p_buttonBase);

	PageButton_s *p_pageButton = (PageButton_s*)p_buttonBase;

	Label_s icon;
	label_initBmpPosSize(
			&icon, p_pageButton->icon,
			p_buttonBase->x, p_buttonBase->y,
			p_buttonBase->width, p_buttonBase->height);
	theme_applyThemeProperty(&icon);
	theme_applyAccentColorProperty(&icon);
	base_setVerticalAlignment(&icon, Gui_Align_Top);
	base_setTopPadding(&icon, 20);
	base_display(&icon);

	Label_s text;
	label_initBmpPosSize(
			&text, p_pageButton->text,
			p_buttonBase->x, p_buttonBase->y,
			p_buttonBase->width, p_buttonBase->height);
	base_setVerticalAlignment(&text, Gui_Align_Bottom);
	base_setBottomPadding(&text, 18);
	gui_app_translate(&text);
	theme_applyThemeProperty(&text);
	base_display(&text);
}

static void page_btn_displayBackground(BaseComponent_s *p_baseComponent)
{
    Rectangle_s rect;
    rectangle_initFillPosSize(
            &rect, theme_getButtonBackgroundColor(),
            p_baseComponent->x, p_baseComponent->y,
            p_baseComponent->width, p_baseComponent->height);
    rectangle_setRadius(&rect, 3);
    base_display(&rect);
}
