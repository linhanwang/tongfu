#pragma once

#include <iostream>

#include "tongfu/container/linked_binary_tree.h"

namespace tongfu {

template <typename E, typename R>
class EulerTour {
   protected:
    struct Result {
        R leftResult;
        R rightResult;
        R finalResult;
    };
    using BinaryTree = LinkedBinaryTree<E>;
    using Position = typename BinaryTree::Position;

   protected:
    const BinaryTree* tree;

   public:
    void initialize(const BinaryTree& T) { tree = &T; }

   protected:
    int eulerTour(const Position& p) const;

    virtual void visitExternal(const Position& p, Result& r) const {}
    virtual void visitLeft(const Position& p, Result& r) const {}
    virtual void visitBelow(const Position& p, Result& r) const {}
    virtual void visitRight(const Position& p, Result& r) const {}

    Result initResult() const { return Result(); }
    int result(const Result& r) const { return r.finalResult; }
};

template <typename E, typename R>
int EulerTour<E, R>::eulerTour(const Position& p) const {
    Result r = initResult();
    if (p.isExternal()) {
        visitExternal(p, r);
    } else {
        visitLeft(p, r);
        r.leftResult = eulerTour(p.left());
        visitBelow(p, r);
        r.rightResult = eulerTour(p.right());
        visitRight(p, r);
    }
    return result(r);
}

template <typename E, typename R>
class EvaluateExpressionTour : public EulerTour<E, R> {
   protected:
    using BinaryTree = typename EulerTour<E, R>::BinaryTree;
    using Position = typename EulerTour<E, R>::Position;
    using Result = typename EulerTour<E, R>::Result;

   public:
    void execute(const BinaryTree& T) {
        initialize(T);
        std::cout << "The value is: " << eulerTour(T.root()) << std::endl;
    }

   protected:
    virtual void visitExternal(const Position& p, Result& r) const {
        r.finalResult = (*p).value();
    }

    virtual void visitRight(const Position& p, Result& r) const {
        r.finalResult = (*p).operation(r.leftResult, r.rightResult);
    }
};

template <typename E, typename R>
class PrintExpressionTour : public EulerTour<E, R> {
   protected:
    using BinaryTree = typename EulerTour<E, R>::BinaryTree;
    using Position = typename EulerTour<E, R>::Position;
    using Result = typename EulerTour<E, R>::Result;

   public:
    void execute(const BinaryTree& T) {
        initialize(T);
        std::cout << "Expression: ";
        eulerTour(T.root());
        std::cout << std::endl;
    }

   protected:
    virtual void visitExternal(const Position& p, Result& r) const {
        (*p).print();
    }

    virtual void visitLeft(const Position& p, Result& r) const {
        std::cout << "(";
    }

    virtual void visitBelow(const Position& p, Result& r) const {
        (*p).print();
    }

    virtual void visitRight(const Position& p, Result& r) const {
        std::cout << ")";
    }
};

}  // namespace tongfu
