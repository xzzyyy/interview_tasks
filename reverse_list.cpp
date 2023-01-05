#include <iostream>


// разворот односвязного списка

struct Node
{
    int val;
    Node* next;
};

Node* reverse(Node* head)
{
    if (!head) 
		return nullptr;
	
	Node* prev = nullptr;
    Node* curr = head;
    Node* next;
    
	while (curr)
    {
        next = curr->next;
        curr->next = prev;
		
        prev = curr;
        curr = next;
    }
	
    return prev;
}

// prev = null; curr = 1; next = ?;
// prev = 1; curr = 2; next = 2;
// prev = 2; curr = 5; next = 5;
// prev = 5; curr = 10; next = 10;
// prev = 10; curr = 3; next = 3;


void print_fwdlist(Node* head)
{
    if (!head)
        return;
    
    do
    {
        std::cout << head->val;
        
        head = head->next;
        if (head)
            std::cout << "->";
    }
    while (head);
    
    std::cout << std::endl;
}

int main()
{
    Node fwd_list[5] = { 
        { 1, &fwd_list[1] }, 
        { 2, &fwd_list[2] }, 
        { 5, &fwd_list[3] }, 
        { 10, &fwd_list[4] }, 
        { 3, nullptr }
    };
    
    print_fwdlist(fwd_list);
    print_fwdlist(reverse(fwd_list));
}






// --- Less pretty solution ---

#ifdef DEBUG
std::string to_string(Node* n)
{
	return n ? std::to_string(n->val) : "null";
}
#endif

Node* reverse2(Node* head)
{
    if (!head)
        return nullptr;
        
    Node* prev = nullptr;
    Node* curr = head;
    Node* next = head->next;
    
    while (next)
    {
        curr->next = prev;
        
        prev = curr;
        curr = next;
        next = next->next;
        
#ifdef DEBUG
        std::cout << "prev " << to_string(prev) 
        		  << " curr " << to_string(curr) 
        		  << " next " << to_string(next) 
        << std::endl;
#endif
    }
    curr->next = prev;
    
    return curr;
}

// --- Less pretty solution ---
