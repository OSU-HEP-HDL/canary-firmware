
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Arduino.h"
#include "Template.h"
using ::testing::Return;

namespace {

    Template libTemplate;

    TEST(SetupTest, handles0) {
        EXPECT_EQ(libTemplate.begin(0),0);
    }
    TEST(SetupTest, handles1) {
        EXPECT_EQ(libTemplate.begin(1),1);
    }
}