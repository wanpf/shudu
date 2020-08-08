#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


int shudu[9][9];
unsigned int mix = 503010;
unsigned int seed = 0;

int SIDE = 9 + 1;

unsigned int get_seed()
{
	mix++;
	if (seed == 0) {
		seed = time(NULL) + mix;		
	}	
	seed = (seed * 3 + mix * 13) ^ 2865539980; // 135797531;
	return seed;
}


void init()
{
	int i = 0;
	int j = 0;

	for (i = 1; i < SIDE; i++) {
		for (j = 1; j < SIDE; j++) {
			shudu[i - 1][j - 1] = (i + j - 2) % (SIDE - 1) + 1;
		}
	}
}

void transform_x()
{
	int i, t;
	int a = get_seed() % (SIDE - 1);
	int b = get_seed() % (SIDE - 1);

	if (b == a) {
		b = (b + 1) % (SIDE - 1);
	}	
	for (i = 0; i < SIDE - 1; i++) {
		t = shudu[a][i];
		shudu[a][i] = shudu[b][i];
		shudu[b][i] = t;
	}
}

void transform_y()
{
	int i, t;
	int a = get_seed() % (SIDE - 1);
	int b = get_seed() % (SIDE - 1);

	if (b == a) {
		b = (b + 1) % (SIDE - 1);
	}	
	for (i = 0; i < SIDE - 1; i++) {
		t = shudu[i][a];
		shudu[i][a] = shudu[i][b];
		shudu[i][b] = t;
	}
}

int no = 0;

void print(FILE *fp)
{
	int i = 0;
	int j = 0;

	fprintf(fp, "================ %d ================\n\n", ++no);

	for (i = 1; i < SIDE; i++) {
		for (j = 1; j < SIDE; j++) {
			printf("%d ", shudu[i - 1][j - 1]);
			fprintf(fp, "%d ", shudu[i - 1][j - 1]);
		}
		printf("\n");
		fprintf(fp, "\n\n");
	}
}

char* get()
{
	int i = 0;
	int j = 0;

	int p = 0;
	char *s = (char*)malloc(82);
	s[81] = '\0';


	for (i = 1; i < SIDE; i++) {
		for (j = 1; j < SIDE; j++) {
			s[p++] = shudu[i - 1][j - 1] + '0';
		}		
	}

	printf("%s\n", s);
	return s;
}


void transform()
{
	int i;

	for (i = 0; i < 2390; i++) {
		transform_x();
		transform_y();
	}
	for (i = 0; i < 4321; i++) {		
		transform_y();
		transform_x();
	}

}

struct bin_tree {
char *data;
struct bin_tree * right, * left;
};
typedef struct bin_tree node;

void insert(node ** tree, char *val)
{
	int cmp = 0;
    node *temp = NULL;
    if(!(*tree))
    {
        temp = (node *)malloc(sizeof(node));
        temp->left = temp->right = NULL;
        temp->data = val;
        *tree = temp;
        return;
    }

	cmp = strcmp(val, (*tree)->data);
    if(cmp < 0)
    {
        insert(&(*tree)->left, val);
    }
    else if(cmp > 0)
    {
        insert(&(*tree)->right, val);
    }

}

void print_preorder(node * tree)
{
    if (tree)
    {
        printf("%s\n",tree->data);
        print_preorder(tree->left);
        print_preorder(tree->right);
    }

}

void print_inorder(node * tree)
{
    if (tree)
    {
        print_inorder(tree->left);
        printf("%s\n",tree->data);
        print_inorder(tree->right);
    }
}

void print_postorder(node * tree)
{
    if (tree)
    {
        print_postorder(tree->left);
        print_postorder(tree->right);
        printf("%s\n",tree->data);
    }
}

void deltree(node * tree)
{
    if (tree)
    {
        deltree(tree->left);
        deltree(tree->right);
        free(tree);
    }
}

node* search(node ** tree, int val)
{
	int cmp = 0;

    if(!(*tree))
    {
        return NULL;
    }

	cmp = strcmp(val, (*tree)->data);
    if(cmp < 0)
    {
        search(&((*tree)->left), val);
    }
    else if(cmp > 0)
    {
        search(&((*tree)->right), val);
    }
    else if(cmp == 0)
    {
        return *tree;
    }
	return NULL;
}

void main()
{
	int i;
	char *s;

	char *e = NULL;

	FILE *fp = fopen("d:\\shudu.txt", "w");

    node *tmp = NULL;
	node *root = NULL;

	init();

	for (i = 0; i < 1500; i++) {
		transform();
		s = get();

		if (e == NULL) {
			e = s;
		}

		tmp = search(&root, s);

		if (tmp != NULL) {
			printf("conflict =======================================\n");
			return ;
		}

		insert(&root, s);

		// print_preorder(root);

		print(fp);

	}

	fclose(fp);

	tmp = search(&root, e);
	if (tmp != NULL) {
			printf("conflict ............\n");
			return ;
		}


	
}