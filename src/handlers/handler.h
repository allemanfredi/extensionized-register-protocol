
#include <string>

using namespace std;

class Handler {

    public:
        Handler(); //constructor
        bool registerProtocol( string protocol , string extension_id , string extension_name ); 
        bool removeProtocol( string protocol ); 
    private:
        
};