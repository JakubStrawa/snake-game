//
//  exception.h
//  Snake
//
//  Created by Jakub Strawa on 21/05/2019.
//  Copyright © 2019 Jakub Strawa. All rights reserved.
//

#ifndef exception_h
#define exception_h

class Exception{
private:
    int e;
public:
    Exception (int val = 20) : e(val) {}
    int get(){
        return e;
    }
};
#endif /* exception_h */
