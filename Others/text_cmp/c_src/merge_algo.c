void insert_node(merge_node** head, int l, int r){
    // compare and insert 
    // if the head is null, initialize the head
    merge_node *aux;
    if(*head == NULL){
        *head = malloc(sizeof(merge_node));
        *head -> l = l;
        *head -> r = r;
        *head -> next = NULL;
    }
    // conpare, assume to insert left value
    aux = *head;
    while(aux && aux -> r < l){
        //skip current
        aux = aux -> next;
    }
}
void release_list(merge_node* head){
    merge_node *tmp;
    while(head){
        tmp=head;
        head = head->next;
        free(tmp);
    }
}
int check_out(merge_node* head){
    int rtn = 0;
    while(head){
        rtn += head->r - head->l;
        head = head->next;
    }
}
