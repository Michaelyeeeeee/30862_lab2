#include "hash_list.h"

hash_list::hash_list()
{
    size = 0;
    head = nullptr;
    iter_ptr = nullptr;
}

/**-----------------------------------------------------------------------------------
 * START Part 1
 *------------------------------------------------------------------------------------*/

void hash_list::insert(int key, float value)
{
    if (!head)
    {
        node *newnode = new node;
        newnode->key = key;
        newnode->value = value;
        newnode->next = nullptr;
        head = newnode;
        size = 1;
        return;
    }
    node *curr = head;
    node *prev = head;
    while (curr)
    {
        if (curr->key == key)
        {
            curr->value = value;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    node *newnode = new node;
    newnode->key = key;
    newnode->value = value;
    newnode->next = nullptr;
    prev->next = newnode;
    size++;
}

std::optional<float> hash_list::get_value(int key) const
{
    node *curr = head;
    while (curr)
    {
        if (curr->key == key)
        {
            return curr->value;
        }
        curr = curr->next;
    }
    return std::nullopt;
}

bool hash_list::remove(int key)
{
    node *curr = head;
    node *prev = nullptr;
    while (curr)
    {
        if (curr->key == key)
        {
            if (prev)
            {
                prev->next = curr->next;
            }
            else
            {
                head = curr->next;
            }
            if (iter_ptr == curr)
            {
                iter_ptr = nullptr;
            }
            delete curr;
            size--;
            return true;
        }
        prev = curr;
        curr = curr->next;
    }
    return false;
}

size_t hash_list::get_size() const
{
    return size;
}

hash_list::~hash_list()
{
    if (!head)
    {
        return;
    }
    node *next;
    while (head)
    {
        next = head->next;
        delete head;
        head = next;
    }
}

/**-----------------------------------------------------------------------------------
 * END Part 1
 *------------------------------------------------------------------------------------*/

/**-----------------------------------------------------------------------------------
 * START Part 2
 *------------------------------------------------------------------------------------*/

hash_list::hash_list(const hash_list &other)
{
    size = other.size;
    head = nullptr;
    iter_ptr = nullptr;
    if (other.head == nullptr)
    {
        return;
    }

    head = new node{other.head->key, other.head->value, nullptr};
    if (other.iter_ptr == other.head)
    {
        iter_ptr = head;
    }

    node *current_original = other.head->next;
    node *current_copy = head;

    while (current_original != nullptr)
    {
        current_copy->next = new node{current_original->key, current_original->value, nullptr};
        current_copy = current_copy->next;

        if (other.iter_ptr == current_original)
        {
            iter_ptr = current_copy;
        }

        current_original = current_original->next;
    }
}

hash_list &hash_list::operator=(const hash_list &other)
{
    if (this == &other)
    {
        return *this;
    }

    while (head != nullptr)
    {
        node *temp = head;
        head = head->next;
        delete temp;
    }

    iter_ptr = nullptr;
    size = other.size;

    if (other.head == nullptr)
    {
        return *this;
    }

    head = new node{other.head->key, other.head->value, nullptr};
    if (other.iter_ptr == other.head)
    {
        iter_ptr = head;
    }

    node *current_original = other.head->next;
    node *current_copy = head;

    while (current_original != nullptr)
    {
        current_copy->next = new node{current_original->key, current_original->value, nullptr};
        current_copy = current_copy->next;

        if (other.iter_ptr == current_original)
        {
            iter_ptr = current_copy;
        }

        current_original = current_original->next;
    }

    return *this;
}

void hash_list::reset_iter()
{
    iter_ptr = head;
}

void hash_list::increment_iter()
{
    if (iter_ptr == nullptr)
        return;
    iter_ptr = iter_ptr->next;
}

std::optional<std::pair<const int *, float *>> hash_list::get_iter_value()
{
    if (iter_ptr != nullptr)
    {
        return std::pair<const int *, float *>{&iter_ptr->key, &iter_ptr->value};
    }
    return std::nullopt;
}

bool hash_list::iter_at_end()
{
    if (iter_ptr == nullptr)
        return true;
    return false;
}
/**-----------------------------------------------------------------------------------
 * END Part 2
 *------------------------------------------------------------------------------------*/
