// разворот односвязного списка

#include <iostream>
#include <vector>
#include <cassert>

#define BOOST_TEST_MODULE tools_for_brokers
#include <boost/test/included/unit_test.hpp>

struct SLLNode
{
    int data;
    SLLNode* next;
};

SLLNode* reverse_sll(SLLNode* sll_head) {
    SLLNode* cur = sll_head;
    SLLNode* new_dir_next = nullptr;
    while (cur != nullptr)
    {
        SLLNode* old_dir_next = cur->next;
        cur->next = new_dir_next;
        new_dir_next = cur;
        cur = old_dir_next;
    }
    return new_dir_next;
}

SLLNode* create_sll(std::vector<int>& nodes_data, std::vector<SLLNode>& nodes)
{
    assert(nodes_data.size() == nodes.size());
    
    for (size_t i = 0; i < nodes_data.size(); ++i)
    {
        nodes[i].data = nodes_data[i];
        nodes[i].next = i < nodes.size() - 1 ? &nodes[0] + i + 1 : nullptr;
    }
    return &nodes[0];
}

std::vector<int> extract_values(SLLNode* sll_head)
{
    std::vector<int> res;
    SLLNode* cur = sll_head;
    while (cur != nullptr)
    {
        res.push_back(cur->data);
        cur = cur->next;
    }
    return res;
}

void test_sll_case(std::vector<int>&& src, std::vector<int>&& expected)
{
    assert(src.size() == expected.size());
    std::vector<SLLNode> tc_nodes(src.size());

    SLLNode* sll = create_sll(src, tc_nodes);
    SLLNode* reversed = reverse_sll(sll);
    BOOST_TEST(extract_values(reversed) == expected);
}

BOOST_AUTO_TEST_CASE(test_reverse_sll) 
{
    test_sll_case({ 1, 2, 3, 4, 5 }, { 5, 4, 3, 2, 1 });
    test_sll_case({ 3, 4, 2, 5 }, { 5, 2, 4, 3 });
    test_sll_case({}, {});
}
