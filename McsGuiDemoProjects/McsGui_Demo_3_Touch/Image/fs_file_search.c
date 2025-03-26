#include "fs_file_search.h"

#define FS_FILE_INFO_SIZE 9
#define FS_FILE_DUMMY 0xFFFFFFFFU

const fs_file_info_s fs_file_infos[] =
{
    { .dataOffset = 16, .properties = 0, .width = 30, .height = 30 },    /* Button_minus, 0 */
    { .dataOffset = 1816, .properties = 0, .width = 80, .height = 30 },    /* Play, 0 */
    { .dataOffset = 6616, .properties = 0, .width = 80, .height = 30 },    /* Play_Pressed, 0 */
    { .dataOffset = 11416, .properties = 0, .width = 30, .height = 30 },    /* Button_plus, 0 */
    { .dataOffset = 13216, .properties = 0, .width = 80, .height = 30 },    /* Stop, 0 */
    { .dataOffset = 18016, .properties = 0, .width = 80, .height = 30 },    /* Stop_Pressed, 0 */
    { .dataOffset = 22816, .properties = 0, .width = 6, .height = 12 },    /* icon_Arrow-Down-Small, 0 */
    { .dataOffset = 22960, .properties = 0, .width = 6, .height = 12 },    /* icon_Arrow-Up-Small, 0 */
    { .dataOffset = 23104, .properties = 0, .width = 45, .height = 38 },    /* icon_back, 0 */
    { .dataOffset = 26524, .properties = 12, .width = 22, .height = 22 },    /* icon_Bullseye@C0_D0, 1100 */
    { .dataOffset = 27492, .properties = 12, .width = 22, .height = 22 },    /* icon_Bullseye@C0_D1, 1100 */
    { .dataOffset = 28460, .properties = 12, .width = 22, .height = 22 },    /* icon_Bullseye@C1_D0, 1100 */
    { .dataOffset = 29428, .properties = 12, .width = 22, .height = 22 },    /* icon_Bullseye@C1_D1, 1100 */
    { .dataOffset = 30396, .properties = 0, .width = 18, .height = 18 },    /* icon_Clock, 0 */
    { .dataOffset = 31044, .properties = 4, .width = 22, .height = 17 },    /* icon_Data@C0, 100 */
    { .dataOffset = 31792, .properties = 4, .width = 22, .height = 17 },    /* icon_Data@C1, 100 */
    { .dataOffset = 32540, .properties = 0, .width = 22, .height = 20 },    /* icon_display, 0 */
    { .dataOffset = 33420, .properties = 4, .width = 20, .height = 20 },    /* icon_Focus@C0, 100 */
    { .dataOffset = 34220, .properties = 4, .width = 20, .height = 20 },    /* icon_Focus@C1, 100 */
    { .dataOffset = 35020, .properties = 4, .width = 20, .height = 20 },    /* icon_Gear@C0, 100 */
    { .dataOffset = 35820, .properties = 4, .width = 20, .height = 20 },    /* icon_Gear@C1, 100 */
    { .dataOffset = 36620, .properties = 4, .width = 20, .height = 23 },    /* icon_Home@C0, 100 */
    { .dataOffset = 37540, .properties = 4, .width = 20, .height = 23 },    /* icon_Home@C1, 100 */
    { .dataOffset = 38460, .properties = 0, .width = 22, .height = 22 },    /* icon_language, 0 */
    { .dataOffset = 39428, .properties = 0, .width = 16, .height = 4 },    /* icon_minus, 0 */
    { .dataOffset = 39556, .properties = 0, .width = 18, .height = 20 },    /* icon_pane_Agenda, 0 */
    { .dataOffset = 40276, .properties = 0, .width = 18, .height = 18 },    /* icon_pane_Clock, 0 */
    { .dataOffset = 40924, .properties = 0, .width = 16, .height = 16 },    /* icon_plus, 0 */
    { .dataOffset = 41436, .properties = 0, .width = 22, .height = 18 },    /* icon_Pulse, 0 */
    { .dataOffset = 42228, .properties = 0, .width = 24, .height = 24 },    /* icon_Scroll-down, 0 */
    { .dataOffset = 43380, .properties = 0, .width = 24, .height = 24 },    /* icon_Scroll-up, 0 */
    { .dataOffset = 44532, .properties = 0, .width = 20, .height = 20 },    /* icon_Slider_knob, 0 */
    { .dataOffset = 45332, .properties = 4, .width = 20, .height = 20 },    /* icon_Sliders@C0, 100 */
    { .dataOffset = 46132, .properties = 4, .width = 20, .height = 20 },    /* icon_Sliders@C1, 100 */
    { .dataOffset = 46932, .properties = 4, .width = 50, .height = 22 },    /* icon_Switch@C0, 100 */
    { .dataOffset = 49132, .properties = 4, .width = 50, .height = 22 },    /* icon_Switch@C1, 100 */
    { .dataOffset = 51332, .properties = 0, .width = 13, .height = 25 },    /* icon_thermometer, 0 */
    { .dataOffset = 51982, .properties = 0, .width = 18, .height = 20 },    /* icon_Trash, 0 */
    { .dataOffset = 52702, .properties = 0, .width = 128, .height = 128 },    /* IRL_Logo 128, 0 */
    { .dataOffset = 85470, .properties = 0, .width = 48, .height = 48 },    /* IRL_Logo_48, 0 */
    { .dataOffset = 90078, .properties = 4, .width = 19, .height = 19 },    /* Radio-Button@C0, 100 */
    { .dataOffset = 90800, .properties = 4, .width = 19, .height = 19 },    /* Radio-Button@C1, 100 */
    { .dataOffset = 91522, .properties = 0, .width = 33, .height = 21 },    /* text_chinese_sim, 0 */
    { .dataOffset = 92908, .properties = 1, .width = 72, .height = 21 },    /* text_date_time@A0, 1 */
    { .dataOffset = 95932, .properties = 1, .width = 76, .height = 21 },    /* text_date_time@A1, 1 */
    { .dataOffset = 99124, .properties = 1, .width = 106, .height = 21 },    /* text_date_time@A2, 1 */
    { .dataOffset = 103576, .properties = 1, .width = 80, .height = 21 },    /* text_date_time@A3, 1 */
    { .dataOffset = 106936, .properties = 1, .width = 82, .height = 21 },    /* text_date_time@A4, 1 */
    { .dataOffset = 110380, .properties = 1, .width = 63, .height = 21 },    /* text_date_time@A5, 1 */
    { .dataOffset = 113026, .properties = 1, .width = 92, .height = 21 },    /* text_date_time@A6, 1 */
    { .dataOffset = 116890, .properties = 1, .width = 74, .height = 21 },    /* text_date_time@A7, 1 */
    { .dataOffset = 119998, .properties = 1, .width = 75, .height = 21 },    /* text_date_time@A8, 1 */
    { .dataOffset = 123148, .properties = 1, .width = 70, .height = 21 },    /* text_date_time@A9, 1 */
    { .dataOffset = 126088, .properties = 0, .width = 16, .height = 21 },    /* text_deg_cel, 0 */
    { .dataOffset = 126760, .properties = 0, .width = 15, .height = 21 },    /* text_deg_far, 0 */
    { .dataOffset = 127390, .properties = 1, .width = 52, .height = 21 },    /* text_display@A0, 1 */
    { .dataOffset = 129574, .properties = 1, .width = 94, .height = 21 },    /* text_display@A1, 1 */
    { .dataOffset = 133522, .properties = 1, .width = 48, .height = 21 },    /* text_display@A2, 1 */
    { .dataOffset = 135538, .properties = 1, .width = 57, .height = 21 },    /* text_display@A3, 1 */
    { .dataOffset = 137932, .properties = 1, .width = 56, .height = 21 },    /* text_display@A4, 1 */
    { .dataOffset = 140284, .properties = 1, .width = 55, .height = 21 },    /* text_display@A5, 1 */
    { .dataOffset = 142594, .properties = 1, .width = 66, .height = 21 },    /* text_display@A6, 1 */
    { .dataOffset = 145366, .properties = 1, .width = 34, .height = 21 },    /* text_display@A7, 1 */
    { .dataOffset = 146794, .properties = 1, .width = 33, .height = 21 },    /* text_display@A8, 1 */
    { .dataOffset = 148180, .properties = 1, .width = 29, .height = 21 },    /* text_display@A9, 1 */
    { .dataOffset = 149398, .properties = 0, .width = 82, .height = 21 },    /* text_dutch, 0 */
    { .dataOffset = 152842, .properties = 0, .width = 51, .height = 21 },    /* text_english, 0 */
    { .dataOffset = 154984, .properties = 0, .width = 61, .height = 21 },    /* text_french, 0 */
    { .dataOffset = 157546, .properties = 0, .width = 58, .height = 21 },    /* text_german, 0 */
    { .dataOffset = 159982, .properties = 0, .width = 10, .height = 21 },    /* text_hashtag, 0 */
    { .dataOffset = 160402, .properties = 1, .width = 85, .height = 21 },    /* text_hide_date@A0, 1 */
    { .dataOffset = 163972, .properties = 1, .width = 124, .height = 21 },    /* text_hide_date@A1, 1 */
    { .dataOffset = 169180, .properties = 1, .width = 150, .height = 21 },    /* text_hide_date@A2, 1 */
    { .dataOffset = 175480, .properties = 1, .width = 104, .height = 21 },    /* text_hide_date@A3, 1 */
    { .dataOffset = 179848, .properties = 1, .width = 92, .height = 21 },    /* text_hide_date@A4, 1 */
    { .dataOffset = 183712, .properties = 1, .width = 103, .height = 21 },    /* text_hide_date@A5, 1 */
    { .dataOffset = 188038, .properties = 1, .width = 98, .height = 21 },    /* text_hide_date@A6, 1 */
    { .dataOffset = 192154, .properties = 1, .width = 70, .height = 21 },    /* text_hide_date@A7, 1 */
    { .dataOffset = 195094, .properties = 1, .width = 86, .height = 21 },    /* text_hide_date@A8, 1 */
    { .dataOffset = 198706, .properties = 1, .width = 69, .height = 21 },    /* text_hide_date@A9, 1 */
    { .dataOffset = 201604, .properties = 1, .width = 89, .height = 21 },    /* text_hide_time@A0, 1 */
    { .dataOffset = 205342, .properties = 1, .width = 104, .height = 21 },    /* text_hide_time@A1, 1 */
    { .dataOffset = 209710, .properties = 1, .width = 116, .height = 21 },    /* text_hide_time@A2, 1 */
    { .dataOffset = 214582, .properties = 1, .width = 98, .height = 21 },    /* text_hide_time@A3, 1 */
    { .dataOffset = 218698, .properties = 1, .width = 105, .height = 21 },    /* text_hide_time@A4, 1 */
    { .dataOffset = 223108, .properties = 1, .width = 130, .height = 21 },    /* text_hide_time@A5, 1 */
    { .dataOffset = 228568, .properties = 1, .width = 119, .height = 21 },    /* text_hide_time@A6, 1 */
    { .dataOffset = 233566, .properties = 1, .width = 70, .height = 21 },    /* text_hide_time@A7, 1 */
    { .dataOffset = 236506, .properties = 1, .width = 94, .height = 21 },    /* text_hide_time@A8, 1 */
    { .dataOffset = 240454, .properties = 1, .width = 85, .height = 21 },    /* text_hide_time@A9, 1 */
    { .dataOffset = 244024, .properties = 0, .width = 13, .height = 21 },    /* text_id, 0 */
    { .dataOffset = 244570, .properties = 1, .width = 76, .height = 21 },    /* text_interval@A0, 1 */
    { .dataOffset = 247762, .properties = 1, .width = 76, .height = 21 },    /* text_interval@A1, 1 */
    { .dataOffset = 250954, .properties = 1, .width = 80, .height = 21 },    /* text_interval@A2, 1 */
    { .dataOffset = 254314, .properties = 1, .width = 89, .height = 21 },    /* text_interval@A3, 1 */
    { .dataOffset = 258052, .properties = 1, .width = 85, .height = 21 },    /* text_interval@A4, 1 */
    { .dataOffset = 261622, .properties = 1, .width = 89, .height = 21 },    /* text_interval@A5, 1 */
    { .dataOffset = 265360, .properties = 1, .width = 97, .height = 21 },    /* text_interval@A6, 1 */
    { .dataOffset = 269434, .properties = 1, .width = 58, .height = 21 },    /* text_interval@A7, 1 */
    { .dataOffset = 271870, .properties = 1, .width = 40, .height = 21 },    /* text_interval@A8, 1 */
    { .dataOffset = 273550, .properties = 1, .width = 38, .height = 21 },    /* text_interval@A9, 1 */
    { .dataOffset = 275146, .properties = 0, .width = 52, .height = 21 },    /* text_italian, 0 */
    { .dataOffset = 277330, .properties = 0, .width = 50, .height = 21 },    /* text_japanese, 0 */
    { .dataOffset = 279430, .properties = 0, .width = 46, .height = 21 },    /* text_korean, 0 */
    { .dataOffset = 281362, .properties = 1, .width = 71, .height = 21 },    /* text_language@A0, 1 */
    { .dataOffset = 284344, .properties = 1, .width = 31, .height = 21 },    /* text_language@A1, 1 */
    { .dataOffset = 285646, .properties = 1, .width = 59, .height = 21 },    /* text_language@A2, 1 */
    { .dataOffset = 288124, .properties = 1, .width = 52, .height = 21 },    /* text_language@A3, 1 */
    { .dataOffset = 290308, .properties = 1, .width = 48, .height = 21 },    /* text_language@A4, 1 */
    { .dataOffset = 292324, .properties = 1, .width = 47, .height = 21 },    /* text_language@A5, 1 */
    { .dataOffset = 294298, .properties = 1, .width = 40, .height = 21 },    /* text_language@A6, 1 */
    { .dataOffset = 295978, .properties = 1, .width = 35, .height = 21 },    /* text_language@A7, 1 */
    { .dataOffset = 297448, .properties = 1, .width = 35, .height = 21 },    /* text_language@A8, 1 */
    { .dataOffset = 298918, .properties = 1, .width = 29, .height = 21 },    /* text_language@A9, 1 */
    { .dataOffset = 300136, .properties = 1, .width = 120, .height = 21 },    /* text_max_data_points@A0, 1 */
    { .dataOffset = 305176, .properties = 1, .width = 125, .height = 21 },    /* text_max_data_points@A1, 1 */
    { .dataOffset = 310426, .properties = 1, .width = 131, .height = 21 },    /* text_max_data_points@A2, 1 */
    { .dataOffset = 315928, .properties = 1, .width = 174, .height = 21 },    /* text_max_data_points@A3, 1 */
    { .dataOffset = 323236, .properties = 1, .width = 156, .height = 21 },    /* text_max_data_points@A4, 1 */
    { .dataOffset = 329788, .properties = 1, .width = 219, .height = 21 },    /* text_max_data_points@A5, 1 */
    { .dataOffset = 338986, .properties = 1, .width = 96, .height = 21 },    /* text_max_data_points@A6, 1 */
    { .dataOffset = 343018, .properties = 1, .width = 108, .height = 21 },    /* text_max_data_points@A7, 1 */
    { .dataOffset = 347554, .properties = 1, .width = 132, .height = 21 },    /* text_max_data_points@A8, 1 */
    { .dataOffset = 353098, .properties = 1, .width = 138, .height = 21 },    /* text_max_data_points@A9, 1 */
    { .dataOffset = 358894, .properties = 0, .width = 61, .height = 21 },    /* text_russian, 0 */
    { .dataOffset = 361456, .properties = 1, .width = 35, .height = 21 },    /* text_save@A0, 1 */
    { .dataOffset = 362926, .properties = 1, .width = 59, .height = 21 },    /* text_save@A1, 1 */
    { .dataOffset = 365404, .properties = 1, .width = 45, .height = 21 },    /* text_save@A2, 1 */
    { .dataOffset = 367294, .properties = 1, .width = 92, .height = 21 },    /* text_save@A3, 1 */
    { .dataOffset = 371158, .properties = 1, .width = 45, .height = 21 },    /* text_save@A4, 1 */
    { .dataOffset = 373048, .properties = 1, .width = 53, .height = 21 },    /* text_save@A5, 1 */
    { .dataOffset = 375274, .properties = 1, .width = 63, .height = 21 },    /* text_save@A6, 1 */
    { .dataOffset = 377920, .properties = 1, .width = 17, .height = 21 },    /* text_save@A7, 1 */
    { .dataOffset = 378634, .properties = 1, .width = 43, .height = 21 },    /* text_save@A8, 1 */
    { .dataOffset = 380440, .properties = 1, .width = 65, .height = 21 },    /* text_save@A9, 1 */
    { .dataOffset = 383170, .properties = 1, .width = 141, .height = 21 },    /* text_save_rec@A0, 1 */
    { .dataOffset = 389092, .properties = 1, .width = 120, .height = 21 },    /* text_save_rec@A1, 1 */
    { .dataOffset = 394132, .properties = 1, .width = 141, .height = 21 },    /* text_save_rec@A2, 1 */
    { .dataOffset = 400054, .properties = 1, .width = 154, .height = 21 },    /* text_save_rec@A3, 1 */
    { .dataOffset = 406522, .properties = 1, .width = 129, .height = 21 },    /* text_save_rec@A4, 1 */
    { .dataOffset = 411940, .properties = 1, .width = 133, .height = 21 },    /* text_save_rec@A5, 1 */
    { .dataOffset = 417526, .properties = 1, .width = 170, .height = 21 },    /* text_save_rec@A6, 1 */
    { .dataOffset = 424666, .properties = 1, .width = 71, .height = 21 },    /* text_save_rec@A7, 1 */
    { .dataOffset = 427648, .properties = 1, .width = 104, .height = 21 },    /* text_save_rec@A8, 1 */
    { .dataOffset = 432016, .properties = 1, .width = 85, .height = 21 },    /* text_save_rec@A9, 1 */
    { .dataOffset = 435586, .properties = 1, .width = 44, .height = 21 },    /* text_saved@A0, 1 */
    { .dataOffset = 437434, .properties = 1, .width = 86, .height = 21 },    /* text_saved@A1, 1 */
    { .dataOffset = 441046, .properties = 1, .width = 87, .height = 21 },    /* text_saved@A2, 1 */
    { .dataOffset = 444700, .properties = 1, .width = 44, .height = 21 },    /* text_saved@A3, 1 */
    { .dataOffset = 446548, .properties = 1, .width = 71, .height = 21 },    /* text_saved@A4, 1 */
    { .dataOffset = 449530, .properties = 1, .width = 54, .height = 21 },    /* text_saved@A5, 1 */
    { .dataOffset = 451798, .properties = 1, .width = 83, .height = 21 },    /* text_saved@A6, 1 */
    { .dataOffset = 455284, .properties = 1, .width = 35, .height = 21 },    /* text_saved@A7, 1 */
    { .dataOffset = 456754, .properties = 1, .width = 35, .height = 21 },    /* text_saved@A8, 1 */
    { .dataOffset = 458224, .properties = 1, .width = 31, .height = 21 },    /* text_saved@A9, 1 */
    { .dataOffset = 459526, .properties = 1, .width = 83, .height = 21 },    /* text_show_date@A0, 1 */
    { .dataOffset = 463012, .properties = 1, .width = 120, .height = 21 },    /* text_show_date@A1, 1 */
    { .dataOffset = 468052, .properties = 1, .width = 111, .height = 21 },    /* text_show_date@A2, 1 */
    { .dataOffset = 472714, .properties = 1, .width = 83, .height = 21 },    /* text_show_date@A3, 1 */
    { .dataOffset = 476200, .properties = 1, .width = 93, .height = 21 },    /* text_show_date@A4, 1 */
    { .dataOffset = 480106, .properties = 1, .width = 87, .height = 21 },    /* text_show_date@A5, 1 */
    { .dataOffset = 483760, .properties = 1, .width = 107, .height = 21 },    /* text_show_date@A6, 1 */
    { .dataOffset = 488254, .properties = 1, .width = 70, .height = 21 },    /* text_show_date@A7, 1 */
    { .dataOffset = 491194, .properties = 1, .width = 71, .height = 21 },    /* text_show_date@A8, 1 */
    { .dataOffset = 494176, .properties = 1, .width = 102, .height = 21 },    /* text_show_date@A9, 1 */
    { .dataOffset = 498460, .properties = 1, .width = 87, .height = 21 },    /* text_show_time@A0, 1 */
    { .dataOffset = 502114, .properties = 1, .width = 99, .height = 21 },    /* text_show_time@A1, 1 */
    { .dataOffset = 506272, .properties = 1, .width = 91, .height = 21 },    /* text_show_time@A2, 1 */
    { .dataOffset = 510094, .properties = 1, .width = 101, .height = 21 },    /* text_show_time@A3, 1 */
    { .dataOffset = 514336, .properties = 1, .width = 106, .height = 21 },    /* text_show_time@A4, 1 */
    { .dataOffset = 518788, .properties = 1, .width = 106, .height = 21 },    /* text_show_time@A5, 1 */
    { .dataOffset = 523240, .properties = 1, .width = 120, .height = 21 },    /* text_show_time@A6, 1 */
    { .dataOffset = 528280, .properties = 1, .width = 70, .height = 21 },    /* text_show_time@A7, 1 */
    { .dataOffset = 531220, .properties = 1, .width = 122, .height = 21 },    /* text_show_time@A8, 1 */
    { .dataOffset = 536344, .properties = 1, .width = 102, .height = 21 },    /* text_show_time@A9, 1 */
    { .dataOffset = 540628, .properties = 0, .width = 56, .height = 21 },    /* text_spanish, 0 */
    { .dataOffset = 542980, .properties = 1, .width = 37, .height = 21 },    /* text_units@A0, 1 */
    { .dataOffset = 544534, .properties = 1, .width = 70, .height = 21 },    /* text_units@A1, 1 */
    { .dataOffset = 547474, .properties = 1, .width = 65, .height = 21 },    /* text_units@A2, 1 */
    { .dataOffset = 550204, .properties = 1, .width = 45, .height = 21 },    /* text_units@A3, 1 */
    { .dataOffset = 552094, .properties = 1, .width = 68, .height = 21 },    /* text_units@A4, 1 */
    { .dataOffset = 554950, .properties = 1, .width = 37, .height = 21 },    /* text_units@A5, 1 */
    { .dataOffset = 556504, .properties = 1, .width = 56, .height = 21 },    /* text_units@A6, 1 */
    { .dataOffset = 558856, .properties = 1, .width = 35, .height = 21 },    /* text_units@A7, 1 */
    { .dataOffset = 560326, .properties = 1, .width = 35, .height = 21 },    /* text_units@A8, 1 */
    { .dataOffset = 561796, .properties = 1, .width = 29, .height = 21 },    /* text_units@A9, 1 */
    { .dataOffset = 563014, .properties = 1, .width = 87, .height = 23 },    /* title_brightness@A0, 1 */
    { .dataOffset = 567016, .properties = 1, .width = 87, .height = 23 },    /* title_brightness@A1, 1 */
    { .dataOffset = 571018, .properties = 1, .width = 75, .height = 23 },    /* title_brightness@A2, 1 */
    { .dataOffset = 574468, .properties = 1, .width = 90, .height = 23 },    /* title_brightness@A3, 1 */
    { .dataOffset = 578608, .properties = 1, .width = 40, .height = 23 },    /* title_brightness@A4, 1 */
    { .dataOffset = 580448, .properties = 1, .width = 90, .height = 23 },    /* title_brightness@A5, 1 */
    { .dataOffset = 584588, .properties = 1, .width = 71, .height = 23 },    /* title_brightness@A6, 1 */
    { .dataOffset = 587854, .properties = 1, .width = 39, .height = 23 },    /* title_brightness@A7, 1 */
    { .dataOffset = 589648, .properties = 1, .width = 48, .height = 23 },    /* title_brightness@A8, 1 */
    { .dataOffset = 591856, .properties = 1, .width = 32, .height = 23 },    /* title_brightness@A9, 1 */
    { .dataOffset = 593328, .properties = 1, .width = 128, .height = 23 },    /* title_calibrate_touch@A0, 1 */
    { .dataOffset = 599216, .properties = 1, .width = 134, .height = 23 },    /* title_calibrate_touch@A1, 1 */
    { .dataOffset = 605380, .properties = 1, .width = 155, .height = 23 },    /* title_calibrate_touch@A2, 1 */
    { .dataOffset = 612510, .properties = 1, .width = 132, .height = 23 },    /* title_calibrate_touch@A3, 1 */
    { .dataOffset = 618582, .properties = 1, .width = 129, .height = 23 },    /* title_calibrate_touch@A4, 1 */
    { .dataOffset = 624516, .properties = 1, .width = 107, .height = 23 },    /* title_calibrate_touch@A5, 1 */
    { .dataOffset = 629438, .properties = 1, .width = 266, .height = 23 },    /* title_calibrate_touch@A6, 1 */
    { .dataOffset = 641674, .properties = 1, .width = 81, .height = 23 },    /* title_calibrate_touch@A7, 1 */
    { .dataOffset = 645400, .properties = 1, .width = 190, .height = 23 },    /* title_calibrate_touch@A8, 1 */
    { .dataOffset = 654140, .properties = 1, .width = 74, .height = 23 },    /* title_calibrate_touch@A9, 1 */
    { .dataOffset = 657544, .properties = 1, .width = 81, .height = 23 },    /* title_date_time@A0, 1 */
    { .dataOffset = 661270, .properties = 1, .width = 86, .height = 23 },    /* title_date_time@A1, 1 */
    { .dataOffset = 665226, .properties = 1, .width = 119, .height = 23 },    /* title_date_time@A2, 1 */
    { .dataOffset = 670700, .properties = 1, .width = 91, .height = 23 },    /* title_date_time@A3, 1 */
    { .dataOffset = 674886, .properties = 1, .width = 93, .height = 23 },    /* title_date_time@A4, 1 */
    { .dataOffset = 679164, .properties = 1, .width = 71, .height = 23 },    /* title_date_time@A5, 1 */
    { .dataOffset = 682430, .properties = 1, .width = 104, .height = 23 },    /* title_date_time@A6, 1 */
    { .dataOffset = 687214, .properties = 1, .width = 84, .height = 23 },    /* title_date_time@A7, 1 */
    { .dataOffset = 691078, .properties = 1, .width = 84, .height = 23 },    /* title_date_time@A8, 1 */
    { .dataOffset = 694942, .properties = 1, .width = 79, .height = 23 },    /* title_date_time@A9, 1 */
    { .dataOffset = 698576, .properties = 0, .width = 15, .height = 23 },    /* title_id, 0 */
    { .dataOffset = 699266, .properties = 1, .width = 80, .height = 23 },    /* title_language@A0, 1 */
    { .dataOffset = 702946, .properties = 1, .width = 35, .height = 23 },    /* title_language@A1, 1 */
    { .dataOffset = 704556, .properties = 1, .width = 67, .height = 23 },    /* title_language@A2, 1 */
    { .dataOffset = 707638, .properties = 1, .width = 59, .height = 23 },    /* title_language@A3, 1 */
    { .dataOffset = 710352, .properties = 1, .width = 55, .height = 23 },    /* title_language@A4, 1 */
    { .dataOffset = 712882, .properties = 1, .width = 53, .height = 23 },    /* title_language@A5, 1 */
    { .dataOffset = 715320, .properties = 1, .width = 45, .height = 23 },    /* title_language@A6, 1 */
    { .dataOffset = 717390, .properties = 1, .width = 39, .height = 23 },    /* title_language@A7, 1 */
    { .dataOffset = 719184, .properties = 1, .width = 39, .height = 23 },    /* title_language@A8, 1 */
    { .dataOffset = 720978, .properties = 1, .width = 32, .height = 23 },    /* title_language@A9, 1 */
    { .dataOffset = 722450, .properties = 1, .width = 122, .height = 23 },    /* title_measurements@A0, 1 */
    { .dataOffset = 728062, .properties = 1, .width = 85, .height = 23 },    /* title_measurements@A1, 1 */
    { .dataOffset = 731972, .properties = 1, .width = 94, .height = 23 },    /* title_measurements@A2, 1 */
    { .dataOffset = 736296, .properties = 1, .width = 112, .height = 23 },    /* title_measurements@A3, 1 */
    { .dataOffset = 741448, .properties = 1, .width = 69, .height = 23 },    /* title_measurements@A4, 1 */
    { .dataOffset = 744622, .properties = 1, .width = 55, .height = 23 },    /* title_measurements@A5, 1 */
    { .dataOffset = 747152, .properties = 1, .width = 96, .height = 23 },    /* title_measurements@A6, 1 */
    { .dataOffset = 751568, .properties = 1, .width = 40, .height = 23 },    /* title_measurements@A7, 1 */
    { .dataOffset = 753408, .properties = 1, .width = 38, .height = 23 },    /* title_measurements@A8, 1 */
    { .dataOffset = 755156, .properties = 1, .width = 33, .height = 23 },    /* title_measurements@A9, 1 */
    { .dataOffset = 756674, .properties = 1, .width = 91, .height = 23 },    /* title_recordings@A0, 1 */
    { .dataOffset = 760860, .properties = 1, .width = 78, .height = 23 },    /* title_recordings@A1, 1 */
    { .dataOffset = 764448, .properties = 1, .width = 95, .height = 23 },    /* title_recordings@A2, 1 */
    { .dataOffset = 768818, .properties = 1, .width = 134, .height = 23 },    /* title_recordings@A3, 1 */
    { .dataOffset = 774982, .properties = 1, .width = 102, .height = 23 },    /* title_recordings@A4, 1 */
    { .dataOffset = 779674, .properties = 1, .width = 105, .height = 23 },    /* title_recordings@A5, 1 */
    { .dataOffset = 784504, .properties = 1, .width = 62, .height = 23 },    /* title_recordings@A6, 1 */
    { .dataOffset = 787356, .properties = 1, .width = 39, .height = 23 },    /* title_recordings@A7, 1 */
    { .dataOffset = 789150, .properties = 1, .width = 39, .height = 23 },    /* title_recordings@A8, 1 */
    { .dataOffset = 790944, .properties = 1, .width = 35, .height = 23 },    /* title_recordings@A9, 1 */
    { .dataOffset = 792554, .properties = 1, .width = 67, .height = 23 },    /* title_settings@A0, 1 */
    { .dataOffset = 795636, .properties = 1, .width = 93, .height = 23 },    /* title_settings@A1, 1 */
    { .dataOffset = 799914, .properties = 1, .width = 109, .height = 23 },    /* title_settings@A2, 1 */
    { .dataOffset = 804928, .properties = 1, .width = 94, .height = 23 },    /* title_settings@A3, 1 */
    { .dataOffset = 809252, .properties = 1, .width = 114, .height = 23 },    /* title_settings@A4, 1 */
    { .dataOffset = 814496, .properties = 1, .width = 105, .height = 23 },    /* title_settings@A5, 1 */
    { .dataOffset = 819326, .properties = 1, .width = 98, .height = 23 },    /* title_settings@A6, 1 */
    { .dataOffset = 823834, .properties = 1, .width = 39, .height = 23 },    /* title_settings@A7, 1 */
    { .dataOffset = 825628, .properties = 1, .width = 38, .height = 23 },    /* title_settings@A8, 1 */
    { .dataOffset = 827376, .properties = 1, .width = 33, .height = 23 },    /* title_settings@A9, 1 */
    { .dataOffset = 828894, .properties = 1, .width = 39, .height = 23 },    /* title_start@A0, 1 */
    { .dataOffset = 830688, .properties = 1, .width = 39, .height = 23 },    /* title_start@A1, 1 */
    { .dataOffset = 832482, .properties = 1, .width = 78, .height = 23 },    /* title_start@A2, 1 */
    { .dataOffset = 836070, .properties = 1, .width = 100, .height = 23 },    /* title_start@A3, 1 */
    { .dataOffset = 840670, .properties = 1, .width = 71, .height = 23 },    /* title_start@A4, 1 */
    { .dataOffset = 843936, .properties = 1, .width = 42, .height = 23 },    /* title_start@A5, 1 */
    { .dataOffset = 845868, .properties = 1, .width = 63, .height = 23 },    /* title_start@A6, 1 */
    { .dataOffset = 848766, .properties = 1, .width = 39, .height = 23 },    /* title_start@A7, 1 */
    { .dataOffset = 850560, .properties = 1, .width = 50, .height = 23 },    /* title_start@A8, 1 */
    { .dataOffset = 852860, .properties = 1, .width = 72, .height = 23 },    /* title_start@A9, 1 */
    { .dataOffset = 856172, .properties = 1, .width = 37, .height = 23 },    /* title_stop@A0, 1 */
    { .dataOffset = 857874, .properties = 1, .width = 37, .height = 23 },    /* title_stop@A1, 1 */
    { .dataOffset = 859576, .properties = 1, .width = 75, .height = 23 },    /* title_stop@A2, 1 */
    { .dataOffset = 863026, .properties = 1, .width = 57, .height = 23 },    /* title_stop@A3, 1 */
    { .dataOffset = 865648, .properties = 1, .width = 43, .height = 23 },    /* title_stop@A4, 1 */
    { .dataOffset = 867626, .properties = 1, .width = 71, .height = 23 },    /* title_stop@A5, 1 */
    { .dataOffset = 870892, .properties = 1, .width = 91, .height = 23 },    /* title_stop@A6, 1 */
    { .dataOffset = 875078, .properties = 1, .width = 18, .height = 23 },    /* title_stop@A7, 1 */
    { .dataOffset = 875906, .properties = 1, .width = 50, .height = 23 },    /* title_stop@A8, 1 */
    { .dataOffset = 878206, .properties = 1, .width = 53, .height = 23 },    /* title_stop@A9, 1 */
};

const uint8_t maxProperty[FS_MAX_FILE_PROPERTIES] =
{
    10, 2, 2, 2, 
};

file_search_result_e fs_getFileInfo(
                            const file_key_e file_key,
                            const uint8_t *p_properties,
                            const uint8_t propertiesLength,
                            fs_file_info_s *p_out_file_info)
{
    const int32_t fileIndex = (int32_t)file_key;

    if ((fileIndex < 0) || (fileIndex >= FS_FILES))
    {
        return FILE_SEARCH_OUT_OF_BOUNDS;
    }

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
