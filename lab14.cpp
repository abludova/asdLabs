#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
using namespace std;

//Вторая лаба по хеш-таблицам, тут открытая адрессация и двойное хеширование.
//Отличий достаточно много, основные заключаются в том, что храним данные теперь в динамическом массиве строк
//ля хеширования используем 2 функции, для минимизации коллизий, в случае коллизий линейно двигаемся по таблице
// Из-за этого поиск совершается не за O(1) а за O(n) в самом плохом случае, но в целом скорость будет близка к константе.

class HashTable
{
    int capacity;
    string* table;
    vector<int> keys;
    int N = 13;
    double A = 0.618033;
public:
    HashTable(int V);
    void insertItem(int key, string data);
    int search(string text);
    int checkPrime(int n)
    {
        int i;
        if (n == 1 || n == 0)
        {
            return 0;
        }
        for (i = 2; i < n / 2; i++)
        {
            if (n % i == 0)
            {
                return 0;
            }
        }
        return 1;
    }
    int getPrime(int n)
    {
        if (n % 2 == 0)
        {
            n++;
        }
        while (!checkPrime(n))
        {
            n += 2;
        }
        return n;
    }
    int hashFunctionMod(int key) const
    {
        return (key % capacity);
    }
    int hashFunctionComb(int key)
    {
        return N * (fmod(key * A, 1));
    }
    int hashFunctionPowered(int key)
    {

        return(hashFunctionMod(key) + hashFunctionComb(key));
    }
    void displayHash();
};
HashTable::HashTable(int c)
{
    int size = getPrime(c);
    this->capacity = size;
    table = new string[size];
}
void HashTable::insertItem(int key, string data)
{
    int index = hashFunctionPowered(key);
    if (table[index].empty()) {
        keys.push_back(index);
    }
    else {
        int i = 0;
        while (true) {
            cout << table[index + i] << endl;
            if (table[index + i].empty()) {
                keys.push_back(index + i);
                index += i;
                break;
            }
            i++;
        }
    }
    table[index] = data;
}
void HashTable::displayHash()
{
    for (int j = 0; j < keys.size(); j++) {
        cout << "[" << keys[j] << "]" << " ----> " << table[keys[j]] << endl;
    }
}
int HashTable::search(string text)
{
    int tempHash = 0;
    for (char i : text) {
        tempHash += (int)i;
    }
    int index = hashFunctionPowered(tempHash);
    int counter = 0;
    int i = 0;
    while (true) {
        if (table[index + i].empty())
            break;
        if (table[index + i] == text) {
            counter++;
        }
        i++;
    }
    return counter;
}
int main()
{
    string text;
    string subText;
    int preHash = 0;
    HashTable h(1000);
    getline(cin, text, '\n');
    for (int i = 0; i <= text.size(); i++) {
        if (text[i] != ' ' && (int)text[i] != 0) {
            subText += text[i];
            preHash += (int)text[i];
        }
        else {
            h.insertItem(preHash, subText);
            preHash = 0;
            subText = "";
        }
    }
    h.displayHash();

    cout << h.search("is") << endl;

}