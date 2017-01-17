/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "ProtocolFunctions.h"
#include <string>

void strNmbrFieldToArray(string &field, unsigned char *buffer, unsigned int *length) //Le llega "12,3,20,4"y sale [(0x0C),(0x03),(0x14),(0x04)]
{
	unsigned int i = 0;
	size_t found;
	size_t currentPos = 0;
	string auxStr2;
	found = field.find(',', currentPos);
	if (found != string::npos)
	{
		do
		{
			size_t aux = currentPos;
			string auxStr = field.substr(aux, found - currentPos);
			buffer[i] = stoi(auxStr, nullptr);
			currentPos = found + 1;
			i++;
		} while ((found = field.find(',', currentPos)) != string::npos);
		auxStr2 = field.substr(currentPos, field.length() - currentPos);
		buffer[i] = stoi(auxStr2, nullptr);
		currentPos = found + 1;
		i++;
	}
	else
	{
		buffer[i] = stoi(field, nullptr);
		i++;
	}
	*length = i;
}
void arrayToStrNmbrField(string *field, unsigned char *buffer, unsigned int length)
{
	string straux;
	char arrayaux[3];			//Siempre se trabaja con 2 cifras como m�ximo.
	straux.clear();
	for (unsigned int i = 0; i < length; i++)
	{
		sprintf(arrayaux, "%d", (unsigned int)buffer[i]);
		straux += arrayaux;
		if (i != (length - 1))
			straux += ",";
		arrayaux[0] = '\0';
	}
	*field = straux;
}
CardLocation protocolToCardLocation(std::string location)
{
	CardLocation retVal;
	retVal.row = (unsigned int) location[1] - '1';
	retVal.column = (unsigned int) location[0] - 'A';
	retVal.floor = (unsigned int) location[3] - '1';
	return retVal;
	
}
std::string cardLocationToProtocol(CardLocation &cardLocation)
{
	char rowChar = '1' + (char)cardLocation.row;
	char columnChar = 'A' + (char)cardLocation.column;
	char floorChar = '1' + (char)cardLocation.floor;
	std::string aux1(1, rowChar);
	std::string aux2(1, columnChar);
	std::string aux3(1, 'F');
	std::string aux4(1, floorChar);
	std::string retVal = aux2 + aux1 + aux3 + aux4;
	return retVal;
}
