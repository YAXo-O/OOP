#include <cstring>
#include "linemanagment.h"

char *getLine(file_t &f)
{
    size_t const bufSize = 80;

    char buffer[bufSize];
    size_t size = bufSize;
    char *line = nullptr;
    size_t times = 0; // Сколько раз выделилась память

    bool bGo = true;
    while(getString(buffer, size, f) && bGo)
    {
          char *tmp = resize(line, times*size,  (times+1)*size);
          if(tmp == nullptr)
          {
              if(line)
                delete[] line;
              line = nullptr;
              bGo = false;
          }
          else
          {
              times++;
              line = tmp;

              for(size_t i = 0; (i < size) && bGo; i++)
              {
                  line[i + size*(times-1)] = buffer[i];

                  if(buffer[i] == '\n')
                  {
                      line[i + size*(times-1)] = '\0';
                      bGo = false;
                  }
              }
              if(!bGo)
                  break;
          }

    }

    return line;
}

char *resize(char *str, size_t oldSize, size_t newSize)
{
    char *resizedStr = new char[newSize];
    if(resizedStr == nullptr)
        return nullptr;

    if(oldSize)
        memcpy(resizedStr, str, oldSize);
    delete[] str;

    return resizedStr;

}

void clearLine(char *&str)
{
    delete[] str;
    str = nullptr;
}
