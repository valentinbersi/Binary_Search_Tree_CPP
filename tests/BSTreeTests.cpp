#include "gmock/gmock.h"
#include "BSTree.hpp"

bool less(int a, int b) {
    return a < b;
}

bool equal(int a, int b) {
    return a == b;
}

class BSTreeTests : public ::testing::Test {
protected:
    BSTree<int, less, equal> tree{};
    std::vector<int> elements{};

    static void load(BSTree<int, less, equal> &tree) {
        tree.add(10);
        tree.add(7);
        tree.add(3);
        tree.add(13);
        tree.add(16);
        tree.add(11);
    }
};

// inorder travesar is used arbitrarily to rescue all elements.
TEST_F(BSTreeTests, add) {
    load(tree);
    tree.add(8);

    elements = tree.inorder();
    ASSERT_THAT(elements, testing::ElementsAre(3, 7, 8, 10, 11, 13, 16));
    ASSERT_EQ(elements.size(), 7);
}

TEST_F(BSTreeTests, AddHandlesDuplicates) {
    load(tree);
    EXPECT_THROW(tree.add(10), FrequencyException);
}

TEST_F(BSTreeTests, Find) {
    load(tree);
    EXPECT_TRUE(tree.find(10));
    EXPECT_FALSE(tree.find(8));
}

TEST_F(BSTreeTests, Inorder) {
    load(tree);
    elements = tree.inorder();
    ASSERT_THAT(elements, testing::ElementsAre(3, 7, 10, 11, 13, 16));
}

TEST_F(BSTreeTests, Preorder) {
    load(tree);
    elements = tree.preorder();
    ASSERT_THAT(elements, testing::ElementsAre(10, 7, 3, 13, 11, 16));
}

TEST_F(BSTreeTests, Postorder) {
    load(tree);
    elements = tree.postorder();
    ASSERT_THAT(elements, testing::ElementsAre(3, 7, 11, 16, 13, 10));
}

TEST_F(BSTreeTests, WidthOrder) {
    load(tree);
    elements = tree.width_order();
    ASSERT_THAT(elements, testing::ElementsAre(10, 7, 13, 3, 11, 16));
}

TEST_F(BSTreeTests, Size) {
    load(tree);
    ASSERT_EQ(tree.size(), 6);
}

TEST_F(BSTreeTests, Empty) {
    ASSERT_TRUE(tree.empty());
    load(tree);
    ASSERT_FALSE(tree.empty());
}

TEST_F(BSTreeTests, Remove) {
    load(tree);
    tree.remove(10);
    ASSERT_THAT(tree.inorder(), testing::ElementsAre(3, 7, 11, 13, 16));
    ASSERT_THAT(tree.preorder(), testing::ElementsAre(11, 7, 3, 13, 16));
    ASSERT_THAT(tree.postorder(), testing::ElementsAre(3, 7, 16, 13, 11));
    ASSERT_THAT(tree.width_order(), testing::ElementsAre(11, 7, 13, 3, 16));
    ASSERT_EQ(tree.size(), 5);

    tree.remove(13);
    ASSERT_THAT(tree.inorder(), testing::ElementsAre(3, 7, 11, 16));
    ASSERT_THAT(tree.preorder(), testing::ElementsAre(11, 7, 3, 16));
    ASSERT_THAT(tree.postorder(), testing::ElementsAre(3, 7, 16, 11));
    ASSERT_THAT(tree.width_order(), testing::ElementsAre(11, 7, 16, 3));
    ASSERT_EQ(tree.size(), 4);

    tree.remove(16);
    ASSERT_THAT(tree.inorder(), testing::ElementsAre(3, 7, 11));
    ASSERT_THAT(tree.preorder(), testing::ElementsAre(11, 7, 3));
    ASSERT_THAT(tree.postorder(), testing::ElementsAre(3, 7, 11));
    ASSERT_THAT(tree.width_order(), testing::ElementsAre(11, 7, 3));
    ASSERT_EQ(tree.size(), 3);

    tree.remove(1);
    ASSERT_THAT(tree.inorder(), testing::ElementsAre(3, 7, 11));
    ASSERT_THAT(tree.preorder(), testing::ElementsAre(11, 7, 3));
    ASSERT_THAT(tree.postorder(), testing::ElementsAre(3, 7, 11));
    ASSERT_THAT(tree.width_order(), testing::ElementsAre(11, 7, 3));
    ASSERT_EQ(tree.size(), 3);
}