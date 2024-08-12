#pragma once
#include <memory>
#include <iostream>
using namespace std;

static const double LOAD_INDEX = 0.75;

template <class T>
class HashMap
{
    class Node
    {
    public:
        shared_ptr<T> m_data;
        int m_id;
        unique_ptr<Node> m_next;

        Node(int id, shared_ptr<T> data) : m_data(data), m_id(id), m_next(nullptr) {}

        shared_ptr<T> data() const { return m_data; }
        int id() const { return m_id; }
        Node *next() const { return m_next.get(); }

        void setNext(unique_ptr<Node> next)
        {
            m_next = std::move(next);
        }
    };

private:
    unique_ptr<unique_ptr<Node>[]> m_hashArray;
    int m_size;
    double m_numberOfData;

public:
    HashMap() : m_size(1), m_numberOfData(0)
    {
        m_hashArray = unique_ptr<unique_ptr<Node>[]>(new unique_ptr<Node>[m_size]);
    }

    int hash(int key) const
    {
        return key % m_size;
    }

    int nextSize() const
    {
        return 2 * m_size;
    }

    void insert(shared_ptr<T> curr, int id)
    {
        if (m_numberOfData / m_size > LOAD_INDEX)
        {
            increase();
        }

        int index = hash(id);
        unique_ptr<Node> &list = m_hashArray[index];
        Node *it = list.get();

        while (it)
        {
            if (*(it->data()) == *curr)
            {
                return;
            }
            it = it->next();
        }

        auto newNode = unique_ptr<Node>(new Node(id, curr));
        newNode->setNext(std::move(list));
        m_hashArray[index] = std::move(newNode);
        m_numberOfData += 1;
    }

    void increase()
    {
        int newSize = nextSize();
        auto tempArray = unique_ptr<unique_ptr<Node>[]>(new unique_ptr<Node>[newSize]);

        for (int i = 0; i < m_size; ++i)
        {
            unique_ptr<Node> current = std::move(m_hashArray[i]);
            while (current)
            {
                int newIndex = current->id() % newSize;
                unique_ptr<Node> &list = tempArray[newIndex];

                unique_ptr<Node> nextNode = std::move(current->m_next);
                current->m_next = std::move(list);
                list = std::move(current);

                current = std::move(nextNode);
            }
        }

        m_hashArray = std::move(tempArray);
        m_size = newSize;
    }

    shared_ptr<T> find(int id) const
    {
        int index = hash(id);
        const unique_ptr<Node> &list = m_hashArray[index];
        if (!list)
        {
            return nullptr;
        }
        Node *current = list.get();
        while (current)
        {
            if (current->id() == id)
            {
                return current->data();
            }
            current = current->next();
        }
        return nullptr;
    }

    int getNumber() const
    {
        return m_numberOfData;
    }
};
