#ifndef CUSTOMCOMPONENTS_GUI_KEYBOARD_H_
#define CUSTOMCOMPONENTS_GUI_KEYBOARD_H_

#include "gui_theme.h"

typedef enum
{
    LowerCase,
    UpperCase,
    NumbersAndSpecialCharacters,
} KeyboardType_e;

typedef struct keyboard_s
{
    TextBlock_s textBlock;
    KeyboardType_e keyboardType;
    Touch_s touch;
    void (*p_onTextChanged)(struct keyboard_s *p_keyboard);
    void (*p_onEnterPressed)(struct keyboard_s *p_keyboard);
} Keyboard_s;


void keyboard_init(Keyboard_s *p_keyboard);

void keyboard_setText(Keyboard_s *p_keyboard, const char *p_text);
void keyboard_setTextNotifyChanged(Keyboard_s *p_keyboard, const char *p_text);
void keyboard_setOnTextChanged(Keyboard_s *p_keyboard, void (*p_onTextChanged)(Keyboard_s *p_keyboard));
void keyboard_setOnEnterPressed(Keyboard_s *p_keyboard, void (*p_onEnterPressed)(Keyboard_s *p_keyboard));
char *keyboard_getText(Keyboard_s *p_keyboard);

#endif /* CUSTOMCOMPONENTS_GUI_KEYBOARD_H_ */
