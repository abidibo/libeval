#ifndef INCLUDE_NODE_H_
#define INCLUDE_NODE_H_

#include <memory>
#include <string>

class Node;
using NodePtr = std::shared_ptr<Node>;

class Node : public std::enable_shared_from_this<Node>
{
    public:
        Node(std::string symbol);
        Node(std::string symbol, NodePtr child);
        Node(std::string symbol, NodePtr leftChild, NodePtr rightChild);
        std::string getSymbol();
        NodePtr getParent();
        NodePtr getLeftChild();
        NodePtr getRightChild();
    protected:
        std::string symbol;
        NodePtr parent;
        NodePtr leftChild;
        NodePtr rightChild;
};

#endif /* INCLUDE_NODE_H_ */