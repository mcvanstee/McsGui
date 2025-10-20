#include "gui_keyboard.h"

#include <string.h>

#include "Graphics/gui_graphics.h"


#define KB_BTN_HEIGHT 50
#define KB_SMALL_BTN_WIDTH 40
#define KB_MEDIUM_BTN_WIDTH 63
#define KB_LARGE_BTN_WIDTH 109
#define KB_SPACE_BTN_WIDTH 224

#define KB_BUTTON_SPACEING 6

#define KB_ROW1_X 13
#define KB_ROW2_X 37
#define KB_ROW3_X 13
#define KB_ROW4_X 13

#define KB_ROW1_Y 84
#define KB_ROW2_Y (KB_ROW1_Y + KB_BTN_HEIGHT + KB_BUTTON_SPACEING)
#define KB_ROW3_Y (KB_ROW2_Y + KB_BTN_HEIGHT + KB_BUTTON_SPACEING)
#define KB_ROW4_Y (KB_ROW3_Y + KB_BTN_HEIGHT + KB_BUTTON_SPACEING)

#define KB_ROW1_BTN_COUNT 10
#define KB_ROW2_BTN_COUNT 9
#define KB_ROW3_BTN_COUNT 9
#define KB_ROW4_BTN_COUNT 3

#define KB_BACKSPACE 8
#define KB_ENTER 13
#define KB_SPACE 32
#define KB_SWITCH_KEYBOARD 19
#define KB_CAPS 20

typedef struct
{
    uint16_t width;
    char character[3];
} KeyboardBtn_s;

static void keyboard_onDisplay(BaseComponent_s *p_baseComponent);
static void keyboard_delete(BaseComponent_s *p_keyboardBase);
static bool keyboard_handleEvent(BaseComponent_s *p_buttonBase, const GuiEvent_s *p_event);
static bool keyboard_handleBtnEnterPress(Keyboard_s *p_keyboard, const GuiEvent_s *p_event);

static uint8_t keyboard_getBtnRowIndex(const uint16_t pointY);
static char keyboard_getBtnInfoFromBtnRow(
		Keyboard_s *p_keyboard, GuiPoint_s pointPressed,
        const KeyboardBtn_s *p_row, const uint16_t rowBtnCount,
        const uint16_t rowX, const uint16_t rowY);
static char keyboard_getCurrentBtnValue(Keyboard_s *p_keyboard, GuiPoint_s pointPressed);
static file_key_e keyboard_getKeyboard(Keyboard_s *p_keyboard);
static void keyboard_textNotifyChanged(Keyboard_s *p_keyboard);
static void keyboard_showKeyboard(Keyboard_s *p_keyboard);

const static KeyboardBtn_s kb_btnRow1[] = {
        { KB_SMALL_BTN_WIDTH, {'q', 'Q', '1'} }, { KB_SMALL_BTN_WIDTH, {'w', 'W', '2'} }, { KB_SMALL_BTN_WIDTH, {'e', 'E', '3'} }, { KB_SMALL_BTN_WIDTH, {'r', 'R', '4'} },
        { KB_SMALL_BTN_WIDTH, {'t', 'T', '5'} }, { KB_SMALL_BTN_WIDTH, {'y', 'Y', '6'} }, { KB_SMALL_BTN_WIDTH, {'u', 'U', '7'} }, { KB_SMALL_BTN_WIDTH, {'i', 'I', '8'} },
        { KB_SMALL_BTN_WIDTH, {'o', 'O', '9'} }, { KB_SMALL_BTN_WIDTH, {'p', 'P', '0'} } };

const static KeyboardBtn_s kb_btnRow2[] = {
        { KB_SMALL_BTN_WIDTH, {'a', 'A', '+'} }, { KB_SMALL_BTN_WIDTH, {'s', 'S', '-'} }, { KB_SMALL_BTN_WIDTH, {'d', 'D', '*'} }, { KB_SMALL_BTN_WIDTH, {'f', 'F', '='} },
        { KB_SMALL_BTN_WIDTH, {'g', 'G', '<'} }, { KB_SMALL_BTN_WIDTH, {'h', 'H', '>'} }, { KB_SMALL_BTN_WIDTH, {'j', 'J', '/'} }, { KB_SMALL_BTN_WIDTH, {'k', 'K', '('} },
        { KB_SMALL_BTN_WIDTH, {'l', 'L', ')'} } };

const static KeyboardBtn_s kb_btnRow3[] = {
        { KB_MEDIUM_BTN_WIDTH, {KB_CAPS, KB_CAPS, KB_CAPS} },
        { KB_SMALL_BTN_WIDTH, {'z', 'Z', '.'} }, { KB_SMALL_BTN_WIDTH, {'x', 'X', ','} }, { KB_SMALL_BTN_WIDTH, {'c', 'C', ';'} }, { KB_SMALL_BTN_WIDTH, {'v', 'V', ':'} },
        { KB_SMALL_BTN_WIDTH, {'b', 'B', '!'} }, { KB_SMALL_BTN_WIDTH, {'n', 'N', '?'} }, { KB_SMALL_BTN_WIDTH, {'m', 'M', '_'} },
        { KB_MEDIUM_BTN_WIDTH, {KB_BACKSPACE, KB_BACKSPACE, KB_BACKSPACE} } };

const static KeyboardBtn_s kb_btnRow4[] = {
        { KB_LARGE_BTN_WIDTH, {KB_SWITCH_KEYBOARD, KB_SWITCH_KEYBOARD, KB_SWITCH_KEYBOARD} },
        { KB_SPACE_BTN_WIDTH, {KB_SPACE, KB_SPACE, KB_SPACE} },
        { KB_LARGE_BTN_WIDTH, {KB_ENTER, KB_ENTER, KB_ENTER} } };


void keyboard_init(Keyboard_s *p_keyboard)
{
    textblock_init(&p_keyboard->textBlock);
    textblock_setFont(&p_keyboard->textBlock, theme_getKeyboardFont());
    base_setSize(&p_keyboard->textBlock.base, 430, 23);
    base_setPosition(&p_keyboard->textBlock.base, 25, 32);
    base_setHorizontalAlignment(&p_keyboard->textBlock.base, Gui_Align_Left);
    base_setBackground(&p_keyboard->textBlock, theme_keyboard_getTextBackColor());
    base_setTransparent(&p_keyboard->textBlock, false);
    touch_init(&p_keyboard->touch);
    base_addTouch(&p_keyboard->textBlock, &p_keyboard->touch);
    touch_setTouchArea(&p_keyboard->touch, 0, KB_ROW1_Y, STYLE_DISPLAY_WIDTH, (STYLE_DISPLAY_HEIGHT - KB_ROW1_Y));

    p_keyboard->keyboardType = LowerCase;
    base_setOnDisplay(&p_keyboard->textBlock.base, keyboard_onDisplay);
    base_setOnDelete(&p_keyboard->textBlock.base, keyboard_delete);
    base_setOnHandleEvent(&p_keyboard->textBlock.base, keyboard_handleEvent);

    p_keyboard->p_onTextChanged = NULL;
    p_keyboard->p_onEnterPressed = NULL;
}

void keyboard_setText(Keyboard_s *p_keyboard, const char *p_text)
{
    textblock_setText(&p_keyboard->textBlock, p_text);
}

void keyboard_setTextNotifyChanged(Keyboard_s *p_keyboard, const char *p_text)
{
    textblock_setText(&p_keyboard->textBlock, p_text);
    keyboard_textNotifyChanged(p_keyboard);
}

void keyboard_setOnTextChanged(Keyboard_s *p_keyboard, void (*p_onTextChanged)(Keyboard_s *p_keyboard))
{
    p_keyboard->p_onTextChanged = p_onTextChanged;
}

void keyboard_setOnEnterPressed(Keyboard_s *p_keyboard, void (*p_onEnterPressed)(Keyboard_s *p_keyboard))
{
    p_keyboard->p_onEnterPressed = p_onEnterPressed;
}

char *keyboard_getText(Keyboard_s *p_keyboard)
{
    return p_keyboard->textBlock.text;
}

static void keyboard_delete(BaseComponent_s *p_keyboardBase)
{

}

static void keyboard_onDisplay(BaseComponent_s *p_baseComponent)
{
    Keyboard_s *p_keyboard = (Keyboard_s *)p_baseComponent;

    Label_s textbox;
    label_initBmpPos(&textbox, FILE_KEY_KEYBOARD_TEXTBOX, 0, 0);
    theme_setTheme(&textbox);
    base_display(&textbox);
    graphics_displayComponent(p_baseComponent); // display text

    keyboard_showKeyboard(p_keyboard);
}

static bool keyboard_handleEvent(BaseComponent_s *p_buttonBase, const GuiEvent_s *p_event)
{
    Keyboard_s *p_keyboard = (Keyboard_s *)p_buttonBase;
    bool eventHandled = false;

    if (p_event->event == GUI_EVENT_TOUCH_ON_RELEASED)
    {
    	eventHandled = keyboard_handleBtnEnterPress(p_keyboard, p_event);
    }

    return eventHandled;
}

static bool keyboard_handleBtnEnterPress(Keyboard_s *p_keyboard, const GuiEvent_s *p_event)
{
    const uint16_t xPosPressed = ((uint16_t)p_event->eventArgs[1] << 8) + p_event->eventArgs[0];
    const uint16_t yPosPressed = ((uint16_t)p_event->eventArgs[3] << 8) + p_event->eventArgs[2];
    const GuiPoint_s pointPressed = {xPosPressed, yPosPressed};
    const char c = keyboard_getCurrentBtnValue(p_keyboard, pointPressed);

	if (c == 0)
	{
		return false;
	}
    else if (c == KB_ENTER)
    {
        if (p_keyboard->p_onEnterPressed != NULL)
        {
            p_keyboard->p_onEnterPressed(p_keyboard);
        }
    }
    else if (c == KB_BACKSPACE)
    {
        const uint16_t textLength = strlen(p_keyboard->textBlock.text);
        if (textLength > 0)
        {
            p_keyboard->textBlock.text[textLength - 1] = 0;
            base_setTransparent(&p_keyboard->textBlock, false);
            graphics_displayComponent(&p_keyboard->textBlock.base); // display text
            base_setTransparent(&p_keyboard->textBlock, true);
            keyboard_textNotifyChanged(p_keyboard);
        }
    }
    else if (c == KB_CAPS)
    {
        if (p_keyboard->keyboardType == LowerCase)
        {
            p_keyboard->keyboardType = UpperCase;
            keyboard_showKeyboard(p_keyboard);
        }
        else if (p_keyboard->keyboardType == UpperCase)
        {
            p_keyboard->keyboardType = LowerCase;
            keyboard_showKeyboard(p_keyboard);
        }
        else
        {
        }
    }
    else if (c == KB_SWITCH_KEYBOARD)
    {
        if ((p_keyboard->keyboardType == LowerCase) || (p_keyboard->keyboardType == UpperCase))
        {
            p_keyboard->keyboardType = NumbersAndSpecialCharacters;
            keyboard_showKeyboard(p_keyboard);
        }
        else if (p_keyboard->keyboardType == NumbersAndSpecialCharacters)
        {
            p_keyboard->keyboardType = LowerCase;
            keyboard_showKeyboard(p_keyboard);
        }
        else
        {
        }
    }
    else
    {
        const uint16_t textLength = strlen(p_keyboard->textBlock.text);

        if (textLength < GUI_CONFIG_TEXTBLOCK_MAX_STRING_LENGTH)
        {
            char str[2] = {0};
            str[0] = c;
            strcat(p_keyboard->textBlock.text, str);
            graphics_displayComponent(&p_keyboard->textBlock.base); // display text
            keyboard_textNotifyChanged(p_keyboard);
        }
    }

    return true;
}

static uint8_t keyboard_getBtnRowIndex(const uint16_t pointY)
{
	if ((pointY >= KB_ROW1_Y) && (pointY <= (KB_ROW1_Y + KB_BTN_HEIGHT)))
	{
		return 1;
	}
	else if ((pointY >= KB_ROW2_Y) && (pointY <= (KB_ROW2_Y + KB_BTN_HEIGHT)))
	{
		return 2;
	}
	else if ((pointY >= KB_ROW3_Y) && (pointY <= (KB_ROW3_Y + KB_BTN_HEIGHT)))
	{
		return 3;
	}
	else if ((pointY >= KB_ROW4_Y) && (pointY <= (KB_ROW4_Y + KB_BTN_HEIGHT)))
	{
		return 4;
	}
	else
	{
		return 0;
	}
}

static char keyboard_getBtnInfoFromBtnRow(
		Keyboard_s *p_keyboard, GuiPoint_s pointPressed,
        const KeyboardBtn_s *p_row, const uint16_t rowBtnCount,
        const uint16_t rowX, const uint16_t rowY)
{
    char charValue = 0;
    uint16_t xBtn = rowX;

    for (uint16_t i = 0; i < rowBtnCount; i++)
    {
    	if (xBtn <= pointPressed.x && pointPressed.x <= (xBtn + p_row[i].width))
		{
    		KeyboardBtn_s const *p_btn = &p_row[i];
    		charValue = p_btn->character[p_keyboard->keyboardType];

    		break;
		}

    	xBtn += p_row[i].width + KB_BUTTON_SPACEING;
    }

    return charValue;
}

static char keyboard_getCurrentBtnValue(Keyboard_s *p_keyboard, GuiPoint_s pointPressed)
{
    char charValue = 0;

    uint8_t row = keyboard_getBtnRowIndex(pointPressed.y);

    switch (row)
    {
        case 1:
        	charValue = keyboard_getBtnInfoFromBtnRow(
        			p_keyboard, pointPressed,
                    kb_btnRow1, KB_ROW1_BTN_COUNT,
                    KB_ROW1_X, KB_ROW1_Y);
            break;
        case 2:
        	charValue = keyboard_getBtnInfoFromBtnRow(
        			p_keyboard, pointPressed,
                    kb_btnRow2, KB_ROW2_BTN_COUNT,
                    KB_ROW2_X, KB_ROW2_Y);
            break;
        case 3:
        	charValue = keyboard_getBtnInfoFromBtnRow(
        			p_keyboard, pointPressed,
                    kb_btnRow3, KB_ROW3_BTN_COUNT,
                    KB_ROW3_X, KB_ROW3_Y);
            break;
        case 4:
        	charValue = keyboard_getBtnInfoFromBtnRow(
        			p_keyboard, pointPressed,
                    kb_btnRow4, KB_ROW4_BTN_COUNT,
                    KB_ROW4_X, KB_ROW4_Y);
            break;
        default:
            break;
    }

    return charValue;
}

static file_key_e keyboard_getKeyboard(Keyboard_s *p_keyboard)
{
    switch (p_keyboard->keyboardType)
    {
        case LowerCase:
            return FILE_KEY_KEYBOARD_LC;
        case UpperCase:
            return FILE_KEY_KEYBOARD_UC;
        case NumbersAndSpecialCharacters:
            return FILE_KEY_KEYBOARD_NUM;
        default:
            return FILE_KEY_KEYBOARD_LC;
    }
}

static void keyboard_textNotifyChanged(Keyboard_s *p_keyboard)
{
    if (p_keyboard->p_onTextChanged != NULL)
    {
        p_keyboard->p_onTextChanged(p_keyboard);
    }
}

static void keyboard_showKeyboard(Keyboard_s *p_keyboard)
{
    const file_key_e kbBmp = keyboard_getKeyboard(p_keyboard);

    Label_s keyboard;
    label_initBmpPos(&keyboard, kbBmp, 0, 84);
    theme_setTheme(&keyboard);
    base_display(&keyboard);
}
