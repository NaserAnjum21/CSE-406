#include<bits/stdc++.h>

#define UP_BOUND 10

using namespace std;

string ptext,ctext;
vector<string> words;
int KEYLEN;
vector<int> key;
vector<string> deciphText;

string LowerString(string input)
{
    string output=input;
    for(int i=0;i<input.size();i++) output[i]=tolower(input[i]);
    return output;
}

void PrintVector(vector<string> vec)
{
    for(int i=0;i<vec.size();i++)
        cout<<vec[i]<<endl;
}

vector<int> Factorize(int n)
{
    vector<int> ret;
    for(int i=2;i<=n;i++)
    {
        if(n%i==0)
            ret.push_back(i);
    }
     return ret;
}

vector<string> MySplit(string s)
{
    vector<string> tokens;
    int i=0;
    string token="";
    while(s[i])
    {
        if(s[i]>='a' and s[i]<='z') token.push_back(toupper(s[i]));
        else{
            if(token.size()> 0) tokens.push_back(token);
            token="";
        }
        i++;

        if(s[i]==0 and token.size()>0) tokens.push_back(token);

    }

    return tokens;

}

vector<string> Split(string s, string delimiter)
{
   vector<string> tokens;
   string token;
   size_t pos=0;
   while ((pos=s.find(delimiter))!=string::npos)
   {
        token=s.substr(0,pos);
        tokens.push_back(token);
        s.erase(0, pos + delimiter.length());
   }
   return tokens;
}

vector<string> Columnize(string ct,int keylen)
{
    int len= ct.size();
    int iterCount= len/keylen;
    iterCount= (len%keylen) ? iterCount +1 : iterCount;

    vector<string> rows;
    string row;

    for(int i=0;i<iterCount;i++)
    {
        string dummy(keylen,'~');
        rows.push_back(dummy);
    }

    int j=0;
    int rem=len;

    vector<string> columns;

    for(int i=0;i<keylen;i++)
    {
        string col;
        if(rem>=iterCount)
            col= ct.substr(j,iterCount);
        else
        {
            col= ct.substr(j,rem);
            string pad((iterCount-rem),'X');
            col+=pad;
        }

        columns.push_back(col);

        j+=iterCount;
        rem-=iterCount;
    }


    for(int i=0;i<iterCount;i++)
    {
        for(int j=0;j<keylen;j++)
        {
            rows[i][j]= columns[j][i];
        }
    }

    return rows;

}

bool CheckHelper(vector<string> text, string word,int keylen)
{

    if(word.size()<keylen) return false;

    int row= ctext.size()/keylen;

    int count= word.size() - keylen;

    //cout<<row<<" "<<count<<endl;

    for(int p=0;p< word.size()-keylen ; p++ )
    {
        for(int i=0;i<row-1;i++)
        {
            for(int j=0;j<keylen;j++)
            {
                if(word[p]==text[i][j] and word[p+keylen]==text[i+1][j])
                {
                    count--;
                    goto found;
                }
            }
        }
        found:
            continue;
    }

    if(count==0) return true;
    return false;


}

bool CheckKeylenValidity(vector<string> text, int keylen)
{
    int count=0;
    for(int i=0;i<words.size();i++)
    {
        //cout<<words[i]<<endl;
        if(CheckHelper(text,words[i],keylen)) count++;
    }

    if(count==words.size()) return true;
    return false;

}

string VectorToString(vector<string> vec)
{
    string ret="";
    for(int i=0;i<vec.size();i++) ret += vec[i];
    return ret;
}

bool AreWordsPresent(string pt)
{
    for(int i=0;i<words.size();i++)
    {
        size_t pos= pt.find(words[i]);
        if(pos==string::npos) return false;
    }
    return true;
}

void FindKeyOrder(vector<string> text)
{
    vector<int> kpermutation;
    for(int i=0;i<KEYLEN;i++) kpermutation.push_back(i);

    do{

        vector<string> newtext=text;
        for(int j=0;j<KEYLEN;j++)
        {
            for(int i=0;i<text.size();i++)
            {
                newtext[i][j]= text[i][kpermutation[j]];
            }
        }
        string plaintext= VectorToString(newtext);

        if(AreWordsPresent(plaintext))
        {
            cout<<"The Deciphered text- \n\n";
            cout<<LowerString(plaintext)<<endl<<endl;

            //PrintVector(newtext);

            cout<<"\nThe key order-->> ";
            for(int i=0;i<kpermutation.size();i++) cout<<kpermutation[i]+1<<" ";
            cout<<endl;

            key=kpermutation;
            deciphText=newtext;

            break;
        }
    } while(next_permutation(kpermutation.begin(),kpermutation.end()));
}

string encode()
{
    vector<string> encodedVec=deciphText;
    for(int j=0;j<KEYLEN;j++)
    {
        for(int i=0;i<encodedVec.size();i++)
        {
            encodedVec[i][key[j]]= deciphText[i][j];
        }
    }

    string ret="";

    for(int j=0;j<KEYLEN;j++)
    {
        for(int i=0;i<encodedVec.size();i++)
        {
            ret.push_back(encodedVec[i][j]);
        }
    }

    return ret;
}

void FindAccuracy(string encodedText)
{
    int count=0;
    for(int i=0;i<ctext.size();i++)
    {
        if(ctext[i]==encodedText[i]) count++;
    }
    cout<<endl<<count<<" of "<<ctext.size()<<" characters matched\n";
    double acc= 100.0*count/ctext.size();
    cout<<"Accuracy--> "<<acc<<" percent\n";
}

void Tester(string cipher)
{
    vector<int> factors= Factorize(cipher.size());
    vector<string> vec;
    for(int k=0;k<factors.size();k++)
    {
        if(factors[k]>UP_BOUND) continue; // limiting the key length to avoid large computation

        //cout<<"\n\nChecking with key length ------- "<<factors[k]<<endl<<endl;
        vec= Columnize(cipher,factors[k]);
        //PrintVector(vec);

        if(CheckKeylenValidity(vec,factors[k]))
        {
            KEYLEN=factors[k];
            cout<<"Key Length -->> "<<factors[k]<<endl<<endl;
            break;
        }

    }

    FindKeyOrder(vec);

    string encodedText =encode();
    cout<<"\n\nAfter encoding, the cipher is - \n\n"<< encodedText<<endl<<endl;

    FindAccuracy(encodedText);

}

int main()
{

    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);


    string blank, givenWords;

    cin>>ctext;

    getline(cin,blank);
    getline(cin,blank);

    getline(cin,givenWords);

    //cout<<givenWords<<endl;

    words = MySplit(givenWords);
    //PrintVector(words);

    //cout<<ctext.size()<<endl;

    Tester(ctext);


    return 0;
}
