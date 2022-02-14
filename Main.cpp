#include <bits/stdc++.h>
#include <string>
#include "BTree.h"
#include "sorting.h"


using namespace std;
vector<string> res;
class Database
{
public:
    string table_name;
    vector<BTree> trees;
    vector<Node *> glob2;
    vector<string> glob;
    int idd[1000] = {0};
    Database(string name, vector<string> info)
    {
        table_name = name;
        idd[0] = 1;
        for (int i = 0; i < info.size(); i++)
        {
            string column_name = info[i];
            string column_type = info[i + 1];
            BTree t(3, column_name, column_type);
            trees.push_back(t);
            i++;
        }
    }
    void insert(vector<string> values)
    {
        LinkedList row;

        for (int i = 0; i < values.size(); i++)
        {
            if (trees[i].btree_type == "timestamp")
            {
                row.add(trees[i].TimeHashFunction(values[i]));
                trees[i].insertTime(values[i]);
            }
            else if (trees[i].btree_type == "int")
            {
                row.add(stoi(values[i]));
                trees[i].insertValue(values[i]);
            }
            else
            {
                row.add(trees[i].StringHashFunction(values[i]));
                trees[i].insertString(values[i]);
            }
        }
        for (int i = 0; i < values.size(); i++)
        {
            trees[i].insert(row.place(i));
            // trees[i].display();
            // cout << endl;
        }
        // row.display();
    }

    int deletee(string operatorr, string col, string value)
    {
        threshold = 0;
        flag = 0;
        if (operatorr == "==")
        {
            yogurt = NULL;
            BTreeNode *check = NULL;
            int d;
            Node *next, *present;
            for (int i = 0; i < trees.size(); i++)
            {
                if (trees[i].btree_name == col)
                {
                    if (trees[i].btree_type == "timestamp")
                    {
                        flag = 0;
                        trees[i].traverse(trees[i].TimeHashFunction(value));
                        present = yogurt;
                        if (present == NULL)
                            return -1;

                        // cout << "checkmate " << present->data << endl;
                        next = present->nextField;
                        trees[i].remove(present->data, present);
                        // cout << present->data << endl;
                    }
                    else if (trees[i].btree_type == "int")
                    {
                        trees[i].traverse(stoi(value));
                        present = yogurt;
                        if (present == NULL)
                        {
                            return -1;
                        }
                        next = present->nextField;
                        if (trees[i].btree_name == "id")
                            idd[present->data] = 0;
                        trees[i].remove(present->data, present);
                        // cout << "nextttt one " << next->data << endl;
                    }
                    else
                    {
                        // cout << "double check : ";
                        // trees[i].display();
                        // cout << endl;
                        trees[i].traverse(trees[i].StringHashFunction(value));
                        // cout << endl;
                        present = yogurt;
                        if (present == NULL)
                            return -1;
                        // cout << present->data << " also " << present->nextField->data << endl;
                        next = present->nextField;
                        trees[i].remove(present->data, present);
                        // cout << "nexttttt " << next->data << endl;
                    }
                    // trees[i].display();
                    // cout << endl;

                    int counter = 1, t = i + 1;
                    if (t == trees.size())
                        t = 0;
                    while (counter != trees.size())
                    {
                        present = next;
                        next = present->nextField;
                        // cout << "check point " << present->data << " dd " << present->nextField->data << endl;
                        // trees[t].display(); cout << endl;
                        if (trees[t].btree_name == "id")
                            idd[present->data] = 0;
                        trees[t].remove(present->data, present);
                        // cout << "next one " << next->data << endl;
                        counter++;
                        t++;
                        if (t == trees.size())
                            t = 0;
                    }
                }
            }
        }
        else if (operatorr == "<")
        {
            yogurt = NULL;
            BTreeNode *check = NULL;
            int d;
            Node *next, *present;
            for (int i = 0; i < trees.size(); i++)
            {
                if (trees[i].btree_name == col)
                {
                    if (trees[i].btree_type == "timestamp")
                    {
                        trees[i].traverse_smaller(trees[i].TimeHashFunction(value));
                        present = yogurt;
                        if (present == NULL)
                            return -1;
                        next = present->nextField;
                        trees[i].remove(present->data, present);
                        // cout << present->data << endl;
                    }
                    else if (trees[i].btree_type == "int")
                    {
                        trees[i].traverse_smaller(stoi(value));
                        present = yogurt;
                        if (present == NULL)
                        {
                            return -1;
                        }
                        // cout << present->data << " < " << stoi(value) << endl;
                        next = present->nextField;
                        if (trees[i].btree_name == "id")
                            idd[present->data] = 0;
                        trees[i].remove(present->data, present);
                        // cout << "nexttttt " << next->data << endl;
                    }
                    else
                    {
                        trees[i].traverse_smaller(trees[i].StringHashFunction(value));
                        present = yogurt;
                        if (present == NULL)
                            return -1;
                        // cout << present->data << " also " << trees[i].StringHashFunction(value) << endl;
                        next = present->nextField;
                        trees[i].remove(present->data, present);
                        // cout << "nexttttt " << next->data << endl;
                    }
                    // trees[i].display();
                    // cout << endl;

                    int counter = 1, t = i + 1;
                    if (t == trees.size())
                        t = 0;
                    while (counter != trees.size())
                    {
                        present = next;
                        next = present->nextField;
                        // cout << "check point " << present->data << " dd " << present->nextField->data << endl;
                        if (trees[t].btree_name == "id")
                            idd[present->data] = 0;
                        trees[t].remove(present->data, present);
                        // cout << "next one " << next->data << endl;

                        counter++;
                        t++;
                        if (t == trees.size())
                            t = 0;
                    }
                }
            }
        }
        else if (operatorr == ">")
        {
            yogurt = NULL;
            BTreeNode *check = NULL;
            int d;
            Node *next, *present;
            for (int i = 0; i < trees.size(); i++)
            {
                if (trees[i].btree_name == col)
                {
                    if (trees[i].btree_type == "timestamp")
                    {
                        trees[i].traverse_greater(trees[i].TimeHashFunction(value));
                        present = yogurt;
                        if (present == NULL)
                            return -1;
                        next = present->nextField;
                        trees[i].remove(present->data, present);
                        // cout << present->data << endl;
                    }
                    else if (trees[i].btree_type == "int")
                    {

                        trees[i].traverse_greater(stoi(value));
                        present = yogurt;
                        if (present == NULL)
                        {
                            return -1;
                        }
                        // cout << present->data << " < " << stoi(value) << endl;
                        next = present->nextField;
                        if (trees[i].btree_name == "id")
                            idd[present->data] = 0;
                        trees[i].remove(present->data, present);
                        // cout << "nexttttt " << next->data << endl;
                    }
                    else
                    {
                        trees[i].traverse_greater(trees[i].StringHashFunction(value));
                        present = yogurt;
                        if (present == NULL)
                            return -1;
                        // cout << present->data << " also " << trees[i].StringHashFunction(value) << endl;
                        next = present->nextField;
                        trees[i].remove(present->data, present);
                        // cout << "nexttttt " << next->data << endl;
                    }
                    // trees[i].display();
                    // cout << endl;

                    int counter = 1, t = i + 1;
                    if (t == trees.size())
                        t = 0;
                    while (counter != trees.size())
                    {
                        present = next;
                        next = present->nextField;
                        // cout << "check point " << present->data << " dd " << present->nextField->data << endl;
                        if (trees[i].btree_name == "id")
                            idd[present->data] = 0;
                        trees[t].remove(present->data, present);
                        // cout << "next one " << next->data << endl;

                        counter++;
                        t++;
                        if (t == trees.size())
                            t = 0;
                    }
                }
            }
        }
        return 1;
    }

    int update(string operatorr, string col, string value)
    {
        threshold = 0;
        flag = 0;
        if (operatorr == "==")
        {
            yogurt = NULL;
            BTreeNode *check = NULL;
            int d;
            Node *next, *present;
            for (int i = 0; i < trees.size(); i++)
            {
                if (trees[i].btree_name == col)
                {
                    if (trees[i].btree_type == "timestamp")
                    {
                        trees[i].traverse(trees[i].TimeHashFunction(value));
                        present = yogurt;
                        if (present == NULL)
                            return -1;
                        next = present->nextField;
                        trees[i].remove(trees[i].TimeHashFunction(value), present);
                        // cout << present->data << endl;
                    }
                    else if (trees[i].btree_type == "int")
                    {
                        if (trees[i].btree_name == "id")
                            glob.push_back(value);
                        trees[i].traverse(stoi(value));
                        present = yogurt;
                        if (present == NULL)
                        {
                            return -1;
                        }
                        next = present->nextField;
                        trees[i].remove(stoi(value), present);
                        // cout << present->data << endl;
                    }
                    else
                    {
                        trees[i].traverse(trees[i].StringHashFunction(value));
                        present = yogurt;
                        if (present == NULL)
                            return -1;
                        // cout << present->data << " also " << trees[i].StringHashFunction(value) << endl;
                        next = present->nextField;
                        trees[i].remove(present->data, present);
                        // cout << "nexttttt " << next->data << endl;
                    }
                    // trees[i].display();
                    // cout << endl;

                    int counter = 1, t = i + 1;
                    if (t == trees.size())
                        t = 0;
                    while (counter != trees.size())
                    {
                        present = next;
                        next = present->nextField;
                        // cout << "check point " << present->data << " dd " << present->nextField->data << endl;
                        if (trees[t].btree_name == "id")
                            glob.push_back(to_string(present->data));
                        trees[t].remove(present->data, present);
                        // cout << "next one " << next->data << endl;

                        counter++;
                        t++;
                        if (t == trees.size())
                            t = 0;
                    }
                }
            }
        }
        else if (operatorr == "<")
        {
            yogurt = NULL;
            BTreeNode *check = NULL;
            int d;
            Node *next, *present;
            for (int i = 0; i < trees.size(); i++)
            {
                if (trees[i].btree_name == col)
                {
                    if (trees[i].btree_type == "timestamp")
                    {
                        trees[i].traverse_smaller(trees[i].TimeHashFunction(value));
                        present = yogurt;
                        if (present == NULL)
                            return -1;
                        next = present->nextField;
                        trees[i].remove(present->data, present);
                        // cout << present->data << endl;
                    }
                    else if (trees[i].btree_type == "int")
                    {
                        if (trees[i].btree_name == "id")
                            glob.push_back(value);
                        trees[i].traverse_smaller(stoi(value));
                        present = yogurt;
                        if (present == NULL)
                        {
                            return -1;
                        }
                        next = present->nextField;
                        trees[i].remove(present->data, present);
                        // cout << present->data << endl;
                    }
                    else
                    {
                        trees[i].traverse_smaller(trees[i].StringHashFunction(value));
                        present = yogurt;
                        if (present == NULL)
                            return -1;
                        // cout << present->data << " also " << trees[i].StringHashFunction(value) << endl;
                        next = present->nextField;
                        trees[i].remove(present->data, present);
                        // cout << "nexttttt " << next->data << endl;
                    }
                    // trees[i].display();
                    // cout << endl;

                    int counter = 1, t = i + 1;
                    if (t == trees.size())
                        t = 0;
                    while (counter != trees.size())
                    {
                        present = next;
                        next = present->nextField;
                        // cout << "check point " << present->data << " dd " << present->nextField->data << endl;
                        if (trees[t].btree_name == "id")
                            glob.push_back(to_string(present->data));
                        trees[t].remove(present->data, present);
                        // cout << "next one " << next->data << endl;

                        counter++;
                        t++;
                        if (t == trees.size())
                            t = 0;
                    }
                }
            }
        }
        else if (operatorr == ">")
        {
            yogurt = NULL;
            BTreeNode *check = NULL;
            int d;
            Node *next, *present;
            for (int i = 0; i < trees.size(); i++)
            {
                if (trees[i].btree_name == col)
                {
                    if (trees[i].btree_type == "timestamp")
                    {
                        trees[i].traverse_greater(trees[i].TimeHashFunction(value));
                        present = yogurt;
                        if (present == NULL)
                            return -1;
                        next = present->nextField;
                        trees[i].remove(present->data, present);
                        // cout << present->data << endl;
                    }
                    else if (trees[i].btree_type == "int")
                    {
                        if (trees[i].btree_name == "id")
                            glob.push_back(value);
                        trees[i].traverse_greater(stoi(value));
                        present = yogurt;
                        if (present == NULL)
                        {
                            return -1;
                        }
                        next = present->nextField;
                        trees[i].remove(present->data, present);
                        // cout << present->data << endl;
                    }
                    else
                    {
                        trees[i].traverse_greater(trees[i].StringHashFunction(value));
                        present = yogurt;
                        if (present == NULL)
                            return -1;
                        // cout << present->data << " also " << trees[i].StringHashFunction(value) << endl;
                        next = present->nextField;
                        trees[i].remove(present->data, present);
                        // cout << "nexttttt " << next->data << endl;
                    }
                    // trees[i].display();
                    // cout << endl;

                    int counter = 1, t = i + 1;
                    if (t == trees.size())
                        t = 0;
                    while (counter != trees.size())
                    {
                        present = next;
                        next = present->nextField;
                        // cout << "check point " << present->data << " dd " << present->nextField->data << endl;
                        if (trees[t].btree_name == "id")
                            glob.push_back(to_string(present->data));
                        trees[t].remove(present->data, present);
                        // cout << "next one " << next->data << endl;

                        counter++;
                        t++;
                        if (t == trees.size())
                            t = 0;
                    }
                }
            }
        }
        return 1;
    }
    int select(string operatorr, string col, string value)
    {
        flag = 0;
        if (operatorr == "==")
        {
            yogurt = NULL;
            BTreeNode *check = NULL;
            int d;
            Node *next, *present;
            for (int i = 0; i < trees.size(); i++)
            {
                if (trees[i].btree_name == col)
                {
                    if (trees[i].btree_type == "timestamp")
                    {
                        trees[i].traverse(trees[i].TimeHashFunction(value));
                        present = yogurt;
                        if (present == NULL)
                            return -1;
                        next = present->nextField;
                        // cout << present->data << endl;
                    }
                    else if (trees[i].btree_type == "int")
                    {

                        trees[i].traverse(stoi(value));
                        present = yogurt;
                        if (present == NULL)
                        {
                            return -1;
                        }
                        next = present->nextField;
                        if (trees[i].btree_name == "id")
                            glob2.push_back(present);
                        // cout << "NN " << present->data << " " << next->data << endl;
                    }
                    else
                    {
                        trees[i].traverse(trees[i].StringHashFunction(value));
                        present = yogurt;
                        if (present == NULL)
                            return -1;
                        // cout << present->data << " also " << trees[i].StringHashFunction(value) << endl;
                        next = present->nextField;
                        // cout << "nexttttt " << next->data << endl;
                    }
                    // trees[i].display();
                    // cout << endl;

                    int counter = 1, t = i + 1;
                    if (t == trees.size())
                        t = 0;
                    while (counter != trees.size())
                    {
                        present = next;
                        next = present->nextField;
                        if (trees[t].btree_name == "id")
                        {
                            glob2.push_back(present);
                        }
                        // cout << "next one " << next->data << endl;
                        counter++;
                        t++;
                        if (t == trees.size())
                            t = 0;
                    }
                }
            }
        }
        if (operatorr == "<")
        {
            yogurt = NULL;
            BTreeNode *check = NULL;
            int d;
            Node *next, *present;
            for (int i = 0; i < trees.size(); i++)
            {
                if (trees[i].btree_name == col)
                {
                    if (trees[i].btree_type == "timestamp")
                    {
                        trees[i].traverse_smaller(trees[i].TimeHashFunction(value));
                        present = yogurt;
                        if (present == NULL)
                            return -1;
                        next = present->nextField;
                        // cout << present->data << endl;
                    }
                    else if (trees[i].btree_type == "int")
                    {

                        trees[i].traverse_smaller(stoi(value));
                        present = yogurt;
                        if (present == NULL)
                        {
                            return -1;
                        }
                        next = present->nextField;
                        if (trees[i].btree_name == "id")
                            glob2.push_back(present);
                        // cout << "NN " << present->data << " " << next->data << endl;
                    }
                    else
                    {
                        trees[i].traverse_smaller(trees[i].StringHashFunction(value));
                        present = yogurt;
                        if (present == NULL)
                            return -1;
                        // cout << present->data << " also " << trees[i].StringHashFunction(value) << endl;
                        next = present->nextField;
                        // cout << "nexttttt " << next->data << endl;
                    }

                    int counter = 1, t = i + 1;
                    if (t == trees.size())
                        t = 0;
                    while (counter != trees.size())
                    {
                        present = next;
                        next = present->nextField;
                        if (trees[t].btree_name == "id")
                        {
                            glob2.push_back(present);
                        }
                        // cout << "next one " << next->data << endl;
                        counter++;
                        t++;
                        if (t == trees.size())
                            t = 0;
                    }
                }
            }
        }
        if (operatorr == ">")
        {
            yogurt = NULL;
            BTreeNode *check = NULL;
            int d;
            Node *next, *present;
            for (int i = 0; i < trees.size(); i++)
            {
                if (trees[i].btree_name == col)
                {
                    if (trees[i].btree_type == "timestamp")
                    {
                        trees[i].traverse_greater(trees[i].TimeHashFunction(value));
                        present = yogurt;
                        if (present == NULL)
                            return -1;
                        next = present->nextField;
                        // cout << present->data << endl;
                    }
                    else if (trees[i].btree_type == "int")
                    {

                        trees[i].traverse_greater(stoi(value));
                        present = yogurt;
                        if (present == NULL)
                        {
                            return -1;
                        }
                        next = present->nextField;
                        if (trees[i].btree_name == "id")
                            glob2.push_back(present);
                        // cout << "NN " << present->data << " " << next->data <<  endl;
                    }
                    else
                    {
                        trees[i].traverse_greater(trees[i].StringHashFunction(value));
                        present = yogurt;
                        if (present == NULL)
                            return -1;
                        // cout << present->data << " also " << trees[i].StringHashFunction(value) << endl;
                        next = present->nextField;
                        // cout << "nexttttt " << next->data << endl;
                    }

                    int counter = 1, t = i + 1;
                    if (t == trees.size())
                        t = 0;
                    while (counter != trees.size())
                    {
                        present = next;
                        next = present->nextField;
                        if (trees[t].btree_name == "id")
                        {
                            glob2.push_back(present);
                        }
                        // cout << "next one " << next->data << endl;
                        counter++;
                        t++;
                        if (t == trees.size())
                            t = 0;
                    }
                }
            }
        }
        return 1;
    }
    void print(vector<string> cols)
    {
        int j = 0, counter = 0;
        string tmp = "";
        // cout << trees[1].table[glob2[0]->nextField->data] << endl;
        for (int k = 0; k < glob2.size(); k++)
        {
            for (int i = 0; i < trees.size(); i++)
            {
                for (int j = 0; j < cols.size(); j++)
                {
                    if (trees[i].btree_name == cols[j])
                    {
                        // cout << trees[i].table[glob2[k]->data] << " ";
                        if (trees[i].btree_type == "string")
                            tmp += trees[i].table[glob2[k]->data].substr(1, trees[i].table[glob2[k]->data].size() - 2);
                        else
                            tmp += trees[i].table[glob2[k]->data];

                        if (counter != cols.size() - 1)
                            tmp += " ";
                    }
                }
                glob2[k] = glob2[k]->nextField;
            }
            cout << tmp.substr(0, tmp.size() - 1) << endl;
            res.push_back(tmp.substr(0, tmp.size() - 1));
            tmp = "";
        }
        glob2.clear();
    }
    // void show()
    // {
    //     for (int i = 0; i < trees.size(); i++)
    //         trees[i].display();
    //     cout << endl;
    // }
};



int main()
{
    int n, index, index2;
    string input;
    vector<Database> tables;
    cin >> n;
    cin.ignore(256, '\n');
    for (int i = 0; i < n; i++)
    {
        getline(cin, input);
        if (input[0] == 'C')
        {
            index = input.find("(");
            string tmp = input.substr(0, index - 1);
            vector<string> firstpart;
            istringstream iss(tmp);
            for (std::string s; iss >> s;)
                firstpart.push_back(s);

            string table_name = firstpart[2];

            index2 = input.find(")");
            string cols = input.substr(index + 1, index2 - index - 1);
            vector<string> tokens;
            tokens.push_back("id");
            tokens.push_back("int");
            int l = 0;
            string tt = "";
            for (int j = 0; j < cols.size(); j++)
            {
                if (cols[j] != ' ' && cols[j] != ',')
                {
                    tt += cols[j];
                }
                else if (tt != "")
                {
                    tokens.push_back(tt);
                    tt = "";
                }
            }
            if (tt != "")
                tokens.push_back(tt);
            // for (int i = 0; i < tokens.size(); i++)
            //     cout << tokens[i] << " / ";
            // cout << endl;
            Database d(table_name, tokens);
            tables.push_back(d);
        }
        if (input[0] == 'I')
        {
            index = input.find("(");
            string tmp = input.substr(0, index - 1);
            vector<string> firstpart;
            istringstream iss(tmp);
            for (std::string s; iss >> s;)
                firstpart.push_back(s);

            string table_name = firstpart[2];
            index2 = input.find(")");
            string cols = input.substr(index + 1, index2 - index - 1);
            vector<string> tokens;
            tokens.push_back("-");
            int l = 0;
            string tt = "";
            for (int j = 0; j < cols.size(); j++)
            {
                if (cols[j] != ' ' && cols[j] != ',')
                {
                    tt += cols[j];
                }
                else if (tt != "")
                {
                    tokens.push_back(tt);
                    tt = "";
                }
            }
            if (tt != "")
                tokens.push_back(tt);
            // for (int j = 0; j < tokens.size(); j++)
            //     cout << tokens[j] << " ";
            // cout << endl;

            for (int j = 0; j < tables.size(); j++)
            {
                if (tables[j].table_name == table_name)
                {
                    for (int k = 0; k < 1000; k++)
                        if (tables[j].idd[k] == 0)
                        {
                            tokens[0] = (to_string(k));
                            tables[j].idd[k] = 1;
                            break;
                        }
                    tables[j].insert(tokens);
                }
                // tables[i].show();
            }
        }
        if (input[0] == 'D')
        {
            threshold = 0;
            int end = input.find("WHERE");
            string input1 = input.substr(0, end + 5);
            string input2 = input.substr(end + 5, input.size() - end - 4);

            vector<string> tokens;
            istringstream iss(input1);
            for (std::string s; iss >> s;)
                tokens.push_back(s);
            string table_name = tokens[2];

            if (input2.find("==") != -1)
            {
                vector<string> helper;
                int l = 0;
                string tt = "";
                for (int j = 0; j < input2.size(); j++)
                {
                    if (input2[j] != ' ' && input2[j] != '=')
                    {
                        tt += input2[j];
                    }
                    else if (tt != "")
                    {
                        helper.push_back(tt);
                        tt = "";
                    }
                }
                if (tt != "")
                    helper.push_back(tt);
                string col = helper[0];
                string val = helper[1];
                // cout << col << " " << val << endl;
                // return 0;
                for (int j = 0; j < tables.size(); j++)
                {
                    if (tables[j].table_name == table_name)
                    {
                        int checkdel = tables[j].deletee("==", col, val);
                        // tables[j].show();
                        while (checkdel != -1)
                        {
                            checkdel = tables[j].deletee("==", col, val);
                            // tables[j].show();
                        }
                    }
                    // tables[j].show();
                }
            }
            else if (input2.find('<') != -1)
            {

                vector<string> helper;
                int l = 0;
                string tt = "";
                for (int j = 0; j < input2.size(); j++)
                {
                    if (input2[j] != ' ' && input2[j] != '<')
                    {
                        tt += input2[j];
                    }
                    else if (tt != "")
                    {
                        helper.push_back(tt);
                        tt = "";
                    }
                }
                if (tt != "")
                    helper.push_back(tt);
                string col = helper[0];
                string val = helper[1];
                // cout << col << " " << val << endl;
                for (int j = 0; j < tables.size(); j++)
                {
                    if (tables[j].table_name == table_name)
                    {
                        int checkdel = tables[j].deletee("<", col, val);
                        while (checkdel != -1)
                        {
                            checkdel = tables[j].deletee("<", col, val);
                        }
                    }
                    // tables[j].show();
                }
            }
            else if (input2.find('>') != -1)
            {
                vector<string> helper;
                int l = 0;
                string tt = "";
                for (int j = 0; j < input2.size(); j++)
                {
                    if (input2[j] != ' ' && input2[j] != '>')
                    {
                        tt += input2[j];
                    }
                    else if (tt != "")
                    {
                        helper.push_back(tt);
                        tt = "";
                    }
                }
                if (tt != "")
                    helper.push_back(tt);
                string col = helper[0];
                string val = helper[1];
                // cout << col << " " << val << endl;

                for (int j = 0; j < tables.size(); j++)
                {
                    if (tables[j].table_name == table_name)
                    {
                        int checkdel = tables[j].deletee(">", col, val);
                        while (checkdel != -1)
                        {
                            checkdel = tables[j].deletee(">", col, val);
                        }
                    }
                    // tables[j].show();
                }
            }
        }
        if (input[0] == 'U')
        {
            threshold = 0;
            int end = input.find("WHERE");
            string input1 = input.substr(0, end + 5);
            string input2 = input.substr(end + 5, input.size() - end - 4);
            index = input1.find("(");
            string tmp = input1.substr(0, index - 1);
            vector<string> firstpart;
            istringstream iss(tmp);
            for (std::string s; iss >> s;)
                firstpart.push_back(s);

            string table_name = firstpart[1];

            index2 = input.find(")");
            string cols = input1.substr(index + 1, index2 - index - 1);
            // cout << cols << endl;
            vector<string> values;
            string tt = "";
            for (int j = 0; j < cols.size(); j++)
            {
                if (cols[j] != ' ' && cols[j] != ',')
                {
                    tt += cols[j];
                }
                else if (tt != "")
                {
                    values.push_back(tt);
                    tt = "";
                }
            }
            if (tt != "")
                values.push_back(tt);

            if (input.find("==") != -1)
            {
                vector<string> helper;
                int l = 0;
                string tt = "";
                for (int j = 0; j < input2.size(); j++)
                {
                    if (input2[j] != ' ' && input2[j] != '=')
                    {
                        tt += input2[j];
                    }
                    else if (tt != "")
                    {
                        helper.push_back(tt);
                        tt = "";
                    }
                }
                if (tt != "")
                    helper.push_back(tt);
                string col = helper[0];
                string val = helper[1];

                for (int j = 0; j < tables.size(); j++)
                {
                    if (tables[j].table_name == table_name)
                    {

                        int checkdel = tables[j].update("==", col, val);
                        // tables[j].show();
                        while (checkdel != -1)
                        {
                            checkdel = tables[j].update("==", col, val);
                            // tables[j].show();
                        }
                        for (int q = 0; q < tables[j].glob.size(); q++)
                        {
                            vector<string> updated;
                            updated.push_back(tables[j].glob[q]);
                            for (int w = 0; w < values.size(); w++)
                                updated.push_back(values[w]);
                            // for (int w = 0; w < updated.size(); w++)
                            //     cout << updated[w] << " ";
                            tables[j].insert(updated);
                        }
                        // tables[j].show();
                        tables[j].glob.clear();
                    }
                }
            }
            else if (input.find("<") != -1)
            {
                vector<string> helper;
                int l = 0;
                string tt = "";
                for (int j = 0; j < input2.size(); j++)
                {
                    if (input2[j] != ' ' && input2[j] != '<')
                    {
                        tt += input2[j];
                    }
                    else if (tt != "")
                    {
                        helper.push_back(tt);
                        tt = "";
                    }
                }
                if (tt != "")
                    helper.push_back(tt);
                string col = helper[0];
                string val = helper[1];

                for (int j = 0; j < tables.size(); j++)
                {
                    if (tables[j].table_name == table_name)
                    {

                        int checkdel = tables[j].update("<", col, val);
                        // tables[j].show();
                        while (checkdel != -1)
                        {
                            checkdel = tables[j].update("<", col, val);
                            // tables[j].show();
                        }
                        for (int q = 0; q < tables[j].glob.size(); q++)
                        {
                            vector<string> updated;
                            updated.push_back(tables[j].glob[q]);
                            for (int w = 0; w < values.size(); w++)
                                updated.push_back(values[w]);
                            // for (int w = 0; w < updated.size(); w++)
                            //     cout << updated[w] << " ";
                            tables[j].insert(updated);
                        }
                        // tables[j].show();
                        tables[j].glob.clear();
                    }
                }
            }
            else if (input.find(">") != -1)
            {
                vector<string> helper;
                int l = 0;
                string tt = "";
                for (int j = 0; j < input2.size(); j++)
                {
                    if (input2[j] != ' ' && input2[j] != '>')
                    {
                        tt += input2[j];
                    }
                    else if (tt != "")
                    {
                        helper.push_back(tt);
                        tt = "";
                    }
                }
                if (tt != "")
                    helper.push_back(tt);
                string col = helper[0];
                string val = helper[1];
                for (int j = 0; j < tables.size(); j++)
                {
                    if (tables[j].table_name == table_name)
                    {

                        int checkdel = tables[j].update(">", col, val);
                        // tables[j].show();
                        while (checkdel != -1)
                        {
                            checkdel = tables[j].update(">", col, val);
                            // tables[j].show();
                        }
                        for (int q = 0; q < tables[j].glob.size(); q++)
                        {
                            vector<string> updated;
                            updated.push_back(tables[j].glob[q]);
                            for (int w = 0; w < values.size(); w++)
                                updated.push_back(values[w]);
                            // for (int w = 0; w < updated.size(); w++)
                            //     cout << updated[w] << " ";
                            tables[j].insert(updated);
                        }
                        // tables[j].show();
                        tables[j].glob.clear();
                    }
                }
            }
        }
        if (input[0] == 'S')
        {
            vector<string> tokens;
            vector<string> values;
            if (input.find("(") == -1)
            {
                istringstream iss(input);
                for (std::string s; iss >> s;)
                    tokens.push_back(s);
                string table_name = tokens[3];
            }
            else
            {
                index = input.find("(");
                string tmp = input.substr(0, index - 1);
                istringstream iss(tmp);
                for (std::string s; iss >> s;)
                    tokens.push_back(s);

                index2 = input.find(")");
                string cols = input.substr(index + 1, index2 - index - 1);

                string tt = "";
                for (int j = 0; j < cols.size(); j++)
                {
                    if (cols[j] != ' ' && cols[j] != ',')
                    {
                        tt += cols[j];
                    }
                    else if (tt != "")
                    {
                        values.push_back(tt);
                        tt = "";
                    }
                }
                if (tt != "")
                    values.push_back(tt);
                // for (int k = 0; k < values.size(); k++)
                //     cout << values[k] << " ";
                string therest = input.substr(index2 + 1, input.size() - index2);
                tokens.push_back("-");
                istringstream cc(therest);
                for (std::string s; cc >> s;)
                    tokens.push_back(s);
            }

            string table_name = tokens[3];

            vector<string> cols;
            if (tokens[5].find("==") != -1)
            {
                threshold = 0;
                int spliter = tokens[5].find("==");
                string col = tokens[5].substr(0, spliter);
                string val = tokens[5].substr(spliter + 2, tokens[5].size() - spliter - 2);

                for (int j = 0; j < tables.size(); j++)
                {

                    if (tables[j].table_name == table_name)
                    {

                        if (tokens[1] == "*")
                        {
                            for (int k = 0; k < tables[j].trees.size(); k++)
                                values.push_back(tables[j].trees[k].btree_name);
                        }

                        int checkdel = tables[j].select("==", col, val);
                        // tables[i].show();
                        threshold++;
                        while (checkdel != -1)
                        {
                            checkdel = tables[j].select("==", col, val);
                            // tables[i].show();
                            threshold++;
                        }
                        // for (int q = 0; q < tables[j].glob2.size(); q++)
                        //     cout << tables[j].glob2[q]->data << " ";
                        // cout << endl;
                        tables[j].glob2 = bubbleSort(tables[j].glob2);
                        for (int q = 1; q < tables[j].glob2.size(); q++) {
                            if (tables[j].glob2[q]->data == tables[j].glob2[q-1]->data)
                                tables[j].glob2.erase(tables[j].glob2.begin()+q);
                        }
                        tables[j].print(values);
                        values.clear();
                        threshold = 0;
                    }
                    // tables[j].show();
                }
            }
            else if (tokens[5].find("<") != -1)
            {
                int spliter = tokens[5].find("<");
                string col = tokens[5].substr(0, spliter);
                string val = tokens[5].substr(spliter + 1, tokens[5].size() - spliter - 1);

                for (int k = 0; k < tables.size(); k++)
                {
                    if (tables[k].table_name == table_name)
                    {

                        if (tokens[1] == "*")
                        {
                            for (int j = 0; j < tables[k].trees.size(); j++)
                                values.push_back(tables[k].trees[j].btree_name);
                        }

                        int checkdel = tables[k].select("<", col, val);
                        // tables[i].show();
                        threshold++;
                        while (checkdel != -1)
                        {
                            checkdel = tables[k].select("<", col, val);
                            // tables[i].show();
                            threshold++;
                        }
                        tables[k].glob2 = bubbleSort(tables[k].glob2);
                        // for (int q = 0; q < tables[k].glob2.size(); q++)
                        //     cout << tables[k].glob2[q]->data << " ";
                        // cout << endl;
                        tables[k].print(values);
                        values.clear();
                        threshold = 0;
                    }
                    // tables[k].show();
                }
            }
            else if (tokens[5].find(">") != -1)
            {
                int spliter = tokens[5].find(">");
                string col = tokens[5].substr(0, spliter);
                string val = tokens[5].substr(spliter + 1, tokens[5].size() - spliter - 1);
                // cout << tables.size() << endl;
                for (int k = 0; k < tables.size(); k++)
                {

                    if (tables[k].table_name == table_name)
                    {

                        if (tokens[1] == "*")
                        {
                            for (int j = 0; j < tables[k].trees.size(); j++)
                            {

                                values.push_back(tables[k].trees[j].btree_name);
                            }
                        }
                        // cout << tables[k].table_name << " " << col << " " << val << endl;
                        int checkdel = tables[k].select(">", col, val);
                        // tables[i].show();
                        threshold++;
                        while (checkdel != -1)
                        {
                            checkdel = tables[k].select(">", col, val);
                            // tables[i].show();
                            threshold++;
                        }
                        // for (int q = 0; q < tables[k].glob2.size(); q++)
                        // cout << tables[k].glob2[q]->data << " ";
                        // cout << endl;
                        tables[k].glob2 = bubbleSort(tables[k].glob2);
                        // for (int q = 0; q < tables[k].glob2.size(); q++)
                        //     cout << tables[k].glob2[q]->data << " ";
                        // cout << endl;
                        tables[k].print(values);
                        values.clear();
                        threshold = 0;
                    }
                    // tables[i].show();

                    // cout << "DDDDD" << endl;
                }
            }
        }
    }
    // cout << tables[0].res[0] << endl;
    // cout << "DDDDDDD" << endl;
    // for (int k = 0; k < tables.size(); k++)
    // for (int i = 0; i < res.size(); i++)
    //     cout << res[i] << endl;
    return 0;
}
