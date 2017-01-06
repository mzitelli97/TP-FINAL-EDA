/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StrNmbrFieldToArray.h
 * Author: javier
 *
 * Created on December 22, 2016, 7:25 PM
 */

#ifndef STRNMBRFIELDTOARRAY_H
#define STRNMBRFIELDTOARRAY_H
#include <iostream>
#include <string>


using namespace std;

void strNmbrFieldToArray(string &field, unsigned char *buffer, unsigned int *length);
void arrayToStrNmbrField(string *field, unsigned char *buffer, unsigned int length);



#endif /* STRNMBRFIELDTOARRAY_H */

