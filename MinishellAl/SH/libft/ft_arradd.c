
#include "libft.h"

static char **create_new_arr(char **src, char *item)
{
    int     size;
    int     i;
    char    **new_arr;

    size = 0;
    while (src && src[size])
        size++;
    new_arr = malloc(sizeof(char *) * (size + 2));
    if (!new_arr)
        return (NULL);
    i = 0;
    while (i < size)
    {
        new_arr[i] = malloc(ft_strlen(src[i]) + 1);
        if (new_arr[i])
            ft_strcpy(new_arr[i], src[i]);
        i++;
    }
    new_arr[size] = malloc(ft_strlen(item) + 1);
    if (new_arr[size])
        ft_strcpy(new_arr[size], item);
    new_arr[size + 1] = NULL;
    return (new_arr);
}

static void free_old_array(char **src)
{
    int i;

    i = 0;
    while (src && src[i])
    {
        free(src[i]);
        i++;
    }
    free(src);
}

void add_char(char **src, char ***ret, char *item)
{
    char **new_arr;

    new_arr = create_new_arr(src, item);
    *ret = new_arr;
    free_old_array(src);
}


void *ft_arradd(void **src, char *type, void *item)
{
    void    **ret;

    ret = NULL;
    if (!ft_strcmp(type, "char"))
        add_char((char **)src, (char ***)&ret, (char *)item);
    else
    {
        write(1, "add more array types you lazy bug", 33);
        return (NULL);
    }
    return (ret);
}

