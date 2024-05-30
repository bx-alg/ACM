    static int minDepth(TreeNode *head)
    {
        if (head == nullptr)
        {
            return 0;
        }
        TreeNode *cur = head;
        TreeNode *mostRight = nullptr;
        while (cur != nullptr)
        {
            mostRight = cur->left;
            if (mostRight != nullptr)
            {
                while (mostRight->right != nullptr && mostRight->right != cur)
                {
                    mostRight = mostRight->right;
                }
                if (mostRight->right == nullptr)
                {
                    mostRight->right = cur;
                    cur = cur->left;
                    continue;
                } else
                {
                    mostRight->right = nullptr;
                }
            }
            cur = cur->right;
        }
    }