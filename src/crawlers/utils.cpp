#include "utils.h"

void init_string(struct iostring *s)
{
    s->len = 0;
    s->ptr = (char*) malloc(s->len + 1);
    if (s->ptr == NULL)
    {
        fprintf(stderr, "malloc() failed\n");
        exit(EXIT_FAILURE);
    }
    s->ptr[0] = '\0';
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct iostring *s)
{
    size_t new_len = s->len + size*nmemb;
    s->ptr = (char*) realloc(s->ptr, new_len + 1);
    if (s->ptr == NULL)
    {
        fprintf(stderr, "realloc() failed\n");
        exit(EXIT_FAILURE);
    }
    memcpy(s->ptr + s->len, ptr, size * nmemb);
    s->ptr[new_len] = '\0';
    s->len = new_len;

    return size*nmemb;
}

std::string formatString(const std::string fmt, ...)
{
    int size = 100;
    std::string str;
    va_list ap;
    while (1)
    {
        str.resize(size);
        va_start(ap, fmt);
        int n = vsnprintf((char *) str.c_str(), size, fmt.c_str(), ap);
        va_end(ap);
        if (n > -1 && n < size)
        {
            str.resize(n);
            return str;
        }
        if (n > -1)
            size = n + 1;
        else
            size *= 2;
    }
    return str;
}




