#include "text_input_view.h"

#include "gui_app.h"
#include "gui_custom_components.h"
#include "logger.h"

#include "main_view.h"

static void tiv_create(View_s *p_view);
static void tiv_enterPressed(Keyboard_s *p_keyboard);
static void tiv_textChanged(Keyboard_s *p_keyboard);

static Keyboard_s m_keyboard;

void text_input_view_navigateTo(void)
{
    view_navigateTo(&g_guiApp.view, tiv_create);
}

static void tiv_create(View_s *p_view)
{
    header_updateTime(false);

    keyboard_init(&m_keyboard);
    keyboard_setText(&m_keyboard, "Hello world");
    keyboard_setOnEnterPressed(&m_keyboard, tiv_enterPressed);
    keyboard_setOnTextChanged(&m_keyboard, tiv_textChanged);

    view_addComponent(p_view, &m_keyboard);
}

static void tiv_enterPressed(Keyboard_s *p_keyboard)
{
    header_updateTime(true);
    gui_drawHeaderBackground();
    gui_drawFooterBackground();
    mainview_navigateTo();
}

static void tiv_textChanged(Keyboard_s *p_keyboard)
{
    log_debug("Text changed: %s", p_keyboard->textBlock.text);
}
