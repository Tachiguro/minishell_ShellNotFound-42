int ft_numlen(int n)
{
    int i;

    i = 0;
    if (n == 0)
        return (1);
    if (n < 0)
        n = -n;
    while (n > 0)
    {
        n /= 10;
        i++;
    }
    return (i);
}