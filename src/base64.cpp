#include "base64.h"

namespace base64 {

    std::string get_base64_chars() {
        static std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                          "abcdefghijklmnopqrstuvwxyz"
                                          "0123456789+/";
        return base64_chars;
    }

    std::string to_base64(std::string const &data) {
        int counter = 0;
        uint32_t bit_stream = 0;
        const std::string base64_chars = get_base64_chars();
        std::string encoded;
        int offset = 0;
        for (unsigned char c : data) {
            auto num_val = static_cast<unsigned int>(c);
            offset = 16 - counter % 3 * 8;
            bit_stream += num_val << offset;
            if (offset == 16) {
                encoded += base64_chars.at(bit_stream >> 18 & 0x3f);
            }
            if (offset == 8) {
                encoded += base64_chars.at(bit_stream >> 12 & 0x3f);
            }
            if (offset == 0 && counter != 3) {
                encoded += base64_chars.at(bit_stream >> 6 & 0x3f);
                encoded += base64_chars.at(bit_stream & 0x3f);
                bit_stream = 0;
            }
            counter++;
        }
        if (offset == 16) {
            encoded += base64_chars.at(bit_stream >> 12 & 0x3f);
            encoded += "==";
        }
        if (offset == 8) {
            encoded += base64_chars.at(bit_stream >> 6 & 0x3f);
            encoded += '=';
        }
        return encoded;
    }

    std::string from_base64(std::string const &data) {
        int counter = 0;
        uint32_t bit_stream = 0;
        std::string decoded;
        int offset = 0;
        const std::string base64_chars = get_base64_chars();
        for (unsigned char c : data) {
            auto num_val = base64_chars.find(c);
            if (num_val != std::string::npos) {
                offset = 18 - counter % 4 * 6;
                bit_stream += num_val << offset;
                if (offset == 12) {
                    decoded += static_cast<char>(bit_stream >> 16 & 0xff);
                }
                if (offset == 6) {
                    decoded += static_cast<char>(bit_stream >> 8 & 0xff);
                }
                if (offset == 0 && counter != 4) {
                    decoded += static_cast<char>(bit_stream & 0xff);
                    bit_stream = 0;
                }
            } else if (c != '=') {
                return std::string();
            }
            counter++;
        }
        return decoded;
    }

    void encode(string fromfile, string tofile) {
            string line;
            ifstream fin(fromfile);
            ofstream fout(tofile);
            while(getline(fin, line)) {
                line = to_base64(line);
                fout << line << endl;
            }
            fin.close();
            fout.close();
    }

    void decode(string fromfile, string tofile) {
        string line;
        ifstream fin(fromfile);
        ofstream fout(tofile);
        while(getline(fin, line)) {
            line = from_base64(line);
            fout << line << endl;
        }
        fin.close();
        fout.close();
    }
}


void testbase64(){

    /*
    Case 3 Base64 mode of XML
    Result: Accepted
    */

    cout<<"--------------Case 3 Base64 mode of XML------------------"<<endl;

    base64::encode("./xml/xml_bool.xml", "./base64/xml_bool_base64.txt");
    base64::decode("./base64/xml_bool_base64.txt", "./base64/de_xml_bool_base64.xml");

    base64::encode("./xml/xml_int.xml", "./base64/xml_int_base64.txt");
    base64::decode("./base64/xml_int_base64.txt", "./base64/de_xml_int_base64.xml");

    base64::encode("./xml/xml_float.xml", "./base64/xml_float_base64.txt");
    base64::decode("./base64/xml_float_base64.txt", "./base64/de_xml_float_base64.xml");

    base64::encode("./xml/xml_std_vector.xml", "./base64/xml_std_vector_base64.txt");
    base64::decode("./base64/xml_std_vector_base64.txt", "./base64/de_std_vector_base64.xml");

    base64::encode("./xml/xml_std_pair.xml", "./base64/xml_std_pair_base64.txt");
    base64::decode("./base64/xml_std_pair_base64.txt", "./base64/de_xml_std_pair_base64.xml");

    base64::encode("./xml/xml_std_set.xml", "./base64/xml_std_set_base64.txt");
    base64::decode("./base64/xml_std_set_base64.txt", "./base64/de_xml_std_set_base64.xml");

    base64::encode("./xml/xml_std_string.xml", "./base64/xml_std_string_base64.txt");
    base64::decode("./base64/xml_std_string_base64.txt", "./base64/de_xml_std_string_base64.xml");

    base64::encode("./xml/xml_std_map.xml", "./base64/xml_std_map_base64.txt");
    base64::decode("./base64/xml_std_map_base64.txt", "./base64/de_xml_std_map_base64.xml");

    base64::encode("./xml/xml_std_list.xml", "./base64/xml_std_list_base64.txt");
    base64::decode("./base64/xml_std_list_base64.txt", "./base64/de_xml_std_list_base64.xml");

    base64::encode("./xml/xml_shared_ptr.xml", "./base64/xml_shared_ptr_base64.txt");
    base64::decode("./base64/xml_shared_ptr_base64.txt", "./base64/de_xml_shared_ptr_base64.xml");

    base64::encode("./xml/xml_unique_ptr.xml", "./base64/xml_unique_ptr_base64.txt");
    base64::decode("./base64/xml_unique_ptr_base64.txt", "./base64/de_xml_unique_ptr_base64.xml");

    cout << "Result: Accepted in Test #1 !  Base64 mode of XML" << endl;
}