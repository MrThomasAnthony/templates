# Vector Operations Library

This library provides functions for working with vectors of vectors.  It includes functionality for initialization, printing, zipping, filtering, mapping, and reducing vector elements.

## Usage

The library defines several templates for generic vector operations.

### Included Templates

* **`ELEM<T>`:**  A type alias for `std::vector<T>`.
* **`VEC<T>`:** A type alias for `std::vector<ELEM<T>>`.
* **`action_t<T>`:** A type alias for a function pointer that takes an integer and returns a `T`.
* **`pred_t<T>`:** A type alias for a function pointer that takes a `T` and returns a boolean.
* **`map_t<T>`:** A type alias for a function pointer that takes two `T`s and returns a `T`.
* **`printElem<T>`:** Prints an `ELEM<T>` to the console.
* **`initVec<T>`:** Initializes a `VEC<T>` with a single `ELEM<T>`.
* **`printVec<T>`:** Prints a `VEC<T>` to the console.
* **`generate<T>`:** Generates a `VEC<T>` by applying a function to a range of integers.
* **`zip<T>`:** Zips two `VEC<T>`s together, concatenating elements.
* **`filter<T>`:** Filters elements from a `VEC<T>` based on a predicate.
* **`map<T>`:** Applies a function to each element of a `VEC<T>`.
* **`reduce<T>`:** Reduces a `VEC<T>` to a single `ELEM<T>` using a binary operation.

### Example Usage (in `main`)

```C++
// Initialize vectors
VEC<int> v;
initVec(v, ELEM<int>{1, 2, 3, 4});
VEC<int> w;
initVec(w, ELEM<int>{-1, 3, -3, 4});

// Print vectors
printVec(v);
printVec(w);

// Zip vectors
VEC<int> z = zip(v, w);
printVec(z);

// Generate a vector
VEC<int> a = generate(10, f);
printVec(a);

// Filter a vector
VEC<int> y = filter(w, g);
printVec(y);

// Map a vector
VEC<int> u = map(w, h);
printVec(u);

// Reduce a vector
ELEM<int> e = reduce(u, k, ELEM<int>{0});
printElem(e);
```
# Installation - Ubuntu

To get started, follow these steps:

1. **Clone the repository:**
   ```bash
   git clone https://github.com/MrThomasAnthony/templates
   cd 

2. **Install g++ (if not already installed):**
    ```bash
    sudo apt update
    sudo apt install g++

3. **Compile the program:**
    ```bash
    g++ -o templates templates.cpp

4. **Run the program:**
    ```bash
    ./templates
