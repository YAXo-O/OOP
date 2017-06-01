#ifndef COMMANDS_H
#define COMMANDS_H

#include "transformations.h"
#include "int_standart.h"

enum command
{
    c_open, c_transform, c_clean, c_unknown
};

struct argument
{
    transformations &trans;
    const char *fileName;
};

const int_std status_ok = 0;
const int_std status_open_file_error = -1;
const int_std status_invalid_arg_no_file = -2;
const int_std status_no_mesh = -3;
const int_std status_unknown_command = -4;

#endif // COMMANDS_H
