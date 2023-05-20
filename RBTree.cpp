#include "RBTree.h"

RBTree::RBTree() :root(NULL) 
{
	root = nullptr;
}

RBTree::~RBTree() 
{
	destroy(root);
}

void RBTree::destroy(RBTNode*& node)
{
	if (node == NULL)
		return;
	destroy(node->left);
	destroy(node->right);
	delete node;
	node = nullptr;
}

RBTree::RBTree(const RBTree& other)
{
	root = copy(other.root);
}

RBTNode* RBTree::copy(RBTNode* node)
{
	if (node == nullptr)
		return nullptr;
	else
		return new RBTNode(node->key, node->color, nullptr, copy(node->left), copy(node->right));
}

RBTree& RBTree::operator=(const RBTree& other)
{
	if (this != &other)
	{
		destroy(root);
		root = copy(other.root);
	}
	return *this;
}

RBTree::RBTree(RBTree&& other) noexcept
{
	root = other.root;
	other.root = nullptr;
}

RBTree& RBTree::operator=(RBTree&& other) noexcept
{
	if (this != &other)
	{
		destroy(root);
		root = other.root;
		other.root = nullptr;
	}
	return *this;
}

void RBTree::insert(const std::string& key, const std::string& value)
{
	RBTNode* existingNode = search(key);
	if (existingNode && existingNode->translationList.search(value))
		throw std::runtime_error("The entered translation '" + value + "' of the word '" + key + "' is already in the dictionary.\n");
	else if (existingNode != nullptr && !existingNode->translationList.search(value))
		existingNode->translationList.insert(value);
	else
	{
		RBTNode* newNode = new RBTNode(key, COLOR_RED, NULL, NULL, NULL);
		newNode->translationList.insert(value);
		insert(root, newNode);
	}
};

void RBTree::insert(RBTNode*& root, RBTNode* newNode)
{
	RBTNode* currentNode = root;
	RBTNode* parentNode = NULL;

	while (currentNode != NULL)
	{
		parentNode = currentNode;
		if (newNode->key > currentNode->key)
			currentNode = currentNode->right;
		else
			currentNode = currentNode->left;
	}

	newNode->parent = parentNode;

	if (parentNode != NULL)
	{
		if (newNode->key > parentNode->key)
			parentNode->right = newNode;
		else
			parentNode->left = newNode;
	}
	else
		root = newNode;  

	newNode->color = COLOR_RED;

	insertFixUp(root, newNode);
};


void RBTree::insertFixUp(RBTNode*& root, RBTNode* node)
{
	RBTNode* parent = node->parent;
	while (node != RBTree::root && parent->color == COLOR_RED)
	{
		RBTNode* gparent = parent->parent;
		if (gparent->left == parent)
		{
			RBTNode* uncle = gparent->right;
			if (uncle != NULL && uncle->color == COLOR_RED)
			{
				parent->color = COLOR_BLACK;
				uncle->color = COLOR_BLACK;
				gparent->color = COLOR_RED;
				node = gparent;
				parent = node->parent;
			}
			else
			{
				if (parent->right == node)
				{
					leftRotate(root, parent);
					std::swap(node, parent);
				}
				rightRotate(root, gparent);
				gparent->color = COLOR_RED;
				parent->color = COLOR_BLACK;
				break;
			}
		}
		else
		{
			RBTNode* uncle = gparent->left;
			if (uncle != NULL && uncle->color == COLOR_RED)
			{
				gparent->color = COLOR_RED;
				parent->color = COLOR_BLACK;
				uncle->color = COLOR_BLACK;

				node = gparent;
				parent = node->parent;
			}
			else
			{
				if (parent->left == node)
				{
					rightRotate(root, parent);
					std::swap(parent, node);
				}
				leftRotate(root, gparent);
				parent->color = COLOR_BLACK;
				gparent->color = COLOR_RED;
				break;
			}
		}
	}
	root->color = COLOR_BLACK;
}

void RBTree::deleteTranslation(const std::string& key, const std::string& value)
{
	RBTNode* existingNode = search(key);
	if (existingNode != nullptr && existingNode->translationList.search(value))
		deleteTranslationFromNode(existingNode, value);
	else
		throw std::runtime_error("Among the meanings of the word '" + key + "' there is no searchable.\n");
}

void RBTree::deleteTranslationFromNode(RBTNode*& node, const std::string& value)
{
	node->translationList.deleteNode(value);
}

void RBTree::remove(const std::string& key)
{
	RBTNode* deleteNode = search(root, key);

	if (deleteNode != NULL)
		remove(root, deleteNode);
	else
		throw std::runtime_error("There isn't word '" + key + "' in the dictionary.");
}

void RBTree::remove(RBTNode*& root, RBTNode* node)
{
	if (!node) return;

	RBTNode* child, * parent;
	Color color;

	if (node->left != NULL && node->right != NULL)
	{
		RBTNode* replace = node->right;
		while (replace->left != NULL)
		{
			replace = replace->left;
		}

		if (node->parent != NULL)
		{
			if (node->parent->left == node)
				node->parent->left = replace;
			else
				node->parent->right = replace;
		}
		else
			root = replace;

		child = replace->right;
		parent = replace->parent;
		color = replace->color;

		if (parent == node)
			parent = replace;
		else
		{
			if (child != NULL)
				child->parent = parent;
			parent->left = child;

			replace->right = node->right;
			node->right->parent = replace;
		}

		replace->parent = node->parent;
		replace->color = node->color;
		replace->left = node->left;
		node->left->parent = replace;

		delete node;

		if (color == COLOR_BLACK)
			removeFixUp(root, child, parent);

		return;
	}

	if (node->left != NULL)
		child = node->left;
	else
		child = node->right;

	parent = node->parent;
	color = node->color;

	if (child != NULL)
		child->parent = parent;

	if (parent != NULL)
	{
		if (parent->left == node)
			parent->left = child;
		else
			parent->right = child;
	}
	else
		root = child;

	delete node;

	if (color == COLOR_BLACK)
		removeFixUp(root, child, parent);
}

void RBTree::removeFixUp(RBTNode*& root, RBTNode* node, RBTNode* parent)
{
	RBTNode* otherNode;
	while ((!node || node->color == COLOR_BLACK) && node != root)
	{
		if (parent->left == node)
		{
			otherNode = parent->right;
			if (otherNode && otherNode->color == COLOR_RED)
			{
				otherNode->color = COLOR_BLACK;
				parent->color = COLOR_RED;
				leftRotate(root, parent);
				otherNode = parent->right;
			}
			if (!otherNode || !(otherNode->right) || otherNode->right->color == COLOR_BLACK)
			{
				if (otherNode && otherNode->left)
					otherNode->left->color = COLOR_BLACK;
				if (otherNode) {
					otherNode->color = COLOR_RED;
					rightRotate(root, otherNode);
					otherNode = parent->right;
				}
			}
			if (otherNode)
			{
				otherNode->color = parent->color;
				if (otherNode->right)
					otherNode->right->color = COLOR_BLACK;
			}
			parent->color = COLOR_BLACK;
			leftRotate(root, parent);
			node = root;
			break;
		}
		else
		{
			otherNode = parent->left;
			if (otherNode && otherNode->color == COLOR_RED)
			{
				otherNode->color = COLOR_BLACK;
				parent->color = COLOR_RED;
				rightRotate(root, parent);
				otherNode = parent->left;
			}
			if (!otherNode || (!otherNode->left || otherNode->left->color == COLOR_BLACK) && (!otherNode->right || otherNode->right->color == COLOR_BLACK))
			{
				if (otherNode) otherNode->color = COLOR_RED;
				node = parent;
				parent = node ? node->parent : nullptr;
			}
			else
			{
				if (!otherNode || !(otherNode->left) || otherNode->left->color == COLOR_BLACK)
				{
					if (otherNode && otherNode->right)
						otherNode->right->color = COLOR_BLACK;
					if (otherNode) {
						otherNode->color = COLOR_RED;
						leftRotate(root, otherNode);
						otherNode = parent->left;
					}
				}
				if (otherNode) 
				{
					otherNode->color = parent->color;
					if (otherNode->left)
						otherNode->left->color = COLOR_BLACK;
				}
				parent->color = COLOR_BLACK;
				rightRotate(root, parent);
				node = root;
				break;
			}
		}
	}
	if (node)
		node->color = COLOR_BLACK;
}


RBTNode* RBTree::search(const std::string& key)
{
	return search(root, key);
}

RBTNode* RBTree::search(RBTNode* node, const std::string& key) const
{
	if (node == NULL || node->key == key)
		return node;
	else
		if (key > node->key)
			return search(node->right, key);
		else
			return search(node->left, key);
}

void RBTree::printOneKey(const std::string& key)
{
	RBTNode* printNode = search(key);
	if (printNode) printOneKeyFromNode(printNode);
	else
		throw std::runtime_error("There isn't the word '" + key + "' in the dictionary.\n");
}

void RBTree::printOneKeyFromNode(RBTNode* printNode)
{
	if (!printNode)  throw std::runtime_error("The word '" + printNode->key + "' is missing in the dictionary.\n");
	else
	{
		std::cout << "Word: " << printNode->key << '\t' << "Values: ";
		printNode->translationList.outAll();
	}
}

void RBTree::inOrder()
{
	if (root == NULL)
		std::cout << "Dictionary is empty.\n";
	else
	{
		std::cout << "\n=====================DICTIONARY=====================\n\n";
		inOrder(root);
		std::cout << "\n====================================================\n\n";
	}
};

void RBTree::inOrder(RBTNode* node) 
{
	if (node != NULL) {
		inOrder(node->left);
		printOneKeyFromNode(node);
		inOrder(node->right);
	}
}

void RBTree::leftRotate(RBTNode*& root, RBTNode* node) 
{
	if (!node || !node->right)
		return;

	RBTNode* rightNode = node->right;
	node->right = rightNode->left;
	if (rightNode->left != NULL)
		rightNode->left->parent = node;

	rightNode->parent = node->parent;
	if (node->parent == NULL)
		root = rightNode;
	else
	{
		if (node == node->parent->left)
			node->parent->left = rightNode;
		else
			node->parent->right = rightNode;
	}
	rightNode->left = node;
	node->parent = rightNode;
};

void RBTree::rightRotate(RBTNode*& root, RBTNode* node) 
{
	if (!node || !node->left)
		return;

	RBTNode* leftNode = node->left;
	node->left = leftNode->right;
	if (leftNode->right != NULL)
		leftNode->right->parent = node;

	leftNode->parent = node->parent;
	if (node->parent == NULL)
		root = leftNode;
	else 
	{
		if (node == node->parent->right)
			node->parent->right = leftNode;
		else
			node->parent->left = leftNode;
	}
	leftNode->right = node;
	node->parent = leftNode;
}