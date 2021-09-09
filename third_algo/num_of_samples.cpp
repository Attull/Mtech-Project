#include <stdio.h>	// for sprintf()
#include <stdlib.h>	// for exit()
#include<math.h>
#include <iostream>
using namespace std;


class Fraction
{
	int	num, den;
    public:
	void reduce( void );

	// constructors
	Fraction()
	{
        num = 0;
        den = 1;
    }	// default constructor
	Fraction(int m)
    {
        num = m;
        den = 1;
    }
	Fraction(int m,int n)
    {
        num = m;
        den = n;
    }

	// access functions
	int Num( void ) const { return this->num; }
	int Den( void ) const { return this->den; }
	int ipart( void );			// integer part
	Fraction fpart( void );			// fractional part

	// unary and binary operators
	Fraction operator -() const { return Fraction( -num, den ); }

	Fraction operator +( const Fraction& ) const;
	Fraction operator -( const Fraction& ) const;
	Fraction operator *( const Fraction& ) const;
	Fraction operator /( const Fraction& ) const;

	// assignment operators
	Fraction operator +=( const Fraction& );
	Fraction operator -=( const Fraction& );
	Fraction operator *=( const Fraction& );
	Fraction operator /=( const Fraction& );

	Fraction operator =( const int );

	friend Fraction operator / ( const int, const Fraction );
	friend Fraction operator * ( const int, const Fraction );


	friend ostream& operator <<( ostream& s, Fraction& f );
	friend istream& operator >>( istream& s, Fraction& f );

	friend Fraction powerr(const Fraction ,const int);
	friend Fraction sqrt(const Fraction);
	friend Fraction revrse(const Fraction);
	// output length
	int len( void );
};


int gcd( int m, int n )
{
	int	p = ( m < 0 ) ? -m : m;
	int	q = ( n < 0 ) ? -n : n;
	while(q)
    {
        int r = p % q;
        p = q;
        q = r;
    }
	return	p;
}


void Fraction::reduce( void )
{
	int	g = gcd(this->num, this->den);

	if (this->den < 0)
        g = -g;

	if (g != 0)
    {
        this->num /= g;
        this->den /= g;
    }
}


int Fraction::ipart( void )
{
	int	quot = this->num / this->den;
	int	rem = this->num % this->den;
	if(rem < 0)
        --quot;

	return	quot;
}


Fraction Fraction::fpart( void )
{
	Fraction f = *this;
	f -= f.ipart();
	return	f;
}


Fraction Fraction::operator +( const Fraction& f ) const
{
	Fraction sum;

	sum.num = this->num * f.den + this->den * f.num;
	sum.den = this->den * f.den;
	sum.reduce();
	return	sum;
}


Fraction Fraction::operator -( const Fraction& f ) const
{
	Fraction diff;

	diff.num = this->num * f.den - this->den * f.num;
	diff.den = this->den * f.den;
	diff.reduce();
	return	diff;
}


Fraction Fraction::operator *( const Fraction& f ) const
{
	Fraction prod;

	prod.num = this->num * f.num;
	prod.den = this->den * f.den;
	prod.reduce();
	return	prod;
}


Fraction Fraction::operator /( const Fraction& f ) const
{
	Fraction quot;

	if ( f.num == 0 ) { cerr << "\nDivision by zero!\n"; exit(1); }
	quot.num = this->num * f.den;
	quot.den = this->den * f.num;
	quot.reduce();
	return	quot;
}


Fraction Fraction::operator +=( const Fraction& f )
{
	return *this = *this + f;
}


Fraction Fraction::operator -=( const Fraction& f )
{
	return *this = *this - f;
}


Fraction Fraction::operator *=( const Fraction& f )
{
	return *this = *this * f;
}


Fraction Fraction::operator /=( const Fraction& f )
{
	return *this = *this / f;
}


Fraction Fraction::operator =( const int c )
{
	this->num = c;
	this->den = 1;
	return	*this;
}

Fraction operator / ( const int i, const Fraction f )
{
		Fraction	recip;
		recip.num = f.den;
		recip.den = f.num * i;
		recip.reduce();
		return	recip;
}


Fraction operator * ( const int i, const Fraction f )
{
		Fraction	prod;
		prod.num = f.num * i;
		prod.den = f.den;
		prod.reduce();
		return	prod;
}

ostream& operator <<( ostream& s, Fraction& f )
{
	if(f.num < 0)
        s << f.num;
	else
        s <<' '<< f.num;

	if(f.den != 1)
        s << "/" << f.den;

	s <<' ';
	return	s;
}


istream& operator >>( istream& s, Fraction& f )
{
	int	u = 0, v = 1;
	char	c = 0;

	s >> c;
	if ( c == '(' )
		{
		s >> u >> c;
		if ( c == '/' ) s >> v >> c;
		if ( c != ')' ) s.clear( ios::badbit );
		}
	else	{
		s.putback( c );
		s >> u;
		c = s.peek();
		if ( c == '/' ) s >> c >> v;
		}

	if ( s ) { f.num = u; f.den = v; }
	return	s;
}


int Fraction::len( void )
{
	char	line[40];
	int	retval = 0;

	int	n = ( num < 0 ) ? -num : num;
	int	d = den;
	retval += 1 + sprintf( line, "%d", n );
	if ( d != 1 ) retval += 1 + sprintf( line, "%d", d );
	retval += 1;
	return	retval;
}

Fraction powerr(Fraction f1,int n)
{
    Fraction power(1);

    for(int i=0;i<n;++i)
    {
        power.num=power.num*f1.num;
        power.den=power.den*f1.den;
    }
    return power;
}

Fraction sqrt(Fraction f1)
{
    Fraction s(1);

    s.num=sqrt(f1.num);

    return s;
}

Fraction revrse(Fraction f1)
{
    Fraction r(1);

    r.num=f1.den;
    r.den=f1.num;

    return r;
}

int main()
{
    Fraction tau(1,6) ;

	Fraction t1(1,2);

	int d;
	cout<<"\nenter the value of dimension : ";
	cin>>d;

/*
	Fraction t2=t1-2*tau;
	Fraction p1=powerr(t2,2*d);


	Fraction p2=revrse(p1);

    Fraction m=8*d*p2;           //calculate value of m (that define no. of samples)

*/

    Fraction t2=t1-tau;
	Fraction p1=powerr(t2,2);

	Fraction p2=revrse(p1);

    Fraction m=32*d*p2;

   // Fraction t=m*tau+sqrt(d*m);  //calculate threshold value t

	cout<<endl<<m;
	//cout<<endl<<t;

}
