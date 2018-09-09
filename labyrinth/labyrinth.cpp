#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
struct node
{
  int size;
  node * p;
};
void printlabyrinth(int **H,int **V,int m,int n)
{
  int i,j;
  for(i=0;i<n;i++)          //first building the topmost layer
    cout<<"+---";
  cout<<"+";
  cout<<'\n'; 

  for(i=0;i<m-1;i++)
    {
  cout<<"|";
  for(j=0;j<n-1;j++)
    {
      cout<<"   ";
      if(V[i][j]==0)
	cout<<"|";
      else
	cout<<" ";
    }
  cout<<"   |";
  cout<<'\n';                   //printing walls in between if they are not removed
  for(j=0;j<n;j++)
    {
      cout<<"+";
      if(H[i][j]==0)
	cout<<"---";
      else
	cout<<"   ";
    }
  cout<<"+";
  cout<<'\n';
    }
  cout<<"|";
  for(j=0;j<n-1;j++)
    {
      cout<<"   ";
      if(V[i][j]==0)
	cout<<"|";
      else
	cout<<" ";
    }
  cout<<"   |\n";
  for(i=0;i<n;i++)              //building the bottommost layer
    cout<<"+---";
  cout<<"+";
  cout<<'\n';  
  
  
  
}
node** initrooms(node**R,int m,int n)
{
  int i,j;
  
  for(i=0;i<m;i++)
    {
      for(j=0;j<n;j++)
	{
	  R[i][j].size=1;              //initializing size to 1
	  R[i][j].p=&(R[i][j]);        //intializing parent to the same node         
	}
    }
  return R;
}
node* findroot(node **R,int m,int n,int i,int j)
{
  
  node *x;
  x = &R[i][j];
  while(x->p!=x)                      //do this until parent of x is x itself
    x=x->p;
  return x; 
}
void mergeregions(node *x,node *y)
{
  node *child;
  node *parent;
  if(x->size > y->size)             
    {
      child=y;
      parent=x;
    }
  else
    {
      child=x;
      parent=y;
    }
  (child->p)=parent;                 //creating link between child and parent
  (parent->size)+=(child->size);     //updating parent size

}

node** buildlabyrinth(node **R,int **H,int **V,int m,int n)
{
  int c;
  int h1,k1;
  int counter=0;
  node *x;
  node *y;
  while(counter!=(m*n-1))                     //do this until counter gets equal to m*n -1
    {
      c = rand()%2;
      if(c==0) //choose horizontal wall
	{
          h1= rand()%(m-1);
	  k1= rand()%(n);
	  if(H[h1][k1]==1)
	    continue;
	  x = findroot(R,m,n,h1,k1);          //[h1,k1] room
	  y = findroot(R,m,n,h1+1,k1);        //[h1+1,k1] room
	  if(x==y)
	    continue;
	  else
	    {
	      H[h1][k1]=1;
	      mergeregions(x,y);              //merging sets if they are disjoint
	      counter++;
	    }
	  
	}
      else     //choose vertical wall
	{
	  h1= rand()%(m);
	  k1= rand()%(n-1);
	  if(V[h1][k1]==1)
	    continue;
	  x = findroot(R,m,n,h1,k1);         //[h1,k1] room
	  y = findroot(R,m,n,h1,k1+1);       //[h1,k1+1] room
	  if(x==y)
	    continue;
	  else
	    {
	      V[h1][k1]=1;
	      mergeregions(x,y);              //merging sets if they are disjoint
	      counter++;
	    }
	}
    }
  return R;
}

int main()
{
  int m,n;
  cout<<"\nEnter m and n\t";
  cin>>m>>n;

  cout<<"\n m = "<<m;
  cout<<"\n n = "<<n;

  
  node **R;
  int **H,**V;

  srand((unsigned int)time(NULL));

  //Initializing R, H, V
  
  R = (node**)malloc(m*sizeof(node*));
  H = (int**)malloc((m-1)*sizeof(int*));
  V = (int**)malloc(m*sizeof(int*));
  int i,j;
  for(i=0;i<m;i++)
      R[i] = (node*)malloc(n*sizeof(node));
  for(i=0;i<(m-1);i++)
    H[i] = (int*)malloc(n*sizeof(int));
  for(i=0;i<m;i++)
    V[i] = (int*)malloc((n-1)*sizeof(int));


  //calling initrooms
  R=initrooms(R,m,n);

  for(i=0;i<(m-1);i++)
    {
      for(j=0;j<n;j++)
	{
	  H[i][j]=0;
	}
    }
  for(i=0;i<m;i++)
    {
      for(j=0;j<(n-1);j++)
	{
	  V[i][j]=0;
	}
    }
  cout<<"\n+++ Initial labyrinth\n";
  printlabyrinth(H,V,m,n);

  if(m==1 || n==1)                                      //Handling case of m=1 or n=1 separately as they cause the sizes of H or V to be zero
    {
      if(m==1)
	{
	   cout<<"\n+++ Labyrinth created after "<<m*n-1<<" wall removals\n";
           cout<<"\n+++ Final labyrinth\n";
           for(i=0;i<n;i++)          //first building the topmost layer
           cout<<"+---";
           cout<<"+";
           cout<<'\n';

	   cout<<'|';
	   for(i=0;i<n;i++)
	     {
	       cout<<"   ";
	       if(i!=(n-1))
		 cout<<" ";
	     }
	   cout<<"|\n";
	  for(i=0;i<n;i++)          // building the bottommost layer
           cout<<"+---";
           cout<<"+";
           cout<<'\n';
	   return 0;
	}
      else
	{
	   cout<<"\n+++ Labyrinth created after "<<m*n-1<<" wall removals\n";
           cout<<"\n+++ Final labyrinth\n";
	  cout<<"+---+\n";
	  for(i=0;i<m;i++)
	    {
	    cout<<"|   |\n";
	    if(i!=m-1)
	    cout<<"+   +\n";
	    }
	  cout<<"+---+\n";
	  return 0;
	}
    }

  
  //calling build labyrinth
  R=buildlabyrinth(R,H,V,m,n);

  cout<<"\n+++ Labyrinth created after "<<m*n-1<<" wall removals\n";

  
  cout<<"\n+++ Final labyrinth\n";

  
  printlabyrinth(H,V,m,n);

  
  
  return 0;
  
}