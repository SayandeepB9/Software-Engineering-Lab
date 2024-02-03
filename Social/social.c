/*
    This is the most important file in the code. It implements all the structures
    for individuals, businesses, organisations and group. It contains all the
    functionalities for the codebase defined in the assignment. The social
    network derives its general structure from this file. The structure and all
    the functions are described in the social.h file.
*/


#include "social.h"


struct date* new_date()
{
    struct date* date = (struct date*)malloc(sizeof(struct date));
    int dd, mm , yyyy;
    printf("Enter the date, month and year respectively : ");
    scanf("%d%d%d", &dd, &mm, &yyyy);
    date->dd = dd;
    date->mm = mm;
    date->yyyy = yyyy;
    return date;
}

struct date* current_date()
{
    struct date* date = (struct date*)malloc(sizeof(struct date));
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    date->dd = tm.tm_mday;
    date->mm = tm.tm_mon + 1;
    date->yyyy = tm.tm_year + 1900;
    return date;
}



struct Location2D* new_Location2D()
{
    struct Location2D* loc = (struct Location2D*)malloc(sizeof(struct Location2D));
    int x,y;
    printf("Enter the x and y coordinates respectively : ");
    scanf("%d%d", &x, &y);
    loc->x = x;
    loc->y = y;
    return loc;
}



char* new_str()
{
    // Size is taken from the user
    printf("Enter the length of the string : ");
    int n;
    scanf("%d", &n);
    char* s;
    s=(char*)malloc((n+1)*sizeof(char));
    getchar();
    printf("Enter the string : ");
    scanf("%[^\n]", s);
    s[n]='\0';
    return s;
}

char* cpy_str(char str[])
{
    char* s;
    s=(char*)malloc(strlen(str)*sizeof(char));
    strcpy(str,s);
    return s;
}

struct string_link* create_str_link(char str[])
{
    struct string_link* str_link = (struct string_link*)malloc(sizeof(struct string_link));
    str_link->str = str;
    str_link->next = NULL;
    return str_link;
}

struct string_link* add_str_link_to_head(struct string_link* head, char str[])
{
    struct string_link* str_link = create_str_link(str);
    str_link->next = head;
    return str_link;
}

struct string_link* delete_str_link(char str[], struct string_link* head)
{
    struct string_link* temp = head;
    struct string_link* prev = NULL;
    while(temp!=NULL)
    {
        if(strcmp(temp->str,str)==0)
        {
            if(prev==NULL)
            {
                head = temp->next;
                free(temp);
                printf("String deleted\n");
                return head;
            }
            else
            {
                prev->next = temp->next;
                free(temp);
                printf("String deleted\n");
                return head;
            }
        }
        prev = temp;
        temp = temp->next;
    }
    printf("String not found\n");
    return head;
}

struct string_link* delete_post(int n, struct string_link* head)
{
    struct string_link* temp = head;
    struct string_link* prev = NULL;
    int i=1;
    while(temp!=NULL)
    {
        if(i==n)
        {
            if(prev==NULL)
            {
                head = temp->next;
                free(temp);
                printf("String deleted\n");
                return head;
            }
            else
            {
                prev->next = temp->next;
                free(temp);
                printf("String deleted\n");
                return head;
            }
        }
        prev = temp;
        temp = temp->next;
        i++;
    }
    printf("String not found\n");
    return head;
}

char* find_post(int n, struct string_link* head)
{
    struct string_link* temp = head;
    int i=1;
    while(temp!=NULL)
    {
        if(i==n)
        {
            return temp->str;
        }
        temp = temp->next;
        i++;
    }
    return NULL;
}

struct string_link* find_str_link(char str[], struct string_link* head)
{
    struct string_link* temp = head;
    struct string_link* new_head = NULL;
    while(temp!=NULL)
    {
        if(strstr(temp->str,str)!=NULL)
        {
            new_head = add_str_link_to_head(new_head, temp->str);
        }
        temp = temp->next;
    }
    return new_head;
}

void print_str_link(struct string_link* head)
{
    struct string_link* temp = head;
    int count = 1;
    while(temp!=NULL)
    {
        printf("%d. %s\n", count, temp->str);
        temp = temp->next;
        count++;
    }
}

void test_str_link()
{
    struct string_link* head = NULL;
    int choice;
    char* str;
    while(1)
    {
        printf("1. Add string to head\n");
        printf("2. Delete string\n");
        printf("3. Print string link\n");
        printf("4. Delete post\n");
        printf("5. Find post\n");
        printf("6. Exit\n");
        printf("Enter your choice : ");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
                str = new_str();
                head = add_str_link_to_head(head, str);
                break;
            case 2:
                str = new_str();
                head = delete_str_link(str, head);
                break;
            case 3:
                print_str_link(head);
                break;
            case 4:
                printf("Enter the post number : ");
                int n;
                scanf("%d", &n);
                head = delete_post(n, head);
                break;
            case 5:
                printf("Enter the post number : ");
                int m;
                scanf("%d", &m);
                str = find_post(m, head);
                if(str!=NULL)
                {
                    printf("%s\n", str);
                }
                else
                {
                    printf("Post not found\n");
                }
                break;
            case 6:
                return;
            default:
                printf("Invalid choice\n");
        }
    }
}



struct node *new_node(int u_id)
{
    struct node *node = (struct node *)malloc(sizeof(struct node));
    node->unique_id = u_id;
    printf("Your unique id is %d\n", u_id);
    node->creation_date = current_date();
    printf("Creation date : %d/%d/%d\n", node->creation_date->dd, node->creation_date->mm, node->creation_date->yyyy);
    printf("Enter the name : \n");
    node->name = new_str();
    node->contents = NULL;
    return node;
}



struct individual *new_individual(int u_id)
{
    struct individual *ind = (struct individual *)malloc(sizeof(struct individual));
    ind->ind = new_node(u_id);
    printf("Enter the birth date : \n");
    ind->b_day = new_date();
    ind->owner = NULL;
    ind->customer = NULL;
    ind->org_link = NULL;
    ind->grp_link = NULL;
    return ind;
}

struct indi_link *new_indi_link(struct individual *indi)
{
    struct indi_link *indi_link = (struct indi_link *)malloc(sizeof(struct indi_link));
    indi_link->indi = indi;
    indi_link->next = NULL;
    return indi_link;
}

struct indi_link *add_indi_link_to_head(struct indi_link *head, struct individual *indi)
{
    struct indi_link *indi_link = new_indi_link(indi);
    if (head == NULL)
        return indi_link;
    indi_link->next = head;
    return indi_link;
}

struct indi_link *delete_indi_link(struct individual *indi, struct indi_link *head)
{
    struct indi_link *temp = head;
    struct indi_link *prev = NULL;
    while (temp != NULL)
    {
        if (temp->indi == indi)
        {
            if (prev == NULL)
            {
                head = temp->next;
                free(temp);
                printf("Individual link deleted\n");
                return head;
            }
            else
            {
                prev->next = temp->next;
                free(temp);
                printf("Individual link deleted\n");
                return head;
            }
        }
        prev = temp;
        temp = temp->next;
    }
    printf("No individual link with the given individual exists\n");
    return head;
}

struct individual *search_individual_by_unique_id(int u_id, struct indi_link *main_head)
{
    struct indi_link *temp = main_head;
    while (temp != NULL)
    {
        if (temp->indi->ind->unique_id == u_id)
        {
            printf("Individual found\n");
            return temp->indi;
        }
        temp = temp->next;
    }
    printf("No individual with the given unique id exists\n");
    return NULL;
}

struct individual *search_individual_by_name(char name[], struct indi_link *main_head)
{
    struct indi_link *temp = main_head;
    while (temp != NULL)
    {
        if (strcmp(temp->indi->ind->name, name) == 0)
        {
            printf("Individual found\n");
            return temp->indi;
        }
        temp = temp->next;
    }
    printf("No individual with the given name exists\n");
    return NULL;
}

struct individual *search_individual_by_birth_date(struct date *b_day, struct indi_link *main_head)
{
    struct indi_link *temp = main_head;
    while (temp != NULL)
    {
        if (temp->indi->b_day->dd == b_day->dd && temp->indi->b_day->mm == b_day->mm && temp->indi->b_day->yyyy == b_day->yyyy)
        {
            printf("Individual found\n");
            return temp->indi;
        }
        temp = temp->next;
    }
    printf("No individual with the given birth date exists\n");
    return NULL;
}

struct individual *search_individual(struct indi_link *main_head)
{
    int choice;
    printf("1. Unique id\n2. Name\n3. Birthday\nEnter your choice : ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
    {
        int u_id;
        printf("Enter the unique id : ");
        scanf("%d", &u_id);
        return search_individual_by_unique_id(u_id, main_head);
    }
    case 2:
    {
        char name[100];
        printf("Enter the name : ");
        scanf("%s", name);
        return search_individual_by_name(name, main_head);
    }
    case 3:
    {
        printf("Enter the birth date : \n");
        struct date *b_day = new_date();
        return search_individual_by_birth_date(b_day, main_head);
    }
    default:
    {
        printf("Invalid choice\n");
        return NULL;
    }
    }
}

int search_individual_pointer(struct indi_link *main_head, struct individual *indi)
{
    struct indi_link *temp = main_head;
    while (temp != NULL)
    {
        if (temp->indi == indi)
        {
            // printf("Individual found\n");
            return 1;
        }
        temp = temp->next;
    }
    // printf("Individual does not exist\n");
    return 0;
}

struct indi_link *delete_individual(struct indi_link *main_head)
{
    printf("Delete individual by :\n");
    struct individual *indi = search_individual(main_head);
    if (indi == NULL)
    {
        return NULL;
    }

    // TODO: Delete individual from all the groups, organisations and businesses
    struct group_link *grp_link = indi->grp_link;
    while(grp_link != NULL)
    {
        grp_link->grp->indi_link = delete_indi_link(indi, grp_link->grp->indi_link);
        grp_link = grp_link->next;
    }
    struct org_link *org_link = indi->org_link;
    while(org_link != NULL)
    {
        org_link->org->indi_link = delete_indi_link(indi, org_link->org->indi_link);
        org_link = org_link->next;
    }
    struct busi_link *owner = indi->owner;
    while(owner != NULL)
    {
        owner->busi->owners = delete_indi_link(indi, owner->busi->owners);
        owner = owner->next;
    }
    struct busi_link *customer = indi->customer;
    while(customer != NULL)
    {
        customer->busi->customers = delete_indi_link(indi, customer->busi->customers);
        customer = customer->next;
    }

    main_head = delete_indi_link(indi, main_head);
    free(indi);
    return main_head;
}

void print_indi_link(struct indi_link *head, struct individual *indi)
{
    struct indi_link *temp = head;
    while (temp != NULL)
    {
        if(temp->indi != indi)
        {
            printf("Name : %s\n", temp->indi->ind->name);
            printf("Unique ID :  %d\n", temp->indi->ind->unique_id);
            printf("Birthday : %d/%d/%d\n", temp->indi->b_day->dd, temp->indi->b_day->mm, temp->indi->b_day->yyyy);
            printf("Creation date : %d/%d/%d\n", temp->indi->ind->creation_date->dd, temp->indi->ind->creation_date->mm, temp->indi->ind->creation_date->yyyy);
            printf("Contents : \n");
            print_str_link(temp->indi->ind->contents);
            temp = temp->next;
        }
    }
}



struct organisation *new_organisation(int u_id)
{
    struct organisation *org = (struct organisation *)malloc(sizeof(struct organisation));
    org->org = new_node(u_id);
    printf("Enter the location : \n");
    org->loc = new_Location2D();
    org->indi_link = NULL;
    return org;
}

struct org_link *new_org_link(struct organisation *org)
{
    struct org_link *org_link = (struct org_link *)malloc(sizeof(struct org_link));
    org_link->org = org;
    org_link->next = NULL;
    return org_link;
}

struct org_link *add_org_link_to_head(struct org_link *head, struct organisation *org)
{
    struct org_link *org_link = new_org_link(org);
    if (head == NULL)
        return org_link;
    org_link->next = head;
    return org_link;
}

struct org_link *delete_org_link(struct organisation *org, struct org_link *head)
{
    struct org_link *temp = head;
    struct org_link *prev = NULL;
    while (temp != NULL)
    {
        if (temp->org == org)
        {
            if (prev == NULL)
            {
                head = temp->next;
                free(temp);
                printf("Organisation link deleted\n");
                return head;
            }
            else
            {
                prev->next = temp->next;
                free(temp);
                printf("Organisation link deleted\n");
                return head;
            }
        }
        prev = temp;
        temp = temp->next;
    }
    printf("No organisation link with the given organisation exists\n");
    return head;
}

struct organisation *search_organisation_by_unique_id(int u_id, struct org_link *main_head)
{
    struct org_link *temp = main_head;
    while (temp != NULL)
    {
        if (temp->org->org->unique_id == u_id)
        {
            printf("Organisation found\n");
            return temp->org;
        }
        temp = temp->next;
    }
    printf("No organisation with the given unique id exists\n");
    return NULL;
}

struct organisation *search_organisation_by_name(char name[], struct org_link *main_head)
{
    struct org_link *temp = main_head;
    while (temp != NULL)
    {
        if (strcmp(temp->org->org->name, name) == 0)
        {
            printf("Organisation found\n");
            return temp->org;
        }
        temp = temp->next;
    }
    printf("No organisation with the given name exists\n");
    return NULL;
}

struct organisation *search_organisation(struct org_link *main_head)
{
    int choice;
    printf("1. Unique id\n2. Name\nEnter your choice : ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
    {
        int u_id;
        printf("Enter the unique id : ");
        scanf("%d", &u_id);
        return search_organisation_by_unique_id(u_id, main_head);
    }
    case 2:
    {
        char name[100];
        printf("Enter the name : ");
        scanf("%s", name);
        return search_organisation_by_name(name, main_head);
    }
    default:
    {
        printf("Invalid choice\n");
        return NULL;
    }
    }
}

int search_organisation_pointer(struct org_link *main_head, struct organisation *org)
{
    struct org_link *temp = main_head;
    while (temp != NULL)
    {
        if (temp->org == org)
        {
            // printf("Organisation found\n");
            return 1;
        }
        temp = temp->next;
    }
    // printf("Organisation does not exist\n");
    return 0;
}

struct org_link *delete_organisation(struct org_link *main_head)
{
    printf("Delete organisation by :\n");
    struct organisation *org = search_organisation(main_head);
    if (org == NULL)
    {
        return NULL;
    }

    // TODO: Delete organisation from all the groups and businesses
    struct indi_link *indi_link = org->indi_link;
    while(indi_link != NULL)
    {
        indi_link->indi->org_link = delete_org_link(org, indi_link->indi->org_link);
        indi_link = indi_link->next;
    }

    main_head = delete_org_link(org, main_head);
    free(org);
    return main_head;
}

void print_org_link(struct org_link *head, struct organisation *org)
{
    struct org_link *temp = head;
    while (temp != NULL)
    {
        if(temp->org != org)
        {
            printf("Name : %s\n", temp->org->org->name);
            printf("Unique ID :  %d\n", temp->org->org->unique_id);
            printf("Location : %d %d\n", temp->org->loc->x, temp->org->loc->y);
            printf("Creation date : %d/%d/%d\n", temp->org->org->creation_date->dd, temp->org->org->creation_date->mm, temp->org->org->creation_date->yyyy);
            printf("Contents : \n");
            print_str_link(temp->org->org->contents);
            temp = temp->next;
        }
    }
}



struct business *new_business(int u_id)
{
    struct business *busi = (struct business *)malloc(sizeof(struct business));
    busi->busi = new_node(u_id);
    printf("Enter the location : \n");
    busi->loc = new_Location2D();
    busi->owners = NULL;
    busi->customers = NULL;
    busi->grp_link = NULL;
    return busi;
}

struct busi_link *new_busi_link(struct business *busi)
{
    struct busi_link *busi_link = (struct busi_link *)malloc(sizeof(struct busi_link));
    busi_link->busi = busi;
    busi_link->next = NULL;
    return busi_link;
}

struct busi_link *add_busi_link_to_head(struct busi_link *head, struct business *busi)
{
    struct busi_link *busi_link = new_busi_link(busi);
    if (head == NULL)
        return busi_link;
    busi_link->next = head;
    return busi_link;
}

struct busi_link *delete_busi_link(struct business *busi, struct busi_link *head)
{
    struct busi_link *temp = head;
    struct busi_link *prev = NULL;
    while (temp != NULL)
    {
        if (temp->busi == busi)
        {
            if (prev == NULL)
            {
                head = temp->next;
                free(temp);
                printf("Business link deleted\n");
                return head;
            }
            else
            {
                prev->next = temp->next;
                free(temp);
                printf("Business link deleted\n");
                return head;
            }
        }
        prev = temp;
        temp = temp->next;
    }
    printf("No business link with the given business exists\n");
    return head;
}

struct business *search_business_by_unique_id(int u_id, struct busi_link *main_head)
{
    struct busi_link *temp = main_head;
    while (temp != NULL)
    {
        if (temp->busi->busi->unique_id == u_id)
        {
            printf("Business found\n");
            return temp->busi;
        }
        temp = temp->next;
    }
    printf("No business with the given unique id exists\n");
    return NULL;
}

struct business *search_business_by_name(char name[], struct busi_link *main_head)
{
    struct busi_link *temp = main_head;
    while (temp != NULL)
    {
        if (strcmp(temp->busi->busi->name, name) == 0)
        {
            printf("Business found\n");
            return temp->busi;
        }
        temp = temp->next;
    }
    printf("No business with the given name exists\n");
    return NULL;
}

struct business *search_business(struct busi_link *main_head)
{
    int choice;
    printf("1. Unique id\n2. Name\nEnter your choice : ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
    {
        int u_id;
        printf("Enter the unique id : ");
        scanf("%d", &u_id);
        return search_business_by_unique_id(u_id, main_head);
    }
    case 2:
    {
        char name[100];
        printf("Enter the name : ");
        scanf("%s", name);
        return search_business_by_name(name, main_head);
    }
    default:
    {
        printf("Invalid choice\n");
        return NULL;
    }
    }
}

int search_business_pointer(struct busi_link *main_head, struct business *busi)
{
    struct busi_link *temp = main_head;
    while (temp != NULL)
    {
        if (temp->busi == busi)
        {
            // printf("Business found\n");
            return 1;
        }
        temp = temp->next;
    }
    // printf("Business does not exist\n");
    return 0;
}

struct busi_link *delete_business(struct busi_link *main_head)
{
    printf("Delete business by :\n");
    struct business *busi = search_business(main_head);
    if (busi == NULL)
    {
        return NULL;
    }

    // TODO: Delete business from all the groups and organisations
    struct indi_link *owners = busi->owners;
    while(owners != NULL)
    {
        owners->indi->owner = delete_busi_link(busi, owners->indi->owner);
        owners = owners->next;
    }
    struct indi_link *customers = busi->customers;
    while(customers != NULL)
    {
        customers->indi->customer = delete_busi_link(busi, customers->indi->customer);
        customers = customers->next;
    }
    struct group_link *grp_link = busi->grp_link;
    while(grp_link != NULL)
    {
        grp_link->grp->busi_link = delete_busi_link(busi, grp_link->grp->busi_link);
        grp_link = grp_link->next;
    }

    main_head = delete_busi_link(busi, main_head);
    free(busi);
    return main_head;
}

void print_busi_link(struct busi_link *head, struct business *busi)
{
    struct busi_link *temp = head;
    while (temp != NULL)
    {
        if(temp->busi != busi)
        {
            printf("Name : %s\n", temp->busi->busi->name);
            printf("Unique ID :  %d\n", temp->busi->busi->unique_id);
            printf("Location : %d %d\n", temp->busi->loc->x, temp->busi->loc->y);
            printf("Creation date : %d/%d/%d\n", temp->busi->busi->creation_date->dd, temp->busi->busi->creation_date->mm, temp->busi->busi->creation_date->yyyy);
            printf("Contents : \n");
            print_str_link(temp->busi->busi->contents);
            temp = temp->next;
        }
    }
}



struct group *new_group(int u_id)
{
    struct group *grp = (struct group *)malloc(sizeof(struct group));
    grp->grp = new_node(u_id);
    grp->indi_link = NULL;
    grp->busi_link = NULL;
    return grp;
}

struct group_link *new_group_link(struct group *grp)
{
    struct group_link *group_link = (struct group_link *)malloc(sizeof(struct group_link));
    group_link->grp = grp;
    group_link->next = NULL;
    return group_link;
}

struct group_link *add_group_link_to_head(struct group_link *head, struct group *grp)
{
    struct group_link *group_link = new_group_link(grp);
    if (head == NULL)
        return group_link;
    group_link->next = head;
    return group_link;
}

struct group_link *delete_group_link(struct group *grp, struct group_link *head)
{
    struct group_link *temp = head;
    struct group_link *prev = NULL;
    while (temp != NULL)
    {
        if (temp->grp == grp)
        {
            if (prev == NULL)
            {
                head = temp->next;
                free(temp);
                printf("Group link deleted\n");
                return head;
            }
            else
            {
                prev->next = temp->next;
                free(temp);
                printf("Group link deleted\n");
                return head;
            }
        }
        prev = temp;
        temp = temp->next;
    }
    printf("No group link with the given group exists\n");
    return head;
}

struct group *search_group_by_unique_id(int u_id, struct group_link *main_head)
{
    struct group_link *temp = main_head;
    while (temp != NULL)
    {
        if (temp->grp->grp->unique_id == u_id)
        {
            printf("Group found\n");
            return temp->grp;
        }
        temp = temp->next;
    }
    printf("No group with the given unique id exists\n");
    return NULL;
}

struct group *search_group_by_name(char name[], struct group_link *main_head)
{
    struct group_link *temp = main_head;
    while (temp != NULL)
    {
        if (strcmp(temp->grp->grp->name, name) == 0)
        {
            printf("Group found\n");
            return temp->grp;
        }
        temp = temp->next;
    }
    printf("No group with the given name exists\n");
    return NULL;
}

struct group *search_group(struct group_link *main_head)
{
    int choice;
    printf("1. Unique id\n2. Name\nEnter your choice : ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
    {
        int u_id;
        printf("Enter the unique id : ");
        scanf("%d", &u_id);
        return search_group_by_unique_id(u_id, main_head);
    }
    case 2:
    {
        char name[100];
        printf("Enter the name : ");
        scanf("%s", name);
        return search_group_by_name(name, main_head);
    }
    default:
    {
        printf("Invalid choice\n");
        return NULL;
    }
    }
}

int search_group_pointer(struct group_link *main_head, struct group *grp)
{
    struct group_link *temp = main_head;
    while (temp != NULL)
    {
        if (temp->grp == grp)
        {
            // printf("Group found\n");
            return 1;
        }
        temp = temp->next;
    }
    // printf("Group does not exist\n");
    return 0;
}

struct group_link *delete_group(struct group_link *main_head)
{
    printf("Delete group by :\n");
    struct group *grp = search_group(main_head);
    if (grp == NULL)
    {
        return NULL;
    }

    // TODO: Delete group from all the organisations and businesses
    struct indi_link *indi_link = grp->indi_link;
    while(indi_link != NULL)
    {
        indi_link->indi->grp_link = delete_group_link(grp, indi_link->indi->grp_link);
        indi_link = indi_link->next;
    }
    struct busi_link *busi_link = grp->busi_link;
    while(busi_link != NULL)
    {
        busi_link->busi->grp_link = delete_group_link(grp, busi_link->busi->grp_link);
        busi_link = busi_link->next;
    }

    main_head = delete_group_link(grp, main_head);
    free(grp);
    return main_head;
}

void print_group_link(struct group_link *head, struct group *grp)
{
    struct group_link *temp = head;
    while (temp != NULL)
    {
        if(temp->grp != grp)
        {
            printf("Name : %s\n", temp->grp->grp->name);
            printf("Unique ID :  %d\n", temp->grp->grp->unique_id);
            printf("Creation date : %d/%d/%d\n", temp->grp->grp->creation_date->dd, temp->grp->grp->creation_date->mm, temp->grp->grp->creation_date->yyyy);
            printf("Contents : \n");
            print_str_link(temp->grp->grp->contents);
            temp = temp->next;
        }
    }
}



void test_indi_link()
{
    struct indi_link *head = NULL;
    int u_id = 1;
    int choice;
    while (1)
    {
        printf("1. Add individual link to head\n");
        printf("2. Delete individual link\n");
        printf("3. Search individual by unique id\n");
        printf("4. Search individual by name\n");
        printf("5. Search individual by birth date\n");
        printf("6. Print individual link\n");
        printf("7. Delete individual\n");
        printf("8. Exit\n");
        printf("Enter your choice : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
        {
            struct individual *indi = new_individual(u_id);
            u_id++;
            head = add_indi_link_to_head(head, indi);
            break;
        }
        case 2:
        {
            struct individual *indi = search_individual(head);
            if (indi == NULL)
            {
                break;
            }
            head = delete_indi_link(indi, head);
            break;
        }
        case 3:
        {
            int u_id;
            printf("Enter the unique id : ");
            scanf("%d", &u_id);
            search_individual_by_unique_id(u_id, head);
            break;
        }
        case 4:
        {
            printf("Enter the name : \n");
            char *name = new_str();
            search_individual_by_name(name, head);
            break;
        }
        case 5:
        {
            struct date *b_day = new_date();
            search_individual_by_birth_date(b_day, head);
            break;
        }
        case 6:
        {
            print_indi_link(head, NULL);
            break;
        }
        case 7:
        {
            head = delete_individual(head);
            break;
        }
        case 8:
        {
            return;
        }
        default:
        {
            printf("Invalid choice\n");
            break;
        }
        }
    }
}

void test_org_link()
{
    int u_id = 1;
    struct org_link *head = NULL;
    int choice;
    while (1)
    {
        printf("1. Add organisation link to head\n");
        printf("2. Delete organisation link\n");
        printf("3. Search organisation by unique id\n");
        printf("4. Search organisation by name\n");
        printf("5. Print organisation link\n");
        printf("6. Delete organisation\n");
        printf("7. Exit\n");
        printf("Enter your choice : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
        {
            struct organisation *org = new_organisation(u_id);
            u_id++;
            head = add_org_link_to_head(head, org);
            break;
        }
        case 2:
        {
            struct organisation *org = search_organisation(head);
            if (org == NULL)
            {
                break;
            }
            head = delete_org_link(org, head);
            break;
        }
        case 3:
        {
            int u_id;
            printf("Enter the unique id : ");
            scanf("%d", &u_id);
            search_organisation_by_unique_id(u_id, head);
            break;
        }
        case 4:
        {
            printf("Enter the name : \n");
            char *name = new_str();
            search_organisation_by_name(name, head);
            break;
        }
        case 5:
        {
            print_org_link(head, NULL);
            break;
        }
        case 6:
        {
            head = delete_organisation(head);
            break;
        }
        case 7:
        {
            return;
        }
        default:
        {
            printf("Invalid choice\n");
            break;
        }
        }
    }
}

void test_busi_link()
{
    int u_id = 1;
    struct busi_link *head = NULL;
    int choice;
    while (1)
    {
        printf("1. Add business link to head\n");
        printf("2. Delete business link\n");
        printf("3. Search business by unique id\n");
        printf("4. Search business by name\n");
        printf("5. Print business link\n");
        printf("6. Delete business\n");
        printf("7. Exit\n");
        printf("Enter your choice : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
        {
            struct business *busi = new_business(u_id);
            u_id++;
            head = add_busi_link_to_head(head, busi);
            break;
        }
        case 2:
        {
            struct business *busi = search_business(head);
            if (busi == NULL)
            {
                break;
            }
            head = delete_busi_link(busi, head);
            break;
        }
        case 3:
        {
            int u_id;
            printf("Enter the unique id : ");
            scanf("%d", &u_id);
            search_business_by_unique_id(u_id, head);
            break;
        }
        case 4:
        {
            printf("Enter the name : \n");
            char *name = new_str();
            search_business_by_name(name, head);
            break;
        }
        case 5:
        {
            print_busi_link(head, NULL);
            break;
        }
        case 6:
        {
            head = delete_business(head);
            break;
        }
        case 7:
        {
            return;
        }
        default:
        {
            printf("Invalid choice\n");
            break;
        }
        }
    }
}

void test_group_link()
{
    int u_id = 1;
    struct group_link *head = NULL;
    int choice;
    while (1)
    {
        printf("1. Add group link to head\n");
        printf("2. Delete group link\n");
        printf("3. Search group by unique id\n");
        printf("4. Search group by name\n");
        printf("5. Print group link\n");
        printf("6. Delete group\n");
        printf("7. Exit\n");
        printf("Enter your choice : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
        {
            struct group *grp = new_group(u_id);
            u_id++;
            head = add_group_link_to_head(head, grp);
            break;
        }
        case 2:
        {
            struct group *grp = search_group(head);
            if (grp == NULL)
            {
                break;
            }
            head = delete_group_link(grp, head);
            break;
        }
        case 3:
        {
            int u_id;
            printf("Enter the unique id : ");
            scanf("%d", &u_id);
            search_group_by_unique_id(u_id, head);
            break;
        }
        case 4:
        {
            printf("Enter the name : \n");
            char *name = new_str();
            search_group_by_name(name, head);
            break;
        }
        case 5:
        {
            print_group_link(head, NULL);
            break;
        }
        case 6:
        {
            head = delete_group(head);
            break;
        }
        case 7:
        {
            return;
        }
        default:
        {
            printf("Invalid choice\n");
            break;
        }
        }
    }
}

void test_entities()
{
    int choice;
    while (1)
    {
        printf("1. Test individual link\n");
        printf("2. Test organisation link\n");
        printf("3. Test business link\n");
        printf("4. Test group link\n");
        printf("5. Exit\n");
        printf("Enter your choice : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
        {
            test_indi_link();
            break;
        }
        case 2:
        {
            test_org_link();
            break;
        }
        case 3:
        {
            test_busi_link();
            break;
        }
        case 4:
        {
            test_group_link();
            break;
        }
        case 5:
        {
            return;
        }
        default:
        {
            printf("Invalid choice\n");
            break;
        }
        }
    }
}



void add_indi_to_group(struct group_link *group_head, struct indi_link *indi_head)
{
    printf("Search individual by : \n");
    struct individual *indi = search_individual(indi_head);
    if(indi == NULL)
    {
        printf("Individual does not exist\n");
        return;
    }
    printf("Search group by : \n");
    struct group *group = search_group(group_head);
    if(group == NULL)
    {
        printf("Group does not exist\n");
        return;
    }

    if (search_individual_pointer(group->indi_link, indi))
    {
        printf("Individual already in the group\n");
        return;
    }
    printf("Individual added to the group\n");

    indi->grp_link = add_group_link_to_head(indi->grp_link, group);
    group->indi_link = add_indi_link_to_head(group->indi_link, indi);
}

void delete_indi_from_group(struct group_link *group_head, struct indi_link *indi_head)
{
    printf("Search individual by : \n");
    struct individual *indi = search_individual(indi_head);
    printf("Search group by : \n");
    struct group *group = search_group(group_head);

    if (indi == NULL || group == NULL)
    {
        return;
    }

    indi->grp_link = delete_group_link(group, indi->grp_link);
    group->indi_link = delete_indi_link(indi, group->indi_link);
}

void print_indi_in_group(struct group* group)
{
    struct indi_link *temp = group->indi_link;

    while (temp != NULL)
    {
        printf("%s\n", temp->indi->ind->name);
        temp = temp->next;
    }
}

void print_groups_of_indi(struct individual* indi)
{
    struct group_link *temp = indi->grp_link;

    while (temp != NULL)
    {
        printf("%s\n", temp->grp->grp->name);
        temp = temp->next;
    }
}



void add_busi_to_group(struct group_link *group_head, struct busi_link *busi_head)
{
    printf("Search business by : \n");
    struct business *busi = search_business(busi_head);
    if(busi == NULL)
    {
        printf("Business does not exist\n");
        return;
    }
    printf("Search group by : \n");
    struct group *group = search_group(group_head);
    if(group == NULL)
    {
        printf("Group does not exist\n");
        return;
    }

    if (search_business_pointer(group->busi_link, busi))
    {
        printf("Business already in the group\n");
        return;
    }
    printf("Business added to the group\n");

    busi->grp_link = add_group_link_to_head(busi->grp_link, group);
    group->busi_link = add_busi_link_to_head(group->busi_link, busi);
}

void delete_busi_from_group(struct group_link *group_head, struct busi_link *busi_head)
{
    printf("Search business by : \n");
    struct business *busi = search_business(busi_head);
    printf("Search group by : \n");
    struct group *group = search_group(group_head);

    if (busi == NULL || group == NULL)
    {
        return;
    }

    busi->grp_link = delete_group_link(group, busi->grp_link);
    group->busi_link = delete_busi_link(busi, group->busi_link);
}

void print_busi_in_group(struct group* group)
{
    struct busi_link *temp = group->busi_link;

    while (temp != NULL)
    {
        printf("%s\n", temp->busi->busi->name);
        temp = temp->next;
    }
}

void print_groups_of_busi(struct business* busi)
{
    struct group_link *temp = busi->grp_link;

    while (temp != NULL)
    {
        printf("%s\n", temp->grp->grp->name);
        temp = temp->next;
    }
}



void add_indi_owner_to_busi(struct busi_link *busi_head, struct indi_link *indi_head)
{
    printf("Search business by : \n");
    struct business *busi = search_business(busi_head);
    if(busi == NULL)
    {
        printf("Business does not exist\n");
        return;
    }
    printf("Search individual by : \n");
    struct individual *indi = search_individual(indi_head);
    if(indi == NULL)
    {
        printf("Individual does not exist\n");
        return;
    }

    if (search_individual_pointer(busi->owners, indi))
    {
        printf("Individual already owns the business\n");
        return;
    }
    printf("Individual added as owner to the business\n");

    busi->owners = add_indi_link_to_head(busi->owners, indi);
    indi->owner = add_busi_link_to_head(indi->owner, busi);
}

void delete_indi_owner_from_busi(struct busi_link *busi_head, struct indi_link *indi_head)
{
    printf("Search business by : \n");
    struct business *busi = search_business(busi_head);
    printf("Search individual by : \n");
    struct individual *indi = search_individual(indi_head);

    if (busi == NULL || indi == NULL)
    {
        return;
    }

    busi->owners = delete_indi_link(indi, busi->owners);
    indi->owner = delete_busi_link(busi, indi->owner);
}

void print_indi_owner_in_busi(struct business* busi)
{
    struct indi_link *temp = busi->owners;

    while (temp != NULL)
    {
        printf("%s\n", temp->indi->ind->name);
        temp = temp->next;
    }
}

void print_busi_owned_by_indi(struct individual* indi)
{
    struct busi_link *temp = indi->owner;

    while (temp != NULL)
    {
        printf("%s\n", temp->busi->busi->name);
        temp = temp->next;
    }
}



void add_indi_customer_to_busi(struct busi_link *busi_head, struct indi_link *indi_head)
{
    printf("Search business by : \n");
    struct business *busi = search_business(busi_head);
    if(busi == NULL)
    {
        printf("Business does not exist\n");
        return;
    }
    printf("Search individual by : \n");
    struct individual *indi = search_individual(indi_head);
    if(indi == NULL)
    {
        printf("Individual does not exist\n");
        return;
    }

    if (search_individual_pointer(busi->customers, indi))
    {
        printf("Individual already is a customer to the business\n");
        return;
    }
    printf("Individual added as customer to the business\n");

    busi->customers = add_indi_link_to_head(busi->customers, indi);
    indi->customer = add_busi_link_to_head(indi->customer, busi);
}

void delete_indi_customer_from_busi(struct busi_link *busi_head, struct indi_link *indi_head)
{
    printf("Search business by : \n");  
    struct business *busi = search_business(busi_head);
    printf("Search individual by : \n");
    struct individual *indi = search_individual(indi_head);

    if (busi == NULL || indi == NULL)
    {
        return;
    }

    busi->customers = delete_indi_link(indi, busi->customers);
    indi->customer = delete_busi_link(busi, indi->customer);
}

void print_indi_customer_in_busi(struct business* busi)
{
    struct indi_link *temp = busi->customers;

    while (temp != NULL)
    {
        printf("%s\n", temp->indi->ind->name);
        temp = temp->next;
    }
}

void print_indi_customer_of_busi(struct individual* indi)
{
    struct busi_link *temp = indi->customer;

    while (temp != NULL)
    {
        printf("%s\n", temp->busi->busi->name);
        temp = temp->next;
    }
}



void add_indi_to_org(struct org_link *org_head, struct indi_link *indi_head)
{
    printf("Search organisation by : \n");
    struct organisation *org = search_organisation(org_head);
    if(org == NULL)
    {
        printf("Organisation does not exist\n");
        return;
    }
    printf("Search individual by : \n");
    struct individual *indi = search_individual(indi_head);
    if(indi == NULL)
    {
        printf("Individual does not exist\n");
        return;
    }

    if (search_individual_pointer(org->indi_link, indi))
    {
        printf("Individual already in the organisation\n");
        return;
    }
    printf("Individual added to the organisation\n");

    org->indi_link = add_indi_link_to_head(org->indi_link, indi);
    indi->org_link = add_org_link_to_head(indi->org_link, org);
}

void delete_indi_from_org(struct org_link *org_head, struct indi_link *indi_head)
{
    printf("Search organisation by : \n");
    struct organisation *org = search_organisation(org_head);
    printf("Search individual by : \n");
    struct individual *indi = search_individual(indi_head);

    if (org == NULL || indi == NULL)
    {
        return;
    }

    org->indi_link = delete_indi_link(indi, org->indi_link);
    indi->org_link = delete_org_link(org, indi->org_link);
}

void print_indi_in_org(struct organisation* org)
{
    struct indi_link *temp = org->indi_link;

    while (temp != NULL)
    {
        printf("%s\n", temp->indi->ind->name);
        temp = temp->next;
    }
}

void print_org_of_indi(struct individual* indi)
{
    struct org_link *temp = indi->org_link;

    while (temp != NULL)
    {
        printf("%s\n", temp->org->org->name);
        temp = temp->next;
    }
}



void post_content_individual(struct individual *indi, char *str)
{
    indi->ind->contents = add_str_link_to_head(indi->ind->contents, str);
}

void post_content_group(struct group *grp, char *str)
{
    grp->grp->contents = add_str_link_to_head(grp->grp->contents, str);
}

void post_content_business(struct business *busi, char *str)
{
    busi->busi->contents = add_str_link_to_head(busi->busi->contents, str);
}

void post_content_organisation(struct organisation *org, char *str)
{
    org->org->contents = add_str_link_to_head(org->org->contents, str);
}

void delete_content_individual(struct individual *indi)
{
    printf("Enter the content number : ");
    int num;
    scanf("%d", &num);
    indi->ind->contents = delete_post(num, indi->ind->contents);
}

void delete_content_group(struct group *grp)
{
    printf("Enter the content number : ");
    int num;
    scanf("%d", &num);
    grp->grp->contents = delete_post(num, grp->grp->contents);
}

void delete_content_business(struct business *busi)
{
    printf("Enter the content number : ");
    int num;
    scanf("%d", &num);
    busi->busi->contents = delete_post(num, busi->busi->contents);
}

void delete_content_organisation(struct organisation *org)
{
    printf("Enter the content number : ");
    int num;
    scanf("%d", &num);
    org->org->contents = delete_post(num, org->org->contents);
}



void test_ind_org_link()
{
    struct indi_link* indi_head = NULL;
    struct org_link* org_head = NULL;
    int u_id = 0;

    int choice = 0;
    while(choice != 7)
    {
        printf("1. Add an individual\n2. Add an organisation\n3. Add an individual to an organisation\n4. Delete an individual from an organisation\n5. Print all individuals in an organisation\n6. Exit\n");
        printf("Enter your choice : ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                indi_head = add_indi_link_to_head(indi_head, new_individual(u_id));
                u_id++;
                break;
            case 2:
                org_head = add_org_link_to_head(org_head, new_organisation(u_id));
                u_id++;
                break;
            case 3:
                add_indi_to_org(org_head, indi_head);
                break;
            case 4:
                delete_indi_from_org(org_head, indi_head);
                break;
            case 5:
                printf("Search organisation by : \n");
                struct organisation *org = search_organisation(org_head);
                print_indi_in_org(org);
                break;
            case 6:
                printf("Search individual by : \n");
                struct individual *indi = search_individual(indi_head);
                print_org_of_indi(indi);
                break;
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    }
}

void test_ind_grp_link()
{
    struct indi_link* indi_head = NULL;
    struct group_link* group_head = NULL;
    int u_id = 0;

    int choice = 0;
    while(choice != 7)
    {
        printf("1. Add an individual\n2. Add a group\n3. Add an individual to a group\n4. Delete an individual from a group\n5. Print all individuals in a group\n6. Exit\n");
        printf("Enter your choice : ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                indi_head = add_indi_link_to_head(indi_head, new_individual(u_id));
                u_id++;
                break;
            case 2:
                group_head = add_group_link_to_head(group_head, new_group(u_id));
                u_id++;
                break;
            case 3:
                add_indi_to_group(group_head, indi_head);
                break;
            case 4:
                delete_indi_from_group(group_head, indi_head);
                break;
            case 5:
                printf("Search group by : \n");
                struct group *group = search_group(group_head);
                print_indi_in_group(group);
                break;
            case 6:
                printf("Search individual by : \n");
                struct individual *indi = search_individual(indi_head);
                print_groups_of_indi(indi);
                break;
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    }
}

void test_ind_owner_busi_link()
{
    struct indi_link* indi_head = NULL;
    struct busi_link* busi_head = NULL;
    int u_id = 0;

    int choice = 0;
    while(choice != 7)
    {
        printf("1. Add an individual\n2. Add a business\n3. Add an individual as owner to a business\n4. Delete an individual as owner from a business\n5. Print all individuals as owners in a business\n6. Exit\n");
        printf("Enter your choice : ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                indi_head = add_indi_link_to_head(indi_head, new_individual(u_id));
                u_id++;
                break;
            case 2:
                busi_head = add_busi_link_to_head(busi_head, new_business(u_id));
                u_id++;
                break;
            case 3:
                add_indi_owner_to_busi(busi_head, indi_head);
                break;
            case 4:
                delete_indi_owner_from_busi(busi_head, indi_head);
                break;
            case 5:
                printf("Search business by : \n");
                struct business *busi = search_business(busi_head);
                print_indi_owner_in_busi(busi);
                break;
            case 6:
                printf("Search individual by : \n");
                struct individual *indi = search_individual(indi_head);
                print_busi_owned_by_indi(indi);
                break;
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    }
}

void test_indi_customer_busi_link()
{
    struct indi_link* indi_head = NULL;
    struct busi_link* busi_head = NULL;
    int u_id = 0;

    int choice = 0;
    while(choice != 7)
    {
        printf("1. Add an individual\n2. Add a business\n3. Add an individual as customer to a business\n4. Delete an individual as customer from a business\n5. Print all individuals as customers in a business\n6. Exit\n");
        printf("Enter your choice : ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                indi_head = add_indi_link_to_head(indi_head, new_individual(u_id));
                u_id++;
                break;
            case 2:
                busi_head = add_busi_link_to_head(busi_head, new_business(u_id));
                u_id++;
                break;
            case 3:
                add_indi_customer_to_busi(busi_head, indi_head);
                break;
            case 4:
                delete_indi_customer_from_busi(busi_head, indi_head);
                break;
            case 5:
                printf("Search business by : \n");
                struct business *busi = search_business(busi_head);
                print_indi_customer_in_busi(busi);
                break;
            case 6:
                printf("Search individual by : \n");
                struct individual *indi = search_individual(indi_head);
                print_indi_customer_of_busi(indi);
                break;
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    }
}

void test_busi_group_link()
{
    struct busi_link* busi_head = NULL;
    struct group_link* group_head = NULL;
    int u_id = 0;

    int choice = 0;
    while(choice != 7)
    {
        printf("1. Add a business\n2. Add a group\n3. Add a business to a group\n4. Delete a business from a group\n5. Print all businesses in a group\n6. Exit\n");
        printf("Enter your choice : ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                busi_head = add_busi_link_to_head(busi_head, new_business(u_id));
                u_id++;
                break;
            case 2:
                group_head = add_group_link_to_head(group_head, new_group(u_id));
                u_id++;
                break;
            case 3:
                add_busi_to_group(group_head, busi_head);
                break;
            case 4:
                delete_busi_from_group(group_head, busi_head);
                break;
            case 5:
                printf("Search group by : \n");
                struct group *group = search_group(group_head);
                print_busi_in_group(group);
                break;
            case 6:
                printf("Search business by : \n");
                struct business *busi = search_business(busi_head);
                print_groups_of_busi(busi);
                break;
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    }
}

void test_links()
{
    int choice;
    while (1)
    {
        printf("1. Test individual organisation link\n");
        printf("2. Test individual group link\n");
        printf("3. Test individual owner business link\n");
        printf("4. Test individual customer business link\n");
        printf("5. Test business group link\n");
        printf("6. Exit\n");
        printf("Enter your choice : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
        {
            test_ind_org_link();
            break;
        }
        case 2:
        {
            test_ind_grp_link();
            break;
        }
        case 3:
        {
            test_ind_owner_busi_link();
            break;
        }
        case 4:
        {
            test_indi_customer_busi_link();
            break;
        }
        case 5:
        {
            test_busi_group_link();
            break;
        }
        case 6:
        {
            return;
        }
        default:
        {
            printf("Invalid choice\n");
            break;
        }
        }
    }

}



void social()
{
    // The head of the linked list of all the entities
    struct indi_link* indi_head = NULL;
    struct busi_link* busi_head = NULL;
    struct org_link* org_head = NULL;
    struct group_link* group_head = NULL;

    int unique_id = 1;

    int choice = 0;
    printf("Welcome to the social network\n");
    while(choice!=11)
    {
        printf("1. Create an entity\n2. Delete an entity\n3. Search for an entity\n4. Print all 1-hop linked nodes\n5. Create and post content\n6. Print posts of individuals linked to an individual\n7. Create and delete links between entities\n8. Search substring in content\n9. Repost content\n10. Print contents\n11. Exit\n");
        int visited_indi[unique_id];
        printf("Enter your choice : ");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
                printf("1. Individual\n2. Business\n3. Organisation\n4. Group\n");
                printf("Enter your choice : ");
                int choice1;
                scanf("%d", &choice1);
                switch(choice1)
                {
                    case 1:
                        indi_head = add_indi_link_to_head(indi_head, new_individual(unique_id));
                        unique_id++;
                        break;
                    case 2:
                        busi_head = add_busi_link_to_head(busi_head, new_business(unique_id));
                        unique_id++;
                        break;
                    case 3:
                        org_head = add_org_link_to_head(org_head, new_organisation(unique_id));
                        unique_id++;
                        break;
                    case 4:
                        group_head = add_group_link_to_head(group_head, new_group(unique_id));
                        unique_id++;
                        break;
                    default:
                        printf("Invalid choice\n");
                }
                break;
            case 2:
                printf("1. Individual\n2. Business\n3. Organisation\n4. Group\n");
                printf("Enter your choice : ");
                int choice2;
                scanf("%d", &choice2);
                switch(choice2)
                {
                    case 1:
                        indi_head = delete_individual(indi_head);
                        break;
                    case 2:
                        busi_head = delete_business(busi_head);
                        break;
                    case 3:
                        org_head = delete_organisation(org_head);
                        break;
                    case 4:
                        group_head = delete_group(group_head);
                        break;
                    default:
                        printf("Invalid choice\n");
                }
                break;
            case 3:
                printf("1. Individual\n2. Business\n3. Organisation\n4. Group\n");
                printf("Enter your choice : ");
                int choice3;
                scanf("%d", &choice3);
                switch(choice3)
                {
                    case 1:
                        printf("Search individual by :\n");
                        struct individual* indi_3 = search_individual(indi_head);
                        if(indi_3 == NULL)
                        {
                            break;
                        }
                        printf("Name : %s\n", indi_3->ind->name);
                        printf("Unique id : %d\n", indi_3->ind->unique_id);
                        break;
                    case 2:
                        printf("Search business by :\n");
                        struct business* busi_3 = search_business(busi_head);
                        if(busi_3 == NULL)
                        {
                            break;
                        }
                        printf("Name : %s\n", busi_3->busi->name);
                        printf("Unique id : %d\n", busi_3->busi->unique_id);
                        break;
                    case 3:
                        printf("Search organisation by :\n");
                        struct organisation* org_3 = search_organisation(org_head);
                        if(org_3 == NULL)
                        {
                            break;
                        }
                        printf("Name : %s\n", org_3->org->name);
                        printf("Unique id : %d\n", org_3->org->unique_id);
                        break;
                    case 4:
                        printf("Search group by :\n");
                        struct group* grp_3 = search_group(group_head);
                        if(grp_3 == NULL)
                        {
                            break;
                        }
                        printf("Name : %s\n", grp_3->grp->name);
                        printf("Unique id : %d\n", grp_3->grp->unique_id);
                        break;
                    default:
                        printf("Invalid choice\n");
                }
                break;
            case 4:
                printf("1. Individual\n2. Business\n3. Organisation\n4. Group\n");
                printf("Enter your choice : ");
                int choice4;
                scanf("%d", &choice4);
                switch(choice4)
                {
                    case 1:
                        printf("Search individual by :\n");
                        struct individual* indi = search_individual(indi_head);
                        if(indi == NULL)
                        {
                            break;
                        }
                        printf("1. Group\n");
                        print_groups_of_indi(indi);
                        printf("2. Organisation\n");
                        print_org_of_indi(indi);
                        printf("3. Owners of businesses\n");
                        print_busi_owned_by_indi(indi);
                        printf("4. Customers of businesses\n");
                        print_indi_customer_of_busi(indi);
                        break;
                    case 2:
                        printf("Search business by :\n");
                        struct business* busi = search_business(busi_head);
                        if(busi == NULL)
                        {
                            break;
                        }
                        printf("1. Group\n");
                        print_groups_of_busi(busi);
                        printf("2. Owners of businesses\n");
                        print_indi_owner_in_busi(busi);
                        printf("3. Customers of businesses\n");
                        print_indi_customer_in_busi(busi);
                        break;
                    case 3:
                        printf("Search organisation by :\n");
                        struct organisation* org = search_organisation(org_head);
                        if(org == NULL)
                        {
                            break;
                        }
                        printf("1. Individuals in organisation\n");
                        print_indi_in_org(org);
                        break;
                    case 4:
                        printf("Search group by :\n");
                        struct group* grp = search_group(group_head);
                        if(grp == NULL)
                        {
                            break;
                        }
                        printf("1. Individuals in group\n");
                        print_indi_in_group(grp);
                        printf("2. Businesses in group\n");
                        print_busi_in_group(grp);
                        break;
                    default:
                        printf("Invalid choice\n");
                        break;
                }
                break;
            case 5:
                printf("1. Individual\n2. Business\n3. Organisation\n4. Group\n");
                printf("Enter your choice : ");
                int choice5;
                scanf("%d", &choice5);
                switch(choice5)
                {
                    case 1:
                        printf("Search individual by :\n");
                        struct individual* indi = search_individual(indi_head);
                        if(indi == NULL)
                        {
                            break;
                        }
                        post_content_individual(indi, new_str());
                        break;
                    case 2:
                        printf("Search business by :\n");
                        struct business* busi = search_business(busi_head);
                        if(busi == NULL)
                        {
                            break;
                        }
                        post_content_business(busi, new_str());
                        break;
                    case 3:
                        printf("Search organisation by :\n");
                        struct organisation* org = search_organisation(org_head);
                        if(org == NULL)
                        {
                            break;
                        }
                        post_content_organisation(org, new_str());
                        break;
                    case 4:
                        printf("Search group by :\n");
                        struct group* grp = search_group(group_head);
                        if(grp == NULL)
                        {
                            break;
                        }
                        post_content_group(grp, new_str());
                        break;
                    default:
                        printf("Invalid choice\n");
                        break;
                }
                break;
            case 6:
                printf("Search individual by :\n");
                struct individual* indi = search_individual(indi_head);
                if(indi == NULL)
                {
                    break;
                }
                for(int i=0; i<unique_id; i++)
                {
                    visited_indi[i] = 0;
                }
                visited_indi[indi->ind->unique_id] = 1;
                struct group_link* temp_grp = indi->grp_link;
                while(temp_grp != NULL)
                {
                    struct indi_link* temp_indi = temp_grp->grp->indi_link;
                    while(temp_indi != NULL)
                    {
                        if(visited_indi[temp_indi->indi->ind->unique_id] == 0)
                        {
                            printf("%s\n", temp_indi->indi->ind->name);
                            visited_indi[temp_indi->indi->ind->unique_id] = 1;
                            print_str_link(temp_indi->indi->ind->contents);
                        }
                        temp_indi = temp_indi->next;
                    }
                    temp_grp = temp_grp->next;
                }
                struct org_link* temp_org = indi->org_link;
                while(temp_org != NULL)
                {
                    struct indi_link* temp_indi = temp_org->org->indi_link;
                    while(temp_indi != NULL)
                    {
                        if(visited_indi[temp_indi->indi->ind->unique_id] == 0)
                        {
                            printf("%s\n", temp_indi->indi->ind->name);
                            visited_indi[temp_indi->indi->ind->unique_id] = 1;
                            print_str_link(temp_indi->indi->ind->contents);
                        }
                        temp_indi = temp_indi->next;
                    }
                    temp_org = temp_org->next;
                }
                // struct busi_link* temp_busi_own = indi->owner;
                // while(temp_busi_own != NULL)
                // {
                //     struct indi_link* temp_indi = temp_busi_own->busi->owners;
                //     while(temp_indi != NULL)
                //     {
                //         if(visited_indi[temp_indi->indi->ind->unique_id] == 0)
                //         {
                //             printf("%s\n", temp_indi->indi->ind->name);
                //             visited_indi[temp_indi->indi->ind->unique_id] = 1;
                //             print_str_link(temp_indi->indi->ind->contents);
                //         }
                //         temp_indi = temp_indi->next;
                //     }

                //     temp_indi = temp_busi_own->busi->customers;
                //     while(temp_indi != NULL)
                //     {
                //         if(visited_indi[temp_indi->indi->ind->unique_id] == 0)
                //         {
                //             printf("%s\n", temp_indi->indi->ind->name);
                //             visited_indi[temp_indi->indi->ind->unique_id] = 1;
                //             print_str_link(temp_indi->indi->ind->contents);
                //         }
                //         temp_indi = temp_indi->next;
                //     }
                //     temp_busi_own = temp_busi_own->next;
                // }
                // struct busi_link* temp_busi_customer = indi->customer;
                // while(temp_busi_customer != NULL)
                // {
                //     struct indi_link* temp_indi = temp_busi_customer->busi->customers;
                //     while(temp_indi != NULL)
                //     {
                //         if(visited_indi[temp_indi->indi->ind->unique_id] == 0)
                //         {
                //             printf("%s\n", temp_indi->indi->ind->name);
                //             visited_indi[temp_indi->indi->ind->unique_id] = 1;
                //             print_str_link(temp_indi->indi->ind->contents);
                //         }
                //         temp_indi = temp_indi->next;
                //     }

                //     temp_indi = temp_busi_customer->busi->owners;
                //     while(temp_indi != NULL)
                //     {
                //         if(visited_indi[temp_indi->indi->ind->unique_id] == 0)
                //         {
                //             printf("%s\n", temp_indi->indi->ind->name);
                //             visited_indi[temp_indi->indi->ind->unique_id] = 1;
                //             print_str_link(temp_indi->indi->ind->contents);
                //         }
                //         temp_indi = temp_indi->next;
                //     }
                //     temp_busi_customer = temp_busi_customer->next;
                // }
                break;
            case 7:
                printf("1. Add an individual to a group\n2. Delete an individual from a group\n3. Add an individual as owner to a business\n4. Delete an individual as owner from a business\n5. Add an individual as customer to a business\n6. Delete an individual as customer from a business\n7. Add an individual to an organisation\n8. Delete an individual from an organisation\n9. Add a business to a group\n10. Delete a business from a group\n");
                printf("Enter your choice : ");
                int choice7;
                scanf("%d", &choice7);
                switch(choice7)
                {
                    case 1:
                        add_indi_to_group(group_head, indi_head);
                        break;
                    case 2:
                        delete_indi_from_group(group_head, indi_head);
                        break;
                    case 3:
                        add_indi_owner_to_busi(busi_head, indi_head);
                        break;
                    case 4:
                        delete_indi_owner_from_busi(busi_head, indi_head);
                        break;
                    case 5:
                        add_indi_customer_to_busi(busi_head, indi_head);
                        break;
                    case 6:
                        delete_indi_customer_from_busi(busi_head, indi_head);
                        break;
                    case 7:
                        add_indi_to_org(org_head, indi_head);
                        break;
                    case 8:
                        delete_indi_from_org(org_head, indi_head);
                        break;
                    case 9:
                        add_busi_to_group(group_head, busi_head);
                        break;
                    case 10:
                        delete_busi_from_group(group_head, busi_head);
                        break;
                    default:
                        printf("Invalid choice\n");
                        break;
                }
                break;
            case 8:
                printf("Enter the substring : \n");
                char* str = new_str();
                
                struct indi_link* tem_indi = indi_head;
                while(tem_indi != NULL)
                {
                    struct string_link* tem_str = find_str_link(str, tem_indi->indi->ind->contents);
                    if(tem_str != NULL)
                    {
                        printf("%s\n", tem_indi->indi->ind->name);
                    }
                    print_str_link(tem_str);
                    tem_indi = tem_indi->next;
                }
                struct busi_link* tem_busi = busi_head;
                while(tem_busi != NULL)
                {
                    struct string_link* tem_str = find_str_link(str, tem_busi->busi->busi->contents);
                    if(tem_str != NULL)
                    {
                        printf("%s\n", tem_busi->busi->busi->name);
                    }
                    print_str_link(tem_str);
                    tem_busi = tem_busi->next;
                }
                struct org_link* tem_org = org_head;
                while(tem_org != NULL)
                {
                    struct string_link* tem_str = find_str_link(str, tem_org->org->org->contents);
                    if(tem_str != NULL)
                    {
                        printf("%s\n", tem_org->org->org->name);
                    }
                    print_str_link(tem_str);
                    tem_org = tem_org->next;
                }
                struct group_link* tem_grp = group_head;
                while(tem_grp != NULL)
                {
                    struct string_link* tem_str = find_str_link(str, tem_grp->grp->grp->contents);
                    if(tem_str != NULL)
                    {
                        printf("%s\n", tem_grp->grp->grp->name);
                    }
                    print_str_link(tem_str);
                    tem_grp = tem_grp->next;
                }

               break;
            case 9:
                printf("To repost content from :\n");
                printf("1. Individual\n2. Business\n3. Organisation\n4. Group\n");
                printf("Enter your choice : ");
                int choice9;
                int n, choice91;
                char* str_9;
                scanf("%d", &choice9);
                switch(choice9)
                {
                    case 1:
                        printf("Search individual by :\n");
                        struct individual* indi = search_individual(indi_head);
                        if(indi == NULL)
                        {
                            break;
                        }
                        
                        printf("Enter the content number : ");
                        scanf("%d", &n);
                        str_9 = find_post(n, indi->ind->contents);
                        if(str_9 == NULL)
                        {
                            break;
                        }
                        
                        printf("To repost content to :\n");
                        printf("1. Individual\n2. Business\n3. Organisation\n4. Group\n");
                        printf("Enter your choice : ");
                        scanf("%d", &choice91);
                        switch(choice91)
                        {
                            case 1:
                                printf("Search individual by :\n");
                                struct individual* indi = search_individual(indi_head);
                                if(indi == NULL)
                                {
                                    break;
                                }
                                post_content_individual(indi, str_9);
                                break;
                            case 2:
                                printf("Search business by :\n");
                                struct business* busi = search_business(busi_head);
                                if(busi == NULL)
                                {
                                    break;
                                }
                                post_content_business(busi, str_9);
                                break;
                            case 3:
                                printf("Search organisation by :\n");
                                struct organisation* org = search_organisation(org_head);
                                if(org == NULL)
                                {
                                    break;
                                }
                                post_content_organisation(org, str_9);
                                break;
                            case 4:
                                printf("Search group by :\n");
                                struct group* grp = search_group(group_head);
                                if(grp == NULL)
                                {
                                    break;
                                }
                                post_content_group(grp, str_9);
                                break;
                            default:
                                printf("Invalid choice\n");
                                break;
                        }
                        break;
                    case 2:
                        printf("Search business by :\n");
                        struct business* busi = search_business(busi_head);
                        if(busi == NULL)
                        {
                            break;
                        }
                        printf("Enter the content number : ");
                        scanf("%d", &n);
                        str = find_post(n, busi->busi->contents);
                        if(str == NULL)
                        {
                            break;
                        }

                        printf("To repost content to :\n");
                        printf("1. Individual\n2. Business\n3. Organisation\n4. Group\n");
                        printf("Enter your choice : ");
                        scanf("%d", &choice91);
                        switch(choice91)
                        {
                            case 1:
                                printf("Search individual by :\n");
                                struct individual* indi = search_individual(indi_head);
                                if(indi == NULL)
                                {
                                    break;
                                }
                                post_content_individual(indi, str_9);
                                break;
                            case 2:
                                printf("Search business by :\n");
                                struct business* busi = search_business(busi_head);
                                if(busi == NULL)
                                {
                                    break;
                                }
                                post_content_business(busi, str_9);
                                break;
                            case 3:
                                printf("Search organisation by :\n");
                                struct organisation* org = search_organisation(org_head);
                                if(org == NULL)
                                {
                                    break;
                                }
                                post_content_organisation(org, str_9);
                                break;
                            case 4:
                                printf("Search group by :\n");
                                struct group* grp = search_group(group_head);
                                if(grp == NULL)
                                {
                                    break;
                                }
                                post_content_group(grp, str_9);
                                break;
                            default:
                                printf("Invalid choice\n");
                                break;
                        }
                        break;
                    case 3:
                        printf("Search organisation by :\n");
                        struct organisation* org = search_organisation(org_head);
                        if(org == NULL)
                        {
                            break;
                        }
                        printf("Enter the content number : ");
                        scanf("%d", &n);
                        str = find_post(n, org->org->contents);
                        if(str == NULL)
                        {
                            break;
                        }

                        printf("To repost content to :\n");
                        printf("1. Individual\n2. Business\n3. Organisation\n4. Group\n");
                        printf("Enter your choice : ");
                        scanf("%d", &choice91);
                        switch(choice91)
                        {
                            case 1:
                                printf("Search individual by :\n");
                                struct individual* indi = search_individual(indi_head);
                                if(indi == NULL)
                                {
                                    break;
                                }
                                post_content_individual(indi, str_9);
                                break;
                            case 2:
                                printf("Search business by :\n");
                                struct business* busi = search_business(busi_head);
                                if(busi == NULL)
                                {
                                    break;
                                }
                                post_content_business(busi, str_9);
                                break;
                            case 3:
                                printf("Search organisation by :\n");
                                struct organisation* org = search_organisation(org_head);
                                if(org == NULL)
                                {
                                    break;
                                }
                                post_content_organisation(org, str_9);
                                break;
                            case 4:
                                printf("Search group by :\n");
                                struct group* grp = search_group(group_head);
                                if(grp == NULL)
                                {
                                    break;
                                }
                                post_content_group(grp, str_9);
                                break;
                            default:
                                printf("Invalid choice\n");
                                break;
                        }
                        break;
                    case 4:
                        printf("Search group by :\n");
                        struct group* grp = search_group(group_head);
                        if(grp == NULL)
                        {
                            break;
                        }
                        printf("Enter the content number : ");
                        scanf("%d", &n);
                        str = find_post(n, grp->grp->contents);
                        if(str == NULL)
                        {
                            break;
                        }

                        printf("To repost content to :\n");
                        printf("1. Individual\n2. Business\n3. Organisation\n4. Group\n");
                        printf("Enter your choice : ");
                        scanf("%d", &choice91);
                        switch(choice91)
                        {
                            case 1:
                                printf("Search individual by :\n");
                                struct individual* indi = search_individual(indi_head);
                                if(indi == NULL)
                                {
                                    break;
                                }
                                post_content_individual(indi, str_9);
                                break;
                            case 2:
                                printf("Search business by :\n");
                                struct business* busi = search_business(busi_head);
                                if(busi == NULL)
                                {
                                    break;
                                }
                                post_content_business(busi, str_9);
                                break;
                            case 3:
                                printf("Search organisation by :\n");
                                struct organisation* org = search_organisation(org_head);
                                if(org == NULL)
                                {
                                    break;
                                }
                                post_content_organisation(org, str_9);
                                break;
                            case 4:
                                printf("Search group by :\n");
                                struct group* grp = search_group(group_head);
                                if(grp == NULL)
                                {
                                    break;
                                }
                                post_content_group(grp, str_9);
                                break;
                            default:
                                printf("Invalid choice\n");
                                break;
                        }
                        break;
                    default:
                        printf("Invalid choice\n");
                        break;
                }
                break;
            case 10:
                printf("1. Individual\n2. Business\n3. Organisation\n4. Group\n");
                printf("Enter your choice : ");
                int choice10;
                scanf("%d", &choice10);
                switch(choice10)
                {
                    case 1:
                        printf("Search individual by :\n");
                        struct individual* indi = search_individual(indi_head);
                        if(indi == NULL)
                        {
                            break;
                        }
                        print_str_link(indi->ind->contents);
                        break;
                    case 2:
                        printf("Search business by :\n");
                        struct business* busi = search_business(busi_head);
                        if(busi == NULL)
                        {
                            break;
                        }
                        print_str_link(busi->busi->contents);
                        break;
                    case 3:
                        printf("Search organisation by :\n");
                        struct organisation* org = search_organisation(org_head);
                        if(org == NULL)
                        {
                            break;
                        }
                        print_str_link(org->org->contents);
                        break;
                    case 4:
                        printf("Search group by :\n");
                        struct group* grp = search_group(group_head);
                        if(grp == NULL)
                        {
                            break;
                        }
                        print_str_link(grp->grp->contents);
                        break;
                    default:
                        printf("Invalid choice\n");
                        break;
                }
                break;
            case 11:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");
                break;
        }
        printf("\n");
    }
}



int main()
{
    // freopen("input.txt", "r", stdin);

    // freopen("output.txt", "w", stdout);
    
    social();
    return 0;
}
