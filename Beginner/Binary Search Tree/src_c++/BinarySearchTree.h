//
//  BinarySearchTree.h
//  Data Structures
//
//  Created by Jonathan Sullivan on 7/13/15.
//
// The MIT License (MIT)
//
// Copyright (c) 2015 Jonathan Sullivan
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef Data_Structures__BinarySearchTree
#define Data_Structures__BinarySearchTree

#include <cstdio>
#include <functional>


#pragma mark - Enumerations

enum class TraversalType
{
    InOrder,
    PreOrder,
    PostOrder
};

#pragma mark -


#pragma mark - Class Definition

template<class T>
class BinarySearchTree
{
    
    
#pragma mark - Structures
    
    struct Node
    {
        T key;
        
        Node * left = nullptr;
        Node * right = nullptr;
        Node * parent = nullptr;
        
        T minimum()
        {
            return (left ? left->minimum() : key);
        }
        
        T maximum()
        {
            return (right ? right->maximum() : key);
        }
        
        void insert(const T &aKey)
        {
            if (aKey < key)
            {
                if (left)
                {
                    left->insert(aKey);
                }
                else {
                    Node * child = new Node();
                    child->key = aKey;
                    child->parent = this;
                    
                    left = child;
                }
            }
            else {
                if (right)
                {
                    right->insert(aKey);
                }
                else {
                    Node * child = new Node();
                    child->key = aKey;
                    child->parent = this;
                    
                    right = child;
                }
            }
        }
        
        Node * search(const T &aKey)
        {
            if (aKey < key)
            {
                return (left ? left->search(aKey) : nullptr);
            }
            else if (aKey > key)
            {
                return (right ? right->search(aKey) : nullptr);
            }
            else {
                return this;
            }
        }
    };
    
#pragma mark -
    
    
#pragma mark - Private Member Variables
    
    Node * root = nullptr;
    
#pragma mark -
    
    
#pragma mark - Private Action Functions
    
    void removeAll(Node * node)
    {
        if (node == nullptr)
            return;
        
        removeAll(node->left);
        removeAll(node->right);
        
        if (node == root)
            root = nullptr;
        
        delete node;
    }
    
    void traverse(TraversalType traversalType, std::function<void(T key)> printFunctor, Node * node)
    {
        if (node == nullptr)
            return;
        
        if (traversalType == TraversalType::PreOrder)
            printFunctor(node->key);
        
        traverse(traversalType, printFunctor, node->left);
        
        if (traversalType == TraversalType::InOrder)
            printFunctor(node->key);
        
        traverse(traversalType, printFunctor, node->right);
        
        if (traversalType == TraversalType::PostOrder)
            printFunctor(node->key);
    }
    
#pragma mark -
    
    
public:

    
#pragma mark - Life Cycle Methods
    
    ~BinarySearchTree()
    {
        removeAll();
    }
    
#pragma mark -
    
    
#pragma mark - Public Helper Functions
    
    T minimum()
    {
        return root->minimum();
    }
    
    T maximum()
    {
        return root->maximum();
    }
    
#pragma mark -
    
    
#pragma mark - Public Actions Functions
    
    void insert(const T &key)
    {
        if (root == nullptr)
        {
            root = new Node();
            root->key = key;
        }
        else {
            root->insert(key);
        }
    }
    
    void remove(const T &key)
    {
        Node * node = search(key);
        
        if (node == nullptr)
            return;
        
        if (node->left != nullptr && node->right != nullptr)
        {
            T successorKey = node->right->minimum();
            remove(successorKey);
            
            node->key = successorKey;
            
            return;
        }
        else if (node->left == nullptr && node->right == nullptr)
        {
            if (node == root)
            {
                root = nullptr;
            }
            else {
                if (node == node->parent->left)
                    node->parent->left = nullptr;
                else
                    node->parent->right = nullptr;
            }
        }
        else {
            if (node == root)
            {
                if (node->left != nullptr)
                    root = node->left;
                else
                    root = node->right;
            }
            else {
                if (node == node->parent->left)
                {
                    if (node->left != nullptr)
                        node->parent->left = node->left;
                    else
                        node->parent->left = node->right;
                }
                else {
                    if (node->left != nullptr)
                        node->parent->right = node->left;
                    else
                        node->parent->right = node->right;
                }
            }
        }
        
        delete node;
    }
    
    Node * search(const T &key)
    {
        return root->search(key);
    }
    
    void traverse(TraversalType traversalType, std::function<void(T key)> printFunctor)
    {
        traverse(traversalType, printFunctor, root);
    }
    
    void removeAll()
    {
        removeAll(root);
    }
    
#pragma mark -
    
};

#pragma mark -


#endif /* defined(Data_Structures__BinarySearchTree) */
