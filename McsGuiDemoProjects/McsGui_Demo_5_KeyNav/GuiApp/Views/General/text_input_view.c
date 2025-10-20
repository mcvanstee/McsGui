#include "text_input_view.h"

#include <stdio.h>

#include "gui_app.h"
#include "gui_custom_components.h"

#include "main_view.h"

static void tiv_create(View_s *p_view);
static void tiv_enterPressed(Keyboard_s *p_keyboard);
static void tiv_textChanged(Keyboard_s *p_keyboard);

static Keyboard_s m_keyboard;

void text_input_view_navigateTo(void)
{
    view_navigateTo(gui_app_getView(), tiv_create);
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
    gui_app_drawHeaderBackground();
    gui_app_drawFooterBackground();
    mainview_navigateTo();
}

static void tiv_textChanged(Keyboard_s *p_keyboard)
{
    char text[GUI_APP_LOG_MESSAGE_LENGTH_INC_NULL] = {0};
    sprintf(text, "Text changed: %s", p_keyboard->textBlock.text);
    gui_log_debug(text);
}
