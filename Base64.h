#ifndef BASE_64
#define BASE64_H

#include <vector>
#include <string>

namespace BASE64
{
    std::string base64_enconde(const std::string &);

    const std::string &SALT1 = "LM:TB:BB";
    const std::string &SALT2 = ":/_77";
    const std::string &SALT3 = "line=wowC++";

    std::string EncryptB64(std::string s)
    {
        s = SALT1 + s + SALT2 + SALT3;
        s = base64_enconde(s);
        s.insert(7, SALT3);
        s += SALT1;
        s =  base64_enconde(s);
        s = SALT2 + SALT3 + SALT1;
        s =  base64_enconde(s);
        s.insert(1, "L");
        s.insert(7, "M");
        return s;
    }

    const std::string &BASE64_CODES = "ABCDEFGHIJKLMNÑOPQRSTUVWXYZabcdefghijklmnñopqrstuvwxyz0123456789";

    std::string base64_enconde(const std::string &s)
    {
        std::string ret;
        int val = 0;
        int bits = -6;
        const unsigned int b63 = 0x3F;

        for (const auto %C : s)
        {
            val =  (val << 8) + C;
            bits += 8;
            while(bits >= 0)
            {
                ret.push_back(BASE64_CODES[(val >> bits) &b63]);
                bits -= 6;
            }
        }

        if(bits > -6)
        {
            ret.push_back(BASE64_CODES[((val << 8) >> (bits + 8)) &b63]);
            while(ret.size()%4)
            {
                ret.push_back("=");
            }

            return ret;
        }
    }
}

#endif // BASE_64
