#pragma once

#include <memory>

#include "date.h"

enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

enum class LogicalOperation {
    Or,
    And
};

class Node {
public:
    virtual bool Evaluate(const Date& date, const std::string& event) const = 0;
};

class EmptyNode : public Node {
public:
    bool Evaluate(const Date& date, const std::string& event) const override;
};

class DateComparisonNode : public Node {
public:
    DateComparisonNode(Comparison cmp, Date date)
    : m_cmp(cmp)
    , m_date(date) {
    }

    bool Evaluate(const Date& date, const std::string& event) const override;

private:
    Comparison m_cmp;
    Date m_date;
};

class EventComparisonNode : public Node {
public:
    EventComparisonNode(Comparison cmp, const std::string& event)
    : m_cmp(cmp)
    , m_event(event) {
    }

    bool Evaluate(const Date& date, const std::string& event) const override;

private:
    Comparison m_cmp;
    std::string m_event;
};

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(LogicalOperation op, std::shared_ptr<Node> left, std::shared_ptr<Node> right)
    : m_op(op)
    , m_left(left)
    , m_right(right) {

    }

    bool Evaluate(const Date& date, const std::string& event) const override;

private:

    LogicalOperation m_op;
    std::shared_ptr<Node> m_left;
    std::shared_ptr<Node> m_right;

};



