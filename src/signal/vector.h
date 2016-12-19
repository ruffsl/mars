#ifndef __MARS_SIGNAL_VECTOR
#define __MARS_SIGNAL_VECTOR

    #include <stdlib.h>

    /**
    * \file     vector.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  1.0
    * \date     2016-10-25
    * \copyright
    *
    * This program is free software: you can redistribute it and/or modify
    * it under the terms of the GNU General Public License as published by
    * the Free Software Foundation, either version 3 of the License, or
    * (at your option) any later version.
    *
    * This program is distributed in the hope that it will be useful,
    * but WITHOUT ANY WARRANTY; without even the implied warranty of
    * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    * GNU General Public License for more details.
    * 
    * You should have received a copy of the GNU General Public License
    * along with this program.  If not, see <http://www.gnu.org/licenses/>.
    *
    */

    #include <string.h>
    #include <stdio.h>

    //! A structure that holds all the fields of a vector with signed int elements. 
    typedef struct vector_signedint {

        signed int * array;         ///< Pointer to the array of elements.		 
        unsigned int nElements;     ///< Number of elements.

    } vector_signedint;

    //! A structure that holds all the fields of a vector with unsigned int elements. 
    typedef struct vector_unsignedint {

        unsigned int * array;       ///< Pointer to the array of elements.		 
        unsigned int nElements;     ///< Number of elements.

    } vector_unsignedint;

    //! A structure that holds all the fields of a vector with float elements. 
    typedef struct vector_float {

        float * array;              ///< Pointer to the array of elements.		 
        unsigned int nElements;     ///< Number of elements.

    } vector_float;

    /** Constructor of the vector object.	
        \param      nElements   Number of elements.
        \return                 Pointer to the instantiated object.
    */	
    vector_signedint * vector_signedint_malloc(const unsigned int nElements);

    /** Constructor of the vector object.	
        \param      nElements   Number of elements.
        \return                 Pointer to the instantiated object.
    */	
    vector_unsignedint * vector_unsignedint_malloc(const unsigned int nElements);

    /** Constructor of the vector object.	
        \param     nElements    Number of elements.
        \return                 Pointer to the instantiated object.
    */	
    vector_float * vector_float_malloc(const unsigned int nElements);

    /** Destructor of the vector object.
        \param      obj         Pointer to the instantiated object.
    */
    void vector_signedint_free(vector_signedint * obj);

    /** Destructor of the vector object.
        \param      obj         Pointer to the instantiated object.
    */
    void vector_unsignedint_free(vector_unsignedint * obj);

    /** Destructor of the vector object.
        \param      obj         Pointer to the instantiated object.
    */
    void vector_float_free(vector_float * obj);

    /** Copy the matrix object.
        \param      objSrc      Pointer to the source object.
        \param      objDest     Pointer to the destination object.
        \return                 Return -1 if error, 0 otherwise.
    */
    int vector_signedint_copy(const vector_signedint * objSrc, vector_signedint * objDest);    

    /** Copy the matrix object.
        \param      objSrc      Pointer to the source object.
        \param      objDest     Pointer to the destination object.
        \return                 Return -1 if error, 0 otherwise.
    */
    int vector_unsignedint_copy(const vector_unsignedint * objSrc, vector_unsignedint * objDest);    

    /** Copy the matrix object.
        \param      objSrc      Pointer to the source object.
        \param      objDest     Pointer to the destination object.
        \return                 Return -1 if error, 0 otherwise.
    */
    int vector_float_copy(const vector_float * objSrc, vector_float * objDest);  

    /** Copy the vector object and generate a new object.
        \param      obj         Pointer to the source object.
        \return                 Pointer to the newly instantiated object.
    */
    vector_signedint * vector_signedint_clone(const vector_signedint * obj);

    /** Copy the vector object and generate a new object.
        \param      obj         Pointer to the source object.
        \return                 Pointer to the newly instantiated object.
    */
    vector_unsignedint * vector_unsignedint_clone(const vector_unsignedint * obj);

    /** Copy the vector object and generate a new object.
        \param      obj         Pointer to the source object.
        \return                 Pointer to the newly instantiated object.
    */
    vector_float * vector_float_clone(const vector_float * obj);

    int vector_signedint_zero(vector_signedint * obj);

    int vector_unsignedint_zero(vector_unsignedint * obj);    

    int vector_float_zero(vector_float * obj);

    /** Prints the content of the vector in the console.
        \param      obj         Pointer to the object.
        \return                 Return -1 if error, 0 otherwise.
    */    
    void vector_signedint_printf(const vector_signedint * obj);

    /** Prints the content of the vector in the console.
        \param      obj         Pointer to the object.
        \return                 Return -1 if error, 0 otherwise.
    */    
    void vector_unsignedint_printf(const vector_unsignedint * obj);    

    /** Prints the content of the vector in the console.
        \param      obj         Pointer to the object.
        \return                 Return -1 if error, 0 otherwise.
    */    
    void vector_float_printf(const vector_float * obj);    


#endif