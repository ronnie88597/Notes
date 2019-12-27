# How to represent the bit-number of variable or object in LLVM and assembly Lang?

### Generally speaking:

​	b -> byte, 1byte, 8bits

​	h -> halfword, 2bytes, 16bits

​	w -> word, 4bytes, 32bits

​	g -> giant, 8bytes, 64bits. 

### In assembly language:

​	db -> 1btye, 8bits

​	dw -> 2bytes, 16bits

​	dd -> 4bytes, 32bits

​	df -> 6bytes, 48bits

​	dq -> 8bytes, 64bits

​	dt -> 10bytes, 80bits

### In LLVM:

​	The `WordType` is defined as below:

```c++
// file: llvm/include/llvm/ADT/APInt.h
class LLVM_NODISCARD APInt{
    public:
    	typedef uint64_t WordType;
    /// This enum is used to hold the constants we needed for APInt.
    enum : unsigned {
        /// Byte size of word
        APINT_WORD_SIZE = sizeof(WordType),
        /// Bits in a word.
        APINT_BITS_PER_WORD = APINT_WORD_SIZE * CHAR_BIT // CHAR_BIT is defined as 8 in sys-headerfile limits.h
    };
    ... /// ellipsis
};
```

​	As we see the code, a single word represents 8bytes, 64bits.

