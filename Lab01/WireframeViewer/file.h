#ifndef FILE_H
#define FILE_H

#include <stdio.h>

struct file_t
{
    FILE *filePointer = nullptr;
};

bool openFile(file_t &f, const char *fileName, const char *mode);
void closeFile(file_t &f);

bool getString(char *buffer, size_t size, file_t &file);


#endif // FILE_H
