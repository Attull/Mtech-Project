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
    int j=0;
    for(int i=0;i<sam;++i)
    {

        series= a[i];
        int n=inner_product(series,series+d,secret_key,0,myaccumulator,myproduct);
        b[j++]=n;
    }
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

int count_set_bits(int a[],int sam)
{
    int cnt=0;
    for(int i=0;i<sam;++i)
    {
        if(a[i]==1)
            ++cnt;
    }

   // cout<<"hello"<<cnt;
    return cnt;
}

void get_random_error_vector(int arr[],int sam)
{
    srand(time(0));
    int k=0;
    for(int j=0;j<5*sam ;++j)
    {
        int randomNum=rand();
        int randomBit = (randomNum >> j) & 1;

        arr[k++]=randomBit;
        int l=count_set_bits(arr,sam);
        //cout<<"-> "<<l<<endl;
        if(l!=160)
        {
            l=count_set_bits(arr,sam);
            continue;
        }
        else
            break;
    }
}

void get_random_secret_key(int s[],int d)
{
    int k=0;

    for (int i=0; i < d; i++)
    {
        int randomNum=rand();
        int randomBit = (randomNum >> i) & 1;
        s[k++]=randomBit;
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

void error_part(int e[],int b[],int sam,int d)
{
    for(int i=0;i<sam;++i)
    {
        int a=b[i];
        b[i]=e[i]^a;
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

    error_part(b,temp1,sam,d);

    wt=count_set_bit(temp1,sam);
    return wt;
}

int main()
{
    int d,sam;
    cout<<"Enter the dimension value : \t";
    cin>>d;

    cout<<"Number of samples :\t";
    cin>>sam;

    int arr[3000]={0};
    get_random_values(arr,sam,d);

    int a[600][600];
    get_2D_array(arr,a,sam,d);

    cout<<"\nGenerate random values of vector (a) :"<<endl;
    print_2D_array(a,sam,d);

    cout<<"\nEnter the value of secret key (s) :\t";
    int secret_key[300];

    for(int j=0;j<d;++j)
        cin>>secret_key[j];

    int b[2000];
    find_inner_product(a,secret_key,b,sam,d);

    int e[2000];

    get_random_error_vector(e,sam);

    cout<<"\nError vector (e) :\t";
    for(int k=0;k<sam;++k)
        cout<<e[k]<<" ";

    cout<<endl;
    error_part(e,b,sam,d);
    cout<<"\nValue of b=As+e comes out to be :\t";
    for(int k=0;k<=sam;++k)
        cout<<b[k]<<" ";



    int s[600];
   // cout<<"\nRandom secret key :\t";
    int th;
    cout<<"\nEnter threshold value :\t";
    cin>>th;
    for(int i=0;i<sam;++i)
    {
        get_random_secret_key(s,d);

        int wtt=hamming_wt(a,s,b,sam,d);

        if(wtt<th)
        {
            cout<<"secret key is :\t";
            for(int i=0;i<d;++i)
                cout<<s[i]<<" ";

            break;
        }

    }

    cout<<endl;
    return 0;
}



