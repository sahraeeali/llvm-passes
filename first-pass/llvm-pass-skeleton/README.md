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
int main() {
  return 123;
}
```

Run:

    $ clang -flegacy-pass-manager -Xclang -load -Xclang build/skeleton/libSkeletonPass.* file.c


Now, you should see `I saw a function called main!` in your terminal.
