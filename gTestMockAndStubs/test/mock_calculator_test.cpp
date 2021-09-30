#include "MockCalculatorClass.h"
#include "Calculator.h"

#include "/home/bojan/Desktop/unitTests/practiceWithMocks/gtest-demo/googletest-master/googletest/include/gtest/gtest.h"


double factoriel(const double number){
int multiplied=1;
if(number<0)
{
multiplied=0;
}
else if(number==0)
{
multiplied=1;
}
else
{
for(int i=number;i>=1;i--)
{
multiplied*=i;
}
}
return multiplied;
}
// above function is stub. It is declared in calculator Class. But we use this implementation for testing. This type of writing is called stub.
using ::testing::AtLeast;

using ::testing::Return;
TEST(CalculatorTest, add)
{
    MockCalculatorClass calculations;
    EXPECT_CALL(calculations, add(1,2))
    .Times(AtLeast(1)).WillOnce(Return(300));
    EXPECT_CALL(calculations, substract(1,2))
    .Times(AtLeast(1)).WillRepeatedly(Return(300));
    EXPECT_CALL(calculations, multiply(1,2))
    .Times(AtLeast(1)).WillRepeatedly(Return(300));
    Calculator painter(&calculations);

    ASSERT_EQ(1,painter.sameNumber(1));
}

TEST(CalculatorTest, multiplySomething)
{
    MockCalculatorClass calculations;
    EXPECT_CALL(calculations, multiply(1,2))
    .Times(AtLeast(1)).WillRepeatedly(Return(300));
    Calculator painter(&calculations);
    EXPECT_CALL(calculations, substract(1,2))
    .Times(3).WillOnce(Return(300)).WillOnce(Return(200)).WillRepeatedly(Return(200));
    ASSERT_EQ(true,painter.returnSuccesufulIfDone(1,1,1));
}

TEST(CalculatorTest, divideSomething)
{
    MockCalculatorClass calculations;
    for(int i=0; i<numberOfTimes; i++)
    {
        EXPECT_CALL(calculations, divide(1*i,2*i)).WillOnce(Return(300*i));
    }
    Calculator painter(&calculations);
    ASSERT_EQ(1,painter.forDivide(1));
}
TEST(CalculatorTest, factorielPositiveStub)
{
    

    ASSERT_EQ(6,factoriel(3));

}
TEST(CalculatorTest, factorielNegativeStub)
{
    

    ASSERT_EQ(0,factoriel(-6));

}
TEST(CalculatorTest, factorielZeroStub)
{
    

    ASSERT_EQ(1,factoriel(0));

}



int main(int argc, char** argv)
{
    // The following line must be executed to initialize Google Mock
    // (and Google Test) before running the tests.
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}

