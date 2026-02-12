#include "fs_file_search.h"

#define FS_FILE_INFO_SIZE 9
#define FS_FILE_DUMMY 0xFFFFFFFFU

const fs_file_info_s fs_file_infos[] =
{
    { .dataOffset = 20, .properties = 2, .width = 32, .height = 27 },    /* IRL-Logo_@B000, 10 */
    { .dataOffset = 1748, .properties = 2, .width = 36, .height = 29 },    /* IRL-Logo_@B001, 10 */
    { .dataOffset = 3836, .properties = 2, .width = 39, .height = 32 },    /* IRL-Logo_@B002, 10 */
    { .dataOffset = 6332, .properties = 2, .width = 42, .height = 35 },    /* IRL-Logo_@B003, 10 */
    { .dataOffset = 9272, .properties = 2, .width = 46, .height = 37 },    /* IRL-Logo_@B004, 10 */
    { .dataOffset = 12676, .properties = 2, .width = 49, .height = 40 },    /* IRL-Logo_@B005, 10 */
    { .dataOffset = 16596, .properties = 2, .width = 52, .height = 43 },    /* IRL-Logo_@B006, 10 */
    { .dataOffset = 21068, .properties = 2, .width = 56, .height = 46 },    /* IRL-Logo_@B007, 10 */
    { .dataOffset = 26220, .properties = 2, .width = 59, .height = 48 },    /* IRL-Logo_@B008, 10 */
    { .dataOffset = 31884, .properties = 2, .width = 62, .height = 50 },    /* IRL-Logo_@B009, 10 */
    { .dataOffset = 38084, .properties = 2, .width = 65, .height = 54 },    /* IRL-Logo_@B010, 10 */
    { .dataOffset = 45104, .properties = 2, .width = 69, .height = 56 },    /* IRL-Logo_@B011, 10 */
    { .dataOffset = 52832, .properties = 2, .width = 72, .height = 59 },    /* IRL-Logo_@B012, 10 */
    { .dataOffset = 61328, .properties = 2, .width = 76, .height = 62 },    /* IRL-Logo_@B013, 10 */
    { .dataOffset = 70752, .properties = 2, .width = 79, .height = 64 },    /* IRL-Logo_@B014, 10 */
    { .dataOffset = 80864, .properties = 2, .width = 82, .height = 67 },    /* IRL-Logo_@B015, 10 */
    { .dataOffset = 91852, .properties = 2, .width = 86, .height = 69 },    /* IRL-Logo_@B016, 10 */
    { .dataOffset = 103720, .properties = 2, .width = 89, .height = 72 },    /* IRL-Logo_@B017, 10 */
    { .dataOffset = 116536, .properties = 2, .width = 92, .height = 75 },    /* IRL-Logo_@B018, 10 */
    { .dataOffset = 130336, .properties = 2, .width = 95, .height = 77 },    /* IRL-Logo_@B019, 10 */
    { .dataOffset = 144966, .properties = 2, .width = 100, .height = 80 },    /* IRL-Logo_@B020, 10 */
    { .dataOffset = 160966, .properties = 2, .width = 102, .height = 83 },    /* IRL-Logo_@B021, 10 */
    { .dataOffset = 177898, .properties = 2, .width = 105, .height = 85 },    /* IRL-Logo_@B022, 10 */
    { .dataOffset = 195748, .properties = 2, .width = 109, .height = 88 },    /* IRL-Logo_@B023, 10 */
    { .dataOffset = 214932, .properties = 1, .width = 146, .height = 38 },    /* Footer_Button@A0, 1 */
    { .dataOffset = 226028, .properties = 1, .width = 146, .height = 38 },    /* Footer_Button@A1, 1 */
    { .dataOffset = 237124, .properties = 1, .width = 30, .height = 30 },    /* NumInput_minus@A0, 1 */
    { .dataOffset = 238924, .properties = 1, .width = 30, .height = 30 },    /* NumInput_minus@A1, 1 */
    { .dataOffset = 240724, .properties = 1, .width = 30, .height = 30 },    /* NumInput_plus@A0, 1 */
    { .dataOffset = 242524, .properties = 1, .width = 30, .height = 30 },    /* NumInput_plus@A1, 1 */
    { .dataOffset = 244324, .properties = 1, .width = 146, .height = 90 },    /* Page_Background@A0, 1 */
    { .dataOffset = 270604, .properties = 1, .width = 146, .height = 90 },    /* Page_Background@A1, 1 */
    { .dataOffset = 296884, .properties = 1, .width = 22, .height = 31 },    /* Slider@A0, 1 */
    { .dataOffset = 298248, .properties = 1, .width = 22, .height = 31 },    /* Slider@A1, 1 */
    { .dataOffset = 299612, .properties = 17, .width = 18, .height = 20 },    /* icon_button_Agenda@A0_E0, 10001 */
    { .dataOffset = 300332, .properties = 17, .width = 18, .height = 20 },    /* icon_button_Agenda@A0_E1, 10001 */
    { .dataOffset = 301052, .properties = 17, .width = 18, .height = 20 },    /* icon_button_Agenda@A0_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_AGENDA__A000_E003, 11 */
    { .dataOffset = 301772, .properties = 17, .width = 18, .height = 20 },    /* icon_button_Agenda@A1_E0, 10001 */
    { .dataOffset = 302492, .properties = 17, .width = 18, .height = 20 },    /* icon_button_Agenda@A1_E1, 10001 */
    { .dataOffset = 303212, .properties = 17, .width = 18, .height = 20 },    /* icon_button_Agenda@A1_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_AGENDA__A001_E003, 11 */
    { .dataOffset = 303932, .properties = 17, .width = 35, .height = 18 },    /* icon_button_Arrow-Back@A0_E0, 10001 */
    { .dataOffset = 305192, .properties = 17, .width = 35, .height = 18 },    /* icon_button_Arrow-Back@A0_E1, 10001 */
    { .dataOffset = 306452, .properties = 17, .width = 35, .height = 18 },    /* icon_button_Arrow-Back@A0_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_ARROW_BACK__A000_E003, 11 */
    { .dataOffset = 307712, .properties = 17, .width = 35, .height = 18 },    /* icon_button_Arrow-Back@A1_E0, 10001 */
    { .dataOffset = 308972, .properties = 17, .width = 35, .height = 18 },    /* icon_button_Arrow-Back@A1_E1, 10001 */
    { .dataOffset = 310232, .properties = 17, .width = 35, .height = 18 },    /* icon_button_Arrow-Back@A1_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_ARROW_BACK__A001_E003, 11 */
    { .dataOffset = 311492, .properties = 17, .width = 16, .height = 18 },    /* icon_button_Bell@A0_E0, 10001 */
    { .dataOffset = 312068, .properties = 17, .width = 16, .height = 18 },    /* icon_button_Bell@A0_E1, 10001 */
    { .dataOffset = 312644, .properties = 17, .width = 16, .height = 18 },    /* icon_button_Bell@A0_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_BELL__A000_E003, 11 */
    { .dataOffset = 313220, .properties = 17, .width = 16, .height = 18 },    /* icon_button_Bell@A1_E0, 10001 */
    { .dataOffset = 313796, .properties = 17, .width = 16, .height = 18 },    /* icon_button_Bell@A1_E1, 10001 */
    { .dataOffset = 314372, .properties = 17, .width = 16, .height = 18 },    /* icon_button_Bell@A1_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_BELL__A001_E003, 11 */
    { .dataOffset = 314948, .properties = 17, .width = 30, .height = 25 },    /* icon_button_Brightness@A0_E0, 10001 */
    { .dataOffset = 316448, .properties = 17, .width = 30, .height = 25 },    /* icon_button_Brightness@A0_E1, 10001 */
    { .dataOffset = 317948, .properties = 17, .width = 30, .height = 25 },    /* icon_button_Brightness@A0_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_BRIGHTNESS__A000_E003, 11 */
    { .dataOffset = 319448, .properties = 17, .width = 30, .height = 25 },    /* icon_button_Brightness@A1_E0, 10001 */
    { .dataOffset = 320948, .properties = 17, .width = 30, .height = 25 },    /* icon_button_Brightness@A1_E1, 10001 */
    { .dataOffset = 322448, .properties = 17, .width = 30, .height = 25 },    /* icon_button_Brightness@A1_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_BRIGHTNESS__A001_E003, 11 */
    { .dataOffset = 323948, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Brush@A0_E0, 10001 */
    { .dataOffset = 324916, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Brush@A0_E1, 10001 */
    { .dataOffset = 325884, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Brush@A0_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_BRUSH__A000_E003, 11 */
    { .dataOffset = 326852, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Brush@A1_E0, 10001 */
    { .dataOffset = 327820, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Brush@A1_E1, 10001 */
    { .dataOffset = 328788, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Brush@A1_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_BRUSH__A001_E003, 11 */
    { .dataOffset = 329756, .properties = 17, .width = 18, .height = 18 },    /* icon_button_Cancel@A0_E0, 10001 */
    { .dataOffset = 330404, .properties = 17, .width = 18, .height = 18 },    /* icon_button_Cancel@A0_E1, 10001 */
    { .dataOffset = 331052, .properties = 17, .width = 18, .height = 18 },    /* icon_button_Cancel@A0_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_CANCEL__A000_E003, 11 */
    { .dataOffset = 331700, .properties = 17, .width = 18, .height = 18 },    /* icon_button_Cancel@A1_E0, 10001 */
    { .dataOffset = 332348, .properties = 17, .width = 18, .height = 18 },    /* icon_button_Cancel@A1_E1, 10001 */
    { .dataOffset = 332996, .properties = 17, .width = 18, .height = 18 },    /* icon_button_Cancel@A1_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_CANCEL__A001_E003, 11 */
    { .dataOffset = 333644, .properties = 17, .width = 26, .height = 21 },    /* icon_button_Checkmark_large@A0_E0, 10001 */
    { .dataOffset = 334736, .properties = 17, .width = 26, .height = 21 },    /* icon_button_Checkmark_large@A0_E1, 10001 */
    { .dataOffset = 335828, .properties = 17, .width = 26, .height = 21 },    /* icon_button_Checkmark_large@A0_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_CHECKMARK_LARGE__A000_E003, 11 */
    { .dataOffset = 336920, .properties = 17, .width = 26, .height = 21 },    /* icon_button_Checkmark_large@A1_E0, 10001 */
    { .dataOffset = 338012, .properties = 17, .width = 26, .height = 21 },    /* icon_button_Checkmark_large@A1_E1, 10001 */
    { .dataOffset = 339104, .properties = 17, .width = 26, .height = 21 },    /* icon_button_Checkmark_large@A1_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_CHECKMARK_LARGE__A001_E003, 11 */
    { .dataOffset = 340196, .properties = 17, .width = 20, .height = 20 },    /* icon_button_Clock@A0_E0, 10001 */
    { .dataOffset = 340996, .properties = 17, .width = 20, .height = 20 },    /* icon_button_Clock@A0_E1, 10001 */
    { .dataOffset = 341796, .properties = 17, .width = 20, .height = 20 },    /* icon_button_Clock@A0_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_CLOCK__A000_E003, 11 */
    { .dataOffset = 342596, .properties = 17, .width = 20, .height = 20 },    /* icon_button_Clock@A1_E0, 10001 */
    { .dataOffset = 343396, .properties = 17, .width = 20, .height = 20 },    /* icon_button_Clock@A1_E1, 10001 */
    { .dataOffset = 344196, .properties = 17, .width = 20, .height = 20 },    /* icon_button_Clock@A1_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_CLOCK__A001_E003, 11 */
    { .dataOffset = 344996, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Focus@A0_E0, 10001 */
    { .dataOffset = 345964, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Focus@A0_E1, 10001 */
    { .dataOffset = 346932, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Focus@A0_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_FOCUS__A000_E003, 11 */
    { .dataOffset = 347900, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Focus@A1_E0, 10001 */
    { .dataOffset = 348868, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Focus@A1_E1, 10001 */
    { .dataOffset = 349836, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Focus@A1_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_FOCUS__A001_E003, 11 */
    { .dataOffset = 350804, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Gear@A0_E0, 10001 */
    { .dataOffset = 351772, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Gear@A0_E1, 10001 */
    { .dataOffset = 352740, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Gear@A0_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_GEAR__A000_E003, 11 */
    { .dataOffset = 353708, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Gear@A1_E0, 10001 */
    { .dataOffset = 354676, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Gear@A1_E1, 10001 */
    { .dataOffset = 355644, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Gear@A1_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_GEAR__A001_E003, 11 */
    { .dataOffset = 356612, .properties = 17, .width = 20, .height = 20 },    /* icon_button_Global@A0_E0, 10001 */
    { .dataOffset = 357412, .properties = 17, .width = 20, .height = 20 },    /* icon_button_Global@A0_E1, 10001 */
    { .dataOffset = 358212, .properties = 17, .width = 20, .height = 20 },    /* icon_button_Global@A0_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_GLOBAL__A000_E003, 11 */
    { .dataOffset = 359012, .properties = 17, .width = 20, .height = 20 },    /* icon_button_Global@A1_E0, 10001 */
    { .dataOffset = 359812, .properties = 17, .width = 20, .height = 20 },    /* icon_button_Global@A1_E1, 10001 */
    { .dataOffset = 360612, .properties = 17, .width = 20, .height = 20 },    /* icon_button_Global@A1_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_GLOBAL__A001_E003, 11 */
    { .dataOffset = 361412, .properties = 17, .width = 21, .height = 21 },    /* icon_button_Info@A0_E0, 10001 */
    { .dataOffset = 362294, .properties = 17, .width = 21, .height = 21 },    /* icon_button_Info@A0_E1, 10001 */
    { .dataOffset = 363176, .properties = 17, .width = 21, .height = 21 },    /* icon_button_Info@A0_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_INFO__A000_E003, 11 */
    { .dataOffset = 364058, .properties = 17, .width = 21, .height = 21 },    /* icon_button_Info@A1_E0, 10001 */
    { .dataOffset = 364940, .properties = 17, .width = 21, .height = 21 },    /* icon_button_Info@A1_E1, 10001 */
    { .dataOffset = 365822, .properties = 17, .width = 21, .height = 21 },    /* icon_button_Info@A1_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_INFO__A001_E003, 11 */
    { .dataOffset = 366704, .properties = 17, .width = 23, .height = 16 },    /* icon_button_Keyboard@A0_E0, 10001 */
    { .dataOffset = 367440, .properties = 17, .width = 23, .height = 16 },    /* icon_button_Keyboard@A0_E1, 10001 */
    { .dataOffset = 368176, .properties = 17, .width = 23, .height = 16 },    /* icon_button_Keyboard@A0_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_KEYBOARD__A000_E003, 11 */
    { .dataOffset = 368912, .properties = 17, .width = 23, .height = 16 },    /* icon_button_Keyboard@A1_E0, 10001 */
    { .dataOffset = 369648, .properties = 17, .width = 23, .height = 16 },    /* icon_button_Keyboard@A1_E1, 10001 */
    { .dataOffset = 370384, .properties = 17, .width = 23, .height = 16 },    /* icon_button_Keyboard@A1_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_KEYBOARD__A001_E003, 11 */
    { .dataOffset = 371120, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Palette@A0_E0, 10001 */
    { .dataOffset = 372088, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Palette@A0_E1, 10001 */
    { .dataOffset = 373056, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Palette@A0_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_PALETTE__A000_E003, 11 */
    { .dataOffset = 374024, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Palette@A1_E0, 10001 */
    { .dataOffset = 374992, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Palette@A1_E1, 10001 */
    { .dataOffset = 375960, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Palette@A1_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_PALETTE__A001_E003, 11 */
    { .dataOffset = 376928, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Sliders@A0_E0, 10001 */
    { .dataOffset = 377896, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Sliders@A0_E1, 10001 */
    { .dataOffset = 378864, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Sliders@A0_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_SLIDERS__A000_E003, 11 */
    { .dataOffset = 379832, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Sliders@A1_E0, 10001 */
    { .dataOffset = 380800, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Sliders@A1_E1, 10001 */
    { .dataOffset = 381768, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Sliders@A1_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_SLIDERS__A001_E003, 11 */
    { .dataOffset = 382736, .properties = 1, .width = 16, .height = 18 },    /* icon_header_Bell@A0, 1 */
    { .dataOffset = 383312, .properties = 1, .width = 16, .height = 18 },    /* icon_header_Bell@A1, 1 */
    { .dataOffset = 383888, .properties = 1, .width = 20, .height = 20 },    /* icon_header_Clock@A0, 1 */
    { .dataOffset = 384688, .properties = 1, .width = 20, .height = 20 },    /* icon_header_Clock@A1, 1 */
    { .dataOffset = 385488, .properties = 1, .width = 25, .height = 18 },    /* icon_header_Wifi@A0, 1 */
    { .dataOffset = 386388, .properties = 1, .width = 25, .height = 18 },    /* icon_header_Wifi@A1, 1 */
    { .dataOffset = 387288, .properties = 1, .width = 13, .height = 4 },    /* icon_pane_Arrow_down@A0, 1 */
    { .dataOffset = 387392, .properties = 1, .width = 13, .height = 4 },    /* icon_pane_Arrow_down@A1, 1 */
    { .dataOffset = 387496, .properties = 1, .width = 12, .height = 4 },    /* icon_pane_Arrow_up@A0, 1 */
    { .dataOffset = 387592, .properties = 1, .width = 12, .height = 4 },    /* icon_pane_Arrow_up@A1, 1 */
    { .dataOffset = 387688, .properties = 1, .width = 16, .height = 13 },    /* icon_pane_Checkmark@A0, 1 */
    { .dataOffset = 388104, .properties = 1, .width = 16, .height = 13 },    /* icon_pane_Checkmark@A1, 1 */
    { .dataOffset = 388520, .properties = 1, .width = 16, .height = 4 },    /* icon_pane_minus@A0, 1 */
    { .dataOffset = 388648, .properties = 1, .width = 16, .height = 4 },    /* icon_pane_minus@A1, 1 */
    { .dataOffset = 388776, .properties = 1, .width = 16, .height = 16 },    /* icon_pane_plus@A0, 1 */
    { .dataOffset = 389288, .properties = 1, .width = 16, .height = 16 },    /* icon_pane_plus@A1, 1 */
    { .dataOffset = 389800, .properties = 17, .width = 18, .height = 18 },    /* icon_pane_Radio-Button-Checked@A0_E0, 10001 */
    { .dataOffset = 390448, .properties = 17, .width = 18, .height = 18 },    /* icon_pane_Radio-Button-Checked@A0_E1, 10001 */
    { .dataOffset = 391096, .properties = 17, .width = 18, .height = 18 },    /* icon_pane_Radio-Button-Checked@A0_E2, 10001 */
    { .dataOffset = 391744, .properties = 17, .width = 18, .height = 18 },    /* icon_pane_Radio-Button-Checked@A0_E3, 10001 */
    { .dataOffset = 392392, .properties = 17, .width = 18, .height = 18 },    /* icon_pane_Radio-Button-Checked@A1_E0, 10001 */
    { .dataOffset = 393040, .properties = 17, .width = 18, .height = 18 },    /* icon_pane_Radio-Button-Checked@A1_E1, 10001 */
    { .dataOffset = 393688, .properties = 17, .width = 18, .height = 18 },    /* icon_pane_Radio-Button-Checked@A1_E2, 10001 */
    { .dataOffset = 394336, .properties = 17, .width = 18, .height = 18 },    /* icon_pane_Radio-Button-Checked@A1_E3, 10001 */
    { .dataOffset = 394984, .properties = 17, .width = 18, .height = 18 },    /* icon_pane_Radio-Button-UnChecked@A0_E0, 10001 */
    { .dataOffset = 395632, .properties = 17, .width = 18, .height = 18 },    /* icon_pane_Radio-Button-UnChecked@A0_E1, 10001 */
    { .dataOffset = 396280, .properties = 17, .width = 18, .height = 18 },    /* icon_pane_Radio-Button-UnChecked@A0_E2, 10001 */
    { .dataOffset = 396928, .properties = 17, .width = 18, .height = 18 },    /* icon_pane_Radio-Button-UnChecked@A0_E3, 10001 */
    { .dataOffset = 397576, .properties = 17, .width = 18, .height = 18 },    /* icon_pane_Radio-Button-UnChecked@A1_E0, 10001 */
    { .dataOffset = 398224, .properties = 17, .width = 18, .height = 18 },    /* icon_pane_Radio-Button-UnChecked@A1_E1, 10001 */
    { .dataOffset = 398872, .properties = 17, .width = 18, .height = 18 },    /* icon_pane_Radio-Button-UnChecked@A1_E2, 10001 */
    { .dataOffset = 399520, .properties = 17, .width = 18, .height = 18 },    /* icon_pane_Radio-Button-UnChecked@A1_E3, 10001 */
    { .dataOffset = 400168, .properties = 0, .width = 128, .height = 128 },    /* IRL_Logo 128, 0 */
    { .dataOffset = 432936, .properties = 0, .width = 48, .height = 48 },    /* IRL_Logo_48, 0 */
    { .dataOffset = 437544, .properties = 1, .width = 480, .height = 236 },    /* Keyboard_lc@A0, 1 */
    { .dataOffset = 664104, .properties = 1, .width = 480, .height = 236 },    /* Keyboard_lc@A1, 1 */
    { .dataOffset = 890664, .properties = 1, .width = 480, .height = 236 },    /* Keyboard_num@A0, 1 */
    { .dataOffset = 1117224, .properties = 1, .width = 480, .height = 236 },    /* Keyboard_num@A1, 1 */
    { .dataOffset = 1343784, .properties = 1, .width = 480, .height = 84 },    /* Keyboard_textbox@A0, 1 */
    { .dataOffset = 1424424, .properties = 1, .width = 480, .height = 84 },    /* Keyboard_textbox@A1, 1 */
    { .dataOffset = 1505064, .properties = 1, .width = 480, .height = 236 },    /* Keyboard_uc@A0, 1 */
    { .dataOffset = 1731624, .properties = 1, .width = 480, .height = 236 },    /* Keyboard_uc@A1, 1 */
    { .dataOffset = 1958184, .properties = 5, .width = 92, .height = 21 },    /* text_accent_color@C0_A0, 101 */
    { .dataOffset = 1962048, .properties = 5, .width = 91, .height = 21 },    /* text_accent_color@C1_A0, 101 */
    { .dataOffset = 1965870, .properties = 5, .width = 131, .height = 21 },    /* text_accent_color@C2_A0, 101 */
    { .dataOffset = 1971372, .properties = 5, .width = 167, .height = 21 },    /* text_accent_color@C3_A0, 101 */
    { .dataOffset = 1978386, .properties = 5, .width = 115, .height = 21 },    /* text_accent_color@C4_A0, 101 */
    { .dataOffset = 1983216, .properties = 5, .width = 122, .height = 21 },    /* text_accent_color@C5_A0, 101 */
    { .dataOffset = 1988340, .properties = 5, .width = 127, .height = 21 },    /* text_accent_color@C6_A0, 101 */
    { .dataOffset = 1993674, .properties = 5, .width = 50, .height = 21 },    /* text_accent_color@C7_A0, 101 */
    { .dataOffset = 1995774, .properties = 5, .width = 106, .height = 21 },    /* text_accent_color@C8_A0, 101 */
    { .dataOffset = 2000226, .properties = 5, .width = 68, .height = 21 },    /* text_accent_color@C9_A0, 101 */
    { .dataOffset = 2003082, .properties = 5, .width = 92, .height = 21 },    /* text_accent_color@C0_A1, 101 */
    { .dataOffset = 2006946, .properties = 5, .width = 91, .height = 21 },    /* text_accent_color@C1_A1, 101 */
    { .dataOffset = 2010768, .properties = 5, .width = 131, .height = 21 },    /* text_accent_color@C2_A1, 101 */
    { .dataOffset = 2016270, .properties = 5, .width = 167, .height = 21 },    /* text_accent_color@C3_A1, 101 */
    { .dataOffset = 2023284, .properties = 5, .width = 115, .height = 21 },    /* text_accent_color@C4_A1, 101 */
    { .dataOffset = 2028114, .properties = 5, .width = 122, .height = 21 },    /* text_accent_color@C5_A1, 101 */
    { .dataOffset = 2033238, .properties = 5, .width = 127, .height = 21 },    /* text_accent_color@C6_A1, 101 */
    { .dataOffset = 2038572, .properties = 5, .width = 50, .height = 21 },    /* text_accent_color@C7_A1, 101 */
    { .dataOffset = 2040672, .properties = 5, .width = 106, .height = 21 },    /* text_accent_color@C8_A1, 101 */
    { .dataOffset = 2045124, .properties = 5, .width = 68, .height = 21 },    /* text_accent_color@C9_A1, 101 */
    { .dataOffset = 2047980, .properties = 5, .width = 55, .height = 21 },    /* text_alarm@C0_A0, 101 */
    { .dataOffset = 2050290, .properties = 5, .width = 55, .height = 21 },    /* text_alarm@C1_A0, 101 */
    { .dataOffset = 2052600, .properties = 5, .width = 55, .height = 21 },    /* text_alarm@C2_A0, 101 */
    { .dataOffset = 2054910, .properties = 5, .width = 64, .height = 21 },    /* text_alarm@C3_A0, 101 */
    { .dataOffset = 2057598, .properties = 5, .width = 64, .height = 21 },    /* text_alarm@C4_A0, 101 */
    { .dataOffset = 2060286, .properties = 5, .width = 68, .height = 21 },    /* text_alarm@C5_A0, 101 */
    { .dataOffset = 2063142, .properties = 5, .width = 74, .height = 21 },    /* text_alarm@C6_A0, 101 */
    { .dataOffset = 2066250, .properties = 5, .width = 48, .height = 21 },    /* text_alarm@C7_A0, 101 */
    { .dataOffset = 2068266, .properties = 5, .width = 47, .height = 21 },    /* text_alarm@C8_A0, 101 */
    { .dataOffset = 2070240, .properties = 5, .width = 60, .height = 21 },    /* text_alarm@C9_A0, 101 */
    { .dataOffset = 2072760, .properties = 5, .width = 55, .height = 21 },    /* text_alarm@C0_A1, 101 */
    { .dataOffset = 2075070, .properties = 5, .width = 55, .height = 21 },    /* text_alarm@C1_A1, 101 */
    { .dataOffset = 2077380, .properties = 5, .width = 55, .height = 21 },    /* text_alarm@C2_A1, 101 */
    { .dataOffset = 2079690, .properties = 5, .width = 64, .height = 21 },    /* text_alarm@C3_A1, 101 */
    { .dataOffset = 2082378, .properties = 5, .width = 64, .height = 21 },    /* text_alarm@C4_A1, 101 */
    { .dataOffset = 2085066, .properties = 5, .width = 68, .height = 21 },    /* text_alarm@C5_A1, 101 */
    { .dataOffset = 2087922, .properties = 5, .width = 74, .height = 21 },    /* text_alarm@C6_A1, 101 */
    { .dataOffset = 2091030, .properties = 5, .width = 48, .height = 21 },    /* text_alarm@C7_A1, 101 */
    { .dataOffset = 2093046, .properties = 5, .width = 47, .height = 21 },    /* text_alarm@C8_A1, 101 */
    { .dataOffset = 2095020, .properties = 5, .width = 60, .height = 21 },    /* text_alarm@C9_A1, 101 */
    { .dataOffset = 2097540, .properties = 5, .width = 76, .height = 21 },    /* text_brightness@C0_A0, 101 */
    { .dataOffset = 2100732, .properties = 5, .width = 77, .height = 21 },    /* text_brightness@C1_A0, 101 */
    { .dataOffset = 2103966, .properties = 5, .width = 67, .height = 21 },    /* text_brightness@C2_A0, 101 */
    { .dataOffset = 2106780, .properties = 5, .width = 80, .height = 21 },    /* text_brightness@C3_A0, 101 */
    { .dataOffset = 2110140, .properties = 5, .width = 35, .height = 21 },    /* text_brightness@C4_A0, 101 */
    { .dataOffset = 2111610, .properties = 5, .width = 80, .height = 21 },    /* text_brightness@C5_A0, 101 */
    { .dataOffset = 2114970, .properties = 5, .width = 63, .height = 21 },    /* text_brightness@C6_A0, 101 */
    { .dataOffset = 2117616, .properties = 5, .width = 34, .height = 21 },    /* text_brightness@C7_A0, 101 */
    { .dataOffset = 2119044, .properties = 5, .width = 41, .height = 21 },    /* text_brightness@C8_A0, 101 */
    { .dataOffset = 2120766, .properties = 5, .width = 29, .height = 21 },    /* text_brightness@C9_A0, 101 */
    { .dataOffset = 2121984, .properties = 5, .width = 76, .height = 21 },    /* text_brightness@C0_A1, 101 */
    { .dataOffset = 2125176, .properties = 5, .width = 77, .height = 21 },    /* text_brightness@C1_A1, 101 */
    { .dataOffset = 2128410, .properties = 5, .width = 67, .height = 21 },    /* text_brightness@C2_A1, 101 */
    { .dataOffset = 2131224, .properties = 5, .width = 80, .height = 21 },    /* text_brightness@C3_A1, 101 */
    { .dataOffset = 2134584, .properties = 5, .width = 35, .height = 21 },    /* text_brightness@C4_A1, 101 */
    { .dataOffset = 2136054, .properties = 5, .width = 80, .height = 21 },    /* text_brightness@C5_A1, 101 */
    { .dataOffset = 2139414, .properties = 5, .width = 63, .height = 21 },    /* text_brightness@C6_A1, 101 */
    { .dataOffset = 2142060, .properties = 5, .width = 34, .height = 21 },    /* text_brightness@C7_A1, 101 */
    { .dataOffset = 2143488, .properties = 5, .width = 41, .height = 21 },    /* text_brightness@C8_A1, 101 */
    { .dataOffset = 2145210, .properties = 5, .width = 29, .height = 21 },    /* text_brightness@C9_A1, 101 */
    { .dataOffset = 2146428, .properties = 5, .width = 47, .height = 21 },    /* text_colors@C0_A0, 101 */
    { .dataOffset = 2148402, .properties = 5, .width = 53, .height = 21 },    /* text_colors@C1_A0, 101 */
    { .dataOffset = 2150628, .properties = 5, .width = 48, .height = 21 },    /* text_colors@C2_A0, 101 */
    { .dataOffset = 2152644, .properties = 5, .width = 64, .height = 21 },    /* text_colors@C3_A0, 101 */
    { .dataOffset = 2155332, .properties = 5, .width = 55, .height = 21 },    /* text_colors@C4_A0, 101 */
    { .dataOffset = 2157642, .properties = 5, .width = 42, .height = 21 },    /* text_colors@C5_A0, 101 */
    { .dataOffset = 2159406, .properties = 5, .width = 48, .height = 21 },    /* text_colors@C6_A0, 101 */
    { .dataOffset = 2161422, .properties = 5, .width = 35, .height = 21 },    /* text_colors@C7_A0, 101 */
    { .dataOffset = 2162892, .properties = 5, .width = 17, .height = 21 },    /* text_colors@C8_A0, 101 */
    { .dataOffset = 2163606, .properties = 5, .width = 32, .height = 21 },    /* text_colors@C9_A0, 101 */
    { .dataOffset = 2164950, .properties = 5, .width = 47, .height = 21 },    /* text_colors@C0_A1, 101 */
    { .dataOffset = 2166924, .properties = 5, .width = 53, .height = 21 },    /* text_colors@C1_A1, 101 */
    { .dataOffset = 2169150, .properties = 5, .width = 48, .height = 21 },    /* text_colors@C2_A1, 101 */
    { .dataOffset = 2171166, .properties = 5, .width = 64, .height = 21 },    /* text_colors@C3_A1, 101 */
    { .dataOffset = 2173854, .properties = 5, .width = 55, .height = 21 },    /* text_colors@C4_A1, 101 */
    { .dataOffset = 2176164, .properties = 5, .width = 42, .height = 21 },    /* text_colors@C5_A1, 101 */
    { .dataOffset = 2177928, .properties = 5, .width = 48, .height = 21 },    /* text_colors@C6_A1, 101 */
    { .dataOffset = 2179944, .properties = 5, .width = 35, .height = 21 },    /* text_colors@C7_A1, 101 */
    { .dataOffset = 2181414, .properties = 5, .width = 17, .height = 21 },    /* text_colors@C8_A1, 101 */
    { .dataOffset = 2182128, .properties = 5, .width = 32, .height = 21 },    /* text_colors@C9_A1, 101 */
    { .dataOffset = 2183472, .properties = 5, .width = 32, .height = 21 },    /* text_date@C0_A0, 101 */
    { .dataOffset = 2184816, .properties = 5, .width = 46, .height = 21 },    /* text_date@C1_A0, 101 */
    { .dataOffset = 2186748, .properties = 5, .width = 46, .height = 21 },    /* text_date@C2_A0, 101 */
    { .dataOffset = 2188680, .properties = 5, .width = 32, .height = 21 },    /* text_date@C3_A0, 101 */
    { .dataOffset = 2190024, .properties = 5, .width = 42, .height = 21 },    /* text_date@C4_A0, 101 */
    { .dataOffset = 2191788, .properties = 5, .width = 52, .height = 21 },    /* text_date@C5_A0, 101 */
    { .dataOffset = 2193972, .properties = 5, .width = 37, .height = 21 },    /* text_date@C6_A0, 101 */
    { .dataOffset = 2195526, .properties = 5, .width = 31, .height = 21 },    /* text_date@C7_A0, 101 */
    { .dataOffset = 2196828, .properties = 5, .width = 32, .height = 21 },    /* text_date@C8_A0, 101 */
    { .dataOffset = 2198172, .properties = 5, .width = 30, .height = 21 },    /* text_date@C9_A0, 101 */
    { .dataOffset = 2199432, .properties = 5, .width = 32, .height = 21 },    /* text_date@C0_A1, 101 */
    { .dataOffset = 2200776, .properties = 5, .width = 46, .height = 21 },    /* text_date@C1_A1, 101 */
    { .dataOffset = 2202708, .properties = 5, .width = 46, .height = 21 },    /* text_date@C2_A1, 101 */
    { .dataOffset = 2204640, .properties = 5, .width = 32, .height = 21 },    /* text_date@C3_A1, 101 */
    { .dataOffset = 2205984, .properties = 5, .width = 42, .height = 21 },    /* text_date@C4_A1, 101 */
    { .dataOffset = 2207748, .properties = 5, .width = 52, .height = 21 },    /* text_date@C5_A1, 101 */
    { .dataOffset = 2209932, .properties = 5, .width = 37, .height = 21 },    /* text_date@C6_A1, 101 */
    { .dataOffset = 2211486, .properties = 5, .width = 31, .height = 21 },    /* text_date@C7_A1, 101 */
    { .dataOffset = 2212788, .properties = 5, .width = 32, .height = 21 },    /* text_date@C8_A1, 101 */
    { .dataOffset = 2214132, .properties = 5, .width = 30, .height = 21 },    /* text_date@C9_A1, 101 */
    { .dataOffset = 2215392, .properties = 1, .width = 74, .height = 29 },    /* text_footer_mcsgui@A0, 1 */
    { .dataOffset = 2219684, .properties = 1, .width = 74, .height = 29 },    /* text_footer_mcsgui@A1, 1 */
    { .dataOffset = 2223976, .properties = 5, .width = 27, .height = 21 },    /* text_info@C0_A0, 101 */
    { .dataOffset = 2225110, .properties = 5, .width = 27, .height = 21 },    /* text_info@C1_A0, 101 */
    { .dataOffset = 2226244, .properties = 5, .width = 27, .height = 21 },    /* text_info@C2_A0, 101 */
    { .dataOffset = 2227378, .properties = 5, .width = 27, .height = 21 },    /* text_info@C3_A0, 101 */
    { .dataOffset = 2228512, .properties = 5, .width = 86, .height = 21 },    /* text_info@C4_A0, 101 */
    { .dataOffset = 2232124, .properties = 5, .width = 90, .height = 21 },    /* text_info@C5_A0, 101 */
    { .dataOffset = 2235904, .properties = 5, .width = 99, .height = 21 },    /* text_info@C6_A0, 101 */
    { .dataOffset = 2240062, .properties = 5, .width = 35, .height = 21 },    /* text_info@C7_A0, 101 */
    { .dataOffset = 2241532, .properties = 5, .width = 35, .height = 21 },    /* text_info@C8_A0, 101 */
    { .dataOffset = 2243002, .properties = 5, .width = 31, .height = 21 },    /* text_info@C9_A0, 101 */
    { .dataOffset = 2244304, .properties = 5, .width = 27, .height = 21 },    /* text_info@C0_A1, 101 */
    { .dataOffset = 2245438, .properties = 5, .width = 27, .height = 21 },    /* text_info@C1_A1, 101 */
    { .dataOffset = 2246572, .properties = 5, .width = 27, .height = 21 },    /* text_info@C2_A1, 101 */
    { .dataOffset = 2247706, .properties = 5, .width = 27, .height = 21 },    /* text_info@C3_A1, 101 */
    { .dataOffset = 2248840, .properties = 5, .width = 86, .height = 21 },    /* text_info@C4_A1, 101 */
    { .dataOffset = 2252452, .properties = 5, .width = 90, .height = 21 },    /* text_info@C5_A1, 101 */
    { .dataOffset = 2256232, .properties = 5, .width = 99, .height = 21 },    /* text_info@C6_A1, 101 */
    { .dataOffset = 2260390, .properties = 5, .width = 35, .height = 21 },    /* text_info@C7_A1, 101 */
    { .dataOffset = 2261860, .properties = 5, .width = 35, .height = 21 },    /* text_info@C8_A1, 101 */
    { .dataOffset = 2263330, .properties = 5, .width = 31, .height = 21 },    /* text_info@C9_A1, 101 */
    { .dataOffset = 2264632, .properties = 5, .width = 67, .height = 21 },    /* text_keyboard@C0_A0, 101 */
    { .dataOffset = 2267446, .properties = 5, .width = 92, .height = 21 },    /* text_keyboard@C1_A0, 101 */
    { .dataOffset = 2271310, .properties = 5, .width = 61, .height = 21 },    /* text_keyboard@C2_A0, 101 */
    { .dataOffset = 2273872, .properties = 5, .width = 50, .height = 21 },    /* text_keyboard@C3_A0, 101 */
    { .dataOffset = 2275972, .properties = 5, .width = 58, .height = 21 },    /* text_keyboard@C4_A0, 101 */
    { .dataOffset = 2278408, .properties = 5, .width = 59, .height = 21 },    /* text_keyboard@C5_A0, 101 */
    { .dataOffset = 2280886, .properties = 5, .width = 89, .height = 21 },    /* text_keyboard@C6_A0, 101 */
    { .dataOffset = 2284624, .properties = 5, .width = 35, .height = 21 },    /* text_keyboard@C7_A0, 101 */
    { .dataOffset = 2286094, .properties = 5, .width = 71, .height = 21 },    /* text_keyboard@C8_A0, 101 */
    { .dataOffset = 2289076, .properties = 5, .width = 47, .height = 21 },    /* text_keyboard@C9_A0, 101 */
    { .dataOffset = 2291050, .properties = 5, .width = 67, .height = 21 },    /* text_keyboard@C0_A1, 101 */
    { .dataOffset = 2293864, .properties = 5, .width = 92, .height = 21 },    /* text_keyboard@C1_A1, 101 */
    { .dataOffset = 2297728, .properties = 5, .width = 61, .height = 21 },    /* text_keyboard@C2_A1, 101 */
    { .dataOffset = 2300290, .properties = 5, .width = 50, .height = 21 },    /* text_keyboard@C3_A1, 101 */
    { .dataOffset = 2302390, .properties = 5, .width = 58, .height = 21 },    /* text_keyboard@C4_A1, 101 */
    { .dataOffset = 2304826, .properties = 5, .width = 59, .height = 21 },    /* text_keyboard@C5_A1, 101 */
    { .dataOffset = 2307304, .properties = 5, .width = 89, .height = 21 },    /* text_keyboard@C6_A1, 101 */
    { .dataOffset = 2311042, .properties = 5, .width = 35, .height = 21 },    /* text_keyboard@C7_A1, 101 */
    { .dataOffset = 2312512, .properties = 5, .width = 71, .height = 21 },    /* text_keyboard@C8_A1, 101 */
    { .dataOffset = 2315494, .properties = 5, .width = 47, .height = 21 },    /* text_keyboard@C9_A1, 101 */
    { .dataOffset = 2317468, .properties = 5, .width = 70, .height = 21 },    /* text_language@C0_A0, 101 */
    { .dataOffset = 2320408, .properties = 5, .width = 31, .height = 21 },    /* text_language@C1_A0, 101 */
    { .dataOffset = 2321710, .properties = 5, .width = 59, .height = 21 },    /* text_language@C2_A0, 101 */
    { .dataOffset = 2324188, .properties = 5, .width = 52, .height = 21 },    /* text_language@C3_A0, 101 */
    { .dataOffset = 2326372, .properties = 5, .width = 48, .height = 21 },    /* text_language@C4_A0, 101 */
    { .dataOffset = 2328388, .properties = 5, .width = 47, .height = 21 },    /* text_language@C5_A0, 101 */
    { .dataOffset = 2330362, .properties = 5, .width = 40, .height = 21 },    /* text_language@C6_A0, 101 */
    { .dataOffset = 2332042, .properties = 5, .width = 35, .height = 21 },    /* text_language@C7_A0, 101 */
    { .dataOffset = 2333512, .properties = 5, .width = 35, .height = 21 },    /* text_language@C8_A0, 101 */
    { .dataOffset = 2334982, .properties = 5, .width = 29, .height = 21 },    /* text_language@C9_A0, 101 */
    { .dataOffset = 2336200, .properties = 5, .width = 70, .height = 21 },    /* text_language@C0_A1, 101 */
    { .dataOffset = 2339140, .properties = 5, .width = 31, .height = 21 },    /* text_language@C1_A1, 101 */
    { .dataOffset = 2340442, .properties = 5, .width = 59, .height = 21 },    /* text_language@C2_A1, 101 */
    { .dataOffset = 2342920, .properties = 5, .width = 52, .height = 21 },    /* text_language@C3_A1, 101 */
    { .dataOffset = 2345104, .properties = 5, .width = 48, .height = 21 },    /* text_language@C4_A1, 101 */
    { .dataOffset = 2347120, .properties = 5, .width = 47, .height = 21 },    /* text_language@C5_A1, 101 */
    { .dataOffset = 2349094, .properties = 5, .width = 40, .height = 21 },    /* text_language@C6_A1, 101 */
    { .dataOffset = 2350774, .properties = 5, .width = 35, .height = 21 },    /* text_language@C7_A1, 101 */
    { .dataOffset = 2352244, .properties = 5, .width = 35, .height = 21 },    /* text_language@C8_A1, 101 */
    { .dataOffset = 2353714, .properties = 5, .width = 29, .height = 21 },    /* text_language@C9_A1, 101 */
    { .dataOffset = 2354932, .properties = 5, .width = 100, .height = 21 },    /* text_measurement@C0_A0, 101 */
    { .dataOffset = 2359132, .properties = 5, .width = 57, .height = 21 },    /* text_measurement@C1_A0, 101 */
    { .dataOffset = 2361526, .properties = 5, .width = 65, .height = 21 },    /* text_measurement@C2_A0, 101 */
    { .dataOffset = 2364256, .properties = 5, .width = 53, .height = 21 },    /* text_measurement@C3_A0, 101 */
    { .dataOffset = 2366482, .properties = 5, .width = 65, .height = 21 },    /* text_measurement@C4_A0, 101 */
    { .dataOffset = 2369212, .properties = 5, .width = 88, .height = 21 },    /* text_measurement@C5_A0, 101 */
    { .dataOffset = 2372908, .properties = 5, .width = 85, .height = 21 },    /* text_measurement@C6_A0, 101 */
    { .dataOffset = 2376478, .properties = 5, .width = 35, .height = 21 },    /* text_measurement@C7_A0, 101 */
    { .dataOffset = 2377948, .properties = 5, .width = 35, .height = 21 },    /* text_measurement@C8_A0, 101 */
    { .dataOffset = 2379418, .properties = 5, .width = 32, .height = 21 },    /* text_measurement@C9_A0, 101 */
    { .dataOffset = 2380762, .properties = 5, .width = 100, .height = 21 },    /* text_measurement@C0_A1, 101 */
    { .dataOffset = 2384962, .properties = 5, .width = 57, .height = 21 },    /* text_measurement@C1_A1, 101 */
    { .dataOffset = 2387356, .properties = 5, .width = 65, .height = 21 },    /* text_measurement@C2_A1, 101 */
    { .dataOffset = 2390086, .properties = 5, .width = 53, .height = 21 },    /* text_measurement@C3_A1, 101 */
    { .dataOffset = 2392312, .properties = 5, .width = 65, .height = 21 },    /* text_measurement@C4_A1, 101 */
    { .dataOffset = 2395042, .properties = 5, .width = 88, .height = 21 },    /* text_measurement@C5_A1, 101 */
    { .dataOffset = 2398738, .properties = 5, .width = 85, .height = 21 },    /* text_measurement@C6_A1, 101 */
    { .dataOffset = 2402308, .properties = 5, .width = 35, .height = 21 },    /* text_measurement@C7_A1, 101 */
    { .dataOffset = 2403778, .properties = 5, .width = 35, .height = 21 },    /* text_measurement@C8_A1, 101 */
    { .dataOffset = 2405248, .properties = 5, .width = 32, .height = 21 },    /* text_measurement@C9_A1, 101 */
    { .dataOffset = 2406592, .properties = 5, .width = 104, .height = 23 },    /* text_pane_accent_color@C0_A0, 101 */
    { .dataOffset = 2411376, .properties = 5, .width = 102, .height = 23 },    /* text_pane_accent_color@C1_A0, 101 */
    { .dataOffset = 2416068, .properties = 5, .width = 148, .height = 23 },    /* text_pane_accent_color@C2_A0, 101 */
    { .dataOffset = 2422876, .properties = 5, .width = 187, .height = 23 },    /* text_pane_accent_color@C3_A0, 101 */
    { .dataOffset = 2431478, .properties = 5, .width = 128, .height = 23 },    /* text_pane_accent_color@C4_A0, 101 */
    { .dataOffset = 2437366, .properties = 5, .width = 137, .height = 23 },    /* text_pane_accent_color@C5_A0, 101 */
    { .dataOffset = 2443668, .properties = 5, .width = 143, .height = 23 },    /* text_pane_accent_color@C6_A0, 101 */
    { .dataOffset = 2450246, .properties = 5, .width = 57, .height = 23 },    /* text_pane_accent_color@C7_A0, 101 */
    { .dataOffset = 2452868, .properties = 5, .width = 119, .height = 23 },    /* text_pane_accent_color@C8_A0, 101 */
    { .dataOffset = 2458342, .properties = 5, .width = 77, .height = 23 },    /* text_pane_accent_color@C9_A0, 101 */
    { .dataOffset = 2461884, .properties = 5, .width = 104, .height = 23 },    /* text_pane_accent_color@C0_A1, 101 */
    { .dataOffset = 2466668, .properties = 5, .width = 102, .height = 23 },    /* text_pane_accent_color@C1_A1, 101 */
    { .dataOffset = 2471360, .properties = 5, .width = 148, .height = 23 },    /* text_pane_accent_color@C2_A1, 101 */
    { .dataOffset = 2478168, .properties = 5, .width = 187, .height = 23 },    /* text_pane_accent_color@C3_A1, 101 */
    { .dataOffset = 2486770, .properties = 5, .width = 128, .height = 23 },    /* text_pane_accent_color@C4_A1, 101 */
    { .dataOffset = 2492658, .properties = 5, .width = 137, .height = 23 },    /* text_pane_accent_color@C5_A1, 101 */
    { .dataOffset = 2498960, .properties = 5, .width = 143, .height = 23 },    /* text_pane_accent_color@C6_A1, 101 */
    { .dataOffset = 2505538, .properties = 5, .width = 57, .height = 23 },    /* text_pane_accent_color@C7_A1, 101 */
    { .dataOffset = 2508160, .properties = 5, .width = 119, .height = 23 },    /* text_pane_accent_color@C8_A1, 101 */
    { .dataOffset = 2513634, .properties = 5, .width = 77, .height = 23 },    /* text_pane_accent_color@C9_A1, 101 */
    { .dataOffset = 2517176, .properties = 5, .width = 127, .height = 23 },    /* text_pane_activate_alarm@C0_A0, 101 */
    { .dataOffset = 2523018, .properties = 5, .width = 137, .height = 23 },    /* text_pane_activate_alarm@C1_A0, 101 */
    { .dataOffset = 2529320, .properties = 5, .width = 142, .height = 23 },    /* text_pane_activate_alarm@C2_A0, 101 */
    { .dataOffset = 2535852, .properties = 5, .width = 135, .height = 23 },    /* text_pane_activate_alarm@C3_A0, 101 */
    { .dataOffset = 2542062, .properties = 5, .width = 156, .height = 23 },    /* text_pane_activate_alarm@C4_A0, 101 */
    { .dataOffset = 2549238, .properties = 5, .width = 146, .height = 23 },    /* text_pane_activate_alarm@C5_A0, 101 */
    { .dataOffset = 2555954, .properties = 5, .width = 263, .height = 23 },    /* text_pane_activate_alarm@C6_A0, 101 */
    { .dataOffset = 2568052, .properties = 5, .width = 96, .height = 23 },    /* text_pane_activate_alarm@C7_A0, 101 */
    { .dataOffset = 2572468, .properties = 5, .width = 207, .height = 23 },    /* text_pane_activate_alarm@C8_A0, 101 */
    { .dataOffset = 2581990, .properties = 5, .width = 234, .height = 23 },    /* text_pane_activate_alarm@C9_A0, 101 */
    { .dataOffset = 2592754, .properties = 5, .width = 127, .height = 23 },    /* text_pane_activate_alarm@C0_A1, 101 */
    { .dataOffset = 2598596, .properties = 5, .width = 137, .height = 23 },    /* text_pane_activate_alarm@C1_A1, 101 */
    { .dataOffset = 2604898, .properties = 5, .width = 142, .height = 23 },    /* text_pane_activate_alarm@C2_A1, 101 */
    { .dataOffset = 2611430, .properties = 5, .width = 135, .height = 23 },    /* text_pane_activate_alarm@C3_A1, 101 */
    { .dataOffset = 2617640, .properties = 5, .width = 156, .height = 23 },    /* text_pane_activate_alarm@C4_A1, 101 */
    { .dataOffset = 2624816, .properties = 5, .width = 146, .height = 23 },    /* text_pane_activate_alarm@C5_A1, 101 */
    { .dataOffset = 2631532, .properties = 5, .width = 263, .height = 23 },    /* text_pane_activate_alarm@C6_A1, 101 */
    { .dataOffset = 2643630, .properties = 5, .width = 96, .height = 23 },    /* text_pane_activate_alarm@C7_A1, 101 */
    { .dataOffset = 2648046, .properties = 5, .width = 207, .height = 23 },    /* text_pane_activate_alarm@C8_A1, 101 */
    { .dataOffset = 2657568, .properties = 5, .width = 234, .height = 23 },    /* text_pane_activate_alarm@C9_A1, 101 */
    { .dataOffset = 2668332, .properties = 1, .width = 37, .height = 23 },    /* text_pane_chinese_sim@A0, 1 */
    { .dataOffset = 2670034, .properties = 1, .width = 37, .height = 23 },    /* text_pane_chinese_sim@A1, 1 */
    { .dataOffset = 2671736, .properties = 5, .width = 100, .height = 23 },    /* text_pane_cursor_color@C0_A0, 101 */
    { .dataOffset = 2676336, .properties = 5, .width = 99, .height = 23 },    /* text_pane_cursor_color@C1_A0, 101 */
    { .dataOffset = 2680890, .properties = 5, .width = 149, .height = 23 },    /* text_pane_cursor_color@C2_A0, 101 */
    { .dataOffset = 2687744, .properties = 5, .width = 154, .height = 23 },    /* text_pane_cursor_color@C3_A0, 101 */
    { .dataOffset = 2694828, .properties = 5, .width = 129, .height = 23 },    /* text_pane_cursor_color@C4_A0, 101 */
    { .dataOffset = 2700762, .properties = 5, .width = 149, .height = 23 },    /* text_pane_cursor_color@C5_A0, 101 */
    { .dataOffset = 2707616, .properties = 5, .width = 115, .height = 23 },    /* text_pane_cursor_color@C6_A0, 101 */
    { .dataOffset = 2712906, .properties = 5, .width = 79, .height = 23 },    /* text_pane_cursor_color@C7_A0, 101 */
    { .dataOffset = 2716540, .properties = 5, .width = 98, .height = 23 },    /* text_pane_cursor_color@C8_A0, 101 */
    { .dataOffset = 2721048, .properties = 5, .width = 77, .height = 23 },    /* text_pane_cursor_color@C9_A0, 101 */
    { .dataOffset = 2724590, .properties = 5, .width = 100, .height = 23 },    /* text_pane_cursor_color@C0_A1, 101 */
    { .dataOffset = 2729190, .properties = 5, .width = 99, .height = 23 },    /* text_pane_cursor_color@C1_A1, 101 */
    { .dataOffset = 2733744, .properties = 5, .width = 149, .height = 23 },    /* text_pane_cursor_color@C2_A1, 101 */
    { .dataOffset = 2740598, .properties = 5, .width = 154, .height = 23 },    /* text_pane_cursor_color@C3_A1, 101 */
    { .dataOffset = 2747682, .properties = 5, .width = 129, .height = 23 },    /* text_pane_cursor_color@C4_A1, 101 */
    { .dataOffset = 2753616, .properties = 5, .width = 149, .height = 23 },    /* text_pane_cursor_color@C5_A1, 101 */
    { .dataOffset = 2760470, .properties = 5, .width = 115, .height = 23 },    /* text_pane_cursor_color@C6_A1, 101 */
    { .dataOffset = 2765760, .properties = 5, .width = 79, .height = 23 },    /* text_pane_cursor_color@C7_A1, 101 */
    { .dataOffset = 2769394, .properties = 5, .width = 98, .height = 23 },    /* text_pane_cursor_color@C8_A1, 101 */
    { .dataOffset = 2773902, .properties = 5, .width = 77, .height = 23 },    /* text_pane_cursor_color@C9_A1, 101 */
    { .dataOffset = 2777444, .properties = 1, .width = 17, .height = 23 },    /* text_pane_deg_cel@A0, 1 */
    { .dataOffset = 2778226, .properties = 1, .width = 17, .height = 23 },    /* text_pane_deg_cel@A1, 1 */
    { .dataOffset = 2779008, .properties = 1, .width = 16, .height = 23 },    /* text_pane_deg_far@A0, 1 */
    { .dataOffset = 2779744, .properties = 1, .width = 16, .height = 23 },    /* text_pane_deg_far@A1, 1 */
    { .dataOffset = 2780480, .properties = 1, .width = 93, .height = 23 },    /* text_pane_dutch@A0, 1 */
    { .dataOffset = 2784758, .properties = 1, .width = 93, .height = 23 },    /* text_pane_dutch@A1, 1 */
    { .dataOffset = 2789036, .properties = 1, .width = 58, .height = 23 },    /* text_pane_english@A0, 1 */
    { .dataOffset = 2791704, .properties = 1, .width = 58, .height = 23 },    /* text_pane_english@A1, 1 */
    { .dataOffset = 2794372, .properties = 1, .width = 69, .height = 23 },    /* text_pane_french@A0, 1 */
    { .dataOffset = 2797546, .properties = 1, .width = 69, .height = 23 },    /* text_pane_french@A1, 1 */
    { .dataOffset = 2800720, .properties = 1, .width = 66, .height = 23 },    /* text_pane_german@A0, 1 */
    { .dataOffset = 2803756, .properties = 1, .width = 66, .height = 23 },    /* text_pane_german@A1, 1 */
    { .dataOffset = 2806792, .properties = 5, .width = 112, .height = 23 },    /* text_pane_intern_temp@C0_A0, 101 */
    { .dataOffset = 2811944, .properties = 5, .width = 112, .height = 23 },    /* text_pane_intern_temp@C1_A0, 101 */
    { .dataOffset = 2817096, .properties = 5, .width = 161, .height = 23 },    /* text_pane_intern_temp@C2_A0, 101 */
    { .dataOffset = 2824502, .properties = 5, .width = 171, .height = 23 },    /* text_pane_intern_temp@C3_A0, 101 */
    { .dataOffset = 2832368, .properties = 5, .width = 172, .height = 23 },    /* text_pane_intern_temp@C4_A0, 101 */
    { .dataOffset = 2840280, .properties = 5, .width = 172, .height = 23 },    /* text_pane_intern_temp@C5_A0, 101 */
    { .dataOffset = 2848192, .properties = 5, .width = 221, .height = 23 },    /* text_pane_intern_temp@C6_A0, 101 */
    { .dataOffset = 2858358, .properties = 5, .width = 86, .height = 23 },    /* text_pane_intern_temp@C7_A0, 101 */
    { .dataOffset = 2862314, .properties = 5, .width = 83, .height = 23 },    /* text_pane_intern_temp@C8_A0, 101 */
    { .dataOffset = 2866132, .properties = 5, .width = 80, .height = 23 },    /* text_pane_intern_temp@C9_A0, 101 */
    { .dataOffset = 2869812, .properties = 5, .width = 112, .height = 23 },    /* text_pane_intern_temp@C0_A1, 101 */
    { .dataOffset = 2874964, .properties = 5, .width = 112, .height = 23 },    /* text_pane_intern_temp@C1_A1, 101 */
    { .dataOffset = 2880116, .properties = 5, .width = 161, .height = 23 },    /* text_pane_intern_temp@C2_A1, 101 */
    { .dataOffset = 2887522, .properties = 5, .width = 171, .height = 23 },    /* text_pane_intern_temp@C3_A1, 101 */
    { .dataOffset = 2895388, .properties = 5, .width = 172, .height = 23 },    /* text_pane_intern_temp@C4_A1, 101 */
    { .dataOffset = 2903300, .properties = 5, .width = 172, .height = 23 },    /* text_pane_intern_temp@C5_A1, 101 */
    { .dataOffset = 2911212, .properties = 5, .width = 221, .height = 23 },    /* text_pane_intern_temp@C6_A1, 101 */
    { .dataOffset = 2921378, .properties = 5, .width = 86, .height = 23 },    /* text_pane_intern_temp@C7_A1, 101 */
    { .dataOffset = 2925334, .properties = 5, .width = 83, .height = 23 },    /* text_pane_intern_temp@C8_A1, 101 */
    { .dataOffset = 2929152, .properties = 5, .width = 80, .height = 23 },    /* text_pane_intern_temp@C9_A1, 101 */
    { .dataOffset = 2932832, .properties = 1, .width = 59, .height = 23 },    /* text_pane_italian@A0, 1 */
    { .dataOffset = 2935546, .properties = 1, .width = 59, .height = 23 },    /* text_pane_italian@A1, 1 */
    { .dataOffset = 2938260, .properties = 1, .width = 57, .height = 23 },    /* text_pane_japanese@A0, 1 */
    { .dataOffset = 2940882, .properties = 1, .width = 57, .height = 23 },    /* text_pane_japanese@A1, 1 */
    { .dataOffset = 2943504, .properties = 1, .width = 51, .height = 23 },    /* text_pane_korean@A0, 1 */
    { .dataOffset = 2945850, .properties = 1, .width = 51, .height = 23 },    /* text_pane_korean@A1, 1 */
    { .dataOffset = 2948196, .properties = 1, .width = 69, .height = 23 },    /* text_pane_russian@A0, 1 */
    { .dataOffset = 2951370, .properties = 1, .width = 69, .height = 23 },    /* text_pane_russian@A1, 1 */
    { .dataOffset = 2954544, .properties = 5, .width = 102, .height = 23 },    /* text_pane_set_alarm_in@C0_A0, 101 */
    { .dataOffset = 2959236, .properties = 5, .width = 72, .height = 23 },    /* text_pane_set_alarm_in@C1_A0, 101 */
    { .dataOffset = 2962548, .properties = 5, .width = 112, .height = 23 },    /* text_pane_set_alarm_in@C2_A0, 101 */
    { .dataOffset = 2967700, .properties = 5, .width = 156, .height = 23 },    /* text_pane_set_alarm_in@C3_A0, 101 */
    { .dataOffset = 2974876, .properties = 5, .width = 176, .height = 23 },    /* text_pane_set_alarm_in@C4_A0, 101 */
    { .dataOffset = 2982972, .properties = 5, .width = 172, .height = 23 },    /* text_pane_set_alarm_in@C5_A0, 101 */
    { .dataOffset = 2990884, .properties = 5, .width = 218, .height = 23 },    /* text_pane_set_alarm_in@C6_A0, 101 */
    { .dataOffset = 3000912, .properties = 5, .width = 190, .height = 23 },    /* text_pane_set_alarm_in@C7_A0, 101 */
    { .dataOffset = 3009652, .properties = 5, .width = 123, .height = 23 },    /* text_pane_set_alarm_in@C8_A0, 101 */
    { .dataOffset = 3015310, .properties = 5, .width = 81, .height = 23 },    /* text_pane_set_alarm_in@C9_A0, 101 */
    { .dataOffset = 3019036, .properties = 5, .width = 102, .height = 23 },    /* text_pane_set_alarm_in@C0_A1, 101 */
    { .dataOffset = 3023728, .properties = 5, .width = 72, .height = 23 },    /* text_pane_set_alarm_in@C1_A1, 101 */
    { .dataOffset = 3027040, .properties = 5, .width = 112, .height = 23 },    /* text_pane_set_alarm_in@C2_A1, 101 */
    { .dataOffset = 3032192, .properties = 5, .width = 156, .height = 23 },    /* text_pane_set_alarm_in@C3_A1, 101 */
    { .dataOffset = 3039368, .properties = 5, .width = 176, .height = 23 },    /* text_pane_set_alarm_in@C4_A1, 101 */
    { .dataOffset = 3047464, .properties = 5, .width = 172, .height = 23 },    /* text_pane_set_alarm_in@C5_A1, 101 */
    { .dataOffset = 3055376, .properties = 5, .width = 218, .height = 23 },    /* text_pane_set_alarm_in@C6_A1, 101 */
    { .dataOffset = 3065404, .properties = 5, .width = 190, .height = 23 },    /* text_pane_set_alarm_in@C7_A1, 101 */
    { .dataOffset = 3074144, .properties = 5, .width = 123, .height = 23 },    /* text_pane_set_alarm_in@C8_A1, 101 */
    { .dataOffset = 3079802, .properties = 5, .width = 81, .height = 23 },    /* text_pane_set_alarm_in@C9_A1, 101 */
    { .dataOffset = 3083528, .properties = 1, .width = 64, .height = 23 },    /* text_pane_spanish@A0, 1 */
    { .dataOffset = 3086472, .properties = 1, .width = 64, .height = 23 },    /* text_pane_spanish@A1, 1 */
    { .dataOffset = 3089416, .properties = 5, .width = 37, .height = 23 },    /* text_pane_theme_dark@C0_A0, 101 */
    { .dataOffset = 3091118, .properties = 5, .width = 57, .height = 23 },    /* text_pane_theme_dark@C1_A0, 101 */
    { .dataOffset = 3093740, .properties = 5, .width = 54, .height = 23 },    /* text_pane_theme_dark@C2_A0, 101 */
    { .dataOffset = 3096224, .properties = 5, .width = 64, .height = 23 },    /* text_pane_theme_dark@C3_A0, 101 */
    { .dataOffset = 3099168, .properties = 5, .width = 57, .height = 23 },    /* text_pane_theme_dark@C4_A0, 101 */
    { .dataOffset = 3101790, .properties = 5, .width = 57, .height = 23 },    /* text_pane_theme_dark@C5_A0, 101 */
    { .dataOffset = 3104412, .properties = 5, .width = 69, .height = 23 },    /* text_pane_theme_dark@C6_A0, 101 */
    { .dataOffset = 3107586, .properties = 5, .width = 39, .height = 23 },    /* text_pane_theme_dark@C7_A0, 101 */
    { .dataOffset = 3109380, .properties = 5, .width = 36, .height = 23 },    /* text_pane_theme_dark@C8_A0, 101 */
    { .dataOffset = 3111036, .properties = 5, .width = 34, .height = 23 },    /* text_pane_theme_dark@C9_A0, 101 */
    { .dataOffset = 3112600, .properties = 5, .width = 37, .height = 23 },    /* text_pane_theme_dark@C0_A1, 101 */
    { .dataOffset = 3114302, .properties = 5, .width = 57, .height = 23 },    /* text_pane_theme_dark@C1_A1, 101 */
    { .dataOffset = 3116924, .properties = 5, .width = 54, .height = 23 },    /* text_pane_theme_dark@C2_A1, 101 */
    { .dataOffset = 3119408, .properties = 5, .width = 64, .height = 23 },    /* text_pane_theme_dark@C3_A1, 101 */
    { .dataOffset = 3122352, .properties = 5, .width = 57, .height = 23 },    /* text_pane_theme_dark@C4_A1, 101 */
    { .dataOffset = 3124974, .properties = 5, .width = 57, .height = 23 },    /* text_pane_theme_dark@C5_A1, 101 */
    { .dataOffset = 3127596, .properties = 5, .width = 69, .height = 23 },    /* text_pane_theme_dark@C6_A1, 101 */
    { .dataOffset = 3130770, .properties = 5, .width = 39, .height = 23 },    /* text_pane_theme_dark@C7_A1, 101 */
    { .dataOffset = 3132564, .properties = 5, .width = 36, .height = 23 },    /* text_pane_theme_dark@C8_A1, 101 */
    { .dataOffset = 3134220, .properties = 5, .width = 34, .height = 23 },    /* text_pane_theme_dark@C9_A1, 101 */
    { .dataOffset = 3135784, .properties = 5, .width = 40, .height = 23 },    /* text_pane_theme_light@C0_A0, 101 */
    { .dataOffset = 3137624, .properties = 5, .width = 39, .height = 23 },    /* text_pane_theme_light@C1_A0, 101 */
    { .dataOffset = 3139418, .properties = 5, .width = 39, .height = 23 },    /* text_pane_theme_light@C2_A0, 101 */
    { .dataOffset = 3141212, .properties = 5, .width = 65, .height = 23 },    /* text_pane_theme_light@C3_A0, 101 */
    { .dataOffset = 3144202, .properties = 5, .width = 28, .height = 23 },    /* text_pane_theme_light@C4_A0, 101 */
    { .dataOffset = 3145490, .properties = 5, .width = 66, .height = 23 },    /* text_pane_theme_light@C5_A0, 101 */
    { .dataOffset = 3148526, .properties = 5, .width = 40, .height = 23 },    /* text_pane_theme_light@C6_A0, 101 */
    { .dataOffset = 3150366, .properties = 5, .width = 18, .height = 23 },    /* text_pane_theme_light@C7_A0, 101 */
    { .dataOffset = 3151194, .properties = 5, .width = 18, .height = 23 },    /* text_pane_theme_light@C8_A0, 101 */
    { .dataOffset = 3152022, .properties = 5, .width = 17, .height = 23 },    /* text_pane_theme_light@C9_A0, 101 */
    { .dataOffset = 3152804, .properties = 5, .width = 40, .height = 23 },    /* text_pane_theme_light@C0_A1, 101 */
    { .dataOffset = 3154644, .properties = 5, .width = 39, .height = 23 },    /* text_pane_theme_light@C1_A1, 101 */
    { .dataOffset = 3156438, .properties = 5, .width = 39, .height = 23 },    /* text_pane_theme_light@C2_A1, 101 */
    { .dataOffset = 3158232, .properties = 5, .width = 65, .height = 23 },    /* text_pane_theme_light@C3_A1, 101 */
    { .dataOffset = 3161222, .properties = 5, .width = 28, .height = 23 },    /* text_pane_theme_light@C4_A1, 101 */
    { .dataOffset = 3162510, .properties = 5, .width = 66, .height = 23 },    /* text_pane_theme_light@C5_A1, 101 */
    { .dataOffset = 3165546, .properties = 5, .width = 40, .height = 23 },    /* text_pane_theme_light@C6_A1, 101 */
    { .dataOffset = 3167386, .properties = 5, .width = 18, .height = 23 },    /* text_pane_theme_light@C7_A1, 101 */
    { .dataOffset = 3168214, .properties = 5, .width = 18, .height = 23 },    /* text_pane_theme_light@C8_A1, 101 */
    { .dataOffset = 3169042, .properties = 5, .width = 17, .height = 23 },    /* text_pane_theme_light@C9_A1, 101 */
    { .dataOffset = 3169824, .properties = 1, .width = 43, .height = 23 },    /* text_pane_time_mm@A0, 1 */
    { .dataOffset = 3171802, .properties = 1, .width = 43, .height = 23 },    /* text_pane_time_mm@A1, 1 */
    { .dataOffset = 3173780, .properties = 5, .width = 59, .height = 21 },    /* text_settings@C0_A0, 101 */
    { .dataOffset = 3176258, .properties = 5, .width = 82, .height = 21 },    /* text_settings@C1_A0, 101 */
    { .dataOffset = 3179702, .properties = 5, .width = 96, .height = 21 },    /* text_settings@C2_A0, 101 */
    { .dataOffset = 3183734, .properties = 5, .width = 83, .height = 21 },    /* text_settings@C3_A0, 101 */
    { .dataOffset = 3187220, .properties = 5, .width = 102, .height = 21 },    /* text_settings@C4_A0, 101 */
    { .dataOffset = 3191504, .properties = 5, .width = 93, .height = 21 },    /* text_settings@C5_A0, 101 */
    { .dataOffset = 3195410, .properties = 5, .width = 87, .height = 21 },    /* text_settings@C6_A0, 101 */
    { .dataOffset = 3199064, .properties = 5, .width = 35, .height = 21 },    /* text_settings@C7_A0, 101 */
    { .dataOffset = 3200534, .properties = 5, .width = 35, .height = 21 },    /* text_settings@C8_A0, 101 */
    { .dataOffset = 3202004, .properties = 5, .width = 29, .height = 21 },    /* text_settings@C9_A0, 101 */
    { .dataOffset = 3203222, .properties = 5, .width = 59, .height = 21 },    /* text_settings@C0_A1, 101 */
    { .dataOffset = 3205700, .properties = 5, .width = 82, .height = 21 },    /* text_settings@C1_A1, 101 */
    { .dataOffset = 3209144, .properties = 5, .width = 96, .height = 21 },    /* text_settings@C2_A1, 101 */
    { .dataOffset = 3213176, .properties = 5, .width = 83, .height = 21 },    /* text_settings@C3_A1, 101 */
    { .dataOffset = 3216662, .properties = 5, .width = 102, .height = 21 },    /* text_settings@C4_A1, 101 */
    { .dataOffset = 3220946, .properties = 5, .width = 93, .height = 21 },    /* text_settings@C5_A1, 101 */
    { .dataOffset = 3224852, .properties = 5, .width = 87, .height = 21 },    /* text_settings@C6_A1, 101 */
    { .dataOffset = 3228506, .properties = 5, .width = 35, .height = 21 },    /* text_settings@C7_A1, 101 */
    { .dataOffset = 3229976, .properties = 5, .width = 35, .height = 21 },    /* text_settings@C8_A1, 101 */
    { .dataOffset = 3231446, .properties = 5, .width = 29, .height = 21 },    /* text_settings@C9_A1, 101 */
    { .dataOffset = 3232664, .properties = 5, .width = 41, .height = 21 },    /* text_setup@C0_A0, 101 */
    { .dataOffset = 3234386, .properties = 5, .width = 46, .height = 21 },    /* text_setup@C1_A0, 101 */
    { .dataOffset = 3236318, .properties = 5, .width = 80, .height = 21 },    /* text_setup@C2_A0, 101 */
    { .dataOffset = 3239678, .properties = 5, .width = 89, .height = 21 },    /* text_setup@C3_A0, 101 */
    { .dataOffset = 3243416, .properties = 5, .width = 52, .height = 21 },    /* text_setup@C4_A0, 101 */
    { .dataOffset = 3245600, .properties = 5, .width = 91, .height = 21 },    /* text_setup@C5_A0, 101 */
    { .dataOffset = 3249422, .properties = 5, .width = 81, .height = 21 },    /* text_setup@C6_A0, 101 */
    { .dataOffset = 3252824, .properties = 5, .width = 35, .height = 21 },    /* text_setup@C7_A0, 101 */
    { .dataOffset = 3254294, .properties = 5, .width = 76, .height = 21 },    /* text_setup@C8_A0, 101 */
    { .dataOffset = 3257486, .properties = 5, .width = 29, .height = 21 },    /* text_setup@C9_A0, 101 */
    { .dataOffset = 3258704, .properties = 5, .width = 41, .height = 21 },    /* text_setup@C0_A1, 101 */
    { .dataOffset = 3260426, .properties = 5, .width = 46, .height = 21 },    /* text_setup@C1_A1, 101 */
    { .dataOffset = 3262358, .properties = 5, .width = 80, .height = 21 },    /* text_setup@C2_A1, 101 */
    { .dataOffset = 3265718, .properties = 5, .width = 89, .height = 21 },    /* text_setup@C3_A1, 101 */
    { .dataOffset = 3269456, .properties = 5, .width = 52, .height = 21 },    /* text_setup@C4_A1, 101 */
    { .dataOffset = 3271640, .properties = 5, .width = 91, .height = 21 },    /* text_setup@C5_A1, 101 */
    { .dataOffset = 3275462, .properties = 5, .width = 81, .height = 21 },    /* text_setup@C6_A1, 101 */
    { .dataOffset = 3278864, .properties = 5, .width = 35, .height = 21 },    /* text_setup@C7_A1, 101 */
    { .dataOffset = 3280334, .properties = 5, .width = 76, .height = 21 },    /* text_setup@C8_A1, 101 */
    { .dataOffset = 3283526, .properties = 5, .width = 29, .height = 21 },    /* text_setup@C9_A1, 101 */
    { .dataOffset = 3284744, .properties = 5, .width = 50, .height = 21 },    /* text_theme@C0_A0, 101 */
    { .dataOffset = 3286844, .properties = 5, .width = 50, .height = 21 },    /* text_theme@C1_A0, 101 */
    { .dataOffset = 3288944, .properties = 5, .width = 50, .height = 21 },    /* text_theme@C2_A0, 101 */
    { .dataOffset = 3291044, .properties = 5, .width = 50, .height = 21 },    /* text_theme@C3_A0, 101 */
    { .dataOffset = 3293144, .properties = 5, .width = 41, .height = 21 },    /* text_theme@C4_A0, 101 */
    { .dataOffset = 3294866, .properties = 5, .width = 41, .height = 21 },    /* text_theme@C5_A0, 101 */
    { .dataOffset = 3296588, .properties = 5, .width = 39, .height = 21 },    /* text_theme@C6_A0, 101 */
    { .dataOffset = 3298226, .properties = 5, .width = 34, .height = 21 },    /* text_theme@C7_A0, 101 */
    { .dataOffset = 3299654, .properties = 5, .width = 41, .height = 21 },    /* text_theme@C8_A0, 101 */
    { .dataOffset = 3301376, .properties = 5, .width = 30, .height = 21 },    /* text_theme@C9_A0, 101 */
    { .dataOffset = 3302636, .properties = 5, .width = 50, .height = 21 },    /* text_theme@C0_A1, 101 */
    { .dataOffset = 3304736, .properties = 5, .width = 50, .height = 21 },    /* text_theme@C1_A1, 101 */
    { .dataOffset = 3306836, .properties = 5, .width = 50, .height = 21 },    /* text_theme@C2_A1, 101 */
    { .dataOffset = 3308936, .properties = 5, .width = 50, .height = 21 },    /* text_theme@C3_A1, 101 */
    { .dataOffset = 3311036, .properties = 5, .width = 41, .height = 21 },    /* text_theme@C4_A1, 101 */
    { .dataOffset = 3312758, .properties = 5, .width = 41, .height = 21 },    /* text_theme@C5_A1, 101 */
    { .dataOffset = 3314480, .properties = 5, .width = 39, .height = 21 },    /* text_theme@C6_A1, 101 */
    { .dataOffset = 3316118, .properties = 5, .width = 34, .height = 21 },    /* text_theme@C7_A1, 101 */
    { .dataOffset = 3317546, .properties = 5, .width = 41, .height = 21 },    /* text_theme@C8_A1, 101 */
    { .dataOffset = 3319268, .properties = 5, .width = 30, .height = 21 },    /* text_theme@C9_A1, 101 */
    { .dataOffset = 3320528, .properties = 5, .width = 36, .height = 21 },    /* text_time@C0_A0, 101 */
    { .dataOffset = 3322040, .properties = 5, .width = 26, .height = 21 },    /* text_time@C1_A0, 101 */
    { .dataOffset = 3323132, .properties = 5, .width = 27, .height = 21 },    /* text_time@C2_A0, 101 */
    { .dataOffset = 3324266, .properties = 5, .width = 42, .height = 21 },    /* text_time@C3_A0, 101 */
    { .dataOffset = 3326030, .properties = 5, .width = 34, .height = 21 },    /* text_time@C4_A0, 101 */
    { .dataOffset = 3327458, .properties = 5, .width = 25, .height = 21 },    /* text_time@C5_A0, 101 */
    { .dataOffset = 3328508, .properties = 5, .width = 47, .height = 21 },    /* text_time@C6_A0, 101 */
    { .dataOffset = 3330482, .properties = 5, .width = 33, .height = 21 },    /* text_time@C7_A0, 101 */
    { .dataOffset = 3331868, .properties = 5, .width = 33, .height = 21 },    /* text_time@C8_A0, 101 */
    { .dataOffset = 3333254, .properties = 5, .width = 31, .height = 21 },    /* text_time@C9_A0, 101 */
    { .dataOffset = 3334556, .properties = 5, .width = 36, .height = 21 },    /* text_time@C0_A1, 101 */
    { .dataOffset = 3336068, .properties = 5, .width = 26, .height = 21 },    /* text_time@C1_A1, 101 */
    { .dataOffset = 3337160, .properties = 5, .width = 27, .height = 21 },    /* text_time@C2_A1, 101 */
    { .dataOffset = 3338294, .properties = 5, .width = 42, .height = 21 },    /* text_time@C3_A1, 101 */
    { .dataOffset = 3340058, .properties = 5, .width = 34, .height = 21 },    /* text_time@C4_A1, 101 */
    { .dataOffset = 3341486, .properties = 5, .width = 25, .height = 21 },    /* text_time@C5_A1, 101 */
    { .dataOffset = 3342536, .properties = 5, .width = 47, .height = 21 },    /* text_time@C6_A1, 101 */
    { .dataOffset = 3344510, .properties = 5, .width = 33, .height = 21 },    /* text_time@C7_A1, 101 */
    { .dataOffset = 3345896, .properties = 5, .width = 33, .height = 21 },    /* text_time@C8_A1, 101 */
    { .dataOffset = 3347282, .properties = 5, .width = 31, .height = 21 },    /* text_time@C9_A1, 101 */
    { .dataOffset = 3348584, .properties = 5, .width = 76, .height = 29 },    /* title_alarm@C0_A0, 101 */
    { .dataOffset = 3352992, .properties = 5, .width = 76, .height = 29 },    /* title_alarm@C1_A0, 101 */
    { .dataOffset = 3357400, .properties = 5, .width = 76, .height = 29 },    /* title_alarm@C2_A0, 101 */
    { .dataOffset = 3361808, .properties = 5, .width = 88, .height = 29 },    /* title_alarm@C3_A0, 101 */
    { .dataOffset = 3366912, .properties = 5, .width = 88, .height = 29 },    /* title_alarm@C4_A0, 101 */
    { .dataOffset = 3372016, .properties = 5, .width = 93, .height = 29 },    /* title_alarm@C5_A0, 101 */
    { .dataOffset = 3377410, .properties = 5, .width = 102, .height = 29 },    /* title_alarm@C6_A0, 101 */
    { .dataOffset = 3383326, .properties = 5, .width = 66, .height = 29 },    /* title_alarm@C7_A0, 101 */
    { .dataOffset = 3387154, .properties = 5, .width = 65, .height = 29 },    /* title_alarm@C8_A0, 101 */
    { .dataOffset = 3390924, .properties = 5, .width = 83, .height = 29 },    /* title_alarm@C9_A0, 101 */
    { .dataOffset = 3395738, .properties = 5, .width = 76, .height = 29 },    /* title_alarm@C0_A1, 101 */
    { .dataOffset = 3400146, .properties = 5, .width = 76, .height = 29 },    /* title_alarm@C1_A1, 101 */
    { .dataOffset = 3404554, .properties = 5, .width = 76, .height = 29 },    /* title_alarm@C2_A1, 101 */
    { .dataOffset = 3408962, .properties = 5, .width = 88, .height = 29 },    /* title_alarm@C3_A1, 101 */
    { .dataOffset = 3414066, .properties = 5, .width = 88, .height = 29 },    /* title_alarm@C4_A1, 101 */
    { .dataOffset = 3419170, .properties = 5, .width = 93, .height = 29 },    /* title_alarm@C5_A1, 101 */
    { .dataOffset = 3424564, .properties = 5, .width = 102, .height = 29 },    /* title_alarm@C6_A1, 101 */
    { .dataOffset = 3430480, .properties = 5, .width = 66, .height = 29 },    /* title_alarm@C7_A1, 101 */
    { .dataOffset = 3434308, .properties = 5, .width = 65, .height = 29 },    /* title_alarm@C8_A1, 101 */
    { .dataOffset = 3438078, .properties = 5, .width = 83, .height = 29 },    /* title_alarm@C9_A1, 101 */
    { .dataOffset = 3442892, .properties = 5, .width = 105, .height = 29 },    /* title_brightness@C0_A0, 101 */
    { .dataOffset = 3448982, .properties = 5, .width = 106, .height = 29 },    /* title_brightness@C1_A0, 101 */
    { .dataOffset = 3455130, .properties = 5, .width = 92, .height = 29 },    /* title_brightness@C2_A0, 101 */
    { .dataOffset = 3460466, .properties = 5, .width = 110, .height = 29 },    /* title_brightness@C3_A0, 101 */
    { .dataOffset = 3466846, .properties = 5, .width = 49, .height = 29 },    /* title_brightness@C4_A0, 101 */
    { .dataOffset = 3469688, .properties = 5, .width = 110, .height = 29 },    /* title_brightness@C5_A0, 101 */
    { .dataOffset = 3476068, .properties = 5, .width = 86, .height = 29 },    /* title_brightness@C6_A0, 101 */
    { .dataOffset = 3481056, .properties = 5, .width = 46, .height = 29 },    /* title_brightness@C7_A0, 101 */
    { .dataOffset = 3483724, .properties = 5, .width = 57, .height = 29 },    /* title_brightness@C8_A0, 101 */
    { .dataOffset = 3487030, .properties = 5, .width = 39, .height = 29 },    /* title_brightness@C9_A0, 101 */
    { .dataOffset = 3489292, .properties = 5, .width = 105, .height = 29 },    /* title_brightness@C0_A1, 101 */
    { .dataOffset = 3495382, .properties = 5, .width = 106, .height = 29 },    /* title_brightness@C1_A1, 101 */
    { .dataOffset = 3501530, .properties = 5, .width = 92, .height = 29 },    /* title_brightness@C2_A1, 101 */
    { .dataOffset = 3506866, .properties = 5, .width = 110, .height = 29 },    /* title_brightness@C3_A1, 101 */
    { .dataOffset = 3513246, .properties = 5, .width = 49, .height = 29 },    /* title_brightness@C4_A1, 101 */
    { .dataOffset = 3516088, .properties = 5, .width = 110, .height = 29 },    /* title_brightness@C5_A1, 101 */
    { .dataOffset = 3522468, .properties = 5, .width = 86, .height = 29 },    /* title_brightness@C6_A1, 101 */
    { .dataOffset = 3527456, .properties = 5, .width = 46, .height = 29 },    /* title_brightness@C7_A1, 101 */
    { .dataOffset = 3530124, .properties = 5, .width = 57, .height = 29 },    /* title_brightness@C8_A1, 101 */
    { .dataOffset = 3533430, .properties = 5, .width = 39, .height = 29 },    /* title_brightness@C9_A1, 101 */
    { .dataOffset = 3535692, .properties = 5, .width = 63, .height = 29 },    /* title_colors@C0_A0, 101 */
    { .dataOffset = 3539346, .properties = 5, .width = 74, .height = 29 },    /* title_colors@C1_A0, 101 */
    { .dataOffset = 3543638, .properties = 5, .width = 67, .height = 29 },    /* title_colors@C2_A0, 101 */
    { .dataOffset = 3547524, .properties = 5, .width = 87, .height = 29 },    /* title_colors@C3_A0, 101 */
    { .dataOffset = 3552570, .properties = 5, .width = 75, .height = 29 },    /* title_colors@C4_A0, 101 */
    { .dataOffset = 3556920, .properties = 5, .width = 57, .height = 29 },    /* title_colors@C5_A0, 101 */
    { .dataOffset = 3560226, .properties = 5, .width = 66, .height = 29 },    /* title_colors@C6_A0, 101 */
    { .dataOffset = 3564054, .properties = 5, .width = 47, .height = 29 },    /* title_colors@C7_A0, 101 */
    { .dataOffset = 3566780, .properties = 5, .width = 22, .height = 29 },    /* title_colors@C8_A0, 101 */
    { .dataOffset = 3568056, .properties = 5, .width = 42, .height = 29 },    /* title_colors@C9_A0, 101 */
    { .dataOffset = 3570492, .properties = 5, .width = 63, .height = 29 },    /* title_colors@C0_A1, 101 */
    { .dataOffset = 3574146, .properties = 5, .width = 74, .height = 29 },    /* title_colors@C1_A1, 101 */
    { .dataOffset = 3578438, .properties = 5, .width = 67, .height = 29 },    /* title_colors@C2_A1, 101 */
    { .dataOffset = 3582324, .properties = 5, .width = 87, .height = 29 },    /* title_colors@C3_A1, 101 */
    { .dataOffset = 3587370, .properties = 5, .width = 75, .height = 29 },    /* title_colors@C4_A1, 101 */
    { .dataOffset = 3591720, .properties = 5, .width = 57, .height = 29 },    /* title_colors@C5_A1, 101 */
    { .dataOffset = 3595026, .properties = 5, .width = 66, .height = 29 },    /* title_colors@C6_A1, 101 */
    { .dataOffset = 3598854, .properties = 5, .width = 47, .height = 29 },    /* title_colors@C7_A1, 101 */
    { .dataOffset = 3601580, .properties = 5, .width = 22, .height = 29 },    /* title_colors@C8_A1, 101 */
    { .dataOffset = 3602856, .properties = 5, .width = 42, .height = 29 },    /* title_colors@C9_A1, 101 */
    { .dataOffset = 3605292, .properties = 5, .width = 45, .height = 29 },    /* title_date@C0_A0, 101 */
    { .dataOffset = 3607902, .properties = 5, .width = 64, .height = 29 },    /* title_date@C1_A0, 101 */
    { .dataOffset = 3611614, .properties = 5, .width = 64, .height = 29 },    /* title_date@C2_A0, 101 */
    { .dataOffset = 3615326, .properties = 5, .width = 45, .height = 29 },    /* title_date@C3_A0, 101 */
    { .dataOffset = 3617936, .properties = 5, .width = 59, .height = 29 },    /* title_date@C4_A0, 101 */
    { .dataOffset = 3621358, .properties = 5, .width = 72, .height = 29 },    /* title_date@C5_A0, 101 */
    { .dataOffset = 3625534, .properties = 5, .width = 51, .height = 29 },    /* title_date@C6_A0, 101 */
    { .dataOffset = 3628492, .properties = 5, .width = 43, .height = 29 },    /* title_date@C7_A0, 101 */
    { .dataOffset = 3630986, .properties = 5, .width = 43, .height = 29 },    /* title_date@C8_A0, 101 */
    { .dataOffset = 3633480, .properties = 5, .width = 42, .height = 29 },    /* title_date@C9_A0, 101 */
    { .dataOffset = 3635916, .properties = 5, .width = 45, .height = 29 },    /* title_date@C0_A1, 101 */
    { .dataOffset = 3638526, .properties = 5, .width = 64, .height = 29 },    /* title_date@C1_A1, 101 */
    { .dataOffset = 3642238, .properties = 5, .width = 64, .height = 29 },    /* title_date@C2_A1, 101 */
    { .dataOffset = 3645950, .properties = 5, .width = 45, .height = 29 },    /* title_date@C3_A1, 101 */
    { .dataOffset = 3648560, .properties = 5, .width = 59, .height = 29 },    /* title_date@C4_A1, 101 */
    { .dataOffset = 3651982, .properties = 5, .width = 72, .height = 29 },    /* title_date@C5_A1, 101 */
    { .dataOffset = 3656158, .properties = 5, .width = 51, .height = 29 },    /* title_date@C6_A1, 101 */
    { .dataOffset = 3659116, .properties = 5, .width = 43, .height = 29 },    /* title_date@C7_A1, 101 */
    { .dataOffset = 3661610, .properties = 5, .width = 43, .height = 29 },    /* title_date@C8_A1, 101 */
    { .dataOffset = 3664104, .properties = 5, .width = 42, .height = 29 },    /* title_date@C9_A1, 101 */
    { .dataOffset = 3666540, .properties = 5, .width = 37, .height = 29 },    /* title_info@C0_A0, 101 */
    { .dataOffset = 3668686, .properties = 5, .width = 37, .height = 29 },    /* title_info@C1_A0, 101 */
    { .dataOffset = 3670832, .properties = 5, .width = 37, .height = 29 },    /* title_info@C2_A0, 101 */
    { .dataOffset = 3672978, .properties = 5, .width = 37, .height = 29 },    /* title_info@C3_A0, 101 */
    { .dataOffset = 3675124, .properties = 5, .width = 119, .height = 29 },    /* title_info@C4_A0, 101 */
    { .dataOffset = 3682026, .properties = 5, .width = 125, .height = 29 },    /* title_info@C5_A0, 101 */
    { .dataOffset = 3689276, .properties = 5, .width = 136, .height = 29 },    /* title_info@C6_A0, 101 */
    { .dataOffset = 3697164, .properties = 5, .width = 48, .height = 29 },    /* title_info@C7_A0, 101 */
    { .dataOffset = 3699948, .properties = 5, .width = 48, .height = 29 },    /* title_info@C8_A0, 101 */
    { .dataOffset = 3702732, .properties = 5, .width = 42, .height = 29 },    /* title_info@C9_A0, 101 */
    { .dataOffset = 3705168, .properties = 5, .width = 37, .height = 29 },    /* title_info@C0_A1, 101 */
    { .dataOffset = 3707314, .properties = 5, .width = 37, .height = 29 },    /* title_info@C1_A1, 101 */
    { .dataOffset = 3709460, .properties = 5, .width = 37, .height = 29 },    /* title_info@C2_A1, 101 */
    { .dataOffset = 3711606, .properties = 5, .width = 37, .height = 29 },    /* title_info@C3_A1, 101 */
    { .dataOffset = 3713752, .properties = 5, .width = 119, .height = 29 },    /* title_info@C4_A1, 101 */
    { .dataOffset = 3720654, .properties = 5, .width = 125, .height = 29 },    /* title_info@C5_A1, 101 */
    { .dataOffset = 3727904, .properties = 5, .width = 136, .height = 29 },    /* title_info@C6_A1, 101 */
    { .dataOffset = 3735792, .properties = 5, .width = 48, .height = 29 },    /* title_info@C7_A1, 101 */
    { .dataOffset = 3738576, .properties = 5, .width = 48, .height = 29 },    /* title_info@C8_A1, 101 */
    { .dataOffset = 3741360, .properties = 5, .width = 42, .height = 29 },    /* title_info@C9_A1, 101 */
    { .dataOffset = 3743796, .properties = 5, .width = 97, .height = 29 },    /* title_language@C0_A0, 101 */
    { .dataOffset = 3749422, .properties = 5, .width = 42, .height = 29 },    /* title_language@C1_A0, 101 */
    { .dataOffset = 3751858, .properties = 5, .width = 82, .height = 29 },    /* title_language@C2_A0, 101 */
    { .dataOffset = 3756614, .properties = 5, .width = 72, .height = 29 },    /* title_language@C3_A0, 101 */
    { .dataOffset = 3760790, .properties = 5, .width = 67, .height = 29 },    /* title_language@C4_A0, 101 */
    { .dataOffset = 3764676, .properties = 5, .width = 65, .height = 29 },    /* title_language@C5_A0, 101 */
    { .dataOffset = 3768446, .properties = 5, .width = 55, .height = 29 },    /* title_language@C6_A0, 101 */
    { .dataOffset = 3771636, .properties = 5, .width = 47, .height = 29 },    /* title_language@C7_A0, 101 */
    { .dataOffset = 3774362, .properties = 5, .width = 47, .height = 29 },    /* title_language@C8_A0, 101 */
    { .dataOffset = 3777088, .properties = 5, .width = 39, .height = 29 },    /* title_language@C9_A0, 101 */
    { .dataOffset = 3779350, .properties = 5, .width = 97, .height = 29 },    /* title_language@C0_A1, 101 */
    { .dataOffset = 3784976, .properties = 5, .width = 42, .height = 29 },    /* title_language@C1_A1, 101 */
    { .dataOffset = 3787412, .properties = 5, .width = 82, .height = 29 },    /* title_language@C2_A1, 101 */
    { .dataOffset = 3792168, .properties = 5, .width = 72, .height = 29 },    /* title_language@C3_A1, 101 */
    { .dataOffset = 3796344, .properties = 5, .width = 67, .height = 29 },    /* title_language@C4_A1, 101 */
    { .dataOffset = 3800230, .properties = 5, .width = 65, .height = 29 },    /* title_language@C5_A1, 101 */
    { .dataOffset = 3804000, .properties = 5, .width = 55, .height = 29 },    /* title_language@C6_A1, 101 */
    { .dataOffset = 3807190, .properties = 5, .width = 47, .height = 29 },    /* title_language@C7_A1, 101 */
    { .dataOffset = 3809916, .properties = 5, .width = 47, .height = 29 },    /* title_language@C8_A1, 101 */
    { .dataOffset = 3812642, .properties = 5, .width = 39, .height = 29 },    /* title_language@C9_A1, 101 */
    { .dataOffset = 3814904, .properties = 5, .width = 110, .height = 29 },    /* title_main_menu@C0_A0, 101 */
    { .dataOffset = 3821284, .properties = 5, .width = 117, .height = 29 },    /* title_main_menu@C1_A0, 101 */
    { .dataOffset = 3828070, .properties = 5, .width = 115, .height = 29 },    /* title_main_menu@C2_A0, 101 */
    { .dataOffset = 3834740, .properties = 5, .width = 146, .height = 29 },    /* title_main_menu@C3_A0, 101 */
    { .dataOffset = 3843208, .properties = 5, .width = 146, .height = 29 },    /* title_main_menu@C4_A0, 101 */
    { .dataOffset = 3851676, .properties = 5, .width = 159, .height = 29 },    /* title_main_menu@C5_A0, 101 */
    { .dataOffset = 3860898, .properties = 5, .width = 152, .height = 29 },    /* title_main_menu@C6_A0, 101 */
    { .dataOffset = 3869714, .properties = 5, .width = 72, .height = 29 },    /* title_main_menu@C7_A0, 101 */
    { .dataOffset = 3873890, .properties = 5, .width = 123, .height = 29 },    /* title_main_menu@C8_A0, 101 */
    { .dataOffset = 3881024, .properties = 5, .width = 92, .height = 29 },    /* title_main_menu@C9_A0, 101 */
    { .dataOffset = 3886360, .properties = 5, .width = 110, .height = 29 },    /* title_main_menu@C0_A1, 101 */
    { .dataOffset = 3892740, .properties = 5, .width = 117, .height = 29 },    /* title_main_menu@C1_A1, 101 */
    { .dataOffset = 3899526, .properties = 5, .width = 115, .height = 29 },    /* title_main_menu@C2_A1, 101 */
    { .dataOffset = 3906196, .properties = 5, .width = 146, .height = 29 },    /* title_main_menu@C3_A1, 101 */
    { .dataOffset = 3914664, .properties = 5, .width = 146, .height = 29 },    /* title_main_menu@C4_A1, 101 */
    { .dataOffset = 3923132, .properties = 5, .width = 159, .height = 29 },    /* title_main_menu@C5_A1, 101 */
    { .dataOffset = 3932354, .properties = 5, .width = 152, .height = 29 },    /* title_main_menu@C6_A1, 101 */
    { .dataOffset = 3941170, .properties = 5, .width = 72, .height = 29 },    /* title_main_menu@C7_A1, 101 */
    { .dataOffset = 3945346, .properties = 5, .width = 123, .height = 29 },    /* title_main_menu@C8_A1, 101 */
    { .dataOffset = 3952480, .properties = 5, .width = 92, .height = 29 },    /* title_main_menu@C9_A1, 101 */
    { .dataOffset = 3957816, .properties = 5, .width = 138, .height = 29 },    /* title_measurement@C0_A0, 101 */
    { .dataOffset = 3965820, .properties = 5, .width = 79, .height = 29 },    /* title_measurement@C1_A0, 101 */
    { .dataOffset = 3970402, .properties = 5, .width = 90, .height = 29 },    /* title_measurement@C2_A0, 101 */
    { .dataOffset = 3975622, .properties = 5, .width = 74, .height = 29 },    /* title_measurement@C3_A0, 101 */
    { .dataOffset = 3979914, .properties = 5, .width = 90, .height = 29 },    /* title_measurement@C4_A0, 101 */
    { .dataOffset = 3985134, .properties = 5, .width = 122, .height = 29 },    /* title_measurement@C5_A0, 101 */
    { .dataOffset = 3992210, .properties = 5, .width = 117, .height = 29 },    /* title_measurement@C6_A0, 101 */
    { .dataOffset = 3998996, .properties = 5, .width = 48, .height = 29 },    /* title_measurement@C7_A0, 101 */
    { .dataOffset = 4001780, .properties = 5, .width = 46, .height = 29 },    /* title_measurement@C8_A0, 101 */
    { .dataOffset = 4004448, .properties = 5, .width = 42, .height = 29 },    /* title_measurement@C9_A0, 101 */
    { .dataOffset = 4006884, .properties = 5, .width = 138, .height = 29 },    /* title_measurement@C0_A1, 101 */
    { .dataOffset = 4014888, .properties = 5, .width = 79, .height = 29 },    /* title_measurement@C1_A1, 101 */
    { .dataOffset = 4019470, .properties = 5, .width = 90, .height = 29 },    /* title_measurement@C2_A1, 101 */
    { .dataOffset = 4024690, .properties = 5, .width = 74, .height = 29 },    /* title_measurement@C3_A1, 101 */
    { .dataOffset = 4028982, .properties = 5, .width = 90, .height = 29 },    /* title_measurement@C4_A1, 101 */
    { .dataOffset = 4034202, .properties = 5, .width = 122, .height = 29 },    /* title_measurement@C5_A1, 101 */
    { .dataOffset = 4041278, .properties = 5, .width = 117, .height = 29 },    /* title_measurement@C6_A1, 101 */
    { .dataOffset = 4048064, .properties = 5, .width = 48, .height = 29 },    /* title_measurement@C7_A1, 101 */
    { .dataOffset = 4050848, .properties = 5, .width = 46, .height = 29 },    /* title_measurement@C8_A1, 101 */
    { .dataOffset = 4053516, .properties = 5, .width = 42, .height = 29 },    /* title_measurement@C9_A1, 101 */
    { .dataOffset = 4055952, .properties = 5, .width = 81, .height = 29 },    /* title_settings@C0_A0, 101 */
    { .dataOffset = 4060650, .properties = 5, .width = 113, .height = 29 },    /* title_settings@C1_A0, 101 */
    { .dataOffset = 4067204, .properties = 5, .width = 132, .height = 29 },    /* title_settings@C2_A0, 101 */
    { .dataOffset = 4074860, .properties = 5, .width = 115, .height = 29 },    /* title_settings@C3_A0, 101 */
    { .dataOffset = 4081530, .properties = 5, .width = 139, .height = 29 },    /* title_settings@C4_A0, 101 */
    { .dataOffset = 4089592, .properties = 5, .width = 128, .height = 29 },    /* title_settings@C5_A0, 101 */
    { .dataOffset = 4097016, .properties = 5, .width = 120, .height = 29 },    /* title_settings@C6_A0, 101 */
    { .dataOffset = 4103976, .properties = 5, .width = 46, .height = 29 },    /* title_settings@C7_A0, 101 */
    { .dataOffset = 4106644, .properties = 5, .width = 46, .height = 29 },    /* title_settings@C8_A0, 101 */
    { .dataOffset = 4109312, .properties = 5, .width = 41, .height = 29 },    /* title_settings@C9_A0, 101 */
    { .dataOffset = 4111690, .properties = 5, .width = 81, .height = 29 },    /* title_settings@C0_A1, 101 */
    { .dataOffset = 4116388, .properties = 5, .width = 113, .height = 29 },    /* title_settings@C1_A1, 101 */
    { .dataOffset = 4122942, .properties = 5, .width = 132, .height = 29 },    /* title_settings@C2_A1, 101 */
    { .dataOffset = 4130598, .properties = 5, .width = 115, .height = 29 },    /* title_settings@C3_A1, 101 */
    { .dataOffset = 4137268, .properties = 5, .width = 139, .height = 29 },    /* title_settings@C4_A1, 101 */
    { .dataOffset = 4145330, .properties = 5, .width = 128, .height = 29 },    /* title_settings@C5_A1, 101 */
    { .dataOffset = 4152754, .properties = 5, .width = 120, .height = 29 },    /* title_settings@C6_A1, 101 */
    { .dataOffset = 4159714, .properties = 5, .width = 46, .height = 29 },    /* title_settings@C7_A1, 101 */
    { .dataOffset = 4162382, .properties = 5, .width = 46, .height = 29 },    /* title_settings@C8_A1, 101 */
    { .dataOffset = 4165050, .properties = 5, .width = 41, .height = 29 },    /* title_settings@C9_A1, 101 */
    { .dataOffset = 4167428, .properties = 5, .width = 57, .height = 29 },    /* title_setup@C0_A0, 101 */
    { .dataOffset = 4170734, .properties = 5, .width = 62, .height = 29 },    /* title_setup@C1_A0, 101 */
    { .dataOffset = 4174330, .properties = 5, .width = 111, .height = 29 },    /* title_setup@C2_A0, 101 */
    { .dataOffset = 4180768, .properties = 5, .width = 121, .height = 29 },    /* title_setup@C3_A0, 101 */
    { .dataOffset = 4187786, .properties = 5, .width = 72, .height = 29 },    /* title_setup@C4_A0, 101 */
    { .dataOffset = 4191962, .properties = 5, .width = 125, .height = 29 },    /* title_setup@C5_A0, 101 */
    { .dataOffset = 4199212, .properties = 5, .width = 112, .height = 29 },    /* title_setup@C6_A0, 101 */
    { .dataOffset = 4205708, .properties = 5, .width = 46, .height = 29 },    /* title_setup@C7_A0, 101 */
    { .dataOffset = 4208376, .properties = 5, .width = 102, .height = 29 },    /* title_setup@C8_A0, 101 */
    { .dataOffset = 4214292, .properties = 5, .width = 40, .height = 29 },    /* title_setup@C9_A0, 101 */
    { .dataOffset = 4216612, .properties = 5, .width = 57, .height = 29 },    /* title_setup@C0_A1, 101 */
    { .dataOffset = 4219918, .properties = 5, .width = 62, .height = 29 },    /* title_setup@C1_A1, 101 */
    { .dataOffset = 4223514, .properties = 5, .width = 111, .height = 29 },    /* title_setup@C2_A1, 101 */
    { .dataOffset = 4229952, .properties = 5, .width = 121, .height = 29 },    /* title_setup@C3_A1, 101 */
    { .dataOffset = 4236970, .properties = 5, .width = 72, .height = 29 },    /* title_setup@C4_A1, 101 */
    { .dataOffset = 4241146, .properties = 5, .width = 125, .height = 29 },    /* title_setup@C5_A1, 101 */
    { .dataOffset = 4248396, .properties = 5, .width = 112, .height = 29 },    /* title_setup@C6_A1, 101 */
    { .dataOffset = 4254892, .properties = 5, .width = 46, .height = 29 },    /* title_setup@C7_A1, 101 */
    { .dataOffset = 4257560, .properties = 5, .width = 102, .height = 29 },    /* title_setup@C8_A1, 101 */
    { .dataOffset = 4263476, .properties = 5, .width = 40, .height = 29 },    /* title_setup@C9_A1, 101 */
    { .dataOffset = 4265796, .properties = 5, .width = 69, .height = 29 },    /* title_theme@C0_A0, 101 */
    { .dataOffset = 4269798, .properties = 5, .width = 69, .height = 29 },    /* title_theme@C1_A0, 101 */
    { .dataOffset = 4273800, .properties = 5, .width = 69, .height = 29 },    /* title_theme@C2_A0, 101 */
    { .dataOffset = 4277802, .properties = 5, .width = 69, .height = 29 },    /* title_theme@C3_A0, 101 */
    { .dataOffset = 4281804, .properties = 5, .width = 56, .height = 29 },    /* title_theme@C4_A0, 101 */
    { .dataOffset = 4285052, .properties = 5, .width = 56, .height = 29 },    /* title_theme@C5_A0, 101 */
    { .dataOffset = 4288300, .properties = 5, .width = 53, .height = 29 },    /* title_theme@C6_A0, 101 */
    { .dataOffset = 4291374, .properties = 5, .width = 47, .height = 29 },    /* title_theme@C7_A0, 101 */
    { .dataOffset = 4294100, .properties = 5, .width = 55, .height = 29 },    /* title_theme@C8_A0, 101 */
    { .dataOffset = 4297290, .properties = 5, .width = 41, .height = 29 },    /* title_theme@C9_A0, 101 */
    { .dataOffset = 4299668, .properties = 5, .width = 69, .height = 29 },    /* title_theme@C0_A1, 101 */
    { .dataOffset = 4303670, .properties = 5, .width = 69, .height = 29 },    /* title_theme@C1_A1, 101 */
    { .dataOffset = 4307672, .properties = 5, .width = 69, .height = 29 },    /* title_theme@C2_A1, 101 */
    { .dataOffset = 4311674, .properties = 5, .width = 69, .height = 29 },    /* title_theme@C3_A1, 101 */
    { .dataOffset = 4315676, .properties = 5, .width = 56, .height = 29 },    /* title_theme@C4_A1, 101 */
    { .dataOffset = 4318924, .properties = 5, .width = 56, .height = 29 },    /* title_theme@C5_A1, 101 */
    { .dataOffset = 4322172, .properties = 5, .width = 53, .height = 29 },    /* title_theme@C6_A1, 101 */
    { .dataOffset = 4325246, .properties = 5, .width = 47, .height = 29 },    /* title_theme@C7_A1, 101 */
    { .dataOffset = 4327972, .properties = 5, .width = 55, .height = 29 },    /* title_theme@C8_A1, 101 */
    { .dataOffset = 4331162, .properties = 5, .width = 41, .height = 29 },    /* title_theme@C9_A1, 101 */
    { .dataOffset = 4333540, .properties = 5, .width = 50, .height = 29 },    /* title_time@C0_A0, 101 */
    { .dataOffset = 4336440, .properties = 5, .width = 35, .height = 29 },    /* title_time@C1_A0, 101 */
    { .dataOffset = 4338470, .properties = 5, .width = 38, .height = 29 },    /* title_time@C2_A0, 101 */
    { .dataOffset = 4340674, .properties = 5, .width = 58, .height = 29 },    /* title_time@C3_A0, 101 */
    { .dataOffset = 4344038, .properties = 5, .width = 47, .height = 29 },    /* title_time@C4_A0, 101 */
    { .dataOffset = 4346764, .properties = 5, .width = 33, .height = 29 },    /* title_time@C5_A0, 101 */
    { .dataOffset = 4348678, .properties = 5, .width = 65, .height = 29 },    /* title_time@C6_A0, 101 */
    { .dataOffset = 4352448, .properties = 5, .width = 45, .height = 29 },    /* title_time@C7_A0, 101 */
    { .dataOffset = 4355058, .properties = 5, .width = 46, .height = 29 },    /* title_time@C8_A0, 101 */
    { .dataOffset = 4357726, .properties = 5, .width = 42, .height = 29 },    /* title_time@C9_A0, 101 */
    { .dataOffset = 4360162, .properties = 5, .width = 50, .height = 29 },    /* title_time@C0_A1, 101 */
    { .dataOffset = 4363062, .properties = 5, .width = 35, .height = 29 },    /* title_time@C1_A1, 101 */
    { .dataOffset = 4365092, .properties = 5, .width = 38, .height = 29 },    /* title_time@C2_A1, 101 */
    { .dataOffset = 4367296, .properties = 5, .width = 58, .height = 29 },    /* title_time@C3_A1, 101 */
    { .dataOffset = 4370660, .properties = 5, .width = 47, .height = 29 },    /* title_time@C4_A1, 101 */
    { .dataOffset = 4373386, .properties = 5, .width = 33, .height = 29 },    /* title_time@C5_A1, 101 */
    { .dataOffset = 4375300, .properties = 5, .width = 65, .height = 29 },    /* title_time@C6_A1, 101 */
    { .dataOffset = 4379070, .properties = 5, .width = 45, .height = 29 },    /* title_time@C7_A1, 101 */
    { .dataOffset = 4381680, .properties = 5, .width = 46, .height = 29 },    /* title_time@C8_A1, 101 */
    { .dataOffset = 4384348, .properties = 5, .width = 42, .height = 29 },    /* title_time@C9_A1, 101 */
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
