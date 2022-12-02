# Day 1

## Part One

```cpp
g++ solution.cpp
./a.out
```

1. Splitting the input on empty lines, keep a running sum of calories between empty lines.
2. If the sum of calories is greater than the current max, replace the max with the current count.
3. Print out the max once you have parsed through the entire input.

## Part Two

```cpp
g++ solution.cpp
./a.out
```

1. Splitting the input on empty lines, keep a running sum of calories between empty lines
2. Append the sum to a list.
3. After parsing through the input, sort the list.
4. Sum the three highest values in the list and print it

## Notes

- using `endl` is less efficient than just adding a `\n` to the stream. This is because `endl` flushes
the destination buffer, which can be slow.
- `endl` is known as a [stream manipulator](https://cplusplus.com/reference/library/manipulators/) and there are other useful stream manipulators. In a nutshell, they are called manipulators because they change the string's state and behavior. For example, `endl` adds a newline and flushes the destination buffer.

## Questions

- [ ] What is a good template for using `CMake` with C++?
- [ ] Can you add `gtest` for a unit testing suite?
- [ ] `atoi()` is known as an unsafe function in C, but the compiler will still let you use it. What functions is this true for in C++? is `std::stoi()` OK? `std::to_string()`?
- [ ] how to properly configure `.hpp` files in the `CMakeLists.txt` so that you don't have to specify relative paths in the `.cpp` files?