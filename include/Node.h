#ifndef INCLUDE_NODE_H_
#define INCLUDE_NODE_H_

#include <memory>
#include <string>

class Node;
using NodePtr = std::shared_ptr<Node>;

/**
 * Node base class 
 * 
 * This class represents a node in the evaluation tree.
 * Derived classes are used to specialized different kind of nodes:
 * - operator nodes
 * - operand nodes (leaves)
 */
class Node : public std::enable_shared_from_this<Node>
{
public:
    /**
     * Operand node constructor
     * @param symbol: the node token
     * @param depth: the node depth in the tree
     */ 
    Node(const std::string& symbol, int depth)
    {
        this->symbol = symbol;
        this->depth = depth;
    }
    /**
     * Unary operator node constructor
     * @param symbol: the node token
     * @param child: the node child
     * @param depth: the node depth in the tree
     */
    Node(const std::string& symbol, NodePtr child, int depth)
    {
        this->symbol = symbol;
        this->leftChild = child;
        this->depth = depth;
    }
    /*
     * Binary operator node constructor
     * @param symbol: the node token
     * @param leftChild: the node left child
     * @param rightChild: the node right child
     * @param depth: the node depth in the tree
     */
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
    /**
     * Node value getter
     * 
     * A node stores its current value in order to cache it
     * such value will be calculated again only if
     * a child changes
     * @return node current value
     */
    double getValue()
    {
        return value;
    }
    /**
     * Node value calculator
     * 
     * Every derived class should implement this,
     * and calculate the current node value
     */
    virtual double calc() = 0;
protected:
    std::string symbol;
    int depth;
    NodePtr parent;
    NodePtr leftChild;
    NodePtr rightChild;
    double value = NAN;
};

#endif /* INCLUDE_NODE_H_ */