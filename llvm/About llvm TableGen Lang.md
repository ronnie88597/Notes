# About llvm TableGen Lang

- ## TableGen primitives

  TableGen does not care about the meaning of data(that is up to the backend to define), but it does care about syntax, and it enforces a simple type system. This section describes the syntax and the constructs allowed in a TableGen file.

  - ### Comments
  
    Support C++ sytle "//" and "/* */" comments.
  
  - ### Type system
  
    Tablegen files are strongly typed, in a simple(but complete) type-system. These types are used to perform automatic conversion, check for errors, and to help interface designers constrain the input that they allow. Every [value definition](https://releases.llvm.org/4.0.0/docs/TableGen/LangIntro.html#value-definition) is required to have an associated type.
  
    TableGen supports a mixture of very low-level types(such as bit) and very high-level types(such as dag). This flexibility is what allows it to describe a wide range of information conveniently and compactly. The TableGen types are:
  
    - bit
  
      A 'bit' is a boolean value that can hold either 0 or 1.
  
    - int
  
      The 'int' type represents a simple 32-bit integer value, such as 5.
  
    - string
  
      The 'string' type represents an ordered sequence of characters of arbitrary length.
  
    - bits<ty>
  
      a 'bits' type is an arbitrary, but fixed, size integer that is broken up into individual bits. This type is useful because it can handle some bits being defined while others are undefined.
  
    - list<ty>
  
      This type represents a list whose elements are some other type. The contained type is arbitrary: it can even be another list type.
  
    - Class type
  
      Specifying a class name in a type context means that the defined value must be a subclass of the specified class. This is useful in conjunction with the list type, for example, to constrain the elements of the list to a common base class (e.g., a list<Register> can only contain definitions derived from the "Register" class).
  
    - dag(directed acyclic graph)
  
      This type represents a nestable directed graph of elements.
    
    To date, these types have been sufficient for describing things that TableGen has been used for, but it is straight-forward to extend this list if needed.
    
  - ### Values and Expression
  
    TableGen allows for a pretty reasonable number of different expression forms when building up values. These forms allow the TableGen file to be written in a natural syntax and flavor for the application. The current expression forms supported include:
  
    - ?
  
      uninitialized field
  
    - 0b1001011
  
      binary integer value. Note that this is sized by the number of bits given and will not be silently extended/truncated.
  
    - 7
  
      decimal integer value
  
    - 0x7F
  
      hexadecimal integer value
  
    - "foo"
  
      string value
  
    - [{ ... }]
  
      usually called a "code fragment", but is just a multiline string literal.
  
    - [ X, Y, Z ]<type>
  
      list value. <type> is the type of the list element and is usually optional. In rare cases, TableGen is unable to deduce the element type in which case the user must specify it explicitly.
  
    - { a, b, 0b10 }
  
      initializer for a 'bits<4>' value. 1-bit from 'a', 1-bit from 'b', 2-bits from 0b10.
  
    - value
  
      value reference
  
    - value{17}
  
      access to one bit of a value
  
    - value{15-17}
  
      access to multiple bits of a value
  
    - DEF
  
      reference to a record definition
  
    - CLASS<val list>
  
      reference to a new anonymous definition of CLASS with the specified template arguments.
  
    - X.Y
  
      reference to the subfield of value
  
    - list[4-7, 17, 2-3]
  
      A slice of the 'list' list, including elements 4,5,6,7,17,2, and 3 from it. Elements may be included multiple times.
  
    - foreach <var> = [ <list> ] in { <body> }, foreach <var> = [ <list> ] in <def>
  
      Replicate <body> or <def>, replacing instances of <var> with each value in <list>. <var> is scoped at the level of the foreach loop and must not conflict with any other object introduced in <body> or <def>. Currently only defs are expanded within <body>.
  
    - foreach <var> = 0-15 in ...     , foreach <var> = {0-15, 32-47} in ...
  
      Loop over ranges of integers. The braces are required for multiple ranges.
  
    - DEF a, b
  
      a dag value. The first element is required to be a record definition, the remaining elements in the list may be arbitrary other values, including nested 'dag' values.
  
    - !listconcat(a, b, ... )
  
      A list value that is the result of concatenating the 'a' and 'b' lists. The lists must have the same element type. More than two arguments are accepted with the result being the concatenation of all the list given.
  
    - !strconcat(a, b, ...)
  
      A string value that is the result of concatenating the 'a' and 'b' strings. More than two argument are accepted with the result being the concatenation of all the strings given.
  
    - str1#str2
  
      "#"(paste) is a shorthand for !strconcate. It may concatenate things that are not quoted strings, in which case an implicit !cast<string> is done on the operand of the paste.
  
    - !cast<type>(a)
  
      A symbol of type type obtained by looking up the string 'a' in the symbol table. If the type of 'a' does not match type, TableGen aborts with an error. !cast<string> is a special case in that the argument must be an object defined by a 'def' construct.
  
    - !subst(a, b, c)
  
      If 'a' and 'b' are of string type or are symbol references, substitute 'b' for 'a' in 'c'. This operation is analogous to $(subst) is GNU make.
  
    - !foreach(a, b, c)
  
      For each member of dag or list 'b' apply operator 'c'. 'a' is a dummy variable that should be declared as a member variable of an instantiated class. This operation is analogous to $(foreach) in GNU make.
  
    - !head(a)
  
      The first element of list 'a'.
  
    - 
  
    - 
  
    - 
  
- ## Classes and definitions

  - ### Value definitions

  - ### The TableGen type system

  - ### TableGen values and expressions

- ## File scope entities

  - ### File inclusion

  - ### 'let' expressions

  - ### Looping

- ## Code Generator backend info

  - ### 