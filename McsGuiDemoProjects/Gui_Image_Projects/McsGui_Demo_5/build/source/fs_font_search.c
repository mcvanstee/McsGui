#include "fs_font_search.h"

const fs_char_info_s fs_char_info[4][95] =
{
    {
    { .dataOffset = 244686, .width = 7, .height = 21 },
    { .dataOffset = 244688, .width = 4, .height = 21 },
    { .dataOffset = 244738, .width = 6, .height = 21 },
    { .dataOffset = 244773, .width = 12, .height = 21 },
    { .dataOffset = 244875, .width = 10, .height = 21 },
    { .dataOffset = 244994, .width = 13, .height = 21 },
    { .dataOffset = 245112, .width = 12, .height = 21 },
    { .dataOffset = 245244, .width = 4, .height = 21 },
    { .dataOffset = 245261, .width = 7, .height = 21 },
    { .dataOffset = 245346, .width = 7, .height = 21 },
    { .dataOffset = 245431, .width = 9, .height = 21 },
    { .dataOffset = 245484, .width = 11, .height = 21 },
    { .dataOffset = 245530, .width = 5, .height = 21 },
    { .dataOffset = 245552, .width = 6, .height = 21 },
    { .dataOffset = 245559, .width = 5, .height = 21 },
    { .dataOffset = 245572, .width = 8, .height = 21 },
    { .dataOffset = 245633, .width = 10, .height = 21 },
    { .dataOffset = 245746, .width = 10, .height = 21 },
    { .dataOffset = 245813, .width = 10, .height = 21 },
    { .dataOffset = 245898, .width = 10, .height = 21 },
    { .dataOffset = 246002, .width = 10, .height = 21 },
    { .dataOffset = 246073, .width = 10, .height = 21 },
    { .dataOffset = 246166, .width = 10, .height = 21 },
    { .dataOffset = 246272, .width = 10, .height = 21 },
    { .dataOffset = 246335, .width = 10, .height = 21 },
    { .dataOffset = 246449, .width = 10, .height = 21 },
    { .dataOffset = 246546, .width = 5, .height = 21 },
    { .dataOffset = 246572, .width = 5, .height = 21 },
    { .dataOffset = 246608, .width = 9, .height = 21 },
    { .dataOffset = 246658, .width = 9, .height = 21 },
    { .dataOffset = 246670, .width = 10, .height = 21 },
    { .dataOffset = 246720, .width = 9, .height = 21 },
    { .dataOffset = 246794, .width = 16, .height = 21 },
    { .dataOffset = 246985, .width = 12, .height = 21 },
    { .dataOffset = 247088, .width = 10, .height = 21 },
    { .dataOffset = 247201, .width = 12, .height = 21 },
    { .dataOffset = 247309, .width = 11, .height = 21 },
    { .dataOffset = 247429, .width = 10, .height = 21 },
    { .dataOffset = 247491, .width = 10, .height = 21 },
    { .dataOffset = 247553, .width = 12, .height = 21 },
    { .dataOffset = 247671, .width = 11, .height = 21 },
    { .dataOffset = 247766, .width = 4, .height = 21 },
    { .dataOffset = 247804, .width = 10, .height = 21 },
    { .dataOffset = 247891, .width = 11, .height = 21 },
    { .dataOffset = 248017, .width = 9, .height = 21 },
    { .dataOffset = 248078, .width = 14, .height = 21 },
    { .dataOffset = 248269, .width = 11, .height = 21 },
    { .dataOffset = 248401, .width = 12, .height = 21 },
    { .dataOffset = 248522, .width = 11, .height = 21 },
    { .dataOffset = 248617, .width = 12, .height = 21 },
    { .dataOffset = 248745, .width = 11, .height = 21 },
    { .dataOffset = 248864, .width = 11, .height = 21 },
    { .dataOffset = 248979, .width = 11, .height = 21 },
    { .dataOffset = 249052, .width = 11, .height = 21 },
    { .dataOffset = 249182, .width = 12, .height = 21 },
    { .dataOffset = 249293, .width = 16, .height = 21 },
    { .dataOffset = 249468, .width = 12, .height = 21 },
    { .dataOffset = 249587, .width = 13, .height = 21 },
    { .dataOffset = 249682, .width = 11, .height = 21 },
    { .dataOffset = 249754, .width = 5, .height = 21 },
    { .dataOffset = 249831, .width = 9, .height = 21 },
    { .dataOffset = 249897, .width = 6, .height = 21 },
    { .dataOffset = 249950, .width = 8, .height = 21 },
    { .dataOffset = 249994, .width = 10, .height = 21 },
    { .dataOffset = 250001, .width = 6, .height = 21 },
    { .dataOffset = 250014, .width = 10, .height = 21 },
    { .dataOffset = 250104, .width = 10, .height = 21 },
    { .dataOffset = 250223, .width = 10, .height = 21 },
    { .dataOffset = 250298, .width = 10, .height = 21 },
    { .dataOffset = 250391, .width = 10, .height = 21 },
    { .dataOffset = 250471, .width = 8, .height = 21 },
    { .dataOffset = 250536, .width = 10, .height = 21 },
    { .dataOffset = 250646, .width = 10, .height = 21 },
    { .dataOffset = 250766, .width = 5, .height = 21 },
    { .dataOffset = 250825, .width = 6, .height = 21 },
    { .dataOffset = 250911, .width = 10, .height = 21 },
    { .dataOffset = 251024, .width = 4, .height = 21 },
    { .dataOffset = 251086, .width = 15, .height = 21 },
    { .dataOffset = 251222, .width = 10, .height = 21 },
    { .dataOffset = 251324, .width = 11, .height = 21 },
    { .dataOffset = 251415, .width = 10, .height = 21 },
    { .dataOffset = 251534, .width = 10, .height = 21 },
    { .dataOffset = 251626, .width = 7, .height = 21 },
    { .dataOffset = 251686, .width = 10, .height = 21 },
    { .dataOffset = 251768, .width = 8, .height = 21 },
    { .dataOffset = 251814, .width = 10, .height = 21 },
    { .dataOffset = 251913, .width = 10, .height = 21 },
    { .dataOffset = 251990, .width = 14, .height = 21 },
    { .dataOffset = 252118, .width = 10, .height = 21 },
    { .dataOffset = 252199, .width = 10, .height = 21 },
    { .dataOffset = 252292, .width = 10, .height = 21 },
    { .dataOffset = 252343, .width = 7, .height = 21 },
    { .dataOffset = 252425, .width = 4, .height = 21 },
    { .dataOffset = 252497, .width = 7, .height = 21 },
    { .dataOffset = 252575, .width = 12, .height = 21 },
    },
    {
    { .dataOffset = 252610, .width = 8, .height = 23 },
    { .dataOffset = 252612, .width = 5, .height = 23 },
    { .dataOffset = 252679, .width = 6, .height = 23 },
    { .dataOffset = 252704, .width = 12, .height = 23 },
    { .dataOffset = 252819, .width = 11, .height = 23 },
    { .dataOffset = 252956, .width = 14, .height = 23 },
    { .dataOffset = 253102, .width = 13, .height = 23 },
    { .dataOffset = 253248, .width = 4, .height = 23 },
    { .dataOffset = 253269, .width = 7, .height = 23 },
    { .dataOffset = 253359, .width = 7, .height = 23 },
    { .dataOffset = 253451, .width = 10, .height = 23 },
    { .dataOffset = 253510, .width = 12, .height = 23 },
    { .dataOffset = 253557, .width = 5, .height = 23 },
    { .dataOffset = 253579, .width = 7, .height = 23 },
    { .dataOffset = 253587, .width = 5, .height = 23 },
    { .dataOffset = 253601, .width = 9, .height = 23 },
    { .dataOffset = 253671, .width = 10, .height = 23 },
    { .dataOffset = 253799, .width = 10, .height = 23 },
    { .dataOffset = 253883, .width = 10, .height = 23 },
    { .dataOffset = 253978, .width = 10, .height = 23 },
    { .dataOffset = 254091, .width = 10, .height = 23 },
    { .dataOffset = 254192, .width = 10, .height = 23 },
    { .dataOffset = 254294, .width = 10, .height = 23 },
    { .dataOffset = 254412, .width = 10, .height = 23 },
    { .dataOffset = 254489, .width = 10, .height = 23 },
    { .dataOffset = 254620, .width = 10, .height = 23 },
    { .dataOffset = 254739, .width = 5, .height = 23 },
    { .dataOffset = 254765, .width = 5, .height = 23 },
    { .dataOffset = 254790, .width = 10, .height = 23 },
    { .dataOffset = 254847, .width = 10, .height = 23 },
    { .dataOffset = 254861, .width = 10, .height = 23 },
    { .dataOffset = 254919, .width = 10, .height = 23 },
    { .dataOffset = 254998, .width = 17, .height = 23 },
    { .dataOffset = 255229, .width = 14, .height = 23 },
    { .dataOffset = 255350, .width = 12, .height = 23 },
    { .dataOffset = 255490, .width = 12, .height = 23 },
    { .dataOffset = 255610, .width = 12, .height = 23 },
    { .dataOffset = 255754, .width = 11, .height = 23 },
    { .dataOffset = 255834, .width = 11, .height = 23 },
    { .dataOffset = 255914, .width = 12, .height = 23 },
    { .dataOffset = 256036, .width = 13, .height = 23 },
    { .dataOffset = 256188, .width = 5, .height = 23 },
    { .dataOffset = 256268, .width = 11, .height = 23 },
    { .dataOffset = 256366, .width = 13, .height = 23 },
    { .dataOffset = 256518, .width = 11, .height = 23 },
    { .dataOffset = 256598, .width = 16, .height = 23 },
    { .dataOffset = 256826, .width = 13, .height = 23 },
    { .dataOffset = 257012, .width = 13, .height = 23 },
    { .dataOffset = 257153, .width = 12, .height = 23 },
    { .dataOffset = 257272, .width = 13, .height = 23 },
    { .dataOffset = 257426, .width = 12, .height = 23 },
    { .dataOffset = 257575, .width = 12, .height = 23 },
    { .dataOffset = 257698, .width = 13, .height = 23 },
    { .dataOffset = 257778, .width = 12, .height = 23 },
    { .dataOffset = 257921, .width = 14, .height = 23 },
    { .dataOffset = 258052, .width = 18, .height = 23 },
    { .dataOffset = 258271, .width = 13, .height = 23 },
    { .dataOffset = 258407, .width = 13, .height = 23 },
    { .dataOffset = 258521, .width = 12, .height = 23 },
    { .dataOffset = 258600, .width = 6, .height = 23 },
    { .dataOffset = 258694, .width = 10, .height = 23 },
    { .dataOffset = 258770, .width = 6, .height = 23 },
    { .dataOffset = 258878, .width = 9, .height = 23 },
    { .dataOffset = 258925, .width = 10, .height = 23 },
    { .dataOffset = 258931, .width = 7, .height = 23 },
    { .dataOffset = 258950, .width = 10, .height = 23 },
    { .dataOffset = 259055, .width = 11, .height = 23 },
    { .dataOffset = 259188, .width = 11, .height = 23 },
    { .dataOffset = 259272, .width = 11, .height = 23 },
    { .dataOffset = 259394, .width = 11, .height = 23 },
    { .dataOffset = 259481, .width = 9, .height = 23 },
    { .dataOffset = 259557, .width = 11, .height = 23 },
    { .dataOffset = 259694, .width = 10, .height = 23 },
    { .dataOffset = 259820, .width = 5, .height = 23 },
    { .dataOffset = 259884, .width = 6, .height = 23 },
    { .dataOffset = 259966, .width = 10, .height = 23 },
    { .dataOffset = 260067, .width = 4, .height = 23 },
    { .dataOffset = 260139, .width = 16, .height = 23 },
    { .dataOffset = 260281, .width = 10, .height = 23 },
    { .dataOffset = 260384, .width = 12, .height = 23 },
    { .dataOffset = 260494, .width = 11, .height = 23 },
    { .dataOffset = 260600, .width = 11, .height = 23 },
    { .dataOffset = 260702, .width = 7, .height = 23 },
    { .dataOffset = 260758, .width = 11, .height = 23 },
    { .dataOffset = 260847, .width = 8, .height = 23 },
    { .dataOffset = 260919, .width = 10, .height = 23 },
    { .dataOffset = 261010, .width = 11, .height = 23 },
    { .dataOffset = 261103, .width = 16, .height = 23 },
    { .dataOffset = 261256, .width = 11, .height = 23 },
    { .dataOffset = 261356, .width = 11, .height = 23 },
    { .dataOffset = 261469, .width = 11, .height = 23 },
    { .dataOffset = 261532, .width = 8, .height = 23 },
    { .dataOffset = 261627, .width = 4, .height = 23 },
    { .dataOffset = 261689, .width = 8, .height = 23 },
    { .dataOffset = 261779, .width = 12, .height = 23 },
    },
    {
    { .dataOffset = 261815, .width = 8, .height = 26 },
    { .dataOffset = 261817, .width = 5, .height = 26 },
    { .dataOffset = 261882, .width = 7, .height = 26 },
    { .dataOffset = 261926, .width = 14, .height = 26 },
    { .dataOffset = 262050, .width = 12, .height = 26 },
    { .dataOffset = 262195, .width = 15, .height = 26 },
    { .dataOffset = 262360, .width = 14, .height = 26 },
    { .dataOffset = 262517, .width = 4, .height = 26 },
    { .dataOffset = 262536, .width = 8, .height = 26 },
    { .dataOffset = 262654, .width = 8, .height = 26 },
    { .dataOffset = 262773, .width = 11, .height = 26 },
    { .dataOffset = 262851, .width = 12, .height = 26 },
    { .dataOffset = 262911, .width = 6, .height = 26 },
    { .dataOffset = 262942, .width = 8, .height = 26 },
    { .dataOffset = 262956, .width = 5, .height = 26 },
    { .dataOffset = 262970, .width = 10, .height = 26 },
    { .dataOffset = 263052, .width = 12, .height = 26 },
    { .dataOffset = 263204, .width = 12, .height = 26 },
    { .dataOffset = 263297, .width = 12, .height = 26 },
    { .dataOffset = 263406, .width = 12, .height = 26 },
    { .dataOffset = 263525, .width = 12, .height = 26 },
    { .dataOffset = 263625, .width = 12, .height = 26 },
    { .dataOffset = 263736, .width = 12, .height = 26 },
    { .dataOffset = 263863, .width = 12, .height = 26 },
    { .dataOffset = 263948, .width = 12, .height = 26 },
    { .dataOffset = 264094, .width = 12, .height = 26 },
    { .dataOffset = 264225, .width = 5, .height = 26 },
    { .dataOffset = 264251, .width = 6, .height = 26 },
    { .dataOffset = 264291, .width = 10, .height = 26 },
    { .dataOffset = 264351, .width = 11, .height = 26 },
    { .dataOffset = 264373, .width = 11, .height = 26 },
    { .dataOffset = 264438, .width = 10, .height = 26 },
    { .dataOffset = 264522, .width = 19, .height = 26 },
    { .dataOffset = 264801, .width = 15, .height = 26 },
    { .dataOffset = 264938, .width = 12, .height = 26 },
    { .dataOffset = 265063, .width = 14, .height = 26 },
    { .dataOffset = 265198, .width = 13, .height = 26 },
    { .dataOffset = 265334, .width = 11, .height = 26 },
    { .dataOffset = 265402, .width = 11, .height = 26 },
    { .dataOffset = 265474, .width = 14, .height = 26 },
    { .dataOffset = 265624, .width = 13, .height = 26 },
    { .dataOffset = 265756, .width = 4, .height = 26 },
    { .dataOffset = 265814, .width = 12, .height = 26 },
    { .dataOffset = 265921, .width = 13, .height = 26 },
    { .dataOffset = 266075, .width = 11, .height = 26 },
    { .dataOffset = 266147, .width = 16, .height = 26 },
    { .dataOffset = 266380, .width = 13, .height = 26 },
    { .dataOffset = 266564, .width = 14, .height = 26 },
    { .dataOffset = 266717, .width = 13, .height = 26 },
    { .dataOffset = 266823, .width = 14, .height = 26 },
    { .dataOffset = 266997, .width = 13, .height = 26 },
    { .dataOffset = 267132, .width = 13, .height = 26 },
    { .dataOffset = 267266, .width = 14, .height = 26 },
    { .dataOffset = 267352, .width = 13, .height = 26 },
    { .dataOffset = 267493, .width = 15, .height = 26 },
    { .dataOffset = 267641, .width = 20, .height = 26 },
    { .dataOffset = 267889, .width = 15, .height = 26 },
    { .dataOffset = 268048, .width = 14, .height = 26 },
    { .dataOffset = 268171, .width = 13, .height = 26 },
    { .dataOffset = 268256, .width = 7, .height = 26 },
    { .dataOffset = 268372, .width = 11, .height = 26 },
    { .dataOffset = 268459, .width = 6, .height = 26 },
    { .dataOffset = 268556, .width = 9, .height = 26 },
    { .dataOffset = 268618, .width = 12, .height = 26 },
    { .dataOffset = 268632, .width = 7, .height = 26 },
    { .dataOffset = 268653, .width = 11, .height = 26 },
    { .dataOffset = 268761, .width = 12, .height = 26 },
    { .dataOffset = 268904, .width = 11, .height = 26 },
    { .dataOffset = 268995, .width = 11, .height = 26 },
    { .dataOffset = 269125, .width = 12, .height = 26 },
    { .dataOffset = 269215, .width = 10, .height = 26 },
    { .dataOffset = 269309, .width = 12, .height = 26 },
    { .dataOffset = 269463, .width = 11, .height = 26 },
    { .dataOffset = 269598, .width = 5, .height = 26 },
    { .dataOffset = 269678, .width = 7, .height = 26 },
    { .dataOffset = 269782, .width = 12, .height = 26 },
    { .dataOffset = 269933, .width = 5, .height = 26 },
    { .dataOffset = 270025, .width = 18, .height = 26 },
    { .dataOffset = 270209, .width = 11, .height = 26 },
    { .dataOffset = 270328, .width = 12, .height = 26 },
    { .dataOffset = 270441, .width = 12, .height = 26 },
    { .dataOffset = 270586, .width = 11, .height = 26 },
    { .dataOffset = 270717, .width = 8, .height = 26 },
    { .dataOffset = 270789, .width = 11, .height = 26 },
    { .dataOffset = 270894, .width = 8, .height = 26 },
    { .dataOffset = 270969, .width = 11, .height = 26 },
    { .dataOffset = 271080, .width = 12, .height = 26 },
    { .dataOffset = 271181, .width = 17, .height = 26 },
    { .dataOffset = 271354, .width = 12, .height = 26 },
    { .dataOffset = 271464, .width = 12, .height = 26 },
    { .dataOffset = 271588, .width = 11, .height = 26 },
    { .dataOffset = 271656, .width = 9, .height = 26 },
    { .dataOffset = 271769, .width = 4, .height = 26 },
    { .dataOffset = 271856, .width = 9, .height = 26 },
    { .dataOffset = 271975, .width = 14, .height = 26 },
    },
    {
    { .dataOffset = 272028, .width = 9, .height = 29 },
    { .dataOffset = 272032, .width = 5, .height = 29 },
    { .dataOffset = 272117, .width = 7, .height = 29 },
    { .dataOffset = 272162, .width = 14, .height = 29 },
    { .dataOffset = 272308, .width = 12, .height = 29 },
    { .dataOffset = 272474, .width = 17, .height = 29 },
    { .dataOffset = 272675, .width = 16, .height = 29 },
    { .dataOffset = 272862, .width = 5, .height = 29 },
    { .dataOffset = 272894, .width = 8, .height = 29 },
    { .dataOffset = 273030, .width = 8, .height = 29 },
    { .dataOffset = 273166, .width = 11, .height = 29 },
    { .dataOffset = 273256, .width = 14, .height = 29 },
    { .dataOffset = 273309, .width = 5, .height = 29 },
    { .dataOffset = 273335, .width = 8, .height = 29 },
    { .dataOffset = 273349, .width = 5, .height = 29 },
    { .dataOffset = 273363, .width = 11, .height = 29 },
    { .dataOffset = 273458, .width = 12, .height = 29 },
    { .dataOffset = 273622, .width = 12, .height = 29 },
    { .dataOffset = 273730, .width = 12, .height = 29 },
    { .dataOffset = 273853, .width = 12, .height = 29 },
    { .dataOffset = 273995, .width = 12, .height = 29 },
    { .dataOffset = 274134, .width = 12, .height = 29 },
    { .dataOffset = 274263, .width = 12, .height = 29 },
    { .dataOffset = 274411, .width = 12, .height = 29 },
    { .dataOffset = 274506, .width = 12, .height = 29 },
    { .dataOffset = 274674, .width = 12, .height = 29 },
    { .dataOffset = 274830, .width = 5, .height = 29 },
    { .dataOffset = 274856, .width = 6, .height = 29 },
    { .dataOffset = 274898, .width = 12, .height = 29 },
    { .dataOffset = 274971, .width = 12, .height = 29 },
    { .dataOffset = 274997, .width = 12, .height = 29 },
    { .dataOffset = 275069, .width = 12, .height = 29 },
    { .dataOffset = 275170, .width = 20, .height = 29 },
    { .dataOffset = 275481, .width = 16, .height = 29 },
    { .dataOffset = 275640, .width = 14, .height = 29 },
    { .dataOffset = 275808, .width = 14, .height = 29 },
    { .dataOffset = 275950, .width = 14, .height = 29 },
    { .dataOffset = 276126, .width = 13, .height = 29 },
    { .dataOffset = 276224, .width = 13, .height = 29 },
    { .dataOffset = 276322, .width = 14, .height = 29 },
    { .dataOffset = 276469, .width = 15, .height = 29 },
    { .dataOffset = 276651, .width = 5, .height = 29 },
    { .dataOffset = 276749, .width = 13, .height = 29 },
    { .dataOffset = 276856, .width = 15, .height = 29 },
    { .dataOffset = 277045, .width = 12, .height = 29 },
    { .dataOffset = 277141, .width = 19, .height = 29 },
    { .dataOffset = 277442, .width = 15, .height = 29 },
    { .dataOffset = 277676, .width = 15, .height = 29 },
    { .dataOffset = 277846, .width = 14, .height = 29 },
    { .dataOffset = 277984, .width = 15, .height = 29 },
    { .dataOffset = 278175, .width = 14, .height = 29 },
    { .dataOffset = 278349, .width = 14, .height = 29 },
    { .dataOffset = 278496, .width = 15, .height = 29 },
    { .dataOffset = 278594, .width = 14, .height = 29 },
    { .dataOffset = 278782, .width = 16, .height = 29 },
    { .dataOffset = 278946, .width = 21, .height = 29 },
    { .dataOffset = 279238, .width = 15, .height = 29 },
    { .dataOffset = 279406, .width = 15, .height = 29 },
    { .dataOffset = 279549, .width = 14, .height = 29 },
    { .dataOffset = 279647, .width = 7, .height = 29 },
    { .dataOffset = 279775, .width = 11, .height = 29 },
    { .dataOffset = 279877, .width = 7, .height = 29 },
    { .dataOffset = 279967, .width = 11, .height = 29 },
    { .dataOffset = 280041, .width = 13, .height = 29 },
    { .dataOffset = 280057, .width = 7, .height = 29 },
    { .dataOffset = 280076, .width = 12, .height = 29 },
    { .dataOffset = 280195, .width = 12, .height = 29 },
    { .dataOffset = 280352, .width = 13, .height = 29 },
    { .dataOffset = 280459, .width = 13, .height = 29 },
    { .dataOffset = 280626, .width = 13, .height = 29 },
    { .dataOffset = 280735, .width = 10, .height = 29 },
    { .dataOffset = 280841, .width = 13, .height = 29 },
    { .dataOffset = 281012, .width = 12, .height = 29 },
    { .dataOffset = 281186, .width = 5, .height = 29 },
    { .dataOffset = 281272, .width = 7, .height = 29 },
    { .dataOffset = 281381, .width = 12, .height = 29 },
    { .dataOffset = 281545, .width = 5, .height = 29 },
    { .dataOffset = 281649, .width = 19, .height = 29 },
    { .dataOffset = 281862, .width = 12, .height = 29 },
    { .dataOffset = 282006, .width = 14, .height = 29 },
    { .dataOffset = 282130, .width = 12, .height = 29 },
    { .dataOffset = 282282, .width = 13, .height = 29 },
    { .dataOffset = 282439, .width = 8, .height = 29 },
    { .dataOffset = 282515, .width = 12, .height = 29 },
    { .dataOffset = 282620, .width = 10, .height = 29 },
    { .dataOffset = 282695, .width = 12, .height = 29 },
    { .dataOffset = 282837, .width = 12, .height = 29 },
    { .dataOffset = 282953, .width = 18, .height = 29 },
    { .dataOffset = 283156, .width = 13, .height = 29 },
    { .dataOffset = 283280, .width = 12, .height = 29 },
    { .dataOffset = 283418, .width = 12, .height = 29 },
    { .dataOffset = 283493, .width = 9, .height = 29 },
    { .dataOffset = 283618, .width = 5, .height = 29 },
    { .dataOffset = 283734, .width = 9, .height = 29 },
    { .dataOffset = 283861, .width = 15, .height = 29 },
    },
};

const fs_char_info_s fs_char_info_digits[2][12] =
{
    {
    { .dataOffset = 283927, .width = 9, .height = 38 },
    { .dataOffset = 283982, .width = 8, .height = 38 },
    { .dataOffset = 284012, .width = 20, .height = 38 },
    { .dataOffset = 284287, .width = 20, .height = 38 },
    { .dataOffset = 284463, .width = 20, .height = 38 },
    { .dataOffset = 284653, .width = 20, .height = 38 },
    { .dataOffset = 284878, .width = 20, .height = 38 },
    { .dataOffset = 285092, .width = 20, .height = 38 },
    { .dataOffset = 285299, .width = 20, .height = 38 },
    { .dataOffset = 285544, .width = 20, .height = 38 },
    { .dataOffset = 285701, .width = 20, .height = 38 },
    { .dataOffset = 285978, .width = 20, .height = 38 },
    },
    {
    { .dataOffset = 286227, .width = 11, .height = 54 },
    { .dataOffset = 286297, .width = 9, .height = 54 },
    { .dataOffset = 286333, .width = 26, .height = 54 },
    { .dataOffset = 286689, .width = 26, .height = 54 },
    { .dataOffset = 286888, .width = 26, .height = 54 },
    { .dataOffset = 287154, .width = 26, .height = 54 },
    { .dataOffset = 287456, .width = 26, .height = 54 },
    { .dataOffset = 287738, .width = 26, .height = 54 },
    { .dataOffset = 288009, .width = 26, .height = 54 },
    { .dataOffset = 288340, .width = 26, .height = 54 },
    { .dataOffset = 288543, .width = 26, .height = 54 },
    { .dataOffset = 288912, .width = 26, .height = 54 },
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


bool fs_getCharInfo(const char c, const font_key_e font_key, fs_char_info_s *p_out_char_info, uint8_t *p_dataLocation)
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
                *p_dataLocation = FS_FONT_DATA_LOCATION;
            }
            break;
        }
        case FONT_KEY_ROBOTO_36_B:
        case FONT_KEY_ROBOTO_48_B:
        {
            if ((FS_CHAR_INFOS_IN_DIGIT_ONLY_FONT > charIndex) && (FS_CHAR_INFOS_IN_DIGIT_ONLY_FONT > fontIndex) && (charIndex >= 0) && (fontIndex >= 0))
            {
                *p_out_char_info = fs_char_info_digits[fontIndex][charIndex];
                charInfoFound = true;
                *p_dataLocation = FS_FONT_DATA_LOCATION;
            }
            break;
        }
        default:
            break;
    }

    return charInfoFound;
}

/*** end of file ***/
