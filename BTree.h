
using namespace std;
int flag = 0, threshold = 0;
int flag_part=0;
class BTreeNode;
class Node{
public:
    int data; 
    Node *nextField; 
    BTreeNode *self; 
    friend class BTreeNode;
};
Node *yogurt;
class LinkedList
{
public: Node *head; Node *tail;
    int cnt;
    LinkedList()
    {
        head = NULL;
        tail = NULL;
        cnt = 0;
    }
    void add(long int data)
    {
        Node *newNode = new Node;
        newNode->nextField = NULL;
        newNode->data = data;
        if (head == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->nextField = newNode;
            tail = tail->nextField;
        }
        cnt++;
        tail->nextField = head;
    }
    Node place(int i)
    {
        Node *tmp = head;
        for (int j = 0; j < i; ++j)
        {
            tmp = tmp->nextField;
        }
        return *tmp;
    }
    void display()
    {
        Node *t = head;
        for (int i = 0; i < cnt; ++i)
        {
            cout << t->data << " ";
            t = t->nextField;
        }
        cout << endl;
    }
    friend class Node;
};
class BTreeNode
{
    int t; BTreeNode **Childs; int n; bool leaf;     
public:
    Node *keys;              
    BTreeNode(int t1, bool leaf1)
    {
        t = t1;leaf = leaf1;
        keys = new Node[2 * t - 1];
        Childs = new BTreeNode *[2 * t];
        this->n = 0;
    }

    void traverse_greater(long int k);
    void traverse(long int k);
    void traverse_smaller(long int k);
    // void display();
    long int findKey(long int k)
    {
        int idx = 0;
        while (idx < n && keys[idx].data < k)
            ++idx;
        return idx;
    }
    void insertNonFull(Node k)
    {
        int i = n - 1;
        if (leaf == true)
        {
            while (i >= 0 && keys[i].data > k.data)
            {
                keys[i + 1] = keys[i];
                i--;
            }
            keys[i + 1] = k;
            keys[i + 1].self = this;
            n++;
        }
        else 
        {
            while (i >= 0 && keys[i].data > k.data)
                i--;
            if (Childs[i + 1]->n == 2 * t - 1)
            {
                splitChild(i + 1, Childs[i + 1]);
                if (keys[i + 1].data < k.data)
                    i++;
            }
            Childs[i + 1]->insertNonFull(k);
        }
    }
    void splitChild(long int i, BTreeNode *y)
    {
        BTreeNode *z = new BTreeNode(y->t, y->leaf);
        z->n = t - 1;
        for (int j = 0; j < t - 1; j++)
            z->keys[j] = y->keys[j + t];
        if (y->leaf == false) {
            flag_part=0;
            if (flag_part==0)
                for (int j = 0; j < t; j++)
                    z->Childs[j] = y->Childs[j + t];
        }

        y->n = t - 1;

        for (int j = n; j >= i + 1; j--)
            Childs[j + 1] = Childs[j];

        Childs[i + 1] = z; 

        for (int j = n - 1; j >= i; j--)
            keys[j + 1] = keys[j];
        keys[i] = y->keys[t - 1];
        n++;
    }
    void remove(long int k, Node *past)
    {
        int ff = 0;int idx = findKey(k);int idx2 = idx; flag_part++;
        if (idx < n && keys[idx].data == past->data)
        {
            int flag_g = 0;
            while (idx2 < n && keys[idx2].data == past->data)
            {
                if (keys[idx2].nextField == past->nextField)
                {
                    flag_part++;
                    if (leaf) {
                        removeFromLeaf(idx2);
                    }else
                        removeFromNonLeaf(idx2, past);
                    flag_part++;
                    flag_g = 1;
                    break;
                }
                idx2++;
                flag_part++;
            }
            if (flag_g == 0)
            {
                idx2 = idx;
                if (leaf)
                    return;
                bool flag = ((idx2 == n) ? true : false);
                if (Childs[idx2]->n < t)
                    fill(idx2);
                if (flag && idx2 > n)
                    Childs[idx2 - 1]->remove(k, past);
                else
                    Childs[idx2]->remove(k, past);
            }
        }
        else
        {
            if (leaf)
                return;
        

            bool flag = ((idx == n) ? true : false);

            if (Childs[idx]->n < t)
            {
                fill(idx);
            }
            if (flag && idx > n)
            {

                Childs[idx - 1]->remove(k, past);
            }
            else
            {
                Childs[idx]->remove(k, past);
            }
        }
        return;
    }
    void removeFromLeaf(long int idx)
    {

        for (int i = idx + 1; i < n; ++i)
            keys[i - 1] = keys[i];
        n--;

        return;
    }
    void removeFromNonLeaf(long int idx, Node *past)
    {

        int k = keys[idx].data;

        if (Childs[idx]->n >= t)
        {
            Node pred = getPred(idx);
            keys[idx] = pred;
            Childs[idx]->remove(pred.data, &pred);
        }

        else if (Childs[idx + 1]->n >= t)
        {
            Node succ = getSucc(idx);
            keys[idx] = succ;
            Childs[idx + 1]->remove(succ.data, &succ);
        }
        else
        {
            merge(idx);
            Childs[idx]->remove(k, past);
        }
        return;
    }
    Node getSucc(long int idx)
    {
        BTreeNode *cur = Childs[idx + 1];
        while (!cur->leaf)
            cur = cur->Childs[0];
        return cur->keys[0];
    }
    Node getPred(long int idx)
    {

        BTreeNode *cur = Childs[idx];
        while (!cur->leaf)
            cur = cur->Childs[cur->n];
        return cur->keys[cur->n - 1];
    }
    void fill(long int idx)
    {
        if (idx != 0 && Childs[idx - 1]->n >= t)
        {
            borrowFromPrev(idx);
        }
        else if (idx != n && Childs[idx + 1]->n >= t)
            borrowFromNext(idx);
        else
        {
            if (idx != n)
            {
                merge(idx);
            }
            else
            {
                merge(idx - 1);
            }
        }
        return;
    }
    void borrowFromNext(long int idx)
    {

        BTreeNode *child = Childs[idx];
        BTreeNode *sibling = Childs[idx + 1];

        child->keys[(child->n)] = keys[idx];

        if (!(child->leaf)) {
            child->Childs[(child->n) + 1] = sibling->Childs[0];
        }

        keys[idx] = sibling->keys[0];

        for (int i = 1; i < sibling->n; ++i) {
            sibling->keys[i - 1] = sibling->keys[i];
        }
        flag_part--;
        if (!sibling->leaf)
        {
            if (true) {
                for (int i = 1; i <= sibling->n; ++i)
                    sibling->Childs[i - 1] = sibling->Childs[i];
            }
        }
        child->n += 1;
        sibling->n -= 1;

        return;
    }
    void merge(long int idx)
    {
        BTreeNode *child = Childs[idx];
        BTreeNode *sibling = Childs[idx + 1];

        child->keys[t - 1] = keys[idx];

        for (int i = 0; i < sibling->n; ++i) {
            child->keys[i + t] = sibling->keys[i];
        }
        if (!child->leaf)
        {
            for (int i = 0; i <= sibling->n; ++i)
                child->Childs[i + t] = sibling->Childs[i];
        }
        for (int i = idx + 1; i < n; ++i) {
            keys[i - 1] = keys[i];
        }
        for (int i = idx + 2; i <= n; ++i) {
            Childs[i - 1] = Childs[i];
        }
        child->n += sibling->n + 1;
        n--;

        delete (sibling);
        return;
    }
    void borrowFromPrev(long int idx)
    {

        BTreeNode *child = Childs[idx];BTreeNode *sibling = Childs[idx - 1];

        for (int i = child->n - 1; i >= 0; --i)
            child->keys[i + 1] = child->keys[i];

        if (!child->leaf)
        {
            for (int i = child->n; i >= 0; --i)
                child->Childs[i + 1] = child->Childs[i];
                flag_part++;
        }

        child->keys[0] = keys[idx - 1];

        if (!child->leaf)
            child->Childs[0] = sibling->Childs[sibling->n];
        flag_part++;
        keys[idx - 1] = sibling->keys[sibling->n - 1];

        child->n -= 1;
        sibling->n += 1;

        return;
    }
    friend class BTree;
};

class BTree
{
    BTreeNode *root;
    int t;
public:
    string btree_name;string btree_type;long long int BUCKET;vector<string> table;
    BTree(int _t, string name, string type)
    {
        root = NULL;
        t = _t;
        btree_name = name;
        btree_type = type;
        BUCKET = 650200;
        for (long long int i = 0; i < BUCKET; ++i)
            table.push_back("-1");
    }
    void insertString(string key)
    {
        long long int index = StringHashFunction(key);
        table[index] = key;
    }
    void insertTime(string key)
    {
        long long int index = TimeHashFunction(key);
        table[index] = key;
    }
    void insertValue(string key)
    {
        long long int index = stoi(key);
        table[index] = key;
    }
    long long int StringHashFunction(string x)
    {
        long long int tmp = 0;
        for (long long int i = 0; i < x.length(); ++i)
        {
            int a = int(x[i]);
            int b = pow(3.12, i);
            tmp += (a * b);
            tmp %= 100007;
        }
        return tmp;
    }
    long long int TimeHashFunction(string x)
    {
        long long int s = 0;
        vector<int> tokens;
        stringstream check1(x);
        string intermediate;
        while (getline(check1, intermediate, '/'))
            tokens.push_back(stoi(intermediate));
        long long int coef[3] = {413, 23, 3};
        for (long long int i = 0; i < tokens.size(); ++i)
        {
            s += tokens[i] * coef[i];
        }
        return s % BUCKET;
    }
    
    void traverse(long int k)
    {
        if (root != NULL)
            root->traverse(k);
    }
    void traverse_smaller(long int k)
    {
        if (root != NULL)
            root->traverse_smaller(k);
    }
    void traverse_greater(long int k)
    {
        if (root != NULL)
            root->traverse_greater(k);
    }
    // void display()
    // {
    //     if (root != NULL)
    //         root->display();
    // }
    void remove(long int k, Node *past)
    {
        if (!root)
            return;

        root->remove(k, past);
        if (root->n == 0)
        {
            BTreeNode *tmp = root;
            if (root->leaf)
                root = NULL;
            else
                root = root->Childs[0];

            delete tmp;
        }
        return;
    }
    void insert(Node k)
    {
        if (root == NULL)
        {
            root = new BTreeNode(t, true);
            root->keys[0] = k; 
            root->keys[0].self = root;

            root->n = 1; 
        }
        else 
        {
            if (root->n == 2 * t - 1)
            {
                BTreeNode *s = new BTreeNode(t, false);
                s->Childs[0] = root;
                s->splitChild(0, root);
                int i = 0;
                if (s->keys[0].data < k.data)
                    i++;
                s->Childs[i]->insertNonFull(k);
                root = s;
            }
            else 
                root->insertNonFull(k);
        }
    }
    friend class Hash;
};

void BTreeNode::traverse(long int k)
{

    int i;
    for (i = 0; i < n; i++)
    {
        if (leaf == false)
            Childs[i]->traverse(k);

        if (keys[i].data == k)
        {

            if (flag == threshold)
            {
                // cout << "HI! FOUND YOU MF!!! " << keys[i].data << " nextField is " << keys[i].nextField->data << endl;
                yogurt = &keys[i];
            }
            flag++;

        }
    }
    // Print the subtree rooted with last child
    if (leaf == false)
        Childs[i]->traverse(k);
}
void BTreeNode::traverse_smaller(long int k)
{
    // There are n keys and n+1 children, traverse through n keys
    // and first n children
    int i;
    for (i = 0; i < n; i++)
    {
        // If this is not leaf, then before printing key[i],
        // traverse the subtree rooted with child C[i].
        if (leaf == false)
            Childs[i]->traverse_smaller(k);
        // cout << " " << keys[i].data;
        if (keys[i].data < k)
        {
            if (flag == threshold)
            {
                // cout << "HI! FOUND YOU MF!!! " << keys[i].data << " nextField is " << keys[i].nextField->data << endl;
                yogurt = &keys[i];
            }
            flag++;
        }
    }
    // Print the subtree rooted with last child
    if (leaf == false)
        Childs[i]->traverse_smaller(k);
}
void BTreeNode::traverse_greater(long int k)
{

    int i;
    for (i = 0; i < n; i++)
    {
        // If this is not leaf, then before printing key[i],
        // traverse the subtree rooted with child C[i].
        if (leaf == false)
            Childs[i]->traverse_greater(k);
        // cout << " " << keys[i].data;
        if (keys[i].data > k)
        {
            if (flag == threshold)
            {
                // cout << "HI! FOUND YOU MF!!! " << keys[i].data << " nextField is " << keys[i].nextField->data << endl;
                yogurt = &keys[i];
            }
            flag++;
        }
    }
    // Print the subtree rooted with last child
    if (leaf == false)
        Childs[i]->traverse_greater(k);
}

// void BTreeNode::display()
// {
//     int i;
//     for (i = 0; i < n; i++)
//     {
//         if (leaf == false)
//             C[i]->display();
//     }
//     if (leaf == false)
//         C[i]->display();
// }
