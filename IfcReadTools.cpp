#include "Ifcread.h"


void ParseSingleProp(std::string* sTemp, std::string* to_store)
{

	if (sTemp->find('\'') == 0)
	{
		std::stringstream pString(sTemp->substr(1));
		std::getline(pString, *to_store, '\'');
		*sTemp = sTemp->substr(to_store->size() + 3);
	}
	else
	{
		std::stringstream pString(*sTemp);
		std::getline(pString, *to_store, ',');
		*sTemp = sTemp->substr(to_store->size() + 1);
	}
}

void ParseSinglePropEnum(std::string* sTemp, std::string* to_store)
{

	if (sTemp->find('.') == 0)
	{
		std::stringstream pString(sTemp->substr(1));
		std::getline(pString, *to_store, '.');
		*sTemp = sTemp->substr(to_store->size() + 3);
	}
	else
	{
		std::stringstream pString(*sTemp);
		std::getline(pString, *to_store, ',');
		*sTemp = sTemp->substr(to_store->size() + 1);
	}
}

void ParseSinglePropEnd(std::string* sTemp, std::string* to_store)
{

	if (sTemp->find('\'') == 0)
	{
		std::stringstream pString(sTemp->substr(1));
		std::getline(pString, *to_store, '\'');
		*sTemp = sTemp->substr(to_store->size() + 3);
	}
	else
	{
		std::stringstream pString(*sTemp);
		std::getline(pString, *to_store, ')');
		*sTemp = sTemp->substr(to_store->size() + 1);
	}
}

void ParseMultiPropBrace(std::string* sTemp, std::vector<std::string>* to_store)
{

	std::string temp;
	std::string temp2;
	std::string temp3;

	std::stringstream pString(sTemp->substr(1));
	std::getline(pString, temp, ')');
	std::stringstream stData(temp);

	while (stData)
	{
		temp3 = temp2;
		std::getline(stData, temp2, ',');
		if (temp3!=temp2)
			to_store->push_back(temp2);
	}
	*sTemp = sTemp->substr(temp.size() + 3);
}