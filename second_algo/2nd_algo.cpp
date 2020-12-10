#include<iostream>
#include<numeric>
#include<stdlib.h>
#include<time.h>
using namespace std;

int myaccumulator(int x, int y)
{
    return x^y;
}

int myproduct(int x, int y)
{
    return x&y;
}

void get_2D_array(int s[],int a[][600],int row, int col)
{
    int k=0;
    for(int i=0;i<row;i++)
        for(int j=0;j<col;j++)
        {
            a[i][j]=s[k];
            k++;
        }
}

void find_inner_product(int a[][600],int secret_key[],int b[],int sam,int d)
{
    int *series;
   // int j=0;
    for(int i=0;i<sam;++i)
    {

        series= a[i];
        int n=inner_product(series,series+d,secret_key,0,myaccumulator,myproduct);
        b[i]=n;
    }
    /*
        [0 0 1] [1 1 1] = 0 + 0 + 1

    */
}


int count_set_bits(int a[],int sam)
{
    int cnt=0;
    for(int i=0;i<sam;++i)
    {
        if(a[i]==1)
            ++cnt;
    }
    return cnt;
}

void get_random_values(int arr[],int sam,int d)
{
    srand(time(0));
    int k=0;
    for(int j=0;j<sam;++j)
    {
        int randomNum=rand();
        for (int i=0; i < d; i++)
        {
            int randomBit = (randomNum >> i) & 1;

            arr[k++]=randomBit;
        }
    }
}

void get_random_error_vector(int arr[],int sam)
{
    srand(time(0));
    int k=0;
    arr[2000]={0};
    for(int j=0;j<sam ;++j)
    {
        int randomNum=rand();
        int randomBit = (randomNum >> j) & 1;

        arr[k++]=randomBit;

      /*  if(count_set_bits(arr,sam)==40)
        {
             break;
        }
*/
    }
}

void get_random_secret_key(int s[],int d)
{
   // int k=0;

    for (int i=0; i < d; i++)
    {
        int randomNum=rand();
        int randomBit = (randomNum >> i) & 1;
        s[i]=randomBit;
    }

}

void print_2D_array(int arr[][600],int sam,int d)
{
    for(int i=0;i<sam;i++)
    {
        for(int j=0;j<d;j++)
        {
            cout<<arr[i][j]<<" ";
        }
        cout<<endl;
    }
}

void error_part(int e[],int b[],int sam)
{
    for(int i=0;i<sam;++i)
    {
        int a=b[i];
        b[i]=e[i]^a;
        //b[i]=e[i]^b[i];
    }
}

int count_set_bit(int temp2[],int s)
{
    int ans=0;
    for(int i=0;i<s;++i)
    {
        if(temp2[i]==1)
            ++ans;
    }
    return ans;
}

int hamming_wt(int a[][600],int s[],int b[],int sam,int d)
{
    int wt=0;
    int temp1[600]={0};                                 //store value of Ab
    find_inner_product(a,s,temp1,sam,d);

    error_part(b,temp1,sam);

    wt=count_set_bit(temp1,sam);
    return wt;
}

int sel_random_arr(int sam)
{
    int r=0;
    for(int i=0; i < sam; i++)
    {
        int randomNum=rand();
        int randomBit =(randomNum >> i) &(sam-1);
        r=randomBit;
    }
    cout<<"\t r is \t"<<r<<endl;
    return r;
}

int maj(int oracle[],int cnt)
{
    int c0=0,c1=0;
    for(int i=0;i<cnt;++i)
    {
        if(oracle[i]==0)
            ++c0;
        else
            ++c1;
    }
    if(c0 <c1)
        return 1;
    else if(c0==c1)
        return 0;
    else
        return 0;
}

void generate_new(int arr[3000],int a[600][600],int secret_key[300],int b[3000],int e[3000],int sam,int d)
{

     //srand(time(0));
     get_random_values(arr,sam,d);

     get_2D_array(arr,a,sam,d);

     cout<<"\nGenerate random values of vector (a) :"<<endl;
     print_2D_array(a,sam,d);

     find_inner_product(a,secret_key,b,sam,d);

     //e[3000]={0};
      get_random_error_vector(e,sam);

     cout<<"\nError vector (e) :\n";
     for(int k=0;k<sam;++k)
         cout<<e[k]<<" ";

     cout<<endl;
     error_part(e,b,sam);


     cout<<"\nValue of b=As+e comes out to be :\t\n";
     for(int k=0;k<sam;++k)
        cout<<b[k]<<" ";
}

int main()
{
    int d,sam;
    cout<<"Enter the dimension value : \t";
    cin>>d;

    cout<<"Number of samples :\t";
    cin>>sam;

    int arr[3000]={0};

    int a[600][600];

    cout<<"\nEnter the value of secret key (s) :\t";
    int secret_key[300];

    for(int j=0;j<d;++j)
        cin>>secret_key[j];

    int b[2000];

    cout<<endl;
    int s[600];
    int oracle[sam];            //change d to sam

    int dd=0;
    int pp[d]={0};
    int flag;
    int tp;

    int orac2[d]={0};         //to final secret key
    int ij=0;
    int e[2000];
   // int *u;
    int u[d];//={0,1,1};

    e[2000]={0};
   // get_random_error_vector(e,sam);

    for(int z=0;z<d;++z)
    {
       // e[2000]={0};
        generate_new(arr,a,secret_key,b,e,sam,d);
        int ccc=0;
        //tp=sel_random_arr(sam);

        /*
        cout<<"\nenter \t";
        cin>>tp;
        u=a[tp];
*/
        cout<<endl;
        for(int i=0;i<d;++i)
            cin>>u[i];

        cout<<"\nrandom vector \t";
        for(int i=0;i<d;++i)
            cout<<u[i]<<" ";

         cout<<endl;

        oracle[sam]={0};

        int ii=0;
        for(int i=0;i<sam;++i)
        {
            flag=0;

            for(int j=0;j<d;++j)
            {
                pp[j]=a[i][j];
            }


            for(int k=0;k<d;++k)
            {
                if(pp[k]!=u[k])
                {
                    flag=1;
                    break;
                }
            }

            if(flag==0)
            {
                ccc++;
                //cout<<" b" <<b[i]<<endl;
              //  cout<<"\nposi \t"<<i;
                oracle[ii++]=b[i];
            }
        }

        cout<<"oracle is \t";
       // cout<<"\ncount"<<ccc<<endl;
        for(int i=0;i<ccc;++i)
            cout<<oracle[i]<<" ";

       cout<<endl;
        orac2[ij++]=maj(oracle,ccc);
    }

    cout<<endl;
    cout<<" secret key \n";
    for(int i=0;i<d;++i)
        cout<<orac2[i]<<" ";

    return 0;

}

