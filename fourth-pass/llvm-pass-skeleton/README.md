## fourth-pass

Call a native function when a pattern happens. Here, after the first binary operator, we call a custom function called "logop".  
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

The content of `run-time-lib.c`:

```c
#include <stdio.h>

void logop(int i) {
  printf("computed: %i\n", i);
}
```


Output:

To see the effect of the code, write the following commands:

```bash
$ gcc -c run-time-lib.c #generate .o file with whatever compiler you want.
$ clang -Xclang -load -Xclang build/skeleton/libSkeletonPass.so -c file.c
$ gcc file.o rtlib.o
$ ./a.out
#computed: 15
```

We have successfully changed the
