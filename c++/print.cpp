/// Name: PrintFunctions
/// Description: Print function for various containers
/// Detail:
/// Guarantee: } // PrintFunctions


// Print function prototype
template <typename T>
void print(const T data);

void print(const __int128_t data);

void print(const __uint128_t data);

template <typename T, typename U>
void print(const pair<T, U> data);

template <typename T>
void print(const deque<T> data);

template <typename T>
void print(const stack<T> data);

template <typename T>
void print(const queue<T> data);

template <typename T>
void print(const priority_queue<T> data);

template <typename T>
void print(const vector<T> data);

template <typename T>
void print(const set<T> data);

template <typename T>
void print(const unordered_set<T> data);

template <typename T>
void print(const multiset<T> data);

template <typename T, typename U>
void print(const map<T, U> data);

template <typename T, typename U>
void print(const unordered_map<T, U> data);

// Print functions
template <typename T>
void print(const T data)
{
    cout << data;
}

void print(const __int128_t data)
{
    cout << "int128:: ";
    bool negative = false;
    stack<int> temp;
    if (data == 0)
        temp.push(0);
    else
    {
        __int128_t _data = data;
        if (_data < 0)
        {
            negative = true;
            _data = -data;
        }
        while (_data)
        {
            temp.push(_data % 10);
            _data /= 10;
        }
    }
    if (negative)
        cout << "-";
    while (temp.size())
    {
        cout << temp.top();
        temp.pop();
    }
}

void print(const __uint128_t data)
{
    stack<int> temp;
    if (data == 0)
        temp.push(0);
    else
    {
        __uint128_t _data = data;
        while (_data)
        {
            temp.push(_data % 10);
            _data /= 10;
        }
    }
    while (temp.size())
    {
        cout << temp.top();
        temp.pop();
    }
}

template <typename T, typename U>
void print(const pair<T, U> data)
{
    print(data.first);
    cout << " : ";
    print(data.second);
}

template <typename T>
void print(const deque<T> data)
{
    cout << "<deque>{";
    for (T val : data)
    {
        print(val);
        cout << ", ";
    }
    cout << "}";
}

template <typename T>
void print(const stack<T> data)
{
    cout << "<stack>{";
    while (!data.empty())
    {
        T val = data.top();
        data.pop();
        print(val);
        cout << ", ";
    }
    cout << "}";
}

template <typename T>
void print(const queue<T> data)
{
    cout << "<queue>{";
    while (!data.empty())
    {
        T val = data.front();
        data.pop();
        print(val);
        cout << ", ";
    }
    cout << "}";
}

template <typename T>
void print(const priority_queue<T> data)
{
    cout << "<priority_queue>{";
    while (!data.empty())
    {
        T val = data.top();
        data.pop();
        print(val);
        cout << ", ";
    }
    cout << "}";
}

template <typename T>
void print(const vector<T> data)
{
    cout << "<vector>{";
    for (T val : data)
    {
        print(val);
        cout << ", ";
    }
    cout << "}";
}

template <typename T>
void print(const set<T> data)
{
    cout << "<set>{";
    for (T val : data)
    {
        print(val);
        cout << ", ";
    }
    cout << "}";
}

template <typename T>
void print(const unordered_set<T> data)
{
    cout << "<unordered_set>{";
    for (T val : data)
    {
        print(val);
        cout << ", ";
    }
    cout << "}";
}

template <typename T>
void print(const multiset<T> data)
{
    cout << "<multiset>{";
    for (T val : data)
    {
        print(val);
        cout << ", ";
    }
    cout << "}";
}

template <typename T, typename U>
void print(const map<T, U> data)
{
    cout << "<map>{\n";
    for (pair<T, U> val : data)
    {
        print(val);
        cout << "\n";
    }
    cout << "}";
}

template <typename T, typename U>
void print(const unordered_map<T, U> data)
{
    cout << "<unordered_map>{\n";
    for (pair<T, U> val : data)
    {
        print(val);
        cout << "\n";
    }
    cout << "}";
} // PrintFunctions