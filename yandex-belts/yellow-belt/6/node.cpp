#include "node.h"


bool EmptyNode::Evaluate(const Date& date, const std::string& event) {
    return false;
}

bool DateComparisonNode::Evaluate(const Date& date, const std::string& event) {
    if (m_cmp == Comparison::Equal) {
        return date == m_date;
    } else if (m_cmp == Comparison::NotEqual) {
        return date != m_date;
    } else if (m_cmp == Comparison::Less) {
        return date < m_date;
    } else if (m_cmp == Comparison::LessOrEqual) {
        return date < m_date || date == m_date;
    } else if (m_cmp == Comparison::Greater) {
        return m_date < date;
    } else if (m_cmp == Comparison::GreaterOrEqual) {
        return m_date < date || date == m_date;
    }
    return false;
}

bool LogicalOperationNode::Evaluate(const Date& date, const std::string& event) {
    bool left = m_left->Evaluate(date, event);
    bool right = m_right->Evaluate(date, event);
    if (m_op == LogicalOperation::And) {
        return left && right;
    }
    return left || right;
}