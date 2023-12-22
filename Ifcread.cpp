#include "Ifcread.h"

std::map<int, std::string> PSDC{
	{8,"Reference"},
	{9,"FireRating"},
	{10,"AcousticRating"},
	{11,"SecurityRating"},
	{12, "IsExternal"},
	{13, "Infiltration"},
	{14, "ThermalTransmittance"},
	{15, "GlazingAreaFraction"},
	{16, "HandicapAccessible"},
	{17,"FireExit"},
	{18,"SelfClosing"},
	{19,"SmokeStop"}
};


void IFCDOORRELOBJECTS::ReadIfcDoors(std::string temp)
{
	STARTREADIFCOBJ(IFCDOOR);
	
	//for (int i = 0 ; i < MAXRELATION; i++) { &IFCTYPE.relationsToList[i] = RELUNDEFINED; }
	
	ParseSingleProp(&sTemp, &IFCTYPE.p01GlobalId);
	ParseSingleProp(&sTemp, &IFCTYPE.p02OwnerHistory);
	ParseSingleProp(&sTemp, &IFCTYPE.p03Name);
	ParseSingleProp(&sTemp, &IFCTYPE.p04Description);
	ParseSingleProp(&sTemp, &IFCTYPE.p05ObjectType);
	ParseSingleProp(&sTemp, &IFCTYPE.p06ObjectPlacement);
	ParseSingleProp(&sTemp, &IFCTYPE.p07Representation);
	ParseSingleProp(&sTemp, &IFCTYPE.p08Tag);
	
	std::stringstream pString(sTemp);
	std::getline(pString, temp2, ',');
	IFCTYPE.p09OverallHeight = std::stod(temp2);
	std::getline(pString, temp2, ',');
	IFCTYPE.p10OverallWidth = std::stod(temp2);

	ENDREADIFCOBJ(IFCDOORS);
}

//Doorstyles

void IFCDOORRELOBJECTS::ReadIfcDoorStyles(std::string temp)
{
	STARTREADIFCOBJ(IFCDOORSTYLE);

	ParseSingleProp(&sTemp, &IFCTYPE.p01GlobalId);
	ParseSingleProp(&sTemp, &IFCTYPE.p02OwnerHistory);
	ParseSingleProp(&sTemp, &IFCTYPE.p03Name);
	ParseSingleProp(&sTemp, &IFCTYPE.p04Description);
	ParseSingleProp(&sTemp, &IFCTYPE.p05ObjectType);
	ParseMultiPropBrace(&sTemp, &IFCTYPE.p06props);
	ParseMultiPropBrace(&sTemp, &IFCTYPE.p07props);
	ParseSingleProp(&sTemp, &IFCTYPE.p08Tag);
	ParseSinglePropEnum(&sTemp, &IFCTYPE.p09IfcDoorStyleOperationEnum);
	ParseSinglePropEnum(&sTemp, &IFCTYPE.p10IfcDoorStyleConstructionEnum);

	ENDREADIFCOBJ(IFCDOORSTYLES);
}

void IFCDOORRELOBJECTS::ReadRelDefByTypes(std::string temp)
{

	STARTREADIFCOBJ(IFCRELDEFINESBYTYPE);

	ParseSingleProp(&sTemp, &IFCTYPE.p01GlobalId);
	ParseSingleProp(&sTemp, &IFCTYPE.p02OwnerHistory);
	ParseSingleProp(&sTemp, &IFCTYPE.p03Name);
	ParseSingleProp(&sTemp, &IFCTYPE.p04Description);
	ParseMultiPropBrace(&sTemp, &IFCTYPE.p05RelatedObjects_str);
	ParseSinglePropEnd(&sTemp, &IFCTYPE.p06RelatingObject_str);

	ENDREADIFCOBJ(IFCRELDEFINESBYTYPES);
}

/*
void IFCDOORRELOBJECTS::ReadRelDefByTypesAfterRead()
{
	for (int n = 0; n < IFCRELDEFINESBYTYPES.size(); n++)
	{
		for (int i = 0; i < IFCDOORSTYLES.size(); i++)
		{
			if (IFCRELDEFINESBYTYPES[n].p06RelatingType_str == IFCDOORSTYLES[i].p00IfcId)
			{
				IFCRELDEFINESBYTYPES[n].p06RelatingType = i;
			}
		}
	}
	
	for (int n = 0; n < IFCRELDEFINESBYTYPES.size(); n++)
	{
		if (IFCRELDEFINESBYTYPES[n].p06RelatingType == RELUNDEFINED)
			continue;
		for (int i = 0; i < IFCDOORSTYLES.size(); i++)
		{

			if (IFCDOORSTYLES[IFCRELDEFINESBYTYPES[n].p06RelatingType].p00IfcId == IFCDOORSTYLES[i].p00IfcId)
			{

				for (int k = 0; k < IFCRELDEFINESBYTYPES[n].p05RelatedObjects.size(); k++)
				{
					for (int j = 0; j < IFCDOORS.size(); j++)

					{
						if (IFCRELDEFINESBYTYPES[n].p05RelatedObjects[k] == IFCDOORS[j].p00IfcId)
						{
							IFCRELDEFINESBYTYPES[n].p05RelatedDoors.push_back(j);
							IFCDOORS[j].shpDoorstyle = i;
						}
					}
				}
			}
		}
	}
}
*/
//Properties


void IFCDOORRELOBJECTS::ReadRelDefinesByProperties(std::string temp)
{

	STARTREADIFCOBJ(IFCRELDEFINESBYPROPERTIES);

	ParseSingleProp(&sTemp, &IFCTYPE.p01GlobalId);
	ParseSingleProp(&sTemp, &IFCTYPE.p02OwnerHistory);
	ParseSingleProp(&sTemp, &IFCTYPE.p03Name);
	ParseSingleProp(&sTemp, &IFCTYPE.p04Description);
	ParseMultiPropBrace(&sTemp, &IFCTYPE.p05RelatedObjects_str);
	ParseSinglePropEnd(&sTemp, &IFCTYPE.p06RelatingObject_str);

	ENDREADIFCOBJ(IFCRELDEFINESBYPROPERTIESES);
}

void IFCDOORRELOBJECTS::ReadPropertySets(std::string temp)
{
	STARTREADIFCOBJ(IFCPROPERTYSET);

	ParseSingleProp(&sTemp, &IFCTYPE.p01GlobalId);
	ParseSingleProp(&sTemp, &IFCTYPE.p02OwnerHistory);
	ParseSingleProp(&sTemp, &IFCTYPE.p03Name);
	ParseSingleProp(&sTemp, &IFCTYPE.p04Description);
	//ParseMultiPropBrace(&sTemp, &IFCTYPE.p05RelatedObjects_str);

	std::vector<std::string> to_store;
	ParseMultiPropBrace(&sTemp, &to_store);

	for (int k = 0; k < to_store.size(); k++)
	{
		for (int j = 0; j < IFCPROPERTYSINGLEVALUES.size(); j++)

		{
			if (to_store[k] == IFCPROPERTYSINGLEVALUES[j].p00IfcId)
			{
				IFCTYPE.p05RelatedObjects.push_back(j);
			}
		}
	}

	ENDREADIFCOBJ(IFCPROPERTYSETS);
}

void IFCDOORRELOBJECTS::ReadPropertySingleValues(std::string temp)
{
	STARTREADIFCOBJ(IFCPROPERTYSINGLEVALUE);

	ParseSingleProp(&sTemp, &IFCTYPE.p01propertyname);
	ParseSingleProp(&sTemp, &IFCTYPE.p02void);
	ParseSingleProp(&sTemp, &IFCTYPE.p03propertyValue);
	ParseSingleProp(&sTemp, &IFCTYPE.p04void);
	
	ENDREADIFCOBJ(IFCPROPERTYSINGLEVALUES);
}



/*
void IFCDOORRELOBJECTS::ReadRelDefinesByPropertiesAfterRead()
{
	
	for (int n = 0; n < IFCRELDEFINESBYTYPES.size(); n++)
	{
		for (int i = 0; i < IFCDOORSTYLES.size(); i++)
		{
			if (IFCRELDEFINESBYTYPES[n].p06RelatingType_str == IFCDOORSTYLES[i].p00IfcId)
			{
				IFCRELDEFINESBYTYPES[n].p06RelatingType = i;
			}
		}
	}

	for (int n = 0; n < IFCRELDEFINESBYTYPES.size(); n++)
	{
		if (IFCRELDEFINESBYTYPES[n].p06RelatingType == RELUNDEFINED)
			continue;
		for (int i = 0; i < IFCDOORSTYLES.size(); i++)
		{

			if (IFCDOORSTYLES[IFCRELDEFINESBYTYPES[n].p06RelatingType].p00IfcId == IFCDOORSTYLES[i].p00IfcId)
			{

				for (int k = 0; k < IFCRELDEFINESBYTYPES[n].p05RelatedObjects.size(); k++)
				{
					for (int j = 0; j < IFCDOORS.size(); j++)

					{
						if (IFCRELDEFINESBYTYPES[n].p05RelatedObjects[k] == IFCDOORS[j].p00IfcId)
						{
							IFCRELDEFINESBYTYPES[n].p05RelatedDoors.push_back(j);
							IFCDOORS[j].relationsToList[r01_Doorstyle] = i;
						}
					}
				}
			}
		}
	}
}
*/


//Material

void IFCDOORRELOBJECTS::ReadIfcMaterials(std::string temp)
{
	STARTREADIFCOBJ(IFCMATERIAL);

	ParseSinglePropEnd(&sTemp, &IFCTYPE.p01Material);
	ENDREADIFCOBJ(IFCMATERIALS);
}

void IFCDOORRELOBJECTS::ReadIfcMateriallists(std::string temp)
{
	//sTemp and IFCTYPE generated by macro
	STARTREADIFCOBJ(IFCMATERIALLIST);

	std::vector<std::string> to_store;
	ParseMultiPropBrace(&sTemp, &to_store);

	for (int k = 0; k < to_store.size(); k++)
	{
		for (int j = 0; j < IFCMATERIALS.size(); j++)

		{
			if (to_store[k] == IFCMATERIALS[j].p00IfcId)
			{
				IFCTYPE.p01RelatedObjects.push_back(j);
			}
		}
	}
	
	ENDREADIFCOBJ(IFCMATERIALLISTS);
}

void IFCDOORRELOBJECTS::ReadRelAssociatesMaterials(std::string temp)
{
	STARTREADIFCOBJ(IFCRELASSOCIATESMATERIAL);
	ParseSingleProp(&sTemp, &IFCTYPE.p01GlobalId);
	ParseSingleProp(&sTemp, &IFCTYPE.p02OwnerHistory);
	ParseSingleProp(&sTemp, &IFCTYPE.p03Name);
	ParseSingleProp(&sTemp, &IFCTYPE.p04Description);
	ParseMultiPropBrace(&sTemp, &IFCTYPE.p05RelatedObjects_str);
	ParseSinglePropEnd(&sTemp, &IFCTYPE.p06RelatingObject_str);
	ENDREADIFCOBJ(IFCRELASSOCIATESMATERIALS);
}

/*
void IFCDOORRELOBJECTS::ReadRelAssociatesMaterialsAfterRead()
{
	for (int n = 0; n < IFCRELASSOCIATESMATERIALS.size(); n++)
	{
		for (int i = 0; i < IFCMATERIALLISTS.size(); i++)
		{
			if (IFCRELASSOCIATESMATERIALS[n].p06RelatingType_str == IFCMATERIALLISTS[i].p00IfcId)
			{
				IFCRELASSOCIATESMATERIALS[n].p06RelatingType = i;
			}
		}
	}
	
	for (int n = 0; n < IFCRELASSOCIATESMATERIALS.size(); n++)
	{
		if (IFCRELASSOCIATESMATERIALS[n].p06RelatingType == RELUNDEFINED)
			continue;
		for (int i = 0; i < IFCMATERIALLISTS.size(); i++)
		{

			if (IFCMATERIALLISTS[IFCRELASSOCIATESMATERIALS[n].p06RelatingType].p00IfcId == IFCMATERIALLISTS[i].p00IfcId)
			{
				for (int k = 0; k < IFCRELASSOCIATESMATERIALS[n].p05RelatedObjects.size(); k++)
				{
					for (int j = 0; j < IFCDOORS.size(); j++)

					{
						if (IFCRELASSOCIATESMATERIALS[n].p05RelatedObjects[k] == IFCDOORS[j].p00IfcId)
						{
							IFCRELASSOCIATESMATERIALS[n].p05RelatedDoors.push_back(j);
							IFCDOORS[j].relationsToList[r02_Materiallist] = i;
						}
					}
				}
			}
		}
	}
}
*/


// Main read function

void ReadFromIFC(LPWSTR szFile, IFCDOORRELOBJECTS* IFCS)
{
	
	IFCS->Reset();
	IFCS->FileName = szFile;
	std::wstring ws(szFile);
	std::string ifcFile = std::string(ws.begin(), ws.end());

	std::ifstream stData;
	stData.open(ifcFile);  //stData contains the whole IFC file at this time
	std::string temp;

	if (!stData.is_open())
		temp = "Nincs nyitva";

	// Parsing
	while (stData)
	{
		std::getline(stData, temp, '\n');
		
		if (temp.find(IFCDOOR().ParseID) != std::string::npos)
			IFCS->ReadIfcDoors(temp);
		if (temp.find(IFCDOORSTYLE().ParseID) != std::string::npos)
			IFCS->ReadIfcDoorStyles(temp);
		if (temp.find(IFCRELDEFINESBYTYPE().ParseID) != std::string::npos)
			IFCS->ReadRelDefByTypes(temp);

		if (temp.find(IFCMATERIALLIST().ParseID) != std::string::npos)
			IFCS->ReadIfcMateriallists(temp);
		if (temp.find(IFCMATERIAL().ParseID) != std::string::npos)
			IFCS->ReadIfcMaterials(temp);
		if (temp.find(IFCRELASSOCIATESMATERIAL().ParseID) != std::string::npos)
			IFCS->ReadRelAssociatesMaterials(temp);

		if (temp.find(IFCPROPERTYSET().ParseID) != std::string::npos)
			IFCS->ReadPropertySets(temp);
		if (temp.find(IFCPROPERTYSINGLEVALUE().ParseID) != std::string::npos)
			IFCS->ReadPropertySingleValues(temp);
		if (temp.find(IFCRELDEFINESBYPROPERTIES().ParseID) != std::string::npos)
			IFCS->ReadRelDefinesByProperties(temp);


	}
	
	//after reading IFC file
	IFCS->AfterRead();
	
	//Create list to show in Dialog Window
	CreateIfcDoorsToList(IFCS);

	stData.close();
}
