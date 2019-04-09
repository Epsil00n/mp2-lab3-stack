#include "tformula.h"
#include "tstack.h"

#include "gtest.h"

//тестируем стэк
TEST(TStack, can_create_stack_with_positive_length)
{
	TStack st(5);
	
	EXPECT_EQ(DataOK, st.GetRetCode());
}

TEST(TStack, create_empty_stack)
{
	TStack st(3);

	EXPECT_EQ(true, st.IsEmpty());
}

TEST(TStack, cant_put_with_no_mem)
{
	TStack st(0);

	st.Put(3);

	EXPECT_EQ(DataNoMem, st.GetRetCode());
}

TEST(TStack, cant_put_if_full)
{
	TStack st(1);

	st.Put(1);
	st.Put(2);

	EXPECT_EQ(DataFull, st.GetRetCode());
}

TEST(TStack, can_put_if_ok)
{
	TStack st(3);

	st.Put(3);

	EXPECT_EQ(DataOK, st.GetRetCode());
}

TEST(TStack, have_value_when_put)
{
	TStack st(2);

	st.Put(4);

	EXPECT_EQ(4, st.TopElem());
}

TEST(TStack, cant_get_with_no_mem)
{
	TStack st(0);

	st.Get();

	EXPECT_EQ(DataNoMem, st.GetRetCode());
}

TEST(TStack, cant_get_if_empty)
{
	TStack st(3);

	st.Get();

	EXPECT_EQ(DataEmpty, st.GetRetCode());
}

TEST(TStack, can_get_if_have_value)
{
	TStack st(3);

	st.Put(4);
	st.Get();

	EXPECT_EQ(DataOK, st.GetRetCode());
}

TEST(TStack, can_get_true_value)
{
	TStack st(3);

	st.Put(3);
	
	EXPECT_EQ(3, st.Get());
}

TEST(TStack, empty_stack_after_get_first_element)
{
	TStack st(2);

	st.Put(5);
	st.Get();

	EXPECT_EQ(true, st.IsEmpty());
}

TEST(TStack, cant_topelem_when_no_mem)
{
	TStack st(0);

	st.TopElem();

	EXPECT_EQ(DataNoMem, st.GetRetCode());
}

TEST(TStack, cant_topelem_if_empty)
{
	TStack st(5);

	st.TopElem();

	EXPECT_EQ(DataEmpty, st.GetRetCode());
}

TEST(TStack, can_topelem)
{
	TStack st(3);

	st.Put(9);
	st.TopElem();

	EXPECT_EQ(DataOK, st.GetRetCode());
}

TEST(TStack, can_topelem_true_value)
{
	TStack st(3);

	st.Put(4);

	EXPECT_EQ(4, st.TopElem());
}


// тестируем tformula

TEST(TFormula, can_create_formula)
{
	char* s = "2+3";

	ASSERT_NO_THROW(TFormula f(s));
}

TEST(TFormula, check_true_brackets)
{
	char* s1 = "()()";
	char* s2 = "(())";

	int br1[4] = { 0 };
	int br2[4] = { 0 };

	TFormula f1(s1);
	TFormula f2(s2);

	EXPECT_EQ(0, f1.FormulaChecker(br1, 4));
	EXPECT_EQ(0, f2.FormulaChecker(br2, 4));
}

TEST(TFormula, check_true_brackets_in_formula)
{
	char* s = "(2+3)/8*(4/(5-7))";
	TFormula f(s);

	int br[6] = { 0 };

	EXPECT_EQ(0, f.FormulaChecker(br, 6));
}

TEST(TFormula, check_wrong_brackets)
{
	char* c = "((()";
	TFormula f(c);

	int br[6] = { 0 };

	EXPECT_NE(0, f.FormulaChecker(br, 6));
}

TEST(TFormula, check_wrong_brackets_in_formula)
{
	char* s = "((2+3)/8*(4/(5-7))";
	TFormula f(s);

	int br[8] = { 0 };

	EXPECT_NE
(0, f.FormulaChecker(br, 8));
}

TEST(TFormula, cant_convert_formula_with_wrong_brackets)
{
	char* s = "((2+3)/8*(4/(5-7))";
	TFormula f(s);

	ASSERT_ANY_THROW(f.FormulaConverter());

}

TEST(TFormula, can_convert_formula_with_true_brackets)
{
	char* s = "(2+3)/8*(4/(5-7))";
	TFormula f(s);

	ASSERT_NO_THROW(f.FormulaConverter());
}

TEST(TFormula, can_add)
{
	char* s = "2+5+6";
	TFormula f(s);

	f.FormulaConverter();

	EXPECT_EQ(13, f.FormulaCalculator());
}

TEST(TFormula, can_subtract)
{
	char* s = "2-5-6";
	TFormula f(s);

	f.FormulaConverter();

	EXPECT_EQ(-9, f.FormulaCalculator());
}

TEST(TFormula, can_multiply)
{
	char* s = "2*5*6";
	TFormula f(s);

	f.FormulaConverter();

	EXPECT_EQ(60, f.FormulaCalculator());
}

TEST(TFormula, can_divide)
{
	char* s = "2*6/3";
	TFormula f(s);

	f.FormulaConverter();

	EXPECT_EQ(4, f.FormulaCalculator());
}

TEST(TFormula, can_calculate_difficult_formula_with_brackets)
{
	char* c = "2+(4*3-5+9)/8";//4
	TFormula f(c);
	
	f.FormulaConverter();

	EXPECT_EQ(4, f.FormulaCalculator());
}

TEST(TFormula, calculate_with_fractions)
{
	char* c = "2.5+(4*3.5-5+9)/2";//11.5
	TFormula f(c);

	f.FormulaConverter();

	EXPECT_DOUBLE_EQ(11.5, f.FormulaCalculator());
}