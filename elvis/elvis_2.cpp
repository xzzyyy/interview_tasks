///////////////////////////////////////////
// 2. В чем проблема? Как исправить?
///////////////////////////////////////////


int do_foo() {
    Foo* foo = new Foo();       // Foo created dynamically, not freed and pointer is lost after returning
    foo->Init();
    foo->Preprocess();
    foo->Calculate();
    return foo->GetResult();
}
