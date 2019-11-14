class DynamicString {
    string *arr;
    int stringSize;
    int numOfLines;
public:
    DynamicString(int StringSize);
    void AddLine(string txt);
    string GetLine(int indx);
    int getStringSize();
    void removeAll();
};

//Dynamic String
DynamicString::DynamicString(int StringSize){

    if (StringSize < 1){
        stringSize = 1;
    }else{
        stringSize = StringSize;
    }

    numOfLines = 0;
    arr = new string[stringSize];
}

//Add Lines
void DynamicString::AddLine(string txt){
    if (numOfLines == stringSize){
        int temp = stringSize;
        stringSize  = stringSize*2;
        string* newStr = new string[stringSize];
        for (int i = 0; i <temp; i++){
            newStr[i] = arr[i];
        }
        delete[] arr;
        arr = newStr;
        arr[numOfLines] = txt;
        numOfLines ++ ;
    }else{
        arr[numOfLines] = txt;
        numOfLines ++ ;
    }
}

string DynamicString::GetLine(int indx){
    return arr[indx];
}

int DynamicString::getStringSize(){
    return stringSize;
}
void DynamicString::removeAll(){
    string *temp = new string[0];
    this->arr = temp;
    this->stringSize = 0;
    this->numOfLines = 0;
    delete [] temp;
}
