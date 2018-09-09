#include<iostream>
#include<cstdlib>
#define disp(A,i1,i2) for(int x=i1;x<i2;x++){cout<<A[x]<<" ";}cout<<'\n';
#define parent(i) ((i)-1)/2
#define left(i) 2*(i)+1
#define right(i) 2*(i)+2
using namespace std;

int getmin(int A[],int Q1[])
{
  return A[Q1[0]];   //minimum at A[Q1[0]]
}
int getmax(int A[],int Q2[])
{
  return A[Q2[0]];   //maximum at A[Q2[0]]
}

void minheapify(int A[], int Q1[],int I1[],int s,int i)
{
    int l = left(i);
    int r = right(i);

    int small = i;
    if (l < s && A[Q1[l]] < A[Q1[i]])
        small = l;
    if (r < s && A[Q1[r]] < A[Q1[small]])
        small = r;
    if (small != i)
    {
        int temp;

        temp = Q1[i];
        Q1[i]=Q1[small];
        Q1[small]=temp;
        I1[Q1[i]]=i;                //update I1 as well
        I1[Q1[small]]=small;

        minheapify(A,Q1,I1,s,small);  //call recursively
    }
}
void maxheapify(int A[], int Q2[],int I2[], int s,int i)
{
    int l = left(i);
    int r = right(i);

    int large = i;
    if (l < s && A[Q2[l]] > A[Q2[i]])
        large = l;
    if (r < s && A[Q2[r]] > A[Q2[large]])
        large = r;
    if (large != i)
    {
        int temp;

        temp = Q2[i];
        Q2[i]=Q2[large];
        Q2[large]=temp;
        I2[Q2[i]]=i;                 //update I2 as well
        I2[Q2[large]]=large;

        maxheapify(A,Q2,I2,s,large); //call recursively
    }
}
void makeminheap(int A[],int Q1[],int I1[],int s)
{
  int i = parent((s-1));

                              // repeatedly minheapify going from bottom to top
  for(;i>=0;--i)
    {
      minheapify(A,Q1,I1,s,i);
    }
  for(i=0;i<s;i++)
    {

      I1[Q1[i]] =i;
    }
}
void makemaxheap(int A[],int Q2[],int I2[],int s)
{
  int i = parent((s-1));


  for(;i>=0;--i)                  //repeatedly maxheapify going from bottom to top in a heap
    {
      maxheapify(A,Q2,I2,s,i);
    }
  for(i=0;i<s;i++)
    {

      I2[Q2[i]] =i;
    }
}
void minreplace(int A[],int Q1[],int I1[],int Q2[], int I2[],int s,int num)
{
  int i,j;
  i=Q1[0];
  A[i]=num;
  minheapify(A,Q1,I1,s,0);
  j=I2[i];

  for(i=j;i>0;i=parent(i))   //maxheap ordering may get disturbed, so fixing it here
    {
      if(A[Q2[i]]>A[Q2[parent(i)]])
	{
	   int temp;

        temp = Q2[i];
        Q2[i]=Q2[parent(i)];
        Q2[parent(i)]=temp;
        I2[Q2[i]]=i;
        I2[Q2[parent(i)]]=parent(i);
	}
      else
	break;
    }
}
void maxreplace(int A[],int Q1[],int I1[],int Q2[], int I2[],int s,int num)
{
  int i,j;
  i=Q2[0];
  A[i]=num;
  maxheapify(A,Q2,I2,s,0);
  j=I1[i];
   for(i=j;i>0;i=parent(i)) //minheap ordering may get disturbed, so fixing it here
    {
      if(A[Q1[i]]<A[Q1[parent(i)]])
	{
	   int temp;

        temp = Q1[i];
        Q1[i]=Q1[parent(i)];
        Q1[parent(i)]=temp;
        I1[Q1[i]]=i;
        I1[Q1[parent(i)]]=parent(i);
	}
      else
	break;
    }

}
void heapsort(int A[],int H[],int Q2[],int I2[],int s)
{
  if(s>0)
    {
      int max;
      max = getmax(A,Q2);
      H[s-1]=max;
      A[Q2[0]]=A[Q2[s-1]];
      s--;
      maxheapify(A,Q2,I2,s,0);     //extract maximum element and put it in last position

      heapsort(A,H,Q2,I2,s);
    }
  else
    return;
}
void qsort(int M[],int l,int n, int s)
{

  int *A,*Q1,*Q2,*I1,*I2,*H;
   A = (int *)malloc(s*sizeof(int));
  Q1 = (int *)malloc(s*sizeof(int));
  Q2 = (int *)malloc(s*sizeof(int));
  I1 = (int *)malloc(s*sizeof(int));
  I2 = (int *)malloc(s*sizeof(int));
   H = (int *)malloc(s*sizeof(int));

  if((n-l)>=s)
  {
  int i,j;

  for(i=l;i<(s+l);i++)
    A[i-l]=M[i];
  for(j=0;j<s;j++)
    {
      Q1[j]=j;
      I1[j]=j;
      Q2[j]=j;
      I2[j]=j;
    }
  makeminheap(A,Q1,I1,s);
  makemaxheap(A,Q2,I2,s);


  int *L,*R,flag=0;
  L = (int *)malloc((n-s)*sizeof(int));
  R = (int *)malloc((n-s)*sizeof(int));

  int k,x;
  for(i=s+l,k=0,x=0;i<n;i++)
    {
      if(M[i]<=getmin(A,Q1))
	{
	  L[k]=M[i];
	  k++;
	}
      else if(M[i]>=getmax(A,Q2))
	{
	  R[x]=M[i];
	  x++;
	}
      else
	{
	  if(flag==0)
	    {
	      flag=1;
	      int min=getmin(A,Q1);
	      L[k]=min;
	      k++;
	      minreplace(A,Q1,I1,Q2,I2,s,M[i]);
	    }
	  else
	    {
	      flag=0;
	      int max=getmax(A,Q2);
	      R[x]=max;
	      x++;
	      maxreplace(A,Q1,I1,Q2,I2,s,M[i]);
	    }
	}

    }
  heapsort(A,H,Q2,I2,s);
  for(i=0;i<k;i++)
    M[i+l]=L[i];
  for(;i<(k+s);i++)
    M[i+l]=H[i-k];
  for(;i<(k+s+x);i++)
    M[i+l]=R[i-k-s];

  free(L);
  free(H);
  free(R);
  free(Q1);
  free(Q2);
  free(I1);
  free(I2);       //free the memory

  qsort(M,l,l+k,s);                   //recursively call qsort on left and right parts
  qsort(M,k+l+s,k+l+s+x,s);
    }
  else
    {
        int i,j;

  for(i=l;i<n;i++)
    A[i-l]=M[i];
  for(j=0;j<(n-l);j++)
    {
      Q1[j]=j;
      I1[j]=j;
      Q2[j]=j;
      I2[j]=j;
    }
  makeminheap(A,Q1,I1,(n-l));
  makemaxheap(A,Q2,I2,(n-l));

       heapsort(A,H,Q2,I2,(n-l));

       for(i=0;i<(n-l);i++)
            M[i+l]=H[i];

       free(H);
       free(Q1);
       free(Q2);
       free(I1);
       free(I2);
    }
}
int main()
{
  int n,s;
  cin>>n>>s;
  int *M;
  M = (int*) malloc((n)*sizeof(int));
  int i;
  for(i=0;i<n;i++)
    {
      cin>>M[i];
    }

  qsort(M,0,n,s);
  cout<<"\n+++ Array after sorting\n ";
  disp(M,0,n)                   //disp displays the array, used #define here

  return 0;
}
