#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int TreeItem;
typedef struct BinTree {
    TreeItem key;
    struct BinTree *left;
    struct BinTree *right;
    struct BinTree *parent;
} node;
// node (узел) - короткое название структуры BinTree. node хранит значение, а также ссылки на левый, правый и родительский узлы.



/* Создание корня дерева: создаем узел u, заполняем его атрибуты (только значение узла, key, ненулевое) и
присваиваем его созданному в main объекту структуры BinTree (локальное название - root). */

node *create(node *root, TreeItem key)
{
    node *u = malloc(sizeof(node));
    
    u -> key = key;
    u -> parent = NULL;
    u -> left = NULL;
    u -> right = NULL;
    root = u;
    return root;
}



/* Как в create, создаем узел u и заполняем атрибуты: ключ (key) и дети (NULL) известны, находим родителя.
Для этого проходим по узлам дерева, начиная с корня, пока не дойдем до пустого узла.
Переход к следующему узлу осуществляется в зависимости от значения добавляемой вершины:
если оно меньше значения рассматриваемого узла, то выбираем левого сына, и наоборот.
После этого заполняем атрибут parent новой вершины и добавляем ссылку на нее в атрибут родительской. */

node *add(node *root, TreeItem key)
{
    node *tmp_parent = root, *res_parent = NULL;
    node *u = malloc(sizeof(node));
    u -> key = key;
    while (tmp_parent != NULL)
    {
        res_parent = tmp_parent;
        if (key < tmp_parent -> key)
            tmp_parent = tmp_parent -> left;
        else
            tmp_parent = tmp_parent -> right;
    }
    u -> parent = res_parent;
    u -> left = NULL;
    u -> right = NULL;
    if (key < res_parent -> key)
        res_parent -> left = u;
    else
        res_parent -> right = u;
    return root;
}



/* Рекурсивная печать. Вначале фунция вызывается для всех правых вершин относительно родительской, начиная с корня.
Печать дерева начинается с его самой правой вершины. Далее печатается ее отец, потом левый брат и
все его правые потомки (не только сыновья), потом 1 левый брат и так далее аналогично.
Изначально n = 0. Это счетчик для количества пробелов (глубины дерева). */

void show_tree (node *root, int n) {
    if (root -> right)
        show_tree(root -> right, n+1);
    for (int i = 0; i < n; i++) {
        printf("  ");
    }
    printf("%d\n", root -> key);
    if (root -> left)
        show_tree(root -> left, n+1);
}


/* B-дерево: нет ни одного узла степени 1. Проверяем корень. Если это единственный узел графа, возвращаем true.
Иначе для пар атрибутов следующих узлов делаем (рекурсивно ) проверку на одновременное наличие-отсутствие значений пары атрибутов (left, right),
пока не найдется узел, у которого есть ровно 1 сын (тогда функция от корня выведет false && true = false),
либо пока не будут рекурсивно рассмотрены все узлы, включая листья дерева (получим true). */

int is_Btree(node *root) {
    if (root -> left == NULL && root -> right == NULL)
        return 1;
    if (root -> left != NULL && root -> right != NULL)
        return is_Btree(root -> left) && is_Btree(root -> right);
    return 0;
}


/* рекурсивный алгоритм поиска вершины по ключу для дерева поиска: если вершины нет или ключ соответствует вершине,
то функция завершается и возвращает данную вершину. Иначе переход к левому сыну, если ключ искомой вершины меньше рассматриваемого,
или переход к правому сыну в противном случае. */

node *search_node_by_key(node *root, int key)
{
    if ((root == NULL) || (root -> key == key))
        return root;
    if (key < root -> key)
        return search_node_by_key(root -> left, key);
    else
        return search_node_by_key(root -> right, key);
}



node* tree_min(node* root)
{
    node* u = root;
    while (u->left != NULL) {
        u = u->left;
    }
    return u;
}

node* destroy_tree(node* root)
{
    if (root->left)
        destroy_tree(root->left);
    if (root->right)
        destroy_tree(root->right);
    free(root);
}


/* Существует три основных случая для удаления вершины (u) из дерева:
1) Когда вершина - лист, т.е. не имеет детей. Тогда достаточно удалить ссылку на данную вершину у вершины-родителя и саму вершину из памяти (при помощи команды free()).
Когда вершина внутренняя и имеет: 2) одного потомка. В этом случае вместо ссылки на данную вершину у родителя помещаем ссылку на потомка данной вершины, а саму вершину удаляем.
3) двух потомков. Для его разрешения находим минимальную вершину v правого поддерева и заменяем ей удаляемую u, после чего удаляем ссылку на v и освобождаем память. Также можно использовать максимальную вершину из левого поддерева. */

node* delete(node* root, int key)
{
    node* u = NULL, * u_parent = NULL;
    u = search_node_by_key(root, key);
    if (u == NULL) {
        return u;
    }
    // если u - корень
    else if (u->parent == NULL) {
        destroy_tree(root);
        root = NULL;
    }
    else if ((u->left == NULL) && (u->right == NULL))
        // если u - лист
    {
        u_parent = u->parent;
        if (u == u_parent->right)
            u_parent->right = NULL;
        else
            u_parent->left = NULL;
        free(u);
    }
    //Можно ли эти два случая объединить в 1?
    else if ((u->left == NULL) && (u->right != NULL))
        // если u имеет правого сына
    {
        u_parent = u->parent;
        if (u == u_parent->right)
            u_parent->right = u->right;
        else
            u_parent->left = u->right;
        u->right->parent = u_parent;
        free(u);
    }
    else if ((u->left != NULL) && (u->right == NULL))
        // если u им. левого сына
    {
        u_parent = u->parent;
        if (u == u_parent->right)
            u_parent->right = u->left;
        else
            u_parent->left = u->left;
        u->left->parent = u_parent;
        free(u);
    }
    else if ((u->left != NULL) && (u->right != NULL))
        // u им. двух потомков
    {
        node* v = tree_min(u->right);
        u -> key = v -> key;
        //node* v_right = v->right;
        //node* v_parent = v->parent;

        // удаляем ссылку на потомка из правого поддерева, который заменил удаляемую вершину
        if (u->right->left == NULL && u->right->right == NULL) // если он был единственный в правом поддереве от удаляемой вершины
            u->right = NULL;

        else { // иначе
            if (v == v->parent->right)
                v->parent->right = v->right;
            else
                v->parent->left = v->right;
            if (v->right)
                v->right->parent = v->parent;

        }
        free(v);
    }
    return root;
}

// очищает ввод для scanf
void my_flush(void)
{
    int c;
    do {
        c = getchar();
    } while (c != EOF && c != '\n');
}

int main(int argc, char const* argv[])
{
    node* root;
    int key, n = 0, flag = 0;
    char answer[20];

    printf("\n   Для получения помощи в использовании программы напишите 'help' или 'h'.\n");
    while(1)
    {
        printf("\n   Выберите действие, которое нужно выполнить с деревом:\n\n >> ");
        scanf("%s", answer);

        if (!strcmp(answer, "quit")) {
            printf("Программа завершена.");
            break;
        } else if (!strcmp(answer, "show")) {
            if (!root)
                printf("\n   Дерево пусто.\n");
            else {
                printf("\n");
                show_tree(root, 0);
                printf("\n");
            }
        } else if (!strcmp(answer, "add")) {
            do {
                printf("\n   Введите количество узлов:\n >> ");
                flag = scanf("%d", &n);
                my_flush();
                if (flag != 1)
                    printf("\n   Введите натуральное число.");
            } while (flag != 1 || n <= 0);
            
            printf("\n   Введите значения узлов:\n");
            for (int i = 0; i < n; i++) {
                do {
                    printf(" >> ");
                    flag = scanf("%d", &key);
                    my_flush();
                    if (flag != 1)
                        printf("\n   Значение не является целочисленным.\n");
                } while (flag != 1);

                if (!root) // т.е. если дерево пустое
                    root = create(root, key);
                else
                    root = add(root, key);
                printf("\n   Узел успешно добавлен.\n");
            }
        } else if (!strcmp(answer, "delete") || !strcmp(answer, "del")) {
            do {
                printf("\n   Введите значение узла, который нужно удалить:\n\n >> ");
                flag = scanf("%d", &key);
                my_flush();
                if (flag != 1)
                    printf("\n   Значение не является целочисленным.");
            } while (flag != 1);
            if (!root)
                printf("\n   Данной вершины нет в дереве.\n");
            else {
                root = delete(root, key);
                printf("\n   Узел успешно удален.\n");
            }
        } else if (!strcmp(answer, "isB") || !strcmp(answer, "isb")) {
            if (!root) {
                printf("\n   Дерево пусто.\n");
                continue;
            }
            flag = is_Btree(root);
            if (flag)
                printf("\n   Данное дерево является B-деревом.\n");
            else
                printf("\n   Данное дерево не является B-деревом.\n");
        }
        else if (!strcmp(answer, "help") || !strcmp(answer, "h")) {
            printf("\n   Выберите действие, которое нужно выполнить с деревом:\n\n\t-Чтобы добавить один или несколько узлов к дереву, введите 'add'\n\t-Чтобы удалить узел дерева, введите 'delete' или 'del'\n\t-Чтобы вывести содержимое дерева, введите 'show'\n\t-Чтобы проверить, является ли введенное дерево B-деревом - введите 'isB' ('isb')\n\t-Чтобы закончить работу программы, введите 'quit'\n\n >> ");
        } else {
            printf("\n\nТакой команды не существует, воспользуйтесь командами 'help' или 'h'. \n\n");
        }

    }

    return 0;
}