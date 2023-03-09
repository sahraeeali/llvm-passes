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
