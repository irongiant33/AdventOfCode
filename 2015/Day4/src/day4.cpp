// to compile you must link ssl and crypto: -lssl -lcrypto

#include <openssl/evp.h> // need to sudo apt-get install libssl-dev
#include <iostream>
#include <iomanip>
#include <string.h>
#include <string>
#include <sstream>

using namespace std;

unsigned int calculate_md5(string input, int num_zeros)
{
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;
    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len, i;
    md = EVP_md5();
    unsigned int digit = 0;
    unsigned char flag = 1;
    string match(num_zeros, '0');
    while(flag != 0)
    {
        const char * hash_input = (input + to_string(digit)).c_str();
        mdctx = EVP_MD_CTX_new(); //for some reason, it matters that this is reinitialized in each loop. Does not work if you just try to have the digestupdate and digestfinal function here.
        EVP_DigestInit_ex(mdctx, md, NULL);
        EVP_DigestUpdate(mdctx, hash_input, strlen(hash_input));
        EVP_DigestFinal_ex(mdctx, md_value, &md_len);
        stringstream digest;
        for(unsigned int i = 0; i < md_len; i++)
        {
            digest << hex << setw(2) << setfill('0') << (int) md_value[i];
        }
        if(digest.str().substr(0, num_zeros) == match)
        {
            flag = 0;
        }
        else
        {
            digit += 1;
        }
        EVP_MD_CTX_free(mdctx);
    }
    cout << "Digest is ";
    for(i = 0 ; i < md_len; i++)
    {
        cout << hex << setw(2) << setfill('0') << (int) md_value[i];
    }
    cout << endl;
    return digit;
}

int main(int argc, char * argv[])
{
    if(argc != 2)
    {
        cout << "Usage: ./day4 hashval\n";
        exit(1);
    }
    string hash_input = string(argv[1]);
    unsigned int d = calculate_md5(hash_input, 5);
    cout << "Answer to part 1 is " << dec << d << endl;
    d = calculate_md5(hash_input, 6);
    cout << "Answer to part 2 is " << dec << d << endl;
    return 0 ;
}
