struct node;

struct node
{
    struct node* m_Lchild;
    struct node* m_Rchild;
	inte m_data;
	int m_index;
};

int last_left;    //Last Left printed
int last_right;    //Last Right printed
void print_top_view(struct node* tree_head)
{
    if (tree_head == NULL) return;
	 
	tree_head->m_index = 0;
	print_node(tree_head);
	last_left = 0;
	last_right = 0;

	tree_traverse(tree_head);
	
	printf("\n");
}

void tree_traverse(struct node* pNode)
{	
	if (pNode->m_Lchild != NULL)    //Left Top View
    {
    	pNode->m_Lchild->m_index = pNode->m_index + 1;
		
		if (last_left < pNode->m_Lchild->m_index)
        {
            print_node(pNode->m_Lchild);
		    last_left = pNode->m_Lchild->m_index;
	    }
		
		tree_traverse(pNode->m_Lchild);
	}
	
	if (pNode->m_Rchild != NULL)    //Right Top View
    {
        pNode->m_Rchild->m_index = pNode->m_index - 1;
		
	    if (pNode->m_Rchild->m_index < last_right)
        {
            print_node(pNode->m_Rchild);
		    last_right = pNode->m_Rchild->m_index;
	    }
	
	    tree_traverse(pNode->m_Rchild);
	}
}

void print_node(struct node* pNode)
{
    //pNode NULL check is verified before function call
	
    printf("%d ", pNode->m_data);
}
