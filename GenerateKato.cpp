#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <list>
#include <cmath>
using namespace std;

class generateKato
{
public:
    generateKato(int _n) { n = _n; }
    void Generate();//在获得n后判断使用那个阶数的函数
    void write_katolist();//把生成的katolist写入txt中
    ~generateKato()
    {
        delete [] a;
        cout<< "Generate part end!"<<endl;
    }

    list<vector<int> > katolist;

private:
    int *a;
    int n;
    void orderTwo();//
    void orderThr();//
    void orderFou();//
    void orderFiv();//
    void orderSix();//六阶的所有kato项生成
    void orderSev();//七阶
    void orderEig();//八阶
    void orderNin();
    void orderTen();//十阶
    void Set();//将kato项中为零的去掉
    void find_simple(int weight, int b[]);//对kato项进行简化，最后生成最简的序列 01002102 -> 00102012
    void compare_katolist(int weight, int c[]);//将生成的最简序列写入katolist链表中，并进行数值从小到大排列
};
int main()
{
    int n;
    cout<< "Please enter the order n = ";
    cin>>n;
    cout<<endl;
    generateKato g(n);
    g.Generate();
    g.write_katolist();
    return 0;
}
void generateKato::Generate()
{
    switch(n)
    {
    case 2:
        orderTwo();
        break;
    case 3:
        orderThr();
        break;
    case 4:
        orderFou();
        break;
    case 5:
        orderFiv();
        break;
    case 6:
        orderSix();
        break;
    case 7:
        orderSev();
        break;
    case 8:
        orderEig();
        break;
    case 9:
        orderNin();
        break;
    case 10:
        orderTen();
        break;
    default:
        cout<< "wrong order n? Please make sure you enrer the right n! ";
    }

}
void generateKato::orderTwo()
{
    a = new int[3];
    int i0,i1,i2;
    for(i0 = 0; i0 < n; i0++)
    for(i1 = 0; i1 < n - i0; i1++)
    for(i2 = 0; i2 < n - i1 - i0; i2++)
        if(i0+i1+i2 == n-1)
        {
                a[0] = i0; a[1] = i1; a[2] = i2;
                Set();
        }
}
void generateKato::orderThr()
{
    a = new int[4];
    int i0,i1,i2,i3,i4;
    for(i0 = 0; i0 < n; i0++)
    for(i1 = 0; i1 < n - i0; i1++)
    for(i2 = 0; i2 < n - i1 - i0; i2++)
    for(i3 = 0; i3 < n - i2 - i1 - i0; i3++)
        if(i0+i1+i2+i3 == n-1)
        {
                a[0] = i0; a[1] = i1; a[2] = i2; a[3] = i3;
                Set();
        }
}
void generateKato::orderFou()
{
    a = new int[5];
    int i0,i1,i2,i3,i4;
    for(i0 = 0; i0 < n; i0++)
    for(i1 = 0; i1 < n - i0; i1++)
    for(i2 = 0; i2 < n - i1 - i0; i2++)
    for(i3 = 0; i3 < n - i2 - i1 - i0; i3++)
    for(i4 = 0; i4 < n - i3 - i2 - i1 - i0; i4++)
        if(i0+i1+i2+i3+i4 == n-1)
        {
                a[0] = i0; a[1] = i1; a[2] = i2; a[3] = i3;
                a[4] = i4;
                Set();
        }
}
void generateKato::orderFiv()
{
    a = new int[6];
    int i0,i1,i2,i3,i4,i5;
    for(i0 = 0; i0 < n; i0++)
    for(i1 = 0; i1 < n - i0; i1++)
    for(i2 = 0; i2 < n - i1 - i0; i2++)
    for(i3 = 0; i3 < n - i2 - i1 - i0; i3++)
    for(i4 = 0; i4 < n - i3 - i2 - i1 - i0; i4++)
    for(i5 = 0; i5 < n - i4 - i3 - i2 - i1 - i0; i5++)
        if(i0+i1+i2+i3+i4+i5 == n-1)
        {
                a[0] = i0; a[1] = i1; a[2] = i2; a[3] = i3;
                a[4] = i4; a[5] = i5;
                Set();
        }
}
void generateKato::orderSix()
{
    a = new int[7];
    int i0,i1,i2,i3,i4,i5,i6;
    for(i0 = 0; i0 < n; i0++)
    for(i1 = 0; i1 < n - i0; i1++)
    for(i2 = 0; i2 < n - i1 - i0; i2++)
    for(i3 = 0; i3 < n - i2 - i1 - i0; i3++)
    for(i4 = 0; i4 < n - i3 - i2 - i1 - i0; i4++)
    for(i5 = 0; i5 < n - i4 - i3 - i2 - i1 - i0; i5++)
    for(i6 = 0; i6 < n - i5 - i4 - i3 - i2 - i1 - i0; i6++)
        if(i0+i1+i2+i3+i4+i5+i6 == n-1)
        {
                a[0] = i0; a[1] = i1; a[2] = i2; a[3] = i3;
                a[4] = i4; a[5] = i5; a[6] = i6;
                Set();
        }
}
void generateKato::orderSev()
{
    a = new int[8];
    int i0,i1,i2,i3,i4,i5,i6,i7;
    for(i0 = 0; i0 < n; i0++)
    for(i1 = 0; i1 < n - i0; i1++)
    for(i2 = 0; i2 < n - i1 - i0; i2++)
    for(i3 = 0; i3 < n - i2 - i1 - i0; i3++)
    for(i4 = 0; i4 < n - i3 - i2 - i1 - i0; i4++)
    for(i5 = 0; i5 < n - i4 - i3 - i2 - i1 - i0; i5++)
    for(i6 = 0; i6 < n - i5 - i4 - i3 - i2 - i1 - i0; i6++)
    for(i7 = 0; i7 < n - i6 - i5 - i4 - i3 - i2 - i1 - i0; i7++)
        if(i0+i1+i2+i3+i4+i5+i6+i7 == n-1)
        {
                a[0] = i0; a[1] = i1; a[2] = i2; a[3] = i3;
                a[4] = i4; a[5] = i5; a[6] = i6; a[7] = i7;
                Set();
        }
}
void generateKato::orderEig()
{
    a = new int[9];
    int i0,i1,i2,i3,i4,i5,i6,i7,i8;
    for(i0 = 0; i0 < n; i0++)
    for(i1 = 0; i1 < n - i0; i1++)
    for(i2 = 0; i2 < n - i1 - i0; i2++)
    for(i3 = 0; i3 < n - i2 - i1 - i0; i3++)
    for(i4 = 0; i4 < n - i3 - i2 - i1 - i0; i4++)
    for(i5 = 0; i5 < n - i4 - i3 - i2 - i1 - i0; i5++)
    for(i6 = 0; i6 < n - i5 - i4 - i3 - i2 - i1 - i0; i6++)
    for(i7 = 0; i7 < n - i6 - i5 - i4 - i3 - i2 - i1 - i0; i7++)
    for(i8 = 0; i8 < n - i7 - i6 - i5 - i4 - i3 - i2 - i1 - i0; i8++)
        if(i0+i1+i2+i3+i4+i5+i6+i7+i8 == n-1)
        {
                a[0] = i0; a[1] = i1; a[2] = i2; a[3] = i3;
                a[4] = i4; a[5] = i5; a[6] = i6; a[7] = i7;
                a[8] = i8;
                Set();
        }

}
void generateKato::orderNin()
{
    a = new int[10];
    int i0,i1,i2,i3,i4,i5,i6,i7,i8,i9;
    for(i0 = 0; i0 < n; i0++)
    for(i1 = 0; i1 < n - i0; i1++)
    for(i2 = 0; i2 < n - i1 - i0; i2++)
    for(i3 = 0; i3 < n - i2 - i1 - i0; i3++)
    for(i4 = 0; i4 < n - i3 - i2 - i1 - i0; i4++)
    for(i5 = 0; i5 < n - i4 - i3 - i2 - i1 - i0; i5++)
    for(i6 = 0; i6 < n - i5 - i4 - i3 - i2 - i1 - i0; i6++)
    for(i7 = 0; i7 < n - i6 - i5 - i4 - i3 - i2 - i1 - i0; i7++)
    for(i8 = 0; i8 < n - i7 - i6 - i5 - i4 - i3 - i2 - i1 - i0; i8++)
    for(i9 = 0; i9 < n - i8 - i7 - i6 - i5 - i4 - i3 - i2 - i1 - i0; i9++)
        if(i0+i1+i2+i3+i4+i5+i6+i7+i8+i9 == n-1)
        {
                a[0] = i0; a[1] = i1; a[2] = i2; a[3] = i3;
                a[4] = i4; a[5] = i5; a[6] = i6; a[7] = i7;
                a[8] = i8; a[9] = i9;
                Set();
        }
}
void generateKato::orderTen()
{
    a = new int[11];
    int i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10;
    for(i0 = 0; i0 < n; i0++)
    for(i1 = 0; i1 < n - i0; i1++)
    for(i2 = 0; i2 < n - i1 - i0; i2++)
    for(i3 = 0; i3 < n - i2 - i1 - i0; i3++)
    for(i4 = 0; i4 < n - i3 - i2 - i1 - i0; i4++)
    for(i5 = 0; i5 < n - i4 - i3 - i2 - i1 - i0; i5++)
    for(i6 = 0; i6 < n - i5 - i4 - i3 - i2 - i1 - i0; i6++)
    for(i7 = 0; i7 < n - i6 - i5 - i4 - i3 - i2 - i1 - i0; i7++)
    for(i8 = 0; i8 < n - i7 - i6 - i5 - i4 - i3 - i2 - i1 - i0; i8++)
    for(i9 = 0; i9 < n - i8 - i7 - i6 - i5 - i4 - i3 - i2 - i1 - i0; i9++)
    for(i10 = 0; i10 < n - i9 - i8 - i7 - i6 - i5 - i4 - i3 - i2 - i1 - i0; i10++)
        if(i0+i1+i2+i3+i4+i5+i6+i7+i8+i9+i10 == n-1)
        {
                a[0] = i0; a[1] = i1; a[2] = i2; a[3] = i3;
                a[4] = i4; a[5] = i5; a[6] = i6; a[7] = i7;
                a[8] = i8; a[9] = i9; a[10] = i10;
                Set();
        }
}
void generateKato::Set()
{
    if((a[0] == 0 && a[n] == 0) || (a[0] != 0 && a[n] != 0))
    {
        //标定式子的正负号
        int weight = 1;
        vector<int> c;
        if((a[0] == 0) && a[n] == 0)
        {
            for(int i = 1; i < n; i++)
            {
                c.push_back(a[i]);
            }
            //weight_katolist.push_back(1);
            weight = 1;
            /*for(vector<int>::iterator it = c.begin(); it != c.end(); it++)
            {
                cout<<*it<<" ";
            }
            cout<<endl;*/
        } //进行轮转化最简形式。例110001->X10002(=1+1)->XX00021->XX000210->021 0在一分为二的情况下需要加一个负号。
        else if(a[0] != 0 && a[n] != 0)
        {
            vector<int> v;
            a[n] += a[0];
            for(int i = 1; i < n + 1; i++)
            {
                v.push_back(a[i]);
            }
            int first = 0;
            do
            {
                if(v[first] == 0)
                {
                    v.push_back(0);
                    for(int i = first + 1; i < n + first; i++)
                    {
                         c.push_back(v[i]);
                    }
                    weight = -1;
                    //weight_katolist.push_back(-1);
                    //cout<<endl;
                    break;
                }
                else
                {
                    v.push_back(v[first]);
                    first++;
                }
            }while(1);
            /*
            for(vector<int>::iterator it = c.begin(); it != c.end(); it++)
            {
                cout<<*it<<" ";
            }
            cout<<endl;system("pause");*/
        }
        int *temp = new int[n-1];

        for(int i = 0; i < n - 1; i++)
        {
            temp[i] = c[i];
            //cout<<temp[i];
        }
        //cout<<endl;
        find_simple(weight, temp);

        delete [] temp;
    }
}
void generateKato::find_simple(int weight, int b[])
{
    int m;
    int i,j,k,l;
    int *belta = new int[n-1];
    int *num_emes = new int[n-1];
    int *num_elements = new int[n-1];
    int *mid = new int[n-1];
    int *num_emesmidmat = new int[n-1];
    int *c = new int[n-1];
    int num_emesmid;
    m = 0;
    for(int i = 0; i < n-1; i++)
    {
        num_emes[i] = 0;
        c[i] = 0;
    }
    for(int i = 0; i < n-1; i++)
    {
        if(b[i] == 0)//记录序列当中0的个数，并将0的位置记住
        {
            belta[m] = i;
            //cout<<belta[m]<<" ";
            m = m + 1;

        }
        //cout<<b[i]<<" ";
    }
    //cout<<endl;
    if(m == 0) //一个零都没有
    {
        compare_katolist(weight, b);
        return;
    }
    else
    {
        for(i = 0; i < m; i++)
        {
            if(i == 0)//每两个0之间夹着多少个非0的数，belta[i==0]是第一个0的位置，它的坐标就是前面有几个非0数。
                num_elements[i] = belta[i];
            else
                num_elements[i] = belta[i] - belta[i - 1] - 1;
        }
        num_elements[m] = n - 1 - belta[m-1] - 1;//最后一个0后面的数字个数获得方法
    }
    /*cout<<m<<" ";
    for(int i = 0; i < m+1; i++)
        cout<<num_elements[i]<<" ";
    cout<<endl;*/
    /*for(int i = 0; i < v-1; i++)
        cout<<b[i]<<" ";
    cout<<endl;*/
    for(i = 0; i < m+1; i++)
    {
        if(num_elements[i] == 0)
        {
            num_emes[i] = 0;
            //cout<<"1:"<<num_emes[i]<<" ";
        }
        else if(num_elements[i] >= 1)//只有一个非0的数字。
        {
            if(i == 0)
            {
                num_emes[i] = b[0];
            }
            else
            {
                l = 0;
                for(j = 0; j < i; j++)           //求出当前点之前小括号里面数字的个数，没有包括零
                    l = l + num_elements[j];
                l = l + i;                       //加上i，此时的l就等于该点在b中的位置
                num_emes[i] = b[l];
                //cout<<"3:"<<num_emes[i]<<" ";

            }
        }
        /*else if(num_elements[i] > 1)
        {
            if(i == 0)
            {
                num_emesmid = 0;
                for(j = 0; j < num_elements[i]; j++)
                {
                    num_emes[i] = num_emes[i] + b[j] * 1.0 * pow(10.0, num_elements[i] - j - 1);
                    num_emesmid = num_emesmid + b[j] * 1.0 * pow(10.0, j);
                    //cout<<b[j]<<" ";
                }
                //cout<<"4:"<<num_emes[i]<<" "<<num_emesmid<<endl;
                if(num_emes[i] > num_emesmid)
                {
                    num_emes[i] = num_emesmid;
                    //cout<<"4:"<<num_emes[i]<<" ";
                    for(j = 0; j < num_elements[i]; j++)
                        mid[j] = b[num_elements[i] - j - 1];       //镜像对称，存在mid中
                    for(j = 0; j < num_elements[i]; j++)
                        b[j] = mid[j];
                }
            }
            else
            {
                l = 0;
                for(j = 0; j < i; j++)
                    l = l + num_elements[j];
                l = l + i;
                num_emesmid = 0;
                for(j = l; j < l + num_elements[i]; j++)
                {
                    num_emes[i] = num_emes[i] + b[j] * pow(10.0, num_elements[i] + l - 1 - j);
                    num_emesmid = num_emesmid + b[j] * pow(10.0, j - l);
                }
                //cout<<"5:"<<num_emes[i]<<" "<<num_emesmid<<endl;
                if(num_emes[i] > num_emesmid)
                {
                    num_emes[i] = num_emesmid;
                    //cout<<"5:"<<num_emes[i]<<" ";
                    for(j = l; j < l + num_elements[i]; j++)
                        mid[j] = b[l + num_elements[i] - 1 - (j - l)];
                    for(j = l; j < l + num_elements[i]; j++)
                        b[j] = mid[j];
                }
            }
        }*/
    }
    /*for(int i = 0; i < m+1; i++)
        cout<<num_emes[i]<<" ";
    cout<<endl;*/
    /*for(int i = 0; i < v-1; i++)
        cout<<b[i]<<" ";
    cout<<endl;*/
    for(i = 0; i < m + 1; i++)
        mid[i] = i;
    for(i = 0; i < m + 1; i++)
        num_emesmidmat[i] = num_emes[i];
    for(i = 0; i < m; i++)
    {
        for(j = i + 1; j < m + 1; j++)
        {
            if(num_emesmidmat[i] > num_emesmidmat[j])
            {
                num_emesmid = mid[i];
                mid[i] = mid[j];
                mid[j] = num_emesmid;
                num_emesmid = num_emesmidmat[i];
                num_emesmidmat[i] = num_emesmidmat[j];
                num_emesmidmat[j] = num_emesmid;
            }
        }
    }
    /*for(int i = 0; i < m+1; i++)
        cout<<num_emesmidmat[i]<<" "<<mid[i]<<" ";
    cout<<endl;
    for(int i = 0; i < v-1; i++)
        cout<<b[i]<<" ";
    cout<<" ";*/
    for(i = 0; i < m + 1; i++)
    {
        if(num_emes[mid[i]] == 0)
        {
            c[i] = 0;
            //cout<<i<<endl;
        }
        else
        {
            if(i == 0)
                l = 0;
            else
            {
                l = 0;
                for(j = 0; j < i; j++)
                    l = l + num_elements[mid[j]];
                l = l + i;
            }

            if(mid[i] == 0)
                k = 0;
            else
            {
                k = 0;
                for(j = 0; j < mid[i]; j++)
                    k = k + num_elements[j];
                k = k + mid[i];
            }

            for(j = l; j < l + num_elements[mid[i]]; j++)
            {
                c[j] = (b[k + j - l]);
                //cout<<a[j];
            }
            //cout<<j-1<<" ";


            //cout<<i<<endl;
            if(i != m)
            {
                //cout<<n + num_elements[mid[i]]<<endl;
                c[l + num_elements[mid[i]]] = 0;
            }
        }

    }
/*
    for(int i = 0; i < n - 1; i++)
        cout<<c[i]<<" ";
    cout<<endl;
*/
    compare_katolist(weight, c);
    delete [] belta;
    delete [] num_emes;
    delete [] num_elements;
    delete [] mid;
    delete [] num_emesmidmat;
    delete [] c;
}
void generateKato::compare_katolist(int weight, int c[])
{
    vector<int> katoTerm;
    vector<int>::iterator vector_it;
    list<vector<int> >::iterator list_it;
    for(int i = 0; i < n-1; i++)
    {
        katoTerm.push_back(c[i]);
    }
    katoTerm.push_back(weight);
    /*for(int i = 0; i < n; i++)
    {
        cout<<katoTerm.at(i);
    }
    cout<<endl;*/
    //cout<<katolist.size()<<endl;
    if(katolist.size() == 0)
        katolist.push_back(katoTerm);
    else
    {
        bool judge_same = false;
        int  same = 0;
        for(list_it = katolist.begin(); list_it != katolist.end(); list_it++)
        {
            for(int i = 0; i < (*list_it).size()-1; i++)
            {
                if(katoTerm.at(i) == (*list_it).at(i))
                    same++;
            }
            //cout<<same<<endl;
            if(same == (*list_it).size()-1)
            {
                (*list_it).back() += katoTerm.back();
                judge_same = true;
                break;
            }
            same = 0;
        }
        if(judge_same == false)
            katolist.push_back(katoTerm);
    }
}
void generateKato::write_katolist()
{
    ofstream fout1, fout2;
    char name1[50], name2[50];
    sprintf(name1,"kato%d.txt",n);
    sprintf(name2,"NumberOfkatoterms%d.txt",n);
    fout1.open(name1);
    fout2.open(name2);
    if(!fout1.is_open())
    {
        cerr<< "Can't open kato.txt for output.\n";
        exit(EXIT_FAILURE);
    }
    //-----------------------------------------------------
    int Count = 0;
    vector<int>::iterator vector_it;
    list<vector<int> >::iterator list_it;
    for(list_it = katolist.begin(); list_it != katolist.end(); list_it++)
    {
        for(vector_it = (*list_it).begin(); vector_it != (*list_it).end(); vector_it++)
        {
            if(*((*list_it).end()-1) != 0)
                fout1<<*vector_it<<" ";
        }
        if(*((*list_it).end()-1) != 0){
            fout1<<endl;
        Count++;
        }
    }
    //fout<<"Count = "<<Count<<endl;
    fout2<<Count<<endl;

    fout2.close();
    fout1.close();
}
