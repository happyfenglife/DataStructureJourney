// 用类描述实现前缀树
// 测试链接 : https://leetcode.cn/problems/implement-trie-ii-prefix-tree/
#include <bits/stdc++.h>
using namespace std;

// 路是数组实现的
class Trie1
{
  struct Node
  {
    int pass;
    int end;
    Node *nexts[26];
    Node()
    {
      pass = 0;
      end = 0;
      for (int i = 0; i < 26; i++)
      {
        nexts[i] = nullptr;
      }
    }
  };

  Node *root;

public:
  Trie1()
  {
    root = new Node();
  }

  void insert(string word)
  {
    Node *node = root;
    node->pass++;
    for (int i = 0, path; i < word.size(); i++)
    {
      path = word[i] - 'a';
      if (!node->nexts[path])
      {
        node->nexts[path] = new Node();
      }

      node = node->nexts[path];
      node->pass++;
    }

    node->end++;
  }

  // 如果之前word插入过前缀树，那么此时删掉一次
  // 如果之前word没有插入过前缀树，那么什么也不做
  void erase(string word)
  {
    if (countWordsEqualTo(word) > 0)
    {
      Node *node = root;
      node->pass--;
      for (int i = 0, path; i < word.size(); i++)
      {
        path = word[i] - 'a';
        if (--node->nexts[path]->pass == 0)
        {
          node->nexts[path] = nullptr;
          return;
        }

        node = node->nexts[path];
      }

      node->end--;
    }
  }

  // 查询前缀树里，word单词出现了几次
  int countWordsEqualTo(string word)
  {
    Node *node = root;
    for (int i = 0, path; i < word.size(); i++)
    {
      path = word[i] - 'a';
      if (!node->nexts[path])
      {
        return 0;
      }

      node = node->nexts[path];
    }

    return node->end;
  }

  // 查询前缀树里，有多少单词以pre做前缀
  int countWordsStartingWith(string pre)
  {
    Node *node = root;
    for (int i = 0, path; i < pre.size(); i++)
    {
      path = pre[i] - 'a';
      if (!node->nexts[path])
      {
        return 0;
      }

      node = node->nexts[path];
    }

    return node->pass;
  }
};

// 路是哈希表实现的
class Trie2
{
  struct Node
  {
    int pass;
    int end;
    unordered_map<int, Node *> nexts;

    Node()
    {
      pass = 0;
      end = 0;
    }
  };

  Node *root;

public:
  Trie2()
  {
    root = new Node();
  }

  void insert(string word)
  {
    Node *node = root;
    node->pass++;
    for (int i = 0, path; i < word.size(); i++)
    {
      path = word[i];
      if (!node->nexts.count(path))
      {
        node->nexts[path] = new Node();
      }

      node = node->nexts[path];
      node->pass++;
    }

    node->end++;
  }

  void erase(string word)
  {
    if (countWordsEqualTo(word) > 0)
    {
      Node *node = root;
      Node *next;
      node->pass--;

      for (int i = 0, path; i < word.size(); i++)
      {
        path = word[i];
        next = node->nexts[path];
        if (--next->pass == 0)
        {
          node->nexts.erase(path);
          return;
        }

        node = next;
      }

      node->end--;
    }
  }

  int countWordsEqualTo(string word)
  {
    Node *node = root;
    for (int i = 0, path; i < word.size(); i++)
    {
      path = word[i];
      if (!node->nexts.count(path))
      {
        return 0;
      }

      node = node->nexts[path];
    }

    return node->end;
  }

  int countWordsStartingWith(string pre)
  {
    Node *node = root;
    for (int i = 0, path; i < pre.size(); i++)
    {
      path = pre[i];
      if (!node->nexts.count(path))
      {
        return 0;
      }

      node = node->nexts[path];
    }

    return node->pass;
  }
};