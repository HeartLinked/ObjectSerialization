#ifndef DEMO2_BASE64_H
#define DEMO2_BASE64_H

#include <bits/stdc++.h>
using namespace  std;

void test();
void testbase64();

namespace base64 {

    string get_base64_chars() ;
    string to_base64(std::string const &data) ;
    string from_base64(std::string const &data) ;
    void encode(string fromfile, string tofile);
    void decode(string fromfile, string tofile);
}
#endif //DEMO2_BASE64_H
