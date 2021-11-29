# Double-Node-Linked-Lists
Implements a Double Linked list(each node contains a pointer to the previous and next item on the list) using Templates and ADTs. 
Position/index in this case starts with 1 since we're not dealing with arrays and this project contains a destructor(invokes automatically whenever an object is going to be destroyed at the end of the program). Since the Double Linked list has multiple references(i.e pointers) per node, the edge cases are considered with the copy constructor, insert functions, and default constructor, etc. 
Edge Case example: 
Inserting into the head of the list, rear of the list, and in a position that isn't an extremity. 
Since these functions deal with multiple pointers, the clear and remove functions deallocate the pointer references before a node is removed from the list.
