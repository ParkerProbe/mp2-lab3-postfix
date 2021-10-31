#include <string>
class EqExcepion {
    public:
        std::string comment;
        enum error_code 
        {
            empty_expression,
            zero_division, 
            bracket_mistake , 
            end_with_operator,
            start_with_incorrect_operator,
            two_operator_side_by_side
        } error;
        EqExcepion(error_code _error, const std::string& _comment = "")
        : error(_error), comment(_comment) {}

        int GetError() const 
        {
            return error;
        }

        std::string GetComment() const
        {
            return comment;
        }
};