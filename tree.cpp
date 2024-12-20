#include<iostream>
#include<vector>
#include<queue>
#include<stack>
using namespace std;
//实现一棵二叉树的基本功能
class treenode//一棵树的节点
{
public:
    treenode()
    {
        left = nullptr;
        right = nullptr;
    }
    treenode(int& thelement, int mnum, treenode* mleft = nullptr, treenode* mright = nullptr)
    {
        num = mnum;
        element = thelement;
        left = mleft;
        right = mright;
    }
    int element;//这个表示元素值
    int num;///这个表示编号
    treenode* left;
    treenode* right;
};

class Tree//使用链表实现的一棵树
{
public:
    Tree(int mtreesize = 1)
    {
        root = new treenode();
        root->left = nullptr;
        root->right = nullptr;
        root->element = 1;//第一个根节点的序号为1
        root->num = 1;
        treesize = mtreesize;
        visit = nullptr;
        insert_use=new treenode*[10000]();
    }
    bool empty() { return treesize == 0; };
    int size() { return treesize; };
    //由于在这个遍历的函数中需要设置visit，还需要传入自己的私有变量root，所以定义一个在public中，一个在private中，分别接收两个变量
    void preorder(void (*thevisit) (treenode* node));//前序遍历
    void inorder(void (*thevisit) (treenode* node));//中序遍历
    void postorder(void (*thevisit) (treenode* node));//后序遍历
    void levelorder(void (*thevisit) (treenode* node));//。。层次遍历
   // void levelorder();
    void insert_tree(int n);
    void height_total();
    void num_node_total();
private:
    void preorder(treenode* curnode)
    {
        if (curnode != nullptr)
        {
            visit(curnode);
            preorder(curnode->left);
            preorder(curnode->right);
        }
        //cout<<endl;
        return;
    }
    int height(treenode* curnode);
    void inorder(treenode* curnode);
    void postorder(treenode* curnode);
    void levelorder(treenode* curnode);
    int num_node(treenode*curnode);//计算一个节点下的所有节点的个数
    treenode* root;
    treenode**insert_use;//使用一个数组来储存节点，每个索引表示该节点的值，因为节点的插入顺序是不固定的，需要去查找节点
   // int (Tree::* intvisit)(treenode* node);
    void (*visit)(treenode* root);//一个函数指针，指向一个以指针为输入，返回为void的函数
    int treesize;
};

void Tree::insert_tree(int n)//用于填充这一棵树
{
   
    insert_use[1]=root;
    int start=1;
    for(int i=1;i<=n;i++)
    {
      int a,b;
      cin>>a>>b;
      treenode*x=insert_use[i];
      
      if(a!=-1)
      {
        x->left=new treenode(a,start++);
        insert_use[a]=x->left;
      }
      if(b!=-1)
      {
        x->right=new treenode(b,start++);
        insert_use[b]=x->right;
      }
      x=nullptr;
    }
    return;
}

void Tree::inorder(treenode* curnode)
{
    stack<treenode*> in;

    do {
        while (curnode)//如果节点不为空,不断地遍历左子树，直到最后一个节点
        {
            in.push(curnode);
            curnode = curnode->left;
        }

        if (!in.empty())//当上面的循环第一次结束时表示最后一个最左边的叶子节点
        {
            visit(in.top());
            curnode = in.top();
            in.pop();
            curnode = curnode->right;
        }
    } while (!in.empty() || curnode);
    cout << endl;
    return;
}

void Tree::postorder(treenode* curnode)
{
    stack<treenode*> one;//这个是用于将树的每个节点的左子节点和右子节点放入stack中，左节点先入，右节点后入，那么先出来的是右节点，可以先处理右节点的子树，并且将右节点先入two stack。
    //这个stack用于决定左节点和右节点的操作顺序
    stack<treenode*> two;//这个是将从one中出栈的节点储存
    if (curnode == nullptr)//当这棵树为空时
    {
        return;
    }
    one.push(curnode);//先将根节点压入
    while (!one.empty())
    {
        two.push(one.top());
        curnode = one.top();
        one.pop();
        if (curnode->left != nullptr)
        {
            one.push(curnode->left);//先入栈左节点
        }
        if (curnode->right != nullptr)
        {
            one.push(curnode->right);//后入栈右节点
        }
    }

    while (!two.empty())
    {
        cout << two.top()->element << ' ';
        two.pop();
    }
    cout << endl;
    return;
}

void Tree::preorder(void (*thevisit) (treenode* node))
{
    visit = thevisit;
    preorder(root);
    cout << endl;
    return;
}

void Tree::inorder(void (*thevisit) (treenode* node))
{
    visit = thevisit;
    inorder(root);
    return;
}

void Tree::postorder(void (*thevisit) (treenode* node))
{
    visit = thevisit;
    postorder(root);
    return;
}

void Tree::levelorder(treenode* curnode)
{
    queue<treenode*> level;
    level.push(curnode);//root先入队
    while (!level.empty())
    {
        visit(level.front());
        if (level.front()->left != nullptr)
        {
            level.push(level.front()->left);
        }
        if (level.front()->right != nullptr)
        {
            level.push(level.front()->right);
        }
        level.pop();
    }
    cout << endl;
    return;
}

void Tree::levelorder(void (*thevisit) (treenode* node))
{
    visit = thevisit;
    levelorder(root);
    return;
}


void Tree::height_total()
{
   for(int i=1;i<=treesize;i++)
   {
     cout<<height(insert_use[i])<<' ';
   }
   cout<<endl;
    return;
}

int Tree::height(treenode* curnode)
{
    if (curnode == nullptr)
    {
        return 0;
    }

    int hl = height(curnode->left);
    int hr = height(curnode->right);
    int h = max(hl, hr) + 1;
    //cout << h << ' ';
    return h;
}

void Tree::num_node_total()
{
    for(int i=1;i<=treesize;i++)
    {
      cout<<num_node(insert_use[i])<<' ';
    }
    cout<<endl;
    return;
}

int Tree::num_node(treenode*curnode)
{
   if(curnode==nullptr)
   {
      return 0;
   }

   int left_num=num_node(curnode->left);
   int right_num=num_node(curnode->right);  
   return left_num+right_num+1;
} 

void output(treenode* node);

int main()
{
    int n;
    cin >> n;
    Tree test(n);
    test.insert_tree(n);
    test.preorder(output);
    test.inorder(output);
    test.postorder(output);
    test.levelorder(output);
    test.num_node_total();
    test.height_total();
    return 0;
}

void output(treenode* node)//用于输出节点的一个函数，用于传入函数中设置visit
{
    cout << node->element << ' ';
    return;
}