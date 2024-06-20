#pragma once
#include <gtest/gtest.h>

TEST(Version, TestVersionCount) {
    // Arrange

    // Assert
    EXPECT_TRUE(PROJECT_VERSION_PATCH > 0);
}