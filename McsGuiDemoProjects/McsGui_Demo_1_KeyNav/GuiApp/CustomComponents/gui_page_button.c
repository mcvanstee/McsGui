#include "gui_page_button.h"

#include <stddef.h>
#include <string.h>

#include "gui_app.h"
#include "Utils/gui_log.h"
#include "Utils/gui_memory.h"

#define GUI_PAGE_BUTTON_BUFFER_SIZE 8

#define PAGE_BTN_WIDTH 146
#define PAGE_BTN_HEIGHT 90


#if !GUI_USE_DYNAMIC_MEMORY
static bool staticPageButtonMemInUse[GUI_PAGE_BUTTON_BUFFER_SIZE];
static PageButton_s staticPageButtonMem[GUI_PAGE_BUTTON_BUFFER_SIZE];
#endif /* GUI_USE_DYNAMIC_MEMORY */

static void page_btn_onDisplay(BaseComponent_s *p_buttonBase);
static void page_btn_focusChanged(BaseComponent_s *p_baseComponent);
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

PageButton_s* page_btn_newInit(void)
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

	keynav_init(&p_pageButton->keyNavigation);
	base_addKeyNavigation(p_pageButton, &p_pageButton->keyNavigation);

	p_pageButton->icon = FILE_KEY_NONE;
	p_pageButton->text = FILE_KEY_NONE;
}

void page_btn_initIconText(
		PageButton_s *p_pageButton,
		const file_key_e icon, const file_key_e text,
		void (*onPressed)(void))
{
	page_btn_init(p_pageButton);
	base_setBmpKey(p_pageButton, FILE_KEY_BUTTON_PAGE_BACKGROUND);
	p_pageButton->icon = icon;
	p_pageButton->text = text;
	button_setOnPressedEvent(&p_pageButton->button, onPressed);
	base_setSize(p_pageButton, PAGE_BTN_WIDTH, PAGE_BTN_HEIGHT);
	base_setOnFocusChanged(&p_pageButton->button, page_btn_focusChanged);
}

static void page_btn_focusChanged(BaseComponent_s *p_baseComponent)
{
    PageButton_s *p_pageButton = (PageButton_s *)p_baseComponent;
    Color_t color = p_pageButton->button.base.focused ? theme_getCursorColor() : theme_getButtonBorderColor();

    Rectangle_s rect;
    rectangle_initBorderPosSize(
            &rect,
            p_baseComponent->x, p_baseComponent->y,
            p_baseComponent->width, p_baseComponent->height,
            2, color);
    rectangle_setRadius(&rect, 3);
    base_display(&rect);
}

static void page_btn_onDisplay(BaseComponent_s *p_buttonBase)
{
    // Do not call base_display() here, it calls this function again.
    //
    theme_setTheme(p_buttonBase);
	page_btn_displayBackground(p_buttonBase);
	page_btn_focusChanged(p_buttonBase);

	PageButton_s *p_pageButton = (PageButton_s*)p_buttonBase;

	Label_s icon;
	label_initBmpPosSize(
			&icon, p_pageButton->icon,
			p_buttonBase->x, p_buttonBase->y,
			p_buttonBase->width, p_buttonBase->height);
	theme_setTheme(&icon);
	theme_setAccentColor(&icon);
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
	gui_translate(&text);
	theme_setTheme(&text);
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
