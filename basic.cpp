#include <iostream>
using namespace std;

int input_block (string inp) {
    int blocks = 1;
    for (int i = 0; i < inp.length(); i++) {
        if (inp[i] == 43 || inp[i] == 45) blocks++;
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
    
    int ind = inp.length();
    int tmp;
    int out = 0;

    for (int i = 0; i < inp.length(); i++) {
        if (sizeof(inp) == 32)
        {
            ind--;
            tmp = (inp[i]-48)*pngk(10,ind);
            out += tmp;
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
    
    
    for(int i = 0; i < block.length(); i++) {   
        if ((block[i] == 94)) valid = 0;

        if ((block[i] >= 48) && 
            (block[i] <= 57) && 
            (valid == 1)) {result += block[i];}
    }
    
    if (result == "") result = "1";
    return result;
}

string place_pangk(string block) {
    string result = "";
    int     valid = 0;
    
    for(int i = 0; i < block.length(); i++) {   
        if (block[i] == 94) valid = 1;
        
        if (block[i+1] >= 48 && block[i+1] <= 57 && valid == 1) 
        {
            for(int k = i+1; k < block.length(); k++) {
                result += block[k];
            }
        }
    }
    
    if (result == "") result = "1";
    return result;
}

string place_trigo(string block) {
    string result = "";
    int     valid = 0;

    for (int i = 0; i < block.length(); i++) {
        char dcd = block[i];
        char dcp = block[i+1];
        if   (  (dcd >= 65 && dcd <= 90) || (dcd >= 97 && dcd <= 122)) {
            if ((dcp >= 65 && dcp <= 90) || (dcp >= 97 && dcp <= 122)) 
            {valid = 1;}
        }

        if (valid == 1) {
            int stop;
            int stip;
            for(int k = i+1; k < block.length(); k++) {
                if(block[k] == 40) {
                    stop = k;
                    break;
                }
            }
            for(int k=i; k < stop; k++) {
                result += block[k];
            }
        }
    }
    return result;
}

string place_funci(string block, string trigo) {
    string result = "";
    int     valid = 0; 
    int     trigv = 0; 
    if (trigo != "") trigv = 1;
    
    if (trigv == 1) { 
        int go = 0,en = 0;
        for (int i = 0; i < block.length(); i++) {
            if (block[i] == 40) go = i+1;
            if (block[i] == 41) en = i;
        }
        
        for(int k = go; k < en; k++) result += block[k];
    }
    else {
        int go = 0, en = 0;
        for (int i = 0; i < block.length(); i++) {
            char dcd = block[i];
            if ((dcd >= 65 && dcd <= 90) || (dcd >= 97 && dcd <= 122)) valid = 1;
            if (dcd == 94) valid = 0;

            if (valid == 1) {
                if (dcd != 40) {
                    result += block[i];
                    break;
                }
            }
            if (block[i] == 40){
                go = i+1;
                result = "";
                for (int k = go; k < block.length(); k++) {
                    if (block[k] == 40) valid++;
                    if (block[k] == 41) {
                        en = k;
                        valid--;
                    }
                }
                break;
            }
        }
        for (int k = go; k < en; k++) {
            result += block[k];
        }
    }

    return result;
}

string print_angka(int angka,int pangkat,int turunan) {
    string result = "";
    int penyebut = pangkat*turunan;

    if ((angka % ((pangkat)*turunan)) == 0) 
    {
        angka = angka/penyebut;
        result = in_st(angka);
    } 
    else {
        result  = "(";
        result += simply(in_st(angka) +"/"+in_st(penyebut));
        result += ")";
    }
    return result;
}

string turunan (string inp) {
    int const real_amount = input_block(inp);
    char             into = 'x';
    string         result = "";
    string block[real_amount];

    int z = 0;
    for(int i = 0; i < inp.length(); i++) {
        if(inp[i] == 32) {
            z++;
            i+=2;
        }
        else {
            block[z] += inp[i];
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
        
        temp_angka[i] = place_angka(block[i]);
        temp_pangk[i] = place_pangk(block[i]);
        temp_trigo[i] = place_trigo(block[i]);
        real_funci[i] = place_funci(block[i],temp_trigo[i]);
        // real_funci[i] = place_funci(block[i],temp_trigo[i],into);
    
        if ((real_funci[i] == "") && (temp_trigo[i] == "")) {
            // real_funci[i] = into;
            temp_pangk[i] = "0";
        } 
    }

    int id_opera = 0;
    for (int i = 0; i < inp.length(); i++) {
        switch(inp[i]) {
            case 43:
            case 45:
                real_opera[i] = inp[i];
                id_opera++;
            break;
        }
    }

    int     real_angka[real_amount];
    int     real_pangk[real_amount];

    string  strn_pangk[real_amount];
    string  strn_angka[real_amount];


    for(int i = 0; i < real_amount; i++) {
        real_angka[i] = st_in(temp_angka[i]);
        real_pangk[i] = st_in(temp_pangk[i]);

        strn_angka[i] += temp_angka[i];
        real_angka[i] *= real_pangk[i];
        real_pangk[i] -= 1;

        if (real_angka[i] == 1) {
            strn_angka[i] = "";
        }
        else {
            strn_angka[i] = in_st(real_angka[i]);
        }
    }


    for(int i = 0; i < real_amount; i++) {
        if (real_pangk[i] == 0) {
            if (strn_angka[i] != "") result += strn_angka[i];\
        }
        else if (real_pangk[i] == 1) {
            if (strn_angka[i] != "0" && strn_angka[i] != "1") result += strn_angka[i];  
            result += real_funci[i];
            result += " ";
            result += real_opera[i];
            result += " ";
            
        }
        else if (real_pangk[i] > 1)
        {
            if (strn_angka[i] != "0" && strn_angka[i] != "1") result += strn_angka[i];  
            result += real_funci[i];
            result += "^";
            result += in_st(real_pangk[i]);
            result += " ";
            result += real_opera[i];
            result += " ";
        }
    }
    
    return result;
}

string integral (string inp) {
    
    // Mencari banyak jumlah fungsi polinomial dari persamaan
    int const real_amount = input_block(inp);

    // Mencari panjang string input untuk pengecekan2 lanjut
    // char             into = inp[inp_length-1];
    char             into = 'x';
    string         result = "";
    string block[real_amount];

    int z = 0;
    for(int i = 0; i < inp.length(); i++) {
        if(inp[i] != 32) {block[z] += inp[i];}
        else {
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
        
        temp_angka[i] = place_angka(block[i]);
        temp_pangk[i] = place_pangk(block[i]);
        temp_trigo[i] = place_trigo(block[i]);
        real_funci[i] = place_funci(block[i],temp_trigo[i]);
        // real_funci[i] = place_funci(block[i],temp_trigo[i],into);
    
        if ((real_funci[i] == "") && (temp_trigo[i] == "")) {
            // real_funci[i] = into;
            real_funci[i] = "x";
            temp_pangk[i] = "0";
        } 
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

    int     real_angka[real_amount];
    int     real_pangk[real_amount];
    int     real_turun[real_amount];
    int     real_sebut[real_amount];
    string  prnt_angka[real_amount];
    string  prnt_turun[real_amount];


    cout << "Hasil Integral: " << endl;

    for(int i = 0; i < real_amount; i++) { 
        real_turun[i] = st_in(turunan(real_funci[i]));
        real_angka[i] = st_in(temp_angka[i]);
        real_pangk[i] = st_in(temp_pangk[i])+1;
        
        if ((real_funci[i] == "") && (temp_trigo[i] == "")) 
            {real_funci[i] = into;}

        // if (temp_trigo[i] != "") {
        //     intg_trigo(temp_trigo[i]);
        // }
        if (real_turun[i] != 0)
            {prnt_angka[i] = print_angka(real_angka[i],real_pangk[i],real_turun[i]);}
        else if (real_pangk[i] != 0)
            {prnt_angka[i] = print_angka(real_angka[i],real_pangk[i],1);}
        else if (real_pangk[i] == 0)
            {prnt_angka[i] = print_angka(real_angka[i],1,1);}
    }
    
    for(int i = 0; i < real_amount; i++) {
        result += prnt_angka[i];
        result += real_funci[i];
        result += "^";
        
        
        result += in_st(real_pangk[i]);
        result += " ";
        if (real_opera[i] != "") {
            result += real_opera[i];
            result += " ";
        }
    }
    result += "+ C";
    return result;
}

int main () {
    string inp;

    // string inp = "2x^3 + x^1";
    // string inp = "sin(3x)";
    // string inp = "sin(3x)^2";
    // string inp = "(3x)";
    
    // intg_trigo(temp_trigo[0],temp_trigf[0]);

    cout << "===============================================\n";
    cout << "  SELAMAT DATANG DI KALKULATOR INTEGRAL DASAR\n";
    cout << "===============================================\n";
    cout << "Dibuat oleh:  Afrizal Adi Nugroho     (2202834)\n";
    cout << "              Hasna Putri Priswati    (2201115)\n";
    cout << "              Muhammad Salam Pararta  (2202747)\n";
    cout << "              Rajih Nibras Maulana    (2202212)\n";
    cout << "===============================================\n";
    cout << "-----------------------------------------------\n";
    cout << "Kalkulator integral ini akan menghitung nilai integral\n";
    cout << "tak tentu dari fungsi polinomial biasa dengan pangkat\n";
    cout << "berupa bilangan bulat positif\n";
    
    cout << "\n===============================================\n";
    cout << "Masukkan fungsi polinomial yang ingin diintegralkan: \n";
    getline(cin, inp);
    cout << integral(inp);
    cout << "\n===============================================\n";
    system("pause");
    cout << "\nTerimakasih. Kalkulasi integral telah selesai dilakukan.\n";
    
    system("pause");
    system("cls");
    // cout << turunan(inp);
    return 0;
} 