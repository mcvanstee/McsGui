#include "fs_font_search.h"

const fs_char_info_s fs_char_info[4][95] =
{
    {
    { .dataOffset = 344110, .width = 7, .height = 21 },
    { .dataOffset = 344112, .width = 4, .height = 21 },
    { .dataOffset = 344180, .width = 6, .height = 21 },
    { .dataOffset = 344222, .width = 12, .height = 21 },
    { .dataOffset = 344360, .width = 10, .height = 21 },
    { .dataOffset = 344526, .width = 13, .height = 21 },
    { .dataOffset = 344702, .width = 12, .height = 21 },
    { .dataOffset = 344886, .width = 4, .height = 21 },
    { .dataOffset = 344910, .width = 7, .height = 21 },
    { .dataOffset = 345026, .width = 7, .height = 21 },
    { .dataOffset = 345142, .width = 9, .height = 21 },
    { .dataOffset = 345220, .width = 11, .height = 21 },
    { .dataOffset = 345278, .width = 5, .height = 21 },
    { .dataOffset = 345308, .width = 6, .height = 21 },
    { .dataOffset = 345316, .width = 5, .height = 21 },
    { .dataOffset = 345332, .width = 8, .height = 21 },
    { .dataOffset = 345416, .width = 10, .height = 21 },
    { .dataOffset = 345572, .width = 10, .height = 21 },
    { .dataOffset = 345658, .width = 10, .height = 21 },
    { .dataOffset = 345778, .width = 10, .height = 21 },
    { .dataOffset = 345924, .width = 10, .height = 21 },
    { .dataOffset = 346022, .width = 10, .height = 21 },
    { .dataOffset = 346144, .width = 10, .height = 21 },
    { .dataOffset = 346288, .width = 10, .height = 21 },
    { .dataOffset = 346372, .width = 10, .height = 21 },
    { .dataOffset = 346532, .width = 10, .height = 21 },
    { .dataOffset = 346670, .width = 5, .height = 21 },
    { .dataOffset = 346704, .width = 5, .height = 21 },
    { .dataOffset = 346752, .width = 9, .height = 21 },
    { .dataOffset = 346826, .width = 9, .height = 21 },
    { .dataOffset = 346840, .width = 10, .height = 21 },
    { .dataOffset = 346916, .width = 9, .height = 21 },
    { .dataOffset = 347018, .width = 16, .height = 21 },
    { .dataOffset = 347298, .width = 12, .height = 21 },
    { .dataOffset = 347442, .width = 10, .height = 21 },
    { .dataOffset = 347588, .width = 12, .height = 21 },
    { .dataOffset = 347738, .width = 11, .height = 21 },
    { .dataOffset = 347896, .width = 10, .height = 21 },
    { .dataOffset = 347970, .width = 10, .height = 21 },
    { .dataOffset = 348044, .width = 12, .height = 21 },
    { .dataOffset = 348206, .width = 11, .height = 21 },
    { .dataOffset = 348324, .width = 4, .height = 21 },
    { .dataOffset = 348374, .width = 10, .height = 21 },
    { .dataOffset = 348492, .width = 11, .height = 21 },
    { .dataOffset = 348654, .width = 9, .height = 21 },
    { .dataOffset = 348726, .width = 14, .height = 21 },
    { .dataOffset = 348972, .width = 11, .height = 21 },
    { .dataOffset = 349144, .width = 12, .height = 21 },
    { .dataOffset = 349310, .width = 11, .height = 21 },
    { .dataOffset = 349430, .width = 12, .height = 21 },
    { .dataOffset = 349602, .width = 11, .height = 21 },
    { .dataOffset = 349756, .width = 11, .height = 21 },
    { .dataOffset = 349920, .width = 11, .height = 21 },
    { .dataOffset = 350016, .width = 11, .height = 21 },
    { .dataOffset = 350184, .width = 12, .height = 21 },
    { .dataOffset = 350336, .width = 16, .height = 21 },
    { .dataOffset = 350578, .width = 12, .height = 21 },
    { .dataOffset = 350740, .width = 13, .height = 21 },
    { .dataOffset = 350868, .width = 11, .height = 21 },
    { .dataOffset = 350964, .width = 5, .height = 21 },
    { .dataOffset = 351056, .width = 9, .height = 21 },
    { .dataOffset = 351146, .width = 6, .height = 21 },
    { .dataOffset = 351216, .width = 8, .height = 21 },
    { .dataOffset = 351278, .width = 10, .height = 21 },
    { .dataOffset = 351286, .width = 6, .height = 21 },
    { .dataOffset = 351304, .width = 10, .height = 21 },
    { .dataOffset = 351428, .width = 10, .height = 21 },
    { .dataOffset = 351588, .width = 10, .height = 21 },
    { .dataOffset = 351692, .width = 10, .height = 21 },
    { .dataOffset = 351820, .width = 10, .height = 21 },
    { .dataOffset = 351932, .width = 8, .height = 21 },
    { .dataOffset = 352012, .width = 10, .height = 21 },
    { .dataOffset = 352166, .width = 10, .height = 21 },
    { .dataOffset = 352322, .width = 5, .height = 21 },
    { .dataOffset = 352394, .width = 6, .height = 21 },
    { .dataOffset = 352508, .width = 10, .height = 21 },
    { .dataOffset = 352660, .width = 4, .height = 21 },
    { .dataOffset = 352734, .width = 15, .height = 21 },
    { .dataOffset = 352914, .width = 10, .height = 21 },
    { .dataOffset = 353046, .width = 11, .height = 21 },
    { .dataOffset = 353170, .width = 10, .height = 21 },
    { .dataOffset = 353330, .width = 10, .height = 21 },
    { .dataOffset = 353456, .width = 7, .height = 21 },
    { .dataOffset = 353536, .width = 10, .height = 21 },
    { .dataOffset = 353656, .width = 8, .height = 21 },
    { .dataOffset = 353718, .width = 10, .height = 21 },
    { .dataOffset = 353848, .width = 10, .height = 21 },
    { .dataOffset = 353952, .width = 14, .height = 21 },
    { .dataOffset = 354130, .width = 10, .height = 21 },
    { .dataOffset = 354242, .width = 10, .height = 21 },
    { .dataOffset = 354368, .width = 10, .height = 21 },
    { .dataOffset = 354436, .width = 7, .height = 21 },
    { .dataOffset = 354542, .width = 4, .height = 21 },
    { .dataOffset = 354628, .width = 7, .height = 21 },
    { .dataOffset = 354730, .width = 12, .height = 21 },
    },
    {
    { .dataOffset = 354782, .width = 8, .height = 23 },
    { .dataOffset = 354784, .width = 5, .height = 23 },
    { .dataOffset = 354870, .width = 6, .height = 23 },
    { .dataOffset = 354910, .width = 12, .height = 23 },
    { .dataOffset = 355066, .width = 11, .height = 23 },
    { .dataOffset = 355256, .width = 14, .height = 23 },
    { .dataOffset = 355468, .width = 13, .height = 23 },
    { .dataOffset = 355668, .width = 4, .height = 23 },
    { .dataOffset = 355692, .width = 7, .height = 23 },
    { .dataOffset = 355814, .width = 7, .height = 23 },
    { .dataOffset = 355936, .width = 10, .height = 23 },
    { .dataOffset = 356024, .width = 12, .height = 23 },
    { .dataOffset = 356082, .width = 5, .height = 23 },
    { .dataOffset = 356110, .width = 7, .height = 23 },
    { .dataOffset = 356120, .width = 5, .height = 23 },
    { .dataOffset = 356138, .width = 9, .height = 23 },
    { .dataOffset = 356234, .width = 10, .height = 23 },
    { .dataOffset = 356404, .width = 10, .height = 23 },
    { .dataOffset = 356520, .width = 10, .height = 23 },
    { .dataOffset = 356646, .width = 10, .height = 23 },
    { .dataOffset = 356802, .width = 10, .height = 23 },
    { .dataOffset = 356930, .width = 10, .height = 23 },
    { .dataOffset = 357068, .width = 10, .height = 23 },
    { .dataOffset = 357230, .width = 10, .height = 23 },
    { .dataOffset = 357332, .width = 10, .height = 23 },
    { .dataOffset = 357510, .width = 10, .height = 23 },
    { .dataOffset = 357676, .width = 5, .height = 23 },
    { .dataOffset = 357710, .width = 5, .height = 23 },
    { .dataOffset = 357744, .width = 10, .height = 23 },
    { .dataOffset = 357828, .width = 10, .height = 23 },
    { .dataOffset = 357846, .width = 10, .height = 23 },
    { .dataOffset = 357932, .width = 10, .height = 23 },
    { .dataOffset = 358042, .width = 17, .height = 23 },
    { .dataOffset = 358374, .width = 14, .height = 23 },
    { .dataOffset = 358536, .width = 12, .height = 23 },
    { .dataOffset = 358724, .width = 12, .height = 23 },
    { .dataOffset = 358886, .width = 12, .height = 23 },
    { .dataOffset = 359084, .width = 11, .height = 23 },
    { .dataOffset = 359190, .width = 11, .height = 23 },
    { .dataOffset = 359296, .width = 12, .height = 23 },
    { .dataOffset = 359462, .width = 13, .height = 23 },
    { .dataOffset = 359664, .width = 5, .height = 23 },
    { .dataOffset = 359770, .width = 11, .height = 23 },
    { .dataOffset = 359906, .width = 13, .height = 23 },
    { .dataOffset = 360116, .width = 11, .height = 23 },
    { .dataOffset = 360222, .width = 16, .height = 23 },
    { .dataOffset = 360530, .width = 13, .height = 23 },
    { .dataOffset = 360780, .width = 13, .height = 23 },
    { .dataOffset = 360972, .width = 12, .height = 23 },
    { .dataOffset = 361134, .width = 13, .height = 23 },
    { .dataOffset = 361342, .width = 12, .height = 23 },
    { .dataOffset = 361542, .width = 12, .height = 23 },
    { .dataOffset = 361712, .width = 13, .height = 23 },
    { .dataOffset = 361818, .width = 12, .height = 23 },
    { .dataOffset = 362004, .width = 14, .height = 23 },
    { .dataOffset = 362176, .width = 18, .height = 23 },
    { .dataOffset = 362472, .width = 13, .height = 23 },
    { .dataOffset = 362656, .width = 13, .height = 23 },
    { .dataOffset = 362808, .width = 12, .height = 23 },
    { .dataOffset = 362912, .width = 6, .height = 23 },
    { .dataOffset = 363026, .width = 10, .height = 23 },
    { .dataOffset = 363128, .width = 6, .height = 23 },
    { .dataOffset = 363270, .width = 9, .height = 23 },
    { .dataOffset = 363334, .width = 10, .height = 23 },
    { .dataOffset = 363340, .width = 7, .height = 23 },
    { .dataOffset = 363366, .width = 10, .height = 23 },
    { .dataOffset = 363510, .width = 11, .height = 23 },
    { .dataOffset = 363686, .width = 11, .height = 23 },
    { .dataOffset = 363804, .width = 11, .height = 23 },
    { .dataOffset = 363962, .width = 11, .height = 23 },
    { .dataOffset = 364082, .width = 9, .height = 23 },
    { .dataOffset = 364176, .width = 11, .height = 23 },
    { .dataOffset = 364360, .width = 10, .height = 23 },
    { .dataOffset = 364516, .width = 5, .height = 23 },
    { .dataOffset = 364594, .width = 6, .height = 23 },
    { .dataOffset = 364698, .width = 10, .height = 23 },
    { .dataOffset = 364836, .width = 4, .height = 23 },
    { .dataOffset = 364922, .width = 16, .height = 23 },
    { .dataOffset = 365106, .width = 10, .height = 23 },
    { .dataOffset = 365236, .width = 12, .height = 23 },
    { .dataOffset = 365386, .width = 11, .height = 23 },
    { .dataOffset = 365536, .width = 11, .height = 23 },
    { .dataOffset = 365678, .width = 7, .height = 23 },
    { .dataOffset = 365748, .width = 11, .height = 23 },
    { .dataOffset = 365874, .width = 8, .height = 23 },
    { .dataOffset = 365968, .width = 10, .height = 23 },
    { .dataOffset = 366086, .width = 11, .height = 23 },
    { .dataOffset = 366212, .width = 16, .height = 23 },
    { .dataOffset = 366424, .width = 11, .height = 23 },
    { .dataOffset = 366560, .width = 11, .height = 23 },
    { .dataOffset = 366712, .width = 11, .height = 23 },
    { .dataOffset = 366796, .width = 8, .height = 23 },
    { .dataOffset = 366924, .width = 4, .height = 23 },
    { .dataOffset = 367016, .width = 8, .height = 23 },
    { .dataOffset = 367134, .width = 12, .height = 23 },
    },
    {
    { .dataOffset = 367190, .width = 8, .height = 26 },
    { .dataOffset = 367192, .width = 5, .height = 26 },
    { .dataOffset = 367272, .width = 7, .height = 26 },
    { .dataOffset = 367334, .width = 14, .height = 26 },
    { .dataOffset = 367498, .width = 12, .height = 26 },
    { .dataOffset = 367700, .width = 15, .height = 26 },
    { .dataOffset = 367936, .width = 14, .height = 26 },
    { .dataOffset = 368156, .width = 4, .height = 26 },
    { .dataOffset = 368182, .width = 8, .height = 26 },
    { .dataOffset = 368340, .width = 8, .height = 26 },
    { .dataOffset = 368500, .width = 11, .height = 26 },
    { .dataOffset = 368610, .width = 12, .height = 26 },
    { .dataOffset = 368684, .width = 6, .height = 26 },
    { .dataOffset = 368726, .width = 8, .height = 26 },
    { .dataOffset = 368744, .width = 5, .height = 26 },
    { .dataOffset = 368762, .width = 10, .height = 26 },
    { .dataOffset = 368872, .width = 12, .height = 26 },
    { .dataOffset = 369078, .width = 12, .height = 26 },
    { .dataOffset = 369204, .width = 12, .height = 26 },
    { .dataOffset = 369354, .width = 12, .height = 26 },
    { .dataOffset = 369518, .width = 12, .height = 26 },
    { .dataOffset = 369644, .width = 12, .height = 26 },
    { .dataOffset = 369796, .width = 12, .height = 26 },
    { .dataOffset = 369970, .width = 12, .height = 26 },
    { .dataOffset = 370082, .width = 12, .height = 26 },
    { .dataOffset = 370284, .width = 12, .height = 26 },
    { .dataOffset = 370466, .width = 5, .height = 26 },
    { .dataOffset = 370500, .width = 6, .height = 26 },
    { .dataOffset = 370554, .width = 10, .height = 26 },
    { .dataOffset = 370640, .width = 11, .height = 26 },
    { .dataOffset = 370666, .width = 11, .height = 26 },
    { .dataOffset = 370762, .width = 10, .height = 26 },
    { .dataOffset = 370874, .width = 19, .height = 26 },
    { .dataOffset = 371262, .width = 15, .height = 26 },
    { .dataOffset = 371442, .width = 12, .height = 26 },
    { .dataOffset = 371602, .width = 14, .height = 26 },
    { .dataOffset = 371794, .width = 13, .height = 26 },
    { .dataOffset = 371968, .width = 11, .height = 26 },
    { .dataOffset = 372046, .width = 11, .height = 26 },
    { .dataOffset = 372132, .width = 14, .height = 26 },
    { .dataOffset = 372340, .width = 13, .height = 26 },
    { .dataOffset = 372498, .width = 4, .height = 26 },
    { .dataOffset = 372556, .width = 12, .height = 26 },
    { .dataOffset = 372702, .width = 13, .height = 26 },
    { .dataOffset = 372900, .width = 11, .height = 26 },
    { .dataOffset = 372986, .width = 16, .height = 26 },
    { .dataOffset = 373278, .width = 13, .height = 26 },
    { .dataOffset = 373508, .width = 14, .height = 26 },
    { .dataOffset = 373716, .width = 13, .height = 26 },
    { .dataOffset = 373850, .width = 14, .height = 26 },
    { .dataOffset = 374090, .width = 13, .height = 26 },
    { .dataOffset = 374262, .width = 13, .height = 26 },
    { .dataOffset = 374452, .width = 14, .height = 26 },
    { .dataOffset = 374566, .width = 13, .height = 26 },
    { .dataOffset = 374742, .width = 15, .height = 26 },
    { .dataOffset = 374938, .width = 20, .height = 26 },
    { .dataOffset = 375268, .width = 15, .height = 26 },
    { .dataOffset = 375484, .width = 14, .height = 26 },
    { .dataOffset = 375648, .width = 13, .height = 26 },
    { .dataOffset = 375760, .width = 7, .height = 26 },
    { .dataOffset = 375914, .width = 11, .height = 26 },
    { .dataOffset = 376028, .width = 6, .height = 26 },
    { .dataOffset = 376144, .width = 9, .height = 26 },
    { .dataOffset = 376228, .width = 12, .height = 26 },
    { .dataOffset = 376246, .width = 7, .height = 26 },
    { .dataOffset = 376276, .width = 11, .height = 26 },
    { .dataOffset = 376428, .width = 12, .height = 26 },
    { .dataOffset = 376620, .width = 11, .height = 26 },
    { .dataOffset = 376744, .width = 11, .height = 26 },
    { .dataOffset = 376910, .width = 12, .height = 26 },
    { .dataOffset = 377034, .width = 10, .height = 26 },
    { .dataOffset = 377160, .width = 12, .height = 26 },
    { .dataOffset = 377372, .width = 11, .height = 26 },
    { .dataOffset = 377542, .width = 5, .height = 26 },
    { .dataOffset = 377648, .width = 7, .height = 26 },
    { .dataOffset = 377786, .width = 12, .height = 26 },
    { .dataOffset = 377988, .width = 5, .height = 26 },
    { .dataOffset = 378110, .width = 18, .height = 26 },
    { .dataOffset = 378350, .width = 11, .height = 26 },
    { .dataOffset = 378504, .width = 12, .height = 26 },
    { .dataOffset = 378656, .width = 12, .height = 26 },
    { .dataOffset = 378852, .width = 11, .height = 26 },
    { .dataOffset = 379020, .width = 8, .height = 26 },
    { .dataOffset = 379116, .width = 11, .height = 26 },
    { .dataOffset = 379268, .width = 8, .height = 26 },
    { .dataOffset = 379360, .width = 11, .height = 26 },
    { .dataOffset = 379498, .width = 12, .height = 26 },
    { .dataOffset = 379632, .width = 17, .height = 26 },
    { .dataOffset = 379866, .width = 12, .height = 26 },
    { .dataOffset = 380014, .width = 12, .height = 26 },
    { .dataOffset = 380178, .width = 11, .height = 26 },
    { .dataOffset = 380268, .width = 9, .height = 26 },
    { .dataOffset = 380418, .width = 4, .height = 26 },
    { .dataOffset = 380522, .width = 9, .height = 26 },
    { .dataOffset = 380686, .width = 14, .height = 26 },
    },
    {
    { .dataOffset = 380762, .width = 9, .height = 29 },
    { .dataOffset = 380766, .width = 5, .height = 29 },
    { .dataOffset = 380880, .width = 7, .height = 29 },
    { .dataOffset = 380938, .width = 14, .height = 29 },
    { .dataOffset = 381126, .width = 12, .height = 29 },
    { .dataOffset = 381356, .width = 17, .height = 29 },
    { .dataOffset = 381638, .width = 16, .height = 29 },
    { .dataOffset = 381898, .width = 5, .height = 29 },
    { .dataOffset = 381940, .width = 8, .height = 29 },
    { .dataOffset = 382122, .width = 8, .height = 29 },
    { .dataOffset = 382304, .width = 11, .height = 29 },
    { .dataOffset = 382428, .width = 14, .height = 29 },
    { .dataOffset = 382486, .width = 5, .height = 29 },
    { .dataOffset = 382518, .width = 8, .height = 29 },
    { .dataOffset = 382536, .width = 5, .height = 29 },
    { .dataOffset = 382554, .width = 11, .height = 29 },
    { .dataOffset = 382680, .width = 12, .height = 29 },
    { .dataOffset = 382894, .width = 12, .height = 29 },
    { .dataOffset = 383042, .width = 12, .height = 29 },
    { .dataOffset = 383212, .width = 12, .height = 29 },
    { .dataOffset = 383410, .width = 12, .height = 29 },
    { .dataOffset = 383596, .width = 12, .height = 29 },
    { .dataOffset = 383774, .width = 12, .height = 29 },
    { .dataOffset = 383974, .width = 12, .height = 29 },
    { .dataOffset = 384100, .width = 12, .height = 29 },
    { .dataOffset = 384330, .width = 12, .height = 29 },
    { .dataOffset = 384544, .width = 5, .height = 29 },
    { .dataOffset = 384578, .width = 6, .height = 29 },
    { .dataOffset = 384634, .width = 12, .height = 29 },
    { .dataOffset = 384742, .width = 12, .height = 29 },
    { .dataOffset = 384776, .width = 12, .height = 29 },
    { .dataOffset = 384882, .width = 12, .height = 29 },
    { .dataOffset = 385020, .width = 20, .height = 29 },
    { .dataOffset = 385448, .width = 16, .height = 29 },
    { .dataOffset = 385660, .width = 14, .height = 29 },
    { .dataOffset = 385890, .width = 14, .height = 29 },
    { .dataOffset = 386080, .width = 14, .height = 29 },
    { .dataOffset = 386318, .width = 13, .height = 29 },
    { .dataOffset = 386448, .width = 13, .height = 29 },
    { .dataOffset = 386578, .width = 14, .height = 29 },
    { .dataOffset = 386772, .width = 15, .height = 29 },
    { .dataOffset = 387014, .width = 5, .height = 29 },
    { .dataOffset = 387144, .width = 13, .height = 29 },
    { .dataOffset = 387282, .width = 15, .height = 29 },
    { .dataOffset = 387536, .width = 12, .height = 29 },
    { .dataOffset = 387662, .width = 19, .height = 29 },
    { .dataOffset = 388060, .width = 15, .height = 29 },
    { .dataOffset = 388374, .width = 15, .height = 29 },
    { .dataOffset = 388600, .width = 14, .height = 29 },
    { .dataOffset = 388786, .width = 15, .height = 29 },
    { .dataOffset = 389042, .width = 14, .height = 29 },
    { .dataOffset = 389276, .width = 14, .height = 29 },
    { .dataOffset = 389484, .width = 15, .height = 29 },
    { .dataOffset = 389614, .width = 14, .height = 29 },
    { .dataOffset = 389868, .width = 16, .height = 29 },
    { .dataOffset = 390082, .width = 21, .height = 29 },
    { .dataOffset = 390466, .width = 15, .height = 29 },
    { .dataOffset = 390692, .width = 15, .height = 29 },
    { .dataOffset = 390882, .width = 14, .height = 29 },
    { .dataOffset = 391012, .width = 7, .height = 29 },
    { .dataOffset = 391182, .width = 11, .height = 29 },
    { .dataOffset = 391316, .width = 7, .height = 29 },
    { .dataOffset = 391410, .width = 11, .height = 29 },
    { .dataOffset = 391506, .width = 13, .height = 29 },
    { .dataOffset = 391526, .width = 7, .height = 29 },
    { .dataOffset = 391552, .width = 12, .height = 29 },
    { .dataOffset = 391718, .width = 12, .height = 29 },
    { .dataOffset = 391926, .width = 13, .height = 29 },
    { .dataOffset = 392072, .width = 13, .height = 29 },
    { .dataOffset = 392298, .width = 13, .height = 29 },
    { .dataOffset = 392448, .width = 10, .height = 29 },
    { .dataOffset = 392590, .width = 13, .height = 29 },
    { .dataOffset = 392826, .width = 12, .height = 29 },
    { .dataOffset = 393060, .width = 5, .height = 29 },
    { .dataOffset = 393174, .width = 7, .height = 29 },
    { .dataOffset = 393318, .width = 12, .height = 29 },
    { .dataOffset = 393538, .width = 5, .height = 29 },
    { .dataOffset = 393676, .width = 19, .height = 29 },
    { .dataOffset = 393964, .width = 12, .height = 29 },
    { .dataOffset = 394158, .width = 14, .height = 29 },
    { .dataOffset = 394324, .width = 12, .height = 29 },
    { .dataOffset = 394526, .width = 13, .height = 29 },
    { .dataOffset = 394738, .width = 8, .height = 29 },
    { .dataOffset = 394838, .width = 12, .height = 29 },
    { .dataOffset = 394986, .width = 10, .height = 29 },
    { .dataOffset = 395072, .width = 12, .height = 29 },
    { .dataOffset = 395264, .width = 12, .height = 29 },
    { .dataOffset = 395418, .width = 18, .height = 29 },
    { .dataOffset = 395686, .width = 13, .height = 29 },
    { .dataOffset = 395854, .width = 12, .height = 29 },
    { .dataOffset = 396036, .width = 12, .height = 29 },
    { .dataOffset = 396136, .width = 9, .height = 29 },
    { .dataOffset = 396304, .width = 5, .height = 29 },
    { .dataOffset = 396458, .width = 9, .height = 29 },
    { .dataOffset = 396630, .width = 15, .height = 29 },
    },
};

const fs_char_info_s fs_char_info_digits[2][12] =
{
    {
    { .dataOffset = 396722, .width = 9, .height = 38 },
    { .dataOffset = 396796, .width = 8, .height = 38 },
    { .dataOffset = 396838, .width = 20, .height = 38 },
    { .dataOffset = 397202, .width = 20, .height = 38 },
    { .dataOffset = 397440, .width = 20, .height = 38 },
    { .dataOffset = 397694, .width = 20, .height = 38 },
    { .dataOffset = 398004, .width = 20, .height = 38 },
    { .dataOffset = 398292, .width = 20, .height = 38 },
    { .dataOffset = 398576, .width = 20, .height = 38 },
    { .dataOffset = 398912, .width = 20, .height = 38 },
    { .dataOffset = 399120, .width = 20, .height = 38 },
    { .dataOffset = 399500, .width = 20, .height = 38 },
    },
    {
    { .dataOffset = 399844, .width = 11, .height = 54 },
    { .dataOffset = 399934, .width = 9, .height = 54 },
    { .dataOffset = 399982, .width = 26, .height = 54 },
    { .dataOffset = 400450, .width = 26, .height = 54 },
    { .dataOffset = 400698, .width = 26, .height = 54 },
    { .dataOffset = 401064, .width = 26, .height = 54 },
    { .dataOffset = 401484, .width = 26, .height = 54 },
    { .dataOffset = 401860, .width = 26, .height = 54 },
    { .dataOffset = 402228, .width = 26, .height = 54 },
    { .dataOffset = 402686, .width = 26, .height = 54 },
    { .dataOffset = 402952, .width = 26, .height = 54 },
    { .dataOffset = 403462, .width = 26, .height = 54 },
    },
};

static inline int32_t fs_getCharIndex(const font_key_e font_key, const char c)
{
    int32_t charIndex = -1;

    switch (font_key)
    {
        case FONT_KEY_ROBOTO_16_R:
        case FONT_KEY_ROBOTO_18_R:
        case FONT_KEY_ROBOTO_20_R:
        case FONT_KEY_ROBOTO_22_R:
            charIndex = (c - 32);
            break;
        case FONT_KEY_ROBOTO_36_B:
        case FONT_KEY_ROBOTO_48_B:
        {
            if ((c >= '0') && (c <= '9'))
            {
                charIndex = (c - '0' + 2);
            }
            else if (c == '.')
            {
                charIndex = 0;
            }
            else if (c == ',')
            {
                charIndex = 1;
            }
            else
            {
            }
            break;
        }
        default:
            break;
    }

    return charIndex;
}

static inline int32_t fs_getFontIndex(const font_key_e font_key)
{
    int32_t fontIndex = -1;

    switch (font_key)
    {
        case FONT_KEY_ROBOTO_16_R:
            fontIndex = 0;
            break;
        case FONT_KEY_ROBOTO_18_R:
            fontIndex = 1;
            break;
        case FONT_KEY_ROBOTO_20_R:
            fontIndex = 2;
            break;
        case FONT_KEY_ROBOTO_22_R:
            fontIndex = 3;
            break;
        case FONT_KEY_ROBOTO_36_B:
            fontIndex = 0;
            break;
        case FONT_KEY_ROBOTO_48_B:
            fontIndex = 1;
            break;
        default:
            break;
    }

    return fontIndex;
}


bool fs_getCharInfo(const char c, const font_key_e font_key, fs_char_info_s *p_out_char_info)
{
    bool charInfoFound = false;
    const int32_t charIndex = fs_getCharIndex(font_key, c);
    const int32_t fontIndex = fs_getFontIndex(font_key);

    switch (font_key)
    {
        case FONT_KEY_ROBOTO_16_R:
        case FONT_KEY_ROBOTO_18_R:
        case FONT_KEY_ROBOTO_20_R:
        case FONT_KEY_ROBOTO_22_R:
        {
            if ((FS_CHAR_INFOS_IN_FONT > charIndex) && (FS_FONTS > fontIndex) && (charIndex >= 0) && (fontIndex >= 0))
            {
                *p_out_char_info = fs_char_info[fontIndex][charIndex];
                charInfoFound = true;
            }
            break;
        }
        case FONT_KEY_ROBOTO_36_B:
        case FONT_KEY_ROBOTO_48_B:
        {
            if ((FS_CHAR_INFOS_IN_DIGIT_ONLY_FONT > charIndex) && (FS_FONTS > fontIndex) && (charIndex >= 0) && (fontIndex >= 0))
            {
                *p_out_char_info = fs_char_info_digits[fontIndex][charIndex];
                charInfoFound = true;
            }
            break;
        }
        default:
            break;
    }

    return charInfoFound;
}

/*** end of file ***/
