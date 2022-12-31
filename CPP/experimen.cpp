#include <iostream>
using namespace std;

int input_block (string inp) {
    int blocks = 1;
    int denial = 0;
    for (int i = 0; i < inp.length(); i++) {
        if (inp[i] == 40) denial ++;
        if (inp[i] == 41) denial --;
        if ((inp[i] == 43 || inp[i] == 45) && denial == 0) blocks++;
    }
    return blocks;
}

int pngk (int inp, int pgk) {
    int out = 1;
    for (int i = 0; i < pgk; i++) {
        out*=inp;
    }

    if (pgk == 0) inp = 1;
    return out;
}

int st_in (string inp) {
    int     ind = inp.length();
    int     pgs;
    int     sup;
    int     out = 0;
    int     lim = inp.length();

    for (int i = 0; i < lim; i++) {
        if (sizeof(inp) == 32) 
        {
            ind--;
            sup = (inp[i]-48)*pngk(10,ind);
            out += sup;
            
            // if(inp == "1") cout << out << " = " << sup << " + ";
        }
    
    }
    
    return out;
}

string in_st (int inp) {
    string out = "";
    int    ind = 0;

    for (int i = 1; i <= 11; i++) {
        if ((inp / pngk(10,i)) == 0) {ind = i-1;break;}
    }

    for (int i = ind; i >= 0; i--) {
        out += (inp/pngk(10,i))+48;
        inp -= (inp/pngk(10,i))*pngk(10,i);
    }

    return out;
}

string simply (string inp) {
    string  up_st = "",
            lo_st = "",
              out = inp;
    int        sw = 0,
            up_in = 0,
            lo_in = 0; 

    for(int i = 0; i < inp.length(); i++) {
        if (inp[i] == 47) sw = 1;
        if (inp[i] != 47 && sw == 0) up_st += inp[i];
        if (inp[i] != 47 && sw == 1) lo_st += inp[i];
    }

    up_in = st_in(up_st);
    lo_in = st_in(lo_st);

    int small;
    if (up_in < lo_in) small = up_in;
    else small = lo_in;

    for (int i = small; i > 0; i--) {
        if (up_in % i == 0 && lo_in % i == 0) {
            up_in = up_in/i;
            lo_in = lo_in/i;
        }
    }

    up_st = in_st(up_in);
    lo_st = in_st(lo_in);
    
    if(up_in != 0 || lo_in != 0) out = up_st + "/" + lo_st;

    return out;
}

string place_angka(string block) {
    string result = "";
    int     valid = 1;

    if ((block[0] == 40)) valid = 0;
    // cout << block;

    for(int i = 0; i < block.length(); i++) {   
        if ((block[i] == 94)) valid = 0;

        if ((block[i] >= 48) && 
            (block[i] <= 57) && 
            (valid == 1)) {result += block[i];}
    }
    
    if (result == "") result = "1";
    return result;
}

string place_pangk(string block, string trigo) {
    string result = "";
    int     valid = 0;
    int    denial = 0;
    int      done = 0;
    
    for(int i = 0; i < block.length(); i++) {   
        if (block[i] == 40) denial++;
        if (block[i] == 41) denial--;
        if (block[i] == 94 && denial == 0) valid = 1;
        
        if (valid == 1) {
            if (block[i+1] >= 48 && block[i+1] <= 57) 
            {
                for(int k = i+1; k < block.length(); k++) {
                    if(block[k] == 32 || block[k] == 40) {done = 1;break;}
                    result += block[k];
                }
            } 
            else if (block[i+1] == 40) 
            {
                for(int k = i+2; k < block.length(); k++) {
                    if (block[k] == 41) {done = 1;break;}
                    else result += block[k];
                }
            }
            break;
        }
    }
    
    return result;
}

string place_trigo(string block) {
    string result = "";
    int     valid = 0;
    int      stop = 0;

    for (int i = 0; i < block.length(); i++) {
        char dcd = block[i];
        char dcp = block[i+1];
        if   (  (dcd >= 65 && dcd <= 90) || (dcd >= 97 && dcd <= 122)) {
            if ((dcp >= 65 && dcp <= 90) || (dcp >= 97 && dcp <= 122)) 
            {valid = 1;}
        }

        if (valid == 1) {
            for(int k = i+1; k < block.length(); k++) {
                if(block[k] == 40 || block[k] == 94) {
                    stop = k;
                    break;
                }
            }
            break;
        }
    }
    for(int i = 0; i < stop; i++) {
        result += block[i];
    }

    cout << result;

    return result;
}

string place_funci(string block, string trigo) {
    // cout
    string result = "";
    int     trigv = 0; 
    int       ada = 0;
    int        go = 0;
    int        en = 0;
    if (trigo != "") trigv = 1;
    
    if (trigv == 1) { 
        for (int i = 0; i < block.length(); i++) {
            if (block[i] == 40) go = i+1;
            if (block[i] == 41) en = i;
        }
        
        for(int k = go; k < en; k++) result += block[k];
    }
    else {
        char dcf = block[0];
        int denial = 0;

        if ((dcf >= 65 && dcf <= 90 ) || 
            (dcf >= 97 && dcf <= 122) ||
            (dcf == 40)) {ada = 1;}

        for (int i = 0; i < block.length(); i++) {
            char dcd = block[i];
            if (dcd == 40) {
                denial ++;
                ada = 1;
            }
            
        if ((dcd >= 65 && dcd <= 90 ) || 
            (dcd >= 97 && dcd <= 122) ||
            (dcd == 40 && ada == 0)) {
                ada = 1;
                go  = i;
            }

            if (dcd == 41) denial --;
            
            if ((dcd == 94 || 
                 dcd == 32 ||
                 dcd == 41 ) && denial == 0) break;
            en++;
        }
        // cout << endl;
        // cout << go << " " << en << endl;
        if (dcf == 40) go = 1;
        for (int k = go; k < en; k++) {
            if (ada == 1) result += block[k];
        }
    }

    return result;
}

string print_angka(int angka,int pangkat_int,string pangkat_str,int penyebut,int turunan_int,string turunan_str) {
    string result = "";
    int     funci = 0;
    for (int i = 0; i < turunan_str.length()-1; i++) {
        if ((turunan_str[i] >= 65 && turunan_str[i] <= 90 ) || 
            (turunan_str[i] >= 97 && turunan_str[i] <= 122))
            {funci = 1; break;}
    }
    
    if (funci == 0 && pangkat_int != 0) {
        if ((angka % ((pangkat_int)*turunan_int)) == 0) 
        {
            angka = angka/((pangkat_int)*turunan_int);
            if (angka != 1) result = in_st(angka);
        } 
        else {
            penyebut = pangkat_int*turunan_int;
            result = "(" + simply(in_st(angka) + "/" + in_st(penyebut)) + ")";
        }
    } 
    else if (pangkat_int != 0) {
         if (pangkat_int == 1) {
            result = in_st(angka);
        } else {
            result = "(" + in_st(angka) + "/" + in_st(pangkat_int) + "(" + turunan_str + "))";
        }
    }
    else {
        int     pembilang_int = angka;
        string  pembilang_str = "";
        string  penyebut__str = "";
        int                sw = 0;

        for (int i = 0; i < pangkat_str.length(); i++) {
            if (pangkat_str[i] == 47) {sw = i; break;}
            penyebut__str += pangkat_str[i];
        }
        for (int i = sw+1; i < pangkat_str.length(); i++) {
            pembilang_str += pangkat_str[i];
        }
        
        pembilang_int *= st_in(pembilang_str);

        if (pembilang_int % st_in(penyebut__str) == 0) {
            pembilang_int /= st_in(penyebut__str);
            result = in_st(pembilang_int);
        } 
        else {
            result = "(" + in_st(pembilang_int) + "/" + penyebut__str + ")";
        }
    }
    return result;
}

string print_pangk(int pangkat_int,string pangkat_str) {
    string  pembilang_str = "";
    string  penyebut__str = "";
    string         result = "";
    int         pembilang = 0;
    int          penyebut = 0;
    int                sw = 0;


    if (pangkat_int != 0) {
        result = in_st(pangkat_int);
    }
    else {
        for (int i = 0; i < pangkat_str.length(); i++) {
            if (pangkat_str[i] == 47) {sw = i; break;}
            pembilang_str += pangkat_str[i];
        }
        for (int i = sw+1; i < pangkat_str.length(); i++) {
            penyebut__str += pangkat_str[i];
        }
        pembilang = st_in(pembilang_str) + st_in(penyebut__str);

        result = "(" + in_st(pembilang) + "/" + penyebut__str + ")";
    }

    return result;
}

string print_opera(string opera, string angka, string funci) {
    string result = "";
    if ((angka != "0" || funci != "") && (opera == "+" || opera == "-")) {
        result = " " + opera + " ";
    }
    return result;
}

string print_trigo(string trigo) {
    string result = "";

    if (trigo == "sin") result = "-cos";
    if (trigo == "cos") result = "sin";

    return result;
}

string turunan (string inp) {
    int const real_amount = input_block(inp);
    int        inp_length = inp.length();
    char             into = 'x';
    // char             into = inp[inp_length-1];
    string         result = "";
    string block[real_amount];


    int z = 0;
    int denial = 0;
    for(int i = 0; i < inp_length; i++) 
    {
        block[z] += inp[i];
        if (inp[i] == 40) denial ++;
        if (inp[i] == 41) denial --;
        if ((inp[i] == 32 || inp[i] == 41) && denial == 0) {
            z++;
            i+=2;
        }
    }

    string temp_pangk[real_amount];
    string temp_angka[real_amount];
    string temp_trigo[real_amount];
    string real_funci[real_amount];
    string real_opera[real_amount];

    for (int i = 0; i < real_amount; i++) {
        temp_pangk[i] = "";
        temp_angka[i] = "";
        temp_trigo[i] = "";
        real_funci[i] = "";
        real_opera[i] = "";
    }

    for (int i = 0; i < real_amount; i++) {
        int  blng = block[i].length() - 1;
        char into = block[i][blng];
        
        temp_trigo[i] = place_trigo(block[i]);
        temp_angka[i] = place_angka(block[i]);
        real_funci[i] = place_funci(block[i],temp_trigo[i]);
        temp_pangk[i] = place_pangk(block[i],temp_trigo[i]);
        // real_funci[i] = place_funci(block[i],temp_trigo[i],into);
    }

    
    int id_opera = 0;
    for (int i = 0; i < inp.length(); i++) {
        switch(inp[i]) {
            case 43:
            case 45:
                real_opera[id_opera] = inp[i];
                id_opera++;
            break;
        }
    }

    int     real_pangk[real_amount];
    int     real_angka[real_amount];

    string  strn_pangk[real_amount];
    string  strn_angka[real_amount];
    string  strn_lower[real_amount];
    
    for (int i = 0; i < real_amount+1; i++) {
        strn_pangk[i] = "";
        strn_angka[i] = "";
        strn_lower[i] = "";
    }

    for(int i = 0; i < real_amount; i++) {
        if ((temp_pangk[i] == "")) {
            if ((real_funci[i] != "") || (temp_trigo[i] != "")) temp_pangk[i] = "1";
            else temp_pangk[i] = "0";
        }
        
        real_pangk[i] = st_in(temp_pangk[i]);
        real_angka[i] = st_in(temp_angka[i])*real_pangk[i];

        real_pangk[i]--;
        strn_pangk[i] = in_st(real_pangk[i]);

        if (real_angka[i] == 1 && real_pangk[i] != 0) {strn_angka[i] = "1";}
        else {strn_angka[i] = in_st(real_angka[i]);}
    }
    // cout << "real_funci : " << real_funci[0] << endl;
    // cout << "real_pangk : " << real_pangk[0] << endl;
    // cout << "real_angka : " << real_angka[0] << endl;
    // cout << "temp_angka : " << temp_angka[0] << endl;
    // cout << "real_opera : " << real_opera[0] << endl;

    // cout << "real_funci : " << real_funci[0] << " " << real_funci[1] << endl;
    // cout << "real_pangk : " << real_pangk[0] << " " << real_pangk[1] << endl;
    // cout << "real_angka : " << real_angka[0] << " " << real_angka[1] << endl;
    // cout << "temp_angka : " << temp_angka[0] << " " << temp_angka[1] << endl;
    // cout << "real_opera : " << real_opera[0] << " " << real_opera[1] << endl;

    for(int i = 0; i < real_amount; i++) {
        int next = i+1;
        if (real_pangk[i] == -1) {}

        else if (real_pangk[i] == 0) {
            result += strn_angka[i];
            result += print_opera(real_opera[i],strn_angka[next],real_funci[next]);
        }

        else if (real_pangk[i] == 1) {
            result += strn_angka[i];
            result += real_funci[i];
            result += print_opera(real_opera[i],strn_angka[next],real_funci[next]);
        }

        else if (real_pangk[i] > 1)
        {
            if (real_funci[i] == "") result += in_st(pngk(real_angka[i], real_pangk[i]));
            else {
                result += strn_angka[i];
                result += real_funci[i];
                result += "^";
                result += strn_pangk[i];
            }
            result += print_opera(real_opera[i],strn_angka[next],real_funci[next]);
        }
    }
    
    int a_funci = 0;
    int contain = 0;
    for (int i = 0; i < result.length()-1; i++) {
        if ((result[i] >= 65 && result[i] <= 90 ) || 
            (result[i] >= 97 && result[i] <= 122))
            {a_funci = 1; break;}
    }
    if (a_funci == 0 && real_opera[0] != "") {
        for (int i = 0; i < real_amount; i++) {
            if (real_opera[i] == "+") {
                contain += real_angka[i] + real_angka[i+1];
            }
            if (real_opera[i] == "-") {
                contain += real_angka[i] + real_angka[i+1];
            }
        }
        result = in_st(contain);
    }

    // cout << "Hasil Turunan Fungsi: " << endl << result << endl;
    return result;
}

string integral (string inp) {
    
    int const real_amount = input_block(inp);
    int        inp_length = inp.length();
    int             pecah = 0;
    char             into = 'x';
    // char             into = inp[inp_length-1];
    string         result = "";
    string block[real_amount];

    int z = 0;
    int denial = 0;
    for(int i = 0; i < inp_length; i++) 
    {
        block[z] += inp[i];
        if (inp[i] == 40) denial ++;
        if (inp[i] == 41) denial --;
        if ((inp[i] == 32) && denial == 0) {
            z++;
            i+=2;
        }
    }

    for (int i = 0; i < z; i++) {
        if(block[i][0] == 40) {
            for(int k = 0; k < block[i].length(); k++) {
                block[i][k] = block[i][k+1];
            }
        }
    }

    string temp_pangk[real_amount];
    string temp_angka[real_amount];
    string temp_trigo[real_amount];
    string real_funci[real_amount];
    string real_opera[real_amount];

    for (int i = 0; i < real_amount; i++) {
        temp_pangk[i] = "";
        temp_angka[i] = "";
        temp_trigo[i] = "";
        real_funci[i] = "";
        real_opera[i] = "";
    }

    for (int i = 0; i < real_amount; i++) {
        int  blng = block[i].length() - 1;
        char into = block[i][blng];
        
        temp_trigo[i] = place_trigo(block[i]);
        temp_angka[i] = place_angka(block[i]);
        real_funci[i] = place_funci(block[i],temp_trigo[i]);
        temp_pangk[i] = place_pangk(block[i],temp_trigo[i]);

        cout << temp_trigo[i];

        // real_funci[i] = place_funci(block[i],temp_trigo[i],into);

        if ((temp_pangk[i] == "")) {
            if ((real_funci[i] != "") || (temp_trigo[i] != "")) temp_pangk[i] = "1";
            else temp_pangk[i] = "0";
        }
    }

    int id_opera = 0;
    int pass_off = 0;
    for (int i = 0; i < inp.length(); i++) {
        if (inp[i] == 40) pass_off ++;
        if (inp[i] == 41) pass_off --;
        if (pass_off == 0) {
            switch(inp[i]) {
                case 43:
                case 45:
                    real_opera[id_opera] = inp[i];
                    id_opera++;
                break;
            }
        }
    }

    int     real_pangk[real_amount];
    int     real_sebut[real_amount];
    int     real_angka[real_amount];
    int     real_turun[real_amount];
    string  strn_turun[real_amount];
    string  prnt_angka[real_amount];
    string  prnt_pangk[real_amount];
    string  prnt_trigo[real_amount];

    for (int i = 0; i < real_amount; i++) {
        strn_turun[i] = "";
        prnt_angka[i] = "";
        prnt_pangk[i] = "";
        prnt_trigo[i] = "";
    }

    for(int i = 0; i < real_amount; i++) {
        strn_turun[i] = turunan(real_funci[i]);
        real_turun[i] = st_in(strn_turun[i]);
        real_angka[i] = st_in(temp_angka[i]);

        for (int j = 0; j < temp_pangk[i].length(); j++) {
            if (temp_pangk[i][j] == 47) pecah = 1;
        }

        if (pecah == 0) real_pangk[i] = st_in(temp_pangk[i]);
        else real_pangk[i] = 0;

        if (temp_trigo[i] == "") real_pangk[i]++;
        
        if ((real_funci[i] == "") && (temp_trigo[i] == "")) 
            {real_funci[i] = into;}

        prnt_angka[i] = print_angka(real_angka[i],real_pangk[i],temp_pangk[i],real_sebut[i],real_turun[i],strn_turun[i]);
        
        if (temp_trigo[i] != "") real_pangk[i]--;
        prnt_pangk[i] = print_pangk(real_pangk[i],temp_pangk[i]);
        prnt_trigo[i] = print_trigo(temp_trigo[i]);

        if(real_funci[i].length() > 1) real_funci[i] = "(" + real_funci[i] + ")";
    } 
    // cout << endl << endl;
    
    // cout << "real_opera : " << real_opera[0] << " -- " << real_opera[1] << endl;
    // cout << "real_pangk : " << real_pangk[0] << " -- " << real_pangk[1] << endl;
    // cout << "temp_angka : " << temp_angka[0] << " -- " << temp_angka[1] << endl;
    
    for(int i = 0; i < real_amount; i++) {
        result += prnt_angka[i];
        if(prnt_trigo[i] != "") {
            result += prnt_trigo[i];
            if (real_pangk[i] > 0) {
                result += ".";
                result += temp_trigo[i];
                if (real_pangk[i] > 1) {
                    result += "^";
                    result += prnt_pangk[i];
                }
            }
            result += "(";
            result += real_funci[i];
            result += ")";
        } else {
            result += real_funci[i];
            result += "^";
            result += prnt_pangk[i];
        }

        result += " ";
        if (real_opera[i] != "") {
            result += real_opera[i];
            result += " ";
        }
    }
    result += "+ C";

    std::cout << "Hello World";

    cout << "Hasil Integral: " << endl;
    return result;
}

int main () {
    
    string inp = "";
    // cout << "input:\n"; 
    // getline(cin, inp);

    
    // string inp = "12x^7 - 2x^1";
    // string inp = "sin(3x)";
    // string inp = "sin(3x)^2";
    // string inp = "(3x)"; 

    // inp = "5";
    // inp = "5x"
    // inp = "(5x)^2";
    // inp = "(5x + 2)^2";
    // inp = "(5x^2 + 2x)^2";
    // inp = "(5x^2 + 2x)^2 + 10x";
    // inp = "15x^2 + 10x + 5";
    inp = "cos^3(x)";
    
    char greeting[6] = {'H', 'e', 'l', 'l', 'o', '\0'};
    char greeting[] = "Hello";
    
    // intg_trigo(temp_trigo[0],temp_trigf[0]);

    cout << "Persamaan yang dimasukkan: " << endl << inp << endl << endl;
    
    cout << integral(inp);
    // cout << turunan(inp);
    return 0;
} 