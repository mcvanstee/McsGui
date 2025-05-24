#include "fs_file_search.h"

#define FS_FILE_INFO_SIZE 9
#define FS_FILE_DUMMY 0xFFFFFFFFU

const fs_file_info_s fs_file_infos[] =
{
    { .dataOffset = 16, .properties = 2, .width = 32, .height = 27 },    /* IRL-Logo_@B000, 10 */
    { .dataOffset = 1744, .properties = 2, .width = 36, .height = 29 },    /* IRL-Logo_@B001, 10 */
    { .dataOffset = 3832, .properties = 2, .width = 39, .height = 32 },    /* IRL-Logo_@B002, 10 */
    { .dataOffset = 6328, .properties = 2, .width = 42, .height = 35 },    /* IRL-Logo_@B003, 10 */
    { .dataOffset = 9268, .properties = 2, .width = 46, .height = 37 },    /* IRL-Logo_@B004, 10 */
    { .dataOffset = 12672, .properties = 2, .width = 49, .height = 40 },    /* IRL-Logo_@B005, 10 */
    { .dataOffset = 16592, .properties = 2, .width = 52, .height = 43 },    /* IRL-Logo_@B006, 10 */
    { .dataOffset = 21064, .properties = 2, .width = 56, .height = 46 },    /* IRL-Logo_@B007, 10 */
    { .dataOffset = 26216, .properties = 2, .width = 59, .height = 48 },    /* IRL-Logo_@B008, 10 */
    { .dataOffset = 31880, .properties = 2, .width = 62, .height = 50 },    /* IRL-Logo_@B009, 10 */
    { .dataOffset = 38080, .properties = 2, .width = 65, .height = 54 },    /* IRL-Logo_@B010, 10 */
    { .dataOffset = 45100, .properties = 2, .width = 69, .height = 56 },    /* IRL-Logo_@B011, 10 */
    { .dataOffset = 52828, .properties = 2, .width = 72, .height = 59 },    /* IRL-Logo_@B012, 10 */
    { .dataOffset = 61324, .properties = 2, .width = 76, .height = 62 },    /* IRL-Logo_@B013, 10 */
    { .dataOffset = 70748, .properties = 2, .width = 79, .height = 64 },    /* IRL-Logo_@B014, 10 */
    { .dataOffset = 80860, .properties = 2, .width = 82, .height = 67 },    /* IRL-Logo_@B015, 10 */
    { .dataOffset = 91848, .properties = 2, .width = 86, .height = 69 },    /* IRL-Logo_@B016, 10 */
    { .dataOffset = 103716, .properties = 2, .width = 89, .height = 72 },    /* IRL-Logo_@B017, 10 */
    { .dataOffset = 116532, .properties = 2, .width = 92, .height = 75 },    /* IRL-Logo_@B018, 10 */
    { .dataOffset = 130332, .properties = 2, .width = 95, .height = 77 },    /* IRL-Logo_@B019, 10 */
    { .dataOffset = 144962, .properties = 2, .width = 100, .height = 80 },    /* IRL-Logo_@B020, 10 */
    { .dataOffset = 160962, .properties = 2, .width = 102, .height = 83 },    /* IRL-Logo_@B021, 10 */
    { .dataOffset = 177894, .properties = 2, .width = 105, .height = 85 },    /* IRL-Logo_@B022, 10 */
    { .dataOffset = 195744, .properties = 2, .width = 109, .height = 88 },    /* IRL-Logo_@B023, 10 */
    { .dataOffset = 214928, .properties = 1, .width = 146, .height = 38 },    /* Footer_Button@A0, 1 */
    { .dataOffset = 226024, .properties = 1, .width = 146, .height = 38 },    /* Footer_Button@A1, 1 */
    { .dataOffset = 237120, .properties = 1, .width = 30, .height = 30 },    /* NumInput_minus@A0, 1 */
    { .dataOffset = 238920, .properties = 1, .width = 30, .height = 30 },    /* NumInput_minus@A1, 1 */
    { .dataOffset = 240720, .properties = 1, .width = 30, .height = 30 },    /* NumInput_plus@A0, 1 */
    { .dataOffset = 242520, .properties = 1, .width = 30, .height = 30 },    /* NumInput_plus@A1, 1 */
    { .dataOffset = 244320, .properties = 1, .width = 146, .height = 90 },    /* Page_Background@A0, 1 */
    { .dataOffset = 270600, .properties = 1, .width = 146, .height = 90 },    /* Page_Background@A1, 1 */
    { .dataOffset = 296880, .properties = 1, .width = 22, .height = 31 },    /* Slider@A0, 1 */
    { .dataOffset = 298244, .properties = 1, .width = 22, .height = 31 },    /* Slider@A1, 1 */
    { .dataOffset = 299608, .properties = 17, .width = 18, .height = 20 },    /* icon_button_Agenda@A0_E0, 10001 */
    { .dataOffset = 300328, .properties = 17, .width = 18, .height = 20 },    /* icon_button_Agenda@A0_E1, 10001 */
    { .dataOffset = 301048, .properties = 17, .width = 18, .height = 20 },    /* icon_button_Agenda@A0_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_AGENDA__A000_E003, 11 */
    { .dataOffset = 301768, .properties = 17, .width = 18, .height = 20 },    /* icon_button_Agenda@A1_E0, 10001 */
    { .dataOffset = 302488, .properties = 17, .width = 18, .height = 20 },    /* icon_button_Agenda@A1_E1, 10001 */
    { .dataOffset = 303208, .properties = 17, .width = 18, .height = 20 },    /* icon_button_Agenda@A1_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_AGENDA__A001_E003, 11 */
    { .dataOffset = 303928, .properties = 17, .width = 35, .height = 18 },    /* icon_button_Arrow-Back@A0_E0, 10001 */
    { .dataOffset = 305188, .properties = 17, .width = 35, .height = 18 },    /* icon_button_Arrow-Back@A0_E1, 10001 */
    { .dataOffset = 306448, .properties = 17, .width = 35, .height = 18 },    /* icon_button_Arrow-Back@A0_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_ARROW_BACK__A000_E003, 11 */
    { .dataOffset = 307708, .properties = 17, .width = 35, .height = 18 },    /* icon_button_Arrow-Back@A1_E0, 10001 */
    { .dataOffset = 308968, .properties = 17, .width = 35, .height = 18 },    /* icon_button_Arrow-Back@A1_E1, 10001 */
    { .dataOffset = 310228, .properties = 17, .width = 35, .height = 18 },    /* icon_button_Arrow-Back@A1_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_ARROW_BACK__A001_E003, 11 */
    { .dataOffset = 311488, .properties = 17, .width = 16, .height = 18 },    /* icon_button_Bell@A0_E0, 10001 */
    { .dataOffset = 312064, .properties = 17, .width = 16, .height = 18 },    /* icon_button_Bell@A0_E1, 10001 */
    { .dataOffset = 312640, .properties = 17, .width = 16, .height = 18 },    /* icon_button_Bell@A0_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_BELL__A000_E003, 11 */
    { .dataOffset = 313216, .properties = 17, .width = 16, .height = 18 },    /* icon_button_Bell@A1_E0, 10001 */
    { .dataOffset = 313792, .properties = 17, .width = 16, .height = 18 },    /* icon_button_Bell@A1_E1, 10001 */
    { .dataOffset = 314368, .properties = 17, .width = 16, .height = 18 },    /* icon_button_Bell@A1_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_BELL__A001_E003, 11 */
    { .dataOffset = 314944, .properties = 17, .width = 30, .height = 25 },    /* icon_button_Brightness@A0_E0, 10001 */
    { .dataOffset = 316444, .properties = 17, .width = 30, .height = 25 },    /* icon_button_Brightness@A0_E1, 10001 */
    { .dataOffset = 317944, .properties = 17, .width = 30, .height = 25 },    /* icon_button_Brightness@A0_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_BRIGHTNESS__A000_E003, 11 */
    { .dataOffset = 319444, .properties = 17, .width = 30, .height = 25 },    /* icon_button_Brightness@A1_E0, 10001 */
    { .dataOffset = 320944, .properties = 17, .width = 30, .height = 25 },    /* icon_button_Brightness@A1_E1, 10001 */
    { .dataOffset = 322444, .properties = 17, .width = 30, .height = 25 },    /* icon_button_Brightness@A1_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_BRIGHTNESS__A001_E003, 11 */
    { .dataOffset = 323944, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Brush@A0_E0, 10001 */
    { .dataOffset = 324912, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Brush@A0_E1, 10001 */
    { .dataOffset = 325880, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Brush@A0_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_BRUSH__A000_E003, 11 */
    { .dataOffset = 326848, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Brush@A1_E0, 10001 */
    { .dataOffset = 327816, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Brush@A1_E1, 10001 */
    { .dataOffset = 328784, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Brush@A1_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_BRUSH__A001_E003, 11 */
    { .dataOffset = 329752, .properties = 17, .width = 18, .height = 18 },    /* icon_button_Cancel@A0_E0, 10001 */
    { .dataOffset = 330400, .properties = 17, .width = 18, .height = 18 },    /* icon_button_Cancel@A0_E1, 10001 */
    { .dataOffset = 331048, .properties = 17, .width = 18, .height = 18 },    /* icon_button_Cancel@A0_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_CANCEL__A000_E003, 11 */
    { .dataOffset = 331696, .properties = 17, .width = 18, .height = 18 },    /* icon_button_Cancel@A1_E0, 10001 */
    { .dataOffset = 332344, .properties = 17, .width = 18, .height = 18 },    /* icon_button_Cancel@A1_E1, 10001 */
    { .dataOffset = 332992, .properties = 17, .width = 18, .height = 18 },    /* icon_button_Cancel@A1_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_CANCEL__A001_E003, 11 */
    { .dataOffset = 333640, .properties = 17, .width = 26, .height = 21 },    /* icon_button_Checkmark_large@A0_E0, 10001 */
    { .dataOffset = 334732, .properties = 17, .width = 26, .height = 21 },    /* icon_button_Checkmark_large@A0_E1, 10001 */
    { .dataOffset = 335824, .properties = 17, .width = 26, .height = 21 },    /* icon_button_Checkmark_large@A0_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_CHECKMARK_LARGE__A000_E003, 11 */
    { .dataOffset = 336916, .properties = 17, .width = 26, .height = 21 },    /* icon_button_Checkmark_large@A1_E0, 10001 */
    { .dataOffset = 338008, .properties = 17, .width = 26, .height = 21 },    /* icon_button_Checkmark_large@A1_E1, 10001 */
    { .dataOffset = 339100, .properties = 17, .width = 26, .height = 21 },    /* icon_button_Checkmark_large@A1_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_CHECKMARK_LARGE__A001_E003, 11 */
    { .dataOffset = 340192, .properties = 17, .width = 20, .height = 20 },    /* icon_button_Clock@A0_E0, 10001 */
    { .dataOffset = 340992, .properties = 17, .width = 20, .height = 20 },    /* icon_button_Clock@A0_E1, 10001 */
    { .dataOffset = 341792, .properties = 17, .width = 20, .height = 20 },    /* icon_button_Clock@A0_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_CLOCK__A000_E003, 11 */
    { .dataOffset = 342592, .properties = 17, .width = 20, .height = 20 },    /* icon_button_Clock@A1_E0, 10001 */
    { .dataOffset = 343392, .properties = 17, .width = 20, .height = 20 },    /* icon_button_Clock@A1_E1, 10001 */
    { .dataOffset = 344192, .properties = 17, .width = 20, .height = 20 },    /* icon_button_Clock@A1_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_CLOCK__A001_E003, 11 */
    { .dataOffset = 344992, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Focus@A0_E0, 10001 */
    { .dataOffset = 345960, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Focus@A0_E1, 10001 */
    { .dataOffset = 346928, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Focus@A0_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_FOCUS__A000_E003, 11 */
    { .dataOffset = 347896, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Focus@A1_E0, 10001 */
    { .dataOffset = 348864, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Focus@A1_E1, 10001 */
    { .dataOffset = 349832, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Focus@A1_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_FOCUS__A001_E003, 11 */
    { .dataOffset = 350800, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Gear@A0_E0, 10001 */
    { .dataOffset = 351768, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Gear@A0_E1, 10001 */
    { .dataOffset = 352736, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Gear@A0_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_GEAR__A000_E003, 11 */
    { .dataOffset = 353704, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Gear@A1_E0, 10001 */
    { .dataOffset = 354672, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Gear@A1_E1, 10001 */
    { .dataOffset = 355640, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Gear@A1_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_GEAR__A001_E003, 11 */
    { .dataOffset = 356608, .properties = 17, .width = 20, .height = 20 },    /* icon_button_Global@A0_E0, 10001 */
    { .dataOffset = 357408, .properties = 17, .width = 20, .height = 20 },    /* icon_button_Global@A0_E1, 10001 */
    { .dataOffset = 358208, .properties = 17, .width = 20, .height = 20 },    /* icon_button_Global@A0_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_GLOBAL__A000_E003, 11 */
    { .dataOffset = 359008, .properties = 17, .width = 20, .height = 20 },    /* icon_button_Global@A1_E0, 10001 */
    { .dataOffset = 359808, .properties = 17, .width = 20, .height = 20 },    /* icon_button_Global@A1_E1, 10001 */
    { .dataOffset = 360608, .properties = 17, .width = 20, .height = 20 },    /* icon_button_Global@A1_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_GLOBAL__A001_E003, 11 */
    { .dataOffset = 361408, .properties = 17, .width = 21, .height = 21 },    /* icon_button_Info@A0_E0, 10001 */
    { .dataOffset = 362290, .properties = 17, .width = 21, .height = 21 },    /* icon_button_Info@A0_E1, 10001 */
    { .dataOffset = 363172, .properties = 17, .width = 21, .height = 21 },    /* icon_button_Info@A0_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_INFO__A000_E003, 11 */
    { .dataOffset = 364054, .properties = 17, .width = 21, .height = 21 },    /* icon_button_Info@A1_E0, 10001 */
    { .dataOffset = 364936, .properties = 17, .width = 21, .height = 21 },    /* icon_button_Info@A1_E1, 10001 */
    { .dataOffset = 365818, .properties = 17, .width = 21, .height = 21 },    /* icon_button_Info@A1_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_INFO__A001_E003, 11 */
    { .dataOffset = 366700, .properties = 17, .width = 23, .height = 16 },    /* icon_button_Keyboard@A0_E0, 10001 */
    { .dataOffset = 367436, .properties = 17, .width = 23, .height = 16 },    /* icon_button_Keyboard@A0_E1, 10001 */
    { .dataOffset = 368172, .properties = 17, .width = 23, .height = 16 },    /* icon_button_Keyboard@A0_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_KEYBOARD__A000_E003, 11 */
    { .dataOffset = 368908, .properties = 17, .width = 23, .height = 16 },    /* icon_button_Keyboard@A1_E0, 10001 */
    { .dataOffset = 369644, .properties = 17, .width = 23, .height = 16 },    /* icon_button_Keyboard@A1_E1, 10001 */
    { .dataOffset = 370380, .properties = 17, .width = 23, .height = 16 },    /* icon_button_Keyboard@A1_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_KEYBOARD__A001_E003, 11 */
    { .dataOffset = 371116, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Palette@A0_E0, 10001 */
    { .dataOffset = 372084, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Palette@A0_E1, 10001 */
    { .dataOffset = 373052, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Palette@A0_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_PALETTE__A000_E003, 11 */
    { .dataOffset = 374020, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Palette@A1_E0, 10001 */
    { .dataOffset = 374988, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Palette@A1_E1, 10001 */
    { .dataOffset = 375956, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Palette@A1_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_PALETTE__A001_E003, 11 */
    { .dataOffset = 376924, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Sliders@A0_E0, 10001 */
    { .dataOffset = 377892, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Sliders@A0_E1, 10001 */
    { .dataOffset = 378860, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Sliders@A0_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_SLIDERS__A000_E003, 11 */
    { .dataOffset = 379828, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Sliders@A1_E0, 10001 */
    { .dataOffset = 380796, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Sliders@A1_E1, 10001 */
    { .dataOffset = 381764, .properties = 17, .width = 22, .height = 22 },    /* icon_button_Sliders@A1_E2, 10001 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BUTTON_SLIDERS__A001_E003, 11 */
    { .dataOffset = 382732, .properties = 1, .width = 16, .height = 18 },    /* icon_header_Bell@A0, 1 */
    { .dataOffset = 383308, .properties = 1, .width = 16, .height = 18 },    /* icon_header_Bell@A1, 1 */
    { .dataOffset = 383884, .properties = 1, .width = 20, .height = 20 },    /* icon_header_Clock@A0, 1 */
    { .dataOffset = 384684, .properties = 1, .width = 20, .height = 20 },    /* icon_header_Clock@A1, 1 */
    { .dataOffset = 385484, .properties = 1, .width = 25, .height = 18 },    /* icon_header_Wifi@A0, 1 */
    { .dataOffset = 386384, .properties = 1, .width = 25, .height = 18 },    /* icon_header_Wifi@A1, 1 */
    { .dataOffset = 387284, .properties = 1, .width = 13, .height = 4 },    /* icon_pane_Arrow_down@A0, 1 */
    { .dataOffset = 387388, .properties = 1, .width = 13, .height = 4 },    /* icon_pane_Arrow_down@A1, 1 */
    { .dataOffset = 387492, .properties = 1, .width = 12, .height = 4 },    /* icon_pane_Arrow_up@A0, 1 */
    { .dataOffset = 387588, .properties = 1, .width = 12, .height = 4 },    /* icon_pane_Arrow_up@A1, 1 */
    { .dataOffset = 387684, .properties = 1, .width = 16, .height = 13 },    /* icon_pane_Checkmark@A0, 1 */
    { .dataOffset = 388100, .properties = 1, .width = 16, .height = 13 },    /* icon_pane_Checkmark@A1, 1 */
    { .dataOffset = 388516, .properties = 1, .width = 16, .height = 4 },    /* icon_pane_minus@A0, 1 */
    { .dataOffset = 388644, .properties = 1, .width = 16, .height = 4 },    /* icon_pane_minus@A1, 1 */
    { .dataOffset = 388772, .properties = 1, .width = 16, .height = 16 },    /* icon_pane_plus@A0, 1 */
    { .dataOffset = 389284, .properties = 1, .width = 16, .height = 16 },    /* icon_pane_plus@A1, 1 */
    { .dataOffset = 389796, .properties = 17, .width = 18, .height = 18 },    /* icon_pane_Radio-Button-Checked@A0_E0, 10001 */
    { .dataOffset = 390444, .properties = 17, .width = 18, .height = 18 },    /* icon_pane_Radio-Button-Checked@A0_E1, 10001 */
    { .dataOffset = 391092, .properties = 17, .width = 18, .height = 18 },    /* icon_pane_Radio-Button-Checked@A0_E2, 10001 */
    { .dataOffset = 391740, .properties = 17, .width = 18, .height = 18 },    /* icon_pane_Radio-Button-Checked@A0_E3, 10001 */
    { .dataOffset = 392388, .properties = 17, .width = 18, .height = 18 },    /* icon_pane_Radio-Button-Checked@A1_E0, 10001 */
    { .dataOffset = 393036, .properties = 17, .width = 18, .height = 18 },    /* icon_pane_Radio-Button-Checked@A1_E1, 10001 */
    { .dataOffset = 393684, .properties = 17, .width = 18, .height = 18 },    /* icon_pane_Radio-Button-Checked@A1_E2, 10001 */
    { .dataOffset = 394332, .properties = 17, .width = 18, .height = 18 },    /* icon_pane_Radio-Button-Checked@A1_E3, 10001 */
    { .dataOffset = 394980, .properties = 17, .width = 18, .height = 18 },    /* icon_pane_Radio-Button-UnChecked@A0_E0, 10001 */
    { .dataOffset = 395628, .properties = 17, .width = 18, .height = 18 },    /* icon_pane_Radio-Button-UnChecked@A0_E1, 10001 */
    { .dataOffset = 396276, .properties = 17, .width = 18, .height = 18 },    /* icon_pane_Radio-Button-UnChecked@A0_E2, 10001 */
    { .dataOffset = 396924, .properties = 17, .width = 18, .height = 18 },    /* icon_pane_Radio-Button-UnChecked@A0_E3, 10001 */
    { .dataOffset = 397572, .properties = 17, .width = 18, .height = 18 },    /* icon_pane_Radio-Button-UnChecked@A1_E0, 10001 */
    { .dataOffset = 398220, .properties = 17, .width = 18, .height = 18 },    /* icon_pane_Radio-Button-UnChecked@A1_E1, 10001 */
    { .dataOffset = 398868, .properties = 17, .width = 18, .height = 18 },    /* icon_pane_Radio-Button-UnChecked@A1_E2, 10001 */
    { .dataOffset = 399516, .properties = 17, .width = 18, .height = 18 },    /* icon_pane_Radio-Button-UnChecked@A1_E3, 10001 */
    { .dataOffset = 400164, .properties = 0, .width = 128, .height = 128 },    /* IRL_Logo 128, 0 */
    { .dataOffset = 432932, .properties = 0, .width = 48, .height = 48 },    /* IRL_Logo_48, 0 */
    { .dataOffset = 437540, .properties = 1, .width = 480, .height = 236 },    /* Keyboard_lc@A0, 1 */
    { .dataOffset = 664100, .properties = 1, .width = 480, .height = 236 },    /* Keyboard_lc@A1, 1 */
    { .dataOffset = 890660, .properties = 1, .width = 480, .height = 236 },    /* Keyboard_num@A0, 1 */
    { .dataOffset = 1117220, .properties = 1, .width = 480, .height = 236 },    /* Keyboard_num@A1, 1 */
    { .dataOffset = 1343780, .properties = 1, .width = 480, .height = 84 },    /* Keyboard_textbox@A0, 1 */
    { .dataOffset = 1424420, .properties = 1, .width = 480, .height = 84 },    /* Keyboard_textbox@A1, 1 */
    { .dataOffset = 1505060, .properties = 1, .width = 480, .height = 236 },    /* Keyboard_uc@A0, 1 */
    { .dataOffset = 1731620, .properties = 1, .width = 480, .height = 236 },    /* Keyboard_uc@A1, 1 */
    { .dataOffset = 1958180, .properties = 5, .width = 92, .height = 21 },    /* text_accent_color@C0_A0, 101 */
    { .dataOffset = 1962044, .properties = 5, .width = 91, .height = 21 },    /* text_accent_color@C1_A0, 101 */
    { .dataOffset = 1965866, .properties = 5, .width = 131, .height = 21 },    /* text_accent_color@C2_A0, 101 */
    { .dataOffset = 1971368, .properties = 5, .width = 167, .height = 21 },    /* text_accent_color@C3_A0, 101 */
    { .dataOffset = 1978382, .properties = 5, .width = 115, .height = 21 },    /* text_accent_color@C4_A0, 101 */
    { .dataOffset = 1983212, .properties = 5, .width = 122, .height = 21 },    /* text_accent_color@C5_A0, 101 */
    { .dataOffset = 1988336, .properties = 5, .width = 127, .height = 21 },    /* text_accent_color@C6_A0, 101 */
    { .dataOffset = 1993670, .properties = 5, .width = 50, .height = 21 },    /* text_accent_color@C7_A0, 101 */
    { .dataOffset = 1995770, .properties = 5, .width = 106, .height = 21 },    /* text_accent_color@C8_A0, 101 */
    { .dataOffset = 2000222, .properties = 5, .width = 68, .height = 21 },    /* text_accent_color@C9_A0, 101 */
    { .dataOffset = 2003078, .properties = 5, .width = 92, .height = 21 },    /* text_accent_color@C0_A1, 101 */
    { .dataOffset = 2006942, .properties = 5, .width = 91, .height = 21 },    /* text_accent_color@C1_A1, 101 */
    { .dataOffset = 2010764, .properties = 5, .width = 131, .height = 21 },    /* text_accent_color@C2_A1, 101 */
    { .dataOffset = 2016266, .properties = 5, .width = 167, .height = 21 },    /* text_accent_color@C3_A1, 101 */
    { .dataOffset = 2023280, .properties = 5, .width = 115, .height = 21 },    /* text_accent_color@C4_A1, 101 */
    { .dataOffset = 2028110, .properties = 5, .width = 122, .height = 21 },    /* text_accent_color@C5_A1, 101 */
    { .dataOffset = 2033234, .properties = 5, .width = 127, .height = 21 },    /* text_accent_color@C6_A1, 101 */
    { .dataOffset = 2038568, .properties = 5, .width = 50, .height = 21 },    /* text_accent_color@C7_A1, 101 */
    { .dataOffset = 2040668, .properties = 5, .width = 106, .height = 21 },    /* text_accent_color@C8_A1, 101 */
    { .dataOffset = 2045120, .properties = 5, .width = 68, .height = 21 },    /* text_accent_color@C9_A1, 101 */
    { .dataOffset = 2047976, .properties = 5, .width = 55, .height = 21 },    /* text_alarm@C0_A0, 101 */
    { .dataOffset = 2050286, .properties = 5, .width = 55, .height = 21 },    /* text_alarm@C1_A0, 101 */
    { .dataOffset = 2052596, .properties = 5, .width = 55, .height = 21 },    /* text_alarm@C2_A0, 101 */
    { .dataOffset = 2054906, .properties = 5, .width = 64, .height = 21 },    /* text_alarm@C3_A0, 101 */
    { .dataOffset = 2057594, .properties = 5, .width = 64, .height = 21 },    /* text_alarm@C4_A0, 101 */
    { .dataOffset = 2060282, .properties = 5, .width = 68, .height = 21 },    /* text_alarm@C5_A0, 101 */
    { .dataOffset = 2063138, .properties = 5, .width = 74, .height = 21 },    /* text_alarm@C6_A0, 101 */
    { .dataOffset = 2066246, .properties = 5, .width = 48, .height = 21 },    /* text_alarm@C7_A0, 101 */
    { .dataOffset = 2068262, .properties = 5, .width = 47, .height = 21 },    /* text_alarm@C8_A0, 101 */
    { .dataOffset = 2070236, .properties = 5, .width = 60, .height = 21 },    /* text_alarm@C9_A0, 101 */
    { .dataOffset = 2072756, .properties = 5, .width = 55, .height = 21 },    /* text_alarm@C0_A1, 101 */
    { .dataOffset = 2075066, .properties = 5, .width = 55, .height = 21 },    /* text_alarm@C1_A1, 101 */
    { .dataOffset = 2077376, .properties = 5, .width = 55, .height = 21 },    /* text_alarm@C2_A1, 101 */
    { .dataOffset = 2079686, .properties = 5, .width = 64, .height = 21 },    /* text_alarm@C3_A1, 101 */
    { .dataOffset = 2082374, .properties = 5, .width = 64, .height = 21 },    /* text_alarm@C4_A1, 101 */
    { .dataOffset = 2085062, .properties = 5, .width = 68, .height = 21 },    /* text_alarm@C5_A1, 101 */
    { .dataOffset = 2087918, .properties = 5, .width = 74, .height = 21 },    /* text_alarm@C6_A1, 101 */
    { .dataOffset = 2091026, .properties = 5, .width = 48, .height = 21 },    /* text_alarm@C7_A1, 101 */
    { .dataOffset = 2093042, .properties = 5, .width = 47, .height = 21 },    /* text_alarm@C8_A1, 101 */
    { .dataOffset = 2095016, .properties = 5, .width = 60, .height = 21 },    /* text_alarm@C9_A1, 101 */
    { .dataOffset = 2097536, .properties = 5, .width = 76, .height = 21 },    /* text_brightness@C0_A0, 101 */
    { .dataOffset = 2100728, .properties = 5, .width = 77, .height = 21 },    /* text_brightness@C1_A0, 101 */
    { .dataOffset = 2103962, .properties = 5, .width = 67, .height = 21 },    /* text_brightness@C2_A0, 101 */
    { .dataOffset = 2106776, .properties = 5, .width = 80, .height = 21 },    /* text_brightness@C3_A0, 101 */
    { .dataOffset = 2110136, .properties = 5, .width = 35, .height = 21 },    /* text_brightness@C4_A0, 101 */
    { .dataOffset = 2111606, .properties = 5, .width = 80, .height = 21 },    /* text_brightness@C5_A0, 101 */
    { .dataOffset = 2114966, .properties = 5, .width = 63, .height = 21 },    /* text_brightness@C6_A0, 101 */
    { .dataOffset = 2117612, .properties = 5, .width = 34, .height = 21 },    /* text_brightness@C7_A0, 101 */
    { .dataOffset = 2119040, .properties = 5, .width = 41, .height = 21 },    /* text_brightness@C8_A0, 101 */
    { .dataOffset = 2120762, .properties = 5, .width = 29, .height = 21 },    /* text_brightness@C9_A0, 101 */
    { .dataOffset = 2121980, .properties = 5, .width = 76, .height = 21 },    /* text_brightness@C0_A1, 101 */
    { .dataOffset = 2125172, .properties = 5, .width = 77, .height = 21 },    /* text_brightness@C1_A1, 101 */
    { .dataOffset = 2128406, .properties = 5, .width = 67, .height = 21 },    /* text_brightness@C2_A1, 101 */
    { .dataOffset = 2131220, .properties = 5, .width = 80, .height = 21 },    /* text_brightness@C3_A1, 101 */
    { .dataOffset = 2134580, .properties = 5, .width = 35, .height = 21 },    /* text_brightness@C4_A1, 101 */
    { .dataOffset = 2136050, .properties = 5, .width = 80, .height = 21 },    /* text_brightness@C5_A1, 101 */
    { .dataOffset = 2139410, .properties = 5, .width = 63, .height = 21 },    /* text_brightness@C6_A1, 101 */
    { .dataOffset = 2142056, .properties = 5, .width = 34, .height = 21 },    /* text_brightness@C7_A1, 101 */
    { .dataOffset = 2143484, .properties = 5, .width = 41, .height = 21 },    /* text_brightness@C8_A1, 101 */
    { .dataOffset = 2145206, .properties = 5, .width = 29, .height = 21 },    /* text_brightness@C9_A1, 101 */
    { .dataOffset = 2146424, .properties = 5, .width = 47, .height = 21 },    /* text_colors@C0_A0, 101 */
    { .dataOffset = 2148398, .properties = 5, .width = 53, .height = 21 },    /* text_colors@C1_A0, 101 */
    { .dataOffset = 2150624, .properties = 5, .width = 48, .height = 21 },    /* text_colors@C2_A0, 101 */
    { .dataOffset = 2152640, .properties = 5, .width = 64, .height = 21 },    /* text_colors@C3_A0, 101 */
    { .dataOffset = 2155328, .properties = 5, .width = 55, .height = 21 },    /* text_colors@C4_A0, 101 */
    { .dataOffset = 2157638, .properties = 5, .width = 42, .height = 21 },    /* text_colors@C5_A0, 101 */
    { .dataOffset = 2159402, .properties = 5, .width = 48, .height = 21 },    /* text_colors@C6_A0, 101 */
    { .dataOffset = 2161418, .properties = 5, .width = 35, .height = 21 },    /* text_colors@C7_A0, 101 */
    { .dataOffset = 2162888, .properties = 5, .width = 17, .height = 21 },    /* text_colors@C8_A0, 101 */
    { .dataOffset = 2163602, .properties = 5, .width = 32, .height = 21 },    /* text_colors@C9_A0, 101 */
    { .dataOffset = 2164946, .properties = 5, .width = 47, .height = 21 },    /* text_colors@C0_A1, 101 */
    { .dataOffset = 2166920, .properties = 5, .width = 53, .height = 21 },    /* text_colors@C1_A1, 101 */
    { .dataOffset = 2169146, .properties = 5, .width = 48, .height = 21 },    /* text_colors@C2_A1, 101 */
    { .dataOffset = 2171162, .properties = 5, .width = 64, .height = 21 },    /* text_colors@C3_A1, 101 */
    { .dataOffset = 2173850, .properties = 5, .width = 55, .height = 21 },    /* text_colors@C4_A1, 101 */
    { .dataOffset = 2176160, .properties = 5, .width = 42, .height = 21 },    /* text_colors@C5_A1, 101 */
    { .dataOffset = 2177924, .properties = 5, .width = 48, .height = 21 },    /* text_colors@C6_A1, 101 */
    { .dataOffset = 2179940, .properties = 5, .width = 35, .height = 21 },    /* text_colors@C7_A1, 101 */
    { .dataOffset = 2181410, .properties = 5, .width = 17, .height = 21 },    /* text_colors@C8_A1, 101 */
    { .dataOffset = 2182124, .properties = 5, .width = 32, .height = 21 },    /* text_colors@C9_A1, 101 */
    { .dataOffset = 2183468, .properties = 5, .width = 32, .height = 21 },    /* text_date@C0_A0, 101 */
    { .dataOffset = 2184812, .properties = 5, .width = 46, .height = 21 },    /* text_date@C1_A0, 101 */
    { .dataOffset = 2186744, .properties = 5, .width = 46, .height = 21 },    /* text_date@C2_A0, 101 */
    { .dataOffset = 2188676, .properties = 5, .width = 32, .height = 21 },    /* text_date@C3_A0, 101 */
    { .dataOffset = 2190020, .properties = 5, .width = 42, .height = 21 },    /* text_date@C4_A0, 101 */
    { .dataOffset = 2191784, .properties = 5, .width = 52, .height = 21 },    /* text_date@C5_A0, 101 */
    { .dataOffset = 2193968, .properties = 5, .width = 37, .height = 21 },    /* text_date@C6_A0, 101 */
    { .dataOffset = 2195522, .properties = 5, .width = 31, .height = 21 },    /* text_date@C7_A0, 101 */
    { .dataOffset = 2196824, .properties = 5, .width = 32, .height = 21 },    /* text_date@C8_A0, 101 */
    { .dataOffset = 2198168, .properties = 5, .width = 30, .height = 21 },    /* text_date@C9_A0, 101 */
    { .dataOffset = 2199428, .properties = 5, .width = 32, .height = 21 },    /* text_date@C0_A1, 101 */
    { .dataOffset = 2200772, .properties = 5, .width = 46, .height = 21 },    /* text_date@C1_A1, 101 */
    { .dataOffset = 2202704, .properties = 5, .width = 46, .height = 21 },    /* text_date@C2_A1, 101 */
    { .dataOffset = 2204636, .properties = 5, .width = 32, .height = 21 },    /* text_date@C3_A1, 101 */
    { .dataOffset = 2205980, .properties = 5, .width = 42, .height = 21 },    /* text_date@C4_A1, 101 */
    { .dataOffset = 2207744, .properties = 5, .width = 52, .height = 21 },    /* text_date@C5_A1, 101 */
    { .dataOffset = 2209928, .properties = 5, .width = 37, .height = 21 },    /* text_date@C6_A1, 101 */
    { .dataOffset = 2211482, .properties = 5, .width = 31, .height = 21 },    /* text_date@C7_A1, 101 */
    { .dataOffset = 2212784, .properties = 5, .width = 32, .height = 21 },    /* text_date@C8_A1, 101 */
    { .dataOffset = 2214128, .properties = 5, .width = 30, .height = 21 },    /* text_date@C9_A1, 101 */
    { .dataOffset = 2215388, .properties = 1, .width = 74, .height = 29 },    /* text_footer_mcsgui@A0, 1 */
    { .dataOffset = 2219680, .properties = 1, .width = 74, .height = 29 },    /* text_footer_mcsgui@A1, 1 */
    { .dataOffset = 2223972, .properties = 5, .width = 27, .height = 21 },    /* text_info@C0_A0, 101 */
    { .dataOffset = 2225106, .properties = 5, .width = 27, .height = 21 },    /* text_info@C1_A0, 101 */
    { .dataOffset = 2226240, .properties = 5, .width = 27, .height = 21 },    /* text_info@C2_A0, 101 */
    { .dataOffset = 2227374, .properties = 5, .width = 27, .height = 21 },    /* text_info@C3_A0, 101 */
    { .dataOffset = 2228508, .properties = 5, .width = 87, .height = 21 },    /* text_info@C4_A0, 101 */
    { .dataOffset = 2232162, .properties = 5, .width = 90, .height = 21 },    /* text_info@C5_A0, 101 */
    { .dataOffset = 2235942, .properties = 5, .width = 99, .height = 21 },    /* text_info@C6_A0, 101 */
    { .dataOffset = 2240100, .properties = 5, .width = 35, .height = 21 },    /* text_info@C7_A0, 101 */
    { .dataOffset = 2241570, .properties = 5, .width = 35, .height = 21 },    /* text_info@C8_A0, 101 */
    { .dataOffset = 2243040, .properties = 5, .width = 31, .height = 21 },    /* text_info@C9_A0, 101 */
    { .dataOffset = 2244342, .properties = 5, .width = 27, .height = 21 },    /* text_info@C0_A1, 101 */
    { .dataOffset = 2245476, .properties = 5, .width = 27, .height = 21 },    /* text_info@C1_A1, 101 */
    { .dataOffset = 2246610, .properties = 5, .width = 27, .height = 21 },    /* text_info@C2_A1, 101 */
    { .dataOffset = 2247744, .properties = 5, .width = 27, .height = 21 },    /* text_info@C3_A1, 101 */
    { .dataOffset = 2248878, .properties = 5, .width = 87, .height = 21 },    /* text_info@C4_A1, 101 */
    { .dataOffset = 2252532, .properties = 5, .width = 90, .height = 21 },    /* text_info@C5_A1, 101 */
    { .dataOffset = 2256312, .properties = 5, .width = 99, .height = 21 },    /* text_info@C6_A1, 101 */
    { .dataOffset = 2260470, .properties = 5, .width = 35, .height = 21 },    /* text_info@C7_A1, 101 */
    { .dataOffset = 2261940, .properties = 5, .width = 35, .height = 21 },    /* text_info@C8_A1, 101 */
    { .dataOffset = 2263410, .properties = 5, .width = 31, .height = 21 },    /* text_info@C9_A1, 101 */
    { .dataOffset = 2264712, .properties = 5, .width = 67, .height = 21 },    /* text_keyboard@C0_A0, 101 */
    { .dataOffset = 2267526, .properties = 5, .width = 92, .height = 21 },    /* text_keyboard@C1_A0, 101 */
    { .dataOffset = 2271390, .properties = 5, .width = 61, .height = 21 },    /* text_keyboard@C2_A0, 101 */
    { .dataOffset = 2273952, .properties = 5, .width = 50, .height = 21 },    /* text_keyboard@C3_A0, 101 */
    { .dataOffset = 2276052, .properties = 5, .width = 58, .height = 21 },    /* text_keyboard@C4_A0, 101 */
    { .dataOffset = 2278488, .properties = 5, .width = 59, .height = 21 },    /* text_keyboard@C5_A0, 101 */
    { .dataOffset = 2280966, .properties = 5, .width = 89, .height = 21 },    /* text_keyboard@C6_A0, 101 */
    { .dataOffset = 2284704, .properties = 5, .width = 35, .height = 21 },    /* text_keyboard@C7_A0, 101 */
    { .dataOffset = 2286174, .properties = 5, .width = 71, .height = 21 },    /* text_keyboard@C8_A0, 101 */
    { .dataOffset = 2289156, .properties = 5, .width = 47, .height = 21 },    /* text_keyboard@C9_A0, 101 */
    { .dataOffset = 2291130, .properties = 5, .width = 67, .height = 21 },    /* text_keyboard@C0_A1, 101 */
    { .dataOffset = 2293944, .properties = 5, .width = 92, .height = 21 },    /* text_keyboard@C1_A1, 101 */
    { .dataOffset = 2297808, .properties = 5, .width = 61, .height = 21 },    /* text_keyboard@C2_A1, 101 */
    { .dataOffset = 2300370, .properties = 5, .width = 50, .height = 21 },    /* text_keyboard@C3_A1, 101 */
    { .dataOffset = 2302470, .properties = 5, .width = 58, .height = 21 },    /* text_keyboard@C4_A1, 101 */
    { .dataOffset = 2304906, .properties = 5, .width = 59, .height = 21 },    /* text_keyboard@C5_A1, 101 */
    { .dataOffset = 2307384, .properties = 5, .width = 89, .height = 21 },    /* text_keyboard@C6_A1, 101 */
    { .dataOffset = 2311122, .properties = 5, .width = 35, .height = 21 },    /* text_keyboard@C7_A1, 101 */
    { .dataOffset = 2312592, .properties = 5, .width = 71, .height = 21 },    /* text_keyboard@C8_A1, 101 */
    { .dataOffset = 2315574, .properties = 5, .width = 47, .height = 21 },    /* text_keyboard@C9_A1, 101 */
    { .dataOffset = 2317548, .properties = 5, .width = 71, .height = 21 },    /* text_language@C0_A0, 101 */
    { .dataOffset = 2320530, .properties = 5, .width = 31, .height = 21 },    /* text_language@C1_A0, 101 */
    { .dataOffset = 2321832, .properties = 5, .width = 59, .height = 21 },    /* text_language@C2_A0, 101 */
    { .dataOffset = 2324310, .properties = 5, .width = 52, .height = 21 },    /* text_language@C3_A0, 101 */
    { .dataOffset = 2326494, .properties = 5, .width = 48, .height = 21 },    /* text_language@C4_A0, 101 */
    { .dataOffset = 2328510, .properties = 5, .width = 47, .height = 21 },    /* text_language@C5_A0, 101 */
    { .dataOffset = 2330484, .properties = 5, .width = 40, .height = 21 },    /* text_language@C6_A0, 101 */
    { .dataOffset = 2332164, .properties = 5, .width = 35, .height = 21 },    /* text_language@C7_A0, 101 */
    { .dataOffset = 2333634, .properties = 5, .width = 35, .height = 21 },    /* text_language@C8_A0, 101 */
    { .dataOffset = 2335104, .properties = 5, .width = 29, .height = 21 },    /* text_language@C9_A0, 101 */
    { .dataOffset = 2336322, .properties = 5, .width = 71, .height = 21 },    /* text_language@C0_A1, 101 */
    { .dataOffset = 2339304, .properties = 5, .width = 31, .height = 21 },    /* text_language@C1_A1, 101 */
    { .dataOffset = 2340606, .properties = 5, .width = 59, .height = 21 },    /* text_language@C2_A1, 101 */
    { .dataOffset = 2343084, .properties = 5, .width = 52, .height = 21 },    /* text_language@C3_A1, 101 */
    { .dataOffset = 2345268, .properties = 5, .width = 48, .height = 21 },    /* text_language@C4_A1, 101 */
    { .dataOffset = 2347284, .properties = 5, .width = 47, .height = 21 },    /* text_language@C5_A1, 101 */
    { .dataOffset = 2349258, .properties = 5, .width = 40, .height = 21 },    /* text_language@C6_A1, 101 */
    { .dataOffset = 2350938, .properties = 5, .width = 35, .height = 21 },    /* text_language@C7_A1, 101 */
    { .dataOffset = 2352408, .properties = 5, .width = 35, .height = 21 },    /* text_language@C8_A1, 101 */
    { .dataOffset = 2353878, .properties = 5, .width = 29, .height = 21 },    /* text_language@C9_A1, 101 */
    { .dataOffset = 2355096, .properties = 5, .width = 100, .height = 21 },    /* text_measurement@C0_A0, 101 */
    { .dataOffset = 2359296, .properties = 5, .width = 57, .height = 21 },    /* text_measurement@C1_A0, 101 */
    { .dataOffset = 2361690, .properties = 5, .width = 65, .height = 21 },    /* text_measurement@C2_A0, 101 */
    { .dataOffset = 2364420, .properties = 5, .width = 53, .height = 21 },    /* text_measurement@C3_A0, 101 */
    { .dataOffset = 2366646, .properties = 5, .width = 65, .height = 21 },    /* text_measurement@C4_A0, 101 */
    { .dataOffset = 2369376, .properties = 5, .width = 88, .height = 21 },    /* text_measurement@C5_A0, 101 */
    { .dataOffset = 2373072, .properties = 5, .width = 85, .height = 21 },    /* text_measurement@C6_A0, 101 */
    { .dataOffset = 2376642, .properties = 5, .width = 35, .height = 21 },    /* text_measurement@C7_A0, 101 */
    { .dataOffset = 2378112, .properties = 5, .width = 35, .height = 21 },    /* text_measurement@C8_A0, 101 */
    { .dataOffset = 2379582, .properties = 5, .width = 32, .height = 21 },    /* text_measurement@C9_A0, 101 */
    { .dataOffset = 2380926, .properties = 5, .width = 100, .height = 21 },    /* text_measurement@C0_A1, 101 */
    { .dataOffset = 2385126, .properties = 5, .width = 57, .height = 21 },    /* text_measurement@C1_A1, 101 */
    { .dataOffset = 2387520, .properties = 5, .width = 65, .height = 21 },    /* text_measurement@C2_A1, 101 */
    { .dataOffset = 2390250, .properties = 5, .width = 53, .height = 21 },    /* text_measurement@C3_A1, 101 */
    { .dataOffset = 2392476, .properties = 5, .width = 65, .height = 21 },    /* text_measurement@C4_A1, 101 */
    { .dataOffset = 2395206, .properties = 5, .width = 88, .height = 21 },    /* text_measurement@C5_A1, 101 */
    { .dataOffset = 2398902, .properties = 5, .width = 85, .height = 21 },    /* text_measurement@C6_A1, 101 */
    { .dataOffset = 2402472, .properties = 5, .width = 35, .height = 21 },    /* text_measurement@C7_A1, 101 */
    { .dataOffset = 2403942, .properties = 5, .width = 35, .height = 21 },    /* text_measurement@C8_A1, 101 */
    { .dataOffset = 2405412, .properties = 5, .width = 32, .height = 21 },    /* text_measurement@C9_A1, 101 */
    { .dataOffset = 2406756, .properties = 5, .width = 104, .height = 23 },    /* text_pane_accent_color@C0_A0, 101 */
    { .dataOffset = 2411540, .properties = 5, .width = 102, .height = 23 },    /* text_pane_accent_color@C1_A0, 101 */
    { .dataOffset = 2416232, .properties = 5, .width = 148, .height = 23 },    /* text_pane_accent_color@C2_A0, 101 */
    { .dataOffset = 2423040, .properties = 5, .width = 187, .height = 23 },    /* text_pane_accent_color@C3_A0, 101 */
    { .dataOffset = 2431642, .properties = 5, .width = 128, .height = 23 },    /* text_pane_accent_color@C4_A0, 101 */
    { .dataOffset = 2437530, .properties = 5, .width = 137, .height = 23 },    /* text_pane_accent_color@C5_A0, 101 */
    { .dataOffset = 2443832, .properties = 5, .width = 143, .height = 23 },    /* text_pane_accent_color@C6_A0, 101 */
    { .dataOffset = 2450410, .properties = 5, .width = 57, .height = 23 },    /* text_pane_accent_color@C7_A0, 101 */
    { .dataOffset = 2453032, .properties = 5, .width = 119, .height = 23 },    /* text_pane_accent_color@C8_A0, 101 */
    { .dataOffset = 2458506, .properties = 5, .width = 77, .height = 23 },    /* text_pane_accent_color@C9_A0, 101 */
    { .dataOffset = 2462048, .properties = 5, .width = 104, .height = 23 },    /* text_pane_accent_color@C0_A1, 101 */
    { .dataOffset = 2466832, .properties = 5, .width = 102, .height = 23 },    /* text_pane_accent_color@C1_A1, 101 */
    { .dataOffset = 2471524, .properties = 5, .width = 148, .height = 23 },    /* text_pane_accent_color@C2_A1, 101 */
    { .dataOffset = 2478332, .properties = 5, .width = 187, .height = 23 },    /* text_pane_accent_color@C3_A1, 101 */
    { .dataOffset = 2486934, .properties = 5, .width = 128, .height = 23 },    /* text_pane_accent_color@C4_A1, 101 */
    { .dataOffset = 2492822, .properties = 5, .width = 137, .height = 23 },    /* text_pane_accent_color@C5_A1, 101 */
    { .dataOffset = 2499124, .properties = 5, .width = 143, .height = 23 },    /* text_pane_accent_color@C6_A1, 101 */
    { .dataOffset = 2505702, .properties = 5, .width = 57, .height = 23 },    /* text_pane_accent_color@C7_A1, 101 */
    { .dataOffset = 2508324, .properties = 5, .width = 119, .height = 23 },    /* text_pane_accent_color@C8_A1, 101 */
    { .dataOffset = 2513798, .properties = 5, .width = 77, .height = 23 },    /* text_pane_accent_color@C9_A1, 101 */
    { .dataOffset = 2517340, .properties = 5, .width = 127, .height = 23 },    /* text_pane_activate_alarm@C0_A0, 101 */
    { .dataOffset = 2523182, .properties = 5, .width = 137, .height = 23 },    /* text_pane_activate_alarm@C1_A0, 101 */
    { .dataOffset = 2529484, .properties = 5, .width = 142, .height = 23 },    /* text_pane_activate_alarm@C2_A0, 101 */
    { .dataOffset = 2536016, .properties = 5, .width = 135, .height = 23 },    /* text_pane_activate_alarm@C3_A0, 101 */
    { .dataOffset = 2542226, .properties = 5, .width = 156, .height = 23 },    /* text_pane_activate_alarm@C4_A0, 101 */
    { .dataOffset = 2549402, .properties = 5, .width = 146, .height = 23 },    /* text_pane_activate_alarm@C5_A0, 101 */
    { .dataOffset = 2556118, .properties = 5, .width = 263, .height = 23 },    /* text_pane_activate_alarm@C6_A0, 101 */
    { .dataOffset = 2568216, .properties = 5, .width = 96, .height = 23 },    /* text_pane_activate_alarm@C7_A0, 101 */
    { .dataOffset = 2572632, .properties = 5, .width = 207, .height = 23 },    /* text_pane_activate_alarm@C8_A0, 101 */
    { .dataOffset = 2582154, .properties = 5, .width = 234, .height = 23 },    /* text_pane_activate_alarm@C9_A0, 101 */
    { .dataOffset = 2592918, .properties = 5, .width = 127, .height = 23 },    /* text_pane_activate_alarm@C0_A1, 101 */
    { .dataOffset = 2598760, .properties = 5, .width = 137, .height = 23 },    /* text_pane_activate_alarm@C1_A1, 101 */
    { .dataOffset = 2605062, .properties = 5, .width = 142, .height = 23 },    /* text_pane_activate_alarm@C2_A1, 101 */
    { .dataOffset = 2611594, .properties = 5, .width = 135, .height = 23 },    /* text_pane_activate_alarm@C3_A1, 101 */
    { .dataOffset = 2617804, .properties = 5, .width = 156, .height = 23 },    /* text_pane_activate_alarm@C4_A1, 101 */
    { .dataOffset = 2624980, .properties = 5, .width = 146, .height = 23 },    /* text_pane_activate_alarm@C5_A1, 101 */
    { .dataOffset = 2631696, .properties = 5, .width = 263, .height = 23 },    /* text_pane_activate_alarm@C6_A1, 101 */
    { .dataOffset = 2643794, .properties = 5, .width = 96, .height = 23 },    /* text_pane_activate_alarm@C7_A1, 101 */
    { .dataOffset = 2648210, .properties = 5, .width = 207, .height = 23 },    /* text_pane_activate_alarm@C8_A1, 101 */
    { .dataOffset = 2657732, .properties = 5, .width = 234, .height = 23 },    /* text_pane_activate_alarm@C9_A1, 101 */
    { .dataOffset = 2668496, .properties = 1, .width = 37, .height = 23 },    /* text_pane_chinese_sim@A0, 1 */
    { .dataOffset = 2670198, .properties = 1, .width = 37, .height = 23 },    /* text_pane_chinese_sim@A1, 1 */
    { .dataOffset = 2671900, .properties = 5, .width = 100, .height = 23 },    /* text_pane_cursor_color@C0_A0, 101 */
    { .dataOffset = 2676500, .properties = 5, .width = 99, .height = 23 },    /* text_pane_cursor_color@C1_A0, 101 */
    { .dataOffset = 2681054, .properties = 5, .width = 149, .height = 23 },    /* text_pane_cursor_color@C2_A0, 101 */
    { .dataOffset = 2687908, .properties = 5, .width = 155, .height = 23 },    /* text_pane_cursor_color@C3_A0, 101 */
    { .dataOffset = 2695038, .properties = 5, .width = 129, .height = 23 },    /* text_pane_cursor_color@C4_A0, 101 */
    { .dataOffset = 2700972, .properties = 5, .width = 149, .height = 23 },    /* text_pane_cursor_color@C5_A0, 101 */
    { .dataOffset = 2707826, .properties = 5, .width = 116, .height = 23 },    /* text_pane_cursor_color@C6_A0, 101 */
    { .dataOffset = 2713162, .properties = 5, .width = 79, .height = 23 },    /* text_pane_cursor_color@C7_A0, 101 */
    { .dataOffset = 2716796, .properties = 5, .width = 98, .height = 23 },    /* text_pane_cursor_color@C8_A0, 101 */
    { .dataOffset = 2721304, .properties = 5, .width = 77, .height = 23 },    /* text_pane_cursor_color@C9_A0, 101 */
    { .dataOffset = 2724846, .properties = 5, .width = 100, .height = 23 },    /* text_pane_cursor_color@C0_A1, 101 */
    { .dataOffset = 2729446, .properties = 5, .width = 99, .height = 23 },    /* text_pane_cursor_color@C1_A1, 101 */
    { .dataOffset = 2734000, .properties = 5, .width = 149, .height = 23 },    /* text_pane_cursor_color@C2_A1, 101 */
    { .dataOffset = 2740854, .properties = 5, .width = 155, .height = 23 },    /* text_pane_cursor_color@C3_A1, 101 */
    { .dataOffset = 2747984, .properties = 5, .width = 129, .height = 23 },    /* text_pane_cursor_color@C4_A1, 101 */
    { .dataOffset = 2753918, .properties = 5, .width = 149, .height = 23 },    /* text_pane_cursor_color@C5_A1, 101 */
    { .dataOffset = 2760772, .properties = 5, .width = 116, .height = 23 },    /* text_pane_cursor_color@C6_A1, 101 */
    { .dataOffset = 2766108, .properties = 5, .width = 79, .height = 23 },    /* text_pane_cursor_color@C7_A1, 101 */
    { .dataOffset = 2769742, .properties = 5, .width = 98, .height = 23 },    /* text_pane_cursor_color@C8_A1, 101 */
    { .dataOffset = 2774250, .properties = 5, .width = 77, .height = 23 },    /* text_pane_cursor_color@C9_A1, 101 */
    { .dataOffset = 2777792, .properties = 1, .width = 17, .height = 23 },    /* text_pane_deg_cel@A0, 1 */
    { .dataOffset = 2778574, .properties = 1, .width = 17, .height = 23 },    /* text_pane_deg_cel@A1, 1 */
    { .dataOffset = 2779356, .properties = 1, .width = 16, .height = 23 },    /* text_pane_deg_far@A0, 1 */
    { .dataOffset = 2780092, .properties = 1, .width = 16, .height = 23 },    /* text_pane_deg_far@A1, 1 */
    { .dataOffset = 2780828, .properties = 1, .width = 93, .height = 23 },    /* text_pane_dutch@A0, 1 */
    { .dataOffset = 2785106, .properties = 1, .width = 93, .height = 23 },    /* text_pane_dutch@A1, 1 */
    { .dataOffset = 2789384, .properties = 1, .width = 58, .height = 23 },    /* text_pane_english@A0, 1 */
    { .dataOffset = 2792052, .properties = 1, .width = 58, .height = 23 },    /* text_pane_english@A1, 1 */
    { .dataOffset = 2794720, .properties = 1, .width = 69, .height = 23 },    /* text_pane_french@A0, 1 */
    { .dataOffset = 2797894, .properties = 1, .width = 69, .height = 23 },    /* text_pane_french@A1, 1 */
    { .dataOffset = 2801068, .properties = 1, .width = 66, .height = 23 },    /* text_pane_german@A0, 1 */
    { .dataOffset = 2804104, .properties = 1, .width = 66, .height = 23 },    /* text_pane_german@A1, 1 */
    { .dataOffset = 2807140, .properties = 5, .width = 112, .height = 23 },    /* text_pane_intern_temp@C0_A0, 101 */
    { .dataOffset = 2812292, .properties = 5, .width = 112, .height = 23 },    /* text_pane_intern_temp@C1_A0, 101 */
    { .dataOffset = 2817444, .properties = 5, .width = 161, .height = 23 },    /* text_pane_intern_temp@C2_A0, 101 */
    { .dataOffset = 2824850, .properties = 5, .width = 171, .height = 23 },    /* text_pane_intern_temp@C3_A0, 101 */
    { .dataOffset = 2832716, .properties = 5, .width = 172, .height = 23 },    /* text_pane_intern_temp@C4_A0, 101 */
    { .dataOffset = 2840628, .properties = 5, .width = 172, .height = 23 },    /* text_pane_intern_temp@C5_A0, 101 */
    { .dataOffset = 2848540, .properties = 5, .width = 221, .height = 23 },    /* text_pane_intern_temp@C6_A0, 101 */
    { .dataOffset = 2858706, .properties = 5, .width = 86, .height = 23 },    /* text_pane_intern_temp@C7_A0, 101 */
    { .dataOffset = 2862662, .properties = 5, .width = 83, .height = 23 },    /* text_pane_intern_temp@C8_A0, 101 */
    { .dataOffset = 2866480, .properties = 5, .width = 80, .height = 23 },    /* text_pane_intern_temp@C9_A0, 101 */
    { .dataOffset = 2870160, .properties = 5, .width = 112, .height = 23 },    /* text_pane_intern_temp@C0_A1, 101 */
    { .dataOffset = 2875312, .properties = 5, .width = 112, .height = 23 },    /* text_pane_intern_temp@C1_A1, 101 */
    { .dataOffset = 2880464, .properties = 5, .width = 161, .height = 23 },    /* text_pane_intern_temp@C2_A1, 101 */
    { .dataOffset = 2887870, .properties = 5, .width = 171, .height = 23 },    /* text_pane_intern_temp@C3_A1, 101 */
    { .dataOffset = 2895736, .properties = 5, .width = 172, .height = 23 },    /* text_pane_intern_temp@C4_A1, 101 */
    { .dataOffset = 2903648, .properties = 5, .width = 172, .height = 23 },    /* text_pane_intern_temp@C5_A1, 101 */
    { .dataOffset = 2911560, .properties = 5, .width = 221, .height = 23 },    /* text_pane_intern_temp@C6_A1, 101 */
    { .dataOffset = 2921726, .properties = 5, .width = 86, .height = 23 },    /* text_pane_intern_temp@C7_A1, 101 */
    { .dataOffset = 2925682, .properties = 5, .width = 83, .height = 23 },    /* text_pane_intern_temp@C8_A1, 101 */
    { .dataOffset = 2929500, .properties = 5, .width = 80, .height = 23 },    /* text_pane_intern_temp@C9_A1, 101 */
    { .dataOffset = 2933180, .properties = 1, .width = 59, .height = 23 },    /* text_pane_italian@A0, 1 */
    { .dataOffset = 2935894, .properties = 1, .width = 59, .height = 23 },    /* text_pane_italian@A1, 1 */
    { .dataOffset = 2938608, .properties = 1, .width = 57, .height = 23 },    /* text_pane_japanese@A0, 1 */
    { .dataOffset = 2941230, .properties = 1, .width = 57, .height = 23 },    /* text_pane_japanese@A1, 1 */
    { .dataOffset = 2943852, .properties = 1, .width = 51, .height = 23 },    /* text_pane_korean@A0, 1 */
    { .dataOffset = 2946198, .properties = 1, .width = 51, .height = 23 },    /* text_pane_korean@A1, 1 */
    { .dataOffset = 2948544, .properties = 1, .width = 69, .height = 23 },    /* text_pane_russian@A0, 1 */
    { .dataOffset = 2951718, .properties = 1, .width = 69, .height = 23 },    /* text_pane_russian@A1, 1 */
    { .dataOffset = 2954892, .properties = 5, .width = 102, .height = 23 },    /* text_pane_set_alarm_in@C0_A0, 101 */
    { .dataOffset = 2959584, .properties = 5, .width = 72, .height = 23 },    /* text_pane_set_alarm_in@C1_A0, 101 */
    { .dataOffset = 2962896, .properties = 5, .width = 112, .height = 23 },    /* text_pane_set_alarm_in@C2_A0, 101 */
    { .dataOffset = 2968048, .properties = 5, .width = 156, .height = 23 },    /* text_pane_set_alarm_in@C3_A0, 101 */
    { .dataOffset = 2975224, .properties = 5, .width = 176, .height = 23 },    /* text_pane_set_alarm_in@C4_A0, 101 */
    { .dataOffset = 2983320, .properties = 5, .width = 172, .height = 23 },    /* text_pane_set_alarm_in@C5_A0, 101 */
    { .dataOffset = 2991232, .properties = 5, .width = 218, .height = 23 },    /* text_pane_set_alarm_in@C6_A0, 101 */
    { .dataOffset = 3001260, .properties = 5, .width = 190, .height = 23 },    /* text_pane_set_alarm_in@C7_A0, 101 */
    { .dataOffset = 3010000, .properties = 5, .width = 123, .height = 23 },    /* text_pane_set_alarm_in@C8_A0, 101 */
    { .dataOffset = 3015658, .properties = 5, .width = 81, .height = 23 },    /* text_pane_set_alarm_in@C9_A0, 101 */
    { .dataOffset = 3019384, .properties = 5, .width = 102, .height = 23 },    /* text_pane_set_alarm_in@C0_A1, 101 */
    { .dataOffset = 3024076, .properties = 5, .width = 72, .height = 23 },    /* text_pane_set_alarm_in@C1_A1, 101 */
    { .dataOffset = 3027388, .properties = 5, .width = 112, .height = 23 },    /* text_pane_set_alarm_in@C2_A1, 101 */
    { .dataOffset = 3032540, .properties = 5, .width = 156, .height = 23 },    /* text_pane_set_alarm_in@C3_A1, 101 */
    { .dataOffset = 3039716, .properties = 5, .width = 176, .height = 23 },    /* text_pane_set_alarm_in@C4_A1, 101 */
    { .dataOffset = 3047812, .properties = 5, .width = 172, .height = 23 },    /* text_pane_set_alarm_in@C5_A1, 101 */
    { .dataOffset = 3055724, .properties = 5, .width = 218, .height = 23 },    /* text_pane_set_alarm_in@C6_A1, 101 */
    { .dataOffset = 3065752, .properties = 5, .width = 190, .height = 23 },    /* text_pane_set_alarm_in@C7_A1, 101 */
    { .dataOffset = 3074492, .properties = 5, .width = 123, .height = 23 },    /* text_pane_set_alarm_in@C8_A1, 101 */
    { .dataOffset = 3080150, .properties = 5, .width = 81, .height = 23 },    /* text_pane_set_alarm_in@C9_A1, 101 */
    { .dataOffset = 3083876, .properties = 1, .width = 64, .height = 23 },    /* text_pane_spanish@A0, 1 */
    { .dataOffset = 3086820, .properties = 1, .width = 64, .height = 23 },    /* text_pane_spanish@A1, 1 */
    { .dataOffset = 3089764, .properties = 5, .width = 37, .height = 23 },    /* text_pane_theme_dark@C0_A0, 101 */
    { .dataOffset = 3091466, .properties = 5, .width = 57, .height = 23 },    /* text_pane_theme_dark@C1_A0, 101 */
    { .dataOffset = 3094088, .properties = 5, .width = 54, .height = 23 },    /* text_pane_theme_dark@C2_A0, 101 */
    { .dataOffset = 3096572, .properties = 5, .width = 64, .height = 23 },    /* text_pane_theme_dark@C3_A0, 101 */
    { .dataOffset = 3099516, .properties = 5, .width = 57, .height = 23 },    /* text_pane_theme_dark@C4_A0, 101 */
    { .dataOffset = 3102138, .properties = 5, .width = 57, .height = 23 },    /* text_pane_theme_dark@C5_A0, 101 */
    { .dataOffset = 3104760, .properties = 5, .width = 69, .height = 23 },    /* text_pane_theme_dark@C6_A0, 101 */
    { .dataOffset = 3107934, .properties = 5, .width = 39, .height = 23 },    /* text_pane_theme_dark@C7_A0, 101 */
    { .dataOffset = 3109728, .properties = 5, .width = 36, .height = 23 },    /* text_pane_theme_dark@C8_A0, 101 */
    { .dataOffset = 3111384, .properties = 5, .width = 34, .height = 23 },    /* text_pane_theme_dark@C9_A0, 101 */
    { .dataOffset = 3112948, .properties = 5, .width = 37, .height = 23 },    /* text_pane_theme_dark@C0_A1, 101 */
    { .dataOffset = 3114650, .properties = 5, .width = 57, .height = 23 },    /* text_pane_theme_dark@C1_A1, 101 */
    { .dataOffset = 3117272, .properties = 5, .width = 54, .height = 23 },    /* text_pane_theme_dark@C2_A1, 101 */
    { .dataOffset = 3119756, .properties = 5, .width = 64, .height = 23 },    /* text_pane_theme_dark@C3_A1, 101 */
    { .dataOffset = 3122700, .properties = 5, .width = 57, .height = 23 },    /* text_pane_theme_dark@C4_A1, 101 */
    { .dataOffset = 3125322, .properties = 5, .width = 57, .height = 23 },    /* text_pane_theme_dark@C5_A1, 101 */
    { .dataOffset = 3127944, .properties = 5, .width = 69, .height = 23 },    /* text_pane_theme_dark@C6_A1, 101 */
    { .dataOffset = 3131118, .properties = 5, .width = 39, .height = 23 },    /* text_pane_theme_dark@C7_A1, 101 */
    { .dataOffset = 3132912, .properties = 5, .width = 36, .height = 23 },    /* text_pane_theme_dark@C8_A1, 101 */
    { .dataOffset = 3134568, .properties = 5, .width = 34, .height = 23 },    /* text_pane_theme_dark@C9_A1, 101 */
    { .dataOffset = 3136132, .properties = 5, .width = 40, .height = 23 },    /* text_pane_theme_light@C0_A0, 101 */
    { .dataOffset = 3137972, .properties = 5, .width = 39, .height = 23 },    /* text_pane_theme_light@C1_A0, 101 */
    { .dataOffset = 3139766, .properties = 5, .width = 39, .height = 23 },    /* text_pane_theme_light@C2_A0, 101 */
    { .dataOffset = 3141560, .properties = 5, .width = 65, .height = 23 },    /* text_pane_theme_light@C3_A0, 101 */
    { .dataOffset = 3144550, .properties = 5, .width = 28, .height = 23 },    /* text_pane_theme_light@C4_A0, 101 */
    { .dataOffset = 3145838, .properties = 5, .width = 66, .height = 23 },    /* text_pane_theme_light@C5_A0, 101 */
    { .dataOffset = 3148874, .properties = 5, .width = 40, .height = 23 },    /* text_pane_theme_light@C6_A0, 101 */
    { .dataOffset = 3150714, .properties = 5, .width = 18, .height = 23 },    /* text_pane_theme_light@C7_A0, 101 */
    { .dataOffset = 3151542, .properties = 5, .width = 18, .height = 23 },    /* text_pane_theme_light@C8_A0, 101 */
    { .dataOffset = 3152370, .properties = 5, .width = 17, .height = 23 },    /* text_pane_theme_light@C9_A0, 101 */
    { .dataOffset = 3153152, .properties = 5, .width = 40, .height = 23 },    /* text_pane_theme_light@C0_A1, 101 */
    { .dataOffset = 3154992, .properties = 5, .width = 39, .height = 23 },    /* text_pane_theme_light@C1_A1, 101 */
    { .dataOffset = 3156786, .properties = 5, .width = 39, .height = 23 },    /* text_pane_theme_light@C2_A1, 101 */
    { .dataOffset = 3158580, .properties = 5, .width = 65, .height = 23 },    /* text_pane_theme_light@C3_A1, 101 */
    { .dataOffset = 3161570, .properties = 5, .width = 28, .height = 23 },    /* text_pane_theme_light@C4_A1, 101 */
    { .dataOffset = 3162858, .properties = 5, .width = 66, .height = 23 },    /* text_pane_theme_light@C5_A1, 101 */
    { .dataOffset = 3165894, .properties = 5, .width = 40, .height = 23 },    /* text_pane_theme_light@C6_A1, 101 */
    { .dataOffset = 3167734, .properties = 5, .width = 18, .height = 23 },    /* text_pane_theme_light@C7_A1, 101 */
    { .dataOffset = 3168562, .properties = 5, .width = 18, .height = 23 },    /* text_pane_theme_light@C8_A1, 101 */
    { .dataOffset = 3169390, .properties = 5, .width = 17, .height = 23 },    /* text_pane_theme_light@C9_A1, 101 */
    { .dataOffset = 3170172, .properties = 1, .width = 43, .height = 23 },    /* text_pane_time_mm@A0, 1 */
    { .dataOffset = 3172150, .properties = 1, .width = 43, .height = 23 },    /* text_pane_time_mm@A1, 1 */
    { .dataOffset = 3174128, .properties = 5, .width = 59, .height = 21 },    /* text_settings@C0_A0, 101 */
    { .dataOffset = 3176606, .properties = 5, .width = 82, .height = 21 },    /* text_settings@C1_A0, 101 */
    { .dataOffset = 3180050, .properties = 5, .width = 96, .height = 21 },    /* text_settings@C2_A0, 101 */
    { .dataOffset = 3184082, .properties = 5, .width = 83, .height = 21 },    /* text_settings@C3_A0, 101 */
    { .dataOffset = 3187568, .properties = 5, .width = 102, .height = 21 },    /* text_settings@C4_A0, 101 */
    { .dataOffset = 3191852, .properties = 5, .width = 93, .height = 21 },    /* text_settings@C5_A0, 101 */
    { .dataOffset = 3195758, .properties = 5, .width = 87, .height = 21 },    /* text_settings@C6_A0, 101 */
    { .dataOffset = 3199412, .properties = 5, .width = 35, .height = 21 },    /* text_settings@C7_A0, 101 */
    { .dataOffset = 3200882, .properties = 5, .width = 35, .height = 21 },    /* text_settings@C8_A0, 101 */
    { .dataOffset = 3202352, .properties = 5, .width = 29, .height = 21 },    /* text_settings@C9_A0, 101 */
    { .dataOffset = 3203570, .properties = 5, .width = 59, .height = 21 },    /* text_settings@C0_A1, 101 */
    { .dataOffset = 3206048, .properties = 5, .width = 82, .height = 21 },    /* text_settings@C1_A1, 101 */
    { .dataOffset = 3209492, .properties = 5, .width = 96, .height = 21 },    /* text_settings@C2_A1, 101 */
    { .dataOffset = 3213524, .properties = 5, .width = 83, .height = 21 },    /* text_settings@C3_A1, 101 */
    { .dataOffset = 3217010, .properties = 5, .width = 102, .height = 21 },    /* text_settings@C4_A1, 101 */
    { .dataOffset = 3221294, .properties = 5, .width = 93, .height = 21 },    /* text_settings@C5_A1, 101 */
    { .dataOffset = 3225200, .properties = 5, .width = 87, .height = 21 },    /* text_settings@C6_A1, 101 */
    { .dataOffset = 3228854, .properties = 5, .width = 35, .height = 21 },    /* text_settings@C7_A1, 101 */
    { .dataOffset = 3230324, .properties = 5, .width = 35, .height = 21 },    /* text_settings@C8_A1, 101 */
    { .dataOffset = 3231794, .properties = 5, .width = 29, .height = 21 },    /* text_settings@C9_A1, 101 */
    { .dataOffset = 3233012, .properties = 5, .width = 41, .height = 21 },    /* text_setup@C0_A0, 101 */
    { .dataOffset = 3234734, .properties = 5, .width = 46, .height = 21 },    /* text_setup@C1_A0, 101 */
    { .dataOffset = 3236666, .properties = 5, .width = 80, .height = 21 },    /* text_setup@C2_A0, 101 */
    { .dataOffset = 3240026, .properties = 5, .width = 89, .height = 21 },    /* text_setup@C3_A0, 101 */
    { .dataOffset = 3243764, .properties = 5, .width = 52, .height = 21 },    /* text_setup@C4_A0, 101 */
    { .dataOffset = 3245948, .properties = 5, .width = 91, .height = 21 },    /* text_setup@C5_A0, 101 */
    { .dataOffset = 3249770, .properties = 5, .width = 81, .height = 21 },    /* text_setup@C6_A0, 101 */
    { .dataOffset = 3253172, .properties = 5, .width = 35, .height = 21 },    /* text_setup@C7_A0, 101 */
    { .dataOffset = 3254642, .properties = 5, .width = 76, .height = 21 },    /* text_setup@C8_A0, 101 */
    { .dataOffset = 3257834, .properties = 5, .width = 29, .height = 21 },    /* text_setup@C9_A0, 101 */
    { .dataOffset = 3259052, .properties = 5, .width = 41, .height = 21 },    /* text_setup@C0_A1, 101 */
    { .dataOffset = 3260774, .properties = 5, .width = 46, .height = 21 },    /* text_setup@C1_A1, 101 */
    { .dataOffset = 3262706, .properties = 5, .width = 80, .height = 21 },    /* text_setup@C2_A1, 101 */
    { .dataOffset = 3266066, .properties = 5, .width = 89, .height = 21 },    /* text_setup@C3_A1, 101 */
    { .dataOffset = 3269804, .properties = 5, .width = 52, .height = 21 },    /* text_setup@C4_A1, 101 */
    { .dataOffset = 3271988, .properties = 5, .width = 91, .height = 21 },    /* text_setup@C5_A1, 101 */
    { .dataOffset = 3275810, .properties = 5, .width = 81, .height = 21 },    /* text_setup@C6_A1, 101 */
    { .dataOffset = 3279212, .properties = 5, .width = 35, .height = 21 },    /* text_setup@C7_A1, 101 */
    { .dataOffset = 3280682, .properties = 5, .width = 76, .height = 21 },    /* text_setup@C8_A1, 101 */
    { .dataOffset = 3283874, .properties = 5, .width = 29, .height = 21 },    /* text_setup@C9_A1, 101 */
    { .dataOffset = 3285092, .properties = 5, .width = 50, .height = 21 },    /* text_theme@C0_A0, 101 */
    { .dataOffset = 3287192, .properties = 5, .width = 50, .height = 21 },    /* text_theme@C1_A0, 101 */
    { .dataOffset = 3289292, .properties = 5, .width = 50, .height = 21 },    /* text_theme@C2_A0, 101 */
    { .dataOffset = 3291392, .properties = 5, .width = 50, .height = 21 },    /* text_theme@C3_A0, 101 */
    { .dataOffset = 3293492, .properties = 5, .width = 41, .height = 21 },    /* text_theme@C4_A0, 101 */
    { .dataOffset = 3295214, .properties = 5, .width = 41, .height = 21 },    /* text_theme@C5_A0, 101 */
    { .dataOffset = 3296936, .properties = 5, .width = 39, .height = 21 },    /* text_theme@C6_A0, 101 */
    { .dataOffset = 3298574, .properties = 5, .width = 34, .height = 21 },    /* text_theme@C7_A0, 101 */
    { .dataOffset = 3300002, .properties = 5, .width = 41, .height = 21 },    /* text_theme@C8_A0, 101 */
    { .dataOffset = 3301724, .properties = 5, .width = 30, .height = 21 },    /* text_theme@C9_A0, 101 */
    { .dataOffset = 3302984, .properties = 5, .width = 50, .height = 21 },    /* text_theme@C0_A1, 101 */
    { .dataOffset = 3305084, .properties = 5, .width = 50, .height = 21 },    /* text_theme@C1_A1, 101 */
    { .dataOffset = 3307184, .properties = 5, .width = 50, .height = 21 },    /* text_theme@C2_A1, 101 */
    { .dataOffset = 3309284, .properties = 5, .width = 50, .height = 21 },    /* text_theme@C3_A1, 101 */
    { .dataOffset = 3311384, .properties = 5, .width = 41, .height = 21 },    /* text_theme@C4_A1, 101 */
    { .dataOffset = 3313106, .properties = 5, .width = 41, .height = 21 },    /* text_theme@C5_A1, 101 */
    { .dataOffset = 3314828, .properties = 5, .width = 39, .height = 21 },    /* text_theme@C6_A1, 101 */
    { .dataOffset = 3316466, .properties = 5, .width = 34, .height = 21 },    /* text_theme@C7_A1, 101 */
    { .dataOffset = 3317894, .properties = 5, .width = 41, .height = 21 },    /* text_theme@C8_A1, 101 */
    { .dataOffset = 3319616, .properties = 5, .width = 30, .height = 21 },    /* text_theme@C9_A1, 101 */
    { .dataOffset = 3320876, .properties = 5, .width = 36, .height = 21 },    /* text_time@C0_A0, 101 */
    { .dataOffset = 3322388, .properties = 5, .width = 26, .height = 21 },    /* text_time@C1_A0, 101 */
    { .dataOffset = 3323480, .properties = 5, .width = 27, .height = 21 },    /* text_time@C2_A0, 101 */
    { .dataOffset = 3324614, .properties = 5, .width = 42, .height = 21 },    /* text_time@C3_A0, 101 */
    { .dataOffset = 3326378, .properties = 5, .width = 34, .height = 21 },    /* text_time@C4_A0, 101 */
    { .dataOffset = 3327806, .properties = 5, .width = 25, .height = 21 },    /* text_time@C5_A0, 101 */
    { .dataOffset = 3328856, .properties = 5, .width = 47, .height = 21 },    /* text_time@C6_A0, 101 */
    { .dataOffset = 3330830, .properties = 5, .width = 33, .height = 21 },    /* text_time@C7_A0, 101 */
    { .dataOffset = 3332216, .properties = 5, .width = 33, .height = 21 },    /* text_time@C8_A0, 101 */
    { .dataOffset = 3333602, .properties = 5, .width = 31, .height = 21 },    /* text_time@C9_A0, 101 */
    { .dataOffset = 3334904, .properties = 5, .width = 36, .height = 21 },    /* text_time@C0_A1, 101 */
    { .dataOffset = 3336416, .properties = 5, .width = 26, .height = 21 },    /* text_time@C1_A1, 101 */
    { .dataOffset = 3337508, .properties = 5, .width = 27, .height = 21 },    /* text_time@C2_A1, 101 */
    { .dataOffset = 3338642, .properties = 5, .width = 42, .height = 21 },    /* text_time@C3_A1, 101 */
    { .dataOffset = 3340406, .properties = 5, .width = 34, .height = 21 },    /* text_time@C4_A1, 101 */
    { .dataOffset = 3341834, .properties = 5, .width = 25, .height = 21 },    /* text_time@C5_A1, 101 */
    { .dataOffset = 3342884, .properties = 5, .width = 47, .height = 21 },    /* text_time@C6_A1, 101 */
    { .dataOffset = 3344858, .properties = 5, .width = 33, .height = 21 },    /* text_time@C7_A1, 101 */
    { .dataOffset = 3346244, .properties = 5, .width = 33, .height = 21 },    /* text_time@C8_A1, 101 */
    { .dataOffset = 3347630, .properties = 5, .width = 31, .height = 21 },    /* text_time@C9_A1, 101 */
    { .dataOffset = 3348932, .properties = 5, .width = 76, .height = 29 },    /* title_alarm@C0_A0, 101 */
    { .dataOffset = 3353340, .properties = 5, .width = 76, .height = 29 },    /* title_alarm@C1_A0, 101 */
    { .dataOffset = 3357748, .properties = 5, .width = 76, .height = 29 },    /* title_alarm@C2_A0, 101 */
    { .dataOffset = 3362156, .properties = 5, .width = 88, .height = 29 },    /* title_alarm@C3_A0, 101 */
    { .dataOffset = 3367260, .properties = 5, .width = 88, .height = 29 },    /* title_alarm@C4_A0, 101 */
    { .dataOffset = 3372364, .properties = 5, .width = 93, .height = 29 },    /* title_alarm@C5_A0, 101 */
    { .dataOffset = 3377758, .properties = 5, .width = 102, .height = 29 },    /* title_alarm@C6_A0, 101 */
    { .dataOffset = 3383674, .properties = 5, .width = 66, .height = 29 },    /* title_alarm@C7_A0, 101 */
    { .dataOffset = 3387502, .properties = 5, .width = 65, .height = 29 },    /* title_alarm@C8_A0, 101 */
    { .dataOffset = 3391272, .properties = 5, .width = 83, .height = 29 },    /* title_alarm@C9_A0, 101 */
    { .dataOffset = 3396086, .properties = 5, .width = 76, .height = 29 },    /* title_alarm@C0_A1, 101 */
    { .dataOffset = 3400494, .properties = 5, .width = 76, .height = 29 },    /* title_alarm@C1_A1, 101 */
    { .dataOffset = 3404902, .properties = 5, .width = 76, .height = 29 },    /* title_alarm@C2_A1, 101 */
    { .dataOffset = 3409310, .properties = 5, .width = 88, .height = 29 },    /* title_alarm@C3_A1, 101 */
    { .dataOffset = 3414414, .properties = 5, .width = 88, .height = 29 },    /* title_alarm@C4_A1, 101 */
    { .dataOffset = 3419518, .properties = 5, .width = 93, .height = 29 },    /* title_alarm@C5_A1, 101 */
    { .dataOffset = 3424912, .properties = 5, .width = 102, .height = 29 },    /* title_alarm@C6_A1, 101 */
    { .dataOffset = 3430828, .properties = 5, .width = 66, .height = 29 },    /* title_alarm@C7_A1, 101 */
    { .dataOffset = 3434656, .properties = 5, .width = 65, .height = 29 },    /* title_alarm@C8_A1, 101 */
    { .dataOffset = 3438426, .properties = 5, .width = 83, .height = 29 },    /* title_alarm@C9_A1, 101 */
    { .dataOffset = 3443240, .properties = 5, .width = 105, .height = 29 },    /* title_brightness@C0_A0, 101 */
    { .dataOffset = 3449330, .properties = 5, .width = 106, .height = 29 },    /* title_brightness@C1_A0, 101 */
    { .dataOffset = 3455478, .properties = 5, .width = 92, .height = 29 },    /* title_brightness@C2_A0, 101 */
    { .dataOffset = 3460814, .properties = 5, .width = 110, .height = 29 },    /* title_brightness@C3_A0, 101 */
    { .dataOffset = 3467194, .properties = 5, .width = 49, .height = 29 },    /* title_brightness@C4_A0, 101 */
    { .dataOffset = 3470036, .properties = 5, .width = 110, .height = 29 },    /* title_brightness@C5_A0, 101 */
    { .dataOffset = 3476416, .properties = 5, .width = 86, .height = 29 },    /* title_brightness@C6_A0, 101 */
    { .dataOffset = 3481404, .properties = 5, .width = 46, .height = 29 },    /* title_brightness@C7_A0, 101 */
    { .dataOffset = 3484072, .properties = 5, .width = 57, .height = 29 },    /* title_brightness@C8_A0, 101 */
    { .dataOffset = 3487378, .properties = 5, .width = 39, .height = 29 },    /* title_brightness@C9_A0, 101 */
    { .dataOffset = 3489640, .properties = 5, .width = 105, .height = 29 },    /* title_brightness@C0_A1, 101 */
    { .dataOffset = 3495730, .properties = 5, .width = 106, .height = 29 },    /* title_brightness@C1_A1, 101 */
    { .dataOffset = 3501878, .properties = 5, .width = 92, .height = 29 },    /* title_brightness@C2_A1, 101 */
    { .dataOffset = 3507214, .properties = 5, .width = 110, .height = 29 },    /* title_brightness@C3_A1, 101 */
    { .dataOffset = 3513594, .properties = 5, .width = 49, .height = 29 },    /* title_brightness@C4_A1, 101 */
    { .dataOffset = 3516436, .properties = 5, .width = 110, .height = 29 },    /* title_brightness@C5_A1, 101 */
    { .dataOffset = 3522816, .properties = 5, .width = 86, .height = 29 },    /* title_brightness@C6_A1, 101 */
    { .dataOffset = 3527804, .properties = 5, .width = 46, .height = 29 },    /* title_brightness@C7_A1, 101 */
    { .dataOffset = 3530472, .properties = 5, .width = 57, .height = 29 },    /* title_brightness@C8_A1, 101 */
    { .dataOffset = 3533778, .properties = 5, .width = 39, .height = 29 },    /* title_brightness@C9_A1, 101 */
    { .dataOffset = 3536040, .properties = 5, .width = 63, .height = 29 },    /* title_colors@C0_A0, 101 */
    { .dataOffset = 3539694, .properties = 5, .width = 74, .height = 29 },    /* title_colors@C1_A0, 101 */
    { .dataOffset = 3543986, .properties = 5, .width = 67, .height = 29 },    /* title_colors@C2_A0, 101 */
    { .dataOffset = 3547872, .properties = 5, .width = 87, .height = 29 },    /* title_colors@C3_A0, 101 */
    { .dataOffset = 3552918, .properties = 5, .width = 75, .height = 29 },    /* title_colors@C4_A0, 101 */
    { .dataOffset = 3557268, .properties = 5, .width = 57, .height = 29 },    /* title_colors@C5_A0, 101 */
    { .dataOffset = 3560574, .properties = 5, .width = 66, .height = 29 },    /* title_colors@C6_A0, 101 */
    { .dataOffset = 3564402, .properties = 5, .width = 47, .height = 29 },    /* title_colors@C7_A0, 101 */
    { .dataOffset = 3567128, .properties = 5, .width = 22, .height = 29 },    /* title_colors@C8_A0, 101 */
    { .dataOffset = 3568404, .properties = 5, .width = 42, .height = 29 },    /* title_colors@C9_A0, 101 */
    { .dataOffset = 3570840, .properties = 5, .width = 63, .height = 29 },    /* title_colors@C0_A1, 101 */
    { .dataOffset = 3574494, .properties = 5, .width = 74, .height = 29 },    /* title_colors@C1_A1, 101 */
    { .dataOffset = 3578786, .properties = 5, .width = 67, .height = 29 },    /* title_colors@C2_A1, 101 */
    { .dataOffset = 3582672, .properties = 5, .width = 87, .height = 29 },    /* title_colors@C3_A1, 101 */
    { .dataOffset = 3587718, .properties = 5, .width = 75, .height = 29 },    /* title_colors@C4_A1, 101 */
    { .dataOffset = 3592068, .properties = 5, .width = 57, .height = 29 },    /* title_colors@C5_A1, 101 */
    { .dataOffset = 3595374, .properties = 5, .width = 66, .height = 29 },    /* title_colors@C6_A1, 101 */
    { .dataOffset = 3599202, .properties = 5, .width = 47, .height = 29 },    /* title_colors@C7_A1, 101 */
    { .dataOffset = 3601928, .properties = 5, .width = 22, .height = 29 },    /* title_colors@C8_A1, 101 */
    { .dataOffset = 3603204, .properties = 5, .width = 42, .height = 29 },    /* title_colors@C9_A1, 101 */
    { .dataOffset = 3605640, .properties = 5, .width = 44, .height = 29 },    /* title_date@C0_A0, 101 */
    { .dataOffset = 3608192, .properties = 5, .width = 64, .height = 29 },    /* title_date@C1_A0, 101 */
    { .dataOffset = 3611904, .properties = 5, .width = 64, .height = 29 },    /* title_date@C2_A0, 101 */
    { .dataOffset = 3615616, .properties = 5, .width = 44, .height = 29 },    /* title_date@C3_A0, 101 */
    { .dataOffset = 3618168, .properties = 5, .width = 59, .height = 29 },    /* title_date@C4_A0, 101 */
    { .dataOffset = 3621590, .properties = 5, .width = 72, .height = 29 },    /* title_date@C5_A0, 101 */
    { .dataOffset = 3625766, .properties = 5, .width = 51, .height = 29 },    /* title_date@C6_A0, 101 */
    { .dataOffset = 3628724, .properties = 5, .width = 43, .height = 29 },    /* title_date@C7_A0, 101 */
    { .dataOffset = 3631218, .properties = 5, .width = 43, .height = 29 },    /* title_date@C8_A0, 101 */
    { .dataOffset = 3633712, .properties = 5, .width = 42, .height = 29 },    /* title_date@C9_A0, 101 */
    { .dataOffset = 3636148, .properties = 5, .width = 44, .height = 29 },    /* title_date@C0_A1, 101 */
    { .dataOffset = 3638700, .properties = 5, .width = 64, .height = 29 },    /* title_date@C1_A1, 101 */
    { .dataOffset = 3642412, .properties = 5, .width = 64, .height = 29 },    /* title_date@C2_A1, 101 */
    { .dataOffset = 3646124, .properties = 5, .width = 44, .height = 29 },    /* title_date@C3_A1, 101 */
    { .dataOffset = 3648676, .properties = 5, .width = 59, .height = 29 },    /* title_date@C4_A1, 101 */
    { .dataOffset = 3652098, .properties = 5, .width = 72, .height = 29 },    /* title_date@C5_A1, 101 */
    { .dataOffset = 3656274, .properties = 5, .width = 51, .height = 29 },    /* title_date@C6_A1, 101 */
    { .dataOffset = 3659232, .properties = 5, .width = 43, .height = 29 },    /* title_date@C7_A1, 101 */
    { .dataOffset = 3661726, .properties = 5, .width = 43, .height = 29 },    /* title_date@C8_A1, 101 */
    { .dataOffset = 3664220, .properties = 5, .width = 42, .height = 29 },    /* title_date@C9_A1, 101 */
    { .dataOffset = 3666656, .properties = 5, .width = 37, .height = 29 },    /* title_info@C0_A0, 101 */
    { .dataOffset = 3668802, .properties = 5, .width = 37, .height = 29 },    /* title_info@C1_A0, 101 */
    { .dataOffset = 3670948, .properties = 5, .width = 37, .height = 29 },    /* title_info@C2_A0, 101 */
    { .dataOffset = 3673094, .properties = 5, .width = 37, .height = 29 },    /* title_info@C3_A0, 101 */
    { .dataOffset = 3675240, .properties = 5, .width = 119, .height = 29 },    /* title_info@C4_A0, 101 */
    { .dataOffset = 3682142, .properties = 5, .width = 124, .height = 29 },    /* title_info@C5_A0, 101 */
    { .dataOffset = 3689334, .properties = 5, .width = 136, .height = 29 },    /* title_info@C6_A0, 101 */
    { .dataOffset = 3697222, .properties = 5, .width = 48, .height = 29 },    /* title_info@C7_A0, 101 */
    { .dataOffset = 3700006, .properties = 5, .width = 48, .height = 29 },    /* title_info@C8_A0, 101 */
    { .dataOffset = 3702790, .properties = 5, .width = 42, .height = 29 },    /* title_info@C9_A0, 101 */
    { .dataOffset = 3705226, .properties = 5, .width = 37, .height = 29 },    /* title_info@C0_A1, 101 */
    { .dataOffset = 3707372, .properties = 5, .width = 37, .height = 29 },    /* title_info@C1_A1, 101 */
    { .dataOffset = 3709518, .properties = 5, .width = 37, .height = 29 },    /* title_info@C2_A1, 101 */
    { .dataOffset = 3711664, .properties = 5, .width = 37, .height = 29 },    /* title_info@C3_A1, 101 */
    { .dataOffset = 3713810, .properties = 5, .width = 119, .height = 29 },    /* title_info@C4_A1, 101 */
    { .dataOffset = 3720712, .properties = 5, .width = 124, .height = 29 },    /* title_info@C5_A1, 101 */
    { .dataOffset = 3727904, .properties = 5, .width = 136, .height = 29 },    /* title_info@C6_A1, 101 */
    { .dataOffset = 3735792, .properties = 5, .width = 48, .height = 29 },    /* title_info@C7_A1, 101 */
    { .dataOffset = 3738576, .properties = 5, .width = 48, .height = 29 },    /* title_info@C8_A1, 101 */
    { .dataOffset = 3741360, .properties = 5, .width = 42, .height = 29 },    /* title_info@C9_A1, 101 */
    { .dataOffset = 3743796, .properties = 5, .width = 97, .height = 29 },    /* title_language@C0_A0, 101 */
    { .dataOffset = 3749422, .properties = 5, .width = 42, .height = 29 },    /* title_language@C1_A0, 101 */
    { .dataOffset = 3751858, .properties = 5, .width = 81, .height = 29 },    /* title_language@C2_A0, 101 */
    { .dataOffset = 3756556, .properties = 5, .width = 72, .height = 29 },    /* title_language@C3_A0, 101 */
    { .dataOffset = 3760732, .properties = 5, .width = 67, .height = 29 },    /* title_language@C4_A0, 101 */
    { .dataOffset = 3764618, .properties = 5, .width = 65, .height = 29 },    /* title_language@C5_A0, 101 */
    { .dataOffset = 3768388, .properties = 5, .width = 55, .height = 29 },    /* title_language@C6_A0, 101 */
    { .dataOffset = 3771578, .properties = 5, .width = 47, .height = 29 },    /* title_language@C7_A0, 101 */
    { .dataOffset = 3774304, .properties = 5, .width = 47, .height = 29 },    /* title_language@C8_A0, 101 */
    { .dataOffset = 3777030, .properties = 5, .width = 39, .height = 29 },    /* title_language@C9_A0, 101 */
    { .dataOffset = 3779292, .properties = 5, .width = 97, .height = 29 },    /* title_language@C0_A1, 101 */
    { .dataOffset = 3784918, .properties = 5, .width = 42, .height = 29 },    /* title_language@C1_A1, 101 */
    { .dataOffset = 3787354, .properties = 5, .width = 81, .height = 29 },    /* title_language@C2_A1, 101 */
    { .dataOffset = 3792052, .properties = 5, .width = 72, .height = 29 },    /* title_language@C3_A1, 101 */
    { .dataOffset = 3796228, .properties = 5, .width = 67, .height = 29 },    /* title_language@C4_A1, 101 */
    { .dataOffset = 3800114, .properties = 5, .width = 65, .height = 29 },    /* title_language@C5_A1, 101 */
    { .dataOffset = 3803884, .properties = 5, .width = 55, .height = 29 },    /* title_language@C6_A1, 101 */
    { .dataOffset = 3807074, .properties = 5, .width = 47, .height = 29 },    /* title_language@C7_A1, 101 */
    { .dataOffset = 3809800, .properties = 5, .width = 47, .height = 29 },    /* title_language@C8_A1, 101 */
    { .dataOffset = 3812526, .properties = 5, .width = 39, .height = 29 },    /* title_language@C9_A1, 101 */
    { .dataOffset = 3814788, .properties = 5, .width = 110, .height = 29 },    /* title_main_menu@C0_A0, 101 */
    { .dataOffset = 3821168, .properties = 5, .width = 117, .height = 29 },    /* title_main_menu@C1_A0, 101 */
    { .dataOffset = 3827954, .properties = 5, .width = 115, .height = 29 },    /* title_main_menu@C2_A0, 101 */
    { .dataOffset = 3834624, .properties = 5, .width = 146, .height = 29 },    /* title_main_menu@C3_A0, 101 */
    { .dataOffset = 3843092, .properties = 5, .width = 146, .height = 29 },    /* title_main_menu@C4_A0, 101 */
    { .dataOffset = 3851560, .properties = 5, .width = 159, .height = 29 },    /* title_main_menu@C5_A0, 101 */
    { .dataOffset = 3860782, .properties = 5, .width = 153, .height = 29 },    /* title_main_menu@C6_A0, 101 */
    { .dataOffset = 3869656, .properties = 5, .width = 72, .height = 29 },    /* title_main_menu@C7_A0, 101 */
    { .dataOffset = 3873832, .properties = 5, .width = 123, .height = 29 },    /* title_main_menu@C8_A0, 101 */
    { .dataOffset = 3880966, .properties = 5, .width = 92, .height = 29 },    /* title_main_menu@C9_A0, 101 */
    { .dataOffset = 3886302, .properties = 5, .width = 110, .height = 29 },    /* title_main_menu@C0_A1, 101 */
    { .dataOffset = 3892682, .properties = 5, .width = 117, .height = 29 },    /* title_main_menu@C1_A1, 101 */
    { .dataOffset = 3899468, .properties = 5, .width = 115, .height = 29 },    /* title_main_menu@C2_A1, 101 */
    { .dataOffset = 3906138, .properties = 5, .width = 146, .height = 29 },    /* title_main_menu@C3_A1, 101 */
    { .dataOffset = 3914606, .properties = 5, .width = 146, .height = 29 },    /* title_main_menu@C4_A1, 101 */
    { .dataOffset = 3923074, .properties = 5, .width = 159, .height = 29 },    /* title_main_menu@C5_A1, 101 */
    { .dataOffset = 3932296, .properties = 5, .width = 153, .height = 29 },    /* title_main_menu@C6_A1, 101 */
    { .dataOffset = 3941170, .properties = 5, .width = 72, .height = 29 },    /* title_main_menu@C7_A1, 101 */
    { .dataOffset = 3945346, .properties = 5, .width = 123, .height = 29 },    /* title_main_menu@C8_A1, 101 */
    { .dataOffset = 3952480, .properties = 5, .width = 92, .height = 29 },    /* title_main_menu@C9_A1, 101 */
    { .dataOffset = 3957816, .properties = 5, .width = 138, .height = 29 },    /* title_measurement@C0_A0, 101 */
    { .dataOffset = 3965820, .properties = 5, .width = 79, .height = 29 },    /* title_measurement@C1_A0, 101 */
    { .dataOffset = 3970402, .properties = 5, .width = 90, .height = 29 },    /* title_measurement@C2_A0, 101 */
    { .dataOffset = 3975622, .properties = 5, .width = 73, .height = 29 },    /* title_measurement@C3_A0, 101 */
    { .dataOffset = 3979856, .properties = 5, .width = 90, .height = 29 },    /* title_measurement@C4_A0, 101 */
    { .dataOffset = 3985076, .properties = 5, .width = 121, .height = 29 },    /* title_measurement@C5_A0, 101 */
    { .dataOffset = 3992094, .properties = 5, .width = 117, .height = 29 },    /* title_measurement@C6_A0, 101 */
    { .dataOffset = 3998880, .properties = 5, .width = 48, .height = 29 },    /* title_measurement@C7_A0, 101 */
    { .dataOffset = 4001664, .properties = 5, .width = 46, .height = 29 },    /* title_measurement@C8_A0, 101 */
    { .dataOffset = 4004332, .properties = 5, .width = 42, .height = 29 },    /* title_measurement@C9_A0, 101 */
    { .dataOffset = 4006768, .properties = 5, .width = 138, .height = 29 },    /* title_measurement@C0_A1, 101 */
    { .dataOffset = 4014772, .properties = 5, .width = 79, .height = 29 },    /* title_measurement@C1_A1, 101 */
    { .dataOffset = 4019354, .properties = 5, .width = 90, .height = 29 },    /* title_measurement@C2_A1, 101 */
    { .dataOffset = 4024574, .properties = 5, .width = 73, .height = 29 },    /* title_measurement@C3_A1, 101 */
    { .dataOffset = 4028808, .properties = 5, .width = 90, .height = 29 },    /* title_measurement@C4_A1, 101 */
    { .dataOffset = 4034028, .properties = 5, .width = 121, .height = 29 },    /* title_measurement@C5_A1, 101 */
    { .dataOffset = 4041046, .properties = 5, .width = 117, .height = 29 },    /* title_measurement@C6_A1, 101 */
    { .dataOffset = 4047832, .properties = 5, .width = 48, .height = 29 },    /* title_measurement@C7_A1, 101 */
    { .dataOffset = 4050616, .properties = 5, .width = 46, .height = 29 },    /* title_measurement@C8_A1, 101 */
    { .dataOffset = 4053284, .properties = 5, .width = 42, .height = 29 },    /* title_measurement@C9_A1, 101 */
    { .dataOffset = 4055720, .properties = 5, .width = 81, .height = 29 },    /* title_settings@C0_A0, 101 */
    { .dataOffset = 4060418, .properties = 5, .width = 113, .height = 29 },    /* title_settings@C1_A0, 101 */
    { .dataOffset = 4066972, .properties = 5, .width = 133, .height = 29 },    /* title_settings@C2_A0, 101 */
    { .dataOffset = 4074686, .properties = 5, .width = 115, .height = 29 },    /* title_settings@C3_A0, 101 */
    { .dataOffset = 4081356, .properties = 5, .width = 139, .height = 29 },    /* title_settings@C4_A0, 101 */
    { .dataOffset = 4089418, .properties = 5, .width = 128, .height = 29 },    /* title_settings@C5_A0, 101 */
    { .dataOffset = 4096842, .properties = 5, .width = 120, .height = 29 },    /* title_settings@C6_A0, 101 */
    { .dataOffset = 4103802, .properties = 5, .width = 46, .height = 29 },    /* title_settings@C7_A0, 101 */
    { .dataOffset = 4106470, .properties = 5, .width = 46, .height = 29 },    /* title_settings@C8_A0, 101 */
    { .dataOffset = 4109138, .properties = 5, .width = 41, .height = 29 },    /* title_settings@C9_A0, 101 */
    { .dataOffset = 4111516, .properties = 5, .width = 81, .height = 29 },    /* title_settings@C0_A1, 101 */
    { .dataOffset = 4116214, .properties = 5, .width = 113, .height = 29 },    /* title_settings@C1_A1, 101 */
    { .dataOffset = 4122768, .properties = 5, .width = 133, .height = 29 },    /* title_settings@C2_A1, 101 */
    { .dataOffset = 4130482, .properties = 5, .width = 115, .height = 29 },    /* title_settings@C3_A1, 101 */
    { .dataOffset = 4137152, .properties = 5, .width = 139, .height = 29 },    /* title_settings@C4_A1, 101 */
    { .dataOffset = 4145214, .properties = 5, .width = 128, .height = 29 },    /* title_settings@C5_A1, 101 */
    { .dataOffset = 4152638, .properties = 5, .width = 120, .height = 29 },    /* title_settings@C6_A1, 101 */
    { .dataOffset = 4159598, .properties = 5, .width = 46, .height = 29 },    /* title_settings@C7_A1, 101 */
    { .dataOffset = 4162266, .properties = 5, .width = 46, .height = 29 },    /* title_settings@C8_A1, 101 */
    { .dataOffset = 4164934, .properties = 5, .width = 41, .height = 29 },    /* title_settings@C9_A1, 101 */
    { .dataOffset = 4167312, .properties = 5, .width = 57, .height = 29 },    /* title_setup@C0_A0, 101 */
    { .dataOffset = 4170618, .properties = 5, .width = 63, .height = 29 },    /* title_setup@C1_A0, 101 */
    { .dataOffset = 4174272, .properties = 5, .width = 111, .height = 29 },    /* title_setup@C2_A0, 101 */
    { .dataOffset = 4180710, .properties = 5, .width = 121, .height = 29 },    /* title_setup@C3_A0, 101 */
    { .dataOffset = 4187728, .properties = 5, .width = 72, .height = 29 },    /* title_setup@C4_A0, 101 */
    { .dataOffset = 4191904, .properties = 5, .width = 125, .height = 29 },    /* title_setup@C5_A0, 101 */
    { .dataOffset = 4199154, .properties = 5, .width = 112, .height = 29 },    /* title_setup@C6_A0, 101 */
    { .dataOffset = 4205650, .properties = 5, .width = 46, .height = 29 },    /* title_setup@C7_A0, 101 */
    { .dataOffset = 4208318, .properties = 5, .width = 102, .height = 29 },    /* title_setup@C8_A0, 101 */
    { .dataOffset = 4214234, .properties = 5, .width = 40, .height = 29 },    /* title_setup@C9_A0, 101 */
    { .dataOffset = 4216554, .properties = 5, .width = 57, .height = 29 },    /* title_setup@C0_A1, 101 */
    { .dataOffset = 4219860, .properties = 5, .width = 63, .height = 29 },    /* title_setup@C1_A1, 101 */
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
