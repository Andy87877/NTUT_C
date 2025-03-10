// ut.cpp
#include <gtest/gtest.h>

#include <cstdlib>

#include "fms.h"
TEST(fmsTest, HandleInput) {
    char s[] = "rate R2D2 -2 time 555666 0.23 -1.2 5a .123 0 01 0123 -0 12345... Abc... 12345. _hello_ $123$ AAA ___ a z A Z ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz _ 12345ABC {} #";
    char expOutput[] =
        "rate - Identifier\n"
        "R2D2 - Identifier\n"
        "-2 - Negative Integer\n"
        "time - Identifier\n"
        "555666 - Positive Integer\n"
        "0.23 - Positive Floating\n"
        "-1.2 - Negative Floating\n"
        "5a - Error\n"
        ".123 - Error\n"
        "0 - Positive Integer\n"
        "01 - Error\n"
        "0123 - Error\n"
        "-0 - Error\n"
        "12345... - Error\n"
        "Abc... - Error\n"
        "12345. - Error\n"
        "_hello_ - Identifier\n"
        "$123$ - Error\n"
        "AAA - Identifier\n"
        "___ - Identifier\n"
        "a - Identifier\n"
        "z - Identifier\n"
        "A - Identifier\n"
        "Z - Identifier\n"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz - Identifier\n"
        "_ - Identifier\n"
        "12345ABC - Error\n"
        "{} - Error\n";
    ASSERT_STREQ(expOutput, FMS(s));
}
int main(int argc, char **argv) {
    testing ::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}