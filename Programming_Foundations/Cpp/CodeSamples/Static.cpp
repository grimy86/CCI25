// Static outside of a class or struct means that the linkage of the static symbol is going to be internal
// Internal linkage means only visible to that translation unit
// Static inside of a class or struct means that this variable is unique and share memory with all instances of the class

int s_Variable{ 5 };