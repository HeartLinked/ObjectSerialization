#ifndef DEMO2_BINARY_H
#define DEMO2_BINARY_H

#include <bits/stdc++.h>
using namespace tinyxml2;
using namespace std;

struct UserDefinedType;

namespace binarySerialization {

    /*   std::is_arithmetic    */
    template<typename Type>
    typename std::enable_if<std::is_arithmetic<Type>::value>::type Serialization(Type &x, ofstream &osm) ;

    /*    std::string   */
    void Serialization(const string &s, ofstream &osm);

    /*    std::pair    */
    template<typename A, typename B>
    void Serialization(const pair<A, B> &P, ofstream &osm) ;
    /*  std::vector   */
    template<typename Type>
    void Serialization(const vector<Type> &A, ofstream &osm) ;

    /*  std::list   */
    template<typename Type>
    void Serialization(const list<Type> &A, ofstream &osm) ;

    /*  std::set   */
    template<typename Type>
    void Serialization(const set<Type> &A, ofstream &osm) ;

    /*  std::map   */
    template<typename A, typename B>
    void Serialization(const map<A, B> &P, ofstream &osm) ;

    /*   UserDefinedType    */
    void Serialization(const UserDefinedType &Obj, ofstream &osm) ;

    /*  unique_ptr   */
    template <typename Type>
    void Serialization(const unique_ptr<Type> &Obj, ofstream &osm) ;

    /*  shared_ptr   */
    template <typename Type>
    void Serialization(const shared_ptr<Type> &Obj, ofstream &osm) ;

    /*  std::is_arithmetic  */
    template<typename Type>
    typename std::enable_if<std::is_arithmetic<Type>::value>::type Deserialization(Type &x, ifstream &ism) ;

    /*   std::string    */
    void Deserialization(string &s, ifstream &ism);

    /*   std::pair    */
    template<typename A, typename B>
    void Deserialization(pair<A, B> &P, ifstream &ism) ;

    /*  std::vector   */
    template<typename Type>
    void Deserialization(vector<Type> &A, ifstream &ism) ;

    /*  std::list   */
    template<typename Type>
    void Deserialization(list<Type> &A, ifstream &ism) ;
    /*  std::set   */
    template<typename Type>
    void Deserialization(set<Type> &A, ifstream &ism) ;

    /*  std::map   */
    template<typename A, typename B>
    void Deserialization(map<A, B> &P, ifstream &ism) ;

    /*   UserDefinedType    */
    void Deserialization(UserDefinedType &Obj, ifstream &ism) ;

    /*  unique_ptr   */
    template <typename Type>
    void Deserialization(unique_ptr<Type> &Obj, ifstream &ism) ;

    /*  shared_ptr   */
    template <typename Type>
    void Deserialization(shared_ptr<Type> &Obj, ifstream &ism) ;

    template<typename Type>
    void serialize_binary(const Type &x, const char *name);

    template <typename Type>
    void deserialize_binary(Type &x, const char *name) ;
}

#endif //DEMO2_BINARY_H
