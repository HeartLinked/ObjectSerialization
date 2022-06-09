#ifndef DEMO2_XML_H
#define DEMO2_XML_H

#include <bits/stdc++.h>
#include "tinyxml2.h"
using namespace tinyxml2;
using namespace std;

struct UserDefinedType;

namespace XMLSerialization {

    class XMLSer {
    private:
        XMLDocument doc;
        XMLElement *root;
        const char *xmlPath;
    public:
        XMLSer(const char *Path) ;

        ~XMLSer() ;

        XMLElement *Root() ;

        /*   std::is_arithmetic  */
        template<typename Type>
        typename std::enable_if<std::is_arithmetic<Type>::value>::type Serialization(
                const Type &obj, const char *NodeName, XMLElement *p) ;

        /*  std::string */
        void Serialization(
                const string &s, const char *NodeName, XMLElement *p) ;

        /*  std::pair   */
        template<typename A, typename B>
        void Serialization(
                const pair<A, B> P, const char *NodeName, XMLElement *p) ;

        /*  std::vector   */
        template<typename Type>
        void Serialization(const vector<Type> A, const char *NodeName, XMLElement *p) ;

        /*  std::list   */
        template<typename Type>
        void Serialization(const list<Type> A, const char *NodeName, XMLElement *p) ;

        /*  std::set   */
        template<typename Type>
        void Serialization(
                const set<Type> A, const char *NodeName, XMLElement *p) ;

        /*  std::map   */
        template<typename A, typename B>
        void Serialization(
                const map<A, B> P, const char *NodeName, XMLElement *p) ;

        /*   UserDefinedType    */
        void Serialization(
                const UserDefinedType &Obj, const char *NodeName, XMLElement *p) ;

        /*  unique_ptr   */
        template <typename Type>
        void Serialization(
                const unique_ptr<Type> &Obj, const char *NodeName, XMLElement *p) ;

        /*  shared_ptr   */
        template <typename Type>
        void Serialization(
                const shared_ptr<Type> &Obj, const char *NodeName, XMLElement *p) ;
    };

    template<typename T>
    void serialize_xml(const T &x, const char *name, const char *xmlPath) ;

}

struct UserDefinedType {
    int idx;
    std::string name;
    std::vector<double> data;
};


#endif
