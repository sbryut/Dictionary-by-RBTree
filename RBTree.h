#ifndef R_B_TREE_H
#define R_B_TREE_H

#include "TranslationList.h"

enum Color { COLOR_RED, COLOR_BLACK };

struct RBTNode
{
	std::string key;
	Color color;
	TranslationList translationList;
	RBTNode* left;
	RBTNode* right;
	RBTNode* parent;

	RBTNode(const std::string& k, Color c, RBTNode* p = nullptr, RBTNode* l = nullptr, RBTNode* r = nullptr) :
		key(k), color(c), parent(p), left(l), right(r) { };

	~RBTNode()
	{
		left = nullptr;
		right = nullptr;
		parent = nullptr;
	}

};

class RBTree
{
public:

	RBTree();
	~RBTree();
	RBTree(const RBTree& other);
	RBTree& operator=(const RBTree& other);
	RBTree(RBTree&& other) noexcept;
	RBTree& operator=(RBTree&& other) noexcept;
	
	void insert(const std::string& key, const std::string& value);  
	void deleteTranslation(const std::string& key, const std::string& value);
	void remove(const std::string& key);
	RBTNode* search(const std::string& key);
	void printOneKey(const std::string& key);   
	void inOrder();

private:

	void insert(RBTNode*& root, RBTNode* node);
	void insertFixUp(RBTNode*& root, RBTNode* node);
	void deleteTranslationFromNode(RBTNode*& node, const std::string& value);
	void remove(RBTNode*& root, RBTNode* node);
	void removeFixUp(RBTNode*& root, RBTNode* node, RBTNode* parent);
	RBTNode* search(RBTNode* node, const std::string& key) const;
	void printOneKeyFromNode(RBTNode* node);
	void inOrder(RBTNode* tree);
	void leftRotate(RBTNode*& root, RBTNode* x);
	void rightRotate(RBTNode*& root, RBTNode* y);

	void destroy(RBTNode*& node);
	RBTNode* copy(RBTNode* node);

	RBTNode* root;
};

#endif