#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>

using namespace std;

struct AVLTree
{
	size_t height;
	size_t count;
	char* stroka;
	AVLTree* left;
	AVLTree* right;
	AVLTree(char* k)
	{
		stroka = new char[strlen(k)];
		strcpy(stroka, k);
		count = 1;
		left = right = NULL;
		height = 1;
	};
}*Tree;

size_t Height(AVLTree* tree)
{
	return (tree != NULL ? tree->height : 0);
}

int hDiff(AVLTree* tree)
{
	return (Height(tree->right) - Height(tree->left));
}

void FixHeight(AVLTree* tree)
{
	size_t hl = Height(tree->left);
	size_t hr = Height(tree->right);
	tree->height = (hl > hr ? hl : hr) + 1;
}

AVLTree* LeftRotate(AVLTree* tree)
{
	AVLTree* p = tree->left;
	tree->left = p->right;
	p->right = tree;
	FixHeight(tree);
	FixHeight(p);
	return p;
}

AVLTree* RightRotate(AVLTree* tree)
{
	AVLTree* p = tree->right;
	tree->right = p->left;
	p->left = tree;
	FixHeight(tree);
	FixHeight(p);
	return p;
}

AVLTree* Balance(AVLTree* tree)
{
	FixHeight(tree);
	if (hDiff(tree) == 2)
	{
		if (hDiff(tree->right) < 0)
			tree->right = LeftRotate(tree->right);
		return RightRotate(tree);
	}
	if (hDiff(tree) == -2)
	{
		if (hDiff(tree->left) > 0)
			tree->left = RightRotate(tree->left);
		return LeftRotate(tree);
	}
	return tree;
}

AVLTree* Insert(AVLTree* root, char* k)
{
	if (root == NULL)
		return new AVLTree(k);
	if (strcmp(k, root->stroka) == 0)
	{
		root->count++;
		return root;
	}
	if (strcmp(k, root->stroka) < 0)
		root->left = Insert(root->left, k);
	else if (strcmp(k, root->stroka) > 0)
		root->right = Insert(root->right, k);
	return Balance(root);
}

void treeprint(AVLTree* tree)
{
	if (tree != NULL) 
	{
		treeprint(tree->left);
		printf("%s - %d time(s)\n", tree->stroka, tree->count);
		treeprint(tree->right);
	}
}

void Calculate()
{
	fstream code_text("code_text.txt", ios::in);
	if (!code_text.is_open())
	{
		cout << "Couldn't open the file" << endl;
		return;
	}
	while (!code_text.eof())
	{
		for (int i = 0; (code_text.get() != '\"') && (!code_text.eof()); i++);
		if (!code_text.eof())
		{
			char t[256];
			code_text.seekg(-3, ios::cur);
			char c = code_text.get();
			code_text.seekg(2, ios::cur);
			code_text.getline(t, 255, '\"');
			if (t[0] == '\'' && c == '\'')
				continue;
			Tree = Insert(Tree, t);
			
		}
	}
	treeprint(Tree);
}

int main()
{
	Calculate();
	return 0;
}