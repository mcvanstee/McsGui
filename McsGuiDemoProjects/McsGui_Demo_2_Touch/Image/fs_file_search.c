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
    { .dataOffset = 299608, .properties = 4, .width = 74, .height = 29 },    /* Footer_MCSGUI@C0, 100 */
    { .dataOffset = 303900, .properties = 4, .width = 74, .height = 29 },    /* Footer_MCSGUI@C1, 100 */
    { .dataOffset = 308192, .properties = 12, .width = 18, .height = 20 },    /* icon_btn_Agenda@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_AGENDA__C000_D001, 11 */
    { .dataOffset = 308912, .properties = 12, .width = 18, .height = 20 },    /* icon_btn_Agenda@C0_D2, 1100 */
    { .dataOffset = 309632, .properties = 12, .width = 18, .height = 20 },    /* icon_btn_Agenda@C0_D3, 1100 */
    { .dataOffset = 310352, .properties = 12, .width = 18, .height = 20 },    /* icon_btn_Agenda@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_AGENDA__C001_D000, 11 */
    { .dataOffset = 311072, .properties = 12, .width = 18, .height = 20 },    /* icon_btn_Agenda@C1_D1, 1100 */
    { .dataOffset = 311792, .properties = 12, .width = 18, .height = 20 },    /* icon_btn_Agenda@C1_D2, 1100 */
    { .dataOffset = 312512, .properties = 12, .width = 18, .height = 20 },    /* icon_btn_Agenda@C1_D3, 1100 */
    { .dataOffset = 313232, .properties = 12, .width = 18, .height = 20 },    /* icon_btn_Agenda@C1_D4, 1100 */
    { .dataOffset = 313952, .properties = 12, .width = 35, .height = 18 },    /* icon_btn_Arrow-Back@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_ARROW_BACK__C000_D001, 11 */
    { .dataOffset = 315212, .properties = 12, .width = 35, .height = 18 },    /* icon_btn_Arrow-Back@C0_D2, 1100 */
    { .dataOffset = 316472, .properties = 12, .width = 35, .height = 18 },    /* icon_btn_Arrow-Back@C0_D3, 1100 */
    { .dataOffset = 317732, .properties = 12, .width = 35, .height = 18 },    /* icon_btn_Arrow-Back@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_ARROW_BACK__C001_D000, 11 */
    { .dataOffset = 318992, .properties = 12, .width = 35, .height = 18 },    /* icon_btn_Arrow-Back@C1_D1, 1100 */
    { .dataOffset = 320252, .properties = 12, .width = 35, .height = 18 },    /* icon_btn_Arrow-Back@C1_D2, 1100 */
    { .dataOffset = 321512, .properties = 12, .width = 35, .height = 18 },    /* icon_btn_Arrow-Back@C1_D3, 1100 */
    { .dataOffset = 322772, .properties = 12, .width = 35, .height = 18 },    /* icon_btn_Arrow-Back@C1_D4, 1100 */
    { .dataOffset = 324032, .properties = 12, .width = 13, .height = 4 },    /* icon_btn_Arrow_down@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_ARROW_DOWN__C000_D001, 11 */
    { .dataOffset = 324136, .properties = 12, .width = 13, .height = 4 },    /* icon_btn_Arrow_down@C0_D2, 1100 */
    { .dataOffset = 324240, .properties = 12, .width = 13, .height = 4 },    /* icon_btn_Arrow_down@C0_D3, 1100 */
    { .dataOffset = 324344, .properties = 12, .width = 13, .height = 4 },    /* icon_btn_Arrow_down@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_ARROW_DOWN__C001_D000, 11 */
    { .dataOffset = 324448, .properties = 12, .width = 13, .height = 4 },    /* icon_btn_Arrow_down@C1_D1, 1100 */
    { .dataOffset = 324552, .properties = 12, .width = 13, .height = 4 },    /* icon_btn_Arrow_down@C1_D2, 1100 */
    { .dataOffset = 324656, .properties = 12, .width = 13, .height = 4 },    /* icon_btn_Arrow_down@C1_D3, 1100 */
    { .dataOffset = 324760, .properties = 12, .width = 13, .height = 4 },    /* icon_btn_Arrow_down@C1_D4, 1100 */
    { .dataOffset = 324864, .properties = 12, .width = 12, .height = 4 },    /* icon_btn_Arrow_up@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_ARROW_UP__C000_D001, 11 */
    { .dataOffset = 324960, .properties = 12, .width = 12, .height = 4 },    /* icon_btn_Arrow_up@C0_D2, 1100 */
    { .dataOffset = 325056, .properties = 12, .width = 12, .height = 4 },    /* icon_btn_Arrow_up@C0_D3, 1100 */
    { .dataOffset = 325152, .properties = 12, .width = 12, .height = 4 },    /* icon_btn_Arrow_up@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_ARROW_UP__C001_D000, 11 */
    { .dataOffset = 325248, .properties = 12, .width = 12, .height = 4 },    /* icon_btn_Arrow_up@C1_D1, 1100 */
    { .dataOffset = 325344, .properties = 12, .width = 12, .height = 4 },    /* icon_btn_Arrow_up@C1_D2, 1100 */
    { .dataOffset = 325440, .properties = 12, .width = 12, .height = 4 },    /* icon_btn_Arrow_up@C1_D3, 1100 */
    { .dataOffset = 325536, .properties = 12, .width = 12, .height = 4 },    /* icon_btn_Arrow_up@C1_D4, 1100 */
    { .dataOffset = 325632, .properties = 12, .width = 16, .height = 18 },    /* icon_btn_Bell@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_BELL__C000_D001, 11 */
    { .dataOffset = 326208, .properties = 12, .width = 16, .height = 18 },    /* icon_btn_Bell@C0_D2, 1100 */
    { .dataOffset = 326784, .properties = 12, .width = 16, .height = 18 },    /* icon_btn_Bell@C0_D3, 1100 */
    { .dataOffset = 327360, .properties = 12, .width = 16, .height = 18 },    /* icon_btn_Bell@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_BELL__C001_D000, 11 */
    { .dataOffset = 327936, .properties = 12, .width = 16, .height = 18 },    /* icon_btn_Bell@C1_D1, 1100 */
    { .dataOffset = 328512, .properties = 12, .width = 16, .height = 18 },    /* icon_btn_Bell@C1_D2, 1100 */
    { .dataOffset = 329088, .properties = 12, .width = 16, .height = 18 },    /* icon_btn_Bell@C1_D3, 1100 */
    { .dataOffset = 329664, .properties = 12, .width = 16, .height = 18 },    /* icon_btn_Bell@C1_D4, 1100 */
    { .dataOffset = 330240, .properties = 12, .width = 30, .height = 25 },    /* icon_btn_Brightness@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_BRIGHTNESS__C000_D001, 11 */
    { .dataOffset = 331740, .properties = 12, .width = 30, .height = 25 },    /* icon_btn_Brightness@C0_D2, 1100 */
    { .dataOffset = 333240, .properties = 12, .width = 30, .height = 25 },    /* icon_btn_Brightness@C0_D3, 1100 */
    { .dataOffset = 334740, .properties = 12, .width = 30, .height = 25 },    /* icon_btn_Brightness@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_BRIGHTNESS__C001_D000, 11 */
    { .dataOffset = 336240, .properties = 12, .width = 30, .height = 25 },    /* icon_btn_Brightness@C1_D1, 1100 */
    { .dataOffset = 337740, .properties = 12, .width = 30, .height = 25 },    /* icon_btn_Brightness@C1_D2, 1100 */
    { .dataOffset = 339240, .properties = 12, .width = 30, .height = 25 },    /* icon_btn_Brightness@C1_D3, 1100 */
    { .dataOffset = 340740, .properties = 12, .width = 30, .height = 25 },    /* icon_btn_Brightness@C1_D4, 1100 */
    { .dataOffset = 342240, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Brush@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_BRUSH__C000_D001, 11 */
    { .dataOffset = 343208, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Brush@C0_D2, 1100 */
    { .dataOffset = 344176, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Brush@C0_D3, 1100 */
    { .dataOffset = 345144, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Brush@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_BRUSH__C001_D000, 11 */
    { .dataOffset = 346112, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Brush@C1_D1, 1100 */
    { .dataOffset = 347080, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Brush@C1_D2, 1100 */
    { .dataOffset = 348048, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Brush@C1_D3, 1100 */
    { .dataOffset = 349016, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Brush@C1_D4, 1100 */
    { .dataOffset = 349984, .properties = 12, .width = 18, .height = 18 },    /* icon_btn_Cancel@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_CANCEL__C000_D001, 11 */
    { .dataOffset = 350632, .properties = 12, .width = 18, .height = 18 },    /* icon_btn_Cancel@C0_D2, 1100 */
    { .dataOffset = 351280, .properties = 12, .width = 18, .height = 18 },    /* icon_btn_Cancel@C0_D3, 1100 */
    { .dataOffset = 351928, .properties = 12, .width = 18, .height = 18 },    /* icon_btn_Cancel@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_CANCEL__C001_D000, 11 */
    { .dataOffset = 352576, .properties = 12, .width = 18, .height = 18 },    /* icon_btn_Cancel@C1_D1, 1100 */
    { .dataOffset = 353224, .properties = 12, .width = 18, .height = 18 },    /* icon_btn_Cancel@C1_D2, 1100 */
    { .dataOffset = 353872, .properties = 12, .width = 18, .height = 18 },    /* icon_btn_Cancel@C1_D3, 1100 */
    { .dataOffset = 354520, .properties = 12, .width = 18, .height = 18 },    /* icon_btn_Cancel@C1_D4, 1100 */
    { .dataOffset = 355168, .properties = 12, .width = 26, .height = 21 },    /* icon_btn_Checkmark_large@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_CHECKMARK_LARGE__C000_D001, 11 */
    { .dataOffset = 356260, .properties = 12, .width = 26, .height = 21 },    /* icon_btn_Checkmark_large@C0_D2, 1100 */
    { .dataOffset = 357352, .properties = 12, .width = 26, .height = 21 },    /* icon_btn_Checkmark_large@C0_D3, 1100 */
    { .dataOffset = 358444, .properties = 12, .width = 26, .height = 21 },    /* icon_btn_Checkmark_large@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_CHECKMARK_LARGE__C001_D000, 11 */
    { .dataOffset = 359536, .properties = 12, .width = 26, .height = 21 },    /* icon_btn_Checkmark_large@C1_D1, 1100 */
    { .dataOffset = 360628, .properties = 12, .width = 26, .height = 21 },    /* icon_btn_Checkmark_large@C1_D2, 1100 */
    { .dataOffset = 361720, .properties = 12, .width = 26, .height = 21 },    /* icon_btn_Checkmark_large@C1_D3, 1100 */
    { .dataOffset = 362812, .properties = 12, .width = 26, .height = 21 },    /* icon_btn_Checkmark_large@C1_D4, 1100 */
    { .dataOffset = 363904, .properties = 12, .width = 20, .height = 20 },    /* icon_btn_Clock@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_CLOCK__C000_D001, 11 */
    { .dataOffset = 364704, .properties = 12, .width = 20, .height = 20 },    /* icon_btn_Clock@C0_D2, 1100 */
    { .dataOffset = 365504, .properties = 12, .width = 20, .height = 20 },    /* icon_btn_Clock@C0_D3, 1100 */
    { .dataOffset = 366304, .properties = 12, .width = 20, .height = 20 },    /* icon_btn_Clock@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_CLOCK__C001_D000, 11 */
    { .dataOffset = 367104, .properties = 12, .width = 20, .height = 20 },    /* icon_btn_Clock@C1_D1, 1100 */
    { .dataOffset = 367904, .properties = 12, .width = 20, .height = 20 },    /* icon_btn_Clock@C1_D2, 1100 */
    { .dataOffset = 368704, .properties = 12, .width = 20, .height = 20 },    /* icon_btn_Clock@C1_D3, 1100 */
    { .dataOffset = 369504, .properties = 12, .width = 20, .height = 20 },    /* icon_btn_Clock@C1_D4, 1100 */
    { .dataOffset = 370304, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Focus@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_FOCUS__C000_D001, 11 */
    { .dataOffset = 371272, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Focus@C0_D2, 1100 */
    { .dataOffset = 372240, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Focus@C0_D3, 1100 */
    { .dataOffset = 373208, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Focus@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_FOCUS__C001_D000, 11 */
    { .dataOffset = 374176, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Focus@C1_D1, 1100 */
    { .dataOffset = 375144, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Focus@C1_D2, 1100 */
    { .dataOffset = 376112, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Focus@C1_D3, 1100 */
    { .dataOffset = 377080, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Focus@C1_D4, 1100 */
    { .dataOffset = 378048, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Gear@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_GEAR__C000_D001, 11 */
    { .dataOffset = 379016, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Gear@C0_D2, 1100 */
    { .dataOffset = 379984, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Gear@C0_D3, 1100 */
    { .dataOffset = 380952, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Gear@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_GEAR__C001_D000, 11 */
    { .dataOffset = 381920, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Gear@C1_D1, 1100 */
    { .dataOffset = 382888, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Gear@C1_D2, 1100 */
    { .dataOffset = 383856, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Gear@C1_D3, 1100 */
    { .dataOffset = 384824, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Gear@C1_D4, 1100 */
    { .dataOffset = 385792, .properties = 12, .width = 20, .height = 20 },    /* icon_btn_Global@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_GLOBAL__C000_D001, 11 */
    { .dataOffset = 386592, .properties = 12, .width = 20, .height = 20 },    /* icon_btn_Global@C0_D2, 1100 */
    { .dataOffset = 387392, .properties = 12, .width = 20, .height = 20 },    /* icon_btn_Global@C0_D3, 1100 */
    { .dataOffset = 388192, .properties = 12, .width = 20, .height = 20 },    /* icon_btn_Global@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_GLOBAL__C001_D000, 11 */
    { .dataOffset = 388992, .properties = 12, .width = 20, .height = 20 },    /* icon_btn_Global@C1_D1, 1100 */
    { .dataOffset = 389792, .properties = 12, .width = 20, .height = 20 },    /* icon_btn_Global@C1_D2, 1100 */
    { .dataOffset = 390592, .properties = 12, .width = 20, .height = 20 },    /* icon_btn_Global@C1_D3, 1100 */
    { .dataOffset = 391392, .properties = 12, .width = 20, .height = 20 },    /* icon_btn_Global@C1_D4, 1100 */
    { .dataOffset = 392192, .properties = 12, .width = 21, .height = 21 },    /* icon_btn_Info@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_INFO__C000_D001, 11 */
    { .dataOffset = 393074, .properties = 12, .width = 21, .height = 21 },    /* icon_btn_Info@C0_D2, 1100 */
    { .dataOffset = 393956, .properties = 12, .width = 21, .height = 21 },    /* icon_btn_Info@C0_D3, 1100 */
    { .dataOffset = 394838, .properties = 12, .width = 21, .height = 21 },    /* icon_btn_Info@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_INFO__C001_D000, 11 */
    { .dataOffset = 395720, .properties = 12, .width = 21, .height = 21 },    /* icon_btn_Info@C1_D1, 1100 */
    { .dataOffset = 396602, .properties = 12, .width = 21, .height = 21 },    /* icon_btn_Info@C1_D2, 1100 */
    { .dataOffset = 397484, .properties = 12, .width = 21, .height = 21 },    /* icon_btn_Info@C1_D3, 1100 */
    { .dataOffset = 398366, .properties = 12, .width = 21, .height = 21 },    /* icon_btn_Info@C1_D4, 1100 */
    { .dataOffset = 399248, .properties = 12, .width = 23, .height = 16 },    /* icon_btn_Keyboard@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_KEYBOARD__C000_D001, 11 */
    { .dataOffset = 399984, .properties = 12, .width = 23, .height = 16 },    /* icon_btn_Keyboard@C0_D2, 1100 */
    { .dataOffset = 400720, .properties = 12, .width = 23, .height = 16 },    /* icon_btn_Keyboard@C0_D3, 1100 */
    { .dataOffset = 401456, .properties = 12, .width = 23, .height = 16 },    /* icon_btn_Keyboard@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_KEYBOARD__C001_D000, 11 */
    { .dataOffset = 402192, .properties = 12, .width = 23, .height = 16 },    /* icon_btn_Keyboard@C1_D1, 1100 */
    { .dataOffset = 402928, .properties = 12, .width = 23, .height = 16 },    /* icon_btn_Keyboard@C1_D2, 1100 */
    { .dataOffset = 403664, .properties = 12, .width = 23, .height = 16 },    /* icon_btn_Keyboard@C1_D3, 1100 */
    { .dataOffset = 404400, .properties = 12, .width = 23, .height = 16 },    /* icon_btn_Keyboard@C1_D4, 1100 */
    { .dataOffset = 405136, .properties = 12, .width = 16, .height = 4 },    /* icon_btn_minus@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_MINUS__C000_D001, 11 */
    { .dataOffset = 405264, .properties = 12, .width = 16, .height = 4 },    /* icon_btn_minus@C0_D2, 1100 */
    { .dataOffset = 405392, .properties = 12, .width = 16, .height = 4 },    /* icon_btn_minus@C0_D3, 1100 */
    { .dataOffset = 405520, .properties = 12, .width = 16, .height = 4 },    /* icon_btn_minus@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_MINUS__C001_D000, 11 */
    { .dataOffset = 405648, .properties = 12, .width = 16, .height = 4 },    /* icon_btn_minus@C1_D1, 1100 */
    { .dataOffset = 405776, .properties = 12, .width = 16, .height = 4 },    /* icon_btn_minus@C1_D2, 1100 */
    { .dataOffset = 405904, .properties = 12, .width = 16, .height = 4 },    /* icon_btn_minus@C1_D3, 1100 */
    { .dataOffset = 406032, .properties = 12, .width = 16, .height = 4 },    /* icon_btn_minus@C1_D4, 1100 */
    { .dataOffset = 406160, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Palette@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_PALETTE__C000_D001, 11 */
    { .dataOffset = 407128, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Palette@C0_D2, 1100 */
    { .dataOffset = 408096, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Palette@C0_D3, 1100 */
    { .dataOffset = 409064, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Palette@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_PALETTE__C001_D000, 11 */
    { .dataOffset = 410032, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Palette@C1_D1, 1100 */
    { .dataOffset = 411000, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Palette@C1_D2, 1100 */
    { .dataOffset = 411968, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Palette@C1_D3, 1100 */
    { .dataOffset = 412936, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Palette@C1_D4, 1100 */
    { .dataOffset = 413904, .properties = 12, .width = 16, .height = 16 },    /* icon_btn_plus@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_PLUS__C000_D001, 11 */
    { .dataOffset = 414416, .properties = 12, .width = 16, .height = 16 },    /* icon_btn_plus@C0_D2, 1100 */
    { .dataOffset = 414928, .properties = 12, .width = 16, .height = 16 },    /* icon_btn_plus@C0_D3, 1100 */
    { .dataOffset = 415440, .properties = 12, .width = 16, .height = 16 },    /* icon_btn_plus@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_PLUS__C001_D000, 11 */
    { .dataOffset = 415952, .properties = 12, .width = 16, .height = 16 },    /* icon_btn_plus@C1_D1, 1100 */
    { .dataOffset = 416464, .properties = 12, .width = 16, .height = 16 },    /* icon_btn_plus@C1_D2, 1100 */
    { .dataOffset = 416976, .properties = 12, .width = 16, .height = 16 },    /* icon_btn_plus@C1_D3, 1100 */
    { .dataOffset = 417488, .properties = 12, .width = 16, .height = 16 },    /* icon_btn_plus@C1_D4, 1100 */
    { .dataOffset = 418000, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Sliders@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_SLIDERS__C000_D001, 11 */
    { .dataOffset = 418968, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Sliders@C0_D2, 1100 */
    { .dataOffset = 419936, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Sliders@C0_D3, 1100 */
    { .dataOffset = 420904, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Sliders@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_SLIDERS__C001_D000, 11 */
    { .dataOffset = 421872, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Sliders@C1_D1, 1100 */
    { .dataOffset = 422840, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Sliders@C1_D2, 1100 */
    { .dataOffset = 423808, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Sliders@C1_D3, 1100 */
    { .dataOffset = 424776, .properties = 12, .width = 22, .height = 22 },    /* icon_btn_Sliders@C1_D4, 1100 */
    { .dataOffset = 425744, .properties = 12, .width = 25, .height = 18 },    /* icon_btn_Wifi@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_WIFI__C000_D001, 11 */
    { .dataOffset = 426644, .properties = 12, .width = 25, .height = 18 },    /* icon_btn_Wifi@C0_D2, 1100 */
    { .dataOffset = 427544, .properties = 12, .width = 25, .height = 18 },    /* icon_btn_Wifi@C0_D3, 1100 */
    { .dataOffset = 428444, .properties = 12, .width = 25, .height = 18 },    /* icon_btn_Wifi@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_BTN_WIFI__C001_D000, 11 */
    { .dataOffset = 429344, .properties = 12, .width = 25, .height = 18 },    /* icon_btn_Wifi@C1_D1, 1100 */
    { .dataOffset = 430244, .properties = 12, .width = 25, .height = 18 },    /* icon_btn_Wifi@C1_D2, 1100 */
    { .dataOffset = 431144, .properties = 12, .width = 25, .height = 18 },    /* icon_btn_Wifi@C1_D3, 1100 */
    { .dataOffset = 432044, .properties = 12, .width = 25, .height = 18 },    /* icon_btn_Wifi@C1_D4, 1100 */
    { .dataOffset = 432944, .properties = 12, .width = 13, .height = 4 },    /* icon_dft_Arrow_down@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_DFT_ARROW_DOWN__C000_D001, 11 */
    { .dataOffset = 433048, .properties = 12, .width = 13, .height = 4 },    /* icon_dft_Arrow_down@C0_D2, 1100 */
    { .dataOffset = 433152, .properties = 12, .width = 13, .height = 4 },    /* icon_dft_Arrow_down@C0_D3, 1100 */
    { .dataOffset = 433256, .properties = 12, .width = 13, .height = 4 },    /* icon_dft_Arrow_down@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_DFT_ARROW_DOWN__C001_D000, 11 */
    { .dataOffset = 433360, .properties = 12, .width = 13, .height = 4 },    /* icon_dft_Arrow_down@C1_D1, 1100 */
    { .dataOffset = 433464, .properties = 12, .width = 13, .height = 4 },    /* icon_dft_Arrow_down@C1_D2, 1100 */
    { .dataOffset = 433568, .properties = 12, .width = 13, .height = 4 },    /* icon_dft_Arrow_down@C1_D3, 1100 */
    { .dataOffset = 433672, .properties = 12, .width = 13, .height = 4 },    /* icon_dft_Arrow_down@C1_D4, 1100 */
    { .dataOffset = 433776, .properties = 12, .width = 12, .height = 4 },    /* icon_dft_Arrow_up@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_DFT_ARROW_UP__C000_D001, 11 */
    { .dataOffset = 433872, .properties = 12, .width = 12, .height = 4 },    /* icon_dft_Arrow_up@C0_D2, 1100 */
    { .dataOffset = 433968, .properties = 12, .width = 12, .height = 4 },    /* icon_dft_Arrow_up@C0_D3, 1100 */
    { .dataOffset = 434064, .properties = 12, .width = 12, .height = 4 },    /* icon_dft_Arrow_up@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_DFT_ARROW_UP__C001_D000, 11 */
    { .dataOffset = 434160, .properties = 12, .width = 12, .height = 4 },    /* icon_dft_Arrow_up@C1_D1, 1100 */
    { .dataOffset = 434256, .properties = 12, .width = 12, .height = 4 },    /* icon_dft_Arrow_up@C1_D2, 1100 */
    { .dataOffset = 434352, .properties = 12, .width = 12, .height = 4 },    /* icon_dft_Arrow_up@C1_D3, 1100 */
    { .dataOffset = 434448, .properties = 12, .width = 12, .height = 4 },    /* icon_dft_Arrow_up@C1_D4, 1100 */
    { .dataOffset = 434544, .properties = 12, .width = 20, .height = 20 },    /* icon_dft_Checkbox-Checked@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_DFT_CHECKBOX_CHECKED__C000_D001, 11 */
    { .dataOffset = 435344, .properties = 12, .width = 20, .height = 20 },    /* icon_dft_Checkbox-Checked@C0_D2, 1100 */
    { .dataOffset = 436144, .properties = 12, .width = 20, .height = 20 },    /* icon_dft_Checkbox-Checked@C0_D3, 1100 */
    { .dataOffset = 436944, .properties = 12, .width = 20, .height = 20 },    /* icon_dft_Checkbox-Checked@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_DFT_CHECKBOX_CHECKED__C001_D000, 11 */
    { .dataOffset = 437744, .properties = 12, .width = 20, .height = 20 },    /* icon_dft_Checkbox-Checked@C1_D1, 1100 */
    { .dataOffset = 438544, .properties = 12, .width = 20, .height = 20 },    /* icon_dft_Checkbox-Checked@C1_D2, 1100 */
    { .dataOffset = 439344, .properties = 12, .width = 20, .height = 20 },    /* icon_dft_Checkbox-Checked@C1_D3, 1100 */
    { .dataOffset = 440144, .properties = 12, .width = 20, .height = 20 },    /* icon_dft_Checkbox-Checked@C1_D4, 1100 */
    { .dataOffset = 440944, .properties = 12, .width = 20, .height = 20 },    /* icon_dft_Checkbox-UnChecked@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_DFT_CHECKBOX_UNCHECKED__C000_D001, 11 */
    { .dataOffset = 441744, .properties = 12, .width = 20, .height = 20 },    /* icon_dft_Checkbox-UnChecked@C0_D2, 1100 */
    { .dataOffset = 442544, .properties = 12, .width = 20, .height = 20 },    /* icon_dft_Checkbox-UnChecked@C0_D3, 1100 */
    { .dataOffset = 443344, .properties = 12, .width = 20, .height = 20 },    /* icon_dft_Checkbox-UnChecked@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_DFT_CHECKBOX_UNCHECKED__C001_D000, 11 */
    { .dataOffset = 444144, .properties = 12, .width = 20, .height = 20 },    /* icon_dft_Checkbox-UnChecked@C1_D1, 1100 */
    { .dataOffset = 444944, .properties = 12, .width = 20, .height = 20 },    /* icon_dft_Checkbox-UnChecked@C1_D2, 1100 */
    { .dataOffset = 445744, .properties = 12, .width = 20, .height = 20 },    /* icon_dft_Checkbox-UnChecked@C1_D3, 1100 */
    { .dataOffset = 446544, .properties = 12, .width = 20, .height = 20 },    /* icon_dft_Checkbox-UnChecked@C1_D4, 1100 */
    { .dataOffset = 447344, .properties = 12, .width = 16, .height = 13 },    /* icon_dft_Checkmark@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_DFT_CHECKMARK__C000_D001, 11 */
    { .dataOffset = 447760, .properties = 12, .width = 16, .height = 13 },    /* icon_dft_Checkmark@C0_D2, 1100 */
    { .dataOffset = 448176, .properties = 12, .width = 16, .height = 13 },    /* icon_dft_Checkmark@C0_D3, 1100 */
    { .dataOffset = 448592, .properties = 12, .width = 16, .height = 13 },    /* icon_dft_Checkmark@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_DFT_CHECKMARK__C001_D000, 11 */
    { .dataOffset = 449008, .properties = 12, .width = 16, .height = 13 },    /* icon_dft_Checkmark@C1_D1, 1100 */
    { .dataOffset = 449424, .properties = 12, .width = 16, .height = 13 },    /* icon_dft_Checkmark@C1_D2, 1100 */
    { .dataOffset = 449840, .properties = 12, .width = 16, .height = 13 },    /* icon_dft_Checkmark@C1_D3, 1100 */
    { .dataOffset = 450256, .properties = 12, .width = 16, .height = 13 },    /* icon_dft_Checkmark@C1_D4, 1100 */
    { .dataOffset = 450672, .properties = 12, .width = 16, .height = 4 },    /* icon_dft_minus@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_DFT_MINUS__C000_D001, 11 */
    { .dataOffset = 450800, .properties = 12, .width = 16, .height = 4 },    /* icon_dft_minus@C0_D2, 1100 */
    { .dataOffset = 450928, .properties = 12, .width = 16, .height = 4 },    /* icon_dft_minus@C0_D3, 1100 */
    { .dataOffset = 451056, .properties = 12, .width = 16, .height = 4 },    /* icon_dft_minus@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_DFT_MINUS__C001_D000, 11 */
    { .dataOffset = 451184, .properties = 12, .width = 16, .height = 4 },    /* icon_dft_minus@C1_D1, 1100 */
    { .dataOffset = 451312, .properties = 12, .width = 16, .height = 4 },    /* icon_dft_minus@C1_D2, 1100 */
    { .dataOffset = 451440, .properties = 12, .width = 16, .height = 4 },    /* icon_dft_minus@C1_D3, 1100 */
    { .dataOffset = 451568, .properties = 12, .width = 16, .height = 4 },    /* icon_dft_minus@C1_D4, 1100 */
    { .dataOffset = 451696, .properties = 12, .width = 16, .height = 16 },    /* icon_dft_plus@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_DFT_PLUS__C000_D001, 11 */
    { .dataOffset = 452208, .properties = 12, .width = 16, .height = 16 },    /* icon_dft_plus@C0_D2, 1100 */
    { .dataOffset = 452720, .properties = 12, .width = 16, .height = 16 },    /* icon_dft_plus@C0_D3, 1100 */
    { .dataOffset = 453232, .properties = 12, .width = 16, .height = 16 },    /* icon_dft_plus@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_DFT_PLUS__C001_D000, 11 */
    { .dataOffset = 453744, .properties = 12, .width = 16, .height = 16 },    /* icon_dft_plus@C1_D1, 1100 */
    { .dataOffset = 454256, .properties = 12, .width = 16, .height = 16 },    /* icon_dft_plus@C1_D2, 1100 */
    { .dataOffset = 454768, .properties = 12, .width = 16, .height = 16 },    /* icon_dft_plus@C1_D3, 1100 */
    { .dataOffset = 455280, .properties = 12, .width = 16, .height = 16 },    /* icon_dft_plus@C1_D4, 1100 */
    { .dataOffset = 455792, .properties = 12, .width = 18, .height = 18 },    /* icon_dft_Radio-Button-Checked@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_DFT_RADIO_BUTTON_CHECKED__C000_D001, 11 */
    { .dataOffset = 456440, .properties = 12, .width = 18, .height = 18 },    /* icon_dft_Radio-Button-Checked@C0_D2, 1100 */
    { .dataOffset = 457088, .properties = 12, .width = 18, .height = 18 },    /* icon_dft_Radio-Button-Checked@C0_D3, 1100 */
    { .dataOffset = 457736, .properties = 12, .width = 18, .height = 18 },    /* icon_dft_Radio-Button-Checked@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_DFT_RADIO_BUTTON_CHECKED__C001_D000, 11 */
    { .dataOffset = 458384, .properties = 12, .width = 18, .height = 18 },    /* icon_dft_Radio-Button-Checked@C1_D1, 1100 */
    { .dataOffset = 459032, .properties = 12, .width = 18, .height = 18 },    /* icon_dft_Radio-Button-Checked@C1_D2, 1100 */
    { .dataOffset = 459680, .properties = 12, .width = 18, .height = 18 },    /* icon_dft_Radio-Button-Checked@C1_D3, 1100 */
    { .dataOffset = 460328, .properties = 12, .width = 18, .height = 18 },    /* icon_dft_Radio-Button-Checked@C1_D4, 1100 */
    { .dataOffset = 460976, .properties = 12, .width = 18, .height = 18 },    /* icon_dft_Radio-Button-UnChecked@C0_D0, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_DFT_RADIO_BUTTON_UNCHECKED__C000_D001, 11 */
    { .dataOffset = 461624, .properties = 12, .width = 18, .height = 18 },    /* icon_dft_Radio-Button-UnChecked@C0_D2, 1100 */
    { .dataOffset = 462272, .properties = 12, .width = 18, .height = 18 },    /* icon_dft_Radio-Button-UnChecked@C0_D3, 1100 */
    { .dataOffset = 462920, .properties = 12, .width = 18, .height = 18 },    /* icon_dft_Radio-Button-UnChecked@C0_D4, 1100 */
    { .dataOffset = 4294967295, .properties = 3, .width = 0, .height = 0 },    /* Dummy file, ICON_DFT_RADIO_BUTTON_UNCHECKED__C001_D000, 11 */
    { .dataOffset = 463568, .properties = 12, .width = 18, .height = 18 },    /* icon_dft_Radio-Button-UnChecked@C1_D1, 1100 */
    { .dataOffset = 464216, .properties = 12, .width = 18, .height = 18 },    /* icon_dft_Radio-Button-UnChecked@C1_D2, 1100 */
    { .dataOffset = 464864, .properties = 12, .width = 18, .height = 18 },    /* icon_dft_Radio-Button-UnChecked@C1_D3, 1100 */
    { .dataOffset = 465512, .properties = 12, .width = 18, .height = 18 },    /* icon_dft_Radio-Button-UnChecked@C1_D4, 1100 */
    { .dataOffset = 466160, .properties = 4, .width = 16, .height = 18 },    /* icon_header_Bell@C0, 100 */
    { .dataOffset = 466736, .properties = 4, .width = 16, .height = 18 },    /* icon_header_Bell@C1, 100 */
    { .dataOffset = 467312, .properties = 4, .width = 20, .height = 20 },    /* icon_header_Clock@C0, 100 */
    { .dataOffset = 468112, .properties = 4, .width = 20, .height = 20 },    /* icon_header_Clock@C1, 100 */
    { .dataOffset = 468912, .properties = 4, .width = 25, .height = 18 },    /* icon_header_Wifi@C0, 100 */
    { .dataOffset = 469812, .properties = 4, .width = 25, .height = 18 },    /* icon_header_Wifi@C1, 100 */
    { .dataOffset = 470712, .properties = 0, .width = 128, .height = 128 },    /* IRL_Logo 128, 0 */
    { .dataOffset = 503480, .properties = 0, .width = 48, .height = 48 },    /* IRL_Logo_48, 0 */
    { .dataOffset = 508088, .properties = 4, .width = 480, .height = 236 },    /* Keyboard_lc@C0, 100 */
    { .dataOffset = 734648, .properties = 4, .width = 480, .height = 236 },    /* Keyboard_lc@C1, 100 */
    { .dataOffset = 961208, .properties = 4, .width = 480, .height = 236 },    /* Keyboard_num@C0, 100 */
    { .dataOffset = 1187768, .properties = 4, .width = 480, .height = 236 },    /* Keyboard_num@C1, 100 */
    { .dataOffset = 1414328, .properties = 4, .width = 480, .height = 84 },    /* Keyboard_textbox@C0, 100 */
    { .dataOffset = 1494968, .properties = 4, .width = 480, .height = 84 },    /* Keyboard_textbox@C1, 100 */
    { .dataOffset = 1575608, .properties = 4, .width = 480, .height = 236 },    /* Keyboard_uc@C0, 100 */
    { .dataOffset = 1802168, .properties = 4, .width = 480, .height = 236 },    /* Keyboard_uc@C1, 100 */
    { .dataOffset = 2028728, .properties = 5, .width = 52, .height = 23 },    /* Text_button_ACCENT_COLOR@A0_C0, 101 */
    { .dataOffset = 2031120, .properties = 5, .width = 52, .height = 23 },    /* Text_button_ACCENT_COLOR@A0_C1, 101 */
    { .dataOffset = 2033512, .properties = 5, .width = 60, .height = 23 },    /* Text_button_ACCENT_COLOR@A1_C0, 101 */
    { .dataOffset = 2036272, .properties = 5, .width = 60, .height = 23 },    /* Text_button_ACCENT_COLOR@A1_C1, 101 */
    { .dataOffset = 2039032, .properties = 5, .width = 55, .height = 23 },    /* Text_button_ACCENT_COLOR@A2_C0, 101 */
    { .dataOffset = 2041562, .properties = 5, .width = 55, .height = 23 },    /* Text_button_ACCENT_COLOR@A2_C1, 101 */
    { .dataOffset = 2044092, .properties = 5, .width = 72, .height = 23 },    /* Text_button_ACCENT_COLOR@A3_C0, 101 */
    { .dataOffset = 2047404, .properties = 5, .width = 72, .height = 23 },    /* Text_button_ACCENT_COLOR@A3_C1, 101 */
    { .dataOffset = 2050716, .properties = 5, .width = 62, .height = 23 },    /* Text_button_ACCENT_COLOR@A4_C0, 101 */
    { .dataOffset = 2053568, .properties = 5, .width = 62, .height = 23 },    /* Text_button_ACCENT_COLOR@A4_C1, 101 */
    { .dataOffset = 2056420, .properties = 5, .width = 47, .height = 23 },    /* Text_button_ACCENT_COLOR@A5_C0, 101 */
    { .dataOffset = 2058582, .properties = 5, .width = 47, .height = 23 },    /* Text_button_ACCENT_COLOR@A5_C1, 101 */
    { .dataOffset = 2060744, .properties = 5, .width = 54, .height = 23 },    /* Text_button_ACCENT_COLOR@A6_C0, 101 */
    { .dataOffset = 2063228, .properties = 5, .width = 54, .height = 23 },    /* Text_button_ACCENT_COLOR@A6_C1, 101 */
    { .dataOffset = 2065712, .properties = 5, .width = 40, .height = 23 },    /* Text_button_ACCENT_COLOR@A7_C0, 101 */
    { .dataOffset = 2067552, .properties = 5, .width = 40, .height = 23 },    /* Text_button_ACCENT_COLOR@A7_C1, 101 */
    { .dataOffset = 2069392, .properties = 5, .width = 18, .height = 23 },    /* Text_button_ACCENT_COLOR@A8_C0, 101 */
    { .dataOffset = 2070220, .properties = 5, .width = 18, .height = 23 },    /* Text_button_ACCENT_COLOR@A8_C1, 101 */
    { .dataOffset = 2071048, .properties = 5, .width = 35, .height = 23 },    /* Text_button_ACCENT_COLOR@A9_C0, 101 */
    { .dataOffset = 2072658, .properties = 5, .width = 35, .height = 23 },    /* Text_button_ACCENT_COLOR@A9_C1, 101 */
    { .dataOffset = 2074268, .properties = 5, .width = 48, .height = 23 },    /* Text_button_ALARM@A0_C0, 101 */
    { .dataOffset = 2076476, .properties = 5, .width = 48, .height = 23 },    /* Text_button_ALARM@A0_C1, 101 */
    { .dataOffset = 2078684, .properties = 5, .width = 48, .height = 23 },    /* Text_button_ALARM@A1_C0, 101 */
    { .dataOffset = 2080892, .properties = 5, .width = 48, .height = 23 },    /* Text_button_ALARM@A1_C1, 101 */
    { .dataOffset = 2083100, .properties = 5, .width = 48, .height = 23 },    /* Text_button_ALARM@A2_C0, 101 */
    { .dataOffset = 2085308, .properties = 5, .width = 48, .height = 23 },    /* Text_button_ALARM@A2_C1, 101 */
    { .dataOffset = 2087516, .properties = 5, .width = 59, .height = 23 },    /* Text_button_ALARM@A3_C0, 101 */
    { .dataOffset = 2090230, .properties = 5, .width = 59, .height = 23 },    /* Text_button_ALARM@A3_C1, 101 */
    { .dataOffset = 2092944, .properties = 5, .width = 58, .height = 23 },    /* Text_button_ALARM@A4_C0, 101 */
    { .dataOffset = 2095612, .properties = 5, .width = 58, .height = 23 },    /* Text_button_ALARM@A4_C1, 101 */
    { .dataOffset = 2098280, .properties = 5, .width = 63, .height = 23 },    /* Text_button_ALARM@A5_C0, 101 */
    { .dataOffset = 2101178, .properties = 5, .width = 63, .height = 23 },    /* Text_button_ALARM@A5_C1, 101 */
    { .dataOffset = 2104076, .properties = 5, .width = 69, .height = 23 },    /* Text_button_ALARM@A6_C0, 101 */
    { .dataOffset = 2107250, .properties = 5, .width = 69, .height = 23 },    /* Text_button_ALARM@A6_C1, 101 */
    { .dataOffset = 2110424, .properties = 5, .width = 40, .height = 23 },    /* Text_button_ALARM@A7_C0, 101 */
    { .dataOffset = 2112264, .properties = 5, .width = 40, .height = 23 },    /* Text_button_ALARM@A7_C1, 101 */
    { .dataOffset = 2114104, .properties = 5, .width = 39, .height = 23 },    /* Text_button_ALARM@A8_C0, 101 */
    { .dataOffset = 2115898, .properties = 5, .width = 39, .height = 23 },    /* Text_button_ALARM@A8_C1, 101 */
    { .dataOffset = 2117692, .properties = 5, .width = 51, .height = 23 },    /* Text_button_ALARM@A9_C0, 101 */
    { .dataOffset = 2120038, .properties = 5, .width = 51, .height = 23 },    /* Text_button_ALARM@A9_C1, 101 */
    { .dataOffset = 2122384, .properties = 5, .width = 87, .height = 23 },    /* Text_button_BRIGHTNESS@A0_C0, 101 */
    { .dataOffset = 2126386, .properties = 5, .width = 87, .height = 23 },    /* Text_button_BRIGHTNESS@A0_C1, 101 */
    { .dataOffset = 2130388, .properties = 5, .width = 87, .height = 23 },    /* Text_button_BRIGHTNESS@A1_C0, 101 */
    { .dataOffset = 2134390, .properties = 5, .width = 87, .height = 23 },    /* Text_button_BRIGHTNESS@A1_C1, 101 */
    { .dataOffset = 2138392, .properties = 5, .width = 75, .height = 23 },    /* Text_button_BRIGHTNESS@A2_C0, 101 */
    { .dataOffset = 2141842, .properties = 5, .width = 75, .height = 23 },    /* Text_button_BRIGHTNESS@A2_C1, 101 */
    { .dataOffset = 2145292, .properties = 5, .width = 90, .height = 23 },    /* Text_button_BRIGHTNESS@A3_C0, 101 */
    { .dataOffset = 2149432, .properties = 5, .width = 90, .height = 23 },    /* Text_button_BRIGHTNESS@A3_C1, 101 */
    { .dataOffset = 2153572, .properties = 5, .width = 40, .height = 23 },    /* Text_button_BRIGHTNESS@A4_C0, 101 */
    { .dataOffset = 2155412, .properties = 5, .width = 40, .height = 23 },    /* Text_button_BRIGHTNESS@A4_C1, 101 */
    { .dataOffset = 2157252, .properties = 5, .width = 90, .height = 23 },    /* Text_button_BRIGHTNESS@A5_C0, 101 */
    { .dataOffset = 2161392, .properties = 5, .width = 90, .height = 23 },    /* Text_button_BRIGHTNESS@A5_C1, 101 */
    { .dataOffset = 2165532, .properties = 5, .width = 71, .height = 23 },    /* Text_button_BRIGHTNESS@A6_C0, 101 */
    { .dataOffset = 2168798, .properties = 5, .width = 71, .height = 23 },    /* Text_button_BRIGHTNESS@A6_C1, 101 */
    { .dataOffset = 2172064, .properties = 5, .width = 39, .height = 23 },    /* Text_button_BRIGHTNESS@A7_C0, 101 */
    { .dataOffset = 2173858, .properties = 5, .width = 39, .height = 23 },    /* Text_button_BRIGHTNESS@A7_C1, 101 */
    { .dataOffset = 2175652, .properties = 5, .width = 48, .height = 23 },    /* Text_button_BRIGHTNESS@A8_C0, 101 */
    { .dataOffset = 2177860, .properties = 5, .width = 48, .height = 23 },    /* Text_button_BRIGHTNESS@A8_C1, 101 */
    { .dataOffset = 2180068, .properties = 5, .width = 32, .height = 23 },    /* Text_button_BRIGHTNESS@A9_C0, 101 */
    { .dataOffset = 2181540, .properties = 5, .width = 32, .height = 23 },    /* Text_button_BRIGHTNESS@A9_C1, 101 */
    { .dataOffset = 2183012, .properties = 5, .width = 37, .height = 23 },    /* Text_button_DATE@A0_C0, 101 */
    { .dataOffset = 2184714, .properties = 5, .width = 37, .height = 23 },    /* Text_button_DATE@A0_C1, 101 */
    { .dataOffset = 2186416, .properties = 5, .width = 52, .height = 23 },    /* Text_button_DATE@A1_C0, 101 */
    { .dataOffset = 2188808, .properties = 5, .width = 52, .height = 23 },    /* Text_button_DATE@A1_C1, 101 */
    { .dataOffset = 2191200, .properties = 5, .width = 52, .height = 23 },    /* Text_button_DATE@A2_C0, 101 */
    { .dataOffset = 2193592, .properties = 5, .width = 52, .height = 23 },    /* Text_button_DATE@A2_C1, 101 */
    { .dataOffset = 2195984, .properties = 5, .width = 37, .height = 23 },    /* Text_button_DATE@A3_C0, 101 */
    { .dataOffset = 2197686, .properties = 5, .width = 37, .height = 23 },    /* Text_button_DATE@A3_C1, 101 */
    { .dataOffset = 2199388, .properties = 5, .width = 48, .height = 23 },    /* Text_button_DATE@A4_C0, 101 */
    { .dataOffset = 2201596, .properties = 5, .width = 48, .height = 23 },    /* Text_button_DATE@A4_C1, 101 */
    { .dataOffset = 2203804, .properties = 5, .width = 59, .height = 23 },    /* Text_button_DATE@A5_C0, 101 */
    { .dataOffset = 2206518, .properties = 5, .width = 59, .height = 23 },    /* Text_button_DATE@A5_C1, 101 */
    { .dataOffset = 2209232, .properties = 5, .width = 42, .height = 23 },    /* Text_button_DATE@A6_C0, 101 */
    { .dataOffset = 2211164, .properties = 5, .width = 42, .height = 23 },    /* Text_button_DATE@A6_C1, 101 */
    { .dataOffset = 2213096, .properties = 5, .width = 36, .height = 23 },    /* Text_button_DATE@A7_C0, 101 */
    { .dataOffset = 2214752, .properties = 5, .width = 36, .height = 23 },    /* Text_button_DATE@A7_C1, 101 */
    { .dataOffset = 2216408, .properties = 5, .width = 37, .height = 23 },    /* Text_button_DATE@A8_C0, 101 */
    { .dataOffset = 2218110, .properties = 5, .width = 37, .height = 23 },    /* Text_button_DATE@A8_C1, 101 */
    { .dataOffset = 2219812, .properties = 5, .width = 34, .height = 23 },    /* Text_button_DATE@A9_C0, 101 */
    { .dataOffset = 2221376, .properties = 5, .width = 34, .height = 23 },    /* Text_button_DATE@A9_C1, 101 */
    { .dataOffset = 2222940, .properties = 5, .width = 31, .height = 23 },    /* Text_button_INFO@A0_C0, 101 */
    { .dataOffset = 2224366, .properties = 5, .width = 31, .height = 23 },    /* Text_button_INFO@A0_C1, 101 */
    { .dataOffset = 2225792, .properties = 5, .width = 31, .height = 23 },    /* Text_button_INFO@A1_C0, 101 */
    { .dataOffset = 2227218, .properties = 5, .width = 31, .height = 23 },    /* Text_button_INFO@A1_C1, 101 */
    { .dataOffset = 2228644, .properties = 5, .width = 31, .height = 23 },    /* Text_button_INFO@A2_C0, 101 */
    { .dataOffset = 2230070, .properties = 5, .width = 31, .height = 23 },    /* Text_button_INFO@A2_C1, 101 */
    { .dataOffset = 2231496, .properties = 5, .width = 31, .height = 23 },    /* Text_button_INFO@A3_C0, 101 */
    { .dataOffset = 2232922, .properties = 5, .width = 31, .height = 23 },    /* Text_button_INFO@A3_C1, 101 */
    { .dataOffset = 2234348, .properties = 5, .width = 98, .height = 23 },    /* Text_button_INFO@A4_C0, 101 */
    { .dataOffset = 2238856, .properties = 5, .width = 98, .height = 23 },    /* Text_button_INFO@A4_C1, 101 */
    { .dataOffset = 2243364, .properties = 5, .width = 102, .height = 23 },    /* Text_button_INFO@A5_C0, 101 */
    { .dataOffset = 2248056, .properties = 5, .width = 102, .height = 23 },    /* Text_button_INFO@A5_C1, 101 */
    { .dataOffset = 2252748, .properties = 5, .width = 112, .height = 23 },    /* Text_button_INFO@A6_C0, 101 */
    { .dataOffset = 2257900, .properties = 5, .width = 112, .height = 23 },    /* Text_button_INFO@A6_C1, 101 */
    { .dataOffset = 2263052, .properties = 5, .width = 40, .height = 23 },    /* Text_button_INFO@A7_C0, 101 */
    { .dataOffset = 2264892, .properties = 5, .width = 40, .height = 23 },    /* Text_button_INFO@A7_C1, 101 */
    { .dataOffset = 2266732, .properties = 5, .width = 40, .height = 23 },    /* Text_button_INFO@A8_C0, 101 */
    { .dataOffset = 2268572, .properties = 5, .width = 40, .height = 23 },    /* Text_button_INFO@A8_C1, 101 */
    { .dataOffset = 2270412, .properties = 5, .width = 35, .height = 23 },    /* Text_button_INFO@A9_C0, 101 */
    { .dataOffset = 2272022, .properties = 5, .width = 35, .height = 23 },    /* Text_button_INFO@A9_C1, 101 */
    { .dataOffset = 2273632, .properties = 5, .width = 112, .height = 23 },    /* Text_button_INTERN_TEMP@A0_C0, 101 */
    { .dataOffset = 2278784, .properties = 5, .width = 112, .height = 23 },    /* Text_button_INTERN_TEMP@A0_C1, 101 */
    { .dataOffset = 2283936, .properties = 5, .width = 112, .height = 23 },    /* Text_button_INTERN_TEMP@A1_C0, 101 */
    { .dataOffset = 2289088, .properties = 5, .width = 112, .height = 23 },    /* Text_button_INTERN_TEMP@A1_C1, 101 */
    { .dataOffset = 2294240, .properties = 5, .width = 161, .height = 23 },    /* Text_button_INTERN_TEMP@A2_C0, 101 */
    { .dataOffset = 2301646, .properties = 5, .width = 161, .height = 23 },    /* Text_button_INTERN_TEMP@A2_C1, 101 */
    { .dataOffset = 2309052, .properties = 5, .width = 171, .height = 23 },    /* Text_button_INTERN_TEMP@A3_C0, 101 */
    { .dataOffset = 2316918, .properties = 5, .width = 171, .height = 23 },    /* Text_button_INTERN_TEMP@A3_C1, 101 */
    { .dataOffset = 2324784, .properties = 5, .width = 172, .height = 23 },    /* Text_button_INTERN_TEMP@A4_C0, 101 */
    { .dataOffset = 2332696, .properties = 5, .width = 172, .height = 23 },    /* Text_button_INTERN_TEMP@A4_C1, 101 */
    { .dataOffset = 2340608, .properties = 5, .width = 172, .height = 23 },    /* Text_button_INTERN_TEMP@A5_C0, 101 */
    { .dataOffset = 2348520, .properties = 5, .width = 172, .height = 23 },    /* Text_button_INTERN_TEMP@A5_C1, 101 */
    { .dataOffset = 2356432, .properties = 5, .width = 221, .height = 23 },    /* Text_button_INTERN_TEMP@A6_C0, 101 */
    { .dataOffset = 2366598, .properties = 5, .width = 221, .height = 23 },    /* Text_button_INTERN_TEMP@A6_C1, 101 */
    { .dataOffset = 2376764, .properties = 5, .width = 86, .height = 23 },    /* Text_button_INTERN_TEMP@A7_C0, 101 */
    { .dataOffset = 2380720, .properties = 5, .width = 86, .height = 23 },    /* Text_button_INTERN_TEMP@A7_C1, 101 */
    { .dataOffset = 2384676, .properties = 5, .width = 83, .height = 23 },    /* Text_button_INTERN_TEMP@A8_C0, 101 */
    { .dataOffset = 2388494, .properties = 5, .width = 83, .height = 23 },    /* Text_button_INTERN_TEMP@A8_C1, 101 */
    { .dataOffset = 2392312, .properties = 5, .width = 80, .height = 23 },    /* Text_button_INTERN_TEMP@A9_C0, 101 */
    { .dataOffset = 2395992, .properties = 5, .width = 80, .height = 23 },    /* Text_button_INTERN_TEMP@A9_C1, 101 */
    { .dataOffset = 2399672, .properties = 5, .width = 76, .height = 23 },    /* Text_button_KEYBOARD@A0_C0, 101 */
    { .dataOffset = 2403168, .properties = 5, .width = 76, .height = 23 },    /* Text_button_KEYBOARD@A0_C1, 101 */
    { .dataOffset = 2406664, .properties = 5, .width = 104, .height = 23 },    /* Text_button_KEYBOARD@A1_C0, 101 */
    { .dataOffset = 2411448, .properties = 5, .width = 104, .height = 23 },    /* Text_button_KEYBOARD@A1_C1, 101 */
    { .dataOffset = 2416232, .properties = 5, .width = 69, .height = 23 },    /* Text_button_KEYBOARD@A2_C0, 101 */
    { .dataOffset = 2419406, .properties = 5, .width = 69, .height = 23 },    /* Text_button_KEYBOARD@A2_C1, 101 */
    { .dataOffset = 2422580, .properties = 5, .width = 55, .height = 23 },    /* Text_button_KEYBOARD@A3_C0, 101 */
    { .dataOffset = 2425110, .properties = 5, .width = 55, .height = 23 },    /* Text_button_KEYBOARD@A3_C1, 101 */
    { .dataOffset = 2427640, .properties = 5, .width = 66, .height = 23 },    /* Text_button_KEYBOARD@A4_C0, 101 */
    { .dataOffset = 2430676, .properties = 5, .width = 66, .height = 23 },    /* Text_button_KEYBOARD@A4_C1, 101 */
    { .dataOffset = 2433712, .properties = 5, .width = 67, .height = 23 },    /* Text_button_KEYBOARD@A5_C0, 101 */
    { .dataOffset = 2436794, .properties = 5, .width = 67, .height = 23 },    /* Text_button_KEYBOARD@A5_C1, 101 */
    { .dataOffset = 2439876, .properties = 5, .width = 100, .height = 23 },    /* Text_button_KEYBOARD@A6_C0, 101 */
    { .dataOffset = 2444476, .properties = 5, .width = 100, .height = 23 },    /* Text_button_KEYBOARD@A6_C1, 101 */
    { .dataOffset = 2449076, .properties = 5, .width = 40, .height = 23 },    /* Text_button_KEYBOARD@A7_C0, 101 */
    { .dataOffset = 2450916, .properties = 5, .width = 40, .height = 23 },    /* Text_button_KEYBOARD@A7_C1, 101 */
    { .dataOffset = 2452756, .properties = 5, .width = 80, .height = 23 },    /* Text_button_KEYBOARD@A8_C0, 101 */
    { .dataOffset = 2456436, .properties = 5, .width = 80, .height = 23 },    /* Text_button_KEYBOARD@A8_C1, 101 */
    { .dataOffset = 2460116, .properties = 5, .width = 53, .height = 23 },    /* Text_button_KEYBOARD@A9_C0, 101 */
    { .dataOffset = 2462554, .properties = 5, .width = 53, .height = 23 },    /* Text_button_KEYBOARD@A9_C1, 101 */
    { .dataOffset = 2464992, .properties = 5, .width = 80, .height = 23 },    /* Text_button_LANGUAGE@A0_C0, 101 */
    { .dataOffset = 2468672, .properties = 5, .width = 80, .height = 23 },    /* Text_button_LANGUAGE@A0_C1, 101 */
    { .dataOffset = 2472352, .properties = 5, .width = 35, .height = 23 },    /* Text_button_LANGUAGE@A1_C0, 101 */
    { .dataOffset = 2473962, .properties = 5, .width = 35, .height = 23 },    /* Text_button_LANGUAGE@A1_C1, 101 */
    { .dataOffset = 2475572, .properties = 5, .width = 67, .height = 23 },    /* Text_button_LANGUAGE@A2_C0, 101 */
    { .dataOffset = 2478654, .properties = 5, .width = 67, .height = 23 },    /* Text_button_LANGUAGE@A2_C1, 101 */
    { .dataOffset = 2481736, .properties = 5, .width = 59, .height = 23 },    /* Text_button_LANGUAGE@A3_C0, 101 */
    { .dataOffset = 2484450, .properties = 5, .width = 59, .height = 23 },    /* Text_button_LANGUAGE@A3_C1, 101 */
    { .dataOffset = 2487164, .properties = 5, .width = 55, .height = 23 },    /* Text_button_LANGUAGE@A4_C0, 101 */
    { .dataOffset = 2489694, .properties = 5, .width = 55, .height = 23 },    /* Text_button_LANGUAGE@A4_C1, 101 */
    { .dataOffset = 2492224, .properties = 5, .width = 53, .height = 23 },    /* Text_button_LANGUAGE@A5_C0, 101 */
    { .dataOffset = 2494662, .properties = 5, .width = 53, .height = 23 },    /* Text_button_LANGUAGE@A5_C1, 101 */
    { .dataOffset = 2497100, .properties = 5, .width = 45, .height = 23 },    /* Text_button_LANGUAGE@A6_C0, 101 */
    { .dataOffset = 2499170, .properties = 5, .width = 45, .height = 23 },    /* Text_button_LANGUAGE@A6_C1, 101 */
    { .dataOffset = 2501240, .properties = 5, .width = 39, .height = 23 },    /* Text_button_LANGUAGE@A7_C0, 101 */
    { .dataOffset = 2503034, .properties = 5, .width = 39, .height = 23 },    /* Text_button_LANGUAGE@A7_C1, 101 */
    { .dataOffset = 2504828, .properties = 5, .width = 39, .height = 23 },    /* Text_button_LANGUAGE@A8_C0, 101 */
    { .dataOffset = 2506622, .properties = 5, .width = 39, .height = 23 },    /* Text_button_LANGUAGE@A8_C1, 101 */
    { .dataOffset = 2508416, .properties = 5, .width = 32, .height = 23 },    /* Text_button_LANGUAGE@A9_C0, 101 */
    { .dataOffset = 2509888, .properties = 5, .width = 32, .height = 23 },    /* Text_button_LANGUAGE@A9_C1, 101 */
    { .dataOffset = 2511360, .properties = 5, .width = 113, .height = 23 },    /* Text_button_MEASUREMENT@A0_C0, 101 */
    { .dataOffset = 2516558, .properties = 5, .width = 113, .height = 23 },    /* Text_button_MEASUREMENT@A0_C1, 101 */
    { .dataOffset = 2521756, .properties = 5, .width = 65, .height = 23 },    /* Text_button_MEASUREMENT@A1_C0, 101 */
    { .dataOffset = 2524746, .properties = 5, .width = 65, .height = 23 },    /* Text_button_MEASUREMENT@A1_C1, 101 */
    { .dataOffset = 2527736, .properties = 5, .width = 74, .height = 23 },    /* Text_button_MEASUREMENT@A2_C0, 101 */
    { .dataOffset = 2531140, .properties = 5, .width = 74, .height = 23 },    /* Text_button_MEASUREMENT@A2_C1, 101 */
    { .dataOffset = 2534544, .properties = 5, .width = 60, .height = 23 },    /* Text_button_MEASUREMENT@A3_C0, 101 */
    { .dataOffset = 2537304, .properties = 5, .width = 60, .height = 23 },    /* Text_button_MEASUREMENT@A3_C1, 101 */
    { .dataOffset = 2540064, .properties = 5, .width = 74, .height = 23 },    /* Text_button_MEASUREMENT@A4_C0, 101 */
    { .dataOffset = 2543468, .properties = 5, .width = 74, .height = 23 },    /* Text_button_MEASUREMENT@A4_C1, 101 */
    { .dataOffset = 2546872, .properties = 5, .width = 100, .height = 23 },    /* Text_button_MEASUREMENT@A5_C0, 101 */
    { .dataOffset = 2551472, .properties = 5, .width = 100, .height = 23 },    /* Text_button_MEASUREMENT@A5_C1, 101 */
    { .dataOffset = 2556072, .properties = 5, .width = 96, .height = 23 },    /* Text_button_MEASUREMENT@A6_C0, 101 */
    { .dataOffset = 2560488, .properties = 5, .width = 96, .height = 23 },    /* Text_button_MEASUREMENT@A6_C1, 101 */
    { .dataOffset = 2564904, .properties = 5, .width = 40, .height = 23 },    /* Text_button_MEASUREMENT@A7_C0, 101 */
    { .dataOffset = 2566744, .properties = 5, .width = 40, .height = 23 },    /* Text_button_MEASUREMENT@A7_C1, 101 */
    { .dataOffset = 2568584, .properties = 5, .width = 38, .height = 23 },    /* Text_button_MEASUREMENT@A8_C0, 101 */
    { .dataOffset = 2570332, .properties = 5, .width = 38, .height = 23 },    /* Text_button_MEASUREMENT@A8_C1, 101 */
    { .dataOffset = 2572080, .properties = 5, .width = 35, .height = 23 },    /* Text_button_MEASUREMENT@A9_C0, 101 */
    { .dataOffset = 2573690, .properties = 5, .width = 35, .height = 23 },    /* Text_button_MEASUREMENT@A9_C1, 101 */
    { .dataOffset = 2575300, .properties = 5, .width = 67, .height = 23 },    /* Text_button_SETTINGS@A0_C0, 101 */
    { .dataOffset = 2578382, .properties = 5, .width = 67, .height = 23 },    /* Text_button_SETTINGS@A0_C1, 101 */
    { .dataOffset = 2581464, .properties = 5, .width = 93, .height = 23 },    /* Text_button_SETTINGS@A1_C0, 101 */
    { .dataOffset = 2585742, .properties = 5, .width = 93, .height = 23 },    /* Text_button_SETTINGS@A1_C1, 101 */
    { .dataOffset = 2590020, .properties = 5, .width = 109, .height = 23 },    /* Text_button_SETTINGS@A2_C0, 101 */
    { .dataOffset = 2595034, .properties = 5, .width = 109, .height = 23 },    /* Text_button_SETTINGS@A2_C1, 101 */
    { .dataOffset = 2600048, .properties = 5, .width = 94, .height = 23 },    /* Text_button_SETTINGS@A3_C0, 101 */
    { .dataOffset = 2604372, .properties = 5, .width = 94, .height = 23 },    /* Text_button_SETTINGS@A3_C1, 101 */
    { .dataOffset = 2608696, .properties = 5, .width = 114, .height = 23 },    /* Text_button_SETTINGS@A4_C0, 101 */
    { .dataOffset = 2613940, .properties = 5, .width = 114, .height = 23 },    /* Text_button_SETTINGS@A4_C1, 101 */
    { .dataOffset = 2619184, .properties = 5, .width = 105, .height = 23 },    /* Text_button_SETTINGS@A5_C0, 101 */
    { .dataOffset = 2624014, .properties = 5, .width = 105, .height = 23 },    /* Text_button_SETTINGS@A5_C1, 101 */
    { .dataOffset = 2628844, .properties = 5, .width = 98, .height = 23 },    /* Text_button_SETTINGS@A6_C0, 101 */
    { .dataOffset = 2633352, .properties = 5, .width = 98, .height = 23 },    /* Text_button_SETTINGS@A6_C1, 101 */
    { .dataOffset = 2637860, .properties = 5, .width = 39, .height = 23 },    /* Text_button_SETTINGS@A7_C0, 101 */
    { .dataOffset = 2639654, .properties = 5, .width = 39, .height = 23 },    /* Text_button_SETTINGS@A7_C1, 101 */
    { .dataOffset = 2641448, .properties = 5, .width = 38, .height = 23 },    /* Text_button_SETTINGS@A8_C0, 101 */
    { .dataOffset = 2643196, .properties = 5, .width = 38, .height = 23 },    /* Text_button_SETTINGS@A8_C1, 101 */
    { .dataOffset = 2644944, .properties = 5, .width = 33, .height = 23 },    /* Text_button_SETTINGS@A9_C0, 101 */
    { .dataOffset = 2646462, .properties = 5, .width = 33, .height = 23 },    /* Text_button_SETTINGS@A9_C1, 101 */
    { .dataOffset = 2647980, .properties = 5, .width = 47, .height = 23 },    /* Text_button_SETUP@A0_C0, 101 */
    { .dataOffset = 2650142, .properties = 5, .width = 47, .height = 23 },    /* Text_button_SETUP@A0_C1, 101 */
    { .dataOffset = 2652304, .properties = 5, .width = 51, .height = 23 },    /* Text_button_SETUP@A1_C0, 101 */
    { .dataOffset = 2654650, .properties = 5, .width = 51, .height = 23 },    /* Text_button_SETUP@A1_C1, 101 */
    { .dataOffset = 2656996, .properties = 5, .width = 91, .height = 23 },    /* Text_button_SETUP@A2_C0, 101 */
    { .dataOffset = 2661182, .properties = 5, .width = 91, .height = 23 },    /* Text_button_SETUP@A2_C1, 101 */
    { .dataOffset = 2665368, .properties = 5, .width = 99, .height = 23 },    /* Text_button_SETUP@A3_C0, 101 */
    { .dataOffset = 2669922, .properties = 5, .width = 99, .height = 23 },    /* Text_button_SETUP@A3_C1, 101 */
    { .dataOffset = 2674476, .properties = 5, .width = 59, .height = 23 },    /* Text_button_SETUP@A4_C0, 101 */
    { .dataOffset = 2677190, .properties = 5, .width = 59, .height = 23 },    /* Text_button_SETUP@A4_C1, 101 */
    { .dataOffset = 2679904, .properties = 5, .width = 103, .height = 23 },    /* Text_button_SETUP@A5_C0, 101 */
    { .dataOffset = 2684642, .properties = 5, .width = 103, .height = 23 },    /* Text_button_SETUP@A5_C1, 101 */
    { .dataOffset = 2689380, .properties = 5, .width = 92, .height = 23 },    /* Text_button_SETUP@A6_C0, 101 */
    { .dataOffset = 2693612, .properties = 5, .width = 92, .height = 23 },    /* Text_button_SETUP@A6_C1, 101 */
    { .dataOffset = 2697844, .properties = 5, .width = 39, .height = 23 },    /* Text_button_SETUP@A7_C0, 101 */
    { .dataOffset = 2699638, .properties = 5, .width = 39, .height = 23 },    /* Text_button_SETUP@A7_C1, 101 */
    { .dataOffset = 2701432, .properties = 5, .width = 84, .height = 23 },    /* Text_button_SETUP@A8_C0, 101 */
    { .dataOffset = 2705296, .properties = 5, .width = 84, .height = 23 },    /* Text_button_SETUP@A8_C1, 101 */
    { .dataOffset = 2709160, .properties = 5, .width = 33, .height = 23 },    /* Text_button_SETUP@A9_C0, 101 */
    { .dataOffset = 2710678, .properties = 5, .width = 33, .height = 23 },    /* Text_button_SETUP@A9_C1, 101 */
    { .dataOffset = 2712196, .properties = 5, .width = 57, .height = 23 },    /* Text_button_THEME@A0_C0, 101 */
    { .dataOffset = 2714818, .properties = 5, .width = 57, .height = 23 },    /* Text_button_THEME@A0_C1, 101 */
    { .dataOffset = 2717440, .properties = 5, .width = 56, .height = 23 },    /* Text_button_THEME@A1_C0, 101 */
    { .dataOffset = 2720016, .properties = 5, .width = 56, .height = 23 },    /* Text_button_THEME@A1_C1, 101 */
    { .dataOffset = 2722592, .properties = 5, .width = 56, .height = 23 },    /* Text_button_THEME@A2_C0, 101 */
    { .dataOffset = 2725168, .properties = 5, .width = 56, .height = 23 },    /* Text_button_THEME@A2_C1, 101 */
    { .dataOffset = 2727744, .properties = 5, .width = 57, .height = 23 },    /* Text_button_THEME@A3_C0, 101 */
    { .dataOffset = 2730366, .properties = 5, .width = 57, .height = 23 },    /* Text_button_THEME@A3_C1, 101 */
    { .dataOffset = 2732988, .properties = 5, .width = 46, .height = 23 },    /* Text_button_THEME@A4_C0, 101 */
    { .dataOffset = 2735104, .properties = 5, .width = 46, .height = 23 },    /* Text_button_THEME@A4_C1, 101 */
    { .dataOffset = 2737220, .properties = 5, .width = 46, .height = 23 },    /* Text_button_THEME@A5_C0, 101 */
    { .dataOffset = 2739336, .properties = 5, .width = 46, .height = 23 },    /* Text_button_THEME@A5_C1, 101 */
    { .dataOffset = 2741452, .properties = 5, .width = 44, .height = 23 },    /* Text_button_THEME@A6_C0, 101 */
    { .dataOffset = 2743476, .properties = 5, .width = 44, .height = 23 },    /* Text_button_THEME@A6_C1, 101 */
    { .dataOffset = 2745500, .properties = 5, .width = 39, .height = 23 },    /* Text_button_THEME@A7_C0, 101 */
    { .dataOffset = 2747294, .properties = 5, .width = 39, .height = 23 },    /* Text_button_THEME@A7_C1, 101 */
    { .dataOffset = 2749088, .properties = 5, .width = 46, .height = 23 },    /* Text_button_THEME@A8_C0, 101 */
    { .dataOffset = 2751204, .properties = 5, .width = 46, .height = 23 },    /* Text_button_THEME@A8_C1, 101 */
    { .dataOffset = 2753320, .properties = 5, .width = 33, .height = 23 },    /* Text_button_THEME@A9_C0, 101 */
    { .dataOffset = 2754838, .properties = 5, .width = 33, .height = 23 },    /* Text_button_THEME@A9_C1, 101 */
    { .dataOffset = 2756356, .properties = 5, .width = 41, .height = 23 },    /* Text_button_TIME@A0_C0, 101 */
    { .dataOffset = 2758242, .properties = 5, .width = 41, .height = 23 },    /* Text_button_TIME@A0_C1, 101 */
    { .dataOffset = 2760128, .properties = 5, .width = 29, .height = 23 },    /* Text_button_TIME@A1_C0, 101 */
    { .dataOffset = 2761462, .properties = 5, .width = 29, .height = 23 },    /* Text_button_TIME@A1_C1, 101 */
    { .dataOffset = 2762796, .properties = 5, .width = 31, .height = 23 },    /* Text_button_TIME@A2_C0, 101 */
    { .dataOffset = 2764222, .properties = 5, .width = 31, .height = 23 },    /* Text_button_TIME@A2_C1, 101 */
    { .dataOffset = 2765648, .properties = 5, .width = 48, .height = 23 },    /* Text_button_TIME@A3_C0, 101 */
    { .dataOffset = 2767856, .properties = 5, .width = 48, .height = 23 },    /* Text_button_TIME@A3_C1, 101 */
    { .dataOffset = 2770064, .properties = 5, .width = 38, .height = 23 },    /* Text_button_TIME@A4_C0, 101 */
    { .dataOffset = 2771812, .properties = 5, .width = 38, .height = 23 },    /* Text_button_TIME@A4_C1, 101 */
    { .dataOffset = 2773560, .properties = 5, .width = 27, .height = 23 },    /* Text_button_TIME@A5_C0, 101 */
    { .dataOffset = 2774802, .properties = 5, .width = 27, .height = 23 },    /* Text_button_TIME@A5_C1, 101 */
    { .dataOffset = 2776044, .properties = 5, .width = 53, .height = 23 },    /* Text_button_TIME@A6_C0, 101 */
    { .dataOffset = 2778482, .properties = 5, .width = 53, .height = 23 },    /* Text_button_TIME@A6_C1, 101 */
    { .dataOffset = 2780920, .properties = 5, .width = 38, .height = 23 },    /* Text_button_TIME@A7_C0, 101 */
    { .dataOffset = 2782668, .properties = 5, .width = 38, .height = 23 },    /* Text_button_TIME@A7_C1, 101 */
    { .dataOffset = 2784416, .properties = 5, .width = 37, .height = 23 },    /* Text_button_TIME@A8_C0, 101 */
    { .dataOffset = 2786118, .properties = 5, .width = 37, .height = 23 },    /* Text_button_TIME@A8_C1, 101 */
    { .dataOffset = 2787820, .properties = 5, .width = 35, .height = 23 },    /* Text_button_TIME@A9_C0, 101 */
    { .dataOffset = 2789430, .properties = 5, .width = 35, .height = 23 },    /* Text_button_TIME@A9_C1, 101 */
    { .dataOffset = 2791040, .properties = 5, .width = 41, .height = 23 },    /* Text_button_UNITS@A0_C0, 101 */
    { .dataOffset = 2792926, .properties = 5, .width = 41, .height = 23 },    /* Text_button_UNITS@A0_C1, 101 */
    { .dataOffset = 2794812, .properties = 5, .width = 79, .height = 23 },    /* Text_button_UNITS@A1_C0, 101 */
    { .dataOffset = 2798446, .properties = 5, .width = 79, .height = 23 },    /* Text_button_UNITS@A1_C1, 101 */
    { .dataOffset = 2802080, .properties = 5, .width = 74, .height = 23 },    /* Text_button_UNITS@A2_C0, 101 */
    { .dataOffset = 2805484, .properties = 5, .width = 74, .height = 23 },    /* Text_button_UNITS@A2_C1, 101 */
    { .dataOffset = 2808888, .properties = 5, .width = 51, .height = 23 },    /* Text_button_UNITS@A3_C0, 101 */
    { .dataOffset = 2811234, .properties = 5, .width = 51, .height = 23 },    /* Text_button_UNITS@A3_C1, 101 */
    { .dataOffset = 2813580, .properties = 5, .width = 75, .height = 23 },    /* Text_button_UNITS@A4_C0, 101 */
    { .dataOffset = 2817030, .properties = 5, .width = 75, .height = 23 },    /* Text_button_UNITS@A4_C1, 101 */
    { .dataOffset = 2820480, .properties = 5, .width = 41, .height = 23 },    /* Text_button_UNITS@A5_C0, 101 */
    { .dataOffset = 2822366, .properties = 5, .width = 41, .height = 23 },    /* Text_button_UNITS@A5_C1, 101 */
    { .dataOffset = 2824252, .properties = 5, .width = 63, .height = 23 },    /* Text_button_UNITS@A6_C0, 101 */
    { .dataOffset = 2827150, .properties = 5, .width = 63, .height = 23 },    /* Text_button_UNITS@A6_C1, 101 */
    { .dataOffset = 2830048, .properties = 5, .width = 39, .height = 23 },    /* Text_button_UNITS@A7_C0, 101 */
    { .dataOffset = 2831842, .properties = 5, .width = 39, .height = 23 },    /* Text_button_UNITS@A7_C1, 101 */
    { .dataOffset = 2833636, .properties = 5, .width = 39, .height = 23 },    /* Text_button_UNITS@A8_C0, 101 */
    { .dataOffset = 2835430, .properties = 5, .width = 39, .height = 23 },    /* Text_button_UNITS@A8_C1, 101 */
    { .dataOffset = 2837224, .properties = 5, .width = 32, .height = 23 },    /* Text_button_UNITS@A9_C0, 101 */
    { .dataOffset = 2838696, .properties = 5, .width = 32, .height = 23 },    /* Text_button_UNITS@A9_C1, 101 */
    { .dataOffset = 2840168, .properties = 5, .width = 116, .height = 26 },    /* Text-Dft_ACCENT_COLOR@A0_C0, 101 */
    { .dataOffset = 2846200, .properties = 5, .width = 116, .height = 26 },    /* Text-Dft_ACCENT_COLOR@A0_C1, 101 */
    { .dataOffset = 2852232, .properties = 5, .width = 114, .height = 26 },    /* Text-Dft_ACCENT_COLOR@A1_C0, 101 */
    { .dataOffset = 2858160, .properties = 5, .width = 114, .height = 26 },    /* Text-Dft_ACCENT_COLOR@A1_C1, 101 */
    { .dataOffset = 2864088, .properties = 5, .width = 164, .height = 26 },    /* Text-Dft_ACCENT_COLOR@A2_C0, 101 */
    { .dataOffset = 2872616, .properties = 5, .width = 164, .height = 26 },    /* Text-Dft_ACCENT_COLOR@A2_C1, 101 */
    { .dataOffset = 2881144, .properties = 5, .width = 208, .height = 26 },    /* Text-Dft_ACCENT_COLOR@A3_C0, 101 */
    { .dataOffset = 2891960, .properties = 5, .width = 208, .height = 26 },    /* Text-Dft_ACCENT_COLOR@A3_C1, 101 */
    { .dataOffset = 2902776, .properties = 5, .width = 143, .height = 26 },    /* Text-Dft_ACCENT_COLOR@A4_C0, 101 */
    { .dataOffset = 2910212, .properties = 5, .width = 143, .height = 26 },    /* Text-Dft_ACCENT_COLOR@A4_C1, 101 */
    { .dataOffset = 2917648, .properties = 5, .width = 152, .height = 26 },    /* Text-Dft_ACCENT_COLOR@A5_C0, 101 */
    { .dataOffset = 2925552, .properties = 5, .width = 152, .height = 26 },    /* Text-Dft_ACCENT_COLOR@A5_C1, 101 */
    { .dataOffset = 2933456, .properties = 5, .width = 159, .height = 26 },    /* Text-Dft_ACCENT_COLOR@A6_C0, 101 */
    { .dataOffset = 2941724, .properties = 5, .width = 159, .height = 26 },    /* Text-Dft_ACCENT_COLOR@A6_C1, 101 */
    { .dataOffset = 2949992, .properties = 5, .width = 63, .height = 26 },    /* Text-Dft_ACCENT_COLOR@A7_C0, 101 */
    { .dataOffset = 2953268, .properties = 5, .width = 63, .height = 26 },    /* Text-Dft_ACCENT_COLOR@A7_C1, 101 */
    { .dataOffset = 2956544, .properties = 5, .width = 132, .height = 26 },    /* Text-Dft_ACCENT_COLOR@A8_C0, 101 */
    { .dataOffset = 2963408, .properties = 5, .width = 132, .height = 26 },    /* Text-Dft_ACCENT_COLOR@A8_C1, 101 */
    { .dataOffset = 2970272, .properties = 5, .width = 86, .height = 26 },    /* Text-Dft_ACCENT_COLOR@A9_C0, 101 */
    { .dataOffset = 2974744, .properties = 5, .width = 86, .height = 26 },    /* Text-Dft_ACCENT_COLOR@A9_C1, 101 */
    { .dataOffset = 2979216, .properties = 5, .width = 142, .height = 26 },    /* Text-Dft_ACTIVATE_ALARM@A0_C0, 101 */
    { .dataOffset = 2986600, .properties = 5, .width = 142, .height = 26 },    /* Text-Dft_ACTIVATE_ALARM@A0_C1, 101 */
    { .dataOffset = 2993984, .properties = 5, .width = 153, .height = 26 },    /* Text-Dft_ACTIVATE_ALARM@A1_C0, 101 */
    { .dataOffset = 3001940, .properties = 5, .width = 153, .height = 26 },    /* Text-Dft_ACTIVATE_ALARM@A1_C1, 101 */
    { .dataOffset = 3009896, .properties = 5, .width = 158, .height = 26 },    /* Text-Dft_ACTIVATE_ALARM@A2_C0, 101 */
    { .dataOffset = 3018112, .properties = 5, .width = 158, .height = 26 },    /* Text-Dft_ACTIVATE_ALARM@A2_C1, 101 */
    { .dataOffset = 3026328, .properties = 5, .width = 150, .height = 26 },    /* Text-Dft_ACTIVATE_ALARM@A3_C0, 101 */
    { .dataOffset = 3034128, .properties = 5, .width = 150, .height = 26 },    /* Text-Dft_ACTIVATE_ALARM@A3_C1, 101 */
    { .dataOffset = 3041928, .properties = 5, .width = 172, .height = 26 },    /* Text-Dft_ACTIVATE_ALARM@A4_C0, 101 */
    { .dataOffset = 3050872, .properties = 5, .width = 172, .height = 26 },    /* Text-Dft_ACTIVATE_ALARM@A4_C1, 101 */
    { .dataOffset = 3059816, .properties = 5, .width = 163, .height = 26 },    /* Text-Dft_ACTIVATE_ALARM@A5_C0, 101 */
    { .dataOffset = 3068292, .properties = 5, .width = 163, .height = 26 },    /* Text-Dft_ACTIVATE_ALARM@A5_C1, 101 */
    { .dataOffset = 3076768, .properties = 5, .width = 293, .height = 26 },    /* Text-Dft_ACTIVATE_ALARM@A6_C0, 101 */
    { .dataOffset = 3092004, .properties = 5, .width = 293, .height = 26 },    /* Text-Dft_ACTIVATE_ALARM@A6_C1, 101 */
    { .dataOffset = 3107240, .properties = 5, .width = 107, .height = 26 },    /* Text-Dft_ACTIVATE_ALARM@A7_C0, 101 */
    { .dataOffset = 3112804, .properties = 5, .width = 107, .height = 26 },    /* Text-Dft_ACTIVATE_ALARM@A7_C1, 101 */
    { .dataOffset = 3118368, .properties = 5, .width = 230, .height = 26 },    /* Text-Dft_ACTIVATE_ALARM@A8_C0, 101 */
    { .dataOffset = 3130328, .properties = 5, .width = 230, .height = 26 },    /* Text-Dft_ACTIVATE_ALARM@A8_C1, 101 */
    { .dataOffset = 3142288, .properties = 5, .width = 260, .height = 26 },    /* Text-Dft_ACTIVATE_ALARM@A9_C0, 101 */
    { .dataOffset = 3155808, .properties = 5, .width = 260, .height = 26 },    /* Text-Dft_ACTIVATE_ALARM@A9_C1, 101 */
    { .dataOffset = 3169328, .properties = 5, .width = 70, .height = 26 },    /* Text-Dft_ALARM@A0_C0, 101 */
    { .dataOffset = 3172968, .properties = 5, .width = 70, .height = 26 },    /* Text-Dft_ALARM@A0_C1, 101 */
    { .dataOffset = 3176608, .properties = 5, .width = 70, .height = 26 },    /* Text-Dft_ALARM@A1_C0, 101 */
    { .dataOffset = 3180248, .properties = 5, .width = 70, .height = 26 },    /* Text-Dft_ALARM@A1_C1, 101 */
    { .dataOffset = 3183888, .properties = 5, .width = 70, .height = 26 },    /* Text-Dft_ALARM@A2_C0, 101 */
    { .dataOffset = 3187528, .properties = 5, .width = 70, .height = 26 },    /* Text-Dft_ALARM@A2_C1, 101 */
    { .dataOffset = 3191168, .properties = 5, .width = 81, .height = 26 },    /* Text-Dft_ALARM@A3_C0, 101 */
    { .dataOffset = 3195380, .properties = 5, .width = 81, .height = 26 },    /* Text-Dft_ALARM@A3_C1, 101 */
    { .dataOffset = 3199592, .properties = 5, .width = 81, .height = 26 },    /* Text-Dft_ALARM@A4_C0, 101 */
    { .dataOffset = 3203804, .properties = 5, .width = 81, .height = 26 },    /* Text-Dft_ALARM@A4_C1, 101 */
    { .dataOffset = 3208016, .properties = 5, .width = 86, .height = 26 },    /* Text-Dft_ALARM@A5_C0, 101 */
    { .dataOffset = 3212488, .properties = 5, .width = 86, .height = 26 },    /* Text-Dft_ALARM@A5_C1, 101 */
    { .dataOffset = 3216960, .properties = 5, .width = 93, .height = 26 },    /* Text-Dft_ALARM@A6_C0, 101 */
    { .dataOffset = 3221796, .properties = 5, .width = 93, .height = 26 },    /* Text-Dft_ALARM@A6_C1, 101 */
    { .dataOffset = 3226632, .properties = 5, .width = 59, .height = 26 },    /* Text-Dft_ALARM@A7_C0, 101 */
    { .dataOffset = 3229700, .properties = 5, .width = 59, .height = 26 },    /* Text-Dft_ALARM@A7_C1, 101 */
    { .dataOffset = 3232768, .properties = 5, .width = 59, .height = 26 },    /* Text-Dft_ALARM@A8_C0, 101 */
    { .dataOffset = 3235836, .properties = 5, .width = 59, .height = 26 },    /* Text-Dft_ALARM@A8_C1, 101 */
    { .dataOffset = 3238904, .properties = 5, .width = 75, .height = 26 },    /* Text-Dft_ALARM@A9_C0, 101 */
    { .dataOffset = 3242804, .properties = 5, .width = 75, .height = 26 },    /* Text-Dft_ALARM@A9_C1, 101 */
    { .dataOffset = 3246704, .properties = 4, .width = 42, .height = 26 },    /* Text-Dft_CHINESE_SIM@C0, 100 */
    { .dataOffset = 3248888, .properties = 4, .width = 51, .height = 26 },    /* Text-Dft_CHINESE_SIM@C1, 100 */
    { .dataOffset = 3251540, .properties = 5, .width = 112, .height = 26 },    /* Text-Dft_CURSOR_COLOR@A0_C0, 101 */
    { .dataOffset = 3257364, .properties = 5, .width = 112, .height = 26 },    /* Text-Dft_CURSOR_COLOR@A0_C1, 101 */
    { .dataOffset = 3263188, .properties = 5, .width = 110, .height = 26 },    /* Text-Dft_CURSOR_COLOR@A1_C0, 101 */
    { .dataOffset = 3268908, .properties = 5, .width = 110, .height = 26 },    /* Text-Dft_CURSOR_COLOR@A1_C1, 101 */
    { .dataOffset = 3274628, .properties = 5, .width = 165, .height = 26 },    /* Text-Dft_CURSOR_COLOR@A2_C0, 101 */
    { .dataOffset = 3283208, .properties = 5, .width = 165, .height = 26 },    /* Text-Dft_CURSOR_COLOR@A2_C1, 101 */
    { .dataOffset = 3291788, .properties = 5, .width = 172, .height = 26 },    /* Text-Dft_CURSOR_COLOR@A3_C0, 101 */
    { .dataOffset = 3300732, .properties = 5, .width = 172, .height = 26 },    /* Text-Dft_CURSOR_COLOR@A3_C1, 101 */
    { .dataOffset = 3309676, .properties = 5, .width = 144, .height = 26 },    /* Text-Dft_CURSOR_COLOR@A4_C0, 101 */
    { .dataOffset = 3317164, .properties = 5, .width = 144, .height = 26 },    /* Text-Dft_CURSOR_COLOR@A4_C1, 101 */
    { .dataOffset = 3324652, .properties = 5, .width = 166, .height = 26 },    /* Text-Dft_CURSOR_COLOR@A5_C0, 101 */
    { .dataOffset = 3333284, .properties = 5, .width = 166, .height = 26 },    /* Text-Dft_CURSOR_COLOR@A5_C1, 101 */
    { .dataOffset = 3341916, .properties = 5, .width = 128, .height = 26 },    /* Text-Dft_CURSOR_COLOR@A6_C0, 101 */
    { .dataOffset = 3348572, .properties = 5, .width = 128, .height = 26 },    /* Text-Dft_CURSOR_COLOR@A6_C1, 101 */
    { .dataOffset = 3355228, .properties = 5, .width = 88, .height = 26 },    /* Text-Dft_CURSOR_COLOR@A7_C0, 101 */
    { .dataOffset = 3359804, .properties = 5, .width = 88, .height = 26 },    /* Text-Dft_CURSOR_COLOR@A7_C1, 101 */
    { .dataOffset = 3364380, .properties = 5, .width = 109, .height = 26 },    /* Text-Dft_CURSOR_COLOR@A8_C0, 101 */
    { .dataOffset = 3370048, .properties = 5, .width = 109, .height = 26 },    /* Text-Dft_CURSOR_COLOR@A8_C1, 101 */
    { .dataOffset = 3375716, .properties = 5, .width = 86, .height = 26 },    /* Text-Dft_CURSOR_COLOR@A9_C0, 101 */
    { .dataOffset = 3380188, .properties = 5, .width = 86, .height = 26 },    /* Text-Dft_CURSOR_COLOR@A9_C1, 101 */
    { .dataOffset = 3384660, .properties = 4, .width = 19, .height = 26 },    /* Text-Dft_DEG_CEL@C0, 100 */
    { .dataOffset = 3385648, .properties = 4, .width = 27, .height = 26 },    /* Text-Dft_DEG_CEL@C1, 100 */
    { .dataOffset = 3387052, .properties = 4, .width = 18, .height = 26 },    /* Text-Dft_DEG_FAR@C0, 100 */
    { .dataOffset = 3387988, .properties = 4, .width = 25, .height = 26 },    /* Text-Dft_DEG_FAR@C1, 100 */
    { .dataOffset = 3389288, .properties = 4, .width = 102, .height = 26 },    /* Text-Dft_DUTCH@C0, 100 */
    { .dataOffset = 3394592, .properties = 4, .width = 111, .height = 26 },    /* Text-Dft_DUTCH@C1, 100 */
    { .dataOffset = 3400364, .properties = 4, .width = 64, .height = 26 },    /* Text-Dft_ENGLISH@C0, 100 */
    { .dataOffset = 3403692, .properties = 4, .width = 73, .height = 26 },    /* Text-Dft_ENGLISH@C1, 100 */
    { .dataOffset = 3407488, .properties = 4, .width = 76, .height = 26 },    /* Text-Dft_FRENCH@C0, 100 */
    { .dataOffset = 3411440, .properties = 4, .width = 85, .height = 26 },    /* Text-Dft_FRENCH@C1, 100 */
    { .dataOffset = 3415860, .properties = 4, .width = 72, .height = 26 },    /* Text-Dft_GERMAN@C0, 100 */
    { .dataOffset = 3419604, .properties = 4, .width = 81, .height = 26 },    /* Text-Dft_GERMAN@C1, 100 */
    { .dataOffset = 3423816, .properties = 5, .width = 124, .height = 26 },    /* Text-Dft_INTERN_TEMP@A0_C0, 101 */
    { .dataOffset = 3430264, .properties = 5, .width = 124, .height = 26 },    /* Text-Dft_INTERN_TEMP@A0_C1, 101 */
    { .dataOffset = 3436712, .properties = 5, .width = 124, .height = 26 },    /* Text-Dft_INTERN_TEMP@A1_C0, 101 */
    { .dataOffset = 3443160, .properties = 5, .width = 124, .height = 26 },    /* Text-Dft_INTERN_TEMP@A1_C1, 101 */
    { .dataOffset = 3449608, .properties = 5, .width = 178, .height = 26 },    /* Text-Dft_INTERN_TEMP@A2_C0, 101 */
    { .dataOffset = 3458864, .properties = 5, .width = 178, .height = 26 },    /* Text-Dft_INTERN_TEMP@A2_C1, 101 */
    { .dataOffset = 3468120, .properties = 5, .width = 191, .height = 26 },    /* Text-Dft_INTERN_TEMP@A3_C0, 101 */
    { .dataOffset = 3478052, .properties = 5, .width = 191, .height = 26 },    /* Text-Dft_INTERN_TEMP@A3_C1, 101 */
    { .dataOffset = 3487984, .properties = 5, .width = 191, .height = 26 },    /* Text-Dft_INTERN_TEMP@A4_C0, 101 */
    { .dataOffset = 3497916, .properties = 5, .width = 191, .height = 26 },    /* Text-Dft_INTERN_TEMP@A4_C1, 101 */
    { .dataOffset = 3507848, .properties = 5, .width = 191, .height = 26 },    /* Text-Dft_INTERN_TEMP@A5_C0, 101 */
    { .dataOffset = 3517780, .properties = 5, .width = 191, .height = 26 },    /* Text-Dft_INTERN_TEMP@A5_C1, 101 */
    { .dataOffset = 3527712, .properties = 5, .width = 245, .height = 26 },    /* Text-Dft_INTERN_TEMP@A6_C0, 101 */
    { .dataOffset = 3540452, .properties = 5, .width = 245, .height = 26 },    /* Text-Dft_INTERN_TEMP@A6_C1, 101 */
    { .dataOffset = 3553192, .properties = 5, .width = 96, .height = 26 },    /* Text-Dft_INTERN_TEMP@A7_C0, 101 */
    { .dataOffset = 3558184, .properties = 5, .width = 96, .height = 26 },    /* Text-Dft_INTERN_TEMP@A7_C1, 101 */
    { .dataOffset = 3563176, .properties = 5, .width = 93, .height = 26 },    /* Text-Dft_INTERN_TEMP@A8_C0, 101 */
    { .dataOffset = 3568012, .properties = 5, .width = 93, .height = 26 },    /* Text-Dft_INTERN_TEMP@A8_C1, 101 */
    { .dataOffset = 3572848, .properties = 5, .width = 89, .height = 26 },    /* Text-Dft_INTERN_TEMP@A9_C0, 101 */
    { .dataOffset = 3577476, .properties = 5, .width = 89, .height = 26 },    /* Text-Dft_INTERN_TEMP@A9_C1, 101 */
    { .dataOffset = 3582104, .properties = 4, .width = 65, .height = 26 },    /* Text-Dft_ITALIAN@C0, 100 */
    { .dataOffset = 3585484, .properties = 4, .width = 74, .height = 26 },    /* Text-Dft_ITALIAN@C1, 100 */
    { .dataOffset = 3589332, .properties = 4, .width = 63, .height = 26 },    /* Text-Dft_JAPANESE@C0, 100 */
    { .dataOffset = 3592608, .properties = 4, .width = 74, .height = 26 },    /* Text-Dft_JAPANESE@C1, 100 */
    { .dataOffset = 3596456, .properties = 4, .width = 58, .height = 26 },    /* Text-Dft_KOREAN@C0, 100 */
    { .dataOffset = 3599472, .properties = 4, .width = 68, .height = 26 },    /* Text-Dft_KOREAN@C1, 100 */
    { .dataOffset = 3603008, .properties = 5, .width = 125, .height = 26 },    /* Text-Dft_MEASUREMENT@A0_C0, 101 */
    { .dataOffset = 3609508, .properties = 5, .width = 125, .height = 26 },    /* Text-Dft_MEASUREMENT@A0_C1, 101 */
    { .dataOffset = 3616008, .properties = 5, .width = 71, .height = 26 },    /* Text-Dft_MEASUREMENT@A1_C0, 101 */
    { .dataOffset = 3619700, .properties = 5, .width = 71, .height = 26 },    /* Text-Dft_MEASUREMENT@A1_C1, 101 */
    { .dataOffset = 3623392, .properties = 5, .width = 81, .height = 26 },    /* Text-Dft_MEASUREMENT@A2_C0, 101 */
    { .dataOffset = 3627604, .properties = 5, .width = 81, .height = 26 },    /* Text-Dft_MEASUREMENT@A2_C1, 101 */
    { .dataOffset = 3631816, .properties = 5, .width = 67, .height = 26 },    /* Text-Dft_MEASUREMENT@A3_C0, 101 */
    { .dataOffset = 3635300, .properties = 5, .width = 67, .height = 26 },    /* Text-Dft_MEASUREMENT@A3_C1, 101 */
    { .dataOffset = 3638784, .properties = 5, .width = 82, .height = 26 },    /* Text-Dft_MEASUREMENT@A4_C0, 101 */
    { .dataOffset = 3643048, .properties = 5, .width = 82, .height = 26 },    /* Text-Dft_MEASUREMENT@A4_C1, 101 */
    { .dataOffset = 3647312, .properties = 5, .width = 110, .height = 26 },    /* Text-Dft_MEASUREMENT@A5_C0, 101 */
    { .dataOffset = 3653032, .properties = 5, .width = 110, .height = 26 },    /* Text-Dft_MEASUREMENT@A5_C1, 101 */
    { .dataOffset = 3658752, .properties = 5, .width = 106, .height = 26 },    /* Text-Dft_MEASUREMENT@A6_C0, 101 */
    { .dataOffset = 3664264, .properties = 5, .width = 106, .height = 26 },    /* Text-Dft_MEASUREMENT@A6_C1, 101 */
    { .dataOffset = 3669776, .properties = 5, .width = 43, .height = 26 },    /* Text-Dft_MEASUREMENT@A7_C0, 101 */
    { .dataOffset = 3672012, .properties = 5, .width = 43, .height = 26 },    /* Text-Dft_MEASUREMENT@A7_C1, 101 */
    { .dataOffset = 3674248, .properties = 5, .width = 43, .height = 26 },    /* Text-Dft_MEASUREMENT@A8_C0, 101 */
    { .dataOffset = 3676484, .properties = 5, .width = 43, .height = 26 },    /* Text-Dft_MEASUREMENT@A8_C1, 101 */
    { .dataOffset = 3678720, .properties = 5, .width = 39, .height = 26 },    /* Text-Dft_MEASUREMENT@A9_C0, 101 */
    { .dataOffset = 3680748, .properties = 5, .width = 39, .height = 26 },    /* Text-Dft_MEASUREMENT@A9_C1, 101 */
    { .dataOffset = 3682776, .properties = 4, .width = 76, .height = 26 },    /* Text-Dft_RUSSIAN@C0, 100 */
    { .dataOffset = 3686728, .properties = 4, .width = 85, .height = 26 },    /* Text-Dft_RUSSIAN@C1, 100 */
    { .dataOffset = 3691148, .properties = 5, .width = 112, .height = 26 },    /* Text-Dft_SET_ALARM_IN@A0_C0, 101 */
    { .dataOffset = 3696972, .properties = 5, .width = 112, .height = 26 },    /* Text-Dft_SET_ALARM_IN@A0_C1, 101 */
    { .dataOffset = 3702796, .properties = 5, .width = 80, .height = 26 },    /* Text-Dft_SET_ALARM_IN@A1_C0, 101 */
    { .dataOffset = 3706956, .properties = 5, .width = 80, .height = 26 },    /* Text-Dft_SET_ALARM_IN@A1_C1, 101 */
    { .dataOffset = 3711116, .properties = 5, .width = 125, .height = 26 },    /* Text-Dft_SET_ALARM_IN@A2_C0, 101 */
    { .dataOffset = 3717616, .properties = 5, .width = 125, .height = 26 },    /* Text-Dft_SET_ALARM_IN@A2_C1, 101 */
    { .dataOffset = 3724116, .properties = 5, .width = 173, .height = 26 },    /* Text-Dft_SET_ALARM_IN@A3_C0, 101 */
    { .dataOffset = 3733112, .properties = 5, .width = 173, .height = 26 },    /* Text-Dft_SET_ALARM_IN@A3_C1, 101 */
    { .dataOffset = 3742108, .properties = 5, .width = 196, .height = 26 },    /* Text-Dft_SET_ALARM_IN@A4_C0, 101 */
    { .dataOffset = 3752300, .properties = 5, .width = 196, .height = 26 },    /* Text-Dft_SET_ALARM_IN@A4_C1, 101 */
    { .dataOffset = 3762492, .properties = 5, .width = 190, .height = 26 },    /* Text-Dft_SET_ALARM_IN@A5_C0, 101 */
    { .dataOffset = 3772372, .properties = 5, .width = 190, .height = 26 },    /* Text-Dft_SET_ALARM_IN@A5_C1, 101 */
    { .dataOffset = 3782252, .properties = 5, .width = 242, .height = 26 },    /* Text-Dft_SET_ALARM_IN@A6_C0, 101 */
    { .dataOffset = 3794836, .properties = 5, .width = 242, .height = 26 },    /* Text-Dft_SET_ALARM_IN@A6_C1, 101 */
    { .dataOffset = 3807420, .properties = 5, .width = 210, .height = 26 },    /* Text-Dft_SET_ALARM_IN@A7_C0, 101 */
    { .dataOffset = 3818340, .properties = 5, .width = 210, .height = 26 },    /* Text-Dft_SET_ALARM_IN@A7_C1, 101 */
    { .dataOffset = 3829260, .properties = 5, .width = 137, .height = 26 },    /* Text-Dft_SET_ALARM_IN@A8_C0, 101 */
    { .dataOffset = 3836384, .properties = 5, .width = 137, .height = 26 },    /* Text-Dft_SET_ALARM_IN@A8_C1, 101 */
    { .dataOffset = 3843508, .properties = 5, .width = 90, .height = 26 },    /* Text-Dft_SET_ALARM_IN@A9_C0, 101 */
    { .dataOffset = 3848188, .properties = 5, .width = 90, .height = 26 },    /* Text-Dft_SET_ALARM_IN@A9_C1, 101 */
    { .dataOffset = 3852868, .properties = 4, .width = 70, .height = 26 },    /* Text-Dft_SPANISH@C0, 100 */
    { .dataOffset = 3856508, .properties = 4, .width = 79, .height = 26 },    /* Text-Dft_SPANISH@C1, 100 */
    { .dataOffset = 3860616, .properties = 5, .width = 40, .height = 26 },    /* Text-Dft_THEME_DARK@A0_C0, 101 */
    { .dataOffset = 3862696, .properties = 5, .width = 40, .height = 26 },    /* Text-Dft_THEME_DARK@A0_C1, 101 */
    { .dataOffset = 3864776, .properties = 5, .width = 63, .height = 26 },    /* Text-Dft_THEME_DARK@A1_C0, 101 */
    { .dataOffset = 3868052, .properties = 5, .width = 63, .height = 26 },    /* Text-Dft_THEME_DARK@A1_C1, 101 */
    { .dataOffset = 3871328, .properties = 5, .width = 60, .height = 26 },    /* Text-Dft_THEME_DARK@A2_C0, 101 */
    { .dataOffset = 3874448, .properties = 5, .width = 60, .height = 26 },    /* Text-Dft_THEME_DARK@A2_C1, 101 */
    { .dataOffset = 3877568, .properties = 5, .width = 70, .height = 26 },    /* Text-Dft_THEME_DARK@A3_C0, 101 */
    { .dataOffset = 3881208, .properties = 5, .width = 70, .height = 26 },    /* Text-Dft_THEME_DARK@A3_C1, 101 */
    { .dataOffset = 3884848, .properties = 5, .width = 64, .height = 26 },    /* Text-Dft_THEME_DARK@A4_C0, 101 */
    { .dataOffset = 3888176, .properties = 5, .width = 64, .height = 26 },    /* Text-Dft_THEME_DARK@A4_C1, 101 */
    { .dataOffset = 3891504, .properties = 5, .width = 64, .height = 26 },    /* Text-Dft_THEME_DARK@A5_C0, 101 */
    { .dataOffset = 3894832, .properties = 5, .width = 64, .height = 26 },    /* Text-Dft_THEME_DARK@A5_C1, 101 */
    { .dataOffset = 3898160, .properties = 5, .width = 77, .height = 26 },    /* Text-Dft_THEME_DARK@A6_C0, 101 */
    { .dataOffset = 3902164, .properties = 5, .width = 77, .height = 26 },    /* Text-Dft_THEME_DARK@A6_C1, 101 */
    { .dataOffset = 3906168, .properties = 5, .width = 43, .height = 26 },    /* Text-Dft_THEME_DARK@A7_C0, 101 */
    { .dataOffset = 3908404, .properties = 5, .width = 43, .height = 26 },    /* Text-Dft_THEME_DARK@A7_C1, 101 */
    { .dataOffset = 3910640, .properties = 5, .width = 40, .height = 26 },    /* Text-Dft_THEME_DARK@A8_C0, 101 */
    { .dataOffset = 3912720, .properties = 5, .width = 40, .height = 26 },    /* Text-Dft_THEME_DARK@A8_C1, 101 */
    { .dataOffset = 3914800, .properties = 5, .width = 38, .height = 26 },    /* Text-Dft_THEME_DARK@A9_C0, 101 */
    { .dataOffset = 3916776, .properties = 5, .width = 38, .height = 26 },    /* Text-Dft_THEME_DARK@A9_C1, 101 */
    { .dataOffset = 3918752, .properties = 5, .width = 43, .height = 26 },    /* Text-Dft_THEME_LIGHT@A0_C0, 101 */
    { .dataOffset = 3920988, .properties = 5, .width = 43, .height = 26 },    /* Text-Dft_THEME_LIGHT@A0_C1, 101 */
    { .dataOffset = 3923224, .properties = 5, .width = 43, .height = 26 },    /* Text-Dft_THEME_LIGHT@A1_C0, 101 */
    { .dataOffset = 3925460, .properties = 5, .width = 43, .height = 26 },    /* Text-Dft_THEME_LIGHT@A1_C1, 101 */
    { .dataOffset = 3927696, .properties = 5, .width = 43, .height = 26 },    /* Text-Dft_THEME_LIGHT@A2_C0, 101 */
    { .dataOffset = 3929932, .properties = 5, .width = 43, .height = 26 },    /* Text-Dft_THEME_LIGHT@A2_C1, 101 */
    { .dataOffset = 3932168, .properties = 5, .width = 72, .height = 26 },    /* Text-Dft_THEME_LIGHT@A3_C0, 101 */
    { .dataOffset = 3935912, .properties = 5, .width = 72, .height = 26 },    /* Text-Dft_THEME_LIGHT@A3_C1, 101 */
    { .dataOffset = 3939656, .properties = 5, .width = 30, .height = 26 },    /* Text-Dft_THEME_LIGHT@A4_C0, 101 */
    { .dataOffset = 3941216, .properties = 5, .width = 30, .height = 26 },    /* Text-Dft_THEME_LIGHT@A4_C1, 101 */
    { .dataOffset = 3942776, .properties = 5, .width = 72, .height = 26 },    /* Text-Dft_THEME_LIGHT@A5_C0, 101 */
    { .dataOffset = 3946520, .properties = 5, .width = 72, .height = 26 },    /* Text-Dft_THEME_LIGHT@A5_C1, 101 */
    { .dataOffset = 3950264, .properties = 5, .width = 45, .height = 26 },    /* Text-Dft_THEME_LIGHT@A6_C0, 101 */
    { .dataOffset = 3952604, .properties = 5, .width = 45, .height = 26 },    /* Text-Dft_THEME_LIGHT@A6_C1, 101 */
    { .dataOffset = 3954944, .properties = 5, .width = 20, .height = 26 },    /* Text-Dft_THEME_LIGHT@A7_C0, 101 */
    { .dataOffset = 3955984, .properties = 5, .width = 20, .height = 26 },    /* Text-Dft_THEME_LIGHT@A7_C1, 101 */
    { .dataOffset = 3957024, .properties = 5, .width = 20, .height = 26 },    /* Text-Dft_THEME_LIGHT@A8_C0, 101 */
    { .dataOffset = 3958064, .properties = 5, .width = 20, .height = 26 },    /* Text-Dft_THEME_LIGHT@A8_C1, 101 */
    { .dataOffset = 3959104, .properties = 5, .width = 19, .height = 26 },    /* Text-Dft_THEME_LIGHT@A9_C0, 101 */
    { .dataOffset = 3960092, .properties = 5, .width = 19, .height = 26 },    /* Text-Dft_THEME_LIGHT@A9_C1, 101 */
    { .dataOffset = 3961080, .properties = 4, .width = 48, .height = 26 },    /* Text-Dft_TIME_MM@C0, 100 */
    { .dataOffset = 3963576, .properties = 4, .width = 57, .height = 26 },    /* Text-Dft_TIME_MM@C1, 100 */
    { .dataOffset = 3966540, .properties = 5, .width = 58, .height = 29 },    /* Title_ALARM@A0_C0, 101 */
    { .dataOffset = 3969904, .properties = 5, .width = 58, .height = 29 },    /* Title_ALARM@A0_C1, 101 */
    { .dataOffset = 3973268, .properties = 5, .width = 58, .height = 29 },    /* Title_ALARM@A1_C0, 101 */
    { .dataOffset = 3976632, .properties = 5, .width = 58, .height = 29 },    /* Title_ALARM@A1_C1, 101 */
    { .dataOffset = 3979996, .properties = 5, .width = 58, .height = 29 },    /* Title_ALARM@A2_C0, 101 */
    { .dataOffset = 3983360, .properties = 5, .width = 58, .height = 29 },    /* Title_ALARM@A2_C1, 101 */
    { .dataOffset = 3986724, .properties = 5, .width = 71, .height = 29 },    /* Title_ALARM@A3_C0, 101 */
    { .dataOffset = 3990842, .properties = 5, .width = 71, .height = 29 },    /* Title_ALARM@A3_C1, 101 */
    { .dataOffset = 3994960, .properties = 5, .width = 71, .height = 29 },    /* Title_ALARM@A4_C0, 101 */
    { .dataOffset = 3999078, .properties = 5, .width = 71, .height = 29 },    /* Title_ALARM@A4_C1, 101 */
    { .dataOffset = 4003196, .properties = 5, .width = 76, .height = 29 },    /* Title_ALARM@A5_C0, 101 */
    { .dataOffset = 4007604, .properties = 5, .width = 76, .height = 29 },    /* Title_ALARM@A5_C1, 101 */
    { .dataOffset = 4012012, .properties = 5, .width = 84, .height = 29 },    /* Title_ALARM@A6_C0, 101 */
    { .dataOffset = 4016884, .properties = 5, .width = 84, .height = 29 },    /* Title_ALARM@A6_C1, 101 */
    { .dataOffset = 4021756, .properties = 5, .width = 47, .height = 29 },    /* Title_ALARM@A7_C0, 101 */
    { .dataOffset = 4024482, .properties = 5, .width = 47, .height = 29 },    /* Title_ALARM@A7_C1, 101 */
    { .dataOffset = 4027208, .properties = 5, .width = 47, .height = 29 },    /* Title_ALARM@A8_C0, 101 */
    { .dataOffset = 4029934, .properties = 5, .width = 47, .height = 29 },    /* Title_ALARM@A8_C1, 101 */
    { .dataOffset = 4032660, .properties = 5, .width = 63, .height = 29 },    /* Title_ALARM@A9_C0, 101 */
    { .dataOffset = 4036314, .properties = 5, .width = 63, .height = 29 },    /* Title_ALARM@A9_C1, 101 */
    { .dataOffset = 4039968, .properties = 5, .width = 105, .height = 29 },    /* Title_BRIGHTNESS@A0_C0, 101 */
    { .dataOffset = 4046058, .properties = 5, .width = 105, .height = 29 },    /* Title_BRIGHTNESS@A0_C1, 101 */
    { .dataOffset = 4052148, .properties = 5, .width = 106, .height = 29 },    /* Title_BRIGHTNESS@A1_C0, 101 */
    { .dataOffset = 4058296, .properties = 5, .width = 106, .height = 29 },    /* Title_BRIGHTNESS@A1_C1, 101 */
    { .dataOffset = 4064444, .properties = 5, .width = 92, .height = 29 },    /* Title_BRIGHTNESS@A2_C0, 101 */
    { .dataOffset = 4069780, .properties = 5, .width = 92, .height = 29 },    /* Title_BRIGHTNESS@A2_C1, 101 */
    { .dataOffset = 4075116, .properties = 5, .width = 110, .height = 29 },    /* Title_BRIGHTNESS@A3_C0, 101 */
    { .dataOffset = 4081496, .properties = 5, .width = 110, .height = 29 },    /* Title_BRIGHTNESS@A3_C1, 101 */
    { .dataOffset = 4087876, .properties = 5, .width = 49, .height = 29 },    /* Title_BRIGHTNESS@A4_C0, 101 */
    { .dataOffset = 4090718, .properties = 5, .width = 49, .height = 29 },    /* Title_BRIGHTNESS@A4_C1, 101 */
    { .dataOffset = 4093560, .properties = 5, .width = 110, .height = 29 },    /* Title_BRIGHTNESS@A5_C0, 101 */
    { .dataOffset = 4099940, .properties = 5, .width = 110, .height = 29 },    /* Title_BRIGHTNESS@A5_C1, 101 */
    { .dataOffset = 4106320, .properties = 5, .width = 86, .height = 29 },    /* Title_BRIGHTNESS@A6_C0, 101 */
    { .dataOffset = 4111308, .properties = 5, .width = 86, .height = 29 },    /* Title_BRIGHTNESS@A6_C1, 101 */
    { .dataOffset = 4116296, .properties = 5, .width = 46, .height = 29 },    /* Title_BRIGHTNESS@A7_C0, 101 */
    { .dataOffset = 4118964, .properties = 5, .width = 46, .height = 29 },    /* Title_BRIGHTNESS@A7_C1, 101 */
    { .dataOffset = 4121632, .properties = 5, .width = 57, .height = 29 },    /* Title_BRIGHTNESS@A8_C0, 101 */
    { .dataOffset = 4124938, .properties = 5, .width = 57, .height = 29 },    /* Title_BRIGHTNESS@A8_C1, 101 */
    { .dataOffset = 4128244, .properties = 5, .width = 39, .height = 29 },    /* Title_BRIGHTNESS@A9_C0, 101 */
    { .dataOffset = 4130506, .properties = 5, .width = 39, .height = 29 },    /* Title_BRIGHTNESS@A9_C1, 101 */
    { .dataOffset = 4132768, .properties = 5, .width = 63, .height = 29 },    /* Title_COLORS@A0_C0, 101 */
    { .dataOffset = 4136422, .properties = 5, .width = 63, .height = 29 },    /* Title_COLORS@A0_C1, 101 */
    { .dataOffset = 4140076, .properties = 5, .width = 74, .height = 29 },    /* Title_COLORS@A1_C0, 101 */
    { .dataOffset = 4144368, .properties = 5, .width = 74, .height = 29 },    /* Title_COLORS@A1_C1, 101 */
    { .dataOffset = 4148660, .properties = 5, .width = 67, .height = 29 },    /* Title_COLORS@A2_C0, 101 */
    { .dataOffset = 4152546, .properties = 5, .width = 67, .height = 29 },    /* Title_COLORS@A2_C1, 101 */
    { .dataOffset = 4156432, .properties = 5, .width = 87, .height = 29 },    /* Title_COLORS@A3_C0, 101 */
    { .dataOffset = 4161478, .properties = 5, .width = 87, .height = 29 },    /* Title_COLORS@A3_C1, 101 */
    { .dataOffset = 4166524, .properties = 5, .width = 75, .height = 29 },    /* Title_COLORS@A4_C0, 101 */
    { .dataOffset = 4170874, .properties = 5, .width = 75, .height = 29 },    /* Title_COLORS@A4_C1, 101 */
    { .dataOffset = 4175224, .properties = 5, .width = 57, .height = 29 },    /* Title_COLORS@A5_C0, 101 */
    { .dataOffset = 4178530, .properties = 5, .width = 57, .height = 29 },    /* Title_COLORS@A5_C1, 101 */
    { .dataOffset = 4181836, .properties = 5, .width = 66, .height = 29 },    /* Title_COLORS@A6_C0, 101 */
    { .dataOffset = 4185664, .properties = 5, .width = 66, .height = 29 },    /* Title_COLORS@A6_C1, 101 */
    { .dataOffset = 4189492, .properties = 5, .width = 47, .height = 29 },    /* Title_COLORS@A7_C0, 101 */
    { .dataOffset = 4192218, .properties = 5, .width = 47, .height = 29 },    /* Title_COLORS@A7_C1, 101 */
    { .dataOffset = 4194944, .properties = 5, .width = 22, .height = 29 },    /* Title_COLORS@A8_C0, 101 */
    { .dataOffset = 4196220, .properties = 5, .width = 22, .height = 29 },    /* Title_COLORS@A8_C1, 101 */
    { .dataOffset = 4197496, .properties = 5, .width = 42, .height = 29 },    /* Title_COLORS@A9_C0, 101 */
    { .dataOffset = 4199932, .properties = 5, .width = 42, .height = 29 },    /* Title_COLORS@A9_C1, 101 */
    { .dataOffset = 4202368, .properties = 5, .width = 44, .height = 29 },    /* Title_DATE@A0_C0, 101 */
    { .dataOffset = 4204920, .properties = 5, .width = 44, .height = 29 },    /* Title_DATE@A0_C1, 101 */
    { .dataOffset = 4207472, .properties = 5, .width = 64, .height = 29 },    /* Title_DATE@A1_C0, 101 */
    { .dataOffset = 4211184, .properties = 5, .width = 64, .height = 29 },    /* Title_DATE@A1_C1, 101 */
    { .dataOffset = 4214896, .properties = 5, .width = 64, .height = 29 },    /* Title_DATE@A2_C0, 101 */
    { .dataOffset = 4218608, .properties = 5, .width = 64, .height = 29 },    /* Title_DATE@A2_C1, 101 */
    { .dataOffset = 4222320, .properties = 5, .width = 44, .height = 29 },    /* Title_DATE@A3_C0, 101 */
    { .dataOffset = 4224872, .properties = 5, .width = 44, .height = 29 },    /* Title_DATE@A3_C1, 101 */
    { .dataOffset = 4227424, .properties = 5, .width = 59, .height = 29 },    /* Title_DATE@A4_C0, 101 */
    { .dataOffset = 4230846, .properties = 5, .width = 59, .height = 29 },    /* Title_DATE@A4_C1, 101 */
    { .dataOffset = 4234268, .properties = 5, .width = 72, .height = 29 },    /* Title_DATE@A5_C0, 101 */
    { .dataOffset = 4238444, .properties = 5, .width = 72, .height = 29 },    /* Title_DATE@A5_C1, 101 */
    { .dataOffset = 4242620, .properties = 5, .width = 51, .height = 29 },    /* Title_DATE@A6_C0, 101 */
    { .dataOffset = 4245578, .properties = 5, .width = 51, .height = 29 },    /* Title_DATE@A6_C1, 101 */
    { .dataOffset = 4248536, .properties = 5, .width = 43, .height = 29 },    /* Title_DATE@A7_C0, 101 */
    { .dataOffset = 4251030, .properties = 5, .width = 43, .height = 29 },    /* Title_DATE@A7_C1, 101 */
    { .dataOffset = 4253524, .properties = 5, .width = 43, .height = 29 },    /* Title_DATE@A8_C0, 101 */
    { .dataOffset = 4256018, .properties = 5, .width = 43, .height = 29 },    /* Title_DATE@A8_C1, 101 */
    { .dataOffset = 4258512, .properties = 5, .width = 42, .height = 29 },    /* Title_DATE@A9_C0, 101 */
    { .dataOffset = 4260948, .properties = 5, .width = 42, .height = 29 },    /* Title_DATE@A9_C1, 101 */
    { .dataOffset = 4263384, .properties = 5, .width = 37, .height = 29 },    /* Title_INFO@A0_C0, 101 */
    { .dataOffset = 4265530, .properties = 5, .width = 37, .height = 29 },    /* Title_INFO@A0_C1, 101 */
    { .dataOffset = 4267676, .properties = 5, .width = 37, .height = 29 },    /* Title_INFO@A1_C0, 101 */
    { .dataOffset = 4269822, .properties = 5, .width = 37, .height = 29 },    /* Title_INFO@A1_C1, 101 */
    { .dataOffset = 4271968, .properties = 5, .width = 37, .height = 29 },    /* Title_INFO@A2_C0, 101 */
    { .dataOffset = 4274114, .properties = 5, .width = 37, .height = 29 },    /* Title_INFO@A2_C1, 101 */
    { .dataOffset = 4276260, .properties = 5, .width = 37, .height = 29 },    /* Title_INFO@A3_C0, 101 */
    { .dataOffset = 4278406, .properties = 5, .width = 37, .height = 29 },    /* Title_INFO@A3_C1, 101 */
    { .dataOffset = 4280552, .properties = 5, .width = 119, .height = 29 },    /* Title_INFO@A4_C0, 101 */
    { .dataOffset = 4287454, .properties = 5, .width = 119, .height = 29 },    /* Title_INFO@A4_C1, 101 */
    { .dataOffset = 4294356, .properties = 5, .width = 124, .height = 29 },    /* Title_INFO@A5_C0, 101 */
    { .dataOffset = 4301548, .properties = 5, .width = 124, .height = 29 },    /* Title_INFO@A5_C1, 101 */
    { .dataOffset = 4308740, .properties = 5, .width = 136, .height = 29 },    /* Title_INFO@A6_C0, 101 */
    { .dataOffset = 4316628, .properties = 5, .width = 136, .height = 29 },    /* Title_INFO@A6_C1, 101 */
    { .dataOffset = 4324516, .properties = 5, .width = 48, .height = 29 },    /* Title_INFO@A7_C0, 101 */
    { .dataOffset = 4327300, .properties = 5, .width = 48, .height = 29 },    /* Title_INFO@A7_C1, 101 */
    { .dataOffset = 4330084, .properties = 5, .width = 48, .height = 29 },    /* Title_INFO@A8_C0, 101 */
    { .dataOffset = 4332868, .properties = 5, .width = 48, .height = 29 },    /* Title_INFO@A8_C1, 101 */
    { .dataOffset = 4335652, .properties = 5, .width = 42, .height = 29 },    /* Title_INFO@A9_C0, 101 */
    { .dataOffset = 4338088, .properties = 5, .width = 42, .height = 29 },    /* Title_INFO@A9_C1, 101 */
    { .dataOffset = 4340524, .properties = 5, .width = 97, .height = 29 },    /* Title_LANGUAGE@A0_C0, 101 */
    { .dataOffset = 4346150, .properties = 5, .width = 97, .height = 29 },    /* Title_LANGUAGE@A0_C1, 101 */
    { .dataOffset = 4351776, .properties = 5, .width = 42, .height = 29 },    /* Title_LANGUAGE@A1_C0, 101 */
    { .dataOffset = 4354212, .properties = 5, .width = 42, .height = 29 },    /* Title_LANGUAGE@A1_C1, 101 */
    { .dataOffset = 4356648, .properties = 5, .width = 81, .height = 29 },    /* Title_LANGUAGE@A2_C0, 101 */
    { .dataOffset = 4361346, .properties = 5, .width = 81, .height = 29 },    /* Title_LANGUAGE@A2_C1, 101 */
    { .dataOffset = 4366044, .properties = 5, .width = 72, .height = 29 },    /* Title_LANGUAGE@A3_C0, 101 */
    { .dataOffset = 4370220, .properties = 5, .width = 72, .height = 29 },    /* Title_LANGUAGE@A3_C1, 101 */
    { .dataOffset = 4374396, .properties = 5, .width = 67, .height = 29 },    /* Title_LANGUAGE@A4_C0, 101 */
    { .dataOffset = 4378282, .properties = 5, .width = 67, .height = 29 },    /* Title_LANGUAGE@A4_C1, 101 */
    { .dataOffset = 4382168, .properties = 5, .width = 65, .height = 29 },    /* Title_LANGUAGE@A5_C0, 101 */
    { .dataOffset = 4385938, .properties = 5, .width = 65, .height = 29 },    /* Title_LANGUAGE@A5_C1, 101 */
    { .dataOffset = 4389708, .properties = 5, .width = 55, .height = 29 },    /* Title_LANGUAGE@A6_C0, 101 */
    { .dataOffset = 4392898, .properties = 5, .width = 55, .height = 29 },    /* Title_LANGUAGE@A6_C1, 101 */
    { .dataOffset = 4396088, .properties = 5, .width = 47, .height = 29 },    /* Title_LANGUAGE@A7_C0, 101 */
    { .dataOffset = 4398814, .properties = 5, .width = 47, .height = 29 },    /* Title_LANGUAGE@A7_C1, 101 */
    { .dataOffset = 4401540, .properties = 5, .width = 47, .height = 29 },    /* Title_LANGUAGE@A8_C0, 101 */
    { .dataOffset = 4404266, .properties = 5, .width = 47, .height = 29 },    /* Title_LANGUAGE@A8_C1, 101 */
    { .dataOffset = 4406992, .properties = 5, .width = 39, .height = 29 },    /* Title_LANGUAGE@A9_C0, 101 */
    { .dataOffset = 4409254, .properties = 5, .width = 39, .height = 29 },    /* Title_LANGUAGE@A9_C1, 101 */
    { .dataOffset = 4411516, .properties = 5, .width = 110, .height = 29 },    /* Title_MAIN_MENU@A0_C0, 101 */
    { .dataOffset = 4417896, .properties = 5, .width = 110, .height = 29 },    /* Title_MAIN_MENU@A0_C1, 101 */
    { .dataOffset = 4424276, .properties = 5, .width = 117, .height = 29 },    /* Title_MAIN_MENU@A1_C0, 101 */
    { .dataOffset = 4431062, .properties = 5, .width = 117, .height = 29 },    /* Title_MAIN_MENU@A1_C1, 101 */
    { .dataOffset = 4437848, .properties = 5, .width = 115, .height = 29 },    /* Title_MAIN_MENU@A2_C0, 101 */
    { .dataOffset = 4444518, .properties = 5, .width = 115, .height = 29 },    /* Title_MAIN_MENU@A2_C1, 101 */
    { .dataOffset = 4451188, .properties = 5, .width = 146, .height = 29 },    /* Title_MAIN_MENU@A3_C0, 101 */
    { .dataOffset = 4459656, .properties = 5, .width = 146, .height = 29 },    /* Title_MAIN_MENU@A3_C1, 101 */
    { .dataOffset = 4468124, .properties = 5, .width = 146, .height = 29 },    /* Title_MAIN_MENU@A4_C0, 101 */
    { .dataOffset = 4476592, .properties = 5, .width = 146, .height = 29 },    /* Title_MAIN_MENU@A4_C1, 101 */
    { .dataOffset = 4485060, .properties = 5, .width = 159, .height = 29 },    /* Title_MAIN_MENU@A5_C0, 101 */
    { .dataOffset = 4494282, .properties = 5, .width = 159, .height = 29 },    /* Title_MAIN_MENU@A5_C1, 101 */
    { .dataOffset = 4503504, .properties = 5, .width = 153, .height = 29 },    /* Title_MAIN_MENU@A6_C0, 101 */
    { .dataOffset = 4512378, .properties = 5, .width = 153, .height = 29 },    /* Title_MAIN_MENU@A6_C1, 101 */
    { .dataOffset = 4521252, .properties = 5, .width = 72, .height = 29 },    /* Title_MAIN_MENU@A7_C0, 101 */
    { .dataOffset = 4525428, .properties = 5, .width = 72, .height = 29 },    /* Title_MAIN_MENU@A7_C1, 101 */
    { .dataOffset = 4529604, .properties = 5, .width = 123, .height = 29 },    /* Title_MAIN_MENU@A8_C0, 101 */
    { .dataOffset = 4536738, .properties = 5, .width = 123, .height = 29 },    /* Title_MAIN_MENU@A8_C1, 101 */
    { .dataOffset = 4543872, .properties = 5, .width = 92, .height = 29 },    /* Title_MAIN_MENU@A9_C0, 101 */
    { .dataOffset = 4549208, .properties = 5, .width = 92, .height = 29 },    /* Title_MAIN_MENU@A9_C1, 101 */
    { .dataOffset = 4554544, .properties = 5, .width = 138, .height = 29 },    /* Title_MEASUREMENT@A0_C0, 101 */
    { .dataOffset = 4562548, .properties = 5, .width = 138, .height = 29 },    /* Title_MEASUREMENT@A0_C1, 101 */
    { .dataOffset = 4570552, .properties = 5, .width = 79, .height = 29 },    /* Title_MEASUREMENT@A1_C0, 101 */
    { .dataOffset = 4575134, .properties = 5, .width = 79, .height = 29 },    /* Title_MEASUREMENT@A1_C1, 101 */
    { .dataOffset = 4579716, .properties = 5, .width = 90, .height = 29 },    /* Title_MEASUREMENT@A2_C0, 101 */
    { .dataOffset = 4584936, .properties = 5, .width = 90, .height = 29 },    /* Title_MEASUREMENT@A2_C1, 101 */
    { .dataOffset = 4590156, .properties = 5, .width = 73, .height = 29 },    /* Title_MEASUREMENT@A3_C0, 101 */
    { .dataOffset = 4594390, .properties = 5, .width = 73, .height = 29 },    /* Title_MEASUREMENT@A3_C1, 101 */
    { .dataOffset = 4598624, .properties = 5, .width = 90, .height = 29 },    /* Title_MEASUREMENT@A4_C0, 101 */
    { .dataOffset = 4603844, .properties = 5, .width = 90, .height = 29 },    /* Title_MEASUREMENT@A4_C1, 101 */
    { .dataOffset = 4609064, .properties = 5, .width = 121, .height = 29 },    /* Title_MEASUREMENT@A5_C0, 101 */
    { .dataOffset = 4616082, .properties = 5, .width = 121, .height = 29 },    /* Title_MEASUREMENT@A5_C1, 101 */
    { .dataOffset = 4623100, .properties = 5, .width = 117, .height = 29 },    /* Title_MEASUREMENT@A6_C0, 101 */
    { .dataOffset = 4629886, .properties = 5, .width = 117, .height = 29 },    /* Title_MEASUREMENT@A6_C1, 101 */
    { .dataOffset = 4636672, .properties = 5, .width = 48, .height = 29 },    /* Title_MEASUREMENT@A7_C0, 101 */
    { .dataOffset = 4639456, .properties = 5, .width = 48, .height = 29 },    /* Title_MEASUREMENT@A7_C1, 101 */
    { .dataOffset = 4642240, .properties = 5, .width = 46, .height = 29 },    /* Title_MEASUREMENT@A8_C0, 101 */
    { .dataOffset = 4644908, .properties = 5, .width = 46, .height = 29 },    /* Title_MEASUREMENT@A8_C1, 101 */
    { .dataOffset = 4647576, .properties = 5, .width = 42, .height = 29 },    /* Title_MEASUREMENT@A9_C0, 101 */
    { .dataOffset = 4650012, .properties = 5, .width = 42, .height = 29 },    /* Title_MEASUREMENT@A9_C1, 101 */
    { .dataOffset = 4652448, .properties = 5, .width = 81, .height = 29 },    /* Title_SETTINGS@A0_C0, 101 */
    { .dataOffset = 4657146, .properties = 5, .width = 81, .height = 29 },    /* Title_SETTINGS@A0_C1, 101 */
    { .dataOffset = 4661844, .properties = 5, .width = 113, .height = 29 },    /* Title_SETTINGS@A1_C0, 101 */
    { .dataOffset = 4668398, .properties = 5, .width = 113, .height = 29 },    /* Title_SETTINGS@A1_C1, 101 */
    { .dataOffset = 4674952, .properties = 5, .width = 133, .height = 29 },    /* Title_SETTINGS@A2_C0, 101 */
    { .dataOffset = 4682666, .properties = 5, .width = 133, .height = 29 },    /* Title_SETTINGS@A2_C1, 101 */
    { .dataOffset = 4690380, .properties = 5, .width = 115, .height = 29 },    /* Title_SETTINGS@A3_C0, 101 */
    { .dataOffset = 4697050, .properties = 5, .width = 115, .height = 29 },    /* Title_SETTINGS@A3_C1, 101 */
    { .dataOffset = 4703720, .properties = 5, .width = 139, .height = 29 },    /* Title_SETTINGS@A4_C0, 101 */
    { .dataOffset = 4711782, .properties = 5, .width = 139, .height = 29 },    /* Title_SETTINGS@A4_C1, 101 */
    { .dataOffset = 4719844, .properties = 5, .width = 128, .height = 29 },    /* Title_SETTINGS@A5_C0, 101 */
    { .dataOffset = 4727268, .properties = 5, .width = 128, .height = 29 },    /* Title_SETTINGS@A5_C1, 101 */
    { .dataOffset = 4734692, .properties = 5, .width = 120, .height = 29 },    /* Title_SETTINGS@A6_C0, 101 */
    { .dataOffset = 4741652, .properties = 5, .width = 120, .height = 29 },    /* Title_SETTINGS@A6_C1, 101 */
    { .dataOffset = 4748612, .properties = 5, .width = 46, .height = 29 },    /* Title_SETTINGS@A7_C0, 101 */
    { .dataOffset = 4751280, .properties = 5, .width = 46, .height = 29 },    /* Title_SETTINGS@A7_C1, 101 */
    { .dataOffset = 4753948, .properties = 5, .width = 46, .height = 29 },    /* Title_SETTINGS@A8_C0, 101 */
    { .dataOffset = 4756616, .properties = 5, .width = 46, .height = 29 },    /* Title_SETTINGS@A8_C1, 101 */
    { .dataOffset = 4759284, .properties = 5, .width = 41, .height = 29 },    /* Title_SETTINGS@A9_C0, 101 */
    { .dataOffset = 4761662, .properties = 5, .width = 41, .height = 29 },    /* Title_SETTINGS@A9_C1, 101 */
    { .dataOffset = 4764040, .properties = 5, .width = 57, .height = 29 },    /* Title_SETUP@A0_C0, 101 */
    { .dataOffset = 4767346, .properties = 5, .width = 57, .height = 29 },    /* Title_SETUP@A0_C1, 101 */
    { .dataOffset = 4770652, .properties = 5, .width = 63, .height = 29 },    /* Title_SETUP@A1_C0, 101 */
    { .dataOffset = 4774306, .properties = 5, .width = 63, .height = 29 },    /* Title_SETUP@A1_C1, 101 */
    { .dataOffset = 4777960, .properties = 5, .width = 111, .height = 29 },    /* Title_SETUP@A2_C0, 101 */
    { .dataOffset = 4784398, .properties = 5, .width = 111, .height = 29 },    /* Title_SETUP@A2_C1, 101 */
    { .dataOffset = 4790836, .properties = 5, .width = 121, .height = 29 },    /* Title_SETUP@A3_C0, 101 */
    { .dataOffset = 4797854, .properties = 5, .width = 121, .height = 29 },    /* Title_SETUP@A3_C1, 101 */
    { .dataOffset = 4804872, .properties = 5, .width = 72, .height = 29 },    /* Title_SETUP@A4_C0, 101 */
    { .dataOffset = 4809048, .properties = 5, .width = 72, .height = 29 },    /* Title_SETUP@A4_C1, 101 */
    { .dataOffset = 4813224, .properties = 5, .width = 125, .height = 29 },    /* Title_SETUP@A5_C0, 101 */
    { .dataOffset = 4820474, .properties = 5, .width = 125, .height = 29 },    /* Title_SETUP@A5_C1, 101 */
    { .dataOffset = 4827724, .properties = 5, .width = 112, .height = 29 },    /* Title_SETUP@A6_C0, 101 */
    { .dataOffset = 4834220, .properties = 5, .width = 112, .height = 29 },    /* Title_SETUP@A6_C1, 101 */
    { .dataOffset = 4840716, .properties = 5, .width = 46, .height = 29 },    /* Title_SETUP@A7_C0, 101 */
    { .dataOffset = 4843384, .properties = 5, .width = 46, .height = 29 },    /* Title_SETUP@A7_C1, 101 */
    { .dataOffset = 4846052, .properties = 5, .width = 102, .height = 29 },    /* Title_SETUP@A8_C0, 101 */
    { .dataOffset = 4851968, .properties = 5, .width = 102, .height = 29 },    /* Title_SETUP@A8_C1, 101 */
    { .dataOffset = 4857884, .properties = 5, .width = 40, .height = 29 },    /* Title_SETUP@A9_C0, 101 */
    { .dataOffset = 4860204, .properties = 5, .width = 40, .height = 29 },    /* Title_SETUP@A9_C1, 101 */
    { .dataOffset = 4862524, .properties = 5, .width = 69, .height = 29 },    /* Title_THEME@A0_C0, 101 */
    { .dataOffset = 4866526, .properties = 5, .width = 69, .height = 29 },    /* Title_THEME@A0_C1, 101 */
    { .dataOffset = 4870528, .properties = 5, .width = 69, .height = 29 },    /* Title_THEME@A1_C0, 101 */
    { .dataOffset = 4874530, .properties = 5, .width = 69, .height = 29 },    /* Title_THEME@A1_C1, 101 */
    { .dataOffset = 4878532, .properties = 5, .width = 69, .height = 29 },    /* Title_THEME@A2_C0, 101 */
    { .dataOffset = 4882534, .properties = 5, .width = 69, .height = 29 },    /* Title_THEME@A2_C1, 101 */
    { .dataOffset = 4886536, .properties = 5, .width = 69, .height = 29 },    /* Title_THEME@A3_C0, 101 */
    { .dataOffset = 4890538, .properties = 5, .width = 69, .height = 29 },    /* Title_THEME@A3_C1, 101 */
    { .dataOffset = 4894540, .properties = 5, .width = 56, .height = 29 },    /* Title_THEME@A4_C0, 101 */
    { .dataOffset = 4897788, .properties = 5, .width = 56, .height = 29 },    /* Title_THEME@A4_C1, 101 */
    { .dataOffset = 4901036, .properties = 5, .width = 56, .height = 29 },    /* Title_THEME@A5_C0, 101 */
    { .dataOffset = 4904284, .properties = 5, .width = 56, .height = 29 },    /* Title_THEME@A5_C1, 101 */
    { .dataOffset = 4907532, .properties = 5, .width = 53, .height = 29 },    /* Title_THEME@A6_C0, 101 */
    { .dataOffset = 4910606, .properties = 5, .width = 53, .height = 29 },    /* Title_THEME@A6_C1, 101 */
    { .dataOffset = 4913680, .properties = 5, .width = 47, .height = 29 },    /* Title_THEME@A7_C0, 101 */
    { .dataOffset = 4916406, .properties = 5, .width = 47, .height = 29 },    /* Title_THEME@A7_C1, 101 */
    { .dataOffset = 4919132, .properties = 5, .width = 55, .height = 29 },    /* Title_THEME@A8_C0, 101 */
    { .dataOffset = 4922322, .properties = 5, .width = 55, .height = 29 },    /* Title_THEME@A8_C1, 101 */
    { .dataOffset = 4925512, .properties = 5, .width = 41, .height = 29 },    /* Title_THEME@A9_C0, 101 */
    { .dataOffset = 4927890, .properties = 5, .width = 41, .height = 29 },    /* Title_THEME@A9_C1, 101 */
    { .dataOffset = 4930268, .properties = 5, .width = 50, .height = 29 },    /* Title_TIME@A0_C0, 101 */
    { .dataOffset = 4933168, .properties = 5, .width = 50, .height = 29 },    /* Title_TIME@A0_C1, 101 */
    { .dataOffset = 4936068, .properties = 5, .width = 35, .height = 29 },    /* Title_TIME@A1_C0, 101 */
    { .dataOffset = 4938098, .properties = 5, .width = 35, .height = 29 },    /* Title_TIME@A1_C1, 101 */
    { .dataOffset = 4940128, .properties = 5, .width = 38, .height = 29 },    /* Title_TIME@A2_C0, 101 */
    { .dataOffset = 4942332, .properties = 5, .width = 38, .height = 29 },    /* Title_TIME@A2_C1, 101 */
    { .dataOffset = 4944536, .properties = 5, .width = 58, .height = 29 },    /* Title_TIME@A3_C0, 101 */
    { .dataOffset = 4947900, .properties = 5, .width = 58, .height = 29 },    /* Title_TIME@A3_C1, 101 */
    { .dataOffset = 4951264, .properties = 5, .width = 47, .height = 29 },    /* Title_TIME@A4_C0, 101 */
    { .dataOffset = 4953990, .properties = 5, .width = 47, .height = 29 },    /* Title_TIME@A4_C1, 101 */
    { .dataOffset = 4956716, .properties = 5, .width = 33, .height = 29 },    /* Title_TIME@A5_C0, 101 */
    { .dataOffset = 4958630, .properties = 5, .width = 33, .height = 29 },    /* Title_TIME@A5_C1, 101 */
    { .dataOffset = 4960544, .properties = 5, .width = 65, .height = 29 },    /* Title_TIME@A6_C0, 101 */
    { .dataOffset = 4964314, .properties = 5, .width = 65, .height = 29 },    /* Title_TIME@A6_C1, 101 */
    { .dataOffset = 4968084, .properties = 5, .width = 45, .height = 29 },    /* Title_TIME@A7_C0, 101 */
    { .dataOffset = 4970694, .properties = 5, .width = 45, .height = 29 },    /* Title_TIME@A7_C1, 101 */
    { .dataOffset = 4973304, .properties = 5, .width = 46, .height = 29 },    /* Title_TIME@A8_C0, 101 */
    { .dataOffset = 4975972, .properties = 5, .width = 46, .height = 29 },    /* Title_TIME@A8_C1, 101 */
    { .dataOffset = 4978640, .properties = 5, .width = 42, .height = 29 },    /* Title_TIME@A9_C0, 101 */
    { .dataOffset = 4981076, .properties = 5, .width = 42, .height = 29 },    /* Title_TIME@A9_C1, 101 */
};

const uint8_t maxProperty[FS_MAX_FILE_PROPERTIES] =
{
    10, 24, 2, 5, 
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
