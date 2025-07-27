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

bool matchplus(int c, const char *regexp, const char *text) {
    return regexp[0] == *text++ && matchstar(regexp[0], regexp + 2, text);
}

bool matchquestion(int c, const char *regexp, const char *text) {
    if (*text != '\0' && (*text == c || c == '.'))
        return matchhere(regexp, text + 1);
    return matchhere(regexp, text);
}

bool matchhere(const char *regexp, const char *text) {
    if (regexp[0] == '\0')
        return true;
    if (regexp[1] == '*')
        return matchstar(regexp[0], regexp + 2, text);
    if (regexp[1] == '+')
        return matchplus(regexp[0], regexp, text);
    if (regexp[1] == '?')
        return matchquestion(regexp[0], regexp + 2, text);
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
    assert(match("aba", "ababa") == true);
    assert(match("^aba$", "ababa") == false);
    assert(match("a*.c", "abab124124lla") == false);
    assert(match("a*a", "abab124124lla") == true);
    assert(match(".*", "aslfjaslkfalksjg;ajsx,.cbm.c") == true);
    assert(match("a+", "v") == false);
    assert(match("a+", "a") == true);
    assert(match("a+", "aa") == true);
    assert(match("ba+", "baaa") == true);
    assert(match("ba+q", "baaaq") == true);
    assert(match("ba+q", "baaa") == false);
    assert(match("ba+q", "bq") == false);
    assert(match("ba?q", "baq") == true);
    assert(match("ba?q", "bq") == true);
    assert(match("ba3?q", "ba3q") == true);
    assert(match("b?b?", "b") == true);
    assert(match("^b?b?$", "aa") == false);


}
