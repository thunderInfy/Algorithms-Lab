#include<iostream>
#include<cstring>
#include<cstdlib>

using namespace std;

int issubseq(char A[],char B[])
{
  int res = 0;
  int n = strlen(A);
  int m = strlen(B);
  int i,k;
  
  for(i=0,k=0;i<n && k<m;i++)
    {
      if(A[i]==B[k])
	{
	  k++;
	}
    }
  if(k==m)
    res = 1;

  return res;
}


char* repsymbols(char T[], int k)
{
  char *res;
  int m = strlen(T);
  int Size = m*k + 1;
  int temp;
  
  res = (char*)malloc((Size)*sizeof(char));

  int i,x;
  
  for(i=0,x=0;i<m;i++)
    {
      temp = k;

      while(temp>0)
	{
	  res[x]=T[i];
	  x++;
	  temp--;
	}
    }
  res[x] = '\0';
  return res;
}


void prnsubseq(char A[],char B[])
{
  int n = strlen(A);
  int m = strlen(B);

  for(int i=0;i<n;i++)
    {
      cout<<A[i];
    }
  cout<<'\n';
  for(int i=0,k=0;i<n && k<m;i++)
    {
      if(A[i]==B[k])
	{
	  cout<<B[k];
	  k++;
	}
      else
	{
	  cout<<' ';
	}
    }
  cout<<'\n';  
}


//exhaustive search
int exsh(char S[], char T[])
{
  int k;
  int n = strlen(S);
  int m = strlen(T);
  int max_k = n/m;
  
  for(k=1;k<=max_k;k++)
    {
      if(issubseq(S,repsymbols(T,k))==0)
	break;
    }
  int res = k-1;
  return res;
}


//divide and conquer strategy 1
int dnc1(char S[],char T[], int s)
{
  int n = strlen(S);
  int m = strlen(T);

  if(n<2*m)
    return(issubseq(S,T));
  else
    {
      char* S1;
      char* S2;
      S1 = (char*)malloc((n+1)*sizeof(char));
      S2 = (char*)malloc((n+1)*sizeof(char));

      int x,y,z;

      int visited[s] = {0};
      char ch;
      int index;
      
      for(x=0,y=0,z=0;x<n;x++)
	{
	  ch = S[x];
	  index = (int)(ch - 'a');
	  if(visited[index]==0)
	    {
	      visited[index] = 1;
	      S1[y] = ch;
	      y++;
	    }
	  else
	    {
	      visited[index] = 0;
	      S2[z] = ch;
	      z++;
	    }
	}
      S1[y]='\0';
      S2[z]='\0';
      
      if(strlen(S2)==0) //empty S2, which means S1 contains all distinct letters and hence length of S1 will be less than or equal to s
	{
	  //since S1 contains all distinct letters, k would be either 0 or 1
	  //hence just check for T in S1 

	  return(issubseq(S1,T));
	}
      
      int k1,k2;

      k1 = dnc1(S1,T,s);
      k2 = dnc1(S2,T,s);

      int f,d,t;
      f = k1+k2+1;
      d = k1+k2;
      t = k1+k2-1;

      if(issubseq(S,repsymbols(T,f))==1)
	return f;
      
      if(issubseq(S,repsymbols(T,d))==1)
	return d;
      
      if(issubseq(S,repsymbols(T,t))==1)
	return t;
      else
	return 0;
      
    }
}


/*modification in dnc1 is done by reducing number of recurrences from 2 to 1, since we know the
  value of k2, we know all the possible values which k1+k2, k1+k2+1 and k1+k2-1 can take*/
int dnc2(char S[],char T[], int s)
{
  int n = strlen(S);
  int m = strlen(T);

  if(n<2*m)
    return(issubseq(S,T));
  else
    {
      char* S2;
      S2 = (char*)malloc((n+1)*sizeof(char));
      int x,y;

      int visited[s] = {0};
      char ch;
      int index;
      
      for(x=0,y=0;x<n;x++)
	{
	  ch = S[x];
	  index = (int)(ch - 'a');
	  if(visited[index]==0)
	    {
	      visited[index] = 1;
	      
	    }
	  else
	    {
	      visited[index] = 0;
	      S2[y]=ch;
	      y++;
	    }
	}
      S2[y]='\0';
      int k2;

      k2 = dnc2(S2,T,s);
      

      int f,d,t,h,q;
      f = 2*k2+2;
      d = 2*k2+1;
      t = 2*k2;
      h = 2*k2-1;
      q = 2*k2-2;

      if(issubseq(S,repsymbols(T,f))==1)
	return f;
      
      if(issubseq(S,repsymbols(T,d))==1)
	return d;
      
      if(issubseq(S,repsymbols(T,t))==1)
	return t;

      if(issubseq(S,repsymbols(T,h))==1)
	return h;

      if(issubseq(S,repsymbols(T,q))==1)
	return q;
      else
	return 0;
      
    }
}

int main()
{
  int s,n,m;
  cout<<"\nEnter s,n and m\n";
  cin>>s>>n>>m;

  cout<<"\nEnter S string\n";
  char *S;
  char *T;
  
  S=(char*)malloc((n+1)*sizeof(char));
  T=(char*)malloc((m+1)*sizeof(char));

  cin>>S;

  cout<<"\nEnter T string\n";
  cin>>T;

  cout<<"s = "<<s;
  cout<<"\nn = "<<n;
  cout<<"\nm = "<<m;
  cout<<"\n\nS = "<<S;
  cout<<"\nT = "<<T;
  
  int res1,res2,res3;

  res1 = exsh(S,T);

  cout<<"\n\n+++ Exhaustive Search\n";
  cout<<"    k = "<<res1;
  
    res2 = dnc1(S,T,s);
  
  cout<<"\n\n+++ Divide and Conquer Strategy 1";
  cout<<"\n    k = "<<res2;
 
  res3 = dnc2(S,T,s);

  cout<<"\n\n+++ Divide and Conquer Strategy 2";
  cout<<"\n    k = "<<res3;

  cout<<"\n\n+++ The subsequence is:\n";
  prnsubseq(S,repsymbols(T,res1));
  

  return 0;
}