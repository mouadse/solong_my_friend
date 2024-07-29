#include "so_long.h"


#include <stdlib.h>
#include <string.h>

/**
 * Trims characters specified in 'set' from both the start and end of 's'.
 * @param s The string to be trimmed.
 * @param set The set of characters to trim.
 * @return A new string with the specified characters removed from the start and end.
 */
char *ft_strtrim(const char *s, const char *set)
{
    if (!s || !set)
        return NULL;

    size_t start = 0;
    size_t end = strlen(s);

    // Find the first character that is not in the 'set'
    while (s[start] && strchr(set, s[start]))
        start++;

    // If all characters are trimmed, return an empty string
    if (start == end)
        return strdup("");

    // Find the last character that is not in the 'set'
    while (end > start && strchr(set, s[end - 1]))
        end--;

    // Allocate memory for the trimmed string
    char *trimmed = malloc(end - start + 1);
    if (!trimmed)
        return NULL;

    // Copy the trimmed portion of the string
    strncpy(trimmed, s + start, end - start);
    trimmed[end - start] = '\0';  // Null-terminate the new string

    return trimmed;
}
