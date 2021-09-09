#include<iostream>
#include<numeric>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<list>
#include<fstream>
using namespace std;

class Hash
{
	int BUCKET;                     // No. of buckets
	list<int> *table;               // Pointer to an array containing buckets

    public:
        Hash(int V); // Constructor

        void insertItem(int x,int index);
        void displayHash();
        int ele(int index);
};

int Hash::ele(int index)
{
    int cn0=0,cn1=0;
    for (auto x : table[index])
    {
        if(x==0)
            ++cn0;
        else if(x==1)
            ++cn1;
    }

    if(cn0>cn1)
        return 0;
    else
        return 1;
}

Hash::Hash(int b)
{
	this->BUCKET = b;
	table = new list<int>[BUCKET];
}

void Hash::insertItem(int key,int index)
{
	table[index].push_back(key);
}

void Hash::displayHash()            // function to display hash table
{
    for(int i=0; i<BUCKET;i++)
    {
        cout << i;
        for (auto x : table[i])
            cout << " --> " << x;
        cout << endl;
    }
}

int myaccumulator(int x, int y)
{
    return x^y;
}

int myproduct(int x, int y)
{
    return x&y;
}

void get_2D_array(int s[],int a[][20],int row, int col)
{
    int k=0;
    for(int i=0;i<row;i++)
        for(int j=0;j<col;j++)
        {
            a[i][j]=s[k];
            k++;
        }
}

void find_inner_product(int a[][20],int secret_key[],int b[],int sam,int d)
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
   // srand(time(0));
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
    return cnt;
}

/*
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
        if(l!=sam/6)
        {
            l=count_set_bits(arr,sam);
            continue;
        }
        else
            break;
    }
}

*/
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

       if(count_set_bits(arr,sam)==sam/6)
        {
             break;
        }
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

void print_2D_array(int arr[][20],int sam,int d)
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


void getCofactor(int a[10][10],int temp[10][10],int p,int q,int N)
{
    int i=0,j=0;

    for(int row=0;row<N;row++)
    {
        for(int col=0;col<N;++col)
        {
            if(row!=p && col!=q)
            {
                temp[i][j++]=a[row][col];
                if(j==N-1)
                {
                    j=0;
                    ++i;
                }
            }
        }
    }
}

int determinant(int a[10][10],int N)
{
    int D=0;

    if(N==1)                            //base case : if matrix contain single element
        return a[0][0];

    int temp[10][10];                 //to store cofactor
    int sign=1;

    for(int r=0;r<N;++r)
    {
        getCofactor(a,temp,0,r,N);
        D+=sign*a[0][r]*determinant(temp,N-1);
        sign=-sign;
    }
    return D;
}

void adjoint(int a[10][10],int adj[10][10],int d)
{
    if(d==1)
    {
        adj[0][0]=1;
        return;
    }

    int sign=1,temp[10][10];               //temp array is used to store cofactors of a[][]

    for(int i=0;i<d;++i)
    {
        for(int j=0;j<d;++j)
        {
            getCofactor(a,temp,i,j,d);
            sign=((i+j)%2==0)?1:-1;
            adj[j][i]=(sign)*(determinant(temp,d-1));
            adj[j][i]==(-0)?0:adj[j][i];
        }
    }

}

void inverse(int a[10][10],float inverse[10][10],int d,int det)
{
    int adj[10][10];
    adjoint(a,adj,d);

    for(int i=0; i<d; i++)
        for (int j=0; j<d; j++)
            inverse[i][j] = adj[i][j]/float(det);

}

void display(float ab[10][10],int d)
{
    for(int i=0; i<d; i++)
    {
        for(int j=0; j<d; j++)
            cout << ab[i][j] << " ";
        cout << endl;
    }
}

void display_1D(int t[600],int d)
{
    for(int i=0;i<d;++i)
        cout<<t[i]<< " ";
}


void multi(float a[10][10],int b[],int d,int sam,int t[300])
{
    float mult[100][100]={0};
    for(int i = 0; i < d; ++i)
    {
        for(int k = 0; k < d; ++k)
        {
            mult[i][0] += a[i][k] * b[k];
        }
    }

    for(int i=0;i<d;++i)
    {
        t[i]=mult[i][0];
    }
}

void generate_new(int arr[3000],int a[][20],int secret_key[300],int b[],int e[],int sam,int d)
{
     get_random_values(arr,sam,d);

     get_2D_array(arr,a,sam,d);

    // cout<<"\nGenerate random values of vector (a) :"<<endl;
   //  print_2D_array(a,sam,d);

     find_inner_product(a,secret_key,b,sam,d);

     //e[3000]={0};
     get_random_error_vector(e,sam);
/*
     cout<<"\nError vector (e) :\n";
     for(int k=0;k<sam;++k)
         cout<<e[k]<<" ";
*/
   //  cout<<endl;
     error_part(e,b,sam,d);
/*

     cout<<"\nValue of b=As+e comes out to be :\t\n";
     for(int k=0;k<sam;++k)
        cout<<b[k]<<" ";
*/
}

int check(float inv[10][10],int d)
{
    int kk=1;
    for(int i=0;i<d;++i)
    {
        for(int j=0;j<d;++j)
        {
            if(inv[i][j]>1 || inv[i][j]<0)
                kk=0;
        }
    }
    return kk;
}

int main()
{
    clock_t start, endd;                            //to find execution time
    start = clock();

    int tp;
    fstream myfile;                                // opening one file and take input from it
    myfile.open("input5.txt",ios::in);

    int d,sam;
    cout<<"Enter the dimension value : \t";
    myfile>>tp;
    d=tp;

    cout<<"Number of samples :\t";
    myfile>>tp;
    sam=tp;

    int arr[d*sam+10]={0};

    int a[sam+10][20];


    cout<<"\nEnter the value of secret key (s) :\t";
    int secret_key[300];

    for(int j=0;j<d;++j)
    {
       myfile>>tp;
       secret_key[j]=tp;
    }

    int b[sam+1];

    int e[sam+1]={0};
    generate_new(arr,a,secret_key,b,e,sam,d);

    int adj[10][10];                       //to store adjoint

    //adjoint(a,adj,d);

    float inv[10][10];


    Hash h(d);
    int t[300];
    int index;
    int countt=0;

    for(int i=0;i<sam;++i)
    {
        generate_new(arr,a,secret_key,b,e,sam,d);

        int a2[10][10];
        int *p,t8,k=0;

        int temp_arr[d]={0};                     //to store the random selected position of b

      //  srand(time(0));
        for(int i=0;i<d;++i)
        {
            //t8=rand()%(100)+1;          //randomly selected any value
            myfile>>tp;
            t8=tp;
            temp_arr[k]=t8;
            p=a[t8];                             //p is pointer , so it holds the address of 'a' corresponds to that 'b'
            for(int j=0;j<3;++j){
                 a2[k][j]=p[j];                  //this is basically , a randomly selected array , whose inverse we are going to calculate
            }
            ++p;
            ++k;
           // cout<<endl;
        }

        int temp_b[d]={0};                      //temp array to store value of b correspond to above selected array
        for(int i=0;i<d;++i)
            temp_b[i]=b[temp_arr[i]];

            /*
        cout<<"selected b position \n";
        for(int i=0;i<d;++i){
                cout<<temp_arr[i]<<" ";
        }
*/
     //   cout<<endl;
/*
        for(int i=0;i<d;++i){
            cout<<temp_b[i]<<" ";
        }
*/
/*
        cout<<"\nselected array \n";
        for(int i=0;i<d;++i){
            for(int j=0;j<d;++j)
                cout<<a2[i][j]<<" ";

            cout<<endl;
        }
*/
        int det=determinant(a2,d);
  //      cout<<endl<<"determinant \t:"<<det;

        ++countt;

        if(det!=0)
        {
            inverse(a2,inv,d,det);
            if(check(inv,d))
            {
                //cout<<"\n inverse \n";
               // display(inv,d);
                multi(inv,temp_b,d,sam,t);
                index=0;

                for(int i=0;i<d;++i)
                {
                     h.insertItem(t[i],index);
                     index++;
                }

              // h.displayHash();
            }
        }
     //   cout<<endl<<"loop no "<<countt<<endl;
    }

    cout<<"\nour secret key is\n";
    for(int i=0;i<d;++i)
    {
        cout<<h.ele(i)<<" ";
    }
    endd = clock();

    cout<<endl;
    double time_taken = double(endd - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by program is : "<< time_taken ;


    return 0;
}





