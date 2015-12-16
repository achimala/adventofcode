#include <cassert>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

class Node {
public:
    virtual uint16_t evaluate() const = 0;
    virtual void reset() {}
};

class ConstantNode : public Node {
public:
    ConstantNode(int value)
        : m_value(value)
    {
    }

    virtual uint16_t evaluate() const override { return m_value; }

private:
    int m_value;
};

class VariableNode : public Node {
public:
    VariableNode(std::string name, const std::map<std::string, Node*>& variables)
        : m_name(name)
        , m_variables(variables)
        , m_cachedValue(0)
        , m_hasCachedValue(false)
    {
    }

    virtual uint16_t evaluate() const override {
        if (m_hasCachedValue) {
            return m_cachedValue;
        }

        m_hasCachedValue = true;
        return m_cachedValue = m_variables.at(m_name)->evaluate();
    }

    virtual void reset() override {
        m_hasCachedValue = false;
    }

private:
    std::string m_name;
    const std::map<std::string, Node*>& m_variables;
    mutable uint16_t m_cachedValue;
    mutable bool m_hasCachedValue;
};

class NotNode : public Node {
public:
    NotNode(Node& node)
        : m_node(node)
    {
    }

    virtual uint16_t evaluate() const override { return ~m_node.evaluate(); }

    virtual void reset() override {
        m_node.reset();
    }

private:
    Node& m_node;
};

class BinaryOperationNode : public Node {
public:
    BinaryOperationNode(Node& node1, Node& node2)
        : m_node1(node1)
        , m_node2(node2)
    {
    }

    virtual int apply(int, int) const = 0;
    virtual uint16_t evaluate() const override { return apply(m_node1.evaluate(), m_node2.evaluate()); }
    virtual void reset() override {
        m_node1.reset();
        m_node2.reset();
    }

private:
    Node& m_node1;
    Node& m_node2;
};

class AndNode : public BinaryOperationNode {
public:
    using BinaryOperationNode::BinaryOperationNode;
    virtual int apply(int a, int b) const override { return a & b; }
};

class OrNode : public BinaryOperationNode {
public:
    using BinaryOperationNode::BinaryOperationNode;
    virtual int apply(int a, int b) const override { return a | b; }
};

class LeftShiftNode : public BinaryOperationNode {
public:
    using BinaryOperationNode::BinaryOperationNode;
    virtual int apply(int a, int b) const override { return a << b; }
};

class RightShiftNode : public BinaryOperationNode {
public:
    using BinaryOperationNode::BinaryOperationNode;
    virtual int apply(int a, int b) const override { return a >> b; }
};

bool isIntegral(const std::string& string) {
    for (char c : string) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

Node* parseExpression(const std::string& expression, const std::map<std::string, Node*>& variables) {
    if (isIntegral(expression)) {
        return new ConstantNode(stoi(expression));
    }

    return new VariableNode(expression, variables);
}

Node* parseBinaryOperation(Node& left, std::vector<std::string>::iterator& tokens, const std::map<std::string, Node*>& variables) {
    std::string binaryOperator = *tokens;
    ++tokens;
    auto* right = parseExpression(*tokens, variables);

    if (binaryOperator == "AND") {
        return new AndNode(left, *right);
    } else if (binaryOperator == "OR") {
        return new OrNode(left, *right);
    } else if (binaryOperator == "LSHIFT") {
        return new LeftShiftNode(left, *right);
    } else if (binaryOperator == "RSHIFT") {
        return new RightShiftNode(left, *right);
    }

    assert(false);
    return nullptr;
}

void assignVariable(std::map<std::string, Node*>& variables, std::vector<std::string>::iterator tokens) {
    Node* node;
    if (*tokens == "NOT") {
        ++tokens;
        auto* operand = parseExpression(*tokens, variables);
        ++tokens;
        node = new NotNode(*operand);
    } else {
        auto* left = parseExpression(*tokens, variables);
        ++tokens;
        if (*tokens == "->") {
            node = left;
        } else {
            node = parseBinaryOperation(*left, tokens, variables);
            ++tokens;
        }
    }

    assert(*tokens == "->");
    ++tokens;
    variables[*tokens] = node;
}

int main() {
    std::string line;
    std::map<std::string, Node*> variables;
    while (std::getline(std::cin, line)) {
        std::stringstream stream(line);
        std::vector<std::string> tokens;
        std::string word;
        while (std::getline(stream, word, ' ')) {
            tokens.push_back(word);
        }

        assignVariable(variables, tokens.begin());
    }

    int a = variables["a"]->evaluate();
    std::cout << a << std::endl;
    for (auto pair : variables) {
        pair.second->reset();
    }

    variables["b"] = new ConstantNode(a);
    std::cout << variables["a"]->evaluate() << std::endl;
    return 0;
}

