/**
 * @file FibonacciHeap.h
 * @author Utkarsh
 * @brief Header file for Heap
 * @version 0.1
 * @date 2019-10-02
 *
 * @copyright Copyright (c) 2019
 *
 */

#pragma once
#include <iostream>
#include <list>
#include <memory>
#include <unordered_map>
#include <vector>

using namespace std;

/**
 * @brief Node for graph
 *
 * @tparam T Type of data
 */
template <class T>
class Node
{
public:
    T data;
    list<unique_ptr<Node<T>>> child;

    Node(T d) : data(d), child(list<unique_ptr<Node<T>>>()) {}

    /**
 * @brief Get the Rank of Node
 *
 * @return int
 */
    int getRank()
    {
        return child.size();
    }
};

/**
 * @brief Heap class
 *
 * @tparam T Type of data
 */
template <class T>
class Heap
{
    using iterator = typename list<unique_ptr<Node<T>>>::iterator;

public:
    list<unique_ptr<Node<T>>> nodes;
    iterator min;

    Heap() : min(nodes.end()) {}

    /**
 * @brief Insert data to heap
 *
 * @param data Data
 * @return iterator Result
 */
    iterator insert(T data)
    {
        if (empty())
        {
            min = nodes.insert(nodes.end(), make_unique<Node<T>>(data));
            return min;
        }
        if (data < (*min)->data)
        {
            min = nodes.insert(nodes.end(), make_unique<Node<T>>(data));
            return min;
        }
        else
        {
            return nodes.insert(nodes.end(), make_unique<Node<T>>(data));
        }
    }

    /**
 * @brief Checks if heap is empty;
 *
 * @return true
 * @return false
 */
    bool empty()
    {
        return nodes.empty();
    }
    /**
 * @brief Extracts the min element and rearranges
 *
 * @return optional<T>
 */
    optional<T> extract()
    {
        if (nodes.empty())
            return {};
        T result = (*min)->data;
        nodes.merge((*min)->child);
        nodes.erase(min);

        min = findMinimum();
        combine();
        return result;
    }

    iterator findMinimum()
    {
        if (empty())
            return nodes.end();
        iterator result = nodes.begin();
        T data = (*result)->data;
        for (iterator iter = nodes.begin(); iter != nodes.end(); iter++)
        {
            if ((*iter)->data < data)
            {
                data = (*iter)->data;
                result = iter;
            }
        }
        return result;
    }

    unique_ptr<Node<T>> &&merge(unique_ptr<Node<T>> &&a, unique_ptr<Node<T>> &&b)
    {
        if (a->data < b->data)
        {
            a->child.push_back(move(b));
            return move(a);
        }
        else
        {
            b->child.push_back(move(a));
            return move(b);
        }
    }

    void recursivePlace(unordered_map<int, unique_ptr<Node<T>>> &map, unique_ptr<Node<T>> &&tree)
    {
        int rank = tree->getRank();
        if (map.find(rank) != map.end())
        {
            unique_ptr<Node<T>> other = move(map[rank]);
            map.erase(rank);
            recursivePlace(map, move(merge(move(tree), move(other))));
        }
        else
        {
            map[rank] = move(tree);
        }
    }

    void combine()
    {
        int mapSize = nodes.size();
        unordered_map<int, unique_ptr<Node<T>>> map;
        for (auto i = nodes.begin(); i != nodes.end(); i++)
        {
            recursivePlace(map, move(*i));
        }
        nodes.clear();
        for (auto &element : map)
        {
            if (element.second)
            {
                nodes.push_back(move(element.second));
            }
        }
        min = findMinimum();
    }
};