#pragma once
#include <string>
#include <fstream>
#include <cstddef>
#include <cstdint>
#include <frontend/lexer/Token.hpp>

enum class OperatorType {
    Multiplication = 2,
    Division = 2,
    Addition = 1,
    Subtraction = 1,
    Undefined = 999999,
};

class Tokenizer {
	enum class Strategy;
public:
	static OperatorType analyzeOperator(const std::string& operator__);
	void setCurrentFile(const std::string& file) noexcept;
	void initializeFile();
	bool isOperator(const std::string& c) noexcept;
	const Token::Type getToken(std::string value);
	/**
	 * @defgroup TokenGetter Token获取器
	 * @brief 获取Token的函数，有多种不同的模式
	 */
	/**
	 * @addtogroup TokenGetter
	 * @{
	 */
	/**
	 * @brief Token读取的基函数
	 * @details 合并了nextToken pass peek中重复的逻辑
	 */
	const Token readToken(Strategy strategy, uint8_t offset = 1);
	/**
	 * @brief 获取下一个Token并返回
	 * @return 一个常量Token
	 * @note 此函数会递增当前在文件的位置
	 */
	const Token nextToken();
	/**
	 * @brief 跳过下一个Token
	 * @note 此函数会递增当前在文件的位置
	 */
	void pass();
	/**
	 * @brief 查看后n个Token
	 * @param offset 指定看后面第几个Token，默认为1
	 * @return 一个常量Token
	 * @note 此函数不会递增当前在文件的位置
	 */
	const Token peek(uint8_t offset = 1);
	/** @} */
private:
	enum class Strategy {
		CONSUMPTIVE,
		NON_CONSUMPTIVE,
		NO_RETURN
	};
	std::string currentFileName_ = "^v^";
	std::ifstream currentFile_;
	std::string contents_ = "^v^";
	std::size_t pos_ = 0;
};
