#include<iostream>
#include<vector>
using namespace std;

//int answer[200000];
//int top;

struct matrixTerm {//储存每个元素的行和列还有value
    int row;
    int col;
    int num;
    void operator=(const matrixTerm& right)
    {
        row = right.row;
        col = right.col;
        num = right.num;
    }
};

class sparseMatrix {
public:
    sparseMatrix()
    {
        rows = -1;
        cols = -1;
    }
    sparseMatrix(const sparseMatrix& other)
    {
        rows = other.rows;
        cols = other. cols;
        value = other.value;
    }
    void transpose();//转置行列号对换，元素顺序重排
    void add(const sparseMatrix& right);
    //void minus(const sparseMatrix& right);
    void reset(int mrows,int mcols);//
    void mul(sparseMatrix& right);
    void output();
    void operation(int operations_num);
private:
    int rows;
    int cols;
    vector<matrixTerm> value;
};

struct ans
{
    sparseMatrix temp_4;
    int answer_2_3 = 0;
};
//sparseMatrix* record;
//int top_matrix;
ans* answer;
int top;

void sparseMatrix::output()//输出矩阵
{
    //auto it = value.begin();
    int index = 0;
    cout<<rows<<' '<< cols << endl;
    if (value.size()==0)
    {
        for (int i=0;i<rows;i++)
        {
            for (int j=0;j<cols;j++)
            {
                cout<<0<<' ';
            }
            cout << endl;
        }
    }
    else {
        for (int i=1;i<=rows;i++)
        {
            for (int j=1;j<=cols;j++)
            {
                if (index<value.size() && value[index].row == i && value[index].col == j)
                {
                    cout<<value[index].num<<' ';
                    index++;
                }
                else {
                    cout<<0<<' ';
                }
            }
            cout << endl;
        }
    }
    
    return;
}
void sparseMatrix::reset(int mrows,int mcols)//将非0的元素输入到一维的vector中
{
    //value.resize(mrows*mcols);
    rows = mrows;
    cols = mcols;
    value.clear();
    int temp = 0;
    int index = 0;
    matrixTerm matri;

    for (int i=1;i<=rows;i++)
    {
        for (int j=1;j<=cols;j++)
        {
            cin >> temp;
            if (temp!=0)
            {
                matri.row = i;
                matri.col = j;
                matri.num = temp;
                //cout<<temp<<endl;
                value.push_back(matri);
            }
        }
    }
    return;
}

void sparseMatrix::add(const sparseMatrix& right)
{
    
    if (right.cols != cols||right.rows != rows)//当不能add的时候，将right矩阵赋值给left矩阵
    {
        rows = right.rows;
        cols = right.cols;
        value.clear();
        value = right.value;
        //cout<<-1<<endl;
        
        answer[top].answer_2_3 = -1;
        top++;
    }
    else {//当矩阵可以相加的时候//现在这里依然有问题：在将第二个矩阵的值插入的时候，发现迭代器地最后一个值跟输入地不一样
        vector <matrixTerm> c;
        auto it_a = value.begin();
        auto it_b = right.value.begin();
        auto it_a_end = value.end();
        auto it_b_end = right.value.end();
        
        while (it_a != it_a_end && it_b != it_b_end)
         {
             //cout<<(*it_a).num<<' '<<(*it_b).num<<endl;
             int index_a = ((*it_a).row - 1) * cols + (*it_a).col;//因为行序号是从1开始的，所以我们计算这个元素之前的元素个数时，使用row-1
             int index_b = ((*it_b).row - 1) * cols + (*it_b).col;

             if (index_a < index_b)//表示再index——a的位置a有元素，b没有
             {
                 c.push_back((*it_a));
                 ++it_a;
             }
             else {
                 if (index_a == index_b)//表示同一个位置有
                 {
                     if ((*it_a).num + (*it_b).num != 0)
                     {
                         c.push_back(matrixTerm{ (*it_a).row,(*it_a).col,((*it_a).num + (*it_b).num) });
                     }
                     ++it_a;
                     ++it_b;
                 }
                 else
                 {
                     c.push_back((*it_b));
                     ++it_b;
                 }
             }
         }
         for (it_a; it_a != it_a_end; it_a++)
         {
             c.push_back((*it_a));
             //++it_a;
         }
         //cout<<(*it_b).num<<endl;
         //cout<<(*it_b).num<<endl;
         for (it_b; it_b != it_b_end; it_b++)
         {
             //cout<<(*it_b).num<<endl;
             c.push_back((*it_b));
             //++it_b;
         }
         //cout<<"this is right's end" << endl;
         value = c;
    }
    return;
}
void sparseMatrix::mul(sparseMatrix& right)
{
    int index_a = 0;//表示value的第一个元素的索引
    int index_b = 0;//表示right的第一个元素的索引
    //使用整数的索引方便我们跳到我们想要的元素上

    if (cols!=right.rows)
    {
        rows = right.rows;
        cols = right.cols;
        value = right.value;
        //cout<<-1<<endl;
        answer[top].answer_2_3 = -1;
        top++;
    }
    else {//
        int* num_right_hang=new int[right.rows+1];//记录right每一行的元素个数
        int* start_right_hang = new int[right.rows+1];//记录right每一行的非0元素的起始位置
        int* result = new int[right.cols+1];//记录相乘以后，每一行的每一列的所有元素
        int id = 0;//这个是用于遍历本矩阵的一行中的非0元素的
        int size = value.size();
        vector<matrixTerm>mul_ans;

        for (int i=0;i<=right.rows;i++)
        {
            num_right_hang[i] = 0;//将每一行的元素个数赋值为0
        }
        for (int j=0;j<=right.rows;j++)
        {
            start_right_hang[j] = 0;//将每一行的非0元素的起始位置赋值为0
        }

        for (auto it=right.value.begin();it!=right.value.end();it++)
        {
            num_right_hang[(*it).row]++;
        }
        for (int i=1;i<=right.rows;i++)
        {
            start_right_hang[i]=start_right_hang[i-1]+num_right_hang[i-1];//记录每一行第一个非0元素的起始位置
            //cout<<i<<':'<<start_right_hang[i]<< endl;
        }
       
        for (int i=1;id<size;i++)//i表示结果矩阵的每一行
        {
                for (int m = 1; m <= right.cols; m++)result[m] = 0;//将每一列的值初始化为0
                while (id<size&&value[id].row==i)//当该元素的行与我们现在结果的行一致时，可以进行计算
                {
                    //cout<<"现在时value中地"<<id<<"个元素"<< endl;
                    if (num_right_hang[value[id].col]!=0)//当right这一行的元素数量不为0时可以计算
                    {
                       // cout<<"现在是结果矩阵的："<<i<<"行" << endl;
                        for (int x=start_right_hang[value[id].col];x<start_right_hang[value[id].col]+num_right_hang[value[id].col];x++)//遍历right对应的这一行地所有元素
                        {
                            //cout<<"x为："<<x<<' '<<"元素为："<<right.value[x].num<< endl;
                            result[right.value[x].col] +=right.value[x].num*value[id].num;
                        }
                    }
                    id++;//对于每个循环地++我们都要考虑会不会越界，大注意一下
                }
                for (int j=1;j<=right.cols;j++)
                {
                    if (result[j]!=0)
                    {
                        mul_ans.push_back(matrixTerm{i,j,result[j]});//将每一行地结果按顺序输进去
                    }
                }
        }
        cols = right.cols;
        value.swap(mul_ans);//将结果赋值给原矩阵
    }
    return;
}
void sparseMatrix::transpose()
{
    vector<matrixTerm> two(rows*cols, matrixTerm{-1,-1,-1});
    int m_rows = cols;//修改矩阵的行和列
    cols = rows;
    rows = m_rows;

    int* colsize=new int[rows+1];//记录每个列一共有几个元素
    int* rownext=new int[rows+1];//记录转置后每个矩阵的每一行的起始位置

    for (int i = 1; i <= rows;i++) {
        colsize[i] = 0;
        rownext[i] = 0;
    }
    for (auto it=value.begin();it!=value.end();it++)
    {
        colsize[(*it).col]++;
    }
   
    rownext[1] = 0;
    for (int i=2;i<=rows;i++)
    {
        rownext[i] = rownext[i - 1] + colsize[i - 1];
    }
    
    matrixTerm temp;
    for (auto it=value.begin();it!=value.end();it++)
    {
        int j = rownext[(*it).col]++;
        temp.row = (*it).col;
        temp.col = (*it).row;
        temp.num = (*it).num;
        two[j] = temp;
        //cout << (*it).num << ':' << j<<':' << two[j].num << endl;
    }
    //auto it = two.begin();
    int index = 0;
    for (index;index<value.size();index++)
    {
        //cout <<"index is:" << index << endl;
        value[index] = two[index];
        //cout<<value[index].row<<' '<<value[index].col << endl;
        //index++;
    }
    two.clear();
    return;
}

void sparseMatrix::operation(int operations_num)
{
    if (operations_num == 1)
    {
   
        int rows, cols;
        cin >> rows >> cols;
        reset(rows, cols);
    }
    else if (operations_num ==3|| operations_num ==2)
    {
        int n, m,t;
        sparseMatrix temp;
        cin >> n >> m;
        temp.rows = n;
        temp.cols = m;
        cin >> t;

        for (int i=0;i<t;i++)
        {
            int row, col, val;
            cin >> row >> col >> val;
            temp.value.push_back(matrixTerm{row,col,val});
            //cout<<row<<' '<<col<<' '<<val<< endl;
        }
        if (operations_num ==3)
        {
            add(temp);
            output();
        }
        else if (operations_num ==2)
        {
            //cout<<"mul中" << endl;
            mul(temp);//mul函数中对于有0的矩阵的处理出现错误
            output();
        }
       
        //output();
    }
    else if(operations_num ==4){
        //output();
        answer[top].temp_4.value=value;
        //answer[top].temp_4.value=value;
        answer[top].temp_4.rows = rows;
        answer[top].temp_4.cols = cols;
       // cout<<"这是answer地value" << endl;
        /*for (auto it = answer[top].temp_4.value.begin(); it != answer[top].temp_4.value.end(); it++)
        {
            cout<<(*it).num<<' ';
        }
        cout << endl;
        cout<<"这是value地num" << endl;
        for (auto it=value.begin();it!=value.end();it++)
        {
            cout<<(*it).num<<' '<< endl;
        }
        cout << endl;*/
        top++;
    }
    else if (operations_num ==5)
    {
        transpose();
    }
    

    return;
}



int main()
{
    //int n, m;
    //cin>>n>>m;
    sparseMatrix test;
    int operation_num = 0;
    cin >> operation_num;
    //test.reset(n,m);
    //test.operation(3);
    answer = new ans[operation_num];

    for (int i = 0; i < operation_num; i++)
    {
        int num;
        cin >> num;
        test.operation(num);
    }

    for (int i = 0; i<top; i++)
    {
        if (answer[i].answer_2_3==-1)
        {
            cout<<-1<<endl;
        }
        else {
            answer[i].temp_4.output();
        }
    }
    return 0;
}