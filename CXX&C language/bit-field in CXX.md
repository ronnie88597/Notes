# bit-field in CXX

Declares a class data member with explicit size, in bits. Adjacent bit field members may be packed to share and straddle the individual bytes.

A bit filed declaration is a class data member declaration which uses the following declarator:

***identifier(optional) attr(optional) : size			(1)***

***identifier(optional) attr(optional) : size brace-or-equal-initializer			(2) (since C++ 20)***

The type of the bit field is introduced by the `decl-specifier-seq` of the declaration syntax.

-   attr(C++11)    - optional sequence of any number of attributes.
-   identifier		- the name of the bit field that it being declared. The name is optional: nameless bit-fields introduce the specified number of bits of padding.
-   size                  - an integral constant expression with a value greater or equal to zero. When greater than zero. this is the number of bits that this bit field will occupy. The value zero is only allowed for nameless bit-fields and has special meaning: it specifics that the next bit field in the class definition will begin at an allocation unit's boundary.
-   brace-or-equal-initialize     -  default member initializer to be used with this bit field.

Let's take an example:

```c++
struct S {
 // three-bit unsigned field,
 // allowed values are 0...7
 unsigned int b : 3;
};
struct S {
    // will usually occupy 2 bytes:
    // 3 bits: value of b1
    // 2 bits: unused
    // 6 bits: value of b2
    // 2 bits: value of b3
    // 3 bits: unused
    unsigned char b1 : 3, : 2, b2 : 6, b3 : 2;
};
struct S {
    // will usually occupy 2 bytes:
    // 3 bits: value of b1
    // 5 bits: unused
    // 6 bits: value of b2
    // 2 bits: value of b3
    unsigned char b1 : 3;
    unsigned char :0; // start a new byte
    unsigned char b2 : 6;
    unsigned char b3 : 2;
};
```

## For more information:

https://en.cppreference.com/w/cpp/language/bit_field