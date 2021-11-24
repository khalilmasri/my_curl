#include "../include/include.h"

char *remove_http(char *url, char *address)
{
    int i = 0, j = 0;

    while (url[i] != '\0')
    {
        if (url[i] == 'h' && url[i + 1] == 't' && url[i + 2] == 't' && url[i + 3] == 'p' && url[i + 4] == ':')
            i = i + 7;
        else if (url[i] == 'h' && url[i + 1] == 't' && url[i + 2] == 't' && url[i + 3] == 'p' && url[i + 4] == 's' && url[i + 5] == ':')
            i = i + 8;
        else
        {
            address[j] = url[i];
            i++;
            j++;
        }
        address[j] = '\0';
    }
    return address;
}

char *get_path(char *address, char *path)
{
    int i = 0, j = 0;
    while (address[i] != '\0')
    {
        if (address[i] == '/')
        {
            i++;
            while (address[i] != '\0')
            {
                path[j] = address[i];
                i++;
                j++;
            }
            path[j] = '\0';
        }
        else
            i++;
    }
    return path;
}

char *remove_path(char *address)
{
    int i = 0;
    while (address[i] != '\0' && address[i] != '/')
        i++;

    address[i] = '\0';
    return address;
}

