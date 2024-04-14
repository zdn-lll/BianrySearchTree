/*
 * @Author: ZhangDingNian
 * @Date: 2024-04-12 16:36:10
 * @LastEditors: ZhangDingNian
 * @LastEditTime: 2024-04-14 18:22:39
 */
#include <stdio.h>
#include <stdlib.h>

/// @brief 二叉树基础结构
typedef struct binary_tree_node
{
    int data;
    struct binary_tree_node *left;
    struct binary_tree_node *right;
} TreeNode, *TreeLink;

#define QUEUE_ARRAY_USER_DATATYPE TreeLink
#include "queue_array.h"

TreeLink Create_Tree_Node(int data);              // 创建一个新的二叉树节点
TreeLink bst_insert(TreeLink root, TreeLink new); // 按BST规定插入新节点
TreeLink bst_find(TreeLink root, int data);       // 查找搜索二叉树(BST)中的树数据
TreeLink bst_remove(TreeLink root, int data);     // 删除二叉搜索树中的节点data

void pre_travel(TreeLink root);          // 前序遍历
void mid_travel(TreeLink root);          // 中序遍历
void mid_travel_reversal(TreeLink root); // 反转中序遍历
void post_travel(TreeLink root);         // 后续遍历
void level_travel(TreeLink root);        // 按层遍历

/// @brief 创建一个新的二叉树节点
/// @param data 新节点的数据
/// @return 成功，返回指向新节点的指针。失败，返回 NULL。
TreeLink Create_Tree_Node(int data)
{
    TreeLink new = (TreeLink)calloc(1, sizeof(TreeNode));
    if (new == (TreeLink)NULL)
    {
        perror("calloc");
        return (TreeLink)NULL;
    }

    new->data = data;
    new->left = NULL;
    new->right = NULL;

    return new;
}

/// @brief 按BST规定插入新节点
/// @param root 指向树的根节点的指针
/// @param new 指向需要插入的新根节点的指针
/// @return 成功，返回指向根节点的指针。失败，返回 NULL。
/// @note BST(Binary Search Tree)搜索二叉树。BST规定：在任何子树中，根节点必须大于其左子树中任意的节点，且必须小于其右子树中任意的节点，换句话说必须满足“小(右)--中(根)--大(左)”的逻辑次序。
TreeLink bst_insert(TreeLink root, TreeLink new)
{
    if (root == (TreeLink)NULL)
    {
        return new;
    }

    if (new == (TreeLink)NULL)
    {
        return root;
    }

    if (new->data >= root->data)
    {
        root->right = bst_insert(root->right, new);
    }
    else
    {
        root->left = bst_insert(root->left, new);
    }
    return root;
}

/// @brief 查找搜索二叉树(BST)中的树数据
/// @param root 指向树的根节点的指针
/// @param data 需要查找的节点中的数据
/// @return 成功，返回指向目标节点的指针。失败，返回 NULL。
TreeLink bst_find(TreeLink root, int data)
{
    if (root == (TreeLink)NULL)
    {
        printf("Tree is NULL or data not found!\n");
        return (TreeLink)NULL;
    }

    if (data < root->data)
    {
        return bst_find(root->right, data);
    }
    else if (data > root->data)
    {
        return bst_find(root->left, data);
    }
    else
    {
        return root;
    }
}

/// @brief 删除二叉搜索树中的节点data
/// @param root 指向树的根节点的指针
/// @param data 需要查删除的节点中的数据
/// @return 成功，返回指向树的根节点的指针。失败，返回 NULL。
/// @note 二叉搜索树在删除节点后，仍要满足二叉搜索树“小(右)--中(根)--大(左)”的逻辑次序。
TreeLink bst_remove(TreeLink root, int data)
{
    if (root == (TreeLink)NULL)
    {
        return (TreeLink)NULL;
    }
    else if (root->data > data) // 需要删除的数据比根节点的数据小，则进入左子树中查找
    {
        root->left = bst_remove(root->left, data);
    }
    else if (root->data < data) // 需要删除的数据比根节点的数据大，则进入右子树中查找
    {
        root->right = bst_remove(root->right, data);
    }
    else if (root->data == data) // 需要删除的数据等于根节点的数据
    {
        if (root->left == NULL && root->right == NULL) // 需要删除的数据在叶子节点中，直接删除
        {
            free(root);
            return (TreeLink)NULL;
        }
        else if (root->left != NULL) // 有左子树，寻找左子树中的最大值节点，用其替换根节点并删除该节点。
        {
            TreeLink max = root->left;
            while (max->right != NULL)
            {
                max = max->right;
            }
            root->data = max->data;
            root->left = bst_remove(root->left, max->data);
        }
        else if (root->right != NULL) // 有右子树，寻找右子树中的最小值节点，用其替换根节点并删除该节点。
        {
            TreeLink min = root->right;
            while (min->left != NULL)
            {
                min = min->left;
            }
            root->data = min->data;
            root->right = bst_remove(root->right, min->data);
        }
    }

    return root;
}

/// @brief 前序遍历
/// @param root 指向树的根节点的指针
/// @note 前序遍历：即先访问根节点，再访问左子树，最后访问右子树。
void pre_travel(TreeLink root)
{
    if (root != (TreeLink)NULL)
    {
        printf("%d ", root->data);
        pre_travel(root->left);
        pre_travel(root->right);
    }
}

/// @brief 中序遍历
/// @param root 指向树的根节点的指针
/// @note 中序遍历：即先访问左子树，再访问根节点，最后访问右子树。用中序遍历，遍历里BST树，可以把BST中的元素，按从小到大的顺序输出。
void mid_travel(TreeLink root)
{
    if (root != (TreeLink)NULL)
    {
        mid_travel(root->left);
        printf("%d ", root->data);
        mid_travel(root->right);
    }
}

/// @brief 反转中序遍历
/// @param root 指向树的根节点的指针
/// @note 反转中序遍历：即先访问右子树，再访问根节点，最后访问左子树。用反转中序遍历，遍历里BST树，可以把BST中的元素，按从大到小的顺序输出。
void mid_travel_reversal(TreeLink root)
{
    if (root != (TreeLink)NULL)
    {
        mid_travel(root->right);
        printf("%d ", root->data);
        mid_travel(root->left);
    }
}

/// @brief 后续遍历
/// @param root 指向树的根节点的指针
/// @note 后续遍历：即先访问左子树，再访问右子树，最后访问根节点。
void post_travel(TreeLink root)
{
    if (root != (TreeLink)NULL)
    {
        post_travel(root->left);
        post_travel(root->right);
        printf("%d ", root->data);
    }
}

/// @brief 按层遍历
/// @param root 指向树的根节点的指针
void level_travel(TreeLink root)
{
    if (root == NULL)
        return;

    // 将根节点入队
    linkQueue *q = initQueue();
    enQueue(q, root);

    TreeLink tmp;
    while (!isEmpty(q))
    {
        // 出队并访问队头
        outQueue(q, &tmp);
        printf("%d ", tmp->data);

        // 依次将其左右孩子（若有）入队
        if (tmp->left != NULL)
            enQueue(q, tmp->left);

        if (tmp->right != NULL)
            enQueue(q, tmp->right);
    }
    printf("\n");
}

int main()
{
    TreeLink root = Create_Tree_Node(10);
    bst_insert(root, Create_Tree_Node(20));
    bst_insert(root, Create_Tree_Node(30));
    bst_insert(root, Create_Tree_Node(60));
    bst_insert(root, Create_Tree_Node(40));
    bst_insert(root, Create_Tree_Node(50));
    bst_insert(root, Create_Tree_Node(90));
    bst_insert(root, Create_Tree_Node(80));
    bst_insert(root, Create_Tree_Node(60));
    bst_insert(root, Create_Tree_Node(70));
    bst_insert(root, Create_Tree_Node(100));

    level_travel(root);

    mid_travel(root);
    printf("\n");
    mid_travel_reversal(root);
    printf("\n");


    // mid_travel(root);
    // printf("\n");

    // root = bst_remove(root, 10);

    // mid_travel(root);
    // printf("\n");
    // int data;
    // while (1)
    // {
    //     printf("输入命令：");
    //     scanf("%d", &data);
    //     if (data > 0)
    //     {
    //         bst_insert(root, Create_Tree_Node(data));
    //     }
    //     else if (data < 0)
    //     {
    //         bst_remove(root, -data);
    //     }
    //     else if (data == 0)
    //     {
    //         exit(0);
    //     }

    //     mid_travel(root);
    //     printf("\n");
    // }

    return 0;
}
