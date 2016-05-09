
//
// Created by Ivo Georgiev on 5/3/16.
//

#ifndef UCD_CSCI2312_PA5_IMPL_CUSTOM_ITERATOR_H
#define UCD_CSCI2312_PA5_IMPL_CUSTOM_ITERATOR_H

// Naive partial implementation of a custom iterator.
// After Jeet Sukumaran https://github.com/jeetsukumaran

#include <cstddef>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <initializer_list>

namespace CS2312 {

    template <typename T>
    class fixed_array {

    public:

        typedef std::size_t size_type;

        class iterator {

        public:

            typedef iterator self_type;
            typedef T value_type;
            typedef T& reference;
            typedef T* pointer;
            typedef std::forward_iterator_tag iterator_category;
            typedef size_type difference_type;

            iterator(pointer ptr)
            {
                __ptr = ptr;
            }

            self_type operator++()
            {
                __ptr++;        //increments ptr
                return *this;   //returns the current object
            }

            self_type operator++(int junk)
            {
                self_type last = *this;
                __ptr++;
                return last;
            }

            reference operator*()
            {
                return *__ptr;
            }

            pointer operator->()
            {
                return __ptr;
            }

            bool operator==(const self_type& rhs) const{
                return __ptr == rhs.__ptr;
            }

            bool operator!=(const self_type& rhs) const{
                return __ptr != rhs.__ptr;
            }


        private:

            pointer __ptr;

        };  //end of fixed__array class

        class const_iterator {

        public:

            typedef const_iterator self_type;
            typedef T value_type;
            typedef T& reference;
            typedef T* pointer;
            typedef std::forward_iterator_tag iterator_category;
            typedef size_type difference_type;

            const_iterator(pointer ptr)
            {
                __ptr = ptr;
            }

            self_type operator++()
            {
                __ptr++;
                return *this;
            }

            self_type operator++(int junk)
            {
                __ptr++;
                return *this;
            }

            const value_type& operator*() const
            {
                return *__ptr;
            }

            const value_type* operator->() const
            {
                return __ptr;
            }

            bool operator==(const self_type& rhs) const
            {
                return __ptr == rhs.__ptr;
            }

            bool operator!=(const self_type& rhs) const
            {
                return __ptr != rhs.__ptr;
            }

        private:

            pointer __ptr;

        };  //end of const_iterator class


        fixed_array(size_type size)
        {
            //set variables
            __size = size;

            //data will hold new object T initialized
            //with __ size.
            __data = new T[__size];
        }

        fixed_array(std::initializer_list<T> list)
        {
            __size = list.size();
            __data = new T[list.size()];
            int counter = 0;

            for(auto it = list.begin(); it != list.end(); it++, counter++)

            {      //will traverse the list and will increment counter variable
                __data[counter] = *it;
            }
        }

        //Dtor for Fixed array.
        //Deletes fixed_array objects. .
        ~fixed_array()
        {
            delete []__data;
        }

        size_type size() const
        {
            //return size variable
            return __size;
        }

        T& operator[](size_type index)
        {
            //assert that the index is less than size.
            //if true, return the data at the index location.
            assert(index < __size);
            return __data[index];
        }

        const T& operator[](size_type index) const
        {
            //assert index is less than size,
            //if true, return data at index location.
            assert(index < __size);
            return __data[index];
        }

        //ITERATOR FUNCTIONS
        iterator begin()
        {
            //at the beginning of the iterator, give
            //the array address
            return iterator(__data);
        }

        iterator end()
        {
            //At end of iterator, give the array address
            //plus 1 so adjust for the off-by-one-count.
            return iterator(__data + __size);
        }

        const_iterator begin() const
        {

            return const_iterator(__data + __size);
        }

        const_iterator end() const
        {
            return const_iterator(__data + __size);
        }

    private:

        T* __data;
        size_type __size;

    };

}

#endif //UCD_CSCI2312_PA5_IMPL_CUSTOM_ITERATOR_H
