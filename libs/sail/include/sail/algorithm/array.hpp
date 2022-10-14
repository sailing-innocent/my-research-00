template<typename T>
class Array {
public:
    Array();
    Array(Array<T>& rhs);
    Array<T>& operator=(Array<T>& rhs);
    ~Array();
private:
    std::array<Node<T>, SAIL_ARRAY_MAX> nodes;
};
