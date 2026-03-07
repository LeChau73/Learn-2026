#include<iostream>
#include<vector>
using namespace std;

//TODO: Đọc lại code
class Solution {
public:

    string encode(vector<string>& strs) {
        string encode_str;
        string new_str;
        for(auto& s : strs) {
            encode_str += '#' + to_string(s.length()) + '_';
            new_str = "";
            for(char c : s) {
                new_str += c - 1;
            }
            encode_str += new_str;
        }
        return encode_str;
    }

    vector<string> decode(string s) {
        vector<string> strs;
        string str_decode;
        for(int i = 0; i < s.length(); i++) {
            if(s[i] == '#') {
                string size = get_size( s.substr(i+1), '_' );
                int number_character = size.length();
                int stoi_s = stoi(size);
                int length = i + number_character + 2 + stoi_s; //tại chỗ ra # cộng với size của string encode + _
                int j = i + number_character + 2; //TODO: phần index nữa là xong
                str_decode = "";
                for(; j < length; j++) {
                    str_decode += s[j] + 1;
                }
                strs.push_back(str_decode);
                i = j - 1;
            }
        }
        return strs;
    }

    string get_size(const string& s, char delimit) {
        size_t pos = s.find(delimit); //Trả về lần đầu gặp
        if(pos != string::npos) {
            return s.substr(0, pos);
        }
        return s;
    }
};



int main() {
    Solution so;
    vector<string> vt {"!@#$%^&*()", "would"};
    string enc = so.encode(vt);
    cout << enc << endl;
    vector<string> new_vt =  so.decode(enc);
    for (size_t i = 0; i < vt.size(); i++)
    {
        cout << new_vt[i] << " ";
    }
    
    

    return 0;
}