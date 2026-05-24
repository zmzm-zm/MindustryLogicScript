#include "Operation_statement.hpp"
Operation_statement::Operation_statement(const std::string& left,
	std::string operator__,
	std::unique_ptr<Operation_statement> right):
    left_(left), operator_(operator__), right_(std::move(right)), tmp_(left_) {
	type_ = Statement_type::OPERATION;
}
/*
set m 1
set n 2
set x 3
set y t
op add a 1 2
op sub b 3 4
op mul a 3 4
op div b 3 4
op add c_ x y
op add c__ m n
op add c c_ c__
op add d m n
op add d d x
op add d d y

a = 1 + 2 + 3 + 4;
op add a 1 2
op add a a 3
op add a a 4
*/ 
std::string Operation_statement::to_string() {
	if (right_ == nullptr) {
			return "";
	}
	if (operator_ == "*") {
		operator_ = "mul";
	} else if (operator_ == "/") {
		operator_ = "div";
	} else if (operator_ == "+" || operator_ == "=") {
		operator_ = "add";
	} else if (operator_ == "-") {
		operator_ = "sub";
	}
	right_->tmp_ = tmp_;
	return "op " + operator_ + " " + tmp_ + " " + tmp_ + " " + right_->left_ + "\n" + right_->to_string();
}
const std::string& Operation_statement::get_left() const {
	return left_;
}
const std::unique_ptr<Operation_statement>& Operation_statement::get_right() const {
	return right_;
}
const std::string& Operation_statement::get_operator() const {
	return operator_;
}