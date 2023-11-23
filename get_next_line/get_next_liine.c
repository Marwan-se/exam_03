#include<unistd.h>
#include<stdlib.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10
#endif


int ft_strlen(char *s)
{
    int i = 0;

    if(s)
    {
        while(*s++)
        i++;
    }
    return (i);
}

void *ft_calloc(size_t count, size_t size)
{
    void    *ptr;
    ptr = (void *)malloc(count * size);
    if(ptr != NULL)
        ft_bzero(ptr, count * size);
    return(ptr);
}

void    ft_bzero(void *s, size_t n);
{
    unsigned char *dst;
    size_t  i = 0;

    dst = (unsigned char *)s;
    while(i < n)
    {
        dst[i] = 0;
        i++;
    }
}