int main(void)
{
    struct node* list = NULL; 
    int choice;
    int data;  
    struct node* new_node; 

    while(TRUE)
    {
        printf("1:Insert\n2:Show\n3:Destroy\n"); 
        scanf("%d", &choice); 

        switch(choice)
        {
            case 1: 
                printf("Enter data:"); 
                scanf("%d", &data); 
                new_node = malloc(struct node); 
                new_node->data = data; 
                list = insert(list, new_node); 
                break; 

            case 2: 

                break; 

            case 3: 

                break; 
        }

    }    
    

}

struct node* insert(struct node* list, struct node* new_node)
{
    struct node* tmp; 

    if(list == NULL)
        return new_node; 

    tmp = list; 
    while(tmp->next != NULL)
        tmp = tmp->next; 

    tmp->next = new_node; 
    return (list); 
}