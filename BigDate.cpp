#include<iostream>
#include<cstring>
#include<vector>
#include<iterator>
#include<algorithm>
using namespace std;

class BigDate{
friend ostream& operator<<(ostream& os,const BigDate& a);
friend istream& operator>>(istream& is,BigDate& a);
friend BigDate operator+(BigDate& a,BigDate& b);
friend BigDate operator-(BigDate& a,BigDate& b);
friend BigDate operator*(BigDate& a,BigDate& b);
friend bool operator>(const BigDate& a,const BigDate& b);
friend bool operator<(const BigDate& a,const BigDate& b);
friend bool operator>=(const BigDate& a,const BigDate& b);
friend bool operator<=(const BigDate& a,const BigDate& b);
public:
    BigDate(){}
    //BigDate(short a);
    //BigDate(int a);
    BigDate(long long a);  //¿¿¿¿¿short¿int
    BigDate(const char* p_a);
    ~BigDate(){date.clear();}
    void setflag(int i) {flag=i;}
    void clean(){date.clear();}
private:
    vector<char> date;  //¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿
    bool flag;          //¿¿¿¿
};

BigDate::BigDate(long long a)
{
    if(a<0) flag=1,a=-a;
    else flag=0;
    while(a/10!=0)
    {
        date.push_back(a%10);
        a/=10;
    }
    date.push_back(a%10);
}
BigDate::BigDate(const char* p_a)
{
    int l=strlen(p_a);
    int i=0;
    if(p_a[0]=='-') flag=1,i++;
    else flag=0;
    for(;i!=l;i++)
        date.push_back(p_a[i]-'0');
}

ostream& operator<<(ostream& os,const BigDate& a)
{
    if(a.flag==1) cout<<"-";
    for(int i=a.date.size()-1;i>=0;i--)
        cout<<(int)a.date[i];
    return os;
}
istream& operator>>(istream& is,BigDate &a)
{
    char ch;
    cin>>ch;
    if(ch=='-') a.flag=1;
    else
    {
        a.flag=0;
        a.date.insert(a.date.begin(),ch-'0');
    }
    while(ch!='\n')
    {
        cin.get(ch);
        if(ch!='\n')
        a.date.insert(a.date.begin(),ch-'0');
    }
    return is;
}
bool operator<(const BigDate& a,const BigDate& b)
{
    int flag;
    if(a.flag>0)
        if(b.flag>0) flag=0;
        else    return 1;
    else
        if(b.flag>0) return 0;
        else flag=-1;
    int a_w=a.date.size(),b_w=b.date.size();
    if(a_w>b_w) return 1+flag;
    else if(a_w<b_w) return 0-flag;
    else
        while(a_w>=0)
        {
            a_w--;
            if(a.date[a_w]>b.date[a_w]) return 1+flag;
            else if(a.date[a_w]<b.date[a_w]) return 0-flag;
        }
    return 0;
}
bool operator<=(const BigDate& a,const BigDate& b)
{
    int flag;
    if(a.flag>0)
        if(b.flag>0) flag=0;
        else    return 1;
    else
        if(b.flag>0) return 0;
        else flag=-1;
    int a_w=a.date.size(),b_w=b.date.size();
    if(a_w>b_w) return 1+flag;
    else if(a_w<b_w) return 0-flag;
    else
        while(a_w>=0)
        {
            a_w--;
            if(a.date[a_w]>b.date[a_w]) return 1+flag;
            else if(a.date[a_w]<b.date[a_w]) return 0-flag;
        }
    return 1;
}
bool operator>(const BigDate& a,const BigDate& b)
{
    if(a<b) return 0;
    else if(a.flag!=b.flag) return 1;
    else
    {
        int a_w=a.date.size(),b_w=b.date.size();
        if(a_w!=b_w) return 1;
        else
            while(a_w>=0)
        {
            a_w--;
            if(a.date[a_w]!=b.date[a_w])    return 1;
        }
    }
    return 0;
}
bool operator>=(const BigDate& a,const BigDate& b)
{
    if(a<b) return 0;
    else if(a.flag!=b.flag) return 1;
    else
    {
        int a_w=a.date.size(),b_w=b.date.size();
        if(a_w!=b_w) return 1;
        else
            while(a_w>=0)
        {
            a_w--;
            if(a.date[a_w]!=b.date[a_w])    return 1;
        }
    }
    return 1;
}

BigDate operator+(BigDate& a,BigDate& b)
{
    BigDate c;
    if(a.flag==1)
        if(b.flag==1) c.flag=1;
        else {a.setflag(0);c=b-a;a.setflag(1);return c;}
    else
        if(b.flag==1) {b.setflag(0);c=a-b;b.setflag(1);return c;}
        else c.flag=0;
    int a_w=a.date.size(),b_w=b.date.size(),max_w=max(a_w,b_w),min_w=min(a_w,b_w);
    int add=0;
    for(int i=0;i<min_w;i++)
    {
        c.date.push_back((add+a.date[i]+b.date[i])%10);
        add = (add+a.date[i]+b.date[i])/10;
    }
    if(a_w>b_w)
        for(int i1=min_w;i1<max_w;i1++)
        {
            c.date.push_back((add+a.date[i1])%10);
            add = (add+a.date[i1])/10;
        }
    else if(a_w<b_w)
        for(int i2=min_w;i2<max_w;i2++)
        {
            c.date.push_back((add+b.date[i2])%10);
            add = (add+b.date[i2])/10;
        }
    if(add!=0)
        c.date.push_back(add);
    return c;
}
BigDate operator-(BigDate& a,BigDate& b)
{
    BigDate c;
    if(a.flag==1)
        if(b.flag==0) {b.setflag(1);c=a+b;b.setflag(0);return c;}
        else {}
    else
        if(b.flag==0) {}
        else {b.setflag(0);c=a+b;b.setflag(1);return c;}
    if(a>=b) c.flag=0;
    else c.flag=1;
    int a_f=a.flag,b_f=b.flag;
    a.setflag(0),b.setflag(0);
    if(a>=b)
    {
        int a_w=a.date.size(),b_w=b.date.size();
        int add=0;
        for(int i=0;i<b_w;i++)
        {
            if(a.date[i]-b.date[i]+add<0)
            {
                c.date.push_back(a.date[i]-b.date[i]+add+10);
                add=-1;
            }
            else
            {
                c.date.push_back(a.date[i]-b.date[i]+add);
                add=0;
            }
        }
        for(int i2=b_w;i2<a_w;i2++)
        {
            if(a.date[i2]+add<0)
            {
                c.date.push_back(a.date[i2]+add+10);
                add=-1;
            }
            {
                c.date.push_back(a.date[i2]+add);
                add=0;
            }
        }
        vector<char>::iterator i3=c.date.end();
        for(i3--;i3!=c.date.begin();i3--)
        {
            if(*i3==0) c.date.erase(i3);
            else break;
        }
    }
    else
    {
        int c_f=c.flag;
        c=b-a;
        c.flag=c_f;
    }
    a.setflag(a_f),b.setflag(b_f);
    return c;
}
BigDate operator*(BigDate& a,BigDate& b)
{
    BigDate c;
    if(a.flag==b.flag) c.flag=0;
    else c.flag=1;
    int a_f=a.flag,b_f=b.flag,c_f=c.flag;
    a.setflag(0),b.setflag(0);

        int a_w=a.date.size(),b_w=b.date.size(),c_w;
        for(int i1=0;i1<a_w;i1++)
        {
            for(int i2=0;i2<b_w;i2++)
            {
                c_w=c.date.size();
                if(i1+i2>=c_w) c.date.push_back(a.date[i1]*b.date[i2]);
                else
                    c.date[i1+i2]+=a.date[i1]*b.date[i2];
            }
            int m1=0;
            for(int i3=0,c_w=c.date.size();i3<c_w;i3++)
            {
                int m2=c.date[i3];
                if(i3<c_w)
                {
                    c.date[i3]=(c.date[i3]+m1)%10;
                    m1=(m2+m1)/10;
                }
            }
            while(m1!=0)
            {
                c.date.push_back(m1%10);
                m1/=10;
            }
        }
    a.setflag(a_f),b.setflag(b_f);
    return c;
}
int main()
{
	BigDate a,b;
	char ch;
	while(1)
	{
		cin>>a;
		cin>>ch;
		cin>>b;
		cout<<a<<ch<<b<<"=";
		if(ch=='+') cout<<a+b<<endl;
		else if(ch=='-') cout<<a-b<<endl;
		else if(ch=='*') cout<<a*b<<endl;
		else
		{
			cout<<"input wrong!"<<endl;
			cout<<"do you want to exit?1/0"<<endl;
			cin>>ch;
			if(ch=='1') break;
		}
		a.clean();
		b.clean();
	}
    return 0;
}
