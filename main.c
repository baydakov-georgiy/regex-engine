#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

bool matchhere(const char *regexp, const char *text);

bool matchstar(int c, const char *regexp, const char *text) {
    do {
        if (matchhere(regexp, text))
            return true;
    } while (*text != '\0' && (*text++ == c || c == '.'));
    return false;
};

bool matchhere(const char *regexp, const char *text) {
    if (regexp[0] == '\0')
        return true;
    if (regexp[1] == '*')
        return matchstar(regexp[0], regexp + 2, text);
    if (regexp[0] == '$' && regexp[1] == '\0')
        return *text == '\0';
    if (*text != '\0' && (regexp[0] == '.' || regexp[0] == *text))
        return matchhere(regexp + 1, text + 1);
    return false;
};

bool match(const char *regexp, const char *text) {
    if (regexp[0] == '^')
        return matchhere(regexp + 1, text);
    do {
        if (matchhere(regexp, text))
            return true;
    } while (*text++ != '\0');
    return false;
};

int main() {
    assert(match("^aba$", "ababa") == false);
    assert(match("a*.c", "abab124124lla") == false);
    assert(match("a*a", "abab124124lla") == true);
}
