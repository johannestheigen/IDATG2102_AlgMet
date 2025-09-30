/**
* The program shows a self-made implementation of the container class Heap.
* Code has been created for the following functions:
*
* - Heap(const int length = 200)
* - ~Heap
* - void change(const int keyNr, const T newValue)
* - void display()
* - void downHeap(T arr[], const int amount, int keyNr)
* - void extract(const int keyNr)
* - void insert(const T value)
* - T remove()
* - T replace(const T value)
* - void upHeap(int keyNr)
*
* @author Frode Haug, NTNU (Original)
* @author Johannes Nupen Theigen (change() and extract())
* @version 30.09.2025
* @since 30.09.2025
*/
#include <iostream>
#include <limits>

/**
* The container class Heap.
*
* Contains an array ('data') of type 'T', two ints indicating the heap's
* max. length and current number of elements in the array, and a sentinel key.
*/
template<typename T>
class Heap {
private:
    T *data;
    int length,
            amount;
    T sentinelKey;

    // PRIVATE function - then ONLY used by OWN functions!
    // Moves any initial data[keyNr]
    void upHeap(int keyNr) {
        T value = data[keyNr]; // The element that will be moved up.
        data[0] = sentinelKey; // Inserts the sentinel key.
        while (data[keyNr / 2] < value) {
            // Parents are smaller:
            data[keyNr] = data[keyNr / 2]; // Moves parents down.
            keyNr = keyNr / 2; // The index will be the parent's.
        }
        data[keyNr] = value; // Inserts where stopped.
    }

public:
    Heap(const int len = 200) {
        // Initializing constructor:
        data = new T[len];
        length = len;
        amount = 0;
        sentinelKey = std::numeric_limits<T>::max();
    }

    ~Heap() { delete [] data; } // Frees allocated memory.

  /**
   * Change the value at 'keyNr' to 'newValue'.
   * Moves up if the new value is larger or equal,
   * otherwise moves down.
   *
   * @param keyNr    The index of the element to change (1..amount)
   * @param newValue The new value
   */
    void change(const int keyNr, const T newValue) {
        T oldValue = data[keyNr]; // Stores the old value
        data[keyNr] = newValue;   // Change to new value
        if (newValue >= oldValue) {
            upHeap(keyNr);
        } else {
            downHeap(data, amount, keyNr);
        }
    }

    /**
     * Prints the ENTIRE heap content:
     */
    void display() const {
        for (int i = 1; i <= amount; i++) std::cout << ' ' << data[i];
    }

    /**
       * Moves the element at 'keyNr' down the heap until the heap property is restored.
       *
       * @param arr   The array representing the heap
       * @param ant   The number of elements currently in the heap
       * @param keyNr The index of the element that may need to be moved down
    */
    void downHeap(T arr[], const int ant, int keyNr) {
        int j; // The index of one of the children.
        T value = arr[keyNr]; // The element that is possibly moved down.
        while (keyNr <= ant / 2) {
            // The ones before halfway have children:
            j = 2 * keyNr; // Left child index.
            // IF has right child and this is larger,
            // updates to ITS index:
            if (j < ant && arr[j] < arr[j + 1]) j++;
            if (value >= arr[j]) // Current child is NOT larger,
                break; // aborts downward search.
            arr[keyNr] = arr[j]; // Moves the child up.
            keyNr = j; // New index will be this child.
        }
        arr[keyNr] = value; // Inserts/inserts where stopped.
    }

/**
  * Insert a new element at the back and swap with parent
  * until it is no longer larger.
  *
  * @param value The value to insert
  */
    void insert(const T value) {
        if (amount < length - 1) {
            // Is there room:
            data[++amount] = value; // Inserted at the very back.
            upHeap(amount); // Possibly moved up (upHeapes).
        } else // Is there room:
            std::cout << "\nThe heap is full with " << length
                    << " elements (incl. sentinel key)!\n\n";
    }

    /**
     * Store and return the root (index 1).
     * Move the last element to the root and swap down
     * with the largest child until it is no longer smaller.
     *
     * @return The removed root if not empty,
     *         otherwise the sentinel key
     */
    T remove() {
        // the largest/first from the heap:
        if (amount > 0) {
            // The heap is NOT empty:
            T value = data[1]; // Stores away the first.
            data[1] = data[amount--]; // The very back is moved ALL the way to the front.
            downHeap(data, amount, 1); // DownHeaps this.
            return value; // Returns the first (unstored).
        } else {
            // The heap IS empty:
            std::cout << "\nThe heap is completely empty - nothing in 'remove'!\n\n";
            return sentinelKey;
        }
    }

    /**
     * Replace the root (index 1) with a new value and
     * return the new maximum. Uses index 0 (sentinel)
     * to handle the case where the new value is the largest.
     *
     * @param value The new value
     * @return The maximum element after replacement
     */
    T replace(const T value) {
        data[0] = value; // Inserts into element no.0 !!!
        downHeap(data, amount, 0); // Downheaper.
        return data[0]; // Largest is afterwards in element no.0!
    } // And is then EITHER the new one (which is largest!),
    // OR the one that was initially the root (no.1).


  /**
    * Remove the element at 'keyNr'.
    * The last element is moved into its place.
    * Moves up if the new value is larger than the old one,
    * otherwise moves down.
    *
    * @param keyNr The index of the element to remove (1..amount)
    */
    void extract(const int keyNr) {
        T oldValue = data[keyNr];       // Stores away the removed value
        data[keyNr] = data[amount--];   // Move last element into its place
        if (data[keyNr] > oldValue) {
            upHeap(keyNr);
        } else {
            downHeap(data, amount, keyNr);
        }
    }
};

/**
* Main program:
*/
int main() {
    Heap<int> heap;

    std::cout << "\n\nShows the usage of the heap.";
    heap.insert(1);
    std::cout << "\nInsert 1 : ";
    heap.display();
    heap.insert(5);
    std::cout << "\nInsert 5 : ";
    heap.display();
    heap.insert(2);
    std::cout << "\nInsert 2 : ";
    heap.display();
    heap.insert(6);
    std::cout << "\nInsert 6 : ";
    heap.display();
    heap.replace(4);
    std::cout << "\nReplace 4: ";
    heap.display();
    heap.insert(8);
    std::cout << "\nInsert 8 : ";
    heap.display();
    heap.remove();
    std::cout << "\nRemove : ";
    heap.display();
    heap.insert(7);
    std::cout << "\nInsert 7 : ";
    heap.display();
    heap.insert(3);
    std::cout << "\nInsert 3 : ";
    heap.display();

    std::cout << "\n\n\nTesting two self-made functions from task no.15:\n";
    heap.change(4, 5);
    std::cout << "\nChange #4 to 5: ";
    heap.display();
    heap.change(3, 1);
    std::cout << "\nChange #3 to 1: ";
    heap.display();
    heap.extract(2);
    std::cout << "\nExtract #2: ";
    heap.display();
    heap.extract(2);
    std::cout << "\nExtract #2: ";
    heap.display();
    heap.extract(1);
    std::cout << "\nExtract #1: ";
    heap.display();

    std::cout << "\n\n";
    return 0;
}