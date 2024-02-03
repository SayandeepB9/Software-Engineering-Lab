/*
    This file contain the implementation of the social network.
    All the entities and their corresponding functions are defined here.

    The structure of the whole social network :-

    The structure contains four entities :- individuals, organisations,
                                            businesses, groups

    Now for every entity, to store them properly and for properly
    handling them, we define linked lists.
    They have the functionalities of add, search (by different ways), delete
    in them. Note we define only add_to_head because the order does not matter here.

    The linked lists also allow us to handle the linking operations in a elegant
    way.

    The links (along with their corresponding functions) present in the codebase are :-
    Individual---->Business  Business---->Individuals
    Individual---->Organisation  Organisation---->Individuals
    Individual---->Group  Group---->Individuals
    Business---->Group  Group---->Business
    The undirected links are implemented as two opposite directed links.
    We define functions to add, delete and print the links.

    We also use test functions to test the code for proper behaviour. This
    helps us test the code module by module. The modular framework used
    makes debugging simpler. The test entities function can be used to test
    the entities and the test links function can be used to test the links
    between the entities. 

    We also define custom date and location format which are used in the code.
    The date format is dd/mm/yyyy and the location format is (x, y). They have
    their corresponding functions as well.

    Contents posted by an user is also stored in a linked list. This allows us
    to add, delete and print the contents easily. We also define functions to
    post contents and delete contents for the various entities. We also allow
    entities to repost contents of other entities. This is done by simply adding
    the content strings pointer to the contents linked list of the entity. This
    prevents us from storing the same content multiple times.

    We have a wide range of search functions which allow us to search for an
    entity by its unique id, name, birth date, location, etc. This makes the
    code more user friendly.

    The linked lists of the entities are initialised with null values at the 
    beginning in the social function. These are the main heads which point to
    all the entities added. The social function is the driver function which
    calls all the other functions. We support various operations like :-

    1. Create and delete nodes of each type - individual, organization, business, group. 
    2. Search for nodes using the name or type or birthday.
    3. Print all 1-hop linked nodes to a given input node.
    4. Create and post content by a node.
    5. Search for content posted by any node.
    6. Display all content posted by individuals linked to a given individual. Here an
       individual is linked to another individual if they have a common group or
       organization - This part has a special feature implemented to prevent the same
       individual from being printed multiple times. This is done by maintaining a
       visited array of unique ids of the individuals. This does a thing similar to
       the DFS cycle prevention technique.
    7. Create and delete links between entities
    8. Search substring in content
    9. Repost content
    10. Print contents
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



// The date structure
struct date{
    int dd, mm, yyyy;
};

// Takes the date as input from the user and returns a pointer to the same
struct date* new_date();

// Returns the current date of the system
struct date* current_date();



// The location in x and y coordinates 
struct Location2D{
    int x;
    int y;
};

// Takes from the user the x and y coordinates of the location and creates a structure
// of the same. Returns a pointer to the structure
struct Location2D* new_Location2D();



/*
    This part contains the definition of various important structures used in the code.
    It contains functions to input strings of proper length and also implements a linked
    list of strings which helps us maintain posts of the various entities.
*/

// Linked list of strings
struct string_link{
    char* str;
    struct string_link* next;
};

// Takes a string as input and returns a pointer to the same
char* new_str();

// Used to get a copy of a string
char* cpy_str(char*);

// Creates a new node for the string linked list
struct string_link* create_str_link(char*);

// This creates a node and adds a given string to the head of the
// string linked list
struct string_link* add_str_link_to_head(struct string_link*, char*);

// This deletes a node from the string linked list
struct string_link* delete_str_link(char*, struct string_link*);

// This deletes a post from the string linked list
struct string_link* delete_post(int, struct string_link*);

// This finds the nth post in the string linked list
char* find_post(int, struct string_link*);

// This returns a str_link of all strings containing a substring
struct string_link* find_str_link(char*, struct string_link*);

// Prints all the strings in a string linked list
void print_str_link(struct string_link*);

// This function is used to test the functions defined above
void test_str_link();



// This is the basic information which is common for all the entities
struct node
{
    int unique_id;
    char *name;
    struct date *creation_date;
    struct string_link *contents;
};

// Creates a new node
struct node *new_node(int);



// This is the structure of an individual with all the information
// as mentioned in the problem statement
struct individual
{
    struct node *ind;
    struct date *b_day;
    struct busi_link *owner;
    struct busi_link *customer;
    struct org_link *org_link;
    struct group_link *grp_link;
};

// Creates a new individual
struct individual *new_individual(int);

// This is the structure of linked list of individuals
struct indi_link
{
    struct individual *indi;
    struct indi_link *next;
};

// Creates a new node for the individual linked list
struct indi_link *new_indi_link(struct individual *);

// Adds a node to the head of the individual linked list
struct indi_link *add_indi_link_to_head(struct indi_link *, struct individual *);

// Deletes a node from the individual linked list
struct indi_link *delete_indi_link(struct individual *, struct indi_link *);

// Searches for an individual by its unique id in the individual linked list
struct individual *search_individual_by_unique_id(int , struct indi_link *);

// Searches for an individual by its name in the individual linked list
struct individual *search_individual_by_name(char*, struct indi_link *);

// Searches for an individual by its birth date in the individual linked list
struct individual *search_individual_by_birth_date(struct date *, struct indi_link *);

// Searches for an individual in the individual linked list
struct individual *search_individual(struct indi_link *);

// Searches for an individual by its pointer in the individual linked list
// and returns 1 if found
int search_individual_pointer(struct indi_link *, struct individual *);

// Deletes an individual from the individual linked list. This also deletes
// all the links of the individual
struct indi_link *delete_individual(struct indi_link *);

// Prints the individual linked list
void print_indi_link(struct indi_link *, struct individual *);



// This is the structure of an organisation with all the information
// as mentioned in the problem statement
struct organisation
{
    struct node *org;
    struct Location2D *loc;
    struct indi_link *indi_link;
};

// Creates a new organisation
struct organisation *new_organisation(int);

// This is the structure of linked list of organisations
struct org_link
{
    struct organisation *org;
    struct org_link *next;
};

// Creates a new node for the organisation linked list
struct org_link *new_org_link(struct organisation *);

// Adds a node to the head of the organisation linked list
struct org_link *add_org_link_to_head(struct org_link *, struct organisation *);

// Deletes a node from the organisation linked list
struct org_link *delete_org_link(struct organisation *, struct org_link *);

// Searches for an organisation by its unique id in the organisation linked list
struct organisation *search_organisation_by_unique_id(int, struct org_link *);

// Searches for an organisation by its name in the organisation linked list
struct organisation *search_organisation_by_name(char*, struct org_link *);

// Searches for an organisation in the organisation linked list
struct organisation *search_organisation(struct org_link *);

// Searches for an organisation by its pointer in the organisation linked list
// and returns 1 if found
int search_organisation_pointer(struct org_link *, struct organisation *);

// Deletes an organisation from the organisation linked list. This also deletes
// all the links of the organisation
struct org_link *delete_organisation(struct org_link *);

// Prints the organisation linked list
void print_org_link(struct org_link *, struct organisation *);



// This is the structure of a business with all the information
// as mentioned in the problem statement
struct business
{
    struct node *busi;
    struct Location2D *loc;
    struct indi_link *owners;
    struct indi_link *customers;
    struct group_link *grp_link;
};

// Creates a new business
struct business *new_business(int );

// This is the structure of linked list of businesses
struct busi_link
{
    struct business *busi;
    struct busi_link *next;
};

// Creates a new node for the business linked list
struct busi_link *new_busi_link(struct business *);

// Adds a node to the head of the business linked list
struct busi_link *add_busi_link_to_head(struct busi_link *, struct business *);

// Deletes a node from the business linked list
struct busi_link *delete_busi_link(struct business *, struct busi_link *);

// Searches for a business by its unique id in the business linked list
struct business *search_business_by_unique_id(int , struct busi_link *);

// Searches for a business by its name in the business linked list
struct business *search_business_by_name(char*, struct busi_link *);

// Searches for a business in the business linked list
struct business *search_business(struct busi_link *);

// Searches for a business by its pointer in the business linked list
// and returns 1 if found
int search_business_pointer(struct busi_link *, struct business *);

// Deletes a business from the business linked list. This also deletes
// all the links of the business
struct busi_link *delete_business(struct busi_link *);

// Prints the business linked list
void print_busi_link(struct busi_link *, struct business *);



// This is the structure of a group with all the information
// as mentioned in the problem statement
struct group
{
    struct node *grp;
    struct indi_link *indi_link;
    struct busi_link *busi_link;
};

// Creates a new group
struct group *new_group(int);

// This is the structure of linked list of groups
struct group_link
{
    struct group *grp;
    struct group_link *next;
};

// Creates a new node for the group linked list
struct group_link *new_group_link(struct group *);

// Adds a node to the head of the group linked list
struct group_link *add_group_link_to_head(struct group_link *, struct group *);

// Deletes a node from the group linked list
struct group_link *delete_group_link(struct group *, struct group_link *);

// Searches for a group by its unique id in the group linked list
struct group *search_group_by_unique_id(int, struct group_link *);

// Searches for a group by its name in the group linked list
struct group *search_group_by_name(char*, struct group_link *);

// Searches for a group in the group linked list
struct group *search_group(struct group_link *);

// Searches for a group by its pointer in the group linked list
// and returns 1 if found
int search_group_pointer(struct group_link *, struct group *);

// Deletes a group from the group linked list. This also deletes
// all the links of the group
struct group_link *delete_group(struct group_link *);

// Prints the group linked list
void print_group_link(struct group_link *head, struct group *);



// This can be used to test all the functions specified for an individual
void test_indi_link();

// This can be used to test all the functions specified for an organisation
void test_org_link();

// This can be used to test all the functions specified for a business
void test_busi_link();

// This can be used to test all the functions specified for a group
void test_group_link();

// This can be used to test all the functions specified for all the entities
void test_entities();



// This can be used to create a link between an individual and a group
void add_indi_to_group(struct group_link *, struct indi_link *);

// This can be used to delete a link between an individual and a group
void delete_indi_from_group(struct group_link *, struct indi_link *);

// This can be used to print all the individuals in a group
void print_indi_in_group(struct group* );

// This can be used to print all the groups of an individual
void print_groups_of_indi(struct individual* );



// This can be used to create a link between a business and a group
void add_busi_to_group(struct group_link *, struct busi_link *);

// This can be used to delete a link between a business and a group
void delete_busi_from_group(struct group_link *, struct busi_link *);

// This can be used to print all the businesses in a group
void print_busi_in_group(struct group* );

// This can be used to print all the groups of a business
void print_groups_of_busi(struct business* );



// This can be used to create a link between an owner individual and a business
void add_indi_owner_to_busi(struct busi_link *, struct indi_link *);

// This can be used to delete a link between an owner individual and a business
void delete_indi_owner_from_busi(struct busi_link *, struct indi_link *);

// This can be used to print all the owner individuals in a business
void print_indi_owner_in_busi(struct business* );

// This can be used to print all the businesses owned by an individual
void print_busi_owned_by_indi(struct individual* );



// This can be used to create a link between a customer individual and a business
void add_indi_customer_to_busi(struct busi_link *, struct indi_link *);

// This can be used to delete a link between a customer individual and a business
void delete_indi_customer_from_busi(struct busi_link *, struct indi_link *);

// This can be used to print all the customer individuals in a business
void print_indi_customer_in_busi(struct business* );

// This can be used to print all the businesses of an individual customer
void print_indi_customer_of_busi(struct individual* );



// This can be used to create a link between an individual and an organisation
void add_indi_to_org(struct org_link *, struct indi_link *);

// This can be used to delete a link between an individual and an organisation
void delete_indi_from_org(struct org_link *, struct indi_link *);

// This can be used to print all the individuals in an organisation
void print_indi_in_org(struct organisation* );

// This can be used to print all the organisations of an individual
void print_org_of_indi(struct individual* );



// This can be used to post a content from an individual
void post_content_individual(struct individual *, char *);

// This can be used to post a content from a group
void post_content_group(struct group *, char *);

// This can be used to post a content from a business
void post_content_business(struct business *, char *);

// This can be used to post a content from an organisation
void post_content_organisation(struct organisation *, char *);

// This can be used to delete a content from an individual
void delete_content_individual(struct individual *);

// This can be used to delete a content from a group
void delete_content_group(struct group *);

// This can be used to delete a content from a business
void delete_content_business(struct business *);

// This can be used to delete a content from an organisation
void delete_content_organisation(struct organisation *);



// This can be used to test the link between an individual and an organisation
void test_ind_org_link();

// This can be used to test the link between an individual and a group
void test_ind_grp_link();

// This can be used to test the link between a business and an individual owner
void test_ind_owner_busi_link();

// This can be used to test the link between a business and an individual customer
void test_indi_customer_busi_link();

// This can be used to test the link between a business and a group
void test_busi_group_link();

// This can be used to test all the links
void test_links();



// 1. Create and delete nodes of each type - individual, organization, business, group. 
// 2. Search for nodes using the name or type or birthday.
// 3. Print all 1-hop linked nodes to a given input node.
// 4. Create and post content by a node.
// 5. Search for content posted by any node.
// 6. Display all content posted by individuals linked to a given individual. Here an
//     individual is linked to another individual if they have a common group or
//     organization - This part has a special feature implemented to prevent the same
//     individual from being printed multiple times. This is done by maintaining a
//     visited array of unique ids of the individuals. This does a thing similar to
//     the DFS cycle prevention technique.
// 7. Create and delete links between entities
// 8. Search substring in content
// 9. Repost content
// 10. Print contents
void social();



// The main function which calls the social funtion
int main();