#include "fs_file_search.h"

#define FS_FILE_INFO_SIZE 9
#define FS_FILE_DUMMY 0xFFFFFFFFU

const fs_file_info_s fs_file_infos[] =
{                                                                      /* filename, fileproperty, datalocation */
    { .dataOffset = 60, .properties = 0, .width = 30, .height = 30 },    /* Button_minus, 0, 0 - SD */
    { .dataOffset = 1860, .properties = 0, .width = 80, .height = 30 },    /* Play, 0, 0 - SD */
    { .dataOffset = 6660, .properties = 0, .width = 80, .height = 30 },    /* Play_Pressed, 0, 0 - SD */
    { .dataOffset = 11460, .properties = 0, .width = 30, .height = 30 },    /* Button_plus, 0, 0 - SD */
    { .dataOffset = 13260, .properties = 0, .width = 80, .height = 30 },    /* Stop, 0, 0 - SD */
    { .dataOffset = 18060, .properties = 0, .width = 80, .height = 30 },    /* Stop_Pressed, 0, 0 - SD */
    { .dataOffset = 22860, .properties = 0, .width = 6, .height = 12 },    /* icon_Arrow-Down-Small, 0, 0 - SD */
    { .dataOffset = 23004, .properties = 0, .width = 6, .height = 12 },    /* icon_Arrow-Up-Small, 0, 0 - SD */
    { .dataOffset = 23148, .properties = 0, .width = 45, .height = 38 },    /* icon_back, 0, 0 - SD */
    { .dataOffset = 26568, .properties = 12, .width = 22, .height = 22 },    /* icon_Bullseye@C0_D0, 1100, 0 - SD */
    { .dataOffset = 27536, .properties = 12, .width = 22, .height = 22 },    /* icon_Bullseye@C0_D1, 1100, 0 - SD */
    { .dataOffset = 28504, .properties = 12, .width = 22, .height = 22 },    /* icon_Bullseye@C1_D0, 1100, 0 - SD */
    { .dataOffset = 29472, .properties = 12, .width = 22, .height = 22 },    /* icon_Bullseye@C1_D1, 1100, 0 - SD */
    { .dataOffset = 30440, .properties = 0, .width = 18, .height = 18 },    /* icon_Clock, 0, 0 - SD */
    { .dataOffset = 31088, .properties = 4, .width = 22, .height = 17 },    /* icon_Data@C0, 100, 0 - SD */
    { .dataOffset = 31836, .properties = 4, .width = 22, .height = 17 },    /* icon_Data@C1, 100, 0 - SD */
    { .dataOffset = 32584, .properties = 0, .width = 22, .height = 20 },    /* icon_display, 0, 0 - SD */
    { .dataOffset = 33464, .properties = 4, .width = 20, .height = 20 },    /* icon_Focus@C0, 100, 0 - SD */
    { .dataOffset = 34264, .properties = 4, .width = 20, .height = 20 },    /* icon_Focus@C1, 100, 0 - SD */
    { .dataOffset = 35064, .properties = 4, .width = 20, .height = 20 },    /* icon_Gear@C0, 100, 0 - SD */
    { .dataOffset = 35864, .properties = 4, .width = 20, .height = 20 },    /* icon_Gear@C1, 100, 0 - SD */
    { .dataOffset = 36664, .properties = 4, .width = 20, .height = 23 },    /* icon_Home@C0, 100, 0 - SD */
    { .dataOffset = 37584, .properties = 4, .width = 20, .height = 23 },    /* icon_Home@C1, 100, 0 - SD */
    { .dataOffset = 38504, .properties = 0, .width = 22, .height = 22 },    /* icon_language, 0, 0 - SD */
    { .dataOffset = 39472, .properties = 0, .width = 16, .height = 4 },    /* icon_minus, 0, 0 - SD */
    { .dataOffset = 39600, .properties = 0, .width = 18, .height = 20 },    /* icon_pane_Agenda, 0, 0 - SD */
    { .dataOffset = 40320, .properties = 0, .width = 18, .height = 18 },    /* icon_pane_Clock, 0, 0 - SD */
    { .dataOffset = 40968, .properties = 0, .width = 16, .height = 16 },    /* icon_plus, 0, 0 - SD */
    { .dataOffset = 41480, .properties = 0, .width = 22, .height = 18 },    /* icon_Pulse, 0, 0 - SD */
    { .dataOffset = 42272, .properties = 0, .width = 24, .height = 24 },    /* icon_Scroll-down, 0, 0 - SD */
    { .dataOffset = 43424, .properties = 0, .width = 24, .height = 24 },    /* icon_Scroll-up, 0, 0 - SD */
    { .dataOffset = 44576, .properties = 0, .width = 20, .height = 20 },    /* icon_Slider_knob, 0, 0 - SD */
    { .dataOffset = 45376, .properties = 4, .width = 20, .height = 20 },    /* icon_Sliders@C0, 100, 0 - SD */
    { .dataOffset = 46176, .properties = 4, .width = 20, .height = 20 },    /* icon_Sliders@C1, 100, 0 - SD */
    { .dataOffset = 46976, .properties = 4, .width = 50, .height = 22 },    /* icon_Switch@C0, 100, 0 - SD */
    { .dataOffset = 49176, .properties = 4, .width = 50, .height = 22 },    /* icon_Switch@C1, 100, 0 - SD */
    { .dataOffset = 51376, .properties = 0, .width = 13, .height = 25 },    /* icon_thermometer, 0, 0 - SD */
    { .dataOffset = 52026, .properties = 0, .width = 18, .height = 20 },    /* icon_Trash, 0, 0 - SD */
    { .dataOffset = 52746, .properties = 0, .width = 128, .height = 128 },    /* IRL_Logo 128, 0, 0 - SD */
    { .dataOffset = 85514, .properties = 0, .width = 48, .height = 48 },    /* IRL_Logo_48, 0, 0 - SD */
    { .dataOffset = 90122, .properties = 4, .width = 19, .height = 19 },    /* Radio-Button@C0, 100, 0 - SD */
    { .dataOffset = 90844, .properties = 4, .width = 19, .height = 19 },    /* Radio-Button@C1, 100, 0 - SD */
    { .dataOffset = 91566, .properties = 0, .width = 33, .height = 21 },    /* text_chinese_sim, 0, 0 - SD */
    { .dataOffset = 92952, .properties = 1, .width = 72, .height = 21 },    /* text_date_time@A0, 1, 0 - SD */
    { .dataOffset = 95976, .properties = 1, .width = 76, .height = 21 },    /* text_date_time@A1, 1, 0 - SD */
    { .dataOffset = 99168, .properties = 1, .width = 106, .height = 21 },    /* text_date_time@A2, 1, 0 - SD */
    { .dataOffset = 103620, .properties = 1, .width = 80, .height = 21 },    /* text_date_time@A3, 1, 0 - SD */
    { .dataOffset = 106980, .properties = 1, .width = 82, .height = 21 },    /* text_date_time@A4, 1, 0 - SD */
    { .dataOffset = 110424, .properties = 1, .width = 63, .height = 21 },    /* text_date_time@A5, 1, 0 - SD */
    { .dataOffset = 113070, .properties = 1, .width = 92, .height = 21 },    /* text_date_time@A6, 1, 0 - SD */
    { .dataOffset = 116934, .properties = 1, .width = 74, .height = 21 },    /* text_date_time@A7, 1, 0 - SD */
    { .dataOffset = 120042, .properties = 1, .width = 75, .height = 21 },    /* text_date_time@A8, 1, 0 - SD */
    { .dataOffset = 123192, .properties = 1, .width = 70, .height = 21 },    /* text_date_time@A9, 1, 0 - SD */
    { .dataOffset = 126132, .properties = 0, .width = 16, .height = 21 },    /* text_deg_cel, 0, 0 - SD */
    { .dataOffset = 126804, .properties = 0, .width = 15, .height = 21 },    /* text_deg_far, 0, 0 - SD */
    { .dataOffset = 127434, .properties = 1, .width = 52, .height = 21 },    /* text_display@A0, 1, 0 - SD */
    { .dataOffset = 129618, .properties = 1, .width = 94, .height = 21 },    /* text_display@A1, 1, 0 - SD */
    { .dataOffset = 133566, .properties = 1, .width = 48, .height = 21 },    /* text_display@A2, 1, 0 - SD */
    { .dataOffset = 135582, .properties = 1, .width = 57, .height = 21 },    /* text_display@A3, 1, 0 - SD */
    { .dataOffset = 137976, .properties = 1, .width = 56, .height = 21 },    /* text_display@A4, 1, 0 - SD */
    { .dataOffset = 140328, .properties = 1, .width = 55, .height = 21 },    /* text_display@A5, 1, 0 - SD */
    { .dataOffset = 142638, .properties = 1, .width = 66, .height = 21 },    /* text_display@A6, 1, 0 - SD */
    { .dataOffset = 145410, .properties = 1, .width = 34, .height = 21 },    /* text_display@A7, 1, 0 - SD */
    { .dataOffset = 146838, .properties = 1, .width = 33, .height = 21 },    /* text_display@A8, 1, 0 - SD */
    { .dataOffset = 148224, .properties = 1, .width = 29, .height = 21 },    /* text_display@A9, 1, 0 - SD */
    { .dataOffset = 149442, .properties = 0, .width = 82, .height = 21 },    /* text_dutch, 0, 0 - SD */
    { .dataOffset = 152886, .properties = 0, .width = 51, .height = 21 },    /* text_english, 0, 0 - SD */
    { .dataOffset = 155028, .properties = 0, .width = 61, .height = 21 },    /* text_french, 0, 0 - SD */
    { .dataOffset = 157590, .properties = 0, .width = 58, .height = 21 },    /* text_german, 0, 0 - SD */
    { .dataOffset = 160026, .properties = 0, .width = 10, .height = 21 },    /* text_hashtag, 0, 0 - SD */
    { .dataOffset = 160446, .properties = 1, .width = 85, .height = 21 },    /* text_hide_date@A0, 1, 0 - SD */
    { .dataOffset = 164016, .properties = 1, .width = 124, .height = 21 },    /* text_hide_date@A1, 1, 0 - SD */
    { .dataOffset = 169224, .properties = 1, .width = 150, .height = 21 },    /* text_hide_date@A2, 1, 0 - SD */
    { .dataOffset = 175524, .properties = 1, .width = 104, .height = 21 },    /* text_hide_date@A3, 1, 0 - SD */
    { .dataOffset = 179892, .properties = 1, .width = 92, .height = 21 },    /* text_hide_date@A4, 1, 0 - SD */
    { .dataOffset = 183756, .properties = 1, .width = 103, .height = 21 },    /* text_hide_date@A5, 1, 0 - SD */
    { .dataOffset = 188082, .properties = 1, .width = 98, .height = 21 },    /* text_hide_date@A6, 1, 0 - SD */
    { .dataOffset = 192198, .properties = 1, .width = 70, .height = 21 },    /* text_hide_date@A7, 1, 0 - SD */
    { .dataOffset = 195138, .properties = 1, .width = 86, .height = 21 },    /* text_hide_date@A8, 1, 0 - SD */
    { .dataOffset = 198750, .properties = 1, .width = 69, .height = 21 },    /* text_hide_date@A9, 1, 0 - SD */
    { .dataOffset = 201648, .properties = 1, .width = 89, .height = 21 },    /* text_hide_time@A0, 1, 0 - SD */
    { .dataOffset = 205386, .properties = 1, .width = 103, .height = 21 },    /* text_hide_time@A1, 1, 0 - SD */
    { .dataOffset = 209712, .properties = 1, .width = 116, .height = 21 },    /* text_hide_time@A2, 1, 0 - SD */
    { .dataOffset = 214584, .properties = 1, .width = 98, .height = 21 },    /* text_hide_time@A3, 1, 0 - SD */
    { .dataOffset = 218700, .properties = 1, .width = 105, .height = 21 },    /* text_hide_time@A4, 1, 0 - SD */
    { .dataOffset = 223110, .properties = 1, .width = 130, .height = 21 },    /* text_hide_time@A5, 1, 0 - SD */
    { .dataOffset = 228570, .properties = 1, .width = 119, .height = 21 },    /* text_hide_time@A6, 1, 0 - SD */
    { .dataOffset = 233568, .properties = 1, .width = 70, .height = 21 },    /* text_hide_time@A7, 1, 0 - SD */
    { .dataOffset = 236508, .properties = 1, .width = 94, .height = 21 },    /* text_hide_time@A8, 1, 0 - SD */
    { .dataOffset = 240456, .properties = 1, .width = 85, .height = 21 },    /* text_hide_time@A9, 1, 0 - SD */
    { .dataOffset = 244026, .properties = 0, .width = 13, .height = 21 },    /* text_id, 0, 0 - SD */
    { .dataOffset = 244572, .properties = 1, .width = 76, .height = 21 },    /* text_interval@A0, 1, 0 - SD */
    { .dataOffset = 247764, .properties = 1, .width = 76, .height = 21 },    /* text_interval@A1, 1, 0 - SD */
    { .dataOffset = 250956, .properties = 1, .width = 80, .height = 21 },    /* text_interval@A2, 1, 0 - SD */
    { .dataOffset = 254316, .properties = 1, .width = 89, .height = 21 },    /* text_interval@A3, 1, 0 - SD */
    { .dataOffset = 258054, .properties = 1, .width = 85, .height = 21 },    /* text_interval@A4, 1, 0 - SD */
    { .dataOffset = 261624, .properties = 1, .width = 89, .height = 21 },    /* text_interval@A5, 1, 0 - SD */
    { .dataOffset = 265362, .properties = 1, .width = 97, .height = 21 },    /* text_interval@A6, 1, 0 - SD */
    { .dataOffset = 269436, .properties = 1, .width = 58, .height = 21 },    /* text_interval@A7, 1, 0 - SD */
    { .dataOffset = 271872, .properties = 1, .width = 40, .height = 21 },    /* text_interval@A8, 1, 0 - SD */
    { .dataOffset = 273552, .properties = 1, .width = 38, .height = 21 },    /* text_interval@A9, 1, 0 - SD */
    { .dataOffset = 275148, .properties = 0, .width = 52, .height = 21 },    /* text_italian, 0, 0 - SD */
    { .dataOffset = 277332, .properties = 0, .width = 50, .height = 21 },    /* text_japanese, 0, 0 - SD */
    { .dataOffset = 279432, .properties = 0, .width = 46, .height = 21 },    /* text_korean, 0, 0 - SD */
    { .dataOffset = 281364, .properties = 1, .width = 70, .height = 21 },    /* text_language@A0, 1, 0 - SD */
    { .dataOffset = 284304, .properties = 1, .width = 31, .height = 21 },    /* text_language@A1, 1, 0 - SD */
    { .dataOffset = 285606, .properties = 1, .width = 59, .height = 21 },    /* text_language@A2, 1, 0 - SD */
    { .dataOffset = 288084, .properties = 1, .width = 52, .height = 21 },    /* text_language@A3, 1, 0 - SD */
    { .dataOffset = 290268, .properties = 1, .width = 48, .height = 21 },    /* text_language@A4, 1, 0 - SD */
    { .dataOffset = 292284, .properties = 1, .width = 47, .height = 21 },    /* text_language@A5, 1, 0 - SD */
    { .dataOffset = 294258, .properties = 1, .width = 40, .height = 21 },    /* text_language@A6, 1, 0 - SD */
    { .dataOffset = 295938, .properties = 1, .width = 35, .height = 21 },    /* text_language@A7, 1, 0 - SD */
    { .dataOffset = 297408, .properties = 1, .width = 35, .height = 21 },    /* text_language@A8, 1, 0 - SD */
    { .dataOffset = 298878, .properties = 1, .width = 29, .height = 21 },    /* text_language@A9, 1, 0 - SD */
    { .dataOffset = 300096, .properties = 1, .width = 120, .height = 21 },    /* text_max_data_points@A0, 1, 0 - SD */
    { .dataOffset = 305136, .properties = 1, .width = 125, .height = 21 },    /* text_max_data_points@A1, 1, 0 - SD */
    { .dataOffset = 310386, .properties = 1, .width = 131, .height = 21 },    /* text_max_data_points@A2, 1, 0 - SD */
    { .dataOffset = 315888, .properties = 1, .width = 174, .height = 21 },    /* text_max_data_points@A3, 1, 0 - SD */
    { .dataOffset = 323196, .properties = 1, .width = 156, .height = 21 },    /* text_max_data_points@A4, 1, 0 - SD */
    { .dataOffset = 329748, .properties = 1, .width = 219, .height = 21 },    /* text_max_data_points@A5, 1, 0 - SD */
    { .dataOffset = 338946, .properties = 1, .width = 96, .height = 21 },    /* text_max_data_points@A6, 1, 0 - SD */
    { .dataOffset = 342978, .properties = 1, .width = 108, .height = 21 },    /* text_max_data_points@A7, 1, 0 - SD */
    { .dataOffset = 347514, .properties = 1, .width = 132, .height = 21 },    /* text_max_data_points@A8, 1, 0 - SD */
    { .dataOffset = 353058, .properties = 1, .width = 138, .height = 21 },    /* text_max_data_points@A9, 1, 0 - SD */
    { .dataOffset = 358854, .properties = 0, .width = 61, .height = 21 },    /* text_russian, 0, 0 - SD */
    { .dataOffset = 361416, .properties = 1, .width = 35, .height = 21 },    /* text_save@A0, 1, 0 - SD */
    { .dataOffset = 362886, .properties = 1, .width = 59, .height = 21 },    /* text_save@A1, 1, 0 - SD */
    { .dataOffset = 365364, .properties = 1, .width = 45, .height = 21 },    /* text_save@A2, 1, 0 - SD */
    { .dataOffset = 367254, .properties = 1, .width = 92, .height = 21 },    /* text_save@A3, 1, 0 - SD */
    { .dataOffset = 371118, .properties = 1, .width = 45, .height = 21 },    /* text_save@A4, 1, 0 - SD */
    { .dataOffset = 373008, .properties = 1, .width = 53, .height = 21 },    /* text_save@A5, 1, 0 - SD */
    { .dataOffset = 375234, .properties = 1, .width = 63, .height = 21 },    /* text_save@A6, 1, 0 - SD */
    { .dataOffset = 377880, .properties = 1, .width = 17, .height = 21 },    /* text_save@A7, 1, 0 - SD */
    { .dataOffset = 378594, .properties = 1, .width = 43, .height = 21 },    /* text_save@A8, 1, 0 - SD */
    { .dataOffset = 380400, .properties = 1, .width = 65, .height = 21 },    /* text_save@A9, 1, 0 - SD */
    { .dataOffset = 383130, .properties = 1, .width = 141, .height = 21 },    /* text_save_rec@A0, 1, 0 - SD */
    { .dataOffset = 389052, .properties = 1, .width = 120, .height = 21 },    /* text_save_rec@A1, 1, 0 - SD */
    { .dataOffset = 394092, .properties = 1, .width = 141, .height = 21 },    /* text_save_rec@A2, 1, 0 - SD */
    { .dataOffset = 400014, .properties = 1, .width = 154, .height = 21 },    /* text_save_rec@A3, 1, 0 - SD */
    { .dataOffset = 406482, .properties = 1, .width = 129, .height = 21 },    /* text_save_rec@A4, 1, 0 - SD */
    { .dataOffset = 411900, .properties = 1, .width = 133, .height = 21 },    /* text_save_rec@A5, 1, 0 - SD */
    { .dataOffset = 417486, .properties = 1, .width = 170, .height = 21 },    /* text_save_rec@A6, 1, 0 - SD */
    { .dataOffset = 424626, .properties = 1, .width = 71, .height = 21 },    /* text_save_rec@A7, 1, 0 - SD */
    { .dataOffset = 427608, .properties = 1, .width = 104, .height = 21 },    /* text_save_rec@A8, 1, 0 - SD */
    { .dataOffset = 431976, .properties = 1, .width = 85, .height = 21 },    /* text_save_rec@A9, 1, 0 - SD */
    { .dataOffset = 435546, .properties = 1, .width = 43, .height = 21 },    /* text_saved@A0, 1, 0 - SD */
    { .dataOffset = 437352, .properties = 1, .width = 86, .height = 21 },    /* text_saved@A1, 1, 0 - SD */
    { .dataOffset = 440964, .properties = 1, .width = 87, .height = 21 },    /* text_saved@A2, 1, 0 - SD */
    { .dataOffset = 444618, .properties = 1, .width = 44, .height = 21 },    /* text_saved@A3, 1, 0 - SD */
    { .dataOffset = 446466, .properties = 1, .width = 71, .height = 21 },    /* text_saved@A4, 1, 0 - SD */
    { .dataOffset = 449448, .properties = 1, .width = 54, .height = 21 },    /* text_saved@A5, 1, 0 - SD */
    { .dataOffset = 451716, .properties = 1, .width = 83, .height = 21 },    /* text_saved@A6, 1, 0 - SD */
    { .dataOffset = 455202, .properties = 1, .width = 35, .height = 21 },    /* text_saved@A7, 1, 0 - SD */
    { .dataOffset = 456672, .properties = 1, .width = 35, .height = 21 },    /* text_saved@A8, 1, 0 - SD */
    { .dataOffset = 458142, .properties = 1, .width = 31, .height = 21 },    /* text_saved@A9, 1, 0 - SD */
    { .dataOffset = 459444, .properties = 1, .width = 83, .height = 21 },    /* text_show_date@A0, 1, 0 - SD */
    { .dataOffset = 462930, .properties = 1, .width = 119, .height = 21 },    /* text_show_date@A1, 1, 0 - SD */
    { .dataOffset = 467928, .properties = 1, .width = 111, .height = 21 },    /* text_show_date@A2, 1, 0 - SD */
    { .dataOffset = 472590, .properties = 1, .width = 83, .height = 21 },    /* text_show_date@A3, 1, 0 - SD */
    { .dataOffset = 476076, .properties = 1, .width = 93, .height = 21 },    /* text_show_date@A4, 1, 0 - SD */
    { .dataOffset = 479982, .properties = 1, .width = 87, .height = 21 },    /* text_show_date@A5, 1, 0 - SD */
    { .dataOffset = 483636, .properties = 1, .width = 107, .height = 21 },    /* text_show_date@A6, 1, 0 - SD */
    { .dataOffset = 488130, .properties = 1, .width = 70, .height = 21 },    /* text_show_date@A7, 1, 0 - SD */
    { .dataOffset = 491070, .properties = 1, .width = 71, .height = 21 },    /* text_show_date@A8, 1, 0 - SD */
    { .dataOffset = 494052, .properties = 1, .width = 102, .height = 21 },    /* text_show_date@A9, 1, 0 - SD */
    { .dataOffset = 498336, .properties = 1, .width = 87, .height = 21 },    /* text_show_time@A0, 1, 0 - SD */
    { .dataOffset = 501990, .properties = 1, .width = 99, .height = 21 },    /* text_show_time@A1, 1, 0 - SD */
    { .dataOffset = 506148, .properties = 1, .width = 91, .height = 21 },    /* text_show_time@A2, 1, 0 - SD */
    { .dataOffset = 509970, .properties = 1, .width = 101, .height = 21 },    /* text_show_time@A3, 1, 0 - SD */
    { .dataOffset = 514212, .properties = 1, .width = 106, .height = 21 },    /* text_show_time@A4, 1, 0 - SD */
    { .dataOffset = 518664, .properties = 1, .width = 106, .height = 21 },    /* text_show_time@A5, 1, 0 - SD */
    { .dataOffset = 523116, .properties = 1, .width = 120, .height = 21 },    /* text_show_time@A6, 1, 0 - SD */
    { .dataOffset = 528156, .properties = 1, .width = 70, .height = 21 },    /* text_show_time@A7, 1, 0 - SD */
    { .dataOffset = 531096, .properties = 1, .width = 122, .height = 21 },    /* text_show_time@A8, 1, 0 - SD */
    { .dataOffset = 536220, .properties = 1, .width = 102, .height = 21 },    /* text_show_time@A9, 1, 0 - SD */
    { .dataOffset = 540504, .properties = 0, .width = 56, .height = 21 },    /* text_spanish, 0, 0 - SD */
    { .dataOffset = 542856, .properties = 1, .width = 37, .height = 21 },    /* text_units@A0, 1, 0 - SD */
    { .dataOffset = 544410, .properties = 1, .width = 70, .height = 21 },    /* text_units@A1, 1, 0 - SD */
    { .dataOffset = 547350, .properties = 1, .width = 65, .height = 21 },    /* text_units@A2, 1, 0 - SD */
    { .dataOffset = 550080, .properties = 1, .width = 45, .height = 21 },    /* text_units@A3, 1, 0 - SD */
    { .dataOffset = 551970, .properties = 1, .width = 68, .height = 21 },    /* text_units@A4, 1, 0 - SD */
    { .dataOffset = 554826, .properties = 1, .width = 37, .height = 21 },    /* text_units@A5, 1, 0 - SD */
    { .dataOffset = 556380, .properties = 1, .width = 56, .height = 21 },    /* text_units@A6, 1, 0 - SD */
    { .dataOffset = 558732, .properties = 1, .width = 35, .height = 21 },    /* text_units@A7, 1, 0 - SD */
    { .dataOffset = 560202, .properties = 1, .width = 35, .height = 21 },    /* text_units@A8, 1, 0 - SD */
    { .dataOffset = 561672, .properties = 1, .width = 29, .height = 21 },    /* text_units@A9, 1, 0 - SD */
    { .dataOffset = 562890, .properties = 1, .width = 86, .height = 23 },    /* title_brightness@A0, 1, 0 - SD */
    { .dataOffset = 566846, .properties = 1, .width = 87, .height = 23 },    /* title_brightness@A1, 1, 0 - SD */
    { .dataOffset = 570848, .properties = 1, .width = 75, .height = 23 },    /* title_brightness@A2, 1, 0 - SD */
    { .dataOffset = 574298, .properties = 1, .width = 90, .height = 23 },    /* title_brightness@A3, 1, 0 - SD */
    { .dataOffset = 578438, .properties = 1, .width = 40, .height = 23 },    /* title_brightness@A4, 1, 0 - SD */
    { .dataOffset = 580278, .properties = 1, .width = 90, .height = 23 },    /* title_brightness@A5, 1, 0 - SD */
    { .dataOffset = 584418, .properties = 1, .width = 71, .height = 23 },    /* title_brightness@A6, 1, 0 - SD */
    { .dataOffset = 587684, .properties = 1, .width = 39, .height = 23 },    /* title_brightness@A7, 1, 0 - SD */
    { .dataOffset = 589478, .properties = 1, .width = 48, .height = 23 },    /* title_brightness@A8, 1, 0 - SD */
    { .dataOffset = 591686, .properties = 1, .width = 32, .height = 23 },    /* title_brightness@A9, 1, 0 - SD */
    { .dataOffset = 593158, .properties = 1, .width = 128, .height = 23 },    /* title_calibrate_touch@A0, 1, 0 - SD */
    { .dataOffset = 599046, .properties = 1, .width = 134, .height = 23 },    /* title_calibrate_touch@A1, 1, 0 - SD */
    { .dataOffset = 605210, .properties = 1, .width = 155, .height = 23 },    /* title_calibrate_touch@A2, 1, 0 - SD */
    { .dataOffset = 612340, .properties = 1, .width = 132, .height = 23 },    /* title_calibrate_touch@A3, 1, 0 - SD */
    { .dataOffset = 618412, .properties = 1, .width = 128, .height = 23 },    /* title_calibrate_touch@A4, 1, 0 - SD */
    { .dataOffset = 624300, .properties = 1, .width = 107, .height = 23 },    /* title_calibrate_touch@A5, 1, 0 - SD */
    { .dataOffset = 629222, .properties = 1, .width = 266, .height = 23 },    /* title_calibrate_touch@A6, 1, 0 - SD */
    { .dataOffset = 641458, .properties = 1, .width = 81, .height = 23 },    /* title_calibrate_touch@A7, 1, 0 - SD */
    { .dataOffset = 645184, .properties = 1, .width = 190, .height = 23 },    /* title_calibrate_touch@A8, 1, 0 - SD */
    { .dataOffset = 653924, .properties = 1, .width = 74, .height = 23 },    /* title_calibrate_touch@A9, 1, 0 - SD */
    { .dataOffset = 657328, .properties = 1, .width = 81, .height = 23 },    /* title_date_time@A0, 1, 0 - SD */
    { .dataOffset = 661054, .properties = 1, .width = 86, .height = 23 },    /* title_date_time@A1, 1, 0 - SD */
    { .dataOffset = 665010, .properties = 1, .width = 119, .height = 23 },    /* title_date_time@A2, 1, 0 - SD */
    { .dataOffset = 670484, .properties = 1, .width = 91, .height = 23 },    /* title_date_time@A3, 1, 0 - SD */
    { .dataOffset = 674670, .properties = 1, .width = 93, .height = 23 },    /* title_date_time@A4, 1, 0 - SD */
    { .dataOffset = 678948, .properties = 1, .width = 71, .height = 23 },    /* title_date_time@A5, 1, 0 - SD */
    { .dataOffset = 682214, .properties = 1, .width = 104, .height = 23 },    /* title_date_time@A6, 1, 0 - SD */
    { .dataOffset = 686998, .properties = 1, .width = 84, .height = 23 },    /* title_date_time@A7, 1, 0 - SD */
    { .dataOffset = 690862, .properties = 1, .width = 84, .height = 23 },    /* title_date_time@A8, 1, 0 - SD */
    { .dataOffset = 694726, .properties = 1, .width = 79, .height = 23 },    /* title_date_time@A9, 1, 0 - SD */
    { .dataOffset = 698360, .properties = 0, .width = 15, .height = 23 },    /* title_id, 0, 0 - SD */
    { .dataOffset = 699050, .properties = 1, .width = 80, .height = 23 },    /* title_language@A0, 1, 0 - SD */
    { .dataOffset = 702730, .properties = 1, .width = 35, .height = 23 },    /* title_language@A1, 1, 0 - SD */
    { .dataOffset = 704340, .properties = 1, .width = 67, .height = 23 },    /* title_language@A2, 1, 0 - SD */
    { .dataOffset = 707422, .properties = 1, .width = 59, .height = 23 },    /* title_language@A3, 1, 0 - SD */
    { .dataOffset = 710136, .properties = 1, .width = 55, .height = 23 },    /* title_language@A4, 1, 0 - SD */
    { .dataOffset = 712666, .properties = 1, .width = 53, .height = 23 },    /* title_language@A5, 1, 0 - SD */
    { .dataOffset = 715104, .properties = 1, .width = 45, .height = 23 },    /* title_language@A6, 1, 0 - SD */
    { .dataOffset = 717174, .properties = 1, .width = 39, .height = 23 },    /* title_language@A7, 1, 0 - SD */
    { .dataOffset = 718968, .properties = 1, .width = 39, .height = 23 },    /* title_language@A8, 1, 0 - SD */
    { .dataOffset = 720762, .properties = 1, .width = 32, .height = 23 },    /* title_language@A9, 1, 0 - SD */
    { .dataOffset = 722234, .properties = 1, .width = 122, .height = 23 },    /* title_measurements@A0, 1, 0 - SD */
    { .dataOffset = 727846, .properties = 1, .width = 85, .height = 23 },    /* title_measurements@A1, 1, 0 - SD */
    { .dataOffset = 731756, .properties = 1, .width = 94, .height = 23 },    /* title_measurements@A2, 1, 0 - SD */
    { .dataOffset = 736080, .properties = 1, .width = 112, .height = 23 },    /* title_measurements@A3, 1, 0 - SD */
    { .dataOffset = 741232, .properties = 1, .width = 69, .height = 23 },    /* title_measurements@A4, 1, 0 - SD */
    { .dataOffset = 744406, .properties = 1, .width = 55, .height = 23 },    /* title_measurements@A5, 1, 0 - SD */
    { .dataOffset = 746936, .properties = 1, .width = 96, .height = 23 },    /* title_measurements@A6, 1, 0 - SD */
    { .dataOffset = 751352, .properties = 1, .width = 40, .height = 23 },    /* title_measurements@A7, 1, 0 - SD */
    { .dataOffset = 753192, .properties = 1, .width = 38, .height = 23 },    /* title_measurements@A8, 1, 0 - SD */
    { .dataOffset = 754940, .properties = 1, .width = 33, .height = 23 },    /* title_measurements@A9, 1, 0 - SD */
    { .dataOffset = 756458, .properties = 1, .width = 91, .height = 23 },    /* title_recordings@A0, 1, 0 - SD */
    { .dataOffset = 760644, .properties = 1, .width = 78, .height = 23 },    /* title_recordings@A1, 1, 0 - SD */
    { .dataOffset = 764232, .properties = 1, .width = 94, .height = 23 },    /* title_recordings@A2, 1, 0 - SD */
    { .dataOffset = 768556, .properties = 1, .width = 134, .height = 23 },    /* title_recordings@A3, 1, 0 - SD */
    { .dataOffset = 774720, .properties = 1, .width = 102, .height = 23 },    /* title_recordings@A4, 1, 0 - SD */
    { .dataOffset = 779412, .properties = 1, .width = 105, .height = 23 },    /* title_recordings@A5, 1, 0 - SD */
    { .dataOffset = 784242, .properties = 1, .width = 62, .height = 23 },    /* title_recordings@A6, 1, 0 - SD */
    { .dataOffset = 787094, .properties = 1, .width = 39, .height = 23 },    /* title_recordings@A7, 1, 0 - SD */
    { .dataOffset = 788888, .properties = 1, .width = 39, .height = 23 },    /* title_recordings@A8, 1, 0 - SD */
    { .dataOffset = 790682, .properties = 1, .width = 35, .height = 23 },    /* title_recordings@A9, 1, 0 - SD */
    { .dataOffset = 792292, .properties = 1, .width = 67, .height = 23 },    /* title_settings@A0, 1, 0 - SD */
    { .dataOffset = 795374, .properties = 1, .width = 93, .height = 23 },    /* title_settings@A1, 1, 0 - SD */
    { .dataOffset = 799652, .properties = 1, .width = 109, .height = 23 },    /* title_settings@A2, 1, 0 - SD */
    { .dataOffset = 804666, .properties = 1, .width = 94, .height = 23 },    /* title_settings@A3, 1, 0 - SD */
    { .dataOffset = 808990, .properties = 1, .width = 114, .height = 23 },    /* title_settings@A4, 1, 0 - SD */
    { .dataOffset = 814234, .properties = 1, .width = 105, .height = 23 },    /* title_settings@A5, 1, 0 - SD */
    { .dataOffset = 819064, .properties = 1, .width = 98, .height = 23 },    /* title_settings@A6, 1, 0 - SD */
    { .dataOffset = 823572, .properties = 1, .width = 39, .height = 23 },    /* title_settings@A7, 1, 0 - SD */
    { .dataOffset = 825366, .properties = 1, .width = 38, .height = 23 },    /* title_settings@A8, 1, 0 - SD */
    { .dataOffset = 827114, .properties = 1, .width = 33, .height = 23 },    /* title_settings@A9, 1, 0 - SD */
    { .dataOffset = 828632, .properties = 1, .width = 39, .height = 23 },    /* title_start@A0, 1, 0 - SD */
    { .dataOffset = 830426, .properties = 1, .width = 39, .height = 23 },    /* title_start@A1, 1, 0 - SD */
    { .dataOffset = 832220, .properties = 1, .width = 78, .height = 23 },    /* title_start@A2, 1, 0 - SD */
    { .dataOffset = 835808, .properties = 1, .width = 100, .height = 23 },    /* title_start@A3, 1, 0 - SD */
    { .dataOffset = 840408, .properties = 1, .width = 71, .height = 23 },    /* title_start@A4, 1, 0 - SD */
    { .dataOffset = 843674, .properties = 1, .width = 42, .height = 23 },    /* title_start@A5, 1, 0 - SD */
    { .dataOffset = 845606, .properties = 1, .width = 63, .height = 23 },    /* title_start@A6, 1, 0 - SD */
    { .dataOffset = 848504, .properties = 1, .width = 39, .height = 23 },    /* title_start@A7, 1, 0 - SD */
    { .dataOffset = 850298, .properties = 1, .width = 50, .height = 23 },    /* title_start@A8, 1, 0 - SD */
    { .dataOffset = 852598, .properties = 1, .width = 72, .height = 23 },    /* title_start@A9, 1, 0 - SD */
    { .dataOffset = 855910, .properties = 1, .width = 37, .height = 23 },    /* title_stop@A0, 1, 0 - SD */
    { .dataOffset = 857612, .properties = 1, .width = 37, .height = 23 },    /* title_stop@A1, 1, 0 - SD */
    { .dataOffset = 859314, .properties = 1, .width = 75, .height = 23 },    /* title_stop@A2, 1, 0 - SD */
    { .dataOffset = 862764, .properties = 1, .width = 56, .height = 23 },    /* title_stop@A3, 1, 0 - SD */
    { .dataOffset = 865340, .properties = 1, .width = 43, .height = 23 },    /* title_stop@A4, 1, 0 - SD */
    { .dataOffset = 867318, .properties = 1, .width = 71, .height = 23 },    /* title_stop@A5, 1, 0 - SD */
    { .dataOffset = 870584, .properties = 1, .width = 91, .height = 23 },    /* title_stop@A6, 1, 0 - SD */
    { .dataOffset = 874770, .properties = 1, .width = 18, .height = 23 },    /* title_stop@A7, 1, 0 - SD */
    { .dataOffset = 875598, .properties = 1, .width = 50, .height = 23 },    /* title_stop@A8, 1, 0 - SD */
    { .dataOffset = 877898, .properties = 1, .width = 53, .height = 23 },    /* title_stop@A9, 1, 0 - SD */
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
    return FS_DATA_LOCATION_0_COMPRESSION;
}

/*** end of file ***/
