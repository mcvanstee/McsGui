#ifndef VIEWS_GENERAL_CONFIRM_DIALOG_H_
#define VIEWS_GENERAL_CONFIRM_DIALOG_H_

#include "fs_file_search.h"

void confirm_dialog_show(
        const file_key_e title, const file_key_e message,
        void (*okBtnPressed)(void), void (*cancelBtnPressed)(void));

#endif /* VIEWS_GENERAL_CONFIRM_DIALOG_H_ */
