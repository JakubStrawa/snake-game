//
//  exception.h
//  Snake
//
//  Created by Jakub Strawa on 21/05/2019.
//  Copyright © 2019 Jakub Strawa. All rights reserved.
//

#ifndef exception_h
#define exception_h

/*!
 * \file
 * \brief Definition of Exception class
 *
 * Exception class used in move excepction when snake moves outside game borders
 */

/*!
 * \brief Exception class definition
 *
 * Exception class used in move excepction when snake moves outside game borders
 */
class Exception{
private:
    /*!
     * \brief E value used in throwing/catching
     */
    int e;
public:
    /*!
     * \brief Exception class constructor
     */
    Exception (int val = 20) : e(val) {}
    /*!
     * \brief E value getter
     */
    int get(){
        return e;
    }
};
#endif /* exception_h */
