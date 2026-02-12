#include "fs_file_search.h"

#define FS_FILE_INFO_SIZE 9
#define FS_FILE_DUMMY 0xFFFFFFFFU

const fs_file_info_s fs_file_infos[] =
{
    { .dataOffset = 20, .properties = 0, .width = 30, .height = 30 },    /* Button_minus, 0 */
    { .dataOffset = 1820, .properties = 0, .width = 80, .height = 30 },    /* Play, 0 */
    { .dataOffset = 6620, .properties = 0, .width = 80, .height = 30 },    /* Play_Pressed, 0 */
    { .dataOffset = 11420, .properties = 0, .width = 30, .height = 30 },    /* Button_plus, 0 */
    { .dataOffset = 13220, .properties = 0, .width = 80, .height = 30 },    /* Stop, 0 */
    { .dataOffset = 18020, .properties = 0, .width = 80, .height = 30 },    /* Stop_Pressed, 0 */
    { .dataOffset = 22820, .properties = 0, .width = 6, .height = 12 },    /* icon_Arrow-Down-Small, 0 */
    { .dataOffset = 22964, .properties = 0, .width = 6, .height = 12 },    /* icon_Arrow-Up-Small, 0 */
    { .dataOffset = 23108, .properties = 0, .width = 45, .height = 38 },    /* icon_back, 0 */
    { .dataOffset = 26528, .properties = 12, .width = 22, .height = 22 },    /* icon_Bullseye@C0_D0, 1100 */
    { .dataOffset = 27496, .properties = 12, .width = 22, .height = 22 },    /* icon_Bullseye@C0_D1, 1100 */
    { .dataOffset = 28464, .properties = 12, .width = 22, .height = 22 },    /* icon_Bullseye@C1_D0, 1100 */
    { .dataOffset = 29432, .properties = 12, .width = 22, .height = 22 },    /* icon_Bullseye@C1_D1, 1100 */
    { .dataOffset = 30400, .properties = 0, .width = 18, .height = 18 },    /* icon_Clock, 0 */
    { .dataOffset = 31048, .properties = 4, .width = 22, .height = 17 },    /* icon_Data@C0, 100 */
    { .dataOffset = 31796, .properties = 4, .width = 22, .height = 17 },    /* icon_Data@C1, 100 */
    { .dataOffset = 32544, .properties = 0, .width = 22, .height = 20 },    /* icon_display, 0 */
    { .dataOffset = 33424, .properties = 4, .width = 20, .height = 20 },    /* icon_Focus@C0, 100 */
    { .dataOffset = 34224, .properties = 4, .width = 20, .height = 20 },    /* icon_Focus@C1, 100 */
    { .dataOffset = 35024, .properties = 4, .width = 20, .height = 20 },    /* icon_Gear@C0, 100 */
    { .dataOffset = 35824, .properties = 4, .width = 20, .height = 20 },    /* icon_Gear@C1, 100 */
    { .dataOffset = 36624, .properties = 4, .width = 20, .height = 23 },    /* icon_Home@C0, 100 */
    { .dataOffset = 37544, .properties = 4, .width = 20, .height = 23 },    /* icon_Home@C1, 100 */
    { .dataOffset = 38464, .properties = 0, .width = 22, .height = 22 },    /* icon_language, 0 */
    { .dataOffset = 39432, .properties = 0, .width = 16, .height = 4 },    /* icon_minus, 0 */
    { .dataOffset = 39560, .properties = 0, .width = 18, .height = 20 },    /* icon_pane_Agenda, 0 */
    { .dataOffset = 40280, .properties = 0, .width = 18, .height = 18 },    /* icon_pane_Clock, 0 */
    { .dataOffset = 40928, .properties = 0, .width = 16, .height = 16 },    /* icon_plus, 0 */
    { .dataOffset = 41440, .properties = 0, .width = 22, .height = 18 },    /* icon_Pulse, 0 */
    { .dataOffset = 42232, .properties = 0, .width = 24, .height = 24 },    /* icon_Scroll-down, 0 */
    { .dataOffset = 43384, .properties = 0, .width = 24, .height = 24 },    /* icon_Scroll-up, 0 */
    { .dataOffset = 44536, .properties = 0, .width = 20, .height = 20 },    /* icon_Slider_knob, 0 */
    { .dataOffset = 45336, .properties = 4, .width = 20, .height = 20 },    /* icon_Sliders@C0, 100 */
    { .dataOffset = 46136, .properties = 4, .width = 20, .height = 20 },    /* icon_Sliders@C1, 100 */
    { .dataOffset = 46936, .properties = 4, .width = 50, .height = 22 },    /* icon_Switch@C0, 100 */
    { .dataOffset = 49136, .properties = 4, .width = 50, .height = 22 },    /* icon_Switch@C1, 100 */
    { .dataOffset = 51336, .properties = 0, .width = 13, .height = 25 },    /* icon_thermometer, 0 */
    { .dataOffset = 51986, .properties = 0, .width = 18, .height = 20 },    /* icon_Trash, 0 */
    { .dataOffset = 52706, .properties = 0, .width = 128, .height = 128 },    /* IRL_Logo 128, 0 */
    { .dataOffset = 85474, .properties = 0, .width = 48, .height = 48 },    /* IRL_Logo_48, 0 */
    { .dataOffset = 90082, .properties = 4, .width = 19, .height = 19 },    /* Radio-Button@C0, 100 */
    { .dataOffset = 90804, .properties = 4, .width = 19, .height = 19 },    /* Radio-Button@C1, 100 */
    { .dataOffset = 91526, .properties = 0, .width = 33, .height = 21 },    /* text_chinese_sim, 0 */
    { .dataOffset = 92912, .properties = 1, .width = 72, .height = 21 },    /* text_date_time@A0, 1 */
    { .dataOffset = 95936, .properties = 1, .width = 76, .height = 21 },    /* text_date_time@A1, 1 */
    { .dataOffset = 99128, .properties = 1, .width = 106, .height = 21 },    /* text_date_time@A2, 1 */
    { .dataOffset = 103580, .properties = 1, .width = 80, .height = 21 },    /* text_date_time@A3, 1 */
    { .dataOffset = 106940, .properties = 1, .width = 82, .height = 21 },    /* text_date_time@A4, 1 */
    { .dataOffset = 110384, .properties = 1, .width = 63, .height = 21 },    /* text_date_time@A5, 1 */
    { .dataOffset = 113030, .properties = 1, .width = 92, .height = 21 },    /* text_date_time@A6, 1 */
    { .dataOffset = 116894, .properties = 1, .width = 74, .height = 21 },    /* text_date_time@A7, 1 */
    { .dataOffset = 120002, .properties = 1, .width = 75, .height = 21 },    /* text_date_time@A8, 1 */
    { .dataOffset = 123152, .properties = 1, .width = 70, .height = 21 },    /* text_date_time@A9, 1 */
    { .dataOffset = 126092, .properties = 0, .width = 16, .height = 21 },    /* text_deg_cel, 0 */
    { .dataOffset = 126764, .properties = 0, .width = 15, .height = 21 },    /* text_deg_far, 0 */
    { .dataOffset = 127394, .properties = 1, .width = 52, .height = 21 },    /* text_display@A0, 1 */
    { .dataOffset = 129578, .properties = 1, .width = 94, .height = 21 },    /* text_display@A1, 1 */
    { .dataOffset = 133526, .properties = 1, .width = 48, .height = 21 },    /* text_display@A2, 1 */
    { .dataOffset = 135542, .properties = 1, .width = 57, .height = 21 },    /* text_display@A3, 1 */
    { .dataOffset = 137936, .properties = 1, .width = 56, .height = 21 },    /* text_display@A4, 1 */
    { .dataOffset = 140288, .properties = 1, .width = 55, .height = 21 },    /* text_display@A5, 1 */
    { .dataOffset = 142598, .properties = 1, .width = 66, .height = 21 },    /* text_display@A6, 1 */
    { .dataOffset = 145370, .properties = 1, .width = 34, .height = 21 },    /* text_display@A7, 1 */
    { .dataOffset = 146798, .properties = 1, .width = 33, .height = 21 },    /* text_display@A8, 1 */
    { .dataOffset = 148184, .properties = 1, .width = 29, .height = 21 },    /* text_display@A9, 1 */
    { .dataOffset = 149402, .properties = 0, .width = 82, .height = 21 },    /* text_dutch, 0 */
    { .dataOffset = 152846, .properties = 0, .width = 51, .height = 21 },    /* text_english, 0 */
    { .dataOffset = 154988, .properties = 0, .width = 61, .height = 21 },    /* text_french, 0 */
    { .dataOffset = 157550, .properties = 0, .width = 58, .height = 21 },    /* text_german, 0 */
    { .dataOffset = 159986, .properties = 0, .width = 10, .height = 21 },    /* text_hashtag, 0 */
    { .dataOffset = 160406, .properties = 1, .width = 85, .height = 21 },    /* text_hide_date@A0, 1 */
    { .dataOffset = 163976, .properties = 1, .width = 124, .height = 21 },    /* text_hide_date@A1, 1 */
    { .dataOffset = 169184, .properties = 1, .width = 150, .height = 21 },    /* text_hide_date@A2, 1 */
    { .dataOffset = 175484, .properties = 1, .width = 104, .height = 21 },    /* text_hide_date@A3, 1 */
    { .dataOffset = 179852, .properties = 1, .width = 92, .height = 21 },    /* text_hide_date@A4, 1 */
    { .dataOffset = 183716, .properties = 1, .width = 103, .height = 21 },    /* text_hide_date@A5, 1 */
    { .dataOffset = 188042, .properties = 1, .width = 98, .height = 21 },    /* text_hide_date@A6, 1 */
    { .dataOffset = 192158, .properties = 1, .width = 70, .height = 21 },    /* text_hide_date@A7, 1 */
    { .dataOffset = 195098, .properties = 1, .width = 86, .height = 21 },    /* text_hide_date@A8, 1 */
    { .dataOffset = 198710, .properties = 1, .width = 69, .height = 21 },    /* text_hide_date@A9, 1 */
    { .dataOffset = 201608, .properties = 1, .width = 89, .height = 21 },    /* text_hide_time@A0, 1 */
    { .dataOffset = 205346, .properties = 1, .width = 103, .height = 21 },    /* text_hide_time@A1, 1 */
    { .dataOffset = 209672, .properties = 1, .width = 116, .height = 21 },    /* text_hide_time@A2, 1 */
    { .dataOffset = 214544, .properties = 1, .width = 98, .height = 21 },    /* text_hide_time@A3, 1 */
    { .dataOffset = 218660, .properties = 1, .width = 105, .height = 21 },    /* text_hide_time@A4, 1 */
    { .dataOffset = 223070, .properties = 1, .width = 130, .height = 21 },    /* text_hide_time@A5, 1 */
    { .dataOffset = 228530, .properties = 1, .width = 119, .height = 21 },    /* text_hide_time@A6, 1 */
    { .dataOffset = 233528, .properties = 1, .width = 70, .height = 21 },    /* text_hide_time@A7, 1 */
    { .dataOffset = 236468, .properties = 1, .width = 94, .height = 21 },    /* text_hide_time@A8, 1 */
    { .dataOffset = 240416, .properties = 1, .width = 85, .height = 21 },    /* text_hide_time@A9, 1 */
    { .dataOffset = 243986, .properties = 0, .width = 13, .height = 21 },    /* text_id, 0 */
    { .dataOffset = 244532, .properties = 1, .width = 76, .height = 21 },    /* text_interval@A0, 1 */
    { .dataOffset = 247724, .properties = 1, .width = 76, .height = 21 },    /* text_interval@A1, 1 */
    { .dataOffset = 250916, .properties = 1, .width = 80, .height = 21 },    /* text_interval@A2, 1 */
    { .dataOffset = 254276, .properties = 1, .width = 89, .height = 21 },    /* text_interval@A3, 1 */
    { .dataOffset = 258014, .properties = 1, .width = 85, .height = 21 },    /* text_interval@A4, 1 */
    { .dataOffset = 261584, .properties = 1, .width = 89, .height = 21 },    /* text_interval@A5, 1 */
    { .dataOffset = 265322, .properties = 1, .width = 97, .height = 21 },    /* text_interval@A6, 1 */
    { .dataOffset = 269396, .properties = 1, .width = 58, .height = 21 },    /* text_interval@A7, 1 */
    { .dataOffset = 271832, .properties = 1, .width = 40, .height = 21 },    /* text_interval@A8, 1 */
    { .dataOffset = 273512, .properties = 1, .width = 38, .height = 21 },    /* text_interval@A9, 1 */
    { .dataOffset = 275108, .properties = 0, .width = 52, .height = 21 },    /* text_italian, 0 */
    { .dataOffset = 277292, .properties = 0, .width = 50, .height = 21 },    /* text_japanese, 0 */
    { .dataOffset = 279392, .properties = 0, .width = 46, .height = 21 },    /* text_korean, 0 */
    { .dataOffset = 281324, .properties = 1, .width = 70, .height = 21 },    /* text_language@A0, 1 */
    { .dataOffset = 284264, .properties = 1, .width = 31, .height = 21 },    /* text_language@A1, 1 */
    { .dataOffset = 285566, .properties = 1, .width = 59, .height = 21 },    /* text_language@A2, 1 */
    { .dataOffset = 288044, .properties = 1, .width = 52, .height = 21 },    /* text_language@A3, 1 */
    { .dataOffset = 290228, .properties = 1, .width = 48, .height = 21 },    /* text_language@A4, 1 */
    { .dataOffset = 292244, .properties = 1, .width = 47, .height = 21 },    /* text_language@A5, 1 */
    { .dataOffset = 294218, .properties = 1, .width = 40, .height = 21 },    /* text_language@A6, 1 */
    { .dataOffset = 295898, .properties = 1, .width = 35, .height = 21 },    /* text_language@A7, 1 */
    { .dataOffset = 297368, .properties = 1, .width = 35, .height = 21 },    /* text_language@A8, 1 */
    { .dataOffset = 298838, .properties = 1, .width = 29, .height = 21 },    /* text_language@A9, 1 */
    { .dataOffset = 300056, .properties = 1, .width = 120, .height = 21 },    /* text_max_data_points@A0, 1 */
    { .dataOffset = 305096, .properties = 1, .width = 125, .height = 21 },    /* text_max_data_points@A1, 1 */
    { .dataOffset = 310346, .properties = 1, .width = 131, .height = 21 },    /* text_max_data_points@A2, 1 */
    { .dataOffset = 315848, .properties = 1, .width = 174, .height = 21 },    /* text_max_data_points@A3, 1 */
    { .dataOffset = 323156, .properties = 1, .width = 156, .height = 21 },    /* text_max_data_points@A4, 1 */
    { .dataOffset = 329708, .properties = 1, .width = 219, .height = 21 },    /* text_max_data_points@A5, 1 */
    { .dataOffset = 338906, .properties = 1, .width = 96, .height = 21 },    /* text_max_data_points@A6, 1 */
    { .dataOffset = 342938, .properties = 1, .width = 108, .height = 21 },    /* text_max_data_points@A7, 1 */
    { .dataOffset = 347474, .properties = 1, .width = 132, .height = 21 },    /* text_max_data_points@A8, 1 */
    { .dataOffset = 353018, .properties = 1, .width = 138, .height = 21 },    /* text_max_data_points@A9, 1 */
    { .dataOffset = 358814, .properties = 0, .width = 61, .height = 21 },    /* text_russian, 0 */
    { .dataOffset = 361376, .properties = 1, .width = 35, .height = 21 },    /* text_save@A0, 1 */
    { .dataOffset = 362846, .properties = 1, .width = 59, .height = 21 },    /* text_save@A1, 1 */
    { .dataOffset = 365324, .properties = 1, .width = 45, .height = 21 },    /* text_save@A2, 1 */
    { .dataOffset = 367214, .properties = 1, .width = 92, .height = 21 },    /* text_save@A3, 1 */
    { .dataOffset = 371078, .properties = 1, .width = 45, .height = 21 },    /* text_save@A4, 1 */
    { .dataOffset = 372968, .properties = 1, .width = 53, .height = 21 },    /* text_save@A5, 1 */
    { .dataOffset = 375194, .properties = 1, .width = 63, .height = 21 },    /* text_save@A6, 1 */
    { .dataOffset = 377840, .properties = 1, .width = 17, .height = 21 },    /* text_save@A7, 1 */
    { .dataOffset = 378554, .properties = 1, .width = 43, .height = 21 },    /* text_save@A8, 1 */
    { .dataOffset = 380360, .properties = 1, .width = 65, .height = 21 },    /* text_save@A9, 1 */
    { .dataOffset = 383090, .properties = 1, .width = 141, .height = 21 },    /* text_save_rec@A0, 1 */
    { .dataOffset = 389012, .properties = 1, .width = 120, .height = 21 },    /* text_save_rec@A1, 1 */
    { .dataOffset = 394052, .properties = 1, .width = 141, .height = 21 },    /* text_save_rec@A2, 1 */
    { .dataOffset = 399974, .properties = 1, .width = 154, .height = 21 },    /* text_save_rec@A3, 1 */
    { .dataOffset = 406442, .properties = 1, .width = 129, .height = 21 },    /* text_save_rec@A4, 1 */
    { .dataOffset = 411860, .properties = 1, .width = 133, .height = 21 },    /* text_save_rec@A5, 1 */
    { .dataOffset = 417446, .properties = 1, .width = 170, .height = 21 },    /* text_save_rec@A6, 1 */
    { .dataOffset = 424586, .properties = 1, .width = 71, .height = 21 },    /* text_save_rec@A7, 1 */
    { .dataOffset = 427568, .properties = 1, .width = 104, .height = 21 },    /* text_save_rec@A8, 1 */
    { .dataOffset = 431936, .properties = 1, .width = 85, .height = 21 },    /* text_save_rec@A9, 1 */
    { .dataOffset = 435506, .properties = 1, .width = 43, .height = 21 },    /* text_saved@A0, 1 */
    { .dataOffset = 437312, .properties = 1, .width = 86, .height = 21 },    /* text_saved@A1, 1 */
    { .dataOffset = 440924, .properties = 1, .width = 87, .height = 21 },    /* text_saved@A2, 1 */
    { .dataOffset = 444578, .properties = 1, .width = 44, .height = 21 },    /* text_saved@A3, 1 */
    { .dataOffset = 446426, .properties = 1, .width = 71, .height = 21 },    /* text_saved@A4, 1 */
    { .dataOffset = 449408, .properties = 1, .width = 54, .height = 21 },    /* text_saved@A5, 1 */
    { .dataOffset = 451676, .properties = 1, .width = 83, .height = 21 },    /* text_saved@A6, 1 */
    { .dataOffset = 455162, .properties = 1, .width = 35, .height = 21 },    /* text_saved@A7, 1 */
    { .dataOffset = 456632, .properties = 1, .width = 35, .height = 21 },    /* text_saved@A8, 1 */
    { .dataOffset = 458102, .properties = 1, .width = 31, .height = 21 },    /* text_saved@A9, 1 */
    { .dataOffset = 459404, .properties = 1, .width = 83, .height = 21 },    /* text_show_date@A0, 1 */
    { .dataOffset = 462890, .properties = 1, .width = 119, .height = 21 },    /* text_show_date@A1, 1 */
    { .dataOffset = 467888, .properties = 1, .width = 111, .height = 21 },    /* text_show_date@A2, 1 */
    { .dataOffset = 472550, .properties = 1, .width = 83, .height = 21 },    /* text_show_date@A3, 1 */
    { .dataOffset = 476036, .properties = 1, .width = 93, .height = 21 },    /* text_show_date@A4, 1 */
    { .dataOffset = 479942, .properties = 1, .width = 87, .height = 21 },    /* text_show_date@A5, 1 */
    { .dataOffset = 483596, .properties = 1, .width = 107, .height = 21 },    /* text_show_date@A6, 1 */
    { .dataOffset = 488090, .properties = 1, .width = 70, .height = 21 },    /* text_show_date@A7, 1 */
    { .dataOffset = 491030, .properties = 1, .width = 71, .height = 21 },    /* text_show_date@A8, 1 */
    { .dataOffset = 494012, .properties = 1, .width = 102, .height = 21 },    /* text_show_date@A9, 1 */
    { .dataOffset = 498296, .properties = 1, .width = 87, .height = 21 },    /* text_show_time@A0, 1 */
    { .dataOffset = 501950, .properties = 1, .width = 99, .height = 21 },    /* text_show_time@A1, 1 */
    { .dataOffset = 506108, .properties = 1, .width = 91, .height = 21 },    /* text_show_time@A2, 1 */
    { .dataOffset = 509930, .properties = 1, .width = 101, .height = 21 },    /* text_show_time@A3, 1 */
    { .dataOffset = 514172, .properties = 1, .width = 106, .height = 21 },    /* text_show_time@A4, 1 */
    { .dataOffset = 518624, .properties = 1, .width = 106, .height = 21 },    /* text_show_time@A5, 1 */
    { .dataOffset = 523076, .properties = 1, .width = 120, .height = 21 },    /* text_show_time@A6, 1 */
    { .dataOffset = 528116, .properties = 1, .width = 70, .height = 21 },    /* text_show_time@A7, 1 */
    { .dataOffset = 531056, .properties = 1, .width = 122, .height = 21 },    /* text_show_time@A8, 1 */
    { .dataOffset = 536180, .properties = 1, .width = 102, .height = 21 },    /* text_show_time@A9, 1 */
    { .dataOffset = 540464, .properties = 0, .width = 56, .height = 21 },    /* text_spanish, 0 */
    { .dataOffset = 542816, .properties = 1, .width = 37, .height = 21 },    /* text_units@A0, 1 */
    { .dataOffset = 544370, .properties = 1, .width = 70, .height = 21 },    /* text_units@A1, 1 */
    { .dataOffset = 547310, .properties = 1, .width = 65, .height = 21 },    /* text_units@A2, 1 */
    { .dataOffset = 550040, .properties = 1, .width = 45, .height = 21 },    /* text_units@A3, 1 */
    { .dataOffset = 551930, .properties = 1, .width = 68, .height = 21 },    /* text_units@A4, 1 */
    { .dataOffset = 554786, .properties = 1, .width = 37, .height = 21 },    /* text_units@A5, 1 */
    { .dataOffset = 556340, .properties = 1, .width = 56, .height = 21 },    /* text_units@A6, 1 */
    { .dataOffset = 558692, .properties = 1, .width = 35, .height = 21 },    /* text_units@A7, 1 */
    { .dataOffset = 560162, .properties = 1, .width = 35, .height = 21 },    /* text_units@A8, 1 */
    { .dataOffset = 561632, .properties = 1, .width = 29, .height = 21 },    /* text_units@A9, 1 */
    { .dataOffset = 562850, .properties = 1, .width = 86, .height = 23 },    /* title_brightness@A0, 1 */
    { .dataOffset = 566806, .properties = 1, .width = 87, .height = 23 },    /* title_brightness@A1, 1 */
    { .dataOffset = 570808, .properties = 1, .width = 75, .height = 23 },    /* title_brightness@A2, 1 */
    { .dataOffset = 574258, .properties = 1, .width = 90, .height = 23 },    /* title_brightness@A3, 1 */
    { .dataOffset = 578398, .properties = 1, .width = 40, .height = 23 },    /* title_brightness@A4, 1 */
    { .dataOffset = 580238, .properties = 1, .width = 90, .height = 23 },    /* title_brightness@A5, 1 */
    { .dataOffset = 584378, .properties = 1, .width = 71, .height = 23 },    /* title_brightness@A6, 1 */
    { .dataOffset = 587644, .properties = 1, .width = 39, .height = 23 },    /* title_brightness@A7, 1 */
    { .dataOffset = 589438, .properties = 1, .width = 48, .height = 23 },    /* title_brightness@A8, 1 */
    { .dataOffset = 591646, .properties = 1, .width = 32, .height = 23 },    /* title_brightness@A9, 1 */
    { .dataOffset = 593118, .properties = 1, .width = 128, .height = 23 },    /* title_calibrate_touch@A0, 1 */
    { .dataOffset = 599006, .properties = 1, .width = 134, .height = 23 },    /* title_calibrate_touch@A1, 1 */
    { .dataOffset = 605170, .properties = 1, .width = 155, .height = 23 },    /* title_calibrate_touch@A2, 1 */
    { .dataOffset = 612300, .properties = 1, .width = 132, .height = 23 },    /* title_calibrate_touch@A3, 1 */
    { .dataOffset = 618372, .properties = 1, .width = 128, .height = 23 },    /* title_calibrate_touch@A4, 1 */
    { .dataOffset = 624260, .properties = 1, .width = 107, .height = 23 },    /* title_calibrate_touch@A5, 1 */
    { .dataOffset = 629182, .properties = 1, .width = 266, .height = 23 },    /* title_calibrate_touch@A6, 1 */
    { .dataOffset = 641418, .properties = 1, .width = 81, .height = 23 },    /* title_calibrate_touch@A7, 1 */
    { .dataOffset = 645144, .properties = 1, .width = 190, .height = 23 },    /* title_calibrate_touch@A8, 1 */
    { .dataOffset = 653884, .properties = 1, .width = 74, .height = 23 },    /* title_calibrate_touch@A9, 1 */
    { .dataOffset = 657288, .properties = 1, .width = 81, .height = 23 },    /* title_date_time@A0, 1 */
    { .dataOffset = 661014, .properties = 1, .width = 86, .height = 23 },    /* title_date_time@A1, 1 */
    { .dataOffset = 664970, .properties = 1, .width = 119, .height = 23 },    /* title_date_time@A2, 1 */
    { .dataOffset = 670444, .properties = 1, .width = 91, .height = 23 },    /* title_date_time@A3, 1 */
    { .dataOffset = 674630, .properties = 1, .width = 93, .height = 23 },    /* title_date_time@A4, 1 */
    { .dataOffset = 678908, .properties = 1, .width = 71, .height = 23 },    /* title_date_time@A5, 1 */
    { .dataOffset = 682174, .properties = 1, .width = 104, .height = 23 },    /* title_date_time@A6, 1 */
    { .dataOffset = 686958, .properties = 1, .width = 84, .height = 23 },    /* title_date_time@A7, 1 */
    { .dataOffset = 690822, .properties = 1, .width = 84, .height = 23 },    /* title_date_time@A8, 1 */
    { .dataOffset = 694686, .properties = 1, .width = 79, .height = 23 },    /* title_date_time@A9, 1 */
    { .dataOffset = 698320, .properties = 0, .width = 15, .height = 23 },    /* title_id, 0 */
    { .dataOffset = 699010, .properties = 1, .width = 80, .height = 23 },    /* title_language@A0, 1 */
    { .dataOffset = 702690, .properties = 1, .width = 35, .height = 23 },    /* title_language@A1, 1 */
    { .dataOffset = 704300, .properties = 1, .width = 67, .height = 23 },    /* title_language@A2, 1 */
    { .dataOffset = 707382, .properties = 1, .width = 59, .height = 23 },    /* title_language@A3, 1 */
    { .dataOffset = 710096, .properties = 1, .width = 55, .height = 23 },    /* title_language@A4, 1 */
    { .dataOffset = 712626, .properties = 1, .width = 53, .height = 23 },    /* title_language@A5, 1 */
    { .dataOffset = 715064, .properties = 1, .width = 45, .height = 23 },    /* title_language@A6, 1 */
    { .dataOffset = 717134, .properties = 1, .width = 39, .height = 23 },    /* title_language@A7, 1 */
    { .dataOffset = 718928, .properties = 1, .width = 39, .height = 23 },    /* title_language@A8, 1 */
    { .dataOffset = 720722, .properties = 1, .width = 32, .height = 23 },    /* title_language@A9, 1 */
    { .dataOffset = 722194, .properties = 1, .width = 122, .height = 23 },    /* title_measurements@A0, 1 */
    { .dataOffset = 727806, .properties = 1, .width = 85, .height = 23 },    /* title_measurements@A1, 1 */
    { .dataOffset = 731716, .properties = 1, .width = 94, .height = 23 },    /* title_measurements@A2, 1 */
    { .dataOffset = 736040, .properties = 1, .width = 112, .height = 23 },    /* title_measurements@A3, 1 */
    { .dataOffset = 741192, .properties = 1, .width = 69, .height = 23 },    /* title_measurements@A4, 1 */
    { .dataOffset = 744366, .properties = 1, .width = 55, .height = 23 },    /* title_measurements@A5, 1 */
    { .dataOffset = 746896, .properties = 1, .width = 96, .height = 23 },    /* title_measurements@A6, 1 */
    { .dataOffset = 751312, .properties = 1, .width = 40, .height = 23 },    /* title_measurements@A7, 1 */
    { .dataOffset = 753152, .properties = 1, .width = 38, .height = 23 },    /* title_measurements@A8, 1 */
    { .dataOffset = 754900, .properties = 1, .width = 33, .height = 23 },    /* title_measurements@A9, 1 */
    { .dataOffset = 756418, .properties = 1, .width = 91, .height = 23 },    /* title_recordings@A0, 1 */
    { .dataOffset = 760604, .properties = 1, .width = 78, .height = 23 },    /* title_recordings@A1, 1 */
    { .dataOffset = 764192, .properties = 1, .width = 94, .height = 23 },    /* title_recordings@A2, 1 */
    { .dataOffset = 768516, .properties = 1, .width = 134, .height = 23 },    /* title_recordings@A3, 1 */
    { .dataOffset = 774680, .properties = 1, .width = 102, .height = 23 },    /* title_recordings@A4, 1 */
    { .dataOffset = 779372, .properties = 1, .width = 105, .height = 23 },    /* title_recordings@A5, 1 */
    { .dataOffset = 784202, .properties = 1, .width = 62, .height = 23 },    /* title_recordings@A6, 1 */
    { .dataOffset = 787054, .properties = 1, .width = 39, .height = 23 },    /* title_recordings@A7, 1 */
    { .dataOffset = 788848, .properties = 1, .width = 39, .height = 23 },    /* title_recordings@A8, 1 */
    { .dataOffset = 790642, .properties = 1, .width = 35, .height = 23 },    /* title_recordings@A9, 1 */
    { .dataOffset = 792252, .properties = 1, .width = 67, .height = 23 },    /* title_settings@A0, 1 */
    { .dataOffset = 795334, .properties = 1, .width = 93, .height = 23 },    /* title_settings@A1, 1 */
    { .dataOffset = 799612, .properties = 1, .width = 109, .height = 23 },    /* title_settings@A2, 1 */
    { .dataOffset = 804626, .properties = 1, .width = 94, .height = 23 },    /* title_settings@A3, 1 */
    { .dataOffset = 808950, .properties = 1, .width = 114, .height = 23 },    /* title_settings@A4, 1 */
    { .dataOffset = 814194, .properties = 1, .width = 105, .height = 23 },    /* title_settings@A5, 1 */
    { .dataOffset = 819024, .properties = 1, .width = 98, .height = 23 },    /* title_settings@A6, 1 */
    { .dataOffset = 823532, .properties = 1, .width = 39, .height = 23 },    /* title_settings@A7, 1 */
    { .dataOffset = 825326, .properties = 1, .width = 38, .height = 23 },    /* title_settings@A8, 1 */
    { .dataOffset = 827074, .properties = 1, .width = 33, .height = 23 },    /* title_settings@A9, 1 */
    { .dataOffset = 828592, .properties = 1, .width = 39, .height = 23 },    /* title_start@A0, 1 */
    { .dataOffset = 830386, .properties = 1, .width = 39, .height = 23 },    /* title_start@A1, 1 */
    { .dataOffset = 832180, .properties = 1, .width = 78, .height = 23 },    /* title_start@A2, 1 */
    { .dataOffset = 835768, .properties = 1, .width = 100, .height = 23 },    /* title_start@A3, 1 */
    { .dataOffset = 840368, .properties = 1, .width = 71, .height = 23 },    /* title_start@A4, 1 */
    { .dataOffset = 843634, .properties = 1, .width = 42, .height = 23 },    /* title_start@A5, 1 */
    { .dataOffset = 845566, .properties = 1, .width = 63, .height = 23 },    /* title_start@A6, 1 */
    { .dataOffset = 848464, .properties = 1, .width = 39, .height = 23 },    /* title_start@A7, 1 */
    { .dataOffset = 850258, .properties = 1, .width = 50, .height = 23 },    /* title_start@A8, 1 */
    { .dataOffset = 852558, .properties = 1, .width = 72, .height = 23 },    /* title_start@A9, 1 */
    { .dataOffset = 855870, .properties = 1, .width = 37, .height = 23 },    /* title_stop@A0, 1 */
    { .dataOffset = 857572, .properties = 1, .width = 37, .height = 23 },    /* title_stop@A1, 1 */
    { .dataOffset = 859274, .properties = 1, .width = 75, .height = 23 },    /* title_stop@A2, 1 */
    { .dataOffset = 862724, .properties = 1, .width = 56, .height = 23 },    /* title_stop@A3, 1 */
    { .dataOffset = 865300, .properties = 1, .width = 43, .height = 23 },    /* title_stop@A4, 1 */
    { .dataOffset = 867278, .properties = 1, .width = 71, .height = 23 },    /* title_stop@A5, 1 */
    { .dataOffset = 870544, .properties = 1, .width = 91, .height = 23 },    /* title_stop@A6, 1 */
    { .dataOffset = 874730, .properties = 1, .width = 18, .height = 23 },    /* title_stop@A7, 1 */
    { .dataOffset = 875558, .properties = 1, .width = 50, .height = 23 },    /* title_stop@A8, 1 */
    { .dataOffset = 877858, .properties = 1, .width = 53, .height = 23 },    /* title_stop@A9, 1 */
};

const uint8_t maxProperty[FS_MAX_FILE_PROPERTIES] =
{
    10, 2, 2, 2, 
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

    *p_dataLocation = 0;

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
