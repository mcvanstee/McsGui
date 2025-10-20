#ifndef VIEWS_GENERAL_MESSAGE_DIALOG_H_
#define VIEWS_GENERAL_MESSAGE_DIALOG_H_

#include "fs_file_search.h"

void message_dialog_show(const file_key_e title, const file_key_e message, void (*okBtnPressed)(void));

#endif /* VIEWS_GENERAL_MESSAGE_DIALOG_H_ */
