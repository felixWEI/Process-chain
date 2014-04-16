//=================================================
//Graph.cpp -- algorithm of process-chain part two
//Graph part: last edit 2013.2.19
//
//Coder: Wei
//=================================================
//=================================================
//=================================================
//�����õ��������������飬��Ϊ�������ڱ����ʱ��
//����Ҫ֪������ά����ȷ��ֵ��ά����Ҫ�ǳ�������
//���������Ҫ�ڳ���ʼ�������ĳ��Ƚ��ж���Ӧ��ʹ
//�ö�̬����Ķ��巽ʽ�����ó�������鶨�巽ʽ�����
//�����������
//=================================================
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <list>
#include <vector>
#include <iomanip>

using namespace std;

class graph
{
public:
    graph(){ cout<< "Wrong construct! Need the order v and dimension d !!"<<endl; exit(0); }
    graph(int _v, int _d);
    ~graph(){
        delete [] a;
        foutA.close();
        foutB.close();
        cout<<"Calculation Finish!"<<endl;

    }
    //===================================
    void second_step();
    void find_hop(int num1)const;
    bool judge_loop()const;
    //����˼·�������Ҫ����һЩ��̬���飬��þ����ڵ������ĺ�������Ϊ��������ú����������ܹ���������������������ɨ��ǰѩ����һ��new�Ͷ�Ӧ��һ��delete
    int  *cfour(int a_in[], int a_out[], int &d_weight)const;            //��ת�Գƺ͹���ĳЩ�Խ��ߵĶԳ�
    int  comp_diagram(int a_in[], int a_new[], int comp_res)const;       //�Ա��������̴�С�����֣������comp_res = 0
    int  *sym_oper(int a_in[], int a_out[], int ios)const;               //
    int  *trans_sysmmetry(int a_in[], int a_out[], int &d_weight, int &num_sites);   //ƽ�ƶԳ���
    int  *find_small(int ***arrow_sites, int *a_out)const;               //��ԾǨ������ֵ��С����
    int  *smid(int a_in[], int a_out[])const;                            //��¼ԾǨ����ĳ����ڸ��������Ƿ���ԾǨ
    int  get_sitenum(int a_in[]);
    void adiagram(int a_in[], int d_weight);                             //�����ɵ�������к�Ȩ��д��һ������
    //===================================
    void third_step();
    int  **mapping_oper(int c_in[], int **c_out);                        //��ԾǨ������ת����һ����ά�Ĵ�ĳ������ĳ�������
    int  ***platoon(int ***oper_collection, int **oper, int &num_process);
    int  **find_topo(int **oper, int **arrow, int &site_num);            //������ת�����������޹ص����ֹ���000222->1234321
    list<vector<int> >  get_topo_list(int **arrow, list<vector<int> > topo_list, int d_weight);
    list<vector<int> >  map_topo_list(int **arrow, list<vector<int> > topo_list, int &t_weight);
    bool jud_swap(int **oper, int m, int i, bool judge_swap);
    int  **Swap(int **oper, int i, int j);
    double *cal_eng_dia(int ***oper_collection, int m, int *eng_weight, int **eng_katolist, int num_process, double *energy_diagram, double miu, double delta_miu);
    //===================================
private:
    int *a;
    int v;
    int d;
    int v_fac;          //v��ԾǨ��ȫ����
    int g;             //�����
    int num;           //katolist������Ŀ
    vector<int>        site;
    list<vector<int> > diaList;
    vector<int>  weight;
    ifstream fin;
    ofstream foutA, foutB;

};
int main()
{
	int v;
    cout<<"Please enter the order v = ";
    cin>>v;
	graph g(v,2);
	g.second_step();
    g.third_step();


	return 0;
}
graph::graph(int _v, int _d):v(_v), d(_d)
{
    a = new int[v];
    v_fac = 1;
    g = 1;
    int temp_v = v+2;
    do
    {
        v_fac *= temp_v;
        temp_v--;
    }while(temp_v > 1);
    char filename[100];
    sprintf(filename,"NumberOfkatoterms%d.txt",v+2);
    fin.open(filename);
    fin>>num;
    fin.close();
    fin.clear();

    foutA.open("testA.txt");
    foutB.open("testB.txt");
}
void graph::second_step()
{
    int comp_res = 0;
	int	comp_res2 = 0;
	int	comp_res3 = 0;
    int d_weight, d_weight1;
    int *a_new = new int[v];
    int *a_small = new int[v];
    int num_sites = 0;
    int num1;
	for(num1 = 0; num1 < pow((float)4, v); num1++)//�������߷�
    {
		find_hop(num1);
		/*for(int i = 0; i < v; i++)
        {
            cout<<a[i];
        }
        cout<<endl;*/
        a_new = smid(a, a_new);
		/*for(int i = 0; i < v; i++)
        {
            cout<<a_new[i];
        }
        cout<<endl;*/
        //system("pause");
        comp_res = comp_diagram(a, a_new, comp_res);
        //cout<<comp_res<<endl;
        //system("pause");
        if(comp_res == 0)
        {
            a_new = cfour(a, a_new, d_weight);
    		/*for(int i = 0; i < v; i++)
            {
                cout<<a[i];
            }
            cout<<endl;
            cout<<d_weight<<endl;*/
            comp_res2 = comp_diagram(a, a_new, comp_res2);
            if(comp_res2 == 0)
            {
                /*for(int i = 0; i < v; i++)
                {
                    cout<<a[i];
                }
                cout<<endl;*/
                //system("pause");
                //cout<<d_weight<<endl;
                //a_small = trans_sysmmetry(a, a_small, d_weight, num_sites);
                /*for(int i = 0; i < v; i++)
                {
                    cout<<a_small[i];
                }
                cout<<endl;*/
                //cout<<num_sites<<endl;
                //cout<<d_weight<<endl;
                num_sites = get_sitenum(a);
                //cout<<num_sites<<endl;
                d_weight = 8 / d_weight;
                //cout<<d_weight<<endl;
                //system("pause");
                //comp_res3 = comp_diagram(a, a_small, comp_res3);
                //cout<<comp_res3<<endl;
                //if(comp_res3 == 0)
                //{
                    //cout<<d_weight<<endl;
                    site.push_back(num_sites);
                    adiagram(a, d_weight);
                //}
            }
        }
    }
    //cout<<Count<<endl;

    delete [] a_new;
    delete [] a_small;

}
void graph::find_hop(int num1)const
{
    for(int i = 0; i < v; i++)
        a[i] = 0;
    for(int i = 0; i < v; i++)
    {
        if(num1 < 2*d)
        {
            a[i] = num1;
            break;
        }
        else
        {
            a[i] = num1 % (2*d);
            num1 = (num1 - a[i]) / (2*d);
        }
    }
    /*for(int i = 0; i < v; i++)
        cout<<a[i];
    cout<<endl;
    system("pause");*/
}
bool graph::judge_loop()const
{
    int *num_num = new int[2*d];
    for(int i = 0; i< 2*d; i++)
        num_num[i] = 0;
    for(int i = 0; i < v; i++)
        for(int j = 0; j < 2*d; j++)
        {
            if(a[i] == j)
                num_num[j] += 1;
        }
     /*for(int i = 0; i < 2*d; i++)
        cout<<num_num[i]<<" ";
     cout<<endl;*/
    //����ά�ȵ��жϣ�ά�ȱ��ˣ�����Ҫ��
    if(num_num[0] == num_num[2])
    {
        if(num_num[1] == num_num[3])
        {
            return false;
        }
        else
            return true;
    }
    else
        return true;
}
int *graph::smid(int a_in[], int a_out[])const
{
    int ***arrow_sites = new int**[2*v+1];
    for(int i = 0; i < 2*v+1; i++)
    {
        arrow_sites[i] = new int*[2*v+1];
        for(int j = 0; j < 2*v+1; j++)
            arrow_sites[i][j] = new int[2*d];
    }
    for(int i = 0; i < 2*v+1; i++)
        for(int j = 0; j < 2*v+1; j++)
            for(int k = 0; k < 2*d; k++)
                arrow_sites[i][j][k] = 0;
    int x = v;
    int y = v;
    for(int i = 0; i < v; i++)
    {
        if(a_in[i] == 0)
        {
            arrow_sites[x][y][0] += 1;
            x += 1;
        }
        else if(a_in[i] == 1)
        {
            arrow_sites[x][y][1] += 1;
            y -= 1;
        }
        else if(a_in[i] == 2)
        {
            arrow_sites[x][y][2] += 1;
            x -= 1;
        }
        else if(a_in[i] == 3)
        {
            arrow_sites[x][y][3] += 1;
            y += 1;
        }
    }
    a_out = find_small(arrow_sites, a_out);
    for(int i = 0; i < 2*v+1; i++)
    {
        for(int j = 0; j < 2*v+1; j++)
            delete [] arrow_sites[i][j];
        delete [] arrow_sites[i];
    }
    delete [] arrow_sites;
    return a_out;

}
int *graph::find_small(int ***arrow_sites, int *a_out)const
{
    bool jump_cycle;
    int **c = new int*[v];
	for(int i = 0; i < v; i++)
		c[i] = new int[2*d];
    bool judge_end;
    int l = 0;
    int x = v;
    int y = v;
    int n = 0;
    for(int i = 0; i < v; i++)
        for(int j = 0; j < 2*d; j++)
            c[i][j] = -1;
/*
    for(int i = 0; i < 2*d; i++)
        cout<<arrow_sites[v][v][i];
    cout<<endl;
    system("pause");
*/
    jump_cycle = false;
    do
    {
        n += 1;
        if(n > v)
        {
            cout<<"wrong with the hopping loop!"<<endl;
            break;
        }
        if(c[n-1][0] == -1)
        {
            l = 0;
            for(int k = 0; k < 2*d; k++)
            {

                if(arrow_sites[x][y][k] > 0)
                {
                    c[n-1][l] = k;
                    l += 1;
                }
            }
        }
        //--------------------------------------
        arrow_sites[x][y][c[n-1][0]] -= 1;
        a_out[n-1] = c[n-1][0];
        //cout<<a_out[n-1];
        //system("pause");
        //cout<<"("<<x<<","<<y<<")->";
        if(c[n-1][0] == 0)
            x += 1;
        else if(c[n-1][0] == 1)
            y -= 1;
        else if(c[n-1][0] == 2)
            x -= 1;
        else if(c[n-1][0] == 3)
            y += 1;
        //cout<<"("<<x<<","<<y<<")->";
        //system("pause");
        //---------------------------------------
        //---------------------------------------
        /*for(int i = 0; i < l; i++)
            cout<<c[i][n-1];
        cout<<endl;
        system("pause");*/
        //if(x == v && y == v)
        //{
            judge_end = true;
            for(int k = 0; k < 2*d; k++)
            {
                if(arrow_sites[x][y][k] > 0)
                {
                    judge_end = false;
                    break;
                }
            }
            if(judge_end)
            {
                if( n == v )
                    jump_cycle = true;
                else
                {

                    //while�����ж������ڽ���ѭ���塣��do-while�����Ƚ���ѭ���壬Ȼ�����һ��ѭ��������жϣ�
                    while(c[n-1][1] == -1)
                    {
                        a_out[n-1] = -1;
                        if(c[n-1][0] == 0)
                            x -= 1;
                        else if(c[n-1][0] == 1)
                            y += 1;
                        else if(c[n-1][0] == 2)
                            x += 1;
                        else if(c[n-1][0] == 3)
                            y -= 1;
                        arrow_sites[x][y][c[n-1][0]] += 1;
                        c[n-1][0] = -1;
                        n -= 1;
                    }
                    a_out[n-1] = -1;
                    if(c[n-1][0] == 0)
                        x -= 1;
                    else if(c[n-1][0] == 1)
                        y += 1;
                    else if(c[n-1][0] == 2)
                        x += 1;
                    else if(c[n-1][0] == 3)
                        y -= 1;
                    arrow_sites[x][y][c[n-1][0]] += 1;
                    c[n-1][0] = c[n-1][1];
                    c[n-1][1] = c[n-1][2];
                    c[n-1][2] = c[n-1][3];
                    c[n-1][3] = -1;
                    n -= 1;

                }
            }
        //}
    }while(jump_cycle == false);
    //system("pause");
    for(int i = 0; i < v; i++)
    {
        //cout<<a_out[i];
        delete [] c[i];
    }
    //cout<<endl;
    delete [] c;
    return a_out;
}
int graph::comp_diagram(int a_in[], int a_new[], int comp_res)const
{
    for(int i = 0; i < v; i++)
    {
        if(a_in[i] > a_new[i])
        {
            comp_res = 1;
            break;
        }
        else if(a_in[i] < a_new[i])
        {
            comp_res = -1;
            break;
        }
        else
            comp_res = 0;
    }
    /*for(int i = 0; i < v; i++)
        cout<<a_in[i];
    cout<<endl;
    for(int i = 0; i < v; i++)
        cout<<a_new[i];
    cout<<endl;*/
    return comp_res;
}
int *graph::cfour(int a_in[], int a_out[], int &d_weight)const
{
    int *a_mid = new int[v];
    int *a_new1 = new int[v];
    int comp_res1 = 0;
    int comp_res2 = 0;
    for(int i = 0; i < v; i++)
    {
        a_out[i] = a_in[i];
        //cout<<a_out[i];
    }
    //cout<<endl;
    //system("pause");
    d_weight = 1;


   //========================�ҶԳ���===========================
   //90�㣬180�㣬270�㣬x=0, y=0; y = x, y = -x ����
   for(int ios = 1; ios <= 7; ios++)
   {
       a_mid = sym_oper(a_in, a_mid, ios);
/*
       for(int i = 0; i < v; i++)
            cout<<a_mid[i];
       cout<<endl;
*/
       a_new1 = smid(a_mid, a_new1);
       /*for(int i = 0; i < v; i++)
            cout<<a_new1[i];
       cout<<endl;
       system("pause");*/

       comp_res1 = comp_diagram(a_in, a_new1, comp_res1);
       //cout<<comp_res1<<endl;
       if(comp_res1 == 0)
       {
           d_weight += 1;
       }
       else if(comp_res1 > 0)
       {
            comp_res2 = comp_diagram(a_out, a_new1, comp_res2);

            //cout<<"comp_res2 = "<<comp_res2<<endl;
            //system("pause");

            if(comp_res2 == 1)
            {
                for(int i = 0; i < v; i++)
                    a_out[i] = a_new1[i];
            }
            /*
            for(int i = 0; i < v; i++)
                cout<<a_new[i];
            cout<<endl<<endl;
            system("pause");
            */
       }

   }
   /*for(int i = 0; i < v; i++)
        cout<<a_out[i];
   cout<<endl;
   cout<<d_weight<<endl;*/
   //system("pause");

   delete [] a_mid;
   delete [] a_new1;
   return a_out;

}
int *graph::sym_oper(int a_in[], int a_out[], int ios)const
{
    for(int i = 0; i < v; i++)
        a_out[i] = a_in[i];
    if(ios == 1)   //����x�Գ�
    {
        for(int i = 0; i < v; i++)
        {
            if(a_in[i] == 1)
                a_out[i] = 3;
            else if(a_in[i] == 3)
                a_out[i] = 1;
        }
    }
    else if(ios == 2)//����y�Գ�
    {
        for(int i = 0; i < v; i++)
        {
            if(a_in[i] == 0)
                a_out[i] = 2;
            else if(a_in[i] == 2)
                a_out[i] = 0;
        }
    }
    else if(ios == 3)//����y=x�Գ�
    {
        for(int i = 0; i < v; i++)
        {
            if(a_in[i] == 0)
                a_out[i] = 3;
            else if(a_in[i] == 1)
                a_out[i] = 2;
            else if(a_in[i] == 2)
                a_out[i] = 1;
            else if(a_in[i] == 3)
                a_out[i] = 0;
        }
    }
    else if(ios == 4)//����y=-x�Գ�
    {
        for(int i = 0; i < v; i++)
        {
            if(a_in[i] == 0)
                a_out[i] = 1;
            else if(a_in[i] == 1)
                a_out[i] = 0;
            else if(a_in[i] == 2)
                a_out[i] = 3;
            else if(a_in[i] == 3)
                a_out[i] = 2;
        }
    }
    else if(ios == 5)//90����ת
    {
        for(int i = 0; i < v; i++)
        {
            if(a_in[i] == 0)
                a_out[i] = 3;
            else if(a_in[i] == 1)
                a_out[i] = 0;
            else if(a_in[i] == 2)
                a_out[i] = 1;
            else if(a_in[i] == 3)
                a_out[i] = 2;
        }
    }
    else if(ios == 6)//180����ת
    {
        for(int i = 0; i < v; i++)
        {
            if(a_in[i] == 0)
                a_out[i] = 2;
            else if(a_in[i] == 1)
                a_out[i] = 3;
            else if(a_in[i] == 2)
                a_out[i] = 0;
            else if(a_in[i] == 3)
                a_out[i] = 1;
        }
    }
    else if(ios == 7)//270����ת
    {
        for(int i = 0; i < v; i++)
        {
            if(a_in[i] == 0)
                a_out[i] = 1;
            else if(a_in[i] == 1)
                a_out[i] = 2;
            else if(a_in[i] == 2)
                a_out[i] = 3;
            else if(a_in[i] == 3)
                a_out[i] = 0;
        }
    }
    else
        cout<<"sym_oper: Error! The ios must between 1 and 7!\n";
    return a_out;
}
int graph::get_sitenum(int a_in[])
{
    int **site_coordinate = new int*[v+1];//��¼ԾǨ��ͷ��β�ĸ������
	for(int i = 0; i < v+1; i++)
		site_coordinate[i] = new int[2];
    bool same_site;
    int num_sites_temp;
    int x = v;
    int y = v;
    //ԾǨ����
    site_coordinate[0][0] = x;
    site_coordinate[0][1] = y;
    num_sites_temp = 0;
    for(int i = 0; i < v; i++)
    {
        if(a_in[i] == 0)
            x += 1;
        else if(a_in[i] == 1)
            y -= 1;
        else if(a_in[i] == 2)
            x -= 1;
        else if(a_in[i] == 3)
            y += 1;

        same_site = false;
        for(int j = 0; j <= num_sites_temp; j++)
        {
            if(site_coordinate[j][0] == x && site_coordinate[j][1] == y )
            {
                same_site = true;
                break;
            }
        }
        //cout<<same_site<<endl;
        if(same_site == false)
        {
            num_sites_temp += 1;
            site_coordinate[num_sites_temp][0] = x;//������ǲ�ͬ�ĸ���λ����Ϣ,v+1�����
            site_coordinate[num_sites_temp][1] = y;
        }
    }
    /*cout<<num_sites_temp<<endl;
    system("pause");*/

    return num_sites_temp;

}
int *graph::trans_sysmmetry(int a_in[], int a_out[], int &d_weight, int &num_sites)
{
    //==============trans_sysmmetry======================
    int *a_mid = new int[v];
    int *a_new = new int[v];
    int *a_small = new int[v];
    int ***arrow_sites = new int**[2*v+1];
    int ***newarrow_sites = new int**[2*v+1];
    for(int i = 0; i < 2*v+1; i++)
    {
        arrow_sites[i] = new int*[2*v+1];
        newarrow_sites[i] = new int*[2*v+1];
        for(int j = 0; j < 2*v+1; j++)
        {
            newarrow_sites[i][j] = new int[2*d];
            arrow_sites[i][j] = new int[2*d];
        }

    }
    int **site_coordinate = new int*[v+1];//��¼ԾǨ��ͷ��β�ĸ������
	for(int i = 0; i < v+1; i++)
		site_coordinate[i] = new int[2];
    int **newsite_coordinate = new int*[v+1];
	for(int i = 0; i < v+1; i++)
		newsite_coordinate[i] = new int[2];
    bool same_site;
    int d_weight_temp;
    int comp_res = 0;
    int num_sites_temp = num_sites;
    a_out = cfour(a_in, a_out, d_weight_temp);
    comp_res = comp_diagram(a_in, a_out, comp_res);
    //cout<<d_weight_temp<<endl;
    //system("pause");
    if(comp_res != 0)
    {
        num_sites = 0;
        return a_out;
    }
    int x = v;
    int y = v;
    //ԾǨ����
    site_coordinate[0][0] = x;
    site_coordinate[0][1] = y;
    for(int i = 0; i < 2*v+1; i++)
    {
        for(int j = 0; j < 2*v+1; j++)
        {
            for(int k = 0; k < 2*d; k++)
            {
                arrow_sites[i][j][k] = 0;
                newarrow_sites[i][j][k] = 0;
            }
        }
    }
    num_sites_temp = 0;
    for(int i = 0; i < v; i++)
    {
        arrow_sites[x][y][a_in[i]] += 1;
        if(a_in[i] == 0)
            x += 1;
        else if(a_in[i] == 1)
            y -= 1;
        else if(a_in[i] == 2)
            x -= 1;
        else if(a_in[i] == 3)
            y += 1;

        same_site = false;
        for(int j = 0; j <= num_sites_temp; j++)
        {
            if(site_coordinate[j][0] == x && site_coordinate[j][1] == y )
            {
                same_site = true;
                break;
            }
        }
        //cout<<same_site<<endl;
        if(same_site == false)
        {
            num_sites_temp += 1;
            site_coordinate[num_sites_temp][0] = x;//������ǲ�ͬ�ĸ���λ����Ϣ,v+1�����
            site_coordinate[num_sites_temp][1] = y;
        }
    }
    d_weight = d_weight_temp;
    bool open;
    open = judge_loop();
    //cout<<open<<endl;
    if(open)
    {
        num_sites = num_sites_temp;
        //cout<<d_weight<<" "<<num_sites<<endl;
        //system("pause");
        return a_out;
    }
    else{

        /*int**a_tran = new int*[num_sites_temp];
        for(int i = 0; i < num_sites_temp; i++)
            a_tran[i] = new int[v];
        for(int i = 0; i < num_sites_temp; i++)
        {
            for(int j = 0; j < v; j++)
            {
                a_tran[i][j] = 0;
            }
        }
        for(int i = 0; i < v; i++)
            a_out[i] = a_in[i];
        //cout<<d_weight<<endl;
        //system("pause");
        //������ĳ������ƽ�ƣ�����ƽ��
        //ͷβ���Ͳ���ƽ�Ʋο����ˣ���Ϊ�ο�ͷβ����ƽ����ʵ���ǳ�Գ�
        for(int i = 1; i <= num_sites_temp; i++)
        {
            x = site_coordinate[i][0] - site_coordinate[0][0];//i�������ʼ��ľ���
            y = site_coordinate[i][1] - site_coordinate[0][1];
            for(int k = 0; k <= num_sites_temp; k++)
            {
                newsite_coordinate[k][0] = site_coordinate[k][0] - x;//������ȷ��ƽ�ƺ������
                newsite_coordinate[k][1] = site_coordinate[k][1] - y;
            }
            for(int k = 0; k <= num_sites_temp; k++)
            {
                for(int j = 0; j < 2*d; j++)
                {
                    int x1 = newsite_coordinate[k][0];
                    int y1 = newsite_coordinate[k][1];
                    int x2 = site_coordinate[k][0];
                    int y2 = site_coordinate[k][1];
                    newarrow_sites[x1][y1][j] = arrow_sites[x2][y2][j];//ƽ�ƺ�ԭ�ȵ�arrow��Ϣд��newarrow��
                }
            }
            //------��newarrow_site��ԾǨ�������Ӧ------------------------------------
            a_mid = find_small(newarrow_sites, a_mid);//ÿ�ε�ƽ�Ƴ��ֵ��µ����ж���Ҫ��small
            for(int j = 0; j < v; j++)
                a_tran[i-1][j] = a_mid[j];
        }
        for(int i = 0; i < num_sites_temp; i++)
        {
            a_new = cfour(a_tran[i], a_new, d_weight_temp);
            comp_res = comp_diagram(a_in, a_new, comp_res);
            if(comp_res == 0)
            {
                d_weight += d_weight_temp;
            }
            else if(comp_res > 0)
            {
                for(int i = 0; i < v; i++)
                    a_out[i] = a_new[i];
            }
        }
        //cout<<d_weight<<" "<<num_sites_temp<<endl;
        //system("pause");
        for(int i = 0; i < num_sites_temp; i++)
            delete a_tran[i];
        delete a_tran;*/
    }
    //cout<<d_weight<<endl;
    //--------------------------------------------
    delete [] a_mid;
    delete [] a_new;
    delete [] a_small;
    for(int i = 0; i <v; i++)
    {
         delete [] site_coordinate[i];
         delete [] newsite_coordinate[i];
    }
    delete [] site_coordinate;
    delete [] newsite_coordinate;
    for(int i = 0; i < 2*v+1; i++)
    {
        for(int j = 0; j < 2*v+1; j++)
        {
            delete [] arrow_sites[i][j];
            delete [] newarrow_sites[i][j];
        }
        delete [] arrow_sites[i];
        delete [] newarrow_sites[i];
    }
    delete [] arrow_sites;
    delete [] newarrow_sites;
    /*for(int i = 0; i < num_sites_temp; i++)
    {
        delete [] a_tran[i];
    }
    delete [] a_tran;*/
    //---------------------------------------------
    num_sites = num_sites_temp;
    return a_out;
}
void graph::adiagram(int a_in[],int d_weight)
{
    vector<int> avec;
    weight.push_back(d_weight);
    for(int i = 0; i < v; i++)
    {
        avec.push_back(a_in[i]);
        //cout<<avec.at(i)<<" ";
    }
    //cout<<d_weight;
    //cout<<endl;
    diaList.push_back(avec);
}
void graph::third_step()
{
    //����������ַ������壬��������������������ʱҪ��ǿ������ת����ά(int**)eng_katolist
    int *eng_weight = new int[num];
    int **eng_katolist = new int*[num];
    for(int i = 0; i < num; i++)
        eng_katolist[i] = new int[v+1];
    //-----------------------------------------
    char filename[100];
    sprintf(filename,"kato%d.txt",v+2);
    fin.open(filename);
    if(!fin.is_open())
    {
        cerr<<"Something wrong during open kato.txt!"<<endl;
        exit(0);
    }
    //cout<<num<<endl;
    int katoTerm;
    int countNum = 1;
    int j = 0;
    int i = 0;
    while(fin>>katoTerm)
    {
        if(countNum % (v+2) != 0)
        {
            eng_katolist[i][j] = katoTerm;
            //cout<<eng_katolist[i][j];
            countNum++;
            j++;
        }
        else
        {
            eng_weight[i] = katoTerm;
            //cout<<" "<<eng_weight[j]<<endl;
            countNum++;
            j = 0;
            i++;
        }
    }
/*
    for(int i = 0; i < num; i++)
    {
        for(int j = 0; j < v+1; j++)
            cout<<eng_katolist[i][j]<<" ";
        cout<<eng_weight[i];
        cout<<endl;
    }
    cout<<endl;
    system("pause");
*/
    //cout<<num<<endl;
    //system("pause");
    //------------------------------------------
    int *c = new int[v];
    int m = num;
    int site_num;
    int num_process = 0;
    int d_weight;
    int t_weight;
    double *energy_diagram = new double[2];
    double *eOrder_V = new double[2];
    for(int i = 0; i < 2; i++)
    {
        energy_diagram[i] = 0.0;
        eOrder_V[i] = 0.0;
    }
    list<vector<int> >   topo_list;
    list<vector<int> >::iterator it_list;
    vector<int>::iterator it_vect;
    vector<int>::iterator it_weight;
    vector<int>::iterator it_site;
    //--------------------------------------------------
    int **oper;
    int ***oper_collection;
    oper = new int*[v];
    for(int i = 0; i < v; i++)
        oper[i] = new int[2*d];
    //arrow�д����ԾǨ�����и��ı�ǡ�000222����Ϊ1234321
    int **arrow = new int*[v];
    for(int i = 0; i < v; i++)
        arrow[i] = new int[2];
    oper_collection = new int **[v+2];
    for(int i = 0; i < v+2; i++)
    {
        oper_collection[i] = new int *[2*d];
        for(int j = 0; j < 2*d; j++)
        {
            oper_collection[i][j] = new int [v_fac];
        }
    }
    //-------------------------------------------------
    for(it_list = diaList.begin(), it_weight = weight.begin(), it_site = site.begin(); it_list != diaList.end(), it_weight != weight.end(), it_site != site.end(); \
        it_list++, it_weight++, it_site++)
    {
        int i = 0;
        for(it_vect = (*it_list).begin(); it_vect != (*it_list).end(); it_vect++)
        {
            c[i++] = *it_vect;
            //cout<<*it_vect;
        }
        //cout<<endl;
        d_weight = *it_weight;
        //cout<<d_weight<<endl;
        oper = mapping_oper(c, oper);
        site_num = *it_site + 1;
        arrow = find_topo(oper, arrow, site_num);
/*
        for(int i = 0; i < v; i++)
            cout<<arrow[i][0];
        cout<<arrow[v-1][1];
        cout<<endl;
*/
        topo_list = get_topo_list(arrow, topo_list, d_weight);
    }
/*
    for(it_list = topo_list.begin(); it_list != topo_list.end(); it_list++)
    {
        for(it_vect = (*it_list).begin(); it_vect != (*it_list).end(); it_vect++)
            cout<<*it_vect<<" ";
        cout<<endl;
    }
    cout<<endl;
    system("pause");
*/
    ofstream energyA, energyB;
    char name1[100];
    char name2[100];
    sprintf(name1,"alphaA_sl_%d_deltamiu=0.0.txt", v);
    sprintf(name2,"alphaB_sl_%d_deltamiu=0.0.txt", v);
    energyA.open(name1);
    energyB.open(name2);
    list<vector<int> >   topo_list_temp;
    double delta_miu = 0.0;
    for(double miu = 0.01; miu < 1.0; miu += 0.01){
    //double miu  = 0.01;
        topo_list_temp = topo_list;
    for(it_list = diaList.begin(), it_weight = weight.begin(), it_site = site.begin(); it_list != diaList.end(), it_weight != weight.end(), it_site != site.end(); \
        it_list++, it_weight++, it_site++)
    {
        int i = 0;
        for(it_vect = (*it_list).begin(); it_vect != (*it_list).end(); it_vect++)
        {
            c[i++] = *it_vect;
            //cout<<*it_vect;
        }
        //cout<<endl;
        d_weight = *it_weight;
        //cout<<d_weight<<endl;
        oper = mapping_oper(c, oper);
        site_num = *it_site + 1;
        //cout<<site_num<<endl;
        arrow = find_topo(oper, arrow, site_num);
        //t_weight = 0;
        topo_list = map_topo_list(arrow, topo_list, t_weight);
        //cout<<t_weight<<endl;
        if(t_weight != 0)
        {
            //cout<<t_weight<<endl;
            oper_collection = platoon(oper_collection, oper, num_process);
            //cout<<num_process<<endl;
            //miu = 0.15;
            //cout<<site_num<<endl;
            energy_diagram = cal_eng_dia(oper_collection, m, eng_weight, eng_katolist, num_process, energy_diagram, miu, delta_miu);
            //cout<<energy_diagram[0]<<" "<<energy_diagram[1]<<endl;system("pause");
            energy_diagram[0] *= t_weight;
            energy_diagram[1] *= t_weight;
            //cout<<miu<<" "<<energy_diagram<<endl;//
            eOrder_V[0] += energy_diagram[0];
            eOrder_V[1] += energy_diagram[1];
        }
    }
        //cout<<fixed<<setprecision(6)<<eOrder_V[0]<<endl;system("pause");
        energyA<<miu<<" "<<fixed<<setprecision(6)<<eOrder_V[0]<<endl;
        energyB<<miu<<" "<<fixed<<setprecision(6)<<eOrder_V[1]<<endl;
        topo_list = topo_list_temp;
        eOrder_V[0] = 0.0;
        eOrder_V[1] = 0.0;
    }
    //-------------------------------------------
    delete [] c;

    delete [] energy_diagram;
    delete [] eOrder_V;

    for(int i = 0; i < v; i++)
        delete [] oper[i];
    delete [] oper;

    for(int i = 0; i < v; i++)
    {
        for(int j = 0; j < 2*d; j++)
        {
            delete [] oper_collection[i][j];
        }
        delete [] oper_collection[i];
    }
    delete [] oper_collection;

    for(int i = 0; i < v; i++)
    {
        delete [] arrow[i];
    }
    delete [] arrow;
    //--------------------------------------------
}
int** graph::mapping_oper(int c_in[], int **c_out)
{
    for(int i = 0; i < v; i++)
        for(int j = 0; j < 2*d; j++)
            c_out[i][j] = 0;


    for(int i = 0; i < v; i++)
    {
        //2dά��ʾ���Ǵ�ĳ��(00)��ĳ��(01)������仯������0102��ʾ���01->02
        if(c_in[i] == 0)
        {
            c_out[i][2] = c_out[i][0] + 1;
            c_out[i][3] = c_out[i][1];
        }
        else if(c_in[i] == 1)
        {
            c_out[i][2] = c_out[i][0];
            c_out[i][3] = c_out[i][1] - 1;
        }
        else if(c_in[i] == 2)
        {
            c_out[i][2] = c_out[i][0] - 1;
            c_out[i][3] = c_out[i][1];
        }
        else if(c_in[i] == 3)
        {
            c_out[i][2] = c_out[i][0];
            c_out[i][3] = c_out[i][1] + 1;
        }
        //���Թ۲�һ�µ���˶��켣
        //cout<<"("<<oper[0][i]<<","<<oper[1][i]<<") -> "<<"("<<oper[2][i]<<","<<oper[3][i]<<")"<<endl;
        //�ѵ��ƶ�һ�£������´�ѭ��
        if(i < v-1)
        {
            c_out[i+1][0] = c_out[i][2];
            c_out[i+1][1] = c_out[i][3];
        }
    }
    //cout<<endl;
    /*for(int i = 2; i < 4; i++)
    {
        if(c_out[v-1][i] != 0)
            cout<< "mapping_oper: Something wrong with the mapping!"<<endl;
    }*/
    /*for(int i = 0; i < v; i++)
    {
        cout<<c_out[i][0]<<c_out[i][1]<<" ";
    }
    cout<<c_out[v-1][2]<<c_out[v-1][3];
    cout<<endl<<endl;*/
    return c_out;
}
int **graph::find_topo(int **oper, int **arrow, int &site_num)
{
    bool judge_same;
    int numm;
    int **site_mapping = new int*[site_num];
    for(int i = 0; i < site_num; i++)
        site_mapping[i] = new int[2];
    arrow[0][0] = 1;
    arrow[0][1] = 2;
    numm = 2;
    site_mapping[0][0] = oper[0][0];
    site_mapping[0][1] = oper[0][1];
    site_mapping[1][0] = oper[0][2];
    site_mapping[1][1] = oper[0][3];
    //cout<<site_num<<endl;
    //cout<<oper[2][1]<<oper[3][1]<<endl;
    //system("pause");
    for(int i = 1; i < v; i++)
    {
        arrow[i][0] = arrow[i-1][1];
        judge_same = false;
        for(int j = 0; j < numm; j++)
        {
            if(oper[i][2] == site_mapping[j][0] && oper[i][3] == site_mapping[j][1])
            {
                arrow[i][1] = j+1;
                judge_same = true;
                break;
            }
        }
        if(judge_same == false)
        {
            numm += 1;
            arrow[i][1] = numm;
            site_mapping[numm-1][0] = oper[i][2];
            site_mapping[numm-1][1] = oper[i][3];
        }
    }
    //cout<<numm<<endl;
    //------------------------------------------------------------------------------------
    /*if(numm != site_num)
    {
        cout<< "something wrong with finding topolopy";
        exit(0);
    }*/
/*
    for(int i = 0; i < v; i++)
        cout<<arrow[i][0]<<" ";
    cout<<arrow[v-1][1];
    cout<<endl;
    system("pause");
*/
    //---------------------
    for(int i = 0; i < site_num; i++)
    {
        delete [] site_mapping[i];
    }
    delete [] site_mapping;
    //----------------------
    return arrow;
}
list<vector<int> > graph::get_topo_list(int **arrow, list<vector<int> > topo_list, int d_weight)
{
    list<vector<int> >::iterator it_list;
    vector<int>::iterator it_vec1;
    vector<int>::iterator it_vec2;
    vector<int> vec;
    bool judge_same1;
    judge_same1 = true;
    for(int i = 0; i < v; i++)
    {
        vec.push_back(arrow[i][0]);
    }
    vec.push_back(arrow[v-1][1]);
/*
    for(int i = 0; i < v+1; i++)
        cout<<vec.at(i);
    cout<<endl;
*/
    if(topo_list.size() == 0)
    {
        vec.push_back(d_weight);//weight
        vec.push_back(1);//�Ƿ�ʹ�ù��ı��
        topo_list.push_back(vec);
    }
    else
    {
        for(it_list = topo_list.begin(); it_list != topo_list.end(); it_list++)
        {
            for(it_vec1 = (*it_list).begin(), it_vec2 = vec.begin(); it_vec1 != (*it_list).end(), it_vec2 != vec.end(); it_vec1++, it_vec2++)
            {
                if(*it_vec1 != *it_vec2)
                {
                    judge_same1 = false;
                    break;
                }
                judge_same1 = true;
            }
            if(judge_same1 == true)
            {
                it_vec1 = (*it_list).end() - 2;
                *it_vec1 += d_weight;
                break;
            }
        }
        if(judge_same1 == false)
        {
            vec.push_back(d_weight);
            vec.push_back(1);
            topo_list.push_back(vec);
        }
    }
    return topo_list;
}
list<vector<int> > graph::map_topo_list(int **arrow, list<vector<int> > topo_list, int &t_weight)
{
    list<vector<int> >::iterator it_list;
    vector<int>::iterator it_vec1;
    vector<int>::iterator it_vec2;
    vector<int> vec;
    for(int i = 0; i < v; i++)
    {
        vec.push_back(arrow[i][0]);
    }
    vec.push_back(arrow[v-1][1]);
    /*for(it_vec1 = vec.begin(); it_vec1 != vec.end(); it_vec1++)
        cout<<*it_vec1;
    cout<<endl;*/
    bool judge_same;
    for(it_list = topo_list.begin(); it_list != topo_list.end(); it_list++)
    {
        for(it_vec1 = (*it_list).begin(), it_vec2 = vec.begin(); it_vec1 != (*it_list).end()-2, it_vec2 != vec.end(); it_vec1++, it_vec2++)
        {
            if(*it_vec2 != *it_vec1)
            {
                judge_same = false;
                break;
            }
            judge_same = true;
        }
        if(judge_same)
        {
            /*for(it_vec1 = (*it_list).begin(); it_vec1 != (*it_list).end(); it_vec1++)
                cout<<*it_vec1;
            cout<<endl;*/
            it_vec1 = (*it_list).end() - 1;

            if(*it_vec1 == 1)
            {
                t_weight = *(it_vec1-1);
                *it_vec1 = *it_vec1 - 1;
                break;
            }
            else
            {
                t_weight = 0;
                break;
            }

        }
    }
    /*cout<<t_weight<<endl;
    //system("pause");
    for(it_list = topo_list.begin(); it_list != topo_list.end(); it_list++)
    {
        for(it_vec1 = (*it_list).begin(); it_vec1 != (*it_list).end(); it_vec1++)
        {
            cout<<*it_vec1;
        }
        cout<<endl;
    }
    cout<<endl;
    system("pause");*/
    return topo_list;
}
int*** graph::platoon(int ***oper_collection, int **oper, int &num_process)
{
   //cout<<v_fac<<endl;
   //system("pause");
   //���������Ч�����㷨����Ҫ������Դ���Դ�Ȼ����ȫ�����㷨�ڡ�
   //������(1000,1000)->(ĳ��)��ʾΪ��Դ���룬(ĳ��)->(1000,1000)��ʾ��Դ����
    oper_collection[0][0][0] = 1000;
    oper_collection[0][1][0] = 1000;
    oper_collection[0][2][0] = oper[0][0];
    oper_collection[0][3][0] = oper[0][1];
    oper_collection[v+1][0][0] = oper[v-1][2];
    oper_collection[v+1][1][0] = oper[v-1][3];
    oper_collection[v+1][2][0] = 1000;
    oper_collection[v+1][3][0] = 1000;
   for(int i = 1; i < v+1; i++)
   {
       for(int j = 0; j < 2*d; j++)
       {
           for(int k = 0; k < v_fac; k++)
           {
                if(k == 0)
                    oper_collection[i][j][k] = oper[i-1][j];
                else
                    oper_collection[i][j][k] = 0;
           }
       }
   }
/*
   for(int i = 0; i < 2*d; i++)
   {
       for(int j = 0; j < v; j++)
       {
            cout<<oper_collection[i][j][0]<<" ";
       }
       cout<<endl;
   }
   cout<<endl;
   system("pause");
*/
   int *m = new int[v+2];
   int **oper_copy = new  int*[v+2];
   for(int i = 0; i < v+2; i++)
        oper_copy[i] = new int[2*d];
   bool judge_swap = true;
   for(int i =0 ; i < v+2; i++)
        m[i] = 0;
   m[0] = 0;
   //һ��ȫ�����㷨��û����
   for(int i = 0; i < v+1; i++)
   {
       if(i < v+1)
            m[i+1] = m[i];
       for(int k = 0; k <= m[i]; k++)
       {
           for(int row = 0; row < v+2; row++)
           {
               for(int col = 0; col < 2*d; col++)
               {
                   oper_copy[row][col] = oper_collection[row][col][k];
                   //cout<<oper_collection[row][col][0]<<" ";
               }
               //cout<<endl;
           }
           //cout<<endl;
           for(int j = i+1; j < v+2; j++)
           {

               judge_swap = jud_swap(oper_copy, i, j, judge_swap);
               if(judge_swap)
               {
                  oper_copy = Swap(oper_copy, i, j);
                  m[i+1] += 1;
                  //cout<<m[i+1]<<"\t";
                  for(int row = 0; row < v+2; row++)
                      for(int col = 0; col < 2*d; col++)
                          oper_collection[row][col][m[i+1]] = oper_copy[row][col];
               }
           }
       }
   }
   num_process = m[v+1];
   //cout<<"num_process: "<<num_process<<endl;
   //system("pause");
   /*
    for(int k = 0; k < num_process+1; k++)
    {
        for(int i = 0; i < 2*d; i++)
        {
            for(int j = 0; j < v; j++)
            {
                cout<<oper_collection[i][j][k]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
    }
    system("pause");
    */
   //------------------------------------
   delete [] m;
   for(int i = 0; i < v+2; i++)
        delete [] oper_copy[i];
   delete oper_copy;
   //------------------------------------

   return oper_collection;
}
bool graph::jud_swap(int **oper, int m, int i, bool judge_swap)
{
/*    for(int i = 0; i < 2*d; i++)
    {
        for(int j = 0; j < v; j++)
        {
            cout<<oper[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    //cin.get();*/
    bool kkkk;
    judge_swap = true;
    for(int j = m; j <= i - 1; j++)
    {
        kkkk = true;
        //��ǰԾǨ�����֮ǰ��ԾǨ��ͬ�򽻻�
        for(int k = 0; k < 2*d; k++)
        {
            if(oper[i][k] != oper[j][k])
            {
                kkkk = false;
                break;
            }
        }
        if(kkkk)
            judge_swap = false;

    }
    //cout<<judge_swap<<endl;
    return judge_swap;
}
int**graph::Swap(int **oper, int i, int j)
{
    int temp;
    for(int col = 0; col < 2*d; col++)
    {
        temp = oper[i][col];
        oper[i][col] = oper[j][col];
        oper[j][col] = temp;

    }
    return oper;
}
double* graph::cal_eng_dia(int ***oper_collection, int m, int *eng_weight, int **eng_katolist, int num_process, double *energy_diagram, double miu, double delta_miu)
{
    int sites_num;
    bool same_site, judge_ground, judge_good_kato;
    int *ground_excited = new int[v+1];
    double *w1 = new double[v+1];
    double *w2 = new double[v+1];
    double *h = new double[v+2];
    int **site = new int*[v+1];
    for(int i = 0; i < v+1; i++)//v+1�����
        site[i] = new int[2];
    int **particle_num = new int*[v+1];//��������v+1�������̵Ļ�������Դ��������������ʼ̬�ܹ�Ӧ����v+3
    for(int i = 0; i < v+1; i++)
        particle_num[i] = new int[v+3];
    double energy_kato1;
    double energy_kato2;
    int num_zero1, num_zero2;
    energy_diagram[0] = 0.0;
    energy_diagram[1] = 0.0;
    //oper_collection[0][0][0] = 1000;oper_collection[0][1][0] = 1000;
    for(int k = 0; k <= num_process; k++)
    {
        //site[0][0] = oper_collection[0][0][k];         //site�ǵ���Ϣ�����������λ������꣬�ڶ�ά��Ϊ�ڼ���ԾǨ
        //site[0][1] = oper_collection[0][1][k];
        //if(k == 1 || k == 60){
        sites_num = 0;                                    //sites_num��0��ʼ
        for(int i = 0; i < v+2; i++)
        {
            if(oper_collection[i][0][k] != 1000)
            {

                if(sites_num == 0)
                {
                    for(int j = 0; j < 2; j++)
                    {
                        site[sites_num][j] = oper_collection[i][j][k];
                    }
                    sites_num += 1;
                }
                else
                {
                    same_site = false;
                    for(int j = 0; j < i; j++)
                    {
                        //����iλ��ʱ������iǰ������е㣬�Ƿ��и�iλ��һ������һ���Ļ�������ͬ��site������¼��site[][]��
                        //����ע�⵽����oper_collectionֻ���ǰ��һ�����жϣ�������Ϊ�ڶ����㽫����һά�ĵ�һ���㣬���ԡ�����
                        if(oper_collection[i][0][k] == oper_collection[j][0][k] && oper_collection[i][1][k] == oper_collection[j][1][k])
                        {
                            same_site = true;
                            break;// ���break����Ҫ!!!
                        }
                    }
                    if(same_site == false)
                    {
                        for(int j = 0; j < 2; j++)
                        {
                            site[sites_num][j] = oper_collection[i][j][k];
                        }
                        sites_num += 1;
                    }
                }
            }
        }

    /*if(sites_num == 3)
    {
        //cout<<sites_num<<endl;
        //for(int i = 0; i < sites_num; i++)
        //{
        //    cout<<site[i][0]<<site[i][1]<<" ";
        //}
        cout<<endl;
        cout<<k<<endl;
        for(int i = 0; i < v+2; i++)
        {
            cout<<"("<<oper_collection[i][0][k]<<","<<oper_collection[i][1][k]<<")"<<"->"<<"("<<oper_collection[i][2][k]<<","<<oper_collection[i][3][k]<<")"<<" ";
        }
        cout<<endl;system("pause");
    }*/


        for(int i = 0; i < v+1; i++)
        {
            for(int j = 0; j < v+3; j++)
            {
                if(j == 0)
                    particle_num[i][j] = g;          //��һάΪ��ʼ�����
                else
                    particle_num[i][j] = 0;
            }
        }
        //����һ��ȷ����i��k��oper_collection[][i][k]��ǰ������ԾǨ��ʼ�㣬����λ��ԾǨ��ֹ��
        //site�е�һά����λ�����꣬�ڶ�ά�ǵ����Ŀ������������ԾǨ���̵ĵ㣬����sites_numѭ��
        //ʱ�����������ԾǨ��ʼ�㣬��particle_num-1�������ԾǨ��ֹ�㣬��+1��������particle_num
        //�����оʹ��Ÿ�������ĳ����������ˡ�����ʼλ���������̬(1000,1000)����һ��������Ӽ�1
        //�ڽ���λ������ĩ����1
        for(int i = 0; i < v+2; i++)
        {
            for(int j = 0; j < v+1; j++)
            {
                particle_num[j][i+1] = particle_num[j][i];
            }

            //�����sites_num��ȷ�еĸ����Ŀ��û��С1
            //cout<<oper_collection[i][0][k]<<endl;
            for(int j = 0; j < sites_num; j++)
            {
                if(site[j][0] == oper_collection[i][0][k] && site[j][1] == oper_collection[i][1][k])//������Ҫע������ܹ�ֻ��site_num����㣬�����жϸø����ĳ��ԾǨ��������
                {                                                                                   //oper_collection��ǰ�����������Ϳ����ˡ�site�е�˳����ʵ����ν��site��Ҫ���Ǽ�ס���
                    particle_num[j][i+1] = particle_num[j][i+1] - 1;
                }
                else if(site[j][0] == oper_collection[i][2][k] && site[j][1] == oper_collection[i][3][k])
                {
                    particle_num[j][i+1] = particle_num[j][i+1] + 1;
                }
            }
        }
        //cout<<sites_num<<endl;
    /*if(sites_num == 3){
    if(k == 4)
    {

        for(int i = 0; i < sites_num; i++)
        {
           for(int j = 0; j < v+3; j++)
            {
                cout<<particle_num[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
        system("pause");
    }
    }*/

        //���particle_numΪ��ʼ����������̬���ڻ�̬�����Ϊ0��������Ϊ1
        //�����fortran��ͬ����Ϊfortran����ɨ�У���ɨ��
        //������µ����н�����Ҫ��д����̫��ϰ����
        for(int i = 0; i < v+1; i++)
        {
            judge_ground = true;
            for(int j = 0; j < sites_num; j++)
            {
                if(particle_num[j][i+1] != g)
                {
                    judge_ground = false;
                    break;
                }

            }
            if(judge_ground)
                ground_excited[i] = 0;
            else
                ground_excited[i] = 1;

        }
        /*for(int j = 0; j < v+1; j++)
            cout<<ground_excited[j]<<" ";
        cout<<endl;
        system("pause");*/
        num_zero1 = 0;
        for(int j = 0; j < v+1; j++)
        {
            if(ground_excited[j] == 0)
                num_zero1 += 1;
        }
        //һ��һ�е��жϣ�����˳���ܱ�
        //���ɵ�ԾǨ���̺�katolistһһ�ȶԣ����������ͱ���Ȼ����㡣
        //�Աȵ������ǻ�̬����Ŀ
        //����Ƕ��ڼ�����Ч����ʱ��v��ԾǨҪ��Ӧ��v+2�׵�katoterm
        for(int i = 0; i < m; i++)
        {
            judge_good_kato = true;
            num_zero2 = 0;
            for(int j = 0; j < v+1; j++)
                if(eng_katolist[i][j] == 0)
                    num_zero2 += 1;
            if(num_zero1 != num_zero2)
                judge_good_kato = false;
            else
            {
                for(int j = 0; j < v+1; j++)
                {
                    if(eng_katolist[i][j] == 0)
                        if(ground_excited[j] != eng_katolist[i][j])
                            judge_good_kato = false;
                }
            }
            if(judge_good_kato)
            {
                //cout<<k<<endl;
                //w��h���Ǽ����ʽ�ӣ�һ���Ƿ���һ���Ƿ�ĸ
                for(int j = 0; j < v+1; j++)
                {
                    w1[j] = 0.0;
                    w2[j] = 0.0;
                }
                for(int j = 0; j < v+1; j++)
                {

                    //cout<<i<<" "<<j<<" "<<eng_katolist[i][j]<<endl;
                    if(eng_katolist[i][j] == 0)
                    {
                        w1[j] = -1.0;
                        w2[j] = -1.0;
                    }
                    else
                    {

                        for(int l = 0; l < sites_num; l++)
                        {

                            if(abs(site[l][0] + site[l][1])%2 == 0 )//AB��㣬A����㡣����A��ż����ԾǨ����A��B���෴
                            {
                                if(particle_num[l][j+1] != g){
                                    w1[j] = w1[j]  + 0.5*(g*(g-1)) - (miu+delta_miu)*g - 0.5*((particle_num[l][j+1]-1)*particle_num[l][j+1]) + (miu+delta_miu)*particle_num[l][j+1];//Em-Ei,m�ǻ�̬
                                    w2[j] = w2[j]  + 0.5*(g*(g-1)) - miu*g - 0.5*((particle_num[l][j+1]-1)*particle_num[l][j+1]) + miu*particle_num[l][j+1];
                                }
                                //cout<<w1[j]<<endl;

                            }
                            else if(abs(site[l][0] + site[l][1])%2 == 1)
                            {
                                if(particle_num[l][j+1] != g){
                                    w1[j] = w1[j]  + 0.5*(g*(g-1)) - miu*g - 0.5*((particle_num[l][j+1]-1)*particle_num[l][j+1]) + miu*particle_num[l][j+1];//Em-Ei,m�ǻ�̬
                                    w2[j] = w2[j]  + 0.5*(g*(g-1)) - (miu+delta_miu)*g - 0.5*((particle_num[l][j+1]-1)*particle_num[l][j+1]) + (miu+delta_miu)*particle_num[l][j+1];
                                    //Count2++;
                                }
                                //cout<<w1[j]<<endl;
                            }

                            //cout<<particle_num[l][j+1];
                        }
                         /*if(sites_num == 2){
                            if(k == 21){
                                cout<<k<<" "<<i<<endl;
                                /*for(int i = 0; i < v+2; i++)
                                {
                                    cout<<"("<<oper_collection[i][0][k]<<","<<oper_collection[i][1][k]<<")"<<"->"<<"("<<oper_collection[i][2][k]<<","<<oper_collection[i][3][k]<<")"<<" ";
                                }
                                cout<<endl;
                                //for(int j = 0; j < v+1; j++)
                                    cout<<w1[j]<<" ";
                                //cout<<endl;
                                system("pause");
                                }

                        }
                        if(sites_num == 2){
                            if(k == 42){
                                cout<<k<<" "<<i<<endl;
                                /*for(int i = 0; i < v+2; i++)
                                {
                                    cout<<"("<<oper_collection[i][0][k]<<","<<oper_collection[i][1][k]<<")"<<"->"<<"("<<oper_collection[i][2][k]<<","<<oper_collection[i][3][k]<<")"<<" ";
                                }
                                cout<<endl;
                                //for(int j = 0; j < v+1; j++)
                                    cout<<w2[j]<<" ";
                                //cout<<endl;
                                system("pause");
                                }

                        }*/
                        w1[j] = pow(w1[j], -1.0*eng_katolist[i][j]);
                        w2[j] = pow(w2[j], -1.0*eng_katolist[i][j]);
                         /*if(sites_num == 2){
                            if(k == 21){
                                cout<<w1[j]<<" ";
                                system("pause");
                                }

                        }
                        if(sites_num == 2){
                            if(k == 42){
                                cout<<w2[j]<<" ";
                                system("pause");
                                }
                        }*/
                    }
                }
                /*if(sites_num == 2)
                    if(k == 21 || k == 42)
                        cout<<endl;*/
                /*if(sites_num == 2){
                    if(k == 21){
                        cout<<k<<" "<<i<<endl;
                        for(int i = 0; i < v+2; i++)
                        {
                            cout<<"("<<oper_collection[i][0][k]<<","<<oper_collection[i][1][k]<<")"<<"->"<<"("<<oper_collection[i][2][k]<<","<<oper_collection[i][3][k]<<")"<<" ";
                        }
                        cout<<endl;
                        for(int j = 0; j < v+1; j++)
                            cout<<w1[j]<<" ";
                        cout<<endl;
                        system("pause");
                        }

                }
                if(sites_num == 2){
                    if(k == 42){
                        cout<<k<<" "<<i<<endl;
                        for(int i = 0; i < v+2; i++)
                        {
                            cout<<"("<<oper_collection[i][0][k]<<","<<oper_collection[i][1][k]<<")"<<"->"<<"("<<oper_collection[i][2][k]<<","<<oper_collection[i][3][k]<<")"<<" ";
                        }
                        cout<<endl;
                        for(int j = 0; j < v+1; j++)
                            cout<<w2[j]<<" ";
                        cout<<endl;
                        system("pause");
                        }

                }*/

                for(int j = 0; j < v+2; j++)
                    h[j] = 1.0;
                for(int j = 0; j < v+2; j++)
                {
                    for(int l = 0; l < sites_num; l++)
                    {
                        if(site[l][0] == oper_collection[j][0][k] && site[l][1] == oper_collection[j][1][k])
                        {
                            if(particle_num[l][j] > 0)
                                h[j] = h[j] * sqrt(particle_num[l][j]*1.0);
                            else
                                h[j] = 0.0;
                        }
                        if(site[l][0] == oper_collection[j][2][k] && site[l][1] == oper_collection[j][3][k])
                        {
                             if(particle_num[l][j]+1 > 0)
                                h[j] = h[j] * sqrt((particle_num[l][j]+1)*1.0);
                             else
                                h[j] = 0.0;
                        }
                    }
                }
                energy_kato1 = 1.0;
                energy_kato2 = 1.0;
                /*if(sites_num == 3){
                    if(k == 4){
                        cout<<k<<endl;
                        for(int j = 0; j < v+2; j++)
                            cout<<h[j]<<" ";
                        cout<<endl;
                        }

                }*/
                /*if(sites_num == 3){
                    if(k == 60){
                        cout<<k<<endl;
                        for(int j = 0; j < v+2; j++)
                            cout<<h[j]<<" ";
                        cout<<endl;
                        system("pause");
                        }

                }*/
                for(int j = 0; j < v+1; j++)
                {
                    energy_kato1 = energy_kato1 * w1[j];
                    energy_kato2 = energy_kato2 * w2[j];
                }
                for(int j = 0; j < v+2; j++)
                {
                    energy_kato1 = energy_kato1 * h[j];
                    energy_kato2 = energy_kato2 * h[j];
                }
                energy_kato1 = energy_kato1 * eng_weight[i];
                energy_kato2 = energy_kato2 * eng_weight[i];
                /*if(sites_num == 2){
                    //if(k < 10){
                        //system("pause");
                        foutA<<k<<" "<<i<<" ";
                        foutA<<energy_kato1<<endl;
                        foutB<<k<<" "<<i<<" ";
                        foutB<<energy_kato2<<endl;

                    //}
                    //if(energy_kato1 == 2486)
                    //{
                    //    cout<<k<<endl;
                   //     system("pause");
                    //}
                }*/
                /*if(sites_num == 3){
                    if(k == 60){
                        cout<<k<<" ";
                        cout<<energy_kato2<<endl;

                        }

                }*/
                energy_diagram[0] = energy_diagram[0] + energy_kato1;
                energy_diagram[1] = energy_diagram[1] + energy_kato2;
                //if(energy_diagram[1] != energy_diagram[0]){
                //    cout<<k<<endl;system("pause");
                //}
            }
        }
        //}
    }
    //-------------------------------------
    //cout<<energy_diagram[0]<<" "<<energy_diagram[1]<<endl;system("pause");
    delete [] ground_excited;
    delete [] w1;
    delete [] w2;
    delete [] h;
    for(int i = 0; i < v+1; i++)
    {
        delete [] site[i];
        delete [] particle_num[i];
    }
    delete [] site;
    delete [] particle_num;
    //-------------------------------------
    return energy_diagram;
}
