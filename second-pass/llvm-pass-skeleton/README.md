# llvm-pass-skeleton

A completely useless LLVM pass.
It's for LLVM 14.

Build:

    $ mkdir build
    $ cd build
    $ cmake .. # Generate the Makefile.
    $ make     # Actually build the pass.
    $ cd ..

The llvm-pass is created under `build/skeleton/libSkeletonPass.so`.

The content of `file.c`:

```c
int max(int a, int b){
  if(a >= b){
    return a;
  }else{
    return b;
  }
}

int main() {
  int a = 5;
  int b = 10;
  int c = max(a,b);
  return 0;
}

```

Run:

    $ clang -flegacy-pass-manager -Xclang -load -Xclang build/skeleton/libSkeletonPass.* file.c


Output:

DFS interations of `Functions->BasicBlocks->Instructions`
