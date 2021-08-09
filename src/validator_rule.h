#ifndef VALIDATOR_RULE_H
#define VALIDATOR_RULE_H

#include <regex>
#include <string>


class ValidatorRule
{
    unsigned int idRule;
    std::string rule;
    std::regex pattern;
    std::string string_pattern;

public:
    ValidatorRule()
        : idRule(0), rule(""), pattern(nullptr), string_pattern("")
    {
    }

    ValidatorRule(std::string rule, std::regex pattern)
        : idRule(0), rule(rule), pattern(pattern), string_pattern("")
    {

    }

    virtual ~ValidatorRule()
    {

    }

    void setIdRule(unsigned int idRule)
    {
        if (idRule > 0)
        {
            this->idRule = idRule;
        }
    }

    auto getIdRule() const noexcept -> unsigned int
    {
        return this->idRule;
    }

    void setRule(std::string rule)
    {
        this->rule = rule;
    }

    auto getRule() const noexcept -> std::string
    {
        return this->rule;
    }

    void setPattern(std::regex pattern)
    {
        this->pattern = pattern;
    }

    auto getPattern() const noexcept -> std::regex
    {
        return this->pattern;
    }

    void setStringPattern(std::string string_pattern)
    {
        this->string_pattern = string_pattern;
    }

    auto getStringPattern() const noexcept -> std::string
    {
        return this->string_pattern;
    }

};


#endif // VALIDATOR_RULE_H
