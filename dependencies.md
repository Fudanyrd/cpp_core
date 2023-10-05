## Now I may go into details on how to use these template classes.

### BSTree.h

**Dependencies**: [Stack.h](#Stack.h)

root(): get the root pointer of the Binary Sorted Tree.

insert(const _T& value): insert the value into the tree(if the value already exists, nothing will be done); else it will find the *right* place and insert the value.

remove(const _T& value): remove the given value(if the value is *NOT* in the tree, don't worry, the function can deal with this without throwing any exceptions).

find(const _T& value): find the given value(if not exists, return null-pointer).

### charImg.h

**Dependencies**: [String.h](#String.h), [Vec.h](#Vec.h), [Ptr.h](#Ptr.h)

charImg(const Vec&): using a String-element Vec to initialize it.

height(),width(): get the height and width of a character image.

hcat(img1,img2): return the horizontal-linked character image.

vcat(img1,img2): return the vertical-linked character image.

frame(img): return the framed image.

### complex_num.h

**Dependencies**: [String.h](#String.h)

+,-,*,/,~(conjugation) are supported. you can use it as easy as you deal with other numeric types.

you may also convert a *String*(provided in this library) into a complex number.

### dblList.h

**Dependencies**: None

It has its *iterator* and *const_iterator* for easy traverse by ++ and --.

begin(): get the iterator or const_iterator pointing to the first element.

end(): telling you where you should end this tranverse.

**for example**, you may write the following content:

dblList lst;    //then initialize it

for(const_iterator it=lst.begin(), it!=lst.end();++it){

//do something here...

}

empty(): if the list contains elements.

clear(): remove all elements. be very careful if you want to discard all its elements.

insert(), erase(): insert *in front of* an element or delete an element and return its *next* iterator.

## dictionary.h

**Dependencies**: [set.h](#set.h)

generate quick-search based on binary_find on array.

you can use key as index to quickly locate location and extract its value.

size() can help you get its size.

remove_key(): remove a key-value pair in it.

keys(), values(): get an array of its keys, values.(you need to remember to deallocate these memory)

## gen_list.h

**Not Yet Implemented**

## heap.h

**Dependencies** None

A realization of priority queue.

Always guarantee that the element with minimum key is at the front.

## Map.h

**Dependencies** [BSTree.h](#BSTree.h),[Stack.h](#Stack.h)

similar to dictionary, at some time you can use Map the same way as dictionary.

Its *pros*: since it is based on binary sorted tree, it can insert a value in O(lnN).

Its *cons*: tranversal is much harder than dictionary because dictionary is based on array.

You can store its Key-Value pairs into a container through its copy method, though.

## matrix.h

**Dependencies**: [Map.h](#Map.h), [BSTree.h](#BSTree.h), [Stack.h](#Stack.h)

sparce matrix based on Map.

you can generate index by matrixIndex(rowNumber,ColumnNumber).

get(matrixIndex), revalue(matrixIndex, value) can help you get a value in the matrix or modify it.

transposed(): get a **new** matrix which is the transpose of the original one.

operator+(matrix,matrix): get the sum of two matrix(generate a new one)

## polynominal.hpp

**Dependencies**: [dictionary.h](#dictionary.h), [set.h](#set.h)

support + operation.

## Ptr.h

**Dependencies**: None

a reference-counted handle class. It's the basic of other classes in the library.

## Queue.h

**Dependencies**: None

based on round array.

it can deQueue from its head and enQueue from its tail.

## set.h

**Dependencies**: None

basis of class dictionary.

operator+(set,set): find *all* the element in set 1 or set 2, return a new set.

operator*(set,set): find *all* the element both appeared in set 1 and set 2.

operator-(set,set): find *all* the element appeared in set 1 but **Not** in set 2.

## Stack.h

**Dependencies**: None

push_back(): push a value into its tail.

pop(): remove a value from its tail.

empty(): if the stack is empty.

back(): its last element.

## String.h

**Dependencies**: [Vec.h](#Vec.h)

similar to that in the STL.

use c_str() method to convert it into a char*.

## tree.h

**Not Yet Implemented**

## unsignedInt.h

**Dependencies**: [String.h](#String.h), [Vec.h](#Vec.h)

similar to unsigned int, but does *not* support - and /

can store very large integers (e.g. 1e500)

# Vec.h

**Dependencies**: None

similar to vector in the STL except that it has integrated sort method.
