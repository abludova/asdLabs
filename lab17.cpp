#include<iostream>
#include <string>

//Алгоритм поиска простой и основан на основном принципе БДП, т.е мы сравнениями последовательно выходим к нужному узлу
//Алгоритм: если дерево пустое, сообщить, что узел не найден и остановиться иначе сравнить К со значением ключа корневого узла Х
//Максимальное количесвто сравнений при поиске С=2h идеально сбалансированное дерево: C=2(log(n+1))
//Минимальное среднее время поиска Т=О(log2n)


//Алгоритм добавления элемента: Если дерево пусто, заменить на дерево с одним корневым узлом и остановиться
//иначе сравнить К со значением ключа корневого узла Х : Если К>=Х рекурсивно добавть в правое поддерево
//Если К<Х рекурсивно добавить в левое поддерево
//“рекурсивно добавить”, на самом деле просто означает, что мы “переходим” влево или вправо, и пытаемся провернуть вставку уже в новом узле.
// Мы “бежим” по дереву вправо или влево, пока не не наткнемся на пустое дерево, т.е пока подходящее место не будет найдено.


//Идея удаления элемента делится на несколько случаев:у узла нет дочерних узлов; у узла есть левый дочерних узлов;
//у узла есть правый дочерних узлов; у узла есть оба ребёнка.
//В случае 1 просто удаляем узел, дополнительная работа не требуется.В случае 2 и 3 заменяем удаляемый узел на его потомка,
//на этом удаление заканчивается. Случай 4 самый сложный, но концепция такого удаления довольно проста — найти в правом поддереве минимальный элемент 
//и переместить его на место удаляемого узла.
class Tree
{
public:
    int value;
    Tree* parent;
    Tree* left;
    Tree* right;
    std::string string; // для линейно-скобочной записи.

    Tree(const int v, Tree* p)
    {
        value = v;
        parent = p;
    }
    Tree()
    {

    }
    Tree(std::string str)
    {
        string = str;
    }

    void add(const int v)
    {
        if (v > value)
        {
            if (right == nullptr)
            {
                right = new Tree(v, this);
            }
            else
            {
                right->add(v);
            }
        }
        else
        {
            if (left == nullptr)
            {
                left = new Tree(v, this);
            }
            else
            {
                left->add(v);
            }
        }
    }

    Tree* search(Tree* item, int v) // поиск поддерева по элементу
    {
        if (item == nullptr && item->value == v)
        {
            return item;
        }
        if (item != nullptr && item->value > v)
        {
            return search(item->left, v);
        }
        if (item != nullptr && item->value < v)
        {
            return search(item->right, v);
        }
    }

    Tree* Search(int v)
    {
        return search(this, v);
    }

    void remove(int value)
    {
        Tree* item = this->Search(value);
        if (item == nullptr) return;
        Tree* currentTree = nullptr;
        // удаление корня
        if (this == item)
        {
            if (item->right != nullptr)
            {
                currentTree = item->right;
                while (currentTree->left != nullptr)
                {
                    currentTree = currentTree->left;
                }

            }
            else if (item->left != nullptr)
            {
                currentTree = item->left;
                while (currentTree->right != nullptr)
                {
                    currentTree = currentTree->right;
                }
            }

            int val = currentTree->value;
            remove(val);
            item->value = val;

        }
        // удаление листьев
        else if (item->left == nullptr && item->right == nullptr && item->parent != nullptr)
        {
            if (item->parent->right == item)
            {
                item->parent->right = nullptr;
            }
            else
            {
                item->parent->left = nullptr;
            }
        }
        // удаление узла, который имеет левого потомка.
        else if (item->left != nullptr && item->right == nullptr && item->parent != nullptr)
        {
            item->left->parent = item->parent;
            if (item == item->parent->left)
            {
                *item->parent->left = *item->left;
            }
            else if (item == item->parent->right)
            {
                *item->parent->right = *item->left;
            }

        }
        // удаление узла, который имеет правого потомка.
        else if (item->left == nullptr && item->right != nullptr && item->parent != nullptr)
        {
            item->right->parent = item->parent;
            if (item == item->parent->left)
            {
                *item->parent->left = *item->right;
            }
            else if (item == item->parent->right)
            {
                *item->parent->right = *item->right;
            }

        }
        // удаление узла, который имеет оба потомка.
        else if (item->left != nullptr && item->right != nullptr && item->parent != nullptr)
        {
            currentTree = item->right;
            if (currentTree->left != nullptr)
            {
                while (currentTree->left != nullptr)
                {
                    currentTree = currentTree->left;
                }
                if (currentTree->right != nullptr)
                {
                    currentTree->right->parent = currentTree->parent;
                    currentTree->parent->left = currentTree->right;
                }
                else
                {
                    currentTree->parent->left = nullptr;
                }
                item->left->parent = currentTree;
                currentTree->left = item->left;
                if (item->parent->right == item)
                {
                    currentTree->parent = item->parent->right;
                    item->parent->right = currentTree;
                }
                else
                {
                    currentTree->parent = item->parent->left;
                    item->parent->left = currentTree;
                }
                currentTree->right = item->right;
                item->right->parent = currentTree;
            }
            else
            {
                item->left->parent = currentTree;
                currentTree->left = item->left;
                currentTree->parent = item->parent;
                if (item->parent->left == item)
                {
                    item->parent->left = currentTree;
                }
                else
                {
                    item->parent->right = currentTree;
                }
            }

        }


    }
    std::string toString(int value) // переводит число в строку
    {
        std::string result;

        if (value > 9)
        {
            result += char(value / 10 + 48);
            result += char(value % 10 + 48);
        }
        else
        {
            result += char(value + 48);
        }

        return result;
    }
    void print(Tree* tree) // переводит дерево в линейно-скобочуню запись
    {
        string += toString(tree->value);
        if (tree->left != nullptr || tree->right != nullptr)
        {
            string += '(';
            if (tree->left != nullptr)
            {
                print(tree->left);
            }
            string += ',';
            if (tree->right != nullptr)
            {
                print(tree->right);
            }
            string += ')';
        }

    }
    void Print()
    {
        print(this);
    }

    bool isDigital(const char elem)
    {
        return (elem >= '0' && elem <= '9') ? true : false;
    }

    Tree parse(std::string str) // парсит  строку в бинарное дерево
    {
        Tree result;
        int index;
        if (isDigital(str[0]) && isDigital(str[1]))
        {
            int val = (str[0] - 48) * 10 + str[1] - 48;
            result.value = val;
            index = 2;
        }
        else if (isDigital(str[0]) && !isDigital(str[1]))
        {
            int val = str[0] - 48;
            result.value = val;
            index = 1;
        }


        for (int i = index; i < str.size() - 1;)
        {
            if (isDigital(str[i]) && isDigital(str[i + 1]))
            {
                int value = (str[i] - 48) * 10 + str[i + 1] - 48;
                result.add(value);
                i += 2;
            }
            else if (isDigital(str[i]) && !isDigital(str[i + 1]))
            {
                int value = str[i] - 48;
                result.add(value);
                i++;
            }
            else
            {
                i++;
            }
        }
        return result;
    }
};



void main()
{
    std::string str = "8(3(1,6(4,7)),10(,14(13,)))";
    Tree tree;
    tree = tree.parse(str);
    Tree newTree = tree;
    newTree.remove(10);
    newTree.Print();
    for (auto& value : newTree.string)
    {
        std::cout << value;
    }
    /* std::cout << "Choose command: 1) add element, 2) remove element, 3)show tree by element" << std::endl;
     int n =-1;
     while (n != 0)
     {
         std::cin >> n;
         switch(n)
         {
         case 1:
         {
             int value;
             std::cout << "Input value to add:";
             std::cin >> value;
             newTree->add(value);
             newTree->Print();

             for (auto& value:newTree->string)
             {
                 std::cout << value;
             }
             newTree->string = "";
             break;

         }
         case 2:
         {
             int value;
             std::cout << "Input value to remove:";
             std::cin >> value;
             newTree->remove(value);
             newTree->Print();

             for (auto& value : newTree->string)
             {
                 std::cout << value;
             }
             newTree->string = "";
             break;
         }
         case 3:
         {
             newTree->Print();
             for (auto& value : newTree->string)
             {
                 std::cout << value;
             }
             newTree->string = "";
             break;
         }
         default:
         {
             newTree->Print();
             for (auto& value : newTree->string)
             {
                 std::cout << value;
             }
             newTree->string = "";
             break;
         }
         }

     }*/

}