#pragma once
#include <cppunit/extensions/HelperMacros.h>
#include "RBT.hpp"

class RbtTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(RbtTest);

    CPPUNIT_TEST(InitTree);
    CPPUNIT_TEST(FillTree);
    CPPUNIT_TEST(Traversals);
    CPPUNIT_TEST(TreeHeight);
    CPPUNIT_TEST(BlackDepth);
    CPPUNIT_TEST(ClearTree);
    CPPUNIT_TEST(AddAndDelete);

    CPPUNIT_TEST_SUITE_END();

public:
    RbtTest();
    virtual ~RbtTest();
    void setUp();
    void tearDown();

private:
    RBT* tree;
    void InitTree();
    void FillTree();
    void Traversals();
    void TreeHeight();
    void BlackDepth();
    void ClearTree();
    void AddAndDelete();
};
