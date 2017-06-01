#include "file.h"

bool openFile(file_t &f, const char *fileName, const char *mode)
{
    f.filePointer = fopen(fileName, mode);
    if(f.filePointer == nullptr)
        return false;

    return true;
}

void closeFile(file_t &f)
{
    if(f.filePointer != nullptr)
        fclose(f.filePointer);
}

bool getString(char *buffer, size_t size, file_t &file)
{
    return fgets(buffer, size, file.filePointer) != nullptr;
}
