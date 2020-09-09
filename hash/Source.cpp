#include<iostream>
#include<Windows.h>
#include<string>

using namespace std;

const int TABLE_SIZE = 128;


class HashNode
{
    public:
    int key;
    string name;
    string adress;
    HashNode* next;
        HashNode(int key, string name, string adress)
        {
        this->key = key;
        this->name = name;
        this->adress = adress;
        this->next = NULL;
        }
};

class HashMap
{
private:
    HashNode** htable;
public:
    HashMap()
    {
        htable = new HashNode * [TABLE_SIZE];
        for (int i = 0; i < TABLE_SIZE; i++)
            htable[i] = NULL;
    }
    ~HashMap()
    {
        for (int i = 0; i < TABLE_SIZE; ++i)
        {
            HashNode* entry = htable[i];
            while (entry != NULL)
            {
                HashNode* prev = entry;
                entry = entry->next;
                delete prev;
            }
        }
        delete[] htable;
    }
   
   
    int HashFunc(int key)
    {
        return key % TABLE_SIZE;
    }

    
    void Insert(int key, string name, string adress)
    {
        int hash_val = HashFunc(key);
        HashNode* prev = NULL;
        HashNode* entry = htable[hash_val];
        while (entry != NULL)
        {
            prev = entry;
            entry = entry->next;
        }
        if (entry == NULL)
        {
            entry = new HashNode(key, name, adress);
            if (prev == NULL)
            {
                htable[hash_val] = entry;
            }
            else
            {
                prev->next = entry;
            }
        }
        else
        {
            entry->name = name;
            entry->adress = adress;
        }
    }
    
    void Remove(int key)
    {
        int hash_val = HashFunc(key);
        HashNode* entry = htable[hash_val];
        HashNode* prev = NULL;
        if (entry == NULL || entry->key != key)
        {
            cout << "No Element found at key " << key << endl;
            return;
        }
        while (entry->next != NULL)
        {
            prev = entry;
            entry = entry->next;
        }
        if (prev != NULL)
        {
            prev->next = entry->next;
        }
        delete entry;
        cout << "Element Deleted" << endl;
    }
    
    int Search(int key)
    {
        bool flag = false;
        int hash_val = HashFunc(key);
        HashNode* entry = htable[hash_val];
        while (entry != NULL)
        {
            if (entry->key == key)
            {
                cout <<" ФИО: " <<  entry->name << "     ";
                cout << " Адрес: " << entry->adress << endl;
                flag = true;
            }
            entry = entry->next;
        }
        if (!flag)
            return -1;
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");
    HashMap hash;
    int key;
    string name;
    string adress;
    

    hash.Insert(123456, "Махоркин А. Н.", "Ленина 3");
    hash.Insert(123123, "Иванов А. В.", "Цветная 13");
    hash.Insert(321321, "Сидоров М. Н.", "Ореховая 32");
    hash.Insert(456456, "Александров Д. К.", "Пушкина 5");
    hash.Insert(789789, "Петров Д. Д.", "Университетская 1");

    cout << "Введите номер: ";
    cin >> key;
    cout << endl << "Человек с номером " << key << " : ";
    if (hash.Search(key) == -1)
        cout << "Не найдено записей по данному номеру "<< endl;
    return 0;
}