# insert-noop-pass

A pass that puts a noop instruction "add 0, 0" before the first binary operation.

Build:

    $ mkdir build
    $ cd build
    $ cmake .. # Generate the Makefile.
    $ make     # Actually build the pass.
    $ cd ..

The llvm-pass is created under `build/skeleton/libSkeletonPass.so`.

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
```bash
$ clang -emit-llvm -S file.c -o file_original.ll
#Generates the llvm file from the original code (without pass)
$ clang -Xclang -load -Xclang build/skeleton/libSkeletonPass.so -emit-llvm -S file.c -o file.ll
#Generates the llvm file after applying the pass.
```
