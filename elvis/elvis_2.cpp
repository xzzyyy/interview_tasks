///////////////////////////////////////////
// 2. В чем проблема? Как исправить?
///////////////////////////////////////////


int do_foo() {
    Foo* foo = new Foo();       // Foo created dynamically, and its resources will never be released
    foo->Init();                // We can use automatic storage duration (stack) instance of Foo
    foo->Preprocess();
    foo->Calculate();
    return foo->GetResult();
}
