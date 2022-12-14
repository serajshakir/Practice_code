#include <stdio.h>
#include <stdlib.h>
 
// Define the character size
#define CHAR_SIZE 26
 
// Data structure to store a Trie node
struct Trie
{
    int isLeaf;             // 1 when the node is a leaf node
    struct Trie* character[CHAR_SIZE];
};
 
// Function that returns a new Trie node
struct Trie* getNewTrieNode()
{
    struct Trie* node = (struct Trie*)malloc(sizeof(struct Trie));
    node->isLeaf = 0;
 
    for (int i = 0; i < CHAR_SIZE; i++) {
        node->character[i] = NULL;
    }
 
    return node;
}
 
// Iterative function to insert a string into a Trie
void insert(struct Trie *head, char* str)
{
    // start from the root node
    struct Trie* curr = head;
    while (*str)
    {
        // create a new node if the path doesn't exist
        if (curr->character[*str - 'a'] == NULL) {
            curr->character[*str - 'a'] = getNewTrieNode();
        }
 
        // go to the next node
        curr = curr->character[*str - 'a'];
 
        // move to the next character
        str++;
    }
 
    // mark the current node as a leaf
    curr->isLeaf = 1;
}
 
// Iterative function to search a string in a Trie. It returns 1
// if the string is found in the Trie; otherwise, it returns 0.
int search(struct Trie* head, char* str)
{
    // return 0 if Trie is empty
    if (head == NULL) {
        return 0;
    }
 
    struct Trie* curr = head;
    while (*str)
    {
        // go to the next node
        curr = curr->character[*str - 'a'];
 
        // if the string is invalid (reached end of a path in the Trie)
        if (curr == NULL) {
            return 0;
        }
 
        // move to the next character
        str++;
    }
 
    // return 1 if the current node is a leaf and the
    // end of the string is reached
    return curr->isLeaf;
}
 
// Returns 1 if a given Trie node has any children
int hasChildren(struct Trie* curr)
{
    for (int i = 0; i < CHAR_SIZE; i++)
    {
        if (curr->character[i]) {
            return 1;       // child found
        }
    }
 
    return 0;
}
 
// Recursive function to delete a string from a Trie
int deletion(struct Trie **curr, char* str)
{
    // return 0 if Trie is empty
    if (*curr == NULL) {
        return 0;
    }
 
    // if the end of the string is not reached
    if (*str)
    {
        // recur for the node corresponding to the next character in
        // the string and if it returns 1, delete the current node
        // (if it is non-leaf)
        if (*curr != NULL && (*curr)->character[*str - 'a'] != NULL &&
            deletion(&((*curr)->character[*str - 'a']), str + 1) &&
            (*curr)->isLeaf == 0)
        {
            if (!hasChildren(*curr))
            {
                free(*curr);
                (*curr) = NULL;
                return 1;
            }
            else {
                return 0;
            }
        }
    }
 
    // if the end of the string is reached
    if (*str == '\0' && (*curr)->isLeaf)
    {
        // if the current node is a leaf node and doesn't have any children
        if (!hasChildren(*curr))
        {
            free(*curr);    // delete the current node
            (*curr) = NULL;
            return 1;       // delete the non-leaf parent nodes
        }
 
        // if the current node is a leaf node and has children
        else {
            // mark the current node as a non-leaf node (DON'T DELETE IT)
            (*curr)->isLeaf = 0;
            return 0;       // don't delete its parent nodes
        }
    }
 
    return 0;
}
 
// Trie implementation in C ??? Insertion, Searching, and Deletion
int main()
{
    struct Trie* head = getNewTrieNode();

	insert(head, "hello");
        printf("in hello sr hello then %d \n", search(head,"hello"));

        insert(head, "helloworld");
        printf("in helloworld sr helloworld then %d \n", search(head,"helloworld"));


        printf("in \"  \" sr helll then %d \n", search(head,"helll"));

        insert(head, "hell");
        printf("in hell sr hell then %d \n", search(head,"hell"));

        insert(head, "hello");
        printf("in hello sr hello then %d \n", search(head,"hello"));
        printf("in hello sr helloworld then %d \n", search(head,"helloworld"));
        printf("in hello sr hell  then %d \n", search(head,"hell"));
        printf("in hello sr helll then %d \n", search(head,"helll"));

        printf("in \" \" sr h then %d \n", search(head,"h"));
        insert(head, "h");
        printf("in h sr h then %d \n", search(head,"h"));

        printf("in \" \" sr hel then %d \n", search(head,"hel"));
 
    insert(head, "hello");
    printf("%d ", search(head, "hello"));       // print 1
 
    insert(head, "helloworld");
    printf("%d ", search(head, "helloworld"));  // print 1
 
    printf("%d ", search(head, "helll"));       // print 0 (Not present)
 
    insert(head, "hell");
    printf("%d ", search(head, "hell"));        // print 1
 
    insert(head, "h");
    printf("%d \n", search(head, "h"));         // print 1 + newline
 
    deletion(&head, "hello");
    printf("%d ", search(head, "hello"));       // print 0 (hello deleted)
    printf("%d ", search(head, "helloworld"));  // print 1
    printf("%d \n", search(head, "hell"));      // print 1 + newline
 
    deletion(&head, "h");
    printf("%d ", search(head, "h"));           // print 0 (h deleted)
    printf("%d ", search(head, "hell"));        // print 1
    printf("%d\n", search(head, "helloworld")); // print 1 + newline
 
    deletion(&head, "helloworld");
    printf("%d ", search(head, "helloworld"));  // print 0
    printf("%d ", search(head, "hell"));        // print 1
 
    deletion(&head, "hell");
    printf("%d\n", search(head, "hell"));       // print 0 + newline
 
    if (head == NULL) {
        printf("Trie empty!!\n");               // Trie is empty now
    }
 
    printf("%d ", search(head, "hell"));        // print 0
 
    return 0;
}

