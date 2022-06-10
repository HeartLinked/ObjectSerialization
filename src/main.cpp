#include <bits/stdc++.h>
#include "tinyxml2.h"
#include "binary.h"
#include "base64.h"
#include "XML.h"

using namespace std;
using namespace tinyxml2;

static bool open_base64 = 0;

namespace binarySerialization {

    /*   std::is_arithmetic    */
    template<typename Type>
    typename std::enable_if<std::is_arithmetic<Type>::value>::type Serialization(Type &x, ofstream &osm) {
        osm.write((char*)&x, sizeof(x));
    }

    /*    std::string   */
    void Serialization(const string &s, ofstream &osm){
        int cnt = s.size();
        Serialization(cnt, osm);
        for(int i = 0; i < s.size(); i++) {
            Serialization(s[i], osm);
        }
    }

    /*    std::pair    */
    template<typename A, typename B>
    void Serialization(const pair<A, B> &P, ofstream &osm) {
        Serialization(P.first, osm);
        Serialization(P.second, osm);
    }

    /*  std::vector   */
    template<typename Type>
    void Serialization(const vector<Type> &A, ofstream &osm) {
        int cnt = A.size();
        Serialization(cnt, osm);
        for(int i = 0; i < cnt; i++) {
            Serialization(A[i], osm);
        }
    }

    /*  std::list   */
    template<typename Type>
    void Serialization(const list<Type> &A, ofstream &osm) {
        int cnt = A.size();
        Serialization(cnt, osm);
        for(auto iter = A.begin(); iter != A.end(); iter++) {
            Serialization(*iter, osm);
        }
    }

    /*  std::set   */
    template<typename Type>
    void Serialization(const set<Type> &A, ofstream &osm) {
        int cnt = A.size();
        Serialization(cnt, osm);
        for(auto iter = A.begin(); iter != A.end(); iter++) {
            Serialization(*iter, osm);
        }
    }

    /*  std::map   */
    template<typename A, typename B>
    void Serialization(const map<A, B> &P, ofstream &osm) {
        int cnt = P.size();
        Serialization(cnt, osm);
        for(auto iter = P.begin(); iter != P.end(); iter++) {
            Serialization(*iter, osm);
        }
    }

    /*   UserDefinedType    */
    void Serialization(const UserDefinedType &Obj, ofstream &osm) {
        Serialization(Obj.idx, osm);
        Serialization(Obj.name, osm);
        Serialization(Obj.data, osm);
    }

    /*  unique_ptr   */
    template <typename Type>
    void Serialization(const unique_ptr<Type> &Obj, ofstream &osm) {
        Serialization(*Obj, osm);
    }

    /*  shared_ptr   */
    template <typename Type>
    void Serialization(const shared_ptr<Type> &Obj, ofstream &osm) {
        Serialization(*Obj, osm);
    }

    template<typename Type>
    typename std::enable_if<std::is_arithmetic<Type>::value>::type Deserialization(Type &x, ifstream &ism) {
        ism.read((char*)&x, sizeof(x));
    }

    /*   std::string    */
    void Deserialization(string &s, ifstream &ism){
        int cnt;
        Deserialization(cnt, ism);
        s.clear();
        char c;
        for(int i = 0; i < cnt; i++) {
            Deserialization(c, ism);
            s += c;
        }
    }

    template<typename A, typename B>
    void Deserialization(pair<A, B> &P, ifstream &ism) {
        Deserialization(P.first, ism);
        Deserialization(P.second, ism);
    }

    /*  std::vector   */
    template<typename Type>
    void Deserialization(vector<Type> &A, ifstream &ism) {
        int cnt ;
        A.clear();
        Deserialization(cnt, ism);
        Type t;
        for(int i = 0; i < cnt; i++) {
            Deserialization(t, ism);
            A.push_back((t));
        }
    }

    /*  std::list   */
    template<typename Type>
    void Deserialization(list<Type> &A, ifstream &ism) {
        int cnt;
        Deserialization(cnt, ism);
        A.clear();
        Type t;
        for(int i = 0; i < cnt; i++) {
            Deserialization(t, ism);
            A.push_back(t);
        }
    }

    /*  std::set   */
    template<typename Type>
    void Deserialization(set<Type> &A, ifstream &ism) {
        int cnt;
        Deserialization(cnt, ism);
        A.clear();
        Type t;
        for(int i = 0; i < cnt; i++) {
            Deserialization(t, ism);
            A.insert(t);
        }
    }

    /*  std::map   */
    template<typename A, typename B>
    void Deserialization(map<A, B> &P, ifstream &ism) {
        int cnt;
        Deserialization(cnt, ism);
        P.clear();
        pair<A, B> t;
        for(int i = 0; i < cnt; i++) {
            Deserialization(t, ism);
            P.insert(t);
        }
    }

    /*   UserDefinedType    */
    void Deserialization(UserDefinedType &Obj, ifstream &ism) {
        Deserialization(Obj.idx, ism);
        Deserialization(Obj.name, ism);
        Deserialization(Obj.data, ism);
    }

    /*  unique_ptr   */
    template <typename Type>
    void Deserialization(unique_ptr<Type> &Obj, ifstream &ism) {
        Type t;
        Deserialization(t, ism);
        Obj = unique_ptr<Type> (new Type(t));
    }

    /*  shared_ptr   */
    template <typename Type>
    void Deserialization(shared_ptr<Type> &Obj, ifstream &ism) {
        Type t;
        Deserialization(t, ism);
        Obj = shared_ptr<Type> (new Type(t));
    }

    template<typename Type>
    void serialize_binary(const Type &x, const char *name){
        ofstream osm(name, ios::out|ios::binary);
        if(!osm)
            throw exception();
        Serialization(x, osm);
        osm.close();
    }

    template <typename Type>
    void deserialize_binary(Type &x, const char *name) {
        ifstream ism(name, ios::in|ios::binary);
        if(!ism)
            throw exception();
        Deserialization(x, ism);
        ism.close();
    }
}

namespace XMLSerialization {

    XMLSer::XMLSer(const char *Path) : xmlPath(Path) {
        root = doc.NewElement("serialization");
        doc.InsertEndChild(root);
    }

    XMLSer::~XMLSer() {
        doc.SaveFile(xmlPath);
    }

    XMLElement *XMLSer::Root() {
        return root;
    }

    /*   std::is_arithmetic  */
    template<typename Type>
    typename std::enable_if<std::is_arithmetic<Type>::value>::type XMLSer::Serialization(
            const Type &obj, const char *NodeName, XMLElement *p) {
        XMLElement *Node = doc.NewElement(NodeName);
        Node->SetAttribute("val", obj);
        p->InsertEndChild(Node);  // insert new node into the xml tree
    };

    /*  std::string */
    void XMLSer::Serialization(
            const string &s, const char *NodeName, XMLElement *p) {
        XMLElement *Node = doc.NewElement(NodeName);
        Node->SetAttribute("val", s.c_str());
        p->InsertEndChild(Node);  // insert new node into the xml tree
    }

    /*  std::pair   */
    template<typename A, typename B>
    void XMLSer::Serialization(
            const pair<A, B> P, const char *NodeName, XMLElement *p) {
        XMLElement *Node = doc.NewElement(NodeName);
        Serialization(P.first, "first", Node);
        Serialization(P.second, "second", Node);
        p->InsertEndChild(Node);  // insert new node into the xml tree
    }

    /*  std::vector   */
    template<typename Type>
    void XMLSer::Serialization(
            const vector<Type> A, const char *NodeName, XMLElement *p) {
        XMLElement *Node = doc.NewElement(NodeName);
        int cnt = 0;
        for (auto t: A) {
            string s = "element_" + to_string(cnt++);
            Serialization(t, s.c_str(), Node);
        }
        p->InsertEndChild(Node);  // insert new node into the xml tree
    }

    /*  std::list   */
    template<typename Type>
    void XMLSer::Serialization(
            const list<Type> A, const char *NodeName, XMLElement *p) {
        XMLElement *Node = doc.NewElement(NodeName);
        int cnt = 0;
        for (auto t: A) {
            string s = "element_" + to_string(cnt++);
            Serialization(t, s.c_str(), Node);
        }
        p->InsertEndChild(Node);  // insert new node into the xml tree
    }

    /*  std::set   */
    template<typename Type>
    void XMLSer::Serialization(
            const set<Type> A, const char *NodeName, XMLElement *p) {
        XMLElement *Node = doc.NewElement(NodeName);
        int cnt = 0;
        for (auto t: A) {
            string s = "element_" + to_string(cnt++);
            Serialization(t, s.c_str(), Node);
        }
        p->InsertEndChild(Node);  // insert new node into the xml tree
    }

    /*  std::map    */
    template<typename A, typename B>
    void XMLSer::Serialization(
            const map<A, B> P, const char *NodeName, XMLElement *p) {
        XMLElement *Node = doc.NewElement(NodeName);
        int cnt = 0;
        for (auto t: P) {
            string s = "element_" + to_string(cnt++);
            Serialization(t, s.c_str(), Node);
        }
        p->InsertEndChild(Node);  // insert new node into the xml tree
    }

    /*   UserDefinedType    */
    void XMLSer::Serialization(
            const UserDefinedType &Obj, const char *NodeName, XMLElement *p) {
        XMLElement *Node = doc.NewElement(NodeName);
        Serialization(Obj.idx, "int", Node);
        Serialization(Obj.name, "string", Node);
        Serialization(Obj.data, "std::vector<double>", Node);

        p->InsertEndChild(Node);  // insert new node into the xml tree
    }

    /*  unique_ptr   */
    template <typename Type>
    void XMLSer::Serialization(
            const unique_ptr<Type> &Obj, const char *NodeName, XMLElement *p) {
        XMLElement *newNode = doc.NewElement(NodeName);
        p->InsertEndChild(newNode);
        Serialization(*Obj, "unique_ptr", newNode);
    }

    /*  shared_ptr   */
    template <typename Type>
    void XMLSer::Serialization(
            const shared_ptr<Type> &Obj, const char *NodeName, XMLElement *p) {
        XMLElement *newNode = doc.NewElement(NodeName);
        p->InsertEndChild(newNode);
        Serialization(*Obj, "shared_ptr", newNode);
    }

    template<typename T>
    void serialize_xml(const T &x, const char *name, const char *xmlPath) {
        XMLSer t(xmlPath);
        t.Serialization(x, name, t.Root());
    }
};

void test() {

    /*
        Case 1 Binary Serialization & Deserialization
    */
    cout<<"--------------Case 1 Binary Serialization & Deserialization-------------"<<endl;

    /*
        Test #1 std::is_arithmetic
        Result: Accepted
    */

    /*  int  */
    int i = 2333, j = 0;
    binarySerialization::serialize_binary(i, "./binary/binary_int.txt");
    binarySerialization::deserialize_binary(j, "./binary/binary_int.txt");
    if(i != j)   throw exception();

    /*  bool  */
    bool b = true, bo = false;
    binarySerialization::serialize_binary(b, "./binary/binary_bool.txt");
    binarySerialization::deserialize_binary(bo, "./binary/binary_bool.txt");
    if(b != bo)   throw exception();

    /*  float  */
    float f = true, fl = false;
    binarySerialization::serialize_binary(f, "./binary/binary_float.txt");
    binarySerialization::deserialize_binary(fl, "./binary/binary_float.txt");
    if(f != fl)   throw exception();

    cout << "Result: Accepted in Test #1 !  binary std::is_arithmetic" << endl;

    /*
        Test #2 C++ string type
        Result: Accepted
    */

    /*  std::string  */
    string str = "Hello world!", str2;
    binarySerialization::serialize_binary(str, "./binary/binary_std_string.txt");
    binarySerialization::deserialize_binary(str2, "./binary/binary_std_string.txt");
    if(str != str2)  throw exception();

    cout << "Result: Accepted in Test #2 !  binary std::string" << endl;

    /*
        Test #3 C++ STL Container
        Result: Accepted
    */

    /*  std::vector  */
    vector<int> vec = {1, 9, 1, 9, 0, 8, 1, 7}, vec2;
    binarySerialization::serialize_binary(vec, "./binary/binary_std_vector.txt");
    binarySerialization::deserialize_binary(vec2, "./binary/binary_std_vector.txt");
    if(vec != vec2)   throw exception();

    /*  std::pair  */
    pair<string, int> pr = make_pair("abc", 123), pr2;
    binarySerialization::serialize_binary(pr, "./binary/binary_std_pair.txt");
    binarySerialization::deserialize_binary(pr2, "./binary/binary_std_pair.txt");
    if(pr != pr2)   throw exception();

    /*  std::list  */
    list<int> li = {2, 4, 6, 8, 10}, li2;
    binarySerialization::serialize_binary(li, "./binary/binary_std_list.txt");
    binarySerialization::deserialize_binary(li2, "./binary/binary_std_list.txt");
    for(auto it1 = li.begin(), it2 = li2.begin(); it1 != li.end() && it2 != li2.end(); it1++, it2++)  {
        if(*it1 != *it2)    throw exception();
    }

    /*  std::set  */
    set<int> st  = {6, 7, 33, 9, 81, 31, 54}, st2;
    binarySerialization::serialize_binary(st, "./binary/binary_std_set.txt");
    binarySerialization::deserialize_binary(st2, "./binary/binary_std_set.txt");
    for(auto it1 = st.begin(), it2 = st2.begin(); it1 != st.end() && it2 != st2.end(); it1++, it2++)  {
        if(*it1 != *it2)    throw exception();
    }

    /*  std::map  */
    map<double, int> mp  = {pair<double, int>(1.1, 233), pair<double, int>(2.3, 369)}, mp2;
    binarySerialization::serialize_binary(mp, "./binary/binary_std_map.txt");
    binarySerialization::deserialize_binary(mp2, "./binary/binary_std_map.txt");
    for(auto it1 = mp.begin(), it2 = mp2.begin(); it1 != mp.end() && it2 != mp2.end(); it1++, it2++)  {
        if(*it1 != *it2)    throw exception();
    }
    cout << "Result: Accepted in Test #3 !  binary C++ STL Container" << endl;

    /*
        Test #4 Smart Pointers
        Result: Accepted
    */

    /*  unique_ptr  */
    unique_ptr<int> p(new int(2333)), p1;
    binarySerialization::serialize_binary(p, "./binary/binary_unique_ptr.txt");
    binarySerialization::deserialize_binary(p1, "./binary/binary_unique_ptr.txt");
    if(*p != *p1)   throw exception();

    /*  shared_ptr  */
    shared_ptr<int> sp = make_shared<int>(2333), sp1;
    binarySerialization::serialize_binary(sp, "./binary/binary_shared_ptr.txt");
    binarySerialization::deserialize_binary(sp1, "./binary/binary_shared_ptr.txt");
    if(*sp != *sp1)   throw exception();

    cout << "Result: Accepted in Test #4 !  binary Smart Pointers" << endl;

    /*
        Test #5 UserDefinedType
        Result: Accepted
    */

    UserDefinedType Usertype, Usertype2;
    Usertype.idx = 233;
    Usertype.name = "oopyyds";
    Usertype.data.push_back(1.19);
    binarySerialization::serialize_binary(Usertype, "./binary/binary_unique_ptr.txt");
    binarySerialization::deserialize_binary(Usertype2, "./binary/binary_unique_ptr.txt");
    if(Usertype.idx != Usertype2.idx || Usertype.name != Usertype2.name || Usertype.data != Usertype2.data )   throw exception();

    cout << "Result: Accepted in Test #5 !  binary UserDefinedType " << endl;

    /*
        Case 2 XML Serialization
    */
    cout<<"------------------Case 2 XML Serialization-------------------"<<endl;

    /*
        Test #1 std::is_arithmetic
        Result: Accepted
    */

    /*  int  */
    XMLSerialization::serialize_xml(i, "std::int", "./xml/xml_int.xml");

    /*  bool  */
    XMLSerialization::serialize_xml(b, "std::bool", "./xml/xml_bool.xml");

    /*  float  */
    XMLSerialization::serialize_xml(f, "float", "./xml/xml_float.xml");

    cout << "Result: Accepted in Test #1 !  xml std::is_arithmetic" << endl;

    /*
        Test #2 C++ string type
        Result: Accepted
    */

    /*  std::string  */
    XMLSerialization::serialize_xml(str, "std::string", "./xml/xml_std_string.xml");

    cout << "Result: Accepted in Test #2 !  xml std::string" << endl;

    /*
        Test #3 C++ STL Container
        Result: Accepted
    */

    /*  std::vector  */
    XMLSerialization::serialize_xml(vec, "std::vector", "./xml/xml_std_vector.xml");

    /*  std::pair  */
    XMLSerialization::serialize_xml(pr, "std::pair", "./xml/xml_std_pair.xml");

    /*  std::list  */
    XMLSerialization::serialize_xml(li, "std::list", "./xml/xml_std_list.xml");

    /*  std::set  */
    XMLSerialization::serialize_xml(st, "std::set", "./xml/xml_std_set.xml");

    /*  std::map  */
    XMLSerialization::serialize_xml(mp, "std::map", "./xml/xml_std_map.xml");

    cout << "Result: Accepted in Test #3 !  xml C++ STL Container" << endl;

    /*
        Test #4 Smart Pointers
        Result: Accepted
    */

    /*  unique_ptr  */
    XMLSerialization::serialize_xml(p, "unique_ptr", "./xml/xml_unique_ptr.xml");

    /*  shared_ptr  */
    XMLSerialization::serialize_xml(sp, "shared_ptr", "./xml/xml_shared_ptr.xml");

    cout << "Result: Accepted in Test #4 !  xml Smart Pointers" << endl;

    /*
        Test #5 UserDefinedType
        Result: Accepted
    */

    XMLSerialization::serialize_xml(p, "unique_ptr", "./xml/xml_unique_ptr.xml");

    cout << "Result: Accepted in Test #5 !  xml UserDefinedType " << endl;

}

int main(){

    test();
    testbase64();

    return 0;
}