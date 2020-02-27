#ifndef INCLUDE_NODE_H_
#define INCLUDE_NODE_H_

#include <memory>
#include <string>

class Node;
using NodePtr = std::shared_ptr<Node>;

class Node : public std::enable_shared_from_this<Node>
{
public:
    Node(const std::string& symbol, int depth)
    {
        this->symbol = symbol;
        this->depth = depth;
    }
    Node(const std::string& symbol, NodePtr child, int depth)
    {
        this->symbol = symbol;
        this->leftChild = child;
        this->depth = depth;
    }
    Node(const std::string& symbol, NodePtr leftChild, NodePtr rightChild, int depth)
    {
        this->symbol = symbol;
        this->leftChild = leftChild;
        this->rightChild = rightChild;
        this->depth = depth;
    }
    virtual ~Node() = default;
    std::string getSymbol()
    {
        return symbol;
    }
    int getDepth()
    {
        return depth;
    }
    NodePtr getParent()
    {
        return parent;
    }
    NodePtr getLeftChild()
    {
        return leftChild;
    }
    NodePtr getRightChild()
    {
        return rightChild;
    }
    double getValue()
    {
        return value;
    }
    virtual double calc() = 0;
protected:
    std::string symbol;
    int depth;
    NodePtr parent;
    NodePtr leftChild;
    NodePtr rightChild;
    double value;
};

#endif /* INCLUDE_NODE_H_ */