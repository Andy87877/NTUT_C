// ut.cpp
#include <gtest/gtest.h>
#include <cstdlib>
#include "fms.h"

TEST(fmsTest, HandleInput) {
    struct TestCase {
        const char* input;
        const char* expectedOutput;
    };

    TestCase testCases[] = {
        {"rate", "rate - Identifier"},
        {"R2D2", "R2D2 - Identifier"},
        {"-2", "-2 - Negative Integer"},
        {"time", "time - Identifier"},
        {"555666", "555666 - Positive Integer"},
        {"0.23", "0.23 - Positive Floating"},
        {"-1.2", "-1.2 - Negative Floating"},
        {"5a", "5a - Error"},
        {".123", ".123 - Error"},
        {"0", "0 - Positive Integer"},
        {"01", "01 - Error"},
        {"0123", "0123 - Error"},
        {"-0", "-0 - Error"},
        {"12345...", "12345... - Error"},
        {"Abc...", "Abc... - Error"},
        {"12345.", "12345. - Error"},
        {"_hello_", "_hello_ - Identifier"},
        {"$123$", "$123$ - Error"},
        {"AAA", "AAA - Identifier"},
        {"___", "___ - Identifier"},
        {"a", "a - Identifier"},
        {"z", "z - Identifier"},
        {"A", "A - Identifier"},
        {"Z", "Z - Identifier"},
        {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz - Identifier"},
        {"_", "_ - Identifier"},
        {"12345ABC", "12345ABC - Error"},
        {"{}", "{} - Error"}
    };

    for (const auto& testCase : testCases) {
        ASSERT_STREQ(testCase.expectedOutput, FMS(testCase.input));
    }
}

int main(int argc, char **argv) {
    testing ::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}