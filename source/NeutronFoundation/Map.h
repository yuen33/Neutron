#pragma once

#include "Stack.h"

namespace Neutron
{
	namespace Container
	{
		template<typename Key, typename Value, typename CountType = int>
		class Map
		{
		public:
			class Iterator;

		private:
			class RBNode;

			enum : bool
			{
				RED = true,
				BLACK = false
			};

			class RBNode
			{
				friend class Map < Key, Value > ;
				friend class Map<Key, Value>::Iterator;

				RBNode*	parent;
				RBNode*	left;
				RBNode*	right;
				bool	color;
				Key		key;
				Value	value;

			public:
				RBNode(const Key& key_, const Value& value_, bool color_, RBNode* parent_)
					:key(key_)
					, value(value_)
					, color(color_)
					, parent(parent_)
					, left(0)
					, right(0)
				{
				}

				~RBNode()
				{
				}

				inline bool red() const { return color == RED; }
			};

			/***************************************************************
			* RBTree
			***************************************************************/

			RBNode*		root;
			CountType	count;

			static inline RBNode* getMin(RBNode* node)
			{
				while (node && node->left)
				{
					node = node->left;
				}
				return node;
			}

			static inline RBNode* getMax(RBNode* node)
			{
				while (node && node->right)
				{
					node = node->right;
				}
				return node;
			}

			static inline RBNode* next(RBNode* node)
			{
				if (node && node->right != 0)
				{
					node = getMin(node->right);
				}
				else
				{
					RBNode* p = node->parent;
					while (p && node == p->right) { node = p; p = p->parent; }
					if (p == 0 || node->right != p) node = p;
				}
				return node;
			}

			static inline RBNode* prev(RBNode* node)
			{
				if (node->left != 0)
				{
					node = getMax(node->left);
				}
				else
				{
					RBNode* p = node->parent;
					while (p && node == p->left) { node = p; p = p->parent; }
					if (p == 0 || node->left != p) node = p;
				}
			}

			inline RBNode* findNode(const Key& key)
			{
				RBNode* node = root;
				while (node)
				{
					if (key == node->key)
					{
						break;
					}
					else
					{
						node = (key < node->key) ? node->left : node->right;
					}
				}
				return node;
			}

			inline void flipColor(RBNode* node)
			{
				node->color = !node->color;
				node->left->color = !node->left->color;
				node->right->color = !node->right->color;
			}

			inline RBNode* rotateLeft(RBNode* node)
			{
				node->right->parent = node->parent;
				node->parent = node->right;
				if (node->right->left)
				{
					node->right->left->parent = node;
				}

				RBNode* x = node->right;
				node->right = x->left;
				x->left = node;
				x->color = x->left->color;
				x->left->color = RED;
				return x;
			}

			inline RBNode* rotateRight(RBNode* node)
			{
				node->left->parent = node->parent;
				node->parent = node->left;
				if (node->left->right)
				{
					node->left->right->parent = node;
				}

				RBNode* x = node->left;
				node->left = x->right;
				x->right = node;
				x->color = x->right->color;
				x->right->color = RED;
				return x;
			}

			inline RBNode* fixup(RBNode node)
			{
				if (node)
				{
					if (node->right && node->right->red())
					{
						node = rotateLeft(node);
					}

					if (node->left && node->left->red() && node->left->left && node->left->left->red())
					{
						node = rotateRight(node);
					}

					if (node->left && node->left->red() && node->right && node->right->red())
					{
						flipColor(node);
					}
				}

				return node;
			}

			inline RBNode* insertRecursive(RBNode* parent, RBNode* node, Key key, Value value)
			{
				if (!node)
				{
					++count;
					return new RBNode(key, value, RED, parent);
				}

				if (key == node->key)
				{
					node->value = value;
				}
				else if (key < node->key)
				{
					node->left = insertRecursive(node, node->left, key, value);
				}
				else
				{
					node->right = insertRecursive(node, node->right, key, value);
				}

				// 2 nodes to 3 nodes
				if (node->right && node->right->red())
				{
					node = rotateLeft(node);
				}

				// 3 nodes to 4 nodes
				if (node->left && node->left->red() && node->left->left && node->left->left->red())
				{
					node = rotateRight(node);
				}

				// split 4 nodes
				if (node->left && node->left->red() && node->right && node->right->red())
				{
					flipColor(node);
				}

				return node;
			}

			RBNode* moveRedRight(RBNode* node)
			{
				flipColor(node);
				if (node->left && node->left->left && node->left->left->red())
				{
					node = rotateRight(node);
					flipColor(node);
				}
				return node;
			}

			RBNode* moveRedLeft(RBNode* node)
			{
				flipColor(node);
				if (node->right && node->right->left && node->right->left->red())
				{
					node->right = rotateRight(node->right);
					node = rotateLeft(node);
					flipColor(node);
				}
				return node;
			}

			RBNode* deleteMinRecursive(RBNode* node)
			{
				if (node->left)
				{
					if (!node->left->red() && (!node->left->left || !node->left->left->red()))
					{
						node = moveRedLeft(node);
					}
					checkDelete(deleteMinRecursive(node->left), &node->left);
					return fixup(node);
				}
				return 0;
			}

			inline void checkDelete(RBNode* source, RBNode** dest)
			{
				if (source)
				{
					*dest = source;
				}
				else if (*dest)
				{
					delete *dest;
					*dest = 0;
					--count;
				}
			}

			RBNode* deleteRecursive(RBNode* node, const Key& key)
			{
				if (!node)
				{
					return 0;
				}

				if (key < node->key)
				{
					if (node->left && !node->left->red() && (!node->left->left || !node->left->left->red()))
					{
						node = moveRedLeft();
					}

					if (node->left)
					{
						checkDelete(deleteRecursive(node->left, key), &(h->left));
					}
				}
				else
				{
					if (node->left && node->left->red())
					{
						node = rotateRight(node);
					}

					if (node->right)
					{
						if (!node->right->red() && (!node->right->left || !node->right->left->red()))
						{
							node->moveRedRight(h);
						}
					}
					else
					{
						if (key == node->key)
						{
							return 0;
						}
					}

					if (key == node->key)
					{
						RBNode* minRight = getMin(node->right);
						if (minRight)
						{
							node->key = minRight->key;
							node->value = minRight->value;
						}

						checkDelete(deleteMinRecursive(node->right), &(node->right));
					}
					else
					{
						checkDelete(deleteRecursive(node->right, key), &(node->right));
					}
				}

				return fixup(node);
			}

		public:
			class Iterator
			{
				friend class Map < Key, Value > ;
				RBNode* node;

				Iterator(RBNode* node_)
					:node(node_)
				{
				}

			public:
				Iterator()
					:node(0)
				{
				}

				Iterator(const Iterator& other)
					:node(other.node)
				{
				}

				~Iterator()
				{
				}

				inline bool operator=(const Iterator& rhs) { node = rhs.node; return *this; }

				inline Iterator& operator++()
				{
					node = Map::next(node);
					return *this;
				}

				inline Iterator& operator--()
				{
					node = Map::prev(node);
					return *this;
				}

				inline Iterator operator++(int)
				{
					Iterator it = *this;
					node = Map::next(node);
					return it;
				}

				inline Iterator operator--(int)
				{
					Iterator it = *this;
					node = Map::prev(node);
					return it;
				}

				inline bool operator==(const Iterator& rhs) const { return node == rhs.node; }
				inline bool operator!=(const Iterator& rhs) const { return node != rhs.node; }
				inline bool null() const { return node == 0; }
				inline const Key& key() const { assert(node); return node->key; }
				inline Value& value() const { assert(node); return node->value; }

				// debug
				inline void print_path()
				{
					RBNode* n = node;
					while (n)
					{
						printf("%c ", n->value);
						n = n->parent;
					}
					printf("\n");
				}
				inline bool red() const { return node->red(); }
			};

			Map()
				:root(0)
				, count(0)
			{
			}

			virtual ~Map()
			{
				clear();
			}

			Value& operator[](const Key& key)
			{
				Iterator it = find(key);
				assert(!it.null());
				return it.value();
			}

			inline Iterator find(const Key& key) { return Iterator(findNode(key)); }
			inline Iterator begin() { return Iterator(getMin(root)); }
			inline Iterator back() { return Iterator(getMax(root)); }
			inline Iterator end() { return Iterator(0); }

			void add(const Key& key, const Value& value)
			{
				root = insertRecursive(0, root, key, value);
			}

			void remove(const Key& key)
			{
				checkDelete(deleteRecursive(root, key), &root);
				if (root)
				{
					root->color = BLACK;
				}
			}

			void remove(const Iterator& it)
			{
				if (!it.null())
				{
					remove(it.key());
				}
			}

			void clear()
			{
				Stack<RBNode*, CountType> stack;
				stack.reserve(count);
				for (RBNode* it = getMin(root); it; it = next(it))
				{
					stack.push(it);
				}

				count = 0;

				for (CountType i = 0; i < stack.getCount(); ++i)
				{
					delete stack[i];
				}
				stack.clear();

				root = 0;
			}

			inline CountType getCount() const { return count; }
			inline bool any() const { return count > 0; }
			inline bool empty() const { return count <= 0; }
		};
	}
}