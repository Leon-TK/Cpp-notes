#pragma once
#include "include.h"
#include <vector>

namespace CompositePattern {

    class Node {
        std::vector<Node> m_parent;
        std::vector<Node> m_children;
    };
    void ClientClass() {};
    void Run() {};
}