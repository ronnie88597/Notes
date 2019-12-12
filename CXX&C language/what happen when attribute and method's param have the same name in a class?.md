# what happen when attribute and method's param have the same name in a class?

​	In the case, the attribute of class is alway shielded by method's param. If wanting to accessing the attribute, you can use `this->`.

Example:

```c++
#include <iostream>
class Foo{
    private:
        int Var;
    public:
        Foo():Var(10){}
        void Test(int Var=20){
            std::cout<<"Var="<<Var<<std::endl;
            std::cout<<"this->Var="<<this->Var<<std::endl;
        }
};

int main(int argc, char * argv[]){
    Foo f;
    f.Test();
    return 0;
}
```



Result:

```
Var=20
this->Var=10
```



