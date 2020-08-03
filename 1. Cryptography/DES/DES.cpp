#include<bits/stdc++.h>

#define hi cout<<"hi"<<endl
#define PR(a) cout<<a<<endl

using namespace std;

int PI[] = {58, 50, 42, 34, 26, 18, 10, 2,
      60, 52, 44, 36, 28, 20, 12, 4,
      62, 54, 46, 38, 30, 22, 14, 6,
      64, 56, 48, 40, 32, 24, 16, 8,
      57, 49, 41, 33, 25, 17, 9, 1,
      59, 51, 43, 35, 27, 19, 11, 3,
      61, 53, 45, 37, 29, 21, 13, 5,
      63, 55, 47, 39, 31, 23, 15, 7};


int CP_1[] = {57, 49, 41, 33, 25, 17, 9,
        1, 58, 50, 42, 34, 26, 18,
        10, 2, 59, 51, 43, 35, 27,
        19, 11, 3, 60, 52, 44, 36,
        63, 55, 47, 39, 31, 23, 15,
        7, 62, 54, 46, 38, 30, 22,
        14, 6, 61, 53, 45, 37, 29,
        21, 13, 5, 28, 20, 12, 4};

int CP_2[] = {14, 17, 11, 24, 1, 5, 3, 28,
        15, 6, 21, 10, 23, 19, 12, 4,
        26, 8, 16, 7, 27, 20, 13, 2,
        41, 52, 31, 37, 47, 55, 30, 40,
        51, 45, 33, 48, 44, 49, 39, 56,
        34, 53, 46, 42, 50, 36, 29, 32};


int E[] = {32, 1, 2, 3, 4, 5,
     4, 5, 6, 7, 8, 9,
     8, 9, 10, 11, 12, 13,
     12, 13, 14, 15, 16, 17,
     16, 17, 18, 19, 20, 21,
     20, 21, 22, 23, 24, 25,
     24, 25, 26, 27, 28, 29,
     28, 29, 30, 31, 32, 1};


int PI_2[] = {35, 38, 46, 6, 43, 40, 14, 45,
		33, 19, 26, 15, 23, 8, 22, 10,
		12, 11, 5, 25, 27, 21, 16, 31,
		28, 32, 34, 24, 9, 37, 2, 1};


int P[] = {16, 7, 20, 21, 29, 12, 28, 17,
     1, 15, 23, 26, 5, 18, 31, 10,
     2, 8, 24, 14, 32, 27, 3, 9,
     19, 13, 30, 6, 22, 11, 4, 25};


int PI_1[] = {40, 8, 48, 16, 56, 24, 64, 32,
        39, 7, 47, 15, 55, 23, 63, 31,
        38, 6, 46, 14, 54, 22, 62, 30,
        37, 5, 45, 13, 53, 21, 61, 29,
        36, 4, 44, 12, 52, 20, 60, 28,
        35, 3, 43, 11, 51, 19, 59, 27,
        34, 2, 42, 10, 50, 18, 58, 26,
        33, 1, 41, 9, 49, 17, 57, 25};


int SHIFT[] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

string key,ptext,pptext;
vector<string> blocks;
vector<string> keyblocks;
vector<string> keyStore;

void PrintVector(vector<string> vec)
{
    for(int i=0;i<vec.size();i++)
        cout<<vec[i]<<endl;
}

string CharToBits(char ch)
{
    string result;
    while(ch)
    {
        result.push_back((ch%2+'0'));
        ch=ch/2;
    }
    while(result.size()!=8) result.push_back('0');

    reverse(result.begin(),result.end());
    return result;

}

string Pad(string pt)
{
    int padding_len=  (8- pt.size()%8 ) % 8;
    string pad(padding_len,'~');
    string ret= pt+ pad;
    return ret;
}

vector<string> MakeBlocks(string pt)
{
    int num_of_blocks = ceil(1.0*pt.size()/8);

    vector<string> Blocks;

    for(int i=0;i<num_of_blocks;i++)
    {
        string block="";
        for(int j=0;j<8;j++)
        {
            block += CharToBits(pt[i*8+j]);
        }
        Blocks.push_back(block);
    }
    //PrintVector(Blocks);
    return Blocks;
}

string Transpose(string input)
{
    int len= sizeof(PI)/sizeof(int);
    string output(len,'~');
    for(int i=0;i<len;i++)
        output[i]= input[PI[i]-1];

    return output;
}

string Key64to56(string input)
{
    int len= sizeof(CP_1)/sizeof(int);
    string output(len,'~');
    for(int i=0;i<len;i++)
        output[i]= input[CP_1[i]-1];

    return output;
}

string Key56to48(string input)
{
    int len= sizeof(CP_2)/sizeof(int);
    string output(len,'~');
    for(int i=0;i<len;i++)
        output[i]= input[CP_2[i]-1];

    return output;
}

string LeftRotate(string input,int idx)
{
    string output=input;
    int rotLen= SHIFT[idx];

    for(int i=0;i<input.size();i++)
    {
        int newIdx= ( i-rotLen + input.size() ) % input.size();
        output[newIdx]=input[i];
    }
    return output;
}

string Expand32to48(string input)
{
    int len= sizeof(E)/sizeof(int);
    string output(len,'~');
    for(int i=0;i<len;i++)
        output[i]= input[E[i]-1];

    return output;
}

string Xor(string A, string B)
{
    string C=A;
    for(int i=0;i<A.size();i++)
        C[i]= (A[i]==B[i]) ? '0' : '1' ;
    return C;
}

string Shrink48to32(string input)
{
    int len= sizeof(PI_2)/sizeof(int);
    string output(len,'~');
    for(int i=0;i<len;i++)
        output[i]= input[PI_2[i]-1];

    return output;
}

string Pbox(string input)
{
    int len= sizeof(P)/sizeof(int);
    string output(len,'~');
    for(int i=0;i<len;i++)
        output[i]= input[P[i]-1];

    return output;
}

string InverseTranspose(string input)
{
    int len= sizeof(PI_1)/sizeof(int);
    string output(len,'~');
    for(int i=0;i<len;i++)
        output[i]= input[PI_1[i]-1];

    return output;
}

string DES_Func(string block64,int encrypt_or_decrypt)
{
    string L= block64.substr(0,32);
    string R= block64.substr(32,32);

    string K= Key64to56(keyblocks[0]);
    string KL= K.substr(0,28);
    string KR= K.substr(28,28);


    for(int i=0;i<16;i++)
    {
        int idx;
        if(encrypt_or_decrypt==0) //encryption
        {
            KL = LeftRotate(KL,i);
            KR= LeftRotate(KR,i);
            string mergedK= KL + KR;
            keyStore.push_back(mergedK);
            idx=i;
        }
        else idx=15-i;

        //string mergedK= LeftRotate(KL,idx) + LeftRotate(KR,idx);

        string Ki = Key56to48(keyStore[idx]);

        string R48= Expand32to48(R);

        string xoredStr = Xor(R48,Ki);

        string shortStr = Shrink48to32(xoredStr);

        string func= Pbox(shortStr);

        string tempL=L;
        L = R;
        R= Xor(tempL, func );
    }

    string data= R + L; //swap

    string finalData= InverseTranspose(data);

    return finalData;
}

int BitsToChar(string bits)
{
    int ch=0;
    int prod=1;
    reverse(bits.begin(),bits.end());
    for(int i=0;i<bits.size();i++)
    {
        int temp = bits[i]- '0';
        ch += temp*prod;
        prod*=2;
    }
    return ch;
}

string BlocksToString(vector<string> chunks)
{
    string text;
    for(int i=0;i<chunks.size();i++)
    {
        for(int j=0;j<64;j+=8)
        {
            string temp = chunks[i].substr(j,8);
            text.push_back((unsigned char) BitsToChar(temp));
        }
    }
    return text;
}

void encrypt()
{
    for(int i=0;i<blocks.size();i++)
     {
         blocks[i] = Transpose(blocks[i]);
         blocks[i]=DES_Func(blocks[i],0);
     }
     cout<<"Ciphered: ";
     cout<<BlocksToString(blocks)<<endl;
}

string RemovePadding(string str)
{
    string result;
    for(int i=0;i<str.size();i++)
    {
        if(str[i]!='~') result.push_back(str[i]);
    }
    return result;
}

void decrypt()
{
    for(int i=0;i<blocks.size();i++)
     {
         blocks[i] = Transpose(blocks[i]);
         blocks[i]=DES_Func(blocks[i],1);
     }

     string deciphered = BlocksToString(blocks);
     cout<<"Deciphered: ";
     cout<<RemovePadding(deciphered)<<endl;
}

void solve()
{
     //cout<<CharToBits('p')<<endl;
     //cout<<BitsToChar("01111001")<<endl;
     pptext= Pad(ptext);
     blocks= MakeBlocks(pptext);
     keyblocks= MakeBlocks(key);

     encrypt();
     decrypt();

}

int main()
{

    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    getline(cin,key);
    getline(cin,ptext);

    solve();

    return 0;
}
