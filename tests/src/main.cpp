#include "gtest/gtest.h"

#include "QApplication"

int main(int argc, char* argv[])
{
    /*Required to construct any QWidget*/
    QApplication application(argc, argv);

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
