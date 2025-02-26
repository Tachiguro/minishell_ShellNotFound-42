/*
 * update_export_value - Updates or adds an environment variable with an assignment.
 *
 * This function handles the case when item is of the form "NAME=value". It checks
 * if a variable with the same NAME exists in the environment. If so, it frees the
 * old entry and replaces it with a duplicate of item. If not found, it appends item.
 */

 #include "sh.h"

static void update_export_value(const char *item, t_str *stru)
{
    int     name_len;
    int     i;
    char    **env;

    name_len = ft_strchr(item, '=') - item;
    env = stru->environs->env;
    i = 0;
    while (env && env[i])
    {
        if ((ft_strncmp(env[i], item, name_len) == 0) && (env[i][name_len] == '='))
        {
            free(env[i]);
            env[i] = ft_strdup(item);
            return;
        }
        i++;
    }
    stru->environs->env = (char **)ft_arradd((void **)env, "char", (void *)item);
}

/*
 * export_without_value - Adds an environment variable with an empty value.
 *
 * This function handles the case when item is just a variable name (e.g., "VAR").
 * It checks if an entry for "VAR=" exists. If not, it creates a new entry "VAR=" and
 * appends it to the environment.
 */
static void export_without_value(const char *item, t_str *stru)
{
    int     name_len;
    int     i;
    char    **env;
    char    *new_item;

    name_len = strlen(item);
    env = stru->environs->env;
    i = 0;
    while (env && env[i])
    {
        if ((ft_strncmp(env[i], item, name_len) == 0) && (env[i][name_len] == '='))
            return;
        i++;
    }
    new_item = malloc(strlen(item) + 2);
    if (!new_item)
        return;
    ft_strcpy(new_item, item);
    ft_strcat(new_item, "=");
    stru->environs->env = (char **)ft_arradd((void **)env, "char", (void *)new_item);
    free(new_item);
}

/*
 * ft_export - Mimics bash's export command.
 *
 * If item contains an '=' (e.g., "VAR=value"), it updates or appends the variable.
 * If no '=' is present (e.g., "VAR"), it ensures that the variable is in the
 * environment with an empty value ("VAR=").
 */
void ft_export(const char *item, t_str *stru)
{
    char *eq_ptr;

    eq_ptr = strchr(item, '=');
    if (eq_ptr)
        update_export_value(item, stru);
    else
        export_without_value(item, stru);
}
