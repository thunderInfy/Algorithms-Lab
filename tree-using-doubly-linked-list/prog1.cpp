#include<iostream>
using namespace std;
int c=1;
int rrg;
#define hey cout<<'\n'<<"----"<<c<<"----\n";c++;
struct node{
  int key;
  node* left;
  node* right;
};
node* create_node(int data) //creating A node
{
  node *N;
  N = new node;
  N->key=data;
  N->left = NULL;
  N->right=NULL;
  return N;
}
node* left_rotate(node*);
node* right_rotate(node*);
node* insert(node* T,int data)      //inserting
{
  if(T==NULL)
    return create_node(data);
  else if(data < T->key)
    T->left = insert(T->left,data);
  else if(data > T->key)
    T->right = insert(T->right,data);
  else
    return T;
    
}
void print_tree(node *T,int counter=0)  //printing tree
{
  
  if(T!=NULL)
    {
      
      print_tree(T->left,++counter);
      int temp=counter;
      while(temp>0)
	{
	cout<<"    ";
	temp--;
	}
      cout<<T->key;
      print_tree(T->right,++counter);
    }
  else
    cout<<'\n';
}
void flattenleft(node *T)   
{
   if((T->left)!=NULL)
    {
      while(((T->left)->right)!=NULL)
	T->left=left_rotate(T->left);
      
      flattenleft(T->left);
    }
}
void flattenright(node *T)
{
   if((T->right)!=NULL)
    {
      while(((T->right)->left)!=NULL)
	T->right=right_rotate(T->right);
      
      flattenleft(T->right);
    }
}
void print_linked_list(node *root) //printing list
{
  cout<<"\n+++ Linked List\n";
  node *temp=root;
  
  while((temp->right)!=NULL)
    {
    cout<<temp->key<<" ";
    temp=(temp->right);
    }
  cout<<temp->key;
  rrg=temp->key;
  cout<<'\n';
  while((temp->left)!=NULL)
    {
    cout<<temp->key<<" ";
    temp=(temp->left);
    }
  cout<<temp->key;
  cout<<'\n';
  
}
node* tree2list(node* T)    //converting BST to doubly linked list
{
  flattenleft(T);
  flattenright(T);
  node* temp=T;
  node *root;
  cout<<"\n+++ Flattened tree\n";
  print_tree(T);
  while((T->left)!=NULL)
    {
      (T->left)->right=T;
      T=T->left;
    }
  
  root=T;
   T=temp;
  while((T->right)!=NULL)
    {
      (T->right)->left=T;
      T=T->right;
    }
  T=temp;
  print_linked_list(root);
  return root;
}
node* left_rotate(node* T)
{
  node* Z=T->right;
  node* T3=Z->left;
  
  Z->left=T;
  T->right=T3;
 
  return Z;
}
node* right_rotate(node* T)
{
  node* Y=T->left;
  node* T4=Y->right;
  
  Y->right=T;
  T->left=T4;
 
  return Y;
}
node* list2tree(node *start,node *finish=NULL)
{
  if(finish->key == rrg)
    {
      finish->left=NULL;
      finish->right=NULL;
    }
  if(finish==(start->right))//one node
    {
      start->left=NULL;
      start->right=NULL;
     
    return start;
    }
  node* temp=start;
  int n=0;
  while(temp!=finish)
    {
      temp=temp->right;
      ++n;
    }
  
  int righ = (n-1)/2;
  int lef = (n-1) - righ;
  int count=0;
  temp=start;
  while(count!=lef)
    {
      temp=temp->right;
      ++count;
    }
  node* root=temp;
  hey
    cout<<root->key;  
  root->left=list2tree(start,temp);
  root->right=list2tree(temp,finish);
  return root;
}
int main()
{
  int n;
  int i;
  node *T;
  node *start;
  T=NULL;
  int data;
  cin>>n;
  
  for(i=0;i<n;i++)
    {
      cin>>data;
      T=insert(T,data);
    }
  cout<<"\n+++ Initial tree\n";
  print_tree(T);
  start=tree2list(T);
   T=list2tree(start);
  cout<<"\n+++ Balanced tree\n";
  node* temp=T;
  
  while((T)!=NULL)
    T=T->right;
  cout<<"\nREACHED\n";   //here this statement actaully is not reaching which means that T->right is never getting equal to NULL, I checked the code but unable to find why is it getting so
  print_tree(T);
  return 0;
}
