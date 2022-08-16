#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAX_SIZE 10
typedef struct QueryNode
{
    char *query;
    struct QueryNode *prev;
    struct QueryNode *next;
} QueryNode;

typedef struct CountNode
{
    int count;
    struct CountNode *prev;
    struct CountNode *next;
    QueryNode **querylist;
} CountNode;
int converter(char a)
{
    int i,initial=48;
    for(i=0;;i++)
    {
        if(a==initial){return i;}
        else{initial++;}
    }
}
int boolean_traversal(CountNode* head,int counter)
{   
    CountNode* local_ptr;
    for(local_ptr=head;local_ptr;)
    {
        if(local_ptr->count==counter){return 1;}
        else{local_ptr=local_ptr->next;}
    }
    return 0;
}
int string_sorting(char* not_added_query,char* added_query)
{
    char* mp1=not_added_query,*mp2=added_query;
    for(;(*mp1&&*mp2);)
    {
        if(*mp1<*mp2){return 1;}
        else if(*mp1>*mp2){return 0;}
        else{mp1++;mp2++;}
    }
    if(*mp1=='\0'){return 1;}
    else if(*mp2=='\0'){return 0;}
    return 1;
}
void add_QueryNode(CountNode* head,QueryNode* currNode,int counter)
{
    CountNode* local_ptr;
    QueryNode* mobile_qnp;
    for(local_ptr=head;local_ptr;)
    {
        if(local_ptr->count==counter)
        {
            
            mobile_qnp=(*(local_ptr->querylist));

            while(1)
            {
                if(string_sorting(currNode->query,mobile_qnp->query))
                {
                    if(mobile_qnp->prev)
                    {
                        currNode->prev=mobile_qnp->prev;
                        mobile_qnp->prev->next=currNode;
                        mobile_qnp->prev=currNode;
                        currNode->next=mobile_qnp;
                    }
                    else if(mobile_qnp->prev==NULL)
                    {
                        currNode->next=mobile_qnp;
                        currNode->prev=NULL;
                        mobile_qnp->prev=currNode;
                        (*(local_ptr->querylist))=currNode;
                    }
                    else if(mobile_qnp->next==NULL)
                    {
                        mobile_qnp->next=currNode;
                        currNode->prev=mobile_qnp;
                        currNode->next=NULL;
                    }
                    break;
                }
                else if(mobile_qnp->next)
                {
                    mobile_qnp=mobile_qnp->next;
                }
                else
                {
                    mobile_qnp->next=currNode;
                    currNode->prev=mobile_qnp;
                    currNode->next=NULL;
                    break;
                }
            }
            break;
        }
        else{local_ptr=local_ptr->next;}
    }
}
void add_QueryNode_to_null_querylist(CountNode* head,QueryNode* currNode,int counter)
{   
    CountNode* cnp;
    for(cnp=head;cnp;cnp=cnp->next)
    {
        if(cnp->count==counter)
        {
            cnp->querylist=malloc(sizeof(QueryNode*));
            *(cnp->querylist)=currNode;
        }
    }
}
CountNode* sort_countNodes(CountNode* head)
{
    int len,i;
    CountNode* past=NULL,*curr=head,*counter=head,*temporary=NULL;
    for(len=0;counter;len++,counter=counter->next);
    for(i=0;i<len;i++)
    {
        while(1)
        {
            past=curr;
            curr=curr->next;
            if(curr)
            {
                if(past->prev==NULL && (past->count > curr->count))
                {
                    past->next=curr->next;
                    past->prev=curr;
                    curr->next=curr->prev;
                    curr->next=past;
                    curr->prev=NULL;
                    head=curr;
                    temporary=past;
                    past=curr;
                    curr=temporary;
                }
                else if(past->prev && curr->next && (past->count > curr->count) )
                {
                    past->prev->next=curr;
                    curr->prev=past->prev;
                    past->next=curr->next;
                    curr->next->prev=past;
                    curr->next=past;
                    past->prev=curr;
                    temporary=past;
                    past=curr;
                    curr=temporary;
                }
                else if(curr->next==NULL && (past->count > curr->count))
                {
                    past->prev->next=curr;
                    curr->prev=past->prev;
                    curr->next=past;
                    past->prev=curr;
                    past->next=NULL;
                    temporary=past;
                    past=curr;
                    curr=temporary;
                }
            }
            else{past=NULL;curr=head;break;}
        }
    }
    return head;
}
int string_sameness(char* str1,char* str2)
{
    char* mp1=str1,*mp2=str2;
    for(;(*mp1 != '\0'&& *mp2 !='\0');mp1++,mp2++)
    {
        if(*mp1 != *mp2){return 0;}
        else{mp1++,mp2++;}
    }
    return 1;
}
int find_count_of_string_query(CountNode* head,char* insertion_string)
{
    CountNode* cnp=head;
    QueryNode* qnp;
    for(;cnp;cnp=cnp->next)
    {
        qnp=*(cnp->querylist);
        for(;qnp;qnp=qnp->next)
        {
            if(string_sameness(qnp->query,insertion_string)){return cnp->count;}
        }
    }
}
int bool_new_count_node_in_list(CountNode* head,int new_count_node)
{
    CountNode* cnp=head;
    for(;cnp;cnp=cnp->next)
    {
        if(cnp->count==new_count_node){return 1;}
    }
    return 0;
}
void delete_query_from_current_Countnode(CountNode* head,char* insertion_string,int curr_count_node)
{
    CountNode* cnp=head;
    QueryNode* qnp;
    for(;cnp;cnp=cnp->next)
    {
        if(cnp->count==curr_count_node)
        {
            qnp=*(cnp->querylist);
            for(;qnp;qnp=qnp->next)
            {
                if(string_sameness(qnp->query,insertion_string))
                {
                    if(qnp->prev==NULL && qnp->next)
                    {
                        qnp->next->prev=NULL;
                        *(cnp->querylist)=qnp->next;
                        qnp->next=NULL;
                    }
                    else if(qnp->prev && qnp ->next)
                    {
                        qnp->prev->next=qnp->next;
                        qnp->next->prev=qnp->prev;
                        qnp->next=NULL;
                        qnp->prev=NULL;
                    }
                    else if(qnp->next==NULL && qnp->prev)
                    {
                        qnp->prev->next=NULL;
                        qnp->prev=NULL;
                    }
                    else if((qnp->next==NULL && qnp->prev==NULL))
                    {
                        *(cnp->querylist)=NULL;                       
                    }
                    break;
                }
            }
        }
    }
}
CountNode* add_new_count_node_to_list(CountNode* head,int new_count_node)
{
    CountNode* cnp=head;

    for(;cnp;cnp=cnp->next)
    {
        if(new_count_node < cnp->count)
        {   
            if(cnp->prev== NULL)
            {
                cnp->prev=malloc(sizeof(CountNode*));
                cnp->prev->next=cnp;
                cnp->prev->prev=NULL;
                cnp->prev->count=new_count_node;
                head=cnp->prev;
            }
            else if(cnp->prev && cnp->next)
            {
                cnp->prev->next=malloc(sizeof(CountNode*));
                cnp->prev->next->prev=cnp->prev;
                cnp->prev->next->count=new_count_node;
                cnp->prev->next->next=cnp;
                cnp->prev=cnp->prev->next;
            }
            else if(cnp->prev && cnp-> next==NULL)
            {
                cnp->next=malloc(sizeof(CountNode*));
                cnp->next->prev=cnp;
                cnp->next->count=new_count_node;
                cnp->next->next=NULL;
            }
            break;
        }
        if((new_count_node > cnp->count)&&(cnp->next==NULL))
        {
            cnp->next=malloc(sizeof(CountNode*));
            cnp->next->prev=cnp;
            cnp->next->count=new_count_node;
            cnp->next->next=NULL;
            break;
        }

    }
    return head;
}
int bool_null_count_node_checker(CountNode* head,int count)
{
    CountNode* cnp=head;
    for(;cnp;cnp=cnp->next)
    {
        if(cnp->count==count)
        {
            if(*(cnp->querylist)==NULL){return 1;}
        }
    }
    return 0;
}
CountNode* delete_null_count_node(CountNode* head,int count)
{
    CountNode* cnp=head;
    for(;cnp;cnp=cnp->next)
    {
        if(cnp->count==count)
        {
            if(cnp->prev==NULL && cnp->next)
            {
                cnp->next->prev=NULL;
                head=cnp->next;
                cnp->next=NULL;
            }
            else if(cnp->prev && cnp->next)
            {
                cnp->prev->next=cnp->next;
                cnp->next->prev=cnp->prev;
                cnp->next=NULL;
                cnp->prev=NULL;
            }
            else if(cnp->prev && cnp->next==NULL)
            {
                cnp->prev->next=NULL;
                cnp->prev=NULL;
            }
            else if(cnp->prev==NULL && cnp->next==NULL)
            {
                head=NULL;
            }
        }
    }
    return head;
}
int find_index_of_discarted_query(CountNode* head,QueryNode** query_table)
{
    int index;
    char* discarted_str=(*(head->querylist))->query;
    for(index=0;;index++)
    {
        if(string_sameness(discarted_str,query_table[index]->query))
        {
            return index;
        }
    }
}
/* IMPORTANT COMMENT : INPUT ILK SATIR = 10 İÇİN 1 ALIYOR */
int main()
{
    QueryNode* query_table[MAX_SIZE],*print_pointer;
    CountNode* head,*curpos;
    int ch,read_line_boolean=1,read_line_count,index=-1,i,query_len_counter=1,temporary_number_for_count_nodes,counter_for_cn=1,enter_number=2,temporary_number_counter_for_insertion=1,insertion_number,filled_slot_counter,index_of_discarted_query,insertion_sameness_checker,index1,new_count_node;
    char* temporary_number_str,*instertion_temp_str=malloc(sizeof(char)),*insertion_strings;
    for(i=0;i<MAX_SIZE;i++)
    {
        query_table[i]=malloc(sizeof(QueryNode));
    }
    for(i=0;i<MAX_SIZE;i++)
    {
        query_table[i]->query=malloc(sizeof(char));
    }
    while((ch=getchar())!=EOF)
    {
        if(read_line_boolean)
        {
            read_line_count=converter(ch);
            filled_slot_counter=read_line_count;
            read_line_count+=1;
            read_line_boolean=0;
        }
        else
        {
            if(read_line_count >= 1)
            {
                if(ch>=97 && ch<=122)
                {
                    query_len_counter++;
                    query_table[index]->query=realloc(query_table[index]->query,query_len_counter*sizeof(char));
                    query_table[index]->query[query_len_counter-2]=ch;
                }
                else if(ch>=48 && ch<=57)
                {
                    if(counter_for_cn==1)
                    {
                        counter_for_cn++;
                        temporary_number_str=malloc(counter_for_cn*sizeof(char));
                        temporary_number_str[counter_for_cn-2]=ch;
                    }
                    else
                    {
                        counter_for_cn++;
                        temporary_number_str=realloc(temporary_number_str,counter_for_cn*sizeof(char));
                        temporary_number_str[counter_for_cn-2]=ch;
                    }

                }
                else if(ch==' ')
                {
                    query_table[index]->query[query_len_counter-1]='\0';
                    query_len_counter=1;
                }
                else if(ch=='\n')
                {   
                    if(index != -1)
                    {
                        temporary_number_str[counter_for_cn-1]='\0';
                        sscanf(temporary_number_str,"%d",&temporary_number_for_count_nodes);
                        temporary_number_str=NULL;
                        if(index==0)
                        {
                            head=malloc(sizeof(CountNode));
                            head->count=temporary_number_for_count_nodes;
                            head->prev=NULL;
                            head->querylist=malloc(sizeof(QueryNode*));
                            *(head->querylist)=query_table[index];
                            (*(head->querylist))->prev=NULL;
                            (*(head->querylist))->next=NULL;
                            curpos=head;
                            counter_for_cn=1;
                        }
                        else if(index>0 && read_line_count>1)
                        {
                            if(boolean_traversal(head,temporary_number_for_count_nodes))
                            {
                                add_QueryNode(head,query_table[index],temporary_number_for_count_nodes);
                            }
                            else
                            {
                                curpos->next=malloc(sizeof(CountNode));
                                curpos->next->count=temporary_number_for_count_nodes;
                                curpos->next->prev=curpos;
                                curpos=curpos->next;
                                curpos->querylist=malloc(sizeof(QueryNode*));
                                *(curpos->querylist)=query_table[index];
                                (*(curpos->querylist))->prev=NULL;
                                (*(curpos->querylist))->next=NULL;
                            }
                            counter_for_cn=1;
                        }
                        else if(index>0 && read_line_count==1)
                        {
                            if(boolean_traversal(head,temporary_number_for_count_nodes))
                            {
                                add_QueryNode(head,query_table[index],temporary_number_for_count_nodes);
                            }
                            else
                            {
                                curpos->next=malloc(sizeof(CountNode));
                                curpos->next->count=temporary_number_for_count_nodes;
                                curpos->next->prev=curpos;
                                curpos=curpos->next;
                                curpos->querylist=malloc(sizeof(QueryNode*));
                                *(curpos->querylist)=query_table[index];
                                (*(curpos->querylist))->prev=NULL;
                                (*(curpos->querylist))->next=NULL;
                            }
                            counter_for_cn=1;
                            curpos->next=NULL;
                        }
                    }
                    index+=1;read_line_count-=1;

                    if(read_line_count==0){continue;}
                }
            }
            else 
            {
                head=sort_countNodes(head);
                if(enter_number>1)
                {
                    temporary_number_counter_for_insertion++;
                    instertion_temp_str=realloc(instertion_temp_str,temporary_number_counter_for_insertion*sizeof(char));
                    instertion_temp_str[temporary_number_counter_for_insertion-2]=ch;
                }
                if(ch=='\n')
                {
                    enter_number--;
                    if(enter_number==1)
                    {
                        instertion_temp_str[temporary_number_counter_for_insertion-1]='\0';
                        sscanf(instertion_temp_str,"%d",&insertion_number);
                        temporary_number_counter_for_insertion=1;
                    }

                    else if(enter_number==0)
                    {
                        insertion_strings[temporary_number_counter_for_insertion-1]='\0';
                        goto label;
                        
                    }
                }

                else if(ch>=97 && ch<=122)
                {
                    temporary_number_counter_for_insertion++;
                    if(temporary_number_counter_for_insertion==2)
                    {
                        insertion_strings=malloc(sizeof(char)*temporary_number_counter_for_insertion);
                    }
                    else if(temporary_number_counter_for_insertion>2)
                    {
                        insertion_strings=realloc(insertion_strings,temporary_number_counter_for_insertion*sizeof(char));
                    }
                        insertion_strings[temporary_number_counter_for_insertion-2]=ch; 

                }

                else if(ch ==' ')
                {
                    insertion_number--;
                    insertion_strings[temporary_number_counter_for_insertion-1]='\0';
                    temporary_number_counter_for_insertion=1;
                    /* INSERTION İŞLEMLERİ BURADA */
                    label:
                        insertion_sameness_checker=0;
                        for(index1=0;index1<filled_slot_counter;index1++)
                        {
                            if(string_sameness(insertion_strings,query_table[index1]->query)){insertion_sameness_checker=1;break;}
                        }

                        if(insertion_sameness_checker)
                        {
                            new_count_node=find_count_of_string_query(head,insertion_strings)+1;
                            if(bool_new_count_node_in_list(head,new_count_node))
                            {
                                delete_query_from_current_Countnode(head,insertion_strings,new_count_node-1);

                                if(bool_null_count_node_checker(head,new_count_node-1))
                                {
                                    head=delete_null_count_node(head,new_count_node-1);
                                }
                                add_QueryNode(head,query_table[index1],new_count_node);
                            }
                            else
                            {
                                head=add_new_count_node_to_list(head,new_count_node);
                                head=sort_countNodes(head);
                                delete_query_from_current_Countnode(head,insertion_strings,new_count_node-1);
                                if(bool_null_count_node_checker(head,new_count_node-1))
                                {
                                    head=delete_null_count_node(head,new_count_node-1);
                                }
                                add_QueryNode_to_null_querylist(head,query_table[index1],new_count_node);
                            }
                        }
                        else
                        {
                            if(filled_slot_counter != MAX_SIZE)
                            {
                                query_table[filled_slot_counter]->query=insertion_strings;
                                filled_slot_counter++;
                                if(bool_new_count_node_in_list(head,1))
                                {
                                    add_QueryNode(head,query_table[filled_slot_counter-1],1);
                                }
                                else
                                {
                                    head=add_new_count_node_to_list(head,1);
                                    add_QueryNode_to_null_querylist(head,query_table[filled_slot_counter-1],1);
                                }
                            }
                            else
                            {

                                index_of_discarted_query=find_index_of_discarted_query(head,query_table);
                                query_table[index_of_discarted_query]->query=insertion_strings;
                                if((query_table[index_of_discarted_query]->next) || (query_table[index_of_discarted_query]->prev))
                                {
                                    
                                    delete_query_from_current_Countnode(head,query_table[index_of_discarted_query]->query,head->count);
                                    add_QueryNode(head,query_table[index_of_discarted_query],head->count);
                                }
                                
                            }
                        }
                        if(enter_number==0){break;}
                }
            }
        }
    }

    for(curpos=head;curpos;)
    {
        printf("%d ",curpos->count);
        for(print_pointer=*(curpos->querylist);print_pointer;)
        {
            if(print_pointer->next){printf("%s ",print_pointer->query);}
            else{printf("%s\n",print_pointer->query);}
            print_pointer=print_pointer->next;
        }
        curpos=curpos->next;
    }
    return 0;
}

