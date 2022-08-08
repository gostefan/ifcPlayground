#include "IfcFileTokenizer.h"

#include "gtest/gtest.h"

#include <sstream>


class IfcFileTokenizerTests : public ::testing::Test {};

TEST_F(IfcFileTokenizerTests, TwoTokens) {
	std::wistringstream stream(L"a;b", std::ios_base::in);
	ifc::in::IfcFileTokenizer tokenizer(stream);

	auto const& token1 = tokenizer.getCurrentToken();
	EXPECT_EQ(L"a", token1->getValue());
	tokenizer.moveToNextToken();

	auto const& token2 = tokenizer.getCurrentToken();
	EXPECT_EQ(L"b", token2->getValue());
	auto const [line, pos] = token2->getLineAndPos(0);
	EXPECT_EQ(0, line);
	EXPECT_EQ(2, pos);

	tokenizer.moveToNextToken();
	EXPECT_FALSE(tokenizer.getCurrentToken());
}

TEST_F(IfcFileTokenizerTests, NewlineInToken) {
	std::wistringstream stream(L"a\nb", std::ios_base::in);
	ifc::in::IfcFileTokenizer tokenizer(stream);

	auto const& token = tokenizer.getCurrentToken();
	EXPECT_EQ(L"ab", token->getValue());
	tokenizer.moveToNextToken();
	auto const [line, pos] = token->getLineAndPos(1);
	EXPECT_EQ(1, line);
	EXPECT_EQ(0, pos);

	tokenizer.moveToNextToken();
	EXPECT_FALSE(tokenizer.getCurrentToken());
}
