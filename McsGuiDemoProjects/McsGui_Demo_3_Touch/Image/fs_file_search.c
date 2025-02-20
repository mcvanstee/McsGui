#include "fs_file_search.h"

#define FS_FILE_INFO_SIZE 9
#define FS_FILE_DUMMY 0xFFFFFFFFU

const fs_file_info_s fs_file_infos[] =
{
    { .dataOffset = 16, .properties = 0, .width = 80, .height = 30 },    /* Play, 0 */
    { .dataOffset = 4816, .properties = 0, .width = 80, .height = 30 },    /* Play_Pressed, 0 */
    { .dataOffset = 9616, .properties = 0, .width = 80, .height = 30 },    /* Stop, 0 */
    { .dataOffset = 14416, .properties = 0, .width = 80, .height = 30 },    /* Stop_Pressed, 0 */
    { .dataOffset = 19216, .properties = 0, .width = 29, .height = 17 },    /* CHINESE_SIM, 0 */
    { .dataOffset = 20202, .properties = 0, .width = 15, .height = 17 },    /* DEG_CEL, 0 */
    { .dataOffset = 20712, .properties = 0, .width = 13, .height = 17 },    /* DEG_FAR, 0 */
    { .dataOffset = 21154, .properties = 0, .width = 73, .height = 17 },    /* DUTCH, 0 */
    { .dataOffset = 23636, .properties = 0, .width = 46, .height = 17 },    /* ENGLISH, 0 */
    { .dataOffset = 25200, .properties = 0, .width = 54, .height = 17 },    /* FRENCH, 0 */
    { .dataOffset = 27036, .properties = 0, .width = 51, .height = 17 },    /* GERMAN, 0 */
    { .dataOffset = 28770, .properties = 0, .width = 8, .height = 17 },    /* HASHTAG, 0 */
    { .dataOffset = 29042, .properties = 2, .width = 76, .height = 17 },    /* HIDE_DATE@B0, 10 */
    { .dataOffset = 31626, .properties = 2, .width = 110, .height = 17 },    /* HIDE_DATE@B1, 10 */
    { .dataOffset = 35366, .properties = 2, .width = 132, .height = 17 },    /* HIDE_DATE@B2, 10 */
    { .dataOffset = 39854, .properties = 2, .width = 93, .height = 17 },    /* HIDE_DATE@B3, 10 */
    { .dataOffset = 43016, .properties = 2, .width = 81, .height = 17 },    /* HIDE_DATE@B4, 10 */
    { .dataOffset = 45770, .properties = 2, .width = 90, .height = 17 },    /* HIDE_DATE@B5, 10 */
    { .dataOffset = 48830, .properties = 2, .width = 84, .height = 17 },    /* HIDE_DATE@B6, 10 */
    { .dataOffset = 51686, .properties = 2, .width = 61, .height = 17 },    /* HIDE_DATE@B7, 10 */
    { .dataOffset = 53760, .properties = 2, .width = 75, .height = 17 },    /* HIDE_DATE@B8, 10 */
    { .dataOffset = 56310, .properties = 2, .width = 60, .height = 17 },    /* HIDE_DATE@B9, 10 */
    { .dataOffset = 58350, .properties = 2, .width = 79, .height = 17 },    /* HIDE_TIME@B0, 10 */
    { .dataOffset = 61036, .properties = 2, .width = 92, .height = 17 },    /* HIDE_TIME@B1, 10 */
    { .dataOffset = 64164, .properties = 2, .width = 104, .height = 17 },    /* HIDE_TIME@B2, 10 */
    { .dataOffset = 67700, .properties = 2, .width = 86, .height = 17 },    /* HIDE_TIME@B3, 10 */
    { .dataOffset = 70624, .properties = 2, .width = 90, .height = 17 },    /* HIDE_TIME@B4, 10 */
    { .dataOffset = 73684, .properties = 2, .width = 112, .height = 17 },    /* HIDE_TIME@B5, 10 */
    { .dataOffset = 77492, .properties = 2, .width = 103, .height = 17 },    /* HIDE_TIME@B6, 10 */
    { .dataOffset = 80994, .properties = 2, .width = 61, .height = 17 },    /* HIDE_TIME@B7, 10 */
    { .dataOffset = 83068, .properties = 2, .width = 82, .height = 17 },    /* HIDE_TIME@B8, 10 */
    { .dataOffset = 85856, .properties = 2, .width = 74, .height = 17 },    /* HIDE_TIME@B9, 10 */
    { .dataOffset = 88372, .properties = 0, .width = 18, .height = 20 },    /* Icon_Agenda, 0 */
    { .dataOffset = 89092, .properties = 0, .width = 6, .height = 12 },    /* icon_Arrow-Down-Small, 0 */
    { .dataOffset = 89236, .properties = 0, .width = 6, .height = 12 },    /* icon_Arrow-Up-Small, 0 */
    { .dataOffset = 89380, .properties = 1, .width = 45, .height = 38 },    /* Icon_back@A0, 1 */
    { .dataOffset = 92800, .properties = 1, .width = 45, .height = 38 },    /* Icon_back@A1, 1 */
    { .dataOffset = 96220, .properties = 1, .width = 22, .height = 22 },    /* Icon_Bullseye@A0, 1 */
    { .dataOffset = 97188, .properties = 1, .width = 22, .height = 22 },    /* Icon_Bullseye@A1, 1 */
    { .dataOffset = 98156, .properties = 1, .width = 22, .height = 22 },    /* Icon_Bullseye_red@A0, 1 */
    { .dataOffset = 99124, .properties = 1, .width = 22, .height = 22 },    /* Icon_Bullseye_red@A1, 1 */
    { .dataOffset = 100092, .properties = 0, .width = 30, .height = 30 },    /* Icon_ButtonMinus, 0 */
    { .dataOffset = 101892, .properties = 0, .width = 30, .height = 30 },    /* Icon_ButtonPlus, 0 */
    { .dataOffset = 103692, .properties = 0, .width = 18, .height = 18 },    /* Icon_Clock, 0 */
    { .dataOffset = 104340, .properties = 1, .width = 23, .height = 20 },    /* Icon_display@A0, 1 */
    { .dataOffset = 105260, .properties = 1, .width = 23, .height = 20 },    /* Icon_display@A1, 1 */
    { .dataOffset = 106180, .properties = 1, .width = 20, .height = 20 },    /* Icon_Focus@A0, 1 */
    { .dataOffset = 106980, .properties = 1, .width = 20, .height = 20 },    /* Icon_Focus@A1, 1 */
    { .dataOffset = 107780, .properties = 1, .width = 20, .height = 20 },    /* Icon_Gear@A0, 1 */
    { .dataOffset = 108580, .properties = 1, .width = 20, .height = 20 },    /* Icon_Gear@A1, 1 */
    { .dataOffset = 109380, .properties = 1, .width = 20, .height = 23 },    /* Icon_Home@A0, 1 */
    { .dataOffset = 110300, .properties = 1, .width = 20, .height = 23 },    /* Icon_Home@A1, 1 */
    { .dataOffset = 111220, .properties = 1, .width = 22, .height = 22 },    /* Icon_language@A0, 1 */
    { .dataOffset = 112188, .properties = 1, .width = 22, .height = 22 },    /* Icon_language@A1, 1 */
    { .dataOffset = 113156, .properties = 1, .width = 16, .height = 4 },    /* Icon_minus@A0, 1 */
    { .dataOffset = 113284, .properties = 1, .width = 16, .height = 4 },    /* Icon_minus@A1, 1 */
    { .dataOffset = 113412, .properties = 1, .width = 16, .height = 16 },    /* Icon_plus@A0, 1 */
    { .dataOffset = 113924, .properties = 1, .width = 16, .height = 16 },    /* Icon_plus@A1, 1 */
    { .dataOffset = 114436, .properties = 1, .width = 22, .height = 18 },    /* Icon_Pulse@A0, 1 */
    { .dataOffset = 115228, .properties = 1, .width = 22, .height = 18 },    /* Icon_Pulse@A1, 1 */
    { .dataOffset = 116020, .properties = 1, .width = 18, .height = 18 },    /* Icon_Radio@A0, 1 */
    { .dataOffset = 116668, .properties = 1, .width = 18, .height = 18 },    /* Icon_Radio@A1, 1 */
    { .dataOffset = 117316, .properties = 1, .width = 22, .height = 22 },    /* Icon_rec_Recording@A0, 1 */
    { .dataOffset = 118284, .properties = 1, .width = 22, .height = 22 },    /* Icon_rec_Recording@A1, 1 */
    { .dataOffset = 119252, .properties = 0, .width = 24, .height = 24 },    /* Icon_Scroll-down, 0 */
    { .dataOffset = 120404, .properties = 0, .width = 24, .height = 24 },    /* Icon_Scroll-up, 0 */
    { .dataOffset = 121556, .properties = 1, .width = 20, .height = 20 },    /* Icon_Sliders@A0, 1 */
    { .dataOffset = 122356, .properties = 1, .width = 20, .height = 20 },    /* Icon_Sliders@A1, 1 */
    { .dataOffset = 123156, .properties = 1, .width = 50, .height = 22 },    /* Icon_Switch@A0, 1 */
    { .dataOffset = 125356, .properties = 1, .width = 50, .height = 22 },    /* Icon_Switch@A1, 1 */
    { .dataOffset = 127556, .properties = 1, .width = 13, .height = 25 },    /* Icon_thermometer@A0, 1 */
    { .dataOffset = 128206, .properties = 1, .width = 13, .height = 25 },    /* Icon_thermometer@A1, 1 */
    { .dataOffset = 128856, .properties = 1, .width = 18, .height = 20 },    /* Icon_Trash@A0, 1 */
    { .dataOffset = 129576, .properties = 1, .width = 18, .height = 20 },    /* Icon_Trash@A1, 1 */
    { .dataOffset = 130296, .properties = 0, .width = 13, .height = 17 },    /* ID, 0 */
    { .dataOffset = 130738, .properties = 2, .width = 67, .height = 17 },    /* INTERVAL@B0, 10 */
    { .dataOffset = 133016, .properties = 2, .width = 67, .height = 17 },    /* INTERVAL@B1, 10 */
    { .dataOffset = 135294, .properties = 2, .width = 70, .height = 17 },    /* INTERVAL@B2, 10 */
    { .dataOffset = 137674, .properties = 2, .width = 78, .height = 17 },    /* INTERVAL@B3, 10 */
    { .dataOffset = 140326, .properties = 2, .width = 75, .height = 17 },    /* INTERVAL@B4, 10 */
    { .dataOffset = 142876, .properties = 2, .width = 78, .height = 17 },    /* INTERVAL@B5, 10 */
    { .dataOffset = 145528, .properties = 2, .width = 84, .height = 17 },    /* INTERVAL@B6, 10 */
    { .dataOffset = 148384, .properties = 2, .width = 50, .height = 17 },    /* INTERVAL@B7, 10 */
    { .dataOffset = 150084, .properties = 2, .width = 35, .height = 17 },    /* INTERVAL@B8, 10 */
    { .dataOffset = 151274, .properties = 2, .width = 34, .height = 17 },    /* INTERVAL@B9, 10 */
    { .dataOffset = 152430, .properties = 0, .width = 128, .height = 128 },    /* IRL_Logo 128, 0 */
    { .dataOffset = 185198, .properties = 0, .width = 48, .height = 48 },    /* IRL_Logo_48, 0 */
    { .dataOffset = 189806, .properties = 0, .width = 46, .height = 17 },    /* ITALIAN, 0 */
    { .dataOffset = 191370, .properties = 0, .width = 44, .height = 17 },    /* JAPANESE, 0 */
    { .dataOffset = 192866, .properties = 0, .width = 40, .height = 17 },    /* KOREAN, 0 */
    { .dataOffset = 194226, .properties = 2, .width = 105, .height = 17 },    /* MAX_DATA_POINTS@B0, 10 */
    { .dataOffset = 197796, .properties = 2, .width = 110, .height = 17 },    /* MAX_DATA_POINTS@B1, 10 */
    { .dataOffset = 201536, .properties = 2, .width = 116, .height = 17 },    /* MAX_DATA_POINTS@B2, 10 */
    { .dataOffset = 205480, .properties = 2, .width = 152, .height = 17 },    /* MAX_DATA_POINTS@B3, 10 */
    { .dataOffset = 210648, .properties = 2, .width = 136, .height = 17 },    /* MAX_DATA_POINTS@B4, 10 */
    { .dataOffset = 215272, .properties = 2, .width = 189, .height = 17 },    /* MAX_DATA_POINTS@B5, 10 */
    { .dataOffset = 221698, .properties = 2, .width = 84, .height = 17 },    /* MAX_DATA_POINTS@B6, 10 */
    { .dataOffset = 224554, .properties = 2, .width = 93, .height = 17 },    /* MAX_DATA_POINTS@B7, 10 */
    { .dataOffset = 227716, .properties = 2, .width = 115, .height = 17 },    /* MAX_DATA_POINTS@B8, 10 */
    { .dataOffset = 231626, .properties = 2, .width = 122, .height = 17 },    /* MAX_DATA_POINTS@B9, 10 */
    { .dataOffset = 235774, .properties = 0, .width = 53, .height = 17 },    /* RUSSIAN, 0 */
    { .dataOffset = 237576, .properties = 2, .width = 125, .height = 17 },    /* SAVE_REC@B0, 10 */
    { .dataOffset = 241826, .properties = 2, .width = 104, .height = 17 },    /* SAVE_REC@B1, 10 */
    { .dataOffset = 245362, .properties = 2, .width = 123, .height = 17 },    /* SAVE_REC@B2, 10 */
    { .dataOffset = 249544, .properties = 2, .width = 137, .height = 17 },    /* SAVE_REC@B3, 10 */
    { .dataOffset = 254202, .properties = 2, .width = 113, .height = 17 },    /* SAVE_REC@B4, 10 */
    { .dataOffset = 258044, .properties = 2, .width = 118, .height = 17 },    /* SAVE_REC@B5, 10 */
    { .dataOffset = 262056, .properties = 2, .width = 148, .height = 17 },    /* SAVE_REC@B6, 10 */
    { .dataOffset = 267088, .properties = 2, .width = 62, .height = 17 },    /* SAVE_REC@B7, 10 */
    { .dataOffset = 269196, .properties = 2, .width = 90, .height = 17 },    /* SAVE_REC@B8, 10 */
    { .dataOffset = 272256, .properties = 2, .width = 74, .height = 17 },    /* SAVE_REC@B9, 10 */
    { .dataOffset = 274772, .properties = 2, .width = 40, .height = 17 },    /* SAVED@B0, 10 */
    { .dataOffset = 276132, .properties = 2, .width = 76, .height = 17 },    /* SAVED@B1, 10 */
    { .dataOffset = 278716, .properties = 2, .width = 77, .height = 17 },    /* SAVED@B2, 10 */
    { .dataOffset = 281334, .properties = 2, .width = 41, .height = 17 },    /* SAVED@B3, 10 */
    { .dataOffset = 282728, .properties = 2, .width = 63, .height = 17 },    /* SAVED@B4, 10 */
    { .dataOffset = 284870, .properties = 2, .width = 48, .height = 17 },    /* SAVED@B5, 10 */
    { .dataOffset = 286502, .properties = 2, .width = 73, .height = 17 },    /* SAVED@B6, 10 */
    { .dataOffset = 288984, .properties = 2, .width = 30, .height = 17 },    /* SAVED@B7, 10 */
    { .dataOffset = 290004, .properties = 2, .width = 30, .height = 17 },    /* SAVED@B8, 10 */
    { .dataOffset = 291024, .properties = 2, .width = 27, .height = 17 },    /* SAVED@B9, 10 */
    { .dataOffset = 291942, .properties = 2, .width = 74, .height = 17 },    /* SHOW_DATE@B0, 10 */
    { .dataOffset = 294458, .properties = 2, .width = 105, .height = 17 },    /* SHOW_DATE@B1, 10 */
    { .dataOffset = 298028, .properties = 2, .width = 97, .height = 17 },    /* SHOW_DATE@B2, 10 */
    { .dataOffset = 301326, .properties = 2, .width = 74, .height = 17 },    /* SHOW_DATE@B3, 10 */
    { .dataOffset = 303842, .properties = 2, .width = 83, .height = 17 },    /* SHOW_DATE@B4, 10 */
    { .dataOffset = 306664, .properties = 2, .width = 77, .height = 17 },    /* SHOW_DATE@B5, 10 */
    { .dataOffset = 309282, .properties = 2, .width = 94, .height = 17 },    /* SHOW_DATE@B6, 10 */
    { .dataOffset = 312478, .properties = 2, .width = 61, .height = 17 },    /* SHOW_DATE@B7, 10 */
    { .dataOffset = 314552, .properties = 2, .width = 62, .height = 17 },    /* SHOW_DATE@B8, 10 */
    { .dataOffset = 316660, .properties = 2, .width = 89, .height = 17 },    /* SHOW_DATE@B9, 10 */
    { .dataOffset = 319686, .properties = 2, .width = 76, .height = 17 },    /* SHOW_TIME@B0, 10 */
    { .dataOffset = 322270, .properties = 2, .width = 86, .height = 17 },    /* SHOW_TIME@B1, 10 */
    { .dataOffset = 325194, .properties = 2, .width = 79, .height = 17 },    /* SHOW_TIME@B2, 10 */
    { .dataOffset = 327880, .properties = 2, .width = 88, .height = 17 },    /* SHOW_TIME@B3, 10 */
    { .dataOffset = 330872, .properties = 2, .width = 92, .height = 17 },    /* SHOW_TIME@B4, 10 */
    { .dataOffset = 334000, .properties = 2, .width = 92, .height = 17 },    /* SHOW_TIME@B5, 10 */
    { .dataOffset = 337128, .properties = 2, .width = 105, .height = 17 },    /* SHOW_TIME@B6, 10 */
    { .dataOffset = 340698, .properties = 2, .width = 61, .height = 17 },    /* SHOW_TIME@B7, 10 */
    { .dataOffset = 342772, .properties = 2, .width = 106, .height = 17 },    /* SHOW_TIME@B8, 10 */
    { .dataOffset = 346376, .properties = 2, .width = 89, .height = 17 },    /* SHOW_TIME@B9, 10 */
    { .dataOffset = 349402, .properties = 0, .width = 20, .height = 20 },    /* Slider_knob_round, 0 */
    { .dataOffset = 350202, .properties = 0, .width = 51, .height = 17 },    /* SPANISH, 0 */
    { .dataOffset = 351936, .properties = 2, .width = 39, .height = 20 },    /* text_button_SAVE@B0, 10 */
    { .dataOffset = 353496, .properties = 2, .width = 63, .height = 20 },    /* text_button_SAVE@B1, 10 */
    { .dataOffset = 4294967295, .properties = 1, .width = 0, .height = 0 },    /* Dummy file, TEXT_BUTTON_SAVE__B002, 1 */
    { .dataOffset = 4294967295, .properties = 1, .width = 0, .height = 0 },    /* Dummy file, TEXT_BUTTON_SAVE__B003, 1 */
    { .dataOffset = 4294967295, .properties = 1, .width = 0, .height = 0 },    /* Dummy file, TEXT_BUTTON_SAVE__B004, 1 */
    { .dataOffset = 4294967295, .properties = 1, .width = 0, .height = 0 },    /* Dummy file, TEXT_BUTTON_SAVE__B005, 1 */
    { .dataOffset = 4294967295, .properties = 1, .width = 0, .height = 0 },    /* Dummy file, TEXT_BUTTON_SAVE__B006, 1 */
    { .dataOffset = 4294967295, .properties = 1, .width = 0, .height = 0 },    /* Dummy file, TEXT_BUTTON_SAVE__B007, 1 */
    { .dataOffset = 4294967295, .properties = 1, .width = 0, .height = 0 },    /* Dummy file, TEXT_BUTTON_SAVE__B008, 1 */
    { .dataOffset = 4294967295, .properties = 1, .width = 0, .height = 0 },    /* Dummy file, TEXT_BUTTON_SAVE__B009, 1 */
    { .dataOffset = 356016, .properties = 2, .width = 76, .height = 20 },    /* title_BRIGHTNESS@B0, 10 */
    { .dataOffset = 359056, .properties = 2, .width = 78, .height = 20 },    /* title_BRIGHTNESS@B1, 10 */
    { .dataOffset = 362176, .properties = 2, .width = 66, .height = 20 },    /* title_BRIGHTNESS@B2, 10 */
    { .dataOffset = 364816, .properties = 2, .width = 78, .height = 20 },    /* title_BRIGHTNESS@B3, 10 */
    { .dataOffset = 367936, .properties = 2, .width = 35, .height = 20 },    /* title_BRIGHTNESS@B4, 10 */
    { .dataOffset = 369336, .properties = 2, .width = 78, .height = 20 },    /* title_BRIGHTNESS@B5, 10 */
    { .dataOffset = 372456, .properties = 2, .width = 62, .height = 20 },    /* title_BRIGHTNESS@B6, 10 */
    { .dataOffset = 374936, .properties = 2, .width = 34, .height = 20 },    /* title_BRIGHTNESS@B7, 10 */
    { .dataOffset = 376296, .properties = 2, .width = 41, .height = 20 },    /* title_BRIGHTNESS@B8, 10 */
    { .dataOffset = 377936, .properties = 2, .width = 29, .height = 20 },    /* title_BRIGHTNESS@B9, 10 */
    { .dataOffset = 379096, .properties = 2, .width = 115, .height = 20 },    /* title_CALIBRATE_TOUCH@B0, 10 */
    { .dataOffset = 383696, .properties = 2, .width = 119, .height = 20 },    /* title_CALIBRATE_TOUCH@B1, 10 */
    { .dataOffset = 388456, .properties = 2, .width = 138, .height = 20 },    /* title_CALIBRATE_TOUCH@B2, 10 */
    { .dataOffset = 393976, .properties = 2, .width = 118, .height = 20 },    /* title_CALIBRATE_TOUCH@B3, 10 */
    { .dataOffset = 398696, .properties = 2, .width = 115, .height = 20 },    /* title_CALIBRATE_TOUCH@B4, 10 */
    { .dataOffset = 403296, .properties = 2, .width = 96, .height = 20 },    /* title_CALIBRATE_TOUCH@B5, 10 */
    { .dataOffset = 407136, .properties = 2, .width = 232, .height = 20 },    /* title_CALIBRATE_TOUCH@B6, 10 */
    { .dataOffset = 416416, .properties = 2, .width = 72, .height = 20 },    /* title_CALIBRATE_TOUCH@B7, 10 */
    { .dataOffset = 419296, .properties = 2, .width = 168, .height = 20 },    /* title_CALIBRATE_TOUCH@B8, 10 */
    { .dataOffset = 426016, .properties = 2, .width = 66, .height = 20 },    /* title_CALIBRATE_TOUCH@B9, 10 */
    { .dataOffset = 428656, .properties = 2, .width = 69, .height = 20 },    /* title_DATE_TIME@B0, 10 */
    { .dataOffset = 431416, .properties = 2, .width = 72, .height = 20 },    /* title_DATE_TIME@B1, 10 */
    { .dataOffset = 434296, .properties = 2, .width = 104, .height = 20 },    /* title_DATE_TIME@B2, 10 */
    { .dataOffset = 438456, .properties = 2, .width = 80, .height = 20 },    /* title_DATE_TIME@B3, 10 */
    { .dataOffset = 441656, .properties = 2, .width = 81, .height = 20 },    /* title_DATE_TIME@B4, 10 */
    { .dataOffset = 444896, .properties = 2, .width = 61, .height = 20 },    /* title_DATE_TIME@B5, 10 */
    { .dataOffset = 447336, .properties = 2, .width = 90, .height = 20 },    /* title_DATE_TIME@B6, 10 */
    { .dataOffset = 450936, .properties = 2, .width = 72, .height = 20 },    /* title_DATE_TIME@B7, 10 */
    { .dataOffset = 453816, .properties = 2, .width = 72, .height = 20 },    /* title_DATE_TIME@B8, 10 */
    { .dataOffset = 456696, .properties = 2, .width = 67, .height = 20 },    /* title_DATE_TIME@B9, 10 */
    { .dataOffset = 459376, .properties = 2, .width = 53, .height = 20 },    /* title_DISPLAY@B0, 10 */
    { .dataOffset = 461496, .properties = 2, .width = 94, .height = 20 },    /* title_DISPLAY@B1, 10 */
    { .dataOffset = 465256, .properties = 2, .width = 49, .height = 20 },    /* title_DISPLAY@B2, 10 */
    { .dataOffset = 467216, .properties = 2, .width = 56, .height = 20 },    /* title_DISPLAY@B3, 10 */
    { .dataOffset = 469456, .properties = 2, .width = 54, .height = 20 },    /* title_DISPLAY@B4, 10 */
    { .dataOffset = 471616, .properties = 2, .width = 56, .height = 20 },    /* title_DISPLAY@B5, 10 */
    { .dataOffset = 473856, .properties = 2, .width = 66, .height = 20 },    /* title_DISPLAY@B6, 10 */
    { .dataOffset = 476496, .properties = 2, .width = 34, .height = 20 },    /* title_DISPLAY@B7, 10 */
    { .dataOffset = 477856, .properties = 2, .width = 33, .height = 20 },    /* title_DISPLAY@B8, 10 */
    { .dataOffset = 479176, .properties = 2, .width = 29, .height = 20 },    /* title_DISPLAY@B9, 10 */
    { .dataOffset = 480336, .properties = 2, .width = 14, .height = 20 },    /* title_ID@B0, 10 */
    { .dataOffset = 480896, .properties = 2, .width = 14, .height = 20 },    /* title_ID@B1, 10 */
    { .dataOffset = 481456, .properties = 2, .width = 14, .height = 20 },    /* title_ID@B2, 10 */
    { .dataOffset = 482016, .properties = 2, .width = 14, .height = 20 },    /* title_ID@B3, 10 */
    { .dataOffset = 482576, .properties = 2, .width = 14, .height = 20 },    /* title_ID@B4, 10 */
    { .dataOffset = 483136, .properties = 2, .width = 14, .height = 20 },    /* title_ID@B5, 10 */
    { .dataOffset = 483696, .properties = 2, .width = 14, .height = 20 },    /* title_ID@B6, 10 */
    { .dataOffset = 484256, .properties = 2, .width = 14, .height = 20 },    /* title_ID@B7, 10 */
    { .dataOffset = 484816, .properties = 2, .width = 14, .height = 20 },    /* title_ID@B8, 10 */
    { .dataOffset = 485376, .properties = 2, .width = 14, .height = 20 },    /* title_ID@B9, 10 */
    { .dataOffset = 485936, .properties = 2, .width = 72, .height = 20 },    /* title_LANGUAGE@B0, 10 */
    { .dataOffset = 488816, .properties = 2, .width = 31, .height = 20 },    /* title_LANGUAGE@B1, 10 */
    { .dataOffset = 490056, .properties = 2, .width = 61, .height = 20 },    /* title_LANGUAGE@B2, 10 */
    { .dataOffset = 492496, .properties = 2, .width = 53, .height = 20 },    /* title_LANGUAGE@B3, 10 */
    { .dataOffset = 494616, .properties = 2, .width = 47, .height = 20 },    /* title_LANGUAGE@B4, 10 */
    { .dataOffset = 496496, .properties = 2, .width = 47, .height = 20 },    /* title_LANGUAGE@B5, 10 */
    { .dataOffset = 498376, .properties = 2, .width = 40, .height = 20 },    /* title_LANGUAGE@B6, 10 */
    { .dataOffset = 499976, .properties = 2, .width = 35, .height = 20 },    /* title_LANGUAGE@B7, 10 */
    { .dataOffset = 501376, .properties = 2, .width = 35, .height = 20 },    /* title_LANGUAGE@B8, 10 */
    { .dataOffset = 502776, .properties = 2, .width = 29, .height = 20 },    /* title_LANGUAGE@B9, 10 */
    { .dataOffset = 503936, .properties = 2, .width = 107, .height = 20 },    /* title_MEASUREMENTS@B0, 10 */
    { .dataOffset = 508216, .properties = 2, .width = 75, .height = 20 },    /* title_MEASUREMENTS@B1, 10 */
    { .dataOffset = 511216, .properties = 2, .width = 83, .height = 20 },    /* title_MEASUREMENTS@B2, 10 */
    { .dataOffset = 514536, .properties = 2, .width = 97, .height = 20 },    /* title_MEASUREMENTS@B3, 10 */
    { .dataOffset = 518416, .properties = 2, .width = 61, .height = 20 },    /* title_MEASUREMENTS@B4, 10 */
    { .dataOffset = 520856, .properties = 2, .width = 48, .height = 20 },    /* title_MEASUREMENTS@B5, 10 */
    { .dataOffset = 522776, .properties = 2, .width = 85, .height = 20 },    /* title_MEASUREMENTS@B6, 10 */
    { .dataOffset = 526176, .properties = 2, .width = 35, .height = 20 },    /* title_MEASUREMENTS@B7, 10 */
    { .dataOffset = 527576, .properties = 2, .width = 35, .height = 20 },    /* title_MEASUREMENTS@B8, 10 */
    { .dataOffset = 528976, .properties = 2, .width = 30, .height = 20 },    /* title_MEASUREMENTS@B9, 10 */
    { .dataOffset = 530176, .properties = 2, .width = 82, .height = 20 },    /* title_RECORDINGS@B0, 10 */
    { .dataOffset = 533456, .properties = 2, .width = 71, .height = 20 },    /* title_RECORDINGS@B1, 10 */
    { .dataOffset = 536296, .properties = 2, .width = 84, .height = 20 },    /* title_RECORDINGS@B2, 10 */
    { .dataOffset = 539656, .properties = 2, .width = 118, .height = 20 },    /* title_RECORDINGS@B3, 10 */
    { .dataOffset = 544376, .properties = 2, .width = 93, .height = 20 },    /* title_RECORDINGS@B4, 10 */
    { .dataOffset = 548096, .properties = 2, .width = 93, .height = 20 },    /* title_RECORDINGS@B5, 10 */
    { .dataOffset = 551816, .properties = 2, .width = 54, .height = 20 },    /* title_RECORDINGS@B6, 10 */
    { .dataOffset = 553976, .properties = 2, .width = 35, .height = 20 },    /* title_RECORDINGS@B7, 10 */
    { .dataOffset = 555376, .properties = 2, .width = 35, .height = 20 },    /* title_RECORDINGS@B8, 10 */
    { .dataOffset = 556776, .properties = 2, .width = 32, .height = 20 },    /* title_RECORDINGS@B9, 10 */
    { .dataOffset = 558056, .properties = 2, .width = 59, .height = 20 },    /* title_SETTINGS@B0, 10 */
    { .dataOffset = 560416, .properties = 2, .width = 82, .height = 20 },    /* title_SETTINGS@B1, 10 */
    { .dataOffset = 563696, .properties = 2, .width = 97, .height = 20 },    /* title_SETTINGS@B2, 10 */
    { .dataOffset = 567576, .properties = 2, .width = 83, .height = 20 },    /* title_SETTINGS@B3, 10 */
    { .dataOffset = 570896, .properties = 2, .width = 101, .height = 20 },    /* title_SETTINGS@B4, 10 */
    { .dataOffset = 574936, .properties = 2, .width = 90, .height = 20 },    /* title_SETTINGS@B5, 10 */
    { .dataOffset = 578536, .properties = 2, .width = 86, .height = 20 },    /* title_SETTINGS@B6, 10 */
    { .dataOffset = 581976, .properties = 2, .width = 35, .height = 20 },    /* title_SETTINGS@B7, 10 */
    { .dataOffset = 583376, .properties = 2, .width = 35, .height = 20 },    /* title_SETTINGS@B8, 10 */
    { .dataOffset = 584776, .properties = 2, .width = 29, .height = 20 },    /* title_SETTINGS@B9, 10 */
    { .dataOffset = 585936, .properties = 2, .width = 35, .height = 20 },    /* title_START@B0, 10 */
    { .dataOffset = 587336, .properties = 2, .width = 35, .height = 20 },    /* title_START@B1, 10 */
    { .dataOffset = 588736, .properties = 2, .width = 70, .height = 20 },    /* title_START@B2, 10 */
    { .dataOffset = 591536, .properties = 2, .width = 90, .height = 20 },    /* title_START@B3, 10 */
    { .dataOffset = 595136, .properties = 2, .width = 65, .height = 20 },    /* title_START@B4, 10 */
    { .dataOffset = 597736, .properties = 2, .width = 37, .height = 20 },    /* title_START@B5, 10 */
    { .dataOffset = 599216, .properties = 2, .width = 56, .height = 20 },    /* title_START@B6, 10 */
    { .dataOffset = 601456, .properties = 2, .width = 35, .height = 20 },    /* title_START@B7, 10 */
    { .dataOffset = 602856, .properties = 2, .width = 44, .height = 20 },    /* title_START@B8, 10 */
    { .dataOffset = 604616, .properties = 2, .width = 64, .height = 20 },    /* title_START@B9, 10 */
    { .dataOffset = 607176, .properties = 2, .width = 33, .height = 20 },    /* title_STOP@B0, 10 */
    { .dataOffset = 608496, .properties = 2, .width = 33, .height = 20 },    /* title_STOP@B1, 10 */
    { .dataOffset = 609816, .properties = 2, .width = 67, .height = 20 },    /* title_STOP@B2, 10 */
    { .dataOffset = 612496, .properties = 2, .width = 51, .height = 20 },    /* title_STOP@B3, 10 */
    { .dataOffset = 614536, .properties = 2, .width = 39, .height = 20 },    /* title_STOP@B4, 10 */
    { .dataOffset = 616096, .properties = 2, .width = 63, .height = 20 },    /* title_STOP@B5, 10 */
    { .dataOffset = 618616, .properties = 2, .width = 81, .height = 20 },    /* title_STOP@B6, 10 */
    { .dataOffset = 621856, .properties = 2, .width = 17, .height = 20 },    /* title_STOP@B7, 10 */
    { .dataOffset = 622536, .properties = 2, .width = 45, .height = 20 },    /* title_STOP@B8, 10 */
    { .dataOffset = 624336, .properties = 2, .width = 46, .height = 20 },    /* title_STOP@B9, 10 */
    { .dataOffset = 626176, .properties = 2, .width = 32, .height = 17 },    /* UNITS@B0, 10 */
    { .dataOffset = 627264, .properties = 2, .width = 64, .height = 17 },    /* UNITS@B1, 10 */
    { .dataOffset = 629440, .properties = 2, .width = 59, .height = 17 },    /* UNITS@B2, 10 */
    { .dataOffset = 631446, .properties = 2, .width = 40, .height = 17 },    /* UNITS@B3, 10 */
    { .dataOffset = 632806, .properties = 2, .width = 60, .height = 17 },    /* UNITS@B4, 10 */
    { .dataOffset = 634846, .properties = 2, .width = 32, .height = 17 },    /* UNITS@B5, 10 */
    { .dataOffset = 635934, .properties = 2, .width = 50, .height = 17 },    /* UNITS@B6, 10 */
    { .dataOffset = 637634, .properties = 2, .width = 30, .height = 17 },    /* UNITS@B7, 10 */
    { .dataOffset = 638654, .properties = 2, .width = 30, .height = 17 },    /* UNITS@B8, 10 */
    { .dataOffset = 639674, .properties = 2, .width = 25, .height = 17 },    /* UNITS@B9, 10 */
};

const uint8_t maxProperty[FS_MAX_FILE_PROPERTIES] =
{
    2, 10, 
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
