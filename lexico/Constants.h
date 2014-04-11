#ifndef CONSTANTS_H
#define CONSTANTS_H

enum TokenId 
{
    EPSILON  = 0,
    DOLLAR   = 1,
    t_id = 2,
    t_const_integer = 3,
    t_const_float = 4,
    t_const_string = 5,
    t_boolean = 6,
    t_do = 7,
    t_else = 8,
    t_end = 9,
    t_false = 10,
    t_flaot = 11,
    t_if = 12,
    t_integer = 13,
    t_main = 14,
    t_print = 15,
    t_println = 16,
    t_scan = 17,
    t_string = 18,
    t_true = 19,
    t_void = 20,
    t_while = 21,
    t_TOKEN_22 = 22, //"+"
    t_TOKEN_23 = 23, //"-"
    t_TOKEN_24 = 24, //"*"
    t_TOKEN_25 = 25, //"/"
    t_TOKEN_26 = 26, //"="
    t_TOKEN_27 = 27, //"&&"
    t_TOKEN_28 = 28, //"||"
    t_TOKEN_29 = 29, //"!"
    t_TOKEN_30 = 30, //"=="
    t_TOKEN_31 = 31, //"!="
    t_TOKEN_32 = 32, //"<"
    t_TOKEN_33 = 33, //"<="
    t_TOKEN_34 = 34, //">"
    t_TOKEN_35 = 35, //">="
    t_TOKEN_36 = 36, //","
    t_TOKEN_37 = 37, //";"
    t_TOKEN_38 = 38, //"("
    t_TOKEN_39 = 39, //")
};

const int STATES_COUNT = 45;

extern int SCANNER_TABLE[STATES_COUNT][256];

extern int TOKEN_STATE[STATES_COUNT];

extern int SPECIAL_CASES_INDEXES[41];

extern const char *SPECIAL_CASES_KEYS[16];

extern int SPECIAL_CASES_VALUES[16];

extern const char *SCANNER_ERROR[STATES_COUNT];

#endif
