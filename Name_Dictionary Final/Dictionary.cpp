/* C++ Implementation of Dictionary using Trie Data Structure that supports insert, search, delete, and prefix search in O(length of word): Contributed by Surbhit */
#include <bits/stdc++.h>
using namespace std;
struct TrieNode
{
    struct TrieNode *child[256];
    bool isEndOfWord;
};
struct TrieNode *getNode(void)
{
    struct TrieNode *Node = new TrieNode;

    Node->isEndOfWord = false;

    for (int i = 0; i < 256; i++)
        Node->child[i] = NULL;

    return Node;
}
void insert(struct TrieNode *root, string key)
{
    struct TrieNode *temp = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = int(key[i]);
        if (!temp->child[index])
            temp->child[index] = getNode();
        temp = temp->child[index];
    }
    temp->isEndOfWord =true;
}
bool search(struct TrieNode *root, string key)
{
    struct TrieNode *temp = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = int(key[i]);
        if (!temp->child[index])
            return false;

        temp = temp->child[index];
    }

    return (temp != NULL && temp->isEndOfWord);
}
void print (TrieNode *root, char res[], int i)
{
    if(root==NULL)return ;
    if(root->isEndOfWord==true)
    {
        res[i]='\0';
        cout<<res<<"\n";
    }
    for(int j=0;j<256;j++)
    {
        if(root->child[j]!=NULL)
            res[i]=char(j);
        print(root->child[j],res,i+1);

    }
}
bool hasChild(TrieNode* root)
{
    for (int i = 0; i <256; i++)
        if (root->child[i])
            return true;
    return false;
}
int prefixSearch(TrieNode *root, string key)
{
    struct TrieNode *temp = root;
    for (int i = 0; i < key.length(); i++)
    {
        int index = int(key[i]);
        if (!temp->child[index])
            return -1;

        temp = temp->child[index];
    }
    if(temp==NULL)
        return -1;
    if(temp->isEndOfWord)
    {
        cout<<key<<endl;
        return 1;
    }
    else if(hasChild(temp))
    {
        char res[100];
        for(int i=0;i<key.size();i++)
            res[i]=key[i];
        print(temp,res,key.size());
        return 1;
    }
    return -1;
}
TrieNode* deleteNode(TrieNode* root, string key, int depth = 0)
{
    if (!root)
        return NULL;
    if (depth == key.size()) {
        if (root->isEndOfWord)
            root->isEndOfWord = false;
        if (!hasChild(root)) {
            delete (root);
            root = NULL;
        }

        return root;
    }
    int index = int(key[depth]);
    root->child[index] =
            deleteNode(root->child[index], key, depth + 1);
    if (!hasChild(root) && root->isEndOfWord == false) {
        delete (root);
        root = NULL;
    }
    return root;
}
int main()
{
    vector<string>keys={"Ravi Maurya", "Abhay Singh", "Aditya Wankhede","Gaurav Sachdeva",
                        "Vaibhav AgraWal" ,"Chetan Bhalotia", "Aditya Garg", "Aditya Singh",
                        "Sarfaraj Alam", "Rakesh Pandey", "Jatin Bansal", "Yogesh Chaudhary",
                        "Raghav Binani", "Ashok Kumar","Ritik Kumar","Shudhanshu Gupta",
                        "Vikash Goyal" ,"Vikash Saini", "Sidhartha Basista", "Aditya Bansal"};
    int n =keys.size();
    struct TrieNode *root = getNode();
    for (int i = 0; i < n; i++)
        insert(root, keys[i]);
    int input;
    cout<<"\n**************Welcome*************\n";
    do
    {
        cout<<"\nPlease choose an operation to be perform on dictionary\n";
        cout<<"1:To Search a name in dictionary\n2:To insert a new word in dictionary\n3:To delete a existing word in dictionary\n";
        cout<<"4:To print Contents of dictionary\n5:To do auto complition Search or prefix Search on dictionary\n";
        cout<<"0:To Exit\nYour input: ";
        cin>>input;
        switch(input)
        {
            case 1:
            {
                string name;
                //important to use getline to take input for space first
                getline(cin,name);
                cout<<"Enter the name to be search\n";
                //Now getline will override space to the input name
                getline(cin,name);
                if(search(root,name))
                {
                    cout<<"Yes name "<<name<<" is present in dictionary\n";
                    break;
                }
                else
                {

                    cout<<"No Name:"<<name<<" is not present in dictionary\n";
                    break;
                }
            }
            case 2:
            {
                string name;
                getline(cin,name);
                cout<<"Enter the name to be inserted\n";
                getline(cin,name);
                if(search(root,name))
                {
                    cout<<"Name already exist\n";
                    break;
                }
                else
                {
                    insert(root,name);
                    cout<<"Name:"<<name<<" has been inserted successfully\n";
                    break;
                }
            }
            case 3:
            {
                string name;
                getline(cin,name);
                cout<<"Enter the name to be deleteed\n";
                getline(cin,name);
                if(!search(root,name))
                {
                    cout<<"Name does not exist\n";
                    break;
                }
                else
                {
                    deleteNode(root,name);
                    cout<<"Your name:"<<name<<" has been deleted successfully\n";
                    break;
                }
            }
            case 4:
            {
                char res[100];
                cout<<"The fallowing name are present in dictionary:\n";
                print(root,res,0);
                break;
            }
            case 5:
            {
                string name;
                cout<<"Enter Prefix string and then press enter\nPrefix String: ";
                cin>>name;
                int ind=prefixSearch(root,name);
                if(ind==-1)
                {
                    cout<<"No matching string exist\n";
                    break;
                }
                else
                {
                    cout<<"The above names matches with prefix "<<name<<endl;
                    break;
                }
            }
            case 0:
            {
                cout<<"Good Bye See You Soon\n";
                break;
            }
            default:
            {
                cout<<"Please try some valid input\n";
                break;
            }
        }
    }while(input!=0);
    return 0;
} 

