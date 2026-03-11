#include "fs_file_search.h"

#define FS_FILE_INFO_SIZE 9
#define FS_FILE_DUMMY 0xFFFFFFFFU

const fs_file_info_s fs_file_infos[] =
{                                                                      /* filename, fileproperty, datalocation */
    { .dataOffset = 50, .properties = 2, .width = 32, .height = 27 },    /* IRL-Logo_@B000, 10, 0 - SD */
    { .dataOffset = 4028, .properties = 2, .width = 36, .height = 29 },    /* IRL-Logo_@B001, 10, 0 - SD */
    { .dataOffset = 8828, .properties = 2, .width = 39, .height = 32 },    /* IRL-Logo_@B002, 10, 0 - SD */
    { .dataOffset = 14210, .properties = 2, .width = 42, .height = 35 },    /* IRL-Logo_@B003, 10, 0 - SD */
    { .dataOffset = 20276, .properties = 2, .width = 46, .height = 37 },    /* IRL-Logo_@B004, 10, 0 - SD */
    { .dataOffset = 27158, .properties = 2, .width = 49, .height = 40 },    /* IRL-Logo_@B005, 10, 0 - SD */
    { .dataOffset = 34676, .properties = 2, .width = 52, .height = 43 },    /* IRL-Logo_@B006, 10, 0 - SD */
    { .dataOffset = 43220, .properties = 2, .width = 56, .height = 46 },    /* IRL-Logo_@B007, 10, 0 - SD */
    { .dataOffset = 52190, .properties = 2, .width = 59, .height = 48 },    /* IRL-Logo_@B008, 10, 0 - SD */
    { .dataOffset = 62276, .properties = 2, .width = 62, .height = 50 },    /* IRL-Logo_@B009, 10, 0 - SD */
    { .dataOffset = 72890, .properties = 2, .width = 65, .height = 54 },    /* IRL-Logo_@B010, 10, 0 - SD */
    { .dataOffset = 84800, .properties = 2, .width = 69, .height = 56 },    /* IRL-Logo_@B011, 10, 0 - SD */
    { .dataOffset = 97238, .properties = 2, .width = 72, .height = 59 },    /* IRL-Logo_@B012, 10, 0 - SD */
    { .dataOffset = 109982, .properties = 2, .width = 76, .height = 62 },    /* IRL-Logo_@B013, 10, 0 - SD */
    { .dataOffset = 123998, .properties = 2, .width = 79, .height = 64 },    /* IRL-Logo_@B014, 10, 0 - SD */
    { .dataOffset = 138452, .properties = 2, .width = 82, .height = 67 },    /* IRL-Logo_@B015, 10, 0 - SD */
    { .dataOffset = 153992, .properties = 2, .width = 86, .height = 69 },    /* IRL-Logo_@B016, 10, 0 - SD */
    { .dataOffset = 169976, .properties = 2, .width = 89, .height = 72 },    /* IRL-Logo_@B017, 10, 0 - SD */
    { .dataOffset = 186770, .properties = 2, .width = 92, .height = 75 },    /* IRL-Logo_@B018, 10, 0 - SD */
    { .dataOffset = 204542, .properties = 2, .width = 95, .height = 77 },    /* IRL-Logo_@B019, 10, 0 - SD */
    { .dataOffset = 222500, .properties = 2, .width = 100, .height = 80 },    /* IRL-Logo_@B020, 10, 0 - SD */
    { .dataOffset = 241928, .properties = 2, .width = 102, .height = 83 },    /* IRL-Logo_@B021, 10, 0 - SD */
    { .dataOffset = 261254, .properties = 2, .width = 105, .height = 85 },    /* IRL-Logo_@B022, 10, 0 - SD */
    { .dataOffset = 282482, .properties = 2, .width = 109, .height = 88 },    /* IRL-Logo_@B023, 10, 0 - SD */
    { .dataOffset = 302030, .properties = 1, .width = 30, .height = 30 },    /* NumInput_minus@A0, 1, 0 - SD */
    { .dataOffset = 303428, .properties = 1, .width = 30, .height = 30 },    /* NumInput_minus@A1, 1, 0 - SD */
    { .dataOffset = 304826, .properties = 1, .width = 30, .height = 30 },    /* NumInput_plus@A0, 1, 0 - SD */
    { .dataOffset = 306560, .properties = 1, .width = 30, .height = 30 },    /* NumInput_plus@A1, 1, 0 - SD */
    { .dataOffset = 308294, .properties = 1, .width = 22, .height = 31 },    /* Slider@A0, 1, 0 - SD */
    { .dataOffset = 308936, .properties = 1, .width = 22, .height = 31 },    /* Slider@A1, 1, 0 - SD */
    { .dataOffset = 309578, .properties = 0, .width = 128, .height = 128 },    /* IRL_Logo 128, 0, 0 - SD */
    { .dataOffset = 319658, .properties = 0, .width = 48, .height = 48 },    /* IRL_Logo_48, 0, 0 - SD */
    { .dataOffset = 323006, .properties = 1, .width = 480, .height = 236 },    /* Keyboard_lc@A0, 1, 0 - SD */
    { .dataOffset = 367436, .properties = 1, .width = 480, .height = 236 },    /* Keyboard_lc@A1, 1, 0 - SD */
    { .dataOffset = 411878, .properties = 1, .width = 480, .height = 236 },    /* Keyboard_num@A0, 1, 0 - SD */
    { .dataOffset = 451442, .properties = 1, .width = 480, .height = 236 },    /* Keyboard_num@A1, 1, 0 - SD */
    { .dataOffset = 491018, .properties = 1, .width = 480, .height = 84 },    /* Keyboard_textbox@A0, 1, 0 - SD */
    { .dataOffset = 492164, .properties = 1, .width = 480, .height = 84 },    /* Keyboard_textbox@A1, 1, 0 - SD */
    { .dataOffset = 493310, .properties = 1, .width = 480, .height = 236 },    /* Keyboard_uc@A0, 1, 0 - SD */
    { .dataOffset = 541772, .properties = 1, .width = 480, .height = 236 },    /* Keyboard_uc@A1, 1, 0 - SD */
    { .dataOffset = 0, .properties = 0, .width = 18, .height = 20 },    /* icon_Agenda, 0, 1 - code */
    { .dataOffset = 274, .properties = 0, .width = 35, .height = 18 },    /* icon_Arrow-Back, 0, 1 - code */
    { .dataOffset = 428, .properties = 0, .width = 13, .height = 4 },    /* icon_Arrow_down, 0, 1 - code */
    { .dataOffset = 498, .properties = 0, .width = 12, .height = 4 },    /* icon_Arrow_up, 0, 1 - code */
    { .dataOffset = 562, .properties = 0, .width = 16, .height = 18 },    /* icon_Bell, 0, 1 - code */
    { .dataOffset = 722, .properties = 0, .width = 30, .height = 25 },    /* icon_Brightness, 0, 1 - code */
    { .dataOffset = 1118, .properties = 0, .width = 22, .height = 22 },    /* icon_Brush, 0, 1 - code */
    { .dataOffset = 1360, .properties = 0, .width = 18, .height = 18 },    /* icon_Cancel, 0, 1 - code */
    { .dataOffset = 1664, .properties = 0, .width = 16, .height = 13 },    /* icon_Checkmark, 0, 1 - code */
    { .dataOffset = 1826, .properties = 0, .width = 26, .height = 21 },    /* icon_Checkmark_large, 0, 1 - code */
    { .dataOffset = 2106, .properties = 0, .width = 20, .height = 20 },    /* icon_Clock, 0, 1 - code */
    { .dataOffset = 2516, .properties = 0, .width = 22, .height = 22 },    /* icon_Focus, 0, 1 - code */
    { .dataOffset = 2696, .properties = 0, .width = 22, .height = 22 },    /* icon_Gear, 0, 1 - code */
    { .dataOffset = 3030, .properties = 0, .width = 20, .height = 20 },    /* icon_Global, 0, 1 - code */
    { .dataOffset = 3482, .properties = 0, .width = 21, .height = 21 },    /* icon_Info, 0, 1 - code */
    { .dataOffset = 3946, .properties = 0, .width = 23, .height = 16 },    /* icon_Keyboard, 0, 1 - code */
    { .dataOffset = 4292, .properties = 0, .width = 16, .height = 4 },    /* icon_minus, 0, 1 - code */
    { .dataOffset = 4316, .properties = 0, .width = 22, .height = 22 },    /* icon_Palette, 0, 1 - code */
    { .dataOffset = 4628, .properties = 0, .width = 16, .height = 16 },    /* icon_plus, 0, 1 - code */
    { .dataOffset = 4766, .properties = 0, .width = 18, .height = 18 },    /* icon_Radio-Button-Checked, 0, 1 - code */
    { .dataOffset = 5160, .properties = 0, .width = 18, .height = 18 },    /* icon_Radio-Button-UnChecked, 0, 1 - code */
    { .dataOffset = 5464, .properties = 0, .width = 22, .height = 22 },    /* icon_Sliders, 0, 1 - code */
    { .dataOffset = 5652, .properties = 0, .width = 25, .height = 18 },    /* icon_Wifi, 0, 1 - code */
    { .dataOffset = 5956, .properties = 4, .width = 92, .height = 21 },    /* text_accent_color@C0, 100, 1 - code */
    { .dataOffset = 7072, .properties = 4, .width = 91, .height = 21 },    /* text_accent_color@C1, 100, 1 - code */
    { .dataOffset = 8178, .properties = 4, .width = 131, .height = 21 },    /* text_accent_color@C2, 100, 1 - code */
    { .dataOffset = 9760, .properties = 4, .width = 167, .height = 21 },    /* text_accent_color@C3, 100, 1 - code */
    { .dataOffset = 11930, .properties = 4, .width = 115, .height = 21 },    /* text_accent_color@C4, 100, 1 - code */
    { .dataOffset = 13296, .properties = 4, .width = 122, .height = 21 },    /* text_accent_color@C5, 100, 1 - code */
    { .dataOffset = 14810, .properties = 4, .width = 127, .height = 21 },    /* text_accent_color@C6, 100, 1 - code */
    { .dataOffset = 16230, .properties = 4, .width = 50, .height = 21 },    /* text_accent_color@C7, 100, 1 - code */
    { .dataOffset = 17114, .properties = 4, .width = 106, .height = 21 },    /* text_accent_color@C8, 100, 1 - code */
    { .dataOffset = 18128, .properties = 4, .width = 68, .height = 21 },    /* text_accent_color@C9, 100, 1 - code */
    { .dataOffset = 18948, .properties = 4, .width = 55, .height = 21 },    /* text_alarm@C0, 100, 1 - code */
    { .dataOffset = 19726, .properties = 4, .width = 55, .height = 21 },    /* text_alarm@C1, 100, 1 - code */
    { .dataOffset = 20504, .properties = 4, .width = 55, .height = 21 },    /* text_alarm@C2, 100, 1 - code */
    { .dataOffset = 21282, .properties = 4, .width = 64, .height = 21 },    /* text_alarm@C3, 100, 1 - code */
    { .dataOffset = 22200, .properties = 4, .width = 64, .height = 21 },    /* text_alarm@C4, 100, 1 - code */
    { .dataOffset = 23100, .properties = 4, .width = 68, .height = 21 },    /* text_alarm@C5, 100, 1 - code */
    { .dataOffset = 24114, .properties = 4, .width = 74, .height = 21 },    /* text_alarm@C6, 100, 1 - code */
    { .dataOffset = 25090, .properties = 4, .width = 48, .height = 21 },    /* text_alarm@C7, 100, 1 - code */
    { .dataOffset = 25950, .properties = 4, .width = 47, .height = 21 },    /* text_alarm@C8, 100, 1 - code */
    { .dataOffset = 26798, .properties = 4, .width = 60, .height = 21 },    /* text_alarm@C9, 100, 1 - code */
    { .dataOffset = 27538, .properties = 4, .width = 76, .height = 21 },    /* text_brightness@C0, 100, 1 - code */
    { .dataOffset = 28620, .properties = 4, .width = 77, .height = 21 },    /* text_brightness@C1, 100, 1 - code */
    { .dataOffset = 29718, .properties = 4, .width = 67, .height = 21 },    /* text_brightness@C2, 100, 1 - code */
    { .dataOffset = 30730, .properties = 4, .width = 80, .height = 21 },    /* text_brightness@C3, 100, 1 - code */
    { .dataOffset = 31726, .properties = 4, .width = 35, .height = 21 },    /* text_brightness@C4, 100, 1 - code */
    { .dataOffset = 32306, .properties = 4, .width = 80, .height = 21 },    /* text_brightness@C5, 100, 1 - code */
    { .dataOffset = 33310, .properties = 4, .width = 63, .height = 21 },    /* text_brightness@C6, 100, 1 - code */
    { .dataOffset = 34060, .properties = 4, .width = 34, .height = 21 },    /* text_brightness@C7, 100, 1 - code */
    { .dataOffset = 34596, .properties = 4, .width = 41, .height = 21 },    /* text_brightness@C8, 100, 1 - code */
    { .dataOffset = 35230, .properties = 4, .width = 29, .height = 21 },    /* text_brightness@C9, 100, 1 - code */
    { .dataOffset = 35600, .properties = 4, .width = 47, .height = 21 },    /* text_colors@C0, 100, 1 - code */
    { .dataOffset = 36224, .properties = 4, .width = 53, .height = 21 },    /* text_colors@C1, 100, 1 - code */
    { .dataOffset = 36932, .properties = 4, .width = 48, .height = 21 },    /* text_colors@C2, 100, 1 - code */
    { .dataOffset = 37512, .properties = 4, .width = 64, .height = 21 },    /* text_colors@C3, 100, 1 - code */
    { .dataOffset = 38370, .properties = 4, .width = 55, .height = 21 },    /* text_colors@C4, 100, 1 - code */
    { .dataOffset = 39090, .properties = 4, .width = 42, .height = 21 },    /* text_colors@C5, 100, 1 - code */
    { .dataOffset = 39656, .properties = 4, .width = 48, .height = 21 },    /* text_colors@C6, 100, 1 - code */
    { .dataOffset = 40290, .properties = 4, .width = 35, .height = 21 },    /* text_colors@C7, 100, 1 - code */
    { .dataOffset = 40930, .properties = 4, .width = 17, .height = 21 },    /* text_colors@C8, 100, 1 - code */
    { .dataOffset = 41144, .properties = 4, .width = 32, .height = 21 },    /* text_colors@C9, 100, 1 - code */
    { .dataOffset = 41604, .properties = 4, .width = 32, .height = 21 },    /* text_date@C0, 100, 1 - code */
    { .dataOffset = 42040, .properties = 4, .width = 46, .height = 21 },    /* text_date@C1, 100, 1 - code */
    { .dataOffset = 42634, .properties = 4, .width = 46, .height = 21 },    /* text_date@C2, 100, 1 - code */
    { .dataOffset = 43228, .properties = 4, .width = 32, .height = 21 },    /* text_date@C3, 100, 1 - code */
    { .dataOffset = 43664, .properties = 4, .width = 42, .height = 21 },    /* text_date@C4, 100, 1 - code */
    { .dataOffset = 44142, .properties = 4, .width = 52, .height = 21 },    /* text_date@C5, 100, 1 - code */
    { .dataOffset = 44794, .properties = 4, .width = 37, .height = 21 },    /* text_date@C6, 100, 1 - code */
    { .dataOffset = 45238, .properties = 4, .width = 31, .height = 21 },    /* text_date@C7, 100, 1 - code */
    { .dataOffset = 45722, .properties = 4, .width = 32, .height = 21 },    /* text_date@C8, 100, 1 - code */
    { .dataOffset = 46130, .properties = 4, .width = 30, .height = 21 },    /* text_date@C9, 100, 1 - code */
    { .dataOffset = 46544, .properties = 0, .width = 74, .height = 29 },    /* text_footer_mcsgui, 0, 1 - code */
    { .dataOffset = 47686, .properties = 4, .width = 27, .height = 21 },    /* text_info@C0, 100, 1 - code */
    { .dataOffset = 48036, .properties = 4, .width = 27, .height = 21 },    /* text_info@C1, 100, 1 - code */
    { .dataOffset = 48386, .properties = 4, .width = 27, .height = 21 },    /* text_info@C2, 100, 1 - code */
    { .dataOffset = 48736, .properties = 4, .width = 27, .height = 21 },    /* text_info@C3, 100, 1 - code */
    { .dataOffset = 49086, .properties = 4, .width = 86, .height = 21 },    /* text_info@C4, 100, 1 - code */
    { .dataOffset = 50138, .properties = 4, .width = 90, .height = 21 },    /* text_info@C5, 100, 1 - code */
    { .dataOffset = 51198, .properties = 4, .width = 99, .height = 21 },    /* text_info@C6, 100, 1 - code */
    { .dataOffset = 52564, .properties = 4, .width = 35, .height = 21 },    /* text_info@C7, 100, 1 - code */
    { .dataOffset = 53062, .properties = 4, .width = 35, .height = 21 },    /* text_info@C8, 100, 1 - code */
    { .dataOffset = 53672, .properties = 4, .width = 31, .height = 21 },    /* text_info@C9, 100, 1 - code */
    { .dataOffset = 54042, .properties = 4, .width = 67, .height = 21 },    /* text_keyboard@C0, 100, 1 - code */
    { .dataOffset = 54952, .properties = 4, .width = 92, .height = 21 },    /* text_keyboard@C1, 100, 1 - code */
    { .dataOffset = 56106, .properties = 4, .width = 61, .height = 21 },    /* text_keyboard@C2, 100, 1 - code */
    { .dataOffset = 56884, .properties = 4, .width = 50, .height = 21 },    /* text_keyboard@C3, 100, 1 - code */
    { .dataOffset = 57562, .properties = 4, .width = 58, .height = 21 },    /* text_keyboard@C4, 100, 1 - code */
    { .dataOffset = 58310, .properties = 4, .width = 59, .height = 21 },    /* text_keyboard@C5, 100, 1 - code */
    { .dataOffset = 59044, .properties = 4, .width = 89, .height = 21 },    /* text_keyboard@C6, 100, 1 - code */
    { .dataOffset = 60224, .properties = 4, .width = 35, .height = 21 },    /* text_keyboard@C7, 100, 1 - code */
    { .dataOffset = 60934, .properties = 4, .width = 71, .height = 21 },    /* text_keyboard@C8, 100, 1 - code */
    { .dataOffset = 61540, .properties = 4, .width = 47, .height = 21 },    /* text_keyboard@C9, 100, 1 - code */
    { .dataOffset = 61930, .properties = 4, .width = 70, .height = 21 },    /* text_language@C0, 100, 1 - code */
    { .dataOffset = 62900, .properties = 4, .width = 31, .height = 21 },    /* text_language@C1, 100, 1 - code */
    { .dataOffset = 63312, .properties = 4, .width = 59, .height = 21 },    /* text_language@C2, 100, 1 - code */
    { .dataOffset = 64146, .properties = 4, .width = 52, .height = 21 },    /* text_language@C3, 100, 1 - code */
    { .dataOffset = 64846, .properties = 4, .width = 48, .height = 21 },    /* text_language@C4, 100, 1 - code */
    { .dataOffset = 65518, .properties = 4, .width = 47, .height = 21 },    /* text_language@C5, 100, 1 - code */
    { .dataOffset = 66188, .properties = 4, .width = 40, .height = 21 },    /* text_language@C6, 100, 1 - code */
    { .dataOffset = 66716, .properties = 4, .width = 35, .height = 21 },    /* text_language@C7, 100, 1 - code */
    { .dataOffset = 67136, .properties = 4, .width = 35, .height = 21 },    /* text_language@C8, 100, 1 - code */
    { .dataOffset = 67554, .properties = 4, .width = 29, .height = 21 },    /* text_language@C9, 100, 1 - code */
    { .dataOffset = 67994, .properties = 4, .width = 100, .height = 21 },    /* text_measurement@C0, 100, 1 - code */
    { .dataOffset = 69330, .properties = 4, .width = 57, .height = 21 },    /* text_measurement@C1, 100, 1 - code */
    { .dataOffset = 70128, .properties = 4, .width = 65, .height = 21 },    /* text_measurement@C2, 100, 1 - code */
    { .dataOffset = 71050, .properties = 4, .width = 53, .height = 21 },    /* text_measurement@C3, 100, 1 - code */
    { .dataOffset = 71780, .properties = 4, .width = 65, .height = 21 },    /* text_measurement@C4, 100, 1 - code */
    { .dataOffset = 72702, .properties = 4, .width = 88, .height = 21 },    /* text_measurement@C5, 100, 1 - code */
    { .dataOffset = 73908, .properties = 4, .width = 85, .height = 21 },    /* text_measurement@C6, 100, 1 - code */
    { .dataOffset = 75038, .properties = 4, .width = 35, .height = 21 },    /* text_measurement@C7, 100, 1 - code */
    { .dataOffset = 75608, .properties = 4, .width = 35, .height = 21 },    /* text_measurement@C8, 100, 1 - code */
    { .dataOffset = 76174, .properties = 4, .width = 32, .height = 21 },    /* text_measurement@C9, 100, 1 - code */
    { .dataOffset = 76552, .properties = 4, .width = 104, .height = 23 },    /* text_pane_accent_color@C0, 100, 1 - code */
    { .dataOffset = 77934, .properties = 4, .width = 102, .height = 23 },    /* text_pane_accent_color@C1, 100, 1 - code */
    { .dataOffset = 79294, .properties = 4, .width = 148, .height = 23 },    /* text_pane_accent_color@C2, 100, 1 - code */
    { .dataOffset = 81140, .properties = 4, .width = 187, .height = 23 },    /* text_pane_accent_color@C3, 100, 1 - code */
    { .dataOffset = 83706, .properties = 4, .width = 128, .height = 23 },    /* text_pane_accent_color@C4, 100, 1 - code */
    { .dataOffset = 85326, .properties = 4, .width = 137, .height = 23 },    /* text_pane_accent_color@C5, 100, 1 - code */
    { .dataOffset = 87162, .properties = 4, .width = 143, .height = 23 },    /* text_pane_accent_color@C6, 100, 1 - code */
    { .dataOffset = 88866, .properties = 4, .width = 57, .height = 23 },    /* text_pane_accent_color@C7, 100, 1 - code */
    { .dataOffset = 89796, .properties = 4, .width = 119, .height = 23 },    /* text_pane_accent_color@C8, 100, 1 - code */
    { .dataOffset = 91026, .properties = 4, .width = 77, .height = 23 },    /* text_pane_accent_color@C9, 100, 1 - code */
    { .dataOffset = 91888, .properties = 4, .width = 127, .height = 23 },    /* text_pane_activate_alarm@C0, 100, 1 - code */
    { .dataOffset = 93566, .properties = 4, .width = 137, .height = 23 },    /* text_pane_activate_alarm@C1, 100, 1 - code */
    { .dataOffset = 95288, .properties = 4, .width = 142, .height = 23 },    /* text_pane_activate_alarm@C2, 100, 1 - code */
    { .dataOffset = 97168, .properties = 4, .width = 135, .height = 23 },    /* text_pane_activate_alarm@C3, 100, 1 - code */
    { .dataOffset = 98960, .properties = 4, .width = 156, .height = 23 },    /* text_pane_activate_alarm@C4, 100, 1 - code */
    { .dataOffset = 101010, .properties = 4, .width = 146, .height = 23 },    /* text_pane_activate_alarm@C5, 100, 1 - code */
    { .dataOffset = 103040, .properties = 4, .width = 263, .height = 23 },    /* text_pane_activate_alarm@C6, 100, 1 - code */
    { .dataOffset = 106344, .properties = 4, .width = 96, .height = 23 },    /* text_pane_activate_alarm@C7, 100, 1 - code */
    { .dataOffset = 108006, .properties = 4, .width = 207, .height = 23 },    /* text_pane_activate_alarm@C8, 100, 1 - code */
    { .dataOffset = 110636, .properties = 4, .width = 234, .height = 23 },    /* text_pane_activate_alarm@C9, 100, 1 - code */
    { .dataOffset = 113334, .properties = 0, .width = 37, .height = 23 },    /* text_pane_chinese_sim, 0, 1 - code */
    { .dataOffset = 113794, .properties = 4, .width = 100, .height = 23 },    /* text_pane_cursor_color@C0, 100, 1 - code */
    { .dataOffset = 115048, .properties = 4, .width = 99, .height = 23 },    /* text_pane_cursor_color@C1, 100, 1 - code */
    { .dataOffset = 116356, .properties = 4, .width = 149, .height = 23 },    /* text_pane_cursor_color@C2, 100, 1 - code */
    { .dataOffset = 118278, .properties = 4, .width = 154, .height = 23 },    /* text_pane_cursor_color@C3, 100, 1 - code */
    { .dataOffset = 120290, .properties = 4, .width = 129, .height = 23 },    /* text_pane_cursor_color@C4, 100, 1 - code */
    { .dataOffset = 121980, .properties = 4, .width = 149, .height = 23 },    /* text_pane_cursor_color@C5, 100, 1 - code */
    { .dataOffset = 123906, .properties = 4, .width = 115, .height = 23 },    /* text_pane_cursor_color@C6, 100, 1 - code */
    { .dataOffset = 125436, .properties = 4, .width = 79, .height = 23 },    /* text_pane_cursor_color@C7, 100, 1 - code */
    { .dataOffset = 126826, .properties = 4, .width = 98, .height = 23 },    /* text_pane_cursor_color@C8, 100, 1 - code */
    { .dataOffset = 128062, .properties = 4, .width = 77, .height = 23 },    /* text_pane_cursor_color@C9, 100, 1 - code */
    { .dataOffset = 128954, .properties = 0, .width = 17, .height = 23 },    /* text_pane_deg_cel, 0, 1 - code */
    { .dataOffset = 129162, .properties = 0, .width = 16, .height = 23 },    /* text_pane_deg_far, 0, 1 - code */
    { .dataOffset = 129314, .properties = 0, .width = 93, .height = 23 },    /* text_pane_dutch, 0, 1 - code */
    { .dataOffset = 130756, .properties = 0, .width = 58, .height = 23 },    /* text_pane_english, 0, 1 - code */
    { .dataOffset = 131672, .properties = 0, .width = 69, .height = 23 },    /* text_pane_french, 0, 1 - code */
    { .dataOffset = 132658, .properties = 0, .width = 66, .height = 23 },    /* text_pane_german, 0, 1 - code */
    { .dataOffset = 133608, .properties = 4, .width = 112, .height = 23 },    /* text_pane_intern_temp@C0, 100, 1 - code */
    { .dataOffset = 135124, .properties = 4, .width = 112, .height = 23 },    /* text_pane_intern_temp@C1, 100, 1 - code */
    { .dataOffset = 136536, .properties = 4, .width = 161, .height = 23 },    /* text_pane_intern_temp@C2, 100, 1 - code */
    { .dataOffset = 138608, .properties = 4, .width = 171, .height = 23 },    /* text_pane_intern_temp@C3, 100, 1 - code */
    { .dataOffset = 140802, .properties = 4, .width = 172, .height = 23 },    /* text_pane_intern_temp@C4, 100, 1 - code */
    { .dataOffset = 143040, .properties = 4, .width = 172, .height = 23 },    /* text_pane_intern_temp@C5, 100, 1 - code */
    { .dataOffset = 145278, .properties = 4, .width = 221, .height = 23 },    /* text_pane_intern_temp@C6, 100, 1 - code */
    { .dataOffset = 148132, .properties = 4, .width = 86, .height = 23 },    /* text_pane_intern_temp@C7, 100, 1 - code */
    { .dataOffset = 149644, .properties = 4, .width = 83, .height = 23 },    /* text_pane_intern_temp@C8, 100, 1 - code */
    { .dataOffset = 151150, .properties = 4, .width = 80, .height = 23 },    /* text_pane_intern_temp@C9, 100, 1 - code */
    { .dataOffset = 151782, .properties = 0, .width = 59, .height = 23 },    /* text_pane_italian, 0, 1 - code */
    { .dataOffset = 152714, .properties = 0, .width = 57, .height = 23 },    /* text_pane_japanese, 0, 1 - code */
    { .dataOffset = 153534, .properties = 0, .width = 51, .height = 23 },    /* text_pane_korean, 0, 1 - code */
    { .dataOffset = 154108, .properties = 0, .width = 69, .height = 23 },    /* text_pane_russian, 0, 1 - code */
    { .dataOffset = 155106, .properties = 4, .width = 102, .height = 23 },    /* text_pane_set_alarm_in@C0, 100, 1 - code */
    { .dataOffset = 156458, .properties = 4, .width = 72, .height = 23 },    /* text_pane_set_alarm_in@C1, 100, 1 - code */
    { .dataOffset = 157326, .properties = 4, .width = 112, .height = 23 },    /* text_pane_set_alarm_in@C2, 100, 1 - code */
    { .dataOffset = 158648, .properties = 4, .width = 156, .height = 23 },    /* text_pane_set_alarm_in@C3, 100, 1 - code */
    { .dataOffset = 160668, .properties = 4, .width = 176, .height = 23 },    /* text_pane_set_alarm_in@C4, 100, 1 - code */
    { .dataOffset = 163080, .properties = 4, .width = 172, .height = 23 },    /* text_pane_set_alarm_in@C5, 100, 1 - code */
    { .dataOffset = 165436, .properties = 4, .width = 218, .height = 23 },    /* text_pane_set_alarm_in@C6, 100, 1 - code */
    { .dataOffset = 168236, .properties = 4, .width = 190, .height = 23 },    /* text_pane_set_alarm_in@C7, 100, 1 - code */
    { .dataOffset = 170960, .properties = 4, .width = 123, .height = 23 },    /* text_pane_set_alarm_in@C8, 100, 1 - code */
    { .dataOffset = 172432, .properties = 4, .width = 81, .height = 23 },    /* text_pane_set_alarm_in@C9, 100, 1 - code */
    { .dataOffset = 173282, .properties = 0, .width = 64, .height = 23 },    /* text_pane_spanish, 0, 1 - code */
    { .dataOffset = 174200, .properties = 4, .width = 37, .height = 23 },    /* text_pane_theme_dark@C0, 100, 1 - code */
    { .dataOffset = 174804, .properties = 4, .width = 57, .height = 23 },    /* text_pane_theme_dark@C1, 100, 1 - code */
    { .dataOffset = 175622, .properties = 4, .width = 54, .height = 23 },    /* text_pane_theme_dark@C2, 100, 1 - code */
    { .dataOffset = 176472, .properties = 4, .width = 64, .height = 23 },    /* text_pane_theme_dark@C3, 100, 1 - code */
    { .dataOffset = 177382, .properties = 4, .width = 57, .height = 23 },    /* text_pane_theme_dark@C4, 100, 1 - code */
    { .dataOffset = 178146, .properties = 4, .width = 57, .height = 23 },    /* text_pane_theme_dark@C5, 100, 1 - code */
    { .dataOffset = 178910, .properties = 4, .width = 69, .height = 23 },    /* text_pane_theme_dark@C6, 100, 1 - code */
    { .dataOffset = 179782, .properties = 4, .width = 39, .height = 23 },    /* text_pane_theme_dark@C7, 100, 1 - code */
    { .dataOffset = 180532, .properties = 4, .width = 36, .height = 23 },    /* text_pane_theme_dark@C8, 100, 1 - code */
    { .dataOffset = 181088, .properties = 4, .width = 34, .height = 23 },    /* text_pane_theme_dark@C9, 100, 1 - code */
    { .dataOffset = 181448, .properties = 4, .width = 40, .height = 23 },    /* text_pane_theme_light@C0, 100, 1 - code */
    { .dataOffset = 182094, .properties = 4, .width = 39, .height = 23 },    /* text_pane_theme_light@C1, 100, 1 - code */
    { .dataOffset = 182662, .properties = 4, .width = 39, .height = 23 },    /* text_pane_theme_light@C2, 100, 1 - code */
    { .dataOffset = 183230, .properties = 4, .width = 65, .height = 23 },    /* text_pane_theme_light@C3, 100, 1 - code */
    { .dataOffset = 184048, .properties = 4, .width = 28, .height = 23 },    /* text_pane_theme_light@C4, 100, 1 - code */
    { .dataOffset = 184348, .properties = 4, .width = 66, .height = 23 },    /* text_pane_theme_light@C5, 100, 1 - code */
    { .dataOffset = 185336, .properties = 4, .width = 40, .height = 23 },    /* text_pane_theme_light@C6, 100, 1 - code */
    { .dataOffset = 185810, .properties = 4, .width = 18, .height = 23 },    /* text_pane_theme_light@C7, 100, 1 - code */
    { .dataOffset = 186136, .properties = 4, .width = 18, .height = 23 },    /* text_pane_theme_light@C8, 100, 1 - code */
    { .dataOffset = 186462, .properties = 4, .width = 17, .height = 23 },    /* text_pane_theme_light@C9, 100, 1 - code */
    { .dataOffset = 186690, .properties = 0, .width = 43, .height = 23 },    /* text_pane_time_mm, 0, 1 - code */
    { .dataOffset = 187334, .properties = 4, .width = 59, .height = 21 },    /* text_settings@C0, 100, 1 - code */
    { .dataOffset = 188154, .properties = 4, .width = 82, .height = 21 },    /* text_settings@C1, 100, 1 - code */
    { .dataOffset = 189238, .properties = 4, .width = 96, .height = 21 },    /* text_settings@C2, 100, 1 - code */
    { .dataOffset = 190468, .properties = 4, .width = 83, .height = 21 },    /* text_settings@C3, 100, 1 - code */
    { .dataOffset = 191502, .properties = 4, .width = 102, .height = 21 },    /* text_settings@C4, 100, 1 - code */
    { .dataOffset = 192952, .properties = 4, .width = 93, .height = 21 },    /* text_settings@C5, 100, 1 - code */
    { .dataOffset = 194154, .properties = 4, .width = 87, .height = 21 },    /* text_settings@C6, 100, 1 - code */
    { .dataOffset = 195212, .properties = 4, .width = 35, .height = 21 },    /* text_settings@C7, 100, 1 - code */
    { .dataOffset = 195734, .properties = 4, .width = 35, .height = 21 },    /* text_settings@C8, 100, 1 - code */
    { .dataOffset = 196218, .properties = 4, .width = 29, .height = 21 },    /* text_settings@C9, 100, 1 - code */
    { .dataOffset = 196632, .properties = 4, .width = 41, .height = 21 },    /* text_setup@C0, 100, 1 - code */
    { .dataOffset = 197270, .properties = 4, .width = 46, .height = 21 },    /* text_setup@C1, 100, 1 - code */
    { .dataOffset = 197952, .properties = 4, .width = 80, .height = 21 },    /* text_setup@C2, 100, 1 - code */
    { .dataOffset = 198910, .properties = 4, .width = 89, .height = 21 },    /* text_setup@C3, 100, 1 - code */
    { .dataOffset = 200034, .properties = 4, .width = 52, .height = 21 },    /* text_setup@C4, 100, 1 - code */
    { .dataOffset = 200792, .properties = 4, .width = 91, .height = 21 },    /* text_setup@C5, 100, 1 - code */
    { .dataOffset = 202078, .properties = 4, .width = 81, .height = 21 },    /* text_setup@C6, 100, 1 - code */
    { .dataOffset = 203072, .properties = 4, .width = 35, .height = 21 },    /* text_setup@C7, 100, 1 - code */
    { .dataOffset = 203594, .properties = 4, .width = 76, .height = 21 },    /* text_setup@C8, 100, 1 - code */
    { .dataOffset = 204492, .properties = 4, .width = 29, .height = 21 },    /* text_setup@C9, 100, 1 - code */
    { .dataOffset = 204896, .properties = 4, .width = 50, .height = 21 },    /* text_theme@C0, 100, 1 - code */
    { .dataOffset = 205536, .properties = 4, .width = 50, .height = 21 },    /* text_theme@C1, 100, 1 - code */
    { .dataOffset = 206188, .properties = 4, .width = 50, .height = 21 },    /* text_theme@C2, 100, 1 - code */
    { .dataOffset = 206840, .properties = 4, .width = 50, .height = 21 },    /* text_theme@C3, 100, 1 - code */
    { .dataOffset = 207496, .properties = 4, .width = 41, .height = 21 },    /* text_theme@C4, 100, 1 - code */
    { .dataOffset = 207998, .properties = 4, .width = 41, .height = 21 },    /* text_theme@C5, 100, 1 - code */
    { .dataOffset = 208500, .properties = 4, .width = 39, .height = 21 },    /* text_theme@C6, 100, 1 - code */
    { .dataOffset = 208980, .properties = 4, .width = 34, .height = 21 },    /* text_theme@C7, 100, 1 - code */
    { .dataOffset = 209464, .properties = 4, .width = 41, .height = 21 },    /* text_theme@C8, 100, 1 - code */
    { .dataOffset = 209692, .properties = 4, .width = 30, .height = 21 },    /* text_theme@C9, 100, 1 - code */
    { .dataOffset = 210072, .properties = 4, .width = 36, .height = 21 },    /* text_time@C0, 100, 1 - code */
    { .dataOffset = 210556, .properties = 4, .width = 26, .height = 21 },    /* text_time@C1, 100, 1 - code */
    { .dataOffset = 210976, .properties = 4, .width = 27, .height = 21 },    /* text_time@C2, 100, 1 - code */
    { .dataOffset = 211330, .properties = 4, .width = 42, .height = 21 },    /* text_time@C3, 100, 1 - code */
    { .dataOffset = 211802, .properties = 4, .width = 34, .height = 21 },    /* text_time@C4, 100, 1 - code */
    { .dataOffset = 212222, .properties = 4, .width = 25, .height = 21 },    /* text_time@C5, 100, 1 - code */
    { .dataOffset = 212552, .properties = 4, .width = 47, .height = 21 },    /* text_time@C6, 100, 1 - code */
    { .dataOffset = 213164, .properties = 4, .width = 33, .height = 21 },    /* text_time@C7, 100, 1 - code */
    { .dataOffset = 213704, .properties = 4, .width = 33, .height = 21 },    /* text_time@C8, 100, 1 - code */
    { .dataOffset = 214254, .properties = 4, .width = 31, .height = 21 },    /* text_time@C9, 100, 1 - code */
    { .dataOffset = 214632, .properties = 4, .width = 76, .height = 29 },    /* title_alarm@C0, 100, 1 - code */
    { .dataOffset = 215878, .properties = 4, .width = 76, .height = 29 },    /* title_alarm@C1, 100, 1 - code */
    { .dataOffset = 217124, .properties = 4, .width = 76, .height = 29 },    /* title_alarm@C2, 100, 1 - code */
    { .dataOffset = 218370, .properties = 4, .width = 88, .height = 29 },    /* title_alarm@C3, 100, 1 - code */
    { .dataOffset = 219764, .properties = 4, .width = 88, .height = 29 },    /* title_alarm@C4, 100, 1 - code */
    { .dataOffset = 221154, .properties = 4, .width = 93, .height = 29 },    /* title_alarm@C5, 100, 1 - code */
    { .dataOffset = 222524, .properties = 4, .width = 102, .height = 29 },    /* title_alarm@C6, 100, 1 - code */
    { .dataOffset = 223896, .properties = 4, .width = 66, .height = 29 },    /* title_alarm@C7, 100, 1 - code */
    { .dataOffset = 225062, .properties = 4, .width = 65, .height = 29 },    /* title_alarm@C8, 100, 1 - code */
    { .dataOffset = 226234, .properties = 4, .width = 83, .height = 29 },    /* title_alarm@C9, 100, 1 - code */
    { .dataOffset = 227308, .properties = 4, .width = 105, .height = 29 },    /* title_brightness@C0, 100, 1 - code */
    { .dataOffset = 228898, .properties = 4, .width = 106, .height = 29 },    /* title_brightness@C1, 100, 1 - code */
    { .dataOffset = 230456, .properties = 4, .width = 92, .height = 29 },    /* title_brightness@C2, 100, 1 - code */
    { .dataOffset = 231972, .properties = 4, .width = 110, .height = 29 },    /* title_brightness@C3, 100, 1 - code */
    { .dataOffset = 233514, .properties = 4, .width = 49, .height = 29 },    /* title_brightness@C4, 100, 1 - code */
    { .dataOffset = 234388, .properties = 4, .width = 110, .height = 29 },    /* title_brightness@C5, 100, 1 - code */
    { .dataOffset = 235946, .properties = 4, .width = 86, .height = 29 },    /* title_brightness@C6, 100, 1 - code */
    { .dataOffset = 237080, .properties = 4, .width = 46, .height = 29 },    /* title_brightness@C7, 100, 1 - code */
    { .dataOffset = 237808, .properties = 4, .width = 57, .height = 29 },    /* title_brightness@C8, 100, 1 - code */
    { .dataOffset = 238690, .properties = 4, .width = 39, .height = 29 },    /* title_brightness@C9, 100, 1 - code */
    { .dataOffset = 239202, .properties = 4, .width = 63, .height = 29 },    /* title_colors@C0, 100, 1 - code */
    { .dataOffset = 240046, .properties = 4, .width = 74, .height = 29 },    /* title_colors@C1, 100, 1 - code */
    { .dataOffset = 241110, .properties = 4, .width = 67, .height = 29 },    /* title_colors@C2, 100, 1 - code */
    { .dataOffset = 242012, .properties = 4, .width = 87, .height = 29 },    /* title_colors@C3, 100, 1 - code */
    { .dataOffset = 243268, .properties = 4, .width = 75, .height = 29 },    /* title_colors@C4, 100, 1 - code */
    { .dataOffset = 244274, .properties = 4, .width = 57, .height = 29 },    /* title_colors@C5, 100, 1 - code */
    { .dataOffset = 245062, .properties = 4, .width = 66, .height = 29 },    /* title_colors@C6, 100, 1 - code */
    { .dataOffset = 246026, .properties = 4, .width = 47, .height = 29 },    /* title_colors@C7, 100, 1 - code */
    { .dataOffset = 246924, .properties = 4, .width = 22, .height = 29 },    /* title_colors@C8, 100, 1 - code */
    { .dataOffset = 247268, .properties = 4, .width = 42, .height = 29 },    /* title_colors@C9, 100, 1 - code */
    { .dataOffset = 247884, .properties = 4, .width = 45, .height = 29 },    /* title_date@C0, 100, 1 - code */
    { .dataOffset = 248490, .properties = 4, .width = 64, .height = 29 },    /* title_date@C1, 100, 1 - code */
    { .dataOffset = 249392, .properties = 4, .width = 64, .height = 29 },    /* title_date@C2, 100, 1 - code */
    { .dataOffset = 250294, .properties = 4, .width = 45, .height = 29 },    /* title_date@C3, 100, 1 - code */
    { .dataOffset = 250900, .properties = 4, .width = 59, .height = 29 },    /* title_date@C4, 100, 1 - code */
    { .dataOffset = 251704, .properties = 4, .width = 72, .height = 29 },    /* title_date@C5, 100, 1 - code */
    { .dataOffset = 252702, .properties = 4, .width = 51, .height = 29 },    /* title_date@C6, 100, 1 - code */
    { .dataOffset = 253398, .properties = 4, .width = 43, .height = 29 },    /* title_date@C7, 100, 1 - code */
    { .dataOffset = 254154, .properties = 4, .width = 43, .height = 29 },    /* title_date@C8, 100, 1 - code */
    { .dataOffset = 254832, .properties = 4, .width = 42, .height = 29 },    /* title_date@C9, 100, 1 - code */
    { .dataOffset = 255426, .properties = 4, .width = 37, .height = 29 },    /* title_info@C0, 100, 1 - code */
    { .dataOffset = 256046, .properties = 4, .width = 37, .height = 29 },    /* title_info@C1, 100, 1 - code */
    { .dataOffset = 256666, .properties = 4, .width = 37, .height = 29 },    /* title_info@C2, 100, 1 - code */
    { .dataOffset = 257286, .properties = 4, .width = 37, .height = 29 },    /* title_info@C3, 100, 1 - code */
    { .dataOffset = 257906, .properties = 4, .width = 119, .height = 29 },    /* title_info@C4, 100, 1 - code */
    { .dataOffset = 259694, .properties = 4, .width = 125, .height = 29 },    /* title_info@C5, 100, 1 - code */
    { .dataOffset = 261422, .properties = 4, .width = 136, .height = 29 },    /* title_info@C6, 100, 1 - code */
    { .dataOffset = 263516, .properties = 4, .width = 48, .height = 29 },    /* title_info@C7, 100, 1 - code */
    { .dataOffset = 264276, .properties = 4, .width = 48, .height = 29 },    /* title_info@C8, 100, 1 - code */
    { .dataOffset = 265224, .properties = 4, .width = 42, .height = 29 },    /* title_info@C9, 100, 1 - code */
    { .dataOffset = 265722, .properties = 4, .width = 97, .height = 29 },    /* title_language@C0, 100, 1 - code */
    { .dataOffset = 267024, .properties = 4, .width = 42, .height = 29 },    /* title_language@C1, 100, 1 - code */
    { .dataOffset = 267598, .properties = 4, .width = 82, .height = 29 },    /* title_language@C2, 100, 1 - code */
    { .dataOffset = 268780, .properties = 4, .width = 72, .height = 29 },    /* title_language@C3, 100, 1 - code */
    { .dataOffset = 269712, .properties = 4, .width = 67, .height = 29 },    /* title_language@C4, 100, 1 - code */
    { .dataOffset = 270794, .properties = 4, .width = 65, .height = 29 },    /* title_language@C5, 100, 1 - code */
    { .dataOffset = 271682, .properties = 4, .width = 55, .height = 29 },    /* title_language@C6, 100, 1 - code */
    { .dataOffset = 272422, .properties = 4, .width = 47, .height = 29 },    /* title_language@C7, 100, 1 - code */
    { .dataOffset = 272960, .properties = 4, .width = 47, .height = 29 },    /* title_language@C8, 100, 1 - code */
    { .dataOffset = 273576, .properties = 4, .width = 39, .height = 29 },    /* title_language@C9, 100, 1 - code */
    { .dataOffset = 274212, .properties = 4, .width = 110, .height = 29 },    /* title_main_menu@C0, 100, 1 - code */
    { .dataOffset = 275756, .properties = 4, .width = 117, .height = 29 },    /* title_main_menu@C1, 100, 1 - code */
    { .dataOffset = 277404, .properties = 4, .width = 115, .height = 29 },    /* title_main_menu@C2, 100, 1 - code */
    { .dataOffset = 279090, .properties = 4, .width = 146, .height = 29 },    /* title_main_menu@C3, 100, 1 - code */
    { .dataOffset = 281244, .properties = 4, .width = 146, .height = 29 },    /* title_main_menu@C4, 100, 1 - code */
    { .dataOffset = 283422, .properties = 4, .width = 159, .height = 29 },    /* title_main_menu@C5, 100, 1 - code */
    { .dataOffset = 285782, .properties = 4, .width = 152, .height = 29 },    /* title_main_menu@C6, 100, 1 - code */
    { .dataOffset = 287638, .properties = 4, .width = 72, .height = 29 },    /* title_main_menu@C7, 100, 1 - code */
    { .dataOffset = 288570, .properties = 4, .width = 123, .height = 29 },    /* title_main_menu@C8, 100, 1 - code */
    { .dataOffset = 289542, .properties = 4, .width = 92, .height = 29 },    /* title_main_menu@C9, 100, 1 - code */
    { .dataOffset = 290678, .properties = 4, .width = 138, .height = 29 },    /* title_measurement@C0, 100, 1 - code */
    { .dataOffset = 292600, .properties = 4, .width = 79, .height = 29 },    /* title_measurement@C1, 100, 1 - code */
    { .dataOffset = 293916, .properties = 4, .width = 90, .height = 29 },    /* title_measurement@C2, 100, 1 - code */
    { .dataOffset = 295336, .properties = 4, .width = 74, .height = 29 },    /* title_measurement@C3, 100, 1 - code */
    { .dataOffset = 296478, .properties = 4, .width = 90, .height = 29 },    /* title_measurement@C4, 100, 1 - code */
    { .dataOffset = 297968, .properties = 4, .width = 122, .height = 29 },    /* title_measurement@C5, 100, 1 - code */
    { .dataOffset = 299764, .properties = 4, .width = 117, .height = 29 },    /* title_measurement@C6, 100, 1 - code */
    { .dataOffset = 301438, .properties = 4, .width = 48, .height = 29 },    /* title_measurement@C7, 100, 1 - code */
    { .dataOffset = 302346, .properties = 4, .width = 46, .height = 29 },    /* title_measurement@C8, 100, 1 - code */
    { .dataOffset = 303262, .properties = 4, .width = 42, .height = 29 },    /* title_measurement@C9, 100, 1 - code */
    { .dataOffset = 303694, .properties = 4, .width = 81, .height = 29 },    /* title_settings@C0, 100, 1 - code */
    { .dataOffset = 304896, .properties = 4, .width = 113, .height = 29 },    /* title_settings@C1, 100, 1 - code */
    { .dataOffset = 306758, .properties = 4, .width = 132, .height = 29 },    /* title_settings@C2, 100, 1 - code */
    { .dataOffset = 308708, .properties = 4, .width = 115, .height = 29 },    /* title_settings@C3, 100, 1 - code */
    { .dataOffset = 310200, .properties = 4, .width = 139, .height = 29 },    /* title_settings@C4, 100, 1 - code */
    { .dataOffset = 312208, .properties = 4, .width = 128, .height = 29 },    /* title_settings@C5, 100, 1 - code */
    { .dataOffset = 314036, .properties = 4, .width = 120, .height = 29 },    /* title_settings@C6, 100, 1 - code */
    { .dataOffset = 315698, .properties = 4, .width = 46, .height = 29 },    /* title_settings@C7, 100, 1 - code */
    { .dataOffset = 316534, .properties = 4, .width = 46, .height = 29 },    /* title_settings@C8, 100, 1 - code */
    { .dataOffset = 317344, .properties = 4, .width = 41, .height = 29 },    /* title_settings@C9, 100, 1 - code */
    { .dataOffset = 317928, .properties = 4, .width = 57, .height = 29 },    /* title_setup@C0, 100, 1 - code */
    { .dataOffset = 318724, .properties = 4, .width = 62, .height = 29 },    /* title_setup@C1, 100, 1 - code */
    { .dataOffset = 319650, .properties = 4, .width = 111, .height = 29 },    /* title_setup@C2, 100, 1 - code */
    { .dataOffset = 321176, .properties = 4, .width = 121, .height = 29 },    /* title_setup@C3, 100, 1 - code */
    { .dataOffset = 322808, .properties = 4, .width = 72, .height = 29 },    /* title_setup@C4, 100, 1 - code */
    { .dataOffset = 323882, .properties = 4, .width = 125, .height = 29 },    /* title_setup@C5, 100, 1 - code */
    { .dataOffset = 325646, .properties = 4, .width = 112, .height = 29 },    /* title_setup@C6, 100, 1 - code */
    { .dataOffset = 327286, .properties = 4, .width = 46, .height = 29 },    /* title_setup@C7, 100, 1 - code */
    { .dataOffset = 328122, .properties = 4, .width = 102, .height = 29 },    /* title_setup@C8, 100, 1 - code */
    { .dataOffset = 329282, .properties = 4, .width = 40, .height = 29 },    /* title_setup@C9, 100, 1 - code */
    { .dataOffset = 329832, .properties = 4, .width = 69, .height = 29 },    /* title_theme@C0, 100, 1 - code */
    { .dataOffset = 330766, .properties = 4, .width = 69, .height = 29 },    /* title_theme@C1, 100, 1 - code */
    { .dataOffset = 331682, .properties = 4, .width = 69, .height = 29 },    /* title_theme@C2, 100, 1 - code */
    { .dataOffset = 332598, .properties = 4, .width = 69, .height = 29 },    /* title_theme@C3, 100, 1 - code */
    { .dataOffset = 333556, .properties = 4, .width = 56, .height = 29 },    /* title_theme@C4, 100, 1 - code */
    { .dataOffset = 334220, .properties = 4, .width = 56, .height = 29 },    /* title_theme@C5, 100, 1 - code */
    { .dataOffset = 334884, .properties = 4, .width = 53, .height = 29 },    /* title_theme@C6, 100, 1 - code */
    { .dataOffset = 335534, .properties = 4, .width = 47, .height = 29 },    /* title_theme@C7, 100, 1 - code */
    { .dataOffset = 336288, .properties = 4, .width = 55, .height = 29 },    /* title_theme@C8, 100, 1 - code */
    { .dataOffset = 336612, .properties = 4, .width = 41, .height = 29 },    /* title_theme@C9, 100, 1 - code */
    { .dataOffset = 337268, .properties = 4, .width = 50, .height = 29 },    /* title_time@C0, 100, 1 - code */
    { .dataOffset = 337914, .properties = 4, .width = 35, .height = 29 },    /* title_time@C1, 100, 1 - code */
    { .dataOffset = 338462, .properties = 4, .width = 38, .height = 29 },    /* title_time@C2, 100, 1 - code */
    { .dataOffset = 338882, .properties = 4, .width = 58, .height = 29 },    /* title_time@C3, 100, 1 - code */
    { .dataOffset = 339696, .properties = 4, .width = 47, .height = 29 },    /* title_time@C4, 100, 1 - code */
    { .dataOffset = 340344, .properties = 4, .width = 33, .height = 29 },    /* title_time@C5, 100, 1 - code */
    { .dataOffset = 340804, .properties = 4, .width = 65, .height = 29 },    /* title_time@C6, 100, 1 - code */
    { .dataOffset = 341836, .properties = 4, .width = 45, .height = 29 },    /* title_time@C7, 100, 1 - code */
    { .dataOffset = 342694, .properties = 4, .width = 46, .height = 29 },    /* title_time@C8, 100, 1 - code */
    { .dataOffset = 343542, .properties = 4, .width = 42, .height = 29 },    /* title_time@C9, 100, 1 - code */
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

    if (fileIndex >= 40)
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
