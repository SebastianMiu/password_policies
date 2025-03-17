#include <iostream>
#include <string>
#include <vector>


using namespace std;

class Policy{
  protected:
  bool isChecked;
  public:
  virtual void check(const string& password)=0;
  
  bool getCheck() const{
      return isChecked;
  }
};

class LengthPolicy : public Policy{
    private:
    uint16_t minLength;
    uint16_t maxLength;
    public:
   LengthPolicy(uint16_t min): minLength(min), maxLength(255){};
   LengthPolicy(uint16_t min, uint16_t max) : minLength(min), maxLength(max){};
   void check(const string& password){
               
        if(password.size()>=minLength&&password.size()<=maxLength){
            isChecked=true;}
        else isChecked=false;

        }
    
};

class ClassPolicy : public Policy{
    private:
    uint16_t minClassCount;
    public:
    ClassPolicy(uint16_t min){
        minClassCount=min;
    }
    void check(const string&  password){
        bool lower=false, upper=false, digit=false, other=false;
        uint16_t ClassCount=0;
        for(int i=0;i<password.size();i++){
            char character=password[i];
            if(islower(character)&&!lower){
                lower=true;
                ClassCount++;
            }
            else if(isupper(character)&&!upper){
                upper=true;
                ClassCount++;
            }
            else if(isdigit(character)&&!digit){
                digit=true;
                ClassCount++;
            }
            else if(!isalpha(character)&&!isdigit(character)&&!other){
                other=true;
                ClassCount++;
            }
            
        }
        if(minClassCount<=ClassCount) isChecked=true;
        else isChecked=false;
    
        
    }
    
};

class IncludePolicy : public Policy{
    private:
    char characterType;
    public:
   
    IncludePolicy(char Type){
        characterType=Type;
    }
    void check(string const& password){
        isChecked=false;
       
        for(int i=0;i<password.length();i++){
            if(isChecked==true) break;
            char c=password[i];
            switch(characterType){
            case 'A': if (isupper(c)) {
                isChecked=true;
                break;
            }
            case 'a' : if (islower(c)) {
                isChecked=true;
                break;
            }
            case '0' : if (isdigit(c)) {
                isChecked=true;
                break;
            }
            case '$' : if(!isalpha(c)&&!isdigit(c)){
              isChecked=true;
                break;
            }
        }
    }
     
}
};

class NotIncludePolicy : public Policy{
    private:
    char characterType;
    public:
    NotIncludePolicy(char Type): characterType(Type){};
    void check(string const& password){
        isChecked=true;
        bool isUpper=isupper(characterType);
        bool isLower=islower(characterType);
        bool isDigit=isdigit(characterType);
        bool isAlpha=isalpha(characterType);
        for(int i=0;i<password.size();i++){
            char c=password[i];
            if (isUpper&&isupper(c)) {
                isChecked=false;
                break;
            }
            if (isLower&&islower(c)) {
                isChecked=false;
                break;
            }
            if (isDigit&&isdigit(c)) {
                isChecked=false;
                break;
            }
            if(isAlpha&&isalpha(c)){
                isChecked=false;
                break;
            }
        }
       
    }
};

class RepetitionPolicy : public Policy{
    private:
    uint16_t maxCount;
    public:
    RepetitionPolicy(uint16_t Count){
        maxCount=Count;
    }
    void check(string const& password) {
       isChecked=true;
        for(int i=0;i<password.length();i++){
            char c=password[i];
            uint16_t counter=1;
            for(int j=i+1;j<password.size();j++){
                if(password[j]==c) counter++;
                else {
                    c = password[j];
                    break;
                }
            }
            if(counter>maxCount) {
                isChecked=false;
                break;
            }
        
        }
    }
    
};

class ConsecutivePolicy : public Policy{
    private:
    uint16_t maxCount;
    public:
    ConsecutivePolicy(uint16_t Count){
        maxCount=Count;
    }
    void check(string const& password){
        isChecked=true;
        uint16_t counter=1;
        for(int i=1;i<password.length();i++){
            if(password[i]-password[i-1]==1){
                counter++;
                if(counter>maxCount){
                    isChecked=false;
                    break;
                }
            }
            else counter=1;
        }
        
    }
    
};

string checkPassword(string pass, vector<Policy*> politics){
    for(int i=0;i<politics.size();i++){
        politics[i]->check(pass);
        if(politics[i]->getCheck()==false) return "NOK";
    }
    return "OK";
}


int main(){
    int n;
    cin>>n;
    vector<Policy*> politics;
    string cond;
    string pass;
    for(int i=0;i<n;i++){
        
        cin>>cond;
        if(cond=="length"){
            uint16_t min, max;
            char space;
            cin>>min;
            scanf("%c", &space);
            if(space==' '){
            cin>>max;
            politics.push_back(new LengthPolicy(min,max));
            continue;
            }
            politics.push_back(new LengthPolicy(min));
            
        }
        else if(cond=="include"){
            char type;
            cin>>type;
            politics.push_back(new IncludePolicy(type));
        }
        else if(cond=="ninclude"){
            char type;
            cin>>type;
            politics.push_back(new NotIncludePolicy(type));
        }
        else if(cond=="repetition"){
            int max;
            cin>>max;
            politics.push_back(new RepetitionPolicy(max));
        }
        else if(cond=="consecutive"){
            int max;
            cin>>max;
            politics.push_back(new ConsecutivePolicy(max));
        }
        else if(cond=="class"){
            int v;
            cin>>v;
            politics.push_back(new ClassPolicy(v));
        }
    }
    
    string parola; 
    while(cin>>parola){
    cout<<checkPassword(parola, politics)<<"\n";
    }
    
    
    
    return 0;
}