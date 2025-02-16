
#include "libft.h"

static void copy_char(char **src, char ***ret)
{    
    int i;
    int j;

    i = 0;
    while (src[i])
    {
        j = 0;
        while (src[i][j])
        {
            (*ret)[i][j] = src[i][j];
            j++;
        }
        (*ret)[i][j] = '\0';
        i++;
    }
    (*ret)[i] = NULL;
}

static void convert_char(char **src, char ***ret)
{
    int i;

    i = 0;
    while (src[i])
        i++;
    *ret = malloc(sizeof(char *) * (i + 1));
    if (!*ret)
        return;
    i = 0;
    while (src[i])
    {
        (*ret)[i] = malloc(sizeof(char) * (ft_strlen(src[i]) + 1));
        if (!(*ret)[i])
        {
            while (i > 0)
                free((*ret)[--i]);
            free(*ret);
            *ret = NULL;
            return ;
        }
        i++;
    }
    copy_char(src, ret);
}

void **ft_array_dup(void **src, char *type)
{
    void    **ret;

    ret = NULL;
    if (!ft_strcmp(type, "char"))
        convert_char((char **)src, (char ***)&ret);
    else
    {
        write(1, "add more array types you lazy bug", 33);
        return (NULL);
    }
    return (ret);

}
