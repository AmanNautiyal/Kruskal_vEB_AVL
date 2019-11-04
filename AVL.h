#include "MyHeaders.h"
using namespace std;
class AVL
{
private:
    struct avlnode
    {
    public:
        ll value;
     avlnode *left, *right;
        ll height;
    }*head;
public :
AVL()
{
    head=NULL;
}
// avlnode* create_avlnode();
// avlnode* insert_node(avlnode *root, ll value);
// avlnode* right_rotate(avlnode *k2);
// avlnode *left_rotate(avlnode *k2);
// avlnode *left_right_rotate(avlnode *k2);
// avlnode *right_left_rotate(avlnode *k2);
// avlnode* delete_node(avlnode *root, ll value);
// void find_closest(avlnode *root, ll value);
// ll find_cl(ll x);
// void klargest(avlnode *root);
// ll find_klargest(avlnode *root, ll num);
ll d,n,klar,k;
avlnode* create_avlnode(ll value)
{
    avlnode* newnode=new avlnode;
    newnode->left=NULL;
    newnode->right=NULL;
    newnode->value=value;
    newnode->height=1;
    return newnode;
}
ll height(avlnode *root)
{
    if(root==NULL)
        return 0;
    else
        return root->height;
}
ll balance_factor(avlnode* root)
{
    if(root==NULL)
        return 0;
    else
        return height(root->left)-height(root->right);
}
void insert(ll value)
{
    head=insert_node(head,value);
}
void del(ll value)
{
    head=delete_node(head,value);
}
avlnode* insert_node(avlnode *root, ll value)
{
    //bst insertion
    if(root==NULL)
    {
        return create_avlnode(value); // create new node
    }
    if(value<root->value)
        root->left=insert_node(root->left,value); // recursive call to insert at left subtree
    else if(value>root->value)
        root->right=insert_node(root->right,value);// recursive call to insert at right subtree
    else
    {
        cout<<"Value already present in tree\n"; // no duplicate values in set
        return root;
    }
    //bst insertion
    ll l=height(root->left),r=height(root->right);
    root->height=l>r?l+1:r+1; // adjusting root's height
    ll bal_fact=balance_factor(root);
    //cout<<root->value<<"\t"<<bal_fact<<endl;
    if(bal_fact> 1 || bal_fact<-1) // needs readjustment
    {
        if(bal_fact>1 && value<root->left->value)
            root=right_rotate(root);
        else if(bal_fact>1 && value>root->left->value)
            root=left_right_rotate(root);
        else if(bal_fact<1 && value>root->right->value)
            root=left_rotate(root);
        else if(bal_fact<1 && value<root->right->value)
            root=right_left_rotate(root);
    }
    return root; // return readjusted root
}
avlnode* delete_node(avlnode *root, ll value)
{
    // bst deletion
    //cout<<root->value<<endl;
   if(root==NULL)
    {
        cout<<"Key not present in tree\n";
        return NULL;// create new node
    }
    if(value<root->value)
        root->left=delete_node(root->left,value); // recursive call to delete at left subtree
    else if(value>root->value)
        root->right=delete_node(root->right,value);// recursive call to delete at right subtree
    else
    {
            // node found and has to be deleted
            if(root->left==NULL && root->right==NULL) // no children
             {
                avlnode* temp=root;
                root=NULL;
                delete(temp);
             }
            else if(root->left!=NULL && root->right!=NULL) //internal node with both children
            {
                avlnode *successor=root->right;
                while(successor->left!=NULL)
                 successor =successor->left;
                root->value=successor->value;
                root->right=delete_node(root->right,successor->value); // delete successor from the right subtree          
            }
            else if(root->left==NULL)
            {
                avlnode* temp=root;
                delete(temp);
                root=root->right;
            }
            else if(root->right==NULL)
            {
                avlnode* temp=root;
                delete(temp);
                root=root->left;
            }

    }
    //bst deletion
    if(root==NULL)
        return root; // deleted node was the last in the tree
    ll l=height(root->left),r=height(root->right);
    root->height=l>r?l+1:r+1; // adjusting root's height
    ll bal_fact=balance_factor(root);
    //cout<<root->value<<"\t"<<bal_fact<<endl;
    ll bal_fact_l=balance_factor(root->left); // balance factor of left child
   // cout<<"Here\n";
    ll bal_fact_r=balance_factor(root->right); // balance factor of right child
    if(bal_fact> 1 || bal_fact<-1) // needs readjustment
    {
        if(bal_fact>1 && bal_fact_l>1)
            root=right_rotate(root);
        else if(bal_fact>1 && bal_fact_l<1)
            root=left_right_rotate(root);
        else if(bal_fact<1 && bal_fact_r<1)
            root=left_rotate(root);
        else if(bal_fact<1 && bal_fact_r>1)
            root=right_left_rotate(root);
    }
    return root; // return readjusted root
}
avlnode* right_rotate(avlnode *k2)
{

    avlnode *k1=k2->left;
    avlnode *x=k1->left;
    avlnode *y=k1->right;
    avlnode *z=k2->right;
    // rotating
    k2->left=y;
    k1->right=k2;
    k2->height=k2->height-2;
    return k1;
}
avlnode *left_rotate(avlnode *k2)
{
    avlnode *k1=k2->right;
    avlnode *x=k1->right;
    avlnode *y = k1->left;
    avlnode *z=k2->left;
    // rotating
    k2->right=y;
    k1->left=k2;
    if(k2!=NULL) k2->height=k2->height-2;
    return k1;
}
avlnode *left_right_rotate(avlnode *k2)
{
    avlnode *k1=k2->left;
    avlnode *x=k1->left;
    avlnode *k3=k1->right;
    avlnode *y1=k3->left;
    avlnode *y2=k3->right;
    avlnode *z=k2->right;
    // rotation
    k3->left=k1;
    k3->right=k2;
    k1->left=x;
    k1->right=y1;
    k2->left=y2;
    k2->right=z;
    if(k1!=NULL) k1->height=k1->height-1;
    if(k2!=NULL) k2->height=k2->height-2;
    if(k3!=NULL) k3->height=k3->height+1;
    return k3;
}
avlnode *right_left_rotate(avlnode *k2)
{
    avlnode *k1=k2->right;
    avlnode *x=k2->left;
    avlnode *k3=k1->left;
    avlnode *y1=k3->left;
    avlnode *y2=k3->right;
    avlnode *z=k1->right;
    // rotation
    k3->left=k2;
    k3->right=k1;
    k1->left=y2;
    k1->right=z;
    k2->left=x;
    k2->right=y1;
    if(k1!=NULL) k1->height=k1->height-1;
    if(k2!=NULL) k2->height=k2->height-2;
    if(k3!=NULL) k3->height=k3->height+1;
    return k3;
}
// void display(avlnode *root)
// {
//     if(root==NULL)
//         return;
//     cout<<root->value<<endl;
//     display(root->left);
//     display(root->right);
// }
// bool find_value(avlnode* root,ll x)
// {
//     if(root==NULL)
//         return false;
//     if(root->value==x)
//         return true;
//     else if(root->value>x)
//         return find_value(root->left,x);
//     else
//         return find_value(root->right,x);
// }
// void find_closest(avlnode *root, ll value)
// {
//     if(root==NULL)
//         return;
//     if(abs(root->value-value)<=d)
//     {
//         d=abs(root->value-value);
//         if(n>root->value)
//             n=root->value;
//     }
//     if(root->value<value)
//         find_closest(root->right,value);
//     else
//         find_closest(root->left,value);
//     //if root->value== value, no recursion
// }
// ll find_cl(avlnode *root,ll x)
// {
//     d=LLONG_MAX;
//     n=LLONG_MAX;
//     find_closest(root,x);
//     return n;
// }
ll minval()
{
    return findmin(head);
}
bool isempty()
{
    if(head==NULL)
        return true;
    else
        return false;
}
ll findmin(avlnode* root)
{
    if(root->left==NULL)
        return root->value;
    else
        return findmin(root->left);
}
// void klargest(avlnode *root)
// {
//     if(root->right!=NULL)
//         klargest(root->right);
//     if(k==0)
//         return;
//     k=k-1;
//     klar=root->value;
//     //cout<<klar<<endl;
//     if(root->left!=NULL)
//     klargest(root->left);
// }
// ll find_klargest(avlnode *root, ll num)
// {
//     k=num;
//     klargest(root);
//     return klar;
// }
// ll count_range(avlnode *root,ll l, ll r )
// {
//     if(root->value>=l && root->value<=r)
//     {
//         ll x=1;
//         if(root->left!=NULL)
//             x+=count_range(root->left,l,r);
//          if(root->right!=NULL)
//             x+=count_range(root->right,l,r);
//         return x;
//     }
//     else if(root->left!=NULL && root->value>r)
//         return count_range(root->left,l,r);
//     else if(root->right!=NULL && root->value<l)
//         return count_range(root->right,l,r);
// }
// int main()
// {
//     avlnode *root;
//     root=insert_node(root,32);
//     root=insert_node(root,423);
//     root=insert_node(root,53);
//     root=insert_node(root,64);
//     root=insert_node(root,98);
//     root=insert_node(root,1);
//     root=insert_node(root,34);
//     root=delete_node(root,32);
//     root=delete_node(root,423);
//     root=delete_node(root,53);
//     root=delete_node(root,64);
//     root=delete_node(root,98);
//     display(root);
//     return 0;
// }
};