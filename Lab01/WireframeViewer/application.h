#ifndef APPLICATION_H
#define APPLICATION_H

#include "int_standart.h"

class Application
{
private:
    int argc;
    char **argv;

public:
    Application(int _argc, char *_argv[]);
    int run();
};

#endif // APPLICATION_H
