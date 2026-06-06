#pragma once
#include <string>
#include <fstream>
#include <cstddef>
#include <frontend/lexer/Token.hpp>

class Tokenizer {
public:
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
	const Token peek(int offset = 1);
	/** @} */
private:
	std::string currentFileName_ = "^v^";
	std::ifstream currentFile_;
	std::string contents_ = "^v^";
	std::size_t pos_ = 0;
};