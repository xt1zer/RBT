#include "RbtTest.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(RbtTest);

RbtTest::RbtTest() {
    tree = new RBT;
}

RbtTest::~RbtTest() {
    delete tree;
}

void RbtTest::setUp() { }

void RbtTest::tearDown() { }

void RbtTest::InitTree() {
    CPPUNIT_ASSERT_MESSAGE("Tree isn't initialised correctly", tree->isEmpty());
}

void RbtTest::FillTree() {
    tree->add(10);
    tree->add(7);
    tree->add(21);
    CPPUNIT_ASSERT(tree->find(21));
    tree->add(5);
    tree->add(6);
    tree->add(9);
    tree->add(2);
    tree->add(2);
    CPPUNIT_ASSERT(!tree->find(1));
}

void RbtTest::Traversals() {
    CPPUNIT_ASSERT_EQUAL(std::string("10 6 5 2 7 9 21 "), tree->preOrderTraversal());
    CPPUNIT_ASSERT_EQUAL(std::string("2 5 6 7 9 10 21 "), tree->inOrderTraversal());
    CPPUNIT_ASSERT_EQUAL(std::string("2 5 9 7 6 21 10 "), tree->postOrderTraversal());
    CPPUNIT_ASSERT_EQUAL(std::string("10 6 21 5 7 2 9 "), tree->breadthTraversal());
}

void RbtTest::TreeHeight() {
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Wrong height value", 3, tree->getHeight());
}

void RbtTest::BlackDepth() {
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Wrong black depth value", 3, tree->getBlackDepth());
}

void RbtTest::ClearTree() {
    tree->clear();
    CPPUNIT_ASSERT_MESSAGE("Tree wasn't cleared correctly", tree->isEmpty());
}

void RbtTest::AddAndDelete() {
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Expected value not added", 5,
            tree->add(5)->key);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Expected value not found", 0, tree->remove(5));
    CPPUNIT_ASSERT_MESSAGE("Found unexpected value", tree->remove(1) == 1);
}
