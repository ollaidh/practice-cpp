#include "node.h"
#include <stdexcept>


bool EmptyNode::Evaluate(const Date& date, const std::string& event) const {
    return true;
}

bool DateComparisonNode::Evaluate(const Date& date, const std::string& event) const {
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

bool EventComparisonNode::Evaluate(const Date& date, const std::string& event) const {
    if (m_cmp == Comparison::Equal) {
        return event == m_event;
    } else if (m_cmp == Comparison::NotEqual) {
        return event != m_event;
    } else if (m_cmp == Comparison::Less) {
        return event < m_event;
    } else if (m_cmp == Comparison::LessOrEqual) {
        return event < m_event || event == m_event;
    } else if (m_cmp == Comparison::Greater) {
        return m_event < event;
    } else if (m_cmp == Comparison::GreaterOrEqual) {
        return m_event < event || event == m_event;
    }
    return false;
}

bool LogicalOperationNode::Evaluate(const Date& date, const std::string& event) const {
    bool left = m_left->Evaluate(date, event);
    bool right = m_right->Evaluate(date, event);
    if (m_op == LogicalOperation::And) {
        return left && right;
    } else if (m_op == LogicalOperation::Or) {
        return left || right;
    }
    throw std::invalid_argument("crap");
}