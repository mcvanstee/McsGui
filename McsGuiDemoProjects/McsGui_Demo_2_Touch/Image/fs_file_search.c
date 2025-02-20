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
    { .dataOffset = 214928, .properties = 4, .width = 146, .height = 38 },    /* Footer_Button@C0, 100 */
    { .dataOffset = 226024, .properties = 4, .width = 146, .height = 38 },    /* Footer_Button@C1, 100 */
    { .dataOffset = 237120, .properties = 4, .width = 30, .height = 30 },    /* NumInput_minus@C0, 100 */
    { .dataOffset = 238920, .properties = 4, .width = 30, .height = 30 },    /* NumInput_minus@C1, 100 */
    { .dataOffset = 240720, .properties = 4, .width = 30, .height = 30 },    /* NumInput_plus@C0, 100 */
    { .dataOffset = 242520, .properties = 4, .width = 30, .height = 30 },    /* NumInput_plus@C1, 100 */
    { .dataOffset = 244320, .properties = 4, .width = 146, .height = 90 },    /* Page_Background@C0, 100 */
    { .dataOffset = 270600, .properties = 4, .width = 146, .height = 90 },    /* Page_Background@C1, 100 */
    { .dataOffset = 296880, .properties = 4, .width = 22, .height = 31 },    /* Slider@C0, 100 */
    { .dataOffset = 298244, .properties = 4, .width = 22, .height = 31 },    /* Slider@C1, 100 */
    { .dataOffset = 299608, .properties = 4, .width = 74, .height = 27 },    /* Footer_MCSGUI@C0, 100 */
    { .dataOffset = 303604, .properties = 4, .width = 74, .height = 27 },    /* Footer_MCSGUI@C1, 100 */
    { .dataOffset = 307600, .properties = 12, .width = 18, .height = 20 },    /* icon_btn_Agenda@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_AGENDA__C000_D001, 11 */
    { .dataOffset = 308320, .properties = 12, .width = 18, .height = 20 },    /* icon_btn_Agenda@C0_D2, 1100 */
    { .dataOffset = 309040, .properties = 12, .width = 18, .height = 20 },    /* icon_btn_Agenda@C0_D3, 1100 */
    { .dataOffset = 309760, .properties = 12, .width = 18, .height = 20 },    /* icon_btn_Agenda@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_AGENDA__C001_D000, 11 */
    { .dataOffset = 310480, .properties = 12, .width = 18, .height = 20 },    /* icon_btn_Agenda@C1_D1, 1100 */
    { .dataOffset = 311200, .properties = 12, .width = 18, .height = 20 },    /* icon_btn_Agenda@C1_D2, 1100 */
    { .dataOffset = 311920, .properties = 12, .width = 18, .height = 20 },    /* icon_btn_Agenda@C1_D3, 1100 */
    { .dataOffset = 312640, .properties = 12, .width = 18, .height = 20 },    /* icon_btn_Agenda@C1_D4, 1100 */
    { .dataOffset = 313360, .properties = 12, .width = 35, .height = 18 },    /* icon_btn_Arrow-Back@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_ARROW_BACK__C000_D001, 11 */
    { .dataOffset = 314620, .properties = 12, .width = 35, .height = 18 },    /* icon_btn_Arrow-Back@C0_D2, 1100 */
    { .dataOffset = 315880, .properties = 12, .width = 35, .height = 18 },    /* icon_btn_Arrow-Back@C0_D3, 1100 */
    { .dataOffset = 317140, .properties = 12, .width = 35, .height = 18 },    /* icon_btn_Arrow-Back@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_ARROW_BACK__C001_D000, 11 */
    { .dataOffset = 318400, .properties = 12, .width = 35, .height = 18 },    /* icon_btn_Arrow-Back@C1_D1, 1100 */
    { .dataOffset = 319660, .properties = 12, .width = 35, .height = 18 },    /* icon_btn_Arrow-Back@C1_D2, 1100 */
    { .dataOffset = 320920, .properties = 12, .width = 35, .height = 18 },    /* icon_btn_Arrow-Back@C1_D3, 1100 */
    { .dataOffset = 322180, .properties = 12, .width = 35, .height = 18 },    /* icon_btn_Arrow-Back@C1_D4, 1100 */
    { .dataOffset = 323440, .properties = 12, .width = 13, .height = 4 },    /* icon_btn_Arrow_down@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_ARROW_DOWN__C000_D001, 11 */
    { .dataOffset = 323544, .properties = 12, .width = 13, .height = 4 },    /* icon_btn_Arrow_down@C0_D2, 1100 */
    { .dataOffset = 323648, .properties = 12, .width = 13, .height = 4 },    /* icon_btn_Arrow_down@C0_D3, 1100 */
    { .dataOffset = 323752, .properties = 12, .width = 13, .height = 4 },    /* icon_btn_Arrow_down@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_ARROW_DOWN__C001_D000, 11 */
    { .dataOffset = 323856, .properties = 12, .width = 13, .height = 4 },    /* icon_btn_Arrow_down@C1_D1, 1100 */
    { .dataOffset = 323960, .properties = 12, .width = 13, .height = 4 },    /* icon_btn_Arrow_down@C1_D2, 1100 */
    { .dataOffset = 324064, .properties = 12, .width = 13, .height = 4 },    /* icon_btn_Arrow_down@C1_D3, 1100 */
    { .dataOffset = 324168, .properties = 12, .width = 13, .height = 4 },    /* icon_btn_Arrow_down@C1_D4, 1100 */
    { .dataOffset = 324272, .properties = 12, .width = 12, .height = 4 },    /* icon_btn_Arrow_up@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_ARROW_UP__C000_D001, 11 */
    { .dataOffset = 324368, .properties = 12, .width = 12, .height = 4 },    /* icon_btn_Arrow_up@C0_D2, 1100 */
    { .dataOffset = 324464, .properties = 12, .width = 12, .height = 4 },    /* icon_btn_Arrow_up@C0_D3, 1100 */
    { .dataOffset = 324560, .properties = 12, .width = 12, .height = 4 },    /* icon_btn_Arrow_up@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_ARROW_UP__C001_D000, 11 */
    { .dataOffset = 324656, .properties = 12, .width = 12, .height = 4 },    /* icon_btn_Arrow_up@C1_D1, 1100 */
    { .dataOffset = 324752, .properties = 12, .width = 12, .height = 4 },    /* icon_btn_Arrow_up@C1_D2, 1100 */
    { .dataOffset = 324848, .properties = 12, .width = 12, .height = 4 },    /* icon_btn_Arrow_up@C1_D3, 1100 */
    { .dataOffset = 324944, .properties = 12, .width = 12, .height = 4 },    /* icon_btn_Arrow_up@C1_D4, 1100 */
    { .dataOffset = 325040, .properties = 12, .width = 16, .height = 18 },    /* icon_btn_Bell@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_BELL__C000_D001, 11 */
    { .dataOffset = 325616, .properties = 12, .width = 16, .height = 18 },    /* icon_btn_Bell@C0_D2, 1100 */
    { .dataOffset = 326192, .properties = 12, .width = 16, .height = 18 },    /* icon_btn_Bell@C0_D3, 1100 */
    { .dataOffset = 326768, .properties = 12, .width = 16, .height = 18 },    /* icon_btn_Bell@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_BELL__C001_D000, 11 */
    { .dataOffset = 327344, .properties = 12, .width = 16, .height = 18 },    /* icon_btn_Bell@C1_D1, 1100 */
    { .dataOffset = 327920, .properties = 12, .width = 16, .height = 18 },    /* icon_btn_Bell@C1_D2, 1100 */
    { .dataOffset = 328496, .properties = 12, .width = 16, .height = 18 },    /* icon_btn_Bell@C1_D3, 1100 */
    { .dataOffset = 329072, .properties = 12, .width = 16, .height = 18 },    /* icon_btn_Bell@C1_D4, 1100 */
    { .dataOffset = 329648, .properties = 12, .width = 30, .height = 25 },    /* icon_btn_Brightness@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_BRIGHTNESS__C000_D001, 11 */
    { .dataOffset = 331148, .properties = 12, .width = 30, .height = 25 },    /* icon_btn_Brightness@C0_D2, 1100 */
    { .dataOffset = 332648, .properties = 12, .width = 30, .height = 25 },    /* icon_btn_Brightness@C0_D3, 1100 */
    { .dataOffset = 334148, .properties = 12, .width = 30, .height = 25 },    /* icon_btn_Brightness@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_BRIGHTNESS__C001_D000, 11 */
    { .dataOffset = 335648, .properties = 12, .width = 30, .height = 25 },    /* icon_btn_Brightness@C1_D1, 1100 */
    { .dataOffset = 337148, .properties = 12, .width = 30, .height = 25 },    /* icon_btn_Brightness@C1_D2, 1100 */
    { .dataOffset = 338648, .properties = 12, .width = 30, .height = 25 },    /* icon_btn_Brightness@C1_D3, 1100 */
    { .dataOffset = 340148, .properties = 12, .width = 30, .height = 25 },    /* icon_btn_Brightness@C1_D4, 1100 */
    { .dataOffset = 341648, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Brush@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_BRUSH__C000_D001, 11 */
    { .dataOffset = 342616, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Brush@C0_D2, 1100 */
    { .dataOffset = 343584, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Brush@C0_D3, 1100 */
    { .dataOffset = 344552, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Brush@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_BRUSH__C001_D000, 11 */
    { .dataOffset = 345520, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Brush@C1_D1, 1100 */
    { .dataOffset = 346488, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Brush@C1_D2, 1100 */
    { .dataOffset = 347456, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Brush@C1_D3, 1100 */
    { .dataOffset = 348424, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Brush@C1_D4, 1100 */
    { .dataOffset = 349392, .properties = 12, .width = 18, .height = 18 },    /* icon_btn_Cancel@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_CANCEL__C000_D001, 11 */
    { .dataOffset = 350040, .properties = 12, .width = 18, .height = 18 },    /* icon_btn_Cancel@C0_D2, 1100 */
    { .dataOffset = 350688, .properties = 12, .width = 18, .height = 18 },    /* icon_btn_Cancel@C0_D3, 1100 */
    { .dataOffset = 351336, .properties = 12, .width = 18, .height = 18 },    /* icon_btn_Cancel@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_CANCEL__C001_D000, 11 */
    { .dataOffset = 351984, .properties = 12, .width = 18, .height = 18 },    /* icon_btn_Cancel@C1_D1, 1100 */
    { .dataOffset = 352632, .properties = 12, .width = 18, .height = 18 },    /* icon_btn_Cancel@C1_D2, 1100 */
    { .dataOffset = 353280, .properties = 12, .width = 18, .height = 18 },    /* icon_btn_Cancel@C1_D3, 1100 */
    { .dataOffset = 353928, .properties = 12, .width = 18, .height = 18 },    /* icon_btn_Cancel@C1_D4, 1100 */
    { .dataOffset = 354576, .properties = 12, .width = 26, .height = 21 },    /* icon_btn_Checkmark_large@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_CHECKMARK_LARGE__C000_D001, 11 */
    { .dataOffset = 355668, .properties = 12, .width = 26, .height = 21 },    /* icon_btn_Checkmark_large@C0_D2, 1100 */
    { .dataOffset = 356760, .properties = 12, .width = 26, .height = 21 },    /* icon_btn_Checkmark_large@C0_D3, 1100 */
    { .dataOffset = 357852, .properties = 12, .width = 26, .height = 21 },    /* icon_btn_Checkmark_large@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_CHECKMARK_LARGE__C001_D000, 11 */
    { .dataOffset = 358944, .properties = 12, .width = 26, .height = 21 },    /* icon_btn_Checkmark_large@C1_D1, 1100 */
    { .dataOffset = 360036, .properties = 12, .width = 26, .height = 21 },    /* icon_btn_Checkmark_large@C1_D2, 1100 */
    { .dataOffset = 361128, .properties = 12, .width = 26, .height = 21 },    /* icon_btn_Checkmark_large@C1_D3, 1100 */
    { .dataOffset = 362220, .properties = 12, .width = 26, .height = 21 },    /* icon_btn_Checkmark_large@C1_D4, 1100 */
    { .dataOffset = 363312, .properties = 12, .width = 20, .height = 20 },    /* icon_btn_Clock@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_CLOCK__C000_D001, 11 */
    { .dataOffset = 364112, .properties = 12, .width = 20, .height = 20 },    /* icon_btn_Clock@C0_D2, 1100 */
    { .dataOffset = 364912, .properties = 12, .width = 20, .height = 20 },    /* icon_btn_Clock@C0_D3, 1100 */
    { .dataOffset = 365712, .properties = 12, .width = 20, .height = 20 },    /* icon_btn_Clock@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_CLOCK__C001_D000, 11 */
    { .dataOffset = 366512, .properties = 12, .width = 20, .height = 20 },    /* icon_btn_Clock@C1_D1, 1100 */
    { .dataOffset = 367312, .properties = 12, .width = 20, .height = 20 },    /* icon_btn_Clock@C1_D2, 1100 */
    { .dataOffset = 368112, .properties = 12, .width = 20, .height = 20 },    /* icon_btn_Clock@C1_D3, 1100 */
    { .dataOffset = 368912, .properties = 12, .width = 20, .height = 20 },    /* icon_btn_Clock@C1_D4, 1100 */
    { .dataOffset = 369712, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Focus@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_FOCUS__C000_D001, 11 */
    { .dataOffset = 370680, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Focus@C0_D2, 1100 */
    { .dataOffset = 371648, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Focus@C0_D3, 1100 */
    { .dataOffset = 372616, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Focus@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_FOCUS__C001_D000, 11 */
    { .dataOffset = 373584, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Focus@C1_D1, 1100 */
    { .dataOffset = 374552, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Focus@C1_D2, 1100 */
    { .dataOffset = 375520, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Focus@C1_D3, 1100 */
    { .dataOffset = 376488, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Focus@C1_D4, 1100 */
    { .dataOffset = 377456, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Gear@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_GEAR__C000_D001, 11 */
    { .dataOffset = 378424, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Gear@C0_D2, 1100 */
    { .dataOffset = 379392, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Gear@C0_D3, 1100 */
    { .dataOffset = 380360, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Gear@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_GEAR__C001_D000, 11 */
    { .dataOffset = 381328, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Gear@C1_D1, 1100 */
    { .dataOffset = 382296, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Gear@C1_D2, 1100 */
    { .dataOffset = 383264, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Gear@C1_D3, 1100 */
    { .dataOffset = 384232, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Gear@C1_D4, 1100 */
    { .dataOffset = 385200, .properties = 12, .width = 20, .height = 20 },    /* icon_btn_Global@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_GLOBAL__C000_D001, 11 */
    { .dataOffset = 386000, .properties = 12, .width = 20, .height = 20 },    /* icon_btn_Global@C0_D2, 1100 */
    { .dataOffset = 386800, .properties = 12, .width = 20, .height = 20 },    /* icon_btn_Global@C0_D3, 1100 */
    { .dataOffset = 387600, .properties = 12, .width = 20, .height = 20 },    /* icon_btn_Global@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_GLOBAL__C001_D000, 11 */
    { .dataOffset = 388400, .properties = 12, .width = 20, .height = 20 },    /* icon_btn_Global@C1_D1, 1100 */
    { .dataOffset = 389200, .properties = 12, .width = 20, .height = 20 },    /* icon_btn_Global@C1_D2, 1100 */
    { .dataOffset = 390000, .properties = 12, .width = 20, .height = 20 },    /* icon_btn_Global@C1_D3, 1100 */
    { .dataOffset = 390800, .properties = 12, .width = 20, .height = 20 },    /* icon_btn_Global@C1_D4, 1100 */
    { .dataOffset = 391600, .properties = 12, .width = 21, .height = 21 },    /* icon_btn_Info@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_INFO__C000_D001, 11 */
    { .dataOffset = 392482, .properties = 12, .width = 21, .height = 21 },    /* icon_btn_Info@C0_D2, 1100 */
    { .dataOffset = 393364, .properties = 12, .width = 21, .height = 21 },    /* icon_btn_Info@C0_D3, 1100 */
    { .dataOffset = 394246, .properties = 12, .width = 21, .height = 21 },    /* icon_btn_Info@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_INFO__C001_D000, 11 */
    { .dataOffset = 395128, .properties = 12, .width = 21, .height = 21 },    /* icon_btn_Info@C1_D1, 1100 */
    { .dataOffset = 396010, .properties = 12, .width = 21, .height = 21 },    /* icon_btn_Info@C1_D2, 1100 */
    { .dataOffset = 396892, .properties = 12, .width = 21, .height = 21 },    /* icon_btn_Info@C1_D3, 1100 */
    { .dataOffset = 397774, .properties = 12, .width = 21, .height = 21 },    /* icon_btn_Info@C1_D4, 1100 */
    { .dataOffset = 398656, .properties = 12, .width = 23, .height = 16 },    /* icon_btn_Keyboard@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_KEYBOARD__C000_D001, 11 */
    { .dataOffset = 399392, .properties = 12, .width = 23, .height = 16 },    /* icon_btn_Keyboard@C0_D2, 1100 */
    { .dataOffset = 400128, .properties = 12, .width = 23, .height = 16 },    /* icon_btn_Keyboard@C0_D3, 1100 */
    { .dataOffset = 400864, .properties = 12, .width = 23, .height = 16 },    /* icon_btn_Keyboard@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_KEYBOARD__C001_D000, 11 */
    { .dataOffset = 401600, .properties = 12, .width = 23, .height = 16 },    /* icon_btn_Keyboard@C1_D1, 1100 */
    { .dataOffset = 402336, .properties = 12, .width = 23, .height = 16 },    /* icon_btn_Keyboard@C1_D2, 1100 */
    { .dataOffset = 403072, .properties = 12, .width = 23, .height = 16 },    /* icon_btn_Keyboard@C1_D3, 1100 */
    { .dataOffset = 403808, .properties = 12, .width = 23, .height = 16 },    /* icon_btn_Keyboard@C1_D4, 1100 */
    { .dataOffset = 404544, .properties = 12, .width = 16, .height = 4 },    /* icon_btn_minus@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_MINUS__C000_D001, 11 */
    { .dataOffset = 404672, .properties = 12, .width = 16, .height = 4 },    /* icon_btn_minus@C0_D2, 1100 */
    { .dataOffset = 404800, .properties = 12, .width = 16, .height = 4 },    /* icon_btn_minus@C0_D3, 1100 */
    { .dataOffset = 404928, .properties = 12, .width = 16, .height = 4 },    /* icon_btn_minus@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_MINUS__C001_D000, 11 */
    { .dataOffset = 405056, .properties = 12, .width = 16, .height = 4 },    /* icon_btn_minus@C1_D1, 1100 */
    { .dataOffset = 405184, .properties = 12, .width = 16, .height = 4 },    /* icon_btn_minus@C1_D2, 1100 */
    { .dataOffset = 405312, .properties = 12, .width = 16, .height = 4 },    /* icon_btn_minus@C1_D3, 1100 */
    { .dataOffset = 405440, .properties = 12, .width = 16, .height = 4 },    /* icon_btn_minus@C1_D4, 1100 */
    { .dataOffset = 405568, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Palette@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_PALETTE__C000_D001, 11 */
    { .dataOffset = 406536, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Palette@C0_D2, 1100 */
    { .dataOffset = 407504, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Palette@C0_D3, 1100 */
    { .dataOffset = 408472, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Palette@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_PALETTE__C001_D000, 11 */
    { .dataOffset = 409440, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Palette@C1_D1, 1100 */
    { .dataOffset = 410408, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Palette@C1_D2, 1100 */
    { .dataOffset = 411376, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Palette@C1_D3, 1100 */
    { .dataOffset = 412344, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Palette@C1_D4, 1100 */
    { .dataOffset = 413312, .properties = 12, .width = 16, .height = 16 },    /* icon_btn_plus@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_PLUS__C000_D001, 11 */
    { .dataOffset = 413824, .properties = 12, .width = 16, .height = 16 },    /* icon_btn_plus@C0_D2, 1100 */
    { .dataOffset = 414336, .properties = 12, .width = 16, .height = 16 },    /* icon_btn_plus@C0_D3, 1100 */
    { .dataOffset = 414848, .properties = 12, .width = 16, .height = 16 },    /* icon_btn_plus@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_PLUS__C001_D000, 11 */
    { .dataOffset = 415360, .properties = 12, .width = 16, .height = 16 },    /* icon_btn_plus@C1_D1, 1100 */
    { .dataOffset = 415872, .properties = 12, .width = 16, .height = 16 },    /* icon_btn_plus@C1_D2, 1100 */
    { .dataOffset = 416384, .properties = 12, .width = 16, .height = 16 },    /* icon_btn_plus@C1_D3, 1100 */
    { .dataOffset = 416896, .properties = 12, .width = 16, .height = 16 },    /* icon_btn_plus@C1_D4, 1100 */
    { .dataOffset = 417408, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Sliders@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_SLIDERS__C000_D001, 11 */
    { .dataOffset = 418376, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Sliders@C0_D2, 1100 */
    { .dataOffset = 419344, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Sliders@C0_D3, 1100 */
    { .dataOffset = 420312, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Sliders@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_SLIDERS__C001_D000, 11 */
    { .dataOffset = 421280, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Sliders@C1_D1, 1100 */
    { .dataOffset = 422248, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Sliders@C1_D2, 1100 */
    { .dataOffset = 423216, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Sliders@C1_D3, 1100 */
    { .dataOffset = 424184, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Sliders@C1_D4, 1100 */
    { .dataOffset = 425152, .properties = 12, .width = 25, .height = 18 },    /* icon_btn_Wifi@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_WIFI__C000_D001, 11 */
    { .dataOffset = 426052, .properties = 12, .width = 25, .height = 18 },    /* icon_btn_Wifi@C0_D2, 1100 */
    { .dataOffset = 426952, .properties = 12, .width = 25, .height = 18 },    /* icon_btn_Wifi@C0_D3, 1100 */
    { .dataOffset = 427852, .properties = 12, .width = 25, .height = 18 },    /* icon_btn_Wifi@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_WIFI__C001_D000, 11 */
    { .dataOffset = 428752, .properties = 12, .width = 25, .height = 18 },    /* icon_btn_Wifi@C1_D1, 1100 */
    { .dataOffset = 429652, .properties = 12, .width = 25, .height = 18 },    /* icon_btn_Wifi@C1_D2, 1100 */
    { .dataOffset = 430552, .properties = 12, .width = 25, .height = 18 },    /* icon_btn_Wifi@C1_D3, 1100 */
    { .dataOffset = 431452, .properties = 12, .width = 25, .height = 18 },    /* icon_btn_Wifi@C1_D4, 1100 */
    { .dataOffset = 432352, .properties = 12, .width = 13, .height = 4 },    /* icon_dft_Arrow_down@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_DFT_ARROW_DOWN__C000_D001, 11 */
    { .dataOffset = 432456, .properties = 12, .width = 13, .height = 4 },    /* icon_dft_Arrow_down@C0_D2, 1100 */
    { .dataOffset = 432560, .properties = 12, .width = 13, .height = 4 },    /* icon_dft_Arrow_down@C0_D3, 1100 */
    { .dataOffset = 432664, .properties = 12, .width = 13, .height = 4 },    /* icon_dft_Arrow_down@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_DFT_ARROW_DOWN__C001_D000, 11 */
    { .dataOffset = 432768, .properties = 12, .width = 13, .height = 4 },    /* icon_dft_Arrow_down@C1_D1, 1100 */
    { .dataOffset = 432872, .properties = 12, .width = 13, .height = 4 },    /* icon_dft_Arrow_down@C1_D2, 1100 */
    { .dataOffset = 432976, .properties = 12, .width = 13, .height = 4 },    /* icon_dft_Arrow_down@C1_D3, 1100 */
    { .dataOffset = 433080, .properties = 12, .width = 13, .height = 4 },    /* icon_dft_Arrow_down@C1_D4, 1100 */
    { .dataOffset = 433184, .properties = 12, .width = 12, .height = 4 },    /* icon_dft_Arrow_up@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_DFT_ARROW_UP__C000_D001, 11 */
    { .dataOffset = 433280, .properties = 12, .width = 12, .height = 4 },    /* icon_dft_Arrow_up@C0_D2, 1100 */
    { .dataOffset = 433376, .properties = 12, .width = 12, .height = 4 },    /* icon_dft_Arrow_up@C0_D3, 1100 */
    { .dataOffset = 433472, .properties = 12, .width = 12, .height = 4 },    /* icon_dft_Arrow_up@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_DFT_ARROW_UP__C001_D000, 11 */
    { .dataOffset = 433568, .properties = 12, .width = 12, .height = 4 },    /* icon_dft_Arrow_up@C1_D1, 1100 */
    { .dataOffset = 433664, .properties = 12, .width = 12, .height = 4 },    /* icon_dft_Arrow_up@C1_D2, 1100 */
    { .dataOffset = 433760, .properties = 12, .width = 12, .height = 4 },    /* icon_dft_Arrow_up@C1_D3, 1100 */
    { .dataOffset = 433856, .properties = 12, .width = 12, .height = 4 },    /* icon_dft_Arrow_up@C1_D4, 1100 */
    { .dataOffset = 433952, .properties = 12, .width = 20, .height = 20 },    /* icon_dft_Checkbox-Checked@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_DFT_CHECKBOX_CHECKED__C000_D001, 11 */
    { .dataOffset = 434752, .properties = 12, .width = 20, .height = 20 },    /* icon_dft_Checkbox-Checked@C0_D2, 1100 */
    { .dataOffset = 435552, .properties = 12, .width = 20, .height = 20 },    /* icon_dft_Checkbox-Checked@C0_D3, 1100 */
    { .dataOffset = 436352, .properties = 12, .width = 20, .height = 20 },    /* icon_dft_Checkbox-Checked@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_DFT_CHECKBOX_CHECKED__C001_D000, 11 */
    { .dataOffset = 437152, .properties = 12, .width = 20, .height = 20 },    /* icon_dft_Checkbox-Checked@C1_D1, 1100 */
    { .dataOffset = 437952, .properties = 12, .width = 20, .height = 20 },    /* icon_dft_Checkbox-Checked@C1_D2, 1100 */
    { .dataOffset = 438752, .properties = 12, .width = 20, .height = 20 },    /* icon_dft_Checkbox-Checked@C1_D3, 1100 */
    { .dataOffset = 439552, .properties = 12, .width = 20, .height = 20 },    /* icon_dft_Checkbox-Checked@C1_D4, 1100 */
    { .dataOffset = 440352, .properties = 12, .width = 20, .height = 20 },    /* icon_dft_Checkbox-UnChecked@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_DFT_CHECKBOX_UNCHECKED__C000_D001, 11 */
    { .dataOffset = 441152, .properties = 12, .width = 20, .height = 20 },    /* icon_dft_Checkbox-UnChecked@C0_D2, 1100 */
    { .dataOffset = 441952, .properties = 12, .width = 20, .height = 20 },    /* icon_dft_Checkbox-UnChecked@C0_D3, 1100 */
    { .dataOffset = 442752, .properties = 12, .width = 20, .height = 20 },    /* icon_dft_Checkbox-UnChecked@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_DFT_CHECKBOX_UNCHECKED__C001_D000, 11 */
    { .dataOffset = 443552, .properties = 12, .width = 20, .height = 20 },    /* icon_dft_Checkbox-UnChecked@C1_D1, 1100 */
    { .dataOffset = 444352, .properties = 12, .width = 20, .height = 20 },    /* icon_dft_Checkbox-UnChecked@C1_D2, 1100 */
    { .dataOffset = 445152, .properties = 12, .width = 20, .height = 20 },    /* icon_dft_Checkbox-UnChecked@C1_D3, 1100 */
    { .dataOffset = 445952, .properties = 12, .width = 20, .height = 20 },    /* icon_dft_Checkbox-UnChecked@C1_D4, 1100 */
    { .dataOffset = 446752, .properties = 12, .width = 16, .height = 13 },    /* icon_dft_Checkmark@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_DFT_CHECKMARK__C000_D001, 11 */
    { .dataOffset = 447168, .properties = 12, .width = 16, .height = 13 },    /* icon_dft_Checkmark@C0_D2, 1100 */
    { .dataOffset = 447584, .properties = 12, .width = 16, .height = 13 },    /* icon_dft_Checkmark@C0_D3, 1100 */
    { .dataOffset = 448000, .properties = 12, .width = 16, .height = 13 },    /* icon_dft_Checkmark@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_DFT_CHECKMARK__C001_D000, 11 */
    { .dataOffset = 448416, .properties = 12, .width = 16, .height = 13 },    /* icon_dft_Checkmark@C1_D1, 1100 */
    { .dataOffset = 448832, .properties = 12, .width = 16, .height = 13 },    /* icon_dft_Checkmark@C1_D2, 1100 */
    { .dataOffset = 449248, .properties = 12, .width = 16, .height = 13 },    /* icon_dft_Checkmark@C1_D3, 1100 */
    { .dataOffset = 449664, .properties = 12, .width = 16, .height = 13 },    /* icon_dft_Checkmark@C1_D4, 1100 */
    { .dataOffset = 450080, .properties = 12, .width = 16, .height = 4 },    /* icon_dft_minus@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_DFT_MINUS__C000_D001, 11 */
    { .dataOffset = 450208, .properties = 12, .width = 16, .height = 4 },    /* icon_dft_minus@C0_D2, 1100 */
    { .dataOffset = 450336, .properties = 12, .width = 16, .height = 4 },    /* icon_dft_minus@C0_D3, 1100 */
    { .dataOffset = 450464, .properties = 12, .width = 16, .height = 4 },    /* icon_dft_minus@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_DFT_MINUS__C001_D000, 11 */
    { .dataOffset = 450592, .properties = 12, .width = 16, .height = 4 },    /* icon_dft_minus@C1_D1, 1100 */
    { .dataOffset = 450720, .properties = 12, .width = 16, .height = 4 },    /* icon_dft_minus@C1_D2, 1100 */
    { .dataOffset = 450848, .properties = 12, .width = 16, .height = 4 },    /* icon_dft_minus@C1_D3, 1100 */
    { .dataOffset = 450976, .properties = 12, .width = 16, .height = 4 },    /* icon_dft_minus@C1_D4, 1100 */
    { .dataOffset = 451104, .properties = 12, .width = 16, .height = 16 },    /* icon_dft_plus@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_DFT_PLUS__C000_D001, 11 */
    { .dataOffset = 451616, .properties = 12, .width = 16, .height = 16 },    /* icon_dft_plus@C0_D2, 1100 */
    { .dataOffset = 452128, .properties = 12, .width = 16, .height = 16 },    /* icon_dft_plus@C0_D3, 1100 */
    { .dataOffset = 452640, .properties = 12, .width = 16, .height = 16 },    /* icon_dft_plus@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_DFT_PLUS__C001_D000, 11 */
    { .dataOffset = 453152, .properties = 12, .width = 16, .height = 16 },    /* icon_dft_plus@C1_D1, 1100 */
    { .dataOffset = 453664, .properties = 12, .width = 16, .height = 16 },    /* icon_dft_plus@C1_D2, 1100 */
    { .dataOffset = 454176, .properties = 12, .width = 16, .height = 16 },    /* icon_dft_plus@C1_D3, 1100 */
    { .dataOffset = 454688, .properties = 12, .width = 16, .height = 16 },    /* icon_dft_plus@C1_D4, 1100 */
    { .dataOffset = 455200, .properties = 12, .width = 18, .height = 18 },    /* icon_dft_Radio-Button-Checked@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_DFT_RADIO_BUTTON_CHECKED__C000_D001, 11 */
    { .dataOffset = 455848, .properties = 12, .width = 18, .height = 18 },    /* icon_dft_Radio-Button-Checked@C0_D2, 1100 */
    { .dataOffset = 456496, .properties = 12, .width = 18, .height = 18 },    /* icon_dft_Radio-Button-Checked@C0_D3, 1100 */
    { .dataOffset = 457144, .properties = 12, .width = 18, .height = 18 },    /* icon_dft_Radio-Button-Checked@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_DFT_RADIO_BUTTON_CHECKED__C001_D000, 11 */
    { .dataOffset = 457792, .properties = 12, .width = 18, .height = 18 },    /* icon_dft_Radio-Button-Checked@C1_D1, 1100 */
    { .dataOffset = 458440, .properties = 12, .width = 18, .height = 18 },    /* icon_dft_Radio-Button-Checked@C1_D2, 1100 */
    { .dataOffset = 459088, .properties = 12, .width = 18, .height = 18 },    /* icon_dft_Radio-Button-Checked@C1_D3, 1100 */
    { .dataOffset = 459736, .properties = 12, .width = 18, .height = 18 },    /* icon_dft_Radio-Button-Checked@C1_D4, 1100 */
    { .dataOffset = 460384, .properties = 12, .width = 18, .height = 18 },    /* icon_dft_Radio-Button-UnChecked@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_DFT_RADIO_BUTTON_UNCHECKED__C000_D001, 11 */
    { .dataOffset = 461032, .properties = 12, .width = 18, .height = 18 },    /* icon_dft_Radio-Button-UnChecked@C0_D2, 1100 */
    { .dataOffset = 461680, .properties = 12, .width = 18, .height = 18 },    /* icon_dft_Radio-Button-UnChecked@C0_D3, 1100 */
    { .dataOffset = 462328, .properties = 12, .width = 18, .height = 18 },    /* icon_dft_Radio-Button-UnChecked@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_DFT_RADIO_BUTTON_UNCHECKED__C001_D000, 11 */
    { .dataOffset = 462976, .properties = 12, .width = 18, .height = 18 },    /* icon_dft_Radio-Button-UnChecked@C1_D1, 1100 */
    { .dataOffset = 463624, .properties = 12, .width = 18, .height = 18 },    /* icon_dft_Radio-Button-UnChecked@C1_D2, 1100 */
    { .dataOffset = 464272, .properties = 12, .width = 18, .height = 18 },    /* icon_dft_Radio-Button-UnChecked@C1_D3, 1100 */
    { .dataOffset = 464920, .properties = 12, .width = 18, .height = 18 },    /* icon_dft_Radio-Button-UnChecked@C1_D4, 1100 */
    { .dataOffset = 465568, .properties = 4, .width = 16, .height = 18 },    /* icon_header_Bell@C0, 100 */
    { .dataOffset = 466144, .properties = 4, .width = 16, .height = 18 },    /* icon_header_Bell@C1, 100 */
    { .dataOffset = 466720, .properties = 4, .width = 20, .height = 20 },    /* icon_header_Clock@C0, 100 */
    { .dataOffset = 467520, .properties = 4, .width = 20, .height = 20 },    /* icon_header_Clock@C1, 100 */
    { .dataOffset = 468320, .properties = 4, .width = 25, .height = 18 },    /* icon_header_Wifi@C0, 100 */
    { .dataOffset = 469220, .properties = 4, .width = 25, .height = 18 },    /* icon_header_Wifi@C1, 100 */
    { .dataOffset = 470120, .properties = 0, .width = 128, .height = 128 },    /* IRL_Logo 128, 0 */
    { .dataOffset = 502888, .properties = 0, .width = 48, .height = 48 },    /* IRL_Logo_48, 0 */
    { .dataOffset = 507496, .properties = 4, .width = 480, .height = 236 },    /* Keyboard_lc@C0, 100 */
    { .dataOffset = 734056, .properties = 4, .width = 480, .height = 236 },    /* Keyboard_lc@C1, 100 */
    { .dataOffset = 960616, .properties = 4, .width = 480, .height = 236 },    /* Keyboard_num@C0, 100 */
    { .dataOffset = 1187176, .properties = 4, .width = 480, .height = 236 },    /* Keyboard_num@C1, 100 */
    { .dataOffset = 1413736, .properties = 4, .width = 480, .height = 84 },    /* Keyboard_textbox@C0, 100 */
    { .dataOffset = 1494376, .properties = 4, .width = 480, .height = 84 },    /* Keyboard_textbox@C1, 100 */
    { .dataOffset = 1575016, .properties = 4, .width = 480, .height = 236 },    /* Keyboard_uc@C0, 100 */
    { .dataOffset = 1801576, .properties = 4, .width = 480, .height = 236 },    /* Keyboard_uc@C1, 100 */
    { .dataOffset = 2028136, .properties = 5, .width = 53, .height = 22 },    /* Text_button_ACCENT_COLOR@A0_C0, 101 */
    { .dataOffset = 2030468, .properties = 5, .width = 53, .height = 22 },    /* Text_button_ACCENT_COLOR@A0_C1, 101 */
    { .dataOffset = 2032800, .properties = 5, .width = 62, .height = 22 },    /* Text_button_ACCENT_COLOR@A1_C0, 101 */
    { .dataOffset = 2035528, .properties = 5, .width = 62, .height = 22 },    /* Text_button_ACCENT_COLOR@A1_C1, 101 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TEXT_BUTTON_ACCENT_COLOR__A002_C000, 11 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TEXT_BUTTON_ACCENT_COLOR__A002_C001, 11 */
    { .dataOffset = 2038256, .properties = 5, .width = 47, .height = 22 },    /* Text_button_ALARM@A0_C0, 101 */
    { .dataOffset = 2040324, .properties = 5, .width = 47, .height = 22 },    /* Text_button_ALARM@A0_C1, 101 */
    { .dataOffset = 2042392, .properties = 5, .width = 47, .height = 22 },    /* Text_button_ALARM@A1_C0, 101 */
    { .dataOffset = 2044460, .properties = 5, .width = 47, .height = 22 },    /* Text_button_ALARM@A1_C1, 101 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TEXT_BUTTON_ALARM__A002_C000, 11 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TEXT_BUTTON_ALARM__A002_C001, 11 */
    { .dataOffset = 2046528, .properties = 5, .width = 86, .height = 22 },    /* Text_button_BRIGHTNESS@A0_C0, 101 */
    { .dataOffset = 2050312, .properties = 5, .width = 86, .height = 22 },    /* Text_button_BRIGHTNESS@A0_C1, 101 */
    { .dataOffset = 2054096, .properties = 5, .width = 88, .height = 22 },    /* Text_button_BRIGHTNESS@A1_C0, 101 */
    { .dataOffset = 2057968, .properties = 5, .width = 88, .height = 22 },    /* Text_button_BRIGHTNESS@A1_C1, 101 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TEXT_BUTTON_BRIGHTNESS__A002_C000, 11 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TEXT_BUTTON_BRIGHTNESS__A002_C001, 11 */
    { .dataOffset = 2061840, .properties = 5, .width = 37, .height = 22 },    /* Text_button_DATE@A0_C0, 101 */
    { .dataOffset = 2063468, .properties = 5, .width = 37, .height = 22 },    /* Text_button_DATE@A0_C1, 101 */
    { .dataOffset = 2065096, .properties = 5, .width = 52, .height = 22 },    /* Text_button_DATE@A1_C0, 101 */
    { .dataOffset = 2067384, .properties = 5, .width = 52, .height = 22 },    /* Text_button_DATE@A1_C1, 101 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TEXT_BUTTON_DATE__A002_C000, 11 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TEXT_BUTTON_DATE__A002_C001, 11 */
    { .dataOffset = 2069672, .properties = 5, .width = 29, .height = 22 },    /* Text_button_INFO@A0_C0, 101 */
    { .dataOffset = 2070948, .properties = 5, .width = 29, .height = 22 },    /* Text_button_INFO@A0_C1, 101 */
    { .dataOffset = 2072224, .properties = 5, .width = 29, .height = 22 },    /* Text_button_INFO@A1_C0, 101 */
    { .dataOffset = 2073500, .properties = 5, .width = 29, .height = 22 },    /* Text_button_INFO@A1_C1, 101 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TEXT_BUTTON_INFO__A002_C000, 11 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TEXT_BUTTON_INFO__A002_C001, 11 */
    { .dataOffset = 2074776, .properties = 5, .width = 117, .height = 22 },    /* Text_button_INTERN_TEMP@A0_C0, 101 */
    { .dataOffset = 2079924, .properties = 5, .width = 117, .height = 22 },    /* Text_button_INTERN_TEMP@A0_C1, 101 */
    { .dataOffset = 2085072, .properties = 5, .width = 112, .height = 22 },    /* Text_button_INTERN_TEMP@A1_C0, 101 */
    { .dataOffset = 2090000, .properties = 5, .width = 112, .height = 22 },    /* Text_button_INTERN_TEMP@A1_C1, 101 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TEXT_BUTTON_INTERN_TEMP__A002_C000, 11 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TEXT_BUTTON_INTERN_TEMP__A002_C001, 11 */
    { .dataOffset = 2094928, .properties = 5, .width = 77, .height = 22 },    /* Text_button_KEYBOARD@A0_C0, 101 */
    { .dataOffset = 2098316, .properties = 5, .width = 77, .height = 22 },    /* Text_button_KEYBOARD@A0_C1, 101 */
    { .dataOffset = 2101704, .properties = 5, .width = 103, .height = 22 },    /* Text_button_KEYBOARD@A1_C0, 101 */
    { .dataOffset = 2106236, .properties = 5, .width = 103, .height = 22 },    /* Text_button_KEYBOARD@A1_C1, 101 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TEXT_BUTTON_KEYBOARD__A002_C000, 11 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TEXT_BUTTON_KEYBOARD__A002_C001, 11 */
    { .dataOffset = 2110768, .properties = 5, .width = 81, .height = 22 },    /* Text_button_LANGUAGE@A0_C0, 101 */
    { .dataOffset = 2114332, .properties = 5, .width = 81, .height = 22 },    /* Text_button_LANGUAGE@A0_C1, 101 */
    { .dataOffset = 2117896, .properties = 5, .width = 35, .height = 22 },    /* Text_button_LANGUAGE@A1_C0, 101 */
    { .dataOffset = 2119436, .properties = 5, .width = 35, .height = 22 },    /* Text_button_LANGUAGE@A1_C1, 101 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TEXT_BUTTON_LANGUAGE__A002_C000, 11 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TEXT_BUTTON_LANGUAGE__A002_C001, 11 */
    { .dataOffset = 2120976, .properties = 5, .width = 113, .height = 22 },    /* Text_button_MEASUREMENT@A0_C0, 101 */
    { .dataOffset = 2125948, .properties = 5, .width = 113, .height = 22 },    /* Text_button_MEASUREMENT@A0_C1, 101 */
    { .dataOffset = 2130920, .properties = 5, .width = 64, .height = 22 },    /* Text_button_MEASUREMENT@A1_C0, 101 */
    { .dataOffset = 2133736, .properties = 5, .width = 64, .height = 22 },    /* Text_button_MEASUREMENT@A1_C1, 101 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TEXT_BUTTON_MEASUREMENT__A002_C000, 11 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TEXT_BUTTON_MEASUREMENT__A002_C001, 11 */
    { .dataOffset = 2136552, .properties = 5, .width = 66, .height = 22 },    /* Text_button_SETTINGS@A0_C0, 101 */
    { .dataOffset = 2139456, .properties = 5, .width = 66, .height = 22 },    /* Text_button_SETTINGS@A0_C1, 101 */
    { .dataOffset = 2142360, .properties = 5, .width = 92, .height = 22 },    /* Text_button_SETTINGS@A1_C0, 101 */
    { .dataOffset = 2146408, .properties = 5, .width = 92, .height = 22 },    /* Text_button_SETTINGS@A1_C1, 101 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TEXT_BUTTON_SETTINGS__A002_C000, 11 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TEXT_BUTTON_SETTINGS__A002_C001, 11 */
    { .dataOffset = 2150456, .properties = 5, .width = 48, .height = 22 },    /* Text_button_SETUP@A0_C0, 101 */
    { .dataOffset = 2152568, .properties = 5, .width = 48, .height = 22 },    /* Text_button_SETUP@A0_C1, 101 */
    { .dataOffset = 2154680, .properties = 5, .width = 53, .height = 22 },    /* Text_button_SETUP@A1_C0, 101 */
    { .dataOffset = 2157012, .properties = 5, .width = 53, .height = 22 },    /* Text_button_SETUP@A1_C1, 101 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TEXT_BUTTON_SETUP__A002_C000, 11 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TEXT_BUTTON_SETUP__A002_C001, 11 */
    { .dataOffset = 2159344, .properties = 5, .width = 57, .height = 22 },    /* Text_button_THEME@A0_C0, 101 */
    { .dataOffset = 2161852, .properties = 5, .width = 57, .height = 22 },    /* Text_button_THEME@A0_C1, 101 */
    { .dataOffset = 2164360, .properties = 5, .width = 57, .height = 22 },    /* Text_button_THEME@A1_C0, 101 */
    { .dataOffset = 2166868, .properties = 5, .width = 57, .height = 22 },    /* Text_button_THEME@A1_C1, 101 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TEXT_BUTTON_THEME__A002_C000, 11 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TEXT_BUTTON_THEME__A002_C001, 11 */
    { .dataOffset = 2169376, .properties = 5, .width = 41, .height = 22 },    /* Text_button_TIME@A0_C0, 101 */
    { .dataOffset = 2171180, .properties = 5, .width = 41, .height = 22 },    /* Text_button_TIME@A0_C1, 101 */
    { .dataOffset = 2172984, .properties = 5, .width = 29, .height = 22 },    /* Text_button_TIME@A1_C0, 101 */
    { .dataOffset = 2174260, .properties = 5, .width = 29, .height = 22 },    /* Text_button_TIME@A1_C1, 101 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TEXT_BUTTON_TIME__A002_C000, 11 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TEXT_BUTTON_TIME__A002_C001, 11 */
    { .dataOffset = 2175536, .properties = 5, .width = 41, .height = 22 },    /* Text_button_UNITS@A0_C0, 101 */
    { .dataOffset = 2177340, .properties = 5, .width = 41, .height = 22 },    /* Text_button_UNITS@A0_C1, 101 */
    { .dataOffset = 2179144, .properties = 5, .width = 82, .height = 22 },    /* Text_button_UNITS@A1_C0, 101 */
    { .dataOffset = 2182752, .properties = 5, .width = 82, .height = 22 },    /* Text_button_UNITS@A1_C1, 101 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TEXT_BUTTON_UNITS__A002_C000, 11 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TEXT_BUTTON_UNITS__A002_C001, 11 */
    { .dataOffset = 2186360, .properties = 5, .width = 114, .height = 25 },    /* Text-Dft_ACCENT_COLOR@A0_C0, 101 */
    { .dataOffset = 2192060, .properties = 5, .width = 114, .height = 25 },    /* Text-Dft_ACCENT_COLOR@A0_C1, 101 */
    { .dataOffset = 2197760, .properties = 5, .width = 108, .height = 25 },    /* Text-Dft_ACCENT_COLOR@A1_C0, 101 */
    { .dataOffset = 2203160, .properties = 5, .width = 108, .height = 25 },    /* Text-Dft_ACCENT_COLOR@A1_C1, 101 */
    { .dataOffset = 2208560, .properties = 5, .width = 110, .height = 25 },    /* Text-Dft_ACCENT_COLOR@A2_C0, 101 */
    { .dataOffset = 2214060, .properties = 5, .width = 110, .height = 25 },    /* Text-Dft_ACCENT_COLOR@A2_C1, 101 */
    { .dataOffset = 2219560, .properties = 5, .width = 141, .height = 25 },    /* Text-Dft_ACTIVATE_ALARM@A0_C0, 101 */
    { .dataOffset = 2226610, .properties = 5, .width = 141, .height = 25 },    /* Text-Dft_ACTIVATE_ALARM@A0_C1, 101 */
    { .dataOffset = 2233660, .properties = 5, .width = 143, .height = 25 },    /* Text-Dft_ACTIVATE_ALARM@A1_C0, 101 */
    { .dataOffset = 2240810, .properties = 5, .width = 143, .height = 25 },    /* Text-Dft_ACTIVATE_ALARM@A1_C1, 101 */
    { .dataOffset = 2247960, .properties = 5, .width = 159, .height = 25 },    /* Text-Dft_ACTIVATE_ALARM@A2_C0, 101 */
    { .dataOffset = 2255910, .properties = 5, .width = 159, .height = 25 },    /* Text-Dft_ACTIVATE_ALARM@A2_C1, 101 */
    { .dataOffset = 2263860, .properties = 5, .width = 70, .height = 25 },    /* Text-Dft_ALARM@A0_C0, 101 */
    { .dataOffset = 2267360, .properties = 5, .width = 70, .height = 25 },    /* Text-Dft_ALARM@A0_C1, 101 */
    { .dataOffset = 2270860, .properties = 5, .width = 70, .height = 25 },    /* Text-Dft_ALARM@A1_C0, 101 */
    { .dataOffset = 2274360, .properties = 5, .width = 70, .height = 25 },    /* Text-Dft_ALARM@A1_C1, 101 */
    { .dataOffset = 2277860, .properties = 5, .width = 53, .height = 25 },    /* Text-Dft_ALARM@A2_C0, 101 */
    { .dataOffset = 2280510, .properties = 5, .width = 53, .height = 25 },    /* Text-Dft_ALARM@A2_C1, 101 */
    { .dataOffset = 2283160, .properties = 5, .width = 112, .height = 25 },    /* Text-Dft_CURSOR_COLOR@A0_C0, 101 */
    { .dataOffset = 2288760, .properties = 5, .width = 112, .height = 25 },    /* Text-Dft_CURSOR_COLOR@A0_C1, 101 */
    { .dataOffset = 2294360, .properties = 5, .width = 112, .height = 25 },    /* Text-Dft_CURSOR_COLOR@A1_C0, 101 */
    { .dataOffset = 2299960, .properties = 5, .width = 112, .height = 25 },    /* Text-Dft_CURSOR_COLOR@A1_C1, 101 */
    { .dataOffset = 2305560, .properties = 5, .width = 169, .height = 25 },    /* Text-Dft_CURSOR_COLOR@A2_C0, 101 */
    { .dataOffset = 2314010, .properties = 5, .width = 169, .height = 25 },    /* Text-Dft_CURSOR_COLOR@A2_C1, 101 */
    { .dataOffset = 2322460, .properties = 5, .width = 21, .height = 25 },    /* Text-Dft_DEG_CEL@A0_C0, 101 */
    { .dataOffset = 2323510, .properties = 5, .width = 21, .height = 25 },    /* Text-Dft_DEG_CEL@A0_C1, 101 */
    { .dataOffset = 2324560, .properties = 5, .width = 21, .height = 25 },    /* Text-Dft_DEG_CEL@A1_C0, 101 */
    { .dataOffset = 2325610, .properties = 5, .width = 21, .height = 25 },    /* Text-Dft_DEG_CEL@A1_C1, 101 */
    { .dataOffset = 2326660, .properties = 5, .width = 21, .height = 25 },    /* Text-Dft_DEG_CEL@A2_C0, 101 */
    { .dataOffset = 2327710, .properties = 5, .width = 21, .height = 25 },    /* Text-Dft_DEG_CEL@A2_C1, 101 */
    { .dataOffset = 2328760, .properties = 5, .width = 19, .height = 25 },    /* Text-Dft_DEG_FAR@A0_C0, 101 */
    { .dataOffset = 2329710, .properties = 5, .width = 19, .height = 25 },    /* Text-Dft_DEG_FAR@A0_C1, 101 */
    { .dataOffset = 2330660, .properties = 5, .width = 19, .height = 25 },    /* Text-Dft_DEG_FAR@A1_C0, 101 */
    { .dataOffset = 2331610, .properties = 5, .width = 19, .height = 25 },    /* Text-Dft_DEG_FAR@A1_C1, 101 */
    { .dataOffset = 2332560, .properties = 5, .width = 19, .height = 25 },    /* Text-Dft_DEG_FAR@A2_C0, 101 */
    { .dataOffset = 2333510, .properties = 5, .width = 19, .height = 25 },    /* Text-Dft_DEG_FAR@A2_C1, 101 */
    { .dataOffset = 2334460, .properties = 5, .width = 104, .height = 25 },    /* Text-Dft_DUTCH@A0_C0, 101 */
    { .dataOffset = 2339660, .properties = 5, .width = 104, .height = 25 },    /* Text-Dft_DUTCH@A0_C1, 101 */
    { .dataOffset = 2344860, .properties = 5, .width = 104, .height = 25 },    /* Text-Dft_DUTCH@A1_C0, 101 */
    { .dataOffset = 2350060, .properties = 5, .width = 104, .height = 25 },    /* Text-Dft_DUTCH@A1_C1, 101 */
    { .dataOffset = 2355260, .properties = 5, .width = 104, .height = 25 },    /* Text-Dft_DUTCH@A2_C0, 101 */
    { .dataOffset = 2360460, .properties = 5, .width = 104, .height = 25 },    /* Text-Dft_DUTCH@A2_C1, 101 */
    { .dataOffset = 2365660, .properties = 5, .width = 66, .height = 25 },    /* Text-Dft_ENGLISH@A0_C0, 101 */
    { .dataOffset = 2368960, .properties = 5, .width = 66, .height = 25 },    /* Text-Dft_ENGLISH@A0_C1, 101 */
    { .dataOffset = 2372260, .properties = 5, .width = 66, .height = 25 },    /* Text-Dft_ENGLISH@A1_C0, 101 */
    { .dataOffset = 2375560, .properties = 5, .width = 66, .height = 25 },    /* Text-Dft_ENGLISH@A1_C1, 101 */
    { .dataOffset = 2378860, .properties = 5, .width = 66, .height = 25 },    /* Text-Dft_ENGLISH@A2_C0, 101 */
    { .dataOffset = 2382160, .properties = 5, .width = 66, .height = 25 },    /* Text-Dft_ENGLISH@A2_C1, 101 */
    { .dataOffset = 2385460, .properties = 5, .width = 74, .height = 25 },    /* Text-Dft_GERMAN@A0_C0, 101 */
    { .dataOffset = 2389160, .properties = 5, .width = 74, .height = 25 },    /* Text-Dft_GERMAN@A0_C1, 101 */
    { .dataOffset = 2392860, .properties = 5, .width = 74, .height = 25 },    /* Text-Dft_GERMAN@A1_C0, 101 */
    { .dataOffset = 2396560, .properties = 5, .width = 74, .height = 25 },    /* Text-Dft_GERMAN@A1_C1, 101 */
    { .dataOffset = 2400260, .properties = 5, .width = 74, .height = 25 },    /* Text-Dft_GERMAN@A2_C0, 101 */
    { .dataOffset = 2403960, .properties = 5, .width = 74, .height = 25 },    /* Text-Dft_GERMAN@A2_C1, 101 */
    { .dataOffset = 2407660, .properties = 5, .width = 129, .height = 25 },    /* Text-Dft_INTERN_TEMP@A0_C0, 101 */
    { .dataOffset = 2414110, .properties = 5, .width = 129, .height = 25 },    /* Text-Dft_INTERN_TEMP@A0_C1, 101 */
    { .dataOffset = 2420560, .properties = 5, .width = 124, .height = 25 },    /* Text-Dft_INTERN_TEMP@A1_C0, 101 */
    { .dataOffset = 2426760, .properties = 5, .width = 124, .height = 25 },    /* Text-Dft_INTERN_TEMP@A1_C1, 101 */
    { .dataOffset = 2432960, .properties = 5, .width = 179, .height = 25 },    /* Text-Dft_INTERN_TEMP@A2_C0, 101 */
    { .dataOffset = 2441910, .properties = 5, .width = 179, .height = 25 },    /* Text-Dft_INTERN_TEMP@A2_C1, 101 */
    { .dataOffset = 2450860, .properties = 5, .width = 125, .height = 25 },    /* Text-Dft_MEASUREMENT@A0_C0, 101 */
    { .dataOffset = 2457110, .properties = 5, .width = 125, .height = 25 },    /* Text-Dft_MEASUREMENT@A0_C1, 101 */
    { .dataOffset = 2463360, .properties = 5, .width = 71, .height = 25 },    /* Text-Dft_MEASUREMENT@A1_C0, 101 */
    { .dataOffset = 2466910, .properties = 5, .width = 71, .height = 25 },    /* Text-Dft_MEASUREMENT@A1_C1, 101 */
    { .dataOffset = 2470460, .properties = 5, .width = 82, .height = 25 },    /* Text-Dft_MEASUREMENT@A2_C0, 101 */
    { .dataOffset = 2474560, .properties = 5, .width = 82, .height = 25 },    /* Text-Dft_MEASUREMENT@A2_C1, 101 */
    { .dataOffset = 2478660, .properties = 5, .width = 113, .height = 25 },    /* Text-Dft_SET_ALARM_IN@A0_C0, 101 */
    { .dataOffset = 2484310, .properties = 5, .width = 113, .height = 25 },    /* Text-Dft_SET_ALARM_IN@A0_C1, 101 */
    { .dataOffset = 2489960, .properties = 5, .width = 80, .height = 25 },    /* Text-Dft_SET_ALARM_IN@A1_C0, 101 */
    { .dataOffset = 2493960, .properties = 5, .width = 80, .height = 25 },    /* Text-Dft_SET_ALARM_IN@A1_C1, 101 */
    { .dataOffset = 2497960, .properties = 5, .width = 125, .height = 25 },    /* Text-Dft_SET_ALARM_IN@A2_C0, 101 */
    { .dataOffset = 2504210, .properties = 5, .width = 125, .height = 25 },    /* Text-Dft_SET_ALARM_IN@A2_C1, 101 */
    { .dataOffset = 2510460, .properties = 5, .width = 43, .height = 25 },    /* Text-Dft_THEME_DARK@A0_C0, 101 */
    { .dataOffset = 2512610, .properties = 5, .width = 43, .height = 25 },    /* Text-Dft_THEME_DARK@A0_C1, 101 */
    { .dataOffset = 2514760, .properties = 5, .width = 66, .height = 25 },    /* Text-Dft_THEME_DARK@A1_C0, 101 */
    { .dataOffset = 2518060, .properties = 5, .width = 66, .height = 25 },    /* Text-Dft_THEME_DARK@A1_C1, 101 */
    { .dataOffset = 2521360, .properties = 5, .width = 62, .height = 25 },    /* Text-Dft_THEME_DARK@A2_C0, 101 */
    { .dataOffset = 2524460, .properties = 5, .width = 62, .height = 25 },    /* Text-Dft_THEME_DARK@A2_C1, 101 */
    { .dataOffset = 2527560, .properties = 5, .width = 44, .height = 25 },    /* Text-Dft_THEME_LIGHT@A0_C0, 101 */
    { .dataOffset = 2529760, .properties = 5, .width = 44, .height = 25 },    /* Text-Dft_THEME_LIGHT@A0_C1, 101 */
    { .dataOffset = 2531960, .properties = 5, .width = 43, .height = 25 },    /* Text-Dft_THEME_LIGHT@A1_C0, 101 */
    { .dataOffset = 2534110, .properties = 5, .width = 43, .height = 25 },    /* Text-Dft_THEME_LIGHT@A1_C1, 101 */
    { .dataOffset = 2536260, .properties = 5, .width = 43, .height = 25 },    /* Text-Dft_THEME_LIGHT@A2_C0, 101 */
    { .dataOffset = 2538410, .properties = 5, .width = 43, .height = 25 },    /* Text-Dft_THEME_LIGHT@A2_C1, 101 */
    { .dataOffset = 2540560, .properties = 5, .width = 46, .height = 25 },    /* Text-Dft_TIME_MM@A0_C0, 101 */
    { .dataOffset = 2542860, .properties = 5, .width = 46, .height = 25 },    /* Text-Dft_TIME_MM@A0_C1, 101 */
    { .dataOffset = 2545160, .properties = 5, .width = 46, .height = 25 },    /* Text-Dft_TIME_MM@A1_C0, 101 */
    { .dataOffset = 2547460, .properties = 5, .width = 46, .height = 25 },    /* Text-Dft_TIME_MM@A1_C1, 101 */
    { .dataOffset = 2549760, .properties = 5, .width = 46, .height = 25 },    /* Text-Dft_TIME_MM@A2_C0, 101 */
    { .dataOffset = 2552060, .properties = 5, .width = 46, .height = 25 },    /* Text-Dft_TIME_MM@A2_C1, 101 */
    { .dataOffset = 2554360, .properties = 5, .width = 58, .height = 27 },    /* Title_ALARM@A0_C0, 101 */
    { .dataOffset = 2557492, .properties = 5, .width = 58, .height = 27 },    /* Title_ALARM@A0_C1, 101 */
    { .dataOffset = 2560624, .properties = 5, .width = 58, .height = 27 },    /* Title_ALARM@A1_C0, 101 */
    { .dataOffset = 2563756, .properties = 5, .width = 58, .height = 27 },    /* Title_ALARM@A1_C1, 101 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TITLE_ALARM__A002_C000, 11 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TITLE_ALARM__A002_C001, 11 */
    { .dataOffset = 2566888, .properties = 5, .width = 105, .height = 27 },    /* Title_BRIGHTNESS@A0_C0, 101 */
    { .dataOffset = 2572558, .properties = 5, .width = 105, .height = 27 },    /* Title_BRIGHTNESS@A0_C1, 101 */
    { .dataOffset = 2578228, .properties = 5, .width = 107, .height = 27 },    /* Title_BRIGHTNESS@A1_C0, 101 */
    { .dataOffset = 2584006, .properties = 5, .width = 107, .height = 27 },    /* Title_BRIGHTNESS@A1_C1, 101 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TITLE_BRIGHTNESS__A002_C000, 11 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TITLE_BRIGHTNESS__A002_C001, 11 */
    { .dataOffset = 2589784, .properties = 5, .width = 65, .height = 27 },    /* Title_COLORS@A0_C0, 101 */
    { .dataOffset = 2593294, .properties = 5, .width = 65, .height = 27 },    /* Title_COLORS@A0_C1, 101 */
    { .dataOffset = 2596804, .properties = 5, .width = 75, .height = 27 },    /* Title_COLORS@A1_C0, 101 */
    { .dataOffset = 2600854, .properties = 5, .width = 75, .height = 27 },    /* Title_COLORS@A1_C1, 101 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TITLE_COLORS__A002_C000, 11 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TITLE_COLORS__A002_C001, 11 */
    { .dataOffset = 2604904, .properties = 5, .width = 46, .height = 27 },    /* Title_DATE_@A0_C0, 101 */
    { .dataOffset = 2607388, .properties = 5, .width = 46, .height = 27 },    /* Title_DATE_@A0_C1, 101 */
    { .dataOffset = 2609872, .properties = 5, .width = 64, .height = 27 },    /* Title_DATE_@A1_C0, 101 */
    { .dataOffset = 2613328, .properties = 5, .width = 64, .height = 27 },    /* Title_DATE_@A1_C1, 101 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TITLE_DATE__A002_C000, 11 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TITLE_DATE__A002_C001, 11 */
    { .dataOffset = 2616784, .properties = 5, .width = 36, .height = 27 },    /* Title_INFO@A0_C0, 101 */
    { .dataOffset = 2618728, .properties = 5, .width = 36, .height = 27 },    /* Title_INFO@A0_C1, 101 */
    { .dataOffset = 2620672, .properties = 5, .width = 36, .height = 27 },    /* Title_INFO@A1_C0, 101 */
    { .dataOffset = 2622616, .properties = 5, .width = 36, .height = 27 },    /* Title_INFO@A1_C1, 101 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TITLE_INFO__A002_C000, 11 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TITLE_INFO__A002_C001, 11 */
    { .dataOffset = 2624560, .properties = 5, .width = 99, .height = 27 },    /* Title_LANGUAGE@A0_C0, 101 */
    { .dataOffset = 2629906, .properties = 5, .width = 99, .height = 27 },    /* Title_LANGUAGE@A0_C1, 101 */
    { .dataOffset = 2635252, .properties = 5, .width = 43, .height = 27 },    /* Title_LANGUAGE@A1_C0, 101 */
    { .dataOffset = 2637574, .properties = 5, .width = 43, .height = 27 },    /* Title_LANGUAGE@A1_C1, 101 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TITLE_LANGUAGE__A002_C000, 11 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TITLE_LANGUAGE__A002_C001, 11 */
    { .dataOffset = 2639896, .properties = 5, .width = 109, .height = 27 },    /* Title_MAIN_MENU@A0_C0, 101 */
    { .dataOffset = 2645782, .properties = 5, .width = 109, .height = 27 },    /* Title_MAIN_MENU@A0_C1, 101 */
    { .dataOffset = 2651668, .properties = 5, .width = 114, .height = 27 },    /* Title_MAIN_MENU@A1_C0, 101 */
    { .dataOffset = 2657824, .properties = 5, .width = 114, .height = 27 },    /* Title_MAIN_MENU@A1_C1, 101 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TITLE_MAIN_MENU__A002_C000, 11 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TITLE_MAIN_MENU__A002_C001, 11 */
    { .dataOffset = 2663980, .properties = 5, .width = 137, .height = 27 },    /* Title_MEASUREMENT@A0_C0, 101 */
    { .dataOffset = 2671378, .properties = 5, .width = 137, .height = 27 },    /* Title_MEASUREMENT@A0_C1, 101 */
    { .dataOffset = 2678776, .properties = 5, .width = 78, .height = 27 },    /* Title_MEASUREMENT@A1_C0, 101 */
    { .dataOffset = 2682988, .properties = 5, .width = 78, .height = 27 },    /* Title_MEASUREMENT@A1_C1, 101 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TITLE_MEASUREMENT__A002_C000, 11 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TITLE_MEASUREMENT__A002_C001, 11 */
    { .dataOffset = 2687200, .properties = 5, .width = 81, .height = 27 },    /* Title_SETTINGS@A0_C0, 101 */
    { .dataOffset = 2691574, .properties = 5, .width = 81, .height = 27 },    /* Title_SETTINGS@A0_C1, 101 */
    { .dataOffset = 2695948, .properties = 5, .width = 112, .height = 27 },    /* Title_SETTINGS@A1_C0, 101 */
    { .dataOffset = 2701996, .properties = 5, .width = 112, .height = 27 },    /* Title_SETTINGS@A1_C1, 101 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TITLE_SETTINGS__A002_C000, 11 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TITLE_SETTINGS__A002_C001, 11 */
    { .dataOffset = 2708044, .properties = 5, .width = 58, .height = 27 },    /* Title_SETUP@A0_C0, 101 */
    { .dataOffset = 2711176, .properties = 5, .width = 58, .height = 27 },    /* Title_SETUP@A0_C1, 101 */
    { .dataOffset = 2714308, .properties = 5, .width = 65, .height = 27 },    /* Title_SETUP@A1_C0, 101 */
    { .dataOffset = 2717818, .properties = 5, .width = 65, .height = 27 },    /* Title_SETUP@A1_C1, 101 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TITLE_SETUP__A002_C000, 11 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TITLE_SETUP__A002_C001, 11 */
    { .dataOffset = 2721328, .properties = 5, .width = 69, .height = 27 },    /* Title_THEME@A0_C0, 101 */
    { .dataOffset = 2725054, .properties = 5, .width = 69, .height = 27 },    /* Title_THEME@A0_C1, 101 */
    { .dataOffset = 2728780, .properties = 5, .width = 81, .height = 27 },    /* Title_THEME@A1_C0, 101 */
    { .dataOffset = 2733154, .properties = 5, .width = 81, .height = 27 },    /* Title_THEME@A1_C1, 101 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TITLE_THEME__A002_C000, 11 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TITLE_THEME__A002_C001, 11 */
    { .dataOffset = 2737528, .properties = 5, .width = 49, .height = 27 },    /* Title_TIME@A0_C0, 101 */
    { .dataOffset = 2740174, .properties = 5, .width = 49, .height = 27 },    /* Title_TIME@A0_C1, 101 */
    { .dataOffset = 2742820, .properties = 5, .width = 35, .height = 27 },    /* Title_TIME@A1_C0, 101 */
    { .dataOffset = 2744710, .properties = 5, .width = 35, .height = 27 },    /* Title_TIME@A1_C1, 101 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TITLE_TIME__A002_C000, 11 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, TITLE_TIME__A002_C001, 11 */
};

const uint8_t maxProperty[FS_MAX_FILE_PROPERTIES] =
{
    3, 24, 2, 5, 
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
