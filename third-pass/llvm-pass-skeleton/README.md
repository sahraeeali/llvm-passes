# third-pass

A pass to change the add operators to multiply.  
It's for LLVM 14.

Build:

    $ mkdir build
    $ cd build
    $ cmake .. # Generate the Makefile.
    $ make     # Actually build the pass.
    $ cd ..

The llvm pass is created under `build/skeleton/libSkeletonPass.so`.

The content of `file.c`:

```c
int sum(int a, int b){
  int s = a + b;
  return s;
}

int main() {
  int a = 5;
  int b = 10;
  int c = sum(a,b);
  return c;
}
```

Output:

To see the effect of the code, write the following commands:

```bash
$ clang file.c
$ ./a.out
$ echo $?
#15 (5 + 10)
$ clang -Xclang -load -Xclang build/skeleton/libSkeletonPass.so file.c
$ ./a.out
$ echo $?
#50 (5 * 10)
```

We have successfully changed the
