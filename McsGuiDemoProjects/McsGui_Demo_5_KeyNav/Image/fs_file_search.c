#include "fs_file_search.h"

#define FS_FILE_INFO_SIZE 9
#define FS_FILE_DUMMY 0xFFFFFFFFU

const fs_file_info_s fs_file_infos[] =
{
    { .dataOffset = 0, .properties = 0, .width = 18, .height = 20 },    /* icon_Agenda, 0 Optimized pixels: 137 */
    { .dataOffset = 274, .properties = 0, .width = 35, .height = 18 },    /* icon_Arrow-Back, 0 Optimized pixels: 77 */
    { .dataOffset = 428, .properties = 0, .width = 13, .height = 4 },    /* icon_Arrow_down, 0 Optimized pixels: 35 */
    { .dataOffset = 498, .properties = 0, .width = 12, .height = 4 },    /* icon_Arrow_up, 0 Optimized pixels: 32 */
    { .dataOffset = 562, .properties = 0, .width = 16, .height = 18 },    /* icon_Bell, 0 Optimized pixels: 80 */
    { .dataOffset = 722, .properties = 0, .width = 30, .height = 25 },    /* icon_Brightness, 0 Optimized pixels: 198 */
    { .dataOffset = 1118, .properties = 0, .width = 22, .height = 22 },    /* icon_Brush, 0 Optimized pixels: 121 */
    { .dataOffset = 1360, .properties = 0, .width = 18, .height = 18 },    /* icon_Cancel, 0 Optimized pixels: 152 */
    { .dataOffset = 1664, .properties = 0, .width = 16, .height = 13 },    /* icon_Checkmark, 0 Optimized pixels: 81 */
    { .dataOffset = 1826, .properties = 0, .width = 26, .height = 21 },    /* icon_Checkmark_large, 0 Optimized pixels: 140 */
    { .dataOffset = 2106, .properties = 0, .width = 20, .height = 20 },    /* icon_Clock, 0 Optimized pixels: 205 */
    { .dataOffset = 2516, .properties = 0, .width = 22, .height = 22 },    /* icon_Focus, 0 Optimized pixels: 90 */
    { .dataOffset = 2696, .properties = 0, .width = 22, .height = 22 },    /* icon_Gear, 0 Optimized pixels: 167 */
    { .dataOffset = 3030, .properties = 0, .width = 20, .height = 20 },    /* icon_Global, 0 Optimized pixels: 226 */
    { .dataOffset = 3482, .properties = 0, .width = 21, .height = 21 },    /* icon_Info, 0 Optimized pixels: 232 */
    { .dataOffset = 3946, .properties = 0, .width = 23, .height = 16 },    /* icon_Keyboard, 0 Optimized pixels: 173 */
    { .dataOffset = 4292, .properties = 0, .width = 16, .height = 4 },    /* icon_minus, 0 Optimized pixels: 12 */
    { .dataOffset = 4316, .properties = 0, .width = 22, .height = 22 },    /* icon_Palette, 0 Optimized pixels: 156 */
    { .dataOffset = 4628, .properties = 0, .width = 16, .height = 16 },    /* icon_plus, 0 Optimized pixels: 69 */
    { .dataOffset = 4766, .properties = 0, .width = 18, .height = 18 },    /* icon_Radio-Button-Checked, 0 Optimized pixels: 197 */
    { .dataOffset = 5160, .properties = 0, .width = 18, .height = 18 },    /* icon_Radio-Button-UnChecked, 0 Optimized pixels: 152 */
    { .dataOffset = 5464, .properties = 0, .width = 22, .height = 22 },    /* icon_Sliders, 0 Optimized pixels: 94 */
    { .dataOffset = 5652, .properties = 0, .width = 25, .height = 18 },    /* icon_Wifi, 0 Optimized pixels: 152 */
    { .dataOffset = 5956, .properties = 4, .width = 92, .height = 21 },    /* text_accent_color@C0, 100 Optimized pixels: 558 */
    { .dataOffset = 7072, .properties = 4, .width = 91, .height = 21 },    /* text_accent_color@C1, 100 Optimized pixels: 553 */
    { .dataOffset = 8178, .properties = 4, .width = 131, .height = 21 },    /* text_accent_color@C2, 100 Optimized pixels: 791 */
    { .dataOffset = 9760, .properties = 4, .width = 167, .height = 21 },    /* text_accent_color@C3, 100 Optimized pixels: 1085 */
    { .dataOffset = 11930, .properties = 4, .width = 115, .height = 21 },    /* text_accent_color@C4, 100 Optimized pixels: 683 */
    { .dataOffset = 13296, .properties = 4, .width = 122, .height = 21 },    /* text_accent_color@C5, 100 Optimized pixels: 757 */
    { .dataOffset = 14810, .properties = 4, .width = 127, .height = 21 },    /* text_accent_color@C6, 100 Optimized pixels: 710 */
    { .dataOffset = 16230, .properties = 4, .width = 50, .height = 21 },    /* text_accent_color@C7, 100 Optimized pixels: 442 */
    { .dataOffset = 17114, .properties = 4, .width = 106, .height = 21 },    /* text_accent_color@C8, 100 Optimized pixels: 507 */
    { .dataOffset = 18128, .properties = 4, .width = 68, .height = 21 },    /* text_accent_color@C9, 100 Optimized pixels: 410 */
    { .dataOffset = 18948, .properties = 4, .width = 55, .height = 21 },    /* text_alarm@C0, 100 Optimized pixels: 389 */
    { .dataOffset = 19726, .properties = 4, .width = 55, .height = 21 },    /* text_alarm@C1, 100 Optimized pixels: 389 */
    { .dataOffset = 20504, .properties = 4, .width = 55, .height = 21 },    /* text_alarm@C2, 100 Optimized pixels: 389 */
    { .dataOffset = 21282, .properties = 4, .width = 64, .height = 21 },    /* text_alarm@C3, 100 Optimized pixels: 459 */
    { .dataOffset = 22200, .properties = 4, .width = 64, .height = 21 },    /* text_alarm@C4, 100 Optimized pixels: 450 */
    { .dataOffset = 23100, .properties = 4, .width = 68, .height = 21 },    /* text_alarm@C5, 100 Optimized pixels: 507 */
    { .dataOffset = 24114, .properties = 4, .width = 74, .height = 21 },    /* text_alarm@C6, 100 Optimized pixels: 488 */
    { .dataOffset = 25090, .properties = 4, .width = 48, .height = 21 },    /* text_alarm@C7, 100 Optimized pixels: 430 */
    { .dataOffset = 25950, .properties = 4, .width = 47, .height = 21 },    /* text_alarm@C8, 100 Optimized pixels: 424 */
    { .dataOffset = 26798, .properties = 4, .width = 60, .height = 21 },    /* text_alarm@C9, 100 Optimized pixels: 370 */
    { .dataOffset = 27538, .properties = 4, .width = 76, .height = 21 },    /* text_brightness@C0, 100 Optimized pixels: 541 */
    { .dataOffset = 28620, .properties = 4, .width = 77, .height = 21 },    /* text_brightness@C1, 100 Optimized pixels: 549 */
    { .dataOffset = 29718, .properties = 4, .width = 67, .height = 21 },    /* text_brightness@C2, 100 Optimized pixels: 506 */
    { .dataOffset = 30730, .properties = 4, .width = 80, .height = 21 },    /* text_brightness@C3, 100 Optimized pixels: 498 */
    { .dataOffset = 31726, .properties = 4, .width = 35, .height = 21 },    /* text_brightness@C4, 100 Optimized pixels: 290 */
    { .dataOffset = 32306, .properties = 4, .width = 80, .height = 21 },    /* text_brightness@C5, 100 Optimized pixels: 502 */
    { .dataOffset = 33310, .properties = 4, .width = 63, .height = 21 },    /* text_brightness@C6, 100 Optimized pixels: 375 */
    { .dataOffset = 34060, .properties = 4, .width = 34, .height = 21 },    /* text_brightness@C7, 100 Optimized pixels: 268 */
    { .dataOffset = 34596, .properties = 4, .width = 41, .height = 21 },    /* text_brightness@C8, 100 Optimized pixels: 317 */
    { .dataOffset = 35230, .properties = 4, .width = 29, .height = 21 },    /* text_brightness@C9, 100 Optimized pixels: 185 */
    { .dataOffset = 35600, .properties = 4, .width = 47, .height = 21 },    /* text_colors@C0, 100 Optimized pixels: 312 */
    { .dataOffset = 36224, .properties = 4, .width = 53, .height = 21 },    /* text_colors@C1, 100 Optimized pixels: 354 */
    { .dataOffset = 36932, .properties = 4, .width = 48, .height = 21 },    /* text_colors@C2, 100 Optimized pixels: 290 */
    { .dataOffset = 37512, .properties = 4, .width = 64, .height = 21 },    /* text_colors@C3, 100 Optimized pixels: 429 */
    { .dataOffset = 38370, .properties = 4, .width = 55, .height = 21 },    /* text_colors@C4, 100 Optimized pixels: 360 */
    { .dataOffset = 39090, .properties = 4, .width = 42, .height = 21 },    /* text_colors@C5, 100 Optimized pixels: 283 */
    { .dataOffset = 39656, .properties = 4, .width = 48, .height = 21 },    /* text_colors@C6, 100 Optimized pixels: 317 */
    { .dataOffset = 40290, .properties = 4, .width = 35, .height = 21 },    /* text_colors@C7, 100 Optimized pixels: 320 */
    { .dataOffset = 40930, .properties = 4, .width = 17, .height = 21 },    /* text_colors@C8, 100 Optimized pixels: 107 */
    { .dataOffset = 41144, .properties = 4, .width = 32, .height = 21 },    /* text_colors@C9, 100 Optimized pixels: 230 */
    { .dataOffset = 41604, .properties = 4, .width = 32, .height = 21 },    /* text_date@C0, 100 Optimized pixels: 218 */
    { .dataOffset = 42040, .properties = 4, .width = 46, .height = 21 },    /* text_date@C1, 100 Optimized pixels: 297 */
    { .dataOffset = 42634, .properties = 4, .width = 46, .height = 21 },    /* text_date@C2, 100 Optimized pixels: 297 */
    { .dataOffset = 43228, .properties = 4, .width = 32, .height = 21 },    /* text_date@C3, 100 Optimized pixels: 218 */
    { .dataOffset = 43664, .properties = 4, .width = 42, .height = 21 },    /* text_date@C4, 100 Optimized pixels: 239 */
    { .dataOffset = 44142, .properties = 4, .width = 52, .height = 21 },    /* text_date@C5, 100 Optimized pixels: 326 */
    { .dataOffset = 44794, .properties = 4, .width = 37, .height = 21 },    /* text_date@C6, 100 Optimized pixels: 222 */
    { .dataOffset = 45238, .properties = 4, .width = 31, .height = 21 },    /* text_date@C7, 100 Optimized pixels: 242 */
    { .dataOffset = 45722, .properties = 4, .width = 32, .height = 21 },    /* text_date@C8, 100 Optimized pixels: 204 */
    { .dataOffset = 46130, .properties = 4, .width = 30, .height = 21 },    /* text_date@C9, 100 Optimized pixels: 207 */
    { .dataOffset = 46544, .properties = 0, .width = 74, .height = 29 },    /* text_footer_mcsgui, 0 Optimized pixels: 571 */
    { .dataOffset = 47686, .properties = 4, .width = 27, .height = 21 },    /* text_info@C0, 100 Optimized pixels: 175 */
    { .dataOffset = 48036, .properties = 4, .width = 27, .height = 21 },    /* text_info@C1, 100 Optimized pixels: 175 */
    { .dataOffset = 48386, .properties = 4, .width = 27, .height = 21 },    /* text_info@C2, 100 Optimized pixels: 175 */
    { .dataOffset = 48736, .properties = 4, .width = 27, .height = 21 },    /* text_info@C3, 100 Optimized pixels: 175 */
    { .dataOffset = 49086, .properties = 4, .width = 86, .height = 21 },    /* text_info@C4, 100 Optimized pixels: 526 */
    { .dataOffset = 50138, .properties = 4, .width = 90, .height = 21 },    /* text_info@C5, 100 Optimized pixels: 530 */
    { .dataOffset = 51198, .properties = 4, .width = 99, .height = 21 },    /* text_info@C6, 100 Optimized pixels: 683 */
    { .dataOffset = 52564, .properties = 4, .width = 35, .height = 21 },    /* text_info@C7, 100 Optimized pixels: 249 */
    { .dataOffset = 53062, .properties = 4, .width = 35, .height = 21 },    /* text_info@C8, 100 Optimized pixels: 305 */
    { .dataOffset = 53672, .properties = 4, .width = 31, .height = 21 },    /* text_info@C9, 100 Optimized pixels: 185 */
    { .dataOffset = 54042, .properties = 4, .width = 67, .height = 21 },    /* text_keyboard@C0, 100 Optimized pixels: 455 */
    { .dataOffset = 54952, .properties = 4, .width = 92, .height = 21 },    /* text_keyboard@C1, 100 Optimized pixels: 577 */
    { .dataOffset = 56106, .properties = 4, .width = 61, .height = 21 },    /* text_keyboard@C2, 100 Optimized pixels: 389 */
    { .dataOffset = 56884, .properties = 4, .width = 50, .height = 21 },    /* text_keyboard@C3, 100 Optimized pixels: 339 */
    { .dataOffset = 57562, .properties = 4, .width = 58, .height = 21 },    /* text_keyboard@C4, 100 Optimized pixels: 374 */
    { .dataOffset = 58310, .properties = 4, .width = 59, .height = 21 },    /* text_keyboard@C5, 100 Optimized pixels: 367 */
    { .dataOffset = 59044, .properties = 4, .width = 89, .height = 21 },    /* text_keyboard@C6, 100 Optimized pixels: 590 */
    { .dataOffset = 60224, .properties = 4, .width = 35, .height = 21 },    /* text_keyboard@C7, 100 Optimized pixels: 355 */
    { .dataOffset = 60934, .properties = 4, .width = 71, .height = 21 },    /* text_keyboard@C8, 100 Optimized pixels: 303 */
    { .dataOffset = 61540, .properties = 4, .width = 47, .height = 21 },    /* text_keyboard@C9, 100 Optimized pixels: 195 */
    { .dataOffset = 61930, .properties = 4, .width = 70, .height = 21 },    /* text_language@C0, 100 Optimized pixels: 485 */
    { .dataOffset = 62900, .properties = 4, .width = 31, .height = 21 },    /* text_language@C1, 100 Optimized pixels: 206 */
    { .dataOffset = 63312, .properties = 4, .width = 59, .height = 21 },    /* text_language@C2, 100 Optimized pixels: 417 */
    { .dataOffset = 64146, .properties = 4, .width = 52, .height = 21 },    /* text_language@C3, 100 Optimized pixels: 350 */
    { .dataOffset = 64846, .properties = 4, .width = 48, .height = 21 },    /* text_language@C4, 100 Optimized pixels: 336 */
    { .dataOffset = 65518, .properties = 4, .width = 47, .height = 21 },    /* text_language@C5, 100 Optimized pixels: 335 */
    { .dataOffset = 66188, .properties = 4, .width = 40, .height = 21 },    /* text_language@C6, 100 Optimized pixels: 264 */
    { .dataOffset = 66716, .properties = 4, .width = 35, .height = 21 },    /* text_language@C7, 100 Optimized pixels: 210 */
    { .dataOffset = 67136, .properties = 4, .width = 35, .height = 21 },    /* text_language@C8, 100 Optimized pixels: 209 */
    { .dataOffset = 67554, .properties = 4, .width = 29, .height = 21 },    /* text_language@C9, 100 Optimized pixels: 220 */
    { .dataOffset = 67994, .properties = 4, .width = 100, .height = 21 },    /* text_measurement@C0, 100 Optimized pixels: 668 */
    { .dataOffset = 69330, .properties = 4, .width = 57, .height = 21 },    /* text_measurement@C1, 100 Optimized pixels: 399 */
    { .dataOffset = 70128, .properties = 4, .width = 65, .height = 21 },    /* text_measurement@C2, 100 Optimized pixels: 461 */
    { .dataOffset = 71050, .properties = 4, .width = 53, .height = 21 },    /* text_measurement@C3, 100 Optimized pixels: 365 */
    { .dataOffset = 71780, .properties = 4, .width = 65, .height = 21 },    /* text_measurement@C4, 100 Optimized pixels: 461 */
    { .dataOffset = 72702, .properties = 4, .width = 88, .height = 21 },    /* text_measurement@C5, 100 Optimized pixels: 603 */
    { .dataOffset = 73908, .properties = 4, .width = 85, .height = 21 },    /* text_measurement@C6, 100 Optimized pixels: 565 */
    { .dataOffset = 75038, .properties = 4, .width = 35, .height = 21 },    /* text_measurement@C7, 100 Optimized pixels: 285 */
    { .dataOffset = 75608, .properties = 4, .width = 35, .height = 21 },    /* text_measurement@C8, 100 Optimized pixels: 283 */
    { .dataOffset = 76174, .properties = 4, .width = 32, .height = 21 },    /* text_measurement@C9, 100 Optimized pixels: 189 */
    { .dataOffset = 76552, .properties = 4, .width = 104, .height = 23 },    /* text_pane_accent_color@C0, 100 Optimized pixels: 691 */
    { .dataOffset = 77934, .properties = 4, .width = 102, .height = 23 },    /* text_pane_accent_color@C1, 100 Optimized pixels: 680 */
    { .dataOffset = 79294, .properties = 4, .width = 148, .height = 23 },    /* text_pane_accent_color@C2, 100 Optimized pixels: 923 */
    { .dataOffset = 81140, .properties = 4, .width = 187, .height = 23 },    /* text_pane_accent_color@C3, 100 Optimized pixels: 1283 */
    { .dataOffset = 83706, .properties = 4, .width = 128, .height = 23 },    /* text_pane_accent_color@C4, 100 Optimized pixels: 810 */
    { .dataOffset = 85326, .properties = 4, .width = 137, .height = 23 },    /* text_pane_accent_color@C5, 100 Optimized pixels: 918 */
    { .dataOffset = 87162, .properties = 4, .width = 143, .height = 23 },    /* text_pane_accent_color@C6, 100 Optimized pixels: 852 */
    { .dataOffset = 88866, .properties = 4, .width = 57, .height = 23 },    /* text_pane_accent_color@C7, 100 Optimized pixels: 465 */
    { .dataOffset = 89796, .properties = 4, .width = 119, .height = 23 },    /* text_pane_accent_color@C8, 100 Optimized pixels: 615 */
    { .dataOffset = 91026, .properties = 4, .width = 77, .height = 23 },    /* text_pane_accent_color@C9, 100 Optimized pixels: 431 */
    { .dataOffset = 91888, .properties = 4, .width = 127, .height = 23 },    /* text_pane_activate_alarm@C0, 100 Optimized pixels: 839 */
    { .dataOffset = 93566, .properties = 4, .width = 137, .height = 23 },    /* text_pane_activate_alarm@C1, 100 Optimized pixels: 861 */
    { .dataOffset = 95288, .properties = 4, .width = 142, .height = 23 },    /* text_pane_activate_alarm@C2, 100 Optimized pixels: 940 */
    { .dataOffset = 97168, .properties = 4, .width = 135, .height = 23 },    /* text_pane_activate_alarm@C3, 100 Optimized pixels: 896 */
    { .dataOffset = 98960, .properties = 4, .width = 156, .height = 23 },    /* text_pane_activate_alarm@C4, 100 Optimized pixels: 1025 */
    { .dataOffset = 101010, .properties = 4, .width = 146, .height = 23 },    /* text_pane_activate_alarm@C5, 100 Optimized pixels: 1015 */
    { .dataOffset = 103040, .properties = 4, .width = 263, .height = 23 },    /* text_pane_activate_alarm@C6, 100 Optimized pixels: 1652 */
    { .dataOffset = 106344, .properties = 4, .width = 96, .height = 23 },    /* text_pane_activate_alarm@C7, 100 Optimized pixels: 831 */
    { .dataOffset = 108006, .properties = 4, .width = 207, .height = 23 },    /* text_pane_activate_alarm@C8, 100 Optimized pixels: 1315 */
    { .dataOffset = 110636, .properties = 4, .width = 234, .height = 23 },    /* text_pane_activate_alarm@C9, 100 Optimized pixels: 1349 */
    { .dataOffset = 113334, .properties = 0, .width = 37, .height = 23 },    /* text_pane_chinese_sim, 0 Optimized pixels: 230 */
    { .dataOffset = 113794, .properties = 4, .width = 100, .height = 23 },    /* text_pane_cursor_color@C0, 100 Optimized pixels: 627 */
    { .dataOffset = 115048, .properties = 4, .width = 99, .height = 23 },    /* text_pane_cursor_color@C1, 100 Optimized pixels: 654 */
    { .dataOffset = 116356, .properties = 4, .width = 149, .height = 23 },    /* text_pane_cursor_color@C2, 100 Optimized pixels: 961 */
    { .dataOffset = 118278, .properties = 4, .width = 154, .height = 23 },    /* text_pane_cursor_color@C3, 100 Optimized pixels: 1006 */
    { .dataOffset = 120290, .properties = 4, .width = 129, .height = 23 },    /* text_pane_cursor_color@C4, 100 Optimized pixels: 845 */
    { .dataOffset = 121980, .properties = 4, .width = 149, .height = 23 },    /* text_pane_cursor_color@C5, 100 Optimized pixels: 963 */
    { .dataOffset = 123906, .properties = 4, .width = 115, .height = 23 },    /* text_pane_cursor_color@C6, 100 Optimized pixels: 765 */
    { .dataOffset = 125436, .properties = 4, .width = 79, .height = 23 },    /* text_pane_cursor_color@C7, 100 Optimized pixels: 695 */
    { .dataOffset = 126826, .properties = 4, .width = 98, .height = 23 },    /* text_pane_cursor_color@C8, 100 Optimized pixels: 618 */
    { .dataOffset = 128062, .properties = 4, .width = 77, .height = 23 },    /* text_pane_cursor_color@C9, 100 Optimized pixels: 446 */
    { .dataOffset = 128954, .properties = 0, .width = 17, .height = 23 },    /* text_pane_deg_cel, 0 Optimized pixels: 104 */
    { .dataOffset = 129162, .properties = 0, .width = 16, .height = 23 },    /* text_pane_deg_far, 0 Optimized pixels: 76 */
    { .dataOffset = 129314, .properties = 0, .width = 93, .height = 23 },    /* text_pane_dutch, 0 Optimized pixels: 721 */
    { .dataOffset = 130756, .properties = 0, .width = 58, .height = 23 },    /* text_pane_english, 0 Optimized pixels: 458 */
    { .dataOffset = 131672, .properties = 0, .width = 69, .height = 23 },    /* text_pane_french, 0 Optimized pixels: 493 */
    { .dataOffset = 132658, .properties = 0, .width = 66, .height = 23 },    /* text_pane_german, 0 Optimized pixels: 475 */
    { .dataOffset = 133608, .properties = 4, .width = 112, .height = 23 },    /* text_pane_intern_temp@C0, 100 Optimized pixels: 758 */
    { .dataOffset = 135124, .properties = 4, .width = 112, .height = 23 },    /* text_pane_intern_temp@C1, 100 Optimized pixels: 706 */
    { .dataOffset = 136536, .properties = 4, .width = 161, .height = 23 },    /* text_pane_intern_temp@C2, 100 Optimized pixels: 1036 */
    { .dataOffset = 138608, .properties = 4, .width = 171, .height = 23 },    /* text_pane_intern_temp@C3, 100 Optimized pixels: 1097 */
    { .dataOffset = 140802, .properties = 4, .width = 172, .height = 23 },    /* text_pane_intern_temp@C4, 100 Optimized pixels: 1119 */
    { .dataOffset = 143040, .properties = 4, .width = 172, .height = 23 },    /* text_pane_intern_temp@C5, 100 Optimized pixels: 1119 */
    { .dataOffset = 145278, .properties = 4, .width = 221, .height = 23 },    /* text_pane_intern_temp@C6, 100 Optimized pixels: 1427 */
    { .dataOffset = 148132, .properties = 4, .width = 86, .height = 23 },    /* text_pane_intern_temp@C7, 100 Optimized pixels: 756 */
    { .dataOffset = 149644, .properties = 4, .width = 83, .height = 23 },    /* text_pane_intern_temp@C8, 100 Optimized pixels: 753 */
    { .dataOffset = 151150, .properties = 4, .width = 80, .height = 23 },    /* text_pane_intern_temp@C9, 100 Optimized pixels: 316 */
    { .dataOffset = 151782, .properties = 0, .width = 59, .height = 23 },    /* text_pane_italian, 0 Optimized pixels: 466 */
    { .dataOffset = 152714, .properties = 0, .width = 57, .height = 23 },    /* text_pane_japanese, 0 Optimized pixels: 410 */
    { .dataOffset = 153534, .properties = 0, .width = 51, .height = 23 },    /* text_pane_korean, 0 Optimized pixels: 287 */
    { .dataOffset = 154108, .properties = 0, .width = 69, .height = 23 },    /* text_pane_russian, 0 Optimized pixels: 499 */
    { .dataOffset = 155106, .properties = 4, .width = 102, .height = 23 },    /* text_pane_set_alarm_in@C0, 100 Optimized pixels: 676 */
    { .dataOffset = 156458, .properties = 4, .width = 72, .height = 23 },    /* text_pane_set_alarm_in@C1, 100 Optimized pixels: 434 */
    { .dataOffset = 157326, .properties = 4, .width = 112, .height = 23 },    /* text_pane_set_alarm_in@C2, 100 Optimized pixels: 661 */
    { .dataOffset = 158648, .properties = 4, .width = 156, .height = 23 },    /* text_pane_set_alarm_in@C3, 100 Optimized pixels: 1010 */
    { .dataOffset = 160668, .properties = 4, .width = 176, .height = 23 },    /* text_pane_set_alarm_in@C4, 100 Optimized pixels: 1206 */
    { .dataOffset = 163080, .properties = 4, .width = 172, .height = 23 },    /* text_pane_set_alarm_in@C5, 100 Optimized pixels: 1178 */
    { .dataOffset = 165436, .properties = 4, .width = 218, .height = 23 },    /* text_pane_set_alarm_in@C6, 100 Optimized pixels: 1400 */
    { .dataOffset = 168236, .properties = 4, .width = 190, .height = 23 },    /* text_pane_set_alarm_in@C7, 100 Optimized pixels: 1362 */
    { .dataOffset = 170960, .properties = 4, .width = 123, .height = 23 },    /* text_pane_set_alarm_in@C8, 100 Optimized pixels: 736 */
    { .dataOffset = 172432, .properties = 4, .width = 81, .height = 23 },    /* text_pane_set_alarm_in@C9, 100 Optimized pixels: 425 */
    { .dataOffset = 173282, .properties = 0, .width = 64, .height = 23 },    /* text_pane_spanish, 0 Optimized pixels: 459 */
    { .dataOffset = 174200, .properties = 4, .width = 37, .height = 23 },    /* text_pane_theme_dark@C0, 100 Optimized pixels: 302 */
    { .dataOffset = 174804, .properties = 4, .width = 57, .height = 23 },    /* text_pane_theme_dark@C1, 100 Optimized pixels: 409 */
    { .dataOffset = 175622, .properties = 4, .width = 54, .height = 23 },    /* text_pane_theme_dark@C2, 100 Optimized pixels: 425 */
    { .dataOffset = 176472, .properties = 4, .width = 64, .height = 23 },    /* text_pane_theme_dark@C3, 100 Optimized pixels: 455 */
    { .dataOffset = 177382, .properties = 4, .width = 57, .height = 23 },    /* text_pane_theme_dark@C4, 100 Optimized pixels: 382 */
    { .dataOffset = 178146, .properties = 4, .width = 57, .height = 23 },    /* text_pane_theme_dark@C5, 100 Optimized pixels: 382 */
    { .dataOffset = 178910, .properties = 4, .width = 69, .height = 23 },    /* text_pane_theme_dark@C6, 100 Optimized pixels: 436 */
    { .dataOffset = 179782, .properties = 4, .width = 39, .height = 23 },    /* text_pane_theme_dark@C7, 100 Optimized pixels: 375 */
    { .dataOffset = 180532, .properties = 4, .width = 36, .height = 23 },    /* text_pane_theme_dark@C8, 100 Optimized pixels: 278 */
    { .dataOffset = 181088, .properties = 4, .width = 34, .height = 23 },    /* text_pane_theme_dark@C9, 100 Optimized pixels: 180 */
    { .dataOffset = 181448, .properties = 4, .width = 40, .height = 23 },    /* text_pane_theme_light@C0, 100 Optimized pixels: 323 */
    { .dataOffset = 182094, .properties = 4, .width = 39, .height = 23 },    /* text_pane_theme_light@C1, 100 Optimized pixels: 284 */
    { .dataOffset = 182662, .properties = 4, .width = 39, .height = 23 },    /* text_pane_theme_light@C2, 100 Optimized pixels: 284 */
    { .dataOffset = 183230, .properties = 4, .width = 65, .height = 23 },    /* text_pane_theme_light@C3, 100 Optimized pixels: 409 */
    { .dataOffset = 184048, .properties = 4, .width = 28, .height = 23 },    /* text_pane_theme_light@C4, 100 Optimized pixels: 150 */
    { .dataOffset = 184348, .properties = 4, .width = 66, .height = 23 },    /* text_pane_theme_light@C5, 100 Optimized pixels: 494 */
    { .dataOffset = 185336, .properties = 4, .width = 40, .height = 23 },    /* text_pane_theme_light@C6, 100 Optimized pixels: 237 */
    { .dataOffset = 185810, .properties = 4, .width = 18, .height = 23 },    /* text_pane_theme_light@C7, 100 Optimized pixels: 163 */
    { .dataOffset = 186136, .properties = 4, .width = 18, .height = 23 },    /* text_pane_theme_light@C8, 100 Optimized pixels: 163 */
    { .dataOffset = 186462, .properties = 4, .width = 17, .height = 23 },    /* text_pane_theme_light@C9, 100 Optimized pixels: 114 */
    { .dataOffset = 186690, .properties = 0, .width = 43, .height = 23 },    /* text_pane_time_mm, 0 Optimized pixels: 322 */
    { .dataOffset = 187334, .properties = 4, .width = 59, .height = 21 },    /* text_settings@C0, 100 Optimized pixels: 410 */
    { .dataOffset = 188154, .properties = 4, .width = 82, .height = 21 },    /* text_settings@C1, 100 Optimized pixels: 542 */
    { .dataOffset = 189238, .properties = 4, .width = 96, .height = 21 },    /* text_settings@C2, 100 Optimized pixels: 615 */
    { .dataOffset = 190468, .properties = 4, .width = 83, .height = 21 },    /* text_settings@C3, 100 Optimized pixels: 517 */
    { .dataOffset = 191502, .properties = 4, .width = 102, .height = 21 },    /* text_settings@C4, 100 Optimized pixels: 725 */
    { .dataOffset = 192952, .properties = 4, .width = 93, .height = 21 },    /* text_settings@C5, 100 Optimized pixels: 601 */
    { .dataOffset = 194154, .properties = 4, .width = 87, .height = 21 },    /* text_settings@C6, 100 Optimized pixels: 529 */
    { .dataOffset = 195212, .properties = 4, .width = 35, .height = 21 },    /* text_settings@C7, 100 Optimized pixels: 261 */
    { .dataOffset = 195734, .properties = 4, .width = 35, .height = 21 },    /* text_settings@C8, 100 Optimized pixels: 242 */
    { .dataOffset = 196218, .properties = 4, .width = 29, .height = 21 },    /* text_settings@C9, 100 Optimized pixels: 207 */
    { .dataOffset = 196632, .properties = 4, .width = 41, .height = 21 },    /* text_setup@C0, 100 Optimized pixels: 319 */
    { .dataOffset = 197270, .properties = 4, .width = 46, .height = 21 },    /* text_setup@C1, 100 Optimized pixels: 341 */
    { .dataOffset = 197952, .properties = 4, .width = 80, .height = 21 },    /* text_setup@C2, 100 Optimized pixels: 479 */
    { .dataOffset = 198910, .properties = 4, .width = 89, .height = 21 },    /* text_setup@C3, 100 Optimized pixels: 562 */
    { .dataOffset = 200034, .properties = 4, .width = 52, .height = 21 },    /* text_setup@C4, 100 Optimized pixels: 379 */
    { .dataOffset = 200792, .properties = 4, .width = 91, .height = 21 },    /* text_setup@C5, 100 Optimized pixels: 643 */
    { .dataOffset = 202078, .properties = 4, .width = 81, .height = 21 },    /* text_setup@C6, 100 Optimized pixels: 497 */
    { .dataOffset = 203072, .properties = 4, .width = 35, .height = 21 },    /* text_setup@C7, 100 Optimized pixels: 261 */
    { .dataOffset = 203594, .properties = 4, .width = 76, .height = 21 },    /* text_setup@C8, 100 Optimized pixels: 449 */
    { .dataOffset = 204492, .properties = 4, .width = 29, .height = 21 },    /* text_setup@C9, 100 Optimized pixels: 202 */
    { .dataOffset = 204896, .properties = 4, .width = 50, .height = 21 },    /* text_theme@C0, 100 Optimized pixels: 320 */
    { .dataOffset = 205536, .properties = 4, .width = 50, .height = 21 },    /* text_theme@C1, 100 Optimized pixels: 326 */
    { .dataOffset = 206188, .properties = 4, .width = 50, .height = 21 },    /* text_theme@C2, 100 Optimized pixels: 326 */
    { .dataOffset = 206840, .properties = 4, .width = 50, .height = 21 },    /* text_theme@C3, 100 Optimized pixels: 328 */
    { .dataOffset = 207496, .properties = 4, .width = 41, .height = 21 },    /* text_theme@C4, 100 Optimized pixels: 251 */
    { .dataOffset = 207998, .properties = 4, .width = 41, .height = 21 },    /* text_theme@C5, 100 Optimized pixels: 251 */
    { .dataOffset = 208500, .properties = 4, .width = 39, .height = 21 },    /* text_theme@C6, 100 Optimized pixels: 240 */
    { .dataOffset = 208980, .properties = 4, .width = 34, .height = 21 },    /* text_theme@C7, 100 Optimized pixels: 242 */
    { .dataOffset = 209464, .properties = 4, .width = 41, .height = 21 },    /* text_theme@C8, 100 Optimized pixels: 114 */
    { .dataOffset = 209692, .properties = 4, .width = 30, .height = 21 },    /* text_theme@C9, 100 Optimized pixels: 190 */
    { .dataOffset = 210072, .properties = 4, .width = 36, .height = 21 },    /* text_time@C0, 100 Optimized pixels: 242 */
    { .dataOffset = 210556, .properties = 4, .width = 26, .height = 21 },    /* text_time@C1, 100 Optimized pixels: 210 */
    { .dataOffset = 210976, .properties = 4, .width = 27, .height = 21 },    /* text_time@C2, 100 Optimized pixels: 177 */
    { .dataOffset = 211330, .properties = 4, .width = 42, .height = 21 },    /* text_time@C3, 100 Optimized pixels: 236 */
    { .dataOffset = 211802, .properties = 4, .width = 34, .height = 21 },    /* text_time@C4, 100 Optimized pixels: 210 */
    { .dataOffset = 212222, .properties = 4, .width = 25, .height = 21 },    /* text_time@C5, 100 Optimized pixels: 165 */
    { .dataOffset = 212552, .properties = 4, .width = 47, .height = 21 },    /* text_time@C6, 100 Optimized pixels: 306 */
    { .dataOffset = 213164, .properties = 4, .width = 33, .height = 21 },    /* text_time@C7, 100 Optimized pixels: 270 */
    { .dataOffset = 213704, .properties = 4, .width = 33, .height = 21 },    /* text_time@C8, 100 Optimized pixels: 275 */
    { .dataOffset = 214254, .properties = 4, .width = 31, .height = 21 },    /* text_time@C9, 100 Optimized pixels: 189 */
    { .dataOffset = 214632, .properties = 4, .width = 76, .height = 29 },    /* title_alarm@C0, 100 Optimized pixels: 623 */
    { .dataOffset = 215878, .properties = 4, .width = 76, .height = 29 },    /* title_alarm@C1, 100 Optimized pixels: 623 */
    { .dataOffset = 217124, .properties = 4, .width = 76, .height = 29 },    /* title_alarm@C2, 100 Optimized pixels: 623 */
    { .dataOffset = 218370, .properties = 4, .width = 88, .height = 29 },    /* title_alarm@C3, 100 Optimized pixels: 697 */
    { .dataOffset = 219764, .properties = 4, .width = 88, .height = 29 },    /* title_alarm@C4, 100 Optimized pixels: 695 */
    { .dataOffset = 221154, .properties = 4, .width = 93, .height = 29 },    /* title_alarm@C5, 100 Optimized pixels: 685 */
    { .dataOffset = 222524, .properties = 4, .width = 102, .height = 29 },    /* title_alarm@C6, 100 Optimized pixels: 686 */
    { .dataOffset = 223896, .properties = 4, .width = 66, .height = 29 },    /* title_alarm@C7, 100 Optimized pixels: 583 */
    { .dataOffset = 225062, .properties = 4, .width = 65, .height = 29 },    /* title_alarm@C8, 100 Optimized pixels: 586 */
    { .dataOffset = 226234, .properties = 4, .width = 83, .height = 29 },    /* title_alarm@C9, 100 Optimized pixels: 537 */
    { .dataOffset = 227308, .properties = 4, .width = 105, .height = 29 },    /* title_brightness@C0, 100 Optimized pixels: 795 */
    { .dataOffset = 228898, .properties = 4, .width = 106, .height = 29 },    /* title_brightness@C1, 100 Optimized pixels: 779 */
    { .dataOffset = 230456, .properties = 4, .width = 92, .height = 29 },    /* title_brightness@C2, 100 Optimized pixels: 758 */
    { .dataOffset = 231972, .properties = 4, .width = 110, .height = 29 },    /* title_brightness@C3, 100 Optimized pixels: 771 */
    { .dataOffset = 233514, .properties = 4, .width = 49, .height = 29 },    /* title_brightness@C4, 100 Optimized pixels: 437 */
    { .dataOffset = 234388, .properties = 4, .width = 110, .height = 29 },    /* title_brightness@C5, 100 Optimized pixels: 779 */
    { .dataOffset = 235946, .properties = 4, .width = 86, .height = 29 },    /* title_brightness@C6, 100 Optimized pixels: 567 */
    { .dataOffset = 237080, .properties = 4, .width = 46, .height = 29 },    /* title_brightness@C7, 100 Optimized pixels: 364 */
    { .dataOffset = 237808, .properties = 4, .width = 57, .height = 29 },    /* title_brightness@C8, 100 Optimized pixels: 441 */
    { .dataOffset = 238690, .properties = 4, .width = 39, .height = 29 },    /* title_brightness@C9, 100 Optimized pixels: 256 */
    { .dataOffset = 239202, .properties = 4, .width = 63, .height = 29 },    /* title_colors@C0, 100 Optimized pixels: 422 */
    { .dataOffset = 240046, .properties = 4, .width = 74, .height = 29 },    /* title_colors@C1, 100 Optimized pixels: 532 */
    { .dataOffset = 241110, .properties = 4, .width = 67, .height = 29 },    /* title_colors@C2, 100 Optimized pixels: 451 */
    { .dataOffset = 242012, .properties = 4, .width = 87, .height = 29 },    /* title_colors@C3, 100 Optimized pixels: 628 */
    { .dataOffset = 243268, .properties = 4, .width = 75, .height = 29 },    /* title_colors@C4, 100 Optimized pixels: 503 */
    { .dataOffset = 244274, .properties = 4, .width = 57, .height = 29 },    /* title_colors@C5, 100 Optimized pixels: 394 */
    { .dataOffset = 245062, .properties = 4, .width = 66, .height = 29 },    /* title_colors@C6, 100 Optimized pixels: 482 */
    { .dataOffset = 246026, .properties = 4, .width = 47, .height = 29 },    /* title_colors@C7, 100 Optimized pixels: 449 */
    { .dataOffset = 246924, .properties = 4, .width = 22, .height = 29 },    /* title_colors@C8, 100 Optimized pixels: 172 */
    { .dataOffset = 247268, .properties = 4, .width = 42, .height = 29 },    /* title_colors@C9, 100 Optimized pixels: 308 */
    { .dataOffset = 247884, .properties = 4, .width = 45, .height = 29 },    /* title_date@C0, 100 Optimized pixels: 303 */
    { .dataOffset = 248490, .properties = 4, .width = 64, .height = 29 },    /* title_date@C1, 100 Optimized pixels: 451 */
    { .dataOffset = 249392, .properties = 4, .width = 64, .height = 29 },    /* title_date@C2, 100 Optimized pixels: 451 */
    { .dataOffset = 250294, .properties = 4, .width = 45, .height = 29 },    /* title_date@C3, 100 Optimized pixels: 303 */
    { .dataOffset = 250900, .properties = 4, .width = 59, .height = 29 },    /* title_date@C4, 100 Optimized pixels: 402 */
    { .dataOffset = 251704, .properties = 4, .width = 72, .height = 29 },    /* title_date@C5, 100 Optimized pixels: 499 */
    { .dataOffset = 252702, .properties = 4, .width = 51, .height = 29 },    /* title_date@C6, 100 Optimized pixels: 348 */
    { .dataOffset = 253398, .properties = 4, .width = 43, .height = 29 },    /* title_date@C7, 100 Optimized pixels: 378 */
    { .dataOffset = 254154, .properties = 4, .width = 43, .height = 29 },    /* title_date@C8, 100 Optimized pixels: 339 */
    { .dataOffset = 254832, .properties = 4, .width = 42, .height = 29 },    /* title_date@C9, 100 Optimized pixels: 297 */
    { .dataOffset = 255426, .properties = 4, .width = 37, .height = 29 },    /* title_info@C0, 100 Optimized pixels: 310 */
    { .dataOffset = 256046, .properties = 4, .width = 37, .height = 29 },    /* title_info@C1, 100 Optimized pixels: 310 */
    { .dataOffset = 256666, .properties = 4, .width = 37, .height = 29 },    /* title_info@C2, 100 Optimized pixels: 310 */
    { .dataOffset = 257286, .properties = 4, .width = 37, .height = 29 },    /* title_info@C3, 100 Optimized pixels: 310 */
    { .dataOffset = 257906, .properties = 4, .width = 119, .height = 29 },    /* title_info@C4, 100 Optimized pixels: 894 */
    { .dataOffset = 259694, .properties = 4, .width = 125, .height = 29 },    /* title_info@C5, 100 Optimized pixels: 864 */
    { .dataOffset = 261422, .properties = 4, .width = 136, .height = 29 },    /* title_info@C6, 100 Optimized pixels: 1047 */
    { .dataOffset = 263516, .properties = 4, .width = 48, .height = 29 },    /* title_info@C7, 100 Optimized pixels: 380 */
    { .dataOffset = 264276, .properties = 4, .width = 48, .height = 29 },    /* title_info@C8, 100 Optimized pixels: 474 */
    { .dataOffset = 265224, .properties = 4, .width = 42, .height = 29 },    /* title_info@C9, 100 Optimized pixels: 249 */
    { .dataOffset = 265722, .properties = 4, .width = 97, .height = 29 },    /* title_language@C0, 100 Optimized pixels: 651 */
    { .dataOffset = 267024, .properties = 4, .width = 42, .height = 29 },    /* title_language@C1, 100 Optimized pixels: 287 */
    { .dataOffset = 267598, .properties = 4, .width = 82, .height = 29 },    /* title_language@C2, 100 Optimized pixels: 591 */
    { .dataOffset = 268780, .properties = 4, .width = 72, .height = 29 },    /* title_language@C3, 100 Optimized pixels: 466 */
    { .dataOffset = 269712, .properties = 4, .width = 67, .height = 29 },    /* title_language@C4, 100 Optimized pixels: 541 */
    { .dataOffset = 270794, .properties = 4, .width = 65, .height = 29 },    /* title_language@C5, 100 Optimized pixels: 444 */
    { .dataOffset = 271682, .properties = 4, .width = 55, .height = 29 },    /* title_language@C6, 100 Optimized pixels: 370 */
    { .dataOffset = 272422, .properties = 4, .width = 47, .height = 29 },    /* title_language@C7, 100 Optimized pixels: 269 */
    { .dataOffset = 272960, .properties = 4, .width = 47, .height = 29 },    /* title_language@C8, 100 Optimized pixels: 308 */
    { .dataOffset = 273576, .properties = 4, .width = 39, .height = 29 },    /* title_language@C9, 100 Optimized pixels: 318 */
    { .dataOffset = 274212, .properties = 4, .width = 110, .height = 29 },    /* title_main_menu@C0, 100 Optimized pixels: 772 */
    { .dataOffset = 275756, .properties = 4, .width = 117, .height = 29 },    /* title_main_menu@C1, 100 Optimized pixels: 824 */
    { .dataOffset = 277404, .properties = 4, .width = 115, .height = 29 },    /* title_main_menu@C2, 100 Optimized pixels: 843 */
    { .dataOffset = 279090, .properties = 4, .width = 146, .height = 29 },    /* title_main_menu@C3, 100 Optimized pixels: 1077 */
    { .dataOffset = 281244, .properties = 4, .width = 146, .height = 29 },    /* title_main_menu@C4, 100 Optimized pixels: 1089 */
    { .dataOffset = 283422, .properties = 4, .width = 159, .height = 29 },    /* title_main_menu@C5, 100 Optimized pixels: 1180 */
    { .dataOffset = 285782, .properties = 4, .width = 152, .height = 29 },    /* title_main_menu@C6, 100 Optimized pixels: 928 */
    { .dataOffset = 287638, .properties = 4, .width = 72, .height = 29 },    /* title_main_menu@C7, 100 Optimized pixels: 466 */
    { .dataOffset = 288570, .properties = 4, .width = 123, .height = 29 },    /* title_main_menu@C8, 100 Optimized pixels: 486 */
    { .dataOffset = 289542, .properties = 4, .width = 92, .height = 29 },    /* title_main_menu@C9, 100 Optimized pixels: 568 */
    { .dataOffset = 290678, .properties = 4, .width = 138, .height = 29 },    /* title_measurement@C0, 100 Optimized pixels: 961 */
    { .dataOffset = 292600, .properties = 4, .width = 79, .height = 29 },    /* title_measurement@C1, 100 Optimized pixels: 658 */
    { .dataOffset = 293916, .properties = 4, .width = 90, .height = 29 },    /* title_measurement@C2, 100 Optimized pixels: 710 */
    { .dataOffset = 295336, .properties = 4, .width = 74, .height = 29 },    /* title_measurement@C3, 100 Optimized pixels: 571 */
    { .dataOffset = 296478, .properties = 4, .width = 90, .height = 29 },    /* title_measurement@C4, 100 Optimized pixels: 745 */
    { .dataOffset = 297968, .properties = 4, .width = 122, .height = 29 },    /* title_measurement@C5, 100 Optimized pixels: 898 */
    { .dataOffset = 299764, .properties = 4, .width = 117, .height = 29 },    /* title_measurement@C6, 100 Optimized pixels: 837 */
    { .dataOffset = 301438, .properties = 4, .width = 48, .height = 29 },    /* title_measurement@C7, 100 Optimized pixels: 454 */
    { .dataOffset = 302346, .properties = 4, .width = 46, .height = 29 },    /* title_measurement@C8, 100 Optimized pixels: 458 */
    { .dataOffset = 303262, .properties = 4, .width = 42, .height = 29 },    /* title_measurement@C9, 100 Optimized pixels: 216 */
    { .dataOffset = 303694, .properties = 4, .width = 81, .height = 29 },    /* title_settings@C0, 100 Optimized pixels: 601 */
    { .dataOffset = 304896, .properties = 4, .width = 113, .height = 29 },    /* title_settings@C1, 100 Optimized pixels: 931 */
    { .dataOffset = 306758, .properties = 4, .width = 132, .height = 29 },    /* title_settings@C2, 100 Optimized pixels: 975 */
    { .dataOffset = 308708, .properties = 4, .width = 115, .height = 29 },    /* title_settings@C3, 100 Optimized pixels: 746 */
    { .dataOffset = 310200, .properties = 4, .width = 139, .height = 29 },    /* title_settings@C4, 100 Optimized pixels: 1004 */
    { .dataOffset = 312208, .properties = 4, .width = 128, .height = 29 },    /* title_settings@C5, 100 Optimized pixels: 914 */
    { .dataOffset = 314036, .properties = 4, .width = 120, .height = 29 },    /* title_settings@C6, 100 Optimized pixels: 831 */
    { .dataOffset = 315698, .properties = 4, .width = 46, .height = 29 },    /* title_settings@C7, 100 Optimized pixels: 418 */
    { .dataOffset = 316534, .properties = 4, .width = 46, .height = 29 },    /* title_settings@C8, 100 Optimized pixels: 405 */
    { .dataOffset = 317344, .properties = 4, .width = 41, .height = 29 },    /* title_settings@C9, 100 Optimized pixels: 292 */
    { .dataOffset = 317928, .properties = 4, .width = 57, .height = 29 },    /* title_setup@C0, 100 Optimized pixels: 398 */
    { .dataOffset = 318724, .properties = 4, .width = 62, .height = 29 },    /* title_setup@C1, 100 Optimized pixels: 463 */
    { .dataOffset = 319650, .properties = 4, .width = 111, .height = 29 },    /* title_setup@C2, 100 Optimized pixels: 763 */
    { .dataOffset = 321176, .properties = 4, .width = 121, .height = 29 },    /* title_setup@C3, 100 Optimized pixels: 816 */
    { .dataOffset = 322808, .properties = 4, .width = 72, .height = 29 },    /* title_setup@C4, 100 Optimized pixels: 537 */
    { .dataOffset = 323882, .properties = 4, .width = 125, .height = 29 },    /* title_setup@C5, 100 Optimized pixels: 882 */
    { .dataOffset = 325646, .properties = 4, .width = 112, .height = 29 },    /* title_setup@C6, 100 Optimized pixels: 820 */
    { .dataOffset = 327286, .properties = 4, .width = 46, .height = 29 },    /* title_setup@C7, 100 Optimized pixels: 418 */
    { .dataOffset = 328122, .properties = 4, .width = 102, .height = 29 },    /* title_setup@C8, 100 Optimized pixels: 580 */
    { .dataOffset = 329282, .properties = 4, .width = 40, .height = 29 },    /* title_setup@C9, 100 Optimized pixels: 275 */
    { .dataOffset = 329832, .properties = 4, .width = 69, .height = 29 },    /* title_theme@C0, 100 Optimized pixels: 467 */
    { .dataOffset = 330766, .properties = 4, .width = 69, .height = 29 },    /* title_theme@C1, 100 Optimized pixels: 458 */
    { .dataOffset = 331682, .properties = 4, .width = 69, .height = 29 },    /* title_theme@C2, 100 Optimized pixels: 458 */
    { .dataOffset = 332598, .properties = 4, .width = 69, .height = 29 },    /* title_theme@C3, 100 Optimized pixels: 479 */
    { .dataOffset = 333556, .properties = 4, .width = 56, .height = 29 },    /* title_theme@C4, 100 Optimized pixels: 332 */
    { .dataOffset = 334220, .properties = 4, .width = 56, .height = 29 },    /* title_theme@C5, 100 Optimized pixels: 332 */
    { .dataOffset = 334884, .properties = 4, .width = 53, .height = 29 },    /* title_theme@C6, 100 Optimized pixels: 325 */
    { .dataOffset = 335534, .properties = 4, .width = 47, .height = 29 },    /* title_theme@C7, 100 Optimized pixels: 377 */
    { .dataOffset = 336288, .properties = 4, .width = 55, .height = 29 },    /* title_theme@C8, 100 Optimized pixels: 162 */
    { .dataOffset = 336612, .properties = 4, .width = 41, .height = 29 },    /* title_theme@C9, 100 Optimized pixels: 328 */
    { .dataOffset = 337268, .properties = 4, .width = 50, .height = 29 },    /* title_time@C0, 100 Optimized pixels: 323 */
    { .dataOffset = 337914, .properties = 4, .width = 35, .height = 29 },    /* title_time@C1, 100 Optimized pixels: 274 */
    { .dataOffset = 338462, .properties = 4, .width = 38, .height = 29 },    /* title_time@C2, 100 Optimized pixels: 210 */
    { .dataOffset = 338882, .properties = 4, .width = 58, .height = 29 },    /* title_time@C3, 100 Optimized pixels: 407 */
    { .dataOffset = 339696, .properties = 4, .width = 47, .height = 29 },    /* title_time@C4, 100 Optimized pixels: 324 */
    { .dataOffset = 340344, .properties = 4, .width = 33, .height = 29 },    /* title_time@C5, 100 Optimized pixels: 230 */
    { .dataOffset = 340804, .properties = 4, .width = 65, .height = 29 },    /* title_time@C6, 100 Optimized pixels: 516 */
    { .dataOffset = 341836, .properties = 4, .width = 45, .height = 29 },    /* title_time@C7, 100 Optimized pixels: 429 */
    { .dataOffset = 342694, .properties = 4, .width = 46, .height = 29 },    /* title_time@C8, 100 Optimized pixels: 424 */
    { .dataOffset = 343542, .properties = 4, .width = 42, .height = 29 },    /* title_time@C9, 100 Optimized pixels: 284 */
    { .dataOffset = 20, .properties = 2, .width = 32, .height = 27 },    /* IRL-Logo_@B000, 10 Optimized pixels: 864 */
    { .dataOffset = 3998, .properties = 2, .width = 36, .height = 29 },    /* IRL-Logo_@B001, 10 Optimized pixels: 1044 */
    { .dataOffset = 8798, .properties = 2, .width = 39, .height = 32 },    /* IRL-Logo_@B002, 10 Optimized pixels: 1248 */
    { .dataOffset = 14180, .properties = 2, .width = 42, .height = 35 },    /* IRL-Logo_@B003, 10 Optimized pixels: 1470 */
    { .dataOffset = 20246, .properties = 2, .width = 46, .height = 37 },    /* IRL-Logo_@B004, 10 Optimized pixels: 1702 */
    { .dataOffset = 27128, .properties = 2, .width = 49, .height = 40 },    /* IRL-Logo_@B005, 10 Optimized pixels: 1960 */
    { .dataOffset = 34646, .properties = 2, .width = 52, .height = 43 },    /* IRL-Logo_@B006, 10 Optimized pixels: 2236 */
    { .dataOffset = 43190, .properties = 2, .width = 56, .height = 46 },    /* IRL-Logo_@B007, 10 Optimized pixels: 2576 */
    { .dataOffset = 52160, .properties = 2, .width = 59, .height = 48 },    /* IRL-Logo_@B008, 10 Optimized pixels: 2832 */
    { .dataOffset = 62246, .properties = 2, .width = 62, .height = 50 },    /* IRL-Logo_@B009, 10 Optimized pixels: 3100 */
    { .dataOffset = 72860, .properties = 2, .width = 65, .height = 54 },    /* IRL-Logo_@B010, 10 Optimized pixels: 3510 */
    { .dataOffset = 84770, .properties = 2, .width = 69, .height = 56 },    /* IRL-Logo_@B011, 10 Optimized pixels: 3864 */
    { .dataOffset = 97208, .properties = 2, .width = 72, .height = 59 },    /* IRL-Logo_@B012, 10 Optimized pixels: 4248 */
    { .dataOffset = 109952, .properties = 2, .width = 76, .height = 62 },    /* IRL-Logo_@B013, 10 Optimized pixels: 4712 */
    { .dataOffset = 123968, .properties = 2, .width = 79, .height = 64 },    /* IRL-Logo_@B014, 10 Optimized pixels: 5056 */
    { .dataOffset = 138422, .properties = 2, .width = 82, .height = 67 },    /* IRL-Logo_@B015, 10 Optimized pixels: 5494 */
    { .dataOffset = 153962, .properties = 2, .width = 86, .height = 69 },    /* IRL-Logo_@B016, 10 Optimized pixels: 5934 */
    { .dataOffset = 169946, .properties = 2, .width = 89, .height = 72 },    /* IRL-Logo_@B017, 10 Optimized pixels: 6408 */
    { .dataOffset = 186740, .properties = 2, .width = 92, .height = 75 },    /* IRL-Logo_@B018, 10 Optimized pixels: 6900 */
    { .dataOffset = 204512, .properties = 2, .width = 95, .height = 77 },    /* IRL-Logo_@B019, 10 Optimized pixels: 7315 */
    { .dataOffset = 222470, .properties = 2, .width = 100, .height = 80 },    /* IRL-Logo_@B020, 10 Optimized pixels: 8000 */
    { .dataOffset = 241898, .properties = 2, .width = 102, .height = 83 },    /* IRL-Logo_@B021, 10 Optimized pixels: 8466 */
    { .dataOffset = 261224, .properties = 2, .width = 105, .height = 85 },    /* IRL-Logo_@B022, 10 Optimized pixels: 8925 */
    { .dataOffset = 282452, .properties = 2, .width = 109, .height = 88 },    /* IRL-Logo_@B023, 10 Optimized pixels: 9592 */
    { .dataOffset = 302000, .properties = 1, .width = 30, .height = 30 },    /* NumInput_minus@A0, 1 Optimized pixels: 900 */
    { .dataOffset = 303398, .properties = 1, .width = 30, .height = 30 },    /* NumInput_minus@A1, 1 Optimized pixels: 900 */
    { .dataOffset = 304796, .properties = 1, .width = 30, .height = 30 },    /* NumInput_plus@A0, 1 Optimized pixels: 900 */
    { .dataOffset = 306530, .properties = 1, .width = 30, .height = 30 },    /* NumInput_plus@A1, 1 Optimized pixels: 900 */
    { .dataOffset = 308264, .properties = 1, .width = 22, .height = 31 },    /* Slider@A0, 1 Optimized pixels: 682 */
    { .dataOffset = 308906, .properties = 1, .width = 22, .height = 31 },    /* Slider@A1, 1 Optimized pixels: 682 */
    { .dataOffset = 309548, .properties = 0, .width = 128, .height = 128 },    /* IRL_Logo 128, 0 Optimized pixels: 16384 */
    { .dataOffset = 319628, .properties = 0, .width = 48, .height = 48 },    /* IRL_Logo_48, 0 Optimized pixels: 2304 */
    { .dataOffset = 322976, .properties = 1, .width = 480, .height = 236 },    /* Keyboard_lc@A0, 1 Optimized pixels: 113280 */
    { .dataOffset = 367406, .properties = 1, .width = 480, .height = 236 },    /* Keyboard_lc@A1, 1 Optimized pixels: 113280 */
    { .dataOffset = 411848, .properties = 1, .width = 480, .height = 236 },    /* Keyboard_num@A0, 1 Optimized pixels: 113280 */
    { .dataOffset = 451412, .properties = 1, .width = 480, .height = 236 },    /* Keyboard_num@A1, 1 Optimized pixels: 113280 */
    { .dataOffset = 490988, .properties = 1, .width = 480, .height = 84 },    /* Keyboard_textbox@A0, 1 Optimized pixels: 40320 */
    { .dataOffset = 492134, .properties = 1, .width = 480, .height = 84 },    /* Keyboard_textbox@A1, 1 Optimized pixels: 40320 */
    { .dataOffset = 493280, .properties = 1, .width = 480, .height = 236 },    /* Keyboard_uc@A0, 1 Optimized pixels: 113280 */
    { .dataOffset = 541742, .properties = 1, .width = 480, .height = 236 },    /* Keyboard_uc@A1, 1 Optimized pixels: 113280 */
};

const uint8_t maxProperty[FS_MAX_FILE_PROPERTIES] =
{
    2, 24, 10, 2, 4, 
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

    *p_dataLocation = (fileIndex < FS_FILES_START_PIXEL_DATA_INDEX) ? FS_FILE_LOCATION_CODE : FS_FILE_LOCATION_PIXEL_DATA;

    if (0U == propertiesLength)
    {
        *p_out_file_info = fs_file_infos[fileIndex];

        return FILE_SEARCH_OK;
    }

    if (FS_MAX_FILE_PROPERTIES != propertiesLength)
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

/*** end of file ***/
