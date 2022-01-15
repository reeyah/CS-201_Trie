#include <stdio.h>
#include <string.h>

#include "trie.h"

// misc

void endl();

// ----- main test functions -----
void test();

// ----- all other testing functions -----

void test_Trie();

int main()
{
    test();
}

// ======= definitions =======

void test()
{
    test_Trie();
}

void test_Trie()
{
    // initialization test
    Trie t = initTrie();
    printf("Trie is created!\n");
    endl();

    // insertion test
    insert(&t, "abc");
    insert(&t, "ab");
    insert(&t, "abd");
    insert(&t, "abcd");
    insert(&t, "b");
    insert(&t, "bx");
    insert(&t, "bc");
    printf("insertion done!\n");
    // print test
    print_trie(&t);
    printf("number of elements are: %d\n", count(&t));
    endl();

    // searching test
    printf("Searching for abcd: %d\n", search(&t, "abcd"));
    printf("Searching for abb: %d\n", search(&t, "abb"));
    printf("Searching for abcd: %d\n", search(&t, "abcd"));
    printf("Searching for xyz: %d\n", search(&t, "xyz"));
    printf("Searching for a: %d\n", search(&t, "a"));
    endl();

    // remove_string test
    printf("removing abb\n");
    remove_str(&t, "abb");
    print_trie(&t);
    printf("number of elements are: %d\n", count(&t));
    printf("removing ab\n");
    remove_str(&t, "ab");
    print_trie(&t);
    printf("number of elements are: %d\n", count(&t));
    printf("removing abce\n");
    remove_str(&t, "abce");
    print_trie(&t);
    printf("number of elements are: %d\n", count(&t));
    printf("removing xyz\n");
    remove_str(&t, "xyz");
    print_trie(&t);
    printf("number of elements are: %d\n", count(&t));
    endl();

    // some more insertion test
    insert(&t, "abbcb");
    insert(&t, "abcd");
    insert(&t, "acbd");
    insert(&t, "abccd");
    insert(&t, "accbce");
    printf("insertion done!\n");
    print_trie(&t); endl();
    
    // prefix search test
    printf("prefix search abc: %d\n", prefix_search(&t, "abc"));
    printf("prefix search b: %d\n", prefix_search(&t, "b"));
    printf("prefix search ab: %d\n", prefix_search(&t, "ab"));
    printf("prefix search acc: %d\n", prefix_search(&t, "acc"));
    printf("prefix search ac: %d\n", prefix_search(&t, "ac"));
    printf("prefix search abbc: %d\n", prefix_search(&t, "abbc"));
    printf("prefix search abcb: %d\n", prefix_search(&t, "abcb"));
    printf("prefix search xyz: %d\n", prefix_search(&t, "xyz"));
    endl();

    // autocomplete test
    char **ss = autocomplete(&t, "abc", 2);
    printf("2 string starting with abc:\n");
    print_str_array(ss, 2);
    deallocate_str_array(ss, 2);

    // autocomplete test
    ss = autocomplete(&t, "abc", count(&t));
    printf("All string starting with abc:\n");
    print_str_array(ss, count(&t));
    deallocate_str_array(ss, 2);

    // autocomplete test
    ss = autocomplete(&t, "acc", count(&t));
    printf("All string starting with acc:\n");
    print_str_array(ss, count(&t));
    deallocate_str_array(ss, 2);

    // autocomplete test
    ss = autocomplete(&t, "xyz", count(&t));
    printf("All string starting with xyz:\n");
    print_str_array(ss, count(&t));
    deallocate_str_array(ss, 2);
    endl();

    // copy test
    Trie ct = initTrie();
    trie_copy(&ct, &t);
    printf("value of copied trie is:\n");
    print_trie(&ct);
    printf("Number of strings: %d\n", count(&ct));
    endl();

    // sorting of strings
    char *strings[] = {"bcd", "axt", "acd", "bac"};
    char **sorted = sort_strings(strings, 4);
    printf("given strings:\n");
    print_str_array(strings, 4);
    printf("sorted strings:\n");
    print_str_array(sorted, 4);
    endl();
    deallocate_str_array(sorted, 4);

    // clear test
    printf("clear trie\n");
    clear(&t);
    print_trie(&t);
    endl();

    // delete test
    deleteTrie(&t);
    printf("delete successfull!");
}

void endl()
{
    printf("\n");
}