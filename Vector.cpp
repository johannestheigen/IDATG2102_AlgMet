/**
*   Program example no. 1 - Vector (self-made simple class).
 *
 *   This example shows a custom implementation of the container class Vector.
 *   Code has been written for the following functions:
 *
 *     -  Vector(const int length = 200)
 *     -  ~Vector
 *     -  int   capacity()
 *     -  void  clear()
 *     -  void  display()
 *     -  bool  empty()
 *     -  T     get(const int pos)                   //  i.e.: ..... = vec[pos]
 *     -  bool  insert(const int pos, const T t)
 *     -  T     pop_back()
 *     -  T     pop_front()
 *     -  bool  push_back(const T t)
 *     -  bool  push_front(const T t)
 *     -  bool  remove(const int pos)
 *     -  void  resize(const int newLength)
 *     -  void  set(const int pos, const T value)    //  i.e.: vec[pos] = value
 *     -  int   size()
 *
 *   @author Frode Haug, NTNU (Original)
 *   @author Johannes Nupen Theigen (Modifier)
 *   @version 12.09.2025
 *   @since 12.09.2025
 */

#include <iostream>                  //  cout
#include <string>                    //  string
using namespace std;


/**
 *  The container class Vector, which is a custom-made version of the STL <vector>.
 *
 *  Contains an array of type 'T', and two integers that indicate total
 *  capacity/length (capacity) and the current number of elements (size).
 */
template<typename T> //  'template'!  'T': flexible data type!
class Vector {
    //  (Does not exist directly in Java!
    //   "Generics" are something somewhat similar.)
private:
    T *data; //  POINTER to an array of type 'T'.
    int max_length, amount; //  Max length (capacity) and current size.

public: //  Initialize members using default parameter:
    Vector(const int length = 200) {
        data = new T[length];
        max_length = length;
        amount = 0;
    }

    ~Vector() { delete [] data; } // Frees allocated memory (using 'new').

    int capacity() const { return max_length; }


    void clear() {
        //  Reset the usage of the array:
        //          for (int i = 0; i < amount; i++)  data[i] = 0;  //  Unnecessary?!!!
        amount = 0;
    }

    void display() const {
        //  Print the ENTIRE content of the Vector:
        for (int i = 0; i < amount; i++)
            cout << i << ": " << data[i] << "  ";
        cout << "\n\t'amount': " << amount << '\n';
    }

    bool empty() const { return (amount == 0); } //  Empty or not.

    //  Equivalent to:   .... = vec[pos].
    T get(const int pos) const {
        //  Retrieve (if possible) element no. pos:
        if (pos >= 0 && pos < amount) //  Within valid range:
            return data[pos];         //  Return the current value.
        else
            cout << "\nIndex out of bounds .....\n\n"; //  Custom message ??
        return T();
    }

    //  Insert (if possible) 't' at position 'pos':
    bool insert(const int pos, const T t) {
        if (amount == max_length) {
            resize(max_length + 100); //  Increase capacity by 100.
        }
        if (pos >= 0 && pos <= amount) {
            //  Valid index:
            for (int i = amount; i > pos; i--) //  ALL elements after are shifted
                data[i] = data[i - 1];         //    up ONE position.
            data[pos] = t;    //  Insert new element.
            amount++;         //  Increase element count.
            return true;      //  Insertion succeeded.
        }
        cout << "\nIndex out of bounds .....\n\n"; //  Custom message ??
        return false;         //  No insertion.
    }

    T pop_back() {
    //  Remove (if possible) the last element:
    if (!empty()) {
        //  Not empty:
        T last = data[amount - 1]; //  Save the last element.
        amount--;                  //  Decrease the count by 1.
        return last;               //  Return the last element.
    } else
        cout << "\nEmpty Vector - impossible to pop!\n\n";
    return T();
}


T pop_front() {
    //  Remove (if possible) the first element:
    if (!empty()) {
        //  Not empty:
        T first = data[0]; //  Save the first element.
        remove(0);         //  Remove the first.
        return first;      //  Return the stored value.
    } else
        cout << "\nEmpty Vector - impossible to pop!\n\n";
    return T();
}


bool push_back(const T t) {
    //  Add new element at the back,
    return insert(amount, t); //    using another function.
}


bool push_front(const T t) {
    //  Add new element at the front,
    return insert(0, t); //    using another function.
}

bool remove(const int pos) {
    //  Remove (if possible) element no. 'pos':
    if (pos >= 0 && pos < amount) {
        //  Valid index:
        for (int i = pos; i < amount - 1; i++) //  Shift all AFTER
            data[i] = data[i + 1];             //    down ONE position.
        amount--; //  Decrease total count.
        return true;
    } else {
        cout << "\nIndex out of bounds .....\n\n"; //  Custom message ??
        return false;
    }
}

void resize(const int newLength) {
    //  Change capacity to a larger size, not smaller.
    if (newLength > max_length) {
        T *newData = new T[newLength]; //  Allocate new array.
        for (int i = 0; i < amount; i++)
            newData[i] = data[i];      //  Copy old values.
        delete [] data;                //  Free old array.
        data = newData;                //  Assign new array to data.
        max_length = newLength;        //  Update capacity.
    }
}

//  Equivalent to:   vec[pos] = value.
void set(const int pos, const T value) {
    if (pos >= 0 && pos < amount)      //  Valid index:
        data[pos] = value;             //  Set to new value.
    else
        cout << "\nIndex out of bounds .....\n\n"; //  Custom message ??
}


int size() const { return amount; } //  Current number of elements.
};


/**
 *  Main program:
 */
int main() {
    Vector<int> iVec; //  Create a Vector of ints.
    iVec.push_back(10);
    iVec.push_back(20);
    iVec.display();
    return 0;
}