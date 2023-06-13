#include <iostream>
#include <unordered_set>
#include <string>
#include <vector>

using namespace std;

bool isStringInList(const vector<string> &stringList, const string &searchString)
{
    unordered_set<string> stringSet(stringList.begin(), stringList.end());
    return stringSet.find(searchString) != stringSet.end();
}
bool isKeyWord(const string &s)
{
    vector<string> keyWords = {"let", "fn", "where"};
    return isStringInList(keyWords, s);
}

int main()
{
    string searchString = "let";

    if (isKeyWord(searchString))
    {
        cout << "String found in the list." << endl;
    }
    else
    {
        cout << "String not found in the list." << endl;
    }

    return 0;
}
