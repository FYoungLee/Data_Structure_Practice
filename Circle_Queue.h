class mQue {
    int *data;
    size_t front;
    size_t rear;
    size_t cur_size;
    size_t MAX;
public:
    mQue(size_t mx): MAX(mx + 1), data(new int) {
        front = rear = cur_size = 0;
    }
    bool isEmpty() {
        return front == rear;
    }
    bool isFull() {
        if (size() == MAX - 1)
            return true;
        else return false;
    }

    bool push(int x) {
        if (isFull()) { cerr<< "full\n"; return false; }
        ++front %= MAX;
        data[front] = x;
        ++cur_size;
        return true;
    }

    int pop() {
       if (isEmpty()) { cerr<< "empty\n"; return 0; }
       ++rear %= MAX;
       int ret = data[rear];
       --cur_size;
       return ret;
    }

    size_t size() {
        return cur_size;
    }
    int& operator[](size_t i) {
        if (i > size() - 1) { cerr<< "out of range\n"; return data[rear]; }
        return data[rear + i + 1];
    }

    void display() {
        auto n = rear;
        while (n != front) {
            ++n %= MAX;
            cout << data[n] << ' ';
        }
        cout << endl;
    }
};
