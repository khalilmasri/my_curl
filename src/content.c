#include "../include/include.h"

//function to search for "Content-Length: " in buffer
int get_content_len(char *buffer)
{
    int i = 0, j = 0;
    while (buffer[i] != '\0')
    {
        if (buffer[i] == 'C' && buffer[i + 1] == 'o' && buffer[i + 2] == 'n' && buffer[i + 3] == 't' && buffer[i + 4] == 'e' && buffer[i + 5] == 'n' && buffer[i + 6] == 't' && buffer[i + 7] == '-' && buffer[i + 8] == 'L' && buffer[i + 9] == 'e' && buffer[i + 10] == 'n' && buffer[i + 11] == 'g' && buffer[i + 12] == 't' && buffer[i + 13] == 'h' && buffer[i + 14] == ':')
        {
            i = i + 16;
            while (buffer[i] != '\0' && buffer[i] != '\r')
            {
                j = j * 10 + (buffer[i] - '0');
                i++;
            }
            return j;
        }
        else
            i++;
    }
    return -1;
}
