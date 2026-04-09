#include "fs_file_search.h"

#define FS_FILE_INFO_SIZE 9
#define FS_FILE_DUMMY 0xFFFFFFFFU

const fs_file_info_s fs_file_infos[] =
{                                                                      /* filename, fileproperty, datalocation */
    { .dataOffset = 0x00000032, .properties = 0, .width = 30, .height = 30 },    /* Button_minus, 0, 0 - SD */
    { .dataOffset = 0x0000073A, .properties = 0, .width = 80, .height = 30 },    /* Play, 0, 0 - SD */
    { .dataOffset = 0x000019FA, .properties = 0, .width = 80, .height = 30 },    /* Play_Pressed, 0, 0 - SD */
    { .dataOffset = 0x00002CBA, .properties = 0, .width = 30, .height = 30 },    /* Button_plus, 0, 0 - SD */
    { .dataOffset = 0x000033C2, .properties = 0, .width = 80, .height = 30 },    /* Stop, 0, 0 - SD */
    { .dataOffset = 0x00004682, .properties = 0, .width = 80, .height = 30 },    /* Stop_Pressed, 0, 0 - SD */
    { .dataOffset = 0x00005942, .properties = 0, .width = 6, .height = 12 },    /* icon_Arrow-Down-Small, 0, 0 - SD */
    { .dataOffset = 0x000059D2, .properties = 0, .width = 6, .height = 12 },    /* icon_Arrow-Up-Small, 0, 0 - SD */
    { .dataOffset = 0x00005A62, .properties = 0, .width = 45, .height = 38 },    /* icon_back, 0, 0 - SD */
    { .dataOffset = 0x000067BE, .properties = 12, .width = 22, .height = 22 },    /* icon_Bullseye@C0_D0, 1100, 0 - SD */
    { .dataOffset = 0x00006B86, .properties = 12, .width = 22, .height = 22 },    /* icon_Bullseye@C0_D1, 1100, 0 - SD */
    { .dataOffset = 0x00006F4E, .properties = 12, .width = 22, .height = 22 },    /* icon_Bullseye@C1_D0, 1100, 0 - SD */
    { .dataOffset = 0x00007316, .properties = 12, .width = 22, .height = 22 },    /* icon_Bullseye@C1_D1, 1100, 0 - SD */
    { .dataOffset = 0x000076DE, .properties = 0, .width = 18, .height = 18 },    /* icon_Clock, 0, 0 - SD */
    { .dataOffset = 0x00007966, .properties = 4, .width = 22, .height = 17 },    /* icon_Data@C0, 100, 0 - SD */
    { .dataOffset = 0x00007C52, .properties = 4, .width = 22, .height = 17 },    /* icon_Data@C1, 100, 0 - SD */
    { .dataOffset = 0x00007F3E, .properties = 0, .width = 22, .height = 20 },    /* icon_display, 0, 0 - SD */
    { .dataOffset = 0x000082AE, .properties = 4, .width = 20, .height = 20 },    /* icon_Focus@C0, 100, 0 - SD */
    { .dataOffset = 0x000085CE, .properties = 4, .width = 20, .height = 20 },    /* icon_Focus@C1, 100, 0 - SD */
    { .dataOffset = 0x000088EE, .properties = 4, .width = 20, .height = 20 },    /* icon_Gear@C0, 100, 0 - SD */
    { .dataOffset = 0x00008C0E, .properties = 4, .width = 20, .height = 20 },    /* icon_Gear@C1, 100, 0 - SD */
    { .dataOffset = 0x00008F2E, .properties = 4, .width = 20, .height = 23 },    /* icon_Home@C0, 100, 0 - SD */
    { .dataOffset = 0x000092C6, .properties = 4, .width = 20, .height = 23 },    /* icon_Home@C1, 100, 0 - SD */
    { .dataOffset = 0x0000965E, .properties = 0, .width = 22, .height = 22 },    /* icon_language, 0, 0 - SD */
    { .dataOffset = 0x00009A26, .properties = 0, .width = 16, .height = 4 },    /* icon_minus, 0, 0 - SD */
    { .dataOffset = 0x00009AA6, .properties = 0, .width = 18, .height = 20 },    /* icon_pane_Agenda, 0, 0 - SD */
    { .dataOffset = 0x00009D76, .properties = 0, .width = 18, .height = 18 },    /* icon_pane_Clock, 0, 0 - SD */
    { .dataOffset = 0x00009FFE, .properties = 0, .width = 16, .height = 16 },    /* icon_plus, 0, 0 - SD */
    { .dataOffset = 0x0000A1FE, .properties = 0, .width = 22, .height = 18 },    /* icon_Pulse, 0, 0 - SD */
    { .dataOffset = 0x0000A516, .properties = 0, .width = 24, .height = 24 },    /* icon_Scroll-down, 0, 0 - SD */
    { .dataOffset = 0x0000A996, .properties = 0, .width = 24, .height = 24 },    /* icon_Scroll-up, 0, 0 - SD */
    { .dataOffset = 0x0000AE16, .properties = 0, .width = 20, .height = 20 },    /* icon_Slider_knob, 0, 0 - SD */
    { .dataOffset = 0x0000B136, .properties = 4, .width = 20, .height = 20 },    /* icon_Sliders@C0, 100, 0 - SD */
    { .dataOffset = 0x0000B456, .properties = 4, .width = 20, .height = 20 },    /* icon_Sliders@C1, 100, 0 - SD */
    { .dataOffset = 0x0000B776, .properties = 4, .width = 50, .height = 22 },    /* icon_Switch@C0, 100, 0 - SD */
    { .dataOffset = 0x0000C00E, .properties = 4, .width = 50, .height = 22 },    /* icon_Switch@C1, 100, 0 - SD */
    { .dataOffset = 0x0000C8A6, .properties = 0, .width = 13, .height = 25 },    /* icon_thermometer, 0, 0 - SD */
    { .dataOffset = 0x0000CB30, .properties = 0, .width = 18, .height = 20 },    /* icon_Trash, 0, 0 - SD */
    { .dataOffset = 0x0000CE00, .properties = 0, .width = 128, .height = 128 },    /* IRL_Logo 128, 0, 0 - SD */
    { .dataOffset = 0x00014E00, .properties = 0, .width = 48, .height = 48 },    /* IRL_Logo_48, 0, 0 - SD */
    { .dataOffset = 0x00016000, .properties = 4, .width = 19, .height = 19 },    /* Radio-Button@C0, 100, 0 - SD */
    { .dataOffset = 0x000162D2, .properties = 4, .width = 19, .height = 19 },    /* Radio-Button@C1, 100, 0 - SD */
    { .dataOffset = 0x000165A4, .properties = 0, .width = 33, .height = 21 },    /* text_chinese_sim, 0, 0 - SD */
    { .dataOffset = 0x00016B0E, .properties = 1, .width = 72, .height = 21 },    /* text_date_time@A0, 1, 0 - SD */
    { .dataOffset = 0x000176DE, .properties = 1, .width = 76, .height = 21 },    /* text_date_time@A1, 1, 0 - SD */
    { .dataOffset = 0x00018356, .properties = 1, .width = 106, .height = 21 },    /* text_date_time@A2, 1, 0 - SD */
    { .dataOffset = 0x000194BA, .properties = 1, .width = 80, .height = 21 },    /* text_date_time@A3, 1, 0 - SD */
    { .dataOffset = 0x0001A1DA, .properties = 1, .width = 82, .height = 21 },    /* text_date_time@A4, 1, 0 - SD */
    { .dataOffset = 0x0001AF4E, .properties = 1, .width = 63, .height = 21 },    /* text_date_time@A5, 1, 0 - SD */
    { .dataOffset = 0x0001B9A4, .properties = 1, .width = 92, .height = 21 },    /* text_date_time@A6, 1, 0 - SD */
    { .dataOffset = 0x0001C8BC, .properties = 1, .width = 74, .height = 21 },    /* text_date_time@A7, 1, 0 - SD */
    { .dataOffset = 0x0001D4E0, .properties = 1, .width = 75, .height = 21 },    /* text_date_time@A8, 1, 0 - SD */
    { .dataOffset = 0x0001E12E, .properties = 1, .width = 70, .height = 21 },    /* text_date_time@A9, 1, 0 - SD */
    { .dataOffset = 0x0001ECAA, .properties = 0, .width = 16, .height = 21 },    /* text_deg_cel, 0, 0 - SD */
    { .dataOffset = 0x0001EF4A, .properties = 0, .width = 15, .height = 21 },    /* text_deg_far, 0, 0 - SD */
    { .dataOffset = 0x0001F1C0, .properties = 1, .width = 52, .height = 21 },    /* text_display@A0, 1, 0 - SD */
    { .dataOffset = 0x0001FA48, .properties = 1, .width = 94, .height = 21 },    /* text_display@A1, 1, 0 - SD */
    { .dataOffset = 0x000209B4, .properties = 1, .width = 48, .height = 21 },    /* text_display@A2, 1, 0 - SD */
    { .dataOffset = 0x00021194, .properties = 1, .width = 57, .height = 21 },    /* text_display@A3, 1, 0 - SD */
    { .dataOffset = 0x00021AEE, .properties = 1, .width = 56, .height = 21 },    /* text_display@A4, 1, 0 - SD */
    { .dataOffset = 0x0002241E, .properties = 1, .width = 55, .height = 21 },    /* text_display@A5, 1, 0 - SD */
    { .dataOffset = 0x00022D24, .properties = 1, .width = 66, .height = 21 },    /* text_display@A6, 1, 0 - SD */
    { .dataOffset = 0x000237F8, .properties = 1, .width = 34, .height = 21 },    /* text_display@A7, 1, 0 - SD */
    { .dataOffset = 0x00023D8C, .properties = 1, .width = 33, .height = 21 },    /* text_display@A8, 1, 0 - SD */
    { .dataOffset = 0x000242F6, .properties = 1, .width = 29, .height = 21 },    /* text_display@A9, 1, 0 - SD */
    { .dataOffset = 0x000247B8, .properties = 0, .width = 82, .height = 21 },    /* text_dutch, 0, 0 - SD */
    { .dataOffset = 0x0002552C, .properties = 0, .width = 51, .height = 21 },    /* text_english, 0, 0 - SD */
    { .dataOffset = 0x00025D8A, .properties = 0, .width = 61, .height = 21 },    /* text_french, 0, 0 - SD */
    { .dataOffset = 0x0002678C, .properties = 0, .width = 58, .height = 21 },    /* text_german, 0, 0 - SD */
    { .dataOffset = 0x00027110, .properties = 0, .width = 10, .height = 21 },    /* text_hashtag, 0, 0 - SD */
    { .dataOffset = 0x000272B4, .properties = 1, .width = 85, .height = 21 },    /* text_hide_date@A0, 1, 0 - SD */
    { .dataOffset = 0x000280A6, .properties = 1, .width = 124, .height = 21 },    /* text_hide_date@A1, 1, 0 - SD */
    { .dataOffset = 0x000294FE, .properties = 1, .width = 150, .height = 21 },    /* text_hide_date@A2, 1, 0 - SD */
    { .dataOffset = 0x0002AD9A, .properties = 1, .width = 104, .height = 21 },    /* text_hide_date@A3, 1, 0 - SD */
    { .dataOffset = 0x0002BEAA, .properties = 1, .width = 92, .height = 21 },    /* text_hide_date@A4, 1, 0 - SD */
    { .dataOffset = 0x0002CDC2, .properties = 1, .width = 103, .height = 21 },    /* text_hide_date@A5, 1, 0 - SD */
    { .dataOffset = 0x0002DEA8, .properties = 1, .width = 98, .height = 21 },    /* text_hide_date@A6, 1, 0 - SD */
    { .dataOffset = 0x0002EEBC, .properties = 1, .width = 70, .height = 21 },    /* text_hide_date@A7, 1, 0 - SD */
    { .dataOffset = 0x0002FA38, .properties = 1, .width = 86, .height = 21 },    /* text_hide_date@A8, 1, 0 - SD */
    { .dataOffset = 0x00030854, .properties = 1, .width = 69, .height = 21 },    /* text_hide_date@A9, 1, 0 - SD */
    { .dataOffset = 0x000313A6, .properties = 1, .width = 89, .height = 21 },    /* text_hide_time@A0, 1, 0 - SD */
    { .dataOffset = 0x00032240, .properties = 1, .width = 103, .height = 21 },    /* text_hide_time@A1, 1, 0 - SD */
    { .dataOffset = 0x00033326, .properties = 1, .width = 116, .height = 21 },    /* text_hide_time@A2, 1, 0 - SD */
    { .dataOffset = 0x0003462E, .properties = 1, .width = 98, .height = 21 },    /* text_hide_time@A3, 1, 0 - SD */
    { .dataOffset = 0x00035642, .properties = 1, .width = 105, .height = 21 },    /* text_hide_time@A4, 1, 0 - SD */
    { .dataOffset = 0x0003677C, .properties = 1, .width = 130, .height = 21 },    /* text_hide_time@A5, 1, 0 - SD */
    { .dataOffset = 0x00037CD0, .properties = 1, .width = 119, .height = 21 },    /* text_hide_time@A6, 1, 0 - SD */
    { .dataOffset = 0x00039056, .properties = 1, .width = 70, .height = 21 },    /* text_hide_time@A7, 1, 0 - SD */
    { .dataOffset = 0x00039BD2, .properties = 1, .width = 94, .height = 21 },    /* text_hide_time@A8, 1, 0 - SD */
    { .dataOffset = 0x0003AB3E, .properties = 1, .width = 85, .height = 21 },    /* text_hide_time@A9, 1, 0 - SD */
    { .dataOffset = 0x0003B930, .properties = 0, .width = 13, .height = 21 },    /* text_id, 0, 0 - SD */
    { .dataOffset = 0x0003BB52, .properties = 1, .width = 76, .height = 21 },    /* text_interval@A0, 1, 0 - SD */
    { .dataOffset = 0x0003C7CA, .properties = 1, .width = 76, .height = 21 },    /* text_interval@A1, 1, 0 - SD */
    { .dataOffset = 0x0003D442, .properties = 1, .width = 80, .height = 21 },    /* text_interval@A2, 1, 0 - SD */
    { .dataOffset = 0x0003E162, .properties = 1, .width = 89, .height = 21 },    /* text_interval@A3, 1, 0 - SD */
    { .dataOffset = 0x0003EFFC, .properties = 1, .width = 85, .height = 21 },    /* text_interval@A4, 1, 0 - SD */
    { .dataOffset = 0x0003FDEE, .properties = 1, .width = 89, .height = 21 },    /* text_interval@A5, 1, 0 - SD */
    { .dataOffset = 0x00040C88, .properties = 1, .width = 97, .height = 21 },    /* text_interval@A6, 1, 0 - SD */
    { .dataOffset = 0x00041C72, .properties = 1, .width = 58, .height = 21 },    /* text_interval@A7, 1, 0 - SD */
    { .dataOffset = 0x000425F6, .properties = 1, .width = 40, .height = 21 },    /* text_interval@A8, 1, 0 - SD */
    { .dataOffset = 0x00042C86, .properties = 1, .width = 38, .height = 21 },    /* text_interval@A9, 1, 0 - SD */
    { .dataOffset = 0x000432C2, .properties = 0, .width = 52, .height = 21 },    /* text_italian, 0, 0 - SD */
    { .dataOffset = 0x00043B4A, .properties = 0, .width = 50, .height = 21 },    /* text_japanese, 0, 0 - SD */
    { .dataOffset = 0x0004437E, .properties = 0, .width = 46, .height = 21 },    /* text_korean, 0, 0 - SD */
    { .dataOffset = 0x00044B0A, .properties = 1, .width = 70, .height = 21 },    /* text_language@A0, 1, 0 - SD */
    { .dataOffset = 0x00045686, .properties = 1, .width = 31, .height = 21 },    /* text_language@A1, 1, 0 - SD */
    { .dataOffset = 0x00045B9C, .properties = 1, .width = 59, .height = 21 },    /* text_language@A2, 1, 0 - SD */
    { .dataOffset = 0x0004654A, .properties = 1, .width = 52, .height = 21 },    /* text_language@A3, 1, 0 - SD */
    { .dataOffset = 0x00046DD2, .properties = 1, .width = 48, .height = 21 },    /* text_language@A4, 1, 0 - SD */
    { .dataOffset = 0x000475B2, .properties = 1, .width = 47, .height = 21 },    /* text_language@A5, 1, 0 - SD */
    { .dataOffset = 0x00047D68, .properties = 1, .width = 40, .height = 21 },    /* text_language@A6, 1, 0 - SD */
    { .dataOffset = 0x000483F8, .properties = 1, .width = 35, .height = 21 },    /* text_language@A7, 1, 0 - SD */
    { .dataOffset = 0x000489B6, .properties = 1, .width = 35, .height = 21 },    /* text_language@A8, 1, 0 - SD */
    { .dataOffset = 0x00048F74, .properties = 1, .width = 29, .height = 21 },    /* text_language@A9, 1, 0 - SD */
    { .dataOffset = 0x00049436, .properties = 1, .width = 120, .height = 21 },    /* text_max_data_points@A0, 1, 0 - SD */
    { .dataOffset = 0x0004A7E6, .properties = 1, .width = 125, .height = 21 },    /* text_max_data_points@A1, 1, 0 - SD */
    { .dataOffset = 0x0004BC68, .properties = 1, .width = 131, .height = 21 },    /* text_max_data_points@A2, 1, 0 - SD */
    { .dataOffset = 0x0004D1E6, .properties = 1, .width = 174, .height = 21 },    /* text_max_data_points@A3, 1, 0 - SD */
    { .dataOffset = 0x0004EE72, .properties = 1, .width = 156, .height = 21 },    /* text_max_data_points@A4, 1, 0 - SD */
    { .dataOffset = 0x0005080A, .properties = 1, .width = 219, .height = 21 },    /* text_max_data_points@A5, 1, 0 - SD */
    { .dataOffset = 0x00052BF8, .properties = 1, .width = 96, .height = 21 },    /* text_max_data_points@A6, 1, 0 - SD */
    { .dataOffset = 0x00053BB8, .properties = 1, .width = 108, .height = 21 },    /* text_max_data_points@A7, 1, 0 - SD */
    { .dataOffset = 0x00054D70, .properties = 1, .width = 132, .height = 21 },    /* text_max_data_points@A8, 1, 0 - SD */
    { .dataOffset = 0x00056318, .properties = 1, .width = 138, .height = 21 },    /* text_max_data_points@A9, 1, 0 - SD */
    { .dataOffset = 0x000579BC, .properties = 0, .width = 61, .height = 21 },    /* text_russian, 0, 0 - SD */
    { .dataOffset = 0x000583BE, .properties = 1, .width = 35, .height = 21 },    /* text_save@A0, 1, 0 - SD */
    { .dataOffset = 0x0005897C, .properties = 1, .width = 59, .height = 21 },    /* text_save@A1, 1, 0 - SD */
    { .dataOffset = 0x0005932A, .properties = 1, .width = 45, .height = 21 },    /* text_save@A2, 1, 0 - SD */
    { .dataOffset = 0x00059A8C, .properties = 1, .width = 92, .height = 21 },    /* text_save@A3, 1, 0 - SD */
    { .dataOffset = 0x0005A9A4, .properties = 1, .width = 45, .height = 21 },    /* text_save@A4, 1, 0 - SD */
    { .dataOffset = 0x0005B106, .properties = 1, .width = 53, .height = 21 },    /* text_save@A5, 1, 0 - SD */
    { .dataOffset = 0x0005B9B8, .properties = 1, .width = 63, .height = 21 },    /* text_save@A6, 1, 0 - SD */
    { .dataOffset = 0x0005C40E, .properties = 1, .width = 17, .height = 21 },    /* text_save@A7, 1, 0 - SD */
    { .dataOffset = 0x0005C6D8, .properties = 1, .width = 43, .height = 21 },    /* text_save@A8, 1, 0 - SD */
    { .dataOffset = 0x0005CDE6, .properties = 1, .width = 65, .height = 21 },    /* text_save@A9, 1, 0 - SD */
    { .dataOffset = 0x0005D890, .properties = 1, .width = 141, .height = 21 },    /* text_save_rec@A0, 1, 0 - SD */
    { .dataOffset = 0x0005EFB2, .properties = 1, .width = 120, .height = 21 },    /* text_save_rec@A1, 1, 0 - SD */
    { .dataOffset = 0x00060362, .properties = 1, .width = 141, .height = 21 },    /* text_save_rec@A2, 1, 0 - SD */
    { .dataOffset = 0x00061A84, .properties = 1, .width = 154, .height = 21 },    /* text_save_rec@A3, 1, 0 - SD */
    { .dataOffset = 0x000633C8, .properties = 1, .width = 129, .height = 21 },    /* text_save_rec@A4, 1, 0 - SD */
    { .dataOffset = 0x000648F2, .properties = 1, .width = 133, .height = 21 },    /* text_save_rec@A5, 1, 0 - SD */
    { .dataOffset = 0x00065EC4, .properties = 1, .width = 170, .height = 21 },    /* text_save_rec@A6, 1, 0 - SD */
    { .dataOffset = 0x00067AA8, .properties = 1, .width = 71, .height = 21 },    /* text_save_rec@A7, 1, 0 - SD */
    { .dataOffset = 0x0006864E, .properties = 1, .width = 104, .height = 21 },    /* text_save_rec@A8, 1, 0 - SD */
    { .dataOffset = 0x0006975E, .properties = 1, .width = 85, .height = 21 },    /* text_save_rec@A9, 1, 0 - SD */
    { .dataOffset = 0x0006A550, .properties = 1, .width = 43, .height = 21 },    /* text_saved@A0, 1, 0 - SD */
    { .dataOffset = 0x0006AC5E, .properties = 1, .width = 86, .height = 21 },    /* text_saved@A1, 1, 0 - SD */
    { .dataOffset = 0x0006BA7A, .properties = 1, .width = 87, .height = 21 },    /* text_saved@A2, 1, 0 - SD */
    { .dataOffset = 0x0006C8C0, .properties = 1, .width = 44, .height = 21 },    /* text_saved@A3, 1, 0 - SD */
    { .dataOffset = 0x0006CFF8, .properties = 1, .width = 71, .height = 21 },    /* text_saved@A4, 1, 0 - SD */
    { .dataOffset = 0x0006DB9E, .properties = 1, .width = 54, .height = 21 },    /* text_saved@A5, 1, 0 - SD */
    { .dataOffset = 0x0006E47A, .properties = 1, .width = 83, .height = 21 },    /* text_saved@A6, 1, 0 - SD */
    { .dataOffset = 0x0006F218, .properties = 1, .width = 35, .height = 21 },    /* text_saved@A7, 1, 0 - SD */
    { .dataOffset = 0x0006F7D6, .properties = 1, .width = 35, .height = 21 },    /* text_saved@A8, 1, 0 - SD */
    { .dataOffset = 0x0006FD94, .properties = 1, .width = 31, .height = 21 },    /* text_saved@A9, 1, 0 - SD */
    { .dataOffset = 0x000702AA, .properties = 1, .width = 83, .height = 21 },    /* text_show_date@A0, 1, 0 - SD */
    { .dataOffset = 0x00071048, .properties = 1, .width = 119, .height = 21 },    /* text_show_date@A1, 1, 0 - SD */
    { .dataOffset = 0x000723CE, .properties = 1, .width = 111, .height = 21 },    /* text_show_date@A2, 1, 0 - SD */
    { .dataOffset = 0x00073604, .properties = 1, .width = 83, .height = 21 },    /* text_show_date@A3, 1, 0 - SD */
    { .dataOffset = 0x000743A2, .properties = 1, .width = 93, .height = 21 },    /* text_show_date@A4, 1, 0 - SD */
    { .dataOffset = 0x000752E4, .properties = 1, .width = 87, .height = 21 },    /* text_show_date@A5, 1, 0 - SD */
    { .dataOffset = 0x0007612A, .properties = 1, .width = 107, .height = 21 },    /* text_show_date@A6, 1, 0 - SD */
    { .dataOffset = 0x000772B8, .properties = 1, .width = 70, .height = 21 },    /* text_show_date@A7, 1, 0 - SD */
    { .dataOffset = 0x00077E34, .properties = 1, .width = 71, .height = 21 },    /* text_show_date@A8, 1, 0 - SD */
    { .dataOffset = 0x000789DA, .properties = 1, .width = 102, .height = 21 },    /* text_show_date@A9, 1, 0 - SD */
    { .dataOffset = 0x00079A96, .properties = 1, .width = 87, .height = 21 },    /* text_show_time@A0, 1, 0 - SD */
    { .dataOffset = 0x0007A8DC, .properties = 1, .width = 99, .height = 21 },    /* text_show_time@A1, 1, 0 - SD */
    { .dataOffset = 0x0007B91A, .properties = 1, .width = 91, .height = 21 },    /* text_show_time@A2, 1, 0 - SD */
    { .dataOffset = 0x0007C808, .properties = 1, .width = 101, .height = 21 },    /* text_show_time@A3, 1, 0 - SD */
    { .dataOffset = 0x0007D89A, .properties = 1, .width = 106, .height = 21 },    /* text_show_time@A4, 1, 0 - SD */
    { .dataOffset = 0x0007E9FE, .properties = 1, .width = 106, .height = 21 },    /* text_show_time@A5, 1, 0 - SD */
    { .dataOffset = 0x0007FB62, .properties = 1, .width = 120, .height = 21 },    /* text_show_time@A6, 1, 0 - SD */
    { .dataOffset = 0x00080F12, .properties = 1, .width = 70, .height = 21 },    /* text_show_time@A7, 1, 0 - SD */
    { .dataOffset = 0x00081A8E, .properties = 1, .width = 122, .height = 21 },    /* text_show_time@A8, 1, 0 - SD */
    { .dataOffset = 0x00082E92, .properties = 1, .width = 102, .height = 21 },    /* text_show_time@A9, 1, 0 - SD */
    { .dataOffset = 0x00083F4E, .properties = 0, .width = 56, .height = 21 },    /* text_spanish, 0, 0 - SD */
    { .dataOffset = 0x0008487E, .properties = 1, .width = 37, .height = 21 },    /* text_units@A0, 1, 0 - SD */
    { .dataOffset = 0x00084E90, .properties = 1, .width = 70, .height = 21 },    /* text_units@A1, 1, 0 - SD */
    { .dataOffset = 0x00085A0C, .properties = 1, .width = 65, .height = 21 },    /* text_units@A2, 1, 0 - SD */
    { .dataOffset = 0x000864B6, .properties = 1, .width = 45, .height = 21 },    /* text_units@A3, 1, 0 - SD */
    { .dataOffset = 0x00086C18, .properties = 1, .width = 68, .height = 21 },    /* text_units@A4, 1, 0 - SD */
    { .dataOffset = 0x00087740, .properties = 1, .width = 37, .height = 21 },    /* text_units@A5, 1, 0 - SD */
    { .dataOffset = 0x00087D52, .properties = 1, .width = 56, .height = 21 },    /* text_units@A6, 1, 0 - SD */
    { .dataOffset = 0x00088682, .properties = 1, .width = 35, .height = 21 },    /* text_units@A7, 1, 0 - SD */
    { .dataOffset = 0x00088C40, .properties = 1, .width = 35, .height = 21 },    /* text_units@A8, 1, 0 - SD */
    { .dataOffset = 0x000891FE, .properties = 1, .width = 29, .height = 21 },    /* text_units@A9, 1, 0 - SD */
    { .dataOffset = 0x000896C0, .properties = 1, .width = 86, .height = 23 },    /* title_brightness@A0, 1, 0 - SD */
    { .dataOffset = 0x0008A634, .properties = 1, .width = 87, .height = 23 },    /* title_brightness@A1, 1, 0 - SD */
    { .dataOffset = 0x0008B5D6, .properties = 1, .width = 75, .height = 23 },    /* title_brightness@A2, 1, 0 - SD */
    { .dataOffset = 0x0008C350, .properties = 1, .width = 90, .height = 23 },    /* title_brightness@A3, 1, 0 - SD */
    { .dataOffset = 0x0008D37C, .properties = 1, .width = 40, .height = 23 },    /* title_brightness@A4, 1, 0 - SD */
    { .dataOffset = 0x0008DAAC, .properties = 1, .width = 90, .height = 23 },    /* title_brightness@A5, 1, 0 - SD */
    { .dataOffset = 0x0008EAD8, .properties = 1, .width = 71, .height = 23 },    /* title_brightness@A6, 1, 0 - SD */
    { .dataOffset = 0x0008F79A, .properties = 1, .width = 39, .height = 23 },    /* title_brightness@A7, 1, 0 - SD */
    { .dataOffset = 0x0008FE9C, .properties = 1, .width = 48, .height = 23 },    /* title_brightness@A8, 1, 0 - SD */
    { .dataOffset = 0x0009073C, .properties = 1, .width = 32, .height = 23 },    /* title_brightness@A9, 1, 0 - SD */
    { .dataOffset = 0x00090CFC, .properties = 1, .width = 128, .height = 23 },    /* title_calibrate_touch@A0, 1, 0 - SD */
    { .dataOffset = 0x000923FC, .properties = 1, .width = 134, .height = 23 },    /* title_calibrate_touch@A1, 1, 0 - SD */
    { .dataOffset = 0x00093C10, .properties = 1, .width = 155, .height = 23 },    /* title_calibrate_touch@A2, 1, 0 - SD */
    { .dataOffset = 0x000957EA, .properties = 1, .width = 132, .height = 23 },    /* title_calibrate_touch@A3, 1, 0 - SD */
    { .dataOffset = 0x00096FA2, .properties = 1, .width = 128, .height = 23 },    /* title_calibrate_touch@A4, 1, 0 - SD */
    { .dataOffset = 0x000986A2, .properties = 1, .width = 107, .height = 23 },    /* title_calibrate_touch@A5, 1, 0 - SD */
    { .dataOffset = 0x000999DC, .properties = 1, .width = 266, .height = 23 },    /* title_calibrate_touch@A6, 1, 0 - SD */
    { .dataOffset = 0x0009C9A8, .properties = 1, .width = 81, .height = 23 },    /* title_calibrate_touch@A7, 1, 0 - SD */
    { .dataOffset = 0x0009D836, .properties = 1, .width = 190, .height = 23 },    /* title_calibrate_touch@A8, 1, 0 - SD */
    { .dataOffset = 0x0009FA5A, .properties = 1, .width = 74, .height = 23 },    /* title_calibrate_touch@A9, 1, 0 - SD */
    { .dataOffset = 0x000A07A6, .properties = 1, .width = 81, .height = 23 },    /* title_date_time@A0, 1, 0 - SD */
    { .dataOffset = 0x000A1634, .properties = 1, .width = 86, .height = 23 },    /* title_date_time@A1, 1, 0 - SD */
    { .dataOffset = 0x000A25A8, .properties = 1, .width = 119, .height = 23 },    /* title_date_time@A2, 1, 0 - SD */
    { .dataOffset = 0x000A3B0A, .properties = 1, .width = 91, .height = 23 },    /* title_date_time@A3, 1, 0 - SD */
    { .dataOffset = 0x000A4B64, .properties = 1, .width = 93, .height = 23 },    /* title_date_time@A4, 1, 0 - SD */
    { .dataOffset = 0x000A5C1A, .properties = 1, .width = 71, .height = 23 },    /* title_date_time@A5, 1, 0 - SD */
    { .dataOffset = 0x000A68DC, .properties = 1, .width = 104, .height = 23 },    /* title_date_time@A6, 1, 0 - SD */
    { .dataOffset = 0x000A7B8C, .properties = 1, .width = 84, .height = 23 },    /* title_date_time@A7, 1, 0 - SD */
    { .dataOffset = 0x000A8AA4, .properties = 1, .width = 84, .height = 23 },    /* title_date_time@A8, 1, 0 - SD */
    { .dataOffset = 0x000A99BC, .properties = 1, .width = 79, .height = 23 },    /* title_date_time@A9, 1, 0 - SD */
    { .dataOffset = 0x000AA7EE, .properties = 0, .width = 15, .height = 23 },    /* title_id, 0, 0 - SD */
    { .dataOffset = 0x000AAAA0, .properties = 1, .width = 80, .height = 23 },    /* title_language@A0, 1, 0 - SD */
    { .dataOffset = 0x000AB900, .properties = 1, .width = 35, .height = 23 },    /* title_language@A1, 1, 0 - SD */
    { .dataOffset = 0x000ABF4A, .properties = 1, .width = 67, .height = 23 },    /* title_language@A2, 1, 0 - SD */
    { .dataOffset = 0x000ACB54, .properties = 1, .width = 59, .height = 23 },    /* title_language@A3, 1, 0 - SD */
    { .dataOffset = 0x000AD5EE, .properties = 1, .width = 55, .height = 23 },    /* title_language@A4, 1, 0 - SD */
    { .dataOffset = 0x000ADFD0, .properties = 1, .width = 53, .height = 23 },    /* title_language@A5, 1, 0 - SD */
    { .dataOffset = 0x000AE956, .properties = 1, .width = 45, .height = 23 },    /* title_language@A6, 1, 0 - SD */
    { .dataOffset = 0x000AF16C, .properties = 1, .width = 39, .height = 23 },    /* title_language@A7, 1, 0 - SD */
    { .dataOffset = 0x000AF86E, .properties = 1, .width = 39, .height = 23 },    /* title_language@A8, 1, 0 - SD */
    { .dataOffset = 0x000AFF70, .properties = 1, .width = 32, .height = 23 },    /* title_language@A9, 1, 0 - SD */
    { .dataOffset = 0x000B0530, .properties = 1, .width = 122, .height = 23 },    /* title_measurements@A0, 1, 0 - SD */
    { .dataOffset = 0x000B1B1C, .properties = 1, .width = 85, .height = 23 },    /* title_measurements@A1, 1, 0 - SD */
    { .dataOffset = 0x000B2A62, .properties = 1, .width = 94, .height = 23 },    /* title_measurements@A2, 1, 0 - SD */
    { .dataOffset = 0x000B3B46, .properties = 1, .width = 112, .height = 23 },    /* title_measurements@A3, 1, 0 - SD */
    { .dataOffset = 0x000B4F66, .properties = 1, .width = 69, .height = 23 },    /* title_measurements@A4, 1, 0 - SD */
    { .dataOffset = 0x000B5BCC, .properties = 1, .width = 55, .height = 23 },    /* title_measurements@A5, 1, 0 - SD */
    { .dataOffset = 0x000B65AE, .properties = 1, .width = 96, .height = 23 },    /* title_measurements@A6, 1, 0 - SD */
    { .dataOffset = 0x000B76EE, .properties = 1, .width = 40, .height = 23 },    /* title_measurements@A7, 1, 0 - SD */
    { .dataOffset = 0x000B7E1E, .properties = 1, .width = 38, .height = 23 },    /* title_measurements@A8, 1, 0 - SD */
    { .dataOffset = 0x000B84F2, .properties = 1, .width = 33, .height = 23 },    /* title_measurements@A9, 1, 0 - SD */
    { .dataOffset = 0x000B8AE0, .properties = 1, .width = 91, .height = 23 },    /* title_recordings@A0, 1, 0 - SD */
    { .dataOffset = 0x000B9B3A, .properties = 1, .width = 78, .height = 23 },    /* title_recordings@A1, 1, 0 - SD */
    { .dataOffset = 0x000BA93E, .properties = 1, .width = 94, .height = 23 },    /* title_recordings@A2, 1, 0 - SD */
    { .dataOffset = 0x000BBA22, .properties = 1, .width = 134, .height = 23 },    /* title_recordings@A3, 1, 0 - SD */
    { .dataOffset = 0x000BD236, .properties = 1, .width = 102, .height = 23 },    /* title_recordings@A4, 1, 0 - SD */
    { .dataOffset = 0x000BE48A, .properties = 1, .width = 105, .height = 23 },    /* title_recordings@A5, 1, 0 - SD */
    { .dataOffset = 0x000BF768, .properties = 1, .width = 62, .height = 23 },    /* title_recordings@A6, 1, 0 - SD */
    { .dataOffset = 0x000C028C, .properties = 1, .width = 39, .height = 23 },    /* title_recordings@A7, 1, 0 - SD */
    { .dataOffset = 0x000C098E, .properties = 1, .width = 39, .height = 23 },    /* title_recordings@A8, 1, 0 - SD */
    { .dataOffset = 0x000C1090, .properties = 1, .width = 35, .height = 23 },    /* title_recordings@A9, 1, 0 - SD */
    { .dataOffset = 0x000C16DA, .properties = 1, .width = 67, .height = 23 },    /* title_settings@A0, 1, 0 - SD */
    { .dataOffset = 0x000C22E4, .properties = 1, .width = 93, .height = 23 },    /* title_settings@A1, 1, 0 - SD */
    { .dataOffset = 0x000C339A, .properties = 1, .width = 109, .height = 23 },    /* title_settings@A2, 1, 0 - SD */
    { .dataOffset = 0x000C4730, .properties = 1, .width = 94, .height = 23 },    /* title_settings@A3, 1, 0 - SD */
    { .dataOffset = 0x000C5814, .properties = 1, .width = 114, .height = 23 },    /* title_settings@A4, 1, 0 - SD */
    { .dataOffset = 0x000C6C90, .properties = 1, .width = 105, .height = 23 },    /* title_settings@A5, 1, 0 - SD */
    { .dataOffset = 0x000C7F6E, .properties = 1, .width = 98, .height = 23 },    /* title_settings@A6, 1, 0 - SD */
    { .dataOffset = 0x000C910A, .properties = 1, .width = 39, .height = 23 },    /* title_settings@A7, 1, 0 - SD */
    { .dataOffset = 0x000C980C, .properties = 1, .width = 38, .height = 23 },    /* title_settings@A8, 1, 0 - SD */
    { .dataOffset = 0x000C9EE0, .properties = 1, .width = 33, .height = 23 },    /* title_settings@A9, 1, 0 - SD */
    { .dataOffset = 0x000CA4CE, .properties = 1, .width = 39, .height = 23 },    /* title_start@A0, 1, 0 - SD */
    { .dataOffset = 0x000CABD0, .properties = 1, .width = 39, .height = 23 },    /* title_start@A1, 1, 0 - SD */
    { .dataOffset = 0x000CB2D2, .properties = 1, .width = 78, .height = 23 },    /* title_start@A2, 1, 0 - SD */
    { .dataOffset = 0x000CC0D6, .properties = 1, .width = 100, .height = 23 },    /* title_start@A3, 1, 0 - SD */
    { .dataOffset = 0x000CD2CE, .properties = 1, .width = 71, .height = 23 },    /* title_start@A4, 1, 0 - SD */
    { .dataOffset = 0x000CDF90, .properties = 1, .width = 42, .height = 23 },    /* title_start@A5, 1, 0 - SD */
    { .dataOffset = 0x000CE71C, .properties = 1, .width = 63, .height = 23 },    /* title_start@A6, 1, 0 - SD */
    { .dataOffset = 0x000CF26E, .properties = 1, .width = 39, .height = 23 },    /* title_start@A7, 1, 0 - SD */
    { .dataOffset = 0x000CF970, .properties = 1, .width = 50, .height = 23 },    /* title_start@A8, 1, 0 - SD */
    { .dataOffset = 0x000D026C, .properties = 1, .width = 72, .height = 23 },    /* title_start@A9, 1, 0 - SD */
    { .dataOffset = 0x000D0F5C, .properties = 1, .width = 37, .height = 23 },    /* title_stop@A0, 1, 0 - SD */
    { .dataOffset = 0x000D1602, .properties = 1, .width = 37, .height = 23 },    /* title_stop@A1, 1, 0 - SD */
    { .dataOffset = 0x000D1CA8, .properties = 1, .width = 75, .height = 23 },    /* title_stop@A2, 1, 0 - SD */
    { .dataOffset = 0x000D2A22, .properties = 1, .width = 56, .height = 23 },    /* title_stop@A3, 1, 0 - SD */
    { .dataOffset = 0x000D3432, .properties = 1, .width = 43, .height = 23 },    /* title_stop@A4, 1, 0 - SD */
    { .dataOffset = 0x000D3BEC, .properties = 1, .width = 71, .height = 23 },    /* title_stop@A5, 1, 0 - SD */
    { .dataOffset = 0x000D48AE, .properties = 1, .width = 91, .height = 23 },    /* title_stop@A6, 1, 0 - SD */
    { .dataOffset = 0x000D5908, .properties = 1, .width = 18, .height = 23 },    /* title_stop@A7, 1, 0 - SD */
    { .dataOffset = 0x000D5C44, .properties = 1, .width = 50, .height = 23 },    /* title_stop@A8, 1, 0 - SD */
    { .dataOffset = 0x000D6540, .properties = 1, .width = 53, .height = 23 },    /* title_stop@A9, 1, 0 - SD */
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
