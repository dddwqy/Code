#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
//实现一个图的基本操作
struct node {
    int dian;
    struct node* next;
    node(int mnode = -1, struct node* mnext = nullptr)
    {
        dian = mnode;
        next = mnext;
    }
    void set(int mnode)
    {
        dian = mnode;
        return;
    }
};//每一个节点

class graph
{
public:
    graph(int temp = 0) {
        n_node = temp, n_edge = 0;
        array = new struct node* [n_node + 1];
        for (int i = 1; i <= n_node; i++)
        {
            array[i] = new struct node;
        }
        memset(reach, 0, sizeof(reach));
        memset(path, 0, sizeof(path));
        connet = new int[n_node + 1]();
        count = 0;
    }
    void inset_edge(int i, int j)//添加边//注意，这是一个无向图，所以i到j有了，j到i也要有//插入时按照从小开始到大的顺序插入，可以帮助后面的输出最小的路径
    {
        if (i == j)
        {
            cout << "i==j error" << endl;
            return;
        }
        if (array[i]->dian == -1)
        {
            // cout<<i<<endl;
            array[i]->dian = i;
        }
        if (array[j]->dian == -1)
        {
            //cout<<j<<endl;
            array[j]->dian = j;
        }
        struct node* forward_i = array[i];
        struct node* forward_j = array[j];
        struct node* first_i = array[i]->next;
        struct node* first_j = array[j]->next;

        while (first_i != nullptr && first_i->dian < j)//按照从小到大的顺序来排列就可以了
        {
            forward_i = first_i;
            first_i = first_i->next;
        }
        forward_i->next = new struct node(j, forward_i->next);
        while (first_j != nullptr && first_j->dian < i)
        {
            forward_j = first_j;
            first_j = first_j->next;
        }
        forward_j->next = new struct node(i, forward_j->next);
        n_edge++;
        return;
    }

    void erase_edge(int i, int j)//删除一条边//同上
    {
        if (i == j)
        {
            return;
        }

        if (array[i]->dian == -1 || array[j]->dian == -1)
        {
            return;
        }
        if (i<1 || i>n_node || j<1 || j>n_node)
        {
            return;
        }

        struct node* first_i_forward = nullptr;
        struct node* first_j_forward = nullptr;
        struct node* first_i = array[i];
        struct node* first_j = array[j];

        while (first_i != nullptr && first_i->dian != j)//当我们在i的邻接点中找到j点的时候，我们才继续在j中找到i点
        {
            first_i_forward = first_i;
            first_i = first_i->next;
        }
        if (first_i == nullptr)
        {
            cout << "不存在这条边" << endl;
        }
        else {
            first_i_forward->next = first_i->next;
            delete first_i;
            while (first_j != nullptr && first_j->dian != i)
            {
                first_j_forward = first_j;
                first_j = first_j->next;
            }
            first_j_forward->next = first_j->next;
            delete first_j;
            n_edge--;
        }

        return;
    }
    int connect_label()
    {
        //long cnt=0;
        memset(reach, 0, sizeof(reach));
        int label = 0;
        for (int i = 1; i <= n_node; i++)
        {
            if (connet[i] == 0)
            {
                //cout<<"这个连通分量的最小节点为； "<<i<<endl;
                min_dian.push_back(i);//记录每个连通分量的最小编号
                label++;
                //cout<<"label : "<<label<<endl;
                dfs1(i, label);
            }
        }
        return label;
    }

    void dfs1(int s, int label)
    {
        dfs1_p(s, label);
        return;
    }

    void dfs2(long s)
    {
        count = 0;
        memset(reach, 0, sizeof(reach));
        memset(path, 0, sizeof(path));
        dfs2_p(s);
        return;
    }

    void bfs2(int s)
    {
        count = 0;
        memset(reach, 0, sizeof(reach));
        memset(path, 0, sizeof(path));
        bfs2_p(s);
        return;
    }

    int bfs3(int s, int t)
    {
        count = 0;
        memset(reach, 0, sizeof(reach));
        min_path = 1e9;
        return bfs3_p(s, t);
    }

    void output(int s, int t)
    {
        int ans_label = connect_label();
        cout << ans_label << endl;
        dfs2(s);
        for (int i = 0; i < min_dian.size(); i++)//输出连通分量中的最小点
        {
            cout << min_dian[i] << ' ';
        }
        cout << endl;
        cout << count << endl;//输出s的长度
        for (int i = 1; i <= count; i++)//输出字典序最小的序列
        {
            cout << path[i] << ' ';
        }
        cout << endl;
        bfs2(t);
        cout << count << endl;//输出t的长度
        for (int i = 1; i <= count; i++)
        {
            cout << path[i] << ' ';
        }
        cout << endl;
        int layer = bfs3(s, t);
        cout << layer;
        return;
    }

    ~graph()
    {
        for (int i = 1; i <= n_node; i++)
        {
            delete[] array[i];
        }
    }
private:
    void dfs1_p(int s, int label)
    {
        reach[s] = 1;
        connet[s] = label;
        struct node* first = array[s]->next;

        while (first != nullptr)
        {
            if (reach[first->dian] == 0)
            {
                dfs1_p(first->dian, label);//遍历完当前的路径之后
            }
            first = first->next;//转移到该节点的下一个邻接点
        }
        return;
    }

    void dfs2_p(int s)//count 用来记录一共有几个点被记录
    {
        reach[s] = 1;
        count++;//记录点的个数
        path[count] = s;//记录这条路径的节点
        struct node* first = array[s]->next;

        while (first != nullptr)
        {
            if (reach[first->dian] == 0)
            {
                dfs2_p(first->dian);//遍历完当前的路径之后
            }
            first = first->next;//转移到该节点的下一个邻接点
        }
        return;
    }

    void bfs2_p(int s)//count 用来记录一共有几个点被记录
    {
        queue<struct node*>bfs_queue;
        bfs_queue.push(array[s]);
        reach[array[s]->dian] = 1;
        struct node* current = nullptr;
        struct node* neigh = nullptr;

        while (!bfs_queue.empty())
        {
            current = bfs_queue.front();
            bfs_queue.pop();
            count++;
            path[count] = current->dian;
            neigh = current->next;
            while (neigh != nullptr)
            {

                if (reach[neigh->dian] != 1)
                {
                    reach[neigh->dian] = 1;
                    bfs_queue.push(array[neigh->dian]);
                }
                neigh = neigh->next;
            }
        }
        return;
    }

    int bfs3_p(int s, int t)
    {
        if (connet[s] != connet[t])
        {
            return -1;
        }
        queue<struct node*>bfs_min;
        bfs_min.push(array[s]);
        int layer = 1;
        struct node* current = nullptr;
        struct node* neigh = nullptr;

        while (!bfs_min.empty())
        {
            int size = bfs_min.size();
            for (int i = 0; i < size; i++)
            {
                current = bfs_min.front();
                bfs_min.pop();
                neigh = current->next;
                while (neigh != nullptr)
                {
                    if (reach[neigh->dian] == 0)
                    {
                        if (neigh->dian == t)
                        {
                            return layer;
                        }
                        bfs_min.push(array[neigh->dian]);
                        reach[neigh->dian] = 1;
                    }
                    neigh = neigh->next;
                }
            }
            layer++;
        }
        return layer;
    }

    vector<int>min_dian;
    int  n_edge;
    int  n_node;
    int count;
    struct node** array;//这是一个链表的数组 
    int reach[100010];//一个判断是不是已经到达过的数组
    int* connet;//用于标记每个节点属于的连通分量
    int path[100010];
    int min_path;
};

int main()
{
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    graph test(n);

    for (int i = 1; i <= m; i++)
    {
        int sign;
        int x = 0, y = 0;
        cin >> sign >> x >> y;

        if (sign == 0)
        {
            test.inset_edge(x, y);
        }
        else if (sign == 1)
        {
            test.erase_edge(x, y);
        }
    }
    test.output(s, t);

    return 0;
}
