#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char word[25];
    struct node* left;
    struct node* right;
} Node;

typedef struct
{
    Node* root;
} BST;

void newTree(BST *x)
{

    x->root=NULL;
}

Node *newNode(char *value)
{
    Node* n=malloc(sizeof(Node));
    strcpy(n->word,value);
    n->left=NULL;
    n->right=NULL;
}

Node* insertNode(Node*x,char* value)
{
    if(x==NULL)
        return newNode(value);
    if(strcasecmp(x->word,value)>0)
        x->left=insertNode(x->left,value);
    else if(strcasecmp(x->word,value)<0)
        x->right=insertNode(x->right,value);
}

Node* searchNode(Node*x,char *value)
{
    Node *n = x;
    Node *next=NULL;
    while (n!=NULL)
    {
        if(strcasecmp(n->word,value)==0)
            return n;
        else if (strcasecmp(value,n->word)<0)
        {
            next =n;
            n=n->left;
        }
        else
        {
            next =n;
            n=n->right;
        }
    }
    return next;
}

int maxheight (int x, int y)
{
    if(x>y)
        return x;
    else
        return y;
}
int height(Node *root)
{
    if(root==NULL)
        return -1;
    else
        return 1+maxheight(height(root->left),height(root->right));
}
Node *minimum(Node*root)
{
    if(root==NULL)
        return NULL;
    else if(root->left==NULL)
        return root;
    else
        return minimum(root->left);
}
Node *maximum(Node*root)
{
    if(root==NULL)
        return NULL;
    else if(root->right==NULL)
        return root;
    else
        return maximum(root->right);
}
int size(Node*n)
{
    if(n==NULL)
        return 0;

    return size(n->left) + size(n->right) + 1;
}


char*Succesor(Node*root,Node*value)
{
    Node*t=root;
    Node*temp=NULL;

    if (value->right!=NULL)
    {
        temp=minimum(root->right);
        return temp->word;
    }
    else
    {
        while(strcasecmp(t->word,value->word)!=0)
        {
            if(strcasecmp(value->word,t->word)<0 || strcasecmp(t->word,value->word)==0)
            {
                temp = t;
                t=t->left;
            }
            else if(strcasecmp(value->word,t->word)>0)
                t=t->right;
        }
        return temp->word;
    }

}
char*predecessor(Node*root,Node*value)
{
    Node*t=root;
    Node*temp=NULL;

    if (value->right!=NULL)
    {
        temp=maximum(root->right);
        return temp->word;
    }
    else
    {
        while(strcasecmp(t->word,value->word)!=0)
        {
            if(strcasecmp(value->word,t->word)>0)
            {
                temp = t;
                t=t->right;
            }
            else if(strcasecmp(value->word,t->word)<0 || strcasecmp(t->word,value->word)==0)
                t=t->left;
        }
        return temp->word;
    }

}

void printWords (BST tree)
{
    Node * peep = tree.root;

    char sentence[250];
    gets(sentence);
    char *temp2;
    temp2 = strtok(sentence," ");

    while(temp2 != NULL)
    {

        Node *result = searchNode(tree.root,temp2);
        if(strcasecmp(result->word,temp2)==0)
            printf("%s - CORRECT\n",result->word);
        else
        {

            printf("%s - Incorrect, Suggestions : %s,%s,%s\n",temp2,result->word,predecessor(peep,result),Succesor(peep,result));

        }
        temp2 = strtok(NULL," ");
    }

}

int main()
{
    FILE *f;
    f=fopen("EN-US-Dictionary.txt","r");
    BST tree;
    newTree(&tree);
    char temp[30];
    if(f!=NULL)
    {

        while(!feof(f))
        {

            fscanf(f,"%s\n",temp);

            tree.root = insertNode(tree.root,temp);

        }
    }
    printf("Dictionary Loaded Successfully....!\n");
    printf("...................................\n");
    printf("Size of Tree = %d\n",size(tree.root));
    printf("...................................\n");
    printf("Height of Tree = %d\n",height(tree.root));
    printf("...................................\n");

    printf("Enter a Sentence: ");
    printWords(tree);
    return 0;
}
