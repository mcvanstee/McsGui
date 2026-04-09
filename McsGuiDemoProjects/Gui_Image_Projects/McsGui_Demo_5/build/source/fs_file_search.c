#include "fs_file_search.h"

#define FS_FILE_INFO_SIZE 9
#define FS_FILE_DUMMY 0xFFFFFFFFU

const fs_file_info_s fs_file_infos[] =
{                                                                      /* filename, fileproperty, datalocation */
    { .dataOffset = 0x00000032, .properties = 2, .width = 32, .height = 27 },    /* IRL-Logo_@B000, 10, 0 - SD */
    { .dataOffset = 0x0000076D, .properties = 2, .width = 36, .height = 29 },    /* IRL-Logo_@B001, 10, 0 - SD */
    { .dataOffset = 0x00000FC5, .properties = 2, .width = 39, .height = 32 },    /* IRL-Logo_@B002, 10, 0 - SD */
    { .dataOffset = 0x0000195B, .properties = 2, .width = 42, .height = 35 },    /* IRL-Logo_@B003, 10, 0 - SD */
    { .dataOffset = 0x00002420, .properties = 2, .width = 46, .height = 37 },    /* IRL-Logo_@B004, 10, 0 - SD */
    { .dataOffset = 0x00003056, .properties = 2, .width = 49, .height = 40 },    /* IRL-Logo_@B005, 10, 0 - SD */
    { .dataOffset = 0x00003DC4, .properties = 2, .width = 52, .height = 43 },    /* IRL-Logo_@B006, 10, 0 - SD */
    { .dataOffset = 0x00004D5D, .properties = 2, .width = 56, .height = 46 },    /* IRL-Logo_@B007, 10, 0 - SD */
    { .dataOffset = 0x00005DB3, .properties = 2, .width = 59, .height = 48 },    /* IRL-Logo_@B008, 10, 0 - SD */
    { .dataOffset = 0x00006FA7, .properties = 2, .width = 62, .height = 50 },    /* IRL-Logo_@B009, 10, 0 - SD */
    { .dataOffset = 0x00008267, .properties = 2, .width = 65, .height = 54 },    /* IRL-Logo_@B010, 10, 0 - SD */
    { .dataOffset = 0x000096D4, .properties = 2, .width = 69, .height = 56 },    /* IRL-Logo_@B011, 10, 0 - SD */
    { .dataOffset = 0x0000AC52, .properties = 2, .width = 72, .height = 59 },    /* IRL-Logo_@B012, 10, 0 - SD */
    { .dataOffset = 0x0000C29C, .properties = 2, .width = 76, .height = 62 },    /* IRL-Logo_@B013, 10, 0 - SD */
    { .dataOffset = 0x0000DB23, .properties = 2, .width = 79, .height = 64 },    /* IRL-Logo_@B014, 10, 0 - SD */
    { .dataOffset = 0x0000F500, .properties = 2, .width = 82, .height = 67 },    /* IRL-Logo_@B015, 10, 0 - SD */
    { .dataOffset = 0x00010F19, .properties = 2, .width = 86, .height = 69 },    /* IRL-Logo_@B016, 10, 0 - SD */
    { .dataOffset = 0x00012B30, .properties = 2, .width = 89, .height = 72 },    /* IRL-Logo_@B017, 10, 0 - SD */
    { .dataOffset = 0x0001485E, .properties = 2, .width = 92, .height = 75 },    /* IRL-Logo_@B018, 10, 0 - SD */
    { .dataOffset = 0x000165C5, .properties = 2, .width = 95, .height = 77 },    /* IRL-Logo_@B019, 10, 0 - SD */
    { .dataOffset = 0x0001859C, .properties = 2, .width = 100, .height = 80 },    /* IRL-Logo_@B020, 10, 0 - SD */
    { .dataOffset = 0x0001A798, .properties = 2, .width = 102, .height = 83 },    /* IRL-Logo_@B021, 10, 0 - SD */
    { .dataOffset = 0x0001C99A, .properties = 2, .width = 105, .height = 85 },    /* IRL-Logo_@B022, 10, 0 - SD */
    { .dataOffset = 0x0001ECA7, .properties = 2, .width = 109, .height = 88 },    /* IRL-Logo_@B023, 10, 0 - SD */
    { .dataOffset = 0x00020FD5, .properties = 1, .width = 30, .height = 30 },    /* NumInput_minus@A0, 1, 0 - SD */
    { .dataOffset = 0x00021290, .properties = 1, .width = 30, .height = 30 },    /* NumInput_minus@A1, 1, 0 - SD */
    { .dataOffset = 0x000214D3, .properties = 1, .width = 30, .height = 30 },    /* NumInput_plus@A0, 1, 0 - SD */
    { .dataOffset = 0x00021836, .properties = 1, .width = 30, .height = 30 },    /* NumInput_plus@A1, 1, 0 - SD */
    { .dataOffset = 0x00021B21, .properties = 1, .width = 22, .height = 31 },    /* Slider@A0, 1, 0 - SD */
    { .dataOffset = 0x00021C62, .properties = 1, .width = 22, .height = 31 },    /* Slider@A1, 1, 0 - SD */
    { .dataOffset = 0x00021D73, .properties = 0, .width = 128, .height = 128 },    /* IRL_Logo 128, 0, 0 - SD */
    { .dataOffset = 0x00023168, .properties = 0, .width = 48, .height = 48 },    /* IRL_Logo_48, 0, 0 - SD */
    { .dataOffset = 0x000237EC, .properties = 1, .width = 480, .height = 236 },    /* Keyboard_lc@A0, 1, 0 - SD */
    { .dataOffset = 0x00028DFF, .properties = 1, .width = 480, .height = 236 },    /* Keyboard_lc@A1, 1, 0 - SD */
    { .dataOffset = 0x0002E418, .properties = 1, .width = 480, .height = 236 },    /* Keyboard_num@A0, 1, 0 - SD */
    { .dataOffset = 0x000330AA, .properties = 1, .width = 480, .height = 236 },    /* Keyboard_num@A1, 1, 0 - SD */
    { .dataOffset = 0x00037D42, .properties = 1, .width = 480, .height = 84 },    /* Keyboard_textbox@A0, 1, 0 - SD */
    { .dataOffset = 0x000380ED, .properties = 1, .width = 480, .height = 84 },    /* Keyboard_textbox@A1, 1, 0 - SD */
    { .dataOffset = 0x00038498, .properties = 1, .width = 480, .height = 236 },    /* Keyboard_uc@A0, 1, 0 - SD */
    { .dataOffset = 0x0003E28B, .properties = 1, .width = 480, .height = 236 },    /* Keyboard_uc@A1, 1, 0 - SD */
    { .dataOffset = 0x00044081, .properties = 0, .width = 74, .height = 29 },    /* text_footer_mcsgui, 0, 0 - SD */
    { .dataOffset = 0x00044732, .properties = 0, .width = 37, .height = 23 },    /* text_pane_chinese_sim, 0, 0 - SD */
    { .dataOffset = 0x000449E4, .properties = 0, .width = 17, .height = 23 },    /* text_pane_deg_cel, 0, 0 - SD */
    { .dataOffset = 0x00044B1C, .properties = 0, .width = 16, .height = 23 },    /* text_pane_deg_far, 0, 0 - SD */
    { .dataOffset = 0x00044C00, .properties = 0, .width = 93, .height = 23 },    /* text_pane_dutch, 0, 0 - SD */
    { .dataOffset = 0x00045473, .properties = 0, .width = 58, .height = 23 },    /* text_pane_english, 0, 0 - SD */
    { .dataOffset = 0x000459D1, .properties = 0, .width = 69, .height = 23 },    /* text_pane_french, 0, 0 - SD */
    { .dataOffset = 0x00045F98, .properties = 0, .width = 66, .height = 23 },    /* text_pane_german, 0, 0 - SD */
    { .dataOffset = 0x00046529, .properties = 0, .width = 59, .height = 23 },    /* text_pane_italian, 0, 0 - SD */
    { .dataOffset = 0x00046A9F, .properties = 0, .width = 57, .height = 23 },    /* text_pane_japanese, 0, 0 - SD */
    { .dataOffset = 0x00046F6D, .properties = 0, .width = 51, .height = 23 },    /* text_pane_korean, 0, 0 - SD */
    { .dataOffset = 0x000472CA, .properties = 0, .width = 69, .height = 23 },    /* text_pane_russian, 0, 0 - SD */
    { .dataOffset = 0x000478A3, .properties = 0, .width = 64, .height = 23 },    /* text_pane_spanish, 0, 0 - SD */
    { .dataOffset = 0x00047E04, .properties = 0, .width = 43, .height = 23 },    /* text_pane_time_mm, 0, 0 - SD */
    { .dataOffset = 0x00000000, .properties = 0, .width = 18, .height = 20 },    /* icon_Agenda, 0, 1 - code */
    { .dataOffset = 0x000000BD, .properties = 0, .width = 35, .height = 18 },    /* icon_Arrow-Back, 0, 1 - code */
    { .dataOffset = 0x0000012B, .properties = 0, .width = 13, .height = 4 },    /* icon_Arrow_down, 0, 1 - code */
    { .dataOffset = 0x00000158, .properties = 0, .width = 12, .height = 4 },    /* icon_Arrow_up, 0, 1 - code */
    { .dataOffset = 0x00000181, .properties = 0, .width = 16, .height = 18 },    /* icon_Bell, 0, 1 - code */
    { .dataOffset = 0x000001F0, .properties = 0, .width = 30, .height = 25 },    /* icon_Brightness, 0, 1 - code */
    { .dataOffset = 0x00000313, .properties = 0, .width = 22, .height = 22 },    /* icon_Brush, 0, 1 - code */
    { .dataOffset = 0x000003BC, .properties = 0, .width = 18, .height = 18 },    /* icon_Cancel, 0, 1 - code */
    { .dataOffset = 0x00000483, .properties = 0, .width = 16, .height = 13 },    /* icon_Checkmark, 0, 1 - code */
    { .dataOffset = 0x000004E9, .properties = 0, .width = 26, .height = 21 },    /* icon_Checkmark_large, 0, 1 - code */
    { .dataOffset = 0x0000059E, .properties = 0, .width = 20, .height = 20 },    /* icon_Clock, 0, 1 - code */
    { .dataOffset = 0x000006B9, .properties = 0, .width = 22, .height = 22 },    /* icon_Focus, 0, 1 - code */
    { .dataOffset = 0x00000738, .properties = 0, .width = 22, .height = 22 },    /* icon_Gear, 0, 1 - code */
    { .dataOffset = 0x0000081E, .properties = 0, .width = 20, .height = 20 },    /* icon_Global, 0, 1 - code */
    { .dataOffset = 0x00000959, .properties = 0, .width = 21, .height = 21 },    /* icon_Info, 0, 1 - code */
    { .dataOffset = 0x00000A9B, .properties = 0, .width = 23, .height = 16 },    /* icon_Keyboard, 0, 1 - code */
    { .dataOffset = 0x00000B87, .properties = 0, .width = 16, .height = 4 },    /* icon_minus, 0, 1 - code */
    { .dataOffset = 0x00000B97, .properties = 0, .width = 22, .height = 22 },    /* icon_Palette, 0, 1 - code */
    { .dataOffset = 0x00000C6B, .properties = 0, .width = 16, .height = 16 },    /* icon_plus, 0, 1 - code */
    { .dataOffset = 0x00000CCC, .properties = 0, .width = 18, .height = 18 },    /* icon_Radio-Button-Checked, 0, 1 - code */
    { .dataOffset = 0x00000DD4, .properties = 0, .width = 18, .height = 18 },    /* icon_Radio-Button-UnChecked, 0, 1 - code */
    { .dataOffset = 0x00000E9D, .properties = 0, .width = 22, .height = 22 },    /* icon_Sliders, 0, 1 - code */
    { .dataOffset = 0x00000F17, .properties = 0, .width = 25, .height = 18 },    /* icon_Wifi, 0, 1 - code */
    { .dataOffset = 0x00000FD7, .properties = 4, .width = 92, .height = 21 },    /* text_accent_color@C0, 100, 1 - code */
    { .dataOffset = 0x0000130A, .properties = 4, .width = 91, .height = 21 },    /* text_accent_color@C1, 100, 1 - code */
    { .dataOffset = 0x00001643, .properties = 4, .width = 131, .height = 21 },    /* text_accent_color@C2, 100, 1 - code */
    { .dataOffset = 0x00001AD7, .properties = 4, .width = 122, .height = 21 },    /* text_accent_color@C3, 100, 1 - code */
    { .dataOffset = 0x00001F4F, .properties = 4, .width = 115, .height = 21 },    /* text_accent_color@C4, 100, 1 - code */
    { .dataOffset = 0x00002336, .properties = 4, .width = 122, .height = 21 },    /* text_accent_color@C5, 100, 1 - code */
    { .dataOffset = 0x00002788, .properties = 4, .width = 127, .height = 21 },    /* text_accent_color@C6, 100, 1 - code */
    { .dataOffset = 0x00002BC0, .properties = 4, .width = 50, .height = 21 },    /* text_accent_color@C7, 100, 1 - code */
    { .dataOffset = 0x00002DF8, .properties = 4, .width = 106, .height = 21 },    /* text_accent_color@C8, 100, 1 - code */
    { .dataOffset = 0x000030D1, .properties = 4, .width = 68, .height = 21 },    /* text_accent_color@C9, 100, 1 - code */
    { .dataOffset = 0x000032F5, .properties = 4, .width = 55, .height = 21 },    /* text_alarm@C0, 100, 1 - code */
    { .dataOffset = 0x00003538, .properties = 4, .width = 55, .height = 21 },    /* text_alarm@C1, 100, 1 - code */
    { .dataOffset = 0x0000377B, .properties = 4, .width = 55, .height = 21 },    /* text_alarm@C2, 100, 1 - code */
    { .dataOffset = 0x000039BE, .properties = 4, .width = 64, .height = 21 },    /* text_alarm@C3, 100, 1 - code */
    { .dataOffset = 0x00003C6E, .properties = 4, .width = 64, .height = 21 },    /* text_alarm@C4, 100, 1 - code */
    { .dataOffset = 0x00003F15, .properties = 4, .width = 68, .height = 21 },    /* text_alarm@C5, 100, 1 - code */
    { .dataOffset = 0x0000420D, .properties = 4, .width = 74, .height = 21 },    /* text_alarm@C6, 100, 1 - code */
    { .dataOffset = 0x000044E7, .properties = 4, .width = 48, .height = 21 },    /* text_alarm@C7, 100, 1 - code */
    { .dataOffset = 0x00004727, .properties = 4, .width = 47, .height = 21 },    /* text_alarm@C8, 100, 1 - code */
    { .dataOffset = 0x00004958, .properties = 4, .width = 60, .height = 21 },    /* text_alarm@C9, 100, 1 - code */
    { .dataOffset = 0x00004B69, .properties = 4, .width = 76, .height = 21 },    /* text_brightness@C0, 100, 1 - code */
    { .dataOffset = 0x00004E87, .properties = 4, .width = 77, .height = 21 },    /* text_brightness@C1, 100, 1 - code */
    { .dataOffset = 0x000051B1, .properties = 4, .width = 67, .height = 21 },    /* text_brightness@C2, 100, 1 - code */
    { .dataOffset = 0x000054B5, .properties = 4, .width = 80, .height = 21 },    /* text_brightness@C3, 100, 1 - code */
    { .dataOffset = 0x000057A2, .properties = 4, .width = 35, .height = 21 },    /* text_brightness@C4, 100, 1 - code */
    { .dataOffset = 0x00005951, .properties = 4, .width = 80, .height = 21 },    /* text_brightness@C5, 100, 1 - code */
    { .dataOffset = 0x00005C4C, .properties = 4, .width = 63, .height = 21 },    /* text_brightness@C6, 100, 1 - code */
    { .dataOffset = 0x00005E79, .properties = 4, .width = 34, .height = 21 },    /* text_brightness@C7, 100, 1 - code */
    { .dataOffset = 0x00005FDC, .properties = 4, .width = 41, .height = 21 },    /* text_brightness@C8, 100, 1 - code */
    { .dataOffset = 0x000061A6, .properties = 4, .width = 29, .height = 21 },    /* text_brightness@C9, 100, 1 - code */
    { .dataOffset = 0x00006299, .properties = 4, .width = 47, .height = 21 },    /* text_colors@C0, 100, 1 - code */
    { .dataOffset = 0x0000645B, .properties = 4, .width = 53, .height = 21 },    /* text_colors@C1, 100, 1 - code */
    { .dataOffset = 0x00006663, .properties = 4, .width = 48, .height = 21 },    /* text_colors@C2, 100, 1 - code */
    { .dataOffset = 0x0000680A, .properties = 4, .width = 64, .height = 21 },    /* text_colors@C3, 100, 1 - code */
    { .dataOffset = 0x00006A7B, .properties = 4, .width = 55, .height = 21 },    /* text_colors@C4, 100, 1 - code */
    { .dataOffset = 0x00006C84, .properties = 4, .width = 42, .height = 21 },    /* text_colors@C5, 100, 1 - code */
    { .dataOffset = 0x00006E25, .properties = 4, .width = 48, .height = 21 },    /* text_colors@C6, 100, 1 - code */
    { .dataOffset = 0x00006FF3, .properties = 4, .width = 35, .height = 21 },    /* text_colors@C7, 100, 1 - code */
    { .dataOffset = 0x00007196, .properties = 4, .width = 17, .height = 21 },    /* text_colors@C8, 100, 1 - code */
    { .dataOffset = 0x0000722A, .properties = 4, .width = 32, .height = 21 },    /* text_colors@C9, 100, 1 - code */
    { .dataOffset = 0x0000735F, .properties = 4, .width = 32, .height = 21 },    /* text_date@C0, 100, 1 - code */
    { .dataOffset = 0x000074A3, .properties = 4, .width = 46, .height = 21 },    /* text_date@C1, 100, 1 - code */
    { .dataOffset = 0x00007664, .properties = 4, .width = 46, .height = 21 },    /* text_date@C2, 100, 1 - code */
    { .dataOffset = 0x00007825, .properties = 4, .width = 32, .height = 21 },    /* text_date@C3, 100, 1 - code */
    { .dataOffset = 0x00007969, .properties = 4, .width = 42, .height = 21 },    /* text_date@C4, 100, 1 - code */
    { .dataOffset = 0x00007AC7, .properties = 4, .width = 52, .height = 21 },    /* text_date@C5, 100, 1 - code */
    { .dataOffset = 0x00007CAA, .properties = 4, .width = 37, .height = 21 },    /* text_date@C6, 100, 1 - code */
    { .dataOffset = 0x00007DF7, .properties = 4, .width = 31, .height = 21 },    /* text_date@C7, 100, 1 - code */
    { .dataOffset = 0x00007F47, .properties = 4, .width = 32, .height = 21 },    /* text_date@C8, 100, 1 - code */
    { .dataOffset = 0x00008070, .properties = 4, .width = 30, .height = 21 },    /* text_date@C9, 100, 1 - code */
    { .dataOffset = 0x00008194, .properties = 4, .width = 27, .height = 21 },    /* text_info@C0, 100, 1 - code */
    { .dataOffset = 0x0000829C, .properties = 4, .width = 27, .height = 21 },    /* text_info@C1, 100, 1 - code */
    { .dataOffset = 0x000083A4, .properties = 4, .width = 27, .height = 21 },    /* text_info@C2, 100, 1 - code */
    { .dataOffset = 0x000084AC, .properties = 4, .width = 27, .height = 21 },    /* text_info@C3, 100, 1 - code */
    { .dataOffset = 0x000085B4, .properties = 4, .width = 86, .height = 21 },    /* text_info@C4, 100, 1 - code */
    { .dataOffset = 0x000088CB, .properties = 4, .width = 90, .height = 21 },    /* text_info@C5, 100, 1 - code */
    { .dataOffset = 0x00008BEB, .properties = 4, .width = 99, .height = 21 },    /* text_info@C6, 100, 1 - code */
    { .dataOffset = 0x00008FEA, .properties = 4, .width = 35, .height = 21 },    /* text_info@C7, 100, 1 - code */
    { .dataOffset = 0x0000913A, .properties = 4, .width = 35, .height = 21 },    /* text_info@C8, 100, 1 - code */
    { .dataOffset = 0x000092D6, .properties = 4, .width = 31, .height = 21 },    /* text_info@C9, 100, 1 - code */
    { .dataOffset = 0x000093D3, .properties = 4, .width = 67, .height = 21 },    /* text_keyboard@C0, 100, 1 - code */
    { .dataOffset = 0x0000966C, .properties = 4, .width = 92, .height = 21 },    /* text_keyboard@C1, 100, 1 - code */
    { .dataOffset = 0x000099AD, .properties = 4, .width = 61, .height = 21 },    /* text_keyboard@C2, 100, 1 - code */
    { .dataOffset = 0x00009BF5, .properties = 4, .width = 50, .height = 21 },    /* text_keyboard@C3, 100, 1 - code */
    { .dataOffset = 0x00009DF2, .properties = 4, .width = 58, .height = 21 },    /* text_keyboard@C4, 100, 1 - code */
    { .dataOffset = 0x0000A01B, .properties = 4, .width = 59, .height = 21 },    /* text_keyboard@C5, 100, 1 - code */
    { .dataOffset = 0x0000A247, .properties = 4, .width = 89, .height = 21 },    /* text_keyboard@C6, 100, 1 - code */
    { .dataOffset = 0x0000A5B2, .properties = 4, .width = 35, .height = 21 },    /* text_keyboard@C7, 100, 1 - code */
    { .dataOffset = 0x0000A76B, .properties = 4, .width = 71, .height = 21 },    /* text_keyboard@C8, 100, 1 - code */
    { .dataOffset = 0x0000A906, .properties = 4, .width = 47, .height = 21 },    /* text_keyboard@C9, 100, 1 - code */
    { .dataOffset = 0x0000AA23, .properties = 4, .width = 70, .height = 21 },    /* text_language@C0, 100, 1 - code */
    { .dataOffset = 0x0000ACF6, .properties = 4, .width = 31, .height = 21 },    /* text_language@C1, 100, 1 - code */
    { .dataOffset = 0x0000AE2B, .properties = 4, .width = 59, .height = 21 },    /* text_language@C2, 100, 1 - code */
    { .dataOffset = 0x0000B08D, .properties = 4, .width = 52, .height = 21 },    /* text_language@C3, 100, 1 - code */
    { .dataOffset = 0x0000B296, .properties = 4, .width = 48, .height = 21 },    /* text_language@C4, 100, 1 - code */
    { .dataOffset = 0x0000B482, .properties = 4, .width = 47, .height = 21 },    /* text_language@C5, 100, 1 - code */
    { .dataOffset = 0x0000B676, .properties = 4, .width = 40, .height = 21 },    /* text_language@C6, 100, 1 - code */
    { .dataOffset = 0x0000B80B, .properties = 4, .width = 35, .height = 21 },    /* text_language@C7, 100, 1 - code */
    { .dataOffset = 0x0000B929, .properties = 4, .width = 35, .height = 21 },    /* text_language@C8, 100, 1 - code */
    { .dataOffset = 0x0000BA3F, .properties = 4, .width = 29, .height = 21 },    /* text_language@C9, 100, 1 - code */
    { .dataOffset = 0x0000BB6F, .properties = 4, .width = 100, .height = 21 },    /* text_measurement@C0, 100, 1 - code */
    { .dataOffset = 0x0000BF53, .properties = 4, .width = 57, .height = 21 },    /* text_measurement@C1, 100, 1 - code */
    { .dataOffset = 0x0000C1A8, .properties = 4, .width = 65, .height = 21 },    /* text_measurement@C2, 100, 1 - code */
    { .dataOffset = 0x0000C450, .properties = 4, .width = 53, .height = 21 },    /* text_measurement@C3, 100, 1 - code */
    { .dataOffset = 0x0000C66D, .properties = 4, .width = 65, .height = 21 },    /* text_measurement@C4, 100, 1 - code */
    { .dataOffset = 0x0000C91F, .properties = 4, .width = 88, .height = 21 },    /* text_measurement@C5, 100, 1 - code */
    { .dataOffset = 0x0000CCA3, .properties = 4, .width = 85, .height = 21 },    /* text_measurement@C6, 100, 1 - code */
    { .dataOffset = 0x0000CFE4, .properties = 4, .width = 35, .height = 21 },    /* text_measurement@C7, 100, 1 - code */
    { .dataOffset = 0x0000D152, .properties = 4, .width = 35, .height = 21 },    /* text_measurement@C8, 100, 1 - code */
    { .dataOffset = 0x0000D2F0, .properties = 4, .width = 32, .height = 21 },    /* text_measurement@C9, 100, 1 - code */
    { .dataOffset = 0x0000D3E9, .properties = 4, .width = 104, .height = 23 },    /* text_pane_accent_color@C0, 100, 1 - code */
    { .dataOffset = 0x0000D7E5, .properties = 4, .width = 102, .height = 23 },    /* text_pane_accent_color@C1, 100, 1 - code */
    { .dataOffset = 0x0000DBDC, .properties = 4, .width = 148, .height = 23 },    /* text_pane_accent_color@C2, 100, 1 - code */
    { .dataOffset = 0x0000E13A, .properties = 4, .width = 136, .height = 23 },    /* text_pane_accent_color@C3, 100, 1 - code */
    { .dataOffset = 0x0000E691, .properties = 4, .width = 128, .height = 23 },    /* text_pane_accent_color@C4, 100, 1 - code */
    { .dataOffset = 0x0000EB4C, .properties = 4, .width = 137, .height = 23 },    /* text_pane_accent_color@C5, 100, 1 - code */
    { .dataOffset = 0x0000F09B, .properties = 4, .width = 143, .height = 23 },    /* text_pane_accent_color@C6, 100, 1 - code */
    { .dataOffset = 0x0000F5BF, .properties = 4, .width = 57, .height = 23 },    /* text_pane_accent_color@C7, 100, 1 - code */
    { .dataOffset = 0x0000F845, .properties = 4, .width = 119, .height = 23 },    /* text_pane_accent_color@C8, 100, 1 - code */
    { .dataOffset = 0x0000FBCB, .properties = 4, .width = 77, .height = 23 },    /* text_pane_accent_color@C9, 100, 1 - code */
    { .dataOffset = 0x0000FE3D, .properties = 4, .width = 127, .height = 23 },    /* text_pane_activate_alarm@C0, 100, 1 - code */
    { .dataOffset = 0x00010326, .properties = 4, .width = 137, .height = 23 },    /* text_pane_activate_alarm@C1, 100, 1 - code */
    { .dataOffset = 0x0001083E, .properties = 4, .width = 142, .height = 23 },    /* text_pane_activate_alarm@C2, 100, 1 - code */
    { .dataOffset = 0x00010DCB, .properties = 4, .width = 135, .height = 23 },    /* text_pane_activate_alarm@C3, 100, 1 - code */
    { .dataOffset = 0x00011305, .properties = 4, .width = 156, .height = 23 },    /* text_pane_activate_alarm@C4, 100, 1 - code */
    { .dataOffset = 0x000118FD, .properties = 4, .width = 146, .height = 23 },    /* text_pane_activate_alarm@C5, 100, 1 - code */
    { .dataOffset = 0x00011EEC, .properties = 4, .width = 263, .height = 23 },    /* text_pane_activate_alarm@C6, 100, 1 - code */
    { .dataOffset = 0x000128A2, .properties = 4, .width = 96, .height = 23 },    /* text_pane_activate_alarm@C7, 100, 1 - code */
    { .dataOffset = 0x00012D03, .properties = 4, .width = 207, .height = 23 },    /* text_pane_activate_alarm@C8, 100, 1 - code */
    { .dataOffset = 0x00013468, .properties = 4, .width = 234, .height = 23 },    /* text_pane_activate_alarm@C9, 100, 1 - code */
    { .dataOffset = 0x00013C4F, .properties = 4, .width = 100, .height = 23 },    /* text_pane_cursor_color@C0, 100, 1 - code */
    { .dataOffset = 0x00013FFC, .properties = 4, .width = 99, .height = 23 },    /* text_pane_cursor_color@C1, 100, 1 - code */
    { .dataOffset = 0x000143D5, .properties = 4, .width = 149, .height = 23 },    /* text_pane_cursor_color@C2, 100, 1 - code */
    { .dataOffset = 0x00014953, .properties = 4, .width = 154, .height = 23 },    /* text_pane_cursor_color@C3, 100, 1 - code */
    { .dataOffset = 0x00014F3E, .properties = 4, .width = 129, .height = 23 },    /* text_pane_cursor_color@C4, 100, 1 - code */
    { .dataOffset = 0x00015430, .properties = 4, .width = 149, .height = 23 },    /* text_pane_cursor_color@C5, 100, 1 - code */
    { .dataOffset = 0x000159CD, .properties = 4, .width = 115, .height = 23 },    /* text_pane_cursor_color@C6, 100, 1 - code */
    { .dataOffset = 0x00015E38, .properties = 4, .width = 79, .height = 23 },    /* text_pane_cursor_color@C7, 100, 1 - code */
    { .dataOffset = 0x00016200, .properties = 4, .width = 98, .height = 23 },    /* text_pane_cursor_color@C8, 100, 1 - code */
    { .dataOffset = 0x0001658F, .properties = 4, .width = 77, .height = 23 },    /* text_pane_cursor_color@C9, 100, 1 - code */
    { .dataOffset = 0x0001681B, .properties = 4, .width = 112, .height = 23 },    /* text_pane_intern_temp@C0, 100, 1 - code */
    { .dataOffset = 0x00016C86, .properties = 4, .width = 112, .height = 23 },    /* text_pane_intern_temp@C1, 100, 1 - code */
    { .dataOffset = 0x000170A5, .properties = 4, .width = 161, .height = 23 },    /* text_pane_intern_temp@C2, 100, 1 - code */
    { .dataOffset = 0x000176B3, .properties = 4, .width = 171, .height = 23 },    /* text_pane_intern_temp@C3, 100, 1 - code */
    { .dataOffset = 0x00017D1F, .properties = 4, .width = 172, .height = 23 },    /* text_pane_intern_temp@C4, 100, 1 - code */
    { .dataOffset = 0x000183AC, .properties = 4, .width = 172, .height = 23 },    /* text_pane_intern_temp@C5, 100, 1 - code */
    { .dataOffset = 0x00018A39, .properties = 4, .width = 221, .height = 23 },    /* text_pane_intern_temp@C6, 100, 1 - code */
    { .dataOffset = 0x00019294, .properties = 4, .width = 86, .height = 23 },    /* text_pane_intern_temp@C7, 100, 1 - code */
    { .dataOffset = 0x000196CC, .properties = 4, .width = 83, .height = 23 },    /* text_pane_intern_temp@C8, 100, 1 - code */
    { .dataOffset = 0x00019B02, .properties = 4, .width = 80, .height = 23 },    /* text_pane_intern_temp@C9, 100, 1 - code */
    { .dataOffset = 0x00019CD6, .properties = 4, .width = 102, .height = 23 },    /* text_pane_set_alarm_in@C0, 100, 1 - code */
    { .dataOffset = 0x0001A0C4, .properties = 4, .width = 72, .height = 23 },    /* text_pane_set_alarm_in@C1, 100, 1 - code */
    { .dataOffset = 0x0001A362, .properties = 4, .width = 112, .height = 23 },    /* text_pane_set_alarm_in@C2, 100, 1 - code */
    { .dataOffset = 0x0001A749, .properties = 4, .width = 156, .height = 23 },    /* text_pane_set_alarm_in@C3, 100, 1 - code */
    { .dataOffset = 0x0001AD25, .properties = 4, .width = 176, .height = 23 },    /* text_pane_set_alarm_in@C4, 100, 1 - code */
    { .dataOffset = 0x0001B433, .properties = 4, .width = 172, .height = 23 },    /* text_pane_set_alarm_in@C5, 100, 1 - code */
    { .dataOffset = 0x0001BB0A, .properties = 4, .width = 218, .height = 23 },    /* text_pane_set_alarm_in@C6, 100, 1 - code */
    { .dataOffset = 0x0001C33E, .properties = 4, .width = 190, .height = 23 },    /* text_pane_set_alarm_in@C7, 100, 1 - code */
    { .dataOffset = 0x0001CAEC, .properties = 4, .width = 123, .height = 23 },    /* text_pane_set_alarm_in@C8, 100, 1 - code */
    { .dataOffset = 0x0001CF0A, .properties = 4, .width = 81, .height = 23 },    /* text_pane_set_alarm_in@C9, 100, 1 - code */
    { .dataOffset = 0x0001D181, .properties = 4, .width = 37, .height = 23 },    /* text_pane_theme_dark@C0, 100, 1 - code */
    { .dataOffset = 0x0001D339, .properties = 4, .width = 57, .height = 23 },    /* text_pane_theme_dark@C1, 100, 1 - code */
    { .dataOffset = 0x0001D591, .properties = 4, .width = 54, .height = 23 },    /* text_pane_theme_dark@C2, 100, 1 - code */
    { .dataOffset = 0x0001D808, .properties = 4, .width = 64, .height = 23 },    /* text_pane_theme_dark@C3, 100, 1 - code */
    { .dataOffset = 0x0001DAB0, .properties = 4, .width = 57, .height = 23 },    /* text_pane_theme_dark@C4, 100, 1 - code */
    { .dataOffset = 0x0001DCDE, .properties = 4, .width = 57, .height = 23 },    /* text_pane_theme_dark@C5, 100, 1 - code */
    { .dataOffset = 0x0001DF0C, .properties = 4, .width = 69, .height = 23 },    /* text_pane_theme_dark@C6, 100, 1 - code */
    { .dataOffset = 0x0001E1AC, .properties = 4, .width = 39, .height = 23 },    /* text_pane_theme_dark@C7, 100, 1 - code */
    { .dataOffset = 0x0001E3CB, .properties = 4, .width = 36, .height = 23 },    /* text_pane_theme_dark@C8, 100, 1 - code */
    { .dataOffset = 0x0001E575, .properties = 4, .width = 34, .height = 23 },    /* text_pane_theme_dark@C9, 100, 1 - code */
    { .dataOffset = 0x0001E689, .properties = 4, .width = 40, .height = 23 },    /* text_pane_theme_light@C0, 100, 1 - code */
    { .dataOffset = 0x0001E874, .properties = 4, .width = 39, .height = 23 },    /* text_pane_theme_light@C1, 100, 1 - code */
    { .dataOffset = 0x0001EA26, .properties = 4, .width = 39, .height = 23 },    /* text_pane_theme_light@C2, 100, 1 - code */
    { .dataOffset = 0x0001EBD8, .properties = 4, .width = 65, .height = 23 },    /* text_pane_theme_light@C3, 100, 1 - code */
    { .dataOffset = 0x0001EE3E, .properties = 4, .width = 28, .height = 23 },    /* text_pane_theme_light@C4, 100, 1 - code */
    { .dataOffset = 0x0001EF20, .properties = 4, .width = 66, .height = 23 },    /* text_pane_theme_light@C5, 100, 1 - code */
    { .dataOffset = 0x0001F1EF, .properties = 4, .width = 40, .height = 23 },    /* text_pane_theme_light@C6, 100, 1 - code */
    { .dataOffset = 0x0001F350, .properties = 4, .width = 18, .height = 23 },    /* text_pane_theme_light@C7, 100, 1 - code */
    { .dataOffset = 0x0001F435, .properties = 4, .width = 18, .height = 23 },    /* text_pane_theme_light@C8, 100, 1 - code */
    { .dataOffset = 0x0001F51A, .properties = 4, .width = 17, .height = 23 },    /* text_pane_theme_light@C9, 100, 1 - code */
    { .dataOffset = 0x0001F5B4, .properties = 4, .width = 59, .height = 21 },    /* text_settings@C0, 100, 1 - code */
    { .dataOffset = 0x0001F810, .properties = 4, .width = 82, .height = 21 },    /* text_settings@C1, 100, 1 - code */
    { .dataOffset = 0x0001FB4E, .properties = 4, .width = 96, .height = 21 },    /* text_settings@C2, 100, 1 - code */
    { .dataOffset = 0x0001FEFA, .properties = 4, .width = 83, .height = 21 },    /* text_settings@C3, 100, 1 - code */
    { .dataOffset = 0x000201F8, .properties = 4, .width = 102, .height = 21 },    /* text_settings@C4, 100, 1 - code */
    { .dataOffset = 0x00020627, .properties = 4, .width = 93, .height = 21 },    /* text_settings@C5, 100, 1 - code */
    { .dataOffset = 0x000209A2, .properties = 4, .width = 87, .height = 21 },    /* text_settings@C6, 100, 1 - code */
    { .dataOffset = 0x00020CB7, .properties = 4, .width = 35, .height = 21 },    /* text_settings@C7, 100, 1 - code */
    { .dataOffset = 0x00020E05, .properties = 4, .width = 35, .height = 21 },    /* text_settings@C8, 100, 1 - code */
    { .dataOffset = 0x00020F57, .properties = 4, .width = 29, .height = 21 },    /* text_settings@C9, 100, 1 - code */
    { .dataOffset = 0x00021078, .properties = 4, .width = 41, .height = 21 },    /* text_setup@C0, 100, 1 - code */
    { .dataOffset = 0x00021249, .properties = 4, .width = 46, .height = 21 },    /* text_setup@C1, 100, 1 - code */
    { .dataOffset = 0x00021440, .properties = 4, .width = 80, .height = 21 },    /* text_setup@C2, 100, 1 - code */
    { .dataOffset = 0x0002171C, .properties = 4, .width = 89, .height = 21 },    /* text_setup@C3, 100, 1 - code */
    { .dataOffset = 0x00021A5A, .properties = 4, .width = 52, .height = 21 },    /* text_setup@C4, 100, 1 - code */
    { .dataOffset = 0x00021C81, .properties = 4, .width = 91, .height = 21 },    /* text_setup@C5, 100, 1 - code */
    { .dataOffset = 0x0002202B, .properties = 4, .width = 81, .height = 21 },    /* text_setup@C6, 100, 1 - code */
    { .dataOffset = 0x00022313, .properties = 4, .width = 35, .height = 21 },    /* text_setup@C7, 100, 1 - code */
    { .dataOffset = 0x00022461, .properties = 4, .width = 76, .height = 21 },    /* text_setup@C8, 100, 1 - code */
    { .dataOffset = 0x000226E3, .properties = 4, .width = 29, .height = 21 },    /* text_setup@C9, 100, 1 - code */
    { .dataOffset = 0x000227FB, .properties = 4, .width = 50, .height = 21 },    /* text_theme@C0, 100, 1 - code */
    { .dataOffset = 0x000229D2, .properties = 4, .width = 50, .height = 21 },    /* text_theme@C1, 100, 1 - code */
    { .dataOffset = 0x00022BB3, .properties = 4, .width = 50, .height = 21 },    /* text_theme@C2, 100, 1 - code */
    { .dataOffset = 0x00022D94, .properties = 4, .width = 50, .height = 21 },    /* text_theme@C3, 100, 1 - code */
    { .dataOffset = 0x00022F75, .properties = 4, .width = 41, .height = 21 },    /* text_theme@C4, 100, 1 - code */
    { .dataOffset = 0x000230E2, .properties = 4, .width = 41, .height = 21 },    /* text_theme@C5, 100, 1 - code */
    { .dataOffset = 0x0002324F, .properties = 4, .width = 39, .height = 21 },    /* text_theme@C6, 100, 1 - code */
    { .dataOffset = 0x000233B5, .properties = 4, .width = 34, .height = 21 },    /* text_theme@C7, 100, 1 - code */
    { .dataOffset = 0x000234EA, .properties = 4, .width = 41, .height = 21 },    /* text_theme@C8, 100, 1 - code */
    { .dataOffset = 0x0002358F, .properties = 4, .width = 30, .height = 21 },    /* text_theme@C9, 100, 1 - code */
    { .dataOffset = 0x0002369F, .properties = 4, .width = 36, .height = 21 },    /* text_time@C0, 100, 1 - code */
    { .dataOffset = 0x0002380A, .properties = 4, .width = 26, .height = 21 },    /* text_time@C1, 100, 1 - code */
    { .dataOffset = 0x0002394A, .properties = 4, .width = 27, .height = 21 },    /* text_time@C2, 100, 1 - code */
    { .dataOffset = 0x00023A54, .properties = 4, .width = 42, .height = 21 },    /* text_time@C3, 100, 1 - code */
    { .dataOffset = 0x00023BB2, .properties = 4, .width = 34, .height = 21 },    /* text_time@C4, 100, 1 - code */
    { .dataOffset = 0x00023CEB, .properties = 4, .width = 25, .height = 21 },    /* text_time@C5, 100, 1 - code */
    { .dataOffset = 0x00023DDB, .properties = 4, .width = 47, .height = 21 },    /* text_time@C6, 100, 1 - code */
    { .dataOffset = 0x00023FA3, .properties = 4, .width = 33, .height = 21 },    /* text_time@C7, 100, 1 - code */
    { .dataOffset = 0x00024107, .properties = 4, .width = 33, .height = 21 },    /* text_time@C8, 100, 1 - code */
    { .dataOffset = 0x0002427A, .properties = 4, .width = 31, .height = 21 },    /* text_time@C9, 100, 1 - code */
    { .dataOffset = 0x00024397, .properties = 4, .width = 76, .height = 29 },    /* title_alarm@C0, 100, 1 - code */
    { .dataOffset = 0x00024730, .properties = 4, .width = 76, .height = 29 },    /* title_alarm@C1, 100, 1 - code */
    { .dataOffset = 0x00024AC9, .properties = 4, .width = 76, .height = 29 },    /* title_alarm@C2, 100, 1 - code */
    { .dataOffset = 0x00024E62, .properties = 4, .width = 88, .height = 29 },    /* title_alarm@C3, 100, 1 - code */
    { .dataOffset = 0x00025266, .properties = 4, .width = 88, .height = 29 },    /* title_alarm@C4, 100, 1 - code */
    { .dataOffset = 0x0002566A, .properties = 4, .width = 93, .height = 29 },    /* title_alarm@C5, 100, 1 - code */
    { .dataOffset = 0x00025A83, .properties = 4, .width = 102, .height = 29 },    /* title_alarm@C6, 100, 1 - code */
    { .dataOffset = 0x00025E7E, .properties = 4, .width = 66, .height = 29 },    /* title_alarm@C7, 100, 1 - code */
    { .dataOffset = 0x000261CE, .properties = 4, .width = 65, .height = 29 },    /* title_alarm@C8, 100, 1 - code */
    { .dataOffset = 0x0002652C, .properties = 4, .width = 83, .height = 29 },    /* title_alarm@C9, 100, 1 - code */
    { .dataOffset = 0x0002684C, .properties = 4, .width = 105, .height = 29 },    /* title_brightness@C0, 100, 1 - code */
    { .dataOffset = 0x00026CE1, .properties = 4, .width = 106, .height = 29 },    /* title_brightness@C1, 100, 1 - code */
    { .dataOffset = 0x00027178, .properties = 4, .width = 92, .height = 29 },    /* title_brightness@C2, 100, 1 - code */
    { .dataOffset = 0x000275EE, .properties = 4, .width = 110, .height = 29 },    /* title_brightness@C3, 100, 1 - code */
    { .dataOffset = 0x00027A73, .properties = 4, .width = 49, .height = 29 },    /* title_brightness@C4, 100, 1 - code */
    { .dataOffset = 0x00027CF9, .properties = 4, .width = 110, .height = 29 },    /* title_brightness@C5, 100, 1 - code */
    { .dataOffset = 0x00028187, .properties = 4, .width = 86, .height = 29 },    /* title_brightness@C6, 100, 1 - code */
    { .dataOffset = 0x000284D6, .properties = 4, .width = 46, .height = 29 },    /* title_brightness@C7, 100, 1 - code */
    { .dataOffset = 0x000286E1, .properties = 4, .width = 57, .height = 29 },    /* title_brightness@C8, 100, 1 - code */
    { .dataOffset = 0x0002897B, .properties = 4, .width = 39, .height = 29 },    /* title_brightness@C9, 100, 1 - code */
    { .dataOffset = 0x00028B09, .properties = 4, .width = 63, .height = 29 },    /* title_colors@C0, 100, 1 - code */
    { .dataOffset = 0x00028D84, .properties = 4, .width = 74, .height = 29 },    /* title_colors@C1, 100, 1 - code */
    { .dataOffset = 0x000290A8, .properties = 4, .width = 67, .height = 29 },    /* title_colors@C2, 100, 1 - code */
    { .dataOffset = 0x00029344, .properties = 4, .width = 87, .height = 29 },    /* title_colors@C3, 100, 1 - code */
    { .dataOffset = 0x000296E0, .properties = 4, .width = 75, .height = 29 },    /* title_colors@C4, 100, 1 - code */
    { .dataOffset = 0x000299CD, .properties = 4, .width = 57, .height = 29 },    /* title_colors@C5, 100, 1 - code */
    { .dataOffset = 0x00029C28, .properties = 4, .width = 66, .height = 29 },    /* title_colors@C6, 100, 1 - code */
    { .dataOffset = 0x00029EF3, .properties = 4, .width = 47, .height = 29 },    /* title_colors@C7, 100, 1 - code */
    { .dataOffset = 0x0002A173, .properties = 4, .width = 22, .height = 29 },    /* title_colors@C8, 100, 1 - code */
    { .dataOffset = 0x0002A265, .properties = 4, .width = 42, .height = 29 },    /* title_colors@C9, 100, 1 - code */
    { .dataOffset = 0x0002A435, .properties = 4, .width = 45, .height = 29 },    /* title_date@C0, 100, 1 - code */
    { .dataOffset = 0x0002A5FF, .properties = 4, .width = 64, .height = 29 },    /* title_date@C1, 100, 1 - code */
    { .dataOffset = 0x0002A8A9, .properties = 4, .width = 64, .height = 29 },    /* title_date@C2, 100, 1 - code */
    { .dataOffset = 0x0002AB53, .properties = 4, .width = 45, .height = 29 },    /* title_date@C3, 100, 1 - code */
    { .dataOffset = 0x0002AD1D, .properties = 4, .width = 59, .height = 29 },    /* title_date@C4, 100, 1 - code */
    { .dataOffset = 0x0002AF6E, .properties = 4, .width = 72, .height = 29 },    /* title_date@C5, 100, 1 - code */
    { .dataOffset = 0x0002B256, .properties = 4, .width = 51, .height = 29 },    /* title_date@C6, 100, 1 - code */
    { .dataOffset = 0x0002B457, .properties = 4, .width = 43, .height = 29 },    /* title_date@C7, 100, 1 - code */
    { .dataOffset = 0x0002B67B, .properties = 4, .width = 43, .height = 29 },    /* title_date@C8, 100, 1 - code */
    { .dataOffset = 0x0002B867, .properties = 4, .width = 42, .height = 29 },    /* title_date@C9, 100, 1 - code */
    { .dataOffset = 0x0002BA2D, .properties = 4, .width = 37, .height = 29 },    /* title_info@C0, 100, 1 - code */
    { .dataOffset = 0x0002BBF5, .properties = 4, .width = 37, .height = 29 },    /* title_info@C1, 100, 1 - code */
    { .dataOffset = 0x0002BDBD, .properties = 4, .width = 37, .height = 29 },    /* title_info@C2, 100, 1 - code */
    { .dataOffset = 0x0002BF85, .properties = 4, .width = 37, .height = 29 },    /* title_info@C3, 100, 1 - code */
    { .dataOffset = 0x0002C14D, .properties = 4, .width = 119, .height = 29 },    /* title_info@C4, 100, 1 - code */
    { .dataOffset = 0x0002C676, .properties = 4, .width = 125, .height = 29 },    /* title_info@C5, 100, 1 - code */
    { .dataOffset = 0x0002CB98, .properties = 4, .width = 136, .height = 29 },    /* title_info@C6, 100, 1 - code */
    { .dataOffset = 0x0002D1C1, .properties = 4, .width = 48, .height = 29 },    /* title_info@C7, 100, 1 - code */
    { .dataOffset = 0x0002D3E1, .properties = 4, .width = 48, .height = 29 },    /* title_info@C8, 100, 1 - code */
    { .dataOffset = 0x0002D69C, .properties = 4, .width = 42, .height = 29 },    /* title_info@C9, 100, 1 - code */
    { .dataOffset = 0x0002D80E, .properties = 4, .width = 97, .height = 29 },    /* title_language@C0, 100, 1 - code */
    { .dataOffset = 0x0002DBDF, .properties = 4, .width = 42, .height = 29 },    /* title_language@C1, 100, 1 - code */
    { .dataOffset = 0x0002DD86, .properties = 4, .width = 82, .height = 29 },    /* title_language@C2, 100, 1 - code */
    { .dataOffset = 0x0002E0E8, .properties = 4, .width = 72, .height = 29 },    /* title_language@C3, 100, 1 - code */
    { .dataOffset = 0x0002E3A9, .properties = 4, .width = 67, .height = 29 },    /* title_language@C4, 100, 1 - code */
    { .dataOffset = 0x0002E6C1, .properties = 4, .width = 65, .height = 29 },    /* title_language@C5, 100, 1 - code */
    { .dataOffset = 0x0002E965, .properties = 4, .width = 55, .height = 29 },    /* title_language@C6, 100, 1 - code */
    { .dataOffset = 0x0002EB94, .properties = 4, .width = 47, .height = 29 },    /* title_language@C7, 100, 1 - code */
    { .dataOffset = 0x0002ED14, .properties = 4, .width = 47, .height = 29 },    /* title_language@C8, 100, 1 - code */
    { .dataOffset = 0x0002EED0, .properties = 4, .width = 39, .height = 29 },    /* title_language@C9, 100, 1 - code */
    { .dataOffset = 0x0002F0AC, .properties = 4, .width = 110, .height = 29 },    /* title_main_menu@C0, 100, 1 - code */
    { .dataOffset = 0x0002F53C, .properties = 4, .width = 117, .height = 29 },    /* title_main_menu@C1, 100, 1 - code */
    { .dataOffset = 0x0002FA12, .properties = 4, .width = 115, .height = 29 },    /* title_main_menu@C2, 100, 1 - code */
    { .dataOffset = 0x0002FEFB, .properties = 4, .width = 146, .height = 29 },    /* title_main_menu@C3, 100, 1 - code */
    { .dataOffset = 0x0003054E, .properties = 4, .width = 146, .height = 29 },    /* title_main_menu@C4, 100, 1 - code */
    { .dataOffset = 0x00030BB2, .properties = 4, .width = 159, .height = 29 },    /* title_main_menu@C5, 100, 1 - code */
    { .dataOffset = 0x0003129C, .properties = 4, .width = 152, .height = 29 },    /* title_main_menu@C6, 100, 1 - code */
    { .dataOffset = 0x00031813, .properties = 4, .width = 72, .height = 29 },    /* title_main_menu@C7, 100, 1 - code */
    { .dataOffset = 0x00031A9A, .properties = 4, .width = 123, .height = 29 },    /* title_main_menu@C8, 100, 1 - code */
    { .dataOffset = 0x00031D64, .properties = 4, .width = 92, .height = 29 },    /* title_main_menu@C9, 100, 1 - code */
    { .dataOffset = 0x000320E7, .properties = 4, .width = 138, .height = 29 },    /* title_measurement@C0, 100, 1 - code */
    { .dataOffset = 0x00032689, .properties = 4, .width = 79, .height = 29 },    /* title_measurement@C1, 100, 1 - code */
    { .dataOffset = 0x00032A54, .properties = 4, .width = 90, .height = 29 },    /* title_measurement@C2, 100, 1 - code */
    { .dataOffset = 0x00032E62, .properties = 4, .width = 74, .height = 29 },    /* title_measurement@C3, 100, 1 - code */
    { .dataOffset = 0x000331A9, .properties = 4, .width = 90, .height = 29 },    /* title_measurement@C4, 100, 1 - code */
    { .dataOffset = 0x000335FA, .properties = 4, .width = 122, .height = 29 },    /* title_measurement@C5, 100, 1 - code */
    { .dataOffset = 0x00033B33, .properties = 4, .width = 117, .height = 29 },    /* title_measurement@C6, 100, 1 - code */
    { .dataOffset = 0x0003401F, .properties = 4, .width = 48, .height = 29 },    /* title_measurement@C7, 100, 1 - code */
    { .dataOffset = 0x000342A1, .properties = 4, .width = 46, .height = 29 },    /* title_measurement@C8, 100, 1 - code */
    { .dataOffset = 0x00034546, .properties = 4, .width = 42, .height = 29 },    /* title_measurement@C9, 100, 1 - code */
    { .dataOffset = 0x00034685, .properties = 4, .width = 81, .height = 29 },    /* title_settings@C0, 100, 1 - code */
    { .dataOffset = 0x00034A01, .properties = 4, .width = 113, .height = 29 },    /* title_settings@C1, 100, 1 - code */
    { .dataOffset = 0x00034F58, .properties = 4, .width = 132, .height = 29 },    /* title_settings@C2, 100, 1 - code */
    { .dataOffset = 0x0003550B, .properties = 4, .width = 115, .height = 29 },    /* title_settings@C3, 100, 1 - code */
    { .dataOffset = 0x0003595F, .properties = 4, .width = 139, .height = 29 },    /* title_settings@C4, 100, 1 - code */
    { .dataOffset = 0x00035F41, .properties = 4, .width = 128, .height = 29 },    /* title_settings@C5, 100, 1 - code */
    { .dataOffset = 0x0003648F, .properties = 4, .width = 120, .height = 29 },    /* title_settings@C6, 100, 1 - code */
    { .dataOffset = 0x00036966, .properties = 4, .width = 46, .height = 29 },    /* title_settings@C7, 100, 1 - code */
    { .dataOffset = 0x00036BB6, .properties = 4, .width = 46, .height = 29 },    /* title_settings@C8, 100, 1 - code */
    { .dataOffset = 0x00036DED, .properties = 4, .width = 41, .height = 29 },    /* title_settings@C9, 100, 1 - code */
    { .dataOffset = 0x00036F98, .properties = 4, .width = 57, .height = 29 },    /* title_setup@C0, 100, 1 - code */
    { .dataOffset = 0x000371EF, .properties = 4, .width = 62, .height = 29 },    /* title_setup@C1, 100, 1 - code */
    { .dataOffset = 0x000374A0, .properties = 4, .width = 111, .height = 29 },    /* title_setup@C2, 100, 1 - code */
    { .dataOffset = 0x00037939, .properties = 4, .width = 121, .height = 29 },    /* title_setup@C3, 100, 1 - code */
    { .dataOffset = 0x00037DFD, .properties = 4, .width = 72, .height = 29 },    /* title_setup@C4, 100, 1 - code */
    { .dataOffset = 0x0003811D, .properties = 4, .width = 125, .height = 29 },    /* title_setup@C5, 100, 1 - code */
    { .dataOffset = 0x00038645, .properties = 4, .width = 112, .height = 29 },    /* title_setup@C6, 100, 1 - code */
    { .dataOffset = 0x00038AF3, .properties = 4, .width = 46, .height = 29 },    /* title_setup@C7, 100, 1 - code */
    { .dataOffset = 0x00038D43, .properties = 4, .width = 102, .height = 29 },    /* title_setup@C8, 100, 1 - code */
    { .dataOffset = 0x000390AD, .properties = 4, .width = 40, .height = 29 },    /* title_setup@C9, 100, 1 - code */
    { .dataOffset = 0x00039248, .properties = 4, .width = 69, .height = 29 },    /* title_theme@C0, 100, 1 - code */
    { .dataOffset = 0x000394FC, .properties = 4, .width = 69, .height = 29 },    /* title_theme@C1, 100, 1 - code */
    { .dataOffset = 0x000397AA, .properties = 4, .width = 69, .height = 29 },    /* title_theme@C2, 100, 1 - code */
    { .dataOffset = 0x00039A58, .properties = 4, .width = 69, .height = 29 },    /* title_theme@C3, 100, 1 - code */
    { .dataOffset = 0x00039D1D, .properties = 4, .width = 56, .height = 29 },    /* title_theme@C4, 100, 1 - code */
    { .dataOffset = 0x00039F13, .properties = 4, .width = 56, .height = 29 },    /* title_theme@C5, 100, 1 - code */
    { .dataOffset = 0x0003A109, .properties = 4, .width = 53, .height = 29 },    /* title_theme@C6, 100, 1 - code */
    { .dataOffset = 0x0003A2FC, .properties = 4, .width = 47, .height = 29 },    /* title_theme@C7, 100, 1 - code */
    { .dataOffset = 0x0003A4FC, .properties = 4, .width = 55, .height = 29 },    /* title_theme@C8, 100, 1 - code */
    { .dataOffset = 0x0003A5E9, .properties = 4, .width = 41, .height = 29 },    /* title_theme@C9, 100, 1 - code */
    { .dataOffset = 0x0003A7CD, .properties = 4, .width = 50, .height = 29 },    /* title_time@C0, 100, 1 - code */
    { .dataOffset = 0x0003A9B2, .properties = 4, .width = 35, .height = 29 },    /* title_time@C1, 100, 1 - code */
    { .dataOffset = 0x0003AB58, .properties = 4, .width = 38, .height = 29 },    /* title_time@C2, 100, 1 - code */
    { .dataOffset = 0x0003ACA5, .properties = 4, .width = 58, .height = 29 },    /* title_time@C3, 100, 1 - code */
    { .dataOffset = 0x0003AEFC, .properties = 4, .width = 47, .height = 29 },    /* title_time@C4, 100, 1 - code */
    { .dataOffset = 0x0003B0E2, .properties = 4, .width = 33, .height = 29 },    /* title_time@C5, 100, 1 - code */
    { .dataOffset = 0x0003B237, .properties = 4, .width = 65, .height = 29 },    /* title_time@C6, 100, 1 - code */
    { .dataOffset = 0x0003B527, .properties = 4, .width = 45, .height = 29 },    /* title_time@C7, 100, 1 - code */
    { .dataOffset = 0x0003B7B1, .properties = 4, .width = 46, .height = 29 },    /* title_time@C8, 100, 1 - code */
    { .dataOffset = 0x0003BA20, .properties = 4, .width = 42, .height = 29 },    /* title_time@C9, 100, 1 - code */
};

const uint8_t maxProperty[FS_MAX_FILE_PROPERTIES] =
{
    2, 24, 10, 
};

file_search_result_e fs_getFileInfo(
                            const file_key_e file_key,
                            const uint8_t *p_properties,
                            const uint8_t propertiesLength,
                            fs_file_info_s *p_out_file_info,
                            uint8_t *p_dataLocation)
{
    const int32_t fileIndex = (int32_t)file_key - 1;

    if ((fileIndex < 0) || (fileIndex > FS_FILES))
    {
        return FILE_SEARCH_OUT_OF_BOUNDS;
    }

    if (fileIndex >= 54)
    {
        *p_dataLocation = 1;
    }
    else
    {
        *p_dataLocation = 0;
    }

    if (0U == propertiesLength)
    {
        *p_out_file_info = fs_file_infos[fileIndex];

        return FILE_SEARCH_OK;
    }

    if (FS_MAX_FILE_PROPERTIES > propertiesLength)
    {
        return FILE_SEARCH_PROPERTY_LENGTH;
    }

    const fs_file_info_s *p_fileInfo = &fs_file_infos[fileIndex];
    
    if (p_fileInfo->properties == 0)
    {
        *p_out_file_info = fs_file_infos[fileIndex];

        return FILE_SEARCH_OK;
    }

    uint32_t keyOffset = 0;
    uint32_t multiplier = 1;

    for (int32_t i = (propertiesLength - 1); i >= -1; i--)
    {
        const uint16_t propertyBit = (p_fileInfo->properties & (0x01U << i));

        if (propertyBit > 0)
        {
            if (maxProperty[i] > p_properties[i])
            {
                keyOffset += (multiplier * p_properties[i]);
                multiplier *= maxProperty[i];
            }
            else
            {
                return FILE_SEARCH_PROPERTY_NOT_FOUND;
            }
        }
    }

    *p_out_file_info = fs_file_infos[fileIndex + keyOffset];

    if (FS_FILE_DUMMY == p_out_file_info->dataOffset)
    {
        return FILE_SEARCH_PROPERTY_NOT_FOUND;
    }

    return FILE_SEARCH_OK;
}

fs_compression_e fs_getCompression(fs_data_location_e location)
{
    switch (location)
    {
        case FS_DATA_LOCATION_0:
            return FS_DATA_LOCATION_0_COMPRESSION;
        case FS_DATA_LOCATION_1:
            return FS_DATA_LOCATION_1_COMPRESSION;
        default: return NONE;
    }
}

/*** end of file ***/
