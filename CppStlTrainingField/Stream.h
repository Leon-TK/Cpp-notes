#pragma once
#include <string>

namespace LTK {

    //byte buffer, char buffer, memory buffer, file buffer
    template<typename Buffer>
    class Stream {
        Buffer m_buffer;
            public:
        void operator<<(const Buffer& buffer) { m_buffer += buffer; };
        const Buffer& Get() { return m_buffer; };
    };

    /* template<>
    class Stream<std::string> {
        std::string m_buffer; //TODO: seg fault
            public:
        void operator<<(const std::string& str) { m_buffer.append(str); } ;
        const std::string& Get() { return m_buffer; };
    }; */

    using StringStream = Stream<std::string>;

    class TestClass_1 {
        //friend Stream& operator<<(Stream&, TestClass_1&);

        std::string m_str = "TestClass_1";

        public:
        StringStream& operator>>(StringStream& stream) {
            stream << m_str;
            return stream;
        };
    };
}
// this is global "<<", so it takes left and right variable
// left << right
LTK::StringStream& operator<<(LTK::StringStream& stream, LTK::TestClass_1& cls){ 
    return cls >> stream;
};
