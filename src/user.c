#include"define.h"

typedef struct DIRECTORY_NODE
{
    char name[7];
    int index;
    int children[30];
    int parent;
    int dir_count;
    int child_count;
    int hash;
}dir_node;

dir_node dir_node_pool[NODE_POOL_SIZE];
int      dir_node_pool_count;

static bool once;

void mem_copy(char dst[], char src[])
{
    int i = 0;
    while(src[i] != '\0')
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
}

int mem_compare(char a[], char b[])
{
    int i = 0;
    while((a[i] != '\0') && (b[i] != '\0'))
    {
        if(a[i] !=b [i])    return a[i]-b[i];
        i++;
    }

    return a[i]-b[i];
}

int hash_fun(char name[])
{
    int h = 5381;
    int c;

    while(c = *name++)
    {
        h = (((h<<5)+h) + c) % PRIME_NUMBER;
    }

    return (h % PRIME_NUMBER);
}

int find_index(dir_node *temp, int h, char name[])
{
    int c;
    for(c = 0; c<temp->child_count; c++)
    {
        if(dir_node_pool[temp->children[c]].hash == h)
        {
            if(mem_compare(dir_node_pool[temp->children[c]].name,name) == 0)
            {
                return c;
            }
        }
    }
}

dir_node* find_desired_node(char path[])
{
    int i = 0;
    int h = 5381;
    int c = 0;
    int j = 0;
    char name[7];

    dir_node* temp = &dir_node_pool[0];
    
    if(path[i] == '/')   i++;

    if(path[i] == '\0')  return &dir_node_pool[0];

    while(path[i] != '\0')
    {
        if(path[i] == '/')
        {
            name[j] = '\0';
            h = (h%PRIME_NUMBER);

            int count = find_index(temp,h,name);
            temp = &dir_node_pool[temp->children[count]];

            h= 5381;
            c=0;
            j=0;
            i++;
            continue;
        }

        name[j] = path[i];
        c = name[j];
        h = (((h<<5)+h) + c) % PRIME_NUMBER;
        j++;
        i++;
    }

    if(temp->index == dir_node_pool[0].index)
    {
        return 0;
    }
    else   
    {
        return temp;
    }
}

void delete_child_from_parent(int parent, char name[])
{
    int h = hash_fun(name);

    int c,x;
    c = find_index(&dir_node_pool[parent],h,name);

    for(x=c; x<dir_node_pool[parent].child_count-1; x++)
    {
        dir_node_pool[parent].children[x] =dir_node_pool[parent].children[x+1];
    }

    dir_node_pool[parent].child_count--;
}

void increase_count(int dest_index, int count)
{
    while(dest_index!=-1)
    {
        dir_node_pool[dest_index].dir_count += count;
        dest_index = dir_node_pool[dest_index].parent;
    }
}

void traverse_children(dir_node *src, dir_node *dst)
{
    if(src == NULL) return;

    dir_node *new_dir = &dir_node_pool[dir_node_pool_count];

    mem_copy(new_dir->name,src->name);

    new_dir->hash = src->hash;
    new_dir->parent = src->parent;

    dst->children[dst->child_count] = dir_node_pool_count;

    dst->child_count++;

    increase_count(dst->index,1);

    dir_node_pool_count++;

    int c;
    for(c = 0; c<src->child_count;c++)
    {
        traverse_children(&dir_node_pool[src->children[c]], new_dir);
    }
}

void init(int n)
{    
    int i,j;
    if(once==false)
    {
        for(i=0;i<NODE_POOL_SIZE;i++)
        {
            dir_node_pool[i].index = i;
            dir_node_pool[i].child_count = 0;
            for(j=0;j<30;j++)
            {
                dir_node_pool[i].children[j] = -1;
            }

            dir_node_pool[i].name[0] = '\0';
            dir_node_pool[i].dir_count = 0;
            dir_node_pool[i].parent = -1;
            dir_node_pool[i].hash = 0;
        }
        once= true;
    }
    else
    {
        for(i=0;i<n;i++)
        {
            dir_node_pool[i].index = i;
            dir_node_pool[i].child_count = 0;
            for(j=0;j<30;j++)
            {
                dir_node_pool[i].children[j] = -1;
            }

            dir_node_pool[i].name[0] = '\0';
            dir_node_pool[i].dir_count = 0;
            dir_node_pool[i].parent = -1;
            dir_node_pool[i].hash = 0;
        }
    }

    dir_node_pool_count = 0;
    dir_node_pool[0].name[0] = '/';
    dir_node_pool[0].name[1] = '\0';

    dir_node_pool_count++;
}

void cmd_mkdir(char path[PATH_MAX_LEN+1], char name[NAME_MAX_LEN+1])
{
    if(path[0]=='\0' || name[0]=='\0')  return;

    dir_node *parent = find_desired_node(path);

    if(parent == NULL)  return;

    dir_node *new_dir = &dir_node_pool[dir_node_pool_count];

    int h = 5381;
    int c = 0;
    int x = 0;

    while(name[x]!='\0')
    {
        c = name[x];
        h = (((h<<5)+h) + c) % PRIME_NUMBER;
        new_dir->name[x] = name[x];
        x++;
    }

    h = (h%PRIME_NUMBER);

    new_dir->name[x] = '\0';
    new_dir->hash = h;

    new_dir->parent = parent->index;

    parent->children[parent->child_count] = dir_node_pool_count;
    parent->child_count++;

    increase_count(parent->index,1);

    dir_node_pool_count++;
}

void cmd_rm(char path[PATH_MAX_LEN+1])
{
    if(path[0] == '\0') return;

    int removed = 0;

    dir_node *temp = find_desired_node(path);

    if(temp!=0)
    {
        removed = temp->dir_count+1;

        increase_count(temp->parent, -removed);

        delete_child_from_parent(temp->parent, temp->name);
    }
}

void cmd_cp(char src_path[PATH_MAX_LEN+1], char dst_path[PATH_MAX_LEN+1])
{
    if(src_path[0] == '\0' || dst_path[0] == '\0')  return;

    dir_node *src = find_desired_node(src_path);
    if(src==NULL)   return;

    dir_node *dst = find_desired_node(dst_path);
    if(dst==NULL)   return;

    traverse_children(src,dst);
}

void cmd_mv(char src_path[PATH_MAX_LEN+1], char dst_path[PATH_MAX_LEN+1])
{
    if(src_path[0] == '\0' || dst_path[0] == '\0')  return;

    dir_node *src = find_desired_node(src_path);
    if(src==NULL)   return;

    dir_node *dst = find_desired_node(dst_path);
    if(dst==NULL)   return;

    int removed = src->dir_count+1;
    
    increase_count(src->parent, -removed);

    delete_child_from_parent(src->parent,src->name);

    increase_count(dst->index, removed);

    int cc= dir_node_pool[dst->index].child_count;

    dir_node_pool[dst->index].children[cc] = src->index;
    dir_node_pool[dst->index].child_count++;

    dir_node_pool[src->index].parent = dst->index;
}

int  cmd_find(char path[PATH_MAX_LEN+1])
{
    dir_node *temp = find_desired_node(path);

    if(temp ==NULL) return 0;

    return temp->dir_count;
}